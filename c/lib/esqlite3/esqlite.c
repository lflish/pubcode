/** 
* @file sqlite3ex.c
* @date 2020-10-28 05:58:29
* @details 封装sqlite3接口，老版本ssd-db.c暂时保留
* @author lflish
* @par create
**/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "esqlite.h"


int esqlite_busy_handle_callback(void *ptr,int count)
{
        usleep(500000);
        return 1;
}

esqlite *esqlite_open(const char *dbfile, int flag, void *value)
{
	if(dbfile == NULL)
		return NULL;

	esqlite *edb = malloc(sizeof(esqlite));
	if(edb == NULL)
		return NULL;

	if(SQLITE_OK == sqlite3_open_v2(dbfile, &edb->conn, flag, NULL))
		sqlite3_busy_handler(edb->conn, esqlite_busy_handle_callback, (void *)edb->conn);
		return edb;

	EFREE(edb);
	return NULL;
}

int esqlite_set(esqlite *db, int flag, void *value, void *value2)
{
	switch(flag){
		case ESQL_BUSY_HANDLE:
			db->sqlite_busy_handle = value;
			sqlite3_busy_handler(db->conn, db->sqlite_busy_handle, (void *)db->conn);
			break;
		case ESQL_ENCRYPT_HANDLE:
			db->encrypt_handle  = value;
			db->encrypt_destroy = value2;
			break;
		case ESQL_DECRYPT_HANDLE:
			db->decrypt_handle  = value;
			db->decrypt_destroy = value2;
			break;
		default:
			break;
	}
	return 0;
}

int esqlite_exec(esqlite *db, const char *sql, void *vlaue)
{
	int ret = 0;
	char *err_msg;

	ret = sqlite3_exec(db->conn, sql, NULL, NULL, &err_msg);
	if(ret != SQLITE_OK){
		fprintf(stderr, "Exec::%s|%s\n", sql, err_msg);
		sqlite3_free(err_msg);
		return ESQLITE_ERR;
	}

	return ESQLITE_OK;
}

int esqlite_exec_cbk(esqlite *db, const char *sql, int (*callback)(void*,int,char**,char**), void *args)
{
	int ret = 0;
	char *err_msg;

	ret = sqlite3_exec(db->conn, sql, callback, args, &err_msg);
	if(ret != SQLITE_OK){
		fprintf(stderr, "Exec::%s|%s\n", sql, err_msg);
		sqlite3_free(err_msg);
		return ESQLITE_ERR;
	}

	return ESQLITE_OK;
}


int esqlite_prepare(esqlite *db, sqlite3_stmt **stmt, const char *sql, esql_args *head)
{
	int i = 0;
	esql_args *node = head->next;
	char *value = NULL;

	if(db->conn == NULL || sql == NULL)
		return ESQLITE_ERR;

	if(SQLITE_OK != sqlite3_prepare_v2(db->conn, sql, strlen(sql), stmt, NULL))
		return ESQLITE_ERR;

	sqlite3_busy_handler(db->conn, db->sqlite_busy_handle, NULL);

	for(i = 1; node != NULL; node = node->next, i++){
		switch(node->type){
			case DOUBLE:
				sqlite3_bind_double(*stmt, i, *(double *)node->value);
				break;
			case INT:
				sqlite3_bind_int(*stmt, i, *(int *)node->value);
				break;
			case INT64:
				sqlite3_bind_int64(*stmt, i, *(long *)node->value);
				break;
			case TEXT:{
				if(node->encry == ESQLTE_ENCRYPT_NO){
					sqlite3_bind_text(*stmt, i, node->value, -1, SQLITE_STATIC);
					break;
				}
				value = ((char *(*)(char *))db->encrypt_handle)(node->value);
				if(value == NULL)
					goto err;

				sqlite3_bind_text(*stmt, i, value, -1, SQLITE_TRANSIENT);
				EFREE(value);	
				break;
			}
			case VALUE:
				//sqlite3_bind_value(stmt, i, (const sqlite3_value *)node->value);
				break;
			default:
				goto err;
		}
	}

	return ESQLITE_OK;
err:
	sqlite3_finalize(*stmt);
	return ESQLITE_ERR;
}

int esqlite_exec_v2(esqlite *db, const char *sql, esql_args *head)
{
	sqlite3_stmt *stmt;
	int ret = 0;

	ret = esqlite_prepare(db, &stmt, sql, head);
	if(ret != ESQLITE_OK)
		return ESQLITE_ERR;

	ret = sqlite3_step(stmt);
	if(ret != SQLITE_DONE)
		ret = ESQLITE_ERR;

	sqlite3_finalize(stmt);

	return ret;
}

int esqlite_get_table(esqlite *db, const char *sql, char ***dbresult, int *nrow, int *ncol, char **errmsg)
{
	if(sql == NULL || db == NULL || dbresult == NULL || nrow == NULL || ncol == NULL)
		return ESQLITE_ERR;

	if(SQLITE_OK != sqlite3_get_table(db->conn, sql, dbresult, nrow, ncol, errmsg)){
		return ESQLITE_ERR;
	}

	return ESQLITE_OK;
}

int esqlite_free_table(char **dbresult)
{
	sqlite3_free_table(dbresult);

	return ESQLITE_OK;
}

/*
int esqlite_get_table_v2(esqlite *db, const char *sql, esql_args* head, const char *fullquery, char ***dbresult, int *nrow, int *ncol, char **errmsg)
{
	int ret = 0;
	sqlite3_stmt *stmt = NULL;
	
	if(sql == NULL || db == NULL || fullquery == NULL || dbresult == NULL || nrow == NULL || ncol == NULL)
		return ESQLITE_ERR;

	ret = esqlite_prepare(db, &stmt, sql, head);
	if(ESQLITE_OK != ret)
		return ESQLITE_ERR;

	ret = sqlite3_step(stmt);
	if(ESQLITE_ERR==ret)
		*ncol=0;
		*errmsg=NULL;
		esqlite_finalize(stmt);
		return ESQLITE_OK;
	}
	esqlite_finalize(stmt);

	return ESQLITE_OK;
}
*/

void esqlite_close(esqlite *db)
{
	sqlite3_close_v2(db->conn);
	EFREE(db);
}

int esql_args_push(esql_args *head, const int type, const void *value, const int encry)
{
	esql_args *tmp = NULL;

	if(head == NULL || value == NULL || (type != DOUBLE && type != INT && type != INT64 && type != TEXT && type != VALUE)){
		return ESQLITE_ERR;
	}

	tmp = EMALLOC(sizeof(esql_args));
	if(tmp == NULL)
		return ESQLITE_ERR;

	memset(tmp, 0, sizeof(esql_args));

	tmp->type = type;
	tmp->value = (char *)value;
	tmp->encry = encry;
	tmp->next = NULL;

	while(head->next){
		head = head->next;
	}

	head->next = tmp;

	return 0;
}

void esql_args_clear(esql_args *head)
{
	esql_args *node = head->next;
	head->next = NULL;

	while(node){
		esql_args *tmp = node;
		node = node->next;
		EFREE(tmp);
	}

	return;
}

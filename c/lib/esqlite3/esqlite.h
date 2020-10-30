/**
 * @file  times.c
 * @brief 时间封装接口
 * @author    lflish
 * @date     2020-10-15
 * @version  A001
 * @par History: 
 */
#include <stdio.h>
#include <sqlite3.h>

#define ESQLITE_ROW	1
#define ESQLITE_OK	0
#define ESQLITE_DONE	ESQLITE3_OK
#define ESQLITE_ERR	-1

#define ESQLTE_ENCRYPT_NO 	0x00
#define ESQLTE_ENCRYPT_YES	0x01

#define EMALLOC malloc
#define EFREE	free	

#define ESQL_BUSY_HANDLE		0x01
#define ESQL_ENCRYPT_HANDLE		0x02
#define ESQL_DECRYPT_HANDLE		0x03

typedef struct esql_args{
	int type;
	int encry;
	void *value;
	struct esql_args *next;
}esql_args;

enum SQLITE3EX_VALUE_TYPE
{
	DOUBLE,
	INT,
	INT64,
	TEXT,
	VALUE
};

typedef struct esqlite{
	sqlite3 *conn;
	char* (*encrypt_handle)(const char *);
	char* (*decrypt_handle)(const char *);
	char* (*encrypt_destroy)(const char *);
	char* (*decrypt_destroy)(const char *);
	int (*sqlite_busy_handle)(void *, int);
}esqlite;


esqlite *esqlite_open(const char *dbfile, int flag, void *value);

int esqlite_set(esqlite *db, int flag, void *value, void *value2);

int esqlite_exec(esqlite *db, const char *sql, void *value);
int esqlite_exec_v2(esqlite *db, const char *sql, esql_args *head);

int esqlite_get_table(esqlite *db, const char *sql, char ***dbresult, int *nrow, int *ncol, char **errmsg);
int esqlite_free_table(char **dbresult);

int esqlite_exec_cbk(esqlite *db, const char *sql, int (*callback)(void*,int,char**,char**), void *);

void esqlite_close(esqlite * db);

void esql_args_clear(esql_args *head);
int esql_args_push(esql_args *head, const int type, const void *value, const int encry);

/** 
* @file esqlite_extend.c
* @date 2020-11-23 00:16:14
* @details 针对esqlite扩增接口 
* @author lflish
* @par create
**/

#include <stdio.h>
#include "esqlite.h"

int esqlite_extend_passwd_exec(const char *dbpath, const char *key, const char *sql, void *args)
{
	int ret = 0;

    esqlite * edb = esqlite_open(dbpath, ESQLITE_DEF_OPTION, key);
	if(edb == NULL)
		return -1;

    ret = esqlite_exec(edb, sql, args);

    esqlite_close(edb);
    
    return ret;
}

int esqlite_extend_passwd_exec_v2(char *dbpath, const char *key, const char *sql, esql_args *args)
{
	int ret = 0;

    esqlite * edb = esqlite_open(dbpath, ESQLITE_DEF_OPTION, key);
	if(edb == NULL)
		return -1;

    ret = esqlite_exec_v2(edb, sql, args);

    esqlite_close(edb);
    
    return ret;
}

/* esqlite extend api */
int esqlite_extend_exec(char *dbpath, const char *sql, void *args)
{
	return esqlite_extend_passwd_exec(dbpath, NULL, sql, args);
}

int esqlite_extend_exec_v2(char *dbpath, const char *sql, esql_args *args)
{
	return esqlite_extend_passwd_exec_v2(dbpath, NULL, sql, args);
}

int esqlite_extend_cbk_set(char *dbpath, const char *sql, esqlite_extend_set_t handle, void *args)
{
	int ret = 0;

	if(!dbpath || !sql || !handle)
		return -1;

	esql_args head = {0};

	ret = handle(&head, args);
	if(ret != 0){
		esql_args_clear(&head);
		return ret;
	}

	ret = esqlite_extend_exec_v2(dbpath, sql, &head);

	esql_args_clear(&head);

	return ret;
}

int esqlite_extend_cbk_get(char *dbpath, const char *sql, esqlite_extend_get_t handle, void *args)
{
	int ret = 0;

	if(!dbpath || !sql || !handle)
		return -1;

    esqlite * edb = esqlite_open(dbpath, ESQLITE_DEF_OPTION, NULL);
	if(edb == NULL)
		return -1;

    ret = esqlite_exec_cbk(edb, sql, handle, args);

    esqlite_close(edb);
    
    return ret;
}
/*
 *测试支持密码校验
 * */
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "esqlite.h"

#define MAX_TABLE 64

char *g_db = NULL;
char *g_key = NULL;

char *g_table[MAX_TABLE] = {0};

int table_cbk(void *NotUsed, int argc, char **argv, char **azColName)
{
	int *count = NotUsed;

	if(count == NULL)
		return -1;

	g_table[*count] = strdup(argv[0]);
	*count = *count + 1;

	return 0;
}

void get_table_name(char **table)
{
	int ret = 0;
	int count = 0;

	ret = esqlite_extend_passwd_cbk_get(g_db, g_key, "SELECT name FROM sqlite_master WHERE type='table'", table_cbk, &count);
	if(ret != 0){
		fprintf(stderr, "[%s]:[%s]\n", esqlite_errsql(), esqlite_errmsg());
    	exit(0);
	}

	return;
}

int show_cbk(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;

	for (i = 0; i < argc; i++)
		printf("%s:%s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	printf("\n");

	return 0;
}

void show_table(char *name)
{
	printf("-------------------Table:%s------------------\n", name);
	int ret = 0;
	char sql[256] = {0};

	snprintf(sql, sizeof(sql), "select * from %s", name);

	ret = esqlite_extend_passwd_cbk_get(g_db, g_key, sql, show_cbk, NULL);
	if(ret != 0){
		fprintf(stderr, "[%s]:[%s]\n", esqlite_errsql(), esqlite_errmsg());
    	exit(0);
	}
}

void show_tables(char **table)
{
	int i = 0;

	for(i = 0; table[i]; i++){
		show_table(table[i]);
		printf("\n");
	}
}

void usage(char *name)
{
	printf("Usage:%s dbpath [passwd]\n", name);
	exit(0);
}


int main(int argn, char **argv)
{
	if (argv[1] == NULL)
		usage(argv[0]);

	g_db = argv[1];
	g_key = argv[2];

	get_table_name(g_table);

	show_tables(g_table);

	return 0;
}

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "esqlite.h"

#define create_script "create table if not exists `test` (`id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, `ruleid` INT NOT NULL, `scripttype` TEXT, `scriptdata` TEXT, `desc` TEXT);"
#define insert_script "insert into test(ruleid, scripttype, scriptdata, desc) values(%d, %Q, %Q, %Q);"
#define select_script "select * from test aaaa;"
#define erase_script "delete from test;"

static int busy_handle_callback(void *ptr,int count)
{
        usleep(500000);
		fprintf(stderr, "busy\n");
        return 1;
}

int pcallback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;

	for (i = 0; i < argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

	printf("\n");

	return 0;
}

int decallback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;

	printf("NotUser:%s\n", (char *)NotUsed);
	for (i = 0; i < argc; i++){
		if(i == 2 || i == 3)
			printf("%s = %s\n", azColName[i], argv[i] ? (argv[i] + 6) : "NULL");
		else
			printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}

	printf("\n");
	//test_exec();

	return 0;
}

void test_exec()
{
	int ret = 0;
	int i = 0;

	esqlite *db = esqlite_open("test.db", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_FULLMUTEX, NULL);
	assert(db != NULL);

	esqlite_set(db, 0x01, busy_handle_callback, NULL);

	ret = esqlite_exec(db, create_script, NULL);
	assert(ret == 0);


	for(i = 0; i < 1; i++){

		char *zsql = sqlite3_mprintf(insert_script, i, "aaaa", "bbbb", "cccc''");

		ret = esqlite_exec(db, zsql, NULL);
		assert(ret == 0);

		sqlite3_free(zsql);
	}

	ret = esqlite_exec_cbk(db, select_script, pcallback, NULL);
	assert(ret == 0);

	ret = esqlite_exec(db, erase_script, NULL);
	assert(ret == 0);

	esqlite_close(db);

	return;
}

#define create_encrypt "create table if not exists `encrypt` (`id` INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, `ruleid` INT NOT NULL, `scripttype` TEXT, `scriptdata` TEXT, `desc` TEXT);"
#define insert_encrypt "insert into encrypt(ruleid, scripttype, scriptdata, desc) values(?, ?, ?, ?);"
#define select_encrypt "select * from encrypt aaaa;"
#define delete_encrypt "delete from encrypt;"

char* encrypt_fun(const char * src)
{
	char *p = malloc(strlen(src) * 2);
	sprintf(p, "Encry[%s]Encry", src);
	return p;
}

char* encrypt_destroy(const char * src)
{
	char *p = malloc(strlen(src) * 2);
	sprintf(p, "Encry[%s]Encry", src);
	return p;
}

char* unencrypt_fun(const char * src)
{
	char *p = malloc(strlen(src) * 2);
	sprintf(p, "Encry[%s]Encry", src);
	return p;
}

void test_exec_v2()
{
	int ret = 0;
	int i = 0;

	esqlite *db = esqlite_open("test.db", SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_FULLMUTEX, NULL);
	assert(db != NULL);

	esqlite_set(db, 0x01, busy_handle_callback, NULL);
	esqlite_set(db, 0x02, encrypt_fun, encrypt_destroy);

	ret = esqlite_exec(db, create_encrypt, NULL);
	assert(ret == 0);

	for(i = 0; i < 100; i++){

		esql_args head = {0}; 

		esql_args_push(&head, INT, &i, 0);
		esql_args_push(&head, TEXT, "aaaa", 1);
		esql_args_push(&head, TEXT, "bbbb", 1);
		esql_args_push(&head, TEXT, "aaaa", 0);

		ret = esqlite_exec_v2(db, insert_encrypt, &head);

		esql_args_clear(&head);
	}

	ret = esqlite_exec_cbk(db, select_encrypt, decallback, "JJJJJJJJJ");
	assert(ret == 0);

	ret = esqlite_exec(db, delete_encrypt , NULL);
	assert(ret == 0);

	esqlite_close(db);

	return;
}

int main()
{
	//test_exec();

	test_exec_v2();
}

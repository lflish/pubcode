/** 
* @file edb.h
* @date 2020-10-28 19:57:43
* @details description
* @author lflish
* @par create
**/

#define EDB_SQLITE 0x01

typedef struct edb{
	void *db;
	int type;
}edb;

edb* edb_open(int type, void *dbpath, void *args)
{
	if(EDB_SQLITE == type){

	}
}

int *edb_insert();

int *edb_update();

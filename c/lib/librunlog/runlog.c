/**
 * @file  runlog.c 
 * @brief 日志系统
 * @author    yu
 * @date     2018-5-7
 * @version  A002
 * @copyright yu
 * @par History: 
 * 		2020-10-15 添加运行日志大小限制	
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "runlog.h"
#include "wmtime.h"

static FILE *runlog_fp = NULL;
static int runlog_fd = -1;

static unsigned int run_flag;
static unsigned int maxsize;

#define TYPE_1 0x01
#define TYPE_2 0x02
#define TYPE_3 0x04
#define TYPE_4 0x08

#define RUN_MSIZE 0x10
#define RUN_MSIZE2 0x20
#define RUN_MSIZE3 0x40
#define RUN_MSIZE4 0x80

#define RUN_OFILE 0x100
#define RUN_OSOCK 0x200
#define RUN_OUNIX 0x400

/** 
 * runlog_open,打开消息队列
 * @retval  OK      0
 * @retval  ERROR   -1
 * @par 修改日志
 *      yu于2018-05-07创建
 */
void runlog_open(const char *path, int flag, int size)
{
	if(path == NULL)
		return ;

	runlog_fp = fopen(path, "a+");

	if(runlog_fp == NULL)
		fprintf(stderr, "Open Runlog Path[%s] error No:%d\n", path, errno);
	else{
		setbuf(runlog_fp, NULL);
		runlog_fd = fileno(runlog_fp);
	}

	run_flag = flag;
	maxsize = size;

	return ;
}

void outfile(FILE *fd, const char *msg)
{
	int ret = 0;
	struct stat buf = {0};

	if(RUN_MSIZE & run_flag){
		ret = fstat(runlog_fd, &buf);
		if((ret != -1) && (buf.st_size > (maxsize - 4096)))
			ret = ftruncate(runlog_fd, 0);
	}

	if(ret != -1 && fd != NULL)
		ret = fprintf(fd, "%s", msg);

	return ;	
}

void runlog(const char *mod, const char *type, char *file, int line, const char *fun,  char *format, ...)
{
	if(runlog_fp == NULL || format == NULL)
		return ;

	char buf[MSG_DATA_LEN] = {0};
	char msg[MSG_DATA_LEN] = {0};
	char time[32];

	va_list argptr;

	va_start(argptr, format);
	vsnprintf(buf, MSG_DATA_LEN - 512, format, argptr);
	va_end(argptr);

	if(run_flag & TYPE_1)
		snprintf(msg, sizeof(msg), "[%s] <%s> %s %s %s:%d %s\n", wm_localtime(time, sizeof(time)), mod, type, fun, file, line, buf);
	else if(run_flag & TYPE_2)
		snprintf(msg, sizeof(msg), "[%s] <%s> %s %s:%d %s\n", wm_localtime(time, sizeof(time)), mod, type, fun, line, buf);
	else if(run_flag & TYPE_3)
		snprintf(msg, sizeof(msg), "<%s> %s %s\n", mod, type, buf);

	if(run_flag & RUN_OFILE)
		outfile(runlog_fp, msg);

	return ;	
}

/** 
 * @retval  OK      0
 * @par 修改日志
 *      yu于2018-05-07创建
 */
void runlog_close()
{
	if(runlog_fp)
		fclose(runlog_fp);

	return ;
}

#ifdef DEBUG
int main(int argc, char **argv)
{
	int i = 10000000;
	int pid = 0;

	runlog_open("./test", TYPE_2 | RUN_OFILE | RUN_MSIZE, 1024 * 1024 * 20);

	pid = fork();
	while(i--)
		runlog("Keeplive", LOG_ERROR, "pid:%d", getpid());

	runlog_close();
	return 0;
}
#endif

#pragma once

#include <stdio.h>
#include <stdarg.h>

#define MSG_DATA_LEN	4096

#define LOG_ERROR 	"ERROR", __FILE__, __LINE__, __FUNCTION__
#define LOG_INFO	"INFO", __FILE__, __LINE__, __FUNCTION__
#define LOG_DEBUG 	"DEBUG", __FILE__, __LINE__, __FUNCTION__

void runlog_open(const char *path, int size, int flag);

/** 
 * runlog, 程序运行写日志函数
 * @param[in]   logtype 	日志类型
 * @param[in]   file 		文件
 * @param[in]   fun 		函数名
 * @param[in]   line 		行号
 * @param[in]   format 		可变参数列表
 * @retval  OK      0
 * @par 修改日志
 *      lflish于2018-05-07创建
 *      lflish于2020-10-19更新 
 */
void runlog(const char *mod, const char *type, char *file, int line, const char *fun,  char *format, ...);

void runlog_close();

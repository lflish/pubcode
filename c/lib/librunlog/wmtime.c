/**
 * @file  times.c
 * @brief 时间封装接口
 * @author    lflish
 * @date     2020-10-15
 * @version  A001
 * @par History: 
 */

#include <time.h>
#include <string.h>
#include "wmtime.h"

char *wm_localtime(char *result, int size)
{
    struct tm *tm = NULL;
    time_t t = time(NULL);
    if(result == NULL || size < 20) 
        return "1970-00-00 00:00:00";

    tm = localtime(&t);
    if(tm != NULL)
        strftime(result, size, "%Y-%m-%d %H:%M:%S", tm);
    else
        strcpy(result, "1970-00-00 00:00:00");

    return result;
}

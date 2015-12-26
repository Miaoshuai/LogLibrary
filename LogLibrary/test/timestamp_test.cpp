/*======================================================
    > File Name: timestamp_test.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月23日 星期三 09时28分38秒
 =======================================================*/

#include<iostream>
#include<vector>
#include<string.h>
#include "timestamp.h"
#include <time.h>
#include <sys/time.h>
int main(int argc,char **argv)
{
  struct tm time = netlib::Timestamp().now();
  netlib::Timestamp t;
  char *p = t.toStringTime();
  printf("%s\n%d\n",p,strlen(p));

  return 0;
}

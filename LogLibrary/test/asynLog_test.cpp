/*======================================================
    > File Name: asynLog_test.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月26日 星期六 16时39分03秒
 =======================================================*/

#include<iostream>
#include "asynLog.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main(int argc,char **argv)
{
    netlib::AsynLog log(1000);
    char s[100] = "hello\n";
  log.setLevel(netlib::LogLevel::ALL);  
  for(int i = 0; i < 2; i++)
  {

    log.append(s,strlen(s),netlib::LogLevel::INFO);
  }
  log.stop();
  sleep(1000);
  return 0;
}

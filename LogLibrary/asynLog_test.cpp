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
#include <thread>

netlib::AsynLog log(1024*1024*1024);

void func(void)
{
    char s[100] = "hello\n";
    log.setLevel(netlib::LogLevel::ALL);
    while(true)
    {
        log.append(s,strlen(s),netlib::LogLevel::INFO);
    }
}

int main(int argc,char **argv)
{
  std::thread t1(func);
  std::thread t2(func);
  std::thread t3(func);
  std::thread t4(func);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  return 0;
}

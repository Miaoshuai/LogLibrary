/*======================================================
    > File Name: logFile.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月26日 星期六 15时12分35秒
 =======================================================*/
#include "logFile.h"
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

using namespace netlib;

LogFile::LogFile(int rollSize)
    :rollSize_(rollSize),
    fillSize_(0),
    fileNumbers_(1)
{
    fd_ = open("/home/shreck/log/mylog.log",O_WRONLY | O_APPEND | O_CREAT,S_IWUSR | S_IRUSR | S_IXUSR);
    assert(fd_ > 0);
}

LogFile::~LogFile()
{
    close(fd_);
}

void LogFile::append(char *log,int len)
{
    int ret = write(fd_,log,len);
    rollFile(ret);
    assert(ret == len);
}

void LogFile::rollFile(int curLen)
{
    fillSize_ += curLen;
    if(fillSize_ >= rollSize_)
    {
        printf("1G满了\n");
        //置0fillSize_
        fillSize_ = 0;
        char command[80];
        snprintf(command,sizeof(command),"mv /home/shreck/log/mylog.log /home/shreck/log/mylog%d.log",fileNumbers_);
        fileNumbers_++;
        //改当前文件名为fileName
        system(command);
        //重新创建一个mylog.log文件
        fd_ = open("/home/shreck/log/mylog.log",O_WRONLY | O_APPEND | O_CREAT,S_IWUSR | S_IRUSR | S_IXUSR);
        assert(fd_ > 0); 
    }    
}



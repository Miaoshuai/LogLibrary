/*======================================================
    > File Name: asynLog.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月24日 星期四 18时48分21秒
 =======================================================*/
#include "asynLog.h"
#include "logFile.h"
#include "timestamp.h"
#include <stdio.h>
#include <string.h>
#include <memory>
#include "fixBuffer.h"
#include <mutex>
#include <condition_variable>
#include <functional>
#include <pthread.h>

using namespace netlib;

AsynLog::AsynLog(int rollSize)
    :rollSize_(rollSize),
    currentBuffer_(new FixBuffer()),
    nextBuffer_(new FixBuffer()),
    acceptThread_(std::bind(&AsynLog::threadFunc,this))
{
    
}

AsynLog::~AsynLog()
{

}

void AsynLog::append(char *logline,int len)
{
    std::lock_guard<std::mutex> guard(mutex_);
    if(currentBuffer_->writeableSize() >= len)  //如果当前buffer空间足
    {
        std::string log1(logline);
        std::string log2(timestamp_.toStringTime());
        char log3[30];
        snprintf(log3,sizeof(log3),"threadid[%lu]: ",pthread_self());
        log2 = log2 + log3 + log1;
        currentBuffer_->append(log2.c_str(),log2.size());
        printf("111\n");
    }
    else
    {
        printf("222\n");
        buffers_.push_back(std::move(currentBuffer_)); //返回指针，自己变为空
        
        if(nextBuffer_)
        {
            currentBuffer_ = std::move(nextBuffer_);    //将nextBuffer_的控制权交给currentBuffer_
        }
        else
        {
            currentBuffer_.reset(new FixBuffer());  //申请一块新的buffer
        }

        currentBuffer_->append(logline,len);
        condition_.notify_one();    //唤醒后台线程
    }
}

void AsynLog::start(void)
{

}

void AsynLog::threadFunc(void)
{
    std::unique_ptr<FixBuffer> newBuffer1(new FixBuffer);
    std::unique_ptr<FixBuffer> newBuffer2(new FixBuffer); 
    std::vector<std::unique_ptr<FixBuffer>> buffersToWrite;
    LogFile output(1000);
    buffersToWrite.reserve(16);
    printf("333\n");
    while(1)
    {
        {
            printf("444\n");
            std::lock_guard<std::mutex> guard(mutex_);  //临界区加锁
            if(buffers_.empty())    //如果buffers_为空
            {
                condition_.wait_for(mutex_,std::chrono::seconds(3));
            }
            printf("555\n");
            buffers_.push_back(std::move(currentBuffer_));
            currentBuffer_ = std::move(newBuffer1);
            buffersToWrite.swap(buffers_);  //交换俩个容器
            if(!nextBuffer_)
            {
                nextBuffer_ = std::move(newBuffer2);
            }
            
        }
        printf("666\n");
        assert(!buffersToWrite.empty());

        if(buffersToWrite.size() > 25)
        {
            //日志异常
        }

        //将buffer中的内容写进文件中
        for(int i = 0; i < buffersToWrite.size(); i++)
        {
            printf("777\n");
            output.append(buffersToWrite[i]->getReadPeek(),buffersToWrite[i]->readableSize());        
        }

        if(buffersToWrite.size() > 2)
        {
            buffersToWrite.resize(2);
        }

        if(!newBuffer1)
        {
            printf("888\n");
            assert(!buffersToWrite.empty());
            newBuffer1 = std::move(buffersToWrite[0]);
            newBuffer1->resetBuffer();  //重置buffer
        }

        if(!newBuffer2)
        {
            printf("999\n");
            assert(!buffersToWrite.empty());
            newBuffer2 = std::move(buffersToWrite[1]);
            newBuffer2->resetBuffer();
        }

        buffersToWrite.clear();
        printf("000\n");
    }   
}

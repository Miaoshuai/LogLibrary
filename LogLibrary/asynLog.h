/*======================================================
    > File Name: asynLog.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月24日 星期四 17时33分26秒
 =======================================================*/
#ifndef ASYNLOG_H_
#define ASYNLOG_H_

#include <memory>
#include "fixBuffer.h"
#include "timestamp.h"
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace netlib
{
    class AsynLog
    {
        public:
            AsynLog(int roolSize);
            ~AsynLog();
            void append(char *logline,int len); //添加日志行

            void start(void);   //启动日志
        private:
            void threadFunc(void);  //线程函数

            int rollSize_;  //文件达到多大时滚动 
            std::unique_ptr<FixBuffer> currentBuffer_;   //当前buffer
            std::unique_ptr<FixBuffer> nextBuffer_;      //备用buffer
            std::vector<std::unique_ptr<FixBuffer>> buffers_;    //保存buffer的vector
            std::thread acceptThread_;   //后台接受数据的线程
            std::mutex mutex_;      //互斥变量
            std::condition_variable_any condition_; //条件变量
            Timestamp timestamp_;   //时间戳
    };
}

#endif

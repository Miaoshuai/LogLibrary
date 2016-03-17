/*======================================================
    > File Name: logFile.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月26日 星期六 14时57分54秒
 =======================================================*/
#ifndef LOG_FILE_H_
#define LOG_FILE_H_
namespace netlib
{
    class LogFile
    {
        public:
            LogFile(int rollSize);
            ~LogFile();
            //往磁盘里添加消息
            void append(char *log,int len);
            //滚动文件
            void rollFile(int curLen);

        private:
         int rollSize_;      //文件滚动大小
         int fd_;
         int fillSize_;      //当前文件填充大小
         int fileNumbers_;    //已有文件数量   
    };
}

#endif


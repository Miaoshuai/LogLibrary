/*======================================================
    > File Name: timestamp.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月23日 星期三 08时33分16秒
 =======================================================*/
#ifndef TIMESTAMP_H_
#define TIMESTAMP_H_

#include <time.h>
#include <sys/time.h>
#include <stdio.h>

namespace netlib
{
    class Timestamp
    {
        public:
            Timestamp()
            {
                
            }
            ~Timestamp()
            {
            
            }
            
            static struct tm *now()  //获取当前tm格式的时间
            {
                struct timeval tv;
                struct tm time;
                gettimeofday(&tv,NULL);    //获取微妙，秒值
                gmtimer_r(tv.tv_sec,&time);   //将s转换为tm格式
            }

            static timeval *getTime()
            {
                struct timeval tv;
                gettimeofday(&tv,NULL);
                return tv;
            }

            static int getTimeDiff(timeval v1,timeval v2)    //获得俩时间的时间差
            {
                struct timeval t;

                if(v1.tv_usec >= v2.tv_usec)
                {
                    t.tv_sec = v1.tv_sec - v2.tv_sec;
                    t.tv_usec = v1.tv_usec - v2.tv_usec;
                }
                else
                {
                    t.tv_sec = (v1.tv_sec - 1) - v2.tv_sec;
                    t.tv_usec = (1000000 + v1.tv_usec) - v2.tv_usec;
                }

                if(t.tv_sec < 0)
                {
                    int temp;
                    t.tv_sec = t.tv_sec - 2*t.tv_sec;   //转正
                    temp = t.tv_sec*1000000 - t.tv_usec;
                    t.tv_usec = temp%1000000;
                    t.tv_sec = temp/1000000;
                }
            }

        private:
            
    };
}

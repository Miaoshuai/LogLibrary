/*======================================================
    > File Name: mutex.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月23日 星期三 11时21分53秒
 =======================================================*/
#ifndef MUTEX_H_
#define MUTEX_H_

#include <thread>
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
namespace netlib
{
    class Mutex
    {
        public:
            Mutex()
            {
                pthread_mutex_init(&mutex_,NULL);
            }
            ~Mutex()
            {
                pthread_mutex_destroy(&mutex_);
            }

            void lock() //上锁
            {
                int ret = pthread_mutex_lock(&mutex_);
                printf("hello = %p\n",&mutex_);
                assert(ret == 0);
            }

            void unlock()   //解锁
            {
                int ret = pthread_mutex_unlock(&mutex_);
                assert(ret == 0);
            }

            pthread_mutex_t *getMutex() //获得互斥锁
            {
                return &mutex_;
            }
        private:
         pthread_mutex_t mutex_;   
    };
}

#endif

/*======================================================
    > File Name: cond.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月23日 星期三 12时20分02秒
 =======================================================*/

#ifndef CONDTION_H_
#define CONDTION_H_

//#include "mutex.h"
#include <thread>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>

namespace netlib
{
    class Condtion
    {
        public:
            Condtion(pthread_mutex_t *mutex)
                :mutex_(mutex)
            {
                pthread_cond_init(&cond_,NULL);
            }
            ~Condtion()
            {
                pthread_cond_destroy(&cond_);
            }

            void wait()     //条件等待
            {
                int ret = pthread_cond_wait(&cond_,mutex_);   
                assert(ret == 0);
            }

            void notify()   //唤醒
            {
                int ret = pthread_cond_signal(&cond_);
                assert(ret == 0);
            }

            void notifyAll()    //唤醒全部
            {
                int ret = pthread_cond_broadcast(&cond_);
                assert(ret == 0);
            }
        private:
            pthread_mutex_t *mutex_;
            pthread_cond_t cond_;
    };
}

#endif

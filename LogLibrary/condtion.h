/*======================================================
    > File Name: cond.h
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月23日 星期三 12时20分02秒
 =======================================================*/

#ifndef CONDTION_H_
#define CONDTION_H_

#include "mutex.h"
#include <thread>

namespace netlib
{
    class Condtion
    {
        public:
            Condtion(Mutex &mutex)
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
                pthread_cond_wait(&cond,mutex_.getMutex());   
            }

            void notify()   //唤醒
            {
                pthread_cond_singnal(&cond_);
            }

            void notifyAll()    //唤醒全部
            {
                pthread_cond_broadcast(&cond_);
            }
        private:
            Mutex mutex_;
            pthread_cond_t cond_;
    };
}

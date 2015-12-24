/*======================================================
    > File Name: condtion_test.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年12月24日 星期四 12时44分38秒
 =======================================================*/
#include "condtion.h"
#include "mutex.h"
#include <thread>
#include <stdio.h>
#include <unistd.h>

int sum = 0;
netlib::Mutex mutex;
netlib::Condtion condtion(mutex.getMutex());
void work(int n)
{
    while(1)
    {
        mutex.lock();
        sum++;
        printf("%d:被加到%d\n",n,sum);
        mutex.unlock();
        
    }    
}

int main(void)
{
    std::thread t1(work,1);
    std::thread t2(work,2);
    std::thread t3(work,3);
    
    while(1)
    {
        mutex.lock();
        condtion.wait();
        while(sum > 0)
        {
            sum--;
        }
               
        printf("sum被减为sum = %d\n",sum);
        mutex.unlock();
    }    
    return 0;
}

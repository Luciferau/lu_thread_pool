#include "thread.h"

int thread_mutex_create(pthread_mutex_t *mtx)
{
    int            err;
    pthread_mutexattr_t  attr;//设置属性

    err = pthread_mutexattr_init(&attr);
    if (err != 0) {
        fprintf(stderr, "pthread_mutexattr_init() failed, reason: %s\n",strerror(errno));
        return ERROR;
    }

    //PTHREAD_MUTEX_ERRORCHECK PTHREAD_MUTEX_ERRORCHECK是一个宏，用于设置线程互斥锁的类型为错误检查锁。

    //线程互斥锁是一种用于保护共享资源的数据结构，可以防止多个线程同时访问同一个资源。
    //错误检查锁是一种特殊的互斥锁，它在尝试获取锁时，如果锁已经被其他线程持有，
    //那么它会立即返回错误，而不是等待。

    /*THREAD_MUTEX_TIME_UP 错误通常表示在等待互斥量时超时了。
    /这可能是因为互斥量一直处于被其他线程持有的状态，导致当前线程无法获取到互斥量的所有权。
    /超时发生后，系统会返回这个错误代码，以提示调用者当前无法获取互斥量，并需要适当处理该情况，
    /例如等待一段时间后重试，或者采取其他的处理方式。*/
    err = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    if (err != 0) {
		fprintf(stderr, "pthread_mutexattr_settype(PTHREAD_MUTEX_ERRORCHECK) failed, reason: %s\n",strerror(errno));
        return ERROR;
    }

    err = pthread_mutex_init(mtx, &attr);
    if (err != 0) {
        fprintf(stderr,"pthread_mutex_init() failed, reason: %s\n",strerror(errno));
        return ERROR;
    }

    err = pthread_mutexattr_destroy(&attr);
    if (err != 0) {
		fprintf(stderr,"pthread_mutexattr_destroy() failed, reason: %s\n",strerror(errno));
    }

    return OK;
}


int thread_mutex_destroy(pthread_mutex_t *mtx)
{
    int  err;

    err = pthread_mutex_destroy(mtx);
    if (err != 0) {
        fprintf(stderr,"pthread_mutex_destroy() failed, reason: %s\n",strerror(errno));
        return ERROR;
    }

    return OK;
}



int thread_mutex_lock(pthread_mutex_t *mtx)
{
    int  err;

    err = pthread_mutex_lock(mtx);
    if (err == 0) {
        return OK;
    }
	fprintf(stderr,"pthread_mutex_lock() failed, reason: %s\n",strerror(errno));

    return ERROR;
}




int thread_mutex_unlock(pthread_mutex_t *mtx)
{
    int  err;

    err = pthread_mutex_unlock(mtx);

#if 0
    ngx_time_update();
#endif

    if (err == 0) {
        return OK;
    }
	
	fprintf(stderr,"pthread_mutex_unlock() failed, reason: %s\n",strerror(errno));
    return ERROR;
}

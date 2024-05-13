#ifndef _THREAD_POOL_H_INCLUDED_
#define _THREAD_POOL_H_INCLUDED_

#include "thread.h"

#define DEFAULT_THREAD_NUM      8
#define DEFAULT_TASK_QUEUE_NUM  65535

 
//typedef struct thread_task_s  thread_task_t;
//typedef struct thread_pool_s  thread_pool_t;

typedef unsigned long         atomic_uint_t;//atomic 原子操作

typedef struct thread_task_s_  {
    struct thread_task_s_       *next;
    uint_t                      id;
    void                        *ctx;//上下文，也就是任务带的参数
    void                        (*handler)(void *data);
}thread_task_s,thread_task_t;

 
typedef struct {
    thread_task_t        *first;
    thread_task_t        **last;
} thread_pool_queue_t;


#define thread_pool_queue_init(q)                                         \
    (q)->first = NULL;                                                    \
    (q)->last = &(q)->first

typedef struct thread_pool_s_ {
    pthread_mutex_t         mtx;
    thread_pool_queue_t     queue;
    int_t                   waiting;
    pthread_cond_t          cond;

    char                    *name;
    uint_t                  threads;//线程数量
    int_t                   max_queue;//最大队列
}thread_pool_t,thread_pool_s;

 
thread_task_t *thread_task_alloc(size_t size);
int_t thread_task_post(thread_pool_t *tp, thread_task_t *task);
thread_pool_t* thread_pool_init();
void thread_pool_destroy(thread_pool_t *tp);

 




#endif//_THREAD_POOL_H_INCLUDED_
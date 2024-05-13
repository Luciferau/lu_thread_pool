#ifndef _THREAD_POOL_H_INCLUDED_
#define _THREAD_POOL_H_INCLUDED_


#include "thread.h"

#define DEFAULT_THREADS_NUM 4 //默认线程数量
#define DEFAULT_QUEUE_NUM  65535//默认队列数量


typedef unsigned long         atomic_uint_t;
typedef struct thread_task_s  thread_task_t;//任务结构体
typedef struct thread_pool_s  thread_pool_t;//线程池结构体


struct thread_task_s {
    thread_task_t       *next;//下一个任务的指针
    uint_t               id;//任务ID
    void                *ctx;//任务上下文 也就是线程执行函数的参数。使用动态分配内存（柔性数组）
    void               (*handler)(void *data);//线程执行的函数
};

typedef struct {
    thread_task_t        *first;
    thread_task_t        **last;
} thread_pool_queue_t;//队列结构体

//初始化为空队列
#define thread_pool_queue_init(q)                                         \
    (q)->first = NULL;                                                    \
    (q)->last = &(q)->first

//线程池
struct thread_pool_s {
    pthread_mutex_t        mtx;//锁
    thread_pool_queue_t   queue;//队列
    int_t                 waiting;//正在等待的任务数量
    pthread_cond_t         cond;//condition 信号

    char                  *name;//线程池的名字
    uint_t                threads;//线程数量
    int_t                 max_queue;//最大的队列数量
};

thread_task_t   *thread_task_alloc(size_t size);//分配任务
int_t           thread_task_post(thread_pool_t *tp, thread_task_t *task);
thread_pool_t*  thread_pool_init();
void            thread_pool_destroy(thread_pool_t *tp);


#endif /* _THREAD_POOL_H_INCLUDED_ */

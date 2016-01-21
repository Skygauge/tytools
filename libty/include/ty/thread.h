/*
 * ty, a collection of GUI and command-line tools to manage Teensy devices
 *
 * Distributed under the MIT license (see LICENSE.txt or http://opensource.org/licenses/MIT)
 * Copyright (c) 2015 Niels Martignène <niels.martignene@gmail.com>
 */

#ifndef TY_THREAD_H
#define TY_THREAD_H

#include "common.h"
#ifdef _WIN32
    // FIXME: avoid windows.h in public headers
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <pthread.h>
#endif

TY_C_BEGIN

typedef struct ty_thread {
#ifdef _WIN32
    HANDLE h;
#else
    pthread_t thread;
    bool init;
#endif
} ty_thread;

typedef enum ty_mutex_type {
    TY_MUTEX_FAST,
    TY_MUTEX_RECURSIVE
} ty_mutex_type;

typedef struct ty_mutex {
#ifdef _WIN32
    CRITICAL_SECTION mutex;
#else
    pthread_mutex_t mutex;
#endif
    bool init;
} ty_mutex;

typedef struct ty_cond {
#ifdef _WIN32
    union {
        CONDITION_VARIABLE cv;
        struct {
            HANDLE ev;

            CRITICAL_SECTION mutex;
            unsigned int waiting;
            unsigned int wakeup;
        } xp;
    };
#else
    pthread_cond_t cond;
#endif
    bool init;
} ty_cond;

typedef int ty_thread_func(void *udata);

TY_PUBLIC int ty_thread_create(ty_thread *thread, ty_thread_func *f, void *udata);
TY_PUBLIC int ty_thread_join(ty_thread *thread);
TY_PUBLIC void ty_thread_detach(ty_thread *thread);

TY_PUBLIC int ty_mutex_init(ty_mutex *mutex, ty_mutex_type type);
TY_PUBLIC void ty_mutex_release(ty_mutex *mutex);

TY_PUBLIC void ty_mutex_lock(ty_mutex *mutex);
TY_PUBLIC void ty_mutex_unlock(ty_mutex *mutex);

TY_PUBLIC int ty_cond_init(ty_cond *cond);
TY_PUBLIC void ty_cond_release(ty_cond *cond);

TY_PUBLIC void ty_cond_signal(ty_cond *cond);
TY_PUBLIC void ty_cond_broadcast(ty_cond *cond);

TY_PUBLIC bool ty_cond_wait(ty_cond *cond, ty_mutex *mutex, int timeout);

TY_C_END

#endif

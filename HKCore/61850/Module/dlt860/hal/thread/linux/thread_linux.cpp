#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include "gsp_hal_thread.h"

#include "gsp_lib_memory.h"

// pthread 的封装
struct sThread {
	GspThreadExecutionFunction function;
	void* parameter;
	pthread_t pthread;
	int state;
	bool autodestroy;
};

GspSemaphore GspSemaphore_create(int initialValue)
{
    GspSemaphore self = GLOBAL_MALLOC(sizeof(sem_t));

    sem_init((sem_t*) self, 0, initialValue);

    return self;
}

/* Wait until semaphore value is more than zero. Then decrease the semaphore value. */
void GspSemaphore_wait(GspSemaphore self)
{
    sem_wait((sem_t*) self);
}

void GspSemaphore_post(GspSemaphore self)
{
    sem_post((sem_t*) self);
}

void GspSemaphore_destroy(GspSemaphore self)
{
    sem_destroy((sem_t*) self);
    GLOBAL_FREEMEM(self);
}

GspThread GspThread_create(GspThreadExecutionFunction function, void* parameter, bool autodestroy)
{
	GspThread thread = (GspThread) GLOBAL_MALLOC(sizeof(struct sThread));

    if (thread != 0) {
        thread->parameter = parameter;
        thread->function = function;
        thread->state = 0;
        thread->autodestroy = autodestroy;
	}

	return thread;
}

static void* Gsp_DestroyAutomaticThread(void* parameter)
{
    GspThread thread = (GspThread) parameter;

	thread->function(thread->parameter);

	GLOBAL_FREEMEM(thread);

    pthread_exit(0);
}

void GspThread_start(GspThread thread)
{
	if (thread->autodestroy == true) {
        pthread_create(&thread->pthread, 0, Gsp_DestroyAutomaticThread, thread);
		pthread_detach(thread->pthread);
    } else {
        pthread_create(&thread->pthread, 0, thread->function, thread->parameter);
    }

	thread->state = 1;
}

void GspThread_destroy(GspThread thread)
{
	if (thread->state == 1) {
        pthread_join(thread->pthread, 0);
	}

	GLOBAL_FREEMEM(thread);
}

void GspThread_sleep(int millies)
{
	usleep(millies * 1000);
}


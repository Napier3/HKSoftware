/*
 *  thread_win32.c
 */

#include <windows.h>
#include "gsp_lib_memory.h"
#include "gsp_hal_thread.h"

struct sThread {
	GspThreadExecutionFunction function;
	void* parameter;
	HANDLE handle;
	int state;
	bool autodestroy;
};

static DWORD WINAPI
destroyAutomaticThreadRunner(LPVOID parameter)
{
	GspThread thread = (GspThread) parameter;

	thread->function(thread->parameter);

	thread->state = 0;

	GspThread_destroy(thread);

	return 0;
}

static DWORD WINAPI
threadRunner(LPVOID parameter)
{
	GspThread thread = (GspThread) parameter;

	return (UINT) thread->function(thread->parameter);
}

GspThread
GspThread_create(GspThreadExecutionFunction function, void* parameter, bool autodestroy)
{
	DWORD threadId;
	GspThread thread = (GspThread) GLOBAL_MALLOC(sizeof(struct sThread));

	thread->parameter = parameter;
	thread->function = function;
	thread->state = 0;
	thread->autodestroy = autodestroy;

	if (autodestroy == true)
		thread->handle = CreateThread(0, 0, destroyAutomaticThreadRunner, thread, CREATE_SUSPENDED, &threadId);
	else
		thread->handle = CreateThread(0, 0, threadRunner, thread, CREATE_SUSPENDED, &threadId);

	return thread;
}

void
GspThread_start(GspThread thread)
{
	thread->state = 1;
	ResumeThread(thread->handle);
}

void
GspThread_destroy(GspThread thread)
{
	if (thread->state == 1)
		WaitForSingleObject(thread->handle, INFINITE);

	CloseHandle(thread->handle);

	GLOBAL_FREEMEM(thread);
}

void
GspThread_sleep(int millies)
{
	Sleep(millies);
}

GspSemaphore
GspSemaphore_create(int initialValue)
{
    HANDLE self = CreateSemaphore(NULL, 1, 1, NULL);

    return self;
}

/* Wait until semaphore value is greater than zero. Then decrease the semaphore value. */
void
GspSemaphore_wait(GspSemaphore self)
{
    WaitForSingleObject((HANDLE) self, INFINITE);
}

void
GspSemaphore_post(GspSemaphore self)
{
    ReleaseSemaphore((HANDLE) self, 1, NULL);
}

void
GspSemaphore_destroy(GspSemaphore self)
{
    CloseHandle((HANDLE) self);
}

/*
 *  simple_allocator.c
 */

#include "libdlt860_platform_includes.h"
#include "simple_allocator.h"
#include "stack_config.h"

void
GspMemoryAllocator_init(GspMemoryAllocator* self, char* memoryBlock, int size)
{
    self->memoryBlock = memoryBlock;
    self->currentPtr = memoryBlock;
    self->size = size;
}

int
GspMemoryAllocator_getAlignedSize(int size)
{
#if (CONFIG_IEC61850_FORCE_MEMORY_ALIGNMENT == 1)
    if ((size % sizeof(void*)) > 0)
        return sizeof(void*) * ((size + sizeof(void*) - 1) / sizeof(void*));
    else
        return size;
#else
    return size;
#endif
}

char*
GspMemoryAllocator_allocate(GspMemoryAllocator* self, int size)
{
    size = GspMemoryAllocator_getAlignedSize(size);

    if (((self->currentPtr - self->memoryBlock) + size) <= self->size) {
        char* ptr = self->currentPtr;
        self->currentPtr += size;
        return ptr;
    }
    else
        return NULL;
}

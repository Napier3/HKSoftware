/*
 *  buffer_chain.c
 */

#include "libdlt860_platform_includes.h"

#include "buffer_chain.h"

void
BufferChain_init(BufferChain self, int length, int partLength, BufferChain nextPart, uint8_t* buffer)
{
    self->length = length;
    self->partLength = partLength;
    self->partMaxLength = partLength;
    self->nextPart = nextPart;
    self->buffer = buffer;
}

void
MemoryArea_initialize(MemoryArea* self, uint8_t* memory, int size)
{
    self->memory = memory;
    self->size = size;
    self->currentPos = 0;
}

uint8_t*
MemoryArea_getNextBlock(MemoryArea* self, int size)
{
    if ((self->size - self->currentPos) >= size) {
        uint8_t* newBlock = self->memory + self->currentPos;

        self->currentPos += size;
        return newBlock;
    }
    else
        return NULL;

}

/*
 *  byte_buffer.c
 */

#include "libdlt860_platform_includes.h"
#include "byte_buffer.h"

GspByteBuffer* GspByteBuffer_create(GspByteBuffer* self, int maxSize)
{
    if (self == nullptr) {
		self = (GspByteBuffer*) GLOBAL_CALLOC(1, sizeof(GspByteBuffer));
	}

	self->buffer = (uint8_t*) GLOBAL_CALLOC(maxSize, sizeof(uint8_t));
	self->maxSize = maxSize;
	self->size = 0;

	return self;
}

void GspByteBuffer_destroy(GspByteBuffer* self)
{
	GLOBAL_FREEMEM(self->buffer);
	GLOBAL_FREEMEM(self);
}

void GspByteBuffer_wrap(GspByteBuffer* self, uint8_t* buf, int size, int maxSize)
{
	self->buffer = buf;
	self->size = size;
	self->maxSize = maxSize;
}

int GspByteBuffer_append(GspByteBuffer* self, uint8_t* data, int dataSize)
{
	if (self->size + dataSize <= self->maxSize) {
		memcpy(self->buffer + self->size, data, dataSize);
		self->size += dataSize;
		return dataSize;
    } else {
		return -1;
	}
}

int GspByteBuffer_appendByte(GspByteBuffer* self, uint8_t byte)
{
	if (self->size  < self->maxSize) {
		self->buffer[self->size] = byte;
		self->size ++;
		return 1;
    } else {
		return 0;
    }
}


uint8_t* GspByteBuffer_getBuffer(GspByteBuffer* self)
{
	return self->buffer;
}

int GspByteBuffer_getMaxSize(GspByteBuffer* self)
{
	return self->maxSize;
}

int GspByteBuffer_getSize(GspByteBuffer* self)
{
	return self->size;
}

int GspByteBuffer_setSize(GspByteBuffer* self, int size)
{
	if (size <= self->maxSize)
		self->size = size;

	return self->size;
}

void GspByteBuffer_print(GspByteBuffer* self, char* message)
{
    printf("\n%s (size = %i):\n",  message, self->size);

    int i;
    for (i = 0; i < self->size; i++) {
        printf("%02x ", self->buffer[i]);
        if (((i + 1) % 16) == 0)
            printf("\n");
        else if (((i + 1) % 8) == 0)
            printf("| ");

    }
    printf("\n");
}

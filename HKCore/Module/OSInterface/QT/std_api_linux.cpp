#include "std_api_linux.h"



unsigned long  _lrotl (
    unsigned long val,
    int shift
    )
{
    shift &= 0x1f;
    val = (val>>(0x20 - shift)) | (val << shift);
    return val;
}

unsigned  _rotl (
    unsigned val,
    int shift
    )
{
    shift &= 0x1f;
    val = (val>>(0x20 - shift)) | (val << shift);
    return val;
}

__uint64  _rotl64 (
    __uint64 val,
    int shift
    )
{
    shift &= 0x3f;
    val = (val>>(0x40 - shift)) | (val << shift);
    return val;
}

unsigned long  _lrotr (
    unsigned long val,
    int shift
    )
{
    shift &= 0x1f;
    val = (val<<(0x20 - shift)) | (val >> shift);
    return val;
}

unsigned  _rotr (
    unsigned val,
    int shift
    )
{
    shift &= 0x1f;
    val = (val<<(0x20 - shift)) | (val >> shift);
    return val;
}

__uint64  _rotr64 (
    __uint64 val,
    int shift
    )
{
    shift &= 0x3f;
    val = (val<<(0x40 - shift)) | (val >> shift);
    return val;
}

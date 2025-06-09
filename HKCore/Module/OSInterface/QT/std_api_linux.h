#ifndef _std_api_linux_h__
#define _std_api_linux_h__

#include "XGlobalDefine_QT.h"

unsigned long  _lrotl (
    unsigned long val,
    int shift
    );
    
unsigned  _rotl (
    unsigned val,
    int shift
    );
    
__uint64  _rotl64 (
    __uint64 val,
    int shift
    );
    
unsigned long  _lrotr (
    unsigned long val,
    int shift
    );
    
unsigned  _rotr (
    unsigned val,
    int shift
    );
    
__uint64  _rotr64 (
    __uint64 val,
    int shift
    );

#endif   //_std_api_linux_h__

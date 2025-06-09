// MemBuffer.h: interface for the CMemBufferclass.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_MEMBUFFER_H__)
#define _MEMBUFFER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../RtScriptBase/RtScriptBase.h"
#include "MemBufferDef.h"

#include "MemBuffer_Float.h"
#include "MemBuffer_Double.h"
#include "MemBuffer_UnsignedShort.h"
#include "MemBuffer_Long.h"
#include "ComplexMemBuffer_UnsignedShort.h"

typedef CMemBuffer_UnsignedShort CMemBuffer_UShort;
typedef CComplexMemBuffer_Long CComplexBuffer_Long;
typedef CComplexMemBuffer_Float CComplexBuffer_Float;

typedef CComplexMemBuffer_UnsignedShort CComplexBuf_Long_UShort;

#define COMPLEXVARIABLE_USE_FLOAT


#endif // !defined(_MEMBUFFER_H__)

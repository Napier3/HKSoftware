#if !defined(_MemBufferDC_h__)
#define _MemBufferDC_h__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MemBufferDC.h : header file
//

#ifdef _PSX_IDE_QT_
    #include "QT/MemBufferDC_QT.h"
#else
    #include "VC/MemBufferDC_VC.h"
#endif


#endif // !defined(_MemBufferDC_h__)

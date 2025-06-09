// EpParseFrame.h: interface for the CEpParseFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPARSEFRAME_H__)
#define _EPPARSEFRAME_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"


class CEpParseFrame : public CEpFrameBase  
{
public:
	CEpParseFrame();
	virtual ~CEpParseFrame();

public:
	//基本方法
	virtual UINT GetClassID()	{ return EPCLASSID_PARSE_FRAME;	}
	
	//解析
	//字节块的解析  具体的解析在派生类中执行解析
	virtual DWORD Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList)	{ return 0;}

	//字节块的匹配  主要用于解析
	virtual BOOL Match(PEPBUFFERPOS pBufferPos) { return FALSE;}

};

#endif // !defined(_EPPARSEFRAME_H__)

// EpProduceFrame.h: interface for the CEpProduceFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XPPRODUCEPACKGE_H__)
#define _XPPRODUCEPACKGE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EpFrameBase.h"


class CEpProduceFrame : public CEpFrameBase  
{
public:
	CEpProduceFrame();
	virtual ~CEpProduceFrame();

public:
	//基本方法
	virtual UINT GetClassID()	{	return EPCLASSID_PRODUCE_FRAME;	}
	
	//打包
	virtual DWORD Produce(PEPBUFFERPOS pBufferPos) {		return 0;	}
};

#endif // !defined(_XPPRODUCEPACKGE_H__)

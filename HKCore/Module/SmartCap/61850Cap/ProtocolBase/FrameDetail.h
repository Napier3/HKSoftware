// FrameDetail.h: interface for the CFrameDetail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_StFRAMEDETAIL_H__)
#define _StFRAMEDETAIL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <math.h>
#include "ProtocolGlobalDef.h"
#include "ByteBlock.h"
//#include "FrameMemBuffer.h"
#include "../../../SmDb/XSmMemBuffer.h"

class CFrameDetail : public CByteBlocks  
{
public:
	CFrameDetail();
	virtual ~CFrameDetail();

// Ù–‘
protected:
	CXSmMemBuffer *m_pBuffer;

public:
	virtual void AttachFrameMemBuffer(CXSmMemBuffer *pBuffer)	{	m_pBuffer = pBuffer;	}
	virtual CXSmMemBuffer* GetFrameMemBuffer()	{	return m_pBuffer;	}

};

#endif // !defined(_StFRAMEDETAIL_H__)

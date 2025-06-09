//SmvFrameBase.h  
#ifndef _SmvFrameBase_H__
#define _SmvFrameBase_H__

#include "61850FrameBase.h"

class CSmvFrameBase : public C61850FrameBase
{
public:
	CSmvFrameBase();
	virtual ~CSmvFrameBase();

public:
	long m_SampleRate;
	INT32   m_LastSmpCnt;
	UINT64  m_LostPPS;

public:

};


#endif //_SmvFrameBase_H__
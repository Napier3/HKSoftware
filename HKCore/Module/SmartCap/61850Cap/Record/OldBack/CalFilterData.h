// RtCalFilterData.h: interface for the CRtCalFilterData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCALFILTERDATA_H__EB2409BE_D8E1_43D0_92BA_995012F62EF0__INCLUDED_)
#define AFX_RTCALFILTERDATA_H__EB2409BE_D8E1_43D0_92BA_995012F62EF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "RecordDefine.h"
#include "..\MemBuffer\MemBufferDef.h"

class CRtCalFilterData  
{
public:
	CRtCalFilterData(PRTCALFUNCPARA pCalFuncPara, long *pCurrPos);
	virtual ~CRtCalFilterData();

	long *m_ppFilterData[RT_FILTER_BUFFER_LEN];
	short m_pFilterData[RT_FILTER_BUFFER_LEN];
	long *m_pBuffer;
	long m_nDataLength;
	long m_nBufferLength;
	long *m_pCurrPos;

	BOOL IsZeroPos()   {    return (m_bIsZeroPos && m_bIsZeroPos);    }
private:
	CRtCalFilterData(){}
	BOOL m_bIsZeroPos;
	BOOL m_bIsZeroPos2;

	void GetPrevData();
	void GetNextData();
	void Filter();
	void Filter2();
};

#endif // !defined(AFX_RTCALFILTERDATA_H__EB2409BE_D8E1_43D0_92BA_995012F62EF0__INCLUDED_)

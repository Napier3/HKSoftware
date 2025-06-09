// RecordCmpVariable.h: interface for the CRecordCmpVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RecordCmpVariable_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)
#define AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordCmpBuffer.h"

class CRecordCmpVariable : public CExBaseList
{
private:
	CRecordCmpVariable()	{}

public:
	CRecordCmpVariable(CRtSingleVariable *pVariable1, CRtSingleVariable *pVariable2
		, long nSampleRate1, long nSampleRate2, float fSetValForFind, float fSetValForCmp);
	virtual ~CRecordCmpVariable();

	BOOL GetAlignPosVariable2(long &nAlignPos);
	BOOL IsAlignSucc()
	{
		return ((m_nAllignPosition1 != -1) && (m_nAllignPosition2 != -1));
	}

public:
	CRtSingleVariable *m_pRtVariable1;
	CRtSingleVariable *m_pRtVariable2;
	long m_nAllignPosition1, m_nAllignPosition2;

};



#endif // !defined(AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)

// RecordCompareTool.h: interface for the CRecordCompareTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)
#define AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\MR1200BaseApp.h"

#define RCD_CMP_FETURE_TYPE_PEAK      0
#define RCD_CMP_FETURE_TYPE_VALLEY   1
//Peak valley

#define RCD_CMP_FETURE_TYPE_MAX_COUNT   256

#define RCD_CMP_FETURE_TRIG   0.01

typedef struct rcd_cmp_feature
{
	long nBeginPos;
	long nEndPos;
	long nMaxPos;
	float fBeginDelta;
	float fMaxValueDelta;
	float fEndDelta;
	float fBegin;
	float fMaxValue;
	float fEnd;
	UINT nFetureType;
}RCD_CMP_FETURE, *PRCD_CMP_FETURE;

typedef struct rcd_cmp_features
{
	long nFetureCount;
	RCD_CMP_FETURE fetures[RCD_CMP_FETURE_TYPE_MAX_COUNT];
}RCD_CMP_FETURES, *PRCD_CMP_FETURES;


class CRecordCmpBuffer : public CExBaseObject
{
public:
	CRecordCmpBuffer();
	virtual ~CRecordCmpBuffer();

	void SetBuffer(CMemBuffer_Float *pBuff1, CMemBuffer_Float *pBuff2);
	void RcdCmp(CMemBuffer_Float *pBuff1, CMemBuffer_Float *pBuff2
		, long nSampleRate1, long nSampleRate2, float fSetValForFind, float fSetValForCmp);
	void LogRcdCmp(const CString &strVariableID);

	void GetAllignPosition(long &nPos1, long &nPos2)	{	nPos1 = m_nAllignPosition1;		nPos2 = m_nAllignPosition2;}	
	BOOL GetAlignPosVariable2(long &nAlignPos);

protected:
	void InitRcdCmpFetures(CMemBuffer_Float *pBuffDelta, CMemBuffer_Float *pBuff, PRCD_CMP_FETURES pFetures, long nCyclePoints);
	void CalFetureAvg_FindPos(float *pfBegin, float *pfEnd, long nCyclePoints
		,float **ppfBegin, float **ppfEnd, float **ppfGapMax);
	void CalFetureAvg_FindPos_PeakValley(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
		,float **ppfBegin, float **ppfEnd, float **ppfGapMax);

	void CalFetureAvg_FindPos_PeakValley1(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
		,float **ppfBegin, float **ppfEnd, float **ppfGapMax);
	void CalFetureAvg_FindPos_PeakValley2(float fAvgVal, long nCyclePoints, float *pfBegin, float *pfEnd
		,float **ppfBegin, float **ppfEnd, float **ppfGapMax);


	void AddFeture(PRCD_CMP_FETURES pFetures, long nBeginPos, long nMaxPos, long nEndPos, float fBegin, float fMax, float fEnd, float *pfBufValue);

// 	float CalMaxValue(CMemBuffer_Float *pBuff);
// 	void CalFeture(float *pfBegin, float *pfEnd, float &fGapMax, long &nTotalCount, long &nMaxPos);
// 	void CalFetureByVal(float fAvgVal, float *pfBegin, float *pfEnd, float &fGapMax, long &nTotalCount, long &nMaxPos);
// 	void CalFetureAvg(float *pfBegin, float *pfEnd, float &fGapMax, long &nTotalCount, long &nMaxPos, float fSetSub);
// 	void RemoveLittleFetures(PRCD_CMP_FETURES pFetures);
	void RcdFetureAllign();
	BOOL RcdFetureCmp(PRCD_CMP_FETURE pFeture1, PRCD_CMP_FETURE pFeture2);

protected:
	CMemBuffer_Float *m_pDeltaBuffer1;
	CMemBuffer_Float *m_pDeltaBuffer2;
	CMemBuffer_Float *m_pBuffer1;
	CMemBuffer_Float *m_pBuffer2;

	RCD_CMP_FETURES m_oRcdCmpBuffers1;
	RCD_CMP_FETURES m_oRcdCmpBuffers2;

	PRCD_CMP_FETURE m_pRcdCmpFeture1;
	PRCD_CMP_FETURE m_pRcdCmpFeture2;

	long m_nSampleRate1;
	long m_nSampleRate2;

	float m_fSetValForFind;
	float m_fSetValForCmp;
	long m_nAllignPosition1, m_nAllignPosition2;
};


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

class CRecordCompareTool : public CExBaseList
{
public:
	CRecordCompareTool();
	virtual ~CRecordCompareTool();

	long m_nBeginPos1, m_nEndPos1;
	long m_nBeginPos2, m_nEndPos2;

public:
	void Compare(CRecordTest *pRecordTest1, CRecordTest *pRecordTest2);
	CExBaseObject* FindCmpVariable1(CExBaseObject *pVar2, BOOL bRecordCmpDrawAllMatchCh);

protected:
	CRecordTest *m_pRecordTest1;
	CRecordTest *m_pRecordTest2;
	CExBaseList m_listCmpVariable;

protected:
	void CreateCmpVariable(CRtVariables *pRtVariables1, CRtVariables *pRtVariables2, long nSampleRate1, long nSampleRate2);
	void CreateCmpVariableEx(CRtVariables *pRtVariables1, CRtVariables *pRtVariables2, long nSampleRate1, long nSampleRate2);
	CRecordCmpVariable* CreateCmpVariable(CRtSingleVariable *pVariable, CRtVariables *pRtVariables, long nSampleRate1, long nSampleRate2);
	CRtSingleVariable*FindCmpVariable(CRtSingleVariable *pVariable, CRtVariables *pRtVariables);
	void AlignRecord();
	void SetVariablesUse(CRtVariables *pRtVariables, BOOL bUse);
	CRecordCmpVariable* GetAlignPosVariable2(long &nAlignPos);
	void InitCmpVariablesList();

};


#endif // !defined(AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)

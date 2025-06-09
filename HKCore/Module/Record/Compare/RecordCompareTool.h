// RecordCompareTool.h: interface for the CRecordCompareTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)
#define AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RecordCmpVariable.h"
#include "..\..\DataMngr\DvmDataset.h"

class CRecordCompareTool : public CExBaseList
{
public:
	CRecordCompareTool();
	virtual ~CRecordCompareTool();

	long m_nBeginPos1, m_nEndPos1, m_nAlignPos1;
	long m_nBeginPos2, m_nEndPos2, m_nAlignPos2;

public:
	void Compare(CRecordTest *pRecordTest1, CRecordTest *pRecordTest2);
	CExBaseObject* FindCmpVariable1(CExBaseObject *pVar2, BOOL bRecordCmpDrawAllMatchCh);
	CDvmDataset* GetRcdCmpResult()	{	return &m_oCmpResult;	}
	BOOL IsRcdCmpSucc()		{	return ((m_nAlignPos1 > 0) && (m_nAlignPos2 > 0));	}
	double FindPeakValueByStrName(double PeakValue, CString strPh);//通过Variable2的通道名称获得峰值,Liumy,20220927

protected:
	CRecordTest *m_pRecordTest1;
	CRecordTest *m_pRecordTest2;
	CExBaseList m_listCmpVariable;
	CDvmDataset m_oCmpResult;
	CDvmDataset m_oCfgTestConfig;
	long m_bAlignRlt;//是否对齐成功

protected:
	void CreateCmpVariable(CRtVariables *pRtVariables1, CRtVariables *pRtVariables2, long nSampleRate1, long nSampleRate2);
	void CreateCmpVariableEx(CRtVariables *pRtVariables1, CRtVariables *pRtVariables2, long nSampleRate1, long nSampleRate2);
	CRecordCmpVariable* CreateCmpVariable(CRtSingleVariable *pVariable, CRtVariables *pRtVariables, long nSampleRate1, long nSampleRate2);
	CRtSingleVariable*FindCmpVariable(CRtSingleVariable *pVariable, CRtVariables *pRtVariables);
	BOOL AlignRecord();
	void SetVariablesUse(CRtVariables *pRtVariables, BOOL bUse);
	CRecordCmpVariable* GetAlignPosVariable2(long &nAlignPos);
	void InitCmpVariablesList();

	void InitCmpResult();
	void InitCmpResult_Fault();
	void InitCmpResult_Fault_Ph_Pp(CRtVariables *pRtVariables, const CString &strPrefix);
	void InitCmpResult_Fault(const CString &strPrefix);
	void InitCmpResult_Variable(CRtSingleVariable *pRtVariable, const CString &strType, const CString &strPrefix);
	void InitCmpResult_Other();
	void InitCmpResult_PeakVellay();

	void InitAnalyseResult();
	void InitAnalyseResult_Fault();
	void InitAnalyseResult_Fault_Ph_Pp(CRtVariables *pRtVariables, const CString &strPrefix);
	void InitAnalyseResult_Fault(const CString &strPrefix);
	void InitAnalyseResult_Variable(CRtSingleVariable *pRtVariable, const CString &strType, const CString &strPrefix);
	void InitAnalyseResult_Other();
	void InitAnalyseResult_PeakVellay();

	void InitCmpResult_Cfg();
	void InitCmpResult_Cfg_Order();
	void InitCmpResult_Cfg_Name();
	void InitCmpResult_Cfg_Name(const CString &strUnit, const CString &strCh, const CString &strName, CString &strError);
	void InitCmpResult_Cfg_Phase();
	void InitCmpResult_Single_bmp();   //单通道位图,20220918,Liumy

};


#endif // !defined(AFX_RecordCompareTool_H__C8A73265_F86A_47C5_970E_13CB1131337F__INCLUDED_)

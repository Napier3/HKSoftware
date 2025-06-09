// RtDataAttribute.h: interface for the CRtDataAttribute class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTDATAATTRIBUTE_H__51F3FB9C_E490_48FE_AAB4_1679B88892CF__INCLUDED_)
#define AFX_RTDATAATTRIBUTE_H__51F3FB9C_E490_48FE_AAB4_1679B88892CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../Module/BASECLASS/ExBaseList.h"
#include "RecordTestClassDef.h"
#include "RtScript.h"

#include "RtSets.h"

//#define _TEST_CAL_VALUE

class CRtVariable;
class CRtVariables;

class CRtDataAttribute : public CExBaseList  
{
public:
	CRtDataAttribute();
	virtual ~CRtDataAttribute();
	
public:
	//�ؼ���
// 	static const char *g_pszKeyDataAttr;
// 	static const char *g_pszKeyAttrID;
// 	static const char *g_pszKeyUse;
// 	static const char *g_pszKeyUnit;	
// 	static const char *g_pszKeyBufferID;	

	//��������
	double *m_pdValue;         //����ֵ
	double *m_pdMutationValue; //����ֵͻ����
	UINT    m_nAttributeID;
	//CString m_strID;
	CString m_strUnit;
	CString m_strBufferID;
	
	CRtAttrScript *m_pScript; //���Լ���ű�


	CRtSets *m_pSets;

	CALFUNC *m_pfCalFunc;
	RTCALFUNCPARA m_oCalFuncPara;
	CMemBuffer_Float *m_pAttrBuffer;
	CRtDataAttribute *m_pAssociateAttr;

	//�����Ŀ�¡����
	CRtDataAttribute* m_pClone;
public:
	//�ɱ��ⲿ���õķ���
#ifdef _record_use_all_mode_
	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif

	virtual void CalValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer);
	virtual void CalValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer);
	virtual void CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer);
	void AddValueToAttrBuffer();
	virtual void CalFaultValues(long nBeginPos, long nLen, long nCyclePoints);

	BOOL JudgeStartup(long &nStartup);
	void OnSetUseChanged();
	void SetSpyState(long nSpyState);
	virtual double* GetValueRefByID(const CString &strID);
	virtual double* GetMutationValueRefByID(const CString &strID);	
	virtual double* GetAttrValueRefByID(const CString &strID);
	virtual void InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr);	
	BOOL BuildExpression();
	BOOL InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);
	
	//���صķ���		
	virtual UINT GetClassID();
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	virtual const char* GetXmlElementKey();
#endif
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);

	//����Ӧ���ܣ���ͨ��/����ͨ����
// 	virtual CExBaseObject* RTClone();
// 	virtual long RTCloneOwn(CExBaseObject* pDest);
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);
	void InitAfterClone();
	
	//����Ӧ��������ͨ���������
	void InitByAttrID(const CString &strMultiID, long nAttrID);
	void CreateMultiAttrSets();
	CString InitMultiAttrUnit(const CString &strMultiID, long nAttrID);

	//���οؼ���صĲ���
	//virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter = TVI_LAST);

	//ͨ������AttrID������Ե�Index����������
	CString GetAttrName();
	
	//˲ʱֵ�����ж�
	BOOL JudgeStartupAnalogInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);
	BOOL JudgeStartupBinaryInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);
	
	//�ı����Ե�λ
	void ChangeToMilliUnit();//��Ϊ����/����
	void ChangeToUnit();//��Ϊ��/��

	double* GetCalValue();

	void InitAttrBuffer(long nPoints);

public:
	void InitCalFuncPara(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos);
	void InitCalFuncPara();
	void SetUse(long nUse);
	long GetUse()    {   return m_nUse;   }
	long GetSpyState()   {   return m_nSpyState;  }

	BOOL IsEffcValue()		{	return (m_nAttributeID == SingleVariableAttrID_EffecValue);		}
	BOOL IsFrequence()		{	return (m_nAttributeID == SingleVariableAttrID_Frequancy);		}
	BOOL IsInstAttr()		{	return (m_nAttributeID == SingleVariableAttrID_InstValue);		}
	BOOL IsFundValueAttr()	{	return  (m_nAttributeID == SingleVariableAttrID_FundValue);		}
	BOOL IsHarmValueAttr()
	{
		return ( (m_nAttributeID == SingleVariableAttrID_FundValue)
			  || (SingleVariableAttrID_Harm02Value <= m_nAttributeID && m_nAttributeID <= SingleVariableAttrID_Harm25Value) );
	}
	BOOL IsHarmPhase();

	BOOL IsBinaryAttr()		{	return ((m_nAttributeID == BinaryVariableAttrID_Raise) || (m_nAttributeID == BinaryVariableAttrID_Fall));		}


	BOOL IsAttrNeededByOnline()		{	return (IsEffcValue() || IsFrequence() || IsInstAttr() || IsHarmValueAttr());	}
	BOOL IsAttrNeededByOscigraph()	{	return (IsEffcValue() || IsFrequence() || IsInstAttr());	}
	CString GetHarmNumID();

	void CloneRtDataAttribute(CRtDataAttribute* pSrc);
private:
	long m_nUse;
	long m_nSpyState;

	long* m_pnInstUse[3];//˲ʱֵ�����Ķ�ֵ�ж�
	short m_nInstSet[3]; //˲ʱֵ�����Ķ�ֵֵת��ɵ�����ֵ

private:
	void AnalogInstSet();//ģ����˲ʱֵ����
	short GetOldData(long nBegin,long nBufferLen,unsigned short* pnBuffer);

	//ģ������˲ʱֵ�����ж�
	void JudgeStartupAnalogInstHigh(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);
	void JudgeStartupAnalogInstLow(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);
	void JudgeStartupAnalogInstMutation(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);

	//��������˲ʱֵ�����ж�
	void JudgeStartupBinaryInstJumpUp(long nBitIndex,short nOldData,long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);
	void JudgeStartupBinaryInstJumpDown(long nBitIndex,short nOldData,long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);

	//����������λ��
	void SetStartupPos(long nPos,long nStartup);
};

#endif // !defined(AFX_RTDATAATTRIBUTE_H__51F3FB9C_E490_48FE_AAB4_1679B88892CF__INCLUDED_)

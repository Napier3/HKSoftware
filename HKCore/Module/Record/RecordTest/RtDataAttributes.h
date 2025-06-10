// RtDataAttributes.h: interface for the CRtDataAttributes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTDATAATTRIBUTES_H__568E119C_BEB6_4DFB_9D35_E5D444840B28__INCLUDED_)
#define AFX_RTDATAATTRIBUTES_H__568E119C_BEB6_4DFB_9D35_E5D444840B28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "RtDataAttribute.h"

class CRtDataAttributes : public CExBaseList  
{
public:
	CRtDataAttributes();
	virtual ~CRtDataAttributes();

public:
	//�ؼ���
	static const char *g_pszKeyDataAttrs;
	long  m_nStaticAttrs;//Sigleģ��ͨ���������Ĳ�������,����Ƶ�ʡ���Чֵ����λ��������Чֵ��������λ
	
	//�����Ŀ�¡����
	CRtDataAttributes* m_pClone;

public:	
	//�ɱ��ⲿ���õķ���
#ifdef _record_use_all_mode_
	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes);
	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	virtual const char* GetXmlElementKey();
#endif
	void CalValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCal, BOOL bCalUseRecordBuffer);
	void CalStaticValues_Quick(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);
	void CalValues_PeakVellay(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);
	void CalStaticValues(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bAddFrequency, BOOL bCalUseRecordBuffer);
	void InitCalFuncPara();
	void CalFrequncy(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, BOOL bCalUseRecordBuffer);
	BOOL JudgeStartup(long &nStartup);
	void CalFaultValues(long nBeginPos, long nLen, long nCyclePoints);
	CRtDataAttribute* FindFaultSrcAttr(UINT nAttrID);

	virtual double* GetValueRefByID(const CString &strID);
	virtual double* GetMutationValueRefByID(const CString &strID);	
	virtual double* GetAttrValueRefByID(const CString &strID);
	virtual void InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr);	
	void AdjustStaticAttrs();
	BOOL BuildExpression();
	BOOL InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);
	long GetAttrCountWithSets();

	void AdjustMultiVariableAttrs();
	//���صķ���
	virtual UINT GetClassID();
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);
// 
	CRtDataAttribute* FindByAttrID(const char* pstrAttrID);
	CRtDataAttribute* FindByAttrID(UINT nAttrID);
	
	void InitAssociateAttrs();//�������Բ���������ID,����InitAssociateAttr
	void InitAssociateAttr(CRtDataAttribute *pAttr);
	double* GetValueByAttrID(UINT nAttrID);
	
	void InitVariablesAttrList(CRtDataAttribute *pAttr);

	//virtual CExBaseObject* RTClone();
	
	//����Ӧ����multivariable����
	void AutofitCreateMultiAttrChild(const CString &strMultiName);
	void CreateSequenceAttrs(const CString &strMultiID);//������ѹ���������������ԣ��������򡢸�������
	void CreateAttrsWithUI(const CString &strMultiID);//����һ����ѹһ������֮������ԣ����迹���й�����
	CRtDataAttribute* CreateMultiAttrByAttrID(const CString &strMultiID, long nAttrID);//������������ID��������

	void ResetUseAndSpy();
	void SetAttr(CRtDataAttribute* pAttr,long nIndex);

	void ResetAttrSpyState();


	//��ȡ��������(��г����λ֮��)�Ķ�ֵ���ܺ�
	//long GetAllAttrSetCount();

	//��ȡ��������(����λ֮��)�ĵ�ͨ����ֵ���ܺ�
	long GetAllAttrSetCountForSetGrid();
	
	//��ȡ��������(��Чֵ��Ƶ�ʡ�˲ʱֵ)�ĵ�ͨ����ֵ���ܺ�
	long GetEffFreInstSetCountForSetGrid();

	//��¡����
	void CloneRtDataAttributes(CRtDataAttributes* pSrc);

	void CalInstValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos,BOOL bCalUseRecordBuffer);//˲ʱֵ���㣬fdp add 2010.10.8
	void InitAttrsBuffer(long nPoints);
	void SetAttrUse(UINT nAttrID, long nUse);

private:
	CRtDataAttribute* FindAttr(const CString &pszAttrID);
	CRtDataAttribute* FindAttr(UINT nAttrID);
	void AddStaticAttr(const CString &pszAttrID, const CString &pszUnit, long nIndex);


	CRtDataAttribute* m_paDataAttributes[MAX_CHANNEL_ATTRID_KEYS+1];
};

#endif // !defined(AFX_RTDATAATTRIBUTES_H__568E119C_BEB6_4DFB_9D35_E5D444840B28__INCLUDED_)

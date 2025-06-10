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
	//关键字
	static const char *g_pszKeyDataAttrs;
	long  m_nStaticAttrs;//Sigle模拟通道必须计算的参数个数,包括频率、有效值、相位、基波有效值、基波相位
	
	//关联的克隆对象
	CRtDataAttributes* m_pClone;

public:	
	//可被外部调用的方法
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
	//重载的方法
	virtual UINT GetClassID();
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);
// 
	CRtDataAttribute* FindByAttrID(const char* pstrAttrID);
	CRtDataAttribute* FindByAttrID(UINT nAttrID);
	
	void InitAssociateAttrs();//关联属性参数的属性ID,调用InitAssociateAttr
	void InitAssociateAttr(CRtDataAttribute *pAttr);
	double* GetValueByAttrID(UINT nAttrID);
	
	void InitVariablesAttrList(CRtDataAttribute *pAttr);

	//virtual CExBaseObject* RTClone();
	
	//自适应创建multivariable属性
	void AutofitCreateMultiAttrChild(const CString &strMultiName);
	void CreateSequenceAttrs(const CString &strMultiID);//创建电压或电流的序分量属性，包括正序、负序、零序
	void CreateAttrsWithUI(const CString &strMultiID);//创建一个电压一个电流之间的属性，如阻抗、有功功率
	CRtDataAttribute* CreateMultiAttrByAttrID(const CString &strMultiID, long nAttrID);//根据属性数字ID创建属性

	void ResetUseAndSpy();
	void SetAttr(CRtDataAttribute* pAttr,long nIndex);

	void ResetAttrSpyState();


	//获取所有属性(除谐波相位之外)的定值的总和
	//long GetAllAttrSetCount();

	//获取所有属性(除相位之外)的单通道定值的总和
	long GetAllAttrSetCountForSetGrid();
	
	//获取所有属性(有效值、频率、瞬时值)的单通道定值的总和
	long GetEffFreInstSetCountForSetGrid();

	//克隆对象
	void CloneRtDataAttributes(CRtDataAttributes* pSrc);

	void CalInstValue(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos,BOOL bCalUseRecordBuffer);//瞬时值计算，fdp add 2010.10.8
	void InitAttrsBuffer(long nPoints);
	void SetAttrUse(UINT nAttrID, long nUse);

private:
	CRtDataAttribute* FindAttr(const CString &pszAttrID);
	CRtDataAttribute* FindAttr(UINT nAttrID);
	void AddStaticAttr(const CString &pszAttrID, const CString &pszUnit, long nIndex);


	CRtDataAttribute* m_paDataAttributes[MAX_CHANNEL_ATTRID_KEYS+1];
};

#endif // !defined(AFX_RTDATAATTRIBUTES_H__568E119C_BEB6_4DFB_9D35_E5D444840B28__INCLUDED_)

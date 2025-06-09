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
	//关键字
// 	static const char *g_pszKeyDataAttr;
// 	static const char *g_pszKeyAttrID;
// 	static const char *g_pszKeyUse;
// 	static const char *g_pszKeyUnit;	
// 	static const char *g_pszKeyBufferID;	

	//自身属性
	double *m_pdValue;         //属性值
	double *m_pdMutationValue; //属性值突变量
	UINT    m_nAttributeID;
	//CString m_strID;
	CString m_strUnit;
	CString m_strBufferID;
	
	CRtAttrScript *m_pScript; //属性计算脚本


	CRtSets *m_pSets;

	CALFUNC *m_pfCalFunc;
	RTCALFUNCPARA m_oCalFuncPara;
	CMemBuffer_Float *m_pAttrBuffer;
	CRtDataAttribute *m_pAssociateAttr;

	//关联的克隆对象
	CRtDataAttribute* m_pClone;
public:
	//可被外部调用的方法
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
	
	//重载的方法		
	virtual UINT GetClassID();
#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	virtual const char* GetXmlElementKey();
#endif
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);

	//自适应功能（单通道/开关通道）
// 	virtual CExBaseObject* RTClone();
// 	virtual long RTCloneOwn(CExBaseObject* pDest);
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);
	void InitAfterClone();
	
	//自适应创建复合通道属性相关
	void InitByAttrID(const CString &strMultiID, long nAttrID);
	void CreateMultiAttrSets();
	CString InitMultiAttrUnit(const CString &strMultiID, long nAttrID);

	//树形控件相关的操作
	//virtual void InsertTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand, HTREEITEM hAfter = TVI_LAST);

	//通过属性AttrID获得属性的Index和属性名称
	CString GetAttrName();
	
	//瞬时值启动判断
	BOOL JudgeStartupAnalogInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);
	BOOL JudgeStartupBinaryInst(PRTATTRIBUTECALBUFFERPOS pRtAttrCalBufPos, long &nStartup);
	
	//改变属性单位
	void ChangeToMilliUnit();//变为毫伏/毫安
	void ChangeToUnit();//变为伏/安

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

	long* m_pnInstUse[3];//瞬时值启动的定值判断
	short m_nInstSet[3]; //瞬时值启动的定值值转变成的数字值

private:
	void AnalogInstSet();//模拟量瞬时值设置
	short GetOldData(long nBegin,long nBufferLen,unsigned short* pnBuffer);

	//模拟量的瞬时值启动判断
	void JudgeStartupAnalogInstHigh(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);
	void JudgeStartupAnalogInstLow(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);
	void JudgeStartupAnalogInstMutation(long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);

	//开关量的瞬时值启动判断
	void JudgeStartupBinaryInstJumpUp(long nBitIndex,short nOldData,long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);
	void JudgeStartupBinaryInstJumpDown(long nBitIndex,short nOldData,long nBegin1,long nLen1,long nBegin2,long nLen2,long nBufferLen,unsigned short* pnBuffer,long &nStartup);

	//设置启动点位置
	void SetStartupPos(long nPos,long nStartup);
};

#endif // !defined(AFX_RTDATAATTRIBUTE_H__51F3FB9C_E490_48FE_AAB4_1679B88892CF__INCLUDED_)

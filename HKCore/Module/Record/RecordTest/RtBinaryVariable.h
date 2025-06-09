// RtBinaryVariable.h: interface for the CRtBinaryVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTBINARYVARIABLE_H__B00682F3_54F0_4028_94A9_90B3914D66BA__INCLUDED_)
#define AFX_RTBINARYVARIABLE_H__B00682F3_54F0_4028_94A9_90B3914D66BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtVariable.h"
#define BINARYVARIABLE_HDINDEX   12

class CRtBinaryVariable : public CRtVariable  
{
public:
	CRtBinaryVariable();
	virtual ~CRtBinaryVariable();

//属性
public:
	//关键字
	static const char *g_pszKeyBinaryVariable;
	static const char *g_pszKeyIndex;
	
	static const char* g_pszKeyBinaryRaise;
	static const char* g_pszKeyBinaryFall;
	//自身属性
	long m_nIndex;

//方法
public:
	//重载的方法
	virtual long GetRtVariableClassID()		{    return 0;   }
	virtual UINT GetClassID()	{		return RTCLASSID_BINARYVARIABLE;	}

#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	virtual BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);	
#endif
	
	//试验相关的方法
	virtual void InitBufferMngr(CRtMemBufferMngr *pRtMemBufferMngr);	
	virtual BOOL InitDataAttributeCalFunc(BOOL bCalUseRecordBuffer);
	virtual BOOL GetCalFuncByAttrID(const CString &strAttrID, double **ppdValue, double **ppdMutationValue, UINT &nAttrID, CALFUNC **ppCalFunc, RTCALFUNCPARA &oRtCalFuncPara, BOOL bCalUseRecordBuffer);

	//自适应功能
// 	virtual CExBaseObject* RTClone();
// 	virtual long RTCloneOwn(CExBaseObject* pDest);
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);
};

#endif // !defined(AFX_RTBINARYVARIABLE_H__B00682F3_54F0_4028_94A9_90B3914D66BA__INCLUDED_)

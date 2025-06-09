// RtComplexVariable.h: interface for the CRtComplexVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RTCOMPLEXVARIABLE_H__)
#define _RTCOMPLEXVARIABLE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RtSingleVariable.h"

//CRtComplexVariable是基于通道的
class CRtComplexVariable : public CRtSingleVariable  
{
public:
	CRtComplexVariable();
	virtual ~CRtComplexVariable();

//属性
public:
	//关键字
// 	static const char *g_pszKeyComplexVariable;

//方法
public:
	//重载的方法
	virtual UINT GetClassID()                        {     return RTCLASSID_COMPLEXVARIABLE;    };
	virtual long GetRtVariableClassID()		{	return 0;	}

#ifdef _record_use_all_mode_
	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	
	virtual BOOL ReadSetsValueXml(MSXML::IXMLDOMNodePtr &oNode);
	virtual BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);		
#endif
};

#endif // !defined(_RTCOMPLEXVARIABLE_H__)

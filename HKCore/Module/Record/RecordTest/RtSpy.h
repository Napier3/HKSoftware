// RtSpy.h: interface for the CRtSpy class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSPY_H__98A5D533_513A_4107_9551_962155919087__INCLUDED_)
#define AFX_RTSPY_H__98A5D533_513A_4107_9551_962155919087__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../MODULE/BASECLASS/ExBaseObject.h"
#include "RecordTestClassDef.h"

//CRtSpy暂时未用到
class CRtSpy : public CExBaseObject  
{
public:
	CRtSpy();
	virtual ~CRtSpy();

public:
	//节点属性
	long    m_nRefreshTime;
	long    m_nTimeWnd;
	
	//关键字
	static const char *g_pszKeySpy;
	static const char *g_pszKeyRefreshTime;
	static const char *g_pszKeyTimeWnd;
	
public:
	//重载的方法
	virtual UINT GetClassID()            {     return RTCLASSID_SPY;     }
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
// 	virtual const char* GetXmlElementKey()        {     return g_pszKeySpy;        };
	
};

#endif // !defined(AFX_RTSPY_H__98A5D533_513A_4107_9551_962155919087__INCLUDED_)

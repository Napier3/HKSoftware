// RtChannels.h: interface for the CRtChannels class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCHANNELS_H__281B5535_5129_40BF_BBFE_2B56A34E8E90__INCLUDED_)
#define AFX_RTCHANNELS_H__281B5535_5129_40BF_BBFE_2B56A34E8E90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../Module/BASECLASS/ExBaseList.h"
#include "RtChannel.h"
#include "RtScript.h"

class CRtChannels : public CExBaseList  
{
public:
	CRtChannels();
	virtual ~CRtChannels();

public:
	//重载的方法
	virtual UINT GetClassID();
// 	virtual CExBaseObject* CreateNewChild();
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild(long nClassID);

#ifdef _record_use_all_mode_
	virtual const char* GetXmlElementKey();
	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	BOOL ReadSetsValueXml(MSXML::IXMLDOMNodeListPtr &oNodes);
	BOOL WriteSetsValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
#endif
public:
	//关键字
	static const char *g_pszKeyChannels;

public:
	CRtScript *m_pScript;
	
	//自适应创建Multivariable的channal
	void AutofitCreateMultiChChild(const CString &strMultiID, char **szAutoMultiChsName);
};

#endif // !defined(AFX_RTCHANNELS_H__281B5535_5129_40BF_BBFE_2B56A34E8E90__INCLUDED_)

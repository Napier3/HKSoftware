// RtCfgAppModels.h: interface for the CRtCfgAppModels class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RTCFGAPPMODELS_H__)
#define _RTCFGAPPMODELS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../MODULE/BASECLASS/ExBaseList.h"
#include "RecordTestClassDef.h"

class CRtCfgAppModel : public CExBaseObject 
{
public:
	CRtCfgAppModel();
	virtual ~CRtCfgAppModel();
	
public:
	static const char* g_pszKeyAppModel;
	static const char* g_pszKeyMaxSpyBuffer;
	static const char* g_pszKeyMaxRecordBuffer;
	static const char* g_pszKeyHDBuffer;

	long  m_nMaxSpyBuffer;
	long  m_nMaxRecordBuffer;
	long  m_nHDBuffer;

	//方法
public:
	//重载的方法
	virtual UINT GetClassID()                {  return RTCLASSID_APPMODEL;  };
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);
	CRtCfgAppModel* Clone();
};


class CRtCfgAppModels : public CExBaseList  
{
private:
	CRtCfgAppModels();
	virtual ~CRtCfgAppModels();


public:
	static CRtCfgAppModels* g_pRtCfgAppModels;
	static long  m_nRtCfgAppModelsRefCount;
	static CRtCfgAppModels* CreateRtCfgAppModels();
	void Release();

	static const char* g_pszKeyAppModels;
	
public:
	virtual CExBaseObject* CreateNewChild();
	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	
	CRtCfgAppModel* Clone(const CString &strID);
};

#endif // !defined(_RTCFGAPPMODELS_H__)

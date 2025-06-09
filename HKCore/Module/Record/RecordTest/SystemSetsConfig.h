// SystemSetsConfig.h: interface for the CSystemSetsConfig class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMSETSCONFIG_H__9A8C9DBB_058C_4673_BAB9_ED70A593F469__INCLUDED_)
#define AFX_SYSTEMSETSCONFIG_H__9A8C9DBB_058C_4673_BAB9_ED70A593F469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "SystemSetAttr.h"
#define Multi_Default_Range 100 //因为定值设置是根据量程设置的，而复合通道没有量程，默认设置一个值

class CSystemSetsConfig : public CExBaseList  
{
public:
	CSystemSetsConfig();
	virtual ~CSystemSetsConfig();

public:
	static const char* g_pszKeySystemSetsConfigFile;
	static const char* g_pszKeySystemSetsConfig;
	static const char* g_pszKeyTotalTime;
	static const char* g_pszKeyLookBackTime;
	static const char* g_pszKeyRecordGap;
	static const char* g_pszKeyChannelUse;

	double m_dTotalRecordTime;
	double m_dLookBackTime;
	long m_nRecordGap;
	long m_nChannelUse;

public:
	virtual UINT GetClassID(){		return RTCLASSID_SYSTEMSETSCONFIG;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual const char* GetXmlElementKey()	{	return g_pszKeySystemSetsConfig;	}
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{    return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)   	{    return NULL;	}

public:
	//BOOL ReadSystemSetsConfigFromFile(const CString &strFile);
	CSystemSetAttr* FindSystemSetAttrByID(const CString& strID);
};

#endif // !defined(AFX_SYSTEMSETSCONFIG_H__9A8C9DBB_058C_4673_BAB9_ED70A593F469__INCLUDED_)

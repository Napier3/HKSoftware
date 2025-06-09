// SystemSetAttr.h: interface for the CSystemSetAttr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMSETATTR_H__30AF6041_040F_458B_8FE9_290F48952441__INCLUDED_)
#define AFX_SYSTEMSETATTR_H__30AF6041_040F_458B_8FE9_290F48952441__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../Module/BASECLASS/ExBaseObject.h"
#include "RecordTestClassDef.h"

class CSystemSetAttr : public CExBaseObject  
{
public:
	CSystemSetAttr();
	virtual ~CSystemSetAttr();

public:
// 	static const char* g_pszKeySystemSetsAttr;
// 	static const char* g_pszKeyAttrUse;
// 	static const char* g_pszKeyHigh;
// 	static const char* g_pszKeyHighUse;
// 	static const char* g_pszKeyLow;
// 	static const char* g_pszKeyLowUse;
// 	static const char* g_pszKeyMutation;
// 	static const char* g_pszKeyMutationUse;

public:
	double m_dHighPercentValue;
	double m_dLowPercentValue;
	double m_dMutationPercentValue;

	long m_nAttrUse;
	long m_nHighUse;
	long m_nLowUse;
	long m_nMutationUse;

public:
	virtual UINT GetClassID(){		return RTCLASSID_SYSTEMSETATTR;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual const char* GetXmlElementKey()	{	return g_pszKeySystemSetsAttr;	}
};

#endif // !defined(AFX_SYSTEMSETATTR_H__30AF6041_040F_458B_8FE9_290F48952441__INCLUDED_)

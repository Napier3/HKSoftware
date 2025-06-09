// RtCfgVariable.h: interface for the CRtCfgVariable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCFGVARIABLE_H__D669FBC7_0676_4557_9AD3_49339C5DBD38__INCLUDED_)
#define AFX_RTCFGVARIABLE_H__D669FBC7_0676_4557_9AD3_49339C5DBD38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../../MODULE/BASECLASS/ExBaseObject.h"
#include "RecordTestClassDef.h"
class CRtCfgVariables;

class CRtCfgVariable : public CExBaseObject  
{
public:
	CRtCfgVariable();
	virtual ~CRtCfgVariable();

//属性
public:	
	//关键词
	static const char *g_pszKeyColor;
	static const char *g_pszKeySingleVariable;
	static const char *g_pszKeyBinaryVariable;
	static const char *g_pszKeyDCAC;
	static const char *g_pszKeyRange;
	static const char *g_pszKeyPhaseID;

	//电压/电流的数量
	static long m_nUCount;
	static long m_nICount;
	
	//自身属性
	long    m_nType;
	CString m_strDCAC;
	long    m_nACDC;
	double  m_dRange;
	CString m_strPhaseID;	
	long    m_nMemBuffer;
	BOOL    m_bIsBinaryVariable;
	
//方法
public:
	//重载的方法
	virtual UINT GetClassID()     {		return RTCLASSID_CFGVARIABLE;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
};

#endif // !defined(AFX_RTCFGVARIABLE_H__D669FBC7_0676_4557_9AD3_49339C5DBD38__INCLUDED_)

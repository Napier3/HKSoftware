// RtSet.h: interface for the CRtSet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSET_H__F9967D2E_8027_42BA_8AF1_3BBC0B0C700F__INCLUDED_)
#define AFX_RTSET_H__F9967D2E_8027_42BA_8AF1_3BBC0B0C700F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseObject.h"
#include "RtScript.h"
#include "../RecordGlobalDefine.h"

class CRtDataAttribute;
class CRtDataAttributes;
class CRtVariable;
class CMR1200BaseApp;

#define  SET_TYPE_HIGH		0
#define  SET_TYPE_LOW		1
#define  SET_TYPE_MUTATION  2
class CRtSet : public CExBaseObject  
{
public:
	CRtSet();
	virtual ~CRtSet();
public:
	//节点属性
	long    m_nUse;
	CString m_strUnit;
	double  m_dValue;
	long    m_nSratupIndex;//启动的顺序索引，主要在在线录波时使用
	CString m_strType;

	long m_nSetType;
	//关键字
	static const char *g_pszKeyUse;
	static const char *g_pszKeyUnit;
	static const char *g_pszKeyValue;
	static const char *g_pszKeySet;
	static const char *g_pszKeyType;

	static const char* g_pszKeyHigh;
	static const char* g_pszKeyLow;
	static const char* g_pszKeyMutation;
public:
	//重载的方法
	virtual UINT GetClassID();//得到类ID
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);//读自身节点
// 	virtual const char* GetXmlElementKey();
// 	virtual long WriteOwnXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oElement);

	//可以被外部调用的方法
// 	BOOL WriteSetValueXml(const MSXML::IXMLDOMDocumentPtr &oXMLDoc, const MSXML::IXMLDOMElementPtr &oParent);
// 	BOOL ReadSetValueXml(MSXML::IXMLDOMNodePtr &oSet);
	BOOL JudgeStartup(long &nStartup);
	BOOL JudgeStartup(long &nStartup,double* pdAttrValue,double* pdMutationValue);
	void SetUse(long nUse);
	long GetUse()	{	return m_nUse;	}
	BOOL BuildExpression();
	
	//自适应功能
// 	virtual CExBaseObject* RTClone();
// 	virtual long RTCloneOwn(CExBaseObject* pDest);
	virtual long RTUpdateOwnByAutofit(HDINFO &oHDInfo);

	//文件树形控件相关的操作
	//virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand);
	
private:
	CRtScript m_oScript;//判断启动的脚本对象

	//void _JudgeStartUpByValue(double dValue, long &nStartup);
	void GetSetLongTypeByStringType();
};

#endif // !defined(AFX_RTSET_H__F9967D2E_8027_42BA_8AF1_3BBC0B0C700F__INCLUDED_)

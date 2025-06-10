// RtCfgRecordTest.h: interface for the CRtCfgRecordTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCFGRECORDTEST_H__35EAB94E_2297_4694_AE64_F25BFE9EF592__INCLUDED_)
#define AFX_RTCFGRECORDTEST_H__35EAB94E_2297_4694_AE64_F25BFE9EF592__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"
#include "RtCfgVariables.h"
#include "RtCfgAppModels.h"
class CRtCfgRecordTests;
#define RT_CANBEUSED    0
#define RT_CANOTBEUSED  1
#define RT_DEVALOPING   2
#define RT_ENTRY        3


class CRtCfgRecordTest : public CExBaseList  
{
public:
	CRtCfgRecordTest();
	virtual ~CRtCfgRecordTest();

//属性
public:
	//关键字属性
	static const char *g_pszKeyRecordTest;
	static const char *g_pszKeyAppModel;
	static const char *g_pszKeyTestGroup_Type;
	static const char *g_pszKeyRemark;
	static const char *g_pszKeyRtInfo;
	static const char *g_pszKeyAnalysePage;
	static const char *g_pszKeyTestType;

	//子对象属性
	CRtCfgVariables *m_pVariables;    //变量定义
	//CExBaseList     *m_pAppModels;

	CString m_strTestGroupType;//试验组的类型ID
	CString m_strRemark;//试验的硬件说明信息,用于试验主界面表格中的硬件环境的显示
	CString m_strRtInfo;//选中的试验的信息描述
	long    m_nStatus;//试验的状态:可以试验\不可以试验\开发中
	CString m_strTestAnalysePage;//试验对应的分析界面Page名称
	CString m_strTestType;//试验类型ID

//方法
public:
	//重载的方法
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTEST;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);
// 	virtual long ReadChildrenXml(MSXML::IXMLDOMNodeListPtr &oNodes);
	
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()					{    return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)   	{    return NULL;	}
	
public:
// 	void InitAppModel(MSXML::IXMLDOMNodePtr &oNode);//创建设备子对象
	CString GetRTStatusString();
	long GetRTStatus();
	void SetRTStatus(long nRTStatus);
	BOOL IsUniversalTest();

	BOOL IsGetTestTypeOpen()   {	return m_strTestType == g_pRtTestFileType_gopn;	}
	BOOL IsGetTestTypeShort()  {	return m_strTestType == g_pRtTestFileType_gsht;	}

public:
	//文件树形控件相关的操作
	//virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand);	
};

#endif // !defined(AFX_RTCFGRECORDTEST_H__35EAB94E_2297_4694_AE64_F25BFE9EF592__INCLUDED_)

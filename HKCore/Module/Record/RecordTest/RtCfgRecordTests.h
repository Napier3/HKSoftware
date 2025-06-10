// RtCfgRecordTests.h: interface for the CRtCfgRecordTests class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTCFGRECORDTESTS_H__1638E34E_91C4_4880_A4E0_A80A78DFB2F0__INCLUDED_)
#define AFX_RTCFGRECORDTESTS_H__1638E34E_91C4_4880_A4E0_A80A78DFB2F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ExBaseList.h"

#include "RtCfgRecordTest.h"
#include "RtCfgAppModels.h"
//#include "../HDManager/HDMrDevice.h"

//####################CRtType#############################

class CRtType : public CExBaseList  
{
public:
	CRtType();
	virtual ~CRtType();
	
	//属性
public:
	//关键字属性
	static const char *g_pszKeyType;
	
	//方法
public:
	//重载的方法
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTESTTYPE;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
	
	//没有用到
	//CRtType* Clone();
};

//####################CRtTypes#############################
/*试验类型管理对象,管理每种试验类型,试验类型包括:发变组试验、线路组试验、其他试验、通用试验
*/
class CRtTypes : public CExBaseList  
{
private:
	CRtTypes();
	virtual ~CRtTypes();
	
	//属性
public:
	//关键字属性
	static const char *g_pszKeyTypes;
	static const char *g_pszKeyGenerTransformer;
	static const char *g_pszKeyCircuitGroup;
	static const char *g_pszKeyOther;
	static const char *g_pszKeyUniversal;
public:
	static CRtTypes* g_pRtTypes;
	static long  m_nRtTypesRefCount;
	
	static CRtTypes* CreateRtTypes();
	void Release();
	
	//方法
public:
	//重载的方法
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTESTTYPES;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
// 	
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()						{     return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)		{     return NULL;	}
// 	
// 	//自身方法，没有用到
// 	CRtType* Clone(const CString &strID);
};


/*实现试验功能的配置：根据硬件匹配试验，描述各类试验需要的试验环境(如设备型号、通道信息)、试验类型
*/
class CRtCfgRecordTests : public CExBaseList  
{
private:
	CRtCfgRecordTests();
	virtual ~CRtCfgRecordTests();

public:

	static CRtCfgRecordTests *g_pRtCfgRecordTests;
	static long  m_nRtCfgRecordTestsRefCount;
	static CRtCfgRecordTests* CrteateRtCfgRecordTests();
	void Release();
	
//属性
public:
	//关键字属性
	static const char *g_pszKeyRecordTests;
	static const char *g_pszConfigFile;

	//CRtCfgAppModels *m_pAppModels;//设备型号管理对象
	CRtTypes *m_pRtTypes;//试验分类管理对象
	CString m_strCurrRTtestInfo;
	CRtCfgRecordTest *m_pActiveRecordTest;//当前所做试验的对象指针，进入具体的试验界面后进行设置
//方法
public:
	//重载的方法
	virtual UINT GetClassID(){		return RTCLASSID_CFGRECORDTESTS;	}
// 	virtual long ReadOwnXml(MSXML::IXMLDOMNodePtr &oNode);	
// 	virtual long ReadChildrenXml(MSXML::IXMLDOMNodeListPtr &oNodes);
// 	
// 	virtual CExBaseObject* CreateNewChild(LPCTSTR pszClassID);
// 	virtual CExBaseObject* CreateNewChild()						{     return NULL;	}
// 	virtual CExBaseObject* CreateNewChild(long nClassID)		{     return NULL;	}
	
	//试验相关方法
	//读取试验配置文件
	BOOL ReadRtConfigFile(const CString &strFile);
	BOOL ReadRtConfigFile();

	//匹配硬件
// 	BOOL MatchTranslator(CHDMrDevice * pHDMrDevice);

	//当前选中试验信息的操作
	void SetCurrTestInfo(CString strTestInfo) {	  m_strCurrRTtestInfo = strTestInfo;	}
	CString GetCurrTestInfo()				  {   return m_strCurrRTtestInfo;	}

	//根据试验的类型查找所在的试验对象指针，以打开相应的分析界面
	CRtCfgRecordTest *FindByTestType(const CString &strTestType);
	
public:	
	//文件树形控件相关的操作
//	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent, BOOL bParentExpand);
	
private:
	//划分试验类型：例如试验类型包括发变组试验、线路组试验等，根据这些分类将每个功能试验进行分类	
	void AdjustTestByType();
	
	//调整通用试验，包括示波，在线录波
	void AdjustUniversalTest();

	//根据试验所需的量程，将试验排序，便于匹配硬件
	void SortTranRangeFromSmallToLarge(double *dRange, CExBaseList &oTranChannelList);//调用SortTransChannelRange
	void SortTransChannelRange(double *dRange, int Count);//调用Sort()
	void Sort(double *dRange,int left,int right);//排序算法

	//匹配硬件
	BOOL IsMatchFinish(long nMatchCount, CExBaseList &oChannelList);
	long MatchChannelRange(CExBaseList &oChannelList, double *dRange, long nTransUorICount);
};

inline CRtCfgRecordTests* GetCfgRecordTests()
{
	return CRtCfgRecordTests::g_pRtCfgRecordTests;
}



#endif // !defined(AFX_RTCFGRECORDTESTS_H__1638E34E_91C4_4880_A4E0_A80A78DFB2F0__INCLUDED_)

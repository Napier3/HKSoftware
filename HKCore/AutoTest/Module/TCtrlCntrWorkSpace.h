#pragma once

/*
	功能描述：工作区管理
	相关文件：WorkSpace.xsd、WorkSpace.xml
*/
#include "../../Module/BaseClass/ExBaseList.h"

#ifndef _PSX_QT_LINUX_
#include "TaskMngr/TestTask.h"
#include "TestControl/TestControlBase.h"
#endif

#include "TCtrlMsgRcvInterface.h"

class CTCtrlCntrWorkSpace : public CExBaseList
{
public:
	CTCtrlCntrWorkSpace();
	virtual ~CTCtrlCntrWorkSpace();

public:
	static CTCtrlCntrWorkSpace* g_pWorkSpace;
	static long g_nWorkSpaceRef;
	static CTCtrlCntrWorkSpace* Create();
	static void Release();

	//当前测试任务
	//CTestTask* m_pCurrTask;
	//CTestControl类型的链表对象 2010-08-02
#ifndef _PSX_QT_LINUX_
    CTLinkList<CTestControlBase> m_oTestControlList;
#endif

	//属性
	CString m_strAppExitState;    //程序关闭的状态
	CString m_strLastTaskFile;    //最后一个测试文件
	CString m_strLastTestFile;    //最后一个测试文件
	CString m_strLastTestState;   //上次的测试状态
	long m_nCurrTestItemIndex;    //上次的测试项目

	//临时数据
	CString m_strPpEngineProgID;  //规约组件
	CString m_strIecfgFile;	      //Iecfg文件
	CString m_strPpTemplateFile;  //规约模板文件
	CString m_strPpDeviceFile;    //设备点表文件
	CString m_strTemplateFile;    //作业指导书文件
	CString m_strReportMapFile;   //报告映射文件
	CString m_strTestFolder;      //测试的路径
	CString m_strTestName;
	CString m_strTestID;
	DWORD   m_dwTkID_Index;       //当前的测试类型

#ifndef _PSX_QT_LINUX_
    CPpDeviceRefs m_oPpDeviceRefs;

	//2023-4-2  lijunqing
	CPpSttCommConfigs *m_pSttCommConfigs;
	CPpSttCommConfig  *m_pSttCommConfig;
#endif

public:
	//基本方法
	virtual BOOL Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID();
	//串行化
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();
	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	//创建子对象
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	//工作区
	long Save();
	long Open();

public:
	//2010-07-07
	//CTestTask* FindTaskByLocalID(const CString &strLocalID);
	//2010-08-04 CMainFrame继承自CTCtrlMsgRcvInterface
    CTCtrlMsgRcvInterface* FindMsgRcvWndByTestProject(CExBaseObject* pTestProject);

	CString GetLastTaskFile();
	CString GetLastTestFile();
	CString GetLastTestState();
	void SetLastTestFile(const CString &strTestFile);
	void SetLastTaskFile(const CString &strTestFile);
	void SetLastTestState(const CString &strTestState);
	void SetCurrTestItemIndex(long nCurrTestItemIndex);
	CString GetNewGuideBookBinaryFileName();

	CString GetPpEngineProgID()	{	return m_strPpEngineProgID;	}
	CString GetPpTemplateFile()	{	return m_strPpTemplateFile;	}
	CString GetPpDeviceFile()	{	return m_strPpDeviceFile;	}
	CString GetTemplateFile()	{	return m_strTemplateFile;	}
	CString GetReportMapFile() 	{	return m_strReportMapFile;	}
	CString GetTestFolder() 	{	return m_strTestFolder;		}
	CString GetTestName()		{	return m_strTestName;		}
	CString GetTestID()			{	return m_strTestID;			}
	void SetPpEngineProgID(const CString &str)	{	m_strPpEngineProgID = str;	}
	void SetPpTemplateFile(const CString &str)	{	m_strPpTemplateFile = str;	}
	void SetPpDeviceFile(const CString &str)	{	m_strPpDeviceFile = str;	}
	void SetTemplateFile(const CString &str)	{	m_strTemplateFile = str;	}
	void SetReportMapFile(const CString &str) 	{	m_strReportMapFile = str;	}
	void SetTestFolder(const CString &str)		{	m_strTestFolder = str;		}
	void SetTestName(const CString &str)		{	m_strTestName = str;		}
	void SetTestID(const CString &str)			{	m_strTestID = str;			}

public:
	static void s_Save();
	static CString s_GetLastTaskFile();
	static CString s_GetLastTestFile();
	static CString s_GetLastTestState();
	static void s_SetLastTaskFile(const CString &strTaskFile);
	static void s_SetLastTestFile(const CString &strTestFile);
	static void s_SetLastTestState(const CString &strTestState);
	static void s_SetLastTestState(long nCurrTestItemIndex);
	static CString s_GetGuideBookBinaryFileName();
	static CString s_GetNewGuideBookBinaryFileName();

	static CString s_GetPpEngineProgID()	{	return g_pWorkSpace->m_strPpEngineProgID;		}
	static CString s_GetIecfgFile()			{	return g_pWorkSpace->m_strIecfgFile;	}
	static CString s_GetPpTemplateFile()	{	return g_pWorkSpace->m_strPpTemplateFile;	}
	static CString s_GetPpDeviceFile()		{	return g_pWorkSpace->m_strPpDeviceFile;		}
	static CString s_GetTemplateFile()		{	return g_pWorkSpace->m_strTemplateFile;		}
	static CString s_GetReportMapFile() 	{	return g_pWorkSpace->m_strReportMapFile;	}
	static CString s_GetTestFolder() 		{	return g_pWorkSpace->m_strTestFolder;		}
	static CString s_GetTestName()			{	return g_pWorkSpace->m_strTestName;			}
	static CString s_GetTestID()			{	return g_pWorkSpace->m_strTestID;			}
	static DWORD s_GetTkIDIndex()			{	return g_pWorkSpace->m_dwTkID_Index;		}
	static void s_SetCurrTestItemIndex(long nCurrTestItemIndex)			{	g_pWorkSpace->m_nCurrTestItemIndex = nCurrTestItemIndex;			}

	static void s_SetPpEngineProgID(const CString &str)	{	g_pWorkSpace->m_strPpEngineProgID = str;	}
	static void s_SetIecfgFile(const CString &str)	{	g_pWorkSpace->m_strIecfgFile = str;	}
	static void s_SetPpTemplateFile(const CString &str)	{	g_pWorkSpace->m_strPpTemplateFile = str;	}
	static void s_SetPpDeviceFile(const CString &str)	{	g_pWorkSpace->m_strPpDeviceFile = str;	}
	static void s_SetTemplateFile(const CString &str)	{	g_pWorkSpace->m_strTemplateFile = str;	}
	static void s_SetReportMapFile(const CString &str) 	{	g_pWorkSpace->m_strReportMapFile = str;	}
	static void s_SetTestFolder(const CString &str)		{	g_pWorkSpace->m_strTestFolder = str;		}
	static void s_SetTestName(const CString &str)		{	g_pWorkSpace->m_strTestName = str;		}
	static void s_SetTestID(const CString &str)			{	g_pWorkSpace->m_strTestID = str;			}
	static void s_SetTkIDIndex(DWORD dwTkIdIndex)		{	g_pWorkSpace->m_dwTkID_Index = dwTkIdIndex;	}
#ifndef _PSX_QT_LINUX_
    static CPpDeviceRefs* GetPpDeviceRefs()				{	return &g_pWorkSpace->m_oPpDeviceRefs;	}
	static void FreePpDeviceRefs()						{	g_pWorkSpace->m_oPpDeviceRefs.DeleteAll();	}

	static CPpSttCommConfig* GetSttCommConfig(BOOL bCreateNew);
	static CPpSttCommConfigs* GetSttCommConfigs(BOOL bCreateNew);
	static void SetSttCommConfig(CPpSttCommConfig *p);
	static void SetSttCommConfigs(CPpSttCommConfigs *p);

private:
	CPpSttCommConfig* In_GetSttCommConfig(BOOL bCreateNew);
	CPpSttCommConfigs* In_GetSttCommConfigs(BOOL bCreateNew);
	void In_SetSttCommConfig(CPpSttCommConfig *p);
	void In_SetSttCommConfigs(CPpSttCommConfigs *p);
#endif
};


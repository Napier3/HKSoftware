//SttAssistWndInterface.h
#ifndef _SttAppWndAssistInterface_H__
#define _SttAppWndAssistInterface_H__

#include "../../../Module/DataMngr/DataGroup.h"

//2023.9.14 采用原有的助手方式控制块选择,或者使用新的刷新的方式
//#define  STT_MUTest_CBSelect_USE_Assist

//方法名前面增加ast_前缀，是为了避免和已经有的对象类方法重名
class CSttWndAssistInterface
{
public:
	CSttWndAssistInterface()	{};
	virtual ~CSttWndAssistInterface()	{};

//属性
public:
	void *m_pWndRef;    //MFC Windows，窗口指针    QT：Widget指针
	CString m_strWndID; 

public:
	//显示/隐藏一个子窗口
	virtual void ast_Show(const CString &strWndIdPath, bool bShow);
	
	//窗口样式
	virtual void ast_SetStyle(const CString &strWndIDPath, const CString &strStyle);
	virtual CString ast_GetStyle(const CString &strWndIDPath);
	
	//获取窗口位置 找到窗口返回true，否则返回false
	virtual bool ast_GetWndPos(const CString &strWndIdPath, CRect &rcWndPos);

	//查找窗口，保留用 找到返回窗口,      否则返回NULL
	//具体对象必须重载此函数，因为如果直接返回窗口指针，然后强制转换为CSttWndAssistInterface，会出错
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//功能执行接口
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas) = 0;
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID) = 0;
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile) = 0;

};


class CSttAppAssistInterface
{
public:
	CSttAppAssistInterface()	{};
	virtual ~CSttAppAssistInterface()	{};

public:
	//功能执行接口
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas) = 0;
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID) = 0;
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile) = 0;

};


#endif//_SttAssistWndInterface_H__

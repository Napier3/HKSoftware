#pragma once

#include "../Engine/PpScript.h"

#include "DeviceModel/DevcieModel.h"
//#include "DeviceModel/DeviceModelDefine.h"
#include "CmmChannel/DeviceCmmChannel.h"
#include "PpTemplate.h"

#ifndef OS_QT_LINUX
#include "../PpDeviceModelEditInterface/PpDeviceModelEditInterface.h"
#endif

// CPpDevBaseApp
#define LUA_RETURN_STRING_LEN 256

//设备绑定的数据列表互斥区,例如SOE节点的访问
extern CAutoCriticSection g_oDeviceBindListCriticSection;
extern HWND g_hDeviceBindListMsgWnd;
#define WM_DEVICEBINDLIST_SHOW (WM_USER + 1322)

inline void Pp_PostDeviceBindListMsg(WPARAM wPara, LPARAM lPara)
{
	::PostMessage(g_hDeviceBindListMsgWnd, WM_DEVICEBINDLIST_SHOW, wPara, lPara);
}


class CPpDevBaseApp : public CWinAppEx
{
public:
	CPpDevBaseApp();
	virtual ~CPpDevBaseApp();

public:
	//初始化
	virtual long InitPpBaseApp();
	virtual long ExitPpBaseApp();
	virtual void ScriptSetPkgLen(long nLen){}

	//////////////////////////////////////////////////////////////////////////
	//LUA脚本部分
protected:
	CPpScript *m_pPpScript;
	BOOL InitLua();
	void CloseLua();
	//lua_State *m_pLua;
#ifdef _LUA_IN_DEVBASEAPP_
	void *m_pLua;
	CAutoCriticSection m_oScriptCriticSection;

	void BindFuncToLua();
#endif

	//lua_State *m_pExprLua;
	void *m_pExprLua;
	char m_pScriptBuffer[65536];

public:
	// 用于绑定函数返回的字符串
	char m_chReturn[LUA_RETURN_STRING_LEN];

public:
	//脚本执行
	long RunScript(CPpScript *pScript, const CString &strVariables=L"", CBbVariables *pVariables=NULL);
	long CompileScript(CPpScript *pScript, const CString &strVariables=L"");

	CPpScript* GetPpScript();//{return m_pPpScript;}
	double CalExpression(const CString &strValue,const CString& strExpr, const CString &strNomVariables);
	double CalExpression(const CString &strValue,const CString& strExpr);
	virtual void GetNomVarScript(CString &strNomVarScript);

	//数据改变消息
	void OnPpDeviceDataChanged(CDvmData *pDvNodeData, long wPara, long lPara);
	void OnPpDeviceDataChanged(CDvmDataset *pDvNode, long wPara, long lPara);

private:
	void GetLuaReturn();
	void GetLuaGolbalVariables(CBbVariables *pVariables);

	void LogScriptPath(CPpScript *pScript);
};

extern CPpNode *g_pPpEndNode;
extern BOOL g_bDebugPpEngine;   //调试Engine，此种状态不管通讯处理是否成功，只关注数据处理的过程

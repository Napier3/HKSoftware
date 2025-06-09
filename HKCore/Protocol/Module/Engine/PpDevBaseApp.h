#pragma once

#include "../Engine/PpScript.h"

#include "DeviceModel/DevcieModel.h"
//#include "DeviceModel/DeviceModelDefine.h"
#include "CmmChannel/DeviceCmmChannel.h"
#include "PpTemplate.h"

#ifndef _PSX_IDE_QT_
#include "../PpDeviceModelEditInterface/PpDeviceModelEditInterface.h"
#endif

// CPpDevBaseApp
#define LUA_RETURN_STRING_LEN 256

//�豸�󶨵������б�����,����SOE�ڵ�ķ���
extern CAutoCriticSection g_oDeviceBindListCriticSection;
extern HWND g_hDeviceBindListMsgWnd;
#define WM_DEVICEBINDLIST_SHOW (WM_USER + 1322)

inline void Pp_PostDeviceBindListMsg(WPARAM wPara, LPARAM lPara)
{
    if(g_hDeviceBindListMsgWnd == NULL)
        return;

#ifndef _PSX_QT_LINUX_
    ::PostMessage(g_hDeviceBindListMsgWnd, WM_DEVICEBINDLIST_SHOW, wPara, lPara);
#endif
}


class CPpDevBaseApp //: public CWinAppEx
{
public:
	CPpDevBaseApp();
	virtual ~CPpDevBaseApp();

public:
	//��ʼ��
	virtual long InitPpBaseApp();
	virtual long ExitPpBaseApp();
	virtual void ScriptSetPkgLen(long nLen){}

	//////////////////////////////////////////////////////////////////////////
	//LUA�ű�����
protected:
// 	CAutoCriticSection m_oScriptCriticSection;
// 	CPpScript *m_pPpScript;
// 	BOOL InitLua();
// 	void CloseLua();
// 	//lua_State *m_pLua;
// #ifdef _LUA_IN_DEVBASEAPP_
// 	void *m_pLua;
// 
// 	void BindFuncToLua();
// #endif

	//lua_State *m_pExprLua;
	//void *m_pExprLua;
	//char m_pScriptBuffer[65536];

	//CPpScript *m_pPpScript;
public:
	// ���ڰ󶨺������ص��ַ���
	//char m_chReturn[LUA_RETURN_STRING_LEN];

public:
	//�ű�ִ��
// 	long RunScript(CPpScript *pScript, const CString &strVariables=L"", CBbVariables *pVariables=NULL);
// 	long CompileScript(CPpScript *pScript, const CString &strVariables=L"");

	CPpScript* GetPpScript();//{return m_pPpScript;}
	double CalExpression(const CString &strValue,const CString& strExpr, const CString &strNomVariables);
	void CalExpression(CString &strValue,const CString& strExpr, CDvmDataset *pDataset);
	virtual void GetNomVarScript(CString &strNomVarScript);

	//���ݸı���Ϣ
	void OnPpDeviceDataChanged(CDvmData *pDvNodeData, long wPara, long lPara);
	void OnPpDeviceDataChanged(CDvmDataset *pDvNode, long wPara, long lPara);

private:
	//void GetLuaReturn();
	void GetLuaGolbalVariables(CBbVariables *pVariables);

	void LogScriptPath(CPpScript *pScript);
};

extern CPpNode *g_pPpEndNode;
extern CPpDevBaseApp *g_thePpDevBaseApp;


// ../Module/Engine/PpDevBaseApp.cpp : 实现文件
//

#include "stdafx.h"
#include "PpDevBaseApp.h"
#include "PpScriptGlobal.h"
#include "PpEngineDataMngrCntr.h"

// #ifndef _PP_DEV_MODE_
#include "DeviceFile/DeviceTypePathXmlKeys.h"
// #endif

// #ifdef _LUA_IN_DEVBASEAPP_

//Lua
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "luabind.hpp"

// #endif

CPpNode *g_pPpEndNode = NULL;
BOOL g_bDebugPpEngine = FALSE;   //调试Engine，此种状态不管通讯处理是否成功，只关注数据处理的过程

HWND g_hDeviceBindListMsgWnd = NULL;

// CPpDevBaseApp

CPpDevBaseApp::CPpDevBaseApp()
{
	m_pScriptBuffer[0] = 0;
#ifdef _LUA_IN_DEVBASEAPP_
	m_pLua = NULL;
	m_pExprLua = NULL;
#endif
}

CPpDevBaseApp::~CPpDevBaseApp()
{

}


//初始化
long CPpDevBaseApp::InitPpBaseApp()
{
#ifdef _LUA_IN_DEVBASEAPP_
	InitLua();
#endif

	CDeviceModelXmlKeys::Create();
	CProtocolXmlRWKeys::Create();

// #ifndef _PP_DEV_MODE_
	CDeviceTypePathXmlKeys::Create();
// #endif
	
	g_pPpEndNode = new CPpNode(PPNODE_TYPE_PRODUCE);
	g_pPpEndNode->m_strID = CProtocolXmlRWKeys::g_pXmlRWKeys->m_strProcedureEndNodeID;
	g_pPpEndNode->m_strName = g_pPpEndNode->m_strID;

	if (!LoadPpDeviceEditLib())
	{
		AfxMessageBox(_T("点表编辑库PpDeviceModelEdit.dll不存在!"),MB_OK | MB_ICONEXCLAMATION);
	}

	return 0;
}

long CPpDevBaseApp::ExitPpBaseApp()
{
	CDeviceModelXmlKeys::Release();
	CProtocolXmlRWKeys::Release();

// #ifndef _PP_DEV_MODE_
	CDeviceTypePathXmlKeys::Release();
// #endif
	
	if (g_pPpEndNode != NULL)
	{
		delete g_pPpEndNode;
		g_pPpEndNode = NULL;
	}

	ReleasePpDeviceEditLib();

// #ifdef _PP_DEV_MODE_
	CloseLua();
// #endif

	return 0;
}

lua_State* _PpDevBaseApp_Get_Lua(void *p)
{
	return (lua_State*)p;
}

//脚本执行，函数返回，结束互斥处理
long CPpDevBaseApp::RunScript(CPpScript *pScript, const CString &strVariables, CBbVariables *pVariables)
{
#ifdef _LUA_IN_DEVBASEAPP_

	lua_State *pLua = _PpDevBaseApp_Get_Lua(m_pLua);

	// 首先做互斥处理
	CAutoSimpleLock oLock(&m_oScriptCriticSection);

	// 执行脚本
	m_pPpScript = pScript;

	if (pScript == NULL || pLua == NULL)
	{
		return 0;
	}

	if (pScript->m_strScript.GetLength() == 0)
	{
		return 0;
	}

	
	try
	{
		CString strTemp = strVariables+L"      \n";
		strTemp +=pScript->m_strScript;
		strTemp += L"        ";
		CString_to_char(strTemp, m_pScriptBuffer);
		int nErr = luaL_loadstring(pLua, m_pScriptBuffer);

		if (nErr)
		{
			pScript->m_strSyntax = lua_tostring(pLua, -1);
			lua_pop(pLua, 1);

			PPS_LogScriptPath(pScript);

			CLogPrint::LogString(LOGLEVEL_ERROR, pScript->m_strSyntax);
		}
		else
		{
			nErr = lua_pcall(pLua, 0, LUA_MULTRET, 0);

			if (nErr)
			{
				pScript->m_strSyntax = lua_tostring(pLua, -1);
				lua_pop(pLua, -1);

				PPS_LogScriptPath(pScript);
				CLogPrint::LogString(LOGLEVEL_ERROR, pScript->m_strSyntax);
			}
			else
			{
				//获取脚本返回值
				GetLuaReturn();

				//获取变量的值
				GetLuaGolbalVariables(pVariables);
			}
		}
	}
	catch (...)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("LUA Script Error"));
	}

#else
	// 执行脚本
	m_pPpScript = pScript;

	CPpEngineData *pEngineData = (CPpEngineData*)m_pPpScript->GetAncestor(PPCLASSID_PPENGINEDATA);
	pEngineData->RunScript(pScript, strVariables, pVariables);

#endif

	return 0;
}

long CPpDevBaseApp::CompileScript(CPpScript *pScript, const CString &strVariables)
{
	return 0;
}

CPpScript* CPpDevBaseApp::GetPpScript()
{
	return m_pPpScript;
}


double CPpDevBaseApp::CalExpression(const CString& strValue,const CString& strExpr, const CString &strNomVariables)
{
	lua_State *pExprLua = _PpDevBaseApp_Get_Lua(m_pExprLua);
	double dValue = 0.0;

	if (strExpr.GetLength() == 0)
	{
		dValue = _wtof(strValue);
	}
	else
	{
		if(pExprLua == NULL)
		{
			return dValue;
		}

		CString strScript;
		strScript.Format(L"V = %s; V = %s;", strValue, strExpr);

		if(luaL_loadstring(pExprLua,(char*)(_bstr_t)strScript)
			|| lua_pcall(pExprLua,0,0,0))
		{
			return dValue;
		}

		lua_getglobal(pExprLua,"V");

		if( ! lua_isnumber(pExprLua,-1))
		{
			return dValue;
		}

		dValue = lua_tonumber(pExprLua,-1);
	}

	return dValue;
}

double CPpDevBaseApp::CalExpression(const CString &strValue,const CString& strExpr)
{
	double dValue = 0.0;

	if (strExpr.GetLength() == 0)
	{
		dValue = _wtof(strValue);
	}
	else
	{
		CString strNomVarScript;
		GetNomVarScript(strNomVarScript);
		dValue = CalExpression(strValue, strExpr, strNomVarScript);
	}

	return dValue;
}

void CPpDevBaseApp::GetNomVarScript(CString &strNomVarScript)
{
	strNomVarScript = L"Un=57.735;In=5;";
}

void CPpDevBaseApp::OnPpDeviceDataChanged(CDvmData *pDvNodeData, long wPara, long lPara)
{
	CPpEngineData *pEngineData = (CPpEngineData*)m_pPpScript->GetAncestor(PPCLASSID_PPENGINEDATA);
	ASSERT (pEngineData != NULL);

	if (pEngineData == NULL)
	{
		return;
	}

	CDvmDataset *pNode = (CDvmDataset*)pDvNodeData->GetParent();
	pEngineData->m_oMessageMngr.PostMessageByItemData(pDvNodeData->GetIndex(), wPara, lPara);
	pEngineData->m_oMessageMngr.PostMessageByItemData(pNode->GetIndex(), wPara, lPara);
}

void CPpDevBaseApp::OnPpDeviceDataChanged(CDvmDataset *pDvNode, long wPara, long lPara)
{
	CPpEngineData *pEngineData = (CPpEngineData*)m_pPpScript->GetAncestor(PPCLASSID_PPENGINEDATA);
	ASSERT (pEngineData != NULL);

	if (pEngineData == NULL)
	{
		return;
	}

	pEngineData->m_oMessageMngr.PostMessageByItemData(pDvNode->GetIndex(), wPara, lPara);
}

#ifdef _LUA_IN_DEVBASEAPP_

void CPpDevBaseApp::GetLuaReturn()
{
	lua_State *pLua = _PpDevBaseApp_Get_Lua(m_pLua);
	int top = lua_gettop(pLua);

	 //lua的编号从1开始，不是从0开始
	if (top < 1)
	{//如果没有返回值，则不处理
		m_pPpScript->m_dwReturnType = LUA_TBOOLEAN;
		m_pPpScript->m_dReturn = 1;
		return;
	}

	int iPos = 1;
	int t = lua_type(pLua, iPos);   //lua的编号从1开始，不是从0开始
	m_pPpScript->m_dwReturnType = t;

	switch (t) 
	{
	case LUA_TSTRING:  /* strings */
		m_pPpScript->m_strReturn =lua_tostring(pLua, iPos);
		break;

	case LUA_TBOOLEAN:  /* booleans */
		m_pPpScript->m_dwReturn = lua_toboolean(pLua, iPos);
			break;

	case LUA_TNUMBER:  /* numbers */
		m_pPpScript->m_dReturn = lua_tonumber(pLua,iPos);
		m_pPpScript->m_dwReturn = (DWORD)m_pPpScript->m_dReturn;
		break;
	default:  /* other values */
		break;
	}

	lua_settop(pLua, 0);
}

void CPpDevBaseApp::GetLuaGolbalVariables(CBbVariables *pVariables)
{
	if (pVariables == NULL)
	{
		return;
	}

	lua_State *pLua = _PpDevBaseApp_Get_Lua(m_pLua);
	char pszBuffer[MAX_PATH];
	POS pos = pVariables->GetHeadPosition();
	CBbVariable *pVariable = NULL;

	//设置LUA堆栈
	while (pos != NULL)
	{
		pVariable = (CBbVariable*)pVariables->GetNext(pos);
		CString_to_char(pVariable->m_strID, pszBuffer);
		lua_getglobal(pLua, pszBuffer);
	}

	//遍历LUA堆栈，获取变量的值
	int top = lua_gettop(pLua);
	int i = 0;

	for (i = 1; i <= top; i++) 
	{ 
		int t = lua_type(pLua, i);
		pVariable = (CBbVariable*)pVariables->GetAtIndex(i-1);

		//变量不存在
		if (pVariable == NULL)
		{
			break;
		}

		switch (t) 
		{
		case LUA_TSTRING:  /* strings */
			pVariable->m_strValue = CString(lua_tostring(pLua, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			break;

		case LUA_TNUMBER:  /* numbers */
			pVariable->m_strValue.Format(TEXT("%g"), lua_tonumber(pLua, i));
			break;

		default:  /* other values */
			pVariable->m_strValue = L"";
			break;

		}

		//CLogPrint::LogFormatString(NULL, LOGLEVEL_ERROR, _T("%s=%s"), pVariable->m_strID, pVariable->m_strValue);
	}

	//清空堆栈
	lua_settop(pLua, 0);
}

#endif

BOOL CPpDevBaseApp::InitLua()
{
#ifdef _LUA_IN_DEVBASEAPP_
	lua_State *pLua = _PpDevBaseApp_Get_Lua(m_pLua);

	if( pLua == NULL)  // 确保只会初始化一次 
	{ 
		pLua = luaL_newstate(); // 创建Lua状态 

		if( pLua == NULL) 
		{
			return false; 
		}

		luaL_openlibs( pLua ); // 为该Lua状态打开所有Lua库 
		luabind::open( pLua ); // 为该Lua状态打开luabind库 

		m_pLua = pLua;
		BindFuncToLua();		//绑定全局脚本函数
	} 
#endif


	lua_State *pExprLua = _PpDevBaseApp_Get_Lua(m_pExprLua);

	if(pExprLua == NULL)
	{
		pExprLua = luaL_newstate();

		if(pExprLua == NULL)
		{
			return false;
		}

		m_pExprLua = pExprLua;
		luaL_openlibs(pExprLua);
	}

	return TRUE;
}

void CPpDevBaseApp::CloseLua()
{
#ifdef _LUA_IN_DEVBASEAPP_
	lua_State *pLua = _PpDevBaseApp_Get_Lua(m_pLua);

	if (pLua != NULL)
	{
		lua_settop(pLua, 0);
		lua_close(pLua);
	}

	m_pLua = NULL;
#endif

	lua_State *pExprLua = _PpDevBaseApp_Get_Lua(m_pExprLua);

	if(pExprLua != NULL)
	{
		lua_settop(pExprLua,0);
		lua_close(pExprLua);
		m_pExprLua = NULL;
	}

}

#ifdef _LUA_IN_DEVBASEAPP_

void CPpDevBaseApp::BindFuncToLua()
{
	lua_State *pLua = _PpDevBaseApp_Get_Lua(m_pLua);

	luabind::module( pLua ) 
		[ 
			luabind::def("GetValDataType", &script_GetCurrValueDataType ),
			luabind::def("GetValDataLen", &script_GetCurrValueDataLength ), 
			luabind::def("GetBbValLong", &script_GetBbCurrValue),
			luabind::def("GetBbValLong1", &script_GetBbCurrValue1),
			luabind::def("GetBbValLong2", &script_GetBbCurrValue2),
			luabind::def("SetBbValLong", &script_SetBbCurrValue),
			luabind::def("SetBbValLong1", &script_SetBbCurrValue1),
			luabind::def("SetBbValLong2", &script_SetBbCurrValue2),
			luabind::def("SetBbValStr", &script_SetBbCurrValueString),
			luabind::def("GetBbValStr", &script_GetBbCurrValueString),
			luabind::def("GetBbFdataStr", &script_GetBbFormatDataString),
			luabind::def("SetBbValFloat", &script_SetBbCurrValueFloat),
			luabind::def("GetBbValFloat", &script_GetBbCurrValueFloat),
			luabind::def("SetBbValByte", &script_SetBbCurrValueByte),
			luabind::def("GetBbValByte", &script_GetBbCurrValueByte),
			luabind::def("LAnd", &script_LAnd),
			luabind::def("LOr", &script_LOr),
			luabind::def("LNot", &script_LNot),
			luabind::def("LComp", &script_LComplement),
			luabind::def("LComp2", &script_LComplement2),
			luabind::def("LComp1", &script_LComplement1),
			luabind::def("LRComp", &script_LRComplement),
			luabind::def("LShift", &script_LShift),
			luabind::def("RShift", &script_RShift ),
			luabind::def("MkWord", &script_MkWord ), 

			luabind::def("BcdToHex", &script_BcdToHex ),
			luabind::def("HexToBcd", &script_HexToBcd ), 

			luabind::def("GetYear", &script_GetYear ),
			luabind::def("GetMonth", &script_GetMonth ), 
			luabind::def("GetDay", &script_GetDay ),
			luabind::def("GetHour", &script_GetHour), 
			luabind::def("GetMinute", &script_GetMinute ),
			luabind::def("GetSecond", &script_GetSecond ), 
			luabind::def("GetMSecond", &script_GetMillionSecond ), 

			luabind::def("SetBbEnable", &script_SetByteBlockEnable),
			luabind::def("SetBbLen", &script_SetByteBlockLength),
			luabind::def("GetBbLen", &script_GetByteBlockLength),
			luabind::def("SetTimerLong", &script_SetTimerLong),
			luabind::def("GetValue", &script_GetValue),
			luabind::def("GetValueStr", &script_GetValueString),
			luabind::def("SetValueLong", &script_SetValueLong),
			luabind::def("SetValueDouble", &script_SetValueDouble),
			luabind::def("SetValueStr", &script_SetValueString),
			luabind::def("SetPkgLen", &script_SetPkgLen),
			luabind::def("SetPkgValid", &script_SetPkgValid),
			luabind::def("GetPkgLen", &script_GetPkgLen),
			luabind::def("GetPkgParsePos", &script_GetPkgParsePos),
			luabind::def("GetPkgNum", &script_GetPkgNum),
			luabind::def("SetBindDataL", &script_SetBindDataL),
			luabind::def("GetNextNdDataByAttr", &script_GetNextDeviceNodeDataByAttrValue),
			luabind::def("GetNdDataAttrL", &script_GetDeviceNodeDataAttrValueL),
			luabind::def("GetNdDataAttrD", &script_GetDeviceNodeDataAttrValueD),
			luabind::def("SetNdDatasAttr", &script_SetDeviceNodeDataAttrs),
			luabind::def("SetWBindDataL", &script_SetWBindDataL),
			luabind::def("InsertBindData", &script_InsertBindData),
			luabind::def("InsertBindDataset", &script_InsertBindDataset),
			luabind::def("InsertBindLogicDevice", &script_InsertBindLogicDevice),
			luabind::def("GetBindDataL", &script_GetBindDataL),
			luabind::def("GetWBindDataL", &script_GetWBindDataL),
			luabind::def("SetBindDataD", &script_SetBindDataD),
			luabind::def("SetWBindDataD", &script_SetWBindDataD),
			luabind::def("GetBindDataD", &script_GetBindDataD),
			luabind::def("GetWBindDataD", &script_GetWBindDataD),
			luabind::def("GetBindDataStr", &script_GetBindDataStr),
			luabind::def("GetWBindDataStr", &script_GetWBindDataStr),
			luabind::def("SetBindDataStr", &script_SetBindDataStr),
			luabind::def("SetBindDatasetStr", &script_SetBindDatasetStr),
			luabind::def("SetBindLogicDeviceStr", &script_SetBindLogicDeviceStr),
			luabind::def("GetPkgMaxLen", &script_GetPkgMaxLen),
			luabind::def("AdBindDataList", &script_AdBindDataList),
			luabind::def("GetMEA", &script_GetMEA),
			luabind::def("CalMEA", &script_CalMEA),
			luabind::def("FireDataMsg", &script_FireDataChangeMessage),
			luabind::def("GetCP24Time2a", &script_GetCP24Time2a),
			luabind::def("SetCP24Time2a", &script_SetBbCurrValueCP24Time2a),
			luabind::def("GetCP32Time2a", &script_GetCP32Time2a),
			luabind::def("SetCP32Time2a", &script_SetBbCurrValueCP32Time2a),
			luabind::def("GetCP56Time2a", &script_GetCP56Time2a),
			luabind::def("SetCP56Time2a", &script_SetBbCurrValueCP56Time2a),
			luabind::def("SetCP56Time2aEx", &script_SetBbCurrValueCP56Time2aEx),
			luabind::def("BindItemIndex", &script_BindItemIndex),
			luabind::def("GetBitInLong16", &script_GetBitInLong16),
			luabind::def("SetBitInLong16", &script_SetBitInLong16),
			luabind::def("ClearBitInLong16", &script_ClearBitInLong16),
			luabind::def("GetBitInLong32", &script_GetBitInLong32),
			luabind::def("SetBitInLong32", &script_SetBitInLong32),
			luabind::def("ClearBitInLong32", &script_ClearBitInLong32),
			luabind::def("GetBitInLong8", &script_GetBitInLong8),
			luabind::def("SetBitInLong8", &script_SetBitInLong8),
			luabind::def("ClearBitInLong8", &script_ClearBitInLong8),
			luabind::def("GetBitRangeInLong8", &script_GetBitRangeInLong8),
	
			luabind::def("LogPrint", &script_LogPrint),
			luabind::def("ShowMsg", &script_ShowMsg),
			luabind::def("SfCalFloat", &script_SF_ToThreeFloat),
			luabind::def("SfGetAna24Float", &script_SF_GetANA24Float),
			luabind::def("SfGetBcd24Float", &script_SF_GetBcd24Float),
			luabind::def("SfSetBcd24Float", &script_SF_SetBcd24Float),
			luabind::def("SfSetBcd24FloatEx", &script_SF_SetBcd24FloatEx),
			luabind::def("GetGlobal", &script_GetGlobal),
			luabind::def("SetGlobal", &script_SetGlobal),
		
			luabind::def("GetDeviceAddr", &script_GetDeviceAddr),
			luabind::def("GetDeviceAttrL", &script_GetDeviceAttrL),
			luabind::def("SetDeviceAttrL", &script_SetDeviceAttrL),
			luabind::def("GetDeviceAttrStr", &script_GetDeviceAttrStr),
			luabind::def("SetDeviceAttrStr", &script_SetDeviceAttrStr),
			luabind::def("GetCmmMode", &script_GetCmmMode),
			luabind::def("GetPort", &script_GetPort),
			luabind::def("GetSystemPara", &script_GetSystemPara),
			luabind::def("GetIP", &script_GetIP),
	
			luabind::def("Run", &script_Run),
			luabind::def("Connect", &script_Connect),
			luabind::def("DisConnect", &script_DisConnect),
			luabind::def("GetRemoteIP", &script_GetRemoteIP),
			luabind::def("SetPpRunState", &script_SetPpRunState),
			luabind::def("SetPpValid", &script_SetPpValid),

			luabind::def("GetIEEE754", &script_GetIEEE754),
			luabind::def("SetIEEE754", &script_SetIEEE754),
			luabind::def("GetASCII", &script_GetASCII),
			luabind::def("CrcClear",&script_CrcClear),
			luabind::def("CrcPush",&script_CrcPushback),
			luabind::def("CrcPushBb",&script_CrcPushbackBb),
			luabind::def("CrcCDT",&script_CrcCDT),
			luabind::def("CrcSf2000",&script_CrcSfWord),
			luabind::def("CrcModbus16",&script_CrcModbus16),


			luabind::def("CombineDsPathStr", &script_CombineDsPathStr),
			luabind::def("CombineDsPathL", &script_CombineDsPathL),
			luabind::def("ClearDsPath", &script_ClearDsPath),
			luabind::def("GetDsPath",&script_GetDsPath),
			luabind::def("InsertDsData",&script_InsertDsData),
			luabind::def("InsertDataset", &script_InsertDataset),
			luabind::def("InsertLogicDevice", &script_InsertLogicDevice),
			luabind::def("InsertDevice", &script_InsertDevice),
			luabind::def("SetDsDataL",&script_SetDsDataL),
			luabind::def("SetDsDataD",&script_SetDsDataD),
			luabind::def("SetDsDataStr", &script_SetDsDataStr),
			luabind::def("SetDatasetStr", &script_SetDatasetStr),
			luabind::def("SetLogicDeviceStr", &script_SetLogicDeviceStr),
			luabind::def("GetDsDataL", &script_GetDsDataL),
			luabind::def("CountDsData", &script_CountDsData),
			luabind::def("GetDsDataD", &script_GetDsDataD),
			luabind::def("GetDsDataStr",&script_GetDsDataStr),
			luabind::def("AdDsDataList",&script_AdDsDataList),
			luabind::def("AdDsPkgDetail",&script_AdDsPkgDetail),
			luabind::def("AdValPkgDetail",&script_AdValPkgDetail),
			luabind::def("GetRcvIdle",&script_GetRcvIdle),
			luabind::def("AddSectionData",&script_AddSectionData),
			luabind::def("Fis103SaveRCDFile", &script_Fis103SaveRCDFile),
			luabind::def("Fis103SaveCommonFile", &script_Fis103SaveCommonFile)
		];
}

#endif

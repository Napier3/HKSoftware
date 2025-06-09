#include "StdAfx.h"
#include "SmartTestHostApi.h"

#include "GbScriptFunctions.h"
#include "GbScript_System.h"
#include "GbScript_Engine.h"
#include "GbScript_GuideBook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//GbScript_GuideBook/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//跳转到项目
void xvm_GBS_GotoItem(LPVOID pXvm)  //const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char *pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_GotoItem(pSingleVm, pszItemPath);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GotoItemEx(LPVOID pXvm) //const char* pszItemPath, long nRslt, long nAndOr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	long nRslt = pSingleVm->TS_GetParamAsInt(2);
	long nAndOr = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_GotoItemEx(pSingleVm, pszItemPath, nRslt, nAndOr);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_FireTestNextMsg(LPVOID pXvm)      //只针对试验中的通讯命令，目前只支持提示信息
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_FireTestNextMsg(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_BreakLoop(LPVOID pXvm)//long nLevel
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nLevel = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_BreakLoop(pSingleVm, nLevel);
	pSingleVm->TS_Return(nParas+1);
}

//命令消息
void xvm_GBS_MtExcuteCmd(LPVOID pXvm)//const char *pszCmd, const char *pCmdPara
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszCmd = pSingleVm->TS_GetParamAsString(2);
	const char* pszCmdPara = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_MtExcuteCmd(pSingleVm, pszCmd, pszCmdPara);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_MtRegistPpDataMsg(LPVOID pXvm)//const char *pszDvmDataPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDvmDataPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_MtRegistPpDataMsg(pSingleVm, pszDvmDataPath);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_MtUnRegistPpDataMsg(LPVOID pXvm)//const char *pszDvmDataPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDvmDataPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_MtUnRegistPpDataMsg(pSingleVm, pszDvmDataPath);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_MtRegistPpDataMsgRange(LPVOID pXvm)//const char *pszDvmDataPath, double dMin, double dMax
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDvmDataPath = pSingleVm->TS_GetParamAsString(3);
	double dMin = pSingleVm->TS_GetParamAsFloat(2);
	double dMax = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_MtRegistPpDataMsgRange(pSingleVm, pszDvmDataPath, dMin, dMax);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_BreakItems(LPVOID pXvm)//long nLevel
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nLevel = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_BreakItems(pSingleVm, nLevel);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetUploadRptFile(LPVOID pXvm)//const char *pszFileName
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetUploadRptFile(pSingleVm, pszFileName);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_MtRegistCmdMsg(LPVOID pXvm)//const char *pszCmdID, long nCmdState, long nCmdWParam, long nCmdLParam
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszCmdID = pSingleVm->TS_GetParamAsString(4);
	long nCmdState = pSingleVm->TS_GetParamAsInt(3);
	long nCmdWParam = pSingleVm->TS_GetParamAsInt(2);
	long nCmdLParam = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_MtRegistCmdMsg(pSingleVm, pszCmdID, nCmdState, nCmdWParam, nCmdLParam);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_MtUnRegistCmdMsg(LPVOID pXvm)//const char *pszCmdID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszCmdID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_MtUnRegistCmdMsg(pSingleVm, pszCmdID);
	pSingleVm->TS_Return(nParas+1);
}

//数据集访问
void xvm_GBS_GetDsDataValue(LPVOID pXvm)//const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetDsDataValue(pSingleVm, pszID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_GetDsDataAttr(LPVOID pXvm)//const char* pszID, const char *pszAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	const char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetDsDataAttr(pSingleVm, pszID, pszAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_GetDsDataAttrStr(LPVOID pXvm)//const char* pszID, const char *pszAttrID   shaolei  2024-2-26
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	const char* pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetDsDataAttrStr(pSingleVm, pszID, pszAttrID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_SetDsDataValue(LPVOID pXvm)//const char* pszID, double dVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	double dVal = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetDsDataValue(pSingleVm, pszID, dVal);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetDsDataValueStr(LPVOID pXvm)//const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetDsDataValueStr(pSingleVm, pszID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_SetDsDataValueStr(LPVOID pXvm)//const char* pszID, const char* pszVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	const char* pszVal = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetDsDataValueStr(pSingleVm, pszID, pszVal);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetDsDataValueEx(LPVOID pXvm)//long nDeviceIndex, const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDeviceIndex  = pSingleVm->TS_GetParamAsInt(2);
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetDsDataValueEx(pSingleVm, nDeviceIndex, pszID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_SetDsDataValueEx(LPVOID pXvm)//long nDeviceIndex, const char* pszID, double dVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDeviceIndex = pSingleVm->TS_GetParamAsInt(3);
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	double dVal = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetDsDataValueEx(pSingleVm, nDeviceIndex, pszID, dVal);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetDsDataValueStrEx(LPVOID pXvm)//long nDeviceIndex, const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDeviceIndex  = pSingleVm->TS_GetParamAsInt(2);
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetDsDataValueStrEx(pSingleVm, nDeviceIndex, pszID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_SetDsDataValueStrEx(LPVOID pXvm)//long nDeviceIndex, const char* pszID, const char* pszVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDeviceIndex = pSingleVm->TS_GetParamAsInt(3);
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	const char* pszVal = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetDsDataValueStrEx(pSingleVm, nDeviceIndex, pszID, pszVal);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_CalAinError(LPVOID pXvm)//const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszAinID = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalAinError(pSingleVm, pszAinID, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalAinErrorEx(LPVOID pXvm)//double dRate, const char *pszAinID, double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dRate = pSingleVm->TS_GetParamAsFloat(5);
	const char* pszAinID = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalAinErrorEx(pSingleVm, dRate, pszAinID, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalAinErrorNom(LPVOID pXvm)//double dRate, const char *pszAinID, double dRefVal, double dNom, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dRate = pSingleVm->TS_GetParamAsFloat(6);
	const char* pszAinID = pSingleVm->TS_GetParamAsString(5);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(4);
	double dNom = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalAinErrorNom(pSingleVm, dRate, pszAinID, dRefVal, dNom, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalAinStdError(LPVOID pXvm)//double dRate, const char *pszAinID,double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dRate = pSingleVm->TS_GetParamAsFloat(5);
	const char* pszAinID = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalAinStdError(pSingleVm, dRate, pszAinID, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalAinStdError2(LPVOID pXvm)//const char *pszAinID, const char *,double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszAinID = pSingleVm->TS_GetParamAsString(5);
	const char* pszAinBaseID = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalAinStdError2(pSingleVm, pszAinID, pszAinBaseID, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalAinError2(LPVOID pXvm)//const char *pszAinID, const char *pszAinBaseID, double dRate, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszAinID = pSingleVm->TS_GetParamAsString(5);
	const char* pszAinBaseID = pSingleVm->TS_GetParamAsString(4);
	double dRate = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalAinError2(pSingleVm, pszAinID, pszAinBaseID, dRate, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalVariation(LPVOID pXvm)//double dValue, double dTheoreticalVal, double dBaseValue, double dRate
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dValue = pSingleVm->TS_GetParamAsFloat(4);
	double dTheoreticalVal = pSingleVm->TS_GetParamAsFloat(3);
	double dBaseValue = pSingleVm->TS_GetParamAsFloat(2);
	double dRate = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_CalVariation(pSingleVm, dValue, dTheoreticalVal, dBaseValue, dRate);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_CalVariationErr(LPVOID pXvm)//double dValue, double dTheoreticalVal, double dBaseValue, double dRate, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dValue = pSingleVm->TS_GetParamAsFloat(5);
	double dTheoreticalVal = pSingleVm->TS_GetParamAsFloat(4);
	double dBaseValue = pSingleVm->TS_GetParamAsFloat(3);
	double dRate = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalVariationErr(pSingleVm, dValue, dTheoreticalVal, dBaseValue, dRate, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalVariationErrEx(LPVOID pXvm)//const char *pszAinID, const char *pszTheoreticalID, const char *pszBaseValueID, const char *pszRsltID, const char *pszRelErr, double dRate
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszAinID = pSingleVm->TS_GetParamAsString(6);
	const char *pszTheoreticalID = pSingleVm->TS_GetParamAsString(5);
	const char *pszBaseValueID = pSingleVm->TS_GetParamAsString(4);
	const char *pszRsltID = pSingleVm->TS_GetParamAsString(3);
	const char *pszRelErr = pSingleVm->TS_GetParamAsString(2);
	double dRate = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalVariationErrEx(pSingleVm, pszAinID, pszTheoreticalID, pszBaseValueID, pszRsltID, pszRelErr, dRate);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FlterCalErrorMax(LPVOID pXvm)//const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszValID = pSingleVm->TS_GetParamAsString(6);
	const char *pszAbsErrID = pSingleVm->TS_GetParamAsString(5);
	const char *pszRelErrID = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FlterCalErrorMax(pSingleVm, pszValID, pszAbsErrID, pszRelErrID, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FlterCalErrorMin(LPVOID pXvm)//const char *pszValID, const char* pszAbsErrID, const char *pszRelErrID, double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszValID = pSingleVm->TS_GetParamAsString(6);
	const char *pszAbsErrID = pSingleVm->TS_GetParamAsString(5);
	const char *pszRelErrID = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FlterCalErrorMin(pSingleVm, pszValID, pszAbsErrID, pszRelErrID, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

// 获取定值数据
// pszID：数据的ID
void xvm_GBS_GetSetValue(LPVOID pXvm)//const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetSetValue(pSingleVm, pszID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_SetSetValue(LPVOID pXvm)//const char* pszID, double dVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	double dVal = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetSetValue(pSingleVm, pszID, dVal);
	pSingleVm->TS_Return(nParas+1);
}

// void xvm_GBS_GetSoftswitchValue(LPVOID pXvm)//const char* pszID
// {
// 	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
// 	const char* pszID = pSingleVm->TS_GetParamAsString(1);
// 	long nParas = pSingleVm->TS_GetParamAsInt(0);
// 
// 	double vRet = GBS_GetSoftswitchValue(pSingleVm, pszID);
// 	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
// }

// void xvm_GBS_SetSoftswitchValue(LPVOID pXvm)//const char* pszID, double dVal
// {
// 	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
// 	const char* pszID = pSingleVm->TS_GetParamAsString(2);
// 	double dVal = pSingleVm->TS_GetParamAsFloat(1);
// 	long nParas = pSingleVm->TS_GetParamAsInt(0);
// 
// 	GBS_SetSoftswitchValue(pSingleVm, pszID, dVal);
// 	pSingleVm->TS_Return(nParas+1);
// }

// 获取系统参数数据数据
// pszID：数据的ID
void xvm_GBS_GetSysParaValue(LPVOID pXvm)//const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetSysParaValue(pSingleVm, pszID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_SetSysParaValue(LPVOID pXvm)//const char* pszID, double dValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	double dValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetSysParaValue(pSingleVm, pszID, dValue);
	pSingleVm->TS_Return(nParas+1);
}

// 获取测试参数数据
// pszID：数据的ID
void xvm_GBS_GetTestParaValue(LPVOID pXvm)//const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetTestParaValue(pSingleVm, pszID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_GetTestParaStr(LPVOID pXvm)//const char* pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetTestParaStr(pSingleVm, pszID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

// 设置测试参数数据
// pszID：数据的ID
void xvm_GBS_SetTestParaValue(LPVOID pXvm)//const char* pszID, double dValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	double dValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetTestParaValue(pSingleVm, pszID, dValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetTestParaStr(LPVOID pXvm)//const char* pszID, const char *pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszID = pSingleVm->TS_GetParamAsString(2);
	const char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetTestParaStr(pSingleVm, pszID, pszValue);
	pSingleVm->TS_Return(nParas+1);
}

//设置满足条件的项目的Show属性
//pszItemPath为Item的路径
void xvm_GBS_SetItemShow(LPVOID pXvm)//const char* pszItemPath, long nShow);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	long nShow = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemShow(pSingleVm, pszItemPath, nShow);
	pSingleVm->TS_Return(nParas+1);
}

// 获取满足条件的项目的Show属性
// pszItemPath为Item的路径
void xvm_GBS_GetItemShow(LPVOID pXvm)//const char* pszItemPath);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	int nRet = GBS_GetItemShow(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, nRet);
}

// 设置满足条件的项目的Enable属性
// pszItemPath为Item的路径
void xvm_GBS_SetItemEnable(LPVOID pXvm)//const char* pszItemPath, long nEnable);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	long nEnable = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemEnable(pSingleVm, pszItemPath, nEnable);
	pSingleVm->TS_Return(nParas+1);
}

// 获取满足条件的项目的Enable属性
// pszItemPath为Item的路径
void xvm_GBS_GetItemEnable(LPVOID pXvm)//const char* pszItemPath);
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	int nRet = GBS_GetItemEnable(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, nRet);
}

//Seelct
void xvm_GBS_SetItemSelect(LPVOID pXvm)//const char* pszItemPath, long nSelect
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	long nSelect = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemSelect(pSingleVm, pszItemPath, nSelect);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetItemSelect(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	int nRet = GBS_GetItemSelect(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, nRet);
}

// 设置满足条件的项目的Name属性
// pszItemPath为Item的路径
void xvm_GBS_SetItemName(LPVOID pXvm)//const char* pszItemPath, const char* pszName
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	const char* pszName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemName(pSingleVm, pszItemPath, pszName);
	pSingleVm->TS_Return(nParas+1);
}

// 获取满足条件的项目的Name属性
// pszItemPath为Item的路径
void xvm_GBS_GetItemName(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemName(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

// 设置满足条件的项目的结果判断
// pszItemPath为Item的路径
void xvm_GBS_SetItemResultJudge(LPVOID pXvm)//const char* pszItemPath, long nResult
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	long nResult = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemResultJudge(pSingleVm, pszItemPath, nResult);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetItemResultJudge(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	int nRet = GBS_GetItemResultJudge(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, nRet);
}

// 设置满足条件的项目的数据的值
// pszItemPath为Item的路径
void xvm_GBS_SetItemParaValue(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, double dValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	double dValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemParaValue(pSingleVm, pszItemPath, pszValID, dValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetItemParaValueStr(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, const char *pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	const char* pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemParaValueStr(pSingleVm, pszItemPath, pszValID, pszValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetItemParaValue(LPVOID pXvm)//const char* pszItemPath, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetItemParaValue(pSingleVm, pszItemPath, pszValID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_GetItemParaString(LPVOID pXvm)//const char* pszItemPath, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemParaString(pSingleVm, pszItemPath, pszValID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetItemTestTime(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemTestTime(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetItemTestBeginTime(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemTestBeginTime(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetItemTestEndTime(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemTestEndTime(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//通讯命令的参数脚本函数  2019-3-19
void xvm_GBS_ClearCommCmdParas(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_ClearCommCmdParas(pSingleVm, pszItemPath);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_AddCommCmdParaValue(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, double dValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	double dValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_AddCommCmdParaValue(pSingleVm, pszItemPath, pszValID, dValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_AddCommCmdParaValue_Long(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, long nValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_AddCommCmdParaValue_Long(pSingleVm, pszItemPath, pszValID, nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_AddCommCmdParaValue_String(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, const char *pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	const char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_AddCommCmdParaValue_String(pSingleVm, pszItemPath, pszValID, pszValue);
	pSingleVm->TS_Return(nParas+1);
}

//////////////////////////////////////////////////////////////////////////
//常规报告数据处理,处理当前项目的报告数据
//////////////////////////////////////////////////////////////////////////
//多装置、数据库模式下，临时记录，通过添加RptDataMap保证数据不被清除
void xvm_GBS_AddRptMapData(LPVOID pXvm)//const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_AddRptMapData(pSingleVm, pszValID);
	pSingleVm->TS_Return(nParas+1);
}

//设置报告数据
void xvm_GBS_SetItemReportValue(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, double dValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	float fValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemReportValue(pSingleVm, pszItemPath, pszValID, fValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetItemReportValueString(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, const char* pszValString
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	const char *pszValString = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetItemReportValueString(pSingleVm, pszItemPath, pszValID, pszValString);
	pSingleVm->TS_Return(nParas+1);
}

//获取报告数据，返回浮点数
void xvm_GBS_GetItemReportValue(LPVOID pXvm)//const char* pszItemPath, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetItemReportValue(pSingleVm, pszItemPath, pszValID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//获取报告数据，返回整数
void xvm_GBS_GetItemReportValueLong(LPVOID pXvm)//const char* pszItemPath, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetItemReportValueLong(pSingleVm, pszItemPath, pszValID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获取报告数据，返回string
void xvm_GBS_GetItemReportValueString(LPVOID pXvm)//const char* pszItemPath, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemReportValueString(pSingleVm, pszItemPath, pszValID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetItemReportValueEx(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetItemReportValueEx(pSingleVm, pszItemPath, pszValID, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_GetItemReportValueLongEx(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetItemReportValueLongEx(pSingleVm, pszItemPath, pszValID, nIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_GetItemReportValueStringEx(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemReportValueStringEx(pSingleVm, pszItemPath, pszValID, nIndex);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetItemReportCount(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetItemReportCount(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_ClearReports(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_ClearReports(pSingleVm, pszItemPath);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_CalRptValMax(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, double dDefVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	double dDefVal = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_CalRptValMax(pSingleVm, pszItemPath, pszValID, dDefVal);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_CalRptValMin(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, double dDefVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	double dDefVal = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_CalRptValMin(pSingleVm, pszItemPath, pszValID, dDefVal);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_CalRptValAvg(LPVOID pXvm)//const char* pszItemPath, const char* pszValID, double dDefVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszValID = pSingleVm->TS_GetParamAsString(2);
	double dDefVal = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_CalRptValAvg(pSingleVm, pszItemPath, pszValID, dDefVal);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//获取满足条件的报告数据的个数，即根据数据ID和数据值
void xvm_GBS_LGetItemReportDataCount(LPVOID pXvm)//const char* pszItemPath, const char *pszDataID, long nDataValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(3);
	const char* pszDataID = pSingleVm->TS_GetParamAsString(2);
	long nDataValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_LGetItemReportDataCount(pSingleVm, pszItemPath, pszDataID, nDataValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//扩展报告数据
//////////////////////////////////////////////////////////////////////////
//获取扩展报告数据的CReport->m_pRptDataEx
//nIndex：报告的数据索引
//pszValID：数据的值ID
void xvm_GBS_GetItemReportExValue(LPVOID pXvm)//long nIndex, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetItemReportExValue(pSingleVm, nIndex, pszValID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_GetItemReportExValue_D(LPVOID pXvm)//const char* pszDataID, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszDataID = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_GetItemReportExValue_D(pSingleVm, pszDataID, pszValID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void   xvm_GBS_GetItemReportExValue_L(LPVOID pXvm)//const char* pszDataID, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszDataID = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetItemReportExValue_L(pSingleVm, pszDataID, pszValID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void  xvm_GBS_GetItemReportExValue_S(LPVOID pXvm)//const char* pszDataID, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszDataID = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetItemReportExValue_S(pSingleVm, pszDataID, pszValID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetFileInReportEx(LPVOID pXvm)//const char *pszFilePostfix, long nFileIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	char* pszFilePostfix = pSingleVm->TS_GetParamAsString(2);
	long nFileIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetFileInReportEx(pSingleVm, pszFilePostfix, nFileIndex);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetFileNumInReportEx(LPVOID pXvm)//const char *pszFilePostfix
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszFilePostfix = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetFileNumInReportEx(pSingleVm, pszFilePostfix);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获得报告对象的数据个数
void xvm_GBS_GetItemReportExCount(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetItemReportExCount(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//根据ID获得项目的报告的数据个数
void xvm_GBS_GetItemReportExDataCountByID(LPVOID pXvm)//const char* pszDataAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetItemReportExDataCountByID(pSingleVm, pszDataAttrID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//根据ID以及要获取此ID的第几个数据返回其在报告中对应的Index值；nIndex从0开始 
void xvm_GBS_GetItemReportDataIndexByIDIndex(LPVOID pXvm)//const char* pszDataAttrID, long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetItemReportDataIndexByIDIndex(pSingleVm, pszDataAttrID, nIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalTimeGapStr(LPVOID pXvm)//const char* pszTime1, const char* pszTime2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszTime1 = pSingleVm->TS_GetParamAsString(2);
	const char* pszTime2 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalTimeGapStr(pSingleVm, pszTime1, pszTime2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalTimeGapStr_us(LPVOID pXvm)//const char* pszTime1, const char* pszTime2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszTime1 = pSingleVm->TS_GetParamAsString(2);
	const char* pszTime2 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalTimeGapStr_us(pSingleVm, pszTime1, pszTime2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalItemReportTimeGap(LPVOID pXvm)//long nItem1Index, long nItem2Index, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nItem1Index = pSingleVm->TS_GetParamAsInt(3);
	long  nItem2Index = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalItemReportTimeGap(pSingleVm, nItem1Index, nItem2Index, pszValID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalItemReportTimeGapEx(LPVOID pXvm)//long nItem1Index, long nItem2Index, const char* pszValID1, const char* pszValID2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nItem1Index = pSingleVm->TS_GetParamAsInt(4);
	long nItem2Index = pSingleVm->TS_GetParamAsInt(3);
	const char* pszValID1 = pSingleVm->TS_GetParamAsString(2);
	const char* pszValID2 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalItemReportTimeGapEx(pSingleVm, nItem1Index, nItem2Index, pszValID1, pszValID2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalItemReportTimeGapEx2(LPVOID pXvm)//long nItem1Index, long nItem2Index, long nValIndex1, long nValIndex2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nItem1Index = pSingleVm->TS_GetParamAsInt(4);
	long nItem2Index = pSingleVm->TS_GetParamAsInt(3);
	long nValIndex1 = pSingleVm->TS_GetParamAsInt(2);
	long nValIndex2 = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalItemReportTimeGapEx2(pSingleVm, nItem1Index, nItem2Index, nValIndex1, nValIndex2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//报告过滤
void xvm_GBS_FilterInit(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_FilterInit(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_FilterReportExEqualValueL(LPVOID pXvm)//const char* pszDataAttrID, long nAttrValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(2);
	long nAttrValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterReportExEqualValueL(pSingleVm, pszDataAttrID, nAttrValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterReportExEqualValueStr(LPVOID pXvm)//const char* pszDataAttrID, const char* pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(2);
	const char* pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterReportExEqualValueStr(pSingleVm, pszDataAttrID, pszValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterReportExHasValueStr(LPVOID pXvm)//const char* pszDataAttrID, const char* pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(2);
	const char* pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterReportExHasValueStr(pSingleVm, pszDataAttrID, pszValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterReportExHasNoValueStr(LPVOID pXvm)//const char* pszDataAttrID, const char* pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(2);
	const char* pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterReportExHasNoValueStr(pSingleVm, pszDataAttrID, pszValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterCombineReportEx(LPVOID pXvm)//const char* pszDataAttrID, const char* pszRptDataID, const char* pszSeparator
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(3);
	const char* pszRptDataID = pSingleVm->TS_GetParamAsString(2);
	const char* pszSeparator = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_FilterCombineReportEx(pSingleVm, pszDataAttrID, pszRptDataID, pszSeparator);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_FilterRptExQuery(LPVOID pXvm)//const char* pszQuery
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszQuery = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterRptExQuery(pSingleVm, pszQuery);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetCount(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterRptExGetCount(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetLong(LPVOID pXvm)//long nIndex, const char* pszDataAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterRptExGetLong(pSingleVm, nIndex, pszDataAttrID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetString(LPVOID pXvm)//long nIndex, const char* pszDataAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_FilterRptExGetString(pSingleVm, nIndex, pszDataAttrID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetDouble(LPVOID pXvm)//long nIndex, const char* pszDataAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszDataAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_FilterRptExGetDouble(pSingleVm, nIndex, pszDataAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetValCount(LPVOID pXvm)//long nDataIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_FilterRptExGetValCount(pSingleVm, nDataIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetValLong(LPVOID pXvm)//long nDataIndex, const char* pszValIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValIndex = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterRptExGetValLong(pSingleVm, nDataIndex, pszValIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetValString(LPVOID pXvm)//long nDataIndex, const char* pszValIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValIndex = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_FilterRptExGetValString(pSingleVm, nDataIndex, pszValIndex);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_FilterRptExGetValDouble(LPVOID pXvm)//long nDataIndex, const char* pszValIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValIndex = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_FilterRptExGetValDouble(pSingleVm, nDataIndex, pszValIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_FilterRptExCalValError(LPVOID pXvm)//long nDataIndex, const char* pszValIndex, double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(5);
	const char* pszValIndex = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterRptExCalValError(pSingleVm, nDataIndex, pszValIndex, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_FilterRptExCalValErrorEx(LPVOID pXvm)//const char *pszDataID, const char *pszValID, double dRefVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataID = pSingleVm->TS_GetParamAsString(5);
	const char* pszValID = pSingleVm->TS_GetParamAsString(4);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_FilterRptExCalValErrorEx(pSingleVm, pszDataID, pszValID, dRefVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_FilterRptExQueryUseErr(LPVOID pXvm)//const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataID = pSingleVm->TS_GetParamAsString(5);
	const char* pszAttrID = pSingleVm->TS_GetParamAsString(4);
	long nMaxCount = pSingleVm->TS_GetParamAsInt(3);
	double dStand = pSingleVm->TS_GetParamAsFloat(2);
	long nWriteDs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = Gbs_FilterRptExQueryUseErr(pSingleVm, pszDataID, pszAttrID, nMaxCount, dStand, nWriteDs);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_Gbs_FilterRptExQueryUseErrEx(LPVOID pXvm)//const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataID = pSingleVm->TS_GetParamAsString(7);
	const char* pszAttrID1 = pSingleVm->TS_GetParamAsString(6);
	const char* pszAttrID2 = pSingleVm->TS_GetParamAsString(5);
	const char* pszOptr = pSingleVm->TS_GetParamAsString(4);
	long nMaxCount = pSingleVm->TS_GetParamAsInt(3);
	double dStand = pSingleVm->TS_GetParamAsFloat(2);
	long nWriteDs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = Gbs_FilterRptExQueryUseErrEx(pSingleVm, pszDataID, pszAttrID1, pszAttrID2, pszOptr, nMaxCount, dStand, nWriteDs);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_Gbs_FilterRptExQueryUseAvg(LPVOID pXvm)//const char *pszDataID, const char *pszAttrID, long nMaxCount, double dStand, long nWriteDs
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataID = pSingleVm->TS_GetParamAsString(5);
	const char* pszAttrID = pSingleVm->TS_GetParamAsString(4);
	long nMaxCount = pSingleVm->TS_GetParamAsInt(3);
	double dStand = pSingleVm->TS_GetParamAsFloat(2);
	long nWriteDs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = Gbs_FilterRptExQueryUseAvg(pSingleVm, pszDataID, pszAttrID, nMaxCount, dStand, nWriteDs);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_Gbs_FilterRptExQueryUseAvgEx(LPVOID pXvm)//const char *pszDataID, const char *pszAttrID1, const char *pszAttrID2, const char *pszOptr, long nMaxCount, double dStand, long nWriteDs
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataID = pSingleVm->TS_GetParamAsString(7);
	const char* pszAttrID1 = pSingleVm->TS_GetParamAsString(6);
	const char* pszAttrID2 = pSingleVm->TS_GetParamAsString(5);
	const char* pszOptr = pSingleVm->TS_GetParamAsString(4);
	long nMaxCount = pSingleVm->TS_GetParamAsInt(3);
	double dStand = pSingleVm->TS_GetParamAsFloat(2);
	long nWriteDs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = Gbs_FilterRptExQueryUseAvgEx(pSingleVm, pszDataID, pszAttrID1, pszAttrID2, pszOptr, nMaxCount, dStand, nWriteDs);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_Gbs_FilterRptExQueryClearNotUse(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_FilterRptExQueryClearNotUse(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//########################################################################
//报告检索处理函数，处理检索出来的报告数据
//########################################################################
//扩展报告数据为CDvmDataset对象，数据为CDvmData对象
//CTag对象表示一个数据的值
//普通报告数据为CValues*对象，数据值为CValue对象
//所以，对普通报告数据的处理和扩展报告数据的处理方式不一样

//选择某个项目
void xvm_GBS_SSelectItem(LPVOID pXvm)//const char *pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SSelectItem(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//普通报告处理函数******************************************************

//获得当前选择的项目的报告的个数
void xvm_GBS_SGetItemReportCount(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SGetItemReportCount(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//选择项目的报告对象
void xvm_GBS_SSelectItemReport(LPVOID pXvm)//long nReportIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nReportIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SSelectItemReport(pSingleVm, nReportIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获得项目的指定的报告的数据：浮点数
void xvm_GBS_SGetItemReportValue(LPVOID pXvm)//const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_SGetItemReportValue(pSingleVm, pszValID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//获得项目的指定的报告的数据：整数
void xvm_GBS_SGetItemReportValueLong(LPVOID pXvm)//const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SGetItemReportValueLong(pSingleVm, pszValID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获得项目的指定的报告的数据：字符串
void xvm_GBS_SGetItemReportValueString(LPVOID pXvm)//const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_SGetItemReportValueString(pSingleVm, pszValID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//获得项目的指定的报告的数据个数
void xvm_GBS_SGetItemReportValueCount(LPVOID pXvm) 
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SGetItemReportValueCount(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获取报告的第nDataIndex数据的值
void xvm_GBS_SGetItemReportValue2(LPVOID pXvm)  //long nDataIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_SGetItemReportValue2(pSingleVm, nDataIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_SGetItemReportValueLong2(LPVOID pXvm)//long nDataIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SGetItemReportValueLong2(pSingleVm, nDataIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_SGetItemReportValueString2(LPVOID pXvm)//long nDataIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_SGetItemReportValueString2(pSingleVm, nDataIndex);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//扩展报告处理函数******************************************************

//获得项目的指定的报告的数据个数
void xvm_GBS_SGetItemReportExDataCount(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SGetItemReportExDataCount(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获得项目的指定的报告的数据：浮点数
void xvm_GBS_SGetItemReportExDataValue(LPVOID pXvm)//long nDataIndex, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_SGetItemReportExDataValue(pSingleVm, nDataIndex, pszValID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//获得项目的指定的报告的数据：整数
void xvm_GBS_SGetItemReportExDataValueLong(LPVOID pXvm)//long nDataIndex, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SGetItemReportExDataValueLong(pSingleVm, nDataIndex, pszValID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获得项目的指定的报告的数据：整数
void xvm_GBS_SGetItemReportExDataValueString(LPVOID pXvm)//long nDataIndex, const char* pszValID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nDataIndex = pSingleVm->TS_GetParamAsInt(2);
	const char* pszValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_SGetItemReportExDataValueString(pSingleVm, nDataIndex, pszValID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

// 
// //获得项目的指定的报告的数据：浮点数
// double xvm_GBS_SFindItemReportExDataValue(LPVOID pXvm);//const char* pszValID
// 
// //获得项目的指定的报告的数据：整数
// long xvm_GBS_SFindItemReportExDataValueLong(LPVOID pXvm);//const char* pszValID
// 
// //获得项目的指定的报告的数据：整数
// const char* xvm_GBS_SFindItemReportExDataValueString(LPVOID pXvm);//const char* pszValID

//数据集判断函数功能
//获得项目的指定的报告的数据个数
void xvm_GBS_RptExDsGetCount(LPVOID pXvm)//const char* pszPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RptExDsGetCount(pSingleVm, pszPath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获得项目的指定的报告的数据：浮点数
void xvm_GBS_RptExDsGetValueD(LPVOID pXvm)//const char* pszPath, long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszPath = pSingleVm->TS_GetParamAsString(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_RptExDsGetValueD(pSingleVm, pszPath, nIndex);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//获得项目的指定的报告的数据：整数
void xvm_GBS_RptExDsGetValueL(LPVOID pXvm)//const char* pszPath, long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszPath = pSingleVm->TS_GetParamAsString(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RptExDsGetValueL(pSingleVm, pszPath, nIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//获得项目的指定的报告的数据：整数
void xvm_GBS_RptExDsGetValueStr(LPVOID pXvm)//const char* pszPath, long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszPath = pSingleVm->TS_GetParamAsString(2);
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_RptExDsGetValueStr(pSingleVm, pszPath, nIndex);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//数据验证
void xvm_GBS_RptExDsValidClear(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_RptExDsValidClear(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_RptExDsValidAddElement(LPVOID pXvm)//const char* pszText, long nOption, long nUnbound
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszText = pSingleVm->TS_GetParamAsString(3);
	long nOption = pSingleVm->TS_GetParamAsInt(2);
	long nUnbound = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_RptExDsValidAddElement(pSingleVm, pszText, nOption, nUnbound);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_RptExDsValidAddElementChoice(LPVOID pXvm)//const char* pszText, long nOption, long nUnbound
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszText = pSingleVm->TS_GetParamAsString(3);
	long nOption = pSingleVm->TS_GetParamAsInt(2);
	long nUnbound = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_RptExDsValidAddElementChoice(pSingleVm, pszText, nOption, nUnbound);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_RptExDsValid(LPVOID pXvm)//long nValidateHead
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValidateHead = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RptExDsValid(pSingleVm, nValidateHead);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RecordCmd(LPVOID pXvm)//const char *pszCmdID, const char *pszCmdPara
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszCmdID = pSingleVm->TS_GetParamAsString(2);
	const char *pszCmdPara = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RecordCmd(pSingleVm, pszCmdID, pszCmdPara);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_AdjustWord(LPVOID pXvm)//long nPopDlg
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nPopDlg = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_AdjustWord(pSingleVm, nPopDlg);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalSoeTime(LPVOID pXvm)//const char *pszRptID, const char *pszSoeID1, const char *pszSoeID2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszRptID = pSingleVm->TS_GetParamAsString(3);
	const char *pszSoeID1 = pSingleVm->TS_GetParamAsString(2);
	const char *pszSoeID2 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_CalSoeTime(pSingleVm, pszRptID, pszSoeID1, pszSoeID2);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_CalSoeTimeEx(LPVOID pXvm)//const char *pszRptID, const char *pszSoeID1, const char *pszVal1, const char *pszSoeID2, const char *pszVal2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszRptID = pSingleVm->TS_GetParamAsString(5);
	const char *pszSoeID1 = pSingleVm->TS_GetParamAsString(4);
	const char *pszVal1 = pSingleVm->TS_GetParamAsString(3);
	const char *pszSoeID2 = pSingleVm->TS_GetParamAsString(2);
	const char *pszVal2 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_CalSoeTimeEx(pSingleVm, pszRptID, pszSoeID1, pszVal1, pszSoeID2, pszVal2);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetSoeTripDesc(LPVOID pXvm)//const char *pszRptID, const char *pszSoeID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszRptID = pSingleVm->TS_GetParamAsString(2);
	const char *pszSoeID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetSoeTripDesc(pSingleVm, pszRptID, pszSoeID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_CalSoeError(LPVOID pXvm)//double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dRate = pSingleVm->TS_GetParamAsFloat(8);
	const char *pszDsPathID = pSingleVm->TS_GetParamAsString(7);
	const char* pszRptID = pSingleVm->TS_GetParamAsString(6);
	const char* pszAbsErrID = pSingleVm->TS_GetParamAsString(5);
	const char *pszRelErrID = pSingleVm->TS_GetParamAsString(4);
	double dStandVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalSoeError(pSingleVm, dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalSoeError2(LPVOID pXvm)//double dRate, const char *pszDsPathID, const char *pszRptID, const char *pszAbsErrID, const char *pszRelErrID, double dStandVal, double dErrRefStandVal, double dAbsErr, double dRelErr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dRate = pSingleVm->TS_GetParamAsFloat(9);
	const char *pszDsPathID = pSingleVm->TS_GetParamAsString(8);
	const char* pszRptID = pSingleVm->TS_GetParamAsString(7);
	const char* pszAbsErrID = pSingleVm->TS_GetParamAsString(6);
	const char *pszRelErrID = pSingleVm->TS_GetParamAsString(5);
	double dStandVal = pSingleVm->TS_GetParamAsFloat(4);
	double dErrRefStandVal = pSingleVm->TS_GetParamAsFloat(3);
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRelErr = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalSoeError2(pSingleVm, dRate, pszDsPathID, pszRptID, pszAbsErrID, pszRelErrID, dStandVal, dErrRefStandVal, dAbsErr, dRelErr);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//Record
void xvm_GBS_RcdSetProgID(LPVOID pXvm)//const char* pszRcdProgID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszRcdProgID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdSetProgID(pSingleVm, pszRcdProgID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdExit(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdExit(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdConfig(LPVOID pXvm)//const char* pszPara
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPara = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdConfig(pSingleVm, pszPara);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdSelect(LPVOID pXvm)//const char* pszPara
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPara = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdSelect(pSingleVm, pszPara);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdValidate(LPVOID pXvm)//const char* pszRsltID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszRsltID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdValidate(pSingleVm, pszRsltID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdCmpClear(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdCmpClear(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdCmpInit(LPVOID pXvm)//const char* pszRcdFilePathRoot, long nCreateTestTimesDir
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszRcdFilePathRoot = pSingleVm->TS_GetParamAsString(2);
	long nCreateTestTimesDir = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdCmpInit(pSingleVm, pszRcdFilePathRoot, nCreateTestTimesDir);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdCmp(LPVOID pXvm)//const char* pszStdFile, const char* pszTestFile
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszStdFile = pSingleVm->TS_GetParamAsString(2);
	const char* pszTestFile = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdCmp(pSingleVm, pszStdFile, pszTestFile);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdCopyFile(LPVOID pXvm)//const char* pszSrcFile, const char* pszDestFile, long nCreateTestTimesDir
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszSrcFile = pSingleVm->TS_GetParamAsString(3);
	const char* pszDestFile = pSingleVm->TS_GetParamAsString(2);
	long nCreateTestTimesDir = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdCopyFile(pSingleVm, pszSrcFile, pszDestFile, nCreateTestTimesDir);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdAnalyse(LPVOID pXvm)//const char* pszRcdFile
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszRcdFile = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdAnalyse(pSingleVm, pszRcdFile);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RcdSetPath(LPVOID pXvm)//long nAppendItemPath, const char* pszRcdFilePathRoot, long nAppendTestTimeDir
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nAppendItemPath = pSingleVm->TS_GetParamAsInt(3);
	const char* pszRcdFilePathRoot = pSingleVm->TS_GetParamAsString(2);
	long nAppendTestTimeDir = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RcdSetPath(pSingleVm, nAppendItemPath, pszRcdFilePathRoot, nAppendTestTimeDir);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//重复测试相关
void xvm_GBS_GetRepeatTimes(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetRepeatTimes(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_GetRepeatSuccTimes(LPVOID pXvm)//const char* pszItemPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetRepeatSuccTimes(pSingleVm, pszItemPath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//
void xvm_GBS_SetCmdZoneIndex(LPVOID pXvm)//long nZoneIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nZoneIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetCmdZoneIndex(pSingleVm, nZoneIndex);
	pSingleVm->TS_Return(nParas+1);
}

//修正动作值的起始值和终止值
void xvm_Gbs_ValidBeginEndValRange(LPVOID pXvm)//const char *pBeginValID, const char *pEndValID, const char *pStepID, double dMinRange, double dMinStep, long nMinSteps, long nMaxSteps, long nUseNeg
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pBeginValID = pSingleVm->TS_GetParamAsString(8);
	const char *pEndValID = pSingleVm->TS_GetParamAsString(7);
	const char* pStepID = pSingleVm->TS_GetParamAsString(6);
	double dMinRange = pSingleVm->TS_GetParamAsFloat(5);
	double dMinStep = pSingleVm->TS_GetParamAsFloat(4);
	long nMinSteps = pSingleVm->TS_GetParamAsInt(3);
	long nMaxSteps = pSingleVm->TS_GetParamAsInt(2);
	long nUseNeg = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	Gbs_ValidBeginEndValRange(pSingleVm, pBeginValID, pEndValID, pStepID, dMinRange, dMinStep, nMinSteps, nMaxSteps, nUseNeg);
	pSingleVm->TS_Return(nParas+1);
}

//时间出发函数
void xvm_Gbs_SetTmTriggerSecond(LPVOID pXvm)//long nSecond, long nOptr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nSecond = pSingleVm->TS_GetParamAsInt(2);
	long nOptr = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	Gbs_SetTmTriggerSecond(pSingleVm, nSecond, nOptr);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_Gbs_SetTmTriggerCountMinute(LPVOID pXvm)//long nMinute
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nMinute = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	Gbs_SetTmTriggerCountMinute(pSingleVm, nMinute);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_Gbs_EnterTmTrigger(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	Gbs_EnterTmTrigger(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_Gbs_StartTimerTigger(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	Gbs_StartTimerTigger(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_Gbs_StopTimerTrigger(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	Gbs_StopTimerTrigger(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

//数据修约
void xvm_Gbs_ValueRevised(LPVOID pXvm)//double dValue, long nDots
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dValue = pSingleVm->TS_GetParamAsFloat(2);
	long nDots = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = Gbs_ValueRevised(pSingleVm, dValue, nDots);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//日志部分
void xvm_Gbs_log_query_clear(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_clear(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_time(LPVOID pXvm)//const char *pszBeginTine, const char *pszEndTime
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszBeginTine = pSingleVm->TS_GetParamAsString(2);
	const char *pEndValID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_time(pSingleVm, pszBeginTine, pEndValID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_entryid(LPVOID pXvm)//const char *pszEntryID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszEntryID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_entryid(pSingleVm, pszEntryID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_logctrl(LPVOID pXvm)//const char *pszLogCtrl
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszLogCtrl = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_logctrl(pSingleVm, pszLogCtrl);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_dataset(LPVOID pXvm)//const char *pszDataset
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataset = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_dataset(pSingleVm, pszDataset);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_data_clear(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_data_clear(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_data(LPVOID pXvm)//const char *pszDataID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_data(pSingleVm, pszDataID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_data_get_count(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_data_get_count(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query_data_add_to_rpt(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query_data_add_to_rpt(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_query(LPVOID pXvm)//const char *pszScript
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszScript = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_query(pSingleVm, pszScript);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_get_count(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_get_count(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_get_attr(LPVOID pXvm)//long nLogIndex, const char *pszAttr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nLogIndex = pSingleVm->TS_GetParamAsInt(2);
	const char *pszAttr = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = Gbs_log_get_attr(pSingleVm, nLogIndex, pszAttr);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_Gbs_log_get_data_count(LPVOID pXvm)//long nLogIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nLogIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = Gbs_log_get_data_count(pSingleVm, nLogIndex);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_Gbs_log_get_data_attr(LPVOID pXvm)//long nLogIndex, long nDataIndex, const char *pszAttr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nLogIndex = pSingleVm->TS_GetParamAsInt(3);
	long nDataIndex = pSingleVm->TS_GetParamAsInt(2);
	const char *pszAttr = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = Gbs_log_get_data_attr(pSingleVm, nLogIndex, nDataIndex, pszAttr);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_Gbs_log_get_data_attr2(LPVOID pXvm)//long nLogIndex, const char *pszDataID, const char *pszAttr
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nLogIndex = pSingleVm->TS_GetParamAsInt(3);
	const char *pszDataID = pSingleVm->TS_GetParamAsString(2);
	const char *pszAttr = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = Gbs_log_get_data_attr2(pSingleVm, nLogIndex, pszDataID, pszAttr);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//////////////////////////////////////////////////////////////////////////
//字符串处理
void xvm_GBS_InitStrTok(LPVOID pXvm)//const char *pszString, const char *pControl
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszString = pSingleVm->TS_GetParamAsString(2);
	const char *pControl = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_InitStrTok(pSingleVm, pszString, pControl);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_StrTokCount(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_StrTokCount(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_StrTokIndex(LPVOID pXvm)//long nIndex
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nIndex = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_StrTokIndex(pSingleVm, nIndex);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_StrTokNext(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_StrTokNext(pSingleVm);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

//装置的全局参数
void xvm_GBS_SetGlobal_Str(LPVOID pXvm)//const char *pszID, const char *pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszID = pSingleVm->TS_GetParamAsString(2);
	const char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetGlobal_Str(pSingleVm, pszID, pszValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetGlobal_Long(LPVOID pXvm)//const char *pszID, long nValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszID = pSingleVm->TS_GetParamAsString(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetGlobal_Long(pSingleVm, pszID, nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetGlobal_Float(LPVOID pXvm)//const char *pszID, float fValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszID = pSingleVm->TS_GetParamAsString(2);
	float fValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetGlobal_Float(pSingleVm, pszID, fValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetGlobal_Str(LPVOID pXvm)//const char *pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetGlobal_Str(pSingleVm, pszID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetGlobal_Long(LPVOID pXvm)//const char *pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetGlobal_Long(pSingleVm, pszID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_GetGlobal_Float(LPVOID pXvm)//const char *pszID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = GBS_GetGlobal_Float(pSingleVm, pszID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_GetGlobal_Long2(LPVOID pXvm)//const CString &strID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);
	CString strID(pszID);
	//strID.Format(_T("%s"), pszID);

	long vRet = GBS_GetGlobal_Long2(pSingleVm, strID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}


void xvm_GBS_Set_TestError(LPVOID pXvm)//const char *pszTestError
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszTestError = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_Set_TestError(pSingleVm, pszTestError);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_BinRslt(LPVOID pXvm)//const char *pszParaID, const char *pszRsltID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszParaID = pSingleVm->TS_GetParamAsString(2);
	const char *pszRsltID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_BinRslt(pSingleVm, pszParaID, pszRsltID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_BinStateRslt(LPVOID pXvm)//const char *pszParaID, const char *pszRsltID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszParaID = pSingleVm->TS_GetParamAsString(2);
	const char *pszRsltID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_BinStateRslt(pSingleVm, pszParaID, pszRsltID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_BinChngCntRslt(LPVOID pXvm)//const char *pszBinChngData, const char *pszRsltID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszBinChngData = pSingleVm->TS_GetParamAsString(2);
	const char *pszRsltID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_BinChngCntRslt(pSingleVm, pszBinChngData, pszRsltID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

/*long xvm_GBS_BinRsltEx(LPVOID pXvm);*///const char *pszParaDatas, const char *pszRsltDatas

//2019-1-6:增加数据对象是否合格的功能   lijq
void xvm_GBS_Set_AddDataErrorValueToRpt(LPVOID pXvm)//long nValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_Set_AddDataErrorValueToRpt(pSingleVm, nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_AddDataErrorToRpt(LPVOID pXvm)//const char* pszDataID, long nValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDataID = pSingleVm->TS_GetParamAsString(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_AddDataErrorToRpt(pSingleVm, pszDataID, nValue);
	pSingleVm->TS_Return(nParas+1);
}

//2019-6-5  测试记录文件相关
void xvm_GBS_GetTemplateFile(LPVOID pXvm)//long nWithPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nWithPath = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetTemplateFile(pSingleVm, nWithPath);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetGbrptFile(LPVOID pXvm)//long nWithPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nWithPath = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetGbrptFile(pSingleVm, nWithPath);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_SetGbrptFileName(LPVOID pXvm)//const char *pszFileName
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetGbrptFileName(pSingleVm, pszFileName);
	pSingleVm->TS_Return(nParas+1);
}

//2019-7-19     根据装置的编号，调整动作时间
void xvm_GBS_OffsetTestDataByGbrptIndex(LPVOID pXvm)//const char *pszDestDataID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDestDataID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_OffsetTestDataByGbrptIndex(pSingleVm, pszDestDataID);
	pSingleVm->TS_Return(nParas+1);
}

//2020-05-22   磐能版本比对功能  shaolei；
void xvm_GBS_VersionInfoCompare (LPVOID pXvm)//const char* pszPath, const char* pszFilePath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPath = pSingleVm->TS_GetParamAsString(2);
	const char *pszFilePath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_VersionInfoCompare(pSingleVm, pszPath, pszFilePath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_SetComtradeDrawLineMode (LPVOID pXvm)//const char *pszMode
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszMode = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetComtradeDrawLineMode(pSingleVm, pszMode);
	pSingleVm->TS_Return(nParas+1);
}

//GbScript_System/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 在调试监视信息中显示消息
// pszMsg：消息文本/消息ID
void xvm_GBS_ShowMessage(LPVOID pXvm)//const  char* pszMsg
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszMsg = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_ShowMessage(pSingleVm, pszMsg);
	pSingleVm->TS_Return(nParas+1);
}

// 播放音乐文件
// pszFile：音乐文件
// nTimes：播放次数		 0<=表示循环播放 	>0表示实际播放的次数
void xvm_GBS_PlayMusicFile(LPVOID pXvm)//const  char* pszFileName, long nTimes
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszFileName = pSingleVm->TS_GetParamAsString(2);
	long nTimes = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_PlayMusicFile(pSingleVm, pszFileName, nTimes);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetTime(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetTime(pSingleVm);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_IEC(LPVOID pXvm)//double dValue, double dTp, double dK, double dAlpha
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dValue = pSingleVm->TS_GetParamAsFloat(4);
	double dTp = pSingleVm->TS_GetParamAsFloat(3);
	double dK = pSingleVm->TS_GetParamAsFloat(2);
	double dAlpha = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_IEC(pSingleVm, dValue, dTp, dK, dAlpha);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_IEEE(LPVOID pXvm)//double dValue, double dTp, double dA, double dB, double dP, double dQ, double dK1, double dK2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dValue = pSingleVm->TS_GetParamAsFloat(8);
	double dTp = pSingleVm->TS_GetParamAsFloat(7);
	double dA = pSingleVm->TS_GetParamAsFloat(6);
	double dB = pSingleVm->TS_GetParamAsFloat(5);
	double dP = pSingleVm->TS_GetParamAsFloat(4);
	double dQ = pSingleVm->TS_GetParamAsFloat(3);
	double dK1 = pSingleVm->TS_GetParamAsFloat(2);
	double dK2 = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_IEEE(pSingleVm, dValue, dTp, dA, dB, dP, dQ, dK1, dK2);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_IAC(LPVOID pXvm)//double dValue, double dTp, double dA, double dB, double dC, double dD, double dE, double dBeta
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dValue = pSingleVm->TS_GetParamAsFloat(8);
	double dTp = pSingleVm->TS_GetParamAsFloat(7);
	double dA = pSingleVm->TS_GetParamAsFloat(6);
	double dB = pSingleVm->TS_GetParamAsFloat(5);
	double dC = pSingleVm->TS_GetParamAsFloat(4);
	double dD = pSingleVm->TS_GetParamAsFloat(3);
	double dE = pSingleVm->TS_GetParamAsFloat(2);
	double dBeta = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_IAC(pSingleVm, dValue, dTp, dA, dB, dC, dD, dE, dBeta);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_I2T(LPVOID pXvm)//double dValue, double dTp, double dA
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dValue = pSingleVm->TS_GetParamAsFloat(4);
	double dTp = pSingleVm->TS_GetParamAsFloat(3);
	double dA = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_I2T(pSingleVm, dValue, dTp, dA);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_CmpDouble(LPVOID pXvm)//const char *pszVal1, const char *pszVal2, const char *pszPrecision
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszVal1 = pSingleVm->TS_GetParamAsString(3);
	const char *pszVal2 = pSingleVm->TS_GetParamAsString(2);
	const char *pszPrecision = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CmpDouble(pSingleVm, pszVal1, pszVal2, pszPrecision);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CmpDoubleVal(LPVOID pXvm)//double dVal1, double dVal2, double dPrecision
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dVal1 = pSingleVm->TS_GetParamAsFloat(3);
	double dVal2 = pSingleVm->TS_GetParamAsFloat(2);
	double dPrecision = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CmpDoubleVal(pSingleVm, dVal1, dVal2, dPrecision);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalRelError(LPVOID pXvm)//double dAbsErr, double dRefVal
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double dAbsErr = pSingleVm->TS_GetParamAsFloat(2);
	double dRefVal = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_CalRelError(pSingleVm, dAbsErr, dRefVal);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

//外部程序接口部分(DLL调用)
//strPara格式：”Variable1=value1; Variable2=value2;”
//dllReadDatas返回结果的格式相同
void xvm_GBS_dllLoad(LPVOID pXvm)//const char *pszDllFilePath, const char *pszDllID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDllFilePath = pSingleVm->TS_GetParamAsString(2);
	const char *pszDllID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_dllLoad(pSingleVm, pszDllFilePath, pszDllID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_dllCall(LPVOID pXvm)//const char *pszDllID, const char *pszPara
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDllID = pSingleVm->TS_GetParamAsString(2);
	const char *pszPara = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_dllCall(pSingleVm, pszDllID, pszPara);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_dllReadDatas(LPVOID pXvm)//const char *pszDllID, const char *pszPara
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDllID = pSingleVm->TS_GetParamAsString(2);
	const char *pszPara = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_dllReadDatas(pSingleVm, pszDllID, pszPara);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_dllUnload(LPVOID pXvm)//const char *pszDllID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDllID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_dllUnload(pSingleVm, pszDllID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//EXE调用
void xvm_GBS_RunExe(LPVOID pXvm)//const char *pszExeFile, const char *pszPara
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszExeFile = pSingleVm->TS_GetParamAsString(2);
	const char *pszPara = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RunExe(pSingleVm, pszExeFile, pszPara);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_ExitExe(LPVOID pXvm)//const char *pszExeFile
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszExeFile = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_ExitExe(pSingleVm, pszExeFile);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_AddLocalTime(LPVOID pXvm)//long nHour, long nMinute, long nSecond
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nHour = pSingleVm->TS_GetParamAsInt(3);
	long nMinute = pSingleVm->TS_GetParamAsInt(2);
	long nSecond = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_AddLocalTime(pSingleVm, nHour, nMinute, nSecond);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SubLocalTime(LPVOID pXvm)//long nHour, long nMinute, long nSecond
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nHour = pSingleVm->TS_GetParamAsInt(3);
	long nMinute = pSingleVm->TS_GetParamAsInt(2);
	long nSecond = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SubLocalTime(pSingleVm, nHour, nMinute, nSecond);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_RandLong(LPVOID pXvm)//long nMin, long nMax
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nMin = pSingleVm->TS_GetParamAsInt(2);
	long nMax = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_RandLong(pSingleVm, nMin, nMax);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_RandFloat(LPVOID pXvm)//float fMin, float fMax
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	float fMin = pSingleVm->TS_GetParamAsFloat(2);
	float fMax = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	float vRet = GBS_RandFloat(pSingleVm, fMin, fMax);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_RandDouble(LPVOID pXvm)//double fMin, double fMax
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	double fMin = pSingleVm->TS_GetParamAsFloat(2);
	double fMax = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_RandDouble(pSingleVm, fMin, fMax);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_RandSeed(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_RandSeed(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

//文件
void xvm_GBS_GetFileNameFromPath(LPVOID pXvm)//const char *pszPath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_GetFileNameFromPath(pSingleVm, pszPath);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_ParseFilePostfix(LPVOID pXvm)//const char* pszFileName
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_ParseFilePostfix(pSingleVm, pszFileName);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_ParseFileName(LPVOID pXvm)//const char *pszFileName
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_ParseFileName(pSingleVm, pszFileName);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_SubStrToLong(LPVOID pXvm)//const char *pszString, long nBegin, long nLen
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszString = pSingleVm->TS_GetParamAsString(3);
	long nBegin = pSingleVm->TS_GetParamAsInt(2);
	long nLen = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_SubStrToLong(pSingleVm, pszString, nBegin, nLen);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_SubStrToStr(LPVOID pXvm)//const char *pszString, long nBegin, long nLen
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszString = pSingleVm->TS_GetParamAsString(3);
	long nBegin = pSingleVm->TS_GetParamAsInt(2);
	long nLen = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_SubStrToStr(pSingleVm, pszString, nBegin, nLen);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_GetSecondsFromMidnight(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetSecondsFromMidnight(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}


// void xvm_GBS_LogTime_PcTime(PPCTIME pTm);
// void xvm_GBS_LogTime_GpsTime(PGPSTIME pTm);

//GbScript_Engine////////////////////////////////////////////////////////////////////////////////////////////////
// 规约帧录波设置
void xvm_GBS_RecordPackage(LPVOID pXvm)//const  char* pszPkgID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPkgID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_RecordPackage(pSingleVm, pszPkgID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_UnRecordPackage(LPVOID pXvm)//const  char* pszPkgID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPkgID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_UnRecordPackage(pSingleVm, pszPkgID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GetPackagePcTime(LPVOID pXvm)//const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPkgID = pSingleVm->TS_GetParamAsString(3);
	const char *pszPcTimeID = pSingleVm->TS_GetParamAsString(2);
	long nUseHeadOrTail = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_GetPackagePcTime(pSingleVm, pszPkgID, pszPcTimeID, nUseHeadOrTail);
	pSingleVm->TS_Return(nParas+1);
}

// 读取标准源装置GPS时间与PC时间的之间对应关系
void xvm_GBS_GetGpsPcTimeMap(LPVOID pXvm)//const char *pszGpsTime, const char *pszPcTime
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszGpsTime = pSingleVm->TS_GetParamAsString(2);
	const char *pszPcTime = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_GetGpsPcTimeMap(pSingleVm, pszGpsTime, pszPcTime);
	pSingleVm->TS_Return(nParas+1);
}

//读取输出开始时刻的标准源装置GPS时间
void xvm_GBS_GetOutGpsTime(LPVOID pXvm)//const char *pszGpsTimeID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszGpsTimeID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_GetOutGpsTime(pSingleVm, pszGpsTimeID);
	pSingleVm->TS_Return(nParas+1);
}

//计算时间间隔
void xvm_GBS_CalGpsPcTimeGap(LPVOID pXvm)//const char *pszTimeID1, const char *pszTimerID2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszTimeID1 = pSingleVm->TS_GetParamAsString(2);
	const char *pszTimerID2 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalGpsPcTimeGap(pSingleVm, pszTimeID1, pszTimerID2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalTimeGap(LPVOID pXvm)//const char *pszTime1, const char *pszTimer2
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszTime1 = pSingleVm->TS_GetParamAsString(2);
	const char *pszTimer2 = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalTimeGap(pSingleVm, pszTime1, pszTimer2);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CalTimeGapCurr(LPVOID pXvm)//const char *pszTime
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszTime = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CalTimeGapCurr(pSingleVm, pszTime);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//创建一个GPS的时间变量
void xvm_GBS_CreateGpsDateTime(LPVOID pXvm)//const char *pszTimeID, long nYear, long nMonth, long nDay, long nHour, long nMinute, long nS, long nMs, long nUs
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszTimeID = pSingleVm->TS_GetParamAsString(9);
	long nYear = pSingleVm->TS_GetParamAsInt(8);
	long nMonth = pSingleVm->TS_GetParamAsInt(7);
	long nDay = pSingleVm->TS_GetParamAsInt(6);
	long nHour = pSingleVm->TS_GetParamAsInt(5);
	long nMinute = pSingleVm->TS_GetParamAsInt(4);
	long nS = pSingleVm->TS_GetParamAsInt(3);
	long nMs = pSingleVm->TS_GetParamAsInt(2);
	long nUs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CreateGpsDateTime(pSingleVm, pszTimeID, nYear, nMonth, nDay, nHour, nMinute, nS, nMs, nUs);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_CreateGpsTime(LPVOID pXvm)//const char *pszTimeID, long nHour, long nMinute, long nS, long nMs, long nUs
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszTimeID = pSingleVm->TS_GetParamAsString(6);
	long nHour = pSingleVm->TS_GetParamAsInt(5);
	long nMinute = pSingleVm->TS_GetParamAsInt(4);
	long nS = pSingleVm->TS_GetParamAsInt(3);
	long nMs = pSingleVm->TS_GetParamAsInt(2);
	long nUs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_CreateGpsTime(pSingleVm, pszTimeID, nHour, nMinute, nS, nMs, nUs);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//读取标准源的结果数据
void xvm_GBS_ReadMacroTestResult(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_ReadMacroTestResult(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//重新下载电气量测试项目的参数
void xvm_GBS_DownloadMacroTestPara(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_ReadMacroTestResult(pSingleVm);
	pSingleVm->TS_Return(nParas+1);
}

//通讯规约引擎接口函数
void xvm_GBS_PpGetDeviceAttr(LPVOID pXvm)//const char *pszAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_PpGetDeviceAttr(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

void xvm_GBS_PpGetDeviceAttrL(LPVOID pXvm)//const char *pszAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpGetDeviceAttrL(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_PpGetDeviceAttrStr(LPVOID pXvm)//const char *pszAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	const char* vRet = GBS_PpGetDeviceAttrStr(pSingleVm, pszAttrID);
	pSingleVm->TS_ReturnString(nParas+1, vRet);
}

void xvm_GBS_PpSetDeviceAttrL(LPVOID pXvm)//const char *pszAttrID, long nValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszAttrID = pSingleVm->TS_GetParamAsString(2);
	long nValue = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_PpSetDeviceAttrL(pSingleVm, pszAttrID, nValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_PpSetDeviceAttrStr(LPVOID pXvm)//const char *pszAttrID, const char *pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszAttrID = pSingleVm->TS_GetParamAsString(2);
	const char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_PpSetDeviceAttrStr(pSingleVm, pszAttrID, pszValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_PpRptGetDevieNodeDatas(LPVOID pXvm)//const char *pszNodePath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszNodePath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpRptGetDevieNodeDatas(pSingleVm, pszNodePath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_PpRptGetDeviceAttrs(LPVOID pXvm)//void
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpRptGetDeviceAttrs(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_PpGetDevieNodeDataAttr(LPVOID pXvm)//const char *strDataPath, const char *strAttrID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *strDataPath = pSingleVm->TS_GetParamAsString(2);
	const char *strAttrID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	double vRet = GBS_PpGetDevieNodeDataAttr(pSingleVm, strDataPath, strAttrID);
	pSingleVm->TS_ReturnFloat(nParas+1, vRet);
}

// long xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm)//const char *strDataPath, const char *strAttrID, const char *strValue
void xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm)//const char *strDataPath, const char *strAttrID, double dValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *strDataPath = pSingleVm->TS_GetParamAsString(3);
	const char *strAttrID = pSingleVm->TS_GetParamAsString(2);
	double dValue = pSingleVm->TS_GetParamAsFloat(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpSetDevieNodeDataAttr(pSingleVm, strDataPath, strAttrID, dValue);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_PpDeleteAllNodeData(LPVOID pXvm)//const char *pszNodePath
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszNodePath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpDeleteAllNodeData(pSingleVm, pszNodePath);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_PpCreateDevice(LPVOID pXvm)//const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszPpFile = pSingleVm->TS_GetParamAsString(3);
	const char *pszDeviceFile = pSingleVm->TS_GetParamAsString(2);
	const char *pszDeviceID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpCreateDevice(pSingleVm, pszPpFile, pszDeviceFile, pszDeviceID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_PpReleaseDevice(LPVOID pXvm)//const char *pszDeviceID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDeviceID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpReleaseDevice(pSingleVm, pszDeviceID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_PpReleaseAllDevice(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_PpReleaseAllDevice(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

// long xvm_GBS_PpRun(LPVOID pXvm);//const char *pszDeviceID, const char *pszProcedureID, const char *pszPara
void xvm_GBS_GetTestIndex(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_GetTestIndex(pSingleVm);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_IsProtocol(LPVOID pXvm)//const char *pszProtocol
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszProtocol = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_IsProtocol(pSingleVm, pszProtocol);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

//GbScript_EngineTest//////////////////////////////////////////////////////////////////////////////////////////
// CTestControlBase* xvm_GBS_GetTestControl(LPVOID pXvm)
//// 规约帧录波设置
//void xvm_GBS_RecordPackage(LPVOID pXvm);//const  char* pszPkgID
//void xvm_GBS_UnRecordPackage(LPVOID pXvm);//const  char* pszPkgID
//void xvm_GBS_GetPackagePcTime(LPVOID pXvm);//const  char* pszPkgID, const char *pszPcTimeID, long nUseHeadOrTail
// 读取标准源装置GPS时间与PC时间的之间对应关系
//void xvm_GBS_GetGpsPcTimeMap(LPVOID pXvm);//const char *pszGpsTime, const char *pszPcTime
//读取输出开始时刻的标准源装置GPS时间
//void xvm_GBS_GetOutGpsTime(LPVOID pXvm);//const char *pszGpsTimeID
//long xvm_GBS_ReadMacroTestResult(LPVOID pXvm);
//重新下载电气量测试项目的参数
// void xvm_GBS_DownloadMacroTestPara(LPVOID pXvm);
// double xvm_GBS_PpGetDeviceAttr(LPVOID pXvm);//const char *pszAttrID
// long xvm_GBS_PpGetDeviceAttrL(LPVOID pXvm);//const char *pszAttrID
// const char* xvm_GBS_PpGetDeviceAttrStr(LPVOID pXvm);//const char *pszAttrID
// void xvm_GBS_PpSetDeviceAttrL(LPVOID pXvm);//const char *pszAttrID, long nValue
// void xvm_GBS_PpSetDeviceAttrStr(LPVOID pXvm);//const char *pszAttrID, const char *pszValue
// long xvm_GBS_PpRptGetDevieNodeDatas(LPVOID pXvm);//const char *pszNodePath
// long xvm_GBS_PpDeleteAllNodeData(LPVOID pXvm);//const char *pszNodePath
// long xvm_GBS_PpRptGetDeviceAttrs(LPVOID pXvm);//void
// double xvm_GBS_PpGetDevieNodeDataAttr(LPVOID pXvm);//const char *strDataPath, const char *strAttrID
//long xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm)//const char *strDataPath, const char *strAttrID, double dValue
// long xvm_GBS_PpSetDevieNodeDataAttr(LPVOID pXvm);//const char *strDataPath, const char *strAttrID, const char *strValue
// long xvm_GBS_PpCreateDevice(LPVOID pXvm);//const char *pszPpFile, const char *pszDeviceFile, const char *pszDeviceID
// long xvm_GBS_PpReleaseDevice(LPVOID pXvm);//const char *pszDeviceID
// long xvm_GBS_PpReleaseAllDevice(LPVOID pXvm);
// long xvm_GBS_GetTestIndex(LPVOID pXvm);
//long xvm_GBS_IsProtocol(LPVOID pXvm);//const char *pszProtocol

//2021-2-21  lijunqing
void xvm_GBS_RcdAnalysis(LPVOID pXvm)//const char *pszRcdFile, const char *pszAnalysisFile
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszRcdFile = pSingleVm->TS_GetParamAsString(2);
	const char *pszAnalysisFile = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_RcdAnalysis(pSingleVm, pszRcdFile, pszAnalysisFile);
	pSingleVm->TS_Return(nParas+1);
}

//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
// void GBS_CreateSafetyDatasByDvmDataset(CTScriptSingleVM *pXvm, const char *pszDvmDatasetPath, const char *pszAttrs
// 									   , const char *pszDataType, const char *pszDataFormat, const char *pszDefValue);
void xvm_GBS_CreateSafetyDatasByDvmDataset(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDvmDatasetPath = pSingleVm->TS_GetParamAsString(5);
	const char *pszAttrs = pSingleVm->TS_GetParamAsString(4);
	const char *pszDataType = pSingleVm->TS_GetParamAsString(3);
	const char *pszDataFormat = pSingleVm->TS_GetParamAsString(2);
	const char *pszDefValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_CreateSafetyDatasByDvmDataset(pSingleVm, pszDvmDatasetPath, pszAttrs
		, pszDataType, pszDataFormat, pszDefValue);

	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_ImportSets(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_ImportSets(pSingleVm);

	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_Sleep(LPVOID pXvm) //long nMs
{	
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	long nMs = pSingleVm->TS_GetParamAsInt(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_Sleep(pSingleVm, nMs);
	pSingleVm->TS_Return(nParas+1);
}
//2021-11-12  shaolei
void xvm_GBS_SaveExportDatas(LPVOID pXvm)//const char *pszDestFile, const char *pszDataConfig
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszDestFile = pSingleVm->TS_GetParamAsString(2);
	const char *pszDataConfig = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SaveExportDatas(pSingleVm, pszDestFile, pszDataConfig);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SetExportData(LPVOID pXvm)//const char *pszName, const char *pszID, const char *pszDataType, const char *pszValue
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char *pszName = pSingleVm->TS_GetParamAsString(4);
	const char *pszID = pSingleVm->TS_GetParamAsString(3);
	const char *pszDataType = pSingleVm->TS_GetParamAsString(2);
	const char *pszValue = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SetExportData(pSingleVm, pszName, pszID, pszDataType, pszValue);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_IsDsDataExist(LPVOID pXvm)//const char *pszDataID
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataID = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	long vRet = GBS_IsDsDataExist(pSingleVm, pszDataID);
	pSingleVm->TS_ReturnInt(nParas+1, vRet);
}

void xvm_GBS_GenSvMatchItems(LPVOID pXvm)//const char *pszDataNameHas
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszDataNameHas = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_GenSvMatchItems(pSingleVm, pszDataNameHas);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_SaveDvmToLocal(LPVOID pXvm)//const char *pszFileName
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_SaveDvmToLocal(pSingleVm, pszFileName);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_ReadDvmFromLocal(LPVOID pXvm)//const char *pszFileName
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszFileName = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_ReadDvmFromLocal(pSingleVm, pszFileName);
	pSingleVm->TS_Return(nParas+1);
}

//2023-4-17  lijunqing  将IEC接线提示信息添加到安全措施中
void xvm_GBS_IecfgAddCnnInfoToSft(LPVOID pXvm)
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszIecfgID = pSingleVm->TS_GetParamAsString(2);
	const char* pszItemPath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_IecfgAddCnnInfoToSft(pSingleVm, pszItemPath, pszIecfgID);
	pSingleVm->TS_Return(nParas+1);
}

void xvm_GBS_GenTransPlayItems(LPVOID pXvm)//const char *pszDataNameHas
{
	CTScriptSingleVM *pSingleVm = (CTScriptSingleVM *)pXvm;
	const char* pszFilePath = pSingleVm->TS_GetParamAsString(1);
	long nParas = pSingleVm->TS_GetParamAsInt(0);

	GBS_GenTransPlayItems(pSingleVm, pszFilePath);
	pSingleVm->TS_Return(nParas+1);
}
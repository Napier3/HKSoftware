#ifndef _SttTestCntrFrameApi_H_
#define _SttTestCntrFrameApi_H_

//2024-7-10 lijunqing Create

#include "../SttTestResourceMngr/SttTestResourceMngr.h"
//#include "../XLangResource_Native.h"
//#include "../XLangResource_Win.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#include <QApplication>
#include <QMenu>
#include <QButtonGroup>
#include <QDesktopWidget>
#include "../../../Module/API/MathApi.h"
#include "Interface/SttHtmlViewApi.h"
#include "Controls/SttGuideBookTreeCtrl.h"
#include "../../../Module/XDrawBase/XDrawLine.h"
#include <QTableWidget>

class CCharacteristics;

long stt_FrameTestCntrFrameWidth();
long stt_FrameTestCntrFrameHeight();

void stt_Frame_InitTestResource();
void stt_Frame_OnUpdateTestResource(bool b);
void stt_Frame_ClearInfoWidget();
void stt_Frame_EnableManualTriggerButton(bool b);
void stt_Frame_UpdateToolButtons();
bool stt_Frame_IsTestStarted();
void stt_Frame_Ats_UpdateParameter();
void stt_Frame_Ats_UpdateButtonStateByID( const CString &strID,bool bState,bool bShow=true);
void stt_Frame_InitVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent = NULL);
void stt_Frame_UpdateVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList);
void stt_Frame_InitPowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent = NULL);
void stt_Frame_UpdatePowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList);
void stt_Frame_InitStateMonitor(bool bIsEx = false, QWidget* pParent = NULL);
void stt_Frame_InitStateMonitor(int nChannel, int type, bool bStart, QWidget* pPlotExWidget = NULL);
void stt_Frame_StartStateMonitor();
void stt_Frame_StopStateMonitor();
void stt_Frame_StartVectorWidget();
void stt_Frame_StopVectorWidget(bool bUpdate = false);
void stt_Frame_StartPowerWidget();
void stt_Frame_StopPowerWidget(bool bUpdate = false);
void stt_Frame_After_SaveCurr(const CString &strRootItemPath);
void  stt_Frame_UpdatePowerData();
void  stt_Frame_UpdateVectorData();
void stt_Frame_AddTestPoints(double dX, double dY,BOOL bAct);
void stt_Frame_Ats_SetItemPara(const CString &strItemPath, const CString &strMacroID);
void  stt_Frame_SyncBinOutDatas();
void  stt_Frame_UpdateRptHtml();

CSttTestResourceBase*  stt_GetSttTestResource();
tmt_BinaryConfig*  stt_GetBinaryConfig();
CCharacteristics* stt_Frame_Characteristics();
QSttGuideBookTreeCtrl* stt_Frame_GbTreeCtrl();
CExBaseObject* stt_Frame_GetCurrSelTestItem();
CString stt_Frame_CurrSelRootNodePath();
QWidget* stt_Frame_TestCtrlFrame();
CSttMacroTestUI_TestMacroUI* stt_Frame_TestMacroUI();
void stt_Frame_SetTestMacroUI(CSttMacroTestUI_TestMacroUI *pUI);
CDataGroup* stt_Frame_GetTestMacroUI_Paras();
CXDrawLine* stt_Frame_GetCharLibLeftButtonLine();
QTableWidget* stt_Frame_CharTestPointsGrid();
CExBaseList* stt_Frame_GetDvmDevice();
CExBaseObject* stt_Frame_GetTestMacroUiParas(CExBaseObject *pRootNodeItems ,BOOL bSetMacroTest = TRUE);
CExBaseObject* stt_Frame_SafetyMsgCfgs();
CString stt_Frame_TestDeviceType();

extern long g_nLogDebugInfor;
extern QFont *g_pSttGlobalFont;//此处  CFont改为QFont

#endif // _SttTestCntrFrameApi_H_

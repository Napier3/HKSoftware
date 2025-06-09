#include "SttTestCntrFrameApi.h"
#include "SttTestCntrFrameBase.h"
#include "../SttTestCtrl/SttTestAppBase.h"

#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
extern CGbSmartGenWzd *g_theGbSmartGenWzd;

long stt_FrameTestCntrFrameWidth()
{
    return g_theTestCntrFrame->m_pSttFrameConfig->m_nWidth;
}

long stt_FrameTestCntrFrameHeight()
{
    return g_theTestCntrFrame->m_pSttFrameConfig->m_nHeight;
}

void stt_Frame_InitTestResource()
{
    g_theTestCntrFrame->InitTestResource();
}

void stt_Frame_OnUpdateTestResource(bool b)
{
    g_theTestCntrFrame->OnUpdateTestResource(b);
}

void stt_Frame_ClearInfoWidget()
{
    g_theTestCntrFrame->ClearInfoWidget();
}

void stt_Frame_EnableManualTriggerButton(bool b)
{
    g_theTestCntrFrame->EnableManualTriggerButton(b);
}

void stt_Frame_UpdateToolButtons()
{
    g_theTestCntrFrame->UpdateToolButtons();
}

bool stt_Frame_IsTestStarted()
{
    return g_theTestCntrFrame->IsTestStarted();
}

void stt_Frame_Ats_UpdateParameter()
{
    g_theTestCntrFrame->Ats_UpdateParameter();
}

void stt_Frame_Ats_UpdateButtonStateByID( const CString &strID,bool bState,bool bShow)
{
    g_theTestCntrFrame->UpdateButtonStateByID(strID, bState, bShow);
}
void stt_Frame_InitVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent)
{
    g_theTestCntrFrame->InitVectorWidget(pVOL, pCUR, pParent);
}

void stt_Frame_UpdateVectorWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList)
{
    g_theTestCntrFrame->UpdateVectorWidget(pVOL, pCUR, pVolChList, pCurChList);
}

void stt_Frame_InitPowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,QWidget* pParent)
{
    g_theTestCntrFrame->InitPowerWidget(pVOL, pCUR, pParent);
}

void stt_Frame_UpdatePowerWidget(tmt_channel* pVOL,tmt_channel* pCUR,CExBaseList* pVolChList,CExBaseList* pCurChList)
{
    g_theTestCntrFrame->UpdatePowerWidget(pVOL, pCUR, pVolChList, pCurChList);
}

void stt_Frame_InitStateMonitor(bool bIsEx, QWidget* pParent )
{
     g_theTestCntrFrame->InitStateMonitor(bIsEx, pParent);
}

void stt_Frame_InitStateMonitor(int nChannel, int type, bool bStart, QWidget* pPlotExWidget)
{
    g_theTestCntrFrame->InitStateMonitor(nChannel, type, bStart, pPlotExWidget);
}

void stt_Frame_StartStateMonitor()
{
    g_theTestCntrFrame->StartStateMonitor();
}

void stt_Frame_StopStateMonitor()
{
    g_theTestCntrFrame->StopStateMonitor();
}

void stt_Frame_StartVectorWidget()
{
   g_theTestCntrFrame->StartVectorWidget();
}

void stt_Frame_StopVectorWidget(bool bUpdate)
{
     g_theTestCntrFrame->StopVectorWidget(bUpdate);
}

void stt_Frame_StartPowerWidget()
{
	g_theTestCntrFrame->StartPowerWidget();
}

void stt_Frame_StopPowerWidget(bool bUpdate)
{
     g_theTestCntrFrame->StopPowerWidget(bUpdate);
}

void stt_Frame_After_SaveCurr(const CString &strRootItemPath)
{
    g_theTestCntrFrame->m_pSttGbTreeView->After_SaveCurr(strRootItemPath);
}

void  stt_Frame_UpdatePowerData()
{
    g_theTestCntrFrame->UpdatePowerData();
}

void  stt_Frame_UpdateVectorData()
{
    g_theTestCntrFrame->UpdateVectorData();
}

void stt_Frame_AddTestPoints(double dX, double dY,BOOL bAct)
{
    g_theTestCntrFrame->AddTestPoints(dX, dY, bAct);
}

void stt_Frame_Ats_SetItemPara(const CString &strItemPath, const CString &strMacroID)
{
    g_theTestCntrFrame->GetTestCtrlCntrBase()->Ats_SetItemPara(strItemPath, strMacroID);
}

void  stt_Frame_SyncBinOutDatas()
{
    g_theTestCntrFrame->SyncBinOutDatas();
}

void  stt_Frame_UpdateRptHtml()
{
    g_theTestCntrFrame->UpdateRptHtml();
}

void stt_Frame_AddUpdateReport_QT(QString strItemsPath, bool bReportHead)
{
    g_theTestCntrFrame->AddUpdateReport_QT(strItemsPath, bReportHead);
}

void stt_Frame_DeleteReport_QT(QString strItemsPath)
{
    g_theTestCntrFrame->DeleteReport_QT(strItemsPath);
}

void stt_Frame_ClearAllReports_QT()
{
    g_theTestCntrFrame->ClearAllReports_QT();
}

void stt_Frame_Ats_SyncBinOutDatas()
{
    g_theTestCntrFrame->SyncBinOutDatas();
}

void stt_Frame_Ats_UpdateRptHtml()
{
    g_theTestCntrFrame->UpdateRptHtml();
}

CSttTestResourceBase*  stt_GetSttTestResource()
{
    return g_theTestCntrFrame->GetSttTestResource();
}

tmt_BinaryConfig*  stt_GetBinaryConfig()
{
    return g_theTestCntrFrame->GetBinaryConfig();
}

CCharacteristics* stt_Frame_Characteristics()
{
    return g_theTestCntrFrame->m_pCharacteristics;
}

QSttGuideBookTreeCtrl* stt_Frame_GbTreeCtrl()
{
    return g_theTestCntrFrame->m_pSttGbTreeView->m_pTreeCtrl;
}

CExBaseObject* stt_Frame_GetCurrSelTestItem()
{
    return g_theTestCntrFrame->m_pSttGbTreeView->GetCurTestItem();
}

CString stt_Frame_CurrSelRootNodePath()
{
    return g_theTestCntrFrame->m_pSttGbTreeView->m_strCurrSelRootNodePath;
}

QWidget* stt_Frame_TestCtrlFrame()
{
    return g_theTestCntrFrame;
}

CSttMacroTestUI_TestMacroUI* stt_Frame_TestMacroUI()
{
    return g_pTheSttTestApp->m_pTestMacroUI;
}

void stt_Frame_SetTestMacroUI(CSttMacroTestUI_TestMacroUI *pUI)
{
    g_pTheSttTestApp->m_pTestMacroUI = pUI;
}

CDataGroup* stt_Frame_GetTestMacroUI_Paras()
{
    return g_theTestCntrFrame->GetTestMacroUI_Paras();
}

CXDrawLine* stt_Frame_GetCharLibLeftButtonLine()
{
    return g_theTestCntrFrame->GetCharLibLeftButtonLine();
}

QTableWidget* stt_Frame_CharTestPointsGrid()
{
    return g_theTestCntrFrame->GetCharTestPointsGrid();
}

CExBaseList* stt_Frame_GetDvmDevice()
{
    return g_pTheSttTestApp->m_pDvmDevice;
}

CExBaseObject* stt_Frame_GetTestMacroUiParas(CExBaseObject *pRootNodeItems ,BOOL bSetMacroTest)
{
    return g_theTestCntrFrame->GetTestMacroUiParas((CSttItems *)pRootNodeItems, bSetMacroTest);
}

CExBaseObject* stt_Frame_SafetyMsgCfgs()
{
    return &g_theTestCntrFrame->m_oSafetyMsgCfgs;
}

CString stt_Frame_TestDeviceType()
{
    return g_theGbSmartGenWzd->m_strDeviceType;
}


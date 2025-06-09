#include "SttTestCntrFrameWin.h"
#include "../../Module/SttTestCtrl/SttTestCtrlCntrWin.h"
#include "../../Module/LiveUpdate/SttLiveUpdateShell.h"
#include "../../Module/SttSocket/SttCmdOverTimeMngr.h"
#include "../../Module/SttGlobalDef.h"
#include "../../Module/UI/Controls/SttFileSaveAsDlg.h"
#include "../../Module/UI/Interface/SttMacroParaEditViewOriginal.h"
#include "../../Module/UI/Controls/SttCreateNewTestWidget.h"
#include "../../Module/UI/Controls/SttGuideBookTreeWidget_Win.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../Module/API/StringConvertApi.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../AutoTest/Module/AutoTestGlobalDefine.h"
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../Module/UI/SttTestCntrCmdDefine.h"
#include "../../Module/UI/SCL/QSttSelSclIedWidget.h"
#include "../../Module/UI/IEC61850Config/SttIecConfigDialogWin.h"
#include "../../../61850/Module/SCL_Qt/QScdFileRWDlg.h"
#include "../../Module/UI/Module/PopupDialog/SttPopupOpenDialog.h"
#include "../../../61850/Module/SCL_Qt/QSclFileRead.h"
#include "../../../61850/Module/SclToModel/ModelWriteXml.h"
#include "../../../61850/Module/MMS_STACK_CFG/MMS_STACK_CFG.h"
#include "../../../61850/Module/61850ClientConfig/61850ClientConfig.h"
#include "../../../IotProtoServer/Module/SttPxCommCmdDef.h"
#include "../../Module/UI/Module/DCOutput/QAuxDCOutputDlg.h"
#include "../../Module/UI/Controls/TestMacroTool/TestMacroToolDlg.h"
#include "../../Module/SttCmd/GuideBook/SttItemStateObject.h"
#include "../../Module/UI/Controls/SttTestViewsTabWidget.h"
#include "../../Module/Main/SttMainArgvDef.h"
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdAi/GbWzdAiTool.h"

#ifdef use_CSmartCapCtrl
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../Module/RecordTest/UI/SttIecRecordCbWidget.h"
#include "../../Module/RecordTest/UI/MUTest/SttMUTestIecCbSelWidget.h"
#include "../../Module/RecordTest/UI/SttIecRecordDetectWidget.h"
#include "../../Module/RecordTest/UI/SttExportPcapFileDialog.h"
#endif

#include "../../Module/UI/Controls/SttGbSafetyEdit.h"
#include "../../Module/UI/Module/SysParas/QSysParasDlg.h"

//2023/8/29 wjs
#include "../../Module/UI/Module/AinDataMap/QAinDataMapDlg.h"
#include "../../Module/UI/Module/OutPutDebugDlg/QOutPutDebugDlg.h" // 2023-8-22  lcq
#include "../../Module/UI/Controls/ExportWordRpt/SttExportWordReport.h"
#include "../../../AutoTest/Module/TestMacroRptTemplate/RptTemp_Group.h"
#include "../../../AutoTest/Module/TestMacroRptTemplate/RptTemp_Data.h"
#include "../../../Module/xml/PugiXML/pugixml.hpp"
#include "../../../Module/Record/FFT/FFT.h"
#include "../../Module/TestUI/QSttMultiMacroParaEditViewBase.h"
#include "../../Module/UI/Swing/SttMacroParaEditViewSwing.h"
#include <QApplication>
#include <QFileDialog>

#include "../../Module/UI/SttTestCntrFrameApi.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QSttTestCntrFrameWin::QSttTestCntrFrameWin(QWidget *parent) :
    QSttTestCntrFrameBase(parent)
{
	m_pMenuBar = NULL;
	m_pToolBarWin = NULL;
	m_wndWorkspace = NULL;
	m_wndTopTestWnds = NULL;
	m_pVLayout = NULL;
	m_pHBoxLayout = NULL;
	m_wndDockStatusBar = NULL;
	m_pSplitWorkspace = NULL;
	m_tabTestViews = NULL;
	m_tabTestTools = NULL;
	m_pMacroTest_Original = NULL;
	m_pSttCommCmdWzdMainWidget = NULL;
	m_pSttImportDvmFileWidget = NULL;
	m_pCmdWzdDsEditWidget = NULL;
	m_pSelSCLWidget = NULL;
	m_pSclFileRead = NULL;
	m_bIsAutoTest = TRUE;
	m_bIsViewStoped = TRUE;
	CLogPrint::CreateLogFile();
	CLogPrint::SetSaveEveryLogFlag(TRUE);

	m_pAinDataMapCfg = new CDataGroup();
	m_pAinRatios = NULL;

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("AinDataMapCfg.xml");
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pAinDataMapCfg->OpenXmlFile(strFile,CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

	if (m_pSttGbTreeView != NULL)
	{
		connect(this,SIGNAL(sig_OnItemStateChanged(CExBaseObject *)),m_pSttGbTreeView,SLOT(slot_ItemStateChanged(CExBaseObject *)));
	}

	connect(this, SIGNAL(sig_ViewMacroEditWidget(CExBaseObject *)), this, SLOT(slot_ViewMacroEditWidget(CExBaseObject *)), Qt::QueuedConnection);

    //ftt
    m_pSttReportView = NULL;
}

QSttTestCntrFrameWin::~QSttTestCntrFrameWin()
{
	((QSttTestViewsTabWidget*)m_tabTestViews)->m_bHasClosed = true;
	disconnect(m_tabTestViews, SIGNAL(currentChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)));
	disconnect(this,SIGNAL(sig_UpdateCmdButtons_AddMacro()),this,SLOT(slot_UpdateCmdButtons_AddMacro()));

	FreeCommCmdWzdMain();
	FreeImportDvmFileDlg();

	if (m_pCmdWzdDsEditWidget != NULL)
	{
		m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
		delete m_pCmdWzdDsEditWidget;
	}

	if (m_pEngineClientWidget != NULL)
	{
		delete m_pEngineClientWidget;
		m_pEngineClientWidget = NULL;
	}

	if (m_pSelSCLWidget != NULL)
	{
		delete m_pSelSCLWidget;
		m_pSelSCLWidget = NULL;
	}

	if (m_pSclFileRead != NULL)
	{
		delete m_pSclFileRead;
		m_pSclFileRead = NULL;
	}

	if (m_pAinDataMapCfg != NULL)
	{
		delete m_pAinDataMapCfg;
		m_pAinDataMapCfg = NULL;
	}

	if (m_pAinRatios != NULL)
	{
		delete m_pAinRatios;
		m_pAinRatios = NULL;
	}
	//g_pTheSttTestApp->ExitSttTestApp();

	//20240802 huangliang 统一在类QSettingGlobal中执行，删除此处代码
	////20240704 huangliang
	//if(g_pSettingSelectDlg != NULL)
	//{
	//	delete g_pSettingSelectDlg;
	//	g_pSettingSelectDlg = NULL;
	//}
}

void QSttTestCntrFrameWin::InitFrame( const CString &strFrameCfgFile )
{
	//setWindowTitle(tr("PowerTest"));

	CString strName = _P_GetResourcePath();
	strName = strName + "images/SmartTest.png";
	setWindowIcon(QPixmap(strName));

	QSttTestCntrFrameBase::InitFrame(strFrameCfgFile);
	connect(this,SIGNAL(sig_UpdateCmdButtons_AddMacro()),this,SLOT(slot_UpdateCmdButtons_AddMacro()));
	connect(this,SIGNAL(sig_ExpandGuideBookTree()),this,SLOT(slot_ExpandGuideBookTree()));
	connect(this,SIGNAL(sig_Timer_AutoSave()),this,SLOT(slot_Timer_AutoSave_Ex()),Qt::QueuedConnection);
	InitToolButtons_AfterInit();


	//设置样式
	CString strToolButtonStyle = "QToolButton{border:0px;color:rgb(0,0,0);}QToolButton:disabled{color:rgb(128,128,128);}"
		"QToolButton:hover{border:0px;background-color:#d4e8ff;}";
	CString strMenuStyle;
// 	strMenuStyle = "QMenuBar{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,stop:0 #e8f2ff, stop:1 #d4e8ff);}"
// 		"QMenuBar::item{spacing: 3px;padding: 1px 4px;background: transparent;background: transparent;}"
// 		"QMenuBar::item:selected { background: #c0deff;}"
// 		"QMenuBar::item:pressed {background: #99c9ff;}";

	strMenuStyle = "QMenuBar::item:selected { background: #c0deff;}"
		"QMenuBar::item:pressed {background: #99c9ff;}";

	CString strTabWidget = "QTabBar::tab {border:1px solid #C4C4C3; padding:5px;border-top-left-radius:4px;border-top-right-radius:4px;background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);}"
		"QTabBar::tab:selected, QTabBar::tab:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #d4e8ff, stop: 0.4 #e8f2ff,stop: 0.5 #e8f2ff, stop: 1.0 #d4e8ff);}";
// 	CString strTestViewsTabWidget = "QTabBar::tab {border:1px solid #C4C4C3; padding:5px;border-top-left-radius:4px;border-top-right-radius:4px;background:qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);}"
// 		"QTabBar::tab:selected, QTabBar::tab:hover {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #d4e8ff, stop: 0.4 #e8f2ff,stop: 0.5 #e8f2ff, stop: 1.0 #d4e8ff);} QTabBar::tab:disabled {width: 0; color: transparent;}";
	CString strSplitter = "QSplitter::handle{border: 1px solid #F5F5F5;background-color:rgb(211,211,211);}";//solid #c0deff;background-color:rgb(212,232,252)

	m_pMenuBar->setStyleSheet(strMenuStyle);
	m_pToolBarWin->setStyleSheet(strToolButtonStyle);
// 	m_tabTestViews->setStyleSheet(strTabWidget);
// 	m_tabTestTools->setStyleSheet(strTabWidget);
// 	m_tabTestOutput->setStyleSheet(strTabWidget);

 	m_pSplitWorkspace->setStyleSheet(strSplitter);
 	m_pSplitClientVert->setStyleSheet(strSplitter);
}

void QSttTestCntrFrameWin::EnableMenu(const CString& strID, BOOL bEnable)
{
	long nIndex = m_pMenuBar->m_pMenus->FindIndexByID(strID);
	if(nIndex >= 0 && nIndex < m_pMenuBar->m_listMenu.size())
	{
		m_pMenuBar->m_listMenu[nIndex]->setEnabled(bEnable);
	}
}

void QSttTestCntrFrameWin::EnableAction(const CString& strID, BOOL bEnable, BOOL bSelect)
{
	for (int i = 0; i < m_pMenuBar->m_listAct.size(); i++)
	{
		if (m_pMenuBar->m_listAct[i]->m_pCfgData->m_strID == strID)
		{
			m_pMenuBar->m_listAct[i]->setEnabled(bEnable);
			m_pMenuBar->m_listAct[i]->setCheckable(bSelect);
			return;
		}
	}
}

void QSttTestCntrFrameWin::ShowButtonsByID(const CString& strButtonID, BOOL bShow)
{
	CSttFrame_Button *pBtn = m_pSttFrameConfig->FindBtnByID(strButtonID);

	if (pBtn != NULL)
	{
		QSttToolButtonBase *pButton = (QSttToolButtonBase*)pBtn->m_dwItemData;
		if (pButton != NULL)
		{
 			QPoint pt = pButton->pos();
 			QAction* pAct = NULL;
			for (int i = 0; i < m_pToolBarWin->m_listToolBar.size(); i++)
			{
				pAct = m_pToolBarWin->m_listToolBar[i]->actionAt(pt);
				if(pAct && pAct->text() == pButton->text())
				{
					pAct->setVisible(bShow);
					return;
				}
			}
			
		}
	}
}

void QSttTestCntrFrameWin::SelectActionByID(const CString& strID, BOOL bSelect)
{
	QAction* pAction =  NULL;
	for (int i = 0; i < m_pMenuBar->m_listAct.size(); i++)
	{
		if (m_pMenuBar->m_listAct[i]->m_pCfgData->m_strID == strID)
		{
			pAction = m_pMenuBar->m_listAct[i];
			break;
		}
	}

	if(pAction && pAction->isCheckable())
	{
		pAction->setChecked(bSelect);
	}
}

void QSttTestCntrFrameWin::SelectActionByName(const CString& strName, BOOL bSelect)
{
	QAction* pAction =  NULL;
	for (int i = 0; i < m_pMenuBar->m_listAct.size(); i++)
	{
		if (m_pMenuBar->m_listAct[i]->m_pCfgData->m_strName == strName)
		{
			pAction = m_pMenuBar->m_listAct[i];
			break;
		}
	}

	if(pAction && pAction->isCheckable())
	{
		pAction->setChecked(bSelect);
	}
}

void QSttTestCntrFrameWin::InitToolButtons_AfterInit()
{
	//Menu
	EnableMenu("menuSky", FALSE);

	EnableAction(STT_CNTR_CMD_AddMacro, FALSE);
	EnableAction(STT_CNTR_CMD_SaveTemplate, FALSE);
	EnableAction(STT_CNTR_CMD_SaveAsTemplate, FALSE);

	EnableAction(STT_CNTR_CMD_SwitchSet, FALSE);
	EnableAction(STT_CNTR_CMD_HardConfig, FALSE);
	EnableAction(STT_CNTR_CMD_DcSet, TRUE);
	EnableAction(STT_CNTR_CMD_DeviceCom, FALSE);

	EnableAction(STT_CNTR_CMD_TemplateView, FALSE);
	EnableAction(STT_CNTR_CMD_ReportView, FALSE);
	EnableAction(STT_CNTR_CMD_DeviceComView, FALSE);
	EnableAction(STT_CNTR_CMD_VectorDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_SequenceView, FALSE);
	EnableAction(STT_CNTR_CMD_StateDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_PowerDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_CharDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_InfoView, FALSE);
	EnableAction(STT_CNTR_CMD_ImportDvmFile, FALSE);

	EnableAction(STT_CNTR_CMD_SaveTest, FALSE);
	EnableAction(STT_CNTR_CMD_SaveAsRpt, FALSE);
	EnableAction(STT_CNTR_CMD_ExportWordRpt, FALSE);
	EnableAction(STT_CNTR_CMD_ClearReportRslts, FALSE);
	EnableAction(STT_CNTR_CMD_AinDataMapConfig, FALSE);
	EnableAction(STT_CNTR_CMD_LumPowerView, FALSE);
	EnableAction(STT_CNTR_CMD_IecCap, FALSE);
	EnableAction(STT_CNTR_CMD_PpIotEngineClient, FALSE);
	EnableAction(STT_CNTR_CMD_WaveDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_SystemView, FALSE);
	EnableAction(STT_CNTR_CMD_WiringView,FALSE);


	EnableAction(STT_CNTR_CMD_ItemList, TRUE, TRUE);
	SelectActionByID(STT_CNTR_CMD_ItemList, TRUE);

	//ToolBar
	EnableStartStopButton(FALSE);
	EnableManualTriggerButton(FALSE);
	UpdateButtonsStateByID(STT_CNTR_CMD_StopTest, FALSE);
	UpdateButtonsStateByID(STT_CNTR_CMD_AddMacro, FALSE);
	UpdateButtonsStateByID(STT_CNTR_CMD_SaveTemplate, FALSE);
	UpdateButtonsStateByID(STT_CNTR_CMD_SaveAsTemplate, FALSE);
	UpdateButtonsStateByID(STT_CNTR_CMD_TestThis, FALSE);
	if(IsAutoTest())
	{
		ShowButtonsByID(STT_CNTR_CMD_ChRsMaps, FALSE);
		ShowButtonsByID(STT_CNTR_CMD_SystemParas, FALSE);
	}
}

//新建测试后，更新菜单、工具栏的按钮状态
void QSttTestCntrFrameWin::UpdateToolButtons_AfterNew()
{
	//Menu
	EnableAction(STT_CNTR_CMD_SaveTemplate, FALSE);
	EnableAction(STT_CNTR_CMD_SaveAsTemplate, FALSE);

	EnableAction(STT_CNTR_CMD_TemplateView, FALSE);
    EnableAction(STT_CNTR_CMD_ReportView, TRUE); //2024.10.25 BWS
	EnableAction(STT_CNTR_CMD_VectorDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_PowerDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_StateDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_CharDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_InfoView, FALSE);
	EnableAction(STT_CNTR_CMD_ImportDvmFile, TRUE);
	EnableAction(STT_CNTR_CMD_ItemList, TRUE, TRUE);
	SelectActionByID(STT_CNTR_CMD_ItemList, TRUE);
	EnableAction(STT_CNTR_CMD_PpIotEngineClient, FALSE, TRUE);
	SelectActionByID(STT_CNTR_CMD_PpIotEngineClient, TRUE);

	EnableAction(STT_CNTR_CMD_WaveDrawView, FALSE);
	EnableAction(STT_CNTR_CMD_SystemView, FALSE);
	EnableAction(STT_CNTR_CMD_WiringView, FALSE);
	EnableAction(STT_CNTR_CMD_ZTView, FALSE);

	//ToolBar
	UpdateButtonsStateByID(STT_CNTR_CMD_SaveTemplate, TRUE);
	UpdateButtonsStateByID(STT_CNTR_CMD_SaveAsTemplate, TRUE);
}

//选择功能后，更新菜单、工具栏的按钮状态
void QSttTestCntrFrameWin::UpdateToolButtons_AfterAddMacro()
{
	//Menu
	EnableAction(STT_CNTR_CMD_SaveTemplate, TRUE);
	EnableAction(STT_CNTR_CMD_SaveAsTemplate, TRUE);

	EnableAction(STT_CNTR_CMD_TemplateView, TRUE, TRUE);
	EnableAction(STT_CNTR_CMD_ReportView, TRUE, TRUE);
	EnableAction(STT_CNTR_CMD_VectorDrawView, TRUE, TRUE);
	EnableAction(STT_CNTR_CMD_PowerDrawView, TRUE, TRUE);
	EnableAction(STT_CNTR_CMD_StateDrawView, TRUE, TRUE);
	//EnableAction(STT_CNTR_CMD_CharDrawView, TRUE, TRUE);
	EnableAction(STT_CNTR_CMD_InfoView, TRUE, TRUE);

	EnableAction(STT_CNTR_CMD_SaveTest, TRUE);
	EnableAction(STT_CNTR_CMD_SaveAsRpt, TRUE);
	EnableAction(STT_CNTR_CMD_ExportWordRpt, TRUE);
	EnableAction(STT_CNTR_CMD_ClearReportRslts, TRUE);
	EnableAction(STT_CNTR_CMD_AinDataMapConfig, TRUE);
	EnableAction(STT_CNTR_CMD_LumPowerView, TRUE);
	EnableAction(STT_CNTR_CMD_IecCap, TRUE, TRUE);

	if (stt_Frame_TestMacroUI() == NULL)
	{
		return;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = stt_Frame_TestMacroUI();
	CString strMacroID = pTestMacroUI->m_strUI_ID;

	//波形图
	if (HasWaveWidget(strMacroID))
	{
		EnableAction(STT_CNTR_CMD_WaveDrawView, TRUE, TRUE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_WaveDrawView, FALSE);
	}

	//系统图
	if (HasSystemDiagramWidget(strMacroID))
	{
		EnableAction(STT_CNTR_CMD_SystemView, TRUE, TRUE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_SystemView, FALSE);
	}

	//接线图
	if (HasWiringDiagramWidget(strMacroID))
	{
		EnableAction(STT_CNTR_CMD_WiringView, TRUE, TRUE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_WiringView, FALSE);
	}

	//ZT
	if (HasZTViewWidget(strMacroID))
	{
		EnableAction(STT_CNTR_CMD_ZTView, TRUE, TRUE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_ZTView, FALSE);
	}

	//特性曲线图
	if (pTestMacroUI->HasCharLib())
	{
		EnableAction(STT_CNTR_CMD_CharDrawView, TRUE, TRUE);
		SelectActionByID(STT_CNTR_CMD_CharDrawView, TRUE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_CharDrawView, FALSE);
		SelectActionByID(STT_CNTR_CMD_CharDrawView, FALSE);
	}

	//ToolBar
	UpdateButtonsStateByID(STT_CNTR_CMD_SaveTemplate, TRUE);
	UpdateButtonsStateByID(STT_CNTR_CMD_SaveAsTemplate, TRUE);
	UpdateButtonsStateByID(STT_CNTR_CMD_TestThis, TRUE);

	EnableStartStopButton(TRUE);
}

void QSttTestCntrFrameWin::UpdateCmdButtonsState_AddMacro()
{
	if (CanAddTestMacroUI())
	{
		UpdateButtonsStateByID(STT_CNTR_CMD_AddMacro, TRUE);
		EnableAction(STT_CNTR_CMD_AddMacro, TRUE);
	}
	else
	{
		UpdateButtonsStateByID(STT_CNTR_CMD_AddMacro, FALSE);
		EnableAction(STT_CNTR_CMD_AddMacro, FALSE);
	}
}

void QSttTestCntrFrameWin::slot_UpdateChRsMaps( BOOL bSysParasHasChanged )
{
	//通道映射在无Macro以及view的情况下无法生效，这实际上应该算作一个BUG
	if(stt_Frame_TestMacroUI() && m_pMacroEditView)
	{
		if (stt_Frame_TestMacroUI()->IsUIOriginal())
		{
			CSttMacroParaEditViewOriginal* pOri = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
			pOri->m_bChMapsChanged = TRUE;
			OnUpdateTestResource(FALSE);

// 			if (bSysParasHasChanged)
// 			{
// 				pOri->m_bSystemParasChanged = TRUE;
// 				//			pOri->m_bIECParasChanged = TRUE;
// 			}
		}

		if (bSysParasHasChanged)
		{
			Cmd_SendSystemConfig();
		}

		Cmd_SendChMapsConfig();
	}
}

void QSttTestCntrFrameWin::ReInitViews()
{
	m_tabTestTools->clear();
	m_tabTestViews->clear();
}

void QSttTestCntrFrameWin::InitIcon(const CString& strItemID, const QIcon& icon)
{
	CSttFrame_Button* pTestBtn = NULL;

	if ((strItemID == STT_CNTR_CMD_StartTest)||(strItemID == STT_CNTR_CMD_StopTest))
	{
		pTestBtn = GetStartTestBtn();
	}
	else
	{
		pTestBtn = m_pSttFrameConfig->GetToolBar()->FindBtnByID(strItemID);
	}

	if(pTestBtn)
	{
		QSttToolButtonBase *pButton = (QSttToolButtonBase*)pTestBtn->m_dwItemData;
		if(pTestBtn->m_strIcon.GetLength())
		{
			//存在用户自定义的图片名称
			CString strPath = _P_GetResourcePath();//QString在有中文路径时乱码故修改为CString 
			strPath += pTestBtn->m_strIcon;
			pButton->setIcon(QIcon(strPath));
		}
		else
		{
			//否则采用默认图片
			pButton->setIcon(icon);
		}
		pButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//		pButton->setFixedHeight(60);

        if(g_dUIShowCoef >= 1.5)//2024-7-17 wuxinyi 修改2240*1400 缩放150%工具栏按钮宽度
		{
            pButton->setFixedSize(70*g_dUIShowCoef,pButton->m_nHeight*g_dUIShowCoef/*65*/);
		}
		else
		{
			pButton->setFixedSize(90,pButton->m_nHeight/*55*/);
		}

	}
}

void QSttTestCntrFrameWin::InitIcon()
{
	CString strPath = _P_GetResourcePath();
	strPath += "windows/";

	POS pos = m_pSttFrameConfig->GetToolBar()->GetHeadPosition();
	while (pos)
	{
		CSttFrame_Panal* pPanal = (CSttFrame_Panal*)m_pSttFrameConfig->GetToolBar()->GetNext(pos);
		if(pPanal->m_strID == "static-buttons"
			|| pPanal->m_strID == "float-buttons")
		{
			POS posBtn = pPanal->GetHeadPosition();
			while (posBtn)
			{
				CSttFrame_Button* pBtn = (CSttFrame_Button*)pPanal->GetNext(posBtn);
				if(pBtn == m_pSttFrameConfig->FindStartStopBtn())
				{
					InitIcon(pBtn->m_strID, QIcon(strPath + "start.png"));
				}
				else
				{
					InitIcon(pBtn->m_strID, QIcon(strPath + "button_bk.png"));
				}
			}
		}
	}
}

void QSttTestCntrFrameWin::InitUI()
{	
	CString strTitle;
	strTitle = /*_T("智能测试系统")*/g_sLangTxt_Win_IntelligentTestSystem.GetString();
	setWindowTitle(strTitle);
	QSttTestCntrFrameBase::InitUI();

	//this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

	g_theTestCntrFrame = this;

	if (g_pGlobalDatas == NULL)
	{
        g_pGlobalDatas = GetTestMacroUI_Paras();
	}

// 	QDesktopWidget *pDeskTop = QApplication::desktop();
// 	QRect rcScreen = pDeskTop->screenGeometry();
	m_nScreenWidth = 960;//rcScreen.width();
	m_nScreenHeight = 800;//rcScreen.height()-100;

	resize(m_nScreenWidth,m_nScreenHeight);

	HDC hd = GetDC(NULL);
	double dDotPix1 = GetDeviceCaps(hd, LOGPIXELSX);
	g_dUIShowCoef = dDotPix1 / 96;

	//////////////////////////////////////////////////////////////////////////
	//菜单和工具栏区域
	CSttFrame_Menus *pMenusParas = m_pSttFrameConfig->GetMenus();
	CSttFrame_ToolBar *pToolBar = m_pSttFrameConfig->GetToolBar();
	m_pMenuBar = new QSttMenuBar(pMenusParas,this);
	setMenuBar(m_pMenuBar);
	connect(m_pMenuBar,SIGNAL(sig_MenuClicked(QString)),this,SLOT(slot_MenuButtonClick(QString)));
	m_pToolBarWin = new QSttToolBar(pToolBar,this);
	addToolBar(Qt::TopToolBarArea, m_pToolBarWin);
	connect(m_pToolBarWin,SIGNAL(sig_ToolBarClicked(QString)),this,SLOT(slot_MenuButtonClick(QString)));

	//////////////////////////////////////////////////////////////////////////
	//中间工作区域
	m_wndWorkspace = new QWidget(this);
	m_wndTopTestWnds = new QWidget(this);
	m_pHBoxLayout = new QHBoxLayout(m_wndTopTestWnds);
	m_wndTopTestWnds->setLayout(m_pHBoxLayout);
	m_pHBoxLayout->setSpacing(0);
	m_pHBoxLayout->setContentsMargins(0, 0, 0, 0);
	m_wndWorkspace->resize(m_nScreenWidth,m_nScreenHeight);

	m_pSplitClientVert = new QSplitter(Qt::Vertical,m_wndWorkspace);
	m_pSplitWorkspace = new QSplitter(Qt::Horizontal,m_wndTopTestWnds);
	m_pHBoxLayout->addWidget(m_pSplitWorkspace);
	//m_wndWorkspace->setStyleSheet("QWidget::handle{background-color:red}");

	//左边属性视图
	CSttFrame_GbTree *pTree = m_pSttFrameConfig->GetGbTree();
	m_pSttGbTreeView = new QSttGuideBookTreeWidget_Win(NULL, pTree, m_wndTopTestWnds);
	m_tabTestViews = new QSttTestViewsTabWidget(m_wndTopTestWnds);	//中间测试视图区域

	if (m_bIsAutoTest)
	{
		m_tabTestViews->setTabsClosable(true);  //2022-9-13  lijunqing 关闭tab
		m_tabTestViews->setDocumentMode(true); 
	}
	else
	{
		m_tabTestViews->setTabPosition(QTabWidget::South);
		m_tabTestViews->findChildren<QTabBar*>().at(0)->hide();
	}

	connect(m_tabTestViews, SIGNAL(tabCloseRequested(int)), this, SLOT(OnCloseTabTestViews(int)));
	connect(m_tabTestViews, SIGNAL(sig_CurrClickChanged(int)), this, SLOT(slot_currentChangedTabWidget(int)),Qt::UniqueConnection);

	m_tabTestTools = new QTabWidget(m_wndTopTestWnds);	//右边测试工具区域
	InitInfoWidget(this);

	if (m_bIsAutoTest)
	{
		m_tabTestTools->setTabsClosable(true);  //2022-9-13  lijunqing 关闭tab
		m_tabTestTools->setDocumentMode(true); 
	}

	connect(m_tabTestTools, SIGNAL(tabCloseRequested(int)), this, SLOT(OnCloseTabTestTools(int)));

	QFont infoFont = font();
	infoFont.setPointSize(10);
	m_pInfoWidget->horizontalHeader()->setFont(infoFont);
	m_pInfoWidget->setFont(infoFont);
	InitStateMonitor();
 	InitVectorWidget(NULL, NULL, this);
//	CString strTitle; 
// 	strTitle = _T("信息视图");
// 	m_tabTestTools->addTab(m_pInfoWidget, strTitle);
// 	strTitle = _T("状态监视");
// 	m_tabTestTools->addTab(m_pStateMonitorWidget, strTitle);
// 	strTitle = _T("矢量图");
// 	m_tabTestTools->addTab(m_pVectorWidget, strTitle);

//	m_pSttReportViewHtml = new QSttReportViewHtml();
//	m_pSttReportViewHtml->OpenHtmlFile(STT_REPORT_HEAD_HTML_FILE);   //打开报告头文件
// 	strTitle = _T("报告视图");
//	m_tabTestViews->addTab(m_pSttReportViewHtml, strTitle);

    //ftt 2024.9.25
    //m_pSttReportView = new QSttReportView();
//    strTitle = _T("报告视图");
//    m_tabTestViews->addTab(m_pSttReportView, strTitle);

    //ftt 2024.10.23
    m_pSttReportView = new QSttReportView;
    connect(this, SIGNAL(sig_AddUpdateReportQT(QString, CExBaseObject*)), m_pSttReportView, SLOT(slot_AddUpdateReportQT(QString, CExBaseObject*)), Qt::QueuedConnection);
    connect(this, SIGNAL(sig_DeleteReportQT(QString)), m_pSttReportView, SLOT(slot_DeleteReportQT(QString)), Qt::QueuedConnection);
    connect(this, SIGNAL(sig_ClearAllReportsQT()), m_pSttReportView, SLOT(slot_ClearAllReportsQT()), Qt::QueuedConnection);

	//界面初始化时不应该显示与测试项有关的界面
	QRect rcClient = rect();
	QRect rcViews = QRect(rcClient.width() * 2 / 10, rcClient.top(), rcClient.width() * 5 / 10, rcClient.height());
	QRect rcTools = QRect(rcClient.width() * 7 / 10, rcClient.top(), rcClient.width() * 3 / 10, rcClient.height());
	m_tabTestTools->setGeometry(rcTools);
	m_tabTestViews->setGeometry(rcViews);
	m_pInfoWidget->hide();

	InitIecRecordMain();

	QList<int> nSizes;

	m_pSplitWorkspace->setOpaqueResize(false);//取消实时变动，实时变动在存在状态图的界面会因为刷新qwt图像而卡顿
	m_pSplitClientVert->setOpaqueResize(false);

	m_pSplitWorkspace->addWidget(m_pSttGbTreeView);
	m_pSplitWorkspace->addWidget(m_tabTestViews);
	m_pSplitWorkspace->addWidget(m_tabTestTools);
	//m_pSplitClientVert->addWidget(m_pSplitWorkspace);

	if (m_bIsAutoTest)
	{
		nSizes << 150 << 500 << 350;
	}
	else
	{
		QDesktopWidget* desktopWidget = QApplication::desktop(); 
		QRect rect = desktopWidget->screenGeometry();

		if (rect.width() <= 1024)
		{
			nSizes << 150 << 425 << 310;
		}
		else
		{
			nSizes << 150 << 425 << 425;
		}
	}

	m_pSplitWorkspace->setSizes(nSizes);
	m_pSplitWorkspace->setChildrenCollapsible(false);
	

	m_pSttGbTreeView->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	m_tabTestViews->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	m_tabTestTools->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

	m_pSttGbTreeView->setMinimumSize(100, 100);
	m_tabTestViews->setMinimumSize(100, 100);
	m_tabTestTools->setMinimumSize(100, 100);

	//新的输出窗口停靠栏 yizejun 2023-2-6
	CString strTemp = /*"输出"*/g_sLangTxt_Output.GetString();
	m_tabTestOutput = new QTabWidget(this);

	if (m_bIsAutoTest)
	{
		m_tabTestOutput->setTabsClosable(true);  //2022-9-13  lijunqing 关闭tab
		m_tabTestOutput->setDocumentMode(true); 
	}

	m_pOutputWidget = new QSttOutPutWidget();
	m_pOutputWidget->textEdit->setReadOnly(true);
	strTemp = /*"输出栏"*/g_sLangTxt_OutputBar.GetString();
	m_tabTestOutput->addTab(m_pOutputWidget, strTemp);
	m_pWinResultWidget = new QSttOutPutWidget();
	m_pWinResultWidget->textEdit->setReadOnly(true);
	strTemp = /*"结果栏"*/g_sLangTxt_ResultBar.GetString();
	m_tabTestOutput->addTab(m_pWinResultWidget, strTemp);

	m_pSplitClientVert->addWidget(m_pToolBarWin);
	m_pSplitClientVert->addWidget(m_wndTopTestWnds);
	m_pSplitClientVert->addWidget(m_tabTestOutput);

	nSizes.clear();
	nSizes << 50 << 800 << 150;
	m_pSplitClientVert->setSizes(nSizes);
	m_pSplitClientVert->setChildrenCollapsible(false);
	

// #ifdef _DEBUG
// 	//windows下，删除输出框  shaolei 2023-1-11
// 	m_pOutputWidget = new QSttOutPutWidget();
// 	m_pSplitClientVert->addWidget(m_pOutputWidget);
// #endif
// 	m_pSplitClientVert->setStretchFactor(0, 6);
// 	m_pSplitClientVert->setStretchFactor(1, 4);
// 
// #ifdef _DEBUG
// 	m_pOutputWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
// #endif

	m_pVLayout = new QVBoxLayout(this);
	m_wndWorkspace->setLayout(m_pVLayout);
	m_pVLayout->addWidget(m_pSplitClientVert);

	//m_pOutputWidget->resize(m_nScreenWidth, m_nScreenHeight*0.3);
	//listSize.clear();
	//listSize <<m_nScreenHeight*7/10<<m_nScreenHeight*3/10;
	//m_pSplitClientVert->setSizes(listSize);

	m_tabTestViews->setMovable(true);
	m_tabTestTools->setMovable(true);
	m_tabTestOutput->setMovable(true);

	//////////////////////////////////////////////////////////////////////////
	//StatusBar
	CSttFrame_StatusBar *pStatusBarParas = m_pSttFrameConfig->GetStatusBar();
	CString strLight = /*_T("状态灯显示")*/g_sLangTxt_StatusLight.GetString();
	m_wndDockStatusBar = new QDockWidget(strLight,this);  
	m_wndDockStatusBar->setFeatures(QDockWidget::NoDockWidgetFeatures);  
	m_pStatusBar = new QSttBarBase(pStatusBarParas, m_oDataBtnsMngr,m_gFont,m_wndDockStatusBar);
	m_wndDockStatusBar->setWidget(m_pStatusBar);

    if(g_dUIShowCoef >= 1.5)
    {
       m_wndDockStatusBar->setFixedHeight(85);//2024-7-18 wuxinyi 修改2240*1400 缩放150%状态灯显示不全
    }
    else
    {
	m_wndDockStatusBar->setFixedHeight(65);//固定高度 sf 20220326
    }

   // m_wndDockStatusBar->setMinimumHeight(65);
	addDockWidget(Qt::BottomDockWidgetArea,m_wndDockStatusBar,Qt::Vertical);
	m_wndDockStatusBar->show();

	//区域创建完毕
	//setCentralWidget(m_wndWorkspace);


	//resize(m_nScreenWidth,m_nScreenHeight);

	setCentralWidget(m_wndWorkspace);
//	showMaximized();//20230530 zhouhj 放入Main函数中处理,在调用exec()前使用

	((QSttGuideBookTreeWidget_Win*)m_pSttGbTreeView)->CreateGuideBookMenu();
	m_tabTestTools->hide();	//2023-1-28  lijunqing
//	CreateEngineClientWidget();  //2023.5.31 zhouhj  在新建任务时,已经会创建,此处删除
}	

void QSttTestCntrFrameWin::PromptToSave(CExBaseObject *pSelObj, BOOL bIsItemSame)
{
	CSttItems *pItems = (CSttItems *)Stt_GetFirstParentItems(pSelObj, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pItems == NULL)
	{
		return;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("提示保存：    %s     %s    "), m_pSttGbTreeView->m_pCurrSelRootNode->m_strName.GetString(),
//		pItems->m_strName.GetString());
	if (bIsItemSame == FALSE)
	{
		if (m_pSttGbTreeView->m_pCurrSelRootNode == pItems)
		{
			return;
		}
	}

	BOOL bIsParaChanged = FALSE;
	CDataGroup oParas;

	CharactDatasToTestMacroParas();
	IsUiParasChanged(bIsParaChanged, &oParas);
	if (m_pMacroEditView == NULL)
	{
		return;
	}

// 	if(!m_pMacroEditView->IsHtmlView())
// 	{
// 		CSttMacroParaEditViewOriginal* pMacro = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
// 		bIsParaChanged = pMacro->m_bTmtParaChanged;
// 
// 		pMacro->m_bTmtParaChanged = FALSE;
// 	}

	if (bIsParaChanged)
	{
		   // shaolei   修改为参数自动保存   2022-12-21
		CSttMacroTestUI_TestMacroUI *pSttMacroTestUI_TestMacroUI = stt_Frame_TestMacroUI();

		if (pSttMacroTestUI_TestMacroUI->IsInternationalMode())//zhouhj 2024.9.10 国际版模式，参数修改后，固定需要同步给自动测试
		{
			SaveTestMacroUIParas(&oParas);
			UpdateCharactWidgetForTest(0);
		}
		else
		{
			CString strName = pSttMacroTestUI_TestMacroUI->m_strName;
			CString strMsg, strAdd;
			strMsg = _T("项目[ ");
			strMsg += strName;
			strAdd = _T(" ] 的参数发生改变，是否保存？保存将删除上次的测试结果");
			strMsg += strAdd;
			CString strTitle;
			strTitle = _T("确认保存项目参数");
			int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

			if (result == QMessageBox::Yes)
			{
				//m_pTestMacroUI_Paras = &pTestCtrlCntrBase->m_oTestMacroUI_Paras;
				SaveTestMacroUIParas(&oParas);
				UpdateCharactWidgetForTest(0);
			}
		}
	}
}

void QSttTestCntrFrameWin::ClearEmptyChildren(CDataGroup* pSrcObj, CDataGroup* pDesObj)
{
	CExBaseObject *pObj = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = pDesObj->GetHeadPosition();
	while(pos)
	{
		pObj = pDesObj->GetNext(pos);
		pFind = (CExBaseObject *)pSrcObj->FindSame(pObj);
		if(!pFind)
		{
			pDesObj->Delete(pObj);
		}
		else
		{
			ClearEmptyChildren((CDataGroup*)pFind, (CDataGroup*)pObj);
		}
	}
}

BOOL QSttTestCntrFrameWin::UpdateChildren(CDataGroup* pSrcObj, CDataGroup* pDesObj)
{
	if (pSrcObj == pDesObj)
	{
		return FALSE;
	}

	if (!pDesObj->IsBaseList())
	{
		return FALSE;
	}

	CExBaseObject *pObj = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = pSrcObj->GetHeadPosition();
	CExBaseList listAppend;

	while (pos != NULL)
	{
		pObj = pSrcObj->GetNext(pos);
		ASSERT(pObj != NULL);
		pFind = (CExBaseObject *)pDesObj->FindSame(pObj);

		if (pFind != NULL)
		{
			pObj->Update(pFind);
		}
		else
		{
			listAppend.AddTail(pObj);
		}
	}

	pDesObj->AppendClone(listAppend);
	listAppend.RemoveAll();

	//删除pDesObj里多余的子对象
	ClearEmptyChildren(pSrcObj, pDesObj);

	return TRUE;
}

void QSttTestCntrFrameWin::SaveTestMacroUIParas(CDataGroup *pParas)
{
	//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("+++++++++++++++++++++++++++++++620"));
	if (pParas == NULL)
	{
		return;
	}

	if (m_pTestMacroUI_Paras == NULL)
	{
		return;
	}

	CSttItems *pCurrSelRootNode = m_pSttGbTreeView->m_pCurrSelRootNode;

	if (pCurrSelRootNode == NULL)
	{
		return;
	}

	//提示是否保存参数时，形参pSelObj是当前选中的节点：需要页面切换后，新展示项目参数的测试项；
	//m_pCurrSelRootNode是上一次选中节点的，找到的最近的ROOT-TYPE的Items节点。
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pCurrSelRootNode->m_strstxmlFile);
	BOOL bIsInternationalMode = FALSE;

	if (pTestMacroUI != NULL)
	{
		if (pTestMacroUI->IsInternationalMode())
		{
			bIsInternationalMode = TRUE;
		}
	}

	//yzj 2023-3-22 原有的UpdateChildren不能支持m_pTestMacroUI_Paras的子项比pParas子项多的情况,故叠加谐波等场景下无法删除旧子项
	//pParas->UpdateChildren(m_pTestMacroUI_Paras);

	if (bIsInternationalMode)
	{
		Ats_UpdateAllMacroItem_InternationalMode(pCurrSelRootNode);
		return;
	}
	else
	{
		UpdateChildren(pParas, m_pTestMacroUI_Paras);
		SaveUIParaFile(m_pTestMacroUI_Paras);
	}

	if (pTestMacroUI == NULL)
	{
		return;
	}

	CString strItemParentPath;
	QSttGuideBookTreeWidget_Win *pTree = (QSttGuideBookTreeWidget_Win *)m_pSttGbTreeView;
	//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("+++++++++++++++++++++++++++++++654"));

	/*   2023-4-12 shaolei  开始测试时，不进行类型的判断，原生态功能也发送GenerateItems指令
	//因为UpdateItem指令，无法将默认的结果判断返回回来
	if (pTestMacroUI->IsUIOriginal())
	{
		CSttMacroTest *pMacroTest = (CSttMacroTest *)pCurrSelRootNode->FindByID(pTestMacroUI->m_strID);
		ASSERT(pMacroTest != NULL);

		if (pMacroTest == NULL)
		{
			return;
		}

		pTree->m_bTreeUpdateFinish = FALSE;
		strItemParentPath = pMacroTest->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
		CLogPrint::LogString(XLOGLEVEL_TRACE, "B5");
		long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateItem(strItemParentPath);
		CLogPrint::LogString(XLOGLEVEL_TRACE, "B6");
		//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("+++++++++++++++++++++++++++++++669"));
		if (nRet == STT_CMD_ExecStatus_SUCCESS)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, "B7");
			//发送成功，则更新本地的参数
			CSttTestMacroUiParas *pUIParas = (CSttTestMacroUiParas *)pMacroTest->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROUIPARAS);

			++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
			CString strParas = m_pTestMacroUI_Paras->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);
			--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
			pUIParas->m_strParaText = strParas;
			pTree->m_bTreeUpdateFinish = TRUE;
		}
	}
	else if (pTestMacroUI->IsUIWeb())
	*/
	{
		CExBaseObject *pParent = (CExBaseObject *)pCurrSelRootNode->GetParent();
		strItemParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		CGbMacroGenWzd *pMacroGen = (CGbMacroGenWzd *)g_theGbSmartGenWzd->FindMacroGen(pCurrSelRootNode->m_strID
			, pCurrSelRootNode->m_strName, strItemParentPath);

		if (pMacroGen != NULL)
		{
			pTree->m_bTreeUpdateFinish = FALSE;

			CExBaseObject *pParent = (CExBaseObject *)pTree->m_pCurrSelRootNode->GetParent();
			CString strItemParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE); 
			CString strRootNodePath;

			if (strItemParentPath.GetLength() > 0)
			{
				strRootNodePath = strItemParentPath + _T("$");
			}

			strRootNodePath += pTree->m_pCurrSelRootNode->m_strID;

//			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("切换项目，自动保存++++++++++++++++++++0    %s"), pCurrSelRootNode->m_strName.GetString());
			g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems(strItemParentPath, pCurrSelRootNode->m_strName
				, pCurrSelRootNode->m_strID, pMacroGen->m_pCmdGenParas, g_theGbSmartGenWzd->m_strDvmFile
				, pMacroGen->m_strTestClass,pCurrSelRootNode->m_nTestTimes, pCurrSelRootNode->m_nRptTitle
				, pCurrSelRootNode->m_nTitleLevel);

			//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("+++++++++++++++++++++++++++++++709"));
//			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("切换项目，自动保存++++++++++++++++++++1    %s"), pTree->m_pCurrSelRootNode->m_strName.GetString());
 //			QSttGuideBookTreeWidget_Win *pTree = (QSttGuideBookTreeWidget_Win *)m_pSttGbTreeView;
			
			g_pTheSttTestApp->m_pTestCtrlCntr->WaitCmdReplyProcess();
 			pTree->After_SaveCurr(strRootNodePath);
			//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("+++++++++++++++++++++++++++++++715"));
		}
	}
}

BOOL QSttTestCntrFrameWin::IsContinueCreateNew()
{
	if (!m_pTestCtrlCntrBase->IsHasTestTask())
	{
		return TRUE;  //测试不存在时，默认继续创建
	}

	CString strMsg;
	strMsg = _T("当前已存在测试任务，是否继续创建测试。若是，则会覆盖当前测试任务，覆盖后无法恢复！");
	CString strTitle;
	strTitle = _T("测试已存在");
	int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result != QMessageBox::Yes)
	{
		return FALSE;
	}

	//继续创建测试，需要删除已有的HTML报告、删除向导中所有的操作记录
	ClearSmartGenWzd();

	return TRUE;
}

void QSttTestCntrFrameWin::ClearSmartGenWzd()
{
	POS pos = g_theGbSmartGenWzd->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = g_theGbSmartGenWzd->GetNext(pos);

		if (pObj->GetClassID() != DVMCLASSID_GBMACROGENWZD)
		{
			continue;
		}

		CGbMacroGenWzd *pMacroGenWzd = (CGbMacroGenWzd *)pObj;
        //ftt 2024.9.27
        if(m_pSttReportViewHtml != NULL)
        {
            m_pSttReportViewHtml->DeleteMacroTestReport(pMacroGenWzd->m_strParentItemsID, pMacroGenWzd->m_strItemsID);
        }
    }

	stt_Frame_SetTestMacroUI(NULL);
	g_theGbSmartGenWzd->CreateNew();
}

void QSttTestCntrFrameWin::ShowCharEditTab()
{
	CString strTitle;
	xlang_GetLangStrByFile(strTitle, "Win_CharEditTabTitle");
	m_tabTestViews->addTab(m_pCharLibWidget, QIcon(""), strTitle);
}

void QSttTestCntrFrameWin::ShowHideCharactUI(BOOL bIsInternationalMode, BOOL bHasCharLibFile)
{
	if (bIsInternationalMode && (m_pCharactWidgetForTest!= NULL))
	{
		long nTabIndex = m_tabTestTools->indexOf((QWidget*)m_pCharactWidgetForTest);

		if (nTabIndex != -1)
		{
			if (!bHasCharLibFile)
			{
				m_tabTestTools->removeTab(nTabIndex);

				if (m_tabTestTools->count() == 0)
				{
					m_tabTestTools->hide();  //隐藏区域
				}
			}
		}
		else if (bHasCharLibFile)
		{
			if (m_tabTestTools->count() == 0)
			{
				m_tabTestTools->show();  //显示区域
			}

			CString strText;
			xlang_GetLangStrByFile(strText, "Win_CharTabTitle");
			nTabIndex = m_tabTestTools->insertTab(0, m_pCharactWidgetForTest, strText); //20240806 zhangyq 将特性图放在首位
			//nTabIndex = m_tabTestTools->addTab(m_pCharactWidgetForTest, strText);
			m_tabTestTools->setCurrentIndex(nTabIndex);
		}
	} 

	if ((!bIsInternationalMode) && bHasCharLibFile &&
		(m_pCharacteristics != NULL) && (!IsTestStarted()))
	{
		ShowCharEditTab();
	}
	else
	{
		HideCharEditTab();
	}
}

void QSttTestCntrFrameWin::HideCharEditTab()
{
	m_tabTestViews->removeTab(m_tabTestViews->indexOf(m_pCharLibWidget));
}

void QSttTestCntrFrameWin::UpdateStartStopTestButton(const CString &strState)
{
	if (m_pStartTestBtn == NULL)
	{
		return;
	}

	QSttToolButton *pButton = (QSttToolButton*)m_pStartTestBtn->m_dwItemData;
	CString strFilePath = _P_GetResourcePath();
	strFilePath += "windows/";
	if (strState == STT_TEST_STATE_TESTTING)
	{
		m_pStartTestBtn->m_strID = STT_CNTR_CMD_StopTest;
		m_pStartTestBtn->m_strName = g_sLangTxt_StopTest;
		InitIcon(STT_CNTR_CMD_StopTest, QIcon(strFilePath + "stop.png"));
	}
	else
	{
		m_pStartTestBtn->m_strID = STT_CNTR_CMD_StartTest;
		m_pStartTestBtn->m_strName = g_sLangTxt_StartTest;
		InitIcon(STT_CNTR_CMD_StartTest, QIcon(strFilePath + "start.png"));
	}

	pButton->setText(m_pStartTestBtn->m_strName);
}


void QSttTestCntrFrameWin::UpdateEnableState(const CString &strState)
{
	if (m_pToolBarWin != NULL)
	{
		m_pToolBarWin->UpdateEnableState(strState);
	}
}

void QSttTestCntrFrameWin::InitSttIecRecord()
{
#ifdef use_CSmartCapCtrl
	g_pTheSttTestApp->InitKeyDB();//20230302 zhouhj 打开探测界面时,如果KeyDB未初始化,需要进行初始化
	m_oStt61850CapTestAppCfg.SttOpen(_T("TestAppConfig.xml"));
	g_pTheSttTestApp->InitSttIecRecord(&m_oStt61850CapTestAppCfg/*pSttTestAppCfg*/);
#endif

}

void QSttTestCntrFrameWin::InitAfterCreateSttMacroPara()
{
	QSttTestCntrFrameBase::InitAfterCreateSttMacroPara();

	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();

	if(strIDMacroUI == STT_ORG_MACRO_MUAccuracyTest || strIDMacroUI == STT_ORG_MACRO_MUFirstCycleTest
		|| strIDMacroUI == STT_ORG_MACRO_MUAccurAutoTest|| strIDMacroUI == STT_ORG_MACRO_MUAutoTest)
	{
#ifdef use_CSmartCapCtrl
        OnCmd_IecCap();
		g_bSmartCap_RecordNow = 0;//进入监视界面时,再开启报文解析功能,

		if (g_pSttMUTestIecCbSelWidget == NULL)
		{
			g_pSttMUTestIecCbSelWidget = new QSttMUTestIecCbSelWidget();
//			g_pSttMUTestIecCbSelWidget->show();
		}

		if (g_pSttIecRecordDetectWidget != NULL)
		{
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewSmv = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewSmv;
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewGoose = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewGoose;
			g_pSttMUTestIecCbSelWidget->m_pGridIecCb_CBSel->m_bViewFT3 = g_pSttIecRecordDetectWidget->m_pGridIecCb->m_bViewFT3;
		}

		g_pSttMUTestIecCbSelWidget->Refresh_MUTest();
#endif
    }

	//chenling 20240419 ADMU IEC配置FT3码值设置二次额定电压保存时需要除以1000，保留xml小数点不够
	if (strIDMacroUI == STT_ORG_MACRO_MUAccuracyTest || strIDMacroUI == STT_ORG_MACRO_MUAccurAutoTest
		|| strIDMacroUI == STT_MACRO_ID_ShortTimeOverTest || strIDMacroUI == STT_MACRO_ID_SoeTest)
	{
		g_nPugiFloatSize = 9;
	}
	else
	{
		g_nPugiFloatSize = 3;
	}
}


void QSttTestCntrFrameWin::Ats_UpdateParameter()
{
	CDataGroup oRetParas;

	m_pMacroEditView->GetDatas(&oRetParas);
	SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing 记录和保存当前页面设置的值：设置为默认值

	//比较oRetParas 与 m_pTestMacroUI_Paras
	if (!m_pTestMacroUI_Paras->IsEqual(&oRetParas))
	{
		oRetParas.CopyChildren(m_pTestMacroUI_Paras);
		if (stt_Frame_TestMacroUI()->IsUIWeb()
			|| stt_Frame_TestMacroUI()->m_strID == STT_ORG_MACRO_MUAutoTest)
		{
			m_pTestCtrlCntrBase->Ats_GenerateTemplate();
		}
		else
		{
			CString strItemPath;
			CString strMacroID = stt_Frame_TestMacroUI()->m_strID;
			if (m_pMacroTest_Original == NULL)
			{
				strItemPath = stt_Frame_TestMacroUI()->m_strID;
				strItemPath += "$" + strItemPath;
			}
			else
			{
				strItemPath = m_pMacroTest_Original->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
			}
			
			m_pTestCtrlCntrBase->Ats_SetItemPara(strItemPath, strMacroID);
		}
	}
}

void QSttTestCntrFrameWin::AdjustToolBarButtons()
{
	if(g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "??????????????AdjustToolBarButtons lijunqing ：添加调整工具栏按钮状态的功能");
	}
}

void QSttTestCntrFrameWin::ClearAllAinDataMap()
{
	POS pos = m_pAinDataMapCfg->GetHeadPosition();

	while (pos != NULL)
	{
		//2023-9-4  由于传递报文时，只传递了name、id、value、data-type。
		//记录数据集路径的属性，由format改为data-type
		CDvmData *pDataMap = (CDvmData *)m_pAinDataMapCfg->GetNext(pos);
		pDataMap->m_strValue.Empty();
		pDataMap->m_strDataType.Empty();
	}
}

CSttMacroParaEditInterface* QSttTestCntrFrameWin::CreateSttMacroParaEditView(const CString &strMacroID,const CString &strGridFile, BOOL bUseExist)
{
	CSttMacroParaEditInterface* pSttMacroParaEditInterface = QSttTestCntrFrameBase::CreateSttMacroParaEditView(strMacroID,strGridFile,bUseExist);

    if (pSttMacroParaEditInterface == NULL)
    {
        return pSttMacroParaEditInterface;
    }

	if (m_tabTestViews)
	{
		((QSttTestViewsTabWidget*)m_tabTestViews)->SetCurrMacroView((QWidget*)pSttMacroParaEditInterface->m_pMacroParaEditWnd);
	}

	return pSttMacroParaEditInterface;
}

void QSttTestCntrFrameWin::CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI, BOOL bUseExist)
{
	QSttTestCntrFrameBase::CreateSttMacroParaEditView(pTestMacroUI,bUseExist);
}

void QSttTestCntrFrameWin::CreateSttMacroParaEditView(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	if (pTestMacroUI->m_strID == STT_ORG_MACRO_Iec61850Config
		|| pTestMacroUI->m_strID == STT_ORG_MACRO_SystemConfig
		|| pTestMacroUI->m_strID == STT_ORG_MACRO_ChMapsConfig)
	{
		return;
	}

	QWidget *pMacroEditWidget = NULL;
	long nTabIndex = 0;

	if (m_tabTestViews)
	{
		//先设置成未初始化状态； shaolei  2023-11-20
		((QSttTestViewsTabWidget*)m_tabTestViews)->SetHasInit(false);
	}

	//删除之前的tab
	if (m_pMacroEditView != NULL)
	{
		pMacroEditWidget = GetMacroEditWidget();
		nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
		m_tabTestViews->removeTab(nTabIndex);
	}

	m_pMacroEditView = CreateSttMacroParaEditView(pTestMacroUI->m_strUI_ID,pTestMacroUI->m_strGirdFile);
	pMacroEditWidget = GetMacroEditWidget();

    if (pMacroEditWidget != 0)
    {
        pMacroEditWidget->setParent(this);
		//nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);

		//if (nTabIndex<0)
		//{
		//	m_tabTestViews->addTab(pMacroEditWidget, pTestMacroUI->m_strName);
		//}
    }

    UpdateToolButtons_AfterAddMacro();
	
}

void QSttTestCntrFrameWin::AdjustMacroToolWidget(QWidget* pWidget, const CString& strMacroID)
{
	if(m_tabTestTools->indexOf(pWidget) == -1)
	{
		SelectActionByID(strMacroID, TRUE);
		slot_MenuButtonClick(strMacroID);
	}
	else if(m_tabTestTools->currentIndex() == m_tabTestTools->indexOf(pWidget))
	{
		pWidget->show();
	}
}

void QSttTestCntrFrameWin::CharactDatasToTestMacroParas()
{
	if (m_tabTestViews->currentWidget() == m_pCharLibWidget)
	{
		//如果当前界面为特性曲线界面,将特性曲线界面参数同步到测试功能网页界面
        TemplateView_Prepare();
	}
}

void QSttTestCntrFrameWin::FFT_CalDebug()
{
#ifdef use_CSmartCapCtrl
    double dVariable_FftPhaseDeltPoint[1200];
	int nPointCnt = 1024;
	long nSmpRate = 4000;
	double  dMag =  0.0f,    dPhase  = 0.0f,   dFreq =  50.0f,dInitAngle = 5.0f,dSignlePointAng = 0.0f;
//	dInitAngle *= _PI_D_180;
	dSignlePointAng = 50*360.0/4000.0;

	for (int nIndex = 0;nIndex<nPointCnt;nIndex++)
	{
//		dPhase = dInitAngle;

		dPhase = nIndex*dSignlePointAng + dInitAngle;
		dPhase *= _PI_D_180;

		while(dPhase >2*_PI)
		{
			dPhase -= 2*_PI;
		}

		dVariable_FftPhaseDeltPoint[nIndex] = SQRT2*3.0*sin(dPhase);
	}

	AfxCalcFFT(dVariable_FftPhaseDeltPoint, nPointCnt, nSmpRate, dMag, dPhase, dFreq);
	dPhase += 90.0f;
	nSmpRate = 0;
#endif
}

void QSttTestCntrFrameWin::ClearResultWidget()
{
    if(m_pWinResultWidget != NULL)
        m_pWinResultWidget->ClearAll();
}

void QSttTestCntrFrameWin::AdjustMacroToolWidgetOrder(const CString &strMacroID)
{
	if (strMacroID.IsEmpty())
	{
		return;
	}
	m_tabTestTools->clear();

	CStringArray WidgetOrder;

	if (strMacroID == STT_ORG_MACRO_ManualTest
		|| strMacroID == STT_ORG_MACRO_SequenceManuTest
		|| strMacroID == STT_ORG_MACRO_PowerManuTest
		|| strMacroID == STT_ORG_MACRO_LineVolManuTest
		|| strMacroID == STT_ORG_MACRO_ImpedManualTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_StateDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_PowerDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_ReplayTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_WaveDrawView);
	}
	else if (strMacroID == STT_ORG_MACRO_HarmTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_WaveDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_StateTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_StateDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_PowerDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_DiffCBOpTest_I)
	{
		WidgetOrder.Add(STT_CNTR_CMD_SystemView);
		WidgetOrder.Add(STT_CNTR_CMD_WiringView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_VolInverseTimeTest_I
		|| strMacroID == STT_ORG_MACRO_CurrInverseTimeTest_I
		|| strMacroID == STT_ORG_MACRO_CurrInverseTimeTest
		|| strMacroID == STT_ORG_MACRO_VolInverseTimeTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_CharDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_GradientTest 
		|| strMacroID == STT_ORG_MACRO_FaultGradientTest
		|| strMacroID == STT_ORG_MACRO_ActionTimeTest_I
		|| strMacroID == STT_ORG_MACRO_LowFreqTest_I
		|| strMacroID == STT_ORG_MACRO_LowVolTest_I)
	{
		WidgetOrder.Add(STT_CNTR_CMD_StateDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_DistanceTest_I
		|| strMacroID == STT_ORG_MACRO_DistanceTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_CharDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_ZTView);		
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_StateDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_RecloseAccTest_I
		|| strMacroID == STT_ORG_MACRO_CBOperateTest
		|| strMacroID == STT_ORG_MACRO_SequenceGradientTest
		|| strMacroID == STT_ORG_MACRO_LineVolGradientTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_StateDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_PowerDirectionTest_I)
	{
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_SynTest_I
		|| strMacroID == STT_ORG_MACRO_DiffTest_I)
	{
		WidgetOrder.Add(STT_CNTR_CMD_CharDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_WiringView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_DistanceSearchTest_I
		|| strMacroID == STT_ORG_MACRO_DistanceSearchTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_CharDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_ZTView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_DiffCBOpTest_I)
	{
		WidgetOrder.Add(STT_CNTR_CMD_SystemView);
		WidgetOrder.Add(STT_CNTR_CMD_WiringView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_SwingTest)
	{
		WidgetOrder.Add(STT_CNTR_CMD_CharDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_SystemView);
		WidgetOrder.Add(STT_CNTR_CMD_VectorDrawView);
		WidgetOrder.Add(STT_CNTR_CMD_InfoView);
	}
	else if (strMacroID == STT_ORG_MACRO_MUAccuracyTest 
		|| strMacroID == STT_ORG_MACRO_MUFirstCycleTest
		|| strMacroID == STT_ORG_MACRO_MUAccurAutoTest 
		|| strMacroID == STT_ORG_MACRO_MUAutoTest
		|| strMacroID == STT_ORG_MACRO_MUTimingAccurTest
		|| strMacroID == STT_ORG_MACRO_MUPunctAccurTest)
	{
		long nTabIndex = m_tabTestTools->indexOf(m_pSttIecRecordMainWidget);

		if (nTabIndex == -1)
		{
			OnMenuClickedAction_Tools(m_pSttIecRecordMainWidget, "报文探测");
		}
	}


	for (int nIndex = 0; nIndex < WidgetOrder.GetSize(); ++nIndex)
	{
		CString strWidgetID = WidgetOrder.GetAt(nIndex);
		slot_MenuButtonClick(strWidgetID);
	}

	m_tabTestTools->setCurrentIndex(0);
}

void QSttTestCntrFrameWin::AdjustMacroToolWidgetToFrame(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{
	if (stt_Frame_TestMacroUI() == NULL)
	{
		return;
	}

	CString strMacroID = pTestMacroUI->m_strID;

	//固定选中并展示的界面
	SelectActionByID(STT_CNTR_CMD_TemplateView, TRUE);

	if (HasWaveWidget(strMacroID))
	{
		AdjustMacroToolWidget(m_pWaveDrawWidget, STT_CNTR_CMD_WaveDrawView);
	}

//     if(pTestMacroUI->m_strUI_ID != STT_ORG_MACRO_ReplayTest)//2024-7-17 wuxinyi 故障回放无需矢量图
//     {
// 		AdjustMacroToolWidget(m_pVectorWidget, STT_CNTR_CMD_VectorDrawView);
// 		AdjustMacroToolWidget(m_pStateMonitorWidget, STT_CNTR_CMD_StateDrawView);//2024-7-30 wuxinyi 新增需求默认需要状态图
//     }
	//AdjustMacroToolWidget(m_pInfoWidget, STT_CNTR_CMD_InfoView);

    //if(pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_DistanceTest_I)
    //{
    //     AdjustMacroToolWidget(m_pZTViewWidget, STT_CNTR_CMD_ZTView);
    //}
	if (HasVectorWidget(strMacroID))
    {
	AdjustMacroToolWidget(m_pVectorWidget, STT_CNTR_CMD_VectorDrawView);
    }

	if (HasStateMonitorWidget(strMacroID))
	{
		AdjustMacroToolWidget(m_pStateMonitorWidget, STT_CNTR_CMD_StateDrawView);
	}

	if (HasInfoWidget(strMacroID))
	{
	AdjustMacroToolWidget(m_pInfoWidget, STT_CNTR_CMD_InfoView);
	}
	if (HasZTViewWidget(strMacroID)/*pTestMacroUI->m_strUI_ID == STT_ORG_MACRO_DistanceTest_I*/)
    {
         AdjustMacroToolWidget(m_pZTViewWidget, STT_CNTR_CMD_ZTView);
    }
	if (HasPowerDiagramWidget(strMacroID))
	{
		AdjustMacroToolWidget(m_pZTViewWidget, STT_CNTR_CMD_PowerDrawView);
	}	
	if (HasZTViewWidget(strMacroID))
    {
         AdjustMacroToolWidget(m_pZTViewWidget, STT_CNTR_CMD_ZTView);
    }
	if (HasSystemDiagramWidget(strMacroID))
	{
		AdjustMacroToolWidget(m_pSystemDiagramWidget, STT_CNTR_CMD_SystemView);
	}
	if (HasWiringDiagramWidget(strMacroID))
	{
		AdjustMacroToolWidget(m_pWiringDiagramWidget, STT_CNTR_CMD_WiringView);
	}

	AdjustMacroToolWidgetOrder(pTestMacroUI->m_strID);//调整右侧视图顺序


	//根据不同MacroID选择性选中并展示的界面
	//存在特性曲线
	if(pTestMacroUI->m_strCharlibFile.GetLength() && (IsTestStarted()))
	{
		ShowCharacterTesting(TRUE);
		//AdjustMacroToolWidget(m_pCharactWidgetForTest, STT_CNTR_CMD_CharDrawView);
	}
	else
	{
		m_tabTestTools->removeTab(m_tabTestTools->indexOf(m_pCharactWidgetForTest));

		if (m_pCharTestPointsGrid)
		{
			long nGridTabIndex = m_tabTestViews->indexOf(m_pCharTestPointsGrid);

			if (nGridTabIndex>=0)
			{
				m_tabTestViews->removeTab(nGridTabIndex);
			}			
		}
	}
}

void QSttTestCntrFrameWin::ShowCharacterTesting(BOOL bShow)
{
	long nTabIndex = 0;

	if (m_pCharactWidgetForTest != NULL)
	{
		nTabIndex = m_tabTestTools->indexOf((QWidget*)m_pCharactWidgetForTest);

		if(nTabIndex != -1)
		{
			if (!bShow)
			{
				m_tabTestTools->removeTab(nTabIndex);

				if (m_tabTestTools->count() == 0)
				{
					m_tabTestTools->hide();  //隐藏区域
				}
			} 
		}
		else if (bShow)
		{
			if (m_tabTestTools->count() == 0)
			{
				m_tabTestTools->show();  //显示区域
			}

			CString strText;
			xlang_GetLangStrByFile(strText, "Win_CharTabTitle");
			nTabIndex = m_tabTestTools->addTab(m_pCharactWidgetForTest, strText);
			m_tabTestTools->setCurrentIndex(nTabIndex);
		}
	}

	if (m_pCharTestPointsGrid != NULL)
	{
		nTabIndex = m_tabTestViews->indexOf((QWidget*)m_pCharTestPointsGrid);

		if(nTabIndex != -1)
		{
			if (!bShow)
			{
				m_tabTestViews->removeTab(nTabIndex);
			} 
		}
		else if (bShow)
		{
			CString strText;
			xlang_GetLangStrByFile(strText, "CharLib_TestPointsGrid");
			nTabIndex = m_tabTestViews->addTab(m_pCharTestPointsGrid, strText);
			m_tabTestViews->setCurrentIndex(nTabIndex);
		}
	}

// 	if (m_pCharLibWidget != NULL)
// 	{
// 		nTabIndex = m_tabTestViews->indexOf((QWidget*)m_pCharLibWidget);
// 
// 		if(nTabIndex != -1)
// 		{
// 			m_tabTestViews->setTabEnabled(nTabIndex,bShow);
// 		}
// 	}
}

void QSttTestCntrFrameWin::AdjustMacroEditWidgetToFrame(CSttMacroTestUI_TestMacroUI *pTestMacroUI)
{//2022-3-25  调整参数窗口
	QWidget *pMacroEditWidget = GetMacroEditWidget();

	long nTabIndex = m_tabTestViews->addTab(pMacroEditWidget, pTestMacroUI->m_strName);

	if (nTabIndex >= 0)
	{
		m_tabTestViews->setCurrentIndex(nTabIndex);
	}
	
	AdjustMacroToolWidgetToFrame(pTestMacroUI);
}

bool QSttTestCntrFrameWin::GenerateTemplate(CExBaseObject *pParentItems, const CString &strItemsName, const CString &strItemsID, long nRepeatTimes
											, long nRptTitle, long nTitleLevel)
{
	long nRet = 0;
	bool bTemplateGened = false;
	BOOL bInternationalMode = FALSE;
	
	if (g_pTheSttTestApp->m_pTestMacroUI != NULL)
	{
		bInternationalMode =  g_pTheSttTestApp->m_pTestMacroUI->IsInternationalMode();
	}


	if(IsAutoTest() || bInternationalMode)
	{
		CString strItemParentPath;
		strItemParentPath = pParentItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
		CExBaseObject *pSelItems = m_pSttGbTreeView->GetCurrSelectGbItem();
		long nSynMode = STT_CMD_Send_Sync;

		if (IsNeedSendAsync(strItemsID))
		{
			nSynMode = STT_CMD_Send_Async;
		}

		nRet = m_pTestCtrlCntrBase->Ats_GenerateItems(strItemParentPath, strItemsName, strItemsID, NULL, g_theGbSmartGenWzd->m_strDvmFile, _T(""), nRepeatTimes
			, nRptTitle, nTitleLevel, nSynMode);
	}
	else
	{
		//单机测试
		nRet = m_pTestCtrlCntrBase->Ats_GenerateTemplate();
	}

	if (nRet == STT_CMD_ExecStatus_SUCCESS || nRet > 4)	//模板生成完成
	{
		bTemplateGened = true;
		if( g_nLogDebugInfor == 1 ) CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("底层测试模板生成完成."));
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("底层测试模板生成失败."));
	}

	return bTemplateGened;
}

//long QSttTestCntrFrameWin::OnItemStateChanged(CExBaseObject *pItem)
//{
// 	//需要改成信号槽，未完成  shaolei
// 	//对于rootnode的CSttItems节点的项目状态改变：此处必然是测试合格或者不合格
// 	//意味着一个测试功能点的项目做完了
// 	//切换到下一个功能点的测试项目时，需要停止状态图等刷新的定时器，否则会导致崩溃
// 	if (pItem->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
// 	{
// 		CSttItems *pItems = (CSttItems *)pItem;
// 
// 		if (pItems->m_strType == GBITEMS_NODETYPE_ROOTNODE)
// 		{
// 			StopStateMonitor();
// 			m_bInited = false;
// 		}
// 	}
// 	else
// 	{
// 		if(!m_bInited)
// 		{
// 			StartStateMonitor();
// 			m_bInited = true;
// 		}
// 	}
// 	//m_pSttGbTreeView->SetCurTestItem(pItem);
// 	((CSttItemBase *)pItem)->UpdateParentState();
// 	emit sig_OnItemStateChanged(pItem);
// 	QSttTestCntrFrameBase::OnItemStateChanged(pItem);
// 	return 0;
//}

long QSttTestCntrFrameWin::OnTestFinished()
{
// 	QSttGuideBookTreeWidget_Win *pTreeView = (QSttGuideBookTreeWidget_Win *)m_pSttGbTreeView;
// 	pTreeView->SetCheckBoxEnable(TRUE);  20230422 zhouhj 放入sig_OnViewTestStop对应槽函数中处理

	QSttTestCntrFrameBase::OnTestFinished();
	//connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	emit sig_UpdateCmdButtons_AddMacro();
	m_pSttGbTreeView->m_pTreeCtrl->UpdateItemColour();

	//测试结束时，自动保存
	emit sig_Timer_AutoSave();//slot_Timer_AutoSave();
	return 0;
}

long QSttTestCntrFrameWin::OnTestStarted()
{
	//m_pSttGbTreeView->m_pTreeCtrl->setEnabled(false);
	emit sig_ExpandGuideBookTree();
	//ExpandRootNode();

	disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	QSttTestCntrFrameBase::OnTestStarted();
	return 0;
}

long QSttTestCntrFrameWin::OnTestStoped()
{
	QSttTestCntrFrameBase::OnTestStoped();
	//connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	emit sig_UpdateCmdButtons_AddMacro();

	//测试停止时，自动保存
	emit sig_Timer_AutoSave();//slot_Timer_AutoSave();
	return 0;
}

long QSttTestCntrFrameWin::OnItemStateChanged(CExBaseObject *pItem)
{
	QSttTestCntrFrameBase::OnItemStateChanged(pItem);

	CSttItemStateObject* pObj = (CSttItemStateObject*)pItem;
	CSttItemBase *pSttItem = (CSttItemBase*)pObj->m_pItem;

	if (pSttItem->m_nState == TEST_STATE_TESTING)
	{
		QSttGuideBookTreeWidget_Win *pTreeView = (QSttGuideBookTreeWidget_Win *)m_pSttGbTreeView;
		pTreeView->SetCheckBoxEnable(FALSE);
		disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
		//yzj 2023.10.17 两处地方都发该信号会导致在两次信号间停止的测试被再次启动
		//emit sig_OnViewTestStart();
	}
	
	return 0;
}

void QSttTestCntrFrameWin::slot_OnViewTestStop()
{
	if (m_bIsViewStoped)
	{
		//刷新为停止态，只刷新一次。否则会触发SetItemState。
		return;
	}

	m_bIsViewStoped = TRUE;
	QSttTestCntrFrameBase::slot_OnViewTestStop();
	ShowCharacterTesting(FALSE);
	QSttGuideBookTreeWidget_Win *pTreeView = (QSttGuideBookTreeWidget_Win *)m_pSttGbTreeView;
	pTreeView->SetCheckBoxEnable(TRUE);

	CSttMacroTestUI_TestMacroUI* pTestMacroUI  = stt_Frame_TestMacroUI();
	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib()); //2024.7.30 zhangyq 显示/隐藏特性曲线界面

	//特性曲线
	if (pTestMacroUI != NULL)//测试完成后,如果当前测试项包含特性曲线,则显示特性曲线编辑界面
	{
		if (pTestMacroUI->HasCharLib() && (!pTestMacroUI->IsInternationalMode())
			&& m_pCharacteristics != NULL
			&& pTreeView->m_pCurrSelRootNode)
		{
			ShowCharEditTab();
		}
	}

	connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
}

void QSttTestCntrFrameWin::slot_OnViewTestStart()
{
	m_bIsViewStoped = FALSE;
	QSttTestCntrFrameBase::slot_OnViewTestStart();
	QSttGuideBookTreeWidget_Win *pTreeView = (QSttGuideBookTreeWidget_Win *)m_pSttGbTreeView;
	pTreeView->SetCheckBoxEnable(FALSE);
	HideCharEditTab();//开始测试后,隐藏特性曲线编辑界面
}

long QSttTestCntrFrameWin::OnTestCreated()
{
	return 0;
}

void QSttTestCntrFrameWin::OnReport(CExBaseObject *pItem) 
{
	CSttItemBase *pSttItem = (CSttItemBase*)pItem;
	CSttReports *pSttReports = pSttItem->GetSttReports();

	if (pSttReports == NULL)
	{
		return;
	}

	CSttReport *pReport = (CSttReport*)pSttReports->GetTail();

	if (pReport == NULL)
	{
		return;
	}

    CSttItems *pRootNode = Stt_GetFirstParentItems(pItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
	BOOL bIsInternationalMode = FALSE;

	//在页面上显示报告数据，例如手动模块
	if (m_pMacroEditView != NULL)
	{
		m_pMacroEditView->ShowReport(pReport->m_pValues);

		if (m_pMacroEditView->IsInternationalMode())//更新国际版表格结果
		{
			QSttMultiMacroParaEditViewBase *pSttMultiMacroParaEditViewBase = (QSttMultiMacroParaEditViewBase*)m_pMacroEditView;
			pSttMultiMacroParaEditViewBase->ShowRslt(pSttItem);
			bIsInternationalMode = TRUE;
		}
	}

	//对于通讯命令项目，根据报告数据，刷新通讯后台页面显示设备数据模型
	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		CSttCommCmd *pCommCmd = (CSttCommCmd *)pSttItem;
		CString strDsPath;

		CSttCommCmdData *pSttCmdData = pCommCmd->GetCommCmdData(FALSE);

		if (pSttCmdData != NULL)
		{
			strDsPath = pSttCmdData->m_strDatasetPath;

			//先更新模型中的值
			g_theGbSmartGenWzd->UpdateDvmDataset(strDsPath, pReport->m_pValues);
			g_theGbSmartGenWzd->UpdateDvmDataset(pReport->m_pRptDvmDataset);
		}

		if (m_pEngineClientWidget != NULL)
		{
			m_pEngineClientWidget->UpdateShowDvmDataset(strDsPath);
			m_pEngineClientWidget->UpdateShowDvmDataset(pReport->m_pRptDvmDataset);
		}

		if (m_pCmdWzdDsEditWidget != NULL)
		{
			m_pCmdWzdDsEditWidget->UpdateShowDataset(strDsPath);
		}
	}

	FillReport(pItem);
//	AddUpdateReport_QT(pRootNode, false); //ftt  zhouhj 2024.10.16 删除此处在前面已做处理

	if(m_pCharactWidgetForTest)
	{
		if (!bIsInternationalMode)
		{
			m_pCharactWidgetForTest->AddTestResultPoint(pReport->m_pValues);
		} 

		CExBaseObject *pParent = (CExBaseObject*)pSttItem->GetParent();

		//add wangtao 20241022 更新结果数据至特性曲线搜索点
		if ((pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST) && (bIsInternationalMode))
		{
			CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pSttItem;
			CString strMacroID,strItemPath;
			strMacroID = pSttMacroTest->GetTestMacroID();
			strItemPath = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
			UpdateCharactResult_I(strMacroID, strItemPath, pReport->m_pValues);

			CString strCharactPath, strFaultTypeID;
			strCharactPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
			strCharactPath += _T("Img");
			strFaultTypeID = GetPngFaultTypeID(pSttMacroTest);
			emit sig_FillReportImg(strCharactPath.GetString(), strFaultTypeID);
		}
		
// 		CSttSearchResults* pResults = (CSttSearchResults*)pReport->m_pValues;
// 		CSttSearchResults* pResults_Clone = (CSttSearchResults*)pResults->Clone();
// 		emit sig_UpdateSearchResults(GetCurrentUI_ID(), pSttItem->m_strID, pResults_Clone);
		
//		CExBaseObject *pParent = (CExBaseObject*)pSttItem->GetParent();
		//CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(pSttItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
		UINT nClassID = pParent->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTMACROCHARITEMS)
		{
			CSttMacroCharItems *pCharItems = (CSttMacroCharItems *)pParent;

			CString strBase64;
			CSttCharacteristic* pSttChar = (CSttCharacteristic*)pCharItems->FindByClassID(STTGBXMLCLASSID_CSTTCHARACTERISTIC);

			if (pSttChar != NULL)
			{
				//m_pSttCharacterDrawPng->GetSearchingPng(NULL, strBase64);
				CString strCharactPath,strParentItemsPath;
				strParentItemsPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
				strCharactPath = strParentItemsPath + _T("Img");
				emit sig_FillReportImg(strCharactPath.GetString(),"");
				//m_pSttReportViewHtml->FillReportImg("", strCharactPath, strBase64);//zhouhj 20230213 用于插入差动图片
			}
		}
	}

// 	if (m_pCharTestPointsGrid)
// 	{
// 		m_pCharTestPointsGrid->AddTestResultPoint(pReport->m_pValues);
// 	}
}

void QSttTestCntrFrameWin::OnAtsGenerate()
{
	QSttTestCntrFrameBase::OnAtsGenerate();

	//查找第一个rootnode
	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	CSttItems* pRootNode = pGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pRootNode != NULL)
	{
		m_pSttGbTreeView->m_pCurrSelRootNode = pRootNode;
		m_pSttGbTreeView->m_strCurrSelRootNodePath = pRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
        //AddUpdateReport_QT(pRootNode);//zhouhj 2024.10.16 单机模式更新报告
        //ftt 2024.10.23 使用项目路径更新报告
        QString strItemsPath = pRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
        AddUpdateReport_QT(strItemsPath);
	}
}

void QSttTestCntrFrameWin::OnAtsGenerateItems(CExBaseObject *pItems, BOOL bUpdateParent,BOOL bIsInternationalMode)
{
	if (pItems == NULL)
	{
		return;
	}

	//保存参数时，需要从父节点刷新树形控件显示
	CExBaseList *pParent = (CExBaseList *)pItems->GetParent();

	if (bIsInternationalMode)
	{
		if (g_nUpdateMultiMacroParaEditView != 0)
		{
			emit sig_UpdateMultiMacroParaEditView();
		}
	}
	else
	{
		if (bUpdateParent)
		{
			emit sig_ShowItems_TreeView(pParent);
		}
		else
		{
			emit sig_ShowItems_TreeView((CExBaseList *)pItems);
		}
	}

	//装置复归态，特殊处理
	if (pItems->m_strID == STT_ITEMS_ID_DEVRESET)
	{
		return;
	}

	//测试前、后通讯组合，特殊处理
	if (pItems->m_strID == STT_CMD_PARA_generate_items_cmd_add_grp)
	{
		return;
	}

	//导入模型文件(模型替换)
	if (pItems->m_strID == STT_CMD_PARA_generate_items_import_dvm_file)
	{
		return;
	}

	//遥测参数映射
	if (pItems->m_strID == STT_CMD_PARA_generate_items_ain_data_map)
	{
		return;
	}

	CString strParentPath;
	strParentPath = _T("");

	if (pParent != NULL)
	{
		strParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}

	CSttItems *pSttItems = (CSttItems *)pItems;

	if (!bIsInternationalMode)//国际版模式下报告自动测试生成
	{
		UpdateRptHtml(pItems->m_strID,pSttItems->m_strstxmlFile,strParentPath);//20230324 参数2位MacroUI_ID
	}

	if (m_pSttGbTreeView->m_pCurrSelRootNode != NULL)
	{
		CString strNewItemsPath,strCurrRootNodePath;
		strNewItemsPath = pSttItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
//		strCurrRootNodePath = m_pSttGbTreeView->m_pCurrSelRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		if (strNewItemsPath == m_pSttGbTreeView->m_strCurrSelRootNodePath)
		{
			m_pSttGbTreeView->m_pCurrSelRootNode = pSttItems;
			GetTestMacroUiParas(pSttItems);//zhouhj 2023.8.10 更新当前选择原始数据对象m_pMacroTest_Original
		}
	} 
	else if(pSttItems->IsTypeRootNode())
	{
		m_pSttGbTreeView->m_pCurrSelRootNode = pSttItems;
		GetTestMacroUiParas(pSttItems);//zhouhj 2023.8.10 更新当前选择原始数据对象m_pMacroTest_Original
		m_pSttGbTreeView->m_strCurrSelRootNodePath = m_pSttGbTreeView->m_pCurrSelRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("xxxxxxxxfor debugxxxxxxxxxxxxxxxx+++++++++++++++++++++"));

    //AddUpdateReport_QT("pSttItems"); //ftt  自动测试模式,模板生成方式更新报告
    //ftt 2024.10.23 使用项目路径更新报告
    QString strItemsPath = pSttItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
    AddUpdateReport_QT(strItemsPath);
}

void QSttTestCntrFrameWin::OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp)
{
	if (m_pSttCommCmdWzdMainWidget == NULL)
	{
		return;
	}

	m_pSttCommCmdWzdMainWidget->OnAtsGenerateItems_CmdWzd(pCmdGrp);
}

void QSttTestCntrFrameWin::OnAtsGenerateItems_ImportDvm(CExBaseList *pItemsList)
{
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CSttDevice *pDevice = pGuideBook->GetDevice();

	//先刷新整个模板树显示
	emit sig_ShowItems_TreeView(pDevice);

	//再逐个通讯命令进行参数配置，需要弹窗显示。
	CSttItems *pItems = new CSttItems();
	pItems->m_strID = pItemsList->m_strID;
	pItems->AppendCloneEx(*pItemsList, TRUE);
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("import_dvm_file.xml");
	pItems->SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	emit sig_OnImportDvm(pItems);
	//InitImportDvmFileDlg(pItems);

	//释放应答数据，其中的通讯命令项目，应该Remove
	POS pos = pItemsList->GetHeadPosition();

	while (pos != NULL)
	{
		CSttItems *pChild = (CSttItems *)pItemsList->GetNext(pos);
		pChild->RemoveAll();
	}

	delete pItemsList;
	pItemsList = NULL;
}

//2022-9-13  lijunqing
void QSttTestCntrFrameWin::OnAtsQueryItem(CExBaseObject *pItemPara)
{
	if (m_pCmdWzdDsEditWidget == NULL)
	{
		return;
	}

	m_pCmdWzdDsEditWidget->OnAtsQueryItem(pItemPara);
}

void QSttTestCntrFrameWin::OnInputData(CSttParas *pParas,CExBaseList *pMsgs)
{
	//从TCP接收线程，传递过来的参数是临时对象
	CSttParas *pNewParas = new CSttParas();
	pNewParas->AppendCloneEx2(*pParas);
	CExBaseList *pNewMsgs = new CExBaseList();
	pNewMsgs->AppendCloneEx2(*pMsgs);

	emit sig_OnInputData(pNewParas, pNewMsgs);
}

void QSttTestCntrFrameWin::OnTestDisconnected()
{
	QSttTestCntrFrameBase::OnTestDisconnected();
}

void QSttTestCntrFrameWin::SetMacroTest_Original(CExBaseObject *pMacroTest)
{
	m_pMacroTest_Original = pMacroTest;
}
//void QSttTestCntrFramBase::on_btnSetDatas_clicked()
//{
//	CString strFile;
//	strFile = _P_GetDBPath();
//	strFile += _T("paras/");
//	strFile += _T("ZeroTest.sttjs");

//	CFile oFile;
//	oFile.Open(strFile, CFile::modeRead);
//	long nLen = oFile.GetLength();
//	char *pszBuffer = new char [nLen + 1];
//	oFile.Read(pszBuffer, nLen);
//	pszBuffer[nLen] = 0;
//	CString strDataset = pszBuffer;

//	m_pParaEdit->SetDatas(strDataset);

//	delete pszBuffer;

//}

void QSttTestCntrFrameWin::InitCommCmdWzdMain(CExBaseList *pParentItem)
{
	//先自动保存正在编辑的项目
	OnCmd_SaveEdit();

	//通讯命令生成向导
	if (m_pSttCommCmdWzdMainWidget == NULL)
	{
		m_pSttCommCmdWzdMainWidget = new QSttCommCmdWzdMainWidget(m_gFont, this);
		m_pSttCommCmdWzdMainWidget->setParent(this);
		m_pSttCommCmdWzdMainWidget->m_pParentItem = pParentItem;
	}

	CString strParentItemsID;
	strParentItemsID = pParentItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	m_pSttCommCmdWzdMainWidget->NewGbMacroGenWzd(strParentItemsID);
	m_pSttCommCmdWzdMainWidget->show();

	connect(m_pSttCommCmdWzdMainWidget, SIGNAL(sig_FreeCommCmdWzdWidget()), this, SLOT(slot_OnFreeCommCmdWzdWidget()));
}

void QSttTestCntrFrameWin::FreeCommCmdWzdMain()
{
	if (m_pSttCommCmdWzdMainWidget != NULL)
	{
		disconnect(m_pSttCommCmdWzdMainWidget, SIGNAL(sig_FreeCommCmdWzdWidget()), this, SLOT(slot_OnFreeCommCmdWzdWidget()));

		m_pSttCommCmdWzdMainWidget->close();
		delete m_pSttCommCmdWzdMainWidget;
		m_pSttCommCmdWzdMainWidget = NULL;
	}
}

void QSttTestCntrFrameWin::InitStateMonitor(bool bIsEx, QWidget* pParent)
{
	QSttTestCntrFrameBase::InitStateMonitor(bIsEx, pParent);
}

void QSttTestCntrFrameWin::InitStateMonitor(int nChannel, int type, bool bStart, QWidget* pPlotExWidget)
{
	QSttTestCntrFrameBase::InitStateMonitor(nChannel, type, bStart, pPlotExWidget);
}

void QSttTestCntrFrameWin::InitCharLibWidget(QWidget* pParent)
{
	QSttTestCntrFrameBase::InitCharLibWidget(pParent);

	if (m_pCharactWidgetForTest == NULL)
	{
		//2022-9-3  lijunqing
		m_pCharactWidgetForTest = new QCharactWidgetForTest;   //new QCharLibWidget(pParent);
		connect(this, SIGNAL(sig_UpdateDrawCharacters()), m_pCharactWidgetForTest, SLOT(slot_UpdateDrawCharacters()), Qt::QueuedConnection);//add wangtao 20241022 建立队列信号槽方式，刷新特性图
		m_pCharactWidgetForTest->setParent(this);
	}	

	if (m_pCharTestPointsGrid == NULL)
	{
		m_pCharTestPointsGrid = new QCharTestPointsGrid(m_pCharacteristics,this);   //new QCharLibWidget(pParent);
		m_pCharTestPointsGrid->InitGrid();
		//m_pCharTestPointsGrid->setParent(this);
	}
}

void QSttTestCntrFrameWin::AddAinDataMapValues(CSttReport *pSttReport)
{
	if (pSttReport->m_pRptDvmDataset == NULL)
	{
		return;
	}

	CDvmValues *pValues = (CDvmValues*)pSttReport->m_pValues;

	if (pValues == NULL)
	{
		return;
	}

	if (m_pAinDataMapCfg == NULL)
	{
		return;
	}

	CDvmData *pDataMap = NULL,*pDataSrc = NULL;
	CDvmValue *pResultValue = NULL;
	POS pos = m_pAinDataMapCfg->GetHeadPosition();

	while (pos != NULL)
	{
		pDataMap = (CDvmData *)m_pAinDataMapCfg->GetNext(pos);

		if (pDataMap->m_strValue.IsEmpty())
		{
			continue;
		}

		pDataSrc = (CDvmData*)pSttReport->m_pRptDvmDataset->FindByID(pDataMap->m_strValue);

		if (pDataSrc == NULL)
		{
			continue;
		}

		pResultValue = (CDvmValue*)pValues->FindByID(pDataMap->m_strID);

		CString strRptValue;
		AddAinDataMapValues_ProcessRatios(pDataMap->m_strID, pDataSrc->m_strValue, strRptValue);

		if (pResultValue != NULL)
		{
			pResultValue->m_strValue = strRptValue;
		} 
		else
		{
			pResultValue = new CDvmValue;
			pResultValue->m_strID = pDataMap->m_strID;
			pResultValue->m_strValue = strRptValue;
			pValues->AddNewChild(pResultValue);
		}
	}
}

void QSttTestCntrFrameWin::AddAinDataMapValues_ProcessRatios(const CString &strDataMapID, const CString& strSrcValue, CString &strDestValue)
{
	strDestValue = strSrcValue;

	if (m_pAinRatios == NULL)
	{
		return;
	}

	CDvmData *pDevMeas = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_DevMeas);

	if (pDevMeas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("找不到装置采样数据是一次值还是二次值的配置……"));
		return;
	}

	if (pDevMeas->m_strValue == "2")
	{
		//二次值，不用根据变比换算
		return;
	}

	//遥测参数映射时，都是固定ID映射
	if (strDataMapID == _T("MIa")
		|| strDataMapID == _T("MIb")
		|| strDataMapID == _T("MIc"))
	{
		return AddAinDataMapValues_ProcessRatios_I(strSrcValue, strDestValue);
	}
	else if (strDataMapID == _T("MUa")
		|| strDataMapID == _T("MUb")
		|| strDataMapID == _T("MUc"))
	{
		return AddAinDataMapValues_ProcessRatios_U(strSrcValue, strDestValue);
	}
	else if (strDataMapID == _T("P")
		|| strDataMapID == _T("Q"))
	{
		return AddAinDataMapValues_ProcessRatios_PQ(strSrcValue, strDestValue);
	}
	else
	{
		//剩余的功率因素和频率，不用换算
		return;
	}
}

void QSttTestCntrFrameWin::AddAinDataMapValues_ProcessRatios_I(const CString& strSrcValue, CString &strDestValue)
{
	if (m_pAinRatios == NULL)
	{
		return;
	}

	CDvmData *pCtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("找不到CT变比一次值……"));
		return;
	}

	CDvmData *pCtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("找不到CT变比二次值……"));
		return;
	}

	double dPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dRatio = dPrimary / dSecondary;

	double dRptVal = CString_To_double(strSrcValue);
	dRptVal = dRptVal / dRatio;
	strDestValue.Format(_T("%.3f"), dRptVal);
}

void QSttTestCntrFrameWin::AddAinDataMapValues_ProcessRatios_U(const CString& strSrcValue, CString &strDestValue)
{
	if (m_pAinRatios == NULL)
	{
		return;
	}

	CDvmData *pPtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比一次值……"));
		return;
	}

	CDvmData *pPtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比二次值……"));
		return;
	}

	double dPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT变比是 kV / V。
	double dRatio = dPrimary * 1000 / dSecondary;  

	//装置采样一次值时，电压单位为kV
	double dRptVal = CString_To_double(strSrcValue);
	dRptVal = dRptVal * 1000 / dRatio;
	strDestValue.Format(_T("%.3f"), dRptVal);
}

void QSttTestCntrFrameWin::AddAinDataMapValues_ProcessRatios_PQ(const CString& strSrcValue, CString &strDestValue)
{
	if (m_pAinRatios == NULL)
	{
		return;
	}

	CDvmData *pCtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtPrimary);

	if (pCtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比一次值……"));
		return;
	}

	CDvmData *pCtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_CtSecondary);

	if (pCtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到CT变比二次值……"));
		return;
	}

	CDvmData *pPtPrimary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtPrimary);

	if (pPtPrimary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比一次值……"));
		return;
	}

	CDvmData *pPtSecondary = (CDvmData *)m_pAinRatios->FindByID(ID_PARA_PtSecondary);

	if (pPtSecondary == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("模板全局数据中，找不到PT变比二次值……"));
		return;
	}

	double dCtPrimary = CString_To_double(pCtPrimary->m_strValue);
	double dCtSecondary = CString_To_double(pCtSecondary->m_strValue);
	double dPtPrimary = CString_To_double(pPtPrimary->m_strValue);
	double dPtSecondary = CString_To_double(pPtSecondary->m_strValue);
	//PT变比是 kV / V。r
	double dRatio = (dCtPrimary / dCtSecondary) * (dPtPrimary * 1000 / dPtSecondary); 

	//装置采样一次值时，电压单位为kV。功率的单位是MW，MVA
	double dRptVal = CString_To_double(strSrcValue);
	dRptVal = dRptVal * 1000000 / dRatio;
	strDestValue.Format(_T("%.3f"), dRptVal);
}

BOOL QSttTestCntrFrameWin::IsAinDataMapValid()
{
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();

	if (pGuideBook == NULL)
	{
		return FALSE;
	}

	return pGuideBook->IsAinDataMapValid();
}

BOOL QSttTestCntrFrameWin::Warning_AinDataMapInvalid(CSttItemBase *pItem)
{
	CString strMsg, strAdd, strTitle;
	strMsg = _T("检测到存在遥测项目，但未检测到有效的遥测参数映射，请确认是否继续测试？\r\n无效的遥测映射参数，可能会导致无效的实验结果数据！");
	
	if (pItem == NULL)
	{
		strAdd = _T("在当前模板中，");
	}
	else
	{
		strAdd = _T("在当前项目中，");
	}

	strMsg = strAdd + strMsg;
	strTitle = _T("确认是否继续测试");
	int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result == QMessageBox::Yes)
	{
		return TRUE;
	}

	return FALSE;
}

void QSttTestCntrFrameWin::FillReport(CExBaseObject *pItem)
{
	CSttItemBase *pSttItem = (CSttItemBase*)pItem;
	CSttReports *pSttReports = pSttItem->GetSttReports();
	CString strItemID;
	strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	if (pSttReports == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前测试项(%s)下不包含报告数据."),strItemID.GetString());
		return;
	}

	CSttReport *pSttReport = (CSttReport*)pSttReports->GetTail();

	if (pSttReport == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前测试项(%s)下包含的报告数据为空."),strItemID.GetString());
		return;
	}

	CString strMacroID;
	strMacroID = _T("");

	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pItem;
        strMacroID = pSttMacroTest->GetTestMacroID();
	}

	UpdateResultWidget(pSttReport,pSttItem->m_strName,strMacroID);

	//填写报告
	CString strParentItemsPath, /*strItemID,*/ strState;
	CExBaseObject *pParent = (CExBaseObject*)pItem->GetParent();
	strParentItemsPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	strItemID = pItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	strState = Gb_GetTestStateByID(pSttItem->m_nState);
//	CSttReport *pSttReport = (CSttReport *)pSttReports->GetTail();  //取最近的一次报告


	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	pNative->UpdateReportValuesByMacroTestDataType(pSttReport,strMacroID);//根据报告中的数据对象的数据类型判断,更新对应数据的值

	CSttItems *pRootNode = Stt_GetFirstParentItems(pSttItem, GBITEMS_NODETYPE_ROOTNODE, TRUE);
	ASSERT(pRootNode != NULL);

	if (pRootNode != NULL)
	{
		if (stt_IsItemsAin(pRootNode->m_strstxmlFile))
		{
			AddAinDataMapValues(pSttReport);//对于遥测类的结果,将通道映射的内容更新到报告values里面
		}
	}

	FillReport(strParentItemsPath, strItemID, strState, pSttReport);

	//2022-10-3  lijunqing 
	//处理通信命令
	if (pItem->GetClassID() != STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		return;
	}

	CSttCommCmd *pSttCommCmd = (CSttCommCmd*)pItem;

	if (! pSttCommCmd->m_nFillRptDataset)
	{
		return;
	}

	//2024-10-14 wuxinyi 解决当m_pSttReportViewHtml为空的中断问题
	if (m_pSttReportViewHtml)
	{
	if (pSttReport->m_pRptDvmDataset != NULL)
	{
		CDvmData *pDstData = NULL;
			if (g_pTheSttTestApp->GetCurrTestMacroUI() == STT_ORG_MACRO_MUAccurAutoTest)
			{
				if (strItemID.Find(_T("ReadRlts")) >= 0)
				{
			CDvmDataset *pRptDvmDataset = (CDvmDataset *)pSttReport->m_pRptDvmDataset->Clone();

					if (strItemID.Find(_T("UnAccuracy")) >= 0 || strItemID.Find(_T("InAccuracy")) >= 0 || strItemID.Find(_T("LongTimeOver_U")) >= 0 || strItemID.Find(_T("LongTimeOver_I")) >= 0
						|| strItemID.Find(_T("ShortTimeOver_U")) >= 0 || strItemID.Find(_T("ShortTimeOver_I")) >= 0)
				{
			bool bVol  = IsUnMagZero(pRptDvmDataset);
			POS pos = pRptDvmDataset->GetHeadPosition();
						while (pos)
			{
				POS pCurPos = pos;
						pDstData = (CDvmData *)pRptDvmDataset->GetNext(pos);

						if ((!bVol && (pDstData->m_strDataType == _T("Vol") || pDstData->m_strDataType == _T("电压"))) ||
								(bVol && (pDstData->m_strDataType == _T("Curr") || pDstData->m_strDataType == _T("电流"))))
				{
					pRptDvmDataset->RemoveAt(pCurPos);
				}
			}
				}

					POS pos1 = pRptDvmDataset->GetHeadPosition();
					while (pos1)
					{
						POS pCurPos = pos1;
						pDstData = (CDvmData *)pRptDvmDataset->GetNext(pos1);

					if (strItemID.Find(_T("AngAccuracy")) >= 0)
					{
							if (pDstData->m_strID.Find("Ia1") == -1)
						{
							pRptDvmDataset->RemoveAt(pCurPos);
						}
  		}
						else
					{
							if (pDstData->m_strDataType == _T("状态值") || pDstData->m_strDataType == _T("StateValue"))
						{
							pRptDvmDataset->RemoveAt(pCurPos);
    	}
					}
				}
				m_pSttReportViewHtml->FillReportDataset(strParentItemsPath, strItemID, pRptDvmDataset);
				}
    	}
  		else
		{
		m_pSttReportViewHtml->FillReportDataset(strParentItemsPath, strItemID, pSttReport->m_pRptDvmDataset);
		}
	}

	}

}


long QSttTestCntrFrameWin::IsUnMagZero(CDvmDataset *pRptDvmDataset)
{
	bool isZero  = true; 
	POS pos = pRptDvmDataset->GetHeadPosition();
	CDvmData *pDstData = NULL;
	CDvmValue *pDvmValue = NULL;

	while (pos != NULL)
	{
		pDstData  =  (CDvmData *)pRptDvmDataset->GetNext(pos);

		if (pDstData->m_strDataType == _T("Vol") || pDstData->m_strDataType == _T("电压"))
		{
			double dMag = 0;
			POS posIn = pDstData->GetHeadPosition();
			while (posIn != NULL)
			{
				pDvmValue = (CDvmValue*)pDstData->GetNext(posIn);

				if (pDvmValue->m_strID.Find("$mag") > 0)
				{
					dMag = CString_To_double(pDvmValue->m_strValue);

					if (dMag <= 0.00001)				
					{
						isZero = false;
						break; 
					}
				}
			}
		}
	}

	return isZero;
}

void QSttTestCntrFrameWin::FillReport(const CString &strParentItemsPath, const CString &strItemID, const CString &strState,  CSttReport *pSttReport)
{
	char *pszReport = NULL;

	if (NULL == m_pSttReportViewHtml)//add wangtao 20240929
	{
		return;
	}

	if (m_pSttReportViewHtml->IsRptFillMode_MAP_DATAS())
	{
		CSttRptMapDatas *pRptMapDatas = (CSttRptMapDatas*)pSttReport->FindByClassID(STTCMDCLASSID_CSTTRPTMAPDATAS);

		if (pRptMapDatas != NULL)
		{
			pRptMapDatas->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前插入路径(%s)."),strItemID.GetString());//zhouhj 20220317 此处增加打印信息.防止js脚本中出问题时,导致内容打印信息无法返回
			m_pSttReportViewHtml->FillRptMapDatas(pszReport, strState);
		}
	}
	else if (m_pSttReportViewHtml->IsRptFillMode_DATA_PATH())
	{//暂时没实现
	}
	else // (m_pSttReportViewHtml->IsRptFillMode_SYSTEM())
	{//系统模式
		pSttReport->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszReport, 0, _JSON_TYPE_);
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前插入路径(%s)."),strItemID.GetString());//zhouhj 20220317 此处增加打印信息.防止js脚本中出问题时,导致内容打印信息无法返回
		m_pSttReportViewHtml->FillReportData(strParentItemsPath, strItemID, strState, pszReport);
	}
	
	if (pszReport != NULL)
	{
		delete pszReport;
	}

}

void QSttTestCntrFrameWin::FillReport()
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return;
	}

    FillReports((CExBaseList*)m_pTestCtrlCntrBase->GetGuideBook());
}

void QSttTestCntrFrameWin::FillReports(CExBaseList *pItems)
{
	if (pItems == NULL)
	{
		return;
	}

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pItems->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case STTGBXMLCLASSID_CSTTDEVICE:
		case STTGBXMLCLASSID_CSTTITEMS:
			FillReports((CExBaseList*)p);
			break;

		case STTGBXMLCLASSID_CSTTCOMMCMD:
		case STTGBXMLCLASSID_CSTTMACROTEST:
		case STTGBXMLCLASSID_CSTTSAFETY:
		case STTGBXMLCLASSID_CSTTSYSPARAEDIT:
			FillReport(p);
			break;
		}
	}
}

void QSttTestCntrFrameWin::OnMenuClickedAction_Test(void* pWidget, const CString strTitle)
{
	if(pWidget == NULL)
	{
		return;
	}

	long nTabIndex = m_tabTestViews->indexOf((QWidget*)pWidget);

	if(nTabIndex != -1)
	{
		m_tabTestViews->removeTab(nTabIndex);
	}
	else
	{
		m_tabTestViews->addTab((QWidget*)pWidget, strTitle);
		m_tabTestViews->setCurrentIndex(nTabIndex);
	}
}

void QSttTestCntrFrameWin::OnMenuClickedAction_Tools(void* pWidget, const CString strTitle)
{
	if(pWidget == NULL)
	{
		return;
	}

	long nTabIndex = m_tabTestTools->indexOf((QWidget*)pWidget);
	CString strText/* = m_tabTestTools->tabText(nTabIndex)*/;

	if(nTabIndex != -1)
	{
		strText = m_tabTestTools->tabText(nTabIndex);
		m_tabTestTools->removeTab(nTabIndex);
		SelectActionByName(strText, FALSE);

		if (m_tabTestTools->count() == 0)
		{
			m_tabTestTools->hide();  //隐藏区域
		}

//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnMenuClickedAction_Tools[移除%s]"),strTitle.GetString());
	}
	else
	{
		nTabIndex = m_tabTestTools->count();

		if (nTabIndex/*m_tabTestTools->count()*/ == 0)
		{
			m_tabTestTools->show();  //显示区域
		}

		strText = strTitle;
		SelectActionByName(strText, TRUE);
		m_tabTestTools->addTab((QWidget*)pWidget, strTitle);
		m_tabTestTools->setCurrentIndex(nTabIndex);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("OnMenuClickedAction_Tools[添加%s]"),strTitle.GetString());
	}
}

BOOL QSttTestCntrFrameWin::CanAddTestMacroUI()
{
	CExBaseObject *pSel = m_pSttGbTreeView->GetCurrSelectGbItem();
	BOOL bCanAdd = TRUE;

	if (pSel == NULL)
	{
		bCanAdd = FALSE;
	}
	else
	{
		if (pSel->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			CSttItems *pSttItems = (CSttItems*)pSel;

			if (pSttItems->m_strType != STT_CMD_PARA_generate_items_items)
			{
				bCanAdd = FALSE;
			}
		}
		else if (pSel->GetClassID() != STTGBXMLCLASSID_CSTTDEVICE)
		{
			bCanAdd = FALSE;
		}
	}

	return bCanAdd;
}

void QSttTestCntrFrameWin::OpenMacroTestUI(CSttTestMacroUiParas *pUIParas, CSttMacroTestUI_TestMacroUI *pTestMacroUI
										   ,CSttTestMacroCharParas *pSttTestMacroCharParas)
{
	if (m_pMacroEditView == NULL)
	{
		return;
	}

	QSttTestCntrFrameBase::OpenMacroTestUI(pUIParas, pTestMacroUI,pSttTestMacroCharParas);
	//切换测试项时触发刷新可能存在的特性曲线图
//	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
//		QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
		//重新刷新网页的特性曲线图
// 		CString strFile;
// 		GetCharacteristicsFile(pTestMacroUI, strFile);
//		m_pCharacteristics->DeleteAll();
//
// 		if (IsFileExist(strFile))
// 		{
// 			m_pCharacteristics->OpenXmlFile(strFile,CCharacteristicXmlRWKeys::CCharacteristicsKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
// 		}

		//发送特性曲线改变事件
		if (pTestMacroUI->HasCharLib()) //2022-6-30  lijunqing
		{
			m_pCharacteristics->DeleteAll();

			if (pSttTestMacroCharParas != NULL)
			{
				m_pCharacteristics->SetXml(pSttTestMacroCharParas->m_strParaText,CCharacteristicXmlRWKeys::g_pXmlKeys);
			} 
			else
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE,_T("当前CSttTestMacroCharParas对象为空"));
			}

			InitCharLibWidget();
			m_pCharLibWidget->InitCharacteristicsLib(pTestMacroUI->m_strUI_ID,pTestMacroUI->m_strCharlibFile);
			m_pCharLibWidget->ShowCharacteristics(m_pCharacteristics);
//			m_pCharLibWidget->m_strCharParasFile = strFile;

			if (m_pCharactWidgetForTest != NULL)
			{
                m_pCharactWidgetForTest->InitCharacteristic(pTestMacroUI->m_strID, FALSE);//2024-10-15 wuxinyi 重新打开模板不需要删除测试点
			}

			if (m_pCharTestPointsGrid)
			{
				m_pCharTestPointsGrid->InitMacroID(pTestMacroUI->m_strID);
			}
		}
	}	

	//2024-10-14 wuxinyi 重新刷新国际版特性曲线图
	if (pTestMacroUI->HasCharLib() && pTestMacroUI->IsInternationalMode() && (m_pSttGbTreeView->m_pCurrSelRootNode != NULL))
	{
		QSttMultiMacroParaEditViewBase *pSttMultiMacroParaEditViewBase = (QSttMultiMacroParaEditViewBase*)m_pMacroEditView->m_pMacroParaEditWnd;
	}


}

void QSttTestCntrFrameWin::OpenMacroTestUI(CSttMacroTestUI_TestMacroUI *pTestMacroUI, const CString &strItemsName, const CString &strItemsID
										   , long nRepeatTimes, long nRptTitle, long nTitleLevel)
{
	QSttTestCntrFrameBase::OpenMacroTestUI(pTestMacroUI, strItemsName, strItemsID, nRepeatTimes, nRptTitle, nTitleLevel);
}

void QSttTestCntrFrameWin::AddMacroTestReport(CSttMacroTestUI_TestMacroUI *pTestMacroUI, CExBaseObject *pParent, const CString &strItemsName, const CString &strItemsID)
{
	//2024-9-14 wuxinyi 修复 m_pMacroEditView 未创建时导致的中断问题
	if (m_pMacroEditView == NULL)
	{
		return;
	}

	CString strGbDatas;

	char *strReport = NULL;
	CString strMacroID = stt_Frame_TestMacroUI()->m_strID;
	long nLen = 0;
	CString strParentPath;

	if (pParent != NULL)
	{
		strParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}
	CString strItemID_Tmp;
	strItemID_Tmp = strItemsID;

	if (strItemID_Tmp.IsEmpty())
	{
		strItemID_Tmp = pTestMacroUI->m_strID;
	}

	if(g_pTheSttTestApp->IsTestMacro_CurrVolChAsItem())
	{
		m_pMacroEditView->GetMacroItemsXml(strItemID_Tmp, &strReport);
	}

	//GetMacroItemsXml(strItemID_Tmp, &strReport, nLen,strParentPath);
	//m_pSttReportViewHtml->AddMacroTestReport(strParentPath, strItemsID, pTestMacroUI, strReport);	

    //ftt 2024.9.26 加判断
    if(m_pSttReportViewHtml != NULL)
    {
        m_pSttReportViewHtml->AddInsertCmd(pTestMacroUI, strParentPath, strItemID_Tmp/*pTestMacroUI->m_strID*/, strReport);//20230322 zhouhj 参数3应为当前测试项目ID
    }

	//if (strReport != NULL)
	//{
	//	delete strReport;
	//}
}

BOOL QSttTestCntrFrameWin::CreateEngineClientWidget()
{
	if (g_oSttSystemConfig.m_nInternationalMode)
	{
		return FALSE;
	}
// 	g_pTheSttTestApp->IinitGbWzdAiTool();
// 	g_theGbWzdAiTool->SetDvmDevice(g_theGbSmartGenWzd->m_pDvmDevice);
// 	g_theGbWzdAiTool->DvmFilterByExtendKeys();
// 	g_theGbWzdAiTool->SetSttGuideBook((CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook());
// 	//暂时屏蔽通讯后台功能，2023-3-22
 	//return;
	CString strTitle;
	strTitle = _T("通讯后台");
	BOOL bRet = FALSE;

	if (m_pEngineClientWidget == NULL)
	{
		QPpSttIotEngineClientWidgetMain *pMainWidget  =new QPpSttIotEngineClientWidgetMain();
		m_pEngineClientWidget = pMainWidget;
		bRet = TRUE;
	}

	m_tabTestViews->addTab(m_pEngineClientWidget, strTitle);
	m_pEngineClientWidget->ShowDvmDevice( g_theGbSmartGenWzd->m_pDvmDevice );
	m_pEngineClientWidget->NewPpSttIotDeviceClient(&g_theGbSmartGenWzd->m_oCommConfig, g_theGbSmartGenWzd->m_pDvmDevice);
	connect(m_pEngineClientWidget,  SIGNAL(sig_OnConfigDevice(CDataGroup *)), this, SLOT(slot_OnConfigDevice(CDataGroup *)));

	g_pTheSttTestApp->IinitGbWzdAiTool();
	g_theGbWzdAiTool->SetDvmDevice(g_theGbSmartGenWzd->m_pDvmDevice);
	g_theGbWzdAiTool->DvmFilterByExtendKeys();
	g_theGbWzdAiTool->SetSttGuideBook((CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook());
	return bRet;
}

void QSttTestCntrFrameWin::LogStringResult(long nLevel, const CString &strMsg)
{
	if (m_pWinResultWidget != NULL)
	{
		m_pWinResultWidget->LogString(nLevel,strMsg);
	}
}

/*
<group name="generate-items" id="generate-items" data-type="generate-items" value="create">
	<group id="device">
		<data id="EngineProgID" value="PpEngine"/>
		<data id="ppxml-file" value="SZNR-TTU.ppxml"/>
		<data id="dvm-file" value="SZNR-TTU.xml"/>
		<data id="remote-ip" value="127.0.0.1"/>
		<data id="remote-port" value="9988"/>
	</group>
	<group id="test-app">
		<data id="DeviceSN" value="123456789"/>
		<data id="EngineProgID" value="IotVm"/>
		<data id="dvm-file" value="MacroTest.xml"/>
		<data id="remote-ip" value="127.0.0.1"/>
		<data id="remote-port" value="9988"/>
	</group>
</group>
*/

//int g_TestShowType = 1;
//2022-09-09  lijunqing
void QSttTestCntrFrameWin::OnCmd_NewTest()
{
	//CLogPrint::LogString(XLOGLEVEL_TRACE, _T("OnCmd_NewTest : add messagebox to save changed"));
	QSttCreateNewTestWidget dlg(m_gFont,this);

	if (dlg.exec() != 1)
	{
		return;
	}

	if (m_pCmdWzdDsEditWidget != NULL)
	{
		//重新创建测试时，不进行参数保存
		m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
		m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
		DeleteCmdWzdDsEditWidget();
	}

	g_theGbSmartGenWzd->CreateNew();
	CDataGroup *pDevice = g_theGbSmartGenWzd->m_pDevice;
	CDataGroup *pTestApp = g_theGbSmartGenWzd->m_pTestApp;
	CDataGroup *pCommConfig = &g_theGbSmartGenWzd->m_oCommConfig;

	if(g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("?????????????? OnCmd_NewTest: 关闭打开的测试功能页面，并弹框提示是否保存修改 ???????????"));
	}

	g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	m_pSttGbTreeView->m_pCurrSelRootNode = NULL;
	m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
	g_pTheSttTestApp->m_pTestCtrlCntr->NewTest(pDevice, pTestApp, pCommConfig);

	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
	CString strName = GetFileTitleFromFilePath(g_theGbSmartGenWzd->m_strDvmFile, '/');
	pGuideBook->SetGuideBookName(strName);
	m_pSttGbTreeView->show();
	disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	m_pSttGbTreeView->ShowBaseList((CExBaseList *)pGuideBook);
	connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	pGuideBook->AddTimeSettingCoef(g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms);
	pGuideBook->SetItemsTec(NULL);

	UpdateToolButtons_AfterNew();

	m_tabTestTools->clear();
	m_tabTestTools->hide();
	m_tabTestViews->clear();

	CreateEngineClientWidget();   
    //ftt 2024.10.14
//	AddUpdateReport_QT(NULL, true);zhouhj 2024.10.16 在调用创建测试命令时，统一调用该接口


	//20240802 huangliang 统一在函数Stt_Global_SettingParent中执行，删除此处代码
//	//20240703 huangliang 记录模板数据地址
//	g_pDvmDevice_AttachSetting = g_theGbSmartGenWzd->m_pDvmDevice;
////	g_iSettingShowType = &g_TestShowType;	//测试显示类型0数值、1名称、2名称+数值
////	g_pSettingSelectFun = this->OnCmd_SettingSelect;	//20240730 huangliang 记录定值选择界面函数地址
//	if(g_pSettingSelectDlg == NULL)
//	{
//		g_pSettingSelectDlg = new SettingSelectDlg();
//		QObject::connect(g_pSettingSelectDlg, SIGNAL(sig_ShowSetting()), this, SLOT(slot_ShowSetting()), Qt::UniqueConnection);
//		QObject::connect(this, SIGNAL(sig_SettingSelect(CExBaseObject *)), g_pSettingSelectDlg, SLOT(slot_SelectModeData(CExBaseObject *)), Qt::UniqueConnection);
//		QObject::connect(this, SIGNAL(sig_SettingSelect(CString)), g_pSettingSelectDlg, SLOT(slot_SelectModeData(CString)), Qt::UniqueConnection);//20240730 huangliang
//	}
}

//20240802 huangliang 统一在函数Stt_Global_SettingParent中执行，删除此处代码
//void QSttTestCntrFrameWin::slot_ShowSetting()
//{
//	Stt_Global_SettingSelect(NULL);
////	OnCmd_SettingSelect();
//}
//
//void QSttTestCntrFrameWin::SettingSelect(CExBaseObject *pItem)
//{
//	emit sig_SettingSelect(pItem);
//}
//
//void QSttTestCntrFrameWin::SettingSelect(const CString &sValue)	//20240730 huangliang
//{
//	emit sig_SettingSelect(sValue);
//}


void QSttTestCntrFrameWin::SetWaveWidget(QWidget *pWidget)
{
	if (!pWidget)
	{
		return;
	}

	m_pWaveDrawWidget = pWidget;
}

void QSttTestCntrFrameWin::InitWaveDrawWidget()
{
	if (stt_Frame_TestMacroUI() == NULL)
	{
		return;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = stt_Frame_TestMacroUI();
	CString strMacroID = pTestMacroUI->m_strUI_ID;

	if (!HasWaveWidget(strMacroID))
	{
		if (m_pWaveDrawWidget)
		{
			int nIndex = m_tabTestTools->indexOf(m_pWaveDrawWidget);

			if (nIndex >= 0)
			{
				m_tabTestTools->removeTab(nIndex);
			}
		}
		m_pWaveDrawWidget = NULL;
	}
	else
	{
		if (m_pWaveDrawWidget)
		{
			int nIndex = m_tabTestTools->indexOf(m_pWaveDrawWidget);

			if (nIndex >= 0)
			{
				m_tabTestTools->removeTab(nIndex);
			}
		}
		m_pWaveDrawWidget = m_pMacroEditView->GetWaveWidget();
	}

}

void QSttTestCntrFrameWin::InitSystemDiagramWidget()
{
	if (stt_Frame_TestMacroUI() == NULL)
	{
		return;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = stt_Frame_TestMacroUI();
	CString strMacroID = pTestMacroUI->m_strUI_ID;

	if (!HasSystemDiagramWidget(strMacroID))
	{
		if (m_pSystemDiagramWidget)
		{
			int nIndex = m_tabTestTools->indexOf(m_pSystemDiagramWidget);

			if (nIndex >= 0)
			{
				m_tabTestTools->removeTab(nIndex);
			}
		}
		m_pSystemDiagramWidget = NULL;
	}
	else
	{
		if (m_pSystemDiagramWidget)
		{
			int nIndex = m_tabTestTools->indexOf(m_pSystemDiagramWidget);

			if (nIndex >= 0)
			{
				m_tabTestTools->removeTab(nIndex);
			}
		}
		m_pSystemDiagramWidget = m_pMacroEditView->GetSystemDiagramWidget();
	}

}

void QSttTestCntrFrameWin::InitWiringDiagramWidget(QWidget* pParent)
{
	QSttTestCntrFrameBase::InitWiringDiagramWidget(pParent);

	if (stt_Frame_TestMacroUI() == NULL)
	{
		return;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = stt_Frame_TestMacroUI();
	CString strMacroID = pTestMacroUI->m_strUI_ID;

	if (!HasWiringDiagramWidget(strMacroID))
	{
		if (m_pWiringDiagramWidget)
		{
			int nIndex = m_tabTestTools->indexOf(m_pWiringDiagramWidget);

			if (nIndex >= 0)
			{
				m_tabTestTools->removeTab(nIndex);
			}
		}
		m_pWiringDiagramWidget = NULL;
	}
	else
	{
		if (m_pWiringDiagramWidget)
		{
			int nIndex = m_tabTestTools->indexOf(m_pWiringDiagramWidget);

			if (nIndex >= 0)
			{
				m_tabTestTools->removeTab(nIndex);
				
			}
		}
		m_pWiringDiagramWidget = m_pMacroEditView->GetWiringDiagramWidget();//add wangtao 20240823 获取具体模块接线图
//		m_pWiringDiagramWidget->GetWiringDiagramName(pTestMacroUI->m_strUI_ID);
		
	}
}

void QSttTestCntrFrameWin::OnCmd_IecCap(long nPkgDetectType)
{
#ifdef use_CSmartCapCtrl
    m_pSttIecRecordMainWidget->SetIecCapWriteFile(false);
	InitSttIecRecord();
	CXSttCap_61850 *pXSttCap_61850 = CXSmartCapMngr::GetSttCap61850_Global();

	if (pXSttCap_61850 == NULL)
	{
		return;
	}

	if ((pXSttCap_61850->m_oCapDeviceAll.GetCount() == 0)&&(g_bSmartCap_RecordNow))//20220610 第一次进入的时,不用开启录波,在进入监视界面时,启动录波
	{
		g_bSmartCap_RecordNow = 0;
	}

	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();

	if(strIDMacroUI == STT_ORG_MACRO_MUAccuracyTest || strIDMacroUI == STT_ORG_MACRO_MUFirstCycleTest
		|| strIDMacroUI == STT_ORG_MACRO_MUAccurAutoTest|| strIDMacroUI == STT_ORG_MACRO_MUAutoTest)
	{
		long nTabIndex = m_tabTestTools->indexOf(m_pSttIecRecordMainWidget);

		if (nTabIndex == -1)//2023.7.3 在合并单元测试相关模块,固定显示报文探测界面
		{
			OnMenuClickedAction_Tools(m_pSttIecRecordMainWidget, "报文探测");
		}
	}
	else
	{
		OnMenuClickedAction_Tools(m_pSttIecRecordMainWidget, "报文探测");
	}


	//	SetActiveWidget(m_pSttIecRecordMainWidget, ActiveWidgetType_Other);

	if (g_oSystemParas.m_nIecFormatMeas != STT_IEC_FORMAT_61850_92)
	{
		//20240821 suyang 进入报文探测时根据系统参数中选择的类型区别FT3
		nPkgDetectType = 3;
	}

// 	if ((stt_Frame_TestMacroUI() != NULL)&&(g_theSttIecRecordMainWidget != NULL))
// 	{
// 		g_theSttIecRecordMainWidget->InitIecRecordCbWidget(stt_Frame_TestMacroUI()->m_strID,nPkgDetectType);
// 	}
	if (g_theSttIecRecordMainWidget != NULL)
	{
		if (g_pTheSttTestApp->m_pTestMacroUI != NULL)
		{
			g_theSttIecRecordMainWidget->InitIecRecordCbWidget(g_pTheSttTestApp->m_pTestMacroUI->m_strID,/*-1*/nPkgDetectType);
		}
		g_theSttIecRecordMainWidget->UpdateIecDetectType(nPkgDetectType);//更新勾选状态
	}
#endif
}

void QSttTestCntrFrameWin::OnCmd_IecCap()
{
	OnCmd_IecCap(-1);
}

void QSttTestCntrFrameWin::OnMacroTest(CSttMacroTestUI_TestMacroUI* pTestMacroUI)
{
	if (pTestMacroUI == NULL)
	{
		return;
	}

	if (!m_bIsAutoTest)
	{
		setWindowTitle(pTestMacroUI->m_strName);
	}

	OpenMacroTestUI_NoCmd(pTestMacroUI, "", "");
	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib());
// 	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
// 	{
// 		ShowCharEditTab();
// 	}
// 	else
// 	{
// 		HideCharEditTab();
// 	}
}

void QSttTestCntrFrameWin::UpdateButtonStateByID( const CString &strID,bool bState,bool bShow )
{
	if ((m_pManualTriggerBtn != NULL)&&(m_pManualTriggerBtn->m_strID == strID))
	{
		QSttToolButtonBase *pButtonUI = (QSttToolButtonBase*)m_pManualTriggerBtn->m_dwItemData;

		if (pButtonUI != NULL)
		{
			pButtonUI->m_bShow = bShow;
			pButtonUI->setEnabled(bState);
			pButtonUI->setVisible(bShow);
		}
		return;
	}

	if (m_pToolBarWin != NULL)
	{
		QSttToolButtonBase* pButton = NULL;

		for(int i = 0; i<m_pToolBarWin->m_listToolBtn.size();i++)
		{
			pButton = m_pToolBarWin->m_listToolBtn.at(i);

			if (pButton->m_pCfgData->m_strID == strID)
			{
				pButton->setDisabled(!bState);
				pButton->m_bShow = bShow;
				break;
			}
		}
	}

 	if (m_pMenuBar != NULL)
 	{
		QSttAction *pSttAction = NULL;

 		for(int i = 0; i < m_pMenuBar->m_listAct.size(); i++)
 		{
 			pSttAction = m_pMenuBar->m_listAct.at(i);

 			if (pSttAction->m_pCfgData->m_strID == strID)
 			{
				//2024-8-9 wuxinyi 按照传参设置，应是设置是否使能
				//pSttAction->setDisabled(bState);
				pSttAction->setEnabled(bState);
 				pSttAction->setVisible(bShow);
 				break;
 			}
 		}
 	}
}

void QSttTestCntrFrameWin::UpdateCharacterEditButtonState(bool bState, bool bShow, bool bUseCurrMacroUI)
{
	CSttFrame_Button *pSttFrame_Button = GetCharactEditBtn();

	if (pSttFrame_Button == NULL)
	{
		return;
	}

	QSttToolButtonBase *pButtonUI = (QSttToolButtonBase*)pSttFrame_Button->m_dwItemData;

	if (pButtonUI == NULL)
	{
		return;
	}

	if (bUseCurrMacroUI)
	{
		CSttMacroTestUI_TestMacroUI* pTestMacroUI = stt_Frame_TestMacroUI();

		if (pTestMacroUI != NULL)
		{
			bState = (pTestMacroUI->HasCharLib() && pTestMacroUI->IsInternationalMode());
			bShow = bState;
		}
		else
		{
			bState = false;
			bShow = false;
		}
	} 

	pButtonUI->setEnabled(bState);
	pButtonUI->setVisible(bShow);
}

void QSttTestCntrFrameWin::OnAutoTest(QStringList strings)
{
	//与主界面传递的参数值有关【QSttWinAutoTestWidget::slot_btnOK_Clicked】
	CString strGbFile;
	BOOL bRet = FALSE;
	CString strType = strings[0];
	if (strType == ARGV_CMD_ID_NEWTEST)
	{
		g_theGbSmartGenWzd->InitCreateParas_Device();

		g_theGbSmartGenWzd->m_strDevIP = strings[1];
		g_theGbSmartGenWzd->m_nDevPort = CString_To_long(strings[2]);
		g_theGbSmartGenWzd->m_strDeviceType = strings[3];
		g_theGbSmartGenWzd->m_strEngineProgID = strings[4];
		g_theGbSmartGenWzd->m_strDvmFile = strings[5];
		g_theGbSmartGenWzd->m_strPpFile = strings[6];
		g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms = CString_To_long(strings[7]);

		g_theGbSmartGenWzd->CreateNew();
		CDataGroup *pDevice = g_theGbSmartGenWzd->m_pDevice;
		CDataGroup *pTestApp = g_theGbSmartGenWzd->m_pTestApp;
		CDataGroup *pCommConfig = &g_theGbSmartGenWzd->m_oCommConfig;

		//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
		m_pSttGbTreeView->m_pCurrSelRootNode = NULL;
		m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
		g_pTheSttTestApp->m_pTestCtrlCntr->NewTest(pDevice, pTestApp, pCommConfig);

		CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
		CString strName = GetFileTitleFromFilePath(g_theGbSmartGenWzd->m_strDvmFile, '/');
		pGuideBook->SetGuideBookName(strName);
		m_pSttGbTreeView->show();
		disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
		m_pSttGbTreeView->ShowBaseList((CExBaseList *)pGuideBook);
		connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
		pGuideBook->AddTimeSettingCoef(g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms);

		UpdateToolButtons_AfterNew();

		m_tabTestTools->clear();
		m_tabTestTools->hide();
		m_tabTestViews->clear();

		CreateEngineClientWidget();
		return;
	}
	else if(ARGV_CMD_ID_OPENGBRPT)
	{
		CString strGbFile = _P_GetTemplatePath();
		strGbFile += strings[1];
		m_pSttGbTreeView->show();

		CString strWzdxml = ChangeFilePostfix(strGbFile, GbSmartGenWzd_File_Postfix);
		g_theGbSmartGenWzd->OpenSmartGenWzdFile(strWzdxml);

		bRet = OpenTemplate(strGbFile, g_theGbSmartGenWzd->m_strDvmFile);
		ExpandRootNode();
	}
	else if(ARGV_CMD_ID_OPENGBXML)
	{
		CString strGbFile = _P_GetTemplatePath();
		strGbFile += strings[1];
		ClearSmartGenWzd();
		m_pSttGbTreeView->show();

		CString strWzdxml = ChangeFilePostfix(strGbFile, GbSmartGenWzd_File_Postfix);
		g_theGbSmartGenWzd->OpenSmartGenWzdFile(strWzdxml);

		bRet = OpenTest(strGbFile, g_theGbSmartGenWzd->m_strDvmFile);
		ExpandRootNode();
	}

	if (!bRet)
	{
		m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
		//删除之前的tab
		if (m_pMacroEditView != NULL)
		{
			QWidget *pMacroEditWidget = NULL;
			long nTabIndex = 0;
			pMacroEditWidget = GetMacroEditWidget();
			nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
			m_tabTestViews->removeTab(nTabIndex);
		}

		SetActiveWidget(NULL);
		g_pTheSttTestApp->SetCurrTestMacroUI(NULL);
		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
		return;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->AddTimeSettingCoef(g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms);  //打开模板时，也要设置时间定值比例系数
	//打开模板后，设置相关的通讯参数
	CreateEngineClientWidget();

	//打开模板后初始化各界面和菜单
	UpdateToolButtons_AfterAddMacro();
	SelectActionByID(STT_CNTR_CMD_TemplateView, TRUE);
	SelectActionByID(STT_CNTR_CMD_VectorDrawView, TRUE);
	SelectActionByID(STT_CNTR_CMD_InfoView, TRUE);

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(m_pSttGbTreeView->m_pCurrSelRootNode->m_strstxmlFile);

	if (pTestMacroUI == NULL)
	{
		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
		return;
	}

	//特性曲线
	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib());
// 	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
// 	{
// 		ShowCharEditTab();
// 	}
// 	else
// 	{
// 		HideCharEditTab();
// 	}

	CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
}

CString QSttTestCntrFrameWin::OpenSclFileDlg(BOOL bIsOpen)
{
	CString strText = _T("SCL文件路径");
	QFileDialog dlg(this, strText);
	dlg.setFileMode(QFileDialog::AnyFile);
	//strText = _T("SCD文件(*.scd);;ICD文件(*.icd);;CID文件(*.cid)");
	strText = _T("SCL文件(*.scd *.icd *.cid)");
	dlg.setNameFilter(strText);

	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetLibraryPath();
	dlg.setDirectory(strPath);
	strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType, strText);
	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		strText = _T("打开");
		dlg.setLabelText(QFileDialog::Accept, strText);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		strText = _T("保存");
		dlg.setLabelText(QFileDialog::Accept, strText);	
	}
	strText = _T("取消");
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strFileName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
	}

	return strFileName;
}

CString QSttTestCntrFrameWin::OpenDvmFileDlg(const CString &strFileName, BOOL bIsOpen)
{
	CString strText = _T("模型文件路径");
	QFileDialog dlg(this, strText, strFileName);
	dlg.setFileMode(QFileDialog::AnyFile);
	strText = _T("模型文件 (*.xml)");
	dlg.setNameFilter(strText);
	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol\\Library\\");
	dlg.setDirectory(strPath);
	strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType, strText);
	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		strText = _T("打开");
		dlg.setLabelText(QFileDialog::Accept, strText);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		strText = _T("保存");
		dlg.setLabelText(QFileDialog::Accept, strText);	
	}
	strText = _T("取消");
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strName = fileNames.at(0);
	}

	return strName;
}

CString QSttTestCntrFrameWin::OpenTemplateDlg(BOOL bIsOpen)
{
	CString strText = _T("模板路径");
	QFileDialog dlg(this, strText);
	dlg.setFileMode(QFileDialog::AnyFile);
	strText = _T("模板文件 (*.gbxml)");
	dlg.setNameFilter(strText);
	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetTemplatePath();
	dlg.setDirectory(strPath);
	strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType, strText);
	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		strText = _T("打开");
		dlg.setLabelText(QFileDialog::Accept, strText);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		strText = _T("保存");
		dlg.setLabelText(QFileDialog::Accept, strText);	
	}
	strText = _T("取消");
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strFileName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("[strPath%s][strFileName=%s]."),strPath.GetString(),strFileName.GetString());
	}
	
	return strFileName;
}

CString QSttTestCntrFrameWin::OpenTestDlg(BOOL bIsOpen)
{
	CString strText = _T("测试记录文件路径");
	QFileDialog dlg(this, strText);
	dlg.setFileMode(QFileDialog::AnyFile);
	strText = _T("测试记录文件 (*.gbrpt)");
	dlg.setNameFilter(strText);
	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetWorkspacePath();
	dlg.setDirectory(strPath);
	strText = _T("文件路径");
	dlg.setLabelText(QFileDialog::LookIn, strText);
	strText = _T("文件名");
	dlg.setLabelText(QFileDialog::FileName, strText);
	strText = _T("文件类型");
	dlg.setLabelText(QFileDialog::FileType, strText);
	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		strText = _T("打开");
		dlg.setLabelText(QFileDialog::Accept, strText);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		strText = _T("保存");
		dlg.setLabelText(QFileDialog::Accept, strText);	
	}
	strText = _T("取消");
	dlg.setLabelText(QFileDialog::Reject, strText);

	CString strFileName;
	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
	}

	return strFileName;
}

CString QSttTestCntrFrameWin::OpenPpxmlFileDlg(BOOL bIsOpen)
{
	CString strPpxmlPath, strPpxmlFilter, strFilePath, 
		strFileName, strFileType, strOpen, strSave, strCancel;
	xlang_GetLangStrByFile(strPpxmlPath, "Win_PpxmlPath");
	xlang_GetLangStrByFile(strPpxmlFilter, "Win_PpxmlFilter");
	xlang_GetLangStrByFile(strFilePath, "Native_FilePath");
	xlang_GetLangStrByFile(strFileName, "Native_FileName");
	xlang_GetLangStrByFile(strFileType, "Native_FileType");
	xlang_GetLangStrByFile(strOpen, "Native_Open");
	xlang_GetLangStrByFile(strSave, "Native_Save");
	xlang_GetLangStrByFile(strCancel, "Native_Cancel");

	QFileDialog dlg(this, strPpxmlPath);
	dlg.setFileMode(QFileDialog::AnyFile);
	dlg.setNameFilter(strPpxmlFilter);
	dlg.setViewMode(QFileDialog::Detail);
	dlg.setAcceptMode(QFileDialog::AcceptOpen);
	CString strPath = _P_GetInstallPath();
	strPath += _T("e-Protocol/Template");
	dlg.setDirectory(strPath);
	dlg.setLabelText(QFileDialog::LookIn, strFilePath);
	dlg.setLabelText(QFileDialog::FileName, strFileName);
	dlg.setLabelText(QFileDialog::FileType, strFileType);
	if(bIsOpen)
	{
		dlg.setAcceptMode(QFileDialog::AcceptOpen);
		dlg.setLabelText(QFileDialog::Accept, strOpen);
	}
	else
	{
		dlg.setAcceptMode(QFileDialog::AcceptSave);
		dlg.setLabelText(QFileDialog::Accept, strSave);	
	}
	dlg.setLabelText(QFileDialog::Reject, strCancel);

	QStringList fileNames;
	if (dlg.exec() == QFileDialog::Accepted)
	{
		fileNames = dlg.selectedFiles();
		strFileName = fileNames.at(0);
	}

	return strFileName;
}

void QSttTestCntrFrameWin::InitImportDvmFileDlg(CSttItems *pItems)
{
	if (pItems == NULL)
	{
		return;
	}

	if (pItems->GetCount() == 0)
	{
		return;
	}

	long nRet = 0;

	//通讯命令生成向导
	if (m_pSttImportDvmFileWidget == NULL)
	{
		m_pSttImportDvmFileWidget = new QSttImportDvmFileWidget(m_gFont, this);
		m_pSttImportDvmFileWidget->setParent(this);
		m_pSttImportDvmFileWidget->m_pItems = pItems;
		nRet = m_pSttImportDvmFileWidget->InitShow();
	}

	if (nRet)
	{
		m_pSttImportDvmFileWidget->show();
		connect(m_pSttImportDvmFileWidget, SIGNAL(sig_FreeImportDvmFileWidget()), this, SLOT(slot_OnFreeImportDvmFileWidget()));
	}
	else
	{
		slot_OnFreeImportDvmFileWidget();
	}
}

void QSttTestCntrFrameWin::FreeImportDvmFileDlg()
{
	if (m_pSttImportDvmFileWidget != NULL)
	{
		disconnect(m_pSttImportDvmFileWidget, SIGNAL(sig_FreeImportDvmFileWidget()), this, SLOT(slot_OnFreeImportDvmFileWidget()));

		m_pSttImportDvmFileWidget->close();
		delete m_pSttImportDvmFileWidget;
		m_pSttImportDvmFileWidget = NULL;
	}
}

void QSttTestCntrFrameWin::OnCmd_OpenTemplate()
{
	m_tagAppState = APPSTATE_OPENTEMPLATE;
	CString strFile = OpenTemplateDlg();
 
 	if (strFile.GetLength() < 5)
 	{
 		m_tagAppState = APPSTATE_NULL;
 		return;
 	}

	if (!IsAutoTest())//chenling20340423 非自动测试模式打开模板文件
	{
		SetAutoTest(TRUE);//2024-10-14 wuxinyi 非自动测试模块下打开模板，更新为自动测试，避免打开模版时出现模板有多个测试项
		//OpenTemplate(strFile, _T(""));
// 		return;
	}
 
 	if (m_pCmdWzdDsEditWidget != NULL)
 	{
 		//重新创建测试时，不进行参数保存
 		m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
 		m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
 		DeleteCmdWzdDsEditWidget();
 	}

	ClearSmartGenWzd();
	m_pSttGbTreeView->show();
	
	//2023-9-4 先打开wzdxml文件，防止模板是从别的地方拷贝过来的【认为拷贝模板时，会修改wzdxml中的模型文件路径】
	CString strWzdxml = ChangeFilePostfix(strFile, GbSmartGenWzd_File_Postfix);
	g_theGbSmartGenWzd->OpenSmartGenWzdFile(strWzdxml);

	BOOL bRet = OpenTemplate(strFile, g_theGbSmartGenWzd->m_strDvmFile);

	if ( !bRet)
	{
		m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
		//删除之前的tab
		if (m_pMacroEditView != NULL)
		{
			QWidget *pMacroEditWidget = NULL;
			long nTabIndex = 0;
			pMacroEditWidget = GetMacroEditWidget();
			nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
			m_tabTestViews->removeTab(nTabIndex);
		}

		SetActiveWidget(NULL);
		g_pTheSttTestApp->SetCurrTestMacroUI(NULL);
		m_tagAppState = APPSTATE_NULL;
		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
		return;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->AddTimeSettingCoef(g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms);  //打开模板时，也要设置时间定值比例系数
	//打开模板后，设置相关的通讯参数
	CreateEngineClientWidget();

	//打开模板后初始化各界面和菜单
	UpdateToolButtons_AfterAddMacro();
	SelectActionByID(STT_CNTR_CMD_TemplateView, TRUE);
	SelectActionByID(STT_CNTR_CMD_VectorDrawView, TRUE);
	SelectActionByID(STT_CNTR_CMD_InfoView, TRUE);

	//遥测参数映射
	InitAinDataMap(pGuideBook->m_pAinDataMapCfg);

	//打开模板后，默认显示第一个项目的参数页面
	//CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	//m_pSttGbTreeView->m_pCurrSelRootNode = pGuideBook->FindFirstItems(STTITEMS_NODETYPE_ROOTNODE, TRUE);

	//m_pSttGbTreeView->m_strCurrSelRootNodePath = m_pSttGbTreeView->m_pCurrSelRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	//CSttTestMacroUiParas *pUIParas = GetTestMacroUiParas(m_pSttGbTreeView->m_pCurrSelRootNode);
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(m_pSttGbTreeView->m_pCurrSelRootNode->m_strstxmlFile);

	if (pTestMacroUI == NULL)
	{
		m_tagAppState = APPSTATE_NULL;
		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
		return;
	}
// 
// 	CSttTestMacroCharParas *pSttTestMacroCharParas = (CSttTestMacroCharParas *)m_pSttGbTreeView->m_pCurrSelRootNode->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS);
// 	g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUI);
// 	g_pTheSttTestApp->m_pTestCtrlCntr->stt_OpenHdRsFile(pTestMacroUI->m_strHdRsFile);
// 	QSttTestCntrFrameBase::OpenMacroTestUI(pUIParas, pTestMacroUI,pSttTestMacroCharParas);

	//特性曲线
	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib());
// 	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
// 	{
// 		ShowCharEditTab();
// 	}
// 	else
// 	{
// 		HideCharEditTab();
// 	}

	ExpandRootNode();
	m_tagAppState = APPSTATE_NULL;
	CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
}

void QSttTestCntrFrameWin::OnCmd_SaveTemplate()
{	
	//先自动保存正在编辑的项目
	OnCmd_SaveEdit();

	if (m_pMacroEditView != NULL)
	{
		if (!IsAutoTest())//zhouhj 2023.7.13 非自动测试模式下,即单机模式,保存模板即保存缺省参数配置文件
		{
			CDataGroup oRetParas;

			if (stt_Frame_TestMacroUI()->IsUIWeb())
			{
				oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
			}
			else
			{
				if (stt_Frame_TestMacroUI()->IsInternationalMode())//2024-9-13 wuxinyi 国际版模板保存的是添加系列参数，只需保存m_oTestMacroUI_Paras
				{
					oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
				}
				else
				{
					m_pMacroEditView->GetDatas(&oRetParas);
				}
			}


			CString strPath = stt_ui_GetParasFile(stt_Frame_TestMacroUI()->m_strUI_ParaFile);
			oRetParas.SaveXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
			//SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing 记录和保存当前页面设置的值：设置为默认值

            QMessageBox::information(NULL, /*QObject::tr("提示")*/g_sLangTxt_Native_LangTip, g_sLangTxt_Native_FileSaveSuccess/*QObject::tr("文件保存成功！")*/);
			return;
		}

		if(IsTestStarted())
		{
			Ats_UpdateParameter();
		}
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();

	if (pGuideBook == NULL)
	{
		return;
	}

	if (IsAutoTest())
	{
		//自动测试模式下，直接另存为，不对原有模板进行覆盖
		OnCmd_SaveAsTemplate();
		return;
	}

	if (pGuideBook->m_strFile.GetLength() > 0)
	{
		pGuideBook->SaveFile();
		CString strFile = ChangeFilePostfix(pGuideBook->m_strFile, "html");

		CString strFilePath2 = _P_GetDBPath();
		strFilePath2 += _T("ui/");
		strFilePath2 += CXLanguageMngr::g_pXLanguageMngr->m_strCurrLanguage;
		strFilePath2 += _T("/");
		strFilePath2 += _T("SaveTemplate.html");
		//保存模板时，html中不需要保存报告数据。先存一个备份。
		m_pSttReportViewHtml->SaveHtmlReportFile(strFilePath2);
		ClearReportRslts_Html();
		m_pSttReportViewHtml->SaveHtmlReportFile(strFile);
		strFilePath2 = GetFileNameFromFilePath(strFilePath2);
		//重新打开保存的备份，这样“报告视图”中，还是有报告数据
		m_pSttReportViewHtml->InitReport(strFilePath2);

		SaveTemplate(pGuideBook->m_strFile);
	}
	else
	{
		OnCmd_SaveAsTemplate();
	}
}

void QSttTestCntrFrameWin::OnCmd_SaveAsTemplate()
{
	CString strFile,strFile2;
	strFile = OpenTemplateDlg(FALSE);
	if (strFile.GetLength() < 5)
	{
		return;
	}

	//先自动保存正在编辑的项目
	OnCmd_SaveEdit();

	if (m_pMacroEditView != NULL)
	{
		if (!IsAutoTest())//chenling 20240422 非自动测试模式下,模板另存为
		{
			if (strFile.isEmpty())
			{
				return;
			}
			if (strFile.Find(_T(".gbxml")) == -1)
			{
				strFile += _T(".gbxml");
			}

			BOOL bSaveTempRes = FALSE;
			CString strPath, strFileName;
			strPath = GetPathFromFilePathName(strFile);
			strFileName = GetPathFileNameFromFilePathName(strFile);

			//2024-10-17 wuxinyi 补充模板另存为存wzdxml，避免定值关联之后找不到模型文件
			CString strFile2;
			strFile2 = ChangeFilePostfix(strFile, GbSmartGenWzd_File_Postfix);
			g_theGbSmartGenWzd->SaveSmartGenWzdFile(strFile2);

			if (stt_Frame_TestMacroUI()->IsInternationalMode())
			{
				bSaveTempRes = m_pTestCtrlCntrBase->SaveTemplate(strPath, strFileName, NULL);
			}
			else
			{
			CDataGroup oRetParas;
			if (stt_Frame_TestMacroUI()->IsUIWeb())
			{
				oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
			}
			m_pMacroEditView->GetDatas(&oRetParas);
			SaveUIParaFile(&oRetParas);

				bSaveTempRes = m_pTestCtrlCntrBase->SaveTemplate(strPath, strFileName, &oRetParas);

			}

			if (bSaveTempRes)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("另存为模板(%s%s)成功."), strPath.GetString(), strFileName.GetString());

			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("另存为模板(%s%s)失败."), strPath.GetString(), strFileName.GetString());
			}
		}
	}
	

	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->m_strFile = strFile;
	strFile2 = ChangeFilePostfix(strFile, "html");

	if (m_pSttReportViewHtml != NULL)
	{
		CString strFilePath2 = _P_GetDBPath();
		strFilePath2 += _T("ui/");
		strFilePath2 += CXLanguageMngr::g_pXLanguageMngr->m_strCurrLanguage;
		strFilePath2 += _T("/");
		strFilePath2 += _T("SaveAsTemplate.html");
		//保存模板时，html中不需要保存报告数据。先存一个备份。
		m_pSttReportViewHtml->SaveHtmlReportFile(strFilePath2);
		ClearReportRslts_Html();
		m_pSttReportViewHtml->SaveHtmlReportFile(strFile2);
		strFilePath2 = GetFileNameFromFilePath(strFilePath2);
		m_pSttReportViewHtml->InitReport(strFilePath2);
	}
	
	if (IsAutoTest())
	{
		SaveTemplate(strFile2);
	}
}

void QSttTestCntrFrameWin::OnCmd_SaveTest()
{
/*  保存记录时，暂时不保存当前正在编辑的项目。因为保存编辑会导致项目重新生成，当前项目的测试状态及报告会丢失
	//先自动保存正在编辑的项目
	OnCmd_SaveEdit();

	if (m_pMacroEditView != NULL)
	{
		CDataGroup oRetParas;

		if (stt_Frame_TestMacroUI()->IsUIWeb())
		{
			oRetParas.AppendCloneEx(*m_pTestMacroUI_Paras);
		}

		m_pMacroEditView->GetDatas(&oRetParas);
		SaveUIParaFile(&oRetParas);	//2022-10-16  lijunqing 记录和保存当前页面设置的值：设置为默认值

		if(IsTestStarted())
		{
			Ats_UpdateParameter();
		}
	}
*/
	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();

	if (pGuideBook == NULL)
	{
		return;
	}

	if (IsAutoTest())
	{
		//自动测试模式下，直接另存为，不对原有记录进行覆盖
		OnCmd_SaveAsTest();
		return;
	}

	if (pGuideBook->m_strFile_Gbrpt.GetLength() > 0)
	{
		pGuideBook->SaveFile();
		CString strFile = ChangeFilePostfix(pGuideBook->m_strFile, "html");
		m_pSttReportViewHtml->SaveHtmlReportFile(strFile);
		SaveTest(pGuideBook->m_strFile_Gbrpt);
	}
	else
	{
		OnCmd_SaveAsTest();
	}
}

void QSttTestCntrFrameWin::OnCmd_SaveAsTest()
{
	CString strFile = OpenTestDlg(FALSE);
	if (strFile.GetLength() < 5)
	{
		return;
	}
/*  保存记录时，暂时不保存当前正在编辑的项目。因为保存编辑会导致项目重新生成，当前项目的测试状态及报告会丢失
	//先自动保存正在编辑的项目
	//先自动保存正在编辑的项目
	OnCmd_SaveEdit();
*/

	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->m_strFile_Gbrpt= strFile;

	strFile = ChangeFilePostfix(strFile, "html");
	m_pSttReportViewHtml->SaveHtmlReportFile(strFile);
	SaveTest(strFile);
}

void QSttTestCntrFrameWin::OnCmd_SaveAsRpt()
{
	if (m_pSttReportViewHtml == NULL)
	{
		return;
	}

//	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
// 	pGuideBook->m_strFile_Gbrpt= strFile;
// 
// 	strFile = ChangeFilePostfix(strFile, "html");
// 	m_pSttReportViewHtml->SaveHtmlReportFile(strFile);
// 	SaveTest(strFile);

    CString strRptPath = QFileDialog::getSaveFileName(this, g_sLangTxt_Native_ExportWordDoc/*tr("导出word文件")*/,
        QString(),g_sLangTxt_Native_DocType/*_T("Word97-2003报告(*.doc);;Word报告(*.docx);;HTML报告(*.html);;PDF报告(*.pdf)")*/ /*"报告文件(*.doc *.docx *.html)"*/);

	if (!strRptPath.IsEmpty()) 
	{  
		// 如果文件后缀为空，则默认使用.html
		if (QFileInfo(strRptPath).suffix().isEmpty())  
		{
			strRptPath.append(".doc");
		}

		//保存html
		CString strPostfix;
		strPostfix = ParseFilePostfix(strRptPath);

		if (strPostfix == _T("html"))
		{
			m_pSttReportViewHtml->SaveHtmlReportFile(strRptPath);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("网页报告(%s)保存成功."),strRptPath.GetString());
		} 
		else if (strPostfix == _T("pdf"))
		{
			if (m_pSttReportViewHtml->SavePdfReportFile(strRptPath))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("PDF报告文件(%s)保存成功."),strRptPath.GetString());
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("PDF报告文件(%s)保存失败."),strRptPath.GetString());
			}
		} 
		else
		{
			if (m_pSttReportViewHtml->SaveWordReportFile(strRptPath))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("WORD报告文件(%s)保存成功."),strRptPath.GetString());
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("WORD报告文件(%s)保存失败."),strRptPath.GetString());
			}
		}
	} 
}

void QSttTestCntrFrameWin::OnCmd_ExportWordRpt()
{
	if (IsProgramExist(_T("WINWORD.EXE")))
	{
		CString strMsg;
		strMsg = /*_T("检测到WINWORD.EXE进程正在运行，请先关闭进程后，再导出报告。\r\n点击“Yes”，关闭进程，继续导出。点击“No”，取消导出")*/g_sLangTxt_WinwordProcessWarning.GetString();
		CString strTitle;
		strTitle = /*_T("请关闭进程……")*/g_sLangTxt_CloseProcessWarning.GetString();
		int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

		if (result != QMessageBox::Yes)
		{
			return;
		}

		TerminateProgram(_T("WINWORD.EXE"));
	}

	CDataGroup oItemsTecs;
	CString *pszFilePath = new CString();
	*pszFilePath = _P_GetWorkspacePath();
	CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
	CDataGroup *pGrpGb = pGuideBook->GetItemsTec();

	if (pGrpGb != NULL)
	{
		//oItemsTecs.AppendCloneEx2(*pGrpGb, TRUE, TRUE);  //将模板中的配置，同步到临时对象
		//shaolei 2023-11-22 此处不能直接克隆。因为模板中的对象为CDvmData。实际配置的类型为CRptTemp_Data。
		AppendItemsTecFromGuideBook(pGrpGb, &oItemsTecs);
	}

	QSttExportWordReport dlg(pGuideBook, *g_pSttGlobalFont, this);
	dlg.Init(&oItemsTecs, pszFilePath);

	if ( dlg.exec() == QDialog::Rejected)
	{
		return;
	}

	if (pGrpGb == NULL)
	{
		pGuideBook->SetItemsTec(&oItemsTecs);
	}
	else
	{
		pGrpGb->InitDataValues(&oItemsTecs, TRUE);  //编辑结束后，更新到模板
	}

 	ExportWordRpt(*pszFilePath, &oItemsTecs);
}

void QSttTestCntrFrameWin::OnCmd_OpenTest()
{
	CString strFile = OpenTestDlg();

	if (strFile.GetLength() < 5)
	{
		return;
	}

	if (m_pCmdWzdDsEditWidget != NULL)
	{
		//重新创建测试时，不进行参数保存
		m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
		m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
		DeleteCmdWzdDsEditWidget();
	}

	ClearSmartGenWzd();
	m_pSttGbTreeView->show();

	//2023-9-4 先打开wzdxml文件，防止模板是从别的地方拷贝过来的【认为拷贝模板时，会修改wzdxml中的模型文件路径】
	CString strWzdxml = ChangeFilePostfix(strFile, GbSmartGenWzd_File_Postfix);
	g_theGbSmartGenWzd->OpenSmartGenWzdFile(strWzdxml);

	BOOL bRet = OpenTest(strFile, g_theGbSmartGenWzd->m_strDvmFile);

	if ( !bRet)
	{
		m_pSttGbTreeView->m_strCurrSelRootNodePath = _T("");
		//删除之前的tab
		if (m_pMacroEditView != NULL)
		{
			QWidget *pMacroEditWidget = NULL;
			long nTabIndex = 0;
			pMacroEditWidget = GetMacroEditWidget();
			nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
			m_tabTestViews->removeTab(nTabIndex);
		}

		SetActiveWidget(NULL);
		g_pTheSttTestApp->SetCurrTestMacroUI(NULL);
		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
		return;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->AddTimeSettingCoef(g_theGbSmartGenWzd->m_nIsTimeSetsUnit_ms);  //打开模板时，也要设置时间定值比例系数
	//打开模板后，设置相关的通讯参数
	CreateEngineClientWidget();

	//遥测参数映射
	InitAinDataMap(pGuideBook->m_pAinDataMapCfg);

	//打开模板后初始化各界面和菜单
	UpdateToolButtons_AfterAddMacro();
	SelectActionByID(STT_CNTR_CMD_TemplateView, TRUE);
	SelectActionByID(STT_CNTR_CMD_VectorDrawView, TRUE);
	SelectActionByID(STT_CNTR_CMD_InfoView, TRUE);

    if(m_pSttGbTreeView->m_pCurrSelRootNode == NULL)
    {
        return;
    }

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(m_pSttGbTreeView->m_pCurrSelRootNode->m_strstxmlFile);

	if (pTestMacroUI == NULL)
	{
		CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
		return;
	}

	//特性曲线
	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib());
// 	if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
// 	{
// 		ShowCharEditTab();
// 	}
// 	else
// 	{
// 		HideCharEditTab();
// 	}

	ExpandRootNode();
	CheckDvmFileValid(g_theGbSmartGenWzd->m_strDvmFile);
}

void QSttTestCntrFrameWin::OnCmd_AddMacro(BOOL bUseNameID)
{
	if (!CanAddTestMacroUI())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("请在测试项目树形控件中选择合法的项目分类"));
		return;
	}

	//优化后的选择功能框
	QTestMacroToolDlg dlg(m_gFont,this);
	dlg.m_pCurrentSelGbItem = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();
	if (dlg.exec() != 1)
	{
		return;
	}

	CString strItemPath = m_pSttGbTreeView->m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	if(dlg.m_pCurrentSelTest->GetClassID() == MNGRCLASSID_CCOMMCMDREF)
	{
		OnNew_CommCmd(strItemPath, dlg.m_strItemsID);
		return;
	}
	else if (dlg.m_strItemsID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		OnNew_ChMapsConfig(strItemPath);
		return;
	}
	else if (dlg.m_strItemsID == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		OnNew_SystemConfig(strItemPath);
		return;
	}
	else if (dlg.m_strItemsID == STT_CMD_TYPE_SYSTEM_IECConfig)
	{
		OnNew_IECConfig(strItemPath);
		return;
	}
	
	OnCmd_SaveEdit();

	UpdateToolButtons_AfterAddMacro();

	g_pTheSttTestApp->SetCurrTestMacroUI(dlg.GetCurSelTestID());
	OpenMacroTestUI(stt_Frame_TestMacroUI(), dlg.m_strItemsName, dlg.m_strItemsID
		, dlg.m_nRepeatTimes, dlg.m_nRptTitle, dlg.m_nTitleLevel);

	EndBinStateOnStarting();
	UpdateToolButtons();
	UpdateStartStopButtonByItemCount();
// 

/*
 	QSttAddMacroWidget dlg(m_gFont,this);
 	dlg.Use_Name_ID(bUseNameID);
 	dlg.m_pCurrentSelGbItem = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();
 	if (dlg.exec() != 1)
 	{
 		return;
 	}

	//先自动保存正在编辑的项目
	OnCmd_SaveEdit();

	UpdateToolButtons_AfterAddMacro();
	slot_SelectTestMacro(dlg.m_pCurrUIRef, dlg.m_strItemsName, dlg.m_strItemsID);
*/
	CGbMacroGenWzd *pMacroGenWzd = new CGbMacroGenWzd;
	CString strParentItemsID;
	CExBaseObject *pSel = m_pSttGbTreeView->GetCurrSelectGbItem();
	strParentItemsID = pSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	pMacroGenWzd->m_strParentItemsID = strParentItemsID;
	pMacroGenWzd->m_strItemsID = dlg.m_strItemsID;
	pMacroGenWzd->m_strItemsName = dlg.m_strItemsName;
	g_theGbSmartGenWzd->AddNewChild(pMacroGenWzd);

	//m_pSttGbTreeView->m_pCurrSelRootNode->m_nRepeatTimes = dlg.m_nRepeatTimes;
	pMacroGenWzd->m_nRepeatTimes = dlg.m_nRepeatTimes;
	pMacroGenWzd->m_nRptTitle = dlg.m_nRptTitle;
	pMacroGenWzd->m_nTitleLevel = dlg.m_nTitleLevel;

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = stt_Frame_TestMacroUI();

	//测试功能属性
	CDataGroup *pMacroUIAttrs = pMacroGenWzd->GetMacroUIAttrs();
	pTestMacroUI->GetTestMacroUIDataGroup(pMacroUIAttrs);

	//测试功能参数
	CDataGroup *pUIParas = pMacroGenWzd->GetMacroUIParas();
	pUIParas->DeleteAll();
	pUIParas->AppendCloneEx(*m_pTestMacroUI_Paras);

	//特性曲线
    if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
	{
		CDvmContents *pChar = pMacroGenWzd->GetCharacteristic();
        m_pCharacteristics->GetXml(CCharacteristicXmlRWKeys::g_pXmlKeys, pChar->m_strText);
//		ShowCharEditTab();
	}
// 	else
// 	{
// 		HideCharEditTab();
// 	}

	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib());

	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

//2022-9-21  lijunqng
void QSttTestCntrFrameWin::SaveTemplate(const CString &strFile,long nSynMode)
{
	//2022-9-21  lijunqing
	CString strFile2;
	strFile2 = ChangeFilePostfix(strFile, GbSmartGenWzd_File_Postfix);
	g_theGbSmartGenWzd->SaveSmartGenWzdFile(strFile2);

	//2022-9-19  lijunqing 
	strFile2 = ChangeFilePostfix(strFile, g_strGbFileFilter);
	CString strPath,strFileName;
	strPath = GetPathFromFilePathName(strFile2);
	strFileName = GetPathFileNameFromFilePathName(strFile2);

// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("QSttTestCntrFrameWin::SaveTemplate[strPath=%s][strFileName=%s][strFile2=%s].")
// 		,strPath.GetString(),strFileName.GetString(),strFile2.GetString());


	m_pTestCtrlCntrBase->SaveTemplate(strPath, strFileName, NULL, nSynMode);

// 	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
// 
// 	if (pGuideBook == NULL)
// 	{
// 		return;
// 	}
// 
// 	strFile2 = ChangeFilePostfix(strFile, "dscxml");
// 	pGuideBook->SaveXmlFile(strFile2, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void QSttTestCntrFrameWin::SaveTest(const CString &strFile,long nSynMode)
{
	CString strFile2 = ChangeFilePostfix(strFile, GbSmartGenWzd_File_Postfix);
	g_theGbSmartGenWzd->SaveSmartGenWzdFile(strFile2);

	strFile2 = ChangeFilePostfix(strFile, "gbrpt");
	CString strPath = GetPathFromFilePathName(strFile2);
	CString strFileName = GetPathFileNameFromFilePathName(strFile2);
	m_pTestCtrlCntrBase->SaveTest(strPath, strFileName, NULL, nSynMode);

// 	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
// 
// 	if (pGuideBook == NULL)
// 	{
// 		return;
// 	}
// 
// 	strFile2 = ChangeFilePostfix(strFile, "dscxml");
// 	pGuideBook->SaveXmlFile(strFile2, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void QSttTestCntrFrameWin::ExportWordRpt(const CString &strFile, CDataGroup *pParas)
{
	CString strPath = GetPathFromFilePathName(strFile);
	CString strFileName = GetPathFileNameFromFilePathName(strFile);
	CDataGroup oParas;
	CString strSrcFile;
	strSrcFile = _P_GetLibraryPath();
	strSrcFile += _T("DOC_FILE_TEMPLATE_EMPTY.doc");
	oParas.AddNewData(XPARA_ID_Src_Path, strSrcFile);

	if (pParas != NULL)
	{
		CDataGroup *pItemsTec = new CDataGroup();
		pItemsTec->m_strID = STT_CMD_PARA_items_tecs;
		pItemsTec->m_strDataType = STT_CMD_PARA_items_tecs;
		oParas.AddNewChild(pItemsTec);
		pItemsTec->AppendEx(*pParas);
		pParas->RemoveAll();
	}

	m_pTestCtrlCntrBase->ExportWordRpt(strPath, strFileName, &oParas);
}

////将模板中的配置，同步到临时对象pDestGrp。pSrcGrp为模板中已经存在的配置对象
void QSttTestCntrFrameWin::AppendItemsTecFromGuideBook(CDataGroup *pSrcGrp, CDataGroup *pDestGrp)
{
	POS pos = pSrcGrp->GetHeadPosition();

	while (pos != NULL)
	{
		CDataGroup *pSrcTec = (CDataGroup *)pSrcGrp->GetNext(pos);
		CRptTemp_Group *pNewGrp = new CRptTemp_Group();
		pSrcTec->CopyOwn(pNewGrp);
		pDestGrp->AddNewChild(pNewGrp);

		POS posData = pSrcTec->GetHeadPosition();

		while (posData != NULL)
		{
			CDvmData *pSrcData = (CDvmData *)pSrcTec->GetNext(posData);
			CRptTemp_Data *pNewData = new CRptTemp_Data();
			pSrcData->CopyOwn(pNewData);
			pNewGrp->AddNewChild(pNewData);
			pNewData->AppendCloneEx(*pSrcData, TRUE);
		}
	}
}

void QSttTestCntrFrameWin::DeleteCmdWzdDsEditWidget()
{
	if (m_pCmdWzdDsEditWidget == NULL)
	{
		return;
	}

	int nIndex = m_tabTestViews->indexOf(m_pCmdWzdDsEditWidget);
	m_tabTestViews->removeTab(nIndex);
	delete m_pCmdWzdDsEditWidget;
	m_pCmdWzdDsEditWidget = NULL;
}

void QSttTestCntrFrameWin::OnDeleteCurr(CExBaseObject *pCurrObj)
{
	UINT nClassID = pCurrObj->GetClassID();

	if (nClassID == STTGBXMLCLASSID_CSTTCOMMCMD)
	{
		OnDeleteCurr_CommCmd((CSttCommCmd *)pCurrObj);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
	{
		OnDeleteCurr_Items((CSttItems *)pCurrObj);
	}
	else if (nClassID == STTGBXMLCLASSID_CSTTMACROTEST)
	{
		OnDeleteCurr_MacroTest((CSttMacroTest *)pCurrObj);
	}

	//删除项目后检查当前剩余测试项数量
// 	CSttDevice *pDevice = ((CSttTestCtrlCntrWin*)m_pTestCtrlCntrBase)->m_pSttGuideBook->GetDevice();
// 	if(pDevice && pDevice->GetCount() == 1)
// 	{
// 		UpdateToolButtons_AfterNew();
// 	}
}

void QSttTestCntrFrameWin::OnDeleteCurr_CommCmd(CSttCommCmd *pCommCmd)
{
	if (m_pCmdWzdDsEditWidget == NULL)
	{
		return;
	}

	if (m_pCmdWzdDsEditWidget->m_pCurrCmdItem != pCommCmd)
	{
		return;
	}

	//删除项目时，不进行参数保存
	m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
	m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
	DeleteCmdWzdDsEditWidget();
}

void QSttTestCntrFrameWin::OnDeleteCurr_Items(CSttItems *pItems)
{
	//判断当前打开的通讯命令编辑页面的项目，是否在被删除项目中。若是，则自动关闭编辑页面
	if (m_pCmdWzdDsEditWidget != NULL)
	{
		if (pItems->IsChildItemExist(m_pCmdWzdDsEditWidget->m_pCurrCmdItem))
		{
			//删除项目时，不进行参数保存
			m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
			m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
			DeleteCmdWzdDsEditWidget();
		}
	}

	if (m_pMacroEditView != NULL)
	{
		if (m_pMacroEditView->IsInternationalMode())
		{
			QSttMultiMacroParaEditViewBase *pSttMultiMacroParaEditViewBase = (QSttMultiMacroParaEditViewBase*)m_pMacroEditView;
			CSttItems *pMulitMacroRootItems = pSttMultiMacroParaEditViewBase->Get_MulitMacroRootItems();

			if ((pItems == pMulitMacroRootItems)||(pItems->IsChildItemExist(pMulitMacroRootItems)))
			{
				pSttMultiMacroParaEditViewBase->InitDatas(NULL);
			}
		}
	}

	CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(pItems, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pRootItems != NULL)
	{
		if (m_pMacroEditView != NULL)
		{
			if (m_pMacroEditView->m_pSttItems == pRootItems)
			{
				QWidget *pMacroEditWidget = NULL;
				long nTabIndex = 0;

				pMacroEditWidget = GetMacroEditWidget();
				nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
				m_tabTestViews->removeTab(nTabIndex);
			}
		}
	}
}

void QSttTestCntrFrameWin::OnDeleteCurr_MacroTest(CSttMacroTest *pMacroTest)
{
	if (pMacroTest->m_strID == STT_ORG_MACRO_Iec61850Config
		|| pMacroTest->m_strID == STT_ORG_MACRO_SystemConfig
		|| pMacroTest->m_strID == STT_ORG_MACRO_ChMapsConfig)
	{
		return;
	}

	//判断当前打开的通讯命令编辑页面的项目，是否在被删除项目中。若是，则自动关闭编辑页面
	if (m_pCmdWzdDsEditWidget != NULL)
	{
		if (pMacroTest->IsChildItemExist(m_pCmdWzdDsEditWidget->m_pCurrCmdItem))
		{
			//删除项目时，不进行参数保存
			m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
			m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
			DeleteCmdWzdDsEditWidget();
		}
	}

	CSttItems *pRootItems = (CSttItems *)Stt_GetFirstParentItems(pMacroTest, GBITEMS_NODETYPE_ROOTNODE, TRUE);

	if (pRootItems != NULL)
	{
		if (m_pMacroEditView != NULL)
		{
			if (m_pMacroEditView->m_pSttItems == pRootItems)
			{
				QWidget *pMacroEditWidget = NULL;
				long nTabIndex = 0;

				pMacroEditWidget = GetMacroEditWidget();
				nTabIndex = m_tabTestViews->indexOf(pMacroEditWidget);
				m_tabTestViews->removeTab(nTabIndex);
			}
		}
	}
}

BOOL QSttTestCntrFrameWin::Ats_UpdateAllMacroItem_InternationalMode(CSttItemBase *pParentSttItems)
{
	if (pParentSttItems == NULL)
	{
		return FALSE;
	}

	BOOL bIsTypeRootNode = FALSE;

	if (pParentSttItems->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pSttItems_Parent = (CSttItems*)pParentSttItems;
		bIsTypeRootNode = pSttItems_Parent->IsTypeRootNode();

		if (bIsTypeRootNode && CurrCharTestObjectHasChanged())
		{
			long nRet = m_pTestCtrlCntrBase->Ats_UpdateCharacteristic(pSttItems_Parent);

			if ((nRet != STT_CMD_ExecStatus_SUCCESS) && (nRet <= 4))	//模板生成完成
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("特性曲线更新失败."));
			}
			else
			{
				QSttMultiMacroParaEditViewBase *pSttMultiMacroParaEditViewBase = (QSttMultiMacroParaEditViewBase*)m_pMacroEditView->m_pMacroParaEditWnd;
				pSttMultiMacroParaEditViewBase->m_bCharTestObjectHasChanged = FALSE;
			}
		}
	}

	BOOL bRet = TRUE;
	CSttMacroTest *pSttMacroTest = NULL;
	CExBaseObject *pCurrObj = NULL;
	POS pos = pParentSttItems->GetHeadPosition();

	while(pos)
	{
		pCurrObj = pParentSttItems->GetNext(pos);

		if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
		{
			if (!Ats_UpdateAllMacroItem_InternationalMode((CSttItemBase*)pCurrObj))
			{
				bRet = FALSE;
			}
		}
		else if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)             //20240812 zhangyq 电流/电压反时限时节点为CSTTMACROCHARITEMS
		{
			if (!Ats_UpdateAllMacroItem_InternationalMode((CSttItemBase*)pCurrObj))
			{
				bRet = FALSE;
			}
		}
		else if (pCurrObj->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)
		{
			pSttMacroTest = (CSttMacroTest *)pCurrObj;

			if (pSttMacroTest->m_nModified)
			{
				long nRet = m_pTestCtrlCntrBase->Ats_UpdateOneMacroItem(pSttMacroTest);

				if (nRet == STT_CMD_ExecStatus_SUCCESS)
				{
					pSttMacroTest->m_nModified = 0;
				}
				else
				{
					bRet = FALSE;
					CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("更新参数数据失败(%ld)."),nRet);
				}
			}
		}
	}

	if (bIsTypeRootNode)
	{
        //AddUpdateReport_QT((CSttItems*)pParentSttItems);//只对大项根节点更新报告
        //ftt 2024.10.23 使用项目路径更新报告
        QString strItemsPath = ((CSttItems*)pParentSttItems)->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
        AddUpdateReport_QT(strItemsPath);
	}

	return bRet;
}

//pCurrObj，应当是当期的CSttItems（rootnode）。
void QSttTestCntrFrameWin::OnSaveCurr(CExBaseObject *pCurrObj,BOOL IsInternationalMode)
{
	if (pCurrObj == NULL)
	{
		return;
	}

	if (IsInternationalMode)
	{
		Ats_UpdateAllMacroItem_InternationalMode((CSttItems*)pCurrObj);
		return;
	}

	//先关闭正在编辑的通讯命令编辑页面
	//保存参数时，实际上需要重新生成。重新生成需要把原来的项目删掉，因此需要将打开的编辑页面关掉
	if (m_pCmdWzdDsEditWidget != NULL)
	{
		CSttItemBase *pItemBase = (CSttItemBase *)pCurrObj;

		if (pItemBase->IsChildItemExist(m_pCmdWzdDsEditWidget->m_pCurrCmdItem))
		{
			DeleteCmdWzdDsEditWidget();
		}
	}

	//再发送重新生成测试项目的指令
	CString strRootNodeName, strRootNodeID, strItemParentPath;
	strRootNodeName = pCurrObj->m_strName;
	strRootNodeID = pCurrObj->m_strID;
	CExBaseObject *pParent = (CExBaseObject *)pCurrObj->GetParent();
	strItemParentPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	CGbMacroGenWzd *pMacroGen = (CGbMacroGenWzd *)g_theGbSmartGenWzd->FindMacroGen(strRootNodeID
		, strRootNodeName, strItemParentPath);

	if (pMacroGen != NULL)
	{
		g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems(strItemParentPath, strRootNodeName
			, strRootNodeID, pMacroGen->m_pCmdGenParas, g_theGbSmartGenWzd->m_strDvmFile
			, pMacroGen->m_strTestClass, pMacroGen->m_nRepeatTimes, pMacroGen->m_nRptTitle
			, pMacroGen->m_nTitleLevel);
	}
	else
	{
		g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems(strItemParentPath, strRootNodeName, strRootNodeID);
	}
}

void QSttTestCntrFrameWin::Ats_SetItemPara_RsltExpr(CExBaseObject *pItem)
{
	if (pItem == NULL)
	{
		return;
	}

	CString strItemPath, strRsltExpr;
	CSttItemBase *pItemBase = (CSttItemBase *)pItem;

	stt_gb_get_itempath_id(pItemBase, strItemPath);
	CSttItemRsltExpr *pRsltExpr = pItemBase->GetRsltExpr();
	strRsltExpr = pRsltExpr->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	m_pTestCtrlCntrBase->Ats_SetItemPara_RsltExpr(strItemPath, strRsltExpr);

	CExBaseObject *pParent = (CExBaseObject *)pItemBase->GetParent();
	CString strParentItemPath = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdItemRsltExprEdit* pEdit = g_theGbSmartGenWzd->ItemsRsltExprEdit(strParentItemPath, pItemBase->m_strID, pItemBase->m_strName);
	pEdit->SetRsltExpr(strRsltExpr);
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

//shaolei 更新系统参数到CSttDevice的m_pSysPara指针
void QSttTestCntrFrameWin::UpdataSysParaToDevice(const CString &strSysParas)
{
	CSttMacro *pSttMacro = new CSttMacro;
	pSttMacro->SetCreateMacroChild(TRUE);
	BSTR bstrText = strSysParas.AllocSysString();
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	pSttMacro->SetXml(bstrText, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	delete bstrText;// 用完释放

	CSttParas *pParas = pSttMacro->GetParas();
	CDvmDataset oList;
	pParas->SelectAllDatas(oList);
	CSttGuideBook* pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
	pGuideBook->UpdateSysPara(&oList, TRUE);
	oList.RemoveAll();
}

BOOL QSttTestCntrFrameWin::IsAutoTest()
{
	return m_bIsAutoTest;
}

void QSttTestCntrFrameWin::SetAutoTest(BOOL bIsAutoTest)
{
	m_bIsAutoTest = bIsAutoTest;
}

void QSttTestCntrFrameWin::ExpandRootNode()
{
// 	if(m_pSttGbTreeView)
// 	{
// 		m_pSttGbTreeView->m_pTreeCtrl->expandAll();
// 	}

	//shaolei  2023-9-26
	//暂时修改为只展开rootnode节点
	if (m_pSttGbTreeView != NULL)
	{
		m_pSttGbTreeView->ExpandRootNode();
	}
}

void QSttTestCntrFrameWin::OnCmd_StartTest()
{
    //20240909 wanmj 开始测试之外刷新结果栏
    ClearResultWidget();

	if (!IsAutoTest())
	{
		if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
		{
			return;
		}

		if (!g_pTheSttTestApp->m_pTestMacroUI->IsInternationalMode())
		{
			//单机模式下
			QSttTestCntrFrameBase::OnCmd_StartTest();
			return;
		}
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	
	if (stt_IsItemHasAin(pGuideBook))
	{
		if (! IsAinDataMapValid())
		{
			if (! Warning_AinDataMapInvalid(NULL))
			{
				return;
			}
		}
	}

	disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	if (m_pCmdWzdDsEditWidget != NULL)
	{
		m_pCmdWzdDsEditWidget->AutoSave_AfterEdit();
	}

	PromptToSave(m_pSttGbTreeView->m_pCurrSelRootNode, TRUE);

	//测试总是从第一个项目开始
	//在测试开始前，需要将页面切换到模板中的第一个测试功能，以便在测试开始之后，刷新界面上相关的按钮使能，例如：锁
	CSttItems *pItems = pGuideBook->FindFirstItems(GBITEMS_NODETYPE_ROOTNODE);

	if (pItems != NULL)
	{
		((QSttGuideBookTreeWidget_Win*)m_pSttGbTreeView)->SwitchMacroViewByCurrSel(pItems);
	}

	//yzj 2023.10.19 在UpdateCharactWidgetForTest()中存在initPlot(),内部还会清空一次点
// 	if (m_pCharactWidgetForTest != NULL)
// 	{
// 		m_pCharactWidgetForTest->ClearSearchPoints();
// 	} 

	if (m_pSttCharacterDrawPng != NULL)
	{
		m_pSttCharacterDrawPng->ClearSearchPoints_png();
		m_pSttCharacterDrawPng->ClearPngCache();
	}

	//zhouhj 2023.9.8在开始测试前，更新此图,防止在停止测试后,当前特性图参数已被修改
    UpdateCharactWidgetForTest(-1);

	//2024-7-9 wuxinyi
	if (g_pTheSttTestApp->m_pTestMacroUI->IsUIOriginal())
	{
		CSttMacroParaEditViewOriginal *pViewOriginal = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;

		if(pViewOriginal && !pViewOriginal->PrepStartTest())//2024-8-23 wuxinyi 测试准备工作成功开始测试
		{
			return;
		}

	}

	on_UpdateEnableState(STT_TEST_STATE_TESTTING);
	m_oItemStateList.Clear();

//	long nRet = m_pTestCtrlCntrBase->StartTest(NULL);//zhouhj 2024.4.16 返回值为BOOL可以直接判断

	if(m_pTestCtrlCntrBase->StartTest(NULL)/*nRet != STT_CMD_ExecStatus_SUCCESS*/)
	{
		//2024-7-11 wuxinyi 
		if (m_pSttReportViewHtml != NULL)
		{
			m_pSttReportViewHtml->UpdateReportHead_StartEndTestTime(!m_bHasUpdateRptStartTestTime,TRUE);
		}		

		m_bHasUpdateRptStartTestTime = TRUE;
	}
	else
	{
		on_UpdateEnableState(STT_TEST_STATE_TEST_STOPED);
		connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	}
}

void QSttTestCntrFrameWin::OnCmd_TestThis()
{
	if (stt_IsItemHasAin(m_pSttGbTreeView->m_pCurrSelRootNode))
	{
		if (! IsAinDataMapValid())
		{
			if (! Warning_AinDataMapInvalid(m_pSttGbTreeView->m_pCurrSelRootNode))
			{
				return;
			}
		}
	}

	disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

	if (m_pSttGbTreeView->m_pCurrSelRootNode != NULL)
	{
		PromptToSave(m_pSttGbTreeView->m_pCurrSelRootNode, TRUE);
	}

	if (m_pCmdWzdDsEditWidget != NULL)
	{
		m_pCmdWzdDsEditWidget->AutoSave_AfterEdit();
	}

	on_UpdateEnableState(STT_TEST_STATE_TESTTING);
	m_oItemStateList.Clear();

	CString strItemPath;

	if (m_pSttGbTreeView->m_pCurrSelRootNode != NULL)
	{
		strItemPath = m_pSttGbTreeView->m_pCurrSelRootNode->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}
	else
	{
		strItemPath = m_pSttGbTreeView->m_pCurrSelGbItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}
	
	//2023.9.18 zhouhj 在开始测试前更新特性图,防止第一个测试点更新慢了
	//zhouhj 2023.9.8在开始测试前，更新此图,防止在停止测试后,当前特性图参数已被修改
	CSttItemBase* pItem = stt_gb_find_itembase((CSttGuideBook*)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook(), strItemPath);
	long nIndex = ((CExBaseList*)pItem->GetParent())->FindIndex(pItem);
    UpdateCharactWidgetForCurTest(nIndex - 1);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->TestItem(strItemPath);

	//3 == STT_CMD_ExecStatus_SUCCESS
	if(nRet != 3)
	{
        on_UpdateEnableState(STT_TEST_STATE_TEST_STOPED);
		connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
	}
// 	else//zhouhj 2023.9.8在开始测试前，更新此图,防止在停止测试后,当前特性图参数已被修改
// 	{
// 		UpdateCharactWidgetForTest();
// 	}
}

void QSttTestCntrFrameWin::OnCmd_StopTest()
{
	EnableStartStopButton(FALSE);

	if (!m_pTestCtrlCntrBase->StopTest())
	{
		EnableStartStopButton(TRUE);
	}
}

void QSttTestCntrFrameWin::OnCmd_IECConfig()
{
	QSttIecConfigDialogWin oIecConfigDlg(&g_oSttTestResourceMngr.m_oIecDatasMngr);
	oIecConfigDlg.InitUI();
	oIecConfigDlg.m_pSclStation = &m_pTestCtrlCntrBase->m_oSclStation;
// 	QRect rcScreen = QApplication::desktop()->availableGeometry();
// 	oIecConfigDlg.setFixedSize(rcScreen.size());
	connect(&oIecConfigDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),SLOT(slot_IecCfgDataMngrUpdate()));
	oIecConfigDlg.exec();
	disconnect(&oIecConfigDlg, SIGNAL(sig_IecCfgDataMngrUpdate()),this,SLOT(slot_IecCfgDataMngrUpdate()));
}

void QSttTestCntrFrameWin::OnCmd_ReportView()
{
    //ftt 2024.9.24 报告视图用于显示PDF报告
    if(m_pSttReportView == NULL)
    {
        return;
    }

    if (m_bIsAutoTest)
    {
        OnMenuClickedAction_Test(m_pSttReportView, "报告视图");
    }
    else
    {
        long nTabIndex = m_tabTestViews->indexOf((QWidget*)m_pSttReportView);

        if(nTabIndex == -1)
        {
            CString strTabName;
            strTabName = "报告视图";
            nTabIndex = m_tabTestViews->addTab(m_pSttReportView, strTabName);
        }
        m_tabTestViews->setCurrentIndex(nTabIndex);
    }

    //ftt 2024.9.24 此处注释用于显示Html报告的代码
//	OnMenuClickedAction_Test(m_pSttReportViewHtml, "报告视图");

//	if(m_pSttReportViewHtml == NULL)
//	{
//		return;
//	}

//	if (m_bIsAutoTest)
//	{
//		OnMenuClickedAction_Test(m_pSttReportViewHtml, "报告视图");
//	}
//	else
//	{
//		long nTabIndex = m_tabTestViews->indexOf((QWidget*)m_pSttReportViewHtml);

//		if(nTabIndex == -1)
//		{
//			CString strTabName;
//			strTabName = "报告视图";
//			nTabIndex = m_tabTestViews->addTab(m_pSttReportViewHtml, strTabName);
			
//		}

//		m_tabTestViews->setCurrentIndex(nTabIndex);
//	}
}

void QSttTestCntrFrameWin::OnCmd_TemplateView()
{
	QWidget *pMacroEditWidget = GetMacroEditWidget();

	if (pMacroEditWidget == NULL)
	{
		return;
	}

	if (m_bIsAutoTest)
	{
		OnMenuClickedAction_Test(pMacroEditWidget, stt_Frame_TestMacroUI()->m_strName);
	} 
	else
	{
		long nTabIndex = m_tabTestViews->indexOf((QWidget*)pMacroEditWidget);

		//zhouhj 2023.7.5 模板视图界面,固定显示
		if(nTabIndex == -1)
		{
			nTabIndex = m_tabTestViews->addTab(pMacroEditWidget, stt_Frame_TestMacroUI()->m_strName);
			//		m_tabTestViews->setCurrentIndex(nTabIndex);
		}

		m_tabTestViews->setCurrentIndex(nTabIndex);
	}
	

//	OnMenuClickedAction_Test(pMacroEditWidget, stt_Frame_TestMacroUI()->m_strName);
}

void QSttTestCntrFrameWin::OnCmd_VectorDrawView()
{ 
	OnMenuClickedAction_Tools(m_pVectorWidget, /*"矢量图"*/g_sLangTxt_Win_VectorDiagram.GetString());
}

void QSttTestCntrFrameWin::OnCmd_WaveDrawView()
{
	if (m_pWaveDrawWidget)
	{
		OnMenuClickedAction_Tools(m_pWaveDrawWidget, /*"波形图"*/g_sLangTxt_Win_WaveformDiagram.GetString());
	}
}

void QSttTestCntrFrameWin::OnCmd_StateDrawView()
{
	OnMenuClickedAction_Tools(m_pStateMonitorWidget, /*"状态图"*/g_sLangTxt_Win_StatusDiagram.GetString());
}

// void QSttTestCntrFrameWin::OnCmd_CharaView()
// {
// 	//yzj 特性曲线图区分编辑与展示
// 
// }

void QSttTestCntrFrameWin::OnCmd_CharDrawView()
{
	//yzj 特性曲线图区分编辑与展示

    //20240812 wanmj 振荡特性曲线图
    if(strcmp(((CSttMacroParaEditViewOriginal*)m_pMacroEditView)->GetMacroID(), STT_ORG_MACRO_SwingTest) == 0)
    {
		OnMenuClickedAction_Tools(((QSttMacroParaEditViewSwing *)m_pMacroEditView)->m_pImpChart, /*"特性曲线图"*/g_sLangTxt_Win_CharTabTitle);
        return;
    }

	if (m_pCharactWidgetForTest != NULL)
	{
		OnMenuClickedAction_Tools(m_pCharactWidgetForTest, /*"特性曲线图"*/g_sLangTxt_Win_CharTabTitle);
	}
}

void QSttTestCntrFrameWin::OnCmd_PowerDrawView()
{
	if (m_pPowerDiagramWidget != NULL)
	{
		OnMenuClickedAction_Tools(m_pPowerDiagramWidget, /*"功率图"*/g_sLangTxt_Win_PowerDiagram);

		//2024-8-14 wuxinyi 初始刷新功率图界面
		m_pPowerDiagramWidget->cmbVolSetChanged();
		m_pPowerDiagramWidget->cmbCurSetChanged();
		m_pPowerDiagramWidget->updatePowerData();
	}
}

void QSttTestCntrFrameWin::OnCmd_InfoView()
{
	OnMenuClickedAction_Tools(m_pInfoWidget, /*"信息图"*/g_sLangTxt_Win_InfoDiagram);
}
void QSttTestCntrFrameWin::OnCmd_ZTView()
{
	OnMenuClickedAction_Tools(m_pZTViewWidget, /*"ZT视图"*/g_sLangTxt_Win_ZTView);
}

void QSttTestCntrFrameWin::OnCmd_SystemView()
{
	if (m_pSystemDiagramWidget != NULL)
	{
		OnMenuClickedAction_Tools(m_pSystemDiagramWidget, /*"系统图"*/g_sLangTxt_Win_SystemDiagram);
	}
}

void QSttTestCntrFrameWin::OnCmd_WiringView()
{
	if (m_pWiringDiagramWidget != NULL)
	{
		OnMenuClickedAction_Tools(m_pWiringDiagramWidget, /*"接线图"*/g_sLangTxt_Win_WiringDiagram);
	}
}

void QSttTestCntrFrameWin::OnCmd_Liveupdate()
{
	theLiveUpdate.Init();
	theLiveUpdate.LocalUpdate();
}

void QSttTestCntrFrameWin::OnCmd_LiveupdateDevice()
{
	theLiveUpdate.Init();
	theLiveUpdate.TestAppUpdate();
}

void QSttTestCntrFrameWin::OnCmd_DebugOutPutWidget()
{
	if (m_pOutputWidget != NULL)
	{
		bool bShow = m_pOutputWidget->isVisible();
		m_pOutputWidget->setVisible(!bShow);
	}
}

void QSttTestCntrFrameWin::OnCmd_SelSCLFile()
{
	//先不显示历史记录页面，弹窗选择SCD文件
// 	if (m_pSelSCLWidget == NULL)
// 	{
// 		CString strTitle;
// 		strTitle = _T("选择SCL文件");
// 		m_pSelSCLWidget = new QSttSelSclFileWidget(this);
// 		m_tabTestViews->addTab(m_pSelSCLWidget, strTitle);
// 		m_pSelSCLWidget->InitUI();
// 	}

	OpenSclFile();
}

void QSttTestCntrFrameWin::OnCmd_SaveEdit()
{
	if (IsTestStarted())
	{
		return;
	}

	CSttMacroTestUI_TestMacroUI *pSttMacroTestUI_TestMacroUI = stt_Frame_TestMacroUI();

	if (pSttMacroTestUI_TestMacroUI == NULL)
	{
		return;
	}

	if ((!IsAutoTest()) && (!pSttMacroTestUI_TestMacroUI->IsInternationalMode()))
	{
		//单机模式下，应当下发GenerateTemplate指令
		GetDatas();

		if (stt_Frame_TestMacroUI()->IsUIWeb())
		{
			InitBinaryIn_WebUI(m_pTestMacroUI_Paras);
		}
		
		CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
		CSttDevice *pDevice = (CSttDevice *)pGuideBook->FindByClassID(STTGBXMLCLASSID_CSTTDEVICE);
		GenerateTemplate(pDevice, "", "");
		return;
	}

	//保存正在编辑的通讯命令
	if (m_pCmdWzdDsEditWidget != NULL)
	{
		CString strCurrEditCmdPath;
		strCurrEditCmdPath = m_pCmdWzdDsEditWidget->m_pCurrCmdItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
		m_pCmdWzdDsEditWidget->AutoSave_AfterEdit();
	}

	//保存正在编辑的电气量项目
	QSttGuideBookTreeWidget_Win *pTreeView = (QSttGuideBookTreeWidget_Win *)m_pSttGbTreeView;
	BOOL bIsParaChanged = FALSE;
	CDataGroup oParas;

	CharactDatasToTestMacroParas();
	IsUiParasChanged(bIsParaChanged, &oParas);

	if (pTreeView->m_pCurrSelRootNode != NULL)
	{
		if (bIsParaChanged)
		{
			pTreeView->slot_OnBtnSaveCurr();

			if (m_pCharLibWidget != NULL)//zhouhj 2023.8.24 保存编辑后,将特性曲线的变化标记初始化
			{
				m_pCharLibWidget->m_bCharChanged = FALSE;
			}
		}
		else
		{
			//因为当前判断参数是否发生改变，可能存在问题，因此增加提示信息
            //CLogPrint::LogString(XLOGLEVEL_TRACE, _T("++++++++++++++++未检测到参数发生变化，跳过保存！"));
		}	
	}

	//保存后，不自动切换到正在编辑的通讯命令页面：2023-3-22
// 	if ( !strCurrEditCmdPath.IsEmpty() )
// 	{
// 		//保存后，自动打开正在编辑的通讯命令
// 		CSttGuideBook *pGuideBook = (CSttGuideBook *)g_pTheSttTestApp->m_pTestCtrlCntr->GetGuideBook();
// 		CSttItemBase *pItem = stt_gb_find_itembase(pGuideBook, strCurrEditCmdPath);
// 
// 		if (pItem != NULL)
// 		{
// 			ViewCmdEditWidget(pItem);
// 		}
// 	}

// 	CDataGroup oParas;
// 	SaveTestMacroUIParas(&oParas);
}

void QSttTestCntrFrameWin::OnCmd_DcSet()
{
	QAuxDCOutputDlg oAuxDCOutputDlg;
	oAuxDCOutputDlg.initUI();
	connect(&oAuxDCOutputDlg, SIGNAL(sig_UpdateAuxDCOutput()), this, SLOT(slot_UpdateAuxDCOutput()));

    //2024-7-16 wuxinyi 修改辅助直流设置参数下发
    //oAuxDCOutputDlg.exec();
    if (oAuxDCOutputDlg.exec() == QDialog::Accepted)
    {
        slot_UpdateAuxDCOutput();
    }

	disconnect(&oAuxDCOutputDlg, SIGNAL(sig_UpdateAuxDCOutput()), this, SLOT(slot_UpdateAuxDCOutput()));
}

void QSttTestCntrFrameWin::OnCmd_PpIotEngineClient()
{
	if (m_pEngineClientWidget != NULL)
	{
		return;
	}

	CString strTitle;
	strTitle = _T("通讯后台");

	if (m_pEngineClientWidget == NULL)
	{
		QPpSttIotEngineClientWidgetMain *pMainWidget  =new QPpSttIotEngineClientWidgetMain();
		m_pEngineClientWidget = pMainWidget;
	}

	connect(m_pEngineClientWidget,  SIGNAL(sig_OnConfigDevice(CDataGroup *)), this, SLOT(slot_OnConfigDevice(CDataGroup *)));
	m_tabTestViews->addTab(m_pEngineClientWidget, strTitle);
	m_pEngineClientWidget->ShowDvmDevice( g_theGbSmartGenWzd->m_pDvmDevice );
	m_pEngineClientWidget->NewPpSttIotDeviceClient(&g_theGbSmartGenWzd->m_oCommConfig, g_theGbSmartGenWzd->m_pDvmDevice);

}

void QSttTestCntrFrameWin::OnCmd_ClearReportRslts()
{
	CString strMsg;
	strMsg = _T("清除报告数据后，将无法恢复！请确认是否需要继续清除……");
	CString strTitle;
	strTitle = _T("清除报告数据");
	int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

	if (result != QMessageBox::Yes)
	{
		return;
	}

	CDataGroup oParas;
	oParas.AddNewData(STT_CMD_PARA_OnlySelect, _T("1"));
	long nRet = m_pTestCtrlCntrBase->ClearReportsRslts(&oParas);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
		pGuideBook->ClearReport();
		pGuideBook->SetState(TEST_STATE_NORMAL);
		CSttDevice *pDevice = pGuideBook->GetDevice();
		Stt_EmptyReportDatas(pDevice, TRUE);

		disconnect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));
		m_pSttGbTreeView->ShowBaseList((CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook());
		m_pSttGbTreeView->m_pTreeCtrl->UpdateItemColour();
		connect(m_pSttGbTreeView->m_pTreeCtrl,SIGNAL(itemChanged(QTreeWidgetItem *, int)),m_pSttGbTreeView->m_pTreeCtrl,SLOT(slot_TreeItemChanged(QTreeWidgetItem *, int)));

		ClearReportRslts_Html();
	}
}

void QSttTestCntrFrameWin::OnCmd_SystemParas()
{
	QSysParasDlg oSysParasDlg;
	oSysParasDlg.initUI();
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&oSysParasDlg,Keyboard::NUMBER);
	oSysParasDlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	oSysParasDlg.exec();
#endif
}

void QSttTestCntrFrameWin::slot_UpdateCmdButtons_AddMacro()
{
	UpdateCmdButtonsState_AddMacro();
}

void QSttTestCntrFrameWin::slot_ExpandGuideBookTree()
{
	ExpandRootNode();
}

void QSttTestCntrFrameWin::slot_OnInputData(CDataGroup *pParas, CExBaseList *pMsgs)
{
	QSttGbSafetyEdit dlg(NULL, m_pSttGbTreeView);
	dlg.SetDlgRunMode(DLG_SAFETY_RUNMODE_RUN);
	CString strMsgs;

	POS pos = pMsgs->GetHeadPosition();

	while (pos != NULL)
	{
		CSttMsg *pMsg = (CSttMsg *)pMsgs->GetNext(pos);
		strMsgs += pMsg->m_strMsg;

		if (pos != NULL)
		{
			strMsgs += _T("\r\n");
		}
	}

	dlg.SetMsgs(strMsgs);
	dlg.Init(NULL);

	delete pParas;
	delete pMsgs;

	if (dlg.exec() == 0)
	{
		return;
	}

	CSttTestCtrlCntrWin *pCtrlCntrWin = (CSttTestCtrlCntrWin*)g_pTheSttTestApp->m_pTestCtrlCntr;
	pCtrlCntrWin->m_oSttAtsClient.Ats_FinishInputData(NULL, NULL);
}

void QSttTestCntrFrameWin::slot_OnImportDvm(CExBaseList *pListItems)
{
	//先弹窗，逐个指令配置通讯参数。每配置一个，都应该下发commcmd-update指令给19815
	InitImportDvmFileDlg((CSttItems*)pListItems);
}

/*
<group name="" id="">
	<data id="DeviceSN" data-type="string" value="PCS-943-ALL"/>
	<data id="ppxml-file" data-type="string" value=""/>
	<data id="dvm-file" data-type="string" value="D:/Program Files/EPOTO/e-Protocol/Library/PCS-943-ALL.xml"/>
	<data id="EngineProgID" data-type="string" value="MmsEngine"/>
	<group id="comm-config" data-type="" value="">
		<data id="mms" data-type="" value="">
			<value id="local-ip" data-type="" value="172.21.0.100"/>
			<value id="remote-ip" data-type="" value="172.21.0.104"/>
			<value id="remote-port" data-type="" value="102"/>
			<value id="PSW" data-type="" value=""/>
			<value id="KEY" data-type="" value=""/>
		</data>
	</group>
</group>
*/
// //zhouhj 2023.12.6 移入基类
// void QSttTestCntrFrameWin::slot_OnConfigDevice(CDataGroup *pCommCfg)
// {
// 	CSttTestCtrlCntrWin *pCtrlCntrWin = (CSttTestCtrlCntrWin*)g_pTheSttTestApp->m_pTestCtrlCntr;
// 	pCtrlCntrWin->Ats_ConfigDevice(pCommCfg);
// }

BOOL QSttTestCntrFrameWin::OpenSclFile()
{	
	CSclStation *pScl = &m_pTestCtrlCntrBase->m_oSclStation;
	CString strFilePath, strFileName;

	/*
	QStringList astrPostfix;
	CString strFolderPath;
	strFolderPath = _P_GetLibraryPath();
	astrPostfix<<"*.scd"<<"*.icd"<<"*.cid";	
	QSttPopupOpenDialog oOpenDlg(strFolderPath,astrPostfix,this);
	oOpenDlg.setFont(font());
	oOpenDlg.InitUI();

	if (oOpenDlg.exec() != QDialog::Accepted)
		return FALSE;

	if (!oOpenDlg.GetFilePath(strFilePath))
	{
		return FALSE;
	}
	*/

	strFilePath = OpenSclFileDlg();

	if (strFilePath == _T(""))
	{
		return FALSE;
	}

	strFileName = GetFileNameFromFilePath(strFilePath);

	if (pScl->m_strScdFile == strFilePath)
	{
		SelIedFromScl();
		return TRUE;
	}

	pScl->DeleteAll();

	if (m_pSclFileRead != NULL)
	{
		delete m_pSclFileRead;
	}

	m_pSclFileRead = new CSclFileRead();
	m_pSclFileRead->SetIedSaveDvm(FALSE);
	CScdFileRWDlg oScdFileRWDlg(this);
// 	QSclFileRead oRead;
// 	oRead.SetProgressInterface(&oScdFileRWDlg);
// 	oRead.ReadSclFile(strFilePath,pScl);
	m_pSclFileRead->SetProgessInterface(&oScdFileRWDlg);
	m_pSclFileRead->ReadSclFile(strFilePath,NULL, pScl);
	CTickCount32 oWait;

	while( m_pSclFileRead->IsInReadState() )
	{
		oWait.DoEvents(100);
	}

	CString strTscdPath,strSsclPath;
	strTscdPath = _P_GetLibraryPath();
	strFileName = GetFileTitleFromFilePath(strFileName);
	strTscdPath += _T("SCL/");
	strTscdPath += strFileName;
	strTscdPath += _T("/");
	CreateAllDirectories(strTscdPath);
	strTscdPath += strFileName;
	strTscdPath += _T(".tscd");
	pScl->SaveXmlFile(strTscdPath,CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	strSsclPath = ChangeFilePostfix(strTscdPath,_T("sscl"));
	pScl->SaveSsclFiles(strSsclPath);
	SelIedFromScl();
	return TRUE;
}

CString QSttTestCntrFrameWin::SelIedFromScl()
{
	CSclStation *pScl = &m_pTestCtrlCntrBase->m_oSclStation;
	QSttSelSclIedWidget oSttSelSclIedWidget(this);
	oSttSelSclIedWidget.InitUI();
	oSttSelSclIedWidget.InitDatas(pScl);
	oSttSelSclIedWidget.exec();

	CSclIed* pIed = pScl->GetSelectedIed(); 

	if (pIed == NULL)
	{
		return _T("");
	}

	CString strModelFilePath, strModelFilePathDefault;
	strModelFilePath = pIed->m_strModel;
	strModelFilePath += _T("_");
	strModelFilePath += pIed->m_strID;
	strModelFilePath += _T(".xml"); 

	//默认的模型文件路径。
	strModelFilePathDefault = _P_GetInstallPath();
	strModelFilePathDefault += _T("e-Protocol\\Library\\");
	strModelFilePathDefault += strModelFilePath;

	strModelFilePath = OpenDvmFileDlg(strModelFilePath,FALSE);

	if (strModelFilePath.GetLength() > 0)
	{
		//表示用户确认保存。当文件已经存在时，表示用户确认覆盖
		model_XmlWrite(strModelFilePath ,(SCL_IED*)pIed->m_pRefItemData,m_pSclFileRead->GetSCL_INFO(),FALSE);
	}
	else
	{
		if (IsFileExist(strModelFilePathDefault))
		{
			//当文件已经存在
			strModelFilePath = strModelFilePathDefault;
		}
	}

	pIed->m_strDvmFilePath = strModelFilePath;
	return strModelFilePath;
}

void QSttTestCntrFrameWin::OnNew_ChMapsConfig(const CString &strParentItemPath)
{
	CExBaseList* pCurSel = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();

	if (pCurSel->FindByID(STT_CMD_TYPE_ADJUST_ChMapsConfig) != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("创建失败！该节点下，已经存在【硬件通道映射】项目"));
		return;
	}

	QChMapsDlg oChMapsDlg;
	oChMapsDlg.setFont(m_gFont);
	oChMapsDlg.initUI();
	oChMapsDlg.DisableCtrls_SysCfg();
	//	connect(&oChMapsDlg, SIGNAL(sig_UpdateChRsMaps(BOOL)), this, SLOT(slot_UpdateChRsMaps(BOOL)));

	if (oChMapsDlg.exec() != QDialog::Accepted)
	{
		return;
	}

	CString strItemName="硬件通道映射";
	CString strItemParas = g_oSttTestResourceMngr.m_oChMaps.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddMacro(strParentItemPath, strItemName,
		STT_CMD_TYPE_ADJUST_ChMapsConfig, STT_CMD_TYPE_ADJUST_ChMapsConfig, strItemParas);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CSttMacroTest *pMacro = new CSttMacroTest;
		pMacro->m_strName = strItemName;
		pMacro->m_strID = STT_CMD_TYPE_ADJUST_ChMapsConfig;
		pMacro->m_strMacroID = STT_CMD_TYPE_ADJUST_ChMapsConfig;
		pCurSel->AddNewChild(pMacro);
		emit sig_ShowItems_TreeView(pCurSel);
		//m_pSttGbTreeView->ShowBaseList((CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook());

		//2022-9-18  lijunqing
		CGbWzdMacroTestAdd *pNew = g_theGbSmartGenWzd->MacroTestAdd(strParentItemPath, pMacro->m_strID, pMacro->m_strName
			, STT_CMD_TYPE_ADJUST_ChMapsConfig);
		pNew->SetParas(strItemParas);
		//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	}

	UpdateStartStopButtonByItemCount();
}

void QSttTestCntrFrameWin::OnNew_SystemConfig(const CString &strParentItemPath)
{
	CExBaseList* pCurSel = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();

	if (pCurSel->FindByID(STT_CMD_TYPE_SYSTEM_SystemConfig) != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("创建失败！该节点下，已经存在【系统参数配置】项目"));
		return;
	}

	OpenMenuHtmlFile(STT_MACROPARA_HTML_NAME_SYSCONFIG);
	connect(this, SIGNAL(sig_New_SysConfig()),this,SLOT(slot_New_SysConfig()));

	//放到槽函数中
	//UpdateStartStopButtonByItemCount();
}

void QSttTestCntrFrameWin::OnNew_IECConfig(const CString &strParentItemPath)
{
	CExBaseList* pCurSel = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();

	if (pCurSel->FindByID(STT_CMD_TYPE_SYSTEM_IECConfig) != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("创建失败！该节点下，已经存在【IEC61850配置】项目"));
		return;
	}

	QSttIecConfigDialogWin oIecConfigDlg(&g_oSttTestResourceMngr.m_oIecDatasMngr);
	oIecConfigDlg.InitUI();
	oIecConfigDlg.m_pSclStation = &m_pTestCtrlCntrBase->m_oSclStation;
// 	QRect rcScreen = QApplication::desktop()->availableGeometry();
// 	oIecConfigDlg.setFixedSize(rcScreen.size());
	connect(&oIecConfigDlg, SIGNAL(sig_IecCfg_New()),SLOT(slot_IecCfg_New()));
	oIecConfigDlg.exec();
	disconnect(&oIecConfigDlg, SIGNAL(sig_IecCfg_New()),this,SLOT(slot_IecCfg_New()));

	//放到槽函数中
	//UpdateStartStopButtonByItemCount();
}

void QSttTestCntrFrameWin::New_SysConfig()
{
	emit sig_New_SysConfig();
}

//新建单独的通讯命令项目
void QSttTestCntrFrameWin::OnNew_CommCmd(const CString &strParentItemPath, const CString &strCmdID)
{
	CExBaseList* pCurSel = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();
	CDataGroup *pCommCmdCfg = (CDataGroup *)g_theGbSmartGenWzd->m_pCommCmdCfg->FindByID(STT_CMD_PARA_CMDSINGLE);
	CDvmData *pData = (CDvmData *)pCommCmdCfg->FindByID(strCmdID);
	ASSERT(pData != NULL);

	if (pData == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_INFOR, _T("新建通讯命令失败！"));
		return;
	}

	CDataGroup oCommCmd;
	oCommCmd.AddNewGroup(pData->m_strName, pData->m_strID, pData->m_strValue);

	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenrateItems_CmdAdd(strParentItemPath, &oCommCmd, NULL);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CSttCommCmd *pCommCmd = new CSttCommCmd;
		pCommCmd->m_strName = pData->m_strName;
		pCommCmd->m_strID = pData->m_strID;
		//pCommCmd->m_nFillRptDataset = 1;
		pCommCmd->m_strCommCmdID = pData->m_strID;
		pCommCmd->m_strRwOptr = pData->m_strValue;  //read、write、register
		pCommCmd->GetCommCmdData(TRUE);

		//2022-9-19  shaolei
		pCurSel->AddNewChild(pCommCmd, TRUE);
		CGbWzdCommCmdAdd *pNew = g_theGbSmartGenWzd->CommCmdAdd(strParentItemPath, pCommCmd->m_strID, pCommCmd->m_strName
			, pCommCmd->m_strCommCmdID);

		pNew->AddNewData(STT_CMD_PARA_DelayAfterCmd, "2000");
		pNew->AddNewData(STT_CMD_PARA_DelayBeforeCmd, "2000");

		emit sig_ShowItems_TreeView(pCurSel);

		//g_theGbSmartGenWzd->SaveSmartGenWzdFile();

		//自动打开编辑
		ViewCmdEditWidget(pCommCmd);
	}

	UpdateStartStopButtonByItemCount();
}

void QSttTestCntrFrameWin::slot_OnItemStateChanged_Frame(CExBaseObject *pItem)
{
	//对于rootnode的CSttItems节点的项目状态改变：此处必然是测试合格或者不合格
	//意味着一个测试功能点的项目做完了
	//切换到下一个功能点的测试项目时，需要停止状态图等刷新的定时器，否则会导致崩溃
	/*
	if (pItem->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pItems = (CSttItems *)pItem;

		if (pItems->m_strType == GBITEMS_NODETYPE_ROOTNODE)
		{
			StopStateMonitor();
			m_bInited = false;
		}
	}
	else
	{
		if(!m_bInited)
		{
			StartStateMonitor();
			m_bInited = true;
		}
	}
	*/
	//m_pSttGbTreeView->SetCurTestItem(pItem);
	CSttItemStateObject* pSttItemStateObject = (CSttItemStateObject*)pItem;
	CSttItemBase *pSttItem = (CSttItemBase*)pSttItemStateObject->m_pItem;

	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTITEMS)
	{
		CSttItems *pItems = (CSttItems *)pSttItem;

		if (pItems->m_strType == GBITEMS_NODETYPE_ROOTNODE)
		{
// 			if(!m_pMacroEditView->IsHtmlView())
// 			{
// 				CSttMacroParaEditViewOriginal* pMacro = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
// 				pMacro->OnViewTestStop();
// 			}
// 			else
// 			{
// 				QSttMacroParaEditViewHtml* pMacro = (QSttMacroParaEditViewHtml*)m_pMacroEditView;
// 				pMacro->OnViewTestStop();
// 			}

			OnViewTestStop_Common(TRUE);//zhouhj 2023.8.31 只停止公共部分
			m_bInited = false;
		}
	}

	pSttItem->UpdateParentState();
	emit sig_OnItemStateChanged(pSttItem);

//	CSttItemStateObject* pCSttItemStateObject = (CSttItemStateObject*)pItem;
 	CExBaseObject *pParent = (CExBaseObject*)pSttItem->GetParent();

	if ((pParent->GetClassID() == STTGBXMLCLASSID_CSTTMACROCHARITEMS)/*&&()*/)
	{
		CSttMacroTestUI_TestMacroUI *pTestMacroUI =stt_Frame_TestMacroUI();
		if ((pTestMacroUI->m_strID == STT_ORG_MACRO_CurrInverseTimeTest_I) ||
			(pTestMacroUI->m_strID == STT_ORG_MACRO_VolInverseTimeTest_I))
		{
			ShowCharacterTesting(FALSE); //20240810 gongyiping 电压反时限和电流反时限的测试列表不显示
		}
		else
		{
		ShowCharacterTesting(TRUE);
	}
	}

	QSttTestCntrFrameBase::slot_OnItemStateChanged_Frame(pItem);

	//此部分的代码，在该函数入口和出口都有，暂时先注释出口的部分。
	//shaolei 2023-3-16
// 	if (pItem->GetClassID() != STTGBXMLCLASSID_CSTTITEMS)
// 	{
// 		if(!m_bInited)
// 		{
// 			if(!m_pMacroEditView->IsHtmlView())
// 			{
// 				CSttMacroParaEditViewOriginal* pMacro = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
// 				pMacro->OnViewTestStart();
// 			}
// 			else
// 			{
// 				QSttMacroParaEditViewHtml* pMacro = (QSttMacroParaEditViewHtml*)m_pMacroEditView;
// 				pMacro->OnViewTestStart();
// 			}
// 			m_bInited = true;
// 		}
// 	}
}

void QSttTestCntrFrameWin::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_F5)
	{
		OnCmd_SaveEdit();
	}
}

void QSttTestCntrFrameWin::slot_Timer_AutoSave_Ex()
{
	//return;
	//CLogPrint::LogString(XLOGLEVEL_INFOR, _T("触发自动保存"));
	if (IsTestStarted())
	{
		//测试中，屏蔽自动保存
		return;
	}

	if (! IsAutoTest())
	{
		return;
	}

	if (m_bHasClosedUI)
	{
		return;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();

	if (pGuideBook == NULL)
	{
		return;
	}

	if (GetGbItemCount() == 0)
	{
		return;
	}

	//保存记录
	CString strFile = _P_GetWorkspacePath();
	strFile += _T("autosave/");
	CreateAllDirectories(strFile);

	CString strName = pGuideBook->GetGuideBookName();
	strFile += strName;
	strFile += _T("_AutoSave.gbrpt");
	strFile = ChangeFilePostfix(strFile, "html");
    //ftt 2024.9.27
    if(m_pSttReportViewHtml != NULL)
    {
        m_pSttReportViewHtml->SaveHtmlReportFile(strFile);
    }
	SaveTest(strFile, STT_CMD_Send_Async);

	//保存模板
	//2023-9-25 暂时去除保存模板，南瑞是模板和记录合并的
// 	strFile = _P_GetTemplatePath();
// 	strFile += _T("autosave/");
// 	CreateAllDirectories(strFile);
// 
// 	strFile += strName;
// 	strFile += _T("_AutoSave.gbxml");
// 	SaveTemplate(strFile, STT_CMD_Send_Async);
// 	strFile = ChangeFilePostfix(strFile, "html");
// 
// 	CString strFilePath2 = _P_GetDBPath();
// 	strFilePath2 += _T("ui/");
// 	strFilePath2 += CXLanguageMngr::g_pXLanguageMngr->m_strCurrLanguage;
// 	strFilePath2 += _T("/");
// 	strFilePath2 += _T("SaveTemplate.html");
// 	//保存模板时，html中不需要保存报告数据。先存一个备份。
// 	m_pSttReportViewHtml->SaveHtmlReportFile(strFilePath2);
// 	ClearReportRslts_Html();
// 	m_pSttReportViewHtml->SaveHtmlReportFile(strFile);
// 	strFilePath2 = GetFileNameFromFilePath(strFilePath2);
// 	//重新打开保存的备份，这样“报告视图”中，还是有报告数据
// 	//此处删除重新new。是为了防止内存泄漏
// 	delete m_pSttReportViewHtml;
// 	m_pSttReportViewHtml = new QSttReportViewHtml();
// 	m_pSttReportViewHtml->InitReport(strFilePath2);
}

void QSttTestCntrFrameWin::slot_Timer_AutoSave()
{
 	CAutoSimpleLock oLock(m_oCriticSection_AutoSave);
 	slot_Timer_AutoSave_Ex();
}

void QSttTestCntrFrameWin::slot_OnFreeCommCmdWzdWidget()
{
	FreeCommCmdWzdMain();

	CSttItems *pSttItems = m_pSttGbTreeView->m_pCurrSelRootNode;

	if (pSttItems == NULL)
	{
		return;
	}

	CSttMacroTest *pMacroTest = (CSttMacroTest *)pSttItems->FindByID(stt_Frame_TestMacroUI()->m_strID);

	if (pMacroTest != NULL)
	{
		m_pMacroTest_Original = pMacroTest;

		//对于IEC51850配置、硬件通道配置、系统参数配置。在新建后，自动打开编辑界面。
		CString strMacroID = pMacroTest->m_strMacroID;

		if (strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig
			|| strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig
			|| strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig)
		{
			//ViewMacroEditWidget(pMacroTest);
			emit sig_ViewMacroEditWidget(pMacroTest);
		}
	}
}

void QSttTestCntrFrameWin::slot_OnFreeImportDvmFileWidget()
{
	FreeImportDvmFileDlg();
}

void QSttTestCntrFrameWin::OpenMenuHtmlFile(const CString &strMemuFileName)
{
	if (IsHtmlParasEditOpen())
	{
		return;
	}

	CString strTiTle;
	long nMaxWidth = 1024;
	long nMaxHeight = 768;
	strTiTle = _T("系统参数设置");

	if (strMemuFileName == STT_MACROPARA_HTML_NAME_SYSCONFIG)
	{
		strTiTle = _T("系统参数设置");
 		nMaxWidth = 1010;
 		nMaxHeight = 580;
	}

	m_rcWorkArea = QRect(m_tabTestViews->pos().x(), m_tabTestViews->pos().y() + m_pToolBarWin->height() + m_pMenuBar->height(),
		m_tabTestViews->rect().width(), m_tabTestViews->rect().height());

	connect(this, SIGNAL(sig_NewSysConfig()), this, SLOT(slot_NewSysConfig()),Qt::QueuedConnection);
	m_pSysParaEditView = new QSttMacroParaEditViewHtml();
	m_pSysParaEditView->setWindowTitle(strTiTle);
	m_pSysParaEditView->m_nSysConfig_Mode = STT_HTML_SYSCONFIG_MODE_NEW;
	
	QDesktopWidget* pDesktop = QApplication::desktop();
	QRect rcScreen = pDesktop->availableGeometry();
	long nX = (rcScreen.width() - nMaxWidth) / 2;
	long nY = (rcScreen.height() - nMaxHeight) / 2;
	m_pSysParaEditView->setGeometry(QRect(nX, nY, nMaxWidth, nMaxHeight));

	m_pSysParaEditView->OpenHtmlFile(strMemuFileName);
	m_pSysParaEditView->setWindowModality(Qt::ApplicationModal);
	m_pSysParaEditView->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	m_pSysParaEditView->show();
}

void QSttTestCntrFrameWin::Cmd_SendChMapsConfig()
{
	Ats_SetItemPara(STT_CMD_TYPE_ADJUST_ChMapsConfig);
}

void QSttTestCntrFrameWin::Cmd_SendSystemConfig()
{
	Ats_SetItemPara(STT_CMD_TYPE_SYSTEM_SystemConfig);
}

//改函数在基类中实现//2023.3.24
// void QSttTestCntrFrameWin::GetMacroItemsXml(const CString strItemID, char **ppszReport, long &nLen,const CString &strParentPath)
// {
// 	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();
// 	CString strMacroID = stt_Frame_TestMacroUI()->m_strID;
// 
// 	if(strIDMacroUI == STT_ORG_MACRO_ManualTest
// 		|| strIDMacroUI == STT_ORG_MACRO_StateTest
// 		|| strIDMacroUI == STT_ORG_MACRO_HarmTest)
// 	{
// 		nLen = m_pMacroEditView->GetMacroItemsXml(strItemID, ppszReport);
// 	}
// 	else
// 	{
// 		nLen = m_pTestCtrlCntrBase->GetMacroItemsXml(strItemID, ppszReport,strParentPath);
// 	}
// }

BOOL QSttTestCntrFrameWin::SwitchMacroViewByCurrSel(CSttItems *pCurrSelRootNode)
{
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pCurrSelRootNode->m_strstxmlFile);

	if (pTestMacroUI == NULL)
	{
		return FALSE;
	}

	if (pTestMacroUI->IsInternationalMode())
	{
		g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUI);
		//yzj 2023.10.17 同步维护cntr内的当前UI指针
		g_pTheSttTestApp->m_pTestCtrlCntr->SetCurrTestMacroUI(pTestMacroUI);
		g_pTheSttTestApp->m_pTestCtrlCntr->stt_OpenHdRsFile(pTestMacroUI->m_strHdRsFile);

		SetActiveWidget(NULL);
		//2022-3-27  lijunqing  创建参数编辑窗口
		CreateSttMacroParaEditView(pTestMacroUI, TRUE);
		QSttMultiMacroParaEditViewBase *pSttMultiMacroParaEditViewBase = (QSttMultiMacroParaEditViewBase*)m_pMacroEditView;
		pSttMultiMacroParaEditViewBase->InitDatas(pCurrSelRootNode);
		pSttMultiMacroParaEditViewBase->Update_MultiMacroParaEditView();
	} 
	else
	{
		CSttTestMacroUiParas *pUIParas = GetTestMacroUiParas(pCurrSelRootNode);

		if (pUIParas == NULL)
		{
			return FALSE;
		}

		g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUI);
		//yzj 2023.10.17 同步维护cntr内的当前UI指针
		g_pTheSttTestApp->m_pTestCtrlCntr->SetCurrTestMacroUI(pTestMacroUI);
		g_pTheSttTestApp->m_pTestCtrlCntr->stt_OpenHdRsFile(pTestMacroUI->m_strHdRsFile);

		SetActiveWidget(NULL);

		m_pTestMacroUI_Paras->DeleteAll();

		BSTR bstrText = pUIParas->m_strParaText.AllocSysString();
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		m_pTestMacroUI_Paras->SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

#ifdef _PSX_IDE_QT_
		delete bstrText;
#else
		SysFreeString(bstrText);
#endif

		//2022-3-27  lijunqing  创建参数编辑窗口
		CreateSttMacroParaEditView(pTestMacroUI, TRUE);
	}

	if (pTestMacroUI->IsUIOriginal())
	{
		if (pTestMacroUI->m_strID != STT_ORG_MACRO_Iec61850Config
			&& pTestMacroUI->m_strID != STT_ORG_MACRO_SystemConfig
			&& pTestMacroUI->m_strID != STT_ORG_MACRO_ChMapsConfig)
		{
			if (m_pMacroEditView != NULL)
			{
				m_pMacroEditView->SetDatas(m_pTestMacroUI_Paras);
				//zhouhj 2023.9.15 暂时在此处处理，防止测试功能保存模板后,结构体增加了新的参数,导致后期获取的数据数量与之前不一致,
				//每次切换测试功能时,都会提示参数保存
				m_pTestMacroUI_Paras->DeleteAll();
				m_pMacroEditView->GetDatas(m_pTestMacroUI_Paras);
			}
		}
	}

	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
		QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
		pSttMacroParaEditViewHtml->OpenHtmlFile(pTestMacroUI->m_strUI_File);
		//重新刷新网页的矢量图、状态图、信息图
		InitVectorWidget(NULL,NULL);
		InitPowerWidget(NULL,NULL);
		InitStateMonitor();
		ClearInfoWidget();	
	}

	//2024-8-6 wuxinyi 重新刷新波形图
	InitWaveDrawWidget();
	if (!HasWaveWidget(pTestMacroUI->m_strUI_ID))
	{
		EnableAction(STT_CNTR_CMD_WaveDrawView, FALSE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_WaveDrawView, TRUE, TRUE);
	}

	//系统图
	InitSystemDiagramWidget();
	if (!HasSystemDiagramWidget(pTestMacroUI->m_strUI_ID))
	{
		EnableAction(STT_CNTR_CMD_SystemView, FALSE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_SystemView, TRUE, TRUE);
	}

	//接线图
	InitWiringDiagramWidget();
	if (!HasWiringDiagramWidget(pTestMacroUI->m_strUI_ID))
	{
		EnableAction(STT_CNTR_CMD_WiringView, FALSE);
	}
	else
	{
		EnableAction(STT_CNTR_CMD_WiringView, TRUE, TRUE);
	}

	AdjustMacroEditWidgetToFrame(pTestMacroUI);

	AdjustToolBarButtons();

	if (pTestMacroUI->IsUIOriginal())
	{
		if (m_pMacroEditView != NULL)
		{
			CSttMacroParaEditViewOriginal* pMacro = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
			pMacro->m_bIsOpenMacroFinished = TRUE;
		}
	}

	SetCharChanged(FALSE);//测试项切换后,将特性曲线参数改变置为false;
	//切换测试项时触发刷新可能存在的特性曲线图
	if (pTestMacroUI->HasCharLib())
	{
// 		CString strFile;
// 		GetCharacteristicsFile(pTestMacroUI, strFile);
// 		m_pCharacteristics->DeleteAll();
// 
// 		if (IsFileExist(strFile))
// 		{
// 			m_pCharacteristics->OpenXmlFile(strFile,CCharacteristicXmlRWKeys::CCharacteristicsKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
// 			InitCharLibWidget();
// 			m_pCharLibWidget->InitCharacteristicsLib(pTestMacroUI->m_strCharlibFile);
// 			m_pCharLibWidget->ShowCharacteristics(m_pCharacteristics);
// 			m_pCharLibWidget->m_strCharParasFile = strFile;
// 
// 			if (m_pCharactWidgetForTest != NULL)
// 			{
// 				m_pCharactWidgetForTest->InitCharacteristic(pTestMacroUI->m_strID);
// 			}
// 
// 			if (m_pCharTestPointsGrid)
// 			{
// 				m_pCharTestPointsGrid->InitMacroID(pTestMacroUI->m_strID);
// 			}
// 		}

		//重新刷新网页的特性曲线图
		m_pCharacteristics->DeleteAll();

		CSttTestMacroCharParas *pSttTestMacroCharParas = (CSttTestMacroCharParas*)pCurrSelRootNode->FindByClassID(STTGBXMLCLASSID_CSTTTESTMACROCHARPARAS);
		CSttContents *pContents = (CSttContents*)pCurrSelRootNode->FindByClassID(STTGBXMLCLASSID_CSTTCONTENTS);

		if (pSttTestMacroCharParas != NULL)
		{
			m_pCharacteristics->SetXml(pSttTestMacroCharParas->m_strParaText,CCharacteristicXmlRWKeys::g_pXmlKeys);
		}
		else if (pContents != NULL)
		{
			m_pCharacteristics->SetXml(pContents->m_strText, CCharacteristicXmlRWKeys::g_pXmlKeys);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE,_T("当前CSttTestMacroCharParas对象查找失败"));
		}

//		pCurrSelRootNode->CloneCharacteristics(m_pCharacteristics);
		InitCharLibWidget();
		m_pCharLibWidget->InitCharacteristicsLib(pTestMacroUI->m_strUI_ID,pTestMacroUI->m_strCharlibFile);
		m_pCharLibWidget->ShowCharacteristics(m_pCharacteristics);

		if (m_pCharactWidgetForTest != NULL)
		{
            m_pCharactWidgetForTest->InitCharacteristic(pTestMacroUI->m_strID, FALSE);
		}

		if (m_pSttCharacterDrawPng != NULL)
		{
			m_pSttCharacterDrawPng->ClearSearchPoints_png();
//			m_pSttCharacterDrawPng->ClearSearchPoints_png();
		}

		if (m_pCharTestPointsGrid)
		{
			m_pCharTestPointsGrid->InitMacroID(pTestMacroUI->m_strID);
		}
	}

//	OpenMacroTestUI(pUIParas, pTestMacroUI);

	if (!HasManuTrigerBtn())
	{
		EnableManualTriggerButton(false);
	}

	//特性曲线
	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib());
	return TRUE;
}


//函数功能统一在基类中实现  2023.3.24 zhouhj
// void QSttTestCntrFrameWin::UpdateRptHtml(const CString &strItemsID)
// {
// 	if (m_pSttReportViewHtml == NULL)
// 	{
// 		return;
// 	}
// 
// 	char *strReport = NULL;
// 	long nLen = 0;
// 
// 	GetMacroItemsXml(strItemsID, &strReport, nLen,_T(""));
// 
// 	if (nLen > 0)
// 	{
// 		m_pSttReportViewHtml->AddUpdateCmd(stt_Frame_TestMacroUI(), "", strItemsID, strReport);
// 	}
// }

// void QSttTestCntrFrameWin::UpdateRptHtml(const CString &strItemsID,const CString &strMacroUI_ID,const CString &strParentPath)
// {
// 	if (m_pSttReportViewHtml == NULL)
// 	{
// 		return;
// 	}
// 
// 	char *strReport = NULL;
// 	long nLen = 0;
// 
// 	GetMacroItemsXml(strItemsID, &strReport, nLen,strParentPath);
// 
// 	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(strMacroUI_ID);
// 
// 	if ((nLen > 0)&& (pTestMacroUI!= NULL))
// 	{
// 		m_pSttReportViewHtml->AddUpdateCmd(pTestMacroUI, "", strItemsID, strReport);
// 	}
// }

void QSttTestCntrFrameWin::SelectTestMacro_CmdWzd(const CString &strTestMacroUI, const CString &strItemsName
												   , const CString &strItemsID, CDataGroup *pCommCmd
												   , const CString &strTestClass, const CString &strDvmFile
												   , long nRepeatTimes, long nRptTitle, long nTitleLevel)
{
	if (g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI >>");
	}

	g_pTheSttTestApp->SetCurrTestMacroUI(strTestMacroUI);

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = stt_Frame_TestMacroUI();

	//第一步：创建参数编辑页面、加载报告html页面
	m_pTestCtrlCntrBase->OpenMacroTestUI(pTestMacroUI);

	CExBaseObject *pSel = m_pSttGbTreeView->GetCurrSelectGbItem();

	if ((m_pSttGbTreeView!= NULL)&&(pSel != NULL))
	{
		CString strCurrRootNodePath;
		strCurrRootNodePath = pSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		if (strCurrRootNodePath.IsEmpty())
		{
			strCurrRootNodePath = strItemsID;
		} 
		else
		{
			strCurrRootNodePath.AppendFormat(_T("$%s"),strItemsID.GetString());
		}

		m_pSttGbTreeView->m_strCurrSelRootNodePath = strCurrRootNodePath;
	}

	//向导数据导入
	SetErrorValueFromWzd(&m_oErrorValueWzdGroup);

	//创建参数编辑窗口
	CreateSttMacroParaEditView(pTestMacroUI);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI 2 >>");	}

	if (pTestMacroUI->IsUIOriginal())
	{//原生态网页，获取页面参数数据
		if (m_pMacroEditView != NULL)
		{
			m_pMacroEditView->GetDatas(m_pTestMacroUI_Paras);
		}
	}
	else//网页界面的矢量图、状态图、信息图在此处统一初始化,原生界面在各自构造函数中初始化 zhouhj 20220329
	{
		InitBinaryIn_WebUI(m_pTestMacroUI_Paras);
		stt_Frame_InitVectorWidget(NULL,NULL);
		stt_Frame_InitStateMonitor();
		stt_Frame_ClearInfoWidget();	
	}

	SaveUIParaFile(m_pTestMacroUI_Paras);	//2022-10-16  lijunqing 记录和保存当前页面设置的值：设置为默认值

	if (pTestMacroUI->HasCharLib()) //2022-6-30  lijunqing
	{
        InitCharLibWidget();
	}

	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
		QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
		pSttMacroParaEditViewHtml->OpenHtmlFile(pTestMacroUI->m_strUI_File);
	}

	AdjustMacroEditWidgetToFrame(pTestMacroUI);

	//未选择测试功能时，“开始测试”按钮使能为FALSE
	if (pTestMacroUI->m_strID != _T(""))
	{
		UpdateButtonStateByID(STT_CNTR_CMD_StartTest,true,true);
	}
	else
	{
		UpdateButtonStateByID(STT_CNTR_CMD_StartTest,false,true);
	}

	//系统参数页面，未勾选“数字”，应隐藏“IEC配置”按钮 sf 20220317
	if ( ! g_oSystemParas.HasDigitalInOrOut())
	{
		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,false,false);
	}
	else
	{
		UpdateButtonStateByID(STT_CNTR_CMD_IECConfig,true,true);
	}

	//状态序列才使用手动触发这个按钮，其他不用，隐藏 sf 20220218
	if (HasManuTrigerBtn()/*pTestMacroUI->m_strID == STT_ORG_MACRO_StateTest*/)
	{
		UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);
	}
	else
	{
		UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,false);
	}

	AdjustToolBarButtons();

	{
		AddMacroTestReport(pTestMacroUI, pSel, strItemsName, strItemsID);
	}

	//若有特性曲线，打开特性曲线定义，在测试模板生成后，返回的模板信息中如果不带测试模板，则使用默认测试模板
	CString strFile;
	GetCharacteristicsFile(pTestMacroUI, strFile);
	m_pCharacteristics->DeleteAll();

	if (IsFileExist(strFile))
	{
		m_pCharacteristics->OpenXmlFile(strFile,CCharacteristicXmlRWKeys::CCharacteristicsKey(),CCharacteristicXmlRWKeys::g_pXmlKeys);
	}

	//发送特性曲线改变事件
	if (pTestMacroUI->HasCharLib()) 
	{
		m_pCharLibWidget->InitCharacteristicsLib(pTestMacroUI->m_strUI_ID,pTestMacroUI->m_strCharlibFile);
		m_pCharLibWidget->ShowCharacteristics(m_pCharacteristics);
	}

	//特性曲线
	ShowHideCharactUI(pTestMacroUI->IsInternationalMode(), pTestMacroUI->HasCharLib());
//     if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
// 	{
// 		ShowCharEditTab();
// 	}
// 	else
// 	{
// 		HideCharEditTab();
// 	}

	CString strParentItemsPath;
	strParentItemsPath = ((CExBaseList*)pSel)->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_GenerateItems(strParentItemsPath, strItemsName, strItemsID
		, pCommCmd, strDvmFile, strTestClass, nRepeatTimes, nRptTitle, nTitleLevel);

	if (g_nLogDebugInfor == 1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> end OpenMacroTestUI >>");
	}

	UpdateToolButtons();
	UpdateStartStopButtonByItemCount();
	UpdateToolButtons_AfterAddMacro();
}

//2022-9-11  lijunqing
void QSttTestCntrFrameWin::ViewCmdEditWidget(CExBaseObject *pSelObj)
{
	if (m_pCmdWzdDsEditWidget == NULL)
	{
		m_pCmdWzdDsEditWidget = new QSttCmdWzdDsEditWidget(m_gFont, this);
		m_tabTestViews->addTab(m_pCmdWzdDsEditWidget, pSelObj->m_strName);
	}
	else
	{
		long nIndex = m_tabTestViews->indexOf(m_pCmdWzdDsEditWidget);
		m_tabTestViews->setTabText(nIndex, pSelObj->m_strName);
	}

	//先自动保存上一次的
	m_pCmdWzdDsEditWidget->AutoSave_AfterEdit();
	m_pCmdWzdDsEditWidget->ShowCmd((CSttItemBase*)pSelObj);
	m_tabTestViews->setCurrentWidget(m_pCmdWzdDsEditWidget);
	CString strPath;
	strPath = pSelObj->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	m_pTestCtrlCntrBase->Ats_QueryItem(strPath);
}

//2022-9-18  lijunqing
void QSttTestCntrFrameWin::ViewMacroEditWidget(CExBaseObject *pSelObj)
{
	CSttMacroTest *pSttMacroTest = (CSttMacroTest*)pSelObj;

	if (pSttMacroTest->m_strMacroID == STT_CMD_TYPE_ADJUST_ChMapsConfig)
	{
		ViewMacroEditWidget_ChMapsConfig(pSttMacroTest);
	}
	else if (pSttMacroTest->m_strMacroID == STT_CMD_TYPE_SYSTEM_IECConfig)
	{
		ViewMacroEditWidget_IECConfig(pSttMacroTest);
	}
	else if (pSttMacroTest->m_strMacroID == STT_CMD_TYPE_SYSTEM_SystemConfig)
	{
		ViewMacroEditWidget_SystemConfig(pSttMacroTest);
	}
	else
	{
		//对于其他的项目，自动激活参数编辑页面
		if (m_pMacroEditView != NULL)
		{
			//双击事件，会先触发OnItemSelChanged，所以此处可以直接激活页面即可
			QWidget *pMacroEditWidget = GetMacroEditWidget();
			m_tabTestViews->setCurrentWidget(pMacroEditWidget);
		}
	}
}

void QSttTestCntrFrameWin::ViewMacroEditWidget_ChMapsConfig(CSttMacroTest *pSttMacroTest)
{
	CExBaseObject *pParent = (CExBaseObject*)pSttMacroTest->GetParent();
	CString strParentID = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdMacroTestAdd *pFind = (CGbWzdMacroTestAdd*)g_theGbSmartGenWzd->FindXItemBase(pSttMacroTest->m_strID, strParentID);

	if (pFind != NULL)
	{
		g_oSttTestResourceMngr.m_oChMaps.SetChMapsString(pFind->m_pParas->m_strText);
	}

	QChMapsDlg oChMapsDlg;
	oChMapsDlg.setFont(m_gFont);
	oChMapsDlg.initUI();
	oChMapsDlg.DisableCtrls_SysCfg();

	if (oChMapsDlg.exec() != QDialog::Accepted)
	{
		return;
	}

	CString strText = g_oSttTestResourceMngr.m_oChMaps.GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	
	if (pFind != NULL)
	{
		pFind->m_pParas->m_strText = strText;
	}
	
	CString strParentItemPath = pSttMacroTest->m_strID;
	
	if (strParentID.GetLength() > 0)
	{
		strParentItemPath = strParentID + _T("$") + pSttMacroTest->m_strID;
	}

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateItem(strParentItemPath, strText);
}

void QSttTestCntrFrameWin::ViewMacroEditWidget_IECConfig(CSttMacroTest *pSttMacroTest)
{
	CExBaseObject *pParent = (CExBaseObject*)pSttMacroTest->GetParent();
	CString strParentID = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdMacroTestAdd *pFind = (CGbWzdMacroTestAdd*)g_theGbSmartGenWzd->FindXItemBase(pSttMacroTest->m_strID, strParentID);
	//20230428 zhouhj 先克隆一份进行IEC配置修改,防止点击取消后,影响当前IEC配置内容
	CIecCfgDatasMngr *pCIecCfgDatasMngr = (CIecCfgDatasMngr*)g_oSttTestResourceMngr.m_oIecDatasMngr.Clone();

	if (pFind != NULL)
	{
		pCIecCfgDatasMngr->SetIecCfgDataString(pFind->m_pParas->m_strText);
	}

	QSttIecConfigDialogWin oIecConfigDlg(pCIecCfgDatasMngr);
	oIecConfigDlg.InitUI();
	oIecConfigDlg.m_pSclStation = &m_pTestCtrlCntrBase->m_oSclStation;
// 	QRect rcScreen = QApplication::desktop()->availableGeometry();
// 	oIecConfigDlg.setFixedSize(rcScreen.size());

	if (oIecConfigDlg.exec() != QDialog::Accepted)
	{
		delete pCIecCfgDatasMngr;
		return;
	}

	++CCfgDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;
	CString strText = pCIecCfgDatasMngr->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	--CCfgDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;
	delete pCIecCfgDatasMngr;
	g_oSttTestResourceMngr.m_oIecDatasMngr.SetIecCfgDataString(strText);

	if (pFind != NULL)
	{
		pFind->m_pParas->m_strText = strText;
	}
	
	CString strParentItemPath = pSttMacroTest->m_strID;

	if (strParentID.GetLength() > 0)
	{
		strParentItemPath = strParentID + _T("$") + pSttMacroTest->m_strID;
	}

	g_oSttTestResourceMngr.SaveDefaultIec61850Config();//保存xml


	//zhouhj 2023.4.24 IEC配置修改后,更新IEC配置
	if ((stt_Frame_TestMacroUI() != NULL)&&(m_pMacroEditView!=NULL))//判断当前是否加载了测试功能模块,并判断当前测试功能模块是否为网页
	{
		if (stt_Frame_TestMacroUI()->IsUIOriginal())//更新界面
		{
			CSttMacroParaEditViewOriginal* pOriginal = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
			pOriginal->UpdateGoutTab(TRUE);//zhouhj20220319 在非网页界面界面时,更新
		}
	}

#ifdef use_CSmartCapCtrl
    if (m_pSttIecRecordMainWidget != NULL)
	{
		m_pSttIecRecordMainWidget->UpdateIecfg();
	}
#endif  //use_CSmartCapCtrl

	//20230428 zhouhj 先更新参数,再发送命令,防止等待返回报文时,主线程界面刷新使用IEC相关配置时,软件崩溃
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateItem(strParentItemPath, strText);
}

void QSttTestCntrFrameWin::ViewMacroEditWidget_SystemConfig(CSttMacroTest *pSttMacroTest)
{
	//2022-9-19  lijunqing 使用变量记录，避免编辑过程中选择了其他的对象
	m_pCurrGbWzdMacroTestEdit = pSttMacroTest; 
	CExBaseObject *pParent = (CExBaseObject*)pSttMacroTest->GetParent();
	CString strParentID = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdMacroTestAdd *pFind = (CGbWzdMacroTestAdd*)g_theGbSmartGenWzd->FindXItemBase(pSttMacroTest->m_strID, strParentID);

	//添加将pFind->m_pParas->m_strText设置为系统参数的代码， 格式是否正确，需要确认
	if (pFind != NULL)
	{
		stt_SystemParas_SetString(pFind->m_pParas->m_strText);
	}  

	OpenMenuHtmlFile(STT_MACROPARA_HTML_NAME_SYSCONFIG);
	connect(this, SIGNAL(sig_New_SysConfig()),this,SLOT(slot_Edit_SysConfig()));

}

//2022-9-19  lijunqing 编辑系统参数配置项目
void QSttTestCntrFrameWin::slot_Edit_SysConfig()
{
	if (m_pCurrGbWzdMacroTestEdit == NULL)
	{
		return;
	}

	CExBaseObject *pParent = (CExBaseObject*)m_pCurrGbWzdMacroTestEdit->GetParent();
	CString strParentID = pParent->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CGbWzdMacroTestAdd *pFind = (CGbWzdMacroTestAdd*)g_theGbSmartGenWzd->FindXItemBase(m_pCurrGbWzdMacroTestEdit->m_strID, strParentID);

	CString strText;
	stt_SystemParas_GetString(strText);

	if (pFind != NULL)
	{
		pFind->m_pParas->m_strText = strText;
	}

	CString strParentItemPath = m_pCurrGbWzdMacroTestEdit->m_strID;

	if (strParentID.GetLength() > 0)
	{
		strParentItemPath = strParentID + _T("$") + m_pCurrGbWzdMacroTestEdit->m_strID;
	}

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_UpdateItem(strParentItemPath, strText);

	//同步系统参数到CSttDevice中的m_pSysPara指针
	UpdataSysParaToDevice(strText);
	
	if(g_oSystemParas.m_nHasDigital)
	{
		UpdateButtonsStateByID(STT_CNTR_CMD_IECConfig, TRUE);
	}
	else
	{
		UpdateButtonsStateByID(STT_CNTR_CMD_IECConfig, FALSE);
	}

	m_pCurrGbWzdMacroTestEdit = NULL;
}


//2022-9-12 lijunqing
void QSttTestCntrFrameWin::SaveMacroParasToCurrWzd(CDataGroup *pCommCmd)
{
	CGbMacroGenWzd *pMacroGenWzd = g_theGbSmartGenWzd->m_pCurrGbMacroGenWzd;

	//当前没有测试功能向导
	if (pMacroGenWzd == NULL)
	{
		return;
	}

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = stt_Frame_TestMacroUI();

	//测试功能属性
	CDataGroup *pMacroUIAttrs = pMacroGenWzd->GetMacroUIAttrs();
	pTestMacroUI->GetTestMacroUIDataGroup(pMacroUIAttrs);

	//测试功能参数
	CDataGroup *pUIParas = pMacroGenWzd->GetMacroUIParas();
	pUIParas->DeleteAll();
	pUIParas->AppendCloneEx(*m_pTestMacroUI_Paras);

	//通讯命令生成参数
	CDataGroup *pCmdGenParas = pMacroGenWzd->GetCmdGenParas();
	pCmdGenParas->DeleteAll();
	pCmdGenParas->AppendCloneEx2(*pCommCmd);

	//特性曲线
    if (pTestMacroUI->m_strCharlibFile.GetLength() > 0 && m_pCharacteristics != NULL)
	{
		CDvmContents *pChar = pMacroGenWzd->GetCharacteristic();
        m_pCharacteristics->GetXml(CCharacteristicXmlRWKeys::g_pXmlKeys, pChar->m_strText);
	}

	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
}

void QSttTestCntrFrameWin::OnCloseTabTestViews(const int& index)
{
	QWidget* tabItem = m_tabTestViews->widget(index);
	
	if (tabItem == m_pCmdWzdDsEditWidget)
	{
		m_tabTestViews->removeTab(index);
		delete m_pCmdWzdDsEditWidget;
		m_pCmdWzdDsEditWidget = NULL;
	}
}

void QSttTestCntrFrameWin::slot_currentChangedTabWidget(int nCurrIndex)
{
	if (m_pCharLibWidget == NULL)
	{
		return;
	}

	QWidget *pMacroEditWidget = GetMacroEditWidget();

	if (m_tabTestViews->currentWidget() == m_pCharLibWidget)
	{
		CharDrawView_Prepare();
	}
	else if (m_tabTestViews->currentWidget() == pMacroEditWidget)
	{
		TemplateView_Prepare();
	}
}

void QSttTestCntrFrameWin::OnCloseTabTestTools(const int& index)
{
	QWidget* tabItem = m_tabTestTools->widget(index);
	OnMenuClickedAction_Tools(tabItem, "");
}

void QSttTestCntrFrameWin::slot_IecCfg_New()
{
	g_oSttTestResourceMngr.SaveDefaultIec61850Config();//保存xml

#ifdef use_CSmartCapCtrl
    if (m_pSttIecRecordMainWidget != NULL)
	{
		m_pSttIecRecordMainWidget->UpdateIecfg();
	}
#endif  //use_CSmartCapCtrl

	CExBaseList* pCurSel = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();
	CString strParentItemPath = pCurSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	CSttMacroTest *pMacro = NULL;

	CString strItemParas;
	++CCfgDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;
	strItemParas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetXml(CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	--CCfgDataMngrXmlRWKeys::g_pXmlKeys->m_nXmlOnlyWrite_Id_Value;

	CString strItemName=_T("IEC61850配置");
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddMacro(strParentItemPath, strItemName, 
		STT_CMD_TYPE_SYSTEM_IECConfig, STT_CMD_TYPE_SYSTEM_IECConfig, strItemParas);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		pMacro = new CSttMacroTest;
		pMacro->m_strName = strItemName;
		pMacro->m_strID = STT_CMD_TYPE_SYSTEM_IECConfig;
		pMacro->m_strMacroID = STT_CMD_TYPE_SYSTEM_IECConfig;
		pCurSel->AddNewChild(pMacro);
		emit sig_ShowItems_TreeView(pCurSel);
		//m_pSttGbTreeView->ShowBaseList((CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook());

		//2022-9-18  lijunqing
		CGbWzdMacroTestAdd *pNew = g_theGbSmartGenWzd->MacroTestAdd(strParentItemPath, pMacro->m_strID, pMacro->m_strName
			, STT_CMD_TYPE_SYSTEM_IECConfig);
		pNew->SetParas(strItemParas);
		//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	}

	if ((stt_Frame_TestMacroUI() != NULL)&&(m_pMacroEditView!=NULL))//判断当前是否加载了测试功能模块,并判断当前测试功能模块是否为网页
	{
		if (!stt_Frame_TestMacroUI()->IsUIWeb())//更新界面
		{
			CSttMacroParaEditViewOriginal* pOriginal = (CSttMacroParaEditViewOriginal*)m_pMacroEditView;
			pOriginal->UpdateGoutTab(TRUE);//zhouhj20220319 在非网页界面界面时,更新
		}
	}

	UpdateStartStopButtonByItemCount();
}

void QSttTestCntrFrameWin::slot_New_SysConfig()
{
	OnUpdateTestResource(FALSE);
	CExBaseList* pCurSel = (CExBaseList *)m_pSttGbTreeView->GetCurrSelectGbItem();
	CString strParentItemPath = pCurSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	//2022-9-19  lijunqing  同样的代码，出现了好几个地方
	//void stt_GetSystemParasString(CString &strSysParas);
/*
	CSttMacro *pSysConfigMacro = new CSttMacro;
	//		oItemParas.AddNewChild(pSysConfigMacro);
	CSttParas *pSttParas = new CSttParas;
	pSysConfigMacro->AddNewChild(pSttParas);
	CSttDataGroupSerializeRegister oRegister(pSttParas);
	stt_xml_serialize(&g_oSystemParas, &oRegister);
	//此处未完成，需要将系统参数的结构体，转成对象  shaolei
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CString strItemParas = pSysConfigMacro->GetXml(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	delete pSysConfigMacro;
*/
	CString strItemParas;
	CString strItemName = _T("系统参数配置");
	stt_SystemParas_GetString(strItemParas);
	long nRet = g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AddMacro(strParentItemPath, strItemName,
		STT_CMD_TYPE_SYSTEM_SystemConfig, STT_CMD_TYPE_SYSTEM_SystemConfig, strItemParas);

	if (nRet == STT_CMD_ExecStatus_SUCCESS)
	{
		CSttMacroTest *pMacro = new CSttMacroTest;
		pMacro->m_strName = strItemName;
		pMacro->m_strID = STT_CMD_TYPE_SYSTEM_SystemConfig;
		pMacro->m_strMacroID = STT_CMD_TYPE_SYSTEM_SystemConfig;
		pCurSel->AddNewChild(pMacro);
		emit sig_ShowItems_TreeView(pCurSel);
		//m_pSttGbTreeView->ShowBaseList((CExBaseList *)m_pTestCtrlCntrBase->GetGuideBook());

		//同步系统参数到CSttDevice中的m_pSysPara指针
		UpdataSysParaToDevice(strItemParas);
	
		//2022-9-18  lijunqing
		CGbWzdMacroTestAdd *pNew = g_theGbSmartGenWzd->MacroTestAdd(strParentItemPath, pMacro->m_strID, pMacro->m_strName
			, STT_CMD_TYPE_SYSTEM_SystemConfig);
		pNew->SetParas(strItemParas);
		//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	}

	UpdateStartStopButtonByItemCount();
}

void QSttTestCntrFrameWin::slot_ReturnPrevActiveWidget()
{
	disconnect(this, SIGNAL(sig_New_SysConfig()),this,SLOT(slot_New_SysConfig()));
	QSttTestCntrFrameBase::slot_ReturnPrevActiveWidget();
}

void QSttTestCntrFrameWin::slot_SelectTestMacro( CSttMacroTestUI_TestMacroUIRef *pTestMacroUIRef , const CString &strItemsName, const CString &strItemsID)
{
	g_pTheSttTestApp->SetCurrTestMacroUI(pTestMacroUIRef->m_strID);
	OpenMacroTestUI(stt_Frame_TestMacroUI(), strItemsName, strItemsID);

	EndBinStateOnStarting();
	UpdateToolButtons();
	UpdateStartStopButtonByItemCount();
}

void  QSttTestCntrFrameWin::slot_ViewMacroEditWidget(CExBaseObject *pMacroTest)
{
	ViewMacroEditWidget(pMacroTest);
}

//根据装置类型，过滤可供选择的功能
void QSttTestCntrFrameWin::InitTestMacroUI_by_DeviceType(CSttMacroTestUI_TestMacroUIMngr *pTestMacroUIMngr)
{
	if (pTestMacroUIMngr == NULL)
	{
		return;
	}

	if (g_theGbSmartGenWzd == NULL)
	{
		return;
	}

	if (g_theGbSmartGenWzd->m_strDeviceType.isEmpty())
	{
		return;
	}

	POS pos = pTestMacroUIMngr->GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pTestMacroUIMngr->GetNext(pos);

		if (pObj->GetClassID() != MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_GROUP)
		{
			continue;
		}

		if (pObj->m_strID != g_theGbSmartGenWzd->m_strDeviceType)
		{
			pTestMacroUIMngr->Delete(pObj);
		}
	}
}

void QSttTestCntrFrameWin::CloseDevice()
{
	if (m_pEngineClientWidget == NULL)
	{
		return;
	}

	m_pEngineClientWidget->CloseDevice_WhenRelease();
}

void QSttTestCntrFrameWin::ClearReportRslts_Html(QSttReportViewHtml* pHtmlView)
{
	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();

	if (pGuideBook == NULL)
	{
		return;
	}

	CSttDevice *pDevice = pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	POS pos = pDevice->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CString strItemPath;

	while (pos != NULL)
	{
		pObj = pDevice->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pItems = (CSttItems *)pObj;

		if (pItems->m_nSelect == 0)
		{
			continue;
		}

		if (! pItems->IsTypeRootNode())
		{
			ClearReportRslts_Html(pItems, pHtmlView);
			continue;
		}

		stt_gb_get_itempath_id(pItems, strItemPath);

		if (pHtmlView != NULL)
		{
			pHtmlView->ClearRptResults(strItemPath);
		}
		else
		{
			m_pSttReportViewHtml->ClearRptResults(strItemPath);
		}

		ClearReportRslts_Html_SetStateNormal(pItems, pHtmlView);
	}
}

void QSttTestCntrFrameWin::ClearReportRslts_Html(CSttItems *pItems, QSttReportViewHtml* pHtmlView)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CString strItemPath;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != STTGBXMLCLASSID_CSTTITEMS)
		{
			continue;
		}

		CSttItems *pChildItems = (CSttItems *)pObj;

		if (pChildItems->m_nSelect == 0)
		{
			continue;
		}

		if (! pChildItems->IsTypeRootNode())
		{
			ClearReportRslts_Html(pChildItems, pHtmlView);
			continue;
		}

		stt_gb_get_itempath_id(pChildItems, strItemPath);

		if (pHtmlView != NULL)
		{
			pHtmlView->ClearRptResults(strItemPath);
		}
		else
		{
			m_pSttReportViewHtml->ClearRptResults(strItemPath);
		}

		ClearReportRslts_Html_SetStateNormal(pItems, pHtmlView);
	}
}

void QSttTestCntrFrameWin::ClearReportRslts_Html_SetStateNormal(CSttItems *pItems, QSttReportViewHtml* pHtmlView)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CString strParentPath, strItemID;

	while (pos != NULL)
	{
		pObj = pItems->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == STTGBXMLCLASSID_CSTTITEMS)
		{
			CSttItems *pChildItems = (CSttItems *)pObj;
			ClearReportRslts_Html_SetStateNormal(pChildItems, pHtmlView);
			continue;
		}

		if (! Stt_IsGbItemClassID(nClassID))
		{
			continue;
		}
		
		CSttItemBase *pChildItemBase = (CSttItemBase *)pObj;

		strItemID = pChildItemBase->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
		strParentPath = pItems->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

		if (pHtmlView != NULL)
		{
			pHtmlView->ItemStateChanged(strParentPath, strItemID, TEST_STATE_DESC_NORMAL);
		}
		else
		{
			m_pSttReportViewHtml->ItemStateChanged(strParentPath, strItemID, TEST_STATE_DESC_NORMAL);
		}
	}
}

//是否需要添加测试后恢复：默认需要添加
BOOL QSttTestCntrFrameWin::IsNeedAddAft()
{
	if (g_theGbSmartGenWzd == NULL)
	{
		return TRUE;
	}

	CSttGuideBook *pSttGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	ASSERT(pSttGuideBook != NULL);

	if (pSttGuideBook == NULL)
	{
		return TRUE;
	}

	CSttDevice *pDevice = pSttGuideBook->GetDevice();
	ASSERT(pDevice != NULL);

	if (pDevice == NULL)
	{
		return TRUE;
	}

	//装置设置复归态，是一个固定ID的测试分类项目
	CExBaseObject *pDevReset = pDevice->FindByID(STT_ITEMS_ID_DEVRESET);

	if (pDevReset != NULL && g_theGbSmartGenWzd->m_nIsAddDevReset)
	{
		//只有勾选了“添加装置复归态”，并且成功添加了装置复归态项目。才不需要添加测试后恢复
		return FALSE;
	}

	return TRUE;
}

//项目粘贴后，处理报告
void QSttTestCntrFrameWin::ItemPaste_RootNode(CSttItems *pDestItems, CExBaseObject *pCurrentSel)  
{
	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(pDestItems->m_strstxmlFile);
    stt_Frame_SetTestMacroUI(pTestMacroUI);
// 	OpenMacroTestUI(stt_Frame_TestMacroUI(), pDestItems->m_strName, pDestItems->m_strID
// 		, pDestItems->m_nTestTimes, pDestItems->m_nRptTitle, pDestItems->m_nTitleLevel);

	SetActiveWidget(NULL);

	//第一步：创建参数编辑页面、加载报告html页面
	m_pTestCtrlCntrBase->OpenMacroTestUI(pTestMacroUI);

	//2022-3-27  lijunqing  创建参数编辑窗口
	CreateSttMacroParaEditView(pTestMacroUI);

	if (g_nLogDebugInfor == 1)	{		CLogPrint::LogString(XLOGLEVEL_TRACE, ">> begin OpenMacroTestUI 2 >>");	}

	if (pTestMacroUI->IsUIOriginal())
	{//原生态网页，获取页面参数数据
		if (m_pMacroEditView != NULL)
		{
			m_pMacroEditView->GetDatas(m_pTestMacroUI_Paras);
		}
	}
	else//网页界面的矢量图、状态图、信息图在此处统一初始化,原生界面在各自构造函数中初始化 zhouhj 20220329
	{
		InitBinaryIn_WebUI(m_pTestMacroUI_Paras);
		stt_Frame_InitVectorWidget(NULL,NULL);
		stt_Frame_InitPowerWidget(NULL,NULL);
		stt_Frame_InitStateMonitor();
		stt_Frame_ClearInfoWidget();	
	}

	InitAfterCreateSttMacroPara();

	if (pTestMacroUI->HasCharLib()) //2022-6-30  lijunqing
	{
        InitCharLibWidget();
	}

	if (pTestMacroUI->m_strUI_File.GetLength() > 0)
	{
		QSttMacroParaEditViewHtml *pSttMacroParaEditViewHtml = (QSttMacroParaEditViewHtml*)m_pMacroEditView->m_pMacroParaEditWnd;
		pSttMacroParaEditViewHtml->OpenHtmlFile(pTestMacroUI->m_strUI_File);
	}

	AdjustMacroEditWidgetToFrame(pTestMacroUI);
	InitAllButtonStateByTestMacroUI(pTestMacroUI);//根据测试功能初始化工具栏等按钮

	AdjustToolBarButtons();

	AddMacroTestReport(pTestMacroUI, pCurrentSel, pDestItems->m_strName, pDestItems->m_strID);

	CString strParentPath;

	if (pCurrentSel != NULL)
	{
		strParentPath = pCurrentSel->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
	}

	UpdateRptHtml(pDestItems->m_strID,pDestItems->m_strstxmlFile,strParentPath);
}

//校验模型文件是否存在
void QSttTestCntrFrameWin::CheckDvmFileValid(const CString &strDvmFile)
{
	if (IsFileExist(strDvmFile))
	{
		return;
	}

	//2024-10-15 wuxinyi 注释弹窗提示
// 	//文件不存在，提示用户
// 	CString strMsg;
// 	strMsg = _T("检测到模型文件不存在！\r\n");
// 	strMsg += strDvmFile;
// 	strMsg += CString("；请确保模型文件存在，否则将无法正确完成试验！");
// // 	strMsg.Format(_T("检测到模型文件不存在！\r\n%s\r\n；请确保模型文件存在，否则将无法正确完成试验！")
// // 		, strDvmFile.GetString());
// 	CString strTitle;
// 	strTitle = _T("错误！");
// 	CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
}

//形参是从模板中读上来的。打开模板或记录时，更新到界面留存的指针中
void QSttTestCntrFrameWin::InitAinDataMap(CDataGroup *pAinDataMap)
{
	if (pAinDataMap == NULL)
	{
		return;
	}

	POS pos = pAinDataMap->GetHeadPosition();

	while (pos != NULL)
	{
		CDvmData *pAinData = (CDvmData *)pAinDataMap->GetNext(pos);
		CDvmData *pFind = (CDvmData *)m_pAinDataMapCfg->FindByID(pAinData->m_strID);

		if (pFind == NULL)
		{
			pFind = m_pAinDataMapCfg->AddNewData(pAinData->m_strID, pAinData->m_strValue);
		}

		pFind->m_strDataType = pAinData->m_strDataType;

		if (pAinData->m_strName.GetLength() > 0)
		{
			pFind->m_strName = pAinData->m_strName;
		}
		
		pFind->m_strValue = pAinData->m_strValue;
	}
}

BOOL QSttTestCntrFrameWin::IsNeedSendAsync(const CString &strItemsID)
{
	//针对数据量大，底层生成模板慢的，采用异步方式。例如：遥测试验中的谐波影响试验
	//若同步发送方式，则应答时间超过5秒，会被认定为超时
	if (strItemsID.Find(_T("HarmChangeTest")) >= 0)
	{
		return TRUE;
	}

	return FALSE;
}

void QSttTestCntrFrameWin::closeEvent( QCloseEvent * event )
{
	m_bHasClosedUI = TRUE;
	SaveCharacteristicsData();
	CloseIecCapDetect();
	setEnabled(false);

#ifdef use_CSmartCapCtrl
    if (g_pSttMUTestIecCbSelWidget != NULL)
	{
		delete g_pSttMUTestIecCbSelWidget;
		g_pSttMUTestIecCbSelWidget = NULL;
	}
#endif

	if (!IsAutoTest())//zhouhj 2023.7.21 暂时只在单机软件时使用,防止通讯命令还未执行完全
	{
		CTickCount32 oTickCount;

		while(CSttCmdOverTimeTool::HasCmdUsing())
		{
			oTickCount.DoEvents(100);
		}
	}

	if (m_pResultWidget)
	{
		m_pResultWidget->LogString(0, "等待测试服务停止后关闭.");
	}

	CloseDevice();
	m_pTestCtrlCntrBase->CloseTest();
	g_pTheSttTestApp->ExitSmartTest();
	g_pTheSttTestApp->ExitSttTestApp();
//	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
//	pNative->ExitMeasServer();
//	QCoreApplication::removePostedEvents(this);
	QMainWindow::closeEvent(event);
}

BOOL QSttTestCntrFrameWin::GetItemsTitleString(const CString &strItemsPath,char **ppszReport,long &nLen)
{
	if (m_pTestCtrlCntrBase == NULL)
	{
		return FALSE;
	}

	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();

	if (pGuideBook == NULL)
	{
		return FALSE;
	}

// 	char *pszReport = NULL;
// 	long nLen = 0;
	CDataGroup oDataGroup;
 	CDvmData *pData = NULL;
// 	pData->m_strName = pCurrItem->m_strName;
// 	pData->m_strValue = pCurrItem->m_strName;
// 	pData->m_strID = _T("$");
// 	oDataGroup.AddNewChild(pData);
// 	stt_gb_get_all_child_title_itembase(pCurrItem,&oDataGroup,strItemsID);
	POS pos = g_theGbSmartGenWzd->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	CGbWzdItemEdit *pGbWzdItemEdit = NULL;
	CString strEditItem_CurrItemPath,strTmpLeft,strTmpRight;
	long nEditItemCurrItemPath_Lenth = 0,nRootItem_Lenth = 0;

	while(pos)
	{
		pCurrObj = g_theGbSmartGenWzd->GetNext(pos);

		if (pCurrObj->GetClassID() != DVMCLASSID_GBWZDITEMEDIT)
		{
			continue;
		}

		pGbWzdItemEdit = (CGbWzdItemEdit *)pCurrObj;

		if (pGbWzdItemEdit->m_strParentItemsID.IsEmpty())
		{
			strEditItem_CurrItemPath = pGbWzdItemEdit->m_strItemsID;
		} 
		else
		{
			strEditItem_CurrItemPath = pGbWzdItemEdit->m_strParentItemsID;
			strEditItem_CurrItemPath += _T("$");
			strEditItem_CurrItemPath += pGbWzdItemEdit->m_strItemsID;
		} 

		nEditItemCurrItemPath_Lenth = strEditItem_CurrItemPath.GetLength();
		nRootItem_Lenth = strItemsPath.GetLength();

		if (nEditItemCurrItemPath_Lenth < nRootItem_Lenth)
		{
			continue;
		}

		strTmpLeft = strEditItem_CurrItemPath.Left(nRootItem_Lenth);
		strTmpRight = strEditItem_CurrItemPath.Mid(nRootItem_Lenth);

		if (strTmpLeft != strItemsPath)
		{
			continue;
		}

		pData = new CDvmData;
		oDataGroup.AddNewChild(pData);
		pData->m_strValue = pGbWzdItemEdit->m_strItemsName;
		pData->m_strName = pGbWzdItemEdit->m_strItemsName;

		if (strTmpRight.IsEmpty())
		{
			pData->m_strID = _T("$");
		}
		else
		{
			pData->m_strID = strTmpRight;
		}
	}

	CSttItemBase *pCurrItem = stt_gb_find_itembase(pGuideBook, strItemsPath);

	if (pCurrItem != NULL)
	{
		pData = (CDvmData*)oDataGroup.FindByID(_T("$"));

		if (pData == NULL)
		{
			pData = new CDvmData;
			pData->m_strID = _T("$");
			oDataGroup.AddNewChild(pData);
		}

		pData->m_strName = pCurrItem->m_strName;
		pData->m_strValue = pCurrItem->m_strName;
	}

	if (oDataGroup.GetCount() <= 0)
	{
		return FALSE;
	}

	oDataGroup.GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, ppszReport, nLen, _JSON_TYPE_);

// 	if (nLen<= 0)
// 	{
// 		return FALSE;
// 	}
// 
// 	CExBaseObject *pCurrObj = new CExBaseObject;
// 	pCurrObj->m_strID = strItemsID;
// 	pCurrObj->m_dwItemData = (DWORD)pszReport;
//	m_oSttItemsRptTileList.AddNewChild(pCurrObj);
	return TRUE;
}

void QSttTestCntrFrameWin::OnCmd_TransPcapFile()
{
#ifdef use_CSmartCapCtrl
    QSttExportPcapFileDialog oSttExportPcapFileDialog(this);
	oSttExportPcapFileDialog.InitUI();
	oSttExportPcapFileDialog.exec();
#endif  //use_CSmartCapCtrl
}

void QSttTestCntrFrameWin::OnCmd_ImportDvmFile()
{
	CString strFile = OpenDvmFileDlg(_T(""), TRUE);

	if (strFile.GetLength() <= 4)
	{
		return;
	}

	if (g_theGbSmartGenWzd->m_strDvmFile == strFile)
	{
		CString strMsg;
		strMsg = _T("当前模型文件与待导入模型一致，是否继续导入。导入将需要重新整定定值、压板等参数");
		CString strTitle;
		strTitle = _T("模型文件一致");
		int result = CXMessageBox::information(this, strTitle, strMsg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

		if (result != QMessageBox::Yes)
		{
			return;
		}
	}

	if (m_pCmdWzdDsEditWidget != NULL)
	{
		//导入模型时，不进行参数保存
		m_pCmdWzdDsEditWidget->m_bAutoSave = FALSE;
		m_pCmdWzdDsEditWidget->m_pCurrCmdItem = NULL;
		DeleteCmdWzdDsEditWidget();
	}

	if (m_pEngineClientWidget != NULL)
	{
		disconnect(m_pEngineClientWidget,  SIGNAL(sig_OnConfigDevice(CDataGroup *)), this, SLOT(slot_OnConfigDevice(CDataGroup *)));
		m_tabTestViews->removeTab(m_tabTestViews->indexOf(m_pEngineClientWidget));  //关闭原来的“通讯后台”
		delete m_pEngineClientWidget;
		m_pEngineClientWidget = NULL;
	}

	ClearAllAinDataMap();//清空所有已经映射的遥测参数
	CString strDvmFile = g_theGbSmartGenWzd->ImportDvmFile(strFile);
	g_theGbSmartGenWzd->AfterImportDvmFile();//导入模型后，清理跟commcmd相关的记录
	//g_theGbSmartGenWzd->SaveSmartGenWzdFile();
	OnCmd_PpIotEngineClient();//重新打开通讯后台

	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_ImportDvmFile(strFile);

	//刷新模板树中的名称
	CSttGuideBook *pGuideBook = (CSttGuideBook*)m_pTestCtrlCntrBase->GetGuideBook();
	CString strName = GetFileTitleFromFilePath(strDvmFile, '/');
	pGuideBook->SetGuideBookName(strName);

	//刷新项目树的根节点名称显示
	CSttDevice *pDevice = pGuideBook->GetDevice();
	emit sig_ShowItems_TreeView((CExBaseList *)pDevice);
}

//2023/8/29 wjs 遥测试验
void QSttTestCntrFrameWin::OnCmd_AinDataMapConfig()
{
	CSttGuideBook *pGuideBook = (CSttGuideBook *)m_pTestCtrlCntrBase->GetGuideBook();
	CDataGroup *pAinRatios = pGuideBook->GetAinRatios();

	if (m_pAinRatios != NULL)
	{
		delete m_pAinRatios;
	}

	m_pAinRatios = pAinRatios;
	QAinDataMapDlg oAinDataMapDlg(this, m_pAinDataMapCfg, m_pAinRatios);
	oAinDataMapDlg.setWindowTitle("遥测参数映射");

	if (oAinDataMapDlg.exec() != QDialog::Accepted)
	{
		return;
	}

	if (m_pCmdWzdDsEditWidget != NULL)
	{
		DeleteCmdWzdDsEditWidget();
	}

	//下发遥测参数映射的指令
	CDataGroup *pAinDataMap = oAinDataMapDlg.GetAinDataMap();
	CDataGroup *pAinRatiosCfg = oAinDataMapDlg.GetAinRatios();
	m_pAinDataMapCfg = pAinDataMap;
	m_pAinRatios = pAinRatiosCfg;
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_AinDataMap(pAinDataMap, pAinRatiosCfg);
	pGuideBook->SetAinDataMapCfg(pAinDataMap);
	pGuideBook->SetAinRatios(pAinRatiosCfg);  //放到全局数据里面
}

void QSttTestCntrFrameWin::OnCmd_OutputDebug()
{
	QOutPutDebug dlg(this);
	//dlg.InitUI();

#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg, Keyboard::ENGLISH);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();	
#endif
}

void QSttTestCntrFrameWin::UpdateRptHtml(const CString &strItemsID,const CString &strMacroUI_ID,const CString &strParentPath)
{
	if (m_pSttReportViewHtml == NULL)
	{
		return;
	}

	if (strMacroUI_ID.IsEmpty())
	{
		return;
	}

	char *strReport = NULL;
	long nLen = 0;

	CString strCurItemPath;

	if (strParentPath.IsEmpty())
	{
		strCurItemPath = strItemsID;
	} 
	else
	{
		strCurItemPath = strParentPath;
		strCurItemPath += _T("$"); 
		strCurItemPath += strItemsID; 
	}

	GetMacroItemsXml(strItemsID, &strReport, nLen,strParentPath);

	CSttMacroTestUI_TestMacroUI *pTestMacroUI = CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(strMacroUI_ID);

	if ((nLen > 0)&& (pTestMacroUI!= NULL))
	{
		m_pSttReportViewHtml->AddUpdateCmd(pTestMacroUI, strParentPath, strItemsID, strReport);

// 		CExBaseObject *pRptTitleObj = m_oSttItemsRptTileList.FindByID(strItemsID);
// 
// 		if (pRptTitleObj != NULL)
// 		{
// 			m_pSttReportViewHtml->AddFillRptTitleCmd(strItemsID, (const char*)pRptTitleObj->m_dwItemData);
// 			m_oSttItemsRptTileList.Delete(pRptTitleObj);
// 		}
		strReport = NULL;
		nLen = 0;

		if (GetItemsTitleString(strCurItemPath,&strReport,nLen))
		{
			m_pSttReportViewHtml->AddFillRptTitleCmd(strCurItemPath, strReport);
		}
	}
}

void QSttTestCntrFrameWin::GetMacroItemsXml(const CString strItemID, char **ppszReport, long &nLen,const CString &strParentPath)
{
	CString strIDMacroUI = g_pTheSttTestApp->GetCurrTestMacroUI();
	//CString strMacroID = stt_Frame_TestMacroUI()->m_strID;

	if(g_pTheSttTestApp->IsTestMacro_CurrVolChAsItem())
	{
		nLen = m_pMacroEditView->GetMacroItemsXml(strItemID, ppszReport);
	}
	else
	{
		nLen = m_pTestCtrlCntrBase->GetMacroItemsXml(strItemID, ppszReport,strParentPath);
	}
}

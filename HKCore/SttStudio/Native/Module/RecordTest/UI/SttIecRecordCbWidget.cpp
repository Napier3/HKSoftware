#include "SttIecRecordCbWidget.h"
#include "ui_SttIecRecordCbWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../Module/SmartCap/XSmartCapMngr.h"
#include "../../Module/BaseClass/QT/ExBaseListComboBox.h"
#include "../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../XLangResource_Native.h"

#include "SttIecRecordMainWidget.h"
#include "SttIecRecordDetectWidget.h"
#include "SttIecSmvGrid_ChQualitySpy.h"
#include "SttIecSmvGrid_EffecValue.h"
#include "SttIecSmvWaveMainWidget.h"
#include "SttIecSmvGrid_Power.h"
#include "SttIecSmvGrid_Harm.h"
#include "SttIecSmvGrid_PkgError.h"
#include "SttIecSmvGrid_AD.h"
#include "SttIecMUAccuracyWidget.h"
#include "SttIecMUTimeWidget.h"
#include "SttIecSmvGrid_MUErrorStatis.h"
#include "SttIecGooseGrid_RT.h"
#include "SttIecGooseGrid_TurnList.h"
#include "SttIecGooseGrid_PkgError.h"
#include "SttIecEmptyWidget.h"
#include "SttIecSmvVectorWidget.h"
#include "SttIecSmvSequenceWidget.h"
#include "SttIecSmvMeterAxisWidget.h"
#include "SttIecSmvGrid_ChAttr.h"
#include "SttIecSmvGrid_PkgAnalyze.h"
#include "SttIecGooseGrid_PkgAnalyze.h"
#include "SttIecGooseTurnSpyWidget.h"
#include "SttIecRecordWriteFileWidget.h"
#include "FT3_Test/SttIecFT3Grid_RT.h"
#include "FT3_Test/SttIecFT3OriginalMsgWidget.h"

extern QSttIecRecordMainWidget *g_theSttIecRecordMainWidget;
extern QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget;

QSttIecRecordCbWidget::QSttIecRecordCbWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttIecRecordCbWidget)
{
	g_pSttIecRecordCbWidget = this;
    ui->setupUi(this);
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	xlang_SetLangStrToWidget(ui->m_lblSelCb, "Smv_SelCb",XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_lblSelFunc, "Smv_SelFunc", XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget(ui->m_btnBack, "sBack", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnPrevPage, "Smv_PrevPage", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnNextPage, "Smv_NextPage", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnSysSet, "Smv_SysSet", XLang_Ctrls_QPushButton);

// #ifdef _PSX_QT_LINUX_ 
//     ui->m_btnAddToPub->hide();
// 	ui->m_btnAddToSub->hide();
// #endif

	m_cmbCb = new QScrollComboBox;
	m_cmbCb->setObjectName("m_cmbCb");
	m_cmbCb->SetBoxSize(20, 30);
	connect(m_cmbCb, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CbCurrentIndexChanged(int)));
	ui->m_layButtons->insertWidget(1, m_cmbCb);

	m_cmbFunc = new QScrollComboBox;
	m_cmbFunc->setObjectName("m_cmbFunc");
	m_cmbFunc->SetBoxSize(20, 30);
	m_cmbFunc->setMaxVisibleItems(14);
	connect(m_cmbFunc, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_FuncCurrentIndexChanged(int)));
	connect(this, SIGNAL(sig_UpdateSVDatasetsPowerVector()), this, SLOT(slot_UpdateSVDatasetsPowerVector()));
	ui->m_layButtons->insertWidget(3, m_cmbFunc);

	m_pCurrCapDevice = NULL;
//	m_pSelectedCbs = NULL;
	m_pSttIecRcdFuncInterface = NULL;
//    m_pGridIecCb = new CSttIecCbGrid(this);
//    m_pGridIecCb->InitGrid();
//     ui->verticalLayout->insertWidget(0,m_pGridIecCb);

	//д�ļ����ڿؼ���ʼ��
	CString strText;
	strText = /*("¼��ʱ��")*/g_sLangTxt_Native_RecTime;
	m_pWriteFileTime_Label = new QLabel(strText);
	strText = /*_T("�ļ���С")*/g_sLangTxt_FileSize;
	m_pWriteFileSize_Label = new QLabel(strText);
	m_pWriteFileTime_Edit = new QLineEdit;
	m_pWriteFileSize_Edit = new QLineEdit;

	m_pWriteFileTime_Edit->setStyleSheet("color: black;");//2024-1-3 suyang ������ʾ������������������ɫ //�Ӵ�font-weight: bold;
	m_pWriteFileSize_Edit->setStyleSheet("color: black; ");

	m_pSttRcdWriteFileWidget = NULL;

	m_pWriteFileSize_Edit->setEnabled(false);
	m_pWriteFileTime_Edit->setEnabled(false);

	ui->m_layButtons->insertWidget(0, m_pWriteFileTime_Label);
	ui->m_layButtons->insertWidget(1, m_pWriteFileTime_Edit);
	ui->m_layButtons->insertWidget(2, m_pWriteFileSize_Label);
	ui->m_layButtons->insertWidget(3, m_pWriteFileSize_Edit);

	m_pWriteFileTime_Label->hide();
	m_pWriteFileSize_Label->hide();
	m_pWriteFileTime_Edit->hide();
	m_pWriteFileSize_Edit->hide();

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SttIecRcdFuncs.xml");
	m_oIecRcdDataTypes.Open(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(&m_oIecRcdDataTypes, _T("SttIecRcdFuncs.xml"));
#endif

	m_pCurrIecRcdFucsDataType = NULL;
	m_pDataType_SttIecRcdSmvFuncs = (CDataType*)m_oIecRcdDataTypes.FindByID(_T("SttIecRcdSmvFuncs"));
	m_pDataType_SttIecRcdGooseFuncs = (CDataType*)m_oIecRcdDataTypes.FindByID(_T("SttIecRcdGooseFuncs"));
	m_pDataType_SttIecRcdMUFuncs = (CDataType*)m_oIecRcdDataTypes.FindByID(_T("SttIecRcdMUFuncs"));
	m_pDataType_SttIecRcdFT3Funcs = (CDataType*)m_oIecRcdDataTypes.FindByID(_T("SttIecRcdFT3Funcs"));
	
	//m_nHarmDisplayIndex = 0;
	m_cmbHarmDisplay = CombHarmDisplayType();
	m_cmbHarmDisplay->setObjectName("m_cmbHarmDisplay");
	m_cmbHarmDisplay->SetBoxSize(20, 30);
	m_cmbHarmDisplay->setMaxVisibleItems(14);
	connect(m_cmbHarmDisplay, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_CbHarmDisplayIndexChanged(int)));

	connect(&m_oTimerIecRcdUpdate,   SIGNAL(timeout()),    this,   SLOT(slot_Timer_IecRcdUpdate()));

	SetIecRecordCbFont();
}

QSttIecRecordCbWidget::~QSttIecRecordCbWidget()
{
	m_oTimerIecRcdUpdate.stop();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->Release();
		m_pSttIecRcdFuncInterface = NULL;
	}

	if(m_cmbFunc)
	{
		delete m_cmbFunc;
		m_cmbFunc = NULL;
	}

	if(m_cmbCb)
	{
		delete m_cmbCb;
		m_cmbCb = NULL;
	}

	if(m_cmbHarmDisplay)
	{
		delete m_cmbHarmDisplay;
		m_cmbHarmDisplay = NULL;
	}

    delete ui;
}

//////////////////////////////////////////////////////////////////////////
//CSttWndAssistInterface
//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
CSttWndAssistInterface* QSttIecRecordCbWidget::ast_FindWnd(const CString &strWndID)
{

	return NULL;
}

//����ִ�нӿ�
bool QSttIecRecordCbWidget::ast_ExecCmd(const CString &strCmdID,const CString &strParas)
{

	return false;
}

bool QSttIecRecordCbWidget::ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID)
{

	return false;
}

bool QSttIecRecordCbWidget::ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile)
{

	return false;
}

//////////////////////////////////////////////////////////////////////////


void QSttIecRecordCbWidget::HarmFuncType()//г����ʾ�ɼ����
{	
	if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Harm)
	{
		ui->m_layButtons->insertWidget(12, m_cmbHarmDisplay);
		ui->m_lblHarmDisplay->setVisible(true);
		m_cmbHarmDisplay->setVisible(true);
	}
	else
	{
		ui->m_lblHarmDisplay->setVisible(false);
		m_cmbHarmDisplay->setVisible(false);
	}
}

void QSttIecRecordCbWidget::SetIecRecordCbFont()
{
	ui->m_lblSelCb->setFont(*g_pSttGlobalFont);
	ui->m_lblSelFunc->setFont(*g_pSttGlobalFont);
	ui->m_btnPrevPage->setFont(*g_pSttGlobalFont);
	ui->m_btnNextPage->setFont(*g_pSttGlobalFont);
	ui->m_btnSysSet->setFont(*g_pSttGlobalFont);
	ui->m_btnBack->setFont(*g_pSttGlobalFont);
	m_cmbFunc->setFont(*g_pSttGlobalFont);
	m_cmbCb->setFont(*g_pSttGlobalFont);
	m_cmbHarmDisplay->setFont(*g_pSttGlobalFont);

	ui->m_btnAddToSub->setFont(*g_pSttGlobalFont);
	ui->m_btnAddToPub->setFont(*g_pSttGlobalFont);
	ui->m_lblHarmDisplay->setFont(*g_pSttGlobalFont);
	m_pWriteFileTime_Label->setFont(*g_pSttGlobalFont);
	m_pWriteFileSize_Label->setFont(*g_pSttGlobalFont);
	m_pWriteFileTime_Edit->setFont(*g_pSttGlobalFont);
	m_pWriteFileSize_Edit->setFont(*g_pSttGlobalFont); 

}

void QSttIecRecordCbWidget::slot_CbCurrentIndexChanged(int index)
{
	if (index < 0)
	{
		return;
	}

	if(m_cmbCb->IsScrolling())
	{
		return;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pSelectedCbs->GetAtIndex(index);
	SetCapDevice(pCapDevice);
	ui->m_btnAddToSub->setEnabled(m_pSttIecRcdFuncInterface->IsToSubBtn());
}

void QSttIecRecordCbWidget::slot_FuncCurrentIndexChanged(int index)
{
    if(index < 0)
    {
        return;
    }

	if(m_cmbFunc->IsScrolling())
	{
		return;
	}

	if (m_bInSetCapDevice)
	{//�����ڵ�ǰ�豸���µ�ʱ�򣬸�����Func������������SetCapDevice�����д���
		return;
	}

	OnCurrFuncChanged(index);
}

void QSttIecRecordCbWidget::slot_CbHarmDisplayIndexChanged(int index)
{
	if (index < 0)
	{
		return;
	}

	if(m_cmbHarmDisplay->IsScrolling())
	{
		return;
	}
	
	m_pSttIecSmvWidget_Harm->HarmFunc_Create(index);
 	m_pSttIecRcdFuncInterface = m_pSttIecSmvWidget_Harm->m_pSttIecRcdFuncInterface;
	ui->verticalLayout->insertWidget(0, m_pSttIecRcdFuncInterface->m_pIecRcdFuncWidget);
	m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
	

	if (m_pSttIecRcdFuncInterface->NeedNextAndPrev())
	{
		ui->m_btnNextPage->show();
		ui->m_btnPrevPage->show();
		}
	else
		{
		ui->m_btnNextPage->hide();
		ui->m_btnPrevPage->hide();
		}
}


void QSttIecRecordCbWidget::OnCurrFuncChanged(long nIndex)
{
	if (nIndex < 0)
	{
		nIndex = m_cmbFunc->currentIndex();
	}

	CDataTypeValue *pValue = (CDataTypeValue*)m_pCurrIecRcdFucsDataType->GetAtIndex(nIndex);
	m_strIecRcdFuncID = pValue->m_strID;

	//m_cmbHarmDisplay->setCurrentIndex(0);
	
	ExecIecFunc();
}

void QSttIecRecordCbWidget::UpdateSVDatasetsPowerVector()
{
	emit sig_UpdateSVDatasetsPowerVector();
}

void QSttIecRecordCbWidget::on_m_btnBack_clicked()
{
	BtnBack();
}

void QSttIecRecordCbWidget::on_m_btnSysSet_clicked()
{
	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->Config();

		//2023/11/24 wangjunsheng 
		//UpdateRecordFileState();
		if(m_pSttIecRcdFuncInterface->m_strIecRcdFuncID == IECRCD_FUNC_Write_File)
		{
			CString strBtnText;
			if (m_pSttRcdWriteFileWidget->m_bIsStartRecord)
			{
// 				strBtnText = _T("¼��");
				strBtnText = g_sLangTxt_Native_RecWaveform.GetString();
			} 
			else
			{
// 				strBtnText = _T("ֹͣ¼��");
				strBtnText = g_sLangTxt_Native_StopRecrd.GetString();
			}
			
			ui->m_btnSysSet->setText(strBtnText);
			
		}

	}
}

void QSttIecRecordCbWidget::BtnBack()
{
	if (m_pSttIecRcdFuncInterface != NULL)
	{
		if (m_pSttIecRcdFuncInterface->m_strIecRcdFuncID == IECRCD_FUNC_Write_File)
		{
			QSttIecRecordWriteFileWidget *pWriteFileWidget = 
				(QSttIecRecordWriteFileWidget*)m_pSttIecRcdFuncInterface->m_pIecRcdFuncWidget;

			//2023/11/23 wangjunsheng ֱ�ӷ���ʱ�ŵ����Ƿ񱣴�
			if (!pWriteFileWidget->HasSaveAsWriteFile())
			{
				pWriteFileWidget->Config();
			}
		}
	}

	g_bSmartCap_RecordNow = FALSE;  //2022-5-3  lijunqing stop record

	Ats_IecRecord_Stop();
	m_oTimerIecRcdUpdate.stop();

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
#ifdef _XSmartCap_use_SttRcdSocket_
	g_theXSmartCapMngr->StopCap();
	pXSttCap_61850->DisConnectServer();
#endif
	//2024-04-29 wuxinyi ������ز���
	pXSttCap_61850->ClearPara();


	g_theSttIecRecordMainWidget->ShowIecDetectWindow();

	if ( m_pSttIecRcdFuncInterface != NULL )
	{
		m_pSttIecRcdFuncInterface->Release();
		m_pSttIecRcdFuncInterface = NULL;
	}

// #ifndef _PSX_QT_LINUX_//20230703 ��Window��,ͬʱ����һ�ݵ�e-Protocol��,���Զ�����ʹ��
	CString strFile;
	strFile = _P_GetLibraryPath();
//	CreateAllDirectories(strFile)
	strFile += _T("SttIecRecordDetectDvm001.xml");
	pXSttCap_61850->m_pDvmDevice->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
// #endif

	//���¼����ɾ���������ݼ�
//	g_theXSmartCapMngr->InitSmartCapCtrl();//20220919 ��ʱȥ����ɾ������,��ֹ�������ý�����Ӻ�,�˳����½���,֮ǰ����������ѱ�ɾ��
}

// void QSttIecRecordCbWidget::Connect_UpdateMUTimeAccurRlt(BOOL bCoonect)
// {
// 	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
// 
// 	if ((m_pSVDelayData != NULL)&&(pXSttCap_61850!= NULL))
// 	{
// 		if (bCoonect)
// 		{
// 			connect(this, SIGNAL(sig_UpdateMUTimeAccurRlt(CDvmData*)), g_theTestCntrFrame, 
// 				SLOT(slot_UpdateMUTimeAccurRlt(CDvmData*)));
// 		}
// 	}
// }

void QSttIecRecordCbWidget::SetEnable_BtnBack(bool bEnable)
{
	ui->m_btnBack->setEnabled(bEnable);
}

BOOL QSttIecRecordCbWidget::InitFuncTypeComboBox(CCapDeviceBase *pCapDevice)
{
	if (m_pCurrCapDevice != NULL)
	{
		if (m_pCurrCapDevice->m_nType == pCapDevice->m_nType)
		{//��ǰCapDevice��Ϊ�գ���������CapDevice������һ�£��򲻸��¹���ComboBox
			return FALSE;
		}
	}

	long nDefaultIndex = 0;

	if (pCapDevice->m_nType == PROTOCOL_61850_TYPE_GOOSE)
	{
		m_pCurrIecRcdFucsDataType = m_pDataType_SttIecRcdGooseFuncs;
	}
	else if ((pCapDevice->m_nType == PROTOCOL_61850_TYPE_6044)&&(m_pDataType_SttIecRcdFT3Funcs != NULL))
	{
		m_pCurrIecRcdFucsDataType = m_pDataType_SttIecRcdFT3Funcs;
	}
	else if ((m_bMUTestMode)&&(m_pDataType_SttIecRcdMUFuncs != NULL))
	{
		m_pCurrIecRcdFucsDataType = m_pDataType_SttIecRcdMUFuncs;
	}
	else
	{
		m_pCurrIecRcdFucsDataType = m_pDataType_SttIecRcdSmvFuncs;

// 		if (m_bMUTestMode)
// 		{
// 			CExBaseObject *pCurrObj = m_pDataType_SttIecRcdSmvFuncs->FindByID(m_strIecRcdFuncID);
// 
// 			if (pCurrObj != NULL)
// 			{
// 				nDefaultIndex = m_pDataType_SttIecRcdSmvFuncs->FindIndex(pCurrObj);
// 			}
// 		}
	}

	ex_InsertChildreComboBox(m_pCurrIecRcdFucsDataType, m_cmbFunc);
	m_cmbFunc->setCurrentIndex(nDefaultIndex);

	return TRUE;
}

void QSttIecRecordCbWidget::SetCapDevice(CCapDeviceBase *pCapDevice)
{
	if (m_pCurrCapDevice != NULL)
	{
		if (pCapDevice->IsSameType(m_pCurrCapDevice->m_nType)
			&& (pCapDevice->m_dwAppID == m_pCurrCapDevice->m_dwAppID)
			&&(pCapDevice->m_nFiberIndex == m_pCurrCapDevice->m_nFiberIndex))
		{
			return;
		}
	}

	//��ʾΪ����CapDevice״̬����ʱ�����Ϊ�����б����´����ı仯����������
	m_bInSetCapDevice = TRUE;

	InitFuncTypeComboBox(pCapDevice);
	m_pCurrCapDevice = pCapDevice; 
	OnCurrFuncChanged(-1);
	m_bInSetCapDevice = FALSE;

// 	if (pCapDevice->GetCount()>0)
// 	{
// 		UpdateCapDevice(pCapDevice);
// 	}
}

void QSttIecRecordCbWidget::SetSelectedCbs(CExBaseList *pSelectedCbs)
{
	m_pSelectedCbs = pSelectedCbs;
	ex_InsertChildreComboBox(m_pSelectedCbs, m_cmbCb);
	m_cmbCb->setCurrentIndex(0);
}

void QSttIecRecordCbWidget::Ats_IecRecord(BOOL bIsFromIecfgFile)
{
	m_oTimerIecRcdUpdate.stop();

	//if (bIsFromIecfgFile)
	{
		//����Ǵ������ļ����룬������¼��
		//2022-6-11 lijunqing ̽�ⷵ����ͨ�������κ�����£�����¼��
		RecordCapDevice();
	}

    CDataGroup oMacroParas;
    g_theXSmartCapMngr->GetSttCapParas(&oMacroParas, g_pSttIecRecordDetectWidget->m_bViewSmv,
		g_pSttIecRecordDetectWidget->m_bViewGoose,g_pSttIecRecordDetectWidget->m_bViewFT3);
    oMacroParas.AddNewData(_T("Enable"), (long)1);
    oMacroParas.AddNewData(_T("Mode"), (long)1);

	if (CXCapPkgBufferMngrInterface::Is_XSmartCapDebugHead())
	{//����ǵ��Ա���ͷ��ģʽ�����·�������DebugHead��
		oMacroParas.AddNewData(_T("DebugHead"), (long)1);  //���Ա���ͷ
	}

	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
    pNative->Ats_IecRecord(&oMacroParas);

	//for debug====  400 �޸�ˢ��Ƶ��
    m_oTimerIecRcdUpdate.start(m_fIecRcdTimer*1000/*500*/);
}

void QSttIecRecordCbWidget::Ats_IecRecord_Stop()
{
    CDataGroup oMacroParas;
    oMacroParas.AddNewData(_T("Enable"), (long)0);
    CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
    pNative->Ats_IecRecord(&oMacroParas);
}

void QSttIecRecordCbWidget::InitIecRecordCb(const CString &strIecFunc)
{
	m_strIecRcdFuncID = strIecFunc;
	m_pCurrCapDevice = NULL;
}

// void QSttIecRecordCbWidget::UpdateCapDevice(CCapDeviceBase *pCapDevice)
// {//����װ�ã������ǰװ������Ҫ���µ�װ�ã������
// 	//2022-6-11  lijunqing �˺�����Ƶĳ�������Ϊ̽���ʱ��û�з���ͨ����
// 	//����Ҫ��̬���ӵ�RecordDevice�У��°汾������ͨ�������˺���������������
// 	//if (m_pCurrCapDevice == pCapDevice)
// 	//{
// 	//	RecordCapDevice(pCapDevice);
// 	//}
// 
// 	//20022-6-11 lijunqing �����Ƿ�������ͨ������ƥ���������½��棬�����޸�
// 	//????????????????????????????????????????
// }

void QSttIecRecordCbWidget::RecordCapDevice(CCapDeviceBase *pCapDevice)
{
	if (m_pCurrCapDevice != NULL)
	{
		if (m_pCurrCapDevice != pCapDevice)
		{
			//ֹͣ¼��m_pCurrCapDevice
		}
	}

	m_pCurrCapDevice = pCapDevice;
	g_theXSmartCapMngr->RecordDevice(pCapDevice);
	
	//DvmDevice��ʼ�������û�й������豸�������豸����ģ��dsSv
	g_theXSmartCapMngr->InitDvmDevice(pCapDevice);
	g_theXSmartCapMngr->IecAnalysis_AddDatasets();

	//����DvmDevice��RecordTest
	//CCapDeviceChRecordMngr::InitRecordTest()
	g_theXSmartCapMngr->m_pX61850Cap->BeginRecord();
	g_theXSmartCapMngr->m_pX61850Cap->Init_SV_Channels();
	g_theXSmartCapMngr->m_pX61850Cap->Init_GS_Channels();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->IecRcdFunc(pCapDevice);
	}
}

void QSttIecRecordCbWidget::RecordCapDevice()
{
	g_theXSmartCapMngr->m_pX61850Cap->RecordDevices();

	//����DvmDevice��RecordTest
	g_theXSmartCapMngr->m_pX61850Cap->BeginRecord();
	g_theXSmartCapMngr->m_pX61850Cap->Init_SV_Channels();
	g_theXSmartCapMngr->m_pX61850Cap->Init_GS_Channels();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
	}
}

void QSttIecRecordCbWidget::ExecIecFunc(const CString &strIecfFunc)
{
	m_strIecRcdFuncID = strIecfFunc;
	ExecIecFunc();
}

void QSttIecRecordCbWidget::ExecIecFunc_Create()
{
	CString strSysSetString= /*tr("�������")*/g_sLangTxt_Smv_Rates;//Ŀǰϵͳ������,ֻ�б������,��Ϊ�������,�û�����ȷ
//	CString strSysSetString= tr("ϵͳ����");
//	xlang_GetLangStrByFile(strSysSetString, "Smv_SysSet");

#ifndef _PSX_QT_LINUX_
	if (m_bMUTestMode)
	{
		strSysSetString = /*_T("����ͨ��")*/g_sLangTxt_Gradient_RecvChannnel;
	}
#endif
	//SMV   ͨ������
	if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_ChQualitySpy)
	{
		g_oCapAnalysisConfig.Smv_ChQualitySpy();
		CSttIecSmvGrid_ChQualitySpy *pGrid = new CSttIecSmvGrid_ChQualitySpy(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   ͨ������
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_ChAttr)
	{
		g_oCapAnalysisConfig.Smv_EffecValue();
		CSttIecSmvGrid_ChAttr *pGrid = new CSttIecSmvGrid_ChAttr(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV  ��Чֵ
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_EffecValue)
	{
		g_oCapAnalysisConfig.Smv_EffecValue();
		CSttIecSmvGrid_EffecValue *pGrid = new CSttIecSmvGrid_EffecValue(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   ���η���
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Wave)
	{
		g_oCapAnalysisConfig.Smv_Wave();
		//QSttIecSmvWaveWidget *pWave = new QSttIecSmvWaveWidget(this);
		QSttIecSmvWaveMainWidget*pWave = new QSttIecSmvWaveMainWidget(this);
		m_pSttIecRcdFuncInterface = pWave;
	}
	//SMV   ����
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Power)
	{
		g_oCapAnalysisConfig.Smv_Power();
		CSttIecSmvGrid_Power *pGrid = new CSttIecSmvGrid_Power(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   г��
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Harm)
	{
		g_oCapAnalysisConfig.Smv_Harm();
		CSttIecSmvWidget_Harm *pSttIecSmvWidget_Harm = new CSttIecSmvWidget_Harm(this);
 		pSttIecSmvWidget_Harm->HarmFunc_Create(IECRCD_FUNC_Smv_Harm_ValidValue);
		m_pSttIecRcdFuncInterface = pSttIecSmvWidget_Harm->m_pSttIecRcdFuncInterface;
		m_pSttIecSmvWidget_Harm = pSttIecSmvWidget_Harm;
		m_cmbHarmDisplay->setCurrentIndex(0);
	}
// 		CSttIecSmvGrid_Harm *pGrid = new CSttIecSmvGrid_Harm(this);
// 		pGrid->setFont(*g_pSttGlobalFont);
// 		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
// 		pGrid->InitGrid();
// 		m_pSttIecRcdFuncInterface = pGrid;
		

	//SMV   ����ͳ��
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_PkgError)
	{
		strSysSetString = tr("���");
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Smv_PkgError();
		QSttIecSmvPkgErrorWidget *pGrid = new QSttIecSmvPkgErrorWidget(this);
		pGrid->m_pGridPkgError->setFont(*g_pSttGlobalFont);
		pGrid->m_pGridPkgError->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->m_pGridPkgError->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   ˫AD
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_AD)
	{
		g_oCapAnalysisConfig.Smv_AD();
		CSttIecSmvGrid_AD *pGrid = new CSttIecSmvGrid_AD(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   MU��ȷ��
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUAccuracy)
	{
		g_oCapAnalysisConfig.Smv_MUAccuracy();
		QSttIecMUAccuracyWidget *pMUAccuracyWidget = new QSttIecMUAccuracyWidget(this);
		m_pSttIecRcdFuncInterface = pMUAccuracyWidget;
	}
	//SMV   MU���ͳ��
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUErrorStatistics)
	{
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Smv_MUErrorStatistics();
		CSttIecSmvGrid_MUErrorStatis *pGrid = new CSttIecSmvGrid_MUErrorStatis(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV   MUʱ�侫��
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUTimingAccur)
	{
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Smv_MUErrorStatistics();
		QSttIecMUTimeWidget *pSttIecMUTimeWidget = new QSttIecMUTimeWidget(/*STTIEC_MUTIME_TYPE_TimeAccur,*/this);
		m_pSttIecRcdFuncInterface = pSttIecMUTimeWidget;
	}
// 	//SMV   MU��ʱ����
// 	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_MUPunctAccur)
// 	{
// 		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
// 		g_oCapAnalysisConfig.Smv_MUErrorStatistics();
// 		QSttIecMUTimeWidget *pSttIecMUTimeWidget = new QSttIecMUTimeWidget(STTIEC_MUTIME_TYPE_PunctAccur,this);
// 		m_pSttIecRcdFuncInterface = pSttIecMUTimeWidget;
// 	}
	//GOOSE   ʵʱֵ
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Goose_RT)
	{
		g_oCapAnalysisConfig.Goose_RT();
		CSttIecGooseGrid_RT *pGrid = new CSttIecGooseGrid_RT(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//GOOSE   ��λ�б�
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Goose_TurnList)
	{
		strSysSetString = tr("���");
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Goose_TurnList();
		CSttIecGooseGrid_TurnList *pGrid = new CSttIecGooseGrid_TurnList(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//GOOSE   ����ͳ��
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Goose_PkgStc)
	{
		strSysSetString = tr("���");
		xlang_GetLangStrByFile(strSysSetString,"Native_Clear");
		g_oCapAnalysisConfig.Goose_PkgStc();
		CSttIecGooseGrid_PkgError *pGrid = new CSttIecGooseGrid_PkgError(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	//SMV ʸ��ͼ
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Vector)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvVectorMainWidget *pSequence = new QSttIecSmvVectorMainWidget(this);
		m_pSttIecRcdFuncInterface = pSequence;
	}
	//SMV �����
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Sequence)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvSequenceMainWidget *pSequence = new QSttIecSmvSequenceMainWidget(this);
		m_pSttIecRcdFuncInterface = pSequence;
	}
	//SMV ���Է���
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Polar)
	{
		g_oCapAnalysisConfig.Smv_Vector();
		QSttIecSmvMeterAxisWidget *pMeterAxis = new QSttIecSmvMeterAxisWidget(this);
		m_pSttIecRcdFuncInterface = pMeterAxis;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Smv_PkgAnalyze)
	{
//		strSysSetString = tr("���");
		g_oCapAnalysisConfig.Smv_PkgAnalyze();
		CSttIecSmvGrid_PkgAnalyze *pPkgAnalyze = new CSttIecSmvGrid_PkgAnalyze(this);
		pPkgAnalyze->setFont(*g_pSttGlobalFont);
		pPkgAnalyze->horizontalHeader()->setFont(*g_pSttGlobalFont);
		m_pSttIecRcdFuncInterface = pPkgAnalyze;
		pPkgAnalyze->InitGrid();
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Goose_PkgAnalyze)
	{
		g_oCapAnalysisConfig.Goose_PkgAnalyze();
		CSttIecGooseGrid_PkgAnalyze *pPkgAnalyze = new CSttIecGooseGrid_PkgAnalyze(this);
		pPkgAnalyze->setFont(*g_pSttGlobalFont);
		pPkgAnalyze->horizontalHeader()->setFont(*g_pSttGlobalFont);
		m_pSttIecRcdFuncInterface = pPkgAnalyze;
		pPkgAnalyze->InitGrid();
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Goose_TurnSpy)
	{
		g_oCapAnalysisConfig.Goose_TurnSpy();
		QSttIecGooseTurnSpyWidget *pGooseTurnSpy = new QSttIecGooseTurnSpyWidget(this);
		m_pSttIecRcdFuncInterface = pGooseTurnSpy;
	}
	//д�ļ�
	else if (m_strIecRcdFuncID == IECRCD_FUNC_Write_File)
	{
		strSysSetString = /*_T("ֹͣ¼��")*/g_sLangTxt_Native_StopRecrd;
		g_oCapAnalysisConfig.DisableAll();
		QSttIecRecordWriteFileWidget *pWriteFileWidget = new QSttIecRecordWriteFileWidget(this);
		m_pSttIecRcdFuncInterface = pWriteFileWidget;
		m_pSttRcdWriteFileWidget = pWriteFileWidget;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_FT3_RT)
	{
		g_oCapAnalysisConfig.FT3_RT();
		CSttIecFT3Grid_RT *pGrid = new CSttIecFT3Grid_RT(this);
		pGrid->setFont(*g_pSttGlobalFont);
		pGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
		pGrid->InitGrid();
		m_pSttIecRcdFuncInterface = pGrid;
	}
	else if (m_strIecRcdFuncID == IECRCD_FUNC_FT3_OriginalMsg)
	{
		g_oCapAnalysisConfig.FT3_OriginalMsg();
 		CSttIecFT3OriginalMsgWidget *pWidget = new CSttIecFT3OriginalMsgWidget(this);
 		m_pSttIecRcdFuncInterface = pWidget;
	}
	else
	{
		m_pSttIecRcdFuncInterface = new QSttIecEmptyWidget(this);
	}

	m_pSttIecRcdFuncInterface->m_bMUTestMode = m_bMUTestMode;

	if (m_bMUTestMode)//zhouhj 20221026 ����Ǻϲ���Ԫ����ģʽ,��̶������в�������Ϊ1
	{
		g_oCapAnalysisConfig.m_bMU_Test = true;
		g_oCapAnalysisConfig.m_bAnalysisData_PhaseDelt = true;
		g_oCapAnalysisConfig.m_bAnalysisData_Complex = true;
	}

	ui->m_btnSysSet->setText(strSysSetString);
}

void QSttIecRecordCbWidget::ExecIecFunc()
{
	CSttIecRcdFuncInterface *pForDelete = NULL;

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		if (m_pSttIecRcdFuncInterface->m_strIecRcdFuncID == m_strIecRcdFuncID)
		{
			m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);
			return;
		}

		pForDelete = m_pSttIecRcdFuncInterface;
		//pForDelete->m_pIecRcdFuncWidget->hide();
	}

	HarmFuncType();
	ExecIecFunc_Create();

	if (m_pSttIecRcdFuncInterface != NULL)
	{
		m_pSttIecRcdFuncInterface->m_strIecRcdFuncID = m_strIecRcdFuncID;
		ui->verticalLayout->insertWidget(0, m_pSttIecRcdFuncInterface->m_pIecRcdFuncWidget);

		m_pSttIecRcdFuncInterface->IecRcdFunc(m_pCurrCapDevice);

		if (m_pSttIecRcdFuncInterface->NeedNextAndPrev())
		{
			ui->m_btnNextPage->show();
			ui->m_btnPrevPage->show();
		}
		else
		{
			ui->m_btnNextPage->hide();
			ui->m_btnPrevPage->hide();
		}

//#ifndef _PSX_QT_LINUX_ 
		if (m_pSttIecRcdFuncInterface->NeedAddToSubPub())
		{
			ui->m_btnAddToPub->show();
			ui->m_btnAddToSub->show();
			ui->m_btnAddToSub->setEnabled(m_pSttIecRcdFuncInterface->IsToSubBtn());
		}
		else
		{
			ui->m_btnAddToPub->hide();
			ui->m_btnAddToSub->hide();
		}
//#endif

		if (m_pSttIecRcdFuncInterface->NeedConfig())
		{
			ui->m_btnSysSet->show();
		}
		else
		{
			ui->m_btnSysSet->hide();
		}

		//20231019 wxy д�ļ�ģ��ؼ��ı�
		UpdateWriteFileCtrls(m_strIecRcdFuncID == IECRCD_FUNC_Write_File);
		
	}

	if (pForDelete != NULL)
	{
		pForDelete->Release();
	}
}

void QSttIecRecordCbWidget::slot_Timer_IecRcdUpdate()
{
	if ((m_pSttIecRcdFuncInterface == NULL)||(g_theXSmartCapMngr == NULL)
		/*||(!g_bSmartCap_RecordNow)*/ || m_bStopTimerUpdate)//zhouhj 2024.4.10 �˳�¼����,��ʱ������ˢ��
	{
		return;
	}

	CAutoSimpleLock oLock(m_oFuncCriticSection);

	m_pSttIecRcdFuncInterface->IecRcdFuncUpdate(m_pCurrCapDevice);

	if (m_bMUTestMode && (m_strIecRcdFuncID == IECRCD_FUNC_Smv_Wave))//�ϲ���Ԫ����,����ͼ����,Ҳ���¼���
	{
		CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
		pXSttCap_61850->UpdateDvmDeviceDatas();
	}

	if ((m_pSVDelayData != NULL)&&(g_oCapAnalysisConfig.m_bMU_Test))
	{
		CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
		pXSttCap_61850->CalMuTimeTestRlt_NoPPS();
//		emit sig_UpdateMUTimeAccurRlt(m_pSVDelayData);
	}
}



void QSttIecRecordCbWidget::on_m_btnPrevPage_clicked()
{
	CAutoSimpleLock oLock(m_oFuncCriticSection);
	m_pSttIecRcdFuncInterface->PrevPage();
}

void QSttIecRecordCbWidget::on_m_btnNextPage_clicked()
{
	CAutoSimpleLock oLock(m_oFuncCriticSection);
	m_pSttIecRcdFuncInterface->NextPage();
}

void QSttIecRecordCbWidget::on_m_btnAddToSub_clicked()
{
	m_pSttIecRcdFuncInterface->AddToSub();
}

void QSttIecRecordCbWidget::on_m_btnAddToPub_clicked()
{
	m_pSttIecRcdFuncInterface->AddToPub();

}

void QSttIecRecordCbWidget::slot_UpdateSVDatasetsPowerVector()
{
	m_oTimerIecRcdUpdate.stop();
	g_theXSmartCapMngr->m_pX61850Cap->IecAnalysis_UpdateSvDatasetsPowerVector();
	m_oTimerIecRcdUpdate.start(m_fIecRcdTimer*1000/*500*/);
}


QScrollComboBox *QSttIecRecordCbWidget::CombHarmDisplayType()
{
	CString strText;
	QScrollComboBox *pcmbHarmDisplay = new QScrollComboBox(this);
	pcmbHarmDisplay->addItem(/*_T("��Чֵ")*/g_sLangTxt_Native_ValdValue);
	pcmbHarmDisplay->addItem(/*_T("������")*/g_sLangTxt_Native_IncRate);
	pcmbHarmDisplay->addItem(/*_T("��״ͼ")*/g_sLangTxt_Native_BarChar);
	return pcmbHarmDisplay;
}


void QSttIecRecordCbWidget::BtnPreNextEnabled(long nType)
{
	if (nType == 0)
	{	
		ui->m_btnPrevPage->setEnabled(FALSE);
		ui->m_btnNextPage->setEnabled(TRUE);
	}
	else if (nType == 1)
	{
		ui->m_btnPrevPage->setEnabled(TRUE);
		ui->m_btnNextPage->setEnabled(TRUE);
	}
	else if (nType == 2)
	{
		ui->m_btnPrevPage->setEnabled(TRUE);
		ui->m_btnNextPage->setEnabled(FALSE);
	}
}

void QSttIecRecordCbWidget::UpdateWriteFileCtrls(bool bShow)
{
	//20240710 suyang ����UpdateWriteFileCtrls�����ĵط��Ѿ��������ע��
// 	if (m_pSttIecRcdFuncInterface->NeedNextAndPrev())
// 	{
// 		ui->m_btnNextPage->show();
// 		ui->m_btnPrevPage->show();
// 	}
// 	else
// 	{
// 		ui->m_btnNextPage->hide();
// 		ui->m_btnPrevPage->hide();
// 	}
// 
// 	if (m_pSttIecRcdFuncInterface->NeedAddToSubPub())
// 	{
// 		ui->m_btnAddToPub->show();
// 		ui->m_btnAddToSub->show();
// 	}
// 	else
// 	{
// 		ui->m_btnAddToPub->hide();
// 		ui->m_btnAddToSub->hide();
// 	}
// 
// 	if (m_pSttIecRcdFuncInterface->NeedConfig())
// 	{
// 		ui->m_btnSysSet->show();
// 	}
// 	else
// 	{
// 		ui->m_btnSysSet->hide();
// 	}

	if(bShow)
	{
		QSttIecRecordWriteFileWidget *pWidget = (QSttIecRecordWriteFileWidget *)m_pSttIecRcdFuncInterface;
		pWidget->SetSelectedCbs(m_pSelectedCbs);
		ui->m_lblSelCb->hide();
		ui->m_lblSelFunc->hide();
		m_cmbFunc->hide();
		m_cmbCb->hide();
		m_pWriteFileTime_Label->show();
		m_pWriteFileSize_Label->show();
		m_pWriteFileTime_Edit->show();
		m_pWriteFileSize_Edit->show();
	}
	else
	{
		ui->m_lblSelCb->show();
		ui->m_lblSelFunc->show();
		ui->m_btnBack->show();
		m_cmbFunc->show();
		m_cmbCb->show();
		m_pWriteFileTime_Label->hide();
		m_pWriteFileSize_Label->hide();
		m_pWriteFileTime_Edit->hide();
		m_pWriteFileSize_Edit->hide();
	}
}

// void QSttIecRecordCbWidget::slot_ReciveFileSize( long nM, long nK )
// {
// 	CString strSize;
// 	strSize.Format(_T("%d,%d K"), nM, nK);
// 	m_edtWriteSize->setText(strSize);
// }

// void QSttIecRecordCbWidget::slot_ReciveRecordTime( int nTime )
// {
// 	CString strTime;
// 	strTime.Format(_T("%ld s"),nTime);
// 	m_pWriteFileTime_Edit->setText(strTime);
// }

void QSttIecRecordCbWidget::UpdateWriteFileTimeAndFileSize(long nTimeMs,long nFileSize)
{
	CString strTime;
	double dTime = ((double)nTimeMs)/1000.0f;
	strTime.Format(_T("%.03lf s"),dTime);
	m_pWriteFileTime_Edit->setText(strTime);

	nFileSize = nFileSize / 1024;
	long nM = nFileSize / 1024;
	long nK = nFileSize - nM * 1024;
	CString strSize;

	if (nM>0)
	{
		strSize.Format(_T("%ld,%03ld KB"), nM, nK);
	}
	else
	{
		strSize.Format(_T("%ld KB"),  nK);
	}
	
	m_pWriteFileSize_Edit->setText(strSize);
}


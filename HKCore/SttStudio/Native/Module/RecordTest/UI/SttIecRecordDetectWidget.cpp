#include "SttIecRecordDetectWidget.h"
#include "ui_SttIecRecordDetectWidget.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../SttTestCtrl/SttTestCtrlCntrNative.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../Module/SmartCap/61850Cap/CapDevice/CapDevice6044.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "../../../61850/Module/IecCfgSclTool/SclToIecCfgTool.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"
#include "MUTest/SttMUTestIecCbSelWidget.h"
#include "../../XLangResource_Native.h"
#include "SttIecRecordMainWidget.h"
#include "SttIecRecordCbWidget.h"
#include "../../../Module/SmartCap/XSmartCapFileWrite.h"

//2022-12-02 �޸Ĺ���ID���������еĶ�Ҫ���룬Ч�ʵ��£����Դ�ͷ�ļ���ȥ�������κ���Ҫ�����ĵط����а���
#include "../../UI/SttTestCntrCmdDefine.h" 


extern QSttIecRecordMainWidget *g_theSttIecRecordMainWidget;
extern CSttIecRecordCbInterface *g_pSttIecRecordCbWidget;
QSttIecRecordDetectWidget *g_pSttIecRecordDetectWidget = NULL;
extern BOOL g_bIsParsingPkg;

extern long g_nSmvFirstChIsTdelay;


QSttIecRecordDetectWidget::QSttIecRecordDetectWidget(QFont font, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttIecRecordDetectWidget)
{
	m_bIecCapWriteFile = 0;
	m_bIsClearCBs = false;
	m_bIsFromIecfgFile = FALSE;
	m_bStartDetect = FALSE;
	g_theCapDeviceMngrMsgRcvWnd = this;
	g_pSttIecRecordDetectWidget = this;
	m_nIecType = 0;
    ui->setupUi(this);

	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
//	ui->m_btnImportIecfg->setVisible(false);

	xlang_SetLangStrToWidget(ui->m_btnImportIecfg, "IEC_ImportIecfg", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnDetect, "IEC_Detect", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnDetectStop, "IEC_DetectStop", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnClear, "IEC_Clear", XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget(ui->m_btnBeginRecord, "IEC_BeginRecord", XLang_Ctrls_QPushButton);
	//20231017 wxy �޸Ĺ�ѡ������
// 	xlang_SetLangStrToWidget(ui->m_chkUseSmv, "IEC_UseSmv", XLang_Ctrls_QCheckBox);
// 	xlang_SetLangStrToWidget(ui->m_chkUseGoose, "IEC_UseGoose", XLang_Ctrls_QCheckBox);
	xlang_SetLangStrToWidget(ui->m_chkSmvFirstIsTime, "IEC_SmvFirstIsTime", XLang_Ctrls_QCheckBox);

	ui->m_chkSmvFirstIsTime->setVisible(false);//20230605 zhouhj ��ʱ����

	ui->m_btnImportIecfg->setVisible(false);
	m_pGridIecCb = new CSttIecCbGrid(this);
	m_pGridIecCb->setFont(*g_pSttGlobalFont);
	m_pGridIecCb->horizontalHeader()->setFont(*g_pSttGlobalFont);

	if(g_oSystemParas.m_nIecFormatMeas != STT_IEC_FORMAT_61850_92)
	{	//20240914 suyang FT3ʱ��Ҫ��ǰ���ã������ͷ��ʾ����
		m_pGridIecCb->m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_60044;
		m_pGridIecCb->m_bViewFT3 = TRUE;
	}

	m_pGridIecCb->InitGrid();
	ui->verticalLayout->insertWidget(0,m_pGridIecCb);
	m_pGridIecCb->AttachDataViewOptrInterface(this);

	if (g_nSmvFirstChIsTdelay == 1)
	{
		ui->m_chkSmvFirstIsTime->setCheckState(Qt::Checked);
	}
	else
	{
		ui->m_chkSmvFirstIsTime->setCheckState(Qt::Unchecked);
	}


	if(g_oSystemParas.m_nIecFormatMeas != STT_IEC_FORMAT_61850_92)
	{

		ui->m_chkUseSmv->setCheckState(Qt::Unchecked);
		ui->m_chkUseGoose->setCheckState(Qt::Unchecked);
		ui->m_chkUseFT3->setCheckState(Qt::Checked);
		m_bViewSmv = /*TRUE*/FALSE;
		m_bViewGoose = /*TRUE*/FALSE;
		m_bViewFT3 = TRUE;
		m_pGridIecCb->m_bViewSmv = /*TRUE*/FALSE;
		m_pGridIecCb->m_bViewGoose = /*TRUE*/FALSE;
		m_pGridIecCb->m_bViewFT3 = TRUE;

		m_nIecType = STT_IEC_DETECT_TYPE_60044;
	}
	else
	{
	ui->m_chkUseSmv->setCheckState(Qt::Checked);
		ui->m_chkUseGoose->setCheckState(Qt::Unchecked);
	ui->m_chkUseFT3->setCheckState(Qt::Unchecked);
	m_bViewSmv = TRUE;
		m_bViewGoose = /*TRUE*/FALSE;
	m_bViewFT3 = FALSE;
	m_pGridIecCb->m_bViewSmv = TRUE;
		m_pGridIecCb->m_bViewGoose = /*TRUE*/FALSE;
	m_pGridIecCb->m_bViewFT3 = FALSE;

		m_nIecType = STT_IEC_DETECT_TYPE_61850_92;//Ĭ�Ϲ�ѡ92 ��������Ϊ92
	}


	ui->m_btnDetectStop->setEnabled(false);
	ui->m_btnBeginRecord->setEnabled(false);
	
// #ifndef _XSmartCap_use_SttRcdSocket_
// 	ui->m_chkUseFT3->setVisible(false);//20230804 zhouhj ֻ��Socketģʽʹ��
// #endif
	connect(this,SIGNAL(sig_AddNewDevice(CCapDeviceBase*)),this,SLOT(on_AddNewDevice(CCapDeviceBase*)));
	ConnectAll();

	SetIecRecordFont();

	CString strText;
	strText = /*_T("¼��")*/g_sLangTxt_Native_RecWaveform;
	m_chkWaveRecord = new QSttCheckBox(strText);
	ui->m_layButtons->addWidget(m_chkWaveRecord,1);
	connect(m_chkWaveRecord,SIGNAL(stateChanged(int)),this,SLOT(slot_ck_WaveRecordStateChanged(int)));

	//wxy ����ϲ���Ԫ��¼����ѡ����ʾ
// 	if (g_pSttIecRecordCbWidget->IsMUTestMode())
// 	{
// 		m_chkWaveRecord->setVisible(false);
// 	}

	//zhouhj 2023.9.6 �����ڴ˴�����ֱ�������,���ⲿDialog���д���
	// �ֱ���2880*1800 wjs  �ڸ÷ֱ����¸ı䰴ť���
// 	QDesktopWidget* desktopWidget = QApplication::desktop(); 
// 	QRect rect = desktopWidget->screenGeometry();
// 	if(rect.height() == 1800)
// 	{
// 		resize(1200,800);
// 		this->setFixedWidth(1200);
// 		this->setFixedHeight(800);
// 		ui->m_chkUseGoose->setMinimumWidth(220);
// 		ui->m_chkWriteFile->setMinimumWidth(220);
// 	}
}

QSttIecRecordDetectWidget::~QSttIecRecordDetectWidget()
{
    delete ui;
	delete m_pGridIecCb;
}


void QSttIecRecordDetectWidget::slot_ck_WaveRecordStateChanged(int	nIndex)
{
	//2023-1-3 suyang ֻ����ʾ��ʾ��Ϣ����
	if (m_chkWaveRecord->checkState() == Qt::Checked)
	{
        QMessageBox::information(this, g_sLangTxt_Message,"g_sLangTxt_Iec_StartRcd");
	}


}

void QSttIecRecordDetectWidget::SetIecCapWriteFile(bool b)
{
	m_bIecCapWriteFile = b;
	m_chkWaveRecord->setChecked(b);

	if (b && (!m_chkWaveRecord->isVisible()))
	{
		m_chkWaveRecord->setVisible(true);
	}
}

void QSttIecRecordDetectWidget::ConnectAll()
{
	connect(ui->m_chkUseSmv, SIGNAL(clicked()), this, SLOT(slot_chkUseSmvClicked()));
	connect(ui->m_chkUseGoose, SIGNAL(clicked()), this, SLOT(slot_chkUseGooseClicked()));
	connect(ui->m_chkUseFT3, SIGNAL(clicked()), this, SLOT(slot_chkUseFT3Clicked()));
}

void QSttIecRecordDetectWidget::DisConnectAll()
{

}

void QSttIecRecordDetectWidget::SetIecRecordFont()
{
	setFont(*g_pSttGlobalFont);
	ui->m_btnImportIecfg->setFont(*g_pSttGlobalFont);
	ui->m_btnDetect->setFont(*g_pSttGlobalFont);
	ui->m_btnDetectStop->setFont(*g_pSttGlobalFont);
	ui->m_btnClear->setFont(*g_pSttGlobalFont);
	ui->m_btnBeginRecord->setFont(*g_pSttGlobalFont);
	ui->m_chkUseSmv->setFont(*g_pSttGlobalFont);
	ui->m_chkUseGoose->setFont(*g_pSttGlobalFont);
	ui->m_chkSmvFirstIsTime->setFont(*g_pSttGlobalFont);
	ui->m_chkUseFT3->setFont(*g_pSttGlobalFont);

}
void QSttIecRecordDetectWidget::OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol)
{
	//CExBaseObject *pSel = m_pGridIecCb->GetCurrSelData();
	//ui->m_btnBeginRecord->setEnabled(pSel != NULL);
/*
	BOOL bEnable = FALSE;
	POS pos = g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetHeadPosition();
	while (pos != NULL)
	{
		CCapDeviceBase *pCapDevice = (CCapDeviceBase *)g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetNext(pos);

		if (pCapDevice->m_bSelect)
		{
			bEnable = TRUE;
			break;
		}
	}
	
	ui->m_btnBeginRecord->setEnabled(bEnable);
*/
	long nSelCount = g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetSelectDeviceCount();
	ui->m_btnBeginRecord->setEnabled(nSelCount > 0);
}

unsigned int QSttIecRecordDetectWidget::XSetTimer(unsigned int nIDEvent, unsigned int nElapse, void* pFunc)
{
	return 0;
}

BOOL QSttIecRecordDetectWidget::XKillTimer(unsigned int nIDEvent)
{
	return 0;
}

BOOL QSttIecRecordDetectWidget::IsCapDeviceMngrDevice(CCapDeviceBase *pCapDeviceBase)
{
	if (g_theXSmartCapMngr == NULL)
	{
		return FALSE;
	}

	if (g_theXSmartCapMngr->m_pX61850Cap == NULL)
	{
		return FALSE;
	}

	if (g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.Find(pCapDeviceBase) == NULL)
	{
		return FALSE;
	}
	
	return TRUE;
}

void QSttIecRecordDetectWidget::XPostMessage(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
{
	if (WM_ADDCAPDEVICE == nMsgID)
	{
		CCapDeviceBase *pCapDeviceBase = (CCapDeviceBase*)wParam;

		if (pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			AttachDeviceFT3ChMaps(pCapDeviceBase);
		} 
		else
		{
			AttachDeviceChMapsBySCL(pCapDeviceBase);//20221218 zhouhj ����SCD,����SCD�ļ��ж�Ӧ��AppID���µ�ǰ���ƿ�����
		}

		emit sig_AddNewDevice(pCapDeviceBase);
		//2022-12-02  lijunqing ̽�⵽װ���豸

		return;
	}

	if (WM_UPDATECAPDEVICE == nMsgID)
	{//���ݵ�ǰ�򿪵�ҳ�棬��������,���½�������ʾ zhouhj  20220106

		if (IsCapDeviceMngrDevice((CCapDeviceBase*)wParam))
		{
			if (m_pGridIecCb != NULL)
			{
				m_pGridIecCb->UpdateCapDevice((CCapDeviceBase*)wParam);
			}

			g_theSttIecRecordMainWidget->UpdateCapDevice((CCapDeviceBase*)wParam);
		}

		return;
	}
}

void QSttIecRecordDetectWidget::ClearAll_StartDetect()
{
	if (m_bIsClearCBs)
	{
		return;
	}

	if (g_bSmartCap_RecordNow)//¼��������,���˳�¼�����ӽ���
	{
		g_bSmartCap_RecordNow = FALSE;//��ֹͣ���Ľ���
		m_bIsClearCBs = true;
		g_pSttIecRecordCbWidget->BtnBack();//
		m_bIsClearCBs = false;
	}

	CTickCount32 oTickCount;

	//zhouhj 2023.9.18 ��ǵ�ǰ�Ƿ����ڽ���,��ֹ���߳�ʱ,����������,��տ��ƿ�
	while(g_bIsParsingPkg)
	{
		oTickCount.DoEvents(2);
	}

	on_m_btnClear_clicked();

	if (ui->m_btnDetect->isEnabled())//�������ʼ���ԡ���ť���ڷ�ʹ��״̬,��ǰΪ��ʼ����״̬,��Ҫ���·���һ��̽������
	{
		ui->m_btnDetect->setEnabled(false);
		ui->m_btnDetectStop->setEnabled(true);

		m_bIsClearCBs = true;
		CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
		pNative->Ats_IecDetect(1);
		m_bIsClearCBs = false;
	}
}

void QSttIecRecordDetectWidget::UpdateDetectType(long nPkgDetectType)
{
	if (nPkgDetectType<0)
	{
		return;
	}
	//20240913 suyang ֱ�ӵ���m_pGridIecCb��ShowDatas����
// 	int nIecCbType = 0;
// 	if (m_pGridIecCb != NULL)
// 	{
// 		nIecCbType = m_pGridIecCb->m_nIecCbShowType;
// 	}

	if (nPkgDetectType == STT_IEC_DETECT_TYPE_61850)
	{
		m_bViewSmv = TRUE;
		m_bViewGoose = TRUE;
		m_bViewFT3 = FALSE;		
		ui->m_chkUseFT3->setCheckState(Qt::Unchecked);
		ui->m_chkUseSmv->setCheckState(Qt::Checked);
		ui->m_chkUseGoose->setCheckState(Qt::Checked);

		m_nIecType = STT_IEC_DETECT_TYPE_61850;
// 		m_pGridIecCb->m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_61850;
	}
	else if (nPkgDetectType == STT_IEC_DETECT_TYPE_61850_92)
	{
		m_bViewSmv = TRUE;
		m_bViewGoose = FALSE;
		m_bViewFT3 = FALSE;		
		ui->m_chkUseFT3->setCheckState(Qt::Unchecked);
		ui->m_chkUseSmv->setCheckState(Qt::Checked);
		ui->m_chkUseGoose->setCheckState(Qt::Unchecked);
		m_nIecType = STT_IEC_DETECT_TYPE_61850_92;
// 		m_pGridIecCb->m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_61850;
	}
	else if (nPkgDetectType == STT_IEC_DETECT_TYPE_61850_GS)
	{
		m_bViewSmv = FALSE;
		m_bViewGoose = TRUE;
		m_bViewFT3 = FALSE;		
		ui->m_chkUseFT3->setCheckState(Qt::Unchecked);
		ui->m_chkUseSmv->setCheckState(Qt::Unchecked);
		ui->m_chkUseGoose->setCheckState(Qt::Checked);
		m_nIecType = STT_IEC_DETECT_TYPE_61850_GS;
// 		m_pGridIecCb->m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_61850;
	}
	else if (nPkgDetectType == STT_IEC_DETECT_TYPE_60044)
	{
		m_bViewSmv = FALSE;
		m_bViewGoose = FALSE;
		m_bViewFT3 = TRUE;		
		ui->m_chkUseSmv->setCheckState(Qt::Unchecked);
		ui->m_chkUseGoose->setCheckState(Qt::Unchecked);
		ui->m_chkUseFT3->setCheckState(Qt::Checked);
//		g_oCapAnalysisConfig.m_nShowPrimaryValue = 0;
		m_nIecType = STT_IEC_DETECT_TYPE_60044;
// 		m_pGridIecCb->m_nIecCbShowType = STT_IECCBGRID_SHOW_TYPE_60044;
		
	}
	else
	{
		return;
	}
	m_pGridIecCb->m_bViewSmv = m_bViewSmv;
	m_pGridIecCb->m_bViewGoose = m_bViewGoose;
	m_pGridIecCb->m_bViewFT3 = m_bViewFT3;
	g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.UnselectAllCap(!m_bViewSmv,!m_bViewGoose,!m_bViewFT3);
	
// 	//20240913 suyang �˴����ĵ���ShowDatas���������������±�������ʱ���������ͷ��ʾ����
//	UpdateCbGrid();
	if (m_pGridIecCb != NULL)
	{
		m_pGridIecCb->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);
	}
// 	if (m_pGridIecCb != NULL)
// 	{
// 		if (m_pGridIecCb->m_nIecCbShowType != nIecCbType)
// 		{
// 			m_pGridIecCb->UpdateGridTitle();
// 		}
// 	}
}

BOOL QSttIecRecordDetectWidget::AttachDeviceChMapsBySCL(CCapDeviceBase *pCapDeviceBase)
{
	if (pCapDeviceBase == NULL)
	{
		return FALSE;
	}

	CSclStation* pSclStation = g_theTestCntrFrame->GetSclStation();
	CSclCtrlBase *pSclCtrlBase = pSclStation->FindCtrl_GsOutSmvOut(pCapDeviceBase->m_dwAppID,
		pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92);
	CCapDeviceMngr *pCapDeviceAll = &g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll;

	if (pSclCtrlBase == NULL)
	{
		if (pCapDeviceBase->GetClassID() != CPDCLASSID_DEVICE92)//ֻ��SV���ƿ�����Զ��������봦��
		{
			return FALSE;
		}

		CIecCfgDatasSmvIn *pIecCfgDatasSmvIn = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvInMngr();
		CIecCfgDataBase* pIecCfgDataBase = pIecCfgDatasSmvIn->FindByAppIDFiber(pCapDeviceBase->m_dwAppID, -1);

		if (pIecCfgDataBase == NULL)//�Ȳ��Ҹ�APPID,���δ���ҵ�,�������1��
		{
			if (!g_pSttIecRecordCbWidget->IsMUTestMode())
			{
				return FALSE;
			}

			pIecCfgDatasSmvIn->SetSmvType(SMVTYPE_92);
			pIecCfgDataBase = pIecCfgDatasSmvIn->AddNewIecCfgData();
			CIecCfg92InData *pIecCfg92InData = (CIecCfg92InData*)pIecCfgDataBase;
			pIecCfg92InData->m_dwAppID = pCapDeviceBase->m_dwAppID;
		}

		pIecCfgDataBase->m_nFiberIndex = pCapDeviceBase->m_nFiberIndex;
		pIecCfgDataBase->m_nFiber2Index = pCapDeviceBase->m_nFiberIndex;

		if (pCapDeviceBase->GetCount()>0)
		{
			pIecCfgDataBase->SetChannelNum(pCapDeviceBase->GetCount());
		}

		CExBaseList oCurrList;
		long nCBIndex = 1/*0*/;//zhouhj 2024.4.30 ͳһ��1��ʼ���
		nCBIndex = pCapDeviceAll->GetDeviceCount(CPDCLASSID_DEVICE92) + pCapDeviceAll->GetDeviceCount(CPDCLASSID_DEVICE6044) /*- 1*/;
		pIecCfgDataBase->SetAT02D_ChannelID(&oCurrList,nCBIndex);
		oCurrList.RemoveAll();

		pCapDeviceBase->AttachIecCfgData(pIecCfgDataBase);
		return TRUE;
	}

	if (pSclCtrlBase->GetCount() == 0)
	{
		if (!pSclStation->OpenSiedFile((CSclIed*)pSclCtrlBase->GetAncestor(SCLIECCLASSID_IED)))
		{
			return FALSE;
		}
		
		pSclCtrlBase = pSclStation->FindCtrl_GsOutSmvOut(pCapDeviceBase->m_dwAppID,
			pCapDeviceBase->GetClassID() == CPDCLASSID_DEVICE92);

		if (pSclCtrlBase == NULL)
		{
			return FALSE;
		}

		if (pSclCtrlBase->GetCount() == 0)
		{
			return FALSE;
		}
	}

	pSclCtrlBase->m_nFiberIndex = pCapDeviceBase->m_nFiberIndex;
	CSclToIecCfgTool oSclToIecCfgTool;
	oSclToIecCfgTool.AttacthSclFileRead(pSclStation);
	CIecCfgDataBase* pIecCfgDataBase = oSclToIecCfgTool.AddCfgSmvInGin_By_SclSmvOutGout(pSclCtrlBase, &g_oSttTestResourceMngr.m_oIecDatasMngr,TRUE);
	pIecCfgDataBase->m_nFiberIndex = pCapDeviceBase->m_nFiberIndex;
	pIecCfgDataBase->m_nFiber2Index = pCapDeviceBase->m_nFiberIndex;
	CExBaseList oCurrList;
	long nCBIndex = 1/*0*/;//zhouhj 2024.4.30 ͳһ��1��ʼ���
	nCBIndex = pCapDeviceAll->GetDeviceCount(CPDCLASSID_DEVICE92) + pCapDeviceAll->GetDeviceCount(CPDCLASSID_DEVICE6044) /*- 1*/;
//	nCBIndex = g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetDeviceCount(pCapDeviceBase->GetClassID()) - 1;
	pIecCfgDataBase->SetAT02D_ChannelID(&oCurrList,nCBIndex);
	oCurrList.RemoveAll();
	pCapDeviceBase->AttachIecCfgData(pIecCfgDataBase);
	return TRUE;
}

BOOL QSttIecRecordDetectWidget::AttachDeviceFT3ChMaps(CCapDeviceBase *pCapDeviceBase)
{
	if (pCapDeviceBase == NULL)
	{
		return FALSE;
	}

	if (pCapDeviceBase->GetClassID() != CPDCLASSID_DEVICE6044)
	{
		return FALSE;
	}

	CIecCfgDatasSmvIn *pIecCfgDatasSmvIn = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvInMngr();
	CIecCfgDataBase* pIecCfgDataBase = pIecCfgDatasSmvIn->FindByFiber_60044Common( pCapDeviceBase->m_nFiberIndex);

	if (pIecCfgDataBase == NULL)//�Ȳ��Ҹ�APPID,���δ���ҵ�,�������1��
	{
		pIecCfgDatasSmvIn->SetSmvType(SMVTYPE_6044_COMMON);
		pIecCfgDataBase = pIecCfgDatasSmvIn->AddNewIecCfgData();
//		pIecCfgDatasSmvIn->SetSmvType(SMVTYPE_6044_COMMON);
	}

	pIecCfgDataBase->m_nFiberIndex = pCapDeviceBase->m_nFiberIndex;
	pIecCfgDataBase->m_nFiber2Index = pCapDeviceBase->m_nFiberIndex;
	pCapDeviceBase->SetChannelNum(pIecCfgDataBase->GetChannelNum());

	CExBaseList oCurrList;
	long nCBIndex = 1/*0*/;//zhouhj 2024.4.30 ͳһ��1��ʼ���
	CCapDeviceMngr *pCapDeviceAll = &g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll;
	nCBIndex = pCapDeviceAll->GetDeviceCount(CPDCLASSID_DEVICE92) + pCapDeviceAll->GetDeviceCount(CPDCLASSID_DEVICE6044) /*- 1*/;
	pIecCfgDataBase->SetAT02D_ChannelID(&oCurrList,nCBIndex);
	oCurrList.RemoveAll();

	CCapDevice6044 *pCapDevice6044 = (CCapDevice6044*)pCapDeviceBase;
	pCapDevice6044->m_bDC_FT3 = (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC);
	pCapDeviceBase->AttachIecCfgData(pIecCfgDataBase);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CSttWndAssistInterface
//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
CSttWndAssistInterface* QSttIecRecordDetectWidget::ast_FindWnd(const CString &strWndID)
{

	return NULL;
}

//����ִ�нӿ�
bool QSttIecRecordDetectWidget::ast_ExecCmd(const CString &strCmdID,const CString &strParas)
{
	if (strCmdID == Event_ID_IecSelCb)
	{
		UpdateCbGrid();
		return true;
	}

	if (strCmdID == STT_CMD_TYPE_ATS_BeginRecord)
	{
		if (m_pGridIecCb->GetDatas() == NULL)
		{
			return false;
		}

		on_m_btnBeginRecord_clicked();
		return true;
	}

	return false;
}

bool QSttIecRecordDetectWidget::ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID)
{

	return false;
}

bool QSttIecRecordDetectWidget::ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile)
{
	return false;
}

//////////////////////////////////////////////////////////////////////////

void QSttIecRecordDetectWidget::UpdateCbGrid()
{
	if (m_pGridIecCb != NULL)
	{
		m_pGridIecCb->UpdateDatas();
	}
}

void QSttIecRecordDetectWidget::UpdateDetectWidget()
{
	long nSelCount = g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetSelectDeviceCount();
	ui->m_btnBeginRecord->setEnabled(nSelCount > 0);
	UpdateCbGrid();

 	//wxy ����ϲ���Ԫ��¼����ѡ����ʾ
 	if (g_pSttIecRecordCbWidget->IsMUTestMode())
 	{
 		m_chkWaveRecord->setVisible(false);
		m_bIecCapWriteFile = false;
 	}

}

void QSttIecRecordDetectWidget::on_AddNewDevice(CCapDeviceBase *pCapDevice)
{
	if (!IsCapDeviceMngrDevice(pCapDevice))
	{
		return;
	}

	m_pGridIecCb->AddCapDevice(pCapDevice);

	assist_event(Event_ID_IecAddCb, pCapDevice);

	if (g_pSttMUTestIecCbSelWidget != NULL)
	{
		g_pSttMUTestIecCbSelWidget->ShowAllCapDevice();
	}
}

void QSttIecRecordDetectWidget::on_m_btnDetect_clicked()
{
	StartDetect();
}

void QSttIecRecordDetectWidget::StartDetect()
{
	m_bStartDetect =  TRUE;
	m_bIsFromIecfgFile = FALSE;
	g_bSmartCap_RecordNow = FALSE;//����̽�⹦�ܵ�ʱ���ֹͣ¼����,�ڽ�����ӽ���ʱ,����¼��
//	ImportIecfg();//20220609 zhouhj 20220609 ��ʼ̽��ʱ,�̶���������
	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
	pNative->m_oSttAtsClient.m_nIecType = m_nIecType;
	pNative->Ats_IecDetect(1);
	ui->m_btnDetect->setEnabled(false);
	ui->m_btnDetectStop->setEnabled(true);

// 	ui->m_chkUseSmv->setEnabled(false);
// 	ui->m_chkUseGoose->setEnabled(false);
// 	ui->m_chkUseFT3->setEnabled(false);

	assist_event(Event_ID_IecAddCb, NULL);

}

void QSttIecRecordDetectWidget::CloseIecCapDetect()
{
	if ((!ui->m_btnDetect->isEnabled())||g_bSmartCap_RecordNow)//����ѿ�ʼ̽���������¼��,��ر�¼��ͨ��
	{
		CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
		pNative->Ats_IecDetect(0);
	}
}

void QSttIecRecordDetectWidget::on_m_btnClear_clicked()
{
	if (m_bIsClearCBs)
	{
		return;
	}

	if (g_bSmartCap_RecordNow)//��տ��ƿ�ʱ,��Ҫֹͣ���Ľ���
	{
		g_bSmartCap_RecordNow = FALSE;
	}

	m_bIsClearCBs = true;
	CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;

	if (!ui->m_btnDetect->isEnabled())//�����ǰ����̽��״̬,��ֹͣ̽��
	{
		pNative->Ats_IecDetect(0);
	}

	m_bIsFromIecfgFile = FALSE;
    CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	
	pXSttCap_61850->RemoveCapDevices();
    m_pGridIecCb->ShowDatas(NULL);
	g_theXSmartCapMngr->InitSmartCapCtrl();//20220919
	ui->m_btnBeginRecord->setEnabled(false);

	if (!ui->m_btnDetect->isEnabled())//�������ʼ���ԡ���ť���ڷ�ʹ��״̬,��ǰΪ��ʼ����״̬,��Ҫ���·���һ��̽������
	{
		Sleep(100);//zhouhj 2023.7.20 ����̽��������������ʱ,��ֹ�Զ���������ת����
		pNative->Ats_IecDetect(1);
	}

	m_bIsClearCBs = false;
}

/*
<macro type="relay" name="IEC����" id="IecRecord">
	<fault-paras-ex name="" id="">
		<data name="ʹ��" id="Enable" unit="" data-type="bool" value="1" default="0"/>
		<data name="���˼���ģʽ" id="Mode" unit="" data-type="long" value="1" default="0"/> <!-- ��0���㣻1ֱ��ȡCRC�� -->
		<group name="Subscribe0" id="Subscribe0" data-type="Subscribe" value="">
			<data name="DestMac" id="DestMac" data-type="string" value="010CCD013001" unit="" />
			<data name="APPID" id="APPID" data-type="string" value="0x3001" unit="" />
			<data name="Port" id="Port" data-type="string" value="5" unit="" />
			<data name="Type" id="Type" data-type="string" value="2" unit="" />
			<data name="CRC" id="CRC" data-type="string" value="2" unit="" />
		</group>
	</fault-paras-ex>
</macro>
*/

void QSttIecRecordDetectWidget::MuBeginRecord()
{
	on_m_btnBeginRecord_clicked();
}

void QSttIecRecordDetectWidget::on_m_btnBeginRecord_clicked()
{
	if (m_pGridIecCb->rowCount() < 1)
	{
		return;
	}

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	long nSmpRate = 4000;
	BOOL bIsFT3Device = FALSE;
	//�ж��Ƿ�ΪFT3̽��ģʽ
	if ( Qt::Checked == ui->m_chkUseFT3->checkState())
	{
		bIsFT3Device = TRUE;
		if(g_pTheSttTestApp->GetCurrTestMacroUI() == STT_ORG_MACRO_MUAccurAutoTest)
		{
			pXSttCap_61850->m_bIsFT3ADMU = true;
			g_oADMUErrorRanges.InitADMUNormal();
		}

		if (!pXSttCap_61850->m_oCapDeviceAll.ValidSTMode())
		{
			CString strMsgText;
			strMsgText = _T("FT3���տ�ģʽ���ô���,����������.");
			CXMessageBox::information(this,/* tr("��ʾ")*/g_sLangTxt_Message,strMsgText);
			return;
		}

		//20240802 suyang ����CRC���ͣ����������жϳ���   0-��׼16�ֽ�У�飬1-����ĩβУ�飬2-��һ�����ݿ�14�ֽ�У��
		CIecCfgDatasSmvIn* pIecCfgDatasSmvIn = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSmvInMngr();
		long nFT3CrcType =pIecCfgDatasSmvIn->m_nFT3CRCType;

		if (!pXSttCap_61850->m_oCapDeviceAll.ValidSelectFT3CB_PkgLenth(nFT3CrcType))
		{
			CString strMsgText;
			strMsgText = _T("��ǰѡ��FT3���ƿ��Ӧ���ĳ���,��FT3���Ľ���ָ����ڵı��ĳ������ò�һ��.");
			CXMessageBox::information(this,/* tr("��ʾ")*/g_sLangTxt_Message,strMsgText);
			return;
		}

		nSmpRate = pXSttCap_61850->m_oCapDeviceAll.GetSmpRate_FT3();
	}

//	CXSmartCapFileWrite::g_nIsFT3PcapFile = m_bViewFT3;
	g_bSmartCap_RecordNow = TRUE;
	CIecCfgSysParas *pIecSysParas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSysParasMngr();
	pXSttCap_61850->SetPT_CT_Rates(pIecSysParas->GetPrimRatesIn(),bIsFT3Device);//���±��
	pXSttCap_61850->UpdateCapDevicesRecordSmvChRates();

	if (g_pSttIecRecordCbWidget->IsMUTestMode())
	{
		pXSttCap_61850->AddDataset_dsRcdStep6U6I();
	}

	//20241228 suyang ������룬ע��
	//CCapDeviceBase *pSelCapDevice = (CCapDeviceBase*)m_pGridIecCb->GetCurrSelData_BySelect();   //��ȡ��һ��ѡ�еĿ��ƿ�

	//�������¼���豸�����μ����;
	pXSttCap_61850->Reset();
	pXSttCap_61850->UpdateCapDevicesRecordSmvChRates();//20220612 ������ӽ���,����ͨ�����ͼ�CT��PT��ȵȸ���ϵ��
	pXSttCap_61850->InitDvmDevices();//�˴������Ż������Ը���ѡ�еĿ��ƿ飬ȥ��ʼ����Ӧ�����ݼ��������ǳ�ʼ�����п��ƿ�����ݼ�
	pXSttCap_61850->AttachDatasets();
	pXSttCap_61850->InitCapDeviceRecordMngr_SmpRate(nSmpRate);

	if (g_pSttIecRecordCbWidget->IsMUTestMode())
	{
		g_theTestCntrFrame->SetValues_dsRcdStep6U6I(TRUE);
		g_theTestCntrFrame->UpdateCustomReport();
	}
	pXSttCap_61850->InitHarmBaseErrorLimit(bIsFT3Device);

#ifdef _XSmartCap_use_SttRcdSocket_
	pXSttCap_61850->CreateSttRcdSocket();
#endif

	if((m_chkWaveRecord->checkState() == Qt::Checked)&&(m_chkWaveRecord->isVisible()))
	{
		m_bIecCapWriteFile = true;
	}
	else
	{
		m_bIecCapWriteFile = false;
	}

	if (m_bIecCapWriteFile)
	{//�洢¼���ļ����̶����ܣ�����ʾ���ƿ�

#ifdef _XSmartCap_use_SttRcdSocket_
		CString strFile;
		SYSTEMTIME tmSys;
		GetLocalTime(&tmSys);
		strFile = _P_GetLibraryPath();
		strFile.AppendFormat(_T("%d_%d_%d_%d_%d.at02dz"), tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
		CSttRcdSocketBase::CreateAt02dRcdFileWrite(strFile);
#endif
		g_pSttIecRecordCbWidget->InitIecRecordCb(IECRCD_FUNC_Write_File);
		g_pSttIecRecordCbWidget->m_pSelectedCbs = m_pGridIecCb->GetAllSelectedCbs();
	}
	else
	{
		g_pSttIecRecordCbWidget->InitIecRecordCb("");
		g_pSttIecRecordCbWidget->SetSelectedCbs(m_pGridIecCb->GetAllSelectedCbs());
		//���õ�ǰѡ�е��豸
			//g_pSttIecRecordCbWidget->SetCapDevice(pSelCapDevice);
	}

	g_theSttIecRecordMainWidget->ShowIecCbWindow();


//#ifndef _PSX_QT_LINUX_ //20221011 zhouhj �ײ��Զ�������Ҫʹ�ô�ģ��,���ӱ���
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("SttIecRecordDetectDvm.xml");
	pXSttCap_61850->m_pDvmDevice->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

// #ifndef _PSX_QT_LINUX_//20230703 ��Window��,ͬʱ����һ�ݵ�e-Protocol��,���Զ�����ʹ��
	strFile = _P_GetInstallPath();
	strFile += _T("e-Protocol/Library/");
	CreateAllDirectories(strFile);
	strFile += _T("SttIecRecordDetectDvm.xml");
	pXSttCap_61850->m_pDvmDevice->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
// #endif
//#endif

	ui->m_btnDetect->setEnabled(true);//����¼����,���Զ�ֹͣ̽������,�ʸı䰴ťʹ��
	ui->m_btnDetectStop->setEnabled(false);

 	if (g_pSttIecRecordCbWidget->IsMUTestMode())
 	{
 		g_pSttIecRecordCbWidget->m_pSVDelayData = pXSttCap_61850->GetMU_TimeAccurRltData();
// 		g_pSttIecRecordCbWidget->Connect_UpdateMUTimeAccurRlt(TRUE);
 		pXSttCap_61850->g_oSVDelayTickCount.Enter();
 	}

#ifdef _XSmartCap_use_SttRcdSocket_
	Sleep(3000);
#endif
	//�ڽ��滷��׼����֮�󣬷��Ϳ�ʼRecordָ��
	g_pSttIecRecordCbWidget->Ats_IecRecord(m_bIsFromIecfgFile);
	g_pSttIecRecordCbWidget->m_bStopTimerUpdate = FALSE;
}

void QSttIecRecordDetectWidget::slot_chkUseSmvClicked()
{
	m_bViewSmv = ( Qt::Checked == ui->m_chkUseSmv->checkState());
	m_pGridIecCb->m_bViewSmv = m_bViewSmv;

	if (m_bViewSmv)
	{
		m_bViewFT3 = FALSE;
		m_bViewGoose = FALSE;
		m_pGridIecCb->m_bViewGoose = m_bViewGoose;//20240812 suyang ֻ�ܵ�ѡ
		m_pGridIecCb->m_bViewFT3 = m_bViewFT3;
		
		ui->m_chkUseGoose->setCheckState(Qt::Unchecked);
		ui->m_chkUseFT3->setCheckState(Qt::Unchecked);
		ui->m_chkSmvFirstIsTime->setEnabled(true);
		g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.UnselectAllCap(false,/*false*/true,true);

		m_nIecType = STT_IEC_DETECT_TYPE_61850_92;

		if (m_bStartDetect)
		{
			StartDetect();//20241022 suyang  ���¿�ʼ̽��
		}
	} 
	else
	{
		ui->m_chkSmvFirstIsTime->setEnabled(false);
		g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.UnselectAllCap(true,false,false);
	}

	m_pGridIecCb->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);
}

void QSttIecRecordDetectWidget::slot_chkUseGooseClicked()
{
	m_bViewGoose = ( Qt::Checked == ui->m_chkUseGoose->checkState());
	m_pGridIecCb->m_bViewGoose = m_bViewGoose;

	if (m_bViewGoose)
	{
		m_bViewFT3 = FALSE;
		m_bViewSmv = FALSE;
		m_pGridIecCb->m_bViewFT3 = m_bViewFT3;
		m_pGridIecCb->m_bViewSmv = m_bViewSmv;
		ui->m_chkUseSmv->setCheckState(Qt::Unchecked);
		ui->m_chkUseFT3->setCheckState(Qt::Unchecked);
		g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.UnselectAllCap(/*false*/true,false,true);

		m_nIecType = STT_IEC_DETECT_TYPE_61850_GS;
		if (m_bStartDetect)
		{
			StartDetect();//20241022 suyang  ���¿�ʼ̽��
		}
	} 
	else
	{
		g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.UnselectAllCap(false,true,false);
	}

	m_pGridIecCb->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);
}

void QSttIecRecordDetectWidget::slot_chkUseFT3Clicked()
{
	m_bViewFT3 = ( Qt::Checked == ui->m_chkUseFT3->checkState());
	m_pGridIecCb->m_bViewFT3 = m_bViewFT3;

	if (m_bViewFT3)
	{
		m_bViewGoose = FALSE;
		m_bViewSmv = FALSE;
		m_pGridIecCb->m_bViewGoose = m_bViewGoose;
		m_pGridIecCb->m_bViewSmv = m_bViewSmv;
		ui->m_chkUseSmv->setCheckState(Qt::Unchecked);
		ui->m_chkUseGoose->setCheckState(Qt::Unchecked);
		g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.UnselectAllCap(true,true,false);

    	m_nIecType = STT_IEC_DETECT_TYPE_60044;
		if (m_bStartDetect)
		{
			StartDetect();//20241022 suyang  ���¿�ʼ̽��
		}

	} 
	else
	{
		g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.UnselectAllCap(false,false,true);
	}

	m_pGridIecCb->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);
}

void QSttIecRecordDetectWidget::on_m_chkSmvFirstIsTime_clicked()
{
	g_nSmvFirstChIsTdelay =  ( Qt::Checked == ui->m_chkSmvFirstIsTime->checkState());
}

void QSttIecRecordDetectWidget::on_m_btnDetectStop_clicked()
{
    CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
    pNative->Ats_IecDetect(0);
	ui->m_btnDetect->setEnabled(true);
	ui->m_btnDetectStop->setEnabled(false);
	m_bStartDetect = FALSE;
// 	ui->m_chkUseSmv->setEnabled(true);
// 	ui->m_chkUseGoose->setEnabled(true);
// 	ui->m_chkUseFT3->setEnabled(true);
}

void QSttIecRecordDetectWidget::ImportIecfg()
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	pXSttCap_61850->RemoveCapDevices();
	g_theXSmartCapMngr->InitSmartCapCtrl();
	m_pGridIecCb->ShowDatas(NULL);
	ui->m_btnBeginRecord->setEnabled(false);

	BOOL bIsFT3Device = (Qt::Checked == ui->m_chkUseFT3->checkState());

	m_bIsFromIecfgFile = TRUE;
	pXSttCap_61850->InitDvmDevices_BySmvInGin(&g_oSttTestResourceMngr.m_oIecDatasMngr,TRUE);//ͨ��SmvIn��Gin��������
	pXSttCap_61850->AddCapDevices_BySmvInGin(&g_oSttTestResourceMngr.m_oIecDatasMngr); 
	pXSttCap_61850->InitDvmDevices();
	CIecCfgSysParas *pIecSysParas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSysParasMngr();
	pXSttCap_61850->SetPT_CT_Rates(pIecSysParas->GetPrimRatesIn(),bIsFT3Device);

	for (int i = 0; i < g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll.GetCount(); i++)
	{
		CCapDeviceBase* pCapDevice = (CCapDeviceBase*)g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll[i];
		CString strAppID;
		strAppID.Format("0x%04X", pCapDevice->m_dwAppID);
		if(pCapDevice->m_strName.Find(strAppID) == -1)
		{
			if(pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
			{
				strAppID += "_GS_";
			}
			else
			{
				strAppID += "_SV_";
			}

			pCapDevice->m_strName = strAppID + "_" + pCapDevice->m_strName;
		}
	}

	m_pGridIecCb->ShowDatas(&g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll);

	if (!ui->m_btnDetect->isEnabled())//�������ʼ���ԡ���ť���ڷ�ʹ��״̬,��ǰΪ��ʼ����״̬,��Ҫ���·���һ��̽������
	{
		CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;
		pNative->Ats_IecDetect(1);
	}

	//2022-12-25  lijunqing
	assist_event(Event_ID_IecAddCb, NULL);
}

void QSttIecRecordDetectWidget::on_m_btnImportIecfg_clicked()
{
	ImportIecfg();
}

void QSttIecRecordDetectWidget::UpdateIecfg()
{
	if (g_theXSmartCapMngr == NULL)
	{
		return;
	}

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850 == NULL)
	{
		return;
	}

// 	if( !m_bIsFromIecfgFile)//������Ǵ������ļ�����˴����ٿ���
// 	{
// 		return;
// 	}

	if (pXSttCap_61850->m_oCapDeviceAll.GetCount() == 0)//�����δ��̽��Ŀ��ƿ�,����ҪҪ��������
	{
		return;
	}	

	BOOL bIsFT3Device = (Qt::Checked == ui->m_chkUseFT3->checkState());
	CIecCfgSysParas *pIecSysParas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSysParasMngr();
	pXSttCap_61850->SetPT_CT_Rates(pIecSysParas->GetPrimRatesIn(),bIsFT3Device);
	pXSttCap_61850->m_oCapDeviceAll.ClearAllIecfgAttach();
	
	if (g_bSmartCap_RecordNow)//¼��������,���˳�¼�����ӽ���
	{
		g_bSmartCap_RecordNow = FALSE;//��ֹͣ���Ľ���
		g_pSttIecRecordCbWidget->BtnBack();//

		//�����Tabģʽ,�����ˢ�½ӿ�
		if (g_pSttIecRecordCbWidget->IsTabUI_Mode())
		{
			if (g_pSttMUTestIecCbSelWidget != NULL)
			{
				g_pSttMUTestIecCbSelWidget->Refresh_MUTest();
			}
		}
	}
	else//�����̽�����,����ֹͣ̽��
	{
		CSttTestCtrlCntrNative *pNative = (CSttTestCtrlCntrNative*)g_pTheSttTestApp->m_pTestCtrlCntr;//��ֹͣ̽��
		pNative->Ats_IecDetect(0);
	}

	on_m_btnClear_clicked();
}

// void QSttIecRecordDetectWidget::on_m_chkWaveRecord_clicked(int bState)
// {
// 	return;
// }



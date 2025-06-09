#include "QSttBinRecordDlg.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapAnalysisConfig.h"
#include "../../AdjustTool/SttAdjModule.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../RecordTest/SttRcdSocketBase.h"
#include "../../../../Module/SmartCap/XSttCap_61850.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceRcdCh.h"
//#include "QSttBinRecordChMapDlg.h"
#include "QSttBinRecordCbWidget.h"
#include "QSttBinRecordMainDlg.h"
#include "QSttBinRecordSetDlg.h"
#include "QSttSaveCfgDlg.h"
#include "../../../../Module/SmartCap/SmartCapCtrl.h"
#include "QSaveComTradeCfgDlg.h"
#include "../../../../Module/SmartCap/61850Cap/SttRecordToComtradeTool.h"
//#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>
#include "SttBinRecordDefine.h"
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

QSttBinRecordDlg *g_pBinRecord = NULL;

QSttBinRecordDlg::QSttBinRecordDlg(QWidget *parent)
: QDialog(parent)
{
	m_pSttBinRecordModuleGrid = NULL;
	m_pSttBinRecordChsGrid = NULL;
	g_pBinRecord = this;

	m_bLoginRecord = FALSE;
	ui.setupUi(this);
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	CString strFile = _P_GetConfigPath();
	strFile += _T("BinRecordConfig.xml");
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oBinRecordCfgDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	CDataGroup *pDisplayTypeData = (CDataGroup *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_DISPLAYTYPE);
	if (pDisplayTypeData != NULL)
	{
		g_oCapAnalysisConfig.m_nShowPrimaryValue = CString_To_long(pDisplayTypeData->m_strValue);
	}
	InitUI();
	m_bAutoSaveComtradeFile = TRUE;
	m_bRecord = FALSE;
	m_nSampleRate = STT_BINRECORD_ID_FOURTHOUSAND;
	CSttAdjDevice *pCurDevice = &g_oSttTestResourceMngr.m_oCurrDevice;
	InitDatas(pCurDevice);

}

QSttBinRecordDlg::~QSttBinRecordDlg()
{

}

void QSttBinRecordDlg::InitUI()
{
	ui.m_Btn_StartMonitor->setEnabled(false);
	ui.m_ChkAutoSaveComtradeFile->setChecked(m_bAutoSaveComtradeFile);
	connect(ui.m_Btn_BeginRecord, SIGNAL(clicked()), this, SLOT(slot_BeginRecord()));
	connect(ui.m_Btn_StartMonitor, SIGNAL(clicked()), this, SLOT(slot_StartMonitor()));
	connect(ui.m_Btn_Close, SIGNAL(clicked()), this, SLOT(slot_Close()));
	connect(ui.m_ChkAutoSaveComtradeFile, SIGNAL(clicked()), this, SLOT(slot_BtnAutoSaveClicked()));
		connect(ui.m_Btn_RecordCfg, SIGNAL(clicked()), this, SLOT(slot_BtnBinRecordSet()));
	connect(ui.m_Btn_SaveCfg, SIGNAL(clicked()), this, SLOT(slot_Btn_SaveCfgclicked()));
	connect(ui.m_Btn_LoadCfg, SIGNAL(clicked()), this, SLOT(slot_Btn_LoadCfgClicked()));

	m_pSttBinRecordModuleGrid = new QSttBinRecordModuleGrid();
	ui.m_pBinRecordTopTableWidget->setLayout(new QVBoxLayout());
	ui.m_pBinRecordTopTableWidget->layout()->addWidget(m_pSttBinRecordModuleGrid);
	

	m_pSttBinRecordChsGrid = new QSttBinRecordChsGrid();
	ui.m_pBinRecordBottomTableWidget->setLayout(new QVBoxLayout());
	ui.m_pBinRecordBottomTableWidget->layout()->addWidget(m_pSttBinRecordChsGrid);
	m_pSttBinRecordChsGrid->InitGrid();
	CString strText = /*_T("启动录波")*/g_sLangTxt_BinRecord_StartRecord;
	ui.m_Btn_BeginRecord->setText(strText);
	connect(ui.m_Comb_SampleRate, SIGNAL(currentIndexChanged(int)), this, SLOT(On_SmpRateChanged()));
	connect(m_pSttBinRecordModuleGrid, SIGNAL(sig_CheckBoxValue(int,int)), this, SLOT(slot_CheckBoxState(int,int)));
}

void QSttBinRecordDlg::InitDatas(CSttAdjDevice *pSttAdjDevice)
{
// 	g_oCapAnalysisConfig.m_bMU_Test = true;
// 	g_oCapAnalysisConfig.m_bAnalysisData_PhaseDelt = true;
	m_pCapDeviceAll = &g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceAll;
	m_pCapDeviceAll->DeleteAll();
	if (pSttAdjDevice == NULL)
	{
		return;
	}

	CDataGroup *pDeviceAttres = pSttAdjDevice->GetDeviceAttrs();//主板信息
	if (pDeviceAttres)
	{
		CDvmData *pBinCount = (CDvmData*)pDeviceAttres->FindByID(STT_ADJ_ID_BinCount);
		CExBaseList oAllModuleListRef;
		pSttAdjDevice->GetAllModules(&oAllModuleListRef);//获取当前所有模块
		if (pBinCount)
		{
			CCapDeviceRecord *pCapDevBinaryFPGA = new CCapDeviceRecord;
			pCapDevBinaryFPGA->m_nType = PROTOCOL_61850_TYPE_BINARY;
			pCapDevBinaryFPGA->m_nUseFlag = STT_BINRECORD_ID_NONE;
			pCapDevBinaryFPGA->m_strID = /*_T("dsSV1")*/STT_BINRECORD_ID_dsSV1;
			pCapDevBinaryFPGA->m_strName = /*_T("主板")*/g_sLangTxt_BinRecord_Module;
			pCapDevBinaryFPGA->m_nModulePos = STT_BINRECORD_ID_NZERO;//插件位置
			long nBinCount = CString_To_long(pBinCount->m_strValue);
			pCapDevBinaryFPGA->m_nChannelNum = nBinCount;//通道数量
			for (int nBinIndex = STT_BINRECORD_ID_NZERO; nBinIndex < nBinCount; nBinIndex++)
			{
				char strIndex = 'A' + nBinIndex;
				CCapDeviceRcdCh *pBinaryCh = new CCapDeviceRcdCh;
//				pBinaryCh->m_strChannelName = _T("主板");
				pBinaryCh->m_strName = g_sLangTxt_Native_BinX;
				pBinaryCh->m_strName.AppendFormat("%c", strIndex);
				pBinaryCh->m_strID.Format(_T("Bin%c"), strIndex);
				UpdateCapDevicesByBinRecordCfg(pBinaryCh, pCapDevBinaryFPGA);
				pCapDevBinaryFPGA->AddNewChild(pBinaryCh);
			}
			pCapDevBinaryFPGA->m_bSelect = TRUE;
			m_pCapDeviceAll->AddNewChild(pCapDevBinaryFPGA);
		}
		POS pos = oAllModuleListRef.GetHeadPosition();
		CSttAdjModule *pModule = NULL;
		long nBinExModuleIndex = STT_BINRECORD_ID_NZERO;
		
		while (pos)
		{
			CString strModuleType;
			pModule = (CSttAdjModule *)oAllModuleListRef.GetNext(pos);
			CDataGroup* pAttrGroup = (CDataGroup*)pModule->FindByID(/*_T("ModuleAttrs")*/STT_BINRECORD_ID_ModuleAttrs);
			CDvmData *pModuleType = (CDvmData*)pAttrGroup->FindByID(/*_T("ModuleType")*/STT_BINRECORD_ID_ModuleType);
			strModuleType = pModuleType->m_strValue;
			if (strModuleType == STT_MODULE_TYPE_SWITCH_ID)//获取开关量模块
			{
				nBinExModuleIndex++;
				CCapDeviceRecord *pCapDevBinaryModule = new CCapDeviceRecord;
				pCapDevBinaryModule->m_nUseFlag = STT_BINRECORD_ID_NONE;
				pCapDevBinaryModule->m_nType = PROTOCOL_61850_TYPE_BINARY;
				pCapDevBinaryModule->m_strID.Format(_T("dsSV%d"), nBinExModuleIndex+1);

				CDvmData *pModuleName = (CDvmData*)pAttrGroup->FindByID(/*_T("Model")*/STT_BINRECORD_ID_Model);
				pCapDevBinaryModule->m_strName = pModuleName->m_strValue;
				CDvmData *pModulePos = (CDvmData*)pAttrGroup->FindByID(/*_T("ModulePos")*/STT_BINRECORD_ID_ModulePos);
				pCapDevBinaryModule->m_nModulePos = CString_To_long(pModulePos->m_strValue);
				POS posAttr = pAttrGroup->GetHeadPosition();
				CDvmData *pAttr = NULL;
				long nBinCount = STT_BINRECORD_ID_NZERO;
				while (posAttr)
				{
					pAttr = (CDvmData *)pAttrGroup->GetNext(posAttr);
					if (pAttr->m_strID.Find(/*_T("SwitchIn")*/STT_BINRECORD_ID_SwitchIn) != -1)
					{
						long nGroupIndex = CString_To_long(pAttr->m_strID.right(STT_BINRECORD_ID_NONE));
						if (pAttr->m_strValue == /*_T("1")*/STT_BINRECORD_ID_STRONE)
						{
							nBinCount += STT_BINRECORD_ID_NEIGHT;
							for (int nBinIndex = nGroupIndex * STT_BINRECORD_ID_NEIGHT + STT_BINRECORD_ID_NONE; nBinIndex <= (nGroupIndex + STT_BINRECORD_ID_NONE) * STT_BINRECORD_ID_NEIGHT; nBinIndex++)
							{
								CCapDeviceRcdCh *pBinaryCh = new CCapDeviceRcdCh;
//								pBinaryCh->m_strChannelName = pModuleName->m_strValue;
								pBinaryCh->m_strName = g_sLangTxt_Native_BinX;
								pBinaryCh->m_strName.AppendFormat("%d", nBinIndex);
								pBinaryCh->m_strID.Format(_T("ExBin%d_%02d"), nBinExModuleIndex, nBinIndex);
								UpdateCapDevicesByBinRecordCfg(pBinaryCh, pCapDevBinaryModule);

								pCapDevBinaryModule->AddNewChild(pBinaryCh);

							}
						}
					}
				}
				pCapDevBinaryModule->m_nChannelNum = nBinCount;
				pCapDevBinaryModule->m_bSelect = TRUE;
				m_pCapDeviceAll->AddNewChild(pCapDevBinaryModule);
			}
		}
		oAllModuleListRef.RemoveAll();
	}
	m_pSttBinRecordModuleGrid->InitGrid(m_pCapDeviceAll);
	m_pSttBinRecordModuleGrid->ShowDatas(m_pCapDeviceAll);

	long nValue = m_pCapDeviceAll->GetCount();
	for (int i = STT_BINRECORD_ID_NZERO; i < nValue; i++)
	{
		CCapDeviceRecord *pCapDevBin = (CCapDeviceRecord *)m_pCapDeviceAll->GetAtIndex(i);
		m_pSttBinRecordChsGrid->ShowDatas(pCapDevBin);
	}

	CDataGroup *pChannelInformationGroup = (CDataGroup *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);
	pChannelInformationGroup->DeleteAll();
}

void QSttBinRecordDlg::GenerateParas()
{
	m_oBinRecordParas.DeleteAll();
	if (m_bRecord == FALSE)
	{
		m_oBinRecordParas.AddNewData(_T("起停使能"), _T("Enable"), _T("long"), STT_BINRECORD_ID_STRONE);
	}
	else
	{
		m_oBinRecordParas.AddNewData(_T("起停使能"), _T("Enable"), _T("long"), STT_BINRECORD_ID_STRZERO);
	}
	m_oBinRecordParas.AddNewData(_T("Sample"), m_nSampleRate);
	POS posModule = m_pCapDeviceAll->GetHeadPosition();
	CCapDeviceRecord *pModule = NULL;
	while (posModule)
	{
		pModule = (CCapDeviceRecord*)m_pCapDeviceAll->GetNext(posModule);
		if (pModule->m_bSelect == FALSE)
		{
			continue;
		}
		if (pModule->m_nModulePos == STT_BINRECORD_ID_NZERO)
		{
			CCapDeviceRcdCh *pBin = NULL;
			POS posBin = pModule->GetHeadPosition();
			while (posBin)
			{
				pBin = (CCapDeviceRcdCh*)pModule->GetNext(posBin);
				CDataGroup *pBinNew = new CDataGroup;
				pBinNew->m_strID = pBin->m_strID;
				pBinNew->m_strName = pBin->m_strName;
				pBinNew->m_strDataType = _T("Bin");
				pBinNew->AddNewData(STT_BINRECORD_ID_ETYPE, pBin->m_nEType);
				pBinNew->AddNewData(/*_T("SwitchVolt")*/STT_BINRECORD_ID_SwitchVolt, pBin->m_fSwitchVolt);
				pBinNew->AddNewData(STT_BINRECORD_ID_MEASGEAR, pBin->m_nMeasGear);
				m_oBinRecordParas.AddNewChild(pBinNew);
			}
		}
		else
		{
			CDataGroup *pModuleNew = new CDataGroup;
			pModuleNew->m_strID = pModule->m_strID;
			pModuleNew->m_strDataType = _T("BinExModule");
			CCapDeviceRcdCh *pBin = NULL;
			POS posBin = pModule->GetHeadPosition();
			while (posBin)
			{
				pBin = (CCapDeviceRcdCh*)pModule->GetNext(posBin);
				CDataGroup *pBinNew = new CDataGroup;
				pBinNew->m_strID = pBin->m_strID;
				pBinNew->m_strName = pBin->m_strName;
				pBinNew->m_strDataType = _T("Bin");
				pBinNew->AddNewData(STT_BINRECORD_ID_ETYPE, pBin->m_nEType);
				pBinNew->AddNewData(/*_T("SwitchVolt")*/STT_BINRECORD_ID_SwitchVolt, pBin->m_fSwitchVolt);
				pBinNew->AddNewData(STT_BINRECORD_ID_MEASGEAR, pBin->m_nMeasGear);
				pModuleNew->AddNewChild(pBinNew);
			}
			m_oBinRecordParas.AddNewChild(pModuleNew);
		}
	}
}

void QSttBinRecordDlg::InitBinRecord()
{
	if (m_bLoginRecord)
	{
		return;
	}
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	m_bLoginRecord = pXSttCap_61850->CreateSttRcdSocket();
	pXSttCap_61850->CreateCapTrhead();
	pXSttCap_61850->CreateUpdateDvmDeviceDatasThread();
	pXSttCap_61850->SetDvmDevice(&g_theSmartCapCtrl->m_oDeviceModel);
	pXSttCap_61850->InitDvmDevices();
	pXSttCap_61850->AddDataset_dsRcdStep6U6I();
	pXSttCap_61850->AttachDatasets();
}

void QSttBinRecordDlg::SendBinRecordCmd()
{
	GenerateParas();
//	g_nSttRcdSocketUseZip = 0;
	g_pTheSttTestApp->m_pTestCtrlCntr->Ats_BinRecord(&m_oBinRecordParas);
	if (m_bAutoSaveComtradeFile)//自动保存录波文件
	{
		SYSTEMTIME tmSys;
		GetLocalTime(&tmSys);
		m_strPkgZipFile = _P_GetLibraryPath();
		m_strPkgUnZipFile = _P_GetLibraryPath();
		m_strPCapFile = _P_GetLibraryPath();
		m_strComtradeFile = _P_GetLibraryPath();
		m_strPkgZipFile.AppendFormat(_T("%d_%d_%d_%d_%d.at02dz"), tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
		m_strPkgUnZipFile.AppendFormat(_T("%d_%d_%d_%d_%d.at02d"), tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
		m_strPCapFile.AppendFormat(_T("%d_%d_%d_%d_%d.txt"), tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
		m_strComtradeFile.AppendFormat(_T("%d_%d_%d_%d_%d"), tmSys.wMonth, tmSys.wDay, tmSys.wHour, tmSys.wMinute, tmSys.wSecond);
		CSttRcdSocketBase::CreateAt02dRcdFileWrite(m_strPkgZipFile);
	}
}


void QSttBinRecordDlg::ExistBinRecord()
{
	g_pTheSttTestApp->m_pTestCtrlCntr->StopTest();
	CSttRcdSocketBase::CloseAt02dRcdFileWrite();
	if (g_theSmartCapCtrl != NULL)
	{
		g_pTheSttTestApp->ExitSttIecRecord();
	}
	m_bRecord = FALSE;
}

void QSttBinRecordDlg::UpdateBinRecordCfgByCapDevices(CCapDeviceRcdCh *pBinaryCh)
{
	CDvmData *pDvmData;
	CDataGroup *pChannelInformationGroup = (CDataGroup *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);
	if (pChannelInformationGroup == NULL)
	{
		return;
	}
	CDataGroup *pBinGroup = (CDataGroup *)pChannelInformationGroup->FindByID(pBinaryCh->m_strID);
	if (pBinGroup != NULL)
	{
		pBinGroup->m_strName = pBinaryCh->m_strName;
	}
	else
	{
		pBinGroup = new CDataGroup;
		pBinGroup->m_strName = pBinaryCh->m_strName;
		pBinGroup->m_strID = pBinaryCh->m_strID;
		pBinGroup->m_strValue = STT_BINRECORD_ID_STRONE;
		pBinGroup->AddNewData(/*_T("主板")*/g_sLangTxt_BinRecord_Module, STT_BINRECORD_ID_MODULE, _T(""), _T(""));
		pBinGroup->AddNewData(/*_T("相别")*/g_sLangTxt_Native_phaseDifference, STT_BINRECORD_ID_CHANGTYPE, _T(""), STT_BINRECORD_ID_STRZERO);
		pBinGroup->AddNewData(/*_T("记录类型")*/g_sLangTxt_BinRecord_RecordType, STT_BINRECORD_ID_RECORDTYPE, _T(""), STT_BINRECORD_ID_STRFOUR);
		pBinGroup->AddNewData(/*_T("档位")*/g_sLangTxt_Native_Gear, STT_BINRECORD_ID_MEASGEAR, _T(""), STT_BINRECORD_ID_STRTHREE);
		pBinGroup->AddNewData(/*_T("夹钳比率")*/g_sLangTxt_BinRecord_ClampRate, STT_BINRECORD_ID_CLAMPRATE, _T(""), STT_BINRECORD_ID_STRONETHOUSAND);
		pBinGroup->AddNewData(/*_T("门槛值")*/g_sLangTxt_Native_Threshold, STT_BINRECORD_ID_THRESHOLDS, _T(""), STT_BINRECORD_ID_STRFIVE);
		pBinGroup->AddNewData(/*_T("一次侧")*/g_sLangTxt_BinRecord_PrimValue, STT_BINRECORD_ID_PRIMVALUE, _T(""), STT_BINRECORD_ID_STRTEN);
		pBinGroup->AddNewData(/*_T("二次侧")*/g_sLangTxt_BinRecord_SecondValue, STT_BINRECORD_ID_SECONDVALUE, _T(""), STT_BINRECORD_ID_STRONEHUNDRED);
		pChannelInformationGroup->AddNewChild(pBinGroup);
	}

	if (pChannelInformationGroup != NULL)
	{
		POS pos = pChannelInformationGroup->GetHeadPosition();
		while (pos)
		{
			CDataGroup *pBinGroup = (CDataGroup *)pChannelInformationGroup->GetNext(pos);
			if (pBinaryCh->m_strID != pBinGroup->m_strID)
			{
				continue;
			}
			if (pBinGroup != NULL)
			{
				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_MODULE);
				if (pDvmData != NULL)
				{
					pDvmData->m_strName = pBinaryCh->GetModuleName();
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_CHANGTYPE);
				if (pDvmData != NULL)
				{
					pDvmData->m_strValue.Format(_T("%d"), pBinaryCh->m_nChAngType);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_RECORDTYPE);
				if (pDvmData != NULL)
				{
					pDvmData->m_strValue.Format(_T("%d"), pBinaryCh->m_nEType);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_MEASGEAR);
				if (pDvmData != NULL)
				{
					pDvmData->m_strValue.Format(_T("%d"), pBinaryCh->m_nMeasGear);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_CLAMPRATE);
				if (pDvmData != NULL)
				{
					pDvmData->m_strValue.Format(_T("%.2f"), pBinaryCh->m_dClampRate);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_THRESHOLDS);
				if (pDvmData != NULL)
				{
					pDvmData->m_strValue.Format(_T("%.2f"), pBinaryCh->m_fSwitchVolt);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_PRIMVALUE);
				if (pDvmData != NULL)
				{
					pDvmData->m_strValue.Format(_T("%.02lf"), pBinaryCh->m_dPrimValue);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_SECONDVALUE);
				if (pDvmData != NULL)
				{
					pDvmData->m_strValue.Format(_T("%.02lf"), pBinaryCh->m_dSecondValue);
				}
				break;
			}
		}
	}
}

void QSttBinRecordDlg::UpdateCapDevicesByBinRecordCfg(CCapDeviceRcdCh *pBinaryCh, CCapDeviceRecord *pCapDevBinaryModule)
{
	CCapDeviceRecord *pCapDevBin = NULL;
	CDvmData *pDvmData = NULL;

	CDataGroup *pChannelInformationGroup = (CDataGroup *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);

	if (pChannelInformationGroup == NULL)
	{
		return;
	}

	CDataGroup *pCfgBinGroup = (CDataGroup *)pChannelInformationGroup->FindByID(pBinaryCh->m_strID);

	if (pCfgBinGroup != NULL)
	{
		pCfgBinGroup->m_strName = pBinaryCh->m_strName;
		pCapDevBinaryModule->m_nUseFlag = CString_To_long(pCfgBinGroup->m_strValue);
	}

	if (pChannelInformationGroup != NULL)
	{
		POS pos = pChannelInformationGroup->GetHeadPosition();
		while (pos)
		{
			CDataGroup *pBinGroup = (CDataGroup *)pChannelInformationGroup->GetNext(pos);
			if (pBinGroup->m_strID != pBinaryCh->m_strID)
			{
				continue;
			}
			if (pBinGroup != NULL)
			{
				//pDvmData = (CDvmData *)pBinGroup->FindByID("Module");
				//if (pDvmData != NULL)
				//{
				//	pBinaryCh->m_strChannelName = pDvmData->m_strName;
				//}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_CHANGTYPE);
				if (pDvmData != NULL)
				{

					pBinaryCh->m_nChAngType = CString_To_long(pDvmData->m_strValue);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_RECORDTYPE);
				if (pDvmData != NULL)
				{
					pBinaryCh->m_nEType = CString_To_long(pDvmData->m_strValue);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_MEASGEAR);
				if (pDvmData != NULL)
				{
					pBinaryCh->m_nMeasGear = CString_To_long(pDvmData->m_strValue);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_CLAMPRATE);
				if (pDvmData != NULL)
				{
					pBinaryCh->m_dClampRate = CString_To_double(pDvmData->m_strValue);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_THRESHOLDS);
				if (pDvmData != NULL)
				{
					pBinaryCh->m_fSwitchVolt = CString_To_double(pDvmData->m_strValue);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_PRIMVALUE);
				if (pDvmData != NULL)
				{
					pBinaryCh->m_dPrimValue = CString_To_double(pDvmData->m_strValue);
				}

				pDvmData = (CDvmData *)pBinGroup->FindByID(STT_BINRECORD_ID_SECONDVALUE);
				if (pDvmData != NULL)
				{
					pBinaryCh->m_dSecondValue = CString_To_double(pDvmData->m_strValue);
				}

				break;
			}
		}
	}
}

void QSttBinRecordDlg::slot_BeginRecord()
{
	CString strBeginRecord = /*_T("启动录波")*/g_sLangTxt_BinRecord_StartRecord;
	CString strStopRecord = /*_T("停止录波")*/g_sLangTxt_BinRecord_StopRecord;
	CString strText = ui.m_Btn_BeginRecord->text();
	if (strText == strBeginRecord)
	{
		InitBinRecord();
		if (!m_bLoginRecord)
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle(/*"提示"*/g_sLangTxt_Message);
			msgBox.setText(/*联机失败*/g_sLangTxt_OnlineFail + "!");
			QAbstractButton *okButton = msgBox.addButton(/*"确定"*/g_sLangTxt_OK, QMessageBox::AcceptRole);
			okButton->setText(/*"确定"*/g_sLangTxt_OK);
			msgBox.setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::Dialog);
			msgBox.exec();
			if (msgBox.clickedButton() == okButton)
			{
				return;
			}
		}
		m_bRecord = TRUE;
		g_bSmartCap_RecordNow = TRUE;
		g_theXSmartCapMngr->m_pX61850Cap->BeginRecord();
		g_pSttBinRecordCbWidget->SetCapDeviceAll(m_pCapDeviceAll);
		g_pSttBinRecordCbWidget->RecordCapDevice();
		g_theXSmartCapMngr->m_pX61850Cap->UpdateCapDevicesRecordSmvChRates();
		g_theXSmartCapMngr->m_pX61850Cap->InitCapDeviceRecordMngr_SmpRate(m_nSampleRate);//用于更新变比
		g_pSttBinRecordCbWidget->m_oTimerBinRcdUpdate.start(1000); 
		SendBinRecordCmd();
		ui.m_Btn_StartMonitor->setEnabled(true);
		ui.m_Btn_BeginRecord->setText(strStopRecord);
	}
	else if (strText == strStopRecord)
	{
		g_bSmartCap_RecordNow = FALSE;
		m_bRecord = FALSE;
		g_pTheSttTestApp->m_pTestCtrlCntr->StopTest();
		QSaveComTradeCfgDlg oSaveComTradeCfgDlg;
		oSaveComTradeCfgDlg.show();
		oSaveComTradeCfgDlg.exec();

		CSttRcdSocketBase::CloseAt02dRcdFileWrite();
		stt_rcd_unzip_file(m_strPkgZipFile.GetString(), m_strPkgUnZipFile.GetString());
		stt_save_bin_record_file_text(m_strPkgUnZipFile, m_strPCapFile.GetString());

		//m_strPkgZipFile = _P_GetLibraryPath();
		//m_strPkgZipFile += _T("8_26_15_22_37.at02dz");
		//m_strComtradeFile = oSaveComTradeCfgDlg.m_strFilePath /*+ oSaveComTradeCfgDlg.m_strFileName*/;
		//m_strComtradeFile += _T("/001");//调试
		m_strComtradeFile = oSaveComTradeCfgDlg.m_strFilePath + "/" + oSaveComTradeCfgDlg.m_strFileName;
		//2024.9.29 zhangyq 转换成comtrade文件
		SttRecordToComtradeTool oSttRecordToComtradeTool;
		oSttRecordToComtradeTool.InitRecordSrcDatas_at02dz(m_strPkgZipFile, m_pCapDeviceAll, &m_oBinRecordCfgDataGroup);
		oSttRecordToComtradeTool.SaveContradeFile(m_strComtradeFile, TRUE);

		ui.m_Btn_BeginRecord->setText(strBeginRecord);
	}	
}

void QSttBinRecordDlg::slot_StartMonitor()
{
	g_theSttBinRecordMainWidget->on_ShowBinRecordCbWindow();
}

void QSttBinRecordDlg::slot_Close()
{
	ExistBinRecord();
// 	m_strPkgZipFile = _P_GetLibraryPath();
// 	m_strPkgUnZipFile = _P_GetLibraryPath();
//	m_strPCapFile = _P_GetLibraryPath();
// 	m_strPkgZipFile += _T("8_23_10_38_32.at02dz");
// 	m_strPkgUnZipFile += _T("001.at02d");
// 	m_strPCapFile += _T("001.txt");//调试用
	stt_rcd_unzip_file(m_strPkgZipFile.GetString(), m_strPkgUnZipFile.GetString());
	stt_save_bin_record_file_text(m_strPkgUnZipFile, m_strPCapFile.GetString());
	g_theSttBinRecordMainWidget->close();
}

void QSttBinRecordDlg::On_SmpRateChanged()
{
	CString strSample = ui.m_Comb_SampleRate->currentText();
	long nIndexK = strSample.Find("k");
	CString strDigit = strSample.left(nIndexK);
	long nSampleK = CString_To_long(strSample);
	m_nSampleRate = nSampleK * STT_BINRECORD_ID_ONETHOUSAND;
}

void QSttBinRecordDlg::slot_BtnAutoSaveClicked()
{
	m_bAutoSaveComtradeFile = !m_bAutoSaveComtradeFile;
}

void QSttBinRecordDlg::slot_BtnBinRecordSet()
{
	CCapDeviceRcdCh *pBinaryCh;
	long nValue = m_pCapDeviceAll->GetCount();
	for (int i = STT_BINRECORD_ID_NZERO; i < nValue; i++)
	{
		pBinaryCh = new CCapDeviceRcdCh;
		CCapDeviceRecord *pCapDevBin = (CCapDeviceRecord *)m_pCapDeviceAll->GetAtIndex(i);
		POS pos = pCapDevBin->GetHeadPosition();
		while (pos)
		{
			pBinaryCh = (CCapDeviceRcdCh *)pCapDevBin->GetNext(pos);
			UpdateBinRecordCfgByCapDevices(pBinaryCh);    //把CapDevice中的数据更新到配置文件链表中
		}

	}
	QSttBinRecordSetDlg SttBinRecordSetDlg(m_pCapDeviceAll, &m_oBinRecordCfgDataGroup, this);

	if (SttBinRecordSetDlg.exec() == QDialog::Accepted)
	{
		CDvmData *pFolderPathData = (CDvmData *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_DEFAULTSAVEPATH);
		if (pFolderPathData != NULL)
		{
			QDir dir;
			dir.mkpath(pFolderPathData->m_strValue);
		}
		m_oBinRecordCfgDataGroup = *SttBinRecordSetDlg.m_pBinRecordSetGroup;
		SttBinRecordSetDlg.SaveDataToCfg();  //保存到配置文件中
		CDataGroup *pDisplayTypeData = (CDataGroup *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_DISPLAYTYPE);
		if (pDisplayTypeData != NULL)
		{
			g_oCapAnalysisConfig.m_nShowPrimaryValue = CString_To_long(pDisplayTypeData->m_strValue);
		}
	}
}

void QSttBinRecordDlg::slot_CheckBoxState(int nRow,int nState)    //根据checkbox的状态设置配置文件中的值
{
	CDataGroup *pBinRecordChannel = (CDataGroup *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);
	CDataGroup *pBinRecordState;
	long nBinRecordCount = pBinRecordChannel->GetCount();
	if (nRow == STT_BINRECORD_ID_NZERO)
	{
		for (int BinID = STT_BINRECORD_ID_NZERO; BinID < nBinRecordCount; BinID++)
		{
			char strIndex = 'A' + BinID;
			CString strGroupID;
			strGroupID.Format(_T("Bin%c"), strIndex);

			pBinRecordState = (CDataGroup *)pBinRecordChannel->FindByID(strGroupID);
			if (pBinRecordState != NULL)
			{
				if (nState == STT_BINRECORD_ID_NZERO)
				{
					pBinRecordState->m_strValue = STT_BINRECORD_ID_STRZERO;
				}
				else if (nState == STT_BINRECORD_ID_NONE)
				{
					pBinRecordState->m_strValue = STT_BINRECORD_ID_STRONE;
				}
			}
			else
			{
				break;
			}
		}
	}
	else if (nRow == STT_BINRECORD_ID_NONE || nRow == STT_BINRECORD_ID_NTWO)
	{
		for (int BinID = STT_BINRECORD_ID_NZERO; BinID < nBinRecordCount; BinID++)
		{
			CString strGroupID;
			strGroupID.Format(_T("ExBin%d_%02d"), nRow, BinID + STT_BINRECORD_ID_NONE);

			CDataGroup *pBinRecordState = (CDataGroup *)pBinRecordChannel->FindByID(strGroupID);
			if (pBinRecordState != NULL)
			{
				pBinRecordState->m_strValue = (nState == STT_BINRECORD_ID_NZERO) ? STT_BINRECORD_ID_STRZERO : STT_BINRECORD_ID_STRONE;
			}
			else
			{
				break;
			}
		}
	}
}

void QSttBinRecordDlg::slot_Btn_SaveCfgclicked()   //保存配置
{
	CDvmData *pFolderPathData = (CDvmData *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_DEFAULTSAVEPATH);
	CDvmData *pFileNameData = (CDvmData *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_BINRECORDFILENAME);

if (!pFolderPathData && !pFileNameData) 
{
    return;
}
	QSttSaveCfgDlg oSaveFileCfgDlg(pFolderPathData->m_strValue, pFileNameData->m_strValue);

	oSaveFileCfgDlg.show();

	if (oSaveFileCfgDlg.exec() == QDialog::Accepted)
	{
		if (pFolderPathData != NULL)
		{
			CString strPath = oSaveFileCfgDlg.ui.m_pEditSavePath->text();
			CString strFileName = oSaveFileCfgDlg.ui.m_pEditFileName->text();

			if (strPath.IsEmpty() || strFileName.IsEmpty())
			{
				return;
			}
			QMessageBox::StandardButton reply;
			reply = QMessageBox::question(this, g_sLangTxt_CharacterEng_FaulTipTile, g_sLangTxt_BinRecord_SaveDefaultCfg/*CString("是否保存为默认配置?")*/,
				QMessageBox::Yes | QMessageBox::No);

			if (reply == QMessageBox::Yes)
			{
				pFolderPathData->m_strValue = strPath;
				pFileNameData->m_strValue = strFileName;

				CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
				m_oBinRecordCfgDataGroup.SaveXmlFile(strPath + "/" + strFileName, CDataMngrXmlRWKeys::g_pXmlKeys);
				CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
			}
		}
	}
}

void QSttBinRecordDlg::slot_Btn_LoadCfgClicked()   //导入配置
{
	QFileDialog oFileDlg(this);

	oFileDlg.setWindowTitle(/*CString("选择文件")*/g_sLangTxt_BinRecord_SelFile);
	oFileDlg.setFileMode(QFileDialog::ExistingFiles);
	oFileDlg.setViewMode(QFileDialog::List);
	oFileDlg.show();

	oFileDlg.setNameFilter("XML Files (*.xml)");
	oFileDlg.setAcceptMode(QFileDialog::AcceptOpen);

	CString strDirPath;
	
	if (oFileDlg.exec() == QFileDialog::Accepted)
	{
		strDirPath = oFileDlg.selectedFiles().first();

		if (!strDirPath.endsWith(".xml", Qt::CaseInsensitive)) 
		{
			return;
		}

		m_oBinRecordCfgDataGroup.DeleteAll();
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		m_oBinRecordCfgDataGroup.OpenXmlFile(strDirPath, CDataMngrXmlRWKeys::g_pXmlKeys);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

		long nValue = m_pCapDeviceAll->GetCount();
		CDataGroup *pChannelInformationGroup = (CDataGroup *)m_oBinRecordCfgDataGroup.FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);

		if (pChannelInformationGroup == NULL)
		{
			return;
		}
		for (int i = STT_BINRECORD_ID_NZERO; i < nValue; i++)
		{
			CCapDeviceRecord *pCapDevBin = (CCapDeviceRecord *)m_pCapDeviceAll->GetAtIndex(i);
			long nCapDevBinNum = pCapDevBin->GetCount();
			long nBinCfgBinNum = pChannelInformationGroup->GetCount();

			for (long nNewBinNum = nBinCfgBinNum - STT_BINRECORD_ID_NONE; nNewBinNum >= nCapDevBinNum; nNewBinNum--)
			{
				pChannelInformationGroup->DeleteAt(nNewBinNum);
			}

			POS pos = pCapDevBin->GetHeadPosition();
			while (pos)
			{
				CCapDeviceRcdCh *pBinaryCh = (CCapDeviceRcdCh *)pCapDevBin->GetNext(pos);

				UpdateCapDevicesByBinRecordCfg(pBinaryCh, pCapDevBin);   //配置文件中的数据更新到CapDevice中
			}

			m_pSttBinRecordChsGrid->ShowDatas(pCapDevBin);
		}

	}
}

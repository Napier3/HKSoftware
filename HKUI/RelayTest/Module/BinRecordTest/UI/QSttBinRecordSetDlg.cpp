#include "QSttBinRecordSetDlg.h"
#include "../../../../Module/API/GlobalConfigApi.h"
//#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <QFileDialog>
#include "SttBinRecordDefine.h"
#include "../../XLangResource_Native.h"

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QStandardPaths>
#else
#include <QDesktopServices>
#endif

QSttBinRecordSetDlg::QSttBinRecordSetDlg(CCapDeviceMngr *pCapDeviceAll, CDataGroup *pBinRecordCfgDataGroup, QWidget *parent)
{
	ui.setupUi(this);
	m_pSttBinRecordSetGrid = new QSttBinRecordSetGrid();
	ui.m_pBinRecordSetTableWidget->setLayout(new QVBoxLayout());
	ui.m_pBinRecordSetTableWidget->layout()->addWidget(m_pSttBinRecordSetGrid);
	m_pSttBinRecordSetGrid->InitGrid();

	CDataGroup *pDataGroup = (CDataGroup *)pBinRecordCfgDataGroup->FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);
	if (pDataGroup != NULL)
	{
//	POS pos = pDataGroup->GetHeadPosition();
	m_pSttBinRecordSetGrid->ShowDatas(pDataGroup);
	}

	connect(m_pSttBinRecordSetGrid, SIGNAL(sig_BinSetGridRowValue(int)), this, SLOT(slot_BtnEnable(int)));
	m_pBinRecordSetGroup = pBinRecordCfgDataGroup;

	InitComboBox(pCapDeviceAll);
	InitConnect();
	InitData();
}

QSttBinRecordSetDlg::~QSttBinRecordSetDlg()
{
	delete m_pSttBinRecordSetGrid;
	m_pSttBinRecordSetGrid = NULL;
}

void QSttBinRecordSetDlg::InitData()
{
	CDvmData *pDvmData;
	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTIMETYPE);
	if (pDvmData != NULL)
	{
		if (CString_To_long(pDvmData->m_strValue))
		{
			ui.m_pRButtonAll->setChecked(false);
			ui.m_pRButtronCustomize->setChecked(true);
			ui.m_pEditCustomize->setEnabled(true);
		}
		else
		{
			ui.m_pRButtonAll->setChecked(true);
			ui.m_pRButtronCustomize->setChecked(false);
			ui.m_pEditCustomize->setEnabled(false);
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_BINRECORDTYPE);
	if (pDvmData != NULL)
	{
		if (CString_To_long(pDvmData->m_strValue))
		{
			ui.m_pRButtonALL->setChecked(false);
			ui.m_pRButtonPlug->setChecked(true);
			ui.m_pCmbButtonPlug->setEnabled(true);
		}
		else
		{
			ui.m_pRButtonALL->setChecked(true);
			ui.m_pRButtonPlug->setChecked(false);
			ui.m_pCmbButtonPlug->setEnabled(false);
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_DISPLAYTYPE);
	if (pDvmData != NULL)
	{
		long nValue = CString_To_long(pDvmData->m_strValue);
		if (nValue == STT_BINRECORD_ID_NZERO)
		{
			ui.m_pRButtonOne->setChecked(true);
			ui.m_pRButtonTwo->setChecked(false);
		}
		else if (nValue == STT_BINRECORD_ID_NONE)
		{
			ui.m_pRButtonOne->setChecked(false);
			ui.m_pRButtonTwo->setChecked(true);
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERTYPE);
	if (pDvmData != NULL)
	{
		long nValue = CString_To_long(pDvmData->m_strValue);

		if (nValue == STT_BINRECORD_ID_NZERO)
		{
			ui.m_pRButtonFlip->setChecked(true);
			ui.m_pRButtonRis->setChecked(false);
			ui.m_pRButtonRis->setChecked(false);
			ui.m_pRButtonGPS->setChecked(false);

			ui.m_pEditHour->setEnabled(false);
			ui.m_pEditminute->setEnabled(false);
			ui.m_pEditsecond->setEnabled(false);
		}
		else if (nValue == STT_BINRECORD_ID_NONE)
		{
			ui.m_pRButtonFlip->setChecked(false);
			ui.m_pRButtonRis->setChecked(true);
			ui.m_pRButtonRis->setChecked(false);
			ui.m_pRButtonGPS->setChecked(false);

			ui.m_pEditHour->setEnabled(false);
			ui.m_pEditminute->setEnabled(false);
			ui.m_pEditsecond->setEnabled(false);
		}
		else if (nValue == STT_BINRECORD_ID_NTWO)
		{
			ui.m_pRButtonFlip->setChecked(false);
			ui.m_pRButtonRis->setChecked(false);
			ui.m_pRButtonRis->setChecked(true);
			ui.m_pRButtonGPS->setChecked(false);

			ui.m_pEditHour->setEnabled(false);
			ui.m_pEditminute->setEnabled(false);
			ui.m_pEditsecond->setEnabled(false);
		}
		else if (nValue == STT_BINRECORD_ID_NTHREE)
		{
			ui.m_pRButtonFlip->setChecked(false);
			ui.m_pRButtonRis->setChecked(false);
			ui.m_pRButtonRis->setChecked(false);
			ui.m_pRButtonGPS->setChecked(true);

			ui.m_pEditHour->setEnabled(true);
			ui.m_pEditminute->setEnabled(true);
			ui.m_pEditsecond->setEnabled(true);
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDALL);
	if (pDvmData != NULL)
	{
		CString strText = /*"排列在最前"*/g_sLangTxt_BinRecord_ArrangeTop;
		CString strText1 = /*"排列在最后"*/g_sLangTxt_BinRecord_ArrangeLast;
		if (CString_To_long(pDvmData->m_strValue) == STT_BINRECORD_ID_NONE)
		{
			ui.m_pBtnALL->setText(strText);
		}
		else
		{
			ui.m_pBtnALL->setText(strText1);
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDPLUG);
	if (pDvmData != NULL)
	{
		long nValue = CString_To_long(pDvmData->m_strValue);
		if (nValue == STT_BINRECORD_ID_NZERO)
		{
			//ui.m_pRButtonALL->setChecked(true);
			//ui.m_pRButtonPlug->setChecked(false);
			ui.m_pCmbButtonPlug->setCurrentIndex(STT_BINRECORD_ID_NZERO);
		}
		else if (nValue == STT_BINRECORD_ID_NONE)
		{
			//ui.m_pRButtonALL->setChecked(false);
			//ui.m_pRButtonPlug->setChecked(true);
			ui.m_pCmbButtonPlug->setCurrentIndex(STT_BINRECORD_ID_NONE);
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_CUSTOMIZETIME);
	if (pDvmData != NULL)
	{
		ui.m_pEditCustomize->setText(QString::number(CString_To_double(pDvmData->m_strValue), 'f', 2) + pDvmData->m_strUnit);
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_DEFAULTSAVEPATH);
	if (pDvmData != NULL)
	{
		ui.m_pEditPath->setText(pDvmData->m_strValue);
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERHOUR);
	if (pDvmData != NULL)
	{
		ui.m_pEditHour->setText(QString::number(CString_To_long(pDvmData->m_strValue)));
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERMINUTE);
	if (pDvmData != NULL)
	{
		ui.m_pEditminute->setText(QString::number(CString_To_long(pDvmData->m_strValue)));
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERSECOND);
	if (pDvmData != NULL)
	{
		ui.m_pEditsecond->setText(QString::number(CString_To_long(pDvmData->m_strValue)));
	}
}

void QSttBinRecordSetDlg::InitConnect()
{
	connect(ui.m_pBtnChannelUp, SIGNAL(clicked()), this, SLOT(slot_BinRecordChannelUp()));
	connect(ui.m_pBtnChannelDown, SIGNAL(clicked()), this, SLOT(slot_BinRecordChannelDown()));
	connect(ui.m_pBtnTop, SIGNAL(clicked()), this, SLOT(slot_BinRecordTop()));
	connect(ui.m_pBtnBottom, SIGNAL(clicked()), this, SLOT(slot_BinRecordBottom()));
	connect(ui.m_pBtnDefault, SIGNAL(clicked()), this, SLOT(slot_BinRecordDefault()));
	connect(ui.m_pBtnBrowse, SIGNAL(clicked()), this, SLOT(slot_BinRecordBrowse()));
	connect(ui.m_pBtnOK, SIGNAL(clicked()), this, SLOT(slot_BinRecordOK()));
	connect(ui.m_pBtnCancel, SIGNAL(clicked()), this, SLOT(slot_BinRecordCancel()));

	connect(ui.m_pRButtonAll, SIGNAL(toggled(bool)), this, SLOT(slot_BinRecordTime(bool)));
	connect(ui.m_pRButtonALL, SIGNAL(toggled(bool)), this, SLOT(slot_BinRecordDisplay(bool)));
	connect(ui.m_pRButtonFlip, SIGNAL(toggled(bool)), this, SLOT(slot_BinRecordTrigger(bool)));
	connect(ui.m_pRButtonRis, SIGNAL(toggled(bool)), this, SLOT(slot_BinRecordTrigger(bool)));
	connect(ui.m_pRButtonFall, SIGNAL(toggled(bool)), this, SLOT(slot_BinRecordTrigger(bool)));
	connect(ui.m_pRButtonGPS, SIGNAL(toggled(bool)), this, SLOT(slot_BinRecordTrigger(bool)));
	connect(ui.m_pBtnALL, SIGNAL(clicked()), this, SLOT(slot_BtnArrange()));

	connect(ui.m_pEditCustomize, SIGNAL(editingFinished()), this, SLOT(slot_EditBinCustomize()));
	connect(ui.m_pEditHour, SIGNAL(editingFinished()), this, SLOT(slot_EditBinHour()));
	connect(ui.m_pEditminute, SIGNAL(editingFinished()), this, SLOT(slot_EditBinminute()));
	connect(ui.m_pEditsecond, SIGNAL(editingFinished()), this, SLOT(slot_EditBinsecond()));
}

void QSttBinRecordSetDlg::InitComboBox(CCapDeviceMngr *pCapDeviceAll)
{
	long nValue = pCapDeviceAll->GetCount();
	QStringList strText;
	for (int i = STT_BINRECORD_ID_NZERO; i < nValue; i++)
	{
		CCapDeviceRecord *pCapDevice = (CCapDeviceRecord *)pCapDeviceAll->GetAtIndex(i);
		strText << pCapDevice->m_strName;
	}
	ui.m_pCmbButtonPlug->addItems(strText);
	ui.m_pCmbButtonPlug->setCurrentIndex(STT_BINRECORD_ID_NZERO);
}

void QSttBinRecordSetDlg::SaveDataToCfg()
{
	CDvmData *pDvmData;
	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTIMETYPE);
	if (pDvmData != NULL)
	{
		if (ui.m_pRButtonAll->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRZERO;
		}
		else if (ui.m_pRButtronCustomize->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRONE;
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_CUSTOMIZETIME);
	if (pDvmData != NULL)
	{
		float fValue = CString_To_long(ui.m_pEditCustomize->text());
		pDvmData->m_strValue.Format("%.2f", fValue);
		pDvmData->m_strUnit = "s";
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_BINRECORDTYPE);
	if (pDvmData != NULL)
	{
		if (ui.m_pRButtonALL->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRZERO;
		}
		else if (ui.m_pRButtonPlug->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRONE;
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDALL);
	if (pDvmData != NULL)
	{
		CString strText = /*"排列在最前"*/g_sLangTxt_BinRecord_ArrangeTop;
		CString strText1 = /*"排列在最后"*/g_sLangTxt_BinRecord_ArrangeLast;
		CString strText2 = ui.m_pBtnALL->text();
		if (strText2 == strText)
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRONE;
		}
		else if (strText2 == strText1)
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRZERO;
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDPLUG);
	if (pDvmData != NULL)
	{
		long nValue = ui.m_pCmbButtonPlug->currentIndex();
		pDvmData->m_strValue.Format("%d", nValue);
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_DISPLAYTYPE);
	if (pDvmData != NULL)
	{
		if (ui.m_pRButtonOne->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRZERO;
		}
		else if (ui.m_pRButtonTwo->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRONE;
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_DEFAULTSAVEPATH);
	if (pDvmData != NULL)
	{
		CString strPath = ui.m_pEditPath->text();
		pDvmData->m_strValue = strPath;
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERTYPE);
	if (pDvmData != NULL)
	{
		if (ui.m_pRButtonFlip->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRZERO;
		}
		else if (ui.m_pRButtonRis->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRONE;
		}
		else if (ui.m_pRButtonFall->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRTWO;
		}
		else if (ui.m_pRButtonGPS->isChecked())
		{
			pDvmData->m_strValue = STT_BINRECORD_ID_STRTHREE;
		}
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERHOUR);
	if (pDvmData != NULL)
	{
		long nValue = CString_To_long(ui.m_pEditHour->text());
		pDvmData->m_strValue.Format("%d", nValue);
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERMINUTE);
	if (pDvmData != NULL)
	{
		
		long nValue = CString_To_long(ui.m_pEditminute->text());
		pDvmData->m_strValue.Format("%d", nValue);
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERSECOND);
	if (pDvmData != NULL)
	{
		
		long nValue = CString_To_long(ui.m_pEditsecond->text());
		pDvmData->m_strValue.Format("%d", nValue);
	}

	CString strFile = _P_GetConfigPath();
	strFile += _T("BinRecordConfig.xml");
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_pBinRecordSetGroup->SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
}

void QSttBinRecordSetDlg::BinRecordSort(CDvmData *pRecordAllData)//开关量通道排序   排列最前/排列最后
{
	CDataGroup *pChannelInformationGroup, *pBinPrevGroup, *pBinNextGroup, *pBinRecordTypeData;
	long nBinValue;
	pChannelInformationGroup = (CDataGroup *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);
	pBinRecordTypeData = (CDataGroup *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_BINRECORDTYPE);
	long nChannelCount = pChannelInformationGroup->GetCount();
	CDataGroup *pSortGroup = new CDataGroup;
	if (CString_To_long(pBinRecordTypeData->m_strValue) == STT_BINRECORD_ID_NZERO && CString_To_long(pRecordAllData->m_strValue) == STT_BINRECORD_ID_NONE)
	{
		POS pos = pChannelInformationGroup->GetTailPosition();
		for (int i = STT_BINRECORD_ID_NZERO; i < nChannelCount; i++)
		{
			pBinPrevGroup = (CDataGroup *)pChannelInformationGroup->GetPrev(pos);

			if (pBinPrevGroup->m_strValue == STT_BINRECORD_ID_STRONE)
			{
				CDvmData *pBinData = (CDvmData *)pBinPrevGroup->FindByID(STT_BINRECORD_ID_RECORDTYPE);
				if (pBinData != NULL)
				{
					nBinValue = CString_To_long(pBinData->m_strValue);
					if (nBinValue == STT_BINRECORD_ID_NTHREE || nBinValue == STT_BINRECORD_ID_NFOUR)
					{
						pChannelInformationGroup->BringToHead(pBinPrevGroup);
					}
				}
			}
		}
		m_pSttBinRecordSetGrid->ShowDatas(pChannelInformationGroup);      //排列最前
	}
	

	if (CString_To_long(pBinRecordTypeData->m_strValue) == STT_BINRECORD_ID_NZERO && CString_To_long(pRecordAllData->m_strValue) == STT_BINRECORD_ID_NZERO)
	{
		POS pos = pChannelInformationGroup->GetHeadPosition();

		for (int i = STT_BINRECORD_ID_NZERO; i < nChannelCount; i++)
		{
			pBinNextGroup = (CDataGroup *)pChannelInformationGroup->GetNext(pos);
			if (pBinNextGroup->m_strValue == STT_BINRECORD_ID_STRONE)
			{
				CDvmData *pBinData = (CDvmData *)pBinNextGroup->FindByID(STT_BINRECORD_ID_RECORDTYPE);
				if (pBinData != NULL)
				{
					nBinValue = CString_To_long(pBinData->m_strValue);
					if (nBinValue == STT_BINRECORD_ID_NTHREE || nBinValue == STT_BINRECORD_ID_NFOUR)
					{
						pChannelInformationGroup->BringToTail(pBinNextGroup);
					}
				}
			}
		}
		m_pSttBinRecordSetGrid->ShowDatas(pChannelInformationGroup);  //排列最后
	}

	if (CString_To_long(pBinRecordTypeData->m_strValue) == STT_BINRECORD_ID_NONE && CString_To_long(pRecordAllData->m_strValue) == STT_BINRECORD_ID_NZERO)
	{
		POS pos = pChannelInformationGroup->GetHeadPosition();
		CString strText = ui.m_pCmbButtonPlug->currentText();
		for (int i = STT_BINRECORD_ID_NZERO; i < nChannelCount; i++)
		{
			pBinNextGroup = (CDataGroup *)pChannelInformationGroup->GetNext(pos);
			if (pBinNextGroup->m_strValue == STT_BINRECORD_ID_STRONE)
			{
				CDvmData *pModuleData = (CDvmData *)pBinNextGroup->FindByID(STT_BINRECORD_ID_MODULE);
				if (pModuleData->m_strName == strText)
				{
					pModuleData = (CDvmData *)pBinNextGroup->FindByID(STT_BINRECORD_ID_RECORDTYPE);
					if (pModuleData != NULL)
					{
						nBinValue = CString_To_long(pModuleData->m_strValue);
						if (nBinValue == STT_BINRECORD_ID_NTHREE || nBinValue == STT_BINRECORD_ID_NFOUR)
						{
							pChannelInformationGroup->BringToTail(pBinNextGroup);
						}
					}
				}
			}
		}
		m_pSttBinRecordSetGrid->ShowDatas(pChannelInformationGroup);  //按插件 - 排列最后
	}

	if (CString_To_long(pBinRecordTypeData->m_strValue) == STT_BINRECORD_ID_NONE && CString_To_long(pRecordAllData->m_strValue) == STT_BINRECORD_ID_NONE)
	{
		POS pos = pChannelInformationGroup->GetTailPosition();
		CString strText = ui.m_pCmbButtonPlug->currentText();
		for (int i = STT_BINRECORD_ID_NZERO; i < nChannelCount; i++)
		{
			pBinPrevGroup = (CDataGroup *)pChannelInformationGroup->GetPrev(pos);
			if (pBinPrevGroup->m_strValue == STT_BINRECORD_ID_STRONE)
			{
				CDvmData *pModuleData = (CDvmData *)pBinPrevGroup->FindByID(STT_BINRECORD_ID_MODULE);
				if (pModuleData->m_strName == strText)
				{
					pModuleData = (CDvmData *)pBinPrevGroup->FindByID(STT_BINRECORD_ID_RECORDTYPE);
					if (pModuleData != NULL)
					{
						nBinValue = CString_To_long(pModuleData->m_strValue);
						if (nBinValue == STT_BINRECORD_ID_NTHREE || nBinValue == STT_BINRECORD_ID_NFOUR)
						{
							pChannelInformationGroup->BringToHead(pBinPrevGroup);
						}
					}
				}
			}
		}
		m_pSttBinRecordSetGrid->ShowDatas(pChannelInformationGroup);//按插件 - 排列最前
	}
}

void QSttBinRecordSetDlg::slot_BinRecordChannelUp()
{ 
	m_pSttBinRecordSetGrid->MoveUp();
}

void QSttBinRecordSetDlg::slot_BinRecordChannelDown()
{
	m_pSttBinRecordSetGrid->MoveDown();
}

void QSttBinRecordSetDlg::slot_BinRecordTop()
{
	m_pSttBinRecordSetGrid->MoveToTop();
}

void QSttBinRecordSetDlg::slot_BinRecordBottom()
{
	m_pSttBinRecordSetGrid->MoveToBottom();
}

void QSttBinRecordSetDlg::slot_BinRecordDefault()
{
	m_pSttBinRecordSetGrid->InitData();
}

void QSttBinRecordSetDlg::slot_BinRecordBrowse()
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
	QString directory = QFileDialog::getExistingDirectory(this, g_sLangTxt_SelFolder,
		QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#else
	QString directory = QFileDialog::getExistingDirectory(this, g_sLangTxt_SelFolder,
		QDesktopServices::storageLocation(QDesktopServices::DesktopLocation),
		QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
#endif

	if (!directory.isEmpty()) 
	{
		ui.m_pEditPath->setText(directory);
	}
}

void QSttBinRecordSetDlg::slot_BinRecordOK()
{
	CDvmData *pDvmData;
	CString strValue;
	long nState;
	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTIMETYPE);
	if (pDvmData != NULL)
	{
		nState = ui.m_pRButtonAll->isChecked();
		strValue.Format("%d", nState);
		pDvmData->m_strValue = strValue;
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_BINRECORDTYPE);
	if (pDvmData != NULL)
	{
		nState = ui.m_pRButtonALL->isChecked();
		strValue.Format("%d", nState);
		pDvmData->m_strValue = strValue;
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_DISPLAYTYPE);
	if (pDvmData != NULL)
	{
		nState = ui.m_pRButtonTwo->isChecked();
		strValue.Format("%d", nState);
		pDvmData->m_strValue = strValue;
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDTRIGGERTYPE);
	if (pDvmData != NULL)
	{
		nState = ui.m_pRButtonFlip->isChecked();
		strValue.Format("%d", nState);
		pDvmData->m_strValue = strValue;
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDPLUG);
	if (pDvmData != NULL)
	{
		nState = ui.m_pCmbButtonPlug->currentIndex();
		strValue.Format("%d", nState);
		pDvmData->m_strValue = strValue;
	}

	pDvmData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDALL);
	if (pDvmData != NULL)
	{
		if (CString_To_long(pDvmData->m_strValue) == STT_BINRECORD_ID_NONE)
		{
			pDvmData->m_strValue == STT_BINRECORD_ID_STRONE;
		}
		else
		{
			pDvmData->m_strValue == STT_BINRECORD_ID_STRZERO;
		}
	}

	this->done(Accepted);
}

void QSttBinRecordSetDlg::slot_BinRecordCancel()
{
	this->close();
}

void QSttBinRecordSetDlg::slot_BtnArrange()
{
	
	CDvmData *pRecordAllData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_RECORDALL);
	BinRecordSort(pRecordAllData);
	if (pRecordAllData == NULL)
	{
		return;
	}
	CString strText = /*"排列在最前"*/g_sLangTxt_BinRecord_ArrangeTop;
	CString strText1 = /*"排列在最后"*/g_sLangTxt_BinRecord_ArrangeLast;
	CString strValue = ui.m_pBtnALL->text();
	if (CString_To_long(pRecordAllData->m_strValue) == STT_BINRECORD_ID_NONE)
	{
		pRecordAllData->m_strValue = STT_BINRECORD_ID_STRZERO;
		ui.m_pBtnALL->setText(strText1);
	}
	else
	{
		pRecordAllData->m_strValue = STT_BINRECORD_ID_STRONE;
		ui.m_pBtnALL->setText(strText);
	}

}

void QSttBinRecordSetDlg::slot_BinRecordTime(bool bState)
{
	
	if (bState)
	{
		ui.m_pRButtonAll->setChecked(true);
		ui.m_pRButtronCustomize->setChecked(false);
		ui.m_pEditCustomize->setEnabled(false);
		
	}
	else
	{
		ui.m_pRButtonAll->setChecked(false);
		ui.m_pRButtronCustomize->setChecked(true);
		ui.m_pEditCustomize->setEnabled(true);
	
	}
}

void QSttBinRecordSetDlg::slot_BinRecordDisplay(bool bState)
{
	CDvmData *pRecordAllData = (CDvmData *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_BINRECORDTYPE);
	if (bState)
	{
		ui.m_pRButtonALL->setChecked(true);
		ui.m_pRButtonPlug->setChecked(false);
		ui.m_pCmbButtonPlug->setEnabled(false);
		pRecordAllData->m_strValue = STT_BINRECORD_ID_STRZERO;
	}
	else
	{
		ui.m_pRButtonALL->setChecked(false);
		ui.m_pRButtonPlug->setChecked(true);
		ui.m_pCmbButtonPlug->setEnabled(true);
		pRecordAllData->m_strValue = STT_BINRECORD_ID_STRONE;
	}
}

void QSttBinRecordSetDlg::slot_BinRecordTrigger(bool bState)
{
	if (ui.m_pRButtonFlip->isChecked()) 
	{
		ui.m_pRButtonRis->setChecked(false);
		ui.m_pRButtonFall->setChecked(false);
		ui.m_pRButtonGPS->setChecked(false);

		ui.m_pEditHour->setEnabled(false);
		ui.m_pEditminute->setEnabled(false);
		ui.m_pEditsecond->setEnabled(false);
	}
	else if (ui.m_pRButtonRis->isChecked()) 
	{
		ui.m_pRButtonFlip->setChecked(false);
		ui.m_pRButtonFall->setChecked(false);
		ui.m_pRButtonGPS->setChecked(false);

		ui.m_pEditHour->setEnabled(false);
		ui.m_pEditminute->setEnabled(false);
		ui.m_pEditsecond->setEnabled(false);
	}
	else if (ui.m_pRButtonFall->isChecked()) 
	{
		ui.m_pRButtonFlip->setChecked(false);
		ui.m_pRButtonRis->setChecked(false);
		ui.m_pRButtonGPS->setChecked(false);

		ui.m_pEditHour->setEnabled(false);
		ui.m_pEditminute->setEnabled(false);
		ui.m_pEditsecond->setEnabled(false);
	}
	else if (ui.m_pRButtonGPS->isChecked())
	{
		ui.m_pRButtonFlip->setChecked(false);
		ui.m_pRButtonRis->setChecked(false);
		ui.m_pRButtonFall->setChecked(false);

		ui.m_pEditHour->setEnabled(true);
		ui.m_pEditminute->setEnabled(true);
		ui.m_pEditsecond->setEnabled(true);
	}
}

void QSttBinRecordSetDlg::slot_BtnEnable(int nValue)
{
	if (nValue == STT_BINRECORD_ID_NZERO)
	{
		ui.m_pBtnChannelUp->setEnabled(false);
		ui.m_pBtnTop->setEnabled(false);
	}
	else
	{
		ui.m_pBtnChannelUp->setEnabled(true);
		ui.m_pBtnTop->setEnabled(true);
	}
	CDataGroup *pDataGroup = (CDataGroup *)m_pBinRecordSetGroup->FindByID(STT_BINRECORD_ID_CHANNELINFORMATION);
	long nGroupNum = pDataGroup->GetCount();
	if (nValue == nGroupNum - STT_BINRECORD_ID_NONE)
	{
		ui.m_pBtnChannelDown->setEnabled(false);
		ui.m_pBtnBottom->setEnabled(false);
	}
	else
	{
		ui.m_pBtnChannelDown->setEnabled(true);
		ui.m_pBtnBottom->setEnabled(true);
	}
}

void QSttBinRecordSetDlg::slot_EditBinCustomize()
{
	ui.m_pEditCustomize->InitCoverage_EditFinished(0.01, 99999, 2);
	ui.m_pEditCustomize->InitUnit("s");
}

void QSttBinRecordSetDlg::slot_EditBinHour()
{
	ui.m_pEditHour->InitCoverage(0, 99999);
}

void QSttBinRecordSetDlg::slot_EditBinminute()
{
	ui.m_pEditminute->InitCoverage(0, 99999);
}

void QSttBinRecordSetDlg::slot_EditBinsecond()
{
	ui.m_pEditsecond->InitCoverage(0, 99999);
}


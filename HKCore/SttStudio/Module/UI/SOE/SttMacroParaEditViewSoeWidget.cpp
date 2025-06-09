#include "SttMacroParaEditViewSoeWidget.h"
#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../Module/CommonMethod/commonMethod.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../../../../Module/OSInterface/QT/XMessageBox.h"

QSttMacroParaEditViewSoeWidget* g_pSoeTest = NULL;

QSttMacroParaEditViewSoeWidget::QSttMacroParaEditViewSoeWidget(QWidget *parent)
{
	setWindowFlags(Qt::FramelessWindowHint);

	debug_time_long_log("SoeWidget setWindowFlags", true);
	g_pTheSttTestApp->IinitGbWzdAiTool();
	debug_time_long_log("SoeWidget IinitGbWzdAiTool", true);
	m_bTmtParaChanged = FALSE;
	m_pPulseWidth_Edit = NULL;
	m_pPulseWidth_Label= NULL;
	m_pSOE_Edit = NULL;
	m_pSOE_Label = NULL;
	m_pTestCount_Edit = NULL;
	m_pTestCount_Label = NULL;
	m_pLoopTestCheckBox = NULL;
	m_pInterSelect = NULL;
	m_pInterSelect_ComboBox = NULL;
	m_pSoeFirstGrid = NULL;
	m_pSoeSecondGrid = NULL;
	m_pBtnClearEventRecords = NULL;
	g_pSoeTest = this;
	m_strParaFileTitle = g_sLangTxt_SOE_TemplateFile;
	m_strParaFilePostfix = "project(*.mntxml)";
	m_strDefaultParaFile = _P_GetConfigPath();
	m_strDefaultParaFile.append("SoeTest.mntxml");
// 	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
// 	g_theTestCntrFrame->InitTestResource();//
	m_pSoeParas = &m_oSoeTest.m_oSoeParas;
	OpenTestTestMngrFile(m_strDefaultParaFile);
	debug_time_long_log("SoeWidget OpenTestTestMngrFile", true);

	InitUI();
	debug_time_long_log("SoeWidget InitUI", true);
	SetFont();
	debug_time_long_log("SoeWidget SetFont", true);
	InitConnections();
	debug_time_long_log("SoeWidget InitConnections", true);
	SetDatas(NULL);
	debug_time_long_log("SoeWidget SetDatas", true);
	InitData();
	debug_time_long_log("SoeWidget InitData", true);
}

QSttMacroParaEditViewSoeWidget::~QSttMacroParaEditViewSoeWidget()
{
	DeleteIntervalListDatas();
}

void QSttMacroParaEditViewSoeWidget::InitUI()
{
	CString strTemp;
	strTemp = _T("脉冲宽度(ms):");
	m_pPulseWidth_Edit = new QSttLineEdit();
	m_pPulseWidth_Label= new QLabel();
	m_pPulseWidth_Label->setText(strTemp);
	strTemp = _T("SOE分辨率(ms):");
	m_pSOE_Edit = new QSttLineEdit();
	m_pSOE_Label=  new QLabel();
	m_pSOE_Label->setText(strTemp);

	m_pTestCount_Edit = new QSttLineEdit;	
	m_pTestCount_Label = new QLabel;
	strTemp = _T("测试次数(次):");
	m_pTestCount_Label->setText(strTemp);
	m_pLoopTestCheckBox = new QSttCheckBox;
	strTemp = _T("闭环测试");
	m_pLoopTestCheckBox->setText(strTemp);

	strTemp = _T("间隔选择:");
	m_pInterSelect = new QLabel(this);
	m_pInterSelect->setText(strTemp);
	m_pInterSelect_ComboBox = new CExBaseListComboBox(this);
	//m_pInterSelect_ComboBox->setFixedWidth(120);

	strTemp = _T("清空事件记录");
	m_pBtnClearEventRecords  = new QPushButton(this);
	m_pBtnClearEventRecords->setText(strTemp);

	QHBoxLayout *pHFirstLineLayout = new QHBoxLayout;
	pHFirstLineLayout->addWidget(m_pPulseWidth_Label);
	pHFirstLineLayout->addWidget(m_pPulseWidth_Edit);
	pHFirstLineLayout->addWidget(m_pSOE_Label);
	pHFirstLineLayout->addWidget(m_pSOE_Edit);
	pHFirstLineLayout->addWidget(m_pTestCount_Label);
	pHFirstLineLayout->addWidget(m_pTestCount_Edit);
	pHFirstLineLayout->addWidget(m_pInterSelect);
	pHFirstLineLayout->addWidget(m_pInterSelect_ComboBox);
	pHFirstLineLayout->addWidget(m_pLoopTestCheckBox);
	pHFirstLineLayout->addWidget(m_pBtnClearEventRecords);


	m_pSoeFirstGrid = new QSttMacroParaEditViewSoeTable(SOE_TABLE_First);
	m_pSoeSecondGrid = new QSttMacroParaEditViewSoeTable(SOE_TABLE_Second);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addLayout(pHFirstLineLayout);
	pMainLayout->addWidget(m_pSoeFirstGrid);
	pMainLayout->addWidget(m_pSoeSecondGrid);
	setLayout(pMainLayout);	
}

void QSttMacroParaEditViewSoeWidget::SetFont()
{
	m_pPulseWidth_Edit->setFont(*g_pSttGlobalFont);
	m_pPulseWidth_Label->setFont(*g_pSttGlobalFont);
	m_pSOE_Label->setFont(*g_pSttGlobalFont);
	m_pSOE_Edit->setFont(*g_pSttGlobalFont);        
	m_pTestCount_Edit->setFont(*g_pSttGlobalFont);	 
	m_pTestCount_Label->setFont(*g_pSttGlobalFont);  
	m_pLoopTestCheckBox->setFont(*g_pSttGlobalFont);
	m_pInterSelect->setFont(*g_pSttGlobalFont);
	m_pInterSelect_ComboBox->setFont(*g_pSttGlobalFont);   
	m_pBtnClearEventRecords->setFont(*g_pSttGlobalFont);
	m_pSoeFirstGrid->setFont(*g_pSttGlobalFont);   
	m_pSoeSecondGrid->setFont(*g_pSttGlobalFont);
	m_pSoeFirstGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);   
	m_pSoeSecondGrid->horizontalHeader()->setFont(*g_pSttGlobalFont);
}


void QSttMacroParaEditViewSoeWidget::InitConnections()
{
	connect(m_pPulseWidth_Edit,SIGNAL(editingFinished()),this,SLOT(slot_EditPulseWidth()));
	connect(m_pSOE_Edit,SIGNAL(editingFinished()),this,SLOT(slot_EditSOEResolution()));
	connect(m_pTestCount_Edit,SIGNAL(editingFinished()),this,SLOT(slot_EditTestCount()));
	connect(m_pLoopTestCheckBox, SIGNAL(clicked(bool)), this, SLOT(slot_Check_LoopTest(bool)));
	connect(m_pInterSelect_ComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_InterSelectIndexChanged(int)));
	connect(m_pBtnClearEventRecords, SIGNAL(clicked()), this, SLOT(slot_btn_ClearClearEventRecordsClicked()));	
}

void QSttMacroParaEditViewSoeWidget::GetDatas( CDataGroup *pParas )
{	
	GetAtsCmdDataParas(pParas);
}

void QSttMacroParaEditViewSoeWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		CSttDataGroupSerializeRead oRead(pParas);
		stt_xml_serialize(m_pSoeParas, &oRead);
	}

	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewSoeWidget::OnViewTestStart()
{
	m_pPulseWidth_Edit->setDisabled(true);
	m_pPulseWidth_Label->setDisabled(true);
	m_pSOE_Edit->setDisabled(true);
	m_pSOE_Label->setDisabled(true);
	m_pTestCount_Edit->setDisabled(true);
	m_pTestCount_Label->setDisabled(true);
	m_pLoopTestCheckBox->setDisabled(true);
	m_pSoeFirstGrid->setDisabled(true);
	//m_pSoeSecondGrid->setDisabled(true);
	m_pInterSelect_ComboBox->setDisabled(true);

	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
	g_theTestCntrFrame->EnableManualTriggerButton(false);
	GetSelectObject();
}

void QSttMacroParaEditViewSoeWidget::OnViewTestStop()
{
	m_pPulseWidth_Edit->setDisabled(false);
	m_pPulseWidth_Label->setDisabled(false);
	m_pSOE_Edit->setDisabled(false);
	m_pSOE_Label->setDisabled(false);
	m_pTestCount_Edit->setDisabled(false);
	m_pTestCount_Label->setDisabled(false);
	m_pLoopTestCheckBox->setDisabled(false);
	m_pInterSelect_ComboBox->setDisabled(false);
	m_pSoeFirstGrid->setDisabled(false);
	//m_pSoeSecondGrid->setDisabled(false);

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget(false);
	g_theTestCntrFrame->StopPowerWidget(false);
}

void QSttMacroParaEditViewSoeWidget::slot_EditPulseWidth()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}
	float fTime = m_pPulseWidth_Edit->text().toFloat();

	fTime = setLimit(10,1000,fTime);

	for (int i=0; i<g_nBinCount; i++)
	{
		QTableWidgetItem *pItem = m_pSoeFirstGrid->item(i,STT_SOE_FirstTABLE_COL_Select);
		if (pItem == NULL)
		{
			return;
		}

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[i].otmt_SoeState[1].time = fTime;
			m_pSoeFirstGrid->item(i,STT_SOE_FirstTABLE_COL_ClosedTime)->setText(QString::number(fTime,'f', 0));
		}
	}

	m_pPulseWidth_Edit->setText(QString::number(fTime,'f', 0));
}

void QSttMacroParaEditViewSoeWidget::slot_EditSOEResolution()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}
	float fSoeTime = m_pSOE_Edit->text().toFloat();
	
	fSoeTime = setLimit(1,10,fSoeTime);

	int nTime = 20,nIndex = 0;

	for (int i = 0; i<g_nBinCount; i++)
	{
		QTableWidgetItem *pItem = m_pSoeFirstGrid->item(i,STT_SOE_FirstTABLE_COL_Select);
		if (pItem == NULL)
		{
			return;
		}

		if (pItem->checkState() !=  Qt::Unchecked)
		{
			m_pSoeParas->m_binOut[i].otmt_SoeState[0].time = nTime + fSoeTime*nIndex; //变位前时长
			nIndex++;
		}
	}

	m_pSoeParas->m_nSoeResolution = fSoeTime;
	m_pSOE_Edit->setText(QString::number(fSoeTime,'f', 0));
}

void QSttMacroParaEditViewSoeWidget::slot_EditTestCount()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}
	int nTestCount = m_pTestCount_Edit->text().toInt();

	if (nTestCount < 1)
	{
		nTestCount = 1;
	}
	if (nTestCount > 5)
	{
		nTestCount = 5;
	}
	m_pSoeParas->m_nTestCount = nTestCount;
	
	m_pTestCount_Edit->setText(QString::number(nTestCount));
}

void QSttMacroParaEditViewSoeWidget::slot_Check_LoopTest( bool checked )
{
	if (checked)
	{	
		m_pInterSelect->show();
		m_pInterSelect_ComboBox->show();
		m_pBtnClearEventRecords->show();
		m_pSoeSecondGrid->show();
		m_pSoeFirstGrid->setColumnHidden(STT_SOE_FirstTABLE_COL_Object, false);
		m_pSoeParas->m_nLoopTest = 1;
	}
	else
	{
		m_pInterSelect->hide();
		m_pInterSelect_ComboBox->hide();
		m_pBtnClearEventRecords->hide();
		m_pSoeSecondGrid->hide();
		m_pSoeFirstGrid->setColumnHidden(STT_SOE_FirstTABLE_COL_Object, true);	
		m_pSoeParas->m_nLoopTest = 0;
	}
}

CSttTestResourceBase* QSttMacroParaEditViewSoeWidget::CreateTestResource()
{
	m_pOriginalSttTestResource = g_theTestCntrFrame->GetSttTestResource();
	return m_pOriginalSttTestResource;
}

void QSttMacroParaEditViewSoeWidget::SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
												  long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)
{
	tmt_SoeTest *pSoeTest = (tmt_SoeTest *)pParas;
	stt_xml_serialize(&pSoeTest->m_oSoeParas, pMacroParas);
}

void QSttMacroParaEditViewSoeWidget::ClearResult(PTMT_PARAS_HEAD pHead)
{
	m_oSoeTest.m_oSoeResult.init();
}

void QSttMacroParaEditViewSoeWidget::OnTestResults(CDataGroup *pResults)
{
	ASSERT(pResults != NULL);

	m_oSoeTest.m_nTestState = 1;	//测试完成
}

CString QSttMacroParaEditViewSoeWidget::GetDefaultParaFile()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += STT_ORG_MACRO_SoeTest;
	strFile += _T(".");
	strFile += "mntxml";

	return strFile;
}

void QSttMacroParaEditViewSoeWidget::InitData()
{
	if (m_pSoeParas == NULL)
	{
		return;
	}
	m_pPulseWidth_Edit->setText(QString::number(m_pSoeParas->m_binOut[0].otmt_SoeState[1].time));
	m_pSOE_Edit->setText(QString::number(m_pSoeParas->m_nSoeResolution));
	m_pTestCount_Edit->setText(QString::number(m_pSoeParas->m_nTestCount));
	m_pLoopTestCheckBox->setChecked(m_pSoeParas->m_nLoopTest);
	InitIntervalListDatas();
	m_pSoeFirstGrid->InitData(m_pSoeParas);
	m_pSoeFirstGrid->UpdateSelTestObject();


	if(m_pSoeParas->m_nLoopTest != 1)
	{
		m_pInterSelect->hide();
		m_pInterSelect_ComboBox->hide();
		m_pSoeSecondGrid->hide();
		m_pSoeFirstGrid->setColumnHidden(STT_SOE_FirstTABLE_COL_Object, true);
		m_pBtnClearEventRecords->hide();
	}
}

void QSttMacroParaEditViewSoeWidget::DeleteIntervalListDatas()
{
	CExBaseList *pChildList = NULL;
	POS pos = m_IntervalList.GetHeadPosition();

	while(pos)
	{
		pChildList = (CExBaseList *)m_IntervalList.GetNext(pos);
		pChildList->RemoveAll();
	}

	m_IntervalList.DeleteAll();
}

void QSttMacroParaEditViewSoeWidget::GetSelectObject()
{
	if (m_pSoeFirstGrid == NULL)
	{
		return;
	}
	m_SelectTestObjetcList.clear();
	for (int i=0; i<g_nBinCount; i++)
	{
		if (m_pSoeFirstGrid->m_pSoeParas->m_binOut[i].isValid == 1)
		{
			CString strValue = m_pSoeFirstGrid->m_pSoeParas->m_binOut[i].m_strTestObject;
			m_SelectTestObjetcList.append(strValue);
		}
	}
}

void QSttMacroParaEditViewSoeWidget::InitIntervalListDatas()
{
	DeleteIntervalListDatas();

	CDvmDevice* pDvmDevice = g_pTheSttTestApp->m_pDvmDevice;

	if (pDvmDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDvmDatasetRef = NULL,*pCurrDataset = NULL;
	CDvmData *pDvmDataRef = NULL,*pCurrDvmData = NULL;

	POS pos = pDvmDevice->GetHeadPosition();
	CExBaseList *pCurObj = NULL;
	while(pos)
	{
		pCurObj = (CExBaseList*)pDvmDevice->GetNext(pos);	

		if (pCurObj->GetClassID() != DVMCLASSID_CDVMLOGICDEVICE)
		{
			continue;
		}

		if (pCurObj->m_strID == _T("report") || pCurObj->m_strID == _T("CommMessage"))
		{
			continue;
		}

		pDvmDatasetRef = new CDvmDataset;
		m_IntervalList.AddNewChild(pDvmDatasetRef);
		pDvmDatasetRef->m_strName = pCurObj->m_strName;
		pDvmDatasetRef->m_strID = pCurObj->m_strID;

		POS pos_dataset = pCurObj->GetHeadPosition();

		while(pos_dataset)
		{
			pCurrDataset = (CDvmDataset *)pCurObj->GetNext(pos_dataset);

			if (pCurrDataset->m_strID/*.Find(g_strPxDataSetIDKey[PX_DSID_dsDin]) >= 0*/ == _T("dsDin"))
			{
				//pDvmDatasetRef->Append(*pCurrDataset);
				pDvmDatasetRef->m_strDataType.Format("%s$%s",pCurObj->m_strID.GetString(),pCurrDataset->m_strID.GetString());
				
			 	POS pos_data = pCurrDataset->GetHeadPosition();
			 	while(pos_data)
			 	{
			 		pCurrDvmData = (CDvmData *)pCurrDataset->GetNext(pos_data);
			 		if (pCurrDvmData->m_strID == _T("Din_1") || pCurrDvmData->m_strID == _T("Din_2") || pCurrDvmData->m_strID == _T("Din_5"))
			 		{
						pDvmDatasetRef->AddNewChild(pCurrDvmData);
			 		}
			 	}
				}
			}
		}
	m_pInterSelect_ComboBox->ShowBaseList(&m_IntervalList);

	CDvmDataset *pInterDataset = (CDvmDataset*)m_pInterSelect_ComboBox->GetCurrSelObject();
	if (pInterDataset)
	{
		CString_to_char(pInterDataset->m_strDataType,m_pSoeParas->m_strDataset_path);
	}

}

void QSttMacroParaEditViewSoeWidget::OpenXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("TestCtrlCommConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;


	CDvmData *pPpDvmData = (CDvmData*)oDataGroup.FindByID(_T("ppxml-file"));
	if (pPpDvmData)
	{
		g_pTheSttTestApp->m_oCommConfig.Set_PpXmlFile(pPpDvmData->m_strValue);
	}
	CDvmData *pDvmData = (CDvmData*)oDataGroup.FindByID(_T("dvm-file"));
	if (pDvmData)
	{
		g_pTheSttTestApp->m_oCommConfig.Set_DvmFile(pDvmData->m_strValue);
	}
}

void QSttMacroParaEditViewSoeWidget::UpdateDeviceModelRef()
{
	g_pTheSttTestApp->m_pDvmDevice = g_theTestCntrFrame->m_pEngineClientWidget->m_pDvmDevice;

	InitIntervalListDatas();

	if (m_pSoeFirstGrid == NULL)
	{
		return;
	}
	for (int i=0; i<g_nBinCount; i++)
	{
		m_pSoeFirstGrid->UpdateDeviceData(i,STT_SOE_FirstTABLE_COL_Object,m_pSoeFirstGrid->item(i, STT_SOE_FirstTABLE_COL_Object));
	}

	m_pSoeFirstGrid->UpdateTestObjet(&m_IntervalList);

	OpenXml();
}


void QSttMacroParaEditViewSoeWidget::slot_InterSelectIndexChanged( int nIndex )
{
	if (nIndex < 0)
	{
		return;
	}
	if (m_pSoeFirstGrid == NULL)
	{
		return;
	}
	m_pSoeParas->m_nInterval = nIndex;
	m_pSoeFirstGrid->slot_InterChanged(nIndex);


	CDvmDataset *pCurrDataset = (CDvmDataset*)m_pInterSelect_ComboBox->GetCurrSelObject();
	if (pCurrDataset)
	{
		CString_to_char(pCurrDataset->m_strDataType,m_pSoeParas->m_strDataset_path);
	}
}



void QSttMacroParaEditViewSoeWidget::slot_btn_ClearClearEventRecordsClicked()
{
	if (m_pSoeSecondGrid == NULL)
	{
		return;
	}
	m_pSoeSecondGrid->clearContents();
	m_pSoeSecondGrid->setRowCount(0);
}

void QSttMacroParaEditViewSoeWidget::AddShowSoeReports( CDvmDataset *pSoeRptDataset )
{
	if (m_pSoeSecondGrid == NULL)
	{
		return;
	}
	m_pSoeSecondGrid->AddShowSoeReports(pSoeRptDataset);
}

BOOL QSttMacroParaEditViewSoeWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	if (pSttItem == NULL)
	{
		return FALSE;
	}
	CString strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	if(strItemID.Find(_T("ReadSoeRlts")) == -1)
	{
		return FALSE;
	}
	CDvmValues *pDvmValues = pReport->m_pValues;
	CString strCount;
	strCount.Format(_T("%d"),m_pSoeParas->m_nTestCount);
	CDvmValue *pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("测试次数");
	pDvmValue->m_strID = _T("TestCount");
	pDvmValue->m_strValue = strCount;
	pDvmValues->AddNewChild(pDvmValue);

	return TRUE;
}


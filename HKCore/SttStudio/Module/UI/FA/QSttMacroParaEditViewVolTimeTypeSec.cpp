#include "../SttTestCntrFrameBase.h"
#include "../Controls/SttTabWidget.h"
#include "QSttMacroParaEditViewVolTimeTypeSec.h"

QSttMacroParaEditViewVolTimeTypeSec *g_pVolTimeTypeSecTestMain = NULL;

QSttMacroParaEditViewVolTimeTypeSec::QSttMacroParaEditViewVolTimeTypeSec(QWidget *parent)
{
	m_pFAStateSequenceGroupGrid = NULL;
	//m_pFATestResultViewGroupGrid = NULL;	
	m_pMacroTestValues = NULL;
	g_pVolTimeTypeSecTestMain = this;
	InitUI();
	OpenTestTestMngrFile(_T(""));
	InitData();
	SetDatas(NULL);
}

QSttMacroParaEditViewVolTimeTypeSec::~QSttMacroParaEditViewVolTimeTypeSec()
{
	if (m_pTestItemWidget != NULL)
	{
		delete m_pTestItemWidget;
		m_pTestItemWidget = NULL;
	}

// 	if (m_pFATestResultViewGroupGrid != NULL)
// 	{
// 		delete m_pFATestResultViewGroupGrid;
// 		m_pFATestResultViewGroupGrid = NULL;
// 	}
	if (m_pFAStateSequenceGroupGrid != NULL)
	{
		delete m_pFAStateSequenceGroupGrid;
		m_pFAStateSequenceGroupGrid = NULL;
	}

	if (m_pMacroTestValues != NULL)
	{
		delete m_pMacroTestValues;
		m_pMacroTestValues = NULL;
	}
}

void QSttMacroParaEditViewVolTimeTypeSec::InitUI()
{
	QTabWidget *pTestWidget = new QTabWidget(this);
	pTestWidget->setFont(*g_pSttGlobalFont);
	QTabWidget *pFACommonSpyWidget = new QTabWidget(this);
	pFACommonSpyWidget->setFont(*g_pSttGlobalFont);

	// 测试项目
	QHBoxLayout* pTestItemLayout = new QHBoxLayout();
	m_pTestItemWidget = new QSttVoltageTimeGroupTestItemWidget(pTestWidget);
	m_pTestItemWidget->setLayout(pTestItemLayout);
	pTestWidget->addTab(m_pTestItemWidget, QString::fromLocal8Bit("测试项目"));

	// 测试结果视图
// 	QWidget *pTestResultViewWidget = new QWidget(pFACommonSpyWidget);
// 	QHBoxLayout* pTestResulLayout = new QHBoxLayout();
// 	pTestResultViewWidget->setLayout(pTestResulLayout);
// 	m_pFATestResultViewGroupGrid = new QSttFATestResultViewGroupGrid(pTestResultViewWidget);
// 	m_pFATestResultViewGroupGrid->InitGrid();
// 	pTestResulLayout->addWidget(m_pFATestResultViewGroupGrid);
// 	pFACommonSpyWidget->addTab(pTestResultViewWidget, "测试结果试图");

	// 状态序列设置
	QWidget *pStateSequenceWidget = new QWidget(pFACommonSpyWidget);
	QHBoxLayout* pStateLayout = new QHBoxLayout();
	pStateSequenceWidget->setLayout(pStateLayout);
	m_pFAStateSequenceGroupGrid = new QSttFAStateSequenceGroupGrid(pStateSequenceWidget);
	m_pFAStateSequenceGroupGrid->InitGrid();
	pStateLayout->addWidget(m_pFAStateSequenceGroupGrid);
	pFACommonSpyWidget->addTab(pStateSequenceWidget, QString::fromLocal8Bit("状态序列视图"));
	
	QHBoxLayout *pMainLayout = new QHBoxLayout;
	QSplitter *pSplitter = new QSplitter(Qt::Horizontal);
	pSplitter->addWidget(pTestWidget);
	pSplitter->addWidget(pFACommonSpyWidget);
// 	pSplitter->setStretchFactor(0, 2); 
// 	pSplitter->setStretchFactor(1, 3); 
	pMainLayout->addWidget(pSplitter);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);
}



void QSttMacroParaEditViewVolTimeTypeSec::GetDatas(CDataGroup *pParas)
{
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();
	m_pVolTimeTypeSecData.CopyChildren(pParas);	
}


void QSttMacroParaEditViewVolTimeTypeSec::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pVolTimeTypeSecData);	
	}

	if(m_pTestItemWidget)
	{
		m_pTestItemWidget->UpdateData(&m_pVolTimeTypeSecData);
	}

 	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
 	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
 	g_theTestCntrFrame->InitStateMonitor();
 	g_theTestCntrFrame->ClearInfoWidget();
}

BOOL QSttMacroParaEditViewVolTimeTypeSec::OpenTestTestMngrFile( const CString& strParasFile )
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	CDataGroup* pDataGroup = g_theTestCntrFrame->GetTestMacroUI_Paras();

	if ((pDataGroup->GetCount()<=0)&&(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.GetLength()>0))
	{
		stt_ui_OpenParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile,pDataGroup);
	}

	if (pDataGroup->GetCount()>0)
	{
		pDataGroup->CopyChildren(&m_pVolTimeTypeSecData);
	}

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	UpdateFAParasData(&oDataGroup);

	return TRUE;
}


void QSttMacroParaEditViewVolTimeTypeSec::OnViewTestStart()
{
	m_pTestItemWidget->StartInit();
	m_pFAStateSequenceGroupGrid->setDisabled(true);
	m_pFAStateSequenceGroupGrid->StartInit();

	CString strItemID,strStateID;
	CDataGroup *pTestItemData = NULL;
	CDataGroup *pStateData = NULL;
	int nCount = m_pVolTimeTypeSecData.GetChildCount(DTMCLASSID_CDATAGROUP);
	for (int i = 0; i<nCount;i++)
	{
		strItemID.Format(_T("TestItem%d"), i+1);
		pTestItemData = (CDataGroup *)m_pVolTimeTypeSecData.FindByID(strItemID);

		if (pTestItemData)
		{
			int nStateCount = pTestItemData->GetChildCount(DTMCLASSID_CDATAGROUP);
			for (int i = 0; i<nStateCount;i++)
			{
				strStateID.Format(_T("state%d"), i);
				pStateData = (CDataGroup *)pTestItemData->FindByID(strStateID);
				pStateData->SetDataValue(_T("ActTime"), _T(""));
			}
		}
	}

	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewVolTimeTypeSec::OnViewTestStop()
{
	m_pTestItemWidget->StopInit();
	m_pFAStateSequenceGroupGrid->setDisabled(false);

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}


void QSttMacroParaEditViewVolTimeTypeSec::SaveXml()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/VolTimeTypeSec_Paras.xml");
	m_pVolTimeTypeSecData.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewVolTimeTypeSec::InitData()
{
	if (m_pTestItemWidget)
	{
		CString strPath = stt_ui_GetParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile);
		CDataGroup pVolTimeTypeSecData;
		pVolTimeTypeSecData.OpenXmlFile(strPath, CDataMngrXmlRWKeys::g_pXmlKeys);
		m_pTestItemWidget->InitData(&pVolTimeTypeSecData);
	}
}

void QSttMacroParaEditViewVolTimeTypeSec::UpdateEventMsg( CEventResult *pCurrEventResult )
{
	if (pCurrEventResult == NULL)
	{
		return;
	}

	if (m_pTestItemWidget)
	{
		m_pTestItemWidget->UpdateEventMsg(pCurrEventResult);
	}
}

void QSttMacroParaEditViewVolTimeTypeSec::UpdateTestResource( BOOL bCreateChMaps )
{
	UpdateStateData(NULL);
}

void QSttMacroParaEditViewVolTimeTypeSec::UpdateStateData( CDataGroup *pParas)
{
	float fVNom = g_oSystemParas.m_fVNom;

	CString strItemID,strStateID;

	CDataGroup *pTestItemData = NULL;
	CDataGroup *pStateData = NULL;
	POS pos = m_pVolTimeTypeSecData.GetHeadPosition();
	while (pos != NULL)
	{
		pTestItemData = (CDataGroup*)m_pVolTimeTypeSecData.GetNext(pos);

		if (pTestItemData->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			POS pos2 = pTestItemData->GetHeadPosition();
			while (pos2 != NULL)
			{
				pStateData = (CDataGroup*)pTestItemData->GetNext(pos2);

				if (pStateData->GetClassID() == DTMCLASSID_CDATAGROUP)
				{
					CDvmData *pU1mag =  (CDvmData *)pStateData->FindChildByID("U1mag");
					if (CString_To_long(pU1mag->m_strValue) > 0)
					{
						pU1mag->m_strValue = QString::number(fVNom,'f',1);
					}
					CDvmData *pU3mag =  (CDvmData *)pStateData->FindChildByID("U3mag");
					if (CString_To_long(pU3mag->m_strValue) > 0)
					{
						pU3mag->m_strValue = QString::number(fVNom,'f',1);
					}
				}
			}
		}
	}
	
	if (m_pTestItemWidget)
	{
		m_pTestItemWidget->UpdateStateTable();
		m_pTestItemWidget->UpdateData(&m_pVolTimeTypeSecData);
	}

}

void QSttMacroParaEditViewVolTimeTypeSec::UpdateResultState( CString strID,const CString &strState )
{
	if(m_pTestItemWidget)
	{
		m_pTestItemWidget->UpdateResultState(strID,strState);
	}
}

//BOOL QSttMacroParaEditViewVolTimeTypeSec::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem )
//{
//	if (m_pMacroTestValues == NULL)
//	{
//		m_pMacroTestValues = new CDvmValues;
//	}
//
//	CDvmValues *pDvmValues = pReport->m_pValues;
//	CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;
//	CString strTmpString;
//	CDvmData *pCurrData = NULL;
//	CDvmValue *pDvmValue = NULL;
//	CDataGroup * pTestItemData = NULL,*pStateData = NULL;
//	CString strItemID,strTestItemID,strStateID;
//	long nCheck;
//	stt_GetDataValueByID(&m_pVolTimeTypeSecData, _T("YX_Check"), nCheck);
//	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD) //通讯命令
//	{
//		m_pMacroTestValues->DeleteAll();
//
//		if (nCheck) //开环
//		{
//			if (pRptDvmDataset == NULL)
//			{
//				return FALSE;
//			}
//
//			strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
//			QStringList parts = strItemID.split('$');
//			pTestItemData = (CDataGroup *)m_pVolTimeTypeSecData.FindChildByID(parts[1]);
//			if (pTestItemData != NULL)
//			{
//				CDvmData *pTestObject = (CDvmData *)pTestItemData->FindChildByID(_T("TestObject"));
//				pCurrData = (CDvmData*)pRptDvmDataset->FindChildByID(pTestObject->m_strValue);
//				if (pCurrData != NULL)
//				{
//					CDvmValue *psystime = (CDvmValue *)pCurrData->FindChildByID(_T("$systime"));
//					CDvmValue *pst_1 = (CDvmValue *)pCurrData->FindChildByID(_T("$st_1"));
//
//					if (CString_To_long(pst_1->m_strValue) > 0)
//					{
//						strTmpString = pCurrData->m_strName + psystime->m_strValue;
//					} 
//					else
//					{
//						strTmpString = _T("");
//					}
//					pDvmValue = new CDvmValue;
//					pDvmValue->m_strID = _T("TestObject");
//					pDvmValue->m_strValue = strTmpString;
//					m_pMacroTestValues->AddNewChild(pDvmValue);
//				}
//			}
//		}
//	}
//
//
//	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)//电气量
//	{
//		if (pDvmValues == NULL)
//		{
//			return FALSE;
//		}
//
//		if (nCheck == 0)
//		{
//			strTmpString = _T("/");
//			pDvmValue = new CDvmValue;
//			pDvmValue->m_strID = _T("TestObject");
//			pDvmValue->m_strValue = strTmpString;
//			pDvmValues->AddNewChild(pDvmValue);
//		}
//		
//		
//		strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);
//		long nIndex = CString_To_long(strItemID.Right(1));
//		strTestItemID.Format(_T("TestItem%d"), nIndex);
//		pTestItemData = (CDataGroup *)m_pVolTimeTypeSecData.FindByID(strTestItemID);
//		if (pTestItemData)
//		{
//			int nStateCount = pTestItemData->GetChildCount(DTMCLASSID_CDATAGROUP);
//			for (int i = 0; i<nStateCount;i++)
//			{
//				strStateID.Format(_T("state%d"), i);
//				pStateData = (CDataGroup *)pTestItemData->FindByID(strStateID);
//				if(pStateData)
//				{
//					long nEndMode;
//					float fActTime;
//					stt_GetDataValueByID(pStateData, _T("EndMode"), nEndMode);
//					stt_GetDataValueByID(pStateData, _T("ActTime"), fActTime);
//
//					if (nEndMode !=0) //非时间触发 
//					{ 
//						CString strID;
//						if (fActTime > 0.00001) //有动作填充具体值
//						{
//							strTmpString.Format(_T("%.3f"), fActTime);
//						}
//						else
//						{
//							strTmpString = _T("未动作")/*g_sLangTxt_State_NoActioned*/;
//						}
//						strID.Format(_T("%s$ActTime"),strStateID.GetString());
//						pDvmValue = new CDvmValue;
//						pDvmValue->m_strID = strID;
//						pDvmValue->m_strValue = strTmpString;
//						pDvmValues->AddNewChild(pDvmValue);
//					}
//				}
//			}
//		}
//		if (m_pMacroTestValues &&m_pMacroTestValues->GetCount() > 0 )
//		{
//			pDvmValues->AppendCloneEx2(*m_pMacroTestValues);
//		}
//	}
//
//	return TRUE;
//}

CString QSttMacroParaEditViewVolTimeTypeSec::GetSoeAttrValue( CDvmData *pCurrData,const CString &strSearchID )
{
	CString strText;
	strText = "---";
	POS pos = pCurrData->GetHeadPosition();
	CDvmValue *pCurrValue = NULL;

	while(pos)
	{
		pCurrValue = (CDvmValue*)pCurrData->GetNext(pos);

		if (pCurrValue->m_strID.Find(strSearchID) != -1)
		{
			strText = pCurrValue->m_strValue;
			break;
		}
	}

	return strText;
}

void QSttMacroParaEditViewVolTimeTypeSec::UpdateFAParasData( CDataGroup *pParas )
{
	float fValue;
	stt_GetDataValueByID(pParas, _T("XTime"), m_fTimeValues[0]);
	m_pVolTimeTypeSecData.SetDataValue(_T("XTime"),m_fTimeValues[0]);
	stt_GetDataValueByID(pParas, _T("YTime"), m_fTimeValues[1]);
	m_pVolTimeTypeSecData.SetDataValue(_T("YTime"),m_fTimeValues[1]);
	stt_GetDataValueByID(pParas, _T("ZTime"), m_fTimeValues[2]);
	m_pVolTimeTypeSecData.SetDataValue(_T("ZTime"),m_fTimeValues[2]);
	stt_GetDataValueByID(pParas, _T("STime"), m_fTimeValues[3]);
	m_pVolTimeTypeSecData.SetDataValue(_T("STime"),m_fTimeValues[3]);
	stt_GetDataValueByID(pParas, _T("TimeAbsError"), fValue);
	m_pVolTimeTypeSecData.SetDataValue(_T("TimeAbsError"),fValue);

	stt_GetDataValueByID(pParas, _T("XLTime"), m_fTimeValues[4]);
	m_pVolTimeTypeSecData.SetDataValue(_T("XLTime"),m_fTimeValues[4]);
	stt_GetDataValueByID(pParas, _T("X2Time"), m_fTimeValues[5]);
	m_pVolTimeTypeSecData.SetDataValue(_T("X2Time"),m_fTimeValues[5]);
	stt_GetDataValueByID(pParas, _T("ResidualVoltage"), fVoltage);
	m_pVolTimeTypeSecData.SetDataValue(_T("ResidualVoltage"),fVoltage);
	stt_GetDataValueByID(pParas, _T("FaultCurrent"), fCurrent);
	m_pVolTimeTypeSecData.SetDataValue(_T("FaultCurrent"),fCurrent);
	stt_GetDataValueByID(pParas, _T("FaultCurrentDuration"), fDuration);
	m_pVolTimeTypeSecData.SetDataValue(_T("FaultCurrentDuration"),fDuration);

	UpdateBinDataValue(pParas, _T("BinA"), _T("A"));
	UpdateBinDataValue(pParas, _T("BinB"), _T("B"));
	UpdateBinDataValue(pParas, _T("BinC"), _T("C"));
	UpdateBinDataValue(pParas, _T("BinD"), _T("R"));
	UpdateBoutDataValue(pParas, _T("Bout1"), _T("_B01"));	
	UpdateBoutDataValue(pParas, _T("Bout2"), _T("_B02"));	
	UpdateBoutDataValue(pParas, _T("Bout3"), _T("_B03"));
	UpdateBoutDataValue(pParas, _T("Bout4"), _T("_B04"));	
	UpdateBoutDataValue(pParas, _T("Bout5"), _T("_B05"));	
	UpdateBoutDataValue(pParas, _T("Bout6"), _T("_B06"));
	UpdateBoutDataValue(pParas, _T("Bout7"), _T("_B07"));	
	UpdateBoutDataValue(pParas, _T("Bout8"), _T("_B08"));

 	UpdateStateData(pParas);
}


void QSttMacroParaEditViewVolTimeTypeSec::UpdateBinDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2 )
{
	// 0-合闸 1-分闸 2-空 index
	CString strValue,strBinValue,strBinIndex;
	stt_GetDataValueByID(pParas, strID1, strValue);
	if (strValue == _T("0"))
	{
		m_strEndBinIn[0] = strID1;
		strBinIndex = UpdateDataValue(strID2);
		strBinValue.Format(_T("ActBin_%s$1"),strBinIndex.GetString());
		m_pVolTimeTypeSecData.SetDataValue(_T("TtripEnd_Bin_H"),strBinValue);
		strValue = _T("2");
	}
	else if(strValue == _T("1"))
	{
		m_strEndBinIn[1] = strID1;
		strBinIndex = UpdateDataValue(strID2);
		strBinValue.Format(_T("ActBin_%s$1"),strBinIndex.GetString());
		m_pVolTimeTypeSecData.SetDataValue(_T("TtripEnd_Bin_T"),strBinValue);

		strValue = _T("1");
	}
	else if(strValue == _T("2"))
	{
		strValue = _T("0");
	}
	
	m_pVolTimeTypeSecData.SetDataValue(strID2, strValue);
}


void QSttMacroParaEditViewVolTimeTypeSec::UpdateBoutDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2 )
{
	//Din1合位-1 Din2分位-0 Din-5未储能-2 空-3
	CString strValue;
	stt_GetDataValueByID(pParas, strID1, strValue);
	if (strValue == _T("2") || strValue == _T("Din_5"))
	{
		strValue = _T("2");
	}
	else if(strValue == _T("1") || strValue == _T("Din_1"))
	{
		strValue = _T("1");
	}
	else if(strValue == _T("0") || strValue == _T("Din_2"))
	{
		strValue = _T("0");
	}
	else 
	{
		strValue = _T("3");
	}

	m_pVolTimeTypeSecData.SetDataValue(strID2, strValue);
}

CString  QSttMacroParaEditViewVolTimeTypeSec::UpdateDataValue( const CString &strID )
{
	CString strBinIndex;
	if (strID == _T("A"))strBinIndex = _T("0");
	else if (strID == _T("B"))strBinIndex = _T("1");
	else if (strID == _T("C"))strBinIndex = _T("2");
	else if (strID == _T("R"))strBinIndex = _T("3");
	return strBinIndex;
}
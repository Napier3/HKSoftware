#include "SttMacroParaEditViewRemote_ShakeWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>


QSttMacroParaEditViewRemote_ShakeWidget::QSttMacroParaEditViewRemote_ShakeWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pShakeTable = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewRemote_ShakeWidget::~QSttMacroParaEditViewRemote_ShakeWidget()
{

}

void QSttMacroParaEditViewRemote_ShakeWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("遥信防抖测试");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

// 	CDvmData* pCurData = (CDvmData*)m_pShakeDataGroup.FindByID(_T("AntiShakeTime_Check"));
// 	if (pCurData)
// 	{
// 		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
// 		m_pGroupBox->setChecked(nIsSelected);
// 	}

	m_pShakeTable = new QSttMacroParaEditViewRemote_ShakeTable(this);
	m_pShakeTable->setFont(*g_pSttGlobalFont);
	m_pShakeTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pShakeTable->m_pShakeDataGroup = &m_pShakeDataGroup;

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pShakeTable);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	OpenBinBoutMapXml();
}

BOOL QSttMacroParaEditViewRemote_ShakeWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pShakeDataGroup);
	}
	return TRUE;
}


void QSttMacroParaEditViewRemote_ShakeWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pShakeDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	m_pShakeTable->InitData(pParas);
}

void QSttMacroParaEditViewRemote_ShakeWidget::SaveParasXml()
{
// 	m_pShakeDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
// 	m_pShakeDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
// 	m_pShakeDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
// 	m_pShakeDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_AntiShake_Paras.xml");
	m_pShakeDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewRemote_ShakeWidget::OnViewTestStart()
{	
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewRemote_ShakeWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewRemote_ShakeWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pShakeDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewRemote_ShakeWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pShakeDataGroup);
	}

 	CDvmData* pCurData = (CDvmData*)m_pShakeDataGroup.FindByID(_T("AntiShakeTime_Check"));
 	if (pCurData)
 	{
 		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
 		m_pGroupBox->setChecked(nIsSelected);
 	}
 
//   	if (m_pShakeTable != NULL)
//   	{
//   		m_pShakeTable->InitData(&m_oBinBoutDataGroup);
//   	}
	m_pShakeTable->UpdateTable(&m_pShakeDataGroup);

 	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
 	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
 	g_theTestCntrFrame->InitStateMonitor();
 	g_theTestCntrFrame->ClearInfoWidget();
}


void QSttMacroParaEditViewRemote_ShakeWidget::OpenBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
// 	m_pShakeTable->InitData(&m_oBinBoutDataGroup);
// 	CString strDatasetpath;
// 	stt_GetDataValueByID(&m_oBinBoutDataGroup, _T("datasetpath"), strDatasetpath);
// 	m_pShakeDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	CString strID,strValue;
	for (int i = 0; i < 8 ;i++)
	{
		strID.Format(_T("Bout%d"), i+1);
		stt_GetDataValueByID(&oDataGroup, strID, strValue);

		if (strValue == _T("Din_1") || strValue == _T("1"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_1"));  
		}
		else if (strValue == _T("Din_2") || strValue == _T("0"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_2"));
		}
		else if (strValue == _T("Din_5") || strValue == _T("2"))
		{
			oDataGroup.SetDataValue(strID, _T("Din_5"));
		}
		else
		{
			oDataGroup.SetDataValue(strID, _T(""));  
		}
	}

	UpdateRemoteBoutData(&oDataGroup);
}

BOOL QSttMacroParaEditViewRemote_ShakeWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	if (pSttItem == NULL)
	{
		return FALSE;
	}
	CString strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	if(strItemID.Find(_T("ReadCount")) == -1)
	{
		return FALSE;
	}
	CDvmValues *pDvmValues = pReport->m_pValues;
	CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;
	CString strTestCount,strID,strChannelName;
	CDataGroup *pTestMacroUI_Paras = &m_pShakeDataGroup;

	CDvmValue *pDvmValue = NULL;
	//AntiShakeTimeTest$TestItem4$ReadCount
	int nTestItemPos = strItemID.Find(_T("$TestItem"));
	int nLastPos = strItemID.Find(_T("$"), nTestItemPos + 1);
	CString strReadCount = _T("$ReadCount");
	CString strTestIndex;
	int nTestIndex = 1;
	if ((nLastPos + strReadCount.GetLength()) == strItemID.GetLength())
	{
		strTestIndex = strItemID.Mid(nTestItemPos + 9, nLastPos - (nTestItemPos + 9));
		nTestIndex = strTestIndex.toInt();
	}

	//int nTestIndex = (strItemID == _T("AntiShakeTimeTest$ReadCount")) ? 1 : strItemID.right(1).toInt()+1;
	strID.Format(_T("TestItem%d"),nTestIndex);
	CDataGroup *pDataGroup = (CDataGroup *)pTestMacroUI_Paras->FindByID(strID);
	if(pDataGroup == NULL)
	{
		return FALSE;
	}

	CDvmData *pChannelData = (CDvmData *)pDataGroup->FindByID(_T("TestObject"));
	if ( pChannelData->m_strValue == _T("Din_1"))
	{
		strChannelName = _T("合位");
	}
	else if (pChannelData->m_strValue == _T("Din_2"))
	{
		strChannelName = _T("分位");
	}
	else if (pChannelData->m_strValue == _T("Din_5"))
	{
		strChannelName = _T("未储能");
	}
	pDvmValue = new CDvmValue;
	pDvmValue->m_strID = _T("TestObject");
	pDvmValue->m_strName = _T("YX通道");
	pDvmValue->m_strValue = strChannelName;
	pDvmValues->AddNewChild(pDvmValue);

	CDvmData *pShakeTimeData = (CDvmData *)pDataGroup->FindByID(_T("AntiShakeTime"));
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("防抖时间");
	pDvmValue->m_strID = _T("AntiShakeTime");
	pDvmValue->m_strValue = pShakeTimeData->m_strValue;
	pDvmValues->AddNewChild(pDvmValue);

	CDvmData *pPulseData = (CDvmData *)pDataGroup->FindByID(_T("PulseWidth"));
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("脉冲宽度");
	pDvmValue->m_strID = _T("PulseWidth");
	pDvmValue->m_strValue = pPulseData->m_strValue;
	pDvmValues->AddNewChild(pDvmValue);

// 	CDvmData *pEstimateTimesData = (CDvmData *)pDataGroup->FindByID(_T("EstimateTimes"));
// 	pDvmValue = new CDvmValue;
// 	pDvmValue->m_strName = _T("预计变位次数");
// 	pDvmValue->m_strID = _T("EstimateTimes");
// 	pDvmValue->m_strValue = pEstimateTimesData->m_strValue;
// 	pDvmValues->AddNewChild(pDvmValue);

	if ((pRptDvmDataset != NULL)&&(pRptDvmDataset->GetCount()>0))
	{
		CString strValue;
		CDvmData *pActualTimesData = (CDvmData *)pRptDvmDataset->FindByID(pChannelData->m_strValue);
		if (pActualTimesData != NULL)
		{
			CDvmValue* pActualTimesValue = pActualTimesData->FindValueByID(_T("$st_all"));
			if (pActualTimesValue != NULL)
			{
				strValue = pActualTimesValue->m_strValue;
		}
		else
		{
				strValue = pActualTimesData->m_strValue;
			}
		}

		pDvmValue = new CDvmValue;
		pDvmValue->m_strName = _T("实际变位次数");
		pDvmValue->m_strID = _T("ActualTimes");
		pDvmValue->m_strValue = strValue;
		pDvmValues->AddNewChild(pDvmValue);
	}
	return TRUE;
}

void QSttMacroParaEditViewRemote_ShakeWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pShakeDataGroup.SetDataValue(_T("AntiShakeTime_Check"),(long)checked);	
}

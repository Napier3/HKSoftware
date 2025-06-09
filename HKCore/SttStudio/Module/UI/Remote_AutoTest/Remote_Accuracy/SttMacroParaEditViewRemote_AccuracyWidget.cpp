#include "SttMacroParaEditViewRemote_AccuracyWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>

QSttMacroParaEditViewRemote_AccuracyWidget* g_pAccuracyWidget = NULL;

QSttMacroParaEditViewRemote_AccuracyWidget::QSttMacroParaEditViewRemote_AccuracyWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pAccuracyTable = NULL;
	m_pGroupBox = NULL;
	g_pAccuracyWidget = this;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewRemote_AccuracyWidget::~QSttMacroParaEditViewRemote_AccuracyWidget()
{

}

void QSttMacroParaEditViewRemote_AccuracyWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("遥信正确性测试");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

// 	CDvmData* pCurData = (CDvmData*)m_pAccuracyDataGroup.FindByID(_T("Remote_Accuracy_Check"));
// 	if (pCurData)
// 	{
// 		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
// 		m_pGroupBox->setChecked(nIsSelected);
// 	}
	
	m_pAccuracyTable = new QSttMacroParaEditViewRemote_AccuracyTable(this);
	m_pAccuracyTable->setFont(*g_pSttGlobalFont);
	m_pAccuracyTable->horizontalHeader()->setFont(*g_pSttGlobalFont);

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pAccuracyTable);
	m_pGroupBox->setLayout(pVBoxLayout);
	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pGroupBox);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

	OpenBinBoutMapXml();

	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
}

BOOL QSttMacroParaEditViewRemote_AccuracyWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pAccuracyDataGroup);
	}
	return TRUE;
}


void QSttMacroParaEditViewRemote_AccuracyWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pAccuracyDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	m_pAccuracyTable->InitData(pParas,&m_pAccuracyDataGroup);
}

void QSttMacroParaEditViewRemote_AccuracyWidget::SaveParasXml()
{
// 	m_pAccuracyDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
// 	m_pAccuracyDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
// 	m_pAccuracyDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
// 	m_pAccuracyDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_Accuracy_Paras.xml");
	m_pAccuracyDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewRemote_AccuracyWidget::OnViewTestStart()
{ 	
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewRemote_AccuracyWidget::OnViewTestStop()
{
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewRemote_AccuracyWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	
	/*SaveParasXml();*/
	m_pAccuracyDataGroup.CopyChildren(pParas);	
}

void QSttMacroParaEditViewRemote_AccuracyWidget::OpenBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
	/*m_pAccuracyTable->InitData(&oDataGroup);*/
// 	CString strDatasetpath;
// 	stt_GetDataValueByID(&oDataGroup, _T("datasetpath"), strDatasetpath);
// 	m_pAccuracyDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);

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

void QSttMacroParaEditViewRemote_AccuracyWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pAccuracyDataGroup);
	}

	CDvmData* pCurData = (CDvmData*)m_pAccuracyDataGroup.FindByID(_T("Remote_Accuracy_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}
	m_pAccuracyTable->UpdateTable(&m_pAccuracyDataGroup);

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

BOOL QSttMacroParaEditViewRemote_AccuracyWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	if (pSttItem == NULL)
	{
		return FALSE;
	}
	CString strItemID = pSttItem->GetIDPathEx(STTGBXMLCLASSID_CSTTDEVICE, FALSE);

	if(strItemID.Find(_T("ReadRlts")) == -1)
	{
		return FALSE;
	}
	CDvmValues *pDvmValues = pReport->m_pValues;
	int nCount = m_pAccuracyDataGroup.GetChildCount(DTMCLASSID_CDATAGROUP);
	CString strID,strTestObject,strChannelName;
	long nSelcet;
	//Remote_AccuracyTest$TestItem1$ReadRlts
	int nTestItemPos = strItemID.Find(_T("$TestItem"));
	int nLastPos = strItemID.Find(_T("$"), nTestItemPos + 1);
	CString strReadRlts = _T("$ReadRlts");
	CString strTestIndex;
	int nTestIndex = 1;
	if ((nLastPos + strReadRlts.GetLength()) == strItemID.GetLength())
	{
		strTestIndex = strItemID.Mid(nTestItemPos + 9, nLastPos - (nTestItemPos + 9));
		nTestIndex = strTestIndex.toInt();
	}
	//int nTestIndex = (strItemID == _T("AccuracyTest$ReadRlts")) ? 1 : strItemID.right(1).toInt()+1;
	strID.Format(_T("TestItem%d"), nTestIndex);
	CDataGroup *pDataGroup = (CDataGroup *)m_pAccuracyDataGroup.FindByID(strID);
	if(pDataGroup)
	{
		stt_GetDataValueByID(pDataGroup, _T("Select"), nSelcet);
		if (nSelcet == 1)
		{
			stt_GetDataValueByID(pDataGroup, _T("TestObject"), strTestObject);
			if ( strTestObject == _T("Din_1"))
			{
				strChannelName = _T("合位");
			}
			else if (strTestObject == _T("Din_2"))
			{
				strChannelName = _T("分位");
			}
			else if (strTestObject == _T("Din_5"))
			{
				strChannelName = _T("未储能");
			}

			CDvmValue *pDvmValue = new CDvmValue;
			pDvmValue->m_strID = _T("TestObject");
			pDvmValue->m_strName = _T("YX通道");
			pDvmValue->m_strValue = strChannelName;
			pDvmValues->AddNewChild(pDvmValue);
		}
	}

	return TRUE;
}

void QSttMacroParaEditViewRemote_AccuracyWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pAccuracyDataGroup.SetDataValue(_T("Remote_Accuracy_Check"),(long)checked);	
}

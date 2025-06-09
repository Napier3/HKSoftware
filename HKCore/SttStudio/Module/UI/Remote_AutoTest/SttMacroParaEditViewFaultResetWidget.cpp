#include "SttMacroParaEditViewFaultResetWidget.h"
#include "../SttTestCntrFrameBase.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewFaultResetWidget::QSttMacroParaEditViewFaultResetWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewFaultResetWidget::~QSttMacroParaEditViewFaultResetWidget()
{
}

void QSttMacroParaEditViewFaultResetWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("故障复归");
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

	QLabel *pLabel1 = new QLabel;
	strText = _T("投入区段");
	pLabel1->setText(strText);
	pLabel1->setFont(*g_pSttGlobalFont);
	QLabel *pLabel2 = new QLabel;
	strText = _T("整定值(A)");
	pLabel2->setText(strText);
	pLabel2->setFont(*g_pSttGlobalFont);
	QLabel *pLabel3 = new QLabel;
	strText = _T("整定时间(s)");
	pLabel3->setText(strText);
	pLabel3->setFont(*g_pSttGlobalFont);
// 	strText = _T("故障电流(A)");
// 	QLabel *pLabel4 = new QLabel;
// 	pLabel4->setText(strText);
// 	pLabel4->setFont(*g_pSttGlobalFont);

	strText = _T("过流I段");
	QLineEdit *pLineEdit1 = new QLineEdit;
	pLineEdit1->setText(strText);
	pLineEdit1->setFont(*g_pSttGlobalFont);
	pLineEdit1->setEnabled(false);


	QLineEdit *pSetLineEdit = new QLineEdit;
	pSetLineEdit->setObjectName(_T("Setting"));
	pSetLineEdit->setFont(*g_pSttGlobalFont);
	QLineEdit *pSetTimeLineEdit = new QLineEdit;
	pSetTimeLineEdit->setFont(*g_pSttGlobalFont);
	pSetTimeLineEdit->setObjectName(_T("SettingTime"));
// 	QLineEdit *pFaultCurLineEdit = new QLineEdit;
// 	pFaultCurLineEdit->setFont(*g_pSttGlobalFont);
// 	pFaultCurLineEdit->setObjectName(_T("FaultCur"));
	m_pAllLineEditList.append(pSetLineEdit);
	m_pAllLineEditList.append(pSetTimeLineEdit);
	//m_pAllLineEditList.append(pFaultCurLineEdit);

	QHBoxLayout *pHBoxLayout1 = new QHBoxLayout;
	pHBoxLayout1->addWidget(pLabel1);
	pHBoxLayout1->addWidget(pLineEdit1);
	pHBoxLayout1->addWidget(pLabel2);
	pHBoxLayout1->addWidget(pSetLineEdit);
	pHBoxLayout1->addWidget(pLabel3);
	pHBoxLayout1->addWidget(pSetTimeLineEdit);
// 	pHBoxLayout1->addWidget(pLabel4);
// 	pHBoxLayout1->addWidget(pFaultCurLineEdit);


	QLabel *pLabel5 = new QLabel;
	strText = _T("故障遥信自动复归时间");
	pLabel5->setText(strText);
	pLabel5->setFont(*g_pSttGlobalFont);

	QLineEdit *pRestTimeLineEdit = new QLineEdit;
	pRestTimeLineEdit->setFont(*g_pSttGlobalFont);
	pRestTimeLineEdit->setObjectName(_T("RestTime"));
	m_pAllLineEditList.append(pRestTimeLineEdit);

	QHBoxLayout *pHBoxLayout2 = new QHBoxLayout;
	pHBoxLayout2->addWidget(pLabel5);
	pHBoxLayout2->addWidget(pRestTimeLineEdit);
	pHBoxLayout2->addStretch(10);

	QVBoxLayout *pVBoxLayout = new QVBoxLayout(m_pGroupBox);
	pVBoxLayout->addLayout(pHBoxLayout1);
	pVBoxLayout->addLayout(pHBoxLayout2);
	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(m_pGroupBox);

	setFocusPolicy(Qt::StrongFocus);
	setLayout(pMainLayout);

	OpenBinBoutMapXml();
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			connect(pLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
		}
	}

	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
}


void QSttMacroParaEditViewFaultResetWidget::OnViewTestStart()
{

// 	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
// 	{
// 		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
// 		pLineEdit->setDisabled(true);
// 	}

	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewFaultResetWidget::OnViewTestStop()
{
// 	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
// 	{
// 		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
// 		pLineEdit->setDisabled(false);
// 	}
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewFaultResetWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue));
		m_pFaultResetDataGroup.SetDataValue(strID,fValue);
	}
}


void QSttMacroParaEditViewFaultResetWidget::slot_GroupBoxtoggled( bool bChecked)
{
	m_pFaultResetDataGroup.SetDataValue(_T("FaultReset_Check"),long(bChecked));
}

void QSttMacroParaEditViewFaultResetWidget::GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue));
}


BOOL QSttMacroParaEditViewFaultResetWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pFaultResetDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewFaultResetWidget::GetDatas( CDataGroup *pParas )
{
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();
	m_pFaultResetDataGroup.CopyChildren(pParas);

	//SaveParasXml();
}

void QSttMacroParaEditViewFaultResetWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pFaultResetDataGroup);	
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pFaultResetDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}

	CDvmData* pCurData = (CDvmData*)m_pFaultResetDataGroup.FindByID(_T("FaultReset_Check"));
	if (pCurData)
	{
		m_pGroupBox->setChecked(CString_To_long(pCurData->m_strValue));
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}


void QSttMacroParaEditViewFaultResetWidget::SaveParasXml()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_FaultReset_Paras.xml");
	m_pFaultResetDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewFaultResetWidget::OpenBinBoutMapXml()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("BinBoutCommMapConfig.xml");
	CDataGroup oDataGroup;
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	oDataGroup.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
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

void QSttMacroParaEditViewFaultResetWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pFaultResetDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);

	UpdateDataValue(pParas, _T("BinA"), _T("A"));
	UpdateDataValue(pParas, _T("BinB"), _T("B"));
	UpdateDataValue(pParas, _T("BinC"), _T("C"));
	UpdateDataValue(pParas, _T("BinD"), _T("R"));
}

void QSttMacroParaEditViewFaultResetWidget::UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2 )
{
	CString strValue;
	stt_GetDataValueByID(pParas, strID1, strValue);
	if (strValue == _T("0"))
	{
		strValue = _T("2");
	}
	else if(strValue == _T("1"))
	{
		strValue = _T("1");
// 		CString strBinValue,strBinIndex;
// 		if (strID2 == _T("A"))strBinIndex = _T("0");
// 		else if (strID2 == _T("B"))strBinIndex = _T("1");
// 		else if (strID2 == _T("C"))strBinIndex = _T("2");
// 		else if (strID2 == _T("R"))strBinIndex = _T("3");
// 		strBinValue.Format(_T("ActBin_%s$1"),strBinIndex.GetString());
// 		m_pZeroDataGroup.SetDataValue(_T("TtripEnd_Bin"),strBinValue);
	}
	else if(strValue == _T("2"))
	{
		strValue = _T("0");
	}

	m_pFaultResetDataGroup.SetDataValue(strID2, strValue);
}





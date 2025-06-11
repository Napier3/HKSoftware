#include "SttMacroParaEditViewPTAlarmWidget.h"
#include "../SttTestCntrFrameBase.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewPTAlarmWidget::QSttMacroParaEditViewPTAlarmWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewPTAlarmWidget::~QSttMacroParaEditViewPTAlarmWidget()
{
}

void QSttMacroParaEditViewPTAlarmWidget::InitUI()
{
	CString strText;
	strText = _T("PT断线告警");
	m_pGroupBox = new QSttCheckableGroupBox;
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

	QLabel *pLabel1 = new QLabel;
	strText = _T("投入:");
	pLabel1->setText(strText);
	pLabel1->setFont(*g_pSttGlobalFont);
	QLineEdit *pLineEdit1 = new QLineEdit;
	strText = _T("PT断线告警");
	pLineEdit1->setText(strText);
	pLineEdit1->setFont(*g_pSttGlobalFont);
	pLineEdit1->setEnabled(false);

	QLabel *pLabel2 = new QLabel;
	strText = _T("仪器输出参数设置");
	pLabel2->setText(strText);
	pLabel2->setFont(*g_pSttGlobalFont);
	QLabel *pLabel3 = new QLabel;
	strText = _T("相电压(V)");
	pLabel3->setText(strText);
	pLabel3->setFont(*g_pSttGlobalFont);
	QLabel *pLabel4 = new QLabel;
	strText = _T("相电流(A)");
	pLabel4->setText(strText);
	pLabel4->setFont(*g_pSttGlobalFont);
	
	QLineEdit *pVolLineEdit = new QLineEdit;
	pVolLineEdit->setObjectName(_T("PhaseVoltage"));
	pVolLineEdit->setFont(*g_pSttGlobalFont);
	QLineEdit *pCurLineEdit = new QLineEdit;
	pCurLineEdit->setFont(*g_pSttGlobalFont);
	pCurLineEdit->setObjectName(_T("PhaseCurrent"));
	m_pAllLineEditList.append(pVolLineEdit);
	m_pAllLineEditList.append(pCurLineEdit);


	QGridLayout *pGridLayout = new QGridLayout(m_pGroupBox);
	pGridLayout->addWidget(pLabel1,0,0,1,1);
	pGridLayout->addWidget(pLineEdit1,0,1,1,1);
	pGridLayout->addWidget(pLabel2,1,0,1,2);
	pGridLayout->addWidget(pLabel3,1,2,1,1);
	pGridLayout->addWidget(pVolLineEdit,1,3,1,1);
	pGridLayout->addWidget(pLabel4,2,2,1,1);
	pGridLayout->addWidget(pCurLineEdit,2,3,1,1);
	QSpacerItem* hSpacer = new QSpacerItem(60, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
	pGridLayout->addItem(hSpacer, 2, 4, 1, 1); 

	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(m_pGroupBox);
	//pGroupBox->setMaximumSize(400,200);
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


void QSttMacroParaEditViewPTAlarmWidget::OnViewTestStart()
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

void QSttMacroParaEditViewPTAlarmWidget::OnViewTestStop()
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

void QSttMacroParaEditViewPTAlarmWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue,'f',1));
		m_pPTAlarmDataGroup.SetDataValue(strID,fValue);
	}
}


void QSttMacroParaEditViewPTAlarmWidget::slot_GroupBoxtoggled( bool bChecked)
{
	m_pPTAlarmDataGroup.SetDataValue(_T("PTAlarm_Check"),long(bChecked));
}

void QSttMacroParaEditViewPTAlarmWidget::GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',1));
}


BOOL QSttMacroParaEditViewPTAlarmWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pPTAlarmDataGroup);
	}

	return TRUE;
}

void QSttMacroParaEditViewPTAlarmWidget::GetDatas( CDataGroup *pParas )
{
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();
	m_pPTAlarmDataGroup.CopyChildren(pParas);

	//SaveParasXml();
}

void QSttMacroParaEditViewPTAlarmWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pPTAlarmDataGroup);	
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pPTAlarmDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}

	CDvmData* pCurData = (CDvmData*)m_pPTAlarmDataGroup.FindByID(_T("PTAlarm_Check"));
	if (pCurData)
	{
		m_pGroupBox->setChecked(CString_To_long(pCurData->m_strValue));
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}


void QSttMacroParaEditViewPTAlarmWidget::SaveParasXml()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_PTAlarm_Paras.xml");
	m_pPTAlarmDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}


void QSttMacroParaEditViewPTAlarmWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewPTAlarmWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pPTAlarmDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
}

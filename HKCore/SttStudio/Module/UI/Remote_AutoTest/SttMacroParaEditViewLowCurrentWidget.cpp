#include "SttMacroParaEditViewLowCurrentWidget.h"
#include "../SttTestCntrFrameBase.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewLowCurrentWidget::QSttMacroParaEditViewLowCurrentWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewLowCurrentWidget::~QSttMacroParaEditViewLowCurrentWidget()
{
}

void QSttMacroParaEditViewLowCurrentWidget::InitUI()
{
	CString strText;
	strText = _T("小电流接地");
	m_pGroupBox = new QSttCheckableGroupBox;
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);
	QLabel *pLabel1 = new QLabel;
	strText = _T("投入:");
	pLabel1->setText(strText);
	pLabel1->setFont(*g_pSttGlobalFont);
	QLabel *pLabel2 = new QLabel;
	pLabel2->setText(strText);
	pLabel2->setFont(*g_pSttGlobalFont);
	QLabel *pLabel3 = new QLabel;
	strText = _T("零序电压整定值(V)");
	pLabel3->setText(strText);
	pLabel3->setFont(*g_pSttGlobalFont);
	QLabel *pLabel4 = new QLabel;
	strText = _T("零序电流整定值(A)");
	pLabel4->setText(strText);
	pLabel4->setFont(*g_pSttGlobalFont);
	QLineEdit *pLineEdit1 = new QLineEdit;
	strText = _T("小电流接地告警");
	pLineEdit1->setText(strText);
	pLineEdit1->setFont(*g_pSttGlobalFont);
	pLineEdit1->setEnabled(false);
	QLineEdit *pLineEdit2 = new QLineEdit;
	strText = _T("小电流接地跳闸");
	pLineEdit2->setText(strText);
	pLineEdit2->setFont(*g_pSttGlobalFont);
	pLineEdit2->setEnabled(false);

	QLineEdit *pZeroVolSetLineEdit = new QLineEdit;
	pZeroVolSetLineEdit->setObjectName(_T("ZeroVolSetValue"));
	pZeroVolSetLineEdit->setFont(*g_pSttGlobalFont);
	QLineEdit *pZeroCurSetLineEdit = new QLineEdit;
	pZeroCurSetLineEdit->setFont(*g_pSttGlobalFont);
	pZeroCurSetLineEdit->setObjectName(_T("ZeroCurSetValue"));
	m_pAllLineEditList.append(pZeroVolSetLineEdit);
	m_pAllLineEditList.append(pZeroCurSetLineEdit);


	QLabel *pLabel5 = new QLabel;
	strText = _T("仪器输出参数设置:");
	pLabel5->setText(strText);
	pLabel5->setFont(*g_pSttGlobalFont);
	QLabel *pLabel6 = new QLabel;
	strText = _T("零序电压(V)");
	pLabel6->setText(strText);
	pLabel6->setFont(*g_pSttGlobalFont);
	QLabel *pLabel7 = new QLabel;
	strText = _T("零序电流(A)");
	pLabel7->setText(strText);
	pLabel7->setFont(*g_pSttGlobalFont);
	QLabel *pLabel8 = new QLabel;
	strText = _T("相位(°)");
	pLabel8->setText(strText);
	pLabel8->setFont(*g_pSttGlobalFont);
	QLabel *pLabel9 = new QLabel;
	pLabel9->setText(strText);
	pLabel9->setFont(*g_pSttGlobalFont);

	QLineEdit *pZeroVolLineEdit = new QLineEdit;
	pZeroVolLineEdit->setFont(*g_pSttGlobalFont);
	pZeroVolLineEdit->setObjectName(_T("ZeroVol"));
	QLineEdit *pZeroCurLineEdit = new QLineEdit;
	pZeroCurLineEdit->setFont(*g_pSttGlobalFont);
	pZeroCurLineEdit->setObjectName(_T("ZeroCur"));
	m_pAllLineEditList.append(pZeroVolLineEdit);
	m_pAllLineEditList.append(pZeroCurLineEdit);


	QLineEdit *pVolPhaseLineEdit = new QLineEdit;
	pVolPhaseLineEdit->setFont(*g_pSttGlobalFont);
	pVolPhaseLineEdit->setObjectName(_T("ZeroVolPhase"));
	QLineEdit *pCurPhaseLineEdit = new QLineEdit;
	pCurPhaseLineEdit->setFont(*g_pSttGlobalFont);
	pCurPhaseLineEdit->setObjectName(_T("ZeroCurPhase"));
	m_pAllLineEditList.append(pVolPhaseLineEdit);
	m_pAllLineEditList.append(pCurPhaseLineEdit);


	QHBoxLayout *pHBoxLayout1 = new QHBoxLayout;
	pHBoxLayout1->addWidget(pLabel1);
	pHBoxLayout1->addWidget(pLineEdit1);
	pHBoxLayout1->addWidget(pLabel2);
	pHBoxLayout1->addWidget(pLineEdit2);
	pHBoxLayout1->addWidget(pLabel3);
	pHBoxLayout1->addWidget(pZeroVolSetLineEdit);
	pHBoxLayout1->addStretch();

	QHBoxLayout *pHBoxLayout2 = new QHBoxLayout;
	pHBoxLayout2->addWidget(pLabel4);
	pHBoxLayout2->addWidget(pZeroCurSetLineEdit);
	pHBoxLayout2->addStretch(20);

	QGridLayout *pGridLayout = new QGridLayout;
	pGridLayout->addWidget(pLabel5,0,0,1,1);
	pGridLayout->addWidget(pLabel6,0,1,1,1);
	pGridLayout->addWidget(pZeroVolLineEdit,0,2,1,1);

	QSpacerItem *spacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
	pGridLayout->addItem(spacer, 0, 3);	
	
	pGridLayout->addWidget(pLabel8,0,4,1,1);
	pGridLayout->addWidget(pVolPhaseLineEdit,0,5,1,1);
	pGridLayout->addWidget(pLabel7,1,1,1,1);
	pGridLayout->addWidget(pZeroCurLineEdit,1,2,1,1);
	pGridLayout->addWidget(pLabel9,1,4,1,1);
	pGridLayout->addWidget(pCurPhaseLineEdit,1,5,1,1);
	QSpacerItem *spacer1 = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
	pGridLayout->addItem(spacer1, 0, 6);	

	QVBoxLayout *pVBoxLayout = new QVBoxLayout(m_pGroupBox);
	pVBoxLayout->addLayout(pHBoxLayout1);
	pVBoxLayout->addLayout(pHBoxLayout2);
	pVBoxLayout->addLayout(pGridLayout);

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


void QSttMacroParaEditViewLowCurrentWidget::OnViewTestStart()
{
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
// 	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
// 	{
// 		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
// 		pLineEdit->setDisabled(true);
// 	}
}

void QSttMacroParaEditViewLowCurrentWidget::OnViewTestStop()
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

void QSttMacroParaEditViewLowCurrentWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		//fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue,'f',1));
		m_pSmallBatteryDataGroup.SetDataValue(strID,fValue);
	}
}


void QSttMacroParaEditViewLowCurrentWidget::GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',1));
}


BOOL QSttMacroParaEditViewLowCurrentWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pSmallBatteryDataGroup);
	}

	return TRUE;
}

void QSttMacroParaEditViewLowCurrentWidget::GetDatas( CDataGroup *pParas )
{
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();
	m_pSmallBatteryDataGroup.CopyChildren(pParas);

	//SaveParasXml();
}

void QSttMacroParaEditViewLowCurrentWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pSmallBatteryDataGroup);	
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pSmallBatteryDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}

	CDvmData* pCurData = (CDvmData*)m_pSmallBatteryDataGroup.FindByID(_T("LowCurrent_Check"));
	if (pCurData)
	{
		m_pGroupBox->setChecked(CString_To_long(pCurData->m_strValue));
	}
	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}


void QSttMacroParaEditViewLowCurrentWidget::SaveParasXml()
{
	m_pSmallBatteryDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pSmallBatteryDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pSmallBatteryDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pSmallBatteryDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_SmallBattery_Paras.xml");
	m_pSmallBatteryDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);

}


void QSttMacroParaEditViewLowCurrentWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewLowCurrentWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pSmallBatteryDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
}

void QSttMacroParaEditViewLowCurrentWidget::slot_GroupBoxtoggled( bool bChecked)
{
	m_pSmallBatteryDataGroup.SetDataValue(_T("LowCurrent_Check"),long(bChecked));
}

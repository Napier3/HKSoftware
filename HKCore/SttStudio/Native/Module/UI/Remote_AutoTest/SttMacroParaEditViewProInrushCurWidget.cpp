#include "SttMacroParaEditViewProInrushCurWidget.h"
#include "../SttTestCntrFrameBase.h"

#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewProInrushCurWidget::QSttMacroParaEditViewProInrushCurWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewProInrushCurWidget::~QSttMacroParaEditViewProInrushCurWidget()
{
}

void QSttMacroParaEditViewProInrushCurWidget::InitUI()
{
	CString strText;
	m_pGroupBox = new QSttCheckableGroupBox;
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("涌流保护");
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
	strText = _T("整定值(A)");
	pLabel3->setText(strText);
	pLabel3->setFont(*g_pSttGlobalFont);
	QLabel *pLabel4 = new QLabel;
	strText = _T("整定时间(s)");
	pLabel4->setText(strText);
	pLabel4->setFont(*g_pSttGlobalFont);
	QLineEdit *pLineEdit1 = new QLineEdit;
	strText = _T("过流I段告警");
	pLineEdit1->setText(strText);
	pLineEdit1->setFont(*g_pSttGlobalFont);
	pLineEdit1->setEnabled(false);
	QLineEdit *pLineEdit2 = new QLineEdit;
	strText = _T("过流I段跳闸");
	pLineEdit2->setText(strText);
	pLineEdit2->setFont(*g_pSttGlobalFont);
	pLineEdit2->setEnabled(false);

	QLineEdit *pSetLineEdit = new QLineEdit;
	pSetLineEdit->setObjectName(_T("Setting"));
	pSetLineEdit->setFont(*g_pSttGlobalFont);
	QLineEdit *pSetTimeLineEdit = new QLineEdit;
	pSetTimeLineEdit->setFont(*g_pSttGlobalFont);
	pSetTimeLineEdit->setObjectName(_T("SettingTime"));
	m_pAllLineEditList.append(pSetLineEdit);
	m_pAllLineEditList.append(pSetTimeLineEdit);

	QHBoxLayout *pHBoxLayout1 = new QHBoxLayout;
	pHBoxLayout1->addWidget(pLabel1);
	pHBoxLayout1->addWidget(pLineEdit1);
	pHBoxLayout1->addWidget(pLabel2);
	pHBoxLayout1->addWidget(pLineEdit2);
	pHBoxLayout1->addWidget(pLabel3);
	pHBoxLayout1->addWidget(pSetLineEdit);
	pHBoxLayout1->addWidget(pLabel4);
	pHBoxLayout1->addWidget(pSetTimeLineEdit);


	QLabel *pLabel5 = new QLabel;
	strText = _T("投入:");
	pLabel5->setText(strText);
	pLabel5->setFont(*g_pSttGlobalFont);
	QLineEdit *pLineEdit3 = new QLineEdit;
	strText = _T("励磁涌流");
	pLineEdit3->setText(strText);
	pLineEdit3->setFont(*g_pSttGlobalFont);
	pLineEdit3->setEnabled(false);
	QLabel *pLabel6 = new QLabel;
	strText = _T("二次谐波闭锁系数");
	pLabel6->setText(strText);
	pLabel6->setFont(*g_pSttGlobalFont);
	QLabel *pLabel7 = new QLabel;
	strText = _T("%");
	pLabel7->setText(strText);
	pLabel7->setFont(*g_pSttGlobalFont);
	QLineEdit *pHarm2FactorLineEdit = new QLineEdit;
	pHarm2FactorLineEdit->setFont(*g_pSttGlobalFont);
	pHarm2FactorLineEdit->setObjectName(_T("Harm2Factor"));
	m_pAllLineEditList.append(pHarm2FactorLineEdit);

	QHBoxLayout *pHBoxLayout2 = new QHBoxLayout;
	pHBoxLayout2->addWidget(pLabel5);
	pHBoxLayout2->addWidget(pLineEdit3);
	pHBoxLayout2->addWidget(pLabel6);
	pHBoxLayout2->addWidget(pHarm2FactorLineEdit);
	pHBoxLayout2->addWidget(pLabel7);
	pHBoxLayout2->addStretch(10);


// 	QLabel *pLabel8 = new QLabel;
// 	strText = _T("仪器输出参数设置:");
// 	pLabel8->setText(strText);
// 	pLabel8->setFont(*g_pSttGlobalFont);
// 	QLabel *pLabel9 = new QLabel;
// 	strText = _T("基波电流(A)");
// 	pLabel9->setText(strText);
// 	pLabel9->setFont(*g_pSttGlobalFont);
// 	QLabel *pLabel10 = new QLabel;
// 	strText = _T("二次谐波电流(A)");
// 	pLabel10->setText(strText);
// 	pLabel10->setFont(*g_pSttGlobalFont);
// 
// 	QLineEdit *pBaseLineEdit = new QLineEdit;
// 	pBaseLineEdit->setFont(*g_pSttGlobalFont);
// 	pBaseLineEdit->setObjectName(_T("BaseCur"));
// 	QLineEdit *pHarm2CurLineEdit = new QLineEdit;
// 	pHarm2CurLineEdit->setFont(*g_pSttGlobalFont);
// 	pHarm2CurLineEdit->setObjectName(_T("Harm2Cur"));
// 	m_pAllLineEditList.append(pBaseLineEdit);
// 	m_pAllLineEditList.append(pHarm2CurLineEdit);
// 
// 	QHBoxLayout *pHBoxLayout3 = new QHBoxLayout;
// 	pHBoxLayout3->addWidget(pLabel8);
// 	pHBoxLayout3->addWidget(pLabel9);
// 	pHBoxLayout3->addWidget(pBaseLineEdit);
// 	pHBoxLayout3->addWidget(pLabel10);
// 	pHBoxLayout3->addWidget(pHarm2CurLineEdit);
// 	pHBoxLayout3->addStretch(10);

	QVBoxLayout *pVBoxLayout = new QVBoxLayout(m_pGroupBox);
	pVBoxLayout->addLayout(pHBoxLayout1);
	pVBoxLayout->addLayout(pHBoxLayout2);
	//pVBoxLayout->addLayout(pHBoxLayout3);

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


void QSttMacroParaEditViewProInrushCurWidget::OnViewTestStart()
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

void QSttMacroParaEditViewProInrushCurWidget::OnViewTestStop()
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

void QSttMacroParaEditViewProInrushCurWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue,'f',1));
		m_pInrushCurDataGroup.SetDataValue(strID,fValue);
	}
}


void QSttMacroParaEditViewProInrushCurWidget::slot_GroupBoxtoggled( bool bChecked)
{
	m_pInrushCurDataGroup.SetDataValue(_T("ProInrushCur_Check"),long(bChecked));

}

void QSttMacroParaEditViewProInrushCurWidget::GetLineEditValue(CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',1));
}


BOOL QSttMacroParaEditViewProInrushCurWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pInrushCurDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewProInrushCurWidget::GetDatas( CDataGroup *pParas )
{
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();
	
	m_pInrushCurDataGroup.CopyChildren(pParas);

	//SaveParasXml();
}

void QSttMacroParaEditViewProInrushCurWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pInrushCurDataGroup);	
	}

	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pInrushCurDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}

	CDvmData* pCurData = (CDvmData*)m_pInrushCurDataGroup.FindByID(_T("ProInrushCur_Check"));
	if (pCurData)
	{
		m_pGroupBox->setChecked(CString_To_long(pCurData->m_strValue));
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}


void QSttMacroParaEditViewProInrushCurWidget::SaveParasXml()
{
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_ProInrushCur_Paras.xml");
	m_pInrushCurDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}


void QSttMacroParaEditViewProInrushCurWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewProInrushCurWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pInrushCurDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
}




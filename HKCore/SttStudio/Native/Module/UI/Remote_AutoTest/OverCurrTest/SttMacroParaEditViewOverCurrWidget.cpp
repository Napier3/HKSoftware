#include "SttMacroParaEditViewOverCurrWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>

QSttMacroParaEditViewOverCurrWidget::QSttMacroParaEditViewOverCurrWidget( QWidget *parent /*= 0*/ )
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOverCurrTable = NULL;

	OpenTestTestMngrFile(_T(""));
	OpenBinBoutMapXml();
	InitUI();
	SetDatas(NULL);
}


QSttMacroParaEditViewOverCurrWidget::~QSttMacroParaEditViewOverCurrWidget()
{

}

void QSttMacroParaEditViewOverCurrWidget::InitUI()
{
	CString strText;
	m_pEstimateBtn = new QPushButton;
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	strText = _T("结果评估");
	m_pEstimateBtn->setText(strText);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addStretch();
	pHBoxLayout->addWidget(m_pEstimateBtn);

	m_pOverCurrTable = new QSttMacroParaEditViewOverCurrTable(3,6,this);
	m_pOverCurrTable->setFont(*g_pSttGlobalFont);
	m_pOverCurrTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pOverCurrTable->InitData(&m_pOverCurrDataGroup);


	m_pOverCurrGroupBox = new QSttCheckableGroupBox(this);
	strText = _T("过流保护");
	m_pOverCurrGroupBox->setTitle(strText);
	m_pOverCurrGroupBox->setFont(*g_pSttGlobalFont);
	m_pOverCurrGroupBox->setCheckable(true);
	m_pOverCurrGroupBox->setObjectName(QString::fromUtf8("OverCurr_Check"));
// 	CDvmData* pCurData = (CDvmData*)m_pOverCurrDataGroup.FindByID(_T("OverCurr_Check"));
// 	m_pOverCurrGroupBox->setChecked(CString_To_long(pCurData->m_strValue));

	QVBoxLayout* pTableLayout = new QVBoxLayout;
	pTableLayout->addWidget(m_pOverCurrTable);
	m_pOverCurrGroupBox->setLayout(pTableLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pOverCurrGroupBox);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	

	setFocusPolicy(Qt::StrongFocus);

	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));
	connect(m_pOverCurrGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));

}

BOOL QSttMacroParaEditViewOverCurrWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pOverCurrDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewOverCurrWidget::slot_Estimate()
{
	QOverCurrEstimateDlg dlg(&m_pOverCurrDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}


void QSttMacroParaEditViewOverCurrWidget::slot_GroupBoxtoggled( bool bChecked)
{
	long nValue = 0;
	if (bChecked)
	{
		nValue = 1;
	}
	else
	{
		nValue = 0;
	}
	m_pOverCurrDataGroup.SetDataValue(_T("OverCurr_Check"),nValue);
}


void QSttMacroParaEditViewOverCurrWidget::SaveParasXml()
{	
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_OverCurr_Paras.xml");
	m_pOverCurrDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewOverCurrWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOverCurrGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewOverCurrWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOverCurrGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewOverCurrWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	m_pOverCurrDataGroup.CopyChildren(pParas);

	//SaveParasXml();
}

void QSttMacroParaEditViewOverCurrWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pOverCurrDataGroup);
	}

	CDvmData* pCurData = (CDvmData*)m_pOverCurrDataGroup.FindByID(_T("OverCurr_Check"));
	if (pCurData)
	{
		m_pOverCurrGroupBox->setChecked(CString_To_long(pCurData->m_strValue));
	}


	if (m_pOverCurrTable != NULL)
	{
		m_pOverCurrTable->UpdateTable();
	}
 	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
 	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
 	g_theTestCntrFrame->InitStateMonitor();
 	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewOverCurrWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewOverCurrWidget::UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2)
{
	CString strValue;
	stt_GetDataValueByID(pParas, strID1, strValue);
	if (strValue == _T("0") || strValue == _T("Din_5"))
	{
		strValue = _T("2");
	}
	else if(strValue == _T("1") || strValue == _T("Din_1"))
	{
		strValue = _T("1");
	}
	else if(strValue == _T("2") || strValue == _T("Din_2"))
	{
		strValue = _T("0");
	}
	else 
	{
		strValue = _T("3");
	}

	m_pOverCurrDataGroup.SetDataValue(strID2, strValue);
}

void QSttMacroParaEditViewOverCurrWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pOverCurrDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);

	UpdateDataValue(pParas, _T("BinA"), _T("A"));
	UpdateDataValue(pParas, _T("BinB"), _T("B"));
	UpdateDataValue(pParas, _T("BinC"), _T("C"));
	UpdateDataValue(pParas, _T("BinD"), _T("R"));
	UpdateDataValue(pParas, _T("Bout1"), _T("_B01"));	
	UpdateDataValue(pParas, _T("Bout2"), _T("_B02"));	
	UpdateDataValue(pParas, _T("Bout3"), _T("_B03"));
	UpdateDataValue(pParas, _T("Bout4"), _T("_B04"));	
	UpdateDataValue(pParas, _T("Bout5"), _T("_B05"));	
	UpdateDataValue(pParas, _T("Bout6"), _T("_B06"));
	UpdateDataValue(pParas, _T("Bout7"), _T("_B07"));	
	UpdateDataValue(pParas, _T("Bout8"), _T("_B08"));
}


void QSttMacroParaEditViewOverCurrWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue));
		m_pOverCurrDataGroup.SetDataValue(strID,fValue);
	}
}


QOverCurrEstimateDlg::QOverCurrEstimateDlg( CDataGroup* pParas, QWidget* parent ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 250);

	m_pParas = pParas;
	InitUI();
}

QOverCurrEstimateDlg::~QOverCurrEstimateDlg()
{

}

void QOverCurrEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("过流保护测试");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);

	QGridLayout* pGridLayout = new QGridLayout(pGroupBox);
	strText = _T("过流I段动作时间误差(s)");
	QLabel *pLabel1 = new QLabel;
	pLabel1->setText(strText);
	QLineEdit *pLineEdit1 = new QLineEdit;
	pLineEdit1->setFont(*g_pSttGlobalFont);
	pLineEdit1->setObjectName(QString::fromUtf8("Ttrip1_AbsErr"));
	GetLineEditValue(pLineEdit1,_T("Ttrip1_AbsErr"));
	pLineEdit1->setFont(*g_pSttGlobalFont);

	strText = _T("过流II段动作时间误差(s)");
	QLabel *pLabel2 = new QLabel;
	pLabel2->setText(strText);
	QLineEdit *pLineEdit2= new QLineEdit;
	pLineEdit2->setObjectName(QString::fromUtf8("Ttrip2_AbsErr"));
	pLineEdit2->setFont(*g_pSttGlobalFont);
	GetLineEditValue(pLineEdit2,_T("Ttrip2_AbsErr"));
	pLineEdit2->setFont(*g_pSttGlobalFont);

	strText = _T("过流III段动作时间误差(s)");
	QLabel *pLabel3 = new QLabel;
	pLabel3->setText(strText);
	QLineEdit *pLineEdit3 = new QLineEdit;
	pLineEdit3->setFont(*g_pSttGlobalFont);
	pLineEdit3->setObjectName(QString::fromUtf8("Ttrip3_AbsErr"));
	GetLineEditValue(pLineEdit3,_T("Ttrip3_AbsErr"));
	pLineEdit3->setFont(*g_pSttGlobalFont);

	pGridLayout->addWidget(pLabel1,0,0,1,1);
	pGridLayout->addWidget(pLineEdit1,0,1,1,1);
	pGridLayout->addWidget(pLabel2,1,0,1,1);
	pGridLayout->addWidget(pLineEdit2,1,1,1,1);
	pGridLayout->addWidget(pLabel3,2,0,1,1);
	pGridLayout->addWidget(pLineEdit3,2,1,1,1);


	QPushButton* pOKBtn = new QPushButton(this);
	strText = _T("确定");
	pOKBtn->setFont(*g_pSttGlobalFont);
	pOKBtn->setText(strText);
	QPushButton* pCancelBtn = new QPushButton(this);
	strText = _T("取消");
	pCancelBtn->setFont(*g_pSttGlobalFont);
	pCancelBtn->setText(strText);
	QHBoxLayout* pOkCancel_HBoxLayout = new QHBoxLayout;
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->addWidget(pOKBtn);
	pOkCancel_HBoxLayout->addSpacing(10);
	pOkCancel_HBoxLayout->addWidget(pCancelBtn);
	pOkCancel_HBoxLayout->addStretch();
	pOkCancel_HBoxLayout->setDirection(QBoxLayout::LeftToRight);

	QVBoxLayout* pMainVLayout = new QVBoxLayout(this);
	pMainVLayout->addWidget(pGroupBox);
	pMainVLayout->addLayout(pOkCancel_HBoxLayout);
	setLayout(pMainVLayout);
	setFocusPolicy(Qt::StrongFocus);

	m_pAllLineEditList.append(pLineEdit1);
	m_pAllLineEditList.append(pLineEdit2);
	m_pAllLineEditList.append(pLineEdit3);
	connect(pLineEdit1, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pLineEdit2, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pLineEdit3, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QOverCurrEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	CString strValue = pCurData->m_strValue;
	float fValue = strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}



void QOverCurrEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Ttrip1_AbsErr"),m_pAllLineEditList[0]->text().toFloat());
	m_pParas->SetDataValue(_T("Ttrip2_AbsErr"),m_pAllLineEditList[1]->text().toFloat());
	m_pParas->SetDataValue(_T("Ttrip3_AbsErr"),m_pAllLineEditList[2]->text().toFloat());
	close();	
}

void QOverCurrEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QOverCurrEstimateDlg::slot_EditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,200,fValue);
		pLineEdit->setText(QString::number(fValue,'f',3));
	}
}

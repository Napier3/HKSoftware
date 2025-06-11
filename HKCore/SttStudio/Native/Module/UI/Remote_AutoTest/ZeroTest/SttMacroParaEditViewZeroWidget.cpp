#include "SttMacroParaEditViewZeroWidget.h"
#include "../../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QGridLayout>


QSttMacroParaEditViewZeroWidget::QSttMacroParaEditViewZeroWidget( QWidget *parent /*= 0*/ )
{
	g_pTheSttTestApp->IinitGbWzdAiTool();

	m_pEstimateBtn = NULL;
	m_pZeroTable = NULL;
	OpenTestTestMngrFile(_T(""));
	OpenBinBoutMapXml();
	InitUI();
	SetDatas(NULL);
}


QSttMacroParaEditViewZeroWidget::~QSttMacroParaEditViewZeroWidget()
{

}

void QSttMacroParaEditViewZeroWidget::InitUI()
{
	CString strText;
	m_pEstimateBtn = new QPushButton;
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	strText = _T("结果评估");
	m_pEstimateBtn->setText(strText);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addStretch();
	pHBoxLayout->addWidget(m_pEstimateBtn);

	m_pZeroTable = new QSttMacroParaEditViewZeroTable(2,6,this);
	m_pZeroTable->setFont(*g_pSttGlobalFont);
	m_pZeroTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pZeroTable->InitData(&m_pZeroDataGroup);


	m_pZeroGroupBox = new QSttCheckableGroupBox(this);
	strText = _T("零序保护");
	m_pZeroGroupBox->setTitle(strText);
	m_pZeroGroupBox->setFont(*g_pSttGlobalFont);
	m_pZeroGroupBox->setCheckable(true);
	m_pZeroGroupBox->setObjectName(QString::fromUtf8("Zero_Check"));
// 	CDvmData* pCurData = (CDvmData*)m_pZeroDataGroup.FindByID(_T("Zero_Check"));
// 	m_pZeroGroupBox->setChecked(CString_To_long(pCurData->m_strValue));

	QVBoxLayout* pTableLayout = new QVBoxLayout;
	pTableLayout->addWidget(m_pZeroTable);
	m_pZeroGroupBox->setLayout(pTableLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pZeroGroupBox);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	

	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));
	connect(m_pZeroGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
}

BOOL QSttMacroParaEditViewZeroWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pZeroDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewZeroWidget::slot_Estimate()
{
	QZeroEstimateDlg dlg(&m_pZeroDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}


void QSttMacroParaEditViewZeroWidget::slot_GroupBoxtoggled( bool bChecked)
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
	m_pZeroDataGroup.SetDataValue(_T("Zero_Check"),nValue);
}



void QSttMacroParaEditViewZeroWidget::SaveParasXml()
{
// 	m_pZeroDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
// 	m_pZeroDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
// 	m_pZeroDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
// 	m_pZeroDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);


	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_Zero_Paras.xml");
	m_pZeroDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewZeroWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pZeroGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewZeroWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pZeroGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewZeroWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	m_pZeroDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewZeroWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pZeroDataGroup);
	}

	CDvmData* pCurData = (CDvmData*)m_pZeroDataGroup.FindByID(_T("Zero_Check"));
	if (pCurData)
	{
		m_pZeroGroupBox->setChecked(CString_To_long(pCurData->m_strValue));
	}

	if (m_pZeroTable != NULL)
	{
		m_pZeroTable->UpdateTable();
	}
 	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
 	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
 	g_theTestCntrFrame->InitStateMonitor();
 	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewZeroWidget::OpenBinBoutMapXml()
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


void QSttMacroParaEditViewZeroWidget::UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2)
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
		CString strBinValue,strBinIndex;
		if (strID2 == _T("A"))strBinIndex = _T("0");
		else if (strID2 == _T("B"))strBinIndex = _T("1");
		else if (strID2 == _T("C"))strBinIndex = _T("2");
		else if (strID2 == _T("R"))strBinIndex = _T("3");
		strBinValue.Format(_T("ActBin_%s$1"),strBinIndex.GetString());
		m_pZeroDataGroup.SetDataValue(_T("TtripEnd_Bin"),strBinValue);
	}
	else if(strValue == _T("2"))
	{
		strValue = _T("0");
	}

	m_pZeroDataGroup.SetDataValue(strID2, strValue);
}

void QSttMacroParaEditViewZeroWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pZeroDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);

	UpdateDataValue(pParas, _T("BinA"), _T("A"));
	UpdateDataValue(pParas, _T("BinB"), _T("B"));
	UpdateDataValue(pParas, _T("BinC"), _T("C"));
	UpdateDataValue(pParas, _T("BinD"), _T("R"));
}


BOOL QSttMacroParaEditViewZeroWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	CDvmValue *pDvmValue = NULL;
	CDvmValues *pDvmValues = pReport->m_pValues;
	CString strValue;
	stt_GetDataValueByID(&m_pZeroDataGroup, _T("ISetingZone1"), strValue);
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("零序1段定值");
	pDvmValue->m_strID = _T("ISetingZone1");
	pDvmValue->m_strValue = strValue;
	pDvmValues->AddNewChild(pDvmValue);


	stt_GetDataValueByID(&m_pZeroDataGroup, _T("ISetingZone2"), strValue);
	pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("零序2段定值");
	pDvmValue->m_strID = _T("ISetingZone2");
	pDvmValue->m_strValue = strValue;
	pDvmValues->AddNewChild(pDvmValue);
	return TRUE;
}

QZeroEstimateDlg::QZeroEstimateDlg( CDataGroup* pParas, QWidget* parent ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 250);

	m_pParas = pParas;
	InitUI();
}

QZeroEstimateDlg::~QZeroEstimateDlg()
{

}

void QZeroEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("零序保护测试");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);

	QGridLayout* pGridLayout = new QGridLayout(pGroupBox);
	strText = _T("零序I段动作时间误差(s)");
	QLabel *pLabel1 = new QLabel;
	pLabel1->setText(strText);
	QLineEdit *pLineEdit1 = new QLineEdit;
	pLineEdit1->setObjectName(QString::fromUtf8("Ttrip1_AbsErr"));
	GetLineEditValue(pLineEdit1,_T("Ttrip1_AbsErr"));
	pLineEdit1->setFont(*g_pSttGlobalFont);

	strText = _T("零序II段动作时间误差(s)");
	QLabel *pLabel2 = new QLabel;
	pLabel2->setText(strText);
	QLineEdit *pLineEdit2= new QLineEdit;
	pLineEdit2->setObjectName(QString::fromUtf8("Ttrip2_AbsErr"));
	GetLineEditValue(pLineEdit2,_T("Ttrip2_AbsErr"));
	pLineEdit2->setFont(*g_pSttGlobalFont);

	pGridLayout->addWidget(pLabel1,0,0,1,1);
	pGridLayout->addWidget(pLineEdit1,0,1,1,1);
	pGridLayout->addWidget(pLabel2,1,0,1,1);
	pGridLayout->addWidget(pLineEdit2,1,1,1,1);
	

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

	pLineEdit1->setFont(*g_pSttGlobalFont);
	pLineEdit2->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(pLineEdit1);
	m_pAllLineEditList.append(pLineEdit2);

	connect(pLineEdit1, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pLineEdit2, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QZeroEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',2));
}


void QZeroEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Ttrip1_AbsErr"),m_pAllLineEditList[0]->text().toFloat());
	m_pParas->SetDataValue(_T("Ttrip2_AbsErr"),m_pAllLineEditList[1]->text().toFloat());
	close();
}

void QZeroEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QZeroEstimateDlg::slot_EditFinished()
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

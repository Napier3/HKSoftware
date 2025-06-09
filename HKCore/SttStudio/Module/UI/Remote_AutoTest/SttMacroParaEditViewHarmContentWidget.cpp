#include "SttMacroParaEditViewHarmContentWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewHarmContentWidget::QSttMacroParaEditViewHarmContentWidget( QWidget *parent /*= 0*/ )
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pHarmTabWidget = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewHarmContentWidget::~QSttMacroParaEditViewHarmContentWidget()
{

}

void QSttMacroParaEditViewHarmContentWidget::InitUI()
{
	m_pHarmTabWidget = new QTableWidget(7, 11); 
	m_pHarmTabWidget->verticalHeader()->setVisible(false);
	m_pHarmTabWidget->horizontalHeader()->setVisible(false);
	m_pHarmTabWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pHarmTabWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pHarmTabWidget->setFont(*g_pSttGlobalFont);


	CString strText;
	QTableWidgetItem *pItem = NULL;
	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("输入量");
	pItem->setText(strText);
	m_pHarmTabWidget->setItem(0, 0, pItem);
	m_pHarmTabWidget->setSpan(0, 0, 1, 2);

	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("谐波(次)");
	pItem->setText(strText);
	m_pHarmTabWidget->setItem(0, 2, pItem);
	m_pHarmTabWidget->setSpan(0, 2, 1, 9);

	InitTable(m_pHarmTabWidget);
	
	m_pHarmTabWidget->setSpan(1, 0, 1, 2);
	m_pHarmTabWidget->setSpan(2, 0, 1, 2);

	m_pHarmTabWidget->setColumnWidth(1, 100); 


	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("有功\n功率");
	pItem->setText(strText);
	m_pHarmTabWidget->setItem(3, 0, pItem);
	m_pHarmTabWidget->setSpan(3, 0, 2, 1);


	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("无功\n功率");
	pItem->setText(strText);
	m_pHarmTabWidget->setItem(5, 0, pItem);
	m_pHarmTabWidget->setSpan(5, 0, 2, 1);


	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
// 	CDvmData* pCurData = (CDvmData*)m_pHarmDataGroup.FindByID(_T("OutputTime"));
// 	m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	m_pEstimateBtn = new QPushButton;
	strText = _T("结果评估");
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	m_pEstimateBtn->setText(strText);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addWidget(pOutPutLabel);
	pHBoxLayout->addWidget(m_pOutPutTimeEdit);
	pHBoxLayout->addStretch(10);
	pHBoxLayout->addWidget(m_pEstimateBtn);

	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(m_pHarmTabWidget);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

	OpenBinBoutMapXml();
	connect(m_pOutPutTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));

	//测试要求暂时隐藏
	pOutPutLabel->hide();
	m_pOutPutTimeEdit->hide();
}

void QSttMacroParaEditViewHarmContentWidget::InitTable(QTableWidget *pTabWidget)
{
	CString strText,strID,strObjectName;
	QStringList oList;
	oList << _T("基波")<< _T("3")<< _T("5")<< _T("7")<< _T("8")<< _T("9")<< _T("11")<< _T("12")<< _T("13");
	for (int row = 1; row < pTabWidget->rowCount(); row++) 
	{
		for (int col = 0; col < pTabWidget->columnCount(); col++) 
		{	
			QSttCheckBox *pCheckBox = new QSttCheckBox();
			pCheckBox->setFont(*g_pSttGlobalFont);
			if (col == 0)
			{
				if (row == 1)
				{
					strText = _T("电压");
					strID = _T("Vol_Check");
				}
				else if (row == 2)
				{
					strID = _T("Curr_Check");
					strText = _T("电流");
				}
				else
				{
					continue;
				}
			}
			else if (col == 1)
			{
				if (row == 3 || row == 5)
				{
					strText = _T("谐波\n电压");
					strID = (row == 3) ? _T("P_Vol_Check") : _T("Q_Vol_Check");

				}
				else if (row == 4 || row == 6)
				{
					strText = _T("谐波\n电流");
					strID = (row == 4) ? _T("P_Curr_Check") : _T("Q_Curr_Check");
				}
				else
				{
					continue;
				}
			}
			else
			{
				if (col - 2 < oList.size())
				{
					strText = oList.at(col - 2);
				}
				if(row == 1)
				{
					strObjectName = _T("Vol_");
				}
				else if (row == 2)
				{
					strObjectName = _T("Curr_");
				}
				else if (row == 3)
				{
					strObjectName = _T("P_Vol_");
				}
				else if (row == 4)
				{
					strObjectName = _T("P_Curr_");
				}
				else if (row == 5)
				{
					strObjectName = _T("Q_Vol_");
				}
				else if (row == 6)
				{
					strObjectName = _T("Q_Curr_");
				}
				if (col == 2)
				{
					if (strObjectName.contains("Vol"))
					{
						strID = _T("U0");
					}
					else
					{
						strID = _T("I0");
					}
					strID = strObjectName + strID + _T("_Check");
				}
				else
				{
					if (col - 3 < oList.size())
					{
						strID = _T("harm") + oList.at(col - 2);
						strID = strObjectName + strID + _T("_Check");
					}
				}
			}
			
			pCheckBox->setText(strText);
			pCheckBox->setObjectName(strID);
// 			GetCheckBoxValue(pCheckBox,strID);
			if (strID.contains("U0") || strID.contains("I0"))
			{
				pCheckBox->setEnabled(false);
				pCheckBox->setChecked(true);
				m_pHarmDataGroup.SetDataValue(strID,(long)1);	
			}
			else
			{
				m_pAllCheckBoxList.append(pCheckBox);
				connect(pCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
			}
			QHBoxLayout *pLayout = new QHBoxLayout();
			pLayout->setAlignment(Qt::AlignCenter);
			pLayout->addWidget(pCheckBox);
			QWidget *pWidget = new QWidget();
			pWidget->setLayout(pLayout);
			pTabWidget->setCellWidget(row, col, pWidget);
		}
	}

	UpdateHarmCheckbox();
}

void QSttMacroParaEditViewHarmContentWidget::UpdateHarmCheckbox()
{
	QSttCheckBox* pCheckBox = NULL;
	pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("Vol_Check"));//开始测试一次后，勾选框变成灰化状态无法修改
	pCheckBox->setDisabled(false);
	UpdateHarmCheckbox(1,pCheckBox->isChecked());
	pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("Curr_Check"));
	pCheckBox->setDisabled(false);
	UpdateHarmCheckbox(2,pCheckBox->isChecked());
	pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("P_Vol_Check"));
	pCheckBox->setDisabled(false);
	UpdateHarmCheckbox(3,pCheckBox->isChecked());
	pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("P_Curr_Check"));
	pCheckBox->setDisabled(false);
	UpdateHarmCheckbox(4,pCheckBox->isChecked());
	pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("Q_Vol_Check"));
	pCheckBox->setDisabled(false);
	UpdateHarmCheckbox(5,pCheckBox->isChecked());
	pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("Q_Curr_Check"));
	pCheckBox->setDisabled(false);
	UpdateHarmCheckbox(6,pCheckBox->isChecked());
}

void QSttMacroParaEditViewHarmContentWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewHarmContentWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pHarmDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}
	long nPhaseNum = 0;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhaseNum);
	m_pHarmDataGroup.SetDataValue(_T("Phase_Number"),nPhaseNum);
}
BOOL QSttMacroParaEditViewHarmContentWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	long nPhase_Number;
	stt_GetDataValueByID(&m_pHarmDataGroup, _T("Phase_Number"), nPhase_Number);

	CDvmValues *pDvmValues = pReport->m_pValues;
	CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;
	if (pRptDvmDataset == NULL)
	{
		return FALSE;
	}
	POS pos = pRptDvmDataset->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	CDvmValue *pDvmValue = NULL;
	while(pos)
	{
		pCurrData = (CDvmData*)pRptDvmDataset->GetNext(pos); 

		if (pCurrData == NULL )
		{
			continue;
		}
		if (pCurrData->m_strID == _T("Ua") || pCurrData->m_strID == _T("Ub") || pCurrData->m_strID == _T("Uc") ||
			pCurrData->m_strID == _T("Ia") || pCurrData->m_strID == _T("Ib") || pCurrData->m_strID == _T("Ic") ||
			pCurrData->m_strID == _T("P") || pCurrData->m_strID == _T("Q"))
		{
			if (nPhase_Number == 2 && pCurrData->m_strID == _T("Ub"))
			{
				pCurrData->m_strValue = _T("--");
			}
			pDvmValue = new CDvmValue;
			pDvmValue->m_strID = pCurrData->m_strID;
			pDvmValue->m_strValue = pCurrData->m_strValue;
			pDvmValues->AddNewChild(pDvmValue);
		}
	}

	if (nPhase_Number == 2)
	{
		POS posValue = pDvmValues->GetHeadPosition();
		while(posValue)
		{
			pCurrData = (CDvmData*)pDvmValues->GetNext(posValue); 
			if (pCurrData && pCurrData->m_strID == _T("U2"))
			{
				pCurrData->m_strValue = _T("--");
				break;
			}
		}
	}

	return TRUE;
}

void QSttMacroParaEditViewHarmContentWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		pCheckBox->setDisabled(true);
	}

	g_theTestCntrFrame->ClearInfoWidget();
// 	g_theTestCntrFrame->StartStateMonitor();
// 	g_theTestCntrFrame->StartVectorWidget();
// 	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewHarmContentWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);

// 	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
// 	{
// 		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
// 		pCheckBox->setDisabled(false);
// 	}
	UpdateHarmCheckbox();
}


void QSttMacroParaEditViewHarmContentWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pHarmDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewHarmContentWidget::SetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pHarmDataGroup);	
	}
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pHarmDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}

	CDvmData* pCurData = (CDvmData*)m_pHarmDataGroup.FindByID(_T("OutputTime"));
	if (pCurData)
	{
		m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	}

// 	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
// 	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
// 	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewHarmContentWidget::GetCheckBoxValue( CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pCheckBox->setChecked(true);;
	}
	else
	{
		pCheckBox->setChecked(false);;
	}
}

BOOL QSttMacroParaEditViewHarmContentWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pHarmDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewHarmContentWidget::slot_Estimate()
{
	QHarmContentEstimateDlg dlg(&m_pHarmDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewHarmContentWidget::slot_CheckBoxStateChanged( int nState)
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}
	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pHarmDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pHarmDataGroup.SetDataValue(strID,(long)0);
	}

	UpdateHarmCheckbox();

}

void QSttMacroParaEditViewHarmContentWidget::UpdateHarmCheckbox(int row,bool bChecked )
{
	if (m_pHarmTabWidget == NULL)
	{
		return;
	}
	
	for (int col = 2; col < m_pHarmTabWidget->columnCount(); ++col) 
	{
		QWidget *cellWidget = m_pHarmTabWidget->cellWidget(row, col);
		if (cellWidget) 
		{
			QHBoxLayout *pLayout = qobject_cast<QHBoxLayout *>(cellWidget->layout());
			if (pLayout) 
			{
				QSttCheckBox *pCheckBox = qobject_cast<QSttCheckBox *>(pLayout->itemAt(0)->widget());
				if (pCheckBox) 
				{
					CString strID = pCheckBox->objectName();
					if (!strID.contains("U0") && !strID.contains("I0"))
					{
						pCheckBox->setEnabled(bChecked);
					}
				}
			}
		}
	}
}


void QSttMacroParaEditViewHarmContentWidget::slot_LineEditFinished()
{
	float fValue = m_pOutPutTimeEdit->text().toFloat();
	fValue = setLimit(0,999,fValue);
	m_pOutPutTimeEdit->setText(QString::number(fValue));
	m_pHarmDataGroup.SetDataValue(_T("OutputTime"),fValue);
}

void QSttMacroParaEditViewHarmContentWidget::SaveParasXml()
{
	m_pHarmDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pHarmDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pHarmDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pHarmDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_HarmContent_Paras.xml");
	m_pHarmDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

QSttCheckBox* QSttMacroParaEditViewHarmContentWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
{
	for (int i = 0; i < checkBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = checkBoxList.at(i);
		if (pCheckBox->objectName() == strID)
		{
			return pCheckBox;
		}
	}
	return NULL;
}



QHarmContentEstimateDlg::QHarmContentEstimateDlg( CDataGroup* pParas, QWidget* parent /*= NULL*/ ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 250);
	m_pValRelLineEdit = NULL;
	m_pPowerRelLineEdit = NULL;
	m_pParas = pParas;
	InitUI();
}

QHarmContentEstimateDlg::~QHarmContentEstimateDlg()
{

}
void QHarmContentEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("谐波影响");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);
	
	QLabel *pLabel = new QLabel;
	strText = _T("电压、电流测量误差(%)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pValRelLineEdit = new QSttLineEdit;
	m_pValRelLineEdit->setFont(*g_pSttGlobalFont);

	QLabel *pLabel1 = new QLabel;
	strText = _T("功率测量误差(%)");
	pLabel1->setFont(*g_pSttGlobalFont);
	pLabel1->setText(strText);
	m_pPowerRelLineEdit = new QSttLineEdit;
	m_pPowerRelLineEdit->setFont(*g_pSttGlobalFont);
	QGridLayout* pGridLayout = new QGridLayout(pGroupBox);
	pGridLayout->addWidget(pLabel,0,0,1,1);
	pGridLayout->addWidget(m_pValRelLineEdit,0,1,1,1);
	pGridLayout->addWidget(pLabel1,1,0,1,1);
	pGridLayout->addWidget(m_pPowerRelLineEdit,1,1,1,1);

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

	m_pValRelLineEdit->setObjectName(QString::fromUtf8("Val_RelErr"));
	GetLineEditValue(m_pValRelLineEdit,_T("Val_RelErr"));
	m_pPowerRelLineEdit->setObjectName(QString::fromUtf8("Power_RelErr"));
	GetLineEditValue(m_pPowerRelLineEdit,_T("Power_RelErr"));

	connect(m_pValRelLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_ValRelEditFinished()));
	connect(m_pPowerRelLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_PowerRelEditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QHarmContentEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Val_RelErr"),m_pValRelLineEdit->text());
	m_pParas->SetDataValue(_T("Power_RelErr"),m_pPowerRelLineEdit->text());

	close();
}

void QHarmContentEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QHarmContentEstimateDlg::slot_ValRelEditFinished()
{
	float fValue = m_pValRelLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pValRelLineEdit->setText(QString::number(fValue,'f',3));
}

void QHarmContentEstimateDlg::slot_PowerRelEditFinished()
{
	float fValue = m_pPowerRelLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pPowerRelLineEdit->setText(QString::number(fValue,'f',3));
}

void QHarmContentEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}
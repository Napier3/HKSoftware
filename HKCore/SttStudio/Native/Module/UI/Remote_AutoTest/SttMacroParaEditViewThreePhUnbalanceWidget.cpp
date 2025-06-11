#include "SttMacroParaEditViewThreePhUnbalanceWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewThreePhUnbalanceWidget::QSttMacroParaEditViewThreePhUnbalanceWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pCurTabWidget = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewThreePhUnbalanceWidget::~QSttMacroParaEditViewThreePhUnbalanceWidget()
{
// 	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
// 	{
// 		delete m_pAllCheckBoxList.at(i); 
// 	}
// 	m_pAllCheckBoxList.clear();
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::InitUI()
{
	CString strText,strID;

	m_pCurTabWidget = new QTableWidget(5, 4); 
	m_pCurTabWidget->verticalHeader()->setVisible(false);
	m_pCurTabWidget->horizontalHeader()->setVisible(false);
	m_pCurTabWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pCurTabWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pCurTabWidget->setFont(*g_pSttGlobalFont);

	QTableWidgetItem *pItem = NULL;
	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("模拟量");
	pItem->setText(strText);
	m_pCurTabWidget->setItem(0, 0, pItem);

	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("输入电流(A)");
	pItem->setText(strText);
	m_pCurTabWidget->setItem(0, 1, pItem);
	m_pCurTabWidget->setSpan(0, 1, 1, 3);
	m_pCurTabWidget->setSpan(1, 0, 2, 1);
	m_pCurTabWidget->setSpan(3, 0, 2, 1);


	QStringList oList1,oList2,oListId1,oListId2;
	oList1 << _T("Ia=Ib=Ic=0.5In")<< _T("Ia=0 Ib=Ic=0.75In")<< _T("Ib=0 Ia=Ic=0.75In");
	oList2 << _T("Ic=0 Ia=Ib=0.75In")<< _T("Ia=In Ib=0.5In Ic=0")<< _T("Ia=0 Ib=0.5In Ic=In");
	
	oListId1 << _T("I050_Check")<< _T("IbIc075_Check")<< _T("IaIc075_Check");
	oListId2 << _T("IaIb075_Check")<< _T("IaIn_Check")<< _T("IcIn_Check");

	for (int row = 1; row < m_pCurTabWidget->rowCount(); row++) 
	{
		for (int col = 0; col < m_pCurTabWidget->columnCount(); col++) 
		{	
			if ((row == 2 && col == 0) || (row == 4 && col == 0))
			{
				continue;
			}

			QSttCheckBox *pCheckBox = new QSttCheckBox();
			pCheckBox->setFont(*g_pSttGlobalFont);

			if (col == 0)
			{
				if (row == 1) 
				{
					strText = _T("有功功率");
					strID = _T("P_Check");
				}
				else if(row == 3)
				{
					strText = _T("无功功率");
					strID = _T("Q_Check");
				}
				else
				{
					continue;
				}
			}
			else
			{
				if (row % 2 == 1 ) 
				{
					if (col - 1 < oList1.size())
					{
						strText = oList1.at(col - 1);
						strID = (row == 1 ? _T("P") : _T("Q")) + oListId1.at(col - 1);
					}
				}
				else
				{
					if (col - 1 < oList2.size())
					{
						strText = oList2.at(col - 1);
						strID = (row == 2 ? _T("P") : _T("Q")) + oListId2.at(col - 1);
					}
				}
			}

		
			pCheckBox->setText(strText);
			pCheckBox->setObjectName(strID);
			//GetCheckBoxValue(pCheckBox,strID);
			if(strID == _T("PI050_Check") || strID == _T("QI050_Check"))
			{
				pCheckBox->setEnabled(false);
				pCheckBox->setChecked(true);
				m_pThreePhDataGroup.SetDataValue(strID,(long)1);	
			}
			else
			{
				m_pAllCheckBoxList.append(pCheckBox);
				connect(pCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
			}

			QHBoxLayout *pLayout = new QHBoxLayout();
			pLayout->addSpacing(20);
			pLayout->addWidget(pCheckBox);
			QWidget *pWidget = new QWidget();
			pWidget->setLayout(pLayout);
			m_pCurTabWidget->setCellWidget(row, col, pWidget);
		}
	}


	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
// 	CDvmData* pCurData = (CDvmData*)m_pThreePhDataGroup.FindByID(_T("OutputTime"));
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

	
	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("不平衡电流对三相有功功率和无功功率引起的改变量");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);


	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pCurTabWidget);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(m_pGroupBox);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);
	
	OpenBinBoutMapXml();
	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	connect(m_pOutPutTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));


	//测试要求暂时隐藏
	pOutPutLabel->hide();
	m_pOutPutTimeEdit->hide();
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::SaveParasXml()
{
	
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_ThreePhUnbalance_Paras.xml");
	m_pThreePhDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}


void QSttMacroParaEditViewThreePhUnbalanceWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
	//UpdateCheckboxEnabled(_T("Curr_Check"));
	//UpdateCheckboxEnabled(_T("P_Check"));
	//UpdateCheckboxEnabled(_T("Q_Check"));
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();

	m_pThreePhDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pThreePhDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pThreePhDataGroup.CopyChildren(pParas);
	//SaveParasXml();
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::SetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pThreePhDataGroup);	
	}
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pThreePhDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}
	CDvmData* pCurData = NULL;
	pCurData = (CDvmData*)m_pThreePhDataGroup.FindByID(_T("Curr_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	pCurData = (CDvmData*)m_pThreePhDataGroup.FindByID(_T("OutputTime"));
	if (pCurData)
	{
		m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	}

	
	UpdateCheckboxEnabled(_T("P_Check"));
	UpdateCheckboxEnabled(_T("Q_Check"));
	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::GetCheckBoxValue(  CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pThreePhDataGroup.*/pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pCheckBox->setChecked(true);
	}
	else
	{
		pCheckBox->setChecked(false);
	}
}

BOOL QSttMacroParaEditViewThreePhUnbalanceWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pThreePhDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::slot_Estimate()
{
	QThreePhUnbalanceEstimateDlg dlg(&m_pThreePhDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::slot_CheckBoxStateChanged( int nState)
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}
	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pThreePhDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pThreePhDataGroup.SetDataValue(strID,(long)0);
	}


	UpdateCheckboxEnabled(strID);
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pThreePhDataGroup.SetDataValue(_T("Curr_Check"),(long)checked);	
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::UpdateCheckboxEnabled(CString strID)
{
	QSttCheckBox* pCheckBox = NULL;
// 	if (strID == _T("Curr_Check"))
// 	{
// 		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
// 		setTableWidgetEnabled(m_pCurTabWidget,pCheckBox->isChecked());
// 	}
	if (strID == _T("P_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateFrequencyCheckbox(m_pCurTabWidget,1,pCheckBox->isChecked());
		UpdateFrequencyCheckbox(m_pCurTabWidget,2,pCheckBox->isChecked());
	}
	else if (strID == _T("Q_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateFrequencyCheckbox(m_pCurTabWidget,3,pCheckBox->isChecked());
		UpdateFrequencyCheckbox(m_pCurTabWidget,4,pCheckBox->isChecked());
	}
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewThreePhUnbalanceWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pThreePhDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}
	long nPhaseNum = 0;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhaseNum);
	m_pThreePhDataGroup.SetDataValue(_T("Phase_Number"),nPhaseNum);
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::slot_LineEditFinished()
{
	float fValue = m_pOutPutTimeEdit->text().toFloat();
	fValue = setLimit(0,999,fValue);
	m_pOutPutTimeEdit->setText(QString::number(fValue));
	m_pThreePhDataGroup.SetDataValue(_T("OutputTime"),fValue);
}

void QSttMacroParaEditViewThreePhUnbalanceWidget::setTableWidgetEnabled( QTableWidget *pTableWidget, bool enabled )
{
	for (int row = 0; row < pTableWidget->rowCount(); ++row) 
	{
		for (int col = 0; col < pTableWidget->columnCount(); ++col) 
		{
			QWidget *pWidget = pTableWidget->cellWidget(row, col);
			if (pWidget) 
			{
				QHBoxLayout *pLayout = qobject_cast<QHBoxLayout *>(pWidget->layout());
				if (pLayout)
				{
					QSttCheckBox *pCheckBox = qobject_cast<QSttCheckBox *>(pLayout->itemAt(1)->widget());
					if (pCheckBox) 
					{
						if (col == 0) 
						{
							pCheckBox->setChecked(enabled);
							pCheckBox->setEnabled(enabled);
						} 
						else 
						{
							pCheckBox->setEnabled(enabled);
						}
					}
				}
			}
		}
	}	
}


void QSttMacroParaEditViewThreePhUnbalanceWidget::UpdateFrequencyCheckbox( QTableWidget *pTableWidget,int row,bool bChecked )
{
	for (int col = 1; col < pTableWidget->columnCount(); ++col) 
	{
		QWidget *cellWidget = pTableWidget->cellWidget(row, col);
		if (cellWidget) 
		{
			QHBoxLayout *pLayout = qobject_cast<QHBoxLayout *>(cellWidget->layout());
			if (pLayout) 
			{
				QCheckBox *pCheckBox = qobject_cast<QCheckBox *>(pLayout->itemAt(1)->widget());
				if (pCheckBox) 
				{
					if (pCheckBox->objectName() != _T("PI050_Check") && pCheckBox->objectName() != _T("QI050_Check"))
					{
						pCheckBox->setEnabled(bChecked);
					}
				}
			}
		}
	}
}

QSttCheckBox* QSttMacroParaEditViewThreePhUnbalanceWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
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
BOOL QSttMacroParaEditViewThreePhUnbalanceWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
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
		if (pCurrData->m_strID == _T("P") || pCurrData->m_strID == _T("Q"))
		{
			pDvmValue = new CDvmValue;
			pDvmValue->m_strID = pCurrData->m_strID;
			pDvmValue->m_strValue = pCurrData->m_strValue;
			pDvmValues->AddNewChild(pDvmValue);
		}
	}
	return TRUE;
}



QThreePhUnbalanceEstimateDlg::QThreePhUnbalanceEstimateDlg( CDataGroup* pParas, QWidget* parent /*= NULL*/ ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 150);
	m_pPowerRelErrLineEdit = NULL;
	m_pParas = pParas;
	InitUI();
}

QThreePhUnbalanceEstimateDlg::~QThreePhUnbalanceEstimateDlg()
{

}
void QThreePhUnbalanceEstimateDlg::InitUI()
{
	CString strText;

	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("功率因数基本误差");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);
	QLabel *pLabel = new QLabel;
	strText = _T("功率变差限(%)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pPowerRelErrLineEdit = new QSttLineEdit;
	m_pPowerRelErrLineEdit->setFont(*g_pSttGlobalFont);

	QHBoxLayout* pHLayout = new QHBoxLayout(pGroupBox);
	pHLayout->addStretch();
	pHLayout->addWidget(pLabel);
	pHLayout->addWidget(m_pPowerRelErrLineEdit);
	pHLayout->addStretch();


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

	m_pPowerRelErrLineEdit->setObjectName(QString::fromUtf8("Curr_Power_RelErr"));
	GetLineEditValue(m_pPowerRelErrLineEdit,_T("Curr_Power_RelErr"));

	connect(m_pPowerRelErrLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QThreePhUnbalanceEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Curr_Power_RelErr"),m_pPowerRelErrLineEdit->text());

	close();
}

void QThreePhUnbalanceEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QThreePhUnbalanceEstimateDlg::slot_EditFinished()
{
	float fValue = m_pPowerRelErrLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pPowerRelErrLineEdit->setText(QString::number(fValue,'f',3));
}

void QThreePhUnbalanceEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}



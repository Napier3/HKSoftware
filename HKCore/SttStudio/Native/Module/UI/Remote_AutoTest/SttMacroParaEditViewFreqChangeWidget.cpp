#include "SttMacroParaEditViewFreqChangeWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewFreqChangeWidget::QSttMacroParaEditViewFreqChangeWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pFreqTabWidget = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewFreqChangeWidget::~QSttMacroParaEditViewFreqChangeWidget()
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		delete m_pAllCheckBoxList.at(i); 
	}
	m_pAllCheckBoxList.clear();
}

void QSttMacroParaEditViewFreqChangeWidget::InitUI()
{
	CString strText,strID;
	
	m_pFreqTabWidget = new QTableWidget(4, 4); 
	m_pFreqTabWidget->verticalHeader()->setVisible(false);
	m_pFreqTabWidget->horizontalHeader()->setVisible(false);
    m_pFreqTabWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_pFreqTabWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_pFreqTabWidget->setFont(*g_pSttGlobalFont);

	QTableWidgetItem *pItem = NULL;
	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("频率(Hz)");
	pItem->setText(strText);
	m_pFreqTabWidget->setItem(0, 0, pItem);

	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("模拟量");
	pItem->setText(strText);
	m_pFreqTabWidget->setItem(0, 1, pItem);
	m_pFreqTabWidget->setSpan(0, 1, 1, 3);
	
	QStringList oFrequencyList,oFreIdList,oList,oListId;
	oFrequencyList  << _T("50") << _T("47.5") << _T("52.5");
	oFreIdList << _T("50Hz") << _T("47_5Hz") << _T("52_5Hz");
	oListId << _T("_UnIn") << _T("_P") << _T("_Q");
	oList << _T("额定电压电流")<< _T("有功功率")<< _T("无功功率");
	for (int row = 1; row < m_pFreqTabWidget->rowCount(); row++) 
	{
		for (int col = 0; col < m_pFreqTabWidget->columnCount(); col++) 
		{				
			QSttCheckBox *pCheckBox = new QSttCheckBox();
			pCheckBox->setFont(*g_pSttGlobalFont);
			m_pAllCheckBoxList.append(pCheckBox);

			if (col == 0)
			{
				strText = oFrequencyList.at(row-1);
				strID = oFreIdList.at(row-1) + _T("_Check");
			}
			else
			{
				strText = oList.at(col-1);
				strID = oFreIdList.at(row-1) + oListId.at(col-1) +  _T("_Check");
			}

			pCheckBox->setText(strText);
			pCheckBox->setObjectName(strID);
			//GetCheckBoxValue(pCheckBox,strID);
			connect(pCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));

			QHBoxLayout *pLayout = new QHBoxLayout();
			pLayout->addSpacing(40);
			pLayout->addWidget(pCheckBox);
			QWidget *pWidget = new QWidget();
			pWidget->setLayout(pLayout);
			m_pFreqTabWidget->setCellWidget(row, col, pWidget);


			int nRow = -1;
			if (strID == _T("50Hz_Check"))
			{
				nRow = 1;
			}
			else if (strID == _T("47_5Hz_Check"))
			{
				nRow = 2;
			}
			else if (strID == _T("52_5Hz_Check"))
			{
				nRow = 3;
			}
			if (nRow != -1)
			{
				UpdateFrequencyCheckbox(m_pFreqTabWidget,nRow,pCheckBox->isChecked());
			}
		}
	}


	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
// 	CDvmData* pCurData = (CDvmData*)m_pFreqChangeDataGroup.FindByID(_T("OutputTime"));
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
	strText = _T("输入量频率变化引起的改变量");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);
	

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pFreqTabWidget);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout *pMainLayout = new QVBoxLayout;
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

void QSttMacroParaEditViewFreqChangeWidget::SaveParasXml()
{
// 	m_pFreqChangeDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
// 	m_pFreqChangeDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
// 	m_pFreqChangeDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
// 	m_pFreqChangeDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);
// 
// 	CString strFile;
// 	strFile = _P_GetDBPath();
// 	strFile += _T("atsgen/Remote_FreqChange_Paras.xml");
// 	m_pFreqChangeDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}



void QSttMacroParaEditViewFreqChangeWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewFreqChangeWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewFreqChangeWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();

	m_pFreqChangeDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pFreqChangeDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pFreqChangeDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewFreqChangeWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pFreqChangeDataGroup);
	}
	ASSERT(pParas != NULL);

	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pFreqChangeDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}
	CDvmData* pCurData = NULL;

	pCurData = (CDvmData*)m_pFreqChangeDataGroup.FindByID(_T("Freq_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	pCurData = (CDvmData*)m_pFreqChangeDataGroup.FindByID(_T("OutputTime"));
	if (pCurData)
	{
		m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewFreqChangeWidget::GetCheckBoxValue(CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID )
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

BOOL QSttMacroParaEditViewFreqChangeWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pFreqChangeDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewFreqChangeWidget::slot_Estimate()
{
	QFreqChangeEstimateDlg dlg(&m_pFreqChangeDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewFreqChangeWidget::slot_CheckBoxStateChanged( int nState)
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}
	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pFreqChangeDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pFreqChangeDataGroup.SetDataValue(strID,(long)0);
	}


// 	if (strID == _T("Freq_Check"))
// 	{
// 		setTableWidgetEnabled(m_pFreqTabWidget,nState);
// 	}

	int nRow = -1;
	if (strID == _T("50Hz_Check"))
	{
		nRow = 1;
	}
	else if (strID == _T("47_5Hz_Check"))
	{
		nRow = 2;
	}
	else if (strID == _T("52_5Hz_Check"))
	{
		nRow = 3;
	}
	if (nRow != -1)
	{
		UpdateFrequencyCheckbox(m_pFreqTabWidget,nRow,nState);
	}
}

void QSttMacroParaEditViewFreqChangeWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pFreqChangeDataGroup.SetDataValue(_T("Freq_Check"),(long)checked);	

}

void QSttMacroParaEditViewFreqChangeWidget::slot_LineEditFinished()
{
	float fValue = m_pOutPutTimeEdit->text().toFloat();
	fValue = setLimit(0,999,fValue);
	m_pOutPutTimeEdit->setText(QString::number(fValue));
	m_pFreqChangeDataGroup.SetDataValue(_T("OutputTime"),fValue);
}

void QSttMacroParaEditViewFreqChangeWidget::setTableWidgetEnabled( QTableWidget *pTableWidget, bool enabled )
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


void QSttMacroParaEditViewFreqChangeWidget::UpdateFrequencyCheckbox( QTableWidget *pTableWidget,int row,bool bChecked )
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
					pCheckBox->setEnabled(bChecked);
				}
			}
		}
	}
}

BOOL QSttMacroParaEditViewFreqChangeWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	long nPhase_Number;
	stt_GetDataValueByID(&m_pFreqChangeDataGroup, _T("Phase_Number"), nPhase_Number);

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
		if (pCurrData->m_strID == _T("Ua") || pCurrData->m_strID == _T("Ub") || pCurrData->m_strID == _T("Uc") || pCurrData->m_strID == _T("U0") ||
			pCurrData->m_strID == _T("Ia") || pCurrData->m_strID == _T("Ib") || pCurrData->m_strID == _T("Ic") || pCurrData->m_strID == _T("I0") ||
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


void QSttMacroParaEditViewFreqChangeWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewFreqChangeWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pFreqChangeDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}
	long nPhaseNum = 0;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhaseNum);
	m_pFreqChangeDataGroup.SetDataValue(_T("Phase_Number"),nPhaseNum);
}

QSttCheckBox* QSttMacroParaEditViewFreqChangeWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
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

QFreqChangeEstimateDlg::QFreqChangeEstimateDlg( CDataGroup* pParas, QWidget* parent /*= NULL*/ ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 150);
	m_pParas = pParas;
	InitUI();
}

QFreqChangeEstimateDlg::~QFreqChangeEstimateDlg()
{

}
void QFreqChangeEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("频率基本误差");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);

	QLabel *pLabel = new QLabel;
	strText = _T("电压电流变差限(%)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	QLineEdit *pLineEdit = new QLineEdit;

	QLabel *pLabel2 = new QLabel;
	strText = _T("功率变差限(%)");
	pLabel2->setFont(*g_pSttGlobalFont);
	pLabel2->setText(strText);
	QLineEdit *pLineEdit2 = new QLineEdit;

	QGridLayout* pGridLayout = new QGridLayout(pGroupBox);
	pGridLayout->addWidget(pLabel,0,0,1,1);
	pGridLayout->addWidget(pLineEdit,0,1,1,1);
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
	setFocusPolicy(Qt::StrongFocus);

	pLineEdit->setObjectName(QString::fromUtf8("Freq_Val_RelErr"));
	GetLineEditValue(pLineEdit,_T("Freq_Val_RelErr"));
	pLineEdit2->setObjectName(QString::fromUtf8("Freq_Power_RelErr"));
	GetLineEditValue(pLineEdit2,_T("Freq_Power_RelErr"));

	m_pAllLineEditList.append(pLineEdit);
	m_pAllLineEditList.append(pLineEdit2);
	connect(pLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pLineEdit2, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QFreqChangeEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Freq_Val_RelErr"),m_pAllLineEditList[0]->text().toFloat());
	m_pParas->SetDataValue(_T("Freq_Power_RelErr"),m_pAllLineEditList[1]->text().toFloat());
	close();
}

void QFreqChangeEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QFreqChangeEstimateDlg::slot_EditFinished()
{
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		CString strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,200,fValue);
		pLineEdit->setText(QString::number(fValue,'f',3));
	}
}

void QFreqChangeEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}



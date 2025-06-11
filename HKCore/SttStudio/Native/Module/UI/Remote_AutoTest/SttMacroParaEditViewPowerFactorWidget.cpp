#include "SttMacroParaEditViewPowerFactorWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewPowerFactorWidget::QSttMacroParaEditViewPowerFactorWidget( QWidget *parent /*= 0*/ )
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pPFactorTabWidget = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewPowerFactorWidget::~QSttMacroParaEditViewPowerFactorWidget()
{

}

void QSttMacroParaEditViewPowerFactorWidget::InitUI()
{
	CString strText,strID;
	m_pPFactorTabWidget = new QTableWidget(3, 5); 
	m_pPFactorTabWidget->verticalHeader()->setVisible(false);
	m_pPFactorTabWidget->horizontalHeader()->setVisible(false);
	m_pPFactorTabWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pPFactorTabWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pPFactorTabWidget->setFont(*g_pSttGlobalFont);

	QTableWidgetItem *pItem = NULL;
	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("模拟量");
	pItem->setText(strText);
	m_pPFactorTabWidget->setItem(0, 0, pItem);

	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("功率因数角");
	pItem->setText(strText);
	m_pPFactorTabWidget->setItem(0, 1, pItem);
	m_pPFactorTabWidget->setSpan(0, 1, 1, 4);

	QStringList oPAngleId,oQAngleId,oPAngleName,oQAngleName;
	oPAngleId << _T("P_Angel0_Check")<< _T("P_Angel60_Check")<< _T("P_Angel_60_Check");
	oQAngleId << _T("Q_Angel90_Check")<< _T("Q_Angel30_Check")<< _T("Q_Angel_90_Check")<< _T("Q_Angel_30_Check");

	oPAngleName << _T("Φ=0°")<< _T("Φ=60°")<< _T("Φ=-60°");
	oQAngleName << _T("Φ=90°")<< _T("Φ=30°")<< _T("Φ=-90°")<< _T("Φ=-30°");

	for (int row = 1; row < m_pPFactorTabWidget->rowCount(); row++) 
	{
		for (int col = 0; col < m_pPFactorTabWidget->columnCount(); col++) 
		{				
			QSttCheckBox *pCheckBox = new QSttCheckBox();
			pCheckBox->setFont(*g_pSttGlobalFont);
			if (row == 1)
			{
				if (col == 0)
				{
					strText = _T("有功功率");
					strID = _T("P_Angel_Check");
				}
				else
				{
					if (col - 1 < oPAngleId.size())
					{
						strID = oPAngleId.at(col - 1);
						strText = oPAngleName.at(col - 1);
					}
					else
					{
						
						QTableWidgetItem *item = new QTableWidgetItem();
						item->setFlags(item->flags() & ~Qt::ItemIsSelectable & ~Qt::ItemIsEditable);
						m_pPFactorTabWidget->setItem(row, col, item);
						continue;
					}
				}
			}
			else
			{
				if (col == 0)
				{
					strText = _T("无功功率");
					strID = _T("Q_Angel_Check");
				}
				else
				{
					if (col - 1 < oQAngleId.size())
					{
						strID = oQAngleId.at(col - 1);
						strText = oQAngleName.at(col - 1);
					}
				}
			}

		
			pCheckBox->setText(strText);
			pCheckBox->setObjectName(strID);
// 			GetCheckBoxValue(pCheckBox,strID);
			if (strID == _T("P_Angel0_Check") || strID == _T("Q_Angel90_Check") || strID == _T("Q_Angel_90_Check"))
			{
				pCheckBox->setEnabled(false);
				pCheckBox->setChecked(true);
				m_pPFDataGroup.SetDataValue(strID,(long)1);	
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
			m_pPFactorTabWidget->setCellWidget(row, col, pWidget);
		}
	}

	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
	//CDvmData* pCurData = (CDvmData*)m_pPFDataGroup.FindByID(_T("OutputTime"));
	//m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
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
	strText = _T("功率因数引起的变化量");
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	//GetCheckBoxValue(pPFactor_Check,_T("Factor_Check"));
	
	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pPFactorTabWidget);
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

void QSttMacroParaEditViewPowerFactorWidget::GetCheckBoxValue( CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID )
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

BOOL QSttMacroParaEditViewPowerFactorWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pPFDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewPowerFactorWidget::slot_CheckBoxStateChanged( int nState)
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}
	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pPFDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pPFDataGroup.SetDataValue(strID,(long)0);
	}

// 	if (strID == _T("Factor_Check"))
// 	{
// 		setTableWidgetEnabled(m_pPFactorTabWidget,nState);
// 	}

	int nRow = -1;
	if (strID == _T("P_Angel_Check"))
	{
		nRow = 1;
	}
	else if (strID == _T("Q_Angel_Check"))
	{
		nRow = 2;
	}
	
	if (nRow != -1)
	{
		UpdateCheckbox(m_pPFactorTabWidget,nRow,nState);
	}
}

void QSttMacroParaEditViewPowerFactorWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pPFDataGroup.SetDataValue(_T("Factor_Check"),(long)checked);	
}

void QSttMacroParaEditViewPowerFactorWidget::slot_Estimate()
{
	QPowerFactorEstimateDlg dlg(&m_pPFDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewPowerFactorWidget::slot_LineEditFinished()
{
	float fValue = m_pOutPutTimeEdit->text().toFloat();
	fValue = setLimit(0,999,fValue);
	m_pOutPutTimeEdit->setText(QString::number(fValue));
	m_pPFDataGroup.SetDataValue(_T("OutputTime"),fValue);
}

void QSttMacroParaEditViewPowerFactorWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();

	m_pPFDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pPFDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);

	m_pPFDataGroup.CopyChildren(pParas);

	//SaveParasXml();
}

void QSttMacroParaEditViewPowerFactorWidget::SetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pPFDataGroup);	
	}
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pPFDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}


	CDvmData* pCurData = NULL;
	pCurData = (CDvmData*)m_pPFDataGroup.FindByID(_T("Factor_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	pCurData = (CDvmData*)m_pPFDataGroup.FindByID(_T("OutputTime"));
	if (pCurData)
	{
		m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	}

	QSttCheckBox* pPAngle_Check = FindCheckBoxByID(m_pAllCheckBoxList, _T("P_Angel_Check"));
	UpdateCheckbox(m_pPFactorTabWidget,1,pPAngle_Check->isChecked());
	QSttCheckBox* pQAngle_Check = FindCheckBoxByID(m_pAllCheckBoxList, _T("Q_Angel_Check"));
	UpdateCheckbox(m_pPFactorTabWidget,2,pQAngle_Check->isChecked());
	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewPowerFactorWidget::SaveParasXml()
{
	m_pPFDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pPFDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pPFDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pPFDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_PowerFactor_Paras.xml");
	m_pPFDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewPowerFactorWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewPowerFactorWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewPowerFactorWidget::setTableWidgetEnabled( QTableWidget *pTableWidget, bool enabled )
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

void QSttMacroParaEditViewPowerFactorWidget::UpdateCheckbox( QTableWidget *pTableWidget,int row,bool bChecked )
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
					if (pCheckBox->objectName() != _T("P_Angel0_Check") && pCheckBox->objectName() != _T("Q_Angel90_Check")
						&& pCheckBox->objectName() != _T("Q_Angel_90_Check"))
					{
						pCheckBox->setEnabled(bChecked);
					}
				}
			}
		}
	}
}


QSttCheckBox* QSttMacroParaEditViewPowerFactorWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
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

BOOL QSttMacroParaEditViewPowerFactorWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
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

void QSttMacroParaEditViewPowerFactorWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewPowerFactorWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	long nPhase_Number;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhase_Number);
	m_pPFDataGroup.SetDataValue(_T("Phase_Number"),nPhase_Number);

	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pPFDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}
}

QPowerFactorEstimateDlg::QPowerFactorEstimateDlg( CDataGroup* pParas, QWidget* parent /*= NULL*/ ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 200);
	m_pParas = pParas;
	m_pPowerLineEdit = NULL;
	InitUI();
}

QPowerFactorEstimateDlg::~QPowerFactorEstimateDlg()
{

}
void QPowerFactorEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("功率因数变化引起的改变量");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);

	QLabel *pLabel = new QLabel;
	strText = _T("功率因数功率测量误差(%)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pPowerLineEdit = new QSttLineEdit;
	m_pPowerLineEdit->setFont(*g_pSttGlobalFont);
	m_pPowerLineEdit->setObjectName(QString::fromUtf8("Power_RelErr"));
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(_T("Power_RelErr"));
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	m_pPowerLineEdit->setText(QString::number(fValue,'f',3));


	QGridLayout* pHLayout = new QGridLayout(pGroupBox);
	pHLayout->addWidget(pLabel,0,1,1,1);
	pHLayout->addWidget(m_pPowerLineEdit,0,2,1,1);

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

	connect(m_pPowerLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QPowerFactorEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Power_RelErr"),m_pPowerLineEdit->text());
	close();
}

void QPowerFactorEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QPowerFactorEstimateDlg::slot_EditFinished()
{
	float fValue = m_pPowerLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pPowerLineEdit->setText(QString::number(fValue,'f',3));
}



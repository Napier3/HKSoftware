#include "SttMacroParaEditViewInputVolWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewInputVolWidget::QSttMacroParaEditViewInputVolWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pTabWidget = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewInputVolWidget::~QSttMacroParaEditViewInputVolWidget()
{

}

void QSttMacroParaEditViewInputVolWidget::InitUI()
{
	CString strText,strID;
	m_pTabWidget = new QTableWidget(3, 4); 
	m_pTabWidget->verticalHeader()->setVisible(false);
	m_pTabWidget->horizontalHeader()->setVisible(false);
	m_pTabWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pTabWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pTabWidget->setFont(*g_pSttGlobalFont);

	QTableWidgetItem *pItem = NULL;
	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("模拟量");
	pItem->setText(strText);
	m_pTabWidget->setItem(0, 0, pItem);

	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("输入电压");
	pItem->setText(strText);
	m_pTabWidget->setItem(0, 1, pItem);
	m_pTabWidget->setSpan(0, 1, 1, 3);

	QStringList oPId,oQId,oPName,oQName;
	oPId << _T("P_Vol_Check")<< _T("P_Vol100_Check")<< _T("P_Vol080_Check")<< _T("P_Vol120_Check");
	oQId << _T("Q_Vol_Check")<< _T("Q_Vol100_Check")<< _T("Q_Vol080_Check")<< _T("Q_Vol120_Check");

	oPName << _T("有功功率")<< _T("Ua=Ub=Uc=Un")<< _T("Ua=Ub=Uc=0.8Un")<< _T("Ua=Ub=Uc=1.2Un");
	oQName << _T("无功功率")<< _T("Ua=Ub=Uc=Un")<< _T("Ua=Ub=Uc=0.8Un")<< _T("Ua=Ub=Uc=1.2Un");


	for (int row = 1; row < m_pTabWidget->rowCount(); row++) 
	{
		for (int col = 0; col < m_pTabWidget->columnCount(); col++) 
		{				
			QSttCheckBox *pCheckBox = new QSttCheckBox();
			pCheckBox->setFont(*g_pSttGlobalFont);

			if (row == 1)
			{
				strID = oPId.at(col);
				strText = oPName.at(col);
			}
			else 
			{
				strID = oQId.at(col);
			    strText = oQName.at(col);
			}		
			pCheckBox->setText(strText);
			pCheckBox->setObjectName(strID);
			//GetCheckBoxValue(pCheckBox,strID);

			if(strID == _T("P_Vol100_Check") || strID == _T("Q_Vol100_Check"))
			{
				pCheckBox->setEnabled(false);
				pCheckBox->setChecked(true);
				m_pDataGroup.SetDataValue(strID,(long)1);	
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
			m_pTabWidget->setCellWidget(row, col, pWidget);
		}
	}


	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
	CDvmData* pCurData = (CDvmData*)m_pDataGroup.FindByID(_T("OutputTime"));
	m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	m_pEstimateBtn = new QPushButton;
	strText = _T("结果评估");
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	m_pEstimateBtn->setText(strText);

	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addWidget(pOutPutLabel);
	pHBoxLayout->addWidget(m_pOutPutTimeEdit);
	pHBoxLayout->addStretch(10);
	pHBoxLayout->addWidget(m_pEstimateBtn);

// 	QSttCheckBox* pOver_Check = new QSttCheckBox;
// 	strText = _T("输入电压变化引起的改变量");
// 	pOver_Check->setText(strText);
// 	pOver_Check->setObjectName(_T("Vol_Check"));
// 	//GetCheckBoxValue(pOver_Check,_T("Vol_Check"));
// 	m_pAllCheckBoxList.append(pOver_Check);

	m_pGroupBox = new QSttCheckableGroupBox;
	strText = _T("输入电压变化引起的改变量");
	m_pGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBox->setTitle(strText);
	m_pGroupBox->setCheckable(true);

	QVBoxLayout *pVBoxLayout = new QVBoxLayout;
	pVBoxLayout->addWidget(m_pTabWidget);
	m_pGroupBox->setLayout(pVBoxLayout);

	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(m_pGroupBox);
	pMainLayout->addStretch();
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

//  	setTableWidgetEnabled(m_pTabWidget,pOver_Check->isChecked());
// 	QSttCheckBox* pPCheck = FindCheckBoxByID(m_pAllCheckBoxList, _T("P_Vol_Check"));
//  	UpdateCheckbox(m_pTabWidget,1,pPCheck->isChecked());
//  	QSttCheckBox* pQCheck = FindCheckBoxByID(m_pAllCheckBoxList, _T("Q_Vol_Check"));
//  	UpdateCheckbox(m_pTabWidget,2,pQCheck->isChecked());
	
	OpenBinBoutMapXml();	
	connect(m_pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	connect(m_pOutPutTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));

	//测试要求暂时隐藏
	pOutPutLabel->hide();
	m_pOutPutTimeEdit->hide();
}

void QSttMacroParaEditViewInputVolWidget::GetCheckBoxValue(CDataGroup *pParas,QSttCheckBox * pCheckBox,const CString strID )
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

void QSttMacroParaEditViewInputVolWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewInputVolWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}
	long nPhaseNum = 0;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhaseNum);
	m_pDataGroup.SetDataValue(_T("Phase_Number"),nPhaseNum);
}

BOOL QSttMacroParaEditViewInputVolWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewInputVolWidget::slot_CheckBoxStateChanged( int nState)
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}
	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pDataGroup.SetDataValue(strID,(long)0);
	}

//  	if (strID == _T("Vol_Check"))
//  	{
//  		setTableWidgetEnabled(m_pTabWidget,nState);
//  	}
 
 	int nRow = -1;
 	if (strID == _T("P_Vol_Check"))
 	{
 		nRow = 1;
 	}
 	else if (strID == _T("Q_Vol_Check"))
 	{
 		nRow = 2;
 	}
	
 	if (nRow != -1)
 	{
 		UpdateCheckbox(m_pTabWidget,nRow,nState);
 	}
}

void QSttMacroParaEditViewInputVolWidget::slot_Estimate()
{
	QInputVolEstimateDlg dlg(&m_pDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewInputVolWidget::slot_LineEditFinished()
{
	float fValue = m_pOutPutTimeEdit->text().toFloat();
	fValue = setLimit(0,999,fValue);
	m_pOutPutTimeEdit->setText(QString::number(fValue));
	m_pDataGroup.SetDataValue(_T("OutputTime"),fValue);
}

void QSttMacroParaEditViewInputVolWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewInputVolWidget::SetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pDataGroup);	
	}
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}
	CDvmData* pCurData = NULL;
	pCurData = (CDvmData*)m_pDataGroup.FindByID(_T("Vol_Check"));
	if (pCurData)
	{
		BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
		m_pGroupBox->setChecked(nIsSelected);
	}

	pCurData = (CDvmData*)m_pDataGroup.FindByID(_T("OutputTime"));
	if (pCurData)
	{
		m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	}

	QSttCheckBox* pPCheck = FindCheckBoxByID(m_pAllCheckBoxList, _T("P_Vol_Check"));
	UpdateCheckbox(m_pTabWidget,1,pPCheck->isChecked());
	QSttCheckBox* pQCheck = FindCheckBoxByID(m_pAllCheckBoxList, _T("Q_Vol_Check"));
	UpdateCheckbox(m_pTabWidget,2,pQCheck->isChecked());
	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewInputVolWidget::slot_GroupBoxtoggled( bool checked)
{
	m_pDataGroup.SetDataValue(_T("Vol_Check"),(long)checked);	

}
void QSttMacroParaEditViewInputVolWidget::SaveParasXml()
{
	m_pDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_InputVol_Paras.xml");
	m_pDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewInputVolWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
	m_pGroupBox->setDisabled(true);
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewInputVolWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);
	m_pGroupBox->setDisabled(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
// 	QSttCheckBox* pCheck = FindCheckBoxByID(m_pAllCheckBoxList, _T("Vol_Check"));
// 	setTableWidgetEnabled(m_pTabWidget,pCheck->isChecked());
// 	QSttCheckBox* pPCheck = FindCheckBoxByID(m_pAllCheckBoxList, _T("P_Vol_Check"));
// 	UpdateCheckbox(m_pTabWidget,1,pPCheck->isChecked());
// 	QSttCheckBox* pQCheck = FindCheckBoxByID(m_pAllCheckBoxList, _T("Q_Vol_Check"));
// 	UpdateCheckbox(m_pTabWidget,2,pQCheck->isChecked());
}

void QSttMacroParaEditViewInputVolWidget::setTableWidgetEnabled( QTableWidget *pTableWidget, bool enabled )
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

void QSttMacroParaEditViewInputVolWidget::UpdateCheckbox( QTableWidget *pTableWidget,int row,bool bChecked )
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
					if(pCheckBox->objectName() != _T("P_Vol100_Check") && pCheckBox->objectName() != _T("Q_Vol100_Check"))
					{
						pCheckBox->setEnabled(bChecked);
					}
				}
			}
		}
	}
}

QSttCheckBox* QSttMacroParaEditViewInputVolWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
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

BOOL QSttMacroParaEditViewInputVolWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
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

QInputVolEstimateDlg::QInputVolEstimateDlg( CDataGroup* pParas, QWidget* parent ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 200);
	m_pVolLineEdit = NULL;
	m_pParas = pParas;
	InitUI();
}

QInputVolEstimateDlg::~QInputVolEstimateDlg()
{

}
void QInputVolEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("输入电压变化引起的改变量");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);
	QLabel *pLabel = new QLabel;
	strText = _T("输入电压功率测量误差(%)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pVolLineEdit = new QSttLineEdit;
	m_pVolLineEdit->setFont(*g_pSttGlobalFont);
	QHBoxLayout* pHLayout = new QHBoxLayout(pGroupBox);
	pHLayout->addWidget(pLabel);
	pHLayout->addWidget(m_pVolLineEdit);

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

	m_pVolLineEdit->setObjectName(_T("Vol_Power_RelErr"));
	GetLineEditValue(m_pVolLineEdit,_T("Vol_Power_RelErr"));
	
	connect(m_pVolLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QInputVolEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Vol_Power_RelErr"),m_pVolLineEdit->text());
	close();
}

void QInputVolEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QInputVolEstimateDlg::slot_EditFinished()
{
	float fValue = m_pVolLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pVolLineEdit->setText(QString::number(fValue,'f',3));
}

void QInputVolEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}



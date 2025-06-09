#include "SttMacroParaEditViewPowerAccuracyWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include <QHeaderView>
#include <QTableWidget>
#include <QSpacerItem>

QSttMacroParaEditViewPowerAccuracyWidget::QSttMacroParaEditViewPowerAccuracyWidget( QWidget *parent)
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	m_pOutPutTimeEdit = NULL;
	m_pMacroTestValues = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewPowerAccuracyWidget::~QSttMacroParaEditViewPowerAccuracyWidget()
{
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		delete m_pAllCheckBoxList.at(i); 
	}
	m_pAllCheckBoxList.clear(); 
}

void QSttMacroParaEditViewPowerAccuracyWidget::InitUI()
{
	m_pTabWidget = new QTableWidget(8, 10); 
	m_pTabWidget->setStyleSheet(
		"QTableWidget::item:selected {"
		"background-color: transparent;" 
		"}"
		);

	m_pTabWidget->setFocusPolicy(Qt::NoFocus);
	m_pTabWidget->verticalHeader()->setVisible(false);
	m_pTabWidget->horizontalHeader()->setVisible(false);
	m_pTabWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pTabWidget->verticalHeader()->setResizeMode(QHeaderView::Stretch);
	m_pTabWidget->setFont(*g_pSttGlobalFont);
	InitTable(m_pTabWidget);

	CString strText;
	QTableWidgetItem *pItem = NULL;
	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("类型");
	pItem->setText(strText);
	m_pTabWidget->setItem(0, 0, pItem);
	m_pTabWidget->setSpan(0, 0, 1, 2);

	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("输入电流(%)");
	pItem->setText(strText);
	m_pTabWidget->setItem(0, 2, pItem);
	m_pTabWidget->setSpan(0, 2, 1, 8);
	
	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("有功功率cosφ");
	pItem->setText(strText);
	m_pTabWidget->setItem(1, 0, pItem);
	m_pTabWidget->setSpan(1, 0, 3, 1);

	pItem = new QTableWidgetItem();
	pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	strText = _T("无功功率sinφ");
	pItem->setText(strText);
	m_pTabWidget->setItem(4, 0, pItem);
	m_pTabWidget->setSpan(4, 0, 4, 1);

	QLabel *pOutPutLabel =new QLabel;
	pOutPutLabel->setFont(*g_pSttGlobalFont);
	strText = _T("输出时长(s)");
	pOutPutLabel->setText(strText);
	m_pOutPutTimeEdit = new QLineEdit;
	m_pOutPutTimeEdit->setFont(*g_pSttGlobalFont);
	m_pOutPutTimeEdit->setObjectName(_T("OutputTime"));
// 	CDvmData* pCurData = (CDvmData*)m_pARPowerErrorDataGroup.FindByID(_T("OutputTime"));
// 	m_pOutPutTimeEdit->setText(QString::number(pCurData->m_strValue.toFloat()));
	m_pAllLineEditList.append(m_pOutPutTimeEdit);
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
	pMainLayout->addWidget(m_pTabWidget);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);


	UpdateCheckboxEnabled(_T("P1_Check"));
	UpdateCheckboxEnabled(_T("P05L_Check"));
	UpdateCheckboxEnabled(_T("P05C_Check"));
	UpdateCheckboxEnabled(_T("Q1L_Check"));
	UpdateCheckboxEnabled(_T("Q05L_Check"));
	UpdateCheckboxEnabled(_T("Q1C_Check"));
	UpdateCheckboxEnabled(_T("Q05C_Check"));

	OpenBinBoutMapXml();

	connect(m_pOutPutTimeEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));


	//测试要求暂时隐藏
	pOutPutLabel->hide();
	m_pOutPutTimeEdit->hide();
}

void QSttMacroParaEditViewPowerAccuracyWidget::InitTable( QTableWidget *pTabWidget )
{
	CString strText,strID;
	QStringList oList;
	oList << _T("5")<< _T("20")<< _T("40")<< _T("60")<< _T("80")<< _T("100");
	for (int row = 1; row < m_pTabWidget->rowCount(); row++) 
	{
		for (int col = 1; col < 8; col++) 
		{	
			QSttCheckBox *pCheckBox = new QSttCheckBox();
			pCheckBox->setFont(*g_pSttGlobalFont);
			m_pAllCheckBoxList.append(pCheckBox);

			if (col == 1)
			{
				if (row == 1)
				{
					strText = _T("1");
					strID = _T("P1_Check");
				}
				else if ( row == 2 ||  row == 5 )
				{
					strText = _T("0.5L");
					strID = (row == 2) ? _T("P05L_Check") : _T("Q05L_Check");
				}
				else if ( row == 3 ||  row == 7 )
				{
					strText = _T("0.5C");
					strID = (row == 3) ? _T("P05C_Check") : _T("Q05C_Check");
				}
				else if ( row == 4 )
				{
					strText = _T("1L");
					strID = _T("Q1L_Check");
				}
				else if( row == 6 )
				{
					strText = _T("1C");
					strID = _T("Q1C_Check");
				}
			}
			else if(col > 1 )
			{		
				QWidget *pWidget = pTabWidget->cellWidget(row, 1);
				CString strName;
				if(pWidget)
				{
					QHBoxLayout *pLayout = qobject_cast<QHBoxLayout*>(pWidget->layout());
					if (pLayout && pLayout->count() > 0) 
					{
						QSttCheckBox *pTypeCheckBox = qobject_cast<QSttCheckBox*>(pLayout->itemAt(1)->widget());
						if (pTypeCheckBox)
						{
							strName = pTypeCheckBox->objectName();
							int index = strName.indexOf('_');
							if (index != -1)
							{
								strName = strName.left(index); 
							}
						}
					}
				}
				if (col - 2 < oList.size())
				{
					strText = oList.at(col - 2);
				}
				
				CString str = ProcessString(strText);
				strID = strName + _T("_Cur") + str + _T("_Check");
			}

			pCheckBox->setText(strText);
			pCheckBox->setObjectName(strID);
			//GetCheckBoxValue(pCheckBox,strID);
			connect(pCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));

 			QHBoxLayout *pLayout = new QHBoxLayout();
 			pLayout->addSpacing(8);
 			pLayout->addWidget(pCheckBox);
 			QWidget *pWidget = new QWidget();
 			pWidget->setLayout(pLayout);
			pTabWidget->setCellWidget(row, col, pWidget);
		}
	}

	CString strOjectName;
	for (int row = 1; row < pTabWidget->rowCount(); row++) 
	{
		for (int col = 8; col < pTabWidget->columnCount(); col++) 
		{
			QWidget *pWidget = pTabWidget->cellWidget(row, 1);
			CString strName;
			if(pWidget)
			{
				QHBoxLayout *pLayout = qobject_cast<QHBoxLayout*>(pWidget->layout());
				if (pLayout && pLayout->count() > 0) 
				{
					QSttCheckBox *pTypeCheckBox = qobject_cast<QSttCheckBox*>(pLayout->itemAt(1)->widget());
					if (pTypeCheckBox)
					{
						strName = pTypeCheckBox->objectName();
						int index = strName.indexOf('_');
						if (index != -1)
						{
							strName = strName.left(index); 
						}
					}
				}
			}
			if (col == 8)
			{
				strID = strName +  _T("_CurCustom1_Check");
				strOjectName = strName +  _T("_CurCustom1");
			}
			else if (col == 9)
			{
				strID = strName +  _T("_CurCustom2_Check");
				strOjectName = strName +  _T("_CurCustom2");
			}

			QSttCheckBox* pCustomCheckBox = new QSttCheckBox;
			QLineEdit *pCustomLineEdit = new QLineEdit;
			pCustomCheckBox->setFont(*g_pSttGlobalFont);
			pCustomLineEdit->setFont(*g_pSttGlobalFont);
			pCustomCheckBox->setObjectName(strID);
			pCustomLineEdit->setObjectName(strOjectName);
			QHBoxLayout* pCustomLayout = new QHBoxLayout;
			pCustomLayout->addWidget(pCustomCheckBox);
			pCustomLayout->addWidget(pCustomLineEdit);
			QWidget *pCustomWidget = new QWidget();
			pCustomWidget->setLayout(pCustomLayout);
			pTabWidget->setCellWidget(row, col, pCustomWidget);
			m_pAllCheckBoxList.append(pCustomCheckBox);
			m_pAllLineEditList.append(pCustomLineEdit);
			//GetCheckBoxValue(pCustomCheckBox,strID);
			connect(pCustomCheckBox, SIGNAL(stateChanged (int)), this, SLOT(slot_CheckBoxStateChanged(int)));
			//GetLineEditValue(pCustomLineEdit,strOjectName);
			connect(pCustomLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
		}
	}
}

void QSttMacroParaEditViewPowerAccuracyWidget::UpdateCheckbox( QTableWidget *pTableWidget,int row,bool bChecked )
{
	for (int col = 2; col < pTableWidget->columnCount(); ++col) 
	{
		QWidget *cellWidget = pTableWidget->cellWidget(row, col);
		if (cellWidget) 
		{
			QHBoxLayout *pLayout = qobject_cast<QHBoxLayout *>(cellWidget->layout());
			if (pLayout) 
			{
				QSttCheckBox *pCheckBox = qobject_cast<QSttCheckBox *>(pLayout->itemAt(1)->widget());
				if (pCheckBox) 
				{
					pCheckBox->setEnabled(bChecked);
				}
			}
		}
	}
}

void QSttMacroParaEditViewPowerAccuracyWidget::UpdateCheckboxEnabled( CString strID)
{
	QSttCheckBox* pCheckBox = NULL;
	QSttCheckBox* pCustomCheckBox = NULL;
	QLineEdit *pCustomLineEdit = NULL;
	if (strID == _T("P1_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateCheckbox(m_pTabWidget,1,pCheckBox->isChecked());
	}
	else if (strID == _T("P05L_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateCheckbox(m_pTabWidget,2,pCheckBox->isChecked());
	}
	else if (strID == _T("P05C_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateCheckbox(m_pTabWidget,3,pCheckBox->isChecked());
	}
	else if (strID == _T("Q1L_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateCheckbox(m_pTabWidget,4,pCheckBox->isChecked());
	}
	else if (strID == _T("Q05L_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateCheckbox(m_pTabWidget,5,pCheckBox->isChecked());
	}
	else if (strID == _T("Q1C_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateCheckbox(m_pTabWidget,6,pCheckBox->isChecked());
	}
	else if (strID == _T("Q05C_Check"))
	{
		pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strID);
		UpdateCheckbox(m_pTabWidget,7,pCheckBox->isChecked());
	}


	CString str = strID.section('_', 0, 0); 
	CString strCustom1,strCustom2;
	strCustom1 = str + _T("_CurCustom1");
	pCustomLineEdit = FindLineEditID(m_pAllLineEditList, strCustom1);
	strCustom1 = strCustom1 + _T("_Check");
	pCustomCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strCustom1);

	if (pCheckBox)
	{
		pCheckBox->setDisabled(false);

		pCustomCheckBox->setEnabled(pCheckBox->isChecked());
		if(pCheckBox->isChecked())
		{
			pCustomLineEdit->setEnabled(pCustomCheckBox->isChecked());
		}
		else
		{
			pCustomLineEdit->setEnabled(false);
		}
	}
	else
	{
		pCustomLineEdit->setEnabled(pCustomCheckBox->isChecked());
	}

	strCustom2 = str + _T("_CurCustom2");
	pCustomLineEdit = FindLineEditID(m_pAllLineEditList, strCustom2);
	strCustom2 = strCustom2 + _T("_Check");
	pCustomCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, strCustom2);
	if (pCheckBox)
	{
		pCustomCheckBox->setEnabled(pCheckBox->isChecked());
		if(pCheckBox->isChecked())
		{
			pCustomLineEdit->setEnabled(pCustomCheckBox->isChecked());
		}
		else
		{
			pCustomLineEdit->setEnabled(false);
		}
	}
	else
	{
		pCustomLineEdit->setEnabled(pCustomCheckBox->isChecked());
	}
}

QSttCheckBox* QSttMacroParaEditViewPowerAccuracyWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
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

QLineEdit* QSttMacroParaEditViewPowerAccuracyWidget::FindLineEditID( const QList<QLineEdit*>& LineEditList, const CString& strID )
{
	for (int i = 0; i < LineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = LineEditList.at(i);
		if (pLineEdit->objectName() == strID)
		{
			return pLineEdit;
		}
	}
	return NULL;
}

void QSttMacroParaEditViewPowerAccuracyWidget::SetDatas( CDataGroup *pParas )
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pARPowerErrorDataGroup);	
	}
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		if (pCheckBox)
		{
			GetCheckBoxValue(&m_pARPowerErrorDataGroup,pCheckBox,pCheckBox->objectName());
		}
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pARPowerErrorDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

BOOL QSttMacroParaEditViewPowerAccuracyWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	if (m_pMacroTestValues == NULL)
	{
		m_pMacroTestValues = new CDvmValues;
	}
	CDvmValues *pDvmValues = pReport->m_pValues;
	CDvmDataset *pRptDvmDataset = pReport->m_pRptDvmDataset;

	POS pos = pRptDvmDataset->GetHeadPosition();
	CDvmData *pCurrData = NULL;
	CDvmValue *pDvmValue = NULL;

	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTCOMMCMD) //通讯命令
	{
		if (pRptDvmDataset == NULL)
		{
			return FALSE;
		}
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

		if (m_pMacroTestValues &&m_pMacroTestValues->GetCount() > 0 )
		{
			pDvmValues->AppendCloneEx2(*m_pMacroTestValues);
		}
	}
	

	if (pSttItem->GetClassID() == STTGBXMLCLASSID_CSTTMACROTEST)//电气量
	{
		m_pMacroTestValues->DeleteAll();

		if (pDvmValues == NULL)
		{
			return FALSE;
		}
		POS posValue = pDvmValues->GetHeadPosition();
		while(posValue)
		{
			pCurrData = (CDvmData*)pDvmValues->GetNext(posValue); 
			if (pCurrData == NULL )
			{
				continue;
			}
			if (pCurrData->m_strID == _T("Poutput") || pCurrData->m_strID == _T("Qoutput"))
			{

				pDvmValue = new CDvmValue;
				pDvmValue->m_strID = pCurrData->m_strID;
				pDvmValue->m_strValue = pCurrData->m_strValue;
				m_pMacroTestValues->AddNewChild(pDvmValue);
			}
		}
	}
	return TRUE;

}

void QSttMacroParaEditViewPowerAccuracyWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewPowerAccuracyWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	long nPhase_Number;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhase_Number);
	m_pARPowerErrorDataGroup.SetDataValue(_T("Phase_Number"),nPhase_Number);


	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pARPowerErrorDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}
}

void QSttMacroParaEditViewPowerAccuracyWidget::UpdateReportFile(long nPhaseNumber)
{
// 	CString strFileName,strPath;
// 	strFileName = g_pTheSttTestApp->m_pTestMacroUI->m_strReportFile;
// 	if(nPhase_Number == 3)
// 	{
// 		strFileName = 
// 	}
// 	else if(nPhase_Number == 2)
// 	{
// 
// 	}
// 
// 	strPath = _P_GetDBPath();
// 	strPath += "ui/";
// 	strPath += _T("chinese");
// 	strPath += "/";
// 	strPath += strFileName;
// 
// 	if (IsFileExist(strPath))
// 	{
// 		g_pTheSttTestApp->m_pTestMacroUI->m_strReportFile = strFileName;
// 	}
}

void QSttMacroParaEditViewPowerAccuracyWidget::slot_Estimate()
{
	QARPowerErrorEstimateDlg dlg(&m_pARPowerErrorDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}



void QSttMacroParaEditViewPowerAccuracyWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue));
		m_pARPowerErrorDataGroup.SetDataValue(strID,fValue);
	}
}

BOOL QSttMacroParaEditViewPowerAccuracyWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pARPowerErrorDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewPowerAccuracyWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();

	m_pARPowerErrorDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pARPowerErrorDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	
	m_pARPowerErrorDataGroup.CopyChildren(pParas);

	//SaveParasXml();
}

void QSttMacroParaEditViewPowerAccuracyWidget::SaveParasXml()
{
	m_pARPowerErrorDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pARPowerErrorDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pARPowerErrorDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pARPowerErrorDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_PowerAccuracy_Paras.xml");
	m_pARPowerErrorDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewPowerAccuracyWidget::GetCheckBoxValue(CDataGroup *pParas, QSttCheckBox * pCheckBox,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pARPowerErrorDataGroup.*/pParas->FindByID(strID);
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

void QSttMacroParaEditViewPowerAccuracyWidget::slot_CheckBoxStateChanged( int )
{
	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
	if (!pCheckBox)
	{
		return;
	}
	CString strID = pCheckBox->objectName();
	if (pCheckBox->isChecked()) 
	{
		m_pARPowerErrorDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pARPowerErrorDataGroup.SetDataValue(strID,(long)0);
	}

	UpdateCheckboxEnabled(strID);
}

CString QSttMacroParaEditViewPowerAccuracyWidget::ProcessString( CString &str )
{
	CString strProcessed = str;
	int index = strProcessed.indexOf('%');
	if (index != -1)
	{
		strProcessed = strProcessed.left(index); 
	}
	if (strProcessed.length() < 3)
	{
		int numZeros = 3 - strProcessed.length();
		strProcessed = QString(numZeros, '0') + strProcessed; // 在前面补足0
	}
	return strProcessed;
}

void QSttMacroParaEditViewPowerAccuracyWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);
	m_pOutPutTimeEdit->setDisabled(true);
	for (int i = 0; i < m_pAllCheckBoxList.size(); ++i) 
	{
		QSttCheckBox *pCheckBox = m_pAllCheckBoxList.at(i);
		pCheckBox->setDisabled(true);
	}

	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit * pLineEdit = m_pAllLineEditList.at(i);
		pLineEdit->setDisabled(true);
	}

	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewPowerAccuracyWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);
	m_pOutPutTimeEdit->setDisabled(false);
	UpdateCheckboxEnabled(_T("P1_Check"));
	UpdateCheckboxEnabled(_T("P05L_Check"));
	UpdateCheckboxEnabled(_T("P05C_Check"));
	UpdateCheckboxEnabled(_T("Q1L_Check"));
	UpdateCheckboxEnabled(_T("Q05L_Check"));
	UpdateCheckboxEnabled(_T("Q1C_Check"));
	UpdateCheckboxEnabled(_T("Q05C_Check"));
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewPowerAccuracyWidget::GetLineEditValue( CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)/*m_pARPowerErrorDataGroup.*/pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue));
}


QARPowerErrorEstimateDlg::QARPowerErrorEstimateDlg( CDataGroup* pParas, QWidget* parent /*= NULL*/ ): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 200);
	m_pParas = pParas;
	m_pPowerErrorLineEdit = NULL;
	InitUI();
}

QARPowerErrorEstimateDlg::~QARPowerErrorEstimateDlg()
{

}
void QARPowerErrorEstimateDlg::InitUI()
{
	CString strText;
	QGroupBox *pGroupBox = new QGroupBox;
	strText = _T("有功无功基本误差");
	pGroupBox->setFont(*g_pSttGlobalFont);
	pGroupBox->setTitle(strText);

	QLabel *pLabel = new QLabel;
	strText = _T("功率测量误差(%)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pPowerErrorLineEdit = new QSttLineEdit;
	m_pPowerErrorLineEdit->setFont(*g_pSttGlobalFont);
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(_T("Power_RelErr"));
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	m_pPowerErrorLineEdit->setText(QString::number(fValue,'f',3));


	QGridLayout* pHLayout = new QGridLayout(pGroupBox);
	//pHLayout->addItem(new QSpacerItem(10, 5, QSizePolicy::Expanding, QSizePolicy::Minimum), 0, 0, 1, 1); 
	pHLayout->addWidget(pLabel,0,1,1,1);
	pHLayout->addWidget(m_pPowerErrorLineEdit,0,2,1,1);

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

	connect(m_pPowerErrorLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QARPowerErrorEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("Power_RelErr"),m_pPowerErrorLineEdit->text());
	close();
}

void QARPowerErrorEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QARPowerErrorEstimateDlg::slot_EditFinished()
{
	float fValue = m_pPowerErrorLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pPowerErrorLineEdit->setText(QString::number(fValue,'f',3));
}



#include "SttMacroParaEditViewTURecloseAccWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../Controls/SttCheckableGroupBox.h"


QSttMacroParaEditViewTURecloseAccWidget::QSttMacroParaEditViewTURecloseAccWidget( QWidget *parent /*= 0*/ )
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	m_pEstimateBtn = NULL;
	//m_pOutPutTimeEdit = NULL;
	OpenTestTestMngrFile(_T(""));
	OpenBinBoutMapXml();
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewTURecloseAccWidget::~QSttMacroParaEditViewTURecloseAccWidget()
{
	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		delete m_pAllLineEditList.at(i); 
	}
	m_pAllLineEditList.clear(); 


	for (int i = 0; i < m_pGroupBoxList.size(); ++i)
	{
		delete m_pGroupBoxList.at(i); 
	}
	m_pGroupBoxList.clear(); 
}

void QSttMacroParaEditViewTURecloseAccWidget::InitUI()
{
	CString strText;
	strText = _T("过流重合闸");
	QSttCheckableGroupBox *pCurrAccGroupBox = new QSttCheckableGroupBox();
	pCurrAccGroupBox->setFont(*g_pSttGlobalFont);
	pCurrAccGroupBox->setTitle(strText);
	pCurrAccGroupBox->setCheckable(true);
	pCurrAccGroupBox->setObjectName(_T("Rec_Check"));

	QGridLayout *pCurrAccLayout = new QGridLayout(pCurrAccGroupBox);
	QLabel *pCurrZoneLab = new QLabel;
	pCurrZoneLab->setFont(*g_pSttGlobalFont);
	strText = _T("投入区段");
	pCurrZoneLab->setText(strText);

	m_pRecAccCombox = new QComboBox;
	m_pRecAccCombox->setFont(*g_pSttGlobalFont);

	QLabel *pCurrSetTimeLab = new QLabel;
	pCurrSetTimeLab->setFont(*g_pSttGlobalFont);
	strText = _T("整定时间(s)");
	pCurrSetTimeLab->setText(strText);
	QLineEdit *pCurrSetTimeEdit = new QLineEdit;
	pCurrSetTimeEdit->setFont(*g_pSttGlobalFont);
	QLabel *pCurrAccTimeLab = new QLabel;
	pCurrAccTimeLab->setFont(*g_pSttGlobalFont);
	strText = _T("重合闸时间(s)");
	pCurrAccTimeLab->setText(strText);
	QLineEdit *pCurrAccTimeEdit = new QLineEdit;
	pCurrAccTimeEdit->setFont(*g_pSttGlobalFont);
	QLabel *pCurrFaultLab = new QLabel;
	pCurrFaultLab->setFont(*g_pSttGlobalFont);
	strText = _T("故障电流(A)");
	pCurrFaultLab->setText(strText);
	QLineEdit *pCurrFaultEdit = new QLineEdit;
	pCurrFaultEdit->setFont(*g_pSttGlobalFont);
	pCurrAccLayout->addWidget(pCurrZoneLab,0,0,1,1);
	pCurrAccLayout->addWidget(m_pRecAccCombox,0,1,1,1);

	pCurrAccLayout->addWidget(pCurrSetTimeLab,0,2,1,1);
	pCurrAccLayout->addWidget(pCurrSetTimeEdit,0,3,1,1);
	pCurrAccLayout->addWidget(pCurrAccTimeLab,0,4,1,1);
	pCurrAccLayout->addWidget(pCurrAccTimeEdit,0,5,1,1);
	pCurrAccLayout->addWidget(pCurrFaultLab,0,6,1,1);
	pCurrAccLayout->addWidget(pCurrFaultEdit,0,7,1,1);

	m_pAllLineEditList.append(pCurrSetTimeEdit);
	m_pAllLineEditList.append(pCurrAccTimeEdit);
	m_pAllLineEditList.append(pCurrFaultEdit);
	m_pRecAccCombox->setObjectName(_T("Trip_Object"));
	m_pRecAccCombox->addItems(QStringList()<<_T("I段")<<_T("II段")<<_T("III段"));
	//GetComboxValue(m_pRecAccCombox,_T("Trip_Object"));

	pCurrSetTimeEdit->setObjectName(_T("TripTime"));
	//GetLineEditValue(pCurrSetTimeEdit,_T("TripTime"));
	pCurrAccTimeEdit->setObjectName(_T("RecloseTime"));
	//GetLineEditValue(pCurrAccTimeEdit,_T("RecloseTime"));
	pCurrFaultEdit->setObjectName(_T("ISet1"));
	//GetLineEditValue(pCurrFaultEdit,_T("ISet1"));

	QSttCheckableGroupBox *pZeroAccGroupBox = new QSttCheckableGroupBox();
	pZeroAccGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("零序过流重合闸");
	pZeroAccGroupBox->setTitle(strText);
	pZeroAccGroupBox->setCheckable(true);
	pZeroAccGroupBox->setObjectName(_T("Zero_Check"));
	QGridLayout *pZeroAccLayout = new QGridLayout(pZeroAccGroupBox);
	QLabel *pZeroZoneLab = new QLabel;
	pZeroZoneLab->setFont(*g_pSttGlobalFont);
	strText = _T("投入区段");
	pZeroZoneLab->setText(strText);
	m_pZeroAccCombox = new QComboBox;
	m_pZeroAccCombox->setFont(*g_pSttGlobalFont);

	QLabel *pZeroSetTimeLab = new QLabel;
	pZeroSetTimeLab->setFont(*g_pSttGlobalFont);
	strText = _T("整定时间(s)");
	pZeroSetTimeLab->setText(strText);
	QLineEdit *pZeroSetTimeEdit = new QLineEdit;
	pZeroSetTimeEdit->setFont(*g_pSttGlobalFont);
	QLabel *pZeroAccTimeLab = new QLabel;
	pZeroAccTimeLab->setFont(*g_pSttGlobalFont);
	strText = _T("重合闸时间(s)");
	pZeroAccTimeLab->setText(strText);
	QLineEdit *pZeroAccTimeEdit = new QLineEdit;
	pZeroAccTimeEdit->setFont(*g_pSttGlobalFont);
	QLabel *pZeroFaultLab = new QLabel;
	pZeroFaultLab->setFont(*g_pSttGlobalFont);
	strText = _T("故障电流(A)");
	pZeroFaultLab->setText(strText);
	QLineEdit *pZeroFaultEdit = new QLineEdit;
	pZeroFaultEdit->setFont(*g_pSttGlobalFont);
	pZeroAccLayout->addWidget(pZeroZoneLab,0,0,1,1);
	pZeroAccLayout->addWidget(m_pZeroAccCombox,0,1,1,1);

	pZeroAccLayout->addWidget(pZeroSetTimeLab,0,2,1,1);
	pZeroAccLayout->addWidget(pZeroSetTimeEdit,0,3,1,1);
	pZeroAccLayout->addWidget(pZeroAccTimeLab,0,4,1,1);
	pZeroAccLayout->addWidget(pZeroAccTimeEdit,0,5,1,1);
	pZeroAccLayout->addWidget(pZeroFaultLab,0,6,1,1);
	pZeroAccLayout->addWidget(pZeroFaultEdit,0,7,1,1);

	m_pAllLineEditList.append(pZeroSetTimeEdit);
	m_pAllLineEditList.append(pZeroAccTimeEdit);
	m_pAllLineEditList.append(pZeroFaultEdit);

	m_pZeroAccCombox->setObjectName(_T("Zero_Trip_Object"));
	m_pZeroAccCombox->addItems(QStringList()<<_T("I段")<<_T("II段"));
	//GetComboxValue(m_pZeroAccCombox,_T("Zero_Trip_Object"));

	pZeroSetTimeEdit->setObjectName(_T("Zero_TripTime"));
	//GetLineEditValue(pZeroSetTimeEdit,_T("Zero_TripTime"));
	pZeroAccTimeEdit->setObjectName(_T("Zero_RecloseTime"));
	//GetLineEditValue(pZeroAccTimeEdit,_T("Zero_RecloseTime"));
	pZeroFaultEdit->setObjectName(_T("Zero_ISet1"));
	//GetLineEditValue(pZeroFaultEdit,_T("Zero_ISet1"));


	QSttCheckableGroupBox *pOverCurrGroupBox = new QSttCheckableGroupBox();
	pOverCurrGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("过流后加速");
	pOverCurrGroupBox->setTitle(strText);
	pOverCurrGroupBox->setCheckable(true);
	pOverCurrGroupBox->setObjectName(_T("AftAcc_Check"));
	QHBoxLayout *pOverCurrLayout = new QHBoxLayout(pOverCurrGroupBox);

	QLabel *pOverCurrSetTimeLab = new QLabel;
	pOverCurrSetTimeLab->setFont(*g_pSttGlobalFont);
	strText = _T("后加速整定时间(s)");
	pOverCurrSetTimeLab->setText(strText);
	QLineEdit *pOverCurrSetTimeEdit = new QLineEdit;
	pOverCurrSetTimeEdit->setFont(*g_pSttGlobalFont);
	QLabel *pOverCurrFaultLab = new QLabel;
	pOverCurrFaultLab->setFont(*g_pSttGlobalFont);
	strText = _T("重合故障(A)");
	pOverCurrFaultLab->setText(strText);
	QLineEdit *pOverCurrFaultEdit = new QLineEdit;
	pOverCurrFaultEdit->setFont(*g_pSttGlobalFont);

	pOverCurrLayout->addWidget(pOverCurrSetTimeLab);
	pOverCurrLayout->addWidget(pOverCurrSetTimeEdit);
	pOverCurrLayout->addWidget(pOverCurrFaultLab);
	pOverCurrLayout->addWidget(pOverCurrFaultEdit);
	pOverCurrLayout->addStretch();

	m_pAllLineEditList.append(pOverCurrSetTimeEdit);
	m_pAllLineEditList.append(pOverCurrFaultEdit);

	pOverCurrSetTimeEdit->setObjectName(_T("AfterAcceTime"));
	//GetLineEditValue(pOverCurrSetTimeEdit,_T("AfterAcceTime"));
	pOverCurrFaultEdit->setObjectName(_T("ISet2"));
	//GetLineEditValue(pOverCurrFaultEdit,_T("ISet2"));



	QSttCheckableGroupBox *pZeroOverCurrGroupBox = new QSttCheckableGroupBox();
	pZeroOverCurrGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("零序过流后加速");
	pZeroOverCurrGroupBox->setTitle(strText);
	pZeroOverCurrGroupBox->setCheckable(true);
	pZeroOverCurrGroupBox->setObjectName(_T("Zero_AftAcc_Check"));
	QHBoxLayout *pZeroOverCurrLayout = new QHBoxLayout(pZeroOverCurrGroupBox);
	QLabel *pZeroOverCurrSetTimeLab = new QLabel;
	pZeroOverCurrSetTimeLab->setFont(*g_pSttGlobalFont);
	strText = _T("后加速整定时间(s)");
	pZeroOverCurrSetTimeLab->setText(strText);
	QLineEdit *pZeroOverCurrSetTimeEdit = new QLineEdit;
	pZeroOverCurrSetTimeEdit->setFont(*g_pSttGlobalFont);
	QLabel *pZeroOverCurrFaultLab = new QLabel;
	pZeroOverCurrFaultLab->setFont(*g_pSttGlobalFont);
	strText = _T("重合故障(A)");
	pZeroOverCurrFaultLab->setText(strText);
	QLineEdit *pZeroOverCurrFaultEdit = new QLineEdit;
	pZeroOverCurrFaultEdit->setFont(*g_pSttGlobalFont);
	pZeroOverCurrLayout->addWidget(pZeroOverCurrSetTimeLab);
	pZeroOverCurrLayout->addWidget(pZeroOverCurrSetTimeEdit);
	pZeroOverCurrLayout->addWidget(pZeroOverCurrFaultLab);
	pZeroOverCurrLayout->addWidget(pZeroOverCurrFaultEdit);
	pZeroOverCurrLayout->addStretch();

	m_pAllLineEditList.append(pZeroOverCurrSetTimeEdit);
	m_pAllLineEditList.append(pZeroOverCurrFaultEdit);

	pZeroOverCurrSetTimeEdit->setObjectName(_T("Zero_AfterAcceTime"));
	//GetLineEditValue(pZeroOverCurrSetTimeEdit,_T("Zero_AfterAcceTime"));
	pZeroOverCurrFaultEdit->setObjectName(_T("Zero_ISet2"));
	//GetLineEditValue(pZeroOverCurrFaultEdit,_T("Zero_ISet2"));
	

	m_pEstimateBtn = new QPushButton;
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	strText = _T("结果评估");
	m_pEstimateBtn->setText(strText);
	QHBoxLayout* pHBoxLayout = new QHBoxLayout;
	pHBoxLayout->addStretch(10);
	pHBoxLayout->addWidget(m_pEstimateBtn);


	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(pCurrAccGroupBox);
	pMainLayout->addWidget(pOverCurrGroupBox);
	pMainLayout->addWidget(pZeroAccGroupBox);
	pMainLayout->addWidget(pZeroOverCurrGroupBox);
	pMainLayout->addLayout(pHBoxLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);

	m_pGroupBoxList.append(pCurrAccGroupBox);
	m_pGroupBoxList.append(pOverCurrGroupBox);
	m_pGroupBoxList.append(pZeroAccGroupBox);
	m_pGroupBoxList.append(pZeroOverCurrGroupBox);


	QStringList oList;
	oList << _T("Rec_Check") << _T("AftAcc_Check")<< _T("Zero_Check") << _T("Zero_AftAcc_Check");
	for (int i = 0; i < m_pGroupBoxList.size(); ++i)
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
 		pGroupBox->setObjectName(oList.at(i));
// 		GetGroupBoxCheckable(pGroupBox,oList.at(i));
		connect(pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	}

	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		connect(pLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	}

	connect(m_pRecAccCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ComboBoxChanged(int)));
	connect(m_pZeroAccCombox, SIGNAL(currentIndexChanged(int)), this, SLOT(slot_ComboBoxChanged(int)));


// 	setGroupBoxEnabled(pCurrAccGroupBox,pCurrAccCheck->isChecked());
// 	setGroupBoxEnabled(pZeroAccGroupBox,pZeroAccCheck->isChecked());
// 	setGroupBoxEnabled(pOverCurrGroupBox,pOverCurrCheck->isChecked());

	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_Estimate()));
}

void QSttMacroParaEditViewTURecloseAccWidget::OnViewTestStart()
{
	m_pEstimateBtn->setDisabled(true);

	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setDisabled(true);
	}

	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewTURecloseAccWidget::OnViewTestStop()
{
	m_pEstimateBtn->setDisabled(false);

	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setDisabled(false);
	}

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewTURecloseAccWidget::GetLineEditValue( CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	if (pCurData->m_strDataType == _T("string"))
	{
		pLineEdit->setText(pCurData->m_strValue);
		//pLineEdit->setDisabled(true);
	}
	else
	{
		float fValue = pCurData->m_strValue.toFloat();
		pLineEdit->setText(QString::number(fValue,'f',1));
	}
}

BOOL QSttMacroParaEditViewTURecloseAccWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pTURecloseAccDataGroup);
	}

	return TRUE;
}

void QSttMacroParaEditViewTURecloseAccWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	
	m_pTURecloseAccDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pTURecloseAccDataGroup.CopyChildren(pParas);
	//SaveParasXml();
}

void QSttMacroParaEditViewTURecloseAccWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pTURecloseAccDataGroup);
	}

	for (int i = 0; i < m_pAllLineEditList.size(); i++)
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pTURecloseAccDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}

	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		if (pGroupBox)
		{
			GetGroupBoxCheckable(&m_pTURecloseAccDataGroup,pGroupBox,pGroupBox->objectName());
		}
	}
 	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
 	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
 	g_theTestCntrFrame->InitStateMonitor();
 	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewTURecloseAccWidget::SaveParasXml()
{
// 	m_pTURecloseAccDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
// 	m_pTURecloseAccDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
// 	m_pTURecloseAccDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
// 	m_pTURecloseAccDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_TURecloseAcc_Paras.xml");
	m_pTURecloseAccDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}

void QSttMacroParaEditViewTURecloseAccWidget::slot_Estimate()
{
	QTURecloseAccEstimateDlg dlg(&m_pTURecloseAccDataGroup, this);
	dlg.setFont(*g_pSttGlobalFont);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}




// void QSttMacroParaEditViewTURecloseAccWidget::slot_CheckBoxStateChanged( int )
// {
// 	QSttCheckBox* pCheckBox = qobject_cast<QSttCheckBox*>(sender()); 
// 	if (!pCheckBox)
// 	{
// 		return;
// 	}
// 	CString strID = pCheckBox->objectName();
// 	if (pCheckBox->isChecked()) 
// 	{
// 		m_pTURecloseAccDataGroup.SetDataValue(strID,(long)1);
// 	}
// 	else
// 	{
// 		m_pTURecloseAccDataGroup.SetDataValue(strID,(long)0);
// 	}
// 
// 	int nGroupBoxIndex = -1;
// 
// 	if(strID == _T("OverCurReclose_Check"))
// 	{
// 		nGroupBoxIndex = 0;
// 	}
// 	else if (strID == _T("ZeroReclose_Check"))
// 	{
// 		nGroupBoxIndex = 1;
// 	}
// 	else 
// 	{
// 		nGroupBoxIndex = 2;
// 	}
// 
// 	if(nGroupBoxIndex != -1)
// 	{
// 		setGroupBoxEnabled(m_pGroupBoxList[nGroupBoxIndex],pCheckBox->isChecked());
// 	}
// }

void QSttMacroParaEditViewTURecloseAccWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue,'f',2));
		m_pTURecloseAccDataGroup.SetDataValue(strID,fValue);
	}
}

void QSttMacroParaEditViewTURecloseAccWidget::slot_GroupBoxtoggled( bool )
{
	CString strID;
	QGroupBox* pGroupBox = qobject_cast<QGroupBox*>(sender()); 
	if (pGroupBox)
	{	
		strID = pGroupBox->objectName();
		if (pGroupBox->isChecked()) 
		{
			m_pTURecloseAccDataGroup.SetDataValue(strID,(long)1);
		}
		else
		{
			m_pTURecloseAccDataGroup.SetDataValue(strID,(long)0);
		}
	}
}


// void QSttMacroParaEditViewTURecloseAccWidget::GetCheckBoxValue( QSttCheckBox * pCheckBox,const CString strID )
// {
// 	CDvmData* pCurData = (CDvmData*)m_pTURecloseAccDataGroup.FindByID(strID);
// 	if (pCurData == NULL)
// 	{
// 		return;
// 	}
// 	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
// 	if(nIsSelected)
// 	{
// 		pCheckBox->setChecked(true);;
// 	}
// 	else
// 	{
// 		pCheckBox->setChecked(false);;
// 	}
// }

void QSttMacroParaEditViewTURecloseAccWidget::setGroupBoxEnabled( QGroupBox *pGroupBox, bool enabled )
{
// 	QList<QWidget *> widgets = pGroupBox->findChildren<QWidget *>();
// 	QList<QWidget *>::iterator it;
// 	for (it = widgets.begin(); it != widgets.end(); ++it)
// 	{
// 		QWidget *pWidget = *it;
// 		QLineEdit *pLineEdit = qobject_cast<QLineEdit *>(pWidget);
// 		if (pLineEdit && pLineEdit->objectName().contains(_T("InSection")))
// 		{
// 			pLineEdit->setEnabled(false);
// 		}
//		else
// 		{
// 			pWidget->setEnabled(enabled);
// 		}
// 	}
}

void QSttMacroParaEditViewTURecloseAccWidget::GetComboxValue( CDataGroup *pParas,QComboBox *pComboBox,const CString strID)
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	int nIndex = -1;
	
	CString strValue = pCurData->m_strValue;
	
	if (strValue == _T("Din_7") || strValue == _T("Din_10"))
	{
		nIndex = 0;
	}
	else if (strValue == _T("Din_8") || strValue == _T("Din_11"))
	{
		nIndex = 1;
	}
	else if (strValue == _T("Din_9"))
	{
		nIndex = 2;
	}

	if (nIndex != -1)
	{
		pComboBox->setCurrentIndex(nIndex);
	}
}


void QSttMacroParaEditViewTURecloseAccWidget::slot_ComboBoxChanged( int index )
{
	if (index < 0)
	{
		return;
	}
	CString strValue;
	QComboBox* pComboBox = qobject_cast<QComboBox*>(sender()); 
	if (!pComboBox) return;

	if (pComboBox->objectName() == _T("Zero_Trip_Object")) 
	{
		if (index == 0)
		{
			strValue = _T("Din_10");
		}
		else
		{
			strValue = _T("Din_11");
		}
	}
	else 
	{
		if (index == 0)
		{
			strValue = _T("Din_7");
		}
		else if (index == 1)
		{
			strValue = _T("Din_8");
		}
		else
		{
			strValue = _T("Din_9");
		}
	}
	
	if (!strValue.IsEmpty()) 
	{
		m_pTURecloseAccDataGroup.SetDataValue(pComboBox->objectName(), strValue);
	}
}

QSttCheckBox* QSttMacroParaEditViewTURecloseAccWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
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



void QSttMacroParaEditViewTURecloseAccWidget::GetGroupBoxCheckable(  CDataGroup *pParas,QGroupBox * pGroupBox,CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pGroupBox->setCheckable(true);
		pGroupBox->setChecked(true);
	}
	else
	{
		pGroupBox->setCheckable(true);
		pGroupBox->setChecked(false);
	}
}

void QSttMacroParaEditViewTURecloseAccWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewTURecloseAccWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
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

	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pTURecloseAccDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
}

void QSttMacroParaEditViewTURecloseAccWidget::UpdateDataValue( CDataGroup *pParas,const CString &strID1,const CString &strID2 )
{
	CString strValue,strBinValue,strBinIndex;
	stt_GetDataValueByID(pParas, strID1, strValue);
	if (strValue == _T("0") || strValue == _T("Din_5"))
	{
		if (strValue == _T("0"))//跳闸
		{
			strBinIndex = UpdateDataValue(strID2);
			strBinValue.Format(_T("ActBin_%s$1"),strBinIndex.GetString());
			m_pTURecloseAccDataGroup.SetDataValue(_T("TtripDEnd_Bin"),strBinValue);
		}
		strValue = _T("2");
	}
	else if(strValue == _T("1") || strValue == _T("Din_1"))
	{
		if (strValue == _T("1")) //合闸
		{
			strBinIndex = UpdateDataValue(strID2);
			strBinValue.Format(_T("ActBin_%s$1"),strBinIndex.GetString());
			m_pTURecloseAccDataGroup.SetDataValue(_T("TtripEnd_Bin"),strBinValue);
		}
		strValue = _T("1");
// 		strBinValue.Format(_T("ActBin_%s$1"),strID2.GetString());
// 		m_pTURecloseAccDataGroup.SetDataValue(_T("TtripEnd_Bin"),strBinValue);
	}
	else if(strValue == _T("2") || strValue == _T("Din_2"))
	{
		strValue = _T("0");
// 		strBinValue.Format(_T("ActBin_%s$1"),strID2.GetString());
// 		m_pTURecloseAccDataGroup.SetDataValue(_T("TtripDEnd_Bin"),strBinValue);
	}
	else 
	{
		strValue = _T("3");
	}

	m_pTURecloseAccDataGroup.SetDataValue(strID2, strValue);
}

CString  QSttMacroParaEditViewTURecloseAccWidget::UpdateDataValue( const CString &strID )
{
	CString strBinIndex;
	if (strID == _T("A"))strBinIndex = _T("0");
	else if (strID == _T("B"))strBinIndex = _T("1");
	else if (strID == _T("C"))strBinIndex = _T("2");
	else if (strID == _T("R"))strBinIndex = _T("3");
	return strBinIndex;
}

BOOL QSttMacroParaEditViewTURecloseAccWidget::GetDatas_Reports( CSttReport *pReport,CSttItemBase *pSttItem)
{
	CDvmValues *pDvmValues = pReport->m_pValues;
	CDvmValue *pDvmValue = NULL;
	CString strValue;
	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit->objectName() == _T("Zero_ISet1"))
		{
			strValue = pLineEdit->text();
			pDvmValue = new CDvmValue;
			pDvmValue->m_strName = _T("零序故障态短路电流");
			pDvmValue->m_strID = _T("Zero_ISet1");
			pDvmValue->m_strValue = strValue;
			pDvmValues->AddNewChild(pDvmValue);
			return TRUE;
		}
	}
	return TRUE;
}

QTURecloseAccEstimateDlg::QTURecloseAccEstimateDlg(CDataGroup* pParas,QWidget* parent): QDialog(parent)
{
	setWindowTitle(_T("结果评估"));
	setWindowFlags(Qt::CustomizeWindowHint|Qt::WindowTitleHint| Qt::Dialog);
	resize(400, 200);
	m_pTtripDLineEdit = NULL;
	m_pTtripAccLineEdit = NULL;
	m_pTtripLineEdit= NULL;
	m_pParas = pParas;
	InitUI();
}

QTURecloseAccEstimateDlg::~QTURecloseAccEstimateDlg()
{

}

void QTURecloseAccEstimateDlg::InitUI()
{
	CString strText;
	QLabel *pLabel = new QLabel;
	strText = _T("重合闸动作时间误差(s)");
	pLabel->setFont(*g_pSttGlobalFont);
	pLabel->setText(strText);
	m_pTtripDLineEdit = new QSttLineEdit;
	m_pTtripDLineEdit->setObjectName(_T("TtripD_AbsErr"));
	m_pTtripDLineEdit->setFont(*g_pSttGlobalFont);
	GetLineEditValue(m_pTtripDLineEdit,_T("TtripD_AbsErr"));

// 	QLabel *pLabel1 = new QLabel;
// 	strText = _T("零序重合闸动作时间误差(s)");
// 	pLabel1->setFont(*g_pSttGlobalFont);
// 	pLabel1->setText(strText);
// 	QLineEdit *pLineEdit1 = new QLineEdit;
// 	pLineEdit1->setObjectName(_T("Zero_TtripD_AbsErr"));
// 	GetLineEditValue(pLineEdit1,_T("Zero_TtripD_AbsErr"));

	QLabel *pLabel2 = new QLabel;
	strText = _T("后加速动作时间误差(s)");
	pLabel2->setFont(*g_pSttGlobalFont);
	pLabel2->setText(strText);
	m_pTtripAccLineEdit = new QSttLineEdit;
	m_pTtripAccLineEdit->setFont(*g_pSttGlobalFont);
	m_pTtripAccLineEdit->setObjectName(_T("TtripAcc_AbsErr"));
	GetLineEditValue(m_pTtripAccLineEdit,_T("TtripAcc_AbsErr"));

	QLabel *pLabel3 = new QLabel;
	strText = _T("动作时间误差(s)");
	pLabel3->setFont(*g_pSttGlobalFont);
	pLabel3->setText(strText);
	m_pTtripLineEdit = new QSttLineEdit;
	m_pTtripLineEdit->setFont(*g_pSttGlobalFont);
	m_pTtripLineEdit->setObjectName(_T("Ttrip_AbsErr"));
	GetLineEditValue(m_pTtripLineEdit,_T("Ttrip_AbsErr"));


	QGridLayout *pGridLayout = new QGridLayout;
	pGridLayout->addWidget(pLabel3,0,0,1,1);
	pGridLayout->addWidget(m_pTtripLineEdit,0,1,1,1);
	pGridLayout->addWidget(pLabel,1,0,1,1);
	pGridLayout->addWidget(m_pTtripDLineEdit,1,1,1,1);
	pGridLayout->addWidget(pLabel2,2,0,1,1);
	pGridLayout->addWidget(m_pTtripAccLineEdit,2,1,1,1);
// 	pGridLayout->addWidget(pLabel1,3,0,1,1);
// 	pGridLayout->addWidget(pLineEdit1,3,1,1,1);

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
	pMainVLayout->addLayout(pGridLayout);
	pMainVLayout->addLayout(pOkCancel_HBoxLayout);
	setLayout(pMainVLayout);
	setFocusPolicy(Qt::StrongFocus);

	connect(m_pTtripDLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_TtripDEditFinished()));
	//connect(pLineEdit1, SIGNAL(editingFinished()), this, SLOT(slot_EditFinished()));
	connect(m_pTtripAccLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_TtripAccEditFinished()));
	connect(m_pTtripLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_TtripEditFinished()));
	connect(pOKBtn, SIGNAL(clicked()), this, SLOT(slot_btnOK_Clicked()));
	connect(pCancelBtn, SIGNAL(clicked()), this, SLOT(slot_btnCancel_Clicked()));
}

void QTURecloseAccEstimateDlg::slot_btnOK_Clicked()
{
	m_pParas->SetDataValue(_T("TtripD_AbsErr"),m_pTtripDLineEdit->text());
	m_pParas->SetDataValue(_T("TtripAcc_AbsErr"),m_pTtripAccLineEdit->text());
	m_pParas->SetDataValue(_T("Ttrip_AbsErr"),m_pTtripLineEdit->text());

	close();
}

void QTURecloseAccEstimateDlg::slot_btnCancel_Clicked()
{
	close();
}

void QTURecloseAccEstimateDlg::slot_TtripDEditFinished()
{
	float fValue = m_pTtripDLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pTtripDLineEdit->setText(QString::number(fValue,'f',3));
}

void QTURecloseAccEstimateDlg::slot_TtripAccEditFinished()
{
	float fValue = m_pTtripAccLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pTtripAccLineEdit->setText(QString::number(fValue,'f',3));
}

void QTURecloseAccEstimateDlg::slot_TtripEditFinished()
{
	float fValue = m_pTtripLineEdit->text().toFloat();
	fValue = setLimit(0,200,fValue);
	m_pTtripLineEdit->setText(QString::number(fValue,'f',3));
}

void QTURecloseAccEstimateDlg::GetLineEditValue( QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)m_pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}

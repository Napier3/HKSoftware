#include "SttMacroParaEditViewCurExcLimitWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif

QSttMacroParaEditViewCurExcLimitWidget::QSttMacroParaEditViewCurExcLimitWidget( QWidget *parent /*= 0*/ )
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewCurExcLimitWidget::~QSttMacroParaEditViewCurExcLimitWidget()
{

}

void QSttMacroParaEditViewCurExcLimitWidget::InitUI()
{
	CString strText ,strID;
	QSttCheckableGroupBox *pPressureGroupBox = new QSttCheckableGroupBox();
	pPressureGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBoxList.append(pPressureGroupBox);
	QHBoxLayout *pPressureLayout = new QHBoxLayout(pPressureGroupBox);
// 	QLabel *pPVolLabel = new QLabel;
// 	pPVolLabel->setFont(*g_pSttGlobalFont);
// 	strText = _T("额定电流(A)");
// 	pPVolLabel->setText(strText);
// 	QLineEdit *pPVolEdit = new QLineEdit;
// 	pPVolEdit->setFont(*g_pSttGlobalFont);
// 	pPVolEdit->setEnabled(false);
// 	m_pAllLineEditList.append(pPVolEdit);
	QLabel *pPSetLabel = new QLabel;
	pPSetLabel->setFont(*g_pSttGlobalFont);
	strText = _T("整定值(A)");
	pPSetLabel->setText(strText);
	QLineEdit *pPSetEdit = new QLineEdit;
	pPSetEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(pPSetEdit);
	QLabel *pPSetTimeLabel = new QLabel;
	pPSetTimeLabel->setFont(*g_pSttGlobalFont);
	strText = _T("整定时间(s)");
	pPSetTimeLabel->setText(strText);
	QLineEdit *pPSetTimeEdit = new QLineEdit;
	pPSetTimeEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(pPSetTimeEdit);
// 	QLabel *pPValueLabel = new QLabel;
// 	pPValueLabel->setFont(*g_pSttGlobalFont);
// 	strText = _T("超限值(A)");
// 	pPValueLabel->setText(strText);
// 	QLineEdit *pPValueEdit = new QLineEdit;
// 	pPValueEdit->setFont(*g_pSttGlobalFont);
// 	m_pAllLineEditList.append(pPValueEdit);
//	pPressureLayout->addWidget(pPVolLabel);
//	pPressureLayout->addWidget(pPVolEdit);
	pPressureLayout->addWidget(pPSetLabel);
	pPressureLayout->addWidget(pPSetEdit);
	pPressureLayout->addWidget(pPSetTimeLabel);
	pPressureLayout->addWidget(pPSetTimeEdit);
// 	pPressureLayout->addWidget(pPValueLabel);
// 	pPressureLayout->addWidget(pPValueEdit);
// 	strID = _T("Inom");
// 	pPVolEdit->setObjectName(strID);
	strID = _T("OverCap_SettingValue");
	pPSetEdit->setObjectName(strID);
	strID = _T("OverCap_SettingTime");
	pPSetTimeEdit->setObjectName(strID);
// 	strID = _T("OverCap_Value");
// 	pPValueEdit->setObjectName(strID);


	QSttCheckableGroupBox *pOverVolGroupBox = new QSttCheckableGroupBox();
	pOverVolGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBoxList.append(pOverVolGroupBox);
	QHBoxLayout *pOverLayout = new QHBoxLayout(pOverVolGroupBox);
// 	QLabel *pOverVolLabel = new QLabel;
// 	pOverVolLabel->setFont(*g_pSttGlobalFont);
// 	strText = _T("额定电流(A)");
// 	pOverVolLabel->setText(strText);
// 	QLineEdit *pOverVolEdit = new QLineEdit;
// 	pOverVolEdit->setFont(*g_pSttGlobalFont);
// 	pOverVolEdit->setEnabled(false);
//	m_pAllLineEditList.append(pOverVolEdit);
	QLabel *pOverSetLabel = new QLabel;
	pOverSetLabel->setFont(*g_pSttGlobalFont);
	strText = _T("整定值(A)");
	pOverSetLabel->setText(strText);
	QLineEdit *pOverSetEdit = new QLineEdit;
	pOverSetEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(pOverSetEdit);
	QLabel *pOverSetTimeLabel = new QLabel;
	pOverSetTimeLabel->setFont(*g_pSttGlobalFont);
	strText = _T("整定时间(s)");
	pOverSetTimeLabel->setText(strText);
	QLineEdit *pOverSetTimeEdit = new QLineEdit;
	pOverSetTimeEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(pOverSetTimeEdit);
// 	QLabel *pOverValueLabel = new QLabel;
// 	pOverValueLabel->setFont(*g_pSttGlobalFont);
// 	strText = _T("重载值(A)");
// 	pOverValueLabel->setText(strText);
// 	QLineEdit *pOverValueEdit = new QLineEdit;
// 	pOverValueEdit->setFont(*g_pSttGlobalFont);
// 	m_pAllLineEditList.append(pOverValueEdit);
	//pOverLayout->addWidget(pOverVolLabel);
	//pOverLayout->addWidget(pOverVolEdit);
	pOverLayout->addWidget(pOverSetLabel);
	pOverLayout->addWidget(pOverSetEdit);
	pOverLayout->addWidget(pOverSetTimeLabel);
	pOverLayout->addWidget(pOverSetTimeEdit);
// 	pOverLayout->addWidget(pOverValueLabel);
// 	pOverLayout->addWidget(pOverValueEdit);
// 	strID = _T("Inom");
// 	pOverVolEdit->setObjectName(strID);
	strID = _T("HeavyLoad_SettingValue");
	pOverSetEdit->setObjectName(strID);
	strID = _T("HeavyLoad_SettingTime");
	pOverSetTimeEdit->setObjectName(strID);
// 	strID = _T("HeavyLoad_Value");
// 	pOverValueEdit->setObjectName(strID);



	QSttCheckableGroupBox *pLowVolGroupBox = new QSttCheckableGroupBox();
	pLowVolGroupBox->setFont(*g_pSttGlobalFont);
	m_pGroupBoxList.append(pLowVolGroupBox);
	QHBoxLayout *pLowLayout = new QHBoxLayout(pLowVolGroupBox);
// 	QLabel *pLowVolLabel = new QLabel;
// 	pLowVolLabel->setFont(*g_pSttGlobalFont);
// 	strText = _T("额定电流(A)");
// 	pLowVolLabel->setText(strText);
// 	QLineEdit *pLowVolEdit = new QLineEdit;
// 	pLowVolEdit->setFont(*g_pSttGlobalFont);
// 	pLowVolEdit->setEnabled(false);
// 	m_pAllLineEditList.append(pLowVolEdit);
	QLabel *pLowSetLabel = new QLabel;
	pLowSetLabel->setFont(*g_pSttGlobalFont);
	strText = _T("整定值(A)");
	pLowSetLabel->setText(strText);
	QLineEdit *pLowSetEdit = new QLineEdit;
	pLowSetEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(pLowSetEdit);
	QLabel *pLowSetTimeLabel = new QLabel;
	pLowSetTimeLabel->setFont(*g_pSttGlobalFont);
	strText = _T("整定时间(s)");
	pLowSetTimeLabel->setText(strText);
	QLineEdit *pLowSetTimeEdit = new QLineEdit;
	pLowSetTimeEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(pLowSetTimeEdit);
// 	QLabel *pLowValueLabel = new QLabel;
// 	pLowValueLabel->setFont(*g_pSttGlobalFont);
// 	strText = _T("过载值(A)");
// 	pLowValueLabel->setText(strText);
// 	QLineEdit *pLowValueEdit = new QLineEdit;
// 	pLowValueEdit->setFont(*g_pSttGlobalFont);
// 	m_pAllLineEditList.append(pLowValueEdit);
	//pLowLayout->addWidget(pLowVolLabel);
	//pLowLayout->addWidget(pLowVolEdit);
	pLowLayout->addWidget(pLowSetLabel);
	pLowLayout->addWidget(pLowSetEdit);
	pLowLayout->addWidget(pLowSetTimeLabel);
	pLowLayout->addWidget(pLowSetTimeEdit);
// 	pLowLayout->addWidget(pLowValueLabel);
// 	pLowLayout->addWidget(pLowValueEdit);
// 	strID = _T("Inom");
// 	pLowVolEdit->setObjectName(strID);
	strID = _T("OverLoad_SettingValue");
	pLowSetEdit->setObjectName(strID);
	strID = _T("OverLoad_SettingTime");
	pLowSetTimeEdit->setObjectName(strID);
// 	strID = _T("OverLoad_Value");
// 	pLowValueEdit->setObjectName(strID);


	strText = _T("过负荷");
	pPressureGroupBox->setTitle(strText);
	pPressureGroupBox->setFont(*g_pSttGlobalFont);
	strID = _T("OverCap_Check");
	pPressureGroupBox->setObjectName(strID);
	pPressureGroupBox->setCheckable(true);

	strText = _T("重载");
	pOverVolGroupBox->setTitle(strText);
	pOverVolGroupBox->setFont(*g_pSttGlobalFont);
	strID = _T("HeavyLoad_Check");
	pOverVolGroupBox->setObjectName(strID);
	pOverVolGroupBox->setCheckable(true);

	strText = _T("过载");
	pLowVolGroupBox->setTitle(strText);
	pLowVolGroupBox->setFont(*g_pSttGlobalFont);
	strID = _T("OverLoad_Check");
	pLowVolGroupBox->setObjectName(strID);
	pLowVolGroupBox->setCheckable(true);


	QVBoxLayout* pMainLayout = new QVBoxLayout();
	pMainLayout->addWidget(pPressureGroupBox);
	pMainLayout->addWidget(pOverVolGroupBox);
	pMainLayout->addWidget(pLowVolGroupBox);
	setLayout(pMainLayout);
	setFocusPolicy(Qt::StrongFocus);

	OpenBinBoutMapXml();
	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QSttCheckableGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		connect(pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	}


	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		connect(pLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	}
}

BOOL QSttMacroParaEditViewCurExcLimitWidget::OpenTestTestMngrFile( const CString& strParasFile )
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

	m_pDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);

	return TRUE;
}

void QSttMacroParaEditViewCurExcLimitWidget::OnViewTestStart()
{
	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QSttCheckableGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setDisabled(true);
	}

	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewCurExcLimitWidget::OnViewTestStop()
{
// 	QSttCheckBox* pCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("OverCap_Check"));
// 	setGroupBoxEnabled(m_pGroupBoxList[0],pCheckBox->isChecked());
// 	QSttCheckBox* pOverCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("HeavyLoad_Check"));
// 	setGroupBoxEnabled(m_pGroupBoxList[1],pOverCheckBox->isChecked());
// 	QSttCheckBox* pLowCheckBox = FindCheckBoxByID(m_pAllCheckBoxList, _T("OverLoad_Check"));
// 	setGroupBoxEnabled(m_pGroupBoxList[2],pLowCheckBox->isChecked());
	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QSttCheckableGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setDisabled(false);
	}

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewCurExcLimitWidget::SaveParasXml()
{
	m_pDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);
	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_CurExcLimit_Paras.xml");
	m_pDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}


//void QSttMacroParaEditViewCurExcLimitWidget::setGroupBoxEnabled(QGroupBox *pGroupBox, bool enabled)
//{
//	QList<QWidget *> widgets = pGroupBox->findChildren<QWidget *>();
//	QList<QWidget *>::iterator it;
//	for (it = widgets.begin(); it != widgets.end(); ++it)
//	{
//		QWidget *pWidget = *it;
//		if (pWidget->objectName().contains("RatedCur"))
//		{
//			pWidget->setEnabled(false);
//		}
//		else
//		{
//			pWidget->setEnabled(enabled);
//		}
//	}
//}
//
//QSttCheckBox* QSttMacroParaEditViewCurExcLimitWidget::FindCheckBoxByID( const QList<QSttCheckBox*>& checkBoxList, const CString& strID )
//{
//	for (int i = 0; i < checkBoxList.size(); ++i) 
//	{
//		QSttCheckBox *pCheckBox = checkBoxList.at(i);
//		if (pCheckBox->objectName() == strID)
//		{
//			return pCheckBox;
//		}
//	}
//	return NULL;
//}

void QSttMacroParaEditViewCurExcLimitWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewCurExcLimitWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewCurExcLimitWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	m_pDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
}

void QSttMacroParaEditViewCurExcLimitWidget::SetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);

	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pDataGroup);
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}
	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QSttCheckableGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		if (pGroupBox)
		{
			GetGroupBoxValue(&m_pDataGroup,pGroupBox,pGroupBox->objectName());
		}
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewCurExcLimitWidget::GetLineEditValue( CDataGroup *pParas,QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',2));
}

void QSttMacroParaEditViewCurExcLimitWidget::GetGroupBoxValue(CDataGroup *pParas,QSttCheckableGroupBox * pGroupBox,const CString strID)
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	if(nIsSelected)
	{
		pGroupBox->setChecked(true);;
	}
	else
	{
		pGroupBox->setChecked(false);;
	}
}

void QSttMacroParaEditViewCurExcLimitWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue,'f',2));
		m_pDataGroup.SetDataValue(strID,fValue);
	}
}

void QSttMacroParaEditViewCurExcLimitWidget::slot_GroupBoxtoggled( bool )
{
	QSttCheckableGroupBox* pGroupBox = qobject_cast<QSttCheckableGroupBox*>(sender()); 
	if (!pGroupBox)
	{
		return;
	}
	CString strID = pGroupBox->objectName();
	if (pGroupBox->isChecked()) 
	{
		m_pDataGroup.SetDataValue(strID,(long)1);
	}
	else
	{
		m_pDataGroup.SetDataValue(strID,(long)0);
	}


// 	int nGroupBoxIndex = -1;
// 	if(strID == _T("OverCap_Check"))
// 	{
// 		nGroupBoxIndex = 0;
// 	}
// 	else if (strID == _T("HeavyLoad_Check"))
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
}


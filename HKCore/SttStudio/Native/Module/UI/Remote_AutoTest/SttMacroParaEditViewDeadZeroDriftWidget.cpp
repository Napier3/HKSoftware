#include "SttMacroParaEditViewDeadZeroDriftWidget.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif


QSttMacroParaEditViewDeadZeroDriftWidget::QSttMacroParaEditViewDeadZeroDriftWidget( QWidget *parent /*= 0*/ )
{
	g_pTheSttTestApp->IinitGbWzdAiTool();
	OpenTestTestMngrFile(_T(""));
	InitUI();
	SetDatas(NULL);
}

QSttMacroParaEditViewDeadZeroDriftWidget::~QSttMacroParaEditViewDeadZeroDriftWidget()
{

}

void QSttMacroParaEditViewDeadZeroDriftWidget::InitUI()
{
	CString strText;
	strText = _T("电压死区");
	QSttCheckableGroupBox *pVolDeadGroupBox = new QSttCheckableGroupBox();
	pVolDeadGroupBox->setFont(*g_pSttGlobalFont);
	pVolDeadGroupBox->setTitle(strText);
	QGridLayout *pVolDeadLayout = new QGridLayout(pVolDeadGroupBox);
	QLabel *pVolDeadLab = new QLabel;
	pVolDeadLab->setFont(*g_pSttGlobalFont);
	strText = _T("额定电压(V)");
	pVolDeadLab->setText(strText);
	QLineEdit *pVolDeadEdit = new QLineEdit;
	pVolDeadEdit->setFont(*g_pSttGlobalFont);
	strText = _T("100.00");
	pVolDeadEdit->setText(strText);
	pVolDeadEdit->setEnabled(false);
	QLabel *pVolDeadSetLab = new QLabel;
	pVolDeadSetLab->setFont(*g_pSttGlobalFont);
	strText = _T("初始值(V)");
	pVolDeadSetLab->setText(strText);
	QLineEdit *pVolDeadSetEdit = new QLineEdit;
	pVolDeadSetEdit->setFont(*g_pSttGlobalFont);
	QLabel *pVolBeyondLab = new QLabel;
	pVolBeyondLab->setFont(*g_pSttGlobalFont);
	strText = _T("越死区(V)");
	pVolBeyondLab->setText(strText);
	QLineEdit *pVolBeyondEdit = new QLineEdit;
	pVolBeyondEdit->setFont(*g_pSttGlobalFont);
	QLabel *pVolNBeyondLab = new QLabel;
	pVolNBeyondLab->setFont(*g_pSttGlobalFont);
	strText = _T("非越死区(V)");
	pVolNBeyondLab->setText(strText);
	QLineEdit *pVolNBeyondEdit = new QLineEdit;
	pVolNBeyondEdit->setFont(*g_pSttGlobalFont);
	pVolDeadLayout->addWidget(pVolDeadLab,0,0,1,1);
	pVolDeadLayout->addWidget(pVolDeadEdit,0,1,1,1);
	pVolDeadLayout->addWidget(pVolDeadSetLab,0,2,1,1);
	pVolDeadLayout->addWidget(pVolDeadSetEdit,0,3,1,1);
	pVolDeadLayout->addWidget(pVolBeyondLab,0,4,1,1);
	pVolDeadLayout->addWidget(pVolBeyondEdit,0,5,1,1);
	pVolDeadLayout->addWidget(pVolNBeyondLab,0,6,1,1);
	pVolDeadLayout->addWidget(pVolNBeyondEdit,0,7,1,1);
	
	pVolDeadEdit->setObjectName(_T("VolDead_Uom"));
	pVolDeadSetEdit->setObjectName(_T("VolDead_Initial"));
	pVolBeyondEdit->setObjectName(_T("VolDead_Beyond"));
	pVolNBeyondEdit->setObjectName(_T("VolDead_UnBeyond"));


	m_pAllLineEditList.append(pVolDeadEdit);
	m_pAllLineEditList.append(pVolDeadSetEdit);
	m_pAllLineEditList.append(pVolBeyondEdit);
	m_pAllLineEditList.append(pVolNBeyondEdit);

// 	GetLineEditValue(pVolDeadEdit,_T("VolDead_Uom"));
// 	GetLineEditValue(pVolDeadSetEdit,_T("VolDead_Set"));
// 	GetLineEditValue(pVolBeyondEdit,_T("VolDead_Beyond"));
// 	GetLineEditValue(pVolNBeyondEdit,_T("VolDead_UnBeyond"));


	strText = _T("电流死区");
	QSttCheckableGroupBox *pCurDeadGroupBox = new QSttCheckableGroupBox();
	pCurDeadGroupBox->setFont(*g_pSttGlobalFont);
	pCurDeadGroupBox->setTitle(strText);
	QGridLayout *pCurDeadLayout = new QGridLayout(pCurDeadGroupBox);
	QLabel *pCurDeadLab = new QLabel;
	pCurDeadLab->setFont(*g_pSttGlobalFont);
	strText = _T("额定电流(A)");
	pCurDeadLab->setText(strText);
	QLineEdit *pCurDeadEdit = new QLineEdit;
	pCurDeadEdit->setFont(*g_pSttGlobalFont);
	strText = _T("5.00");
	pCurDeadEdit->setText(strText);
	pCurDeadEdit->setEnabled(false);
	QLabel *pCurDeadSetLab = new QLabel;
	pCurDeadSetLab->setFont(*g_pSttGlobalFont);
	strText = _T("初始值(A)");
	pCurDeadSetLab->setText(strText);
	QLineEdit *pCurDeadSetEdit = new QLineEdit;
	pCurDeadSetEdit->setFont(*g_pSttGlobalFont);
	QLabel *pCurBeyondLab = new QLabel;
	pCurBeyondLab->setFont(*g_pSttGlobalFont);
	strText = _T("越死区(A)");
	pCurBeyondLab->setText(strText);
	QLineEdit *pCurBeyondEdit = new QLineEdit;
	pCurBeyondEdit->setFont(*g_pSttGlobalFont);
	QLabel *pCurNBeyondLab = new QLabel;
	pCurNBeyondLab->setFont(*g_pSttGlobalFont);
	strText = _T("非越死区(A)");
	pCurNBeyondLab->setText(strText);
	QLineEdit *pCurNBeyondEdit = new QLineEdit;
	pCurNBeyondEdit->setFont(*g_pSttGlobalFont);
	pCurDeadLayout->addWidget(pCurDeadLab,0,0,1,1);
	pCurDeadLayout->addWidget(pCurDeadEdit,0,1,1,1);
	pCurDeadLayout->addWidget(pCurDeadSetLab,0,2,1,1);
	pCurDeadLayout->addWidget(pCurDeadSetEdit,0,3,1,1);
	pCurDeadLayout->addWidget(pCurBeyondLab,0,4,1,1);
	pCurDeadLayout->addWidget(pCurBeyondEdit,0,5,1,1);
	pCurDeadLayout->addWidget(pCurNBeyondLab,0,6,1,1);
	pCurDeadLayout->addWidget(pCurNBeyondEdit,0,7,1,1);

	pCurDeadEdit->setObjectName(_T("CurDead_Iom"));
	pCurDeadSetEdit->setObjectName(_T("CurDead_Initial"));
	pCurBeyondEdit->setObjectName(_T("CurDead_Beyond"));
	pCurNBeyondEdit->setObjectName(_T("CurDead_UnBeyond"));


	m_pAllLineEditList.append(pCurDeadEdit);
	m_pAllLineEditList.append(pCurDeadSetEdit);
	m_pAllLineEditList.append(pCurBeyondEdit);
	m_pAllLineEditList.append(pCurNBeyondEdit);

// 	GetLineEditValue(pCurDeadEdit,_T("CurDead_Iom"));
// 	GetLineEditValue(pCurDeadSetEdit,_T("CurDead_Set"));
// 	GetLineEditValue(pCurBeyondEdit,_T("CurDead_Beyond"));
// 	GetLineEditValue(pCurNBeyondEdit,_T("CurDead_UnBeyond"));

	
	strText = _T("电压零漂");
	QSttCheckableGroupBox *pVolZeroGroupBox = new QSttCheckableGroupBox();
	pVolZeroGroupBox->setFont(*g_pSttGlobalFont);
	pVolZeroGroupBox->setTitle(strText);
	QGridLayout *pVolZeroLayout = new QGridLayout(pVolZeroGroupBox);
	QLabel *pVolZeroLab = new QLabel;
	pVolZeroLab->setFont(*g_pSttGlobalFont);
	strText = _T("额定电压(V)");
	pVolZeroLab->setText(strText);
	QLineEdit *pVolZeroEdit = new QLineEdit;
	pVolZeroEdit->setFont(*g_pSttGlobalFont);
	strText = _T("100.00");
	pVolZeroEdit->setText(strText);
	pVolZeroEdit->setEnabled(false);
// 	QLabel *pVolZeroSetLab = new QLabel;
// 	pVolZeroSetLab->setFont(*g_pSttGlobalFont);
// 	strText = _T("初始值(V)");
// 	pVolZeroSetLab->setText(strText);
// 	QLineEdit *pVolZeroSetEdit = new QLineEdit;
// 	pVolZeroSetEdit->setFont(*g_pSttGlobalFont);
	QLabel *pVolBeyondZeroLab = new QLabel;
	pVolBeyondZeroLab->setFont(*g_pSttGlobalFont);
	strText = _T("越零漂(V)");
	pVolBeyondZeroLab->setText(strText);
	QLineEdit *pVolBeyondZeroEdit = new QLineEdit;
	pVolBeyondZeroEdit->setFont(*g_pSttGlobalFont);
	QLabel *pVolNBeyondZeroLab = new QLabel;
	pVolNBeyondZeroLab->setFont(*g_pSttGlobalFont);
	strText = _T("非越零漂(V)");
	pVolNBeyondZeroLab->setText(strText);
	QLineEdit *pVolNBeyondZeroEdit = new QLineEdit;
	pVolNBeyondZeroEdit->setFont(*g_pSttGlobalFont);
	pVolZeroLayout->addWidget(pVolZeroLab,0,0,1,1);
	pVolZeroLayout->addWidget(pVolZeroEdit,0,1,1,1);
// 	pVolZeroLayout->addWidget(pVolZeroSetLab,0,2,1,1);
// 	pVolZeroLayout->addWidget(pVolZeroSetEdit,0,3,1,1);
	pVolZeroLayout->addWidget(pVolBeyondZeroLab,0,4,1,1);
	pVolZeroLayout->addWidget(pVolBeyondZeroEdit,0,5,1,1);
	pVolZeroLayout->addWidget(pVolNBeyondZeroLab,0,6,1,1);
	pVolZeroLayout->addWidget(pVolNBeyondZeroEdit,0,7,1,1);
	
	pVolZeroEdit->setObjectName(_T("VolZero_Uom"));
	//pVolZeroSetEdit->setObjectName(_T("VolZero_Set"));
	pVolBeyondZeroEdit->setObjectName(_T("VolZero_Beyond"));
	pVolNBeyondZeroEdit->setObjectName(_T("VolZero_UnBeyond"));

	m_pAllLineEditList.append(pVolZeroEdit);
	//m_pAllLineEditList.append(pVolZeroSetEdit);
	m_pAllLineEditList.append(pVolBeyondZeroEdit);
	m_pAllLineEditList.append(pVolNBeyondZeroEdit);

// 	GetLineEditValue(pVolZeroEdit,_T("VolZero_Uom"));
// 	GetLineEditValue(pVolZeroSetEdit,_T("VolZero_Set"));
// 	GetLineEditValue(pVolBeyondZeroEdit,_T("VolZero_Beyond"));
// 	GetLineEditValue(pVolNBeyondZeroEdit,_T("VolZero_UnBeyond"));



	strText = _T("电流零漂");
	QSttCheckableGroupBox *pCurZeroGroupBox = new QSttCheckableGroupBox();
	pCurZeroGroupBox->setFont(*g_pSttGlobalFont);
	pCurZeroGroupBox->setTitle(strText);
	QGridLayout *pCurZeroLayout = new QGridLayout(pCurZeroGroupBox);
	QLabel *pCurZeroLab = new QLabel;
	pCurZeroLab->setFont(*g_pSttGlobalFont);
	strText = _T("额定电流(A)");
	pCurZeroLab->setText(strText);
	QLineEdit *pCurZeroEdit = new QLineEdit;
	pCurZeroEdit->setFont(*g_pSttGlobalFont);
	strText = _T("5.00");
	pCurZeroEdit->setText(strText);
	pCurZeroEdit->setEnabled(false);
	//QLabel *pCurZeroSetLab = new QLabel;
// 	pCurZeroSetLab->setFont(*g_pSttGlobalFont);
// 	strText = _T("初始值(A)");
// 	pCurZeroSetLab->setText(strText);
// 	QLineEdit *pCurZeroSetEdit = new QLineEdit;
// 	pCurZeroSetEdit->setFont(*g_pSttGlobalFont);
	QLabel *pCurBeyondZeroLab = new QLabel;
	pCurBeyondZeroLab->setFont(*g_pSttGlobalFont);
	strText = _T("越零漂(A)");
	pCurBeyondZeroLab->setText(strText);
	QLineEdit *pCurBeyondZeroEdit = new QLineEdit;
	pCurBeyondZeroEdit->setFont(*g_pSttGlobalFont);
	QLabel *pCurNBeyondZeroLab = new QLabel;
	pCurNBeyondZeroLab->setFont(*g_pSttGlobalFont);
	strText = _T("非越零漂(A)");
	pCurNBeyondZeroLab->setText(strText);
	QLineEdit *pCurNBeyondZeroEdit = new QLineEdit;
	pCurNBeyondZeroEdit->setFont(*g_pSttGlobalFont);
	pCurZeroLayout->addWidget(pCurZeroLab,0,0,1,1);
	pCurZeroLayout->addWidget(pCurZeroEdit,0,1,1,1);
// 	pCurZeroLayout->addWidget(pCurZeroSetLab,0,2,1,1);
// 	pCurZeroLayout->addWidget(pCurZeroSetEdit,0,3,1,1);
	pCurZeroLayout->addWidget(pCurBeyondZeroLab,0,4,1,1);
	pCurZeroLayout->addWidget(pCurBeyondZeroEdit,0,5,1,1);
	pCurZeroLayout->addWidget(pCurNBeyondZeroLab,0,6,1,1);
	pCurZeroLayout->addWidget(pCurNBeyondZeroEdit,0,7,1,1);


	pCurZeroEdit->setObjectName(_T("CurZero_Iom"));
	//pCurZeroSetEdit->setObjectName(_T("CurZero_Set"));
	pCurBeyondZeroEdit->setObjectName(_T("CurZero_Beyond"));
	pCurNBeyondZeroEdit->setObjectName(_T("CurZero_UnBeyond"));

	m_pAllLineEditList.append(pCurZeroEdit);
	//m_pAllLineEditList.append(pCurZeroSetEdit);
	m_pAllLineEditList.append(pCurBeyondZeroEdit);
	m_pAllLineEditList.append(pCurNBeyondZeroEdit);

// 	GetLineEditValue(pCurZeroEdit,_T("CurZero_Iom"));
// 	GetLineEditValue(pCurZeroSetEdit,_T("CurZero_Set"));
// 	GetLineEditValue(pCurBeyondZeroEdit,_T("CurZero_Beyond"));
// 	GetLineEditValue(pCurNBeyondZeroEdit,_T("CurZero_UnBeyond"));
	

	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(pVolDeadGroupBox);
	pMainLayout->addWidget(pCurDeadGroupBox);
	pMainLayout->addWidget(pVolZeroGroupBox);
	pMainLayout->addWidget(pCurZeroGroupBox);

	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);


	m_pGroupBoxList.append(pVolDeadGroupBox);
	m_pGroupBoxList.append(pCurDeadGroupBox);
	m_pGroupBoxList.append(pVolZeroGroupBox);
	m_pGroupBoxList.append(pCurZeroGroupBox);


	QStringList oList;
	oList << _T("VolDead_Check") << _T("CurDead_Check") << _T("VolZero_Check")<< _T("CurZero_Check");
	for (int i = 0; i < m_pGroupBoxList.size(); ++i)
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setObjectName(oList.at(i));
		connect(pGroupBox, SIGNAL(toggled (bool)), this, SLOT(slot_GroupBoxtoggled(bool)));
	}

	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		connect(pLineEdit, SIGNAL(editingFinished()), this, SLOT(slot_LineEditFinished()));
	}


	OpenBinBoutMapXml();
}

void QSttMacroParaEditViewDeadZeroDriftWidget::OnViewTestStart()
{
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

void QSttMacroParaEditViewDeadZeroDriftWidget::OnViewTestStop()
{
	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		pGroupBox->setDisabled(false);
	}

	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopVectorWidget();
	g_theTestCntrFrame->StopPowerWidget();
}

void QSttMacroParaEditViewDeadZeroDriftWidget::GetGroupBoxValue(CDataGroup *pParas,QSttCheckableGroupBox * pGroupBox,const CString strID)
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	BOOL nIsSelected = CString_To_long(pCurData->m_strValue);
	pGroupBox->setCheckable(true);
	if(nIsSelected)
	{
		pGroupBox->setChecked(true);;
	}
	else
	{
		pGroupBox->setChecked(false);;
	}
}

void QSttMacroParaEditViewDeadZeroDriftWidget::GetLineEditValue( CDataGroup *pParas, QLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	if (pCurData->m_strDataType == _T("string"))
	{
		pLineEdit->setText(pCurData->m_strValue);
		pLineEdit->setDisabled(true);
	}
	else
	{
		float fValue = pCurData->m_strValue.toFloat();
		pLineEdit->setText(QString::number(fValue,'f',2));
	}
}

BOOL QSttMacroParaEditViewDeadZeroDriftWidget::OpenTestTestMngrFile( const CString& strParasFile )
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
		pDataGroup->CopyChildren(&m_pDeadZeroDriftDataGroup);
	}
	return TRUE;
}

void QSttMacroParaEditViewDeadZeroDriftWidget::GetDatas( CDataGroup *pParas )
{
	ASSERT(pParas != NULL);
	pParas->DeleteAll();
	//SaveParasXml();
	m_pDeadZeroDriftDataGroup.CopyChildren(pParas);
}

void QSttMacroParaEditViewDeadZeroDriftWidget::SetDatas(CDataGroup *pParas)
{
	if (pParas != NULL)
	{
		pParas->CopyChildren(&m_pDeadZeroDriftDataGroup);	
	}
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(&m_pDeadZeroDriftDataGroup,pLineEdit,pLineEdit->objectName());
		}
	}
	for (int i = 0; i < m_pGroupBoxList.size(); ++i) 
	{
		QSttCheckableGroupBox *pGroupBox = m_pGroupBoxList.at(i);
		if (pGroupBox)
		{
			GetGroupBoxValue(&m_pDeadZeroDriftDataGroup,pGroupBox,pGroupBox->objectName());
		}
	}

	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL, NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();
}

void QSttMacroParaEditViewDeadZeroDriftWidget::SaveParasXml()
{
	m_pDeadZeroDriftDataGroup.SetDataValue(_T("Unom"),g_oSystemParas.m_fVNom);
	m_pDeadZeroDriftDataGroup.SetDataValue(_T("Inom"),g_oSystemParas.m_fINom);
	m_pDeadZeroDriftDataGroup.SetDataValue(_T("Uzero"),g_oSystemParas.m_fU0_Std);
	m_pDeadZeroDriftDataGroup.SetDataValue(_T("Izero"),g_oSystemParas.m_fI0_Std);

	CString strFile;
	strFile = _P_GetDBPath();
	strFile += _T("atsgen/Remote_DeadZeroDrift_Paras.xml");
	m_pDeadZeroDriftDataGroup.SaveXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
}


void QSttMacroParaEditViewDeadZeroDriftWidget::slot_LineEditFinished()
{
	CString strID;
	QLineEdit* pLineEdit = qobject_cast<QLineEdit*>(sender()); 
	if (pLineEdit)
	{
		strID = pLineEdit->objectName();
		float fValue = pLineEdit->text().toFloat();
		fValue = setLimit(0,999,fValue);
		pLineEdit->setText(QString::number(fValue,'f',2));
		m_pDeadZeroDriftDataGroup.SetDataValue(strID,fValue);
	}
}

void QSttMacroParaEditViewDeadZeroDriftWidget::slot_GroupBoxtoggled( bool )
{
	CString strID;
	QGroupBox* pGroupBox = qobject_cast<QGroupBox*>(sender()); 
	if (pGroupBox)
	{	
		strID = pGroupBox->objectName();
		if (pGroupBox->isChecked()) 
		{
			m_pDeadZeroDriftDataGroup.SetDataValue(strID,(long)1);
		}
		else
		{
			m_pDeadZeroDriftDataGroup.SetDataValue(strID,(long)0);
		}
	}
}


void QSttMacroParaEditViewDeadZeroDriftWidget::OpenBinBoutMapXml()
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

void QSttMacroParaEditViewDeadZeroDriftWidget::UpdateRemoteBoutData( CDataGroup *pParas )
{
	CString strDatasetpath;
	stt_GetDataValueByID(pParas, _T("datasetpath"), strDatasetpath);
	int pos = strDatasetpath.Find(_T('$'));
	if (pos != -1) 
	{
		strDatasetpath = strDatasetpath.Left(pos+1);
		strDatasetpath = strDatasetpath + _T("dsAin");
		m_pDeadZeroDriftDataGroup.SetDataValue(_T("datasetpath"),strDatasetpath);
	}


	long nPhase_Number;
	stt_GetDataValueByID(pParas, _T("Phase_Number"), nPhase_Number);
	m_pDeadZeroDriftDataGroup.SetDataValue(_T("Phase_Number"),nPhase_Number);
}
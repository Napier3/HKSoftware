#include "SttMacroParaEditViewThreeTURecloseAcc.h"
#include "../SttTestCntrFrameBase.h"
#ifdef _USE_SoftKeyBoard_	
#include "../SoftKeyboard/SoftKeyBoard.h"
#endif
#include "../Controls/SttGroupBox.h"
#include "ThreeRecloseEstimateDlg.h"
#include "ThreeRecloseCommonParasDlg.h"

QSttMacroParaEditViewThreeTURecloseAcc* g_pThreeTURecloseAcc = NULL;

QSttMacroParaEditViewThreeTURecloseAcc::QSttMacroParaEditViewThreeTURecloseAcc( QWidget *parent /*= 0*/ )
{
	m_bAfterAccIsChecked = true;
	g_pThreeTURecloseAcc = this;
	m_pThreeRecAccTable = NULL;
	OpenTestTestMngrFile(_T(""));
	InitUI();
	InitConnect();
	SetDatas(&m_pThreeTURecloseAccData);
}

QSttMacroParaEditViewThreeTURecloseAcc::~QSttMacroParaEditViewThreeTURecloseAcc()
{
	for (int i = 0; i < m_pAllLineEditList.size(); ++i)
	{
		delete m_pAllLineEditList.at(i); 
	}
	m_pAllLineEditList.clear(); 
}

void QSttMacroParaEditViewThreeTURecloseAcc::InitUI()
{
	m_pThreeRecAccTable = new QThreeRecloseAccTable(&m_pThreeTURecloseAccData,this);
	m_pThreeRecAccTable->setFont(*g_pSttGlobalFont);
	m_pThreeRecAccTable->horizontalHeader()->setFont(*g_pSttGlobalFont);
	m_pThreeRecAccTable->setFocusPolicy(Qt::NoFocus);
	CString strText;
	QSttGroupBox *pShortCurGroupBox = new QSttGroupBox;
	pShortCurGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("短路电流");
	pShortCurGroupBox->setTitle(strText);
	QGridLayout *pShortCurLayout = new QGridLayout();
	pShortCurGroupBox->setLayout(pShortCurLayout);
	QLabel *pShortCurLabel = new QLabel;
	strText = _T("短路电流(A)");
	pShortCurLabel->setText(strText);
	pShortCurLabel->setFont(*g_pSttGlobalFont);
	m_pShortCurEdit = new QSttLineEdit;
	m_pShortCurEdit->setObjectName(_T("ISet1"));
	m_pShortCurEdit->setFont(*g_pSttGlobalFont);
	QLabel *pShortTimeLabel = new QLabel;
	pShortTimeLabel->setFont(*g_pSttGlobalFont);
	strText = _T("动作时间定值(s)");
	pShortTimeLabel->setText(strText);
	m_pShortTimeEdit = new QSttLineEdit;
	m_pShortTimeEdit->setFont(*g_pSttGlobalFont);
	m_pShortTimeEdit->setObjectName(_T("TripTime"));
	pShortCurLayout->addWidget(pShortCurLabel,0,0,1,1);
	pShortCurLayout->addWidget(m_pShortCurEdit,0,1,1,1);
	pShortCurLayout->addWidget(pShortTimeLabel,1,0,1,1);
	pShortCurLayout->addWidget(m_pShortTimeEdit,1,1,1,1);
	
	m_pAllLineEditList.append(m_pShortCurEdit);
	m_pAllLineEditList.append(m_pShortTimeEdit);

	QSttGroupBox *pAccGroupBox = new QSttGroupBox;
	pAccGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("后加速");
	pAccGroupBox->setTitle(strText);
	QGridLayout *pAccLayout = new QGridLayout();
	pAccGroupBox->setLayout(pAccLayout);
	m_pAccCurLabel = new QLabel;
	strText = _T("短路电流(A)");
	m_pAccCurLabel->setText(strText);
	m_pAccCurLabel->setFont(*g_pSttGlobalFont);
	m_pAccCurEdit = new QSttLineEdit;
	m_pAccCurEdit->setFont(*g_pSttGlobalFont);
	m_pAccCurEdit->setObjectName(_T("ISet2"));
	m_pAccTimeLabel = new QLabel;
	m_pAccTimeLabel->setFont(*g_pSttGlobalFont);
	strText = _T("后加速时间定值(s)");
	m_pAccTimeLabel->setText(strText);
	m_pAccTimeEdit = new QSttLineEdit;
	m_pAccTimeEdit->setFont(*g_pSttGlobalFont);
	m_pAccTimeEdit->setObjectName(_T("AfterAcceTime"));
	pAccLayout->addWidget(m_pAccCurLabel,0,0,1,1);
	pAccLayout->addWidget(m_pAccCurEdit,0,1,1,1);
	pAccLayout->addWidget(m_pAccTimeLabel,1,0,1,1);
	pAccLayout->addWidget(m_pAccTimeEdit,1,1,1,1);
	m_pAllLineEditList.append(m_pAccCurEdit);
	m_pAllLineEditList.append(m_pAccTimeEdit);
	CDvmData *pCurData = (CDvmData*)m_pThreeTURecloseAccData.FindByID(_T("AftAcc_Check"));
	if (pCurData->m_strValue == "0")
	{
		slot_Grp_AftAccGroupEnabled(false);
	}
	else
	{
		slot_Grp_AftAccGroupEnabled(true);
	}
	

	QSttGroupBox *pTimeGroupBox = new QSttGroupBox;
	pTimeGroupBox->setFont(*g_pSttGlobalFont);
	strText = _T("时间参数");
	pTimeGroupBox->setTitle(strText);
	QGridLayout *pTimeLayout = new QGridLayout();
	pTimeGroupBox->setLayout(pTimeLayout);
	QLabel *pFaultTimeLabel = new QLabel;
	pFaultTimeLabel->setFont(*g_pSttGlobalFont);
	strText = _T("故障前时间(s)");
	pFaultTimeLabel->setText(strText);
	m_pFaultTimeEdit = new QSttLineEdit;
	m_pFaultTimeEdit->setFont(*g_pSttGlobalFont);
	QLabel *pFaultMarginTimeLabel = new QLabel;
	pFaultMarginTimeLabel->setFont(*g_pSttGlobalFont);
	strText = _T("故障时间裕度(s)");
	pFaultMarginTimeLabel->setText(strText);
	m_pFaultMarginTimeEdit = new QSttLineEdit;
	m_pFaultMarginTimeEdit->setFont(*g_pSttGlobalFont);
	m_pAllLineEditList.append(m_pFaultTimeEdit);
	m_pAllLineEditList.append(m_pFaultMarginTimeEdit);
	m_pFaultTimeEdit->setObjectName(_T("PreFaultTime"));
	m_pFaultMarginTimeEdit->setObjectName(_T("FaultTime"));
	pTimeLayout->addWidget(pFaultTimeLabel,0,0,1,1);
	pTimeLayout->addWidget(m_pFaultTimeEdit,0,1,1,1);
	pTimeLayout->addWidget(pFaultMarginTimeLabel,1,0,1,1);
	pTimeLayout->addWidget(m_pFaultMarginTimeEdit,1,1,1,1);


	QHBoxLayout *pGroupLayout = new QHBoxLayout;
	pGroupLayout->addWidget(pShortCurGroupBox);
	pGroupLayout->addWidget(pAccGroupBox);
	pGroupLayout->addWidget(pTimeGroupBox);

	m_pEstimateBtn = new QPushButton;
	m_pEstimateBtn->setFont(*g_pSttGlobalFont);
	strText = _T("结果评估");
	m_pEstimateBtn->setText(strText);
	m_pCommonParasBtn= new QPushButton;
	m_pCommonParasBtn->setFont(*g_pSttGlobalFont);
	strText = _T("通用参数");
	m_pCommonParasBtn->setText(strText);

	QHBoxLayout *pBtnLayout = new QHBoxLayout;
	pBtnLayout->addStretch(20);
	pBtnLayout->addWidget(m_pEstimateBtn);
	pBtnLayout->addWidget(m_pCommonParasBtn);


	QVBoxLayout *pMainLayout = new QVBoxLayout;
	pMainLayout->addWidget(m_pThreeRecAccTable);
	pMainLayout->addLayout(pGroupLayout);
	pMainLayout->addLayout(pBtnLayout);
	setLayout(pMainLayout);	
	setFocusPolicy(Qt::StrongFocus);
}

void QSttMacroParaEditViewThreeTURecloseAcc::InitConnect()
{
	connect(m_pEstimateBtn, SIGNAL(clicked()), this, SLOT(slot_EstimateBtnClicked()));	
	connect(m_pCommonParasBtn, SIGNAL(clicked()), this, SLOT(slot_CommonParasBtnClicked()));	
	connect(m_pShortCurEdit, SIGNAL(editingFinished ()), this, SLOT(slot_lne_ShortCurChanged()));
	connect(m_pShortTimeEdit, SIGNAL(editingFinished ()), this, SLOT(slot_lne_ShortTimeChanged()));
	connect(m_pAccCurEdit, SIGNAL(editingFinished ()), this, SLOT(slot_lne_AccCurChanged()));
	connect(m_pAccTimeEdit, SIGNAL(editingFinished ()), this, SLOT(slot_lne_AccTimeChanged()));
	connect(m_pFaultTimeEdit, SIGNAL(editingFinished ()), this, SLOT(slot_lne_FaultTimeChanged()));
	connect(m_pFaultMarginTimeEdit, SIGNAL(editingFinished ()), this, SLOT(slot_lne_FaultMarginTimeChanged()));
	connect(m_pThreeRecAccTable, SIGNAL(sig_AftAccCheckStateChanged(bool)), this, SLOT(slot_Grp_AftAccGroupEnabled(bool)));
}
void QSttMacroParaEditViewThreeTURecloseAcc::OnViewTestStart()
{
	m_pThreeRecAccTable->setDisabled(true);
	m_pEstimateBtn->setDisabled(true);
	m_pCommonParasBtn->setDisabled(true);

  	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
  	{
  		QSttLineEdit *pLineEdit = m_pAllLineEditList.at(i);
  		pLineEdit->setDisabled(true);
  	}

	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
}

void QSttMacroParaEditViewThreeTURecloseAcc::OnViewTestStop()
{
	m_pThreeRecAccTable->setDisabled(false);
	m_pEstimateBtn->setDisabled(false);
	m_pCommonParasBtn->setDisabled(false);
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QSttLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		pLineEdit->setDisabled(false);
	}
	if (m_bAfterAccIsChecked == false)
	{
		slot_Grp_AftAccGroupEnabled(false);//后加速状态再次刷新
	}
	m_pThreeRecAccTable->UpdateRecSetValue();
	m_pThreeRecAccTable->UpdateTestItemState();
	g_theTestCntrFrame->StopVectorWidget(false);
	g_theTestCntrFrame->StopStateMonitor();
	g_theTestCntrFrame->StopPowerWidget();
}


BOOL QSttMacroParaEditViewThreeTURecloseAcc::OpenTestTestMngrFile( const CString& strParasFile )
{
	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
	{
		return FALSE;
	}

	if ((m_pThreeTURecloseAccData.GetCount()<=0)&&(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile.GetLength()>0))
	{
		stt_ui_OpenParasFile(g_pTheSttTestApp->m_pTestMacroUI->m_strUI_ParaFile,&m_pThreeTURecloseAccData);
	}
	return TRUE;
}

void QSttMacroParaEditViewThreeTURecloseAcc::SetDatas( CDataGroup *pParas )
{
	for (int i = 0; i < m_pAllLineEditList.size(); ++i) 
	{
		QSttLineEdit *pLineEdit = m_pAllLineEditList.at(i);
		if (pLineEdit)
		{
			GetLineEditValue(pParas,pLineEdit,pLineEdit->objectName());
		}
	}


	m_pThreeRecAccTable->UpdateTableData(pParas);
	g_theTestCntrFrame->InitVectorWidget(NULL, NULL);
	g_theTestCntrFrame->InitPowerWidget(NULL,NULL);
	g_theTestCntrFrame->InitStateMonitor();
	g_theTestCntrFrame->ClearInfoWidget();	
}

void QSttMacroParaEditViewThreeTURecloseAcc::GetDatas( CDataGroup *pParas )
{
 	ASSERT(pParas != NULL);
 	pParas->DeleteAll();
	m_pThreeTURecloseAccData.CopyChildren(pParas);
}


void QSttMacroParaEditViewThreeTURecloseAcc::GetLineEditValue( CDataGroup *pParas,QSttLineEdit * pLineEdit,const CString strID )
{
	CDvmData* pCurData = (CDvmData*)pParas->FindByID(strID);
	if (pCurData == NULL)
	{
		return;
	}
	float fValue = pCurData->m_strValue.toFloat();
	pLineEdit->setText(QString::number(fValue,'f',3));
}



void QSttMacroParaEditViewThreeTURecloseAcc::slot_EstimateBtnClicked()
{
	QThreeRecloseEstimateDlg dlg(&m_pThreeTURecloseAccData,this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}

void QSttMacroParaEditViewThreeTURecloseAcc::slot_CommonParasBtnClicked()
{
	QThreeRecloseCommonParasDlg dlg(&m_pThreeTURecloseAccData,this);
	dlg.setWindowModality(Qt::WindowModal);
#ifdef _USE_SoftKeyBoard_
	QSoftKeyBoard::AttachObj(&dlg);
	dlg.exec();
	QSoftKeyBoard::ReAttachObj();
#else
	dlg.exec();
#endif
}



void QSttMacroParaEditViewThreeTURecloseAcc::slot_lne_ShortCurChanged()
{
	float fv = m_pShortCurEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pShortCurEdit->setText(QString::number(fv,'f',3));
	m_pThreeTURecloseAccData.SetDataValue(m_pShortCurEdit->objectName(),fv);
}

void QSttMacroParaEditViewThreeTURecloseAcc::slot_lne_ShortTimeChanged()
{
	float fv = m_pShortTimeEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pShortTimeEdit->setText(QString::number(fv,'f',3));
	m_pThreeTURecloseAccData.SetDataValue(m_pShortTimeEdit->objectName(),fv);
}

void QSttMacroParaEditViewThreeTURecloseAcc::slot_lne_AccCurChanged()
{
	float fv = m_pAccCurEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pAccCurEdit->setText(QString::number(fv,'f',3));
	m_pThreeTURecloseAccData.SetDataValue(m_pAccCurEdit->objectName(),fv);
}

void QSttMacroParaEditViewThreeTURecloseAcc::slot_lne_AccTimeChanged()
{
	float fv = m_pAccTimeEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pAccTimeEdit->setText(QString::number(fv,'f',3));
	m_pThreeTURecloseAccData.SetDataValue(m_pAccTimeEdit->objectName(),fv);
}

void QSttMacroParaEditViewThreeTURecloseAcc::slot_lne_FaultTimeChanged()
{
	float fv = m_pFaultTimeEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pFaultTimeEdit->setText(QString::number(fv,'f',3));

	m_pThreeTURecloseAccData.SetDataValue(m_pFaultTimeEdit->objectName(),fv);
}

void QSttMacroParaEditViewThreeTURecloseAcc::slot_lne_FaultMarginTimeChanged()
{
	float fv = m_pFaultMarginTimeEdit->text().toFloat();
	fv = setLimit(0,999.999,fv);
	m_pFaultMarginTimeEdit->setText(QString::number(fv,'f',3));
	m_pThreeTURecloseAccData.SetDataValue(m_pFaultMarginTimeEdit->objectName(),fv);
}

void QSttMacroParaEditViewThreeTURecloseAcc::slot_Grp_AftAccGroupEnabled(bool bChecked)
{
	m_pAccTimeLabel->setEnabled(bChecked);
	m_pAccCurEdit->setEnabled(bChecked);
	m_pAccCurLabel->setEnabled(bChecked);
	m_pAccTimeEdit->setEnabled(bChecked);
	m_bAfterAccIsChecked = bChecked;
}


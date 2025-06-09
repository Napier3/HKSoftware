#include <QMessageBox>
#include "SttIecGoutWidget.h"
#include <QDebug>
#include <fstream>
#include <QEvent>
#include <QKeyEvent>
#include <QHeaderView>
#include "SttIecSMV92OtherSetDialog.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../Module/CommonMethod/commonMethod.h"
//#include "../SttTestCntrFrameBase.h"

QSttIecGoutWidget::QSttIecGoutWidget(QFont oIecFont,QWidget *parent)
	: QSttIecConfigWidgetBase(parent)
{
	m_oIecFont = oIecFont;
	SetFont(m_oIecFont);
	InitUI();
	initConnect();
//	m_blockTableView->installEventFilter(this);
	this->installEventFilter(this);
}

QSttIecGoutWidget::~QSttIecGoutWidget()
{
}

void QSttIecGoutWidget::InitUI()
{
 	QSttIecConfigWidgetBase::InitUI();
 	CreateToolbar();
	SetIecGoutFont();

	m_pIecCfgDataGridBase = new CIecCfgGoutDataGrid(this);
	m_pIecCfgDataGridBase->horizontalHeader()->setFont(*g_pSttGlobalFont);//2022-10-22 sy 修改为*g_pSttGlobalFont
	m_pIecCfgDataGridBase->setFont(*g_pSttGlobalFont);
	m_pIecCfgDataGridBase->InitGrid();

 	m_pMainVLayout = new QVBoxLayout;
 	setLayout(m_pMainVLayout);
	m_pMainVLayout->addLayout(m_pGoutFirstHLayout);
	m_pMainVLayout->addWidget(m_pIecCfgDataGridBase);
	m_pMainVLayout->addLayout(m_pCtrlBlocksSetHLayout);
}

void QSttIecGoutWidget::CreateToolbar()
{
	m_pT1_LineEdit = new QLongLineEdit();
	m_pT0_LineEdit = new QLongLineEdit();
	m_pTimeQuality_LineEdit = new QIecLineEdit(QIecLineEdit::HEX_TEXT,_T("00"));
	m_pGroupDelay_LineEdit = new QLongLineEdit();

	CString strTemp;

	xlang_GetLangStrByFile(strTemp,"IEC_T1Times");
	m_pT1Times_Label = new QLabel(strTemp);
	m_pGoutFirstHLayout = new QHBoxLayout;
	m_pGoutFirstHLayout->addWidget(m_pT1Times_Label);
	m_pGoutFirstHLayout->addWidget(m_pT1_LineEdit);

 	xlang_GetLangStrByFile(strTemp,"IEC_T0Times");
	m_pT0Times_Label = new QLabel(strTemp);
	m_pGoutFirstHLayout->addWidget(m_pT0Times_Label/*new QLabel(strTemp)*/); 
	m_pGoutFirstHLayout->addWidget(m_pT0_LineEdit);
	
 	xlang_GetLangStrByFile(strTemp,"IEC_TimeQuality");
	m_pTimeQuality_Label = new QLabel(strTemp);
	m_pGoutFirstHLayout->addWidget(m_pTimeQuality_Label/*new QLabel(strTemp)*/);
	m_pGoutFirstHLayout->addWidget(m_pTimeQuality_LineEdit);

	xlang_GetLangStrByFile(strTemp,"IEC_GroupDelay");
	m_pGroupDelay_Label = new QLabel(strTemp);
	m_pGoutFirstHLayout->addWidget(m_pGroupDelay_Label);
	m_pGoutFirstHLayout->addWidget(m_pGroupDelay_LineEdit);
	m_pGoutFirstHLayout->addStretch();

 	m_pGroupDelay_Label->setVisible(false);
 	m_pGroupDelay_LineEdit->setVisible(false);
}

void QSttIecGoutWidget::SetIecGoutFont()
{
	m_pGroupDelay_LineEdit->setFont(*g_pSttGlobalFont);
	m_pT0_LineEdit->setFont(*g_pSttGlobalFont);
	m_pT1_LineEdit->setFont(*g_pSttGlobalFont);
	m_pTimeQuality_LineEdit->setFont(*g_pSttGlobalFont);
	m_pT0Times_Label->setFont(*g_pSttGlobalFont);
	m_pT1Times_Label->setFont(*g_pSttGlobalFont);
	m_pTimeQuality_Label->setFont(*g_pSttGlobalFont);
	m_pGroupDelay_Label->setFont(*g_pSttGlobalFont);

}

void QSttIecGoutWidget::initConnect()
{
	connect(m_pTimeQuality_LineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_TimeQualityEditClicked()),Qt::UniqueConnection);
#ifdef _PSX_QT_LINUX_
	connect(m_pT1_LineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_T1EditClicked()));
	connect(m_pT0_LineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_T0EditClicked()));
	connect(m_pGroupDelay_LineEdit, SIGNAL(clicked()), this, SLOT(slot_lne_GroupDelayEditClicked()));
#endif

	connect(m_pT1_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_T1Edit_editingFinished()));
	connect(m_pT0_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_T0Edit_editingFinished()));
	connect(m_pGroupDelay_LineEdit, SIGNAL(editingFinished()), this, SLOT(slot_lne_GroupDelayEdit_editingFinished()));
}

void QSttIecGoutWidget::InitData(CIecCfgDatasBase* pIecCfgDatasBase)
{
	ASSERT(pIecCfgDatasBase);
 	QSttIecConfigWidgetBase::InitData(pIecCfgDatasBase);
 	CIecCfgGoutDatas* pIecCfgGoutDatas = (CIecCfgGoutDatas*)pIecCfgDatasBase;
 	m_pT1_LineEdit->InitCoverage(1,500000);
 	m_pT1_LineEdit->SetValue(2);
	m_pT0_LineEdit->InitCoverage(1,500000);
	m_pT0_LineEdit->SetValue(5000);
	m_pTimeQuality_LineEdit->InitHexFormat(1);
	m_pGroupDelay_LineEdit->InitCoverage(0,500000);
	m_pGroupDelay_LineEdit->SetValue((long)0);

 	CIecCfgGoutData* pIecCfgGoutData = (CIecCfgGoutData*)pIecCfgGoutDatas->FindByClassID(CFGCLASSID_CIECCFGGOUTDATA);
 
 	if (pIecCfgGoutData != NULL)
 	{
		CString strTmp = pIecCfgGoutData->m_strTQuality;
		long nTQuality = 0x0;
		HexToLong(strTmp.GetString(),nTQuality);
		strTmp.Format(_T("0x%02X"),nTQuality);
 		m_pT1_LineEdit->SetValue(pIecCfgGoutData->m_nT1);
		m_pT0_LineEdit->SetValue(pIecCfgGoutData->m_nT0);
		m_pTimeQuality_LineEdit->setText(strTmp);
		m_pGroupDelay_LineEdit->SetValue(pIecCfgGoutData->m_nTGroup);
	}
}

void QSttIecGoutWidget::SaveData()
{
	CIecCfgGoutDatas* pIecCfgGoutDatas = (CIecCfgGoutDatas*)m_pIecCfgDatasBase;
	long nT1 = m_pT1_LineEdit->GetValue();
	long nT0 = m_pT0_LineEdit->GetValue();
	CString strTQuality = m_pTimeQuality_LineEdit->text();
	long nGroupDelay = m_pGroupDelay_LineEdit->GetValue();
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutData *pIecCfgGoutData = NULL;
	POS pos = pIecCfgGoutDatas->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGoutDatas->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			pIecCfgGoutData = (CIecCfgGoutData *)pCurObj;
			pIecCfgGoutData->m_nT1 = nT1;
			pIecCfgGoutData->m_nT0 = nT0;
			pIecCfgGoutData->m_strTQuality = strTQuality;
			pIecCfgGoutData->m_nTGroup = nGroupDelay;
		}
	}
}


bool QSttIecGoutWidget::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress) 
	{
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);

		if (keyEvent->key() == Qt::Key_Down) 
		{	
		}
		else if (keyEvent->key() == Qt::Key_Up)
		{
		}
		else if (keyEvent->key() == Qt::Key_Escape)
		{
			//SaveBlockModel();
			return true;
		}

		return false;
	}else{
		return false;
	}
}

void QSttIecGoutWidget::slot_lne_T1EditClicked()
{
	CString strValue;
	strValue.Format("%ld",m_pT1_LineEdit->GetValue());
	GetWidgetBoard_DigitData(4, strValue,m_pT1_LineEdit, this);
// 	m_pT1_LineEdit->setText(strValue);
// 	m_pT1_LineEdit->SetEditFinished();
	
	/*
	WidgetKeyboardV_Digit dlg(4,this);
	CString strTemp;
	strTemp.Format("%ld",m_pT1_LineEdit->GetValue());
	dlg.m_strEditInfo = strTemp;
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_pT1_LineEdit->setText(dlg.m_strEditInfo);
	}

	m_pT1_LineEdit->SetEditFinished();
	*/
}
void QSttIecGoutWidget::slot_lne_T1Edit_editingFinished()
{
	CString strValue;
	strValue.Format("%ld",m_pT1_LineEdit->GetValue());
	m_pT1_LineEdit->setText(strValue);
// 	m_pT1_LineEdit->SetEditFinished();
	
}
void QSttIecGoutWidget::slot_lne_T0EditClicked()
{
	CString strValue;
	strValue.Format("%ld",m_pT0_LineEdit->GetValue());
	GetWidgetBoard_DigitData(4, strValue,m_pT0_LineEdit, this);
// 	m_pT0_LineEdit->setText(strValue);
// 	m_pT0_LineEdit->SetEditFinished();

	/*
	WidgetKeyboardV_Digit dlg(4,this);
	CString strTemp;
	strTemp.Format("%ld",m_pT0_LineEdit->GetValue());
	dlg.m_strEditInfo = strTemp;
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_pT0_LineEdit->setText(dlg.m_strEditInfo);
	}

	m_pT0_LineEdit->SetEditFinished();
	*/
}
void QSttIecGoutWidget::slot_lne_T0Edit_editingFinished()
{
	CString strValue;
	strValue.Format("%ld",m_pT0_LineEdit->GetValue());
	m_pT0_LineEdit->setText(strValue);
// 	m_pT0_LineEdit->SetEditFinished();

}

void QSttIecGoutWidget::slot_lne_TimeQualityEditClicked()
{
	QString strValue = m_pTimeQuality_LineEdit->text();
	GetEngWidgetBoard_DigitData(strValue, this);
	m_pTimeQuality_LineEdit->setText(strValue);
	m_pTimeQuality_LineEdit->SetEditFinished();

	/*
	WidgetKeyboard dlg(this);
	dlg.m_InputString = m_pTimeQuality_LineEdit->text();
	dlg.showToEdit();
	if (dlg.exec() == QDialog::Accepted)
	{
		m_pTimeQuality_LineEdit->setText(dlg.m_InputString);
	}
	m_pTimeQuality_LineEdit->SetEditFinished();
	*/
}

void QSttIecGoutWidget::slot_lne_GroupDelayEditClicked()
{
	CString strValue;
	strValue.Format("%ld",m_pGroupDelay_LineEdit->GetValue());
	GetWidgetBoard_DigitData(4, strValue,m_pGroupDelay_LineEdit, this);
// 	m_pGroupDelay_LineEdit->setText(strValue);
// 	m_pGroupDelay_LineEdit->SetEditFinished();

	/*
	WidgetKeyboardV_Digit dlg(4,this);
	CString strTemp;
	strTemp.Format("%ld",m_pGroupDelay_LineEdit->GetValue());
	dlg.m_strEditInfo = strTemp;
	dlg.showToEdit();
	if (dlg.exec()==QDialog::Accepted)
	{
		m_pGroupDelay_LineEdit->setText(dlg.m_strEditInfo);
	}

	m_pGroupDelay_LineEdit->SetEditFinished();
	*/
}
void QSttIecGoutWidget::slot_lne_GroupDelayEdit_editingFinished()
{
	CString strValue;
	strValue.Format("%ld",m_pGroupDelay_LineEdit->GetValue());
	m_pGroupDelay_LineEdit->setText(strValue);
// 	m_pGroupDelay_LineEdit->SetEditFinished();
}

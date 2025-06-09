#include "SynAddMultQuickDlg.h"
#include "ui_SynAddMultQuickDlg.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "SttMultiMacroSynParasDefine.h"
#include "../Distance/DistanceCommonParasDlg.h"
QSynAddMultQuickDlg::QSynAddMultQuickDlg(QWidget *parent ): 
	QDialog(parent),
	ui(new Ui::QSynAddMultQuickDlg)
{
	ui->setupUi(this);

	CString strText;
	strText = _T(g_sLangTxt_Button_AddMultQuick);
	setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);
	this->setWindowTitle(strText);

	m_pDataGroup = NULL;

	initData();
	SetParasFont();
	InitLanuage();
	initConnections();

}


void QSynAddMultQuickDlg::SetParasFont()
{
	ui->m_pUPlusLabel->setFont(*g_pSttGlobalFont);
	ui->m_pUMinusLabel->setFont(*g_pSttGlobalFont);
	ui->m_pFPlusLabel->setFont(*g_pSttGlobalFont);
	ui->m_pFMinusLabel->setFont(*g_pSttGlobalFont);
	ui->m_pUPlusEdit->setFont(*g_pSttGlobalFont);
	ui->m_pUMinusEdit->setFont(*g_pSttGlobalFont);
	ui->m_pFPlusEdit->setFont(*g_pSttGlobalFont);
	ui->m_pFMinusEdit->setFont(*g_pSttGlobalFont);
	ui->m_pCancel_PushButton->setFont(*g_pSttGlobalFont);
	ui->m_pOK_PushButton->setFont(*g_pSttGlobalFont);
	
}


void QSynAddMultQuickDlg::CheckAllPresence()
{
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UPlus);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UMinus);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FPlus);
	CheckForPresence(STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FMinus);
}

void QSynAddMultQuickDlg::CheckForPresence(CString strID)
{
	if(m_pDataGroup == NULL)
		return;
	CDvmData *pData = (CDvmData *)m_pDataGroup->FindByID(strID);
	if(pData == NULL)
	{
		CDvmData *pNew = new CDvmData();
		pNew->m_strName = strID;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_SYN_PARAS_ID_DEFAULT;
		m_pDataGroup->AddNewChild(pNew);
	}
}

void QSynAddMultQuickDlg::SetDatas(CDataGroup *pDataset)
{
	if (pDataset == NULL)
		return;
	m_pDataGroup = pDataset;

	CheckAllPresence();

	POS pos = pDataset->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pDataset->GetNext(pos);
		SetValueToPage(pData);
	}
}

void QSynAddMultQuickDlg::SetValueToPage(CDvmData *pData)
{
	if(pData == NULL)
		return;
	
	if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UPlus)
	{
		ui->m_pUPlusEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UMinus)
	{
		ui->m_pUMinusEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FPlus)
	{
		ui->m_pFPlusEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FMinus)
	{
		ui->m_pFMinusEdit->setText(CheckDataMinMax(pData->m_strValue,999,0,3));
	}
}

void QSynAddMultQuickDlg::GetDatas(CDataGroup *pParas)
{
	if(pParas == NULL)
		return;
	m_pDataGroup = pParas;
	CheckAllPresence();
	//20240614 luozibing 将界面中的参数保存到链表中
	POS pos = pParas->GetHeadPosition();
	while(pos!=NULL)
	{
		CDvmData *pData = (CDvmData*)pParas->GetNext(pos);
		GetPageToValue(pData);
	}
	
}


void QSynAddMultQuickDlg::GetPageToValue(CDvmData *pData)
{
	if(pData == NULL)
		return;
	bool bvalue;
	if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UPlus)
	{
		pData->m_strValue = ui->m_pUPlusEdit->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_UMinus)
	{
		pData->m_strValue = ui->m_pUMinusEdit->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FPlus)
	{
		pData->m_strValue = ui->m_pFPlusEdit->text();
	}
	else if (pData->m_strID == STT_MULTI_MACRO_SYN_PARAS_ID_QUICK_FMinus)
	{
		pData->m_strValue = ui->m_pFMinusEdit->text();
	}
}

void QSynAddMultQuickDlg::initData()
{
#ifdef _PSX_QT_WINDOWS_
	ui->m_pOK_PushButton->setIcon (QPixmap( ":/image/check.png"));
	ui->m_pCancel_PushButton->setIcon (QPixmap( ":/image/Cancel.png"));
#else
	ui->m_pOK_PushButton->setIcon (QPixmap( ":/ctrls/images/check.png"));
	ui->m_pCancel_PushButton->setIcon (QPixmap( ":/ctrls/images/Cancel.png"));
#endif

}


void QSynAddMultQuickDlg::initConnections()
{
	connect(ui->m_pUPlusEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneUPlus_editingFinished()));
	connect(ui->m_pUMinusEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneUMinus_editingFinished()));
	connect(ui->m_pFPlusEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFPlus_editingFinished()));
	connect(ui->m_pFMinusEdit,SIGNAL(editingFinished()),this,SLOT(slot_lneFMinus_editingFinished()));
	
	connect(ui->m_pOK_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_OKClick()));
	connect(ui->m_pCancel_PushButton, SIGNAL(clicked()), this, SLOT(slot_pbn_CancelClick()));

}

void QSynAddMultQuickDlg::InitLanuage()
{
	xlang_SetLangStrToWidget(ui->m_pOK_PushButton, g_sLangID_OK, XLang_Ctrls_QPushButton);//确定
	xlang_SetLangStrToWidget(ui->m_pCancel_PushButton, g_sLangID_Cancel, XLang_Ctrls_QPushButton);//取消
}

float QSynAddMultQuickDlg::slot_lne_Changed(QLineEdit* pLineEdit)
{
	if (pLineEdit->text().isEmpty())
	{
		pLineEdit->setText("0.000");
	}

	QString strValue = pLineEdit->text();
	if (strValue.right(1).contains("."))
	{
		strValue.append("000");
	}
	float fv = strValue.toFloat();
	fv = setLimit(0,1000.000,fv);
	return fv;
}

void QSynAddMultQuickDlg::slot_lneUPlus_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pUPlusEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pUPlusEdit->setText(QString::number(fv,'f',3));
}
void QSynAddMultQuickDlg::slot_lneUMinus_editingFinished()
{
	float fv  = slot_lne_Changed(ui->m_pUMinusEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pUMinusEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultQuickDlg::slot_lneFPlus_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pFPlusEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pFPlusEdit->setText(QString::number(fv,'f',3));
}

void QSynAddMultQuickDlg::slot_lneFMinus_editingFinished()
{
	float fv = slot_lne_Changed(ui->m_pFMinusEdit);
	fv = setLimit(0,999.999,fv);
	ui->m_pFMinusEdit->setText(QString::number(fv,'f',3));
}
void QSynAddMultQuickDlg::slot_pbn_OKClick()
{

	this->done(Accepted);
}

void QSynAddMultQuickDlg::slot_pbn_CancelClick()
{
	this->close();
}
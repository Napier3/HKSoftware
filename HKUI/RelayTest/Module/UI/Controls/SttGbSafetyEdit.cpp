#include "SttGbSafetyEdit.h"
#include "ui_SttGbSafetyEdit.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"
//#include "SttTestCntrFrameWin.h"
#include "../../UI/SttTestCntrFrameApi.h"

#include "../../XLangResource_Native.h"
#include "../../../../AutoTest/Module/XLanguageResourceAts.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "SafetyMsgCfg/SttSafetyMsgCfgs.h"

QSttGbSafetyEdit::QSttGbSafetyEdit(CExBaseList *pParent, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttGbSafetyEdit)
{
    ui->setupUi(this);
	InitLanguage();
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);
	m_pSttParent = pParent;
	m_pMsgCfg = NULL;

	connect(ui->m_Btn_OK,SIGNAL(clicked()),this,SLOT(slot_OKClick()));
	connect(ui->m_Btn_Cancel,SIGNAL(clicked()),this,SLOT(slot_CancelClick()));
}

QSttGbSafetyEdit::~QSttGbSafetyEdit()
{
    delete ui;
}

void QSttGbSafetyEdit::Init(CSttSafety *pSafety)
{
	CString strTitle, strMsgs;
	if (IsRunMode_Edit())
	{
		ASSERT(pSafety != NULL);
		m_pSttSafety = pSafety;
		strTitle = /*_T("修改接线提示")*/g_sLangTxt_Gradient_ModifyTip; //lcq
		pSafety->GetMsgs(strMsgs);
		InitSafetyMsgCfgs(strMsgs);
		ui->lineEdit_Name->setText(m_pSttSafety->m_strName);
		ui->textEdit_Msgs->setText(strMsgs);
	}
	else if(IsRunMode_New())
	{
		m_pSttSafety = new CSttSafety();
		m_pSttSafety->m_strID = _T("safety");
		m_pSttSafety->m_strName = /*_T("接线提示")*/g_sLangTxt_Gradient_WiringTip;//lcq
		strTitle = /*_T("新建接线提示")*/g_sLangTxt_Gradient_WirPrompt; //lcq
		strMsgs = /*_T("请在此处输入接线提示信息……")*/g_sLangTxt_Gradient_EnterTips; //lcq
		InitSafetyMsgCfgs();

		long nIndex = CalAutoIndex(m_pSttSafety->m_strID);

		if (nIndex != -1 && nIndex != 0)
		{	
			//编辑模式下，不需要自动设置名称、ID
			CString strText;
			strText= m_pSttSafety->m_strID + QString::number(nIndex);
			m_pSttSafety->m_strID = strText;
			strText = m_pSttSafety->m_strName + QString::number(nIndex);	
			m_pSttSafety->m_strName = strText;
		}

		ui->lineEdit_Name->setText(m_pSttSafety->m_strName);
	}
	else if (IsRunMode_Run())
	{
		ui->m_label_SelDefaultMsg->setVisible(false);
		ui->m_cmbMsgs->setVisible(false);

		strTitle = /*_T("请按照接线提示信息，完成接线后，点击“完成接线”按钮，继续测试……")*/g_sLangTxt_Gradient_ClickCTest; //lcq
		strMsgs = m_strMsgs;

		ui->label_Name->setVisible(false);
		ui->lineEdit_Name->setVisible(false);
		ui->m_Btn_Cancel->setVisible(false);
		ui->textEdit_Msgs->setReadOnly(true);
		CString strBtnOK;
		strBtnOK = /*_T("完成接线")*/g_sLangTxt_Gradient_CompleteWir; //lcq
		ui->m_Btn_OK->setText(strBtnOK);
		ui->textEdit_Msgs->setText(strMsgs);
	}

	setWindowTitle(strTitle);
}

long QSttGbSafetyEdit::CalAutoIndex(const CString& strID)
{
	if(m_pSttParent == NULL)
	{
		return -1;
	}

	if (m_pSttParent->FindByID(strID) == NULL)
	{
		return 0;
	}

	//计算第一个不存在的ID-Index
	long nIndex = 1;
	CString strTempID = strID + QString::number(nIndex);

	while(m_pSttParent->FindByID(strTempID) != NULL)
	{
		nIndex++;
		strTempID = strID + QString::number(nIndex);
	}

	return nIndex;
}

void QSttGbSafetyEdit::SetDlgRunMode(long nRunMode)
{
	m_nRunMode = nRunMode;
}

void QSttGbSafetyEdit::OnOKClicked_New()
{
	CString strName, strMsgs;
	strName = ui->lineEdit_Name->text();
	strMsgs = ui->textEdit_Msgs->toPlainText();

	CExBaseObject *pFind_Name = m_pSttParent->FindByName(strName);
	CString strMsg;

	if (pFind_Name != NULL)
	{
		strMsg = /*"存在相同名称的接线提示"*/g_sLangTxt_Gradient_WirpromptExit; //lcq
	}

	if (strMsg.GetLength() > 0)
	{
		CXMessageBox::information(this, "", strMsg, QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	m_pSttSafety->m_strName = strName;
	m_pSttSafety->AddNewMsg(strMsgs);
	m_pSttParent->AddNewChild(m_pSttSafety);

	accept();
}

void QSttGbSafetyEdit::OnOKClicked_Edit()
{
	CString strName, strMsgs;
	strName = ui->lineEdit_Name->text();
	strMsgs = ui->textEdit_Msgs->toPlainText();
	CString strMsgsEx;
	m_pSttSafety->GetMsgs(strMsgsEx);

	if (strName == m_pSttSafety->m_strName
		&& strMsgs == strMsgsEx)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, /*_T("接线提示信息编辑，未检测到内容发生变化……")*/g_sLangTxt_Gradient_WEditNoChange.GetString()); //lcq
		reject();
		return;
	}

	CExBaseObject *pFind_Name = m_pSttParent->FindByName(strName);
	CString strMsg;

	if (pFind_Name != NULL && pFind_Name != m_pSttSafety)
	{
		strMsg = /*"存在相同名称的接线提示"*/g_sLangTxt_Gradient_WirpromptExit; //lcq
	}

	if (strMsg.GetLength() > 0)
	{
		CXMessageBox::information(this, "", strMsg, QMessageBox::Ok, QMessageBox::Ok);
		return;
	}

	m_pSttSafety->m_strName = strName;
	m_pSttSafety->UpdateMsgs(strMsgs);

	accept();
}

void QSttGbSafetyEdit::OnOKClicked_Run()
{
	accept();
}

void QSttGbSafetyEdit::SetMsgs(const CString &strMsgs)
{
	m_strMsgs = strMsgs;
}

void QSttGbSafetyEdit::InitSafetyMsgCfgs(const CString &strMsgs)
{
	ui->m_cmbMsgs->clear();
	CString strText;
	strText = /*_T("自定义")*/g_sLangTxt_Custom; //lcq
	ui->m_cmbMsgs->addItem(strText);

    CSttSafetyMsgCfgs *pMsgCfgs = (CSttSafetyMsgCfgs*)stt_Frame_SafetyMsgCfgs();
    CSttSafetyMsgCfg *pMsgCfg = (CSttSafetyMsgCfg *)pMsgCfgs->FindByID(stt_Frame_TestDeviceType());
	m_pMsgCfg = pMsgCfg;

	if (pMsgCfg != NULL)
	{
		POS pos = pMsgCfg->GetHeadPosition();

		while (pos != NULL)
		{
			CSttSafetyMsg *pMsg = (CSttSafetyMsg *)pMsgCfg->GetNext(pos);
			ui->m_cmbMsgs->addItem(pMsg->m_strName);
		}
	}

	if (strMsgs.IsEmpty())
	{
		ui->m_cmbMsgs->setCurrentIndex(0);
	}
	else 
	{
		CSttSafetyMsg *pMsg = pMsgCfg->FindByMsg(strMsgs);

		if (pMsg != NULL)
		{
			long nIndex = pMsgCfg->FindIndex(pMsg);
			ui->m_cmbMsgs->setCurrentIndex(nIndex + 1);
		}
		else
		{
			ui->m_cmbMsgs->setCurrentIndex(0);
		}
	}
}

void QSttGbSafetyEdit::slot_OKClick()
{
	if (IsRunMode_New())
	{
		OnOKClicked_New();
	}
	else if (IsRunMode_Edit())
	{
		OnOKClicked_Edit();
	}
	else if (IsRunMode_Run())
	{
		OnOKClicked_Run();
	}
	else 
	{
		CString strMsg;
		strMsg = /*_T("错误的运行方式！")*/g_sLangTxt_Gradient_WrongWayrun; //lcq
		CXMessageBox::information(this, "", strMsg, QMessageBox::Ok, QMessageBox::Ok);
		accept();
	}
}

void QSttGbSafetyEdit::slot_CancelClick()
{
	if (IsRunMode_New())
	{//新建方式，取消则删除对象
		delete m_pSttSafety;
	}

	reject();
}

void QSttGbSafetyEdit::on_m_cmbMsgs_currentIndexChanged(int index)
{
	CString strText, strMsgs;
	strText = ui->m_cmbMsgs->currentText();

	if (strText == /*_T("自定义")*/g_sLangTxt_Custom)
	{
		strMsgs = /*_T("请在此处输入接线提示信息……")*/g_sLangTxt_Native_PlsEntWiringInstruc;
	}
	else
	{
		CSttSafetyMsg *pMsg = (CSttSafetyMsg *)m_pMsgCfg->FindByName(strText);

		if (pMsg == NULL)
		{
			strMsgs = /*_T("未找到对应的预置提示信息，请在此处输入接线提示信息……")*/g_sLangTxt_Native_NoMatchPresetInstrucPlsEntWiring;
		}
		else
		{
			strMsgs = pMsg->m_strMsg;
		}
	}

	ui->textEdit_Msgs->setText(strMsgs);
}

void QSttGbSafetyEdit::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_OK,g_sLangTxt_Native_Confm,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_label_SelDefaultMsg,g_sLangTxt_Native_SelDesiredWiringInstruc,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->label_Name,g_sLangTxt_Name,XLang_Ctrls_QLabel);
}

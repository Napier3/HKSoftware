#include "SttIecRecordWriteFileWidget.h"
#include "ui_SttIecRecordWriteFileWidget.h"
#include "../../../../../../Module/SmartCap/XSmartCapFileWrite.h"
#include "../../../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../ReportView/XLangResource_PowerTestWin.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
// #include "../../Module/UI/SttTestCntrFrameBase.h"

QSttIecRecordWriteFileWidget::QSttIecRecordWriteFileWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttIecRecordWriteFileWidget)
{
    ui->setupUi(this);
	InitLanguage();
    m_pIecRcdFuncWidget = this;
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

	CXSmartCapFileWrite::Create();
	SetIecRcdFuncfont();
}


QSttIecRecordWriteFileWidget::~QSttIecRecordWriteFileWidget()
{
	CXSmartCapFileWrite::Release();
    delete ui;
}

void QSttIecRecordWriteFileWidget::SetIecRcdFuncfont()
{
	if (g_pSttGlobalFont != NULL)
	{
		ui->m_edtCb1_AppID->setFont(*g_pSttGlobalFont);
		ui->m_lblPkgCount->setFont(*g_pSttGlobalFont);
		ui->m_edtCb3_PkgError->setFont(*g_pSttGlobalFont);
		ui->m_lblPkgErr->setFont(*g_pSttGlobalFont);
		ui->m_edtCb2_PkgCount->setFont(*g_pSttGlobalFont);
		ui->m_edtCb3_AppID->setFont(*g_pSttGlobalFont);
		ui->m_edtCb3_PkgCount->setFont(*g_pSttGlobalFont);
		ui->m_edtCb1_PkgCount->setFont(*g_pSttGlobalFont);
		ui->m_edtCb1_PkgError->setFont(*g_pSttGlobalFont);
		ui->m_edtCb2_PkgError->setFont(*g_pSttGlobalFont);
		ui->m_lblPkgAppID->setFont(*g_pSttGlobalFont);
		ui->m_lblPkgErr_2->setFont(*g_pSttGlobalFont);
		ui->m_edtCb1_MaxTimeDiff->setFont(*g_pSttGlobalFont);
		ui->m_edtCb2_MaxTimeDiff->setFont(*g_pSttGlobalFont);
		ui->m_edtCb3_MaxTimeDiff->setFont(*g_pSttGlobalFont);
		ui->m_edtWriteSize->setFont(*g_pSttGlobalFont);
		ui->m_btnStopWrite->setFont(*g_pSttGlobalFont);
	}
	
}

void QSttIecRecordWriteFileWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{

}

void IecRcdFunc_WriteFile_Show(QLineEdit *pEditAppID, QLineEdit *pEditPkgCount, QLineEdit *pEditPkgErr, QLineEdit *pEditMaxTime,PSTT_AT02_PKT_HEAD_STC pHeadStc)
{
	CString strText;
	strText.Format(_T("%X"), pHeadStc->appid);
	pEditAppID->setText(strText);

	pEditPkgCount->setText(QString::number(pHeadStc->nPkgCount));
	pEditPkgErr->setText(QString::number(pHeadStc->nSmpCntError));
	pEditMaxTime->setText(QString::number(pHeadStc->nMaxTimeDiff));
}

void QSttIecRecordWriteFileWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	long nLen = CXSmartCapFileWrite::GetWriteLen();
	nLen = nLen / 1024;
	long nM = nLen / 1024;
	long nK = nLen - nM * 1024;
	CString strSize;
	strSize.Format(_T("%d,%d K"), nM, nK);
	ui->m_edtWriteSize->setText(strSize);

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	PSTT_AT02_PKT_HEAD_STC_MNGR pHeadStcMngr = pXCapPkgBufferMngr->GetPkgHeadStcMngr();

	if (pHeadStcMngr->nCount >= 1)
	{
		IecRcdFunc_WriteFile_Show(ui->m_edtCb1_AppID, ui->m_edtCb1_PkgCount, ui->m_edtCb1_PkgError,ui->m_edtCb1_MaxTimeDiff ,&pHeadStcMngr->oHeadStc[0]);
	}

	if (pHeadStcMngr->nCount >= 2)
	{
		IecRcdFunc_WriteFile_Show(ui->m_edtCb2_AppID, ui->m_edtCb2_PkgCount, ui->m_edtCb2_PkgError,ui->m_edtCb2_MaxTimeDiff, &pHeadStcMngr->oHeadStc[1]);
	}

	if (pHeadStcMngr->nCount >= 3)
	{
		IecRcdFunc_WriteFile_Show(ui->m_edtCb3_AppID, ui->m_edtCb3_PkgCount, ui->m_edtCb3_PkgError,ui->m_edtCb3_MaxTimeDiff, &pHeadStcMngr->oHeadStc[2]);
	}
}

void QSttIecRecordWriteFileWidget::Release()
{
	delete this;
}


void QSttIecRecordWriteFileWidget::on_m_btnStopWrite_clicked()
{
	 CXSmartCapFileWrite::StopWrite("");
}

void QSttIecRecordWriteFileWidget::InitLanguage()
{	
	xlang_SetLangStrToWidget_Txt(ui->m_lblPkgCount,g_sLangTxt_Native_TotalMsgs,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblPkgErr,g_sLangTxt_Native_PktLossCount,XLang_Ctrls_QLabel);
	xlang_SetLangStrToWidget_Txt(ui->m_lblPkgErr_2,g_sLangTxt_Native_MaxTimeDiff+"(μs)",XLang_Ctrls_QLabel);

	xlang_SetLangStrToWidget_Txt(ui->m_btnStopWrite,g_sLangTxt_Native_StopWriteFile,XLang_Ctrls_QPushButton);
}
#include "SttGbItemsNameSelDlg.h"
#include "ui_SttGbItemsNameSelDlg.h"

#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../../Module/BaseClass/QT/QExBaseListComboBox.h"

#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QSttGbItemsNameSelDlg::QSttGbItemsNameSelDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttGbItemsNameSelDlg)
{
    ui->setupUi(this);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_OK,g_sLangTxt_OK,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_Btn_Cancel,g_sLangTxt_Cancel,XLang_Ctrls_QPushButton);
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	this->setWindowFlags(flags);

	if (g_theGbSmartGenWzd != NULL)
	{
		CDataGroup *pFind = CGbWzdItemsNameLib::FindDeviceTypeLib(g_theGbSmartGenWzd->m_strDeviceType);

		if (pFind != NULL)
		{
			ex_InsertChildreComboBox(pFind, ui->m_cmbItemsName);
		}
		else
		{
			ui->m_cmbItemsName->setEnabled(FALSE);
		}
	}
	else
	{
		ui->m_cmbItemsName->setEnabled(FALSE);
	}
}

QSttGbItemsNameSelDlg::~QSttGbItemsNameSelDlg()
{
    delete ui;
}

void QSttGbItemsNameSelDlg::on_m_Btn_OK_clicked()
{
    accept();
}

void QSttGbItemsNameSelDlg::on_m_Btn_Cancel_clicked()
{
    reject();
}

void QSttGbItemsNameSelDlg::on_m_cmbItemsName_currentIndexChanged(int index)
{
	CExBaseObject *pSel = ex_ComboBox_GetSelObj(ui->m_cmbItemsName);

	if (pSel == NULL)
	{
		ui->m_cmbItemsName->setEnabled(FALSE);
		return;
	}

	m_strName = pSel->m_strName;
	m_strID = pSel->m_strID;
	ui->m_cmbItemsName->setEnabled(TRUE);

}

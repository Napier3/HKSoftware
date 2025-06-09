#include "DistanceSearchQuickAddMultDlg.h"
#include "ui_DistanceSearchQuickAddMultDlg.h"
#include "QMessageBox"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../XLangResource_Native.h"

QDistanceSearchQuickAddMultDlg::QDistanceSearchQuickAddMultDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDistanceSearchQuickAddMultDlg)
{
    ui->setupUi(this);
    InitUI();

 //   return;
}

QDistanceSearchQuickAddMultDlg::~QDistanceSearchQuickAddMultDlg(void)
{
    delete ui;
}

void QDistanceSearchQuickAddMultDlg::InitUI()
{
	CString strPngPath;
#ifdef _PSX_QT_WINDOWS_
	strPngPath = _P_GetResourcePath();
	strPngPath = strPngPath + _T("images/DistanceSearchTest.png");
#else
	strPngPath =  ":/ctrls/images/DistanceSearchTest.png";
#endif
	this->setWindowIcon(QIcon(QPixmap(strPngPath)));
	this->setWindowTitle(g_sLangTxt_Button_AddMultQuick);
	ui->m_btnOk->setText(g_sLangTxt_OK);
	ui->m_btnCancel->setText(g_sLangTxt_Cancel);
}


void QDistanceSearchQuickAddMultDlg::SetDatas(CDataGroup *pParas)
{

}


void QDistanceSearchQuickAddMultDlg::GetDatas(CDataGroup *pParas)
{

}

void QDistanceSearchQuickAddMultDlg::SetDatas(QVector<int> nFaultTypeArr)
{
    if(nFaultTypeArr.size() < 7)
        return;

    ui->m_cbAN->setChecked(!(nFaultTypeArr[0] == 0));
    ui->m_cbBN->setChecked(!(nFaultTypeArr[1] == 0));
    ui->m_cbCN->setChecked(!(nFaultTypeArr[2] == 0));
    ui->m_cbAB->setChecked(!(nFaultTypeArr[3] == 0));
    ui->m_cbBC->setChecked(!(nFaultTypeArr[4] == 0));
    ui->m_cbCA->setChecked(!(nFaultTypeArr[5] == 0));
    ui->m_cbABC->setChecked(!(nFaultTypeArr[6] == 0));
}

void QDistanceSearchQuickAddMultDlg::GetDatas(QVector<int> &nFaultTypeArr)
{
    nFaultTypeArr.resize(7);
    nFaultTypeArr[0] = ui->m_cbAN->isChecked();
    nFaultTypeArr[1] = ui->m_cbBN->isChecked();
    nFaultTypeArr[2] = ui->m_cbCN->isChecked();
    nFaultTypeArr[3] = ui->m_cbAB->isChecked();
    nFaultTypeArr[4] = ui->m_cbBC->isChecked();
    nFaultTypeArr[5] = ui->m_cbCA->isChecked();
    nFaultTypeArr[6] = ui->m_cbABC->isChecked();
}

void QDistanceSearchQuickAddMultDlg::on_m_btnOk_clicked()
{

	this->done(Accepted);
}

void QDistanceSearchQuickAddMultDlg::on_m_btnCancel_clicked()
{
	this->close();
}

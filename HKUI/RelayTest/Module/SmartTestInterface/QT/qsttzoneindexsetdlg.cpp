#include "qsttzoneindexsetdlg.h"
#include "ui_qsttzoneindexsetdlg.h"
#include "../../../../Module/OSInterface/OSInterface.h"

QSttZoneIndexSetDlg::QSttZoneIndexSetDlg(long nZoneIndex, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QSttZoneIndexSetDlg)
{
    ui->setupUi(this);
	m_nZoneIndex = nZoneIndex;
	CString strTitleText;
	strTitleText = _T("定值区号选择界面");
	setWindowTitle(strTitleText);

	long nIndex = 0;

	for (nIndex=1; nIndex < 31; nIndex++)
	{
		ui->m_cmbZone->addItem(QString::number(nIndex));
	}

	ui->m_cmbZone->setCurrentIndex(m_nZoneIndex - 1);
}

QSttZoneIndexSetDlg::~QSttZoneIndexSetDlg()
{
    delete ui;
}

void QSttZoneIndexSetDlg::on_m_btnOK_clicked()
{
	accept();
}

void QSttZoneIndexSetDlg::on_m_btnCancel_clicked()
{
	reject();
}

void QSttZoneIndexSetDlg::on_m_cmbZone_currentIndexChanged(const QString &arg1)
{
	m_nZoneIndex = arg1.toInt();
}

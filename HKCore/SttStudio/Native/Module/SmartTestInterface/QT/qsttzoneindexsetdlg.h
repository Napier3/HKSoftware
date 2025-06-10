#ifndef QSTTZONEINDEXSETDLG_H
#define QSTTZONEINDEXSETDLG_H

#include <QDialog>

namespace Ui {
class QSttZoneIndexSetDlg;
}

class QSttZoneIndexSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSttZoneIndexSetDlg(long nZoneIndex, QWidget *parent = 0);
    ~QSttZoneIndexSetDlg();
	long m_nZoneIndex;

private slots:
    void on_m_btnOK_clicked();

    void on_m_btnCancel_clicked();

    void on_m_cmbZone_currentIndexChanged(const QString &arg1);

private:
    Ui::QSttZoneIndexSetDlg *ui;
};

#endif // QSTTZONEINDEXSETDLG_H

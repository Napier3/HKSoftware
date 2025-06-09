#ifndef DISTANCESEARCHQUICKADDMULTDLG_H
#define DISTANCESEARCHQUICKADDMULTDLG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include "../../../../Module/DataMngr/DataGroup.h"

namespace Ui {
class QDistanceSearchQuickAddMultDlg;
}

class QDistanceSearchQuickAddMultDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceSearchQuickAddMultDlg(QWidget *parent = 0);
    virtual ~QDistanceSearchQuickAddMultDlg(void);
    void InitUI();
    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);
    void SetDatas(QVector<int> nFaultTypeArr);
    void GetDatas(QVector<int> &nFaultTypeArr);

private:
    Ui::QDistanceSearchQuickAddMultDlg *ui;

private slots:
	void on_m_btnOk_clicked();
	void on_m_btnCancel_clicked();
};

#endif // DISTANCESEARCHQUICKADDMULTDLG_H

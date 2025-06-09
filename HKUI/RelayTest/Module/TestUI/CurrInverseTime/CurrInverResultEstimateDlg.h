#ifndef QCURRINVERRESULTESTIMATEDLG_H
#define QCURRINVERRESULTESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include "../../../../Module/DataMngr/DataGroup.h"

namespace Ui {
class QCurrInverResultEstimateDlg;
}

class QCurrInverResultEstimateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QCurrInverResultEstimateDlg(QWidget *parent = 0);
    ~QCurrInverResultEstimateDlg();
    void InitUI();
    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);

public:
    QComboBox *m_pComboBox;
    QLineEdit *m_pLineEdit1;
    QLineEdit *m_pLineEdit2;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
	void on_lineEdit1_TextChanged();
	void on_lineEdit2_TextChanged();

private:
    Ui::QCurrInverResultEstimateDlg *ui;
};

#endif // QCURRINVERRESULTESTIMATEDLG_H

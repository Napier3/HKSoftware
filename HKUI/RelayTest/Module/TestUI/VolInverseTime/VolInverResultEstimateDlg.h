#ifndef QVOLINVERESULTESTIMATEDLG_H
#define QVOLINVERESULTESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include "../../../../Module/DataMngr/DataGroup.h"

namespace Ui {
class QVolInverResultEstimateDlg;
}

class QVolInverResultEstimateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QVolInverResultEstimateDlg(CDataGroup *pPara,QWidget *parent = 0);
    ~QVolInverResultEstimateDlg();
    void InitUI();
    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);

public:
	CDataGroup *m_pCurrDataGroup;
    QComboBox *m_pComboBox;
    QLineEdit *m_pLineEdit1;
    QLineEdit *m_pLineEdit2;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
	void on_lineEdit1_TextChanged();
	void on_lineEdit2_TextChanged();

private:
    Ui::QVolInverResultEstimateDlg *ui;
};

#endif // QVOLINVERESULTESTIMATEDLG_H

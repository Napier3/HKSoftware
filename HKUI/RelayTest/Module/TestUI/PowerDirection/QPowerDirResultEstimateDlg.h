#ifndef QPOWERDIRRESULTESTIMATEDLG_H
#define QPOWERDIRRESULTESTIMATEDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include "../../../../Module/DataMngr/DataGroup.h"

namespace Ui {
class QPowerDirResultEstimateDlg;
}

class QPowerDirResultEstimateDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QPowerDirResultEstimateDlg(CDataGroup *pPara,QWidget *parent = 0);
    ~QPowerDirResultEstimateDlg();
    void InitUI();
	void InitLanguage();
	void initConnections();
    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);

public:
	CDataGroup *m_pCurrDataGroup;

	QLabel *m_pMaxErrorTypeLabel;
	QLabel *m_pErrorType1Label;
	QLabel *m_pErrorType2Label;
    QLabel *m_pRelativeErrorLabel1;
    QLabel *m_pRelativeErrorLabel2;
	QLabel *m_pRelativeErrorLabel3;
	QLineEdit *m_pAbsoluteErrorEdit1;
	QLineEdit *m_pAbsoluteErrorEdit2;
	QLineEdit *m_pAbsoluteErrorEdit3;


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
	float on_lineEdit_TextChanged(QLineEdit *pLineEdit);
	void slot_lneAbsoluteErrorEdit1_TextChanged();
	void slot_lneAbsoluteErrorEdit2_TextChanged();
	void slot_lneAbsoluteErrorEdit3_TextChanged();

private:
    Ui::QPowerDirResultEstimateDlg *ui;

};

#endif // QPOWERDIRRESULTESTIMATEDLG_H

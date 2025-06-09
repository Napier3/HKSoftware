#ifndef QACTIONTIMERESULTEVALDLG_H
#define QACTIONTIMERESULTEVALDLG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include "../../UI/Interface/SttMacroParaEditViewOriginal.h"

#define TTRIPRELERR_MIN 0
#define TTRIPRELERR_MAX 100
#define TTRIPABSERR_MIN 0
#define TTRIPABSERR_MAX 200

namespace Ui {
class QActionTimeResultEvalDlg;
}

class QActionTimeResultEvalDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QActionTimeResultEvalDlg(QWidget *parent = 0);
    ~QActionTimeResultEvalDlg();
    void InitUI();
    void SetDatas(CDataGroup *pParas);
    void GetDatas(CDataGroup *pParas);

public:
	CDataGroup *m_pCurrDataGroup;
    QComboBox *m_pComboBox;
    QLineEdit *m_pLineEdit1;
    QLineEdit *m_pLineEdit2;

private slots:
    void on_m_btnOk_clicked();
	void on_m_btnCancel_clicked();
	void on_m_pLineEdit1_editingFinished();
	void on_m_pLineEdit2_editingFinished();

private:
    Ui::QActionTimeResultEvalDlg *ui;
};

#endif // QACTIONTIMERESULTEVALDLG_H

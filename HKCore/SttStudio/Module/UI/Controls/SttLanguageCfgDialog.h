#ifndef QSTTLANGUAGECFGDIALOG_H
#define QSTTLANGUAGECFGDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class QSttLanguageCfgDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QSttLanguageCfgDialog(QWidget *parent = 0);

    QComboBox *m_pComboBox;
    QPushButton *m_pBtnOK;
    QPushButton *m_pBtnCancel;
	QLabel *m_pLabelText;

    QVBoxLayout *m_pMainLayout;
    QHBoxLayout *m_pCenterLayout;
    QHBoxLayout *m_pBottomLayout;
	void SetLanguageCfgFont();

signals:

public slots:
    void slot_OKClick();
    void slot_CancelClick();
};

extern QFont *g_pSttGlobalFont;  

#endif // QSTTLANGUAGECFGDIALOG_H

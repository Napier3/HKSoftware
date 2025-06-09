#ifndef	QSTTCAPFUNSELECTDLG
#define QSTTCAPFUNSELECTDLG
#include <QDialog>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QRadioButton>
#include <QSpacerItem>
#include <QVBoxLayout>
class QSttCapFunSelectDlg:public QDialog
{
	Q_OBJECT
public:

	QSttCapFunSelectDlg(QWidget *parent = 0, Qt::WFlags flags = 0, int nTestFunction = 0);
	virtual ~QSttCapFunSelectDlg();
	QVBoxLayout *verticalLayout_2;
	QGroupBox *m_pFunGroupBox;
	QVBoxLayout *verticalLayout_3;
	QVBoxLayout *m_pVFunsLayout;
	QRadioButton *m_RadioBtnPkgStc;
	QRadioButton *m_RadioBtnMUTest;
	QHBoxLayout *hboxLayout;
	QSpacerItem *spacerItem;
	QPushButton *m_BtnOK;
	QPushButton *m_BtnCancel;

	void InitUI();

signals:
	 void sig_UpdateTestFun(bool bSvAnalysis);

public slots:
	void slot_m_BtnOK_Clicked();
	void slot_m_BtnCancel_Clicked();

};
#endif

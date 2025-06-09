#ifndef QSttProgDlg_H
#define QSttProgDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QProgressBar>
#include <QTimer>
#include "../../../../../Module/OSInterface/OSInterface.h"

class QSttProgDlg : public QDialog
{
	Q_OBJECT

public:
	QSttProgDlg(QWidget *parent = 0);
	~QSttProgDlg();

	void initUI(const CString &strTitle,const CString &strText = _T(""));
	void ReleaseUI();
	void Start(int nMinValue = 0,int nMaxValue = 100,int nCurrValue = 0);
	void Stop();
	void SetText(const CString &strMsgText,const CString &strTitle = _T(""));

protected:
	void InitDatas();
	QProgressBar *m_pCurrProgressBar;
//	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QGridLayout *m_pVBoxLayout1;//第一行的水平布局
	QLabel *m_pMsgLabel;

	QTimer m_oTimer;
	long m_nCurrProgValue;

public:
signals:

public slots:
	void slot_Timer();
};

#endif // QSttProgDlg_H

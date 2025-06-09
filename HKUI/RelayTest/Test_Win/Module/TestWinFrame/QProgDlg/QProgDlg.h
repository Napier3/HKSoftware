#ifndef QProgDlg_H
#define QProgDlg_H

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

#define TYPICALMODULE	0			//常规模块
#define REPLAYTESTOPENFILE  1		//故障回放模块 - 打开录波文件
#define REPLAYTESTDOWNLOADDATA  2	//故障回放模块 - 下载波形数据


class QProgDlg : public QDialog
{
	Q_OBJECT

public:
	QProgDlg(QWidget *parent = 0);
	~QProgDlg();

	void initUI();
	void ReleaseUI();
	void Start();
	void Stop();
	void SetProgDlgType(int nType = TYPICALMODULE);

protected:
	void InitDatas();
	QProgressBar *m_pCurrProgressBar;
	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QGridLayout *m_pVBoxLayout1;//第一行的水平布局

	QTimer m_oTimer;
	long m_nCurrProgValue;
	int m_nProgDlgType;

public:
signals:

public slots:
	void slot_Timer();
};

#endif // QProgDlg_H

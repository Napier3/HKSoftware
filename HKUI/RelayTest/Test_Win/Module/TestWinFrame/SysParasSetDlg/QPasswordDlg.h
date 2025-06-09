#ifndef QPasswordDlg_H
#define QPasswordDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>

class QPasswordDlg : public QDialog
{
	Q_OBJECT

public:
	QPasswordDlg(QWidget *parent = 0);
	~QPasswordDlg();

	void initUI();
	void ReleaseUI();

protected:
	void InitDatas();

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QGroupBox *m_pPasswordGroupBox;//整个的Group
	QLabel *m_pModelLabel;
	QLineEdit *m_pPasswordLineEdit;//

	QGridLayout *m_pVBoxLayout1;//第一行的水平布局
	QHBoxLayout *m_pHBoxLayout2;//第二行的水平布局
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;


public:
	bool m_bIsCorrected;
signals:

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	
};

#endif // QPasswordDlg_H

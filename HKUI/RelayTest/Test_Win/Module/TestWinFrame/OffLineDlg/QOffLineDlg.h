#ifndef QOFFLINEDLG_H
#define QOFFLINEDLG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
//#include "../../../../../Module/XfileMngrBase/XFileMngr.h"

class QOffLineDlg : public QDialog
{
	Q_OBJECT

public:
	QOffLineDlg(QWidget *parent = 0);
	~QOffLineDlg();

	void initUI();
	void ReleaseUI();

protected:
	void InitDatas();
	void GetAllChildFolder(const QString &strParentFolderPath,QStringList &astrChildFolders);

	QVBoxLayout *m_pAllVLayout;//整个界面的垂直布局
	QGroupBox *m_pOfflLineSelGroupBox;//整个的Group
	QLabel *m_pModelLabel;
	QComboBox *m_pModelSelCombobox;//型号选择
	QLabel *m_pSN_Label;
	QComboBox *m_pSN_SelCombobox;//SN选择

	QGridLayout *m_pVBoxLayout1;//第一行的水平布局
	QHBoxLayout *m_pHBoxLayout2;//第二行的水平布局
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

private:
	QStringList m_astrModels;//全部装置型号
	QStringList m_astrSNs;//当前选择型号下的全部SN

//	CXFileMngr m_oDeviceFileMngr;

public:
signals:
	void sig_OffLineSelChanged();//发送型号、SN选择改变信号

public slots:
	void slot_changeModelSel(int nCurComboxIndex);
	void slot_OKClicked();
	void slot_CancelClicked();
	
};

#endif // QOFFLINEDLG_H

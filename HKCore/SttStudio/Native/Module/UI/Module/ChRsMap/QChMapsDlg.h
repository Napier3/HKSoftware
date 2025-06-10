#ifndef QChMapsDlg_H
#define QChMapsDlg_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include "QChMapsWidget.h"


class QChMapsDlg : public QDialog
{
	Q_OBJECT

public:
	QChMapsDlg(QWidget *parent = 0);
	~QChMapsDlg();

	void initUI();
	void ReleaseUI();
	void DisableCtrls_SysCfg();   //��ϵͳ�������ֵĿؼ�������Ϊdisable״̬

	BOOL m_bSysParasHasChanged;

protected:
	void InitDatas();

	QVBoxLayout *m_pAllVLayout;//��������Ĵ�ֱ����
	QHBoxLayout *m_pBottom_HBoxLayout;

	QChMapsWidget *m_pChMapsWidget;

	QPushButton *m_pDefautMaps_PButton;//����ȱʡͨ��ӳ��
	QPushButton *m_pImportChMaps_PButton;//����ͨ��ӳ���ļ�
	QPushButton *m_pExportChMaps_PButton;//����ͨ��ӳ���ļ�

	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	QCheckBox *m_pLockMaps_CheckBox;//����ӳ��

	CSttChMaps m_oSttChMaps;
	STT_SystemParas m_oSysParas;

public:
signals:
	void sig_UpdateChRsMaps(BOOL bSysParasHasChanged);

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();

	void slot_DefautMapsClicked();
	void slot_ImportChMapsClicked();
	void slot_ExportChMapsClicked();
    void slot_LockMapsChecked(int);//wangtao1 20240508
};

#endif // QChMapsDlg_H

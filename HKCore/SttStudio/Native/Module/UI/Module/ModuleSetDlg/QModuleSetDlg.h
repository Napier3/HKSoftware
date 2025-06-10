#ifndef QModuleSetDlg_H
#define QModuleSetDlg_H

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
#include "QModuleSetWidget.h"


class QModuleSetDlg : public QDialog
{
	Q_OBJECT

public:
	QModuleSetDlg(QWidget *parent = 0);
	~QModuleSetDlg();

	void initUI();
	void ReleaseUI();
	void InitDatas();
protected:
	

	QVBoxLayout *m_pAllVLayout;//��������Ĵ�ֱ����
	QHBoxLayout *m_pOkCancel_HBoxLayout;

	QModuleSetWidget *m_pModuleSetWidget;
	QPushButton *m_pOK_PushButton;
	QPushButton *m_pCancel_PushButton;

	STT_SystemParas m_oSysParas;


public:
signals:
	void sig_UpdateModulesGear(BOOL bMergeCurrHasChanged);//֪ͨ�ⲿģ����²�����ģ�鵵λ��Ϣ

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
	
};

#endif // QModuleSetDlg_H

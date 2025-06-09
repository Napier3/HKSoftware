#ifndef QSTTCOMMCFGDEVICEDLG_H  
#define QSTTCOMMCFGDEVICEDLG_H

#include <QDialog>
#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QGridLayout>
#include <QTimerEvent>
#include <QLineEdit>
#include <QVBoxLayout>
#include "../../../../../Module/UI/Controls/SttLineEdit.h"
#include "QSttCommCfgDeviceWidget.h"
//#include "ui_PpSttIotEngineClientWidget.h"

class QSttCommCfgDeviceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QSttCommCfgDeviceDlg(QPpSttIotEngineClientWidget *pSttCommCfgDeviceWidget,QWidget *parent = 0);
    virtual ~QSttCommCfgDeviceDlg();

	void InitUI();
	void SetDialogFont();

	QVBoxLayout *m_pMainLayout;  //��Layout
	QPpSttIotEngineClientWidget *m_pSttCommCfgDeviceWidget; //�м��Widget
	QPushButton *m_pOK_PushButton;  //ȷ����ť
	QPushButton *m_pCancel_PushButton;   //ȡ����ť

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();
};

#endif // QSTTCOMMCFGDEVICEDLG_H

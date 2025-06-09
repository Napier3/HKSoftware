#ifndef SttIecRecordWriteFileWidget_H
#define SttIecRecordWriteFileWidget_H

#include <QDialog>
#include <QFont>

#include "SttIecRcdFuncInterface.h"

namespace Ui {
class QSttIecRecordWriteFileWidget;
}

class QSttIecRecordWriteFileWidget : public QDialog, public CSttIecRcdFuncInterface
{
    Q_OBJECT

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

 	void SetIecRcdFuncfont();//2022-10-24 sy 设置字体
	void InitLanguage();

public:
    explicit QSttIecRecordWriteFileWidget(QWidget *parent = 0);
    virtual ~QSttIecRecordWriteFileWidget();

private slots:
    void on_m_btnStopWrite_clicked();

private:
    Ui::QSttIecRecordWriteFileWidget *ui;
};

extern QFont *g_pSttGlobalFont; 

#endif // SttIecRecordWriteFileWidget_H

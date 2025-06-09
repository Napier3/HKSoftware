#ifndef STTIECMUTIMEWIDGET_H
#define STTIECMUTIMEWIDGET_H

#include <QWidget>
#include "SttIecRcdFuncInterface.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

// #define STTIEC_MUTIME_TYPE_TimeAccur       0
// #define STTIEC_MUTIME_TYPE_PunctAccur      1


class QSttIecMUTimeWidget : public QWidget, public CSttIecRcdFuncInterface
{
	Q_OBJECT

public:
	QSttIecMUTimeWidget(/*long nMUTimeType,*/QWidget *parent);
	virtual ~QSttIecMUTimeWidget();

	void InitUI();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();
	virtual void Config();//页面功能配置
	void SetIecMUTimeFont();

protected:
	QGridLayout *m_pMain_VLayout;

	QLabel *m_pTimeLong_Label;
	QLineEdit *m_pTimeLong_Edit;
	QLabel *m_pCurrErrorValue_Label;
	QLineEdit *m_pCurrErrorValue_Edit;

	QLabel *m_pMaxErrorValue_Label;
	QLineEdit *m_pMaxErrorValue_Edit;
	QLabel *m_pMinErrorValue_Label;
	QLineEdit *m_pMinErrorValue_Edit;


	CDvmData *m_pSVDelayData;
//	long m_nMUTimeType;
};

extern CFont *g_pSttGlobalFont;

#endif // STTIECMUTIMEWIDGET_H

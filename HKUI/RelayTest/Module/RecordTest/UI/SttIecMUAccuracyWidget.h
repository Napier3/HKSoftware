#ifndef STTIECMUACCURACYWIDGET_H
#define STTIECMUACCURACYWIDGET_H

#include <QWidget>
#include "SttIecRcdFuncInterface.h"

#ifdef _PSX_QT_LINUX_
#include "SttIecSmvGrid_MUAccuracy.h"
#else
#include "SttIecSmvMUAccuaryGrid.h"
#endif

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>

class QSttIecMUAccuracyWidget : public QWidget, public CSttIecRcdFuncInterface
{
	Q_OBJECT

public:
	QSttIecMUAccuracyWidget(QWidget *parent);
	virtual ~QSttIecMUAccuracyWidget();

	void InitUI();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();
	virtual void UpdateChName();
	void SetIecSmvGrid_MUAccuracyFont();
	void ShowDelayTimeUI(bool bShow);//是否显示延时相关界面

protected:
	QVBoxLayout *m_pMain_VLayout;

#ifdef _PSX_QT_LINUX_
	CSttIecSmvGrid_MUAccuracy *m_pIecSmvGrid_MUAccuracy;
#else
	CSttIecSmvMUAccuracyGrid *m_pIecSmvGrid_MUAccuracy;
#endif
	QHBoxLayout *m_pBottom_HLayout;

	QLabel *m_pDelayChValue_Label;
	QLineEdit *m_pDelayChValue_Edit;
	QLabel *m_pRealDelayValue_Label;
	QLineEdit *m_pRealDelayValue_Edit;
	QLabel *m_pDelayValueError_Label;
	QLineEdit *m_pDelayValueError_Edit;

	CDvmData *m_pSVDelayData;
};

#endif // STTIECMUACCURACYWIDGET_H

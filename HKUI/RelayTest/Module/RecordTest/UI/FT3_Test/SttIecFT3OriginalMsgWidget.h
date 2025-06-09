#ifndef SttIecFT3OriginalMsgWidget_H
#define SttIecFT3OriginalMsgWidget_H

#include <QWidget>
#include <QLayout>
#include "../SttIecRcdFuncInterface.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDevice6044.h"
#include "SttIecFT3LineNumberPlanTextEdit.h"
#include "../../../../../Module/API/HexTransApi.h"

class CSttIecFT3OriginalMsgWidget :  public QWidget, public CSttIecRcdFuncInterface
{
public:
	CSttIecFT3OriginalMsgWidget(QWidget* pparent);
	virtual ~CSttIecFT3OriginalMsgWidget();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();
public:
	QHBoxLayout *m_pMainLayout;
	QSttIecFT3LineNumberPlanTextEdit* m_pLineNumberPlan;

};

#endif // SttIecFT3OriginalMsgWidget_H

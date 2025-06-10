#ifndef QSttIecEmptyWidget_H
#define QSttIecEmptyWidget_H

#include <QWidget>
#include <QFont>

#include "SttIecRcdFuncInterface.h"


class QSttIecEmptyWidget : public QWidget, public CSttIecRcdFuncInterface
{
    //Q_OBJECT
public:
	explicit QSttIecEmptyWidget(QWidget *parent = 0);

public://CSttIecRcdFuncInterface
	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

};

#endif // QSttIecEmptyWidget_H

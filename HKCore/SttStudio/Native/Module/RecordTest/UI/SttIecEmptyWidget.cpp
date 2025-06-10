#include "SttIecEmptyWidget.h"

QSttIecEmptyWidget::QSttIecEmptyWidget(QWidget *parent)
    : QWidget(parent)
{
	m_pIecRcdFuncWidget = this;
}

void QSttIecEmptyWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{

}

void QSttIecEmptyWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{

}

void QSttIecEmptyWidget::Release()
{
	delete this;
}


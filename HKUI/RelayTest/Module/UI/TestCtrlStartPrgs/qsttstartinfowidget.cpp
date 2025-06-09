#include "qsttstartinfowidget.h"
#include "ui_qsttstartinfowidget.h"

#include <QDebug>

QSttStartInfoWidget::QSttStartInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QSttStartInfoWidget)
{
    ui->setupUi(this);
}

QSttStartInfoWidget::~QSttStartInfoWidget()
{
    delete ui;
}

void QSttStartInfoWidget::slot_ShowInfor(QString strInfor)
{
	ui->m_lblInfo->setText(strInfor);
	qDebug() << strInfor;
}

void QSttStartInfoWidget::slot_SetSteps(long nSteps)
{

}

void QSttStartInfoWidget::slot_Steps(long nStep)
{

}

void QSttStartInfoWidget::slot_Finish(long nStep)
{

}



#include "logwidget.h"
#include "ui_logwidget.h"
#include<QDateTime>

LogWidget::LogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogWidget)
{
    ui->setupUi(this);
    m_vColor.push_back(Qt::red);
    m_vColor.push_back(Qt::blue);
    m_vColor.push_back(Qt::black);
}

LogWidget::~LogWidget()
{
    delete ui;
}

void LogWidget::logString(int nLevel,QString strMsg)
{
    QColor color(Qt::black);
    if(nLevel<3){
        color = m_vColor.at(nLevel);
    }
     addRecord(color,strMsg);
}

void LogWidget::addRecord(QColor color, QString description )
{
    ui->textEdit->setTextColor(color);

    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    time += "      ";
    time += description;   //一行记录

     ui->textEdit->append(time);
	 QTextCursor cursor = ui->textEdit->textCursor();     
	 cursor.movePosition(QTextCursor::End);     
	 ui->textEdit->setTextCursor(cursor);
}

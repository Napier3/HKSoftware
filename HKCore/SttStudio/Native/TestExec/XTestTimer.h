#ifndef CXTestTimer_H
#define CXTestTimer_H

#include "QTimer"
#include <QDebug>

class CTestTimer : public QObject
{
     Q_OBJECT
public slots:
    void OnTestTimer2()
    {
         qDebug()<<"#######CTestTimer";
    }

public:
    CTestTimer()
    {

    }

    ~CTestTimer()
    {

    }

};

class CTestTimerEx : public CTestTimer
{
    Q_OBJECT
public:
    CTestTimerEx()
    {
        connect(&m_oTimer,SIGNAL(timeout()),this,SLOT(OnTestTimer2()));
        connect(&m_oTimer,SIGNAL(timeout()),this,SLOT(OnTestTimer()));

        QObject::connect(this, SIGNAL(CmdMsg(unsigned int , unsigned long , unsigned long ))
                         , this, SLOT(CmmMsgReceiver(unsigned int , unsigned long , unsigned long)));

         m_oTimer.start(1000);
    }

QTimer m_oTimer;

public slots:
    void OnTestTimer()
    {
         qDebug()<<"CTestTimerEx#######";
         emit CmdMsg(0, 0, 0);
    }

public slots:
    void CmmMsgReceiver(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam)
    {
        qDebug()<<"CmmMsgReceiver >>>>>";
    }

signals:
    void CmdMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

};


#endif // CSttNativeTestMainApp_H

#ifndef QSTTLABEL_H
#define QSTTLABEL_H

#include <QLabel>
#include "../Config/Frame/SttFrame_Data.h"

class QSttLabelBase : public QLabel
{
public:
    QSttLabelBase();

    virtual void StateChanged(QString strState){    }
public:
    CSttFrame_Data *m_pData;
};

// class QSttBatteryLabel : public QSttLabel
// {
// public:
// 	QSttBatteryLabel();
// 
// public:
// 	//PVOID *m_pBatteryState; 
// };

#endif // QSTTLABEL_H

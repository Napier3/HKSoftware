#ifndef QSTTACTION_H
#define QSTTACTION_H

#include <QAction>
#include "../Config/Frame/SttFrame_Item.h"
#include "../../../../Module/DataMngr/DvmData.h"

class QSttAction : public QAction
{
	Q_OBJECT
public:
    QSttAction(CSttFrame_Item *pCfgData,QWidget *pParent);
	virtual ~QSttAction();

public:
    CSttFrame_Item *m_pCfgData;

signals:
	void sig_ActionTrigger(QString);
public slots:
	void slot_ActionTrigger();
};


#endif 

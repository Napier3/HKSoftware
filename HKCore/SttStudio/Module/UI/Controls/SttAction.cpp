#include "SttAction.h"
#include "../../../../Module/API/GlobalConfigApi.h"

QSttAction::QSttAction(CSttFrame_Item *pCfgData,QWidget *pParent)
: QAction(pParent)
{
	m_pCfgData = pCfgData;
	this->setText(m_pCfgData->m_strName);
	connect(this,SIGNAL(triggered()),this,SLOT(slot_ActionTrigger()));
}

QSttAction::~QSttAction()
{

}

void QSttAction::slot_ActionTrigger()
{
	QString strID = m_pCfgData->m_strID;

	emit sig_ActionTrigger(strID);
}

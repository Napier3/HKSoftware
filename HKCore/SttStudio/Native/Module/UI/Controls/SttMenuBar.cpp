#include "SttMenuBar.h"
#include "../../../../Module/API/GlobalConfigApi.h"

QSttMenuBar::QSttMenuBar(CSttFrame_Menus *pMenus,QWidget *parent)
: QMenuBar(parent)
{
	m_pMenus = pMenus;
	InitAction();
}

QSttMenuBar::~QSttMenuBar()
{

}

void QSttMenuBar::InitAction()
{
	if (m_pMenus == NULL)
	{
		return;
	}
	POS pos = m_pMenus->GetHeadPosition();
	while(pos)
	{
		CSttFrame_Menu *pMenuObj = (CSttFrame_Menu*)m_pMenus->GetNext(pos);
		if (pMenuObj != NULL)
		{
			QMenu *pMenu = this->addMenu(pMenuObj->m_strName);
			pMenu->addSeparator();

			POS posObj = pMenuObj->GetHeadPosition();
			while(posObj)
			{
				CSttFrame_Item *pItemObj = (CSttFrame_Item*)pMenuObj->GetNext(posObj);
				if (pItemObj != NULL)
				{
					QSttAction *pAct = new QSttAction(pItemObj,this);
					connect(pAct, SIGNAL(sig_ActionTrigger(QString)), this, SIGNAL(sig_MenuClicked(QString)));
					pMenu->addAction(pAct);
					m_listAct.append(pAct);
				}
			}
			m_listMenu.append(pMenu);
		}
	}
}

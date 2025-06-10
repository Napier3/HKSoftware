#include "SttToolBar.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include <QAction>

QSttToolBar::QSttToolBar(CSttFrame_ToolBar *pToolBar,QWidget *parent)
: QToolBar(parent)
{
	m_pToolBar = pToolBar;
	InitToolButton();
}

QSttToolBar::~QSttToolBar()
{

}

void QSttToolBar::InitToolButton()
{
	if (m_pToolBar == NULL)
	{
		return;
	}

	QFont font = this->font();
	POS pos = m_pToolBar->GetHeadPosition();

	while(pos)
	{
		CSttFrame_Panal *pPanlObj = (CSttFrame_Panal*)m_pToolBar->GetNext(pos);

		if (pPanlObj != NULL)
		{
			QToolBar *pToolBar = new QToolBar(pPanlObj->m_strName,this);
			pToolBar->addSeparator();
			POS posObj = pPanlObj->GetHeadPosition();

			while(posObj)
			{
				CSttFrame_Button *pItemObj = (CSttFrame_Button*)pPanlObj->GetNext(posObj);
			
				QSttToolButton *pToolButton = new QSttToolButton(pItemObj,font,this);
				connect(pToolButton, SIGNAL(sig_clicked(QString)), this, SIGNAL(sig_ToolBarClicked(QString)));
				pItemObj->m_dwItemData = (DWORD)pToolButton;
				QAction* pAction = pToolBar->addWidget(pToolButton);
				pAction->setText(pToolButton->text());
				m_listToolBtn.append(pToolButton);
			}

			this->addWidget(pToolBar);
			m_listToolBar.append(pToolBar);
		}
	}
}


void QSttToolBar::UpdateEnableState(const CString &strState)
{
	QSttToolButton *pToolButton = NULL;

	for(int i = 0;i < m_listToolBtn.size(); i++)
	{
		pToolButton = m_listToolBtn.at(i);
		pToolButton->UpdateEnableState(strState);
	}
}

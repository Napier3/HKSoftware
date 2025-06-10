#include "SttItemButton.h"

QSttItemButton::QSttItemButton(CExBaseObject *pCfgData, QFont font, QWidget *parent)
    : QPushButton(parent)
{
    m_pItem = (CSttFrame_Item*)pCfgData;

    this->setText(m_pItem->m_strName);
    this->setFont(font);

    connect(this,SIGNAL(clicked()),this,SLOT(slot_Click()));
}

QSttItemButton::~QSttItemButton()
{

}
void QSttItemButton::slot_Click()
{
    emit sig_clicked(m_pItem->m_strID);
}

void QSttItemButton::UpdateEnableState( const CString &strState )
{
	if (m_pItem == NULL)
	{
		return;
	}

	if (m_pItem->GetClassID() != MNGRCLASSID_CSTTFRAME_ITEM)
	{
		return;
	}

	QSttItemButton *pButton = (QSttItemButton*)m_pItem;

	if (m_pItem->m_strEnableState.GetLength() < 2)
	{
		return;
	}

	if (m_pItem->m_strEnableState == strState)
	{
		setEnabled(TRUE);
	}
	else
	{
		setEnabled(FALSE);
	}
}

#include "SttXFolderButton.h"


CXFolderButton::CXFolderButton(QWidget *parent)
{
	connect(this,SIGNAL(clicked()),SLOT(slot_OnFileViewOnClick()));
}

CXFolderButton:: ~CXFolderButton()
{

}


void CXFolderButton::slot_OnFileViewOnClick()
{
	m_pDlg->OnClickXFolderBtn(m_pFolder);
}


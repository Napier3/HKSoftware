#ifndef QSTTXFOLDERBUTTON_H
#define QSTTXFOLDERBUTTON_H

#include <QPushButton>

#include "../../../../../Module/XfileMngrBase/XFolder.h"
#include "SttFileMngrChildren.h"

// class QSttFileMngrChildren;

class CXFolderButton : public QPushButton
{
	Q_OBJECT

public:
	CXFolderButton(QWidget *parent=0);
	virtual ~CXFolderButton();

	CXFolder *m_pFolder;
	QSttFileMngrChildren *m_pDlg;

public slots:
	void slot_OnFileViewOnClick();
	
};

#endif//QSTTXFOLDERBUTTON_H

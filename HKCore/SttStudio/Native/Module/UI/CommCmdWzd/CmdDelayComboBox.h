#ifndef CmdDelayComboBox_H
#define CmdDelayComboBox_H

#include "../Module/ScrollCtrl/ScrollComboBox.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

class CCmdDelayComboBox : public QScrollComboBox
{
public:
	CCmdDelayComboBox(QWidget* pparent);
	virtual ~CCmdDelayComboBox();

	void Init(CExBaseList *pList);
	CString GetCmdDelay();
	
};

void CmdDelayComboBox_Init(QComboBox *pComboBox, CExBaseList *pList);
CString CmdDelayComboBox_GetCmdDelay(QComboBox *pComboBox);


#endif // CmdDelayComboBox_H

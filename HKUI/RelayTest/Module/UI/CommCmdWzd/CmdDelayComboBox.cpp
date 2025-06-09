#include "CmdDelayComboBox.h"
#include "../../../../Module/DataMngr/DataGroup.h"

CCmdDelayComboBox::CCmdDelayComboBox(QWidget* pparent):QScrollComboBox(pparent)
{
	
}

CCmdDelayComboBox::~CCmdDelayComboBox()
{
	
}

void CCmdDelayComboBox::Init(CExBaseList *pList)
{
	CmdDelayComboBox_Init(this, pList);
}

CString CCmdDelayComboBox::GetCmdDelay()
{
	return currentText();
}

void CmdDelayComboBox_Init(QComboBox *pComboBox, CExBaseList *pList)
{
	pComboBox->clear();

	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		CExBaseObject *pObj = pList->GetNext(pos);
		pComboBox->addItem(pObj->m_strID);
	}

// 	CString strDelay;
// 	strDelay = _T("0");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("100");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("200");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("500");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("1000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("2000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("3000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("5000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("8000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("10000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("20000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("30000");
// 	pComboBox->addItem(strDelay);
// 
// 	strDelay = _T("60000");
// 	pComboBox->addItem(strDelay);

	pComboBox->setCurrentIndex(0);
}

CString CmdDelayComboBox_GetCmdDelay(QComboBox *pComboBox)
{
	return pComboBox->currentText();
}

#include "SettingZoneComboBox.h"
#include "../../../../Module/DataMngr/DvmData.h"
#include"../../../../AutoTest/Module/XLanguageResourceAts.h"
#include"../../Module/XLangResource_Native.h"

CSettingZoneComboBox::CSettingZoneComboBox(QWidget* pparent):QScrollComboBox(pparent)
{
	
}

CSettingZoneComboBox::~CSettingZoneComboBox()
{
	
}

void CSettingZoneComboBox::Init()
{
	SettingZoneComboBox_Init(this);
}

long CSettingZoneComboBox::GetZone()
{
	return currentIndex();
}

void SettingZoneComboBox_Init(QComboBox *pComboBox)
{
	pComboBox->clear();

	CString strZone;
	//strZone = _T("当前定值区");
	pComboBox->addItem(g_sLangTxt_CurrZoneIndex);
	CString strText;
	//strZone = _T("区");

	for (int nIndex=1; nIndex<32; nIndex++)
	{
		strText.Format(_T("%d"), nIndex);
		strText += g_sLangTxt_zero ;
		pComboBox->addItem(strText);
	}

	pComboBox->setCurrentIndex(0);
}


long SettingZoneComboBox_GetZone(QComboBox *pComboBox)
{
	return pComboBox->currentIndex();
}

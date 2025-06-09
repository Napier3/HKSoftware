#include "stdafx.h"
#include "CXCtrl_QT.h"
#include "../../API/StringApi.h"

void Stt_Global_SetComboBoxIndexByText(CComboBox *pCombox, CString strText)
{
#ifndef _USE_NO_GUI_
    if (pCombox == NULL)
	{  
		CLogPrint::LogString(XLOGLEVEL_ERROR, "ComboBox is null!");  
		return;  
	} 

	int nindex = -1;
	for (int i = 0; i < pCombox->count(); ++i)
	{
		if (pCombox->itemText(i) == strText)
		{
			nindex = i;
			break;
		}
	}

	if (nindex != -1) 
	{  
		pCombox->setCurrentIndex(nindex);  
	} 
	else 
	{  
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("��comboBox��������û���ҵ���Ӧ�ı�"));
		return;
	}  
#endif
}

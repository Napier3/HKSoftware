#include "StdAfx.h"
#include "CommCmdGrid_Analogs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCommCmdGrid_Analogs::CCommCmdGrid_Analogs(void)
{
	
}

CCommCmdGrid_Analogs::~CCommCmdGrid_Analogs(void)
{
}

void CCommCmdGrid_Analogs::SaveValue(CExBaseObject *pParaObject, const CString &strValue)
{
	CAnalog *pAnalog = (CAnalog*)pParaObject;
	pAnalog->m_strValue = strValue;
}

//用于定值、软压板、控制字
CExBaseList* CCommCmdGrid_Analogs::GetDatas()
{
	ASSERT (m_pCurCpu != NULL);

	if (m_pCurCpu != NULL)
	{
		return m_pCurCpu->m_pAnalogs;
	}
	else
	{
		return NULL;
	}
}


BOOL CCommCmdGrid_Analogs::ShowOneObject(CExBaseObject * pParaObject,long &nRow)
{
	CAnalog *pAnalog = (CAnalog*)pParaObject;

	if (pAnalog->m_strType == g_strAnalogType_Error)
	{
		return FALSE;
	}

	GV_ITEM Item;
	Item.mask=GVIF_FORMAT|GVIF_PARAM|GVIF_TEXT | GVIF_FGCLR|GVIF_BKCLR | GVIF_DATATYPE;	
	Item.nFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	Item.nDataType = 0;
	Item.lParam = (LPARAM)pParaObject;
	Item.row = nRow;	

	Item.crBkClr=RGB(241,249,98);
	Item.crBkClr=RGB(200, 251, 196);
	SetTextColor(RGB(120,120,255));
	Item.crFgClr=RGB(0,0,255);

	Item.col = 0;
	Item.szText = pAnalog->m_strName;
	SetItem(&Item);	

	Item.col++;
	Item.szText = pAnalog->m_strID;
	SetItem(&Item);

	Item.nDataType = GVET_CreateDataTyp(GVET_EDITBOX, 0);
	Item.col++;
	Item.szText = pAnalog->m_strValue;
	SetItem(&Item);

	Item.nDataType = 0;
	Item.col++;
	Item.szText = pAnalog->m_strUnit;
	SetItem(&Item);

	nRow++;
	return TRUE;
}

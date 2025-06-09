#include "SttModuleAttrsGrid.h"
#include "../../../../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttTest/Common/tmt_adjust_sys_para_module_def.h"


CSttModuleAttrsGrid::CSttModuleAttrsGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttModuleAttrsGrid::~CSttModuleAttrsGrid()
{

}

void CSttModuleAttrsGrid::InitGrid()
{
 	InitGridTitle();
	SetEditable(FALSE);
}

void CSttModuleAttrsGrid::InitGridTitle()
{
	CString astrGridTitle[CDEVICE_MODULE_ATTRS_GRID_COLS] = {/*_T("名称")*/g_sLangTxt_Name,/*_T("数据值")*/g_sLangTxt_State_Datavalue};
	//xlang_GetLangStrByFile(astrGridTitle[0],"Smv_Name"); //名称
	//xlang_GetLangStrByFile(astrGridTitle[1],"State_Datavalue");  //数据值
	int  iColType[CDEVICE_MODULE_ATTRS_GRID_COLS]={QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[CDEVICE_MODULE_ATTRS_GRID_COLS]={300,300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, CDEVICE_MODULE_ATTRS_GRID_COLS);
}

void CSttModuleAttrsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
 	ASSERT(pData);	
	
	if (pData->GetClassID() == DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData *)pData;
	Show_String(pData,nRow,0,&pDvmData->m_strName); 

	CString strValue,strDataType;
	strDataType = pDvmData->m_strDataType;
	strDataType.MakeUpper();

	if (strDataType == "FLOAT")
	{
		double dValue = CString_To_double(pDvmData->m_strValue);
		strValue.Format(_T("%.03lf"),dValue);
	}
	else
	{
		strValue = pDvmData->m_strValue;
	}

	Show_StaticString(pData,nRow,1,strValue); 
 	nRow++;
}



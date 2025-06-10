//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ?


#include "stdafx.h"
#include "SttAdjModulesGrid.h"
#include "../SttAdjBase.h"
#include "../SttMesLocalDb.h"

CSttAdjModulesGrid::CSttAdjModulesGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	m_strChildDataTypeID = STT_ADJ_DATA_TYPE_Module;
}

CSttAdjModulesGrid::~CSttAdjModulesGrid()
{

}


void CSttAdjModulesGrid::InitGrid()
{
	m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(8);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModulesGrid::InitGridTitle()
{
	CString astrTitle[8] = {_T("���"),_T("ģ������"),_T("ͨ����"),_T("λ�ú�"), _T("�ͺ�"), _T("���к�"), _T("ģ��汾"), _T("��������")};
	CString astrAttrs[8] = {_T(""),_T("ModuleType"), _T("ChannelNum"), _T("ModulePos"), _T("Model"), _T("SN"), _T("FpgaVer"), _T("DateFac")};
	int nWidth[8]={40,80,60,60, 150, 120, 120, 120};

	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 8);
	InitGridColAttrs(astrAttrs, 8);
}


// void CSttAdjModulesGrid::ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol)  	//��ʾDvmData�Ӷ���
// {
// 	if (strDataID != STT_ADJ_ID_ModuleType)
// 	{
// 		CXDataGroupGridBase::ShowAttrCol(pDataGroup, strDataID, nRow, nCol);
// 		return;
// 	}
// 
// 	CExBaseObject *pFind = pDataGroup->FindByID(strDataID);
// 
// 	if (pFind == NULL)
// 	{
// 		return;
// 	}
// 
// 	if (pFind->GetClassID() != DVMCLASSID_CDVMDATA)
// 	{
// 		return;
// 	}
// 
// 	CDvmData *pData = (CDvmData*)pFind;
// 	CDvmData *pModuleType = CSttMesLocalDb::FindModuleTypeData(pData->m_strValue);
// 
// 	if (pModuleType != NULL)
// 	{
// 		Show_StaticString(pData, nRow, nCol, pModuleType->m_strName);
// 	}
// 	else
// 	{
// 		Show_StaticString(pData, nRow, nCol, pData->m_strValue);
// 	}
// }

void CSttAdjModulesGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}

	Show_Index(pData, nRow, 0);
	CDataGroup *pModule = (CDataGroup*)pData;
	CDataGroup *pModuleAttrs = (CDataGroup*)pModule->FindByDataType(STT_ADJ_DATA_TYPE_ModuleAttrs);

	if (pModuleAttrs == NULL)
	{
		return;
	}

	for (long nCol=1; nCol<m_nCols; nCol++)
	{
		CXDataGroupGridBase::ShowAttrCol(pModuleAttrs, nRow, nCol);
	}

	nRow++;
}

#include "..\SttMesLocalDb.h"
CDataType* CSttAdjModulesGrid::FindDataType(const CString &strDataType)
{
	return CSttMesLocalDb::FindDataType(strDataType);
}

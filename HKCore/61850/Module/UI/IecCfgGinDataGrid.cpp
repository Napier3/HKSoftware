#include "StdAfx.h"
#include "IecCfgGinDataGrid.h"

#include "..\XLanguageResourceIec.h"//20161014

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgGinDataGrid::CIecCfgGinDataGrid(long nUseType)
{
	m_nUseType = nUseType;
}


CIecCfgGinDataGrid::~CIecCfgGinDataGrid(void)
{
	
}

void CIecCfgGinDataGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		SetColumnCount(IECCFG_COLS_GINDATA_AT02D);
	} 
	else if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		SetColumnCount(IECCFG_COLS_GINDATA_ISmartTest);
	} 
	else
	{
		SetColumnCount(IECCFG_COLS_GINDATA);
	}

	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgGinDataGrid::InitGridTitle()
{
	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		CString cTempStr[IECCFG_COLS_GINDATA_AT02D]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,//_T("���"),_T("ѡ��"),
			_T("MAC"),_T("APPID"),
			g_sLtxt_InputSel,_T("AT02D���"), g_sLtxt_Description,g_sLtxt_SICDChaNO,//_T("�����ѡ��"), _T("����"), _T("ͨ����")
			g_sLtxt_VersionNumber,g_sLtxt_TestMark,//, _T("�汾��"),_T("���Ա��"),
			_T("gocbRef"), _T("datSet"), _T("goID"), _T("ndsCom") ,
			_T("��������ʱ��(ms)"),_T("�Ƿ����GoCB,GooseID"),
			g_sLtxt_SICDIED};//_T("��������ʱ��(ms)"), _T("�Ƿ����GoCB,GooseID��AppID"), _T("���ƿ�����IED")};
			int iWidth[IECCFG_COLS_GINDATA_AT02D]={60,60, 160,160,90, 100, 80, 80, 80, 80, 80, 80,80 ,80, 120, 120, 80};

			CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GINDATA_AT02D);
	}
	else if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		CString cTempStr[IECCFG_COLS_GINDATA_ISmartTest]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,//_T("���"),_T("ѡ��"),
			_T("����"),_T("�����ѡ��"),g_sLtxt_TestMark,
			_T("MAC"),_T("APPID"),
			g_sLtxt_SICDChaNO,//, , _T("ͨ����")
			g_sLtxt_VersionNumber,//, _T("�汾��")
			_T("gocbRef"), _T("datSet"), _T("goID"), _T("ndsCom") ,
			_T("��������ʱ��(ms)"),_T("�Ƿ����GoCB,GooseID"),
			g_sLtxt_SICDIED};//_T("��������ʱ��(ms)"), _T("�Ƿ����GoCB,GooseID��AppID"), _T("���ƿ�����IED")};
			int iWidth[IECCFG_COLS_GINDATA_ISmartTest]={60,60, 80,80,80,90, 100, 80, 80,  80, 80, 80, 80, 120, 120, 80};

			CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GINDATA_ISmartTest);
	} 
	else
	{
		CString cTempStr[IECCFG_COLS_GINDATA]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,//_T("���"),_T("ѡ��"),
			_T("MAC"),_T("APPID"),
			g_sLtxt_InputSel,g_sLtxt_Description,g_sLtxt_SICDChaNO,//_T("�����ѡ��"), _T("����"), _T("ͨ����")
			g_sLtxt_VersionNumber,g_sLtxt_TestMark,//, _T("�汾��"),_T("���Ա��"),
			_T("gocbRef"), _T("datSet"), _T("goID"), _T("ndsCom") ,
			_T("��������ʱ��(ms)"),_T("�Ƿ����GoCB,GooseID"),
			g_sLtxt_SICDIED};//_T("��������ʱ��(ms)"), _T("�Ƿ����GoCB,GooseID��AppID"), _T("���ƿ�����IED")};
			int iWidth[IECCFG_COLS_GINDATA]={60,60, 160,160,90, 100, 80, 80, 80, 80, 80, 80, 80, 120, 120, 80};

			CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_GINDATA);
	} 
}


void CIecCfgGinDataGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFGGINDATA)
	{
		return;
	}

	CIecCfgDataGridBase::ShowData(pData, nRow, bInsertRow);
	CIecCfgGinData *pIecCfgGinData = (CIecCfgGinData*)pData;

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		CString strTmp;
		Show_StaticString(pData, nRow, 2,    &pIecCfgGinData->m_strIedRefDesc/*m_strgocbIED*/);
		Show_Fiber(pData, nRow, 3,    &pIecCfgGinData->m_nFiberIndex, EndEditCell_Fiber_Gin); //g_strAppPortDataType_Fiber
		Show_DataType_Val(pData, nRow, 4,  g_strAppTestSetDataType,  &pIecCfgGinData->m_bTest,EndEditCell_DataType_Val);
		Show_StaticString(pData, nRow, 5, &pIecCfgGinData->m_strDestAddress);
		strTmp.Format(_T("0X%04X"),pIecCfgGinData->m_dwAppID);
		Show_StaticString(pData, nRow, 6,    strTmp);

		Show_Long(pData, nRow, 7,  &pIecCfgGinData->m_nChannelNum,FALSE);
		Show_Long(pData, nRow, 8,    (long*)&pIecCfgGinData->m_dwVersion, FALSE);
		Show_StaticString(pData, nRow, 9,    &pIecCfgGinData->m_strgocbRef);
		Show_StaticString(pData, nRow, 10,    &pIecCfgGinData->m_strDataSet);
		Show_StaticString(pData, nRow, 11,    &pIecCfgGinData->m_strGooseId);
		Show_Long(pData, nRow, 12,    &pIecCfgGinData->m_bNdsCom,FALSE);
		Show_Long(pData, nRow, 13,    &pIecCfgGinData->m_nLiveTime,FALSE);

		if (pIecCfgGinData->m_nUseGooseID)
		{
			Show_StaticString(pData, nRow, 14, _T("��"));
		} 
		else
		{
			Show_StaticString(pData, nRow, 14, _T("��"));
		}
		
		Show_StaticString(pData, nRow, 15, &pIecCfgGinData->m_strgocbIED/*m_strIedRefDesc*/);
		SetRowFgClr(nRow,4,15,RGB(128,128,128));
		nRow++;
		return;
	}

	Show_Mac(pData, nRow, IECCFG_COL_ID_GINDATA_MAC, &pIecCfgGinData->m_strDestAddress);
	Show_Hex(pData, nRow, IECCFG_COL_ID_GINDATA_APPID,    &pIecCfgGinData->m_dwAppID, 2);
	Show_Fiber(pData, nRow, IECCFG_COL_ID_GINDATA_PORT,    &pIecCfgGinData->m_nFiberIndex, EndEditCell_Fiber_Gin); //g_strAppPortDataType_Fiber

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		Show_Fiber2(pData, nRow, IECCFG_COL_ID_GINDATA_PORT+1,    &pIecCfgGinData->m_nFiber2Index, EndEditCell_Fiber2_Gin); //g_strAppPortDataType_Fiber
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_DESC+1,    &pIecCfgGinData->m_strIedRefDesc/*m_strgocbIED*/);
		Show_ChNum(pData, nRow, IECCFG_COL_ID_GINDATA_CHNUM+1,  &pIecCfgGinData->m_nChannelNum);
		Show_Hex(pData, nRow, IECCFG_COL_ID_GINDATA_VERS+1,    &pIecCfgGinData->m_dwVersion, 2);
		Show_DataType_Val(pData, nRow, IECCFG_COL_ID_GINDATA_TEST+1, g_strAppTestSetDataType,   &pIecCfgGinData->m_bTest,EndEditCell_DataType_Val);
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_GCREF+1,    &pIecCfgGinData->m_strgocbRef);
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_DTSET+1,    &pIecCfgGinData->m_strDataSet);
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_GOID+1,    &pIecCfgGinData->m_strGooseId);
		Show_Check(pData, nRow, IECCFG_COL_ID_GINDATA_NDS+1,    &pIecCfgGinData->m_bNdsCom);
		Show_Long(pData, nRow, IECCFG_COL_ID_GINDATA_LIVE+1,    &pIecCfgGinData->m_nLiveTime);
		Show_Check(pData, nRow, IECCFG_COL_ID_GINDATA_ANALY+1, &pIecCfgGinData->m_nUseGooseID);
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINDATA_CTRLREF+1, &pIecCfgGinData->m_strgocbIED/*m_strIedRefDesc*/);
	}
	else
	{
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_DESC,    &pIecCfgGinData->m_strIedRefDesc/*m_strgocbIED*/);
		Show_ChNum(pData, nRow, IECCFG_COL_ID_GINDATA_CHNUM,  &pIecCfgGinData->m_nChannelNum);
		Show_Hex(pData, nRow, IECCFG_COL_ID_GINDATA_VERS,    &pIecCfgGinData->m_dwVersion, 2);
		Show_DataType_Val(pData, nRow, IECCFG_COL_ID_GINDATA_TEST,  g_strAppTestSetDataType,  &pIecCfgGinData->m_bTest,EndEditCell_DataType_Val);
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_GCREF,    &pIecCfgGinData->m_strgocbRef);
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_DTSET,    &pIecCfgGinData->m_strDataSet);
		Show_String(pData, nRow, IECCFG_COL_ID_GINDATA_GOID,    &pIecCfgGinData->m_strGooseId);
		Show_Check(pData, nRow, IECCFG_COL_ID_GINDATA_NDS,    &pIecCfgGinData->m_bNdsCom);
		Show_Long(pData, nRow, IECCFG_COL_ID_GINDATA_LIVE,    &pIecCfgGinData->m_nLiveTime);
		Show_Check(pData, nRow, IECCFG_COL_ID_GINDATA_ANALY, &pIecCfgGinData->m_nUseGooseID);
		Show_StaticString(pData, nRow, IECCFG_COL_ID_GINDATA_CTRLREF, &pIecCfgGinData->m_strgocbIED/*m_strIedRefDesc*/);
	} 

	nRow++;
}

void CIecCfgGinDataGrid::EndEditCell_Fiber_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgDataGridBase *pIecCfgDataGrid = (CIecCfgDataGridBase*)pGrid;

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
	CIecCfgDatasBase *pIecCfgDatas = (CIecCfgDatasBase*)pIecCfgData->GetParent();
	long nFiberIndex = pIecCfgData->m_nFiberIndex;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
	CExBaseList oListUseDatas;

	if (nFiberIndex == pIecCfgData->m_nFiberIndex)
	{
		return;
	}

	pIecCfgDatas->GetUseDatas(oListUseDatas);

//	if (oListUseDatas.FindIndex(pIecCfgData) < 8) //zhouhj 20210903 �°�ģ�黯���������轫��5���������Ϊ��ͬ,Ϊ���ּ���,���Ŷ�������ÿ�����ƿ�Ĺ��
	{
		if (pIecCfgData->ValidateFiberIndex())
		{
			oListUseDatas.RemoveAll();
			return;
		}

		pIecCfgData->m_nFiberIndex = nFiberIndex;
		pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
		pIecCfgDataGrid->Show_Fiber(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiberIndex);
	}
// 	else
// 	{
// 		//ȥ��ͷ8��
// 		long nIndex = 0;
// 		POS pos = oListUseDatas.GetHeadPosition();
// 
// 		while (nIndex<8)
// 		{
// 			oListUseDatas.RemoveAt(pos);
// 			pos = oListUseDatas.GetHeadPosition();
// 			nIndex++;
// 		}
// 
// 		CExBaseList oListAll;
// 		pIecCfgDatas->GetIecCfgDatas(oListAll);
// 		pos = oListUseDatas.GetHeadPosition();
// 		nFiberIndex = pIecCfgData->m_nFiberIndex;
// 
// 		while (pos != NULL)
// 		{
// 			pIecCfgData = (CIecCfgDataBase *)oListUseDatas.GetNext(pos);
// 			pIecCfgData->m_nFiberIndex = nFiberIndex;
// 			nRow = oListAll.FindIndex(pIecCfgData) + 1;
// 			pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
// 			pIecCfgDataGrid->Show_Fiber(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiberIndex, EndEditCell_Fiber_Gin);
// 		}
// 
// 		oListAll.RemoveAll();
// 	}


	oListUseDatas.RemoveAll();
}

void CIecCfgGinDataGrid::EndEditCell_Fiber2_Gin (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVellData = (_ExBaseCellData*)pCell->lParam;
	ASSERT (pVellData != NULL);
	CIecCfgDataGridBase *pIecCfgDataGrid = (CIecCfgDataGridBase*)pGrid;

	CIecCfgDataBase *pIecCfgData = (CIecCfgDataBase*)pVellData->pObj;
	CIecCfgDatasBase *pIecCfgDatas = (CIecCfgDatasBase*)pIecCfgData->GetParent();
	long nFiber2Index = pIecCfgData->m_nFiber2Index;
	EndEditCell_DataType_Val(nRow, nCol, pCell, pGrid);
// 	CExBaseList oListUseDatas;  //zhouhj 20201205 ������֤�����Ч��
// 
// 	if (nFiberIndex == pIecCfgData->m_nFiberIndex)
// 	{
// 		return;
// 	}
// 
// 	pIecCfgDatas->GetUseDatas(oListUseDatas);
// 
// 	if (oListUseDatas.FindIndex(pIecCfgData) < 8)
// 	{
// 		if (pIecCfgData->ValidateFiberIndex())
// 		{
// 			oListUseDatas.RemoveAll();
// 			return;
// 		}
// 
// 		pIecCfgData->m_nFiberIndex = nFiberIndex;
// 		pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
// 		pIecCfgDataGrid->Show_Fiber(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiberIndex);
// 	}
// 	else
// 	{
// 		//ȥ��ͷ8��
// 		long nIndex = 0;
// 		POS pos = oListUseDatas.GetHeadPosition();
// 
// 		while (nIndex<8)
// 		{
// 			oListUseDatas.RemoveAt(pos);
// 			pos = oListUseDatas.GetHeadPosition();
// 			nIndex++;
// 		}
// 
// 		CExBaseList oListAll;
// 		pIecCfgDatas->GetIecCfgDatas(oListAll);
// 		pos = oListUseDatas.GetHeadPosition();
// 		nFiberIndex = pIecCfgData->m_nFiberIndex;
// 
// 		while (pos != NULL)
// 		{
// 			pIecCfgData = (CIecCfgDataBase *)oListUseDatas.GetNext(pos);
// 			pIecCfgData->m_nFiberIndex = nFiberIndex;
// 			nRow = oListAll.FindIndex(pIecCfgData) + 1;
// 			pIecCfgDataGrid->FreeExBaseCellData(nRow, nCol);
// 			pIecCfgDataGrid->Show_Fiber(pIecCfgData, nRow, nCol, &pIecCfgData->m_nFiberIndex, EndEditCell_Fiber_Gin);
// 		}
// 
// 		oListAll.RemoveAll();
// 	}
// 
// 
// 	oListUseDatas.RemoveAll();
}
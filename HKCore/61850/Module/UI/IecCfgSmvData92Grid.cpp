#include "StdAfx.h"
#include "IecCfgSmvData92Grid.h"

#include "..\XLanguageResourceIec.h"

#define IECFG_COL_WIDTH_INDEX   40
#define IECFG_COL_WIDTH_SELECT  40
#define IECFG_COL_WIDTH_MAC     110
#define IECFG_COL_WIDTH_HEX2    80
#define IECFG_COL_WIDTH_HEX4    100
#define IECFG_COL_WIDTH_HEX8    100

//////////////////////////////////////////////////////////////////////////
//CStCfgGridBase

CIecCfgSmvData92Grid::CIecCfgSmvData92Grid(long nUseType)
{
	m_nUseType = nUseType;
}


CIecCfgSmvData92Grid::~CIecCfgSmvData92Grid(void)
{
	
}

void CIecCfgSmvData92Grid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		SetColumnCount(IECCFG_COLS_92DATA_AT02D);
	}
	else if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		SetColumnCount(IECCFG_COLS_92DATA_ISmartTest);
	} 
	else
	{
		SetColumnCount(IECCFG_COLS_92DATA);
	} 

	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CIecCfgSmvData92Grid::InitGridTitle()
{
 //	CString cTempStr[IECCFG_COLS_92DATA];      ={_T("���"),_T("ѡ��"), _T("���ƿ�����IED"),_T("Ŀ��MAC"),_T("ԴMAC"),_T("APPID"), _T("ͨ����"), _T("TCI Priority"), _T("TCI VID")
// 		, _T("�����ѡ��"), _T("�汾��"), _T("������ʱ"), _T("ͬ����ʽ"), _T("svID"), _T("DataSet")};

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		CString cTempStr[IECCFG_COLS_92DATA_AT02D]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,g_sLtxt_SICDIED,g_sLtxt_SICDDesMAC,
			g_sLtxt_SourceMAC,//_T("���"),_T("ѡ��"), _T("���ƿ�����IED"),_T("Ŀ��MAC"),_T("ԴMAC"),
			_T("APPID"),
			g_sLtxt_SICDChaNO,// _T("ͨ����"),
			_T("TCI Priority"), _T("TCI VID"),
			g_sLtxt_OutputSel,_T("AT02D���"),g_sLtxt_VersionNumber,_T("������ʱ(��s)"),g_sLtxt_SynMode,
			//, _T("�����ѡ��"), _T("�汾��"), _T("������ʱ"), _T("ͬ����ʽ"), 
			_T("svID"), _T("DataSet")};
			int iWidth[IECCFG_COLS_92DATA_AT02D]={IECFG_COL_WIDTH_INDEX,IECFG_COL_WIDTH_SELECT, IECFG_COL_WIDTH_MAC,IECFG_COL_WIDTH_MAC,IECFG_COL_WIDTH_MAC,IECFG_COL_WIDTH_HEX2, IECFG_COL_WIDTH_HEX2, IECFG_COL_WIDTH_HEX2, 80
				, 80, 80, 80, 80, 80, 80, 80};

			CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_92DATA_AT02D);
	}	
	else if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		CString cTempStr[IECCFG_COLS_92DATA_ISmartTest]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,g_sLtxt_SICDIED,
			_T("�����ѡ��"),_T("������ʱ(��s)"),
			g_sLtxt_SICDDesMAC,
			g_sLtxt_SourceMAC,//_T("���"),_T("ѡ��"), _T("���ƿ�����IED"),_T("Ŀ��MAC"),_T("ԴMAC"),
			_T("APPID"),
			g_sLtxt_SICDChaNO,// _T("ͨ����"),
			_T("TCI Priority"), _T("TCI VID"),
			_T("�汾��"),g_sLtxt_SynMode,
			//, _T("�����ѡ��"), _T("�汾��"), _T("������ʱ"), _T("ͬ����ʽ"), 
			_T("svID"), _T("DataSet")};
			int iWidth[IECCFG_COLS_92DATA_ISmartTest]={IECFG_COL_WIDTH_INDEX,IECFG_COL_WIDTH_SELECT,80,80,80, IECFG_COL_WIDTH_MAC,IECFG_COL_WIDTH_MAC,IECFG_COL_WIDTH_HEX2, IECFG_COL_WIDTH_HEX2, IECFG_COL_WIDTH_HEX2, 80
				, 80, 80, 80, 80};

			CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_92DATA_ISmartTest);
	} 
	else
	{
		CString cTempStr[IECCFG_COLS_92DATA]={
			g_sLtxt_SICDGSerial,g_sLtxt_SICDSelect,g_sLtxt_SICDIED,g_sLtxt_SICDDesMAC,
			g_sLtxt_SourceMAC,//_T("���"),_T("ѡ��"), _T("���ƿ�����IED"),_T("Ŀ��MAC"),_T("ԴMAC"),
			_T("APPID"),
			g_sLtxt_SICDChaNO,// _T("ͨ����"),
			_T("TCI Priority"), _T("TCI VID"),
			g_sLtxt_OutputSel,g_sLtxt_VersionNumber,_T("������ʱ(��s)"),g_sLtxt_SynMode,
			//, _T("�����ѡ��"), _T("�汾��"), _T("������ʱ"), _T("ͬ����ʽ"), 
			_T("svID"), _T("DataSet")};
			int iWidth[IECCFG_COLS_92DATA]={IECFG_COL_WIDTH_INDEX,IECFG_COL_WIDTH_SELECT, IECFG_COL_WIDTH_MAC,IECFG_COL_WIDTH_MAC,IECFG_COL_WIDTH_HEX2, IECFG_COL_WIDTH_HEX2, IECFG_COL_WIDTH_HEX2, 80
				, 80, 80, 80, 80, 80, 80, 80};

			CIecCfgDataGridBase::InitGridTitle(cTempStr, iWidth, IECCFG_COLS_92DATA);
	} 

}

void CIecCfgSmvData92Grid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	if (nClassID != CFGCLASSID_CIECCFG92DATA)
	{
		return;
	}

	CIecCfgDataGridBase::ShowData(pData, nRow, bInsertRow);

	CIecCfg92Data *pIecCfg92Data = (CIecCfg92Data*)pData;

	Show_StaticString(pData, nRow, IECCFG_COL_ID_92DATA_CTRLREF,    &pIecCfg92Data->m_strIedRefDesc);

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_ISmartTest)
	{
		CString strTmp;
		Show_Fiber(pData, nRow, 3,    &pIecCfg92Data->m_nFiberIndex);
		Show_Long(pData, nRow, 4,    &pIecCfg92Data->m_nDelay,TRUE,_T(""),EndEditCell_Delay);
		Show_StaticString(pData, nRow, 5, &pIecCfg92Data->m_strDestAddress);
		Show_StaticString(pData, nRow, 6,  &pIecCfg92Data->m_strSrcAddress);

		strTmp.Format(_T("0X%04X"),pIecCfg92Data->m_dwAppID);
		Show_StaticString(pData, nRow, 7,    strTmp);

		Show_Long(pData, nRow, 8,    &pIecCfg92Data->m_nChannelNum,FALSE,_T(""));
		Show_Long(pData, nRow, 9,    &pIecCfg92Data->m_nPriority,FALSE,_T(""));
		strTmp.Format(_T("0X%03X"),pIecCfg92Data->m_dwVID);
		Show_StaticString(pData, nRow, 10,    strTmp);
		strTmp.Format(_T("%d"),pIecCfg92Data->m_dwVersion);
		Show_StaticString(pData, nRow, 11,    strTmp);
		strTmp = GetSynModeDataTypeValue(pIecCfg92Data->m_nSyn);
		Show_StaticString(pData, nRow, 12,    strTmp);
		Show_StaticString(pData, nRow, 13,    &pIecCfg92Data->m_strSVID);
		Show_StaticString(pData, nRow, 14,    &pIecCfg92Data->m_strDataSet);
		SetRowFgClr(nRow,5,14,RGB(128,128,128));
		nRow++;
		return;
	}

	Show_Mac(pData, nRow, IECCFG_COL_ID_92DATA_DEST_MAC, &pIecCfg92Data->m_strDestAddress);
	Show_Mac(pData, nRow, IECCFG_COL_ID_92DATA_SRC_MAC,  &pIecCfg92Data->m_strSrcAddress);
	Show_Hex(pData, nRow, IECCFG_COL_ID_92DATA_APPID,    &pIecCfg92Data->m_dwAppID, 2);
	Show_ChNum(pData, nRow, IECCFG_COL_ID_92DATA_CHNUM,  &pIecCfg92Data->m_nChannelNum);
	Show_Long(pData, nRow, IECCFG_COL_ID_92DATA_PRIO,    &pIecCfg92Data->m_nPriority,TRUE,_T(""),EndEditCell_Priority);
	Show_VlanID(pData, nRow, IECCFG_COL_ID_92DATA_VID,    &pIecCfg92Data->m_dwVID, 2);//VlanID��Ϊ2���ֽ�,ʵ��ֻ�õ�16����3λ  zhouhj 20211030
	Show_Fiber(pData, nRow, IECCFG_COL_ID_92DATA_PORT,    &pIecCfg92Data->m_nFiberIndex);

	if (m_nUseType == IEC_CFG_DEVICE_USE_TYPE_AT02D)
	{
		Show_Fiber2(pData, nRow, IECCFG_COL_ID_92DATA_PORT+1,    &pIecCfg92Data->m_nFiber2Index);
		Show_Hex(pData, nRow, IECCFG_COL_ID_92DATA_VERS+1,    &pIecCfg92Data->m_dwVersion,4);
		Show_Long(pData, nRow, IECCFG_COL_ID_92DATA_SMPDELAY+1,    &pIecCfg92Data->m_nDelay,TRUE,_T(""),EndEditCell_Delay);
		Show_Syn(pData, nRow, IECCFG_COL_ID_92DATA_SYN+1,    &pIecCfg92Data->m_nSyn);
		Show_String(pData, nRow, IECCFG_COL_ID_92DATA_SVID+1,    &pIecCfg92Data->m_strSVID);
		Show_String(pData, nRow, IECCFG_COL_ID_92DATA_DATASET+1,    &pIecCfg92Data->m_strDataSet);
	}	
	else
	{
		Show_Hex(pData, nRow, IECCFG_COL_ID_92DATA_VERS,    &pIecCfg92Data->m_dwVersion,4);
		Show_Long(pData, nRow, IECCFG_COL_ID_92DATA_SMPDELAY,    &pIecCfg92Data->m_nDelay,TRUE,_T(""),EndEditCell_Delay);
		Show_Syn(pData, nRow, IECCFG_COL_ID_92DATA_SYN,    &pIecCfg92Data->m_nSyn);
		Show_String(pData, nRow, IECCFG_COL_ID_92DATA_SVID,    &pIecCfg92Data->m_strSVID);
		Show_String(pData, nRow, IECCFG_COL_ID_92DATA_DATASET,    &pIecCfg92Data->m_strDataSet);
	}

	nRow++;
}

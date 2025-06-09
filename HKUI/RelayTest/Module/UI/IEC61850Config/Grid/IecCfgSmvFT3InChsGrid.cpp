#include "IecCfgSmvFT3InChsGrid.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../Module/CommonMethod/commonMethod.h"
#include "../../SoftKeyboard/SoftKeyBoard.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonInData.h"
#include "../../../../../Module/XLanguage/XLanguageResource.h"
#include "../../../XLangResource_Native.h"
#include "../../../61850/Module/CfgDataMngr/IecCfg6044CommonChIn.h"

#define STT_IECCFG_FT3IN_GridIndex_Select                0
#define STT_IECCFG_FT3IN_GridIndex_ChDesc                1
#define STT_IECCFG_FT3IN_GridIndex_ChType                2
#define STT_IECCFG_FT3IN_GridIndex_ChMap                 3
#define STT_IECCFG_FT3IN_GridIndex_ChLenth               4
#define STT_IECCFG_FT3IN_GridIndex_BinMap                5
#define STT_IECCFG_FT3IN_GridIndex_AccuracyLevel         6


CIecCfgSmvFT3InChsGrid::CIecCfgSmvFT3InChsGrid(QWidget* pparent):CIecCfgChsGridBase(pparent)
{
	m_pGinAppChDataType = NULL;
}

CIecCfgSmvFT3InChsGrid::~CIecCfgSmvFT3InChsGrid()
{

}

void CIecCfgSmvFT3InChsGrid::InitGrid()
{
//	CIecCfgChsGridBase::InitGrid();
	InitGridTitle();
	QExBaseListCheckBoxDelegate *pCheckBoxDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(STT_IECCFG_FT3IN_GridIndex_Select,pCheckBoxDelegate);
	m_pChType_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(STT_IECCFG_FT3IN_GridIndex_ChType,m_pChType_DelegBase);
	m_pChMap_DelegBase = new QIecCfgChsComBoxDelegBase(this);
	setItemDelegateForColumn(STT_IECCFG_FT3IN_GridIndex_ChMap,m_pChMap_DelegBase);
#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
	//	AutoAdjColWidth();

	m_pBitLen_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(STT_IECCFG_FT3IN_GridIndex_ChLenth,m_pBitLen_DelegBase);

	m_pChAccLevelDelegate = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,m_pChAccLevelDelegate);
	SetEditable(TRUE);
	m_pGinAppChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);

	connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(slot_BinMap_Clicked(int,int)));
	connect(this,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(slot_doubleClicked(int,int)),Qt::UniqueConnection);
}

void CIecCfgSmvFT3InChsGrid::InitGridTitle()
{
	CString strChChoose;
	xlang_GetLangStrByFile(strChChoose,"sSelect");
	//_T("SMV通道"),_T("描述"),_T("通道类型"),_T("通道映射"),_T("字节长度"),_T("开入量映射")

	CString astrGridTitle[IECCFGSMVFT3InCHS_GRID_COLS] = {strChChoose,g_sLangTxt_IEC_ChDescription,g_sLangTxt_IEC_ChType,g_sLangTxt_IEC_ChMaps,
		g_sLangTxt_IEC_ChByteLen,g_sLangTxt_IEC_InputMap,/*"准确级"*/g_sLangTxt_IEC_AccuratyLevel.GetString()};
	int iGridWidth[IECCFGSMVFT3InCHS_GRID_COLS]={80,200,200,250,150,150,150};

	//20230725 suyang 适配分辨率 1024X768

#ifdef _PSX_QT_WINDOWS_

		iGridWidth[STT_IECCFG_FT3IN_GridIndex_ChDesc] = 150;
		iGridWidth[STT_IECCFG_FT3IN_GridIndex_ChType] = 150;
		iGridWidth[STT_IECCFG_FT3IN_GridIndex_ChMap] = 150;

#endif


	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IECCFGSMVFT3InCHS_GRID_COLS);
}

void CIecCfgSmvFT3InChsGrid::UpdateChLength(CExBaseObject *pData, int& nRow, long nChLength, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFG6044COMMONCHIN)
	{
		return;
	}

	CIecCfg6044CommonChIn *pIecCfgFT3Ch= (CIecCfg6044CommonChIn*)pData;

	if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		Show_DataType_Val(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,
			iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		Show_DataType_Val(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,
			iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
	}
	else 
	{
		pIecCfgFT3Ch->m_nChLenth = nChLength;
		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
	}

	nRow++;
}

void CIecCfgSmvFT3InChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != CFGCLASSID_CIECCFG6044COMMONCHIN)
	{
		return;
	}

	CIecCfg6044CommonChIn *pIecCfgFT3ChIn= (CIecCfg6044CommonChIn*)pData;

	CIecCfg6044CommonInData *pIecCfg6044CommonData = (CIecCfg6044CommonInData*)pIecCfgFT3ChIn->GetAncestor(CFGCLASSID_CIECCFG6044COMMONINDATA);
	BOOL bEnableAll = TRUE;

	if (pIecCfg6044CommonData != NULL)
	{
		if (!pIecCfg6044CommonData->m_strProtocolID.IsEmpty())
		{
			bEnableAll = FALSE;
		}
	}

	long nCurrChIndex = pIecCfgFT3ChIn->m_nIndex ;

    if (pIecCfgFT3ChIn->m_strName.IsEmpty() || pIecCfgFT3ChIn->m_strName.Find(_T("Ch")) >= 0)//cl20231027设置通道缺省项
	{
		pIecCfgFT3ChIn->m_strName.Format(/*_T("通道%d")*/g_sLangTxt_Native_ChnN,nCurrChIndex+1);
	}

	Show_Check(pData,nRow,STT_IECCFG_FT3IN_GridIndex_Select,&pIecCfgFT3ChIn->m_nUseFlag);
	Show_String(pData,nRow,STT_IECCFG_FT3IN_GridIndex_ChDesc,&pIecCfgFT3ChIn->m_strName);

	if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		Show_DataType_Val(pData,nRow,STT_IECCFG_FT3IN_GridIndex_ChType,
			iecfg_SmvCommon6044DCChDataType,&pIecCfgFT3ChIn->m_strChType,
			EndEditCell_SmvFT3ChSelChangged);
	}
	else
	{
		Show_DataType_Val(pData,nRow,STT_IECCFG_FT3IN_GridIndex_ChType,
			iecfg_SmvCommon6044ChInDataType,&pIecCfgFT3ChIn->m_strChType,
			EndEditCell_SmvFT3ChSelChangged);
	}

	UpdateData_ByDataType(pIecCfgFT3ChIn,nRow);
//	Show_DataType_Val(pData,nRow,1,iecfg_SmvCommon6044ChDataType,&pIecCfgFT3Ch->m_strChType,EndEditCell_SmvFT3ChSelChangged);
//	ShowCfgCh_AppCh(pData, nRow, 2, &pIecCfgFT3Ch->m_strAppChID, iecfg_SmvAppChDataType);
//	UpdateData_ByDataType(pIecCfgFT3Ch,nRow);
	//Show_DataType_Val(pData,nRow,2,iecfg_SmvAppChDataType,&pIecCfgFT3Ch->m_strAppChID);
//	Show_DataType_Val(pData,nRow,3,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);

	SetItemEnable(nRow,STT_IECCFG_FT3IN_GridIndex_ChDesc,bEnableAll);
	SetItemEnable(nRow,STT_IECCFG_FT3IN_GridIndex_ChType,bEnableAll);
	SetItemEnable(nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,bEnableAll);
	nRow++;
}
void CIecCfgSmvFT3InChsGrid::EndEditCell_SmvFT3ChSelChangged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfg6044CommonChIn *pIecCfgSmvFT3Ch = (CIecCfg6044CommonChIn*)pVCellData->pObj;
	((CIecCfgSmvFT3InChsGrid*)pGrid)->UpdateData_ByDataType(pIecCfgSmvFT3Ch,nRow);
}
void CIecCfgSmvFT3InChsGrid::UpdateData_ByDataType(CIecCfg6044CommonChIn *pIecCfgFT3Ch,int nRow)
{
	CIecCfg6044CommonInData *pIecCfg6044CommonInData = (CIecCfg6044CommonInData*)pIecCfgFT3Ch->GetAncestor(CFGCLASSID_CIECCFG6044COMMONINDATA);
	//2024-1-20 zhouyangyong 修改通道类型改变成电流电压后，采样位宽不对应刷新的问题
	if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCCur)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_DCI, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_I, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCVol)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_DCU, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_U, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_NeutralU)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_NeutralU, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_U, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	}
// 	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
// 	{
// 		Show_DataType_Val(pIecCfgFT3Ch, nRow, 2,iecfg_SmvAppChDataType_StateValue, &pIecCfgFT3Ch->m_strAppChID,
// 			EndEditCell_SmvFT3ChMapSelChangged);
// 		Show_Long(pIecCfgFT3Ch,nRow,4,&pIecCfgFT3Ch->m_nValue);
// 	}
// 	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
// 	{
// 		Show_DataType_Val(pIecCfgFT3Ch, nRow, 2,iecfg_SmvAppChDataType_Other, &pIecCfgFT3Ch->m_strAppChID,
// 			EndEditCell_SmvFT3ChMapSelChangged);
// 
// 		//两个都是“其它”时,可以独立设置  zhouhj 2023.9.13
// 		if (pIecCfgFT3Ch->m_strAppChID == iecfg_SmvChDataType_Val_Other)
// 		{
// 			Show_Long(pIecCfgFT3Ch,nRow,4,&pIecCfgFT3Ch->m_nValue);
// 		} 
// 		else
// 		{
// 			Show_StaticString(pIecCfgFT3Ch,nRow,4,_T("--"));
// 		}
// 	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_6U, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_U, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_U, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_U, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_6I, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_I, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)||
		(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure))
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_I, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_I, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_6I,&pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));

		if (pIecCfg6044CommonInData != NULL)
		{
			pIecCfgFT3Ch->m_nChLenth = pIecCfg6044CommonInData->m_nSmpDataLen;
		}

		Show_Long(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,&pIecCfgFT3Ch->m_nChLenth,FALSE);
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,iecfg_SmvInAppChAccLevelDataType_I, 
			&pIecCfgFT3Ch->m_nAccuratyLevel);
	}

	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_StateValue, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);

		CString strText;
		ShowCommonBinMap(pIecCfgFT3Ch,strText);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,&strText);

		Show_DataType_Val(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
		Show_StaticString(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,"--");
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		Show_DataType_Val(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_ChMap,
			iecfg_SmvAppChDataType_Other, &pIecCfgFT3Ch->m_strAppChID,EndEditCell_SmvFT3ChMapSelChangged);
		
		//两个都是“其它”时,可以弹出  suyang 2024.02.27
		if (pIecCfgFT3Ch->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			CString strText;
			ShowCommonBinMap(pIecCfgFT3Ch,strText);
			Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,&strText);

		} 
		else
		{
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
		}

		Show_DataType_Val(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_ChLenth,iecfg_SmvChByteLen,&pIecCfgFT3Ch->m_nChLenth);
		Show_StaticString(pIecCfgFT3Ch, nRow, STT_IECCFG_FT3IN_GridIndex_AccuracyLevel,"--");
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前SMVFT3通道映射出错(%s)."),pIecCfgFT3Ch->m_strChType.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurSmvErr.GetString(),pIecCfgFT3Ch->m_strChType.GetString()); 
	}
}

void CIecCfgSmvFT3InChsGrid::EndEditCell_SmvFT3ChMapSelChangged(int nRow, int nCol, QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL);
	ASSERT(pVCellData->pExBaseList != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CIecCfg6044CommonCh *pIecCfgFT3Ch = (CIecCfg6044CommonCh*)pVCellData->pObj;

	((CIecCfgSmvFT3InChsGrid*)pGrid)->UpdateChBinMap(pIecCfgFT3Ch,nRow);

	((CIecCfgSmvFT3InChsGrid*)pGrid)->slot_BinMap_Clicked(nRow,nCol);
}

void CIecCfgSmvFT3InChsGrid::UpdateChBinMap(CIecCfg6044CommonCh *pIecCfgFT3Ch,int nRow)
{
	if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCCur)
	{
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCVol)
	{
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_NeutralU)
	{
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		CString strText;
		ShowCommonBinMap(pIecCfgFT3Ch,strText);
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,&strText);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		//两个都是“其它”时,可以独立设置  20240312 suyang
		if (pIecCfgFT3Ch->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			CString strText;
			ShowCommonBinMap(pIecCfgFT3Ch,strText);
			Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,&strText);
		} 
		else
		{
			Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
		}
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol))
	{
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure))
	{
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		Show_StaticString(pIecCfgFT3Ch,nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,_T("--"));
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurSmvErr.GetString(),pIecCfgFT3Ch->m_strChType.GetString());
	}

	SetItemEditable(nRow,STT_IECCFG_FT3IN_GridIndex_BinMap,FALSE);

}

void CIecCfgSmvFT3InChsGrid::GridDoubleClicked_ShowKeyBoard( int nRow,int nCol )
{
	if (nCol != 0)
	{
		return;
	}
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	QString strValue = pItem->text();
	GetEngWidgetBoard_DigitData(strValue, parentWidget()->parentWidget());
	pItem->setText(strValue);

	// 	WidgetKeyboard dlg(this);
	// 	dlg.m_InputString = pItem->text();
	// 	dlg.showToEdit();
	// 	if (dlg.exec() == QDialog::Accepted)
	// 	{
	// 		pItem->setText(dlg.m_InputString);
	// 	}
}


// void  CIecCfgSmvFT3InChsGrid::ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor)
// {
// 	CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pData;
// 
// 	 if (iecfg_IsOtherChType(pSmvCh->m_strChType))//zhouhj 20211012 增加用于CommonFT3 Smv通道其它
// 	{
// 		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_Other, pstrAppCh);
// 		Show_StaticString(pData, nRow, 4, _T("--"));
// 	}
// 	else
	// 	{
// 		Show_DataType_Val(pData, nRow, nCol, iecfg_SmvAppChDataType_StateValue, pstrAppCh);
// 		//		Show_DataType_Val(pData, nRow, IECCFG_COL_ID_6044CHIN_COMMON_BINMAP, iecfg_GinAppChDataType, &pSmvCh->m_strDevChID);
// 		ShowCommonBinMap_StaticString(pData, nRow);
// 	}
	// 	}

void CIecCfgSmvFT3InChsGrid::ShowCommonBinMap_StaticString(CExBaseObject *pData, int nRow)
{
	CIecCfgDataSmvChBase *pSmvCh = (CIecCfgDataSmvChBase*)pData;
	CString strShowString;

	ShowCommonBinMap(pSmvCh,strShowString);


	Show_StaticString(pData, nRow, STT_IECCFG_FT3IN_GridIndex_BinMap,&strShowString);
}

void CIecCfgSmvFT3InChsGrid::ShowCommonBinMap(CIecCfgDataSmvChBase *pIecCfgDataSmvChBase, CString &strShowString)
{

	strShowString = pIecCfgDataSmvChBase->m_strDevChID;

	if (m_pGinAppChDataType == NULL)
	{
		m_pGinAppChDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);
	}

	if (m_pGinAppChDataType != NULL)
	{
		CEquationBuffer oEquationBuffer(pIecCfgDataSmvChBase->m_strDevChID);
		CString strBitID,strBinID;
		CExBaseObject *pDataTypeValue = NULL;
		strShowString = _T("");

		for (int nIndex = 0;nIndex<16;nIndex++)
		{
			strBinID = _T("");
			strBitID.Format(_T("bit%d"),nIndex);
			oEquationBuffer.ParseString(strBitID,strBinID);

			if (!strBinID.IsEmpty())
			{
				pDataTypeValue = m_pGinAppChDataType->FindByID(strBinID);

				if (pDataTypeValue != NULL)
				{
					strShowString += pDataTypeValue->m_strName;
					strShowString += _T(";");
				}
			} 
		}

		if (strShowString.IsEmpty())
		{
			//strShowString = _T("无");
			strShowString = g_sLangTxt_None; 
		}
	}
}

// void CIecCfgSmvFT3InChsGrid::slot_BinMap_doubleClicked( int nRow,int nCol )
// {
// 	if (nCol != 4)
// 	{
// 		return;
// 	}
// 
// 
// 	QGV_ITEM *pItem = GetCell(nRow,nCol);
// 
// 	if (pItem == NULL)
// 	{
// 		return;
// 	}
// 
// 	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pItem->lParam;
// 
// 	CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pVCellData->pObj;
// 
// 	if (pIecCfg6044CommonCh == NULL)
// 	{
// 		return;
// 	}
// 
// 	QSttIecSMVFT3InMapSetDialog oDIMapDlg(pIecCfg6044CommonCh->m_strDevChID,this);
// 	oDIMapDlg.exec();
// 	pIecCfg6044CommonCh->m_strDevChID = oDIMapDlg.m_strMapString;
// 	ShowCommonBinMap_StaticString(pIecCfg6044CommonCh,nRow);
// 	update();
// }

void CIecCfgSmvFT3InChsGrid::slot_BinMap_Clicked( int nRow,int nCol )
{
	bool isBinMapEnabled = FALSE;

	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem == NULL)
	{
		return;
	}

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pItem->lParam;

	CIecCfg6044CommonCh *pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pVCellData->pObj;

	if (pIecCfg6044CommonCh == NULL)
	{
		return;
	}

	if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{
		isBinMapEnabled = TRUE;

	}	
	else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
	{

		//两个都是“其它”时,可以弹出  suyang 2024.02.27
		if (pIecCfg6044CommonCh->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			isBinMapEnabled = TRUE;

		} 

	}


	emit sig_UpdateBinMapEnabled(isBinMapEnabled);
	
}

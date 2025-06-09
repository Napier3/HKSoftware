#pragma once
#include "..\..\..\module\gridctrl\gridctrl.h"
#include "CfgSclCmpTool.h"

#define CFGSCLCMP_GRID_ROWHEIGHT 19


class CCfgSclCmpGrid :	public CGridCtrl
{
public:
	CCfgSclCmpGrid();
	virtual ~CCfgSclCmpGrid(void);


public:
	void InitStGrid();
	void ShowCfgSclCmp(CCfgSclCmpData *pSclData, CCfgSclCmpData *pCfgData);

protected:
	COLORREF m_crBkColor;
	COLORREF m_crTextColor;
	COLORREF m_crTitleTextBkColor;
	COLORREF m_crDataTextBkColor;

	//œ‘ æπ¶ƒ‹
	void ShowDataAttrCmp(CCfgSclCmpParaObjects *pSclParas, CCfgSclCmpParaObjects *pCfgParas, long& nRow);
	void ShowDataChCmp(CCfgSclCmpParaObjects *pSclParas, CCfgSclCmpParaObjects *pCfgParas, long& nRow);
	void ShowDataPara(CCfgSclCmpParaObject *pSclPara, CCfgSclCmpParaObject *pCfgPara, long& nRow, long nAttrCol);

	void InitDataCellItem(GV_ITEM& Item);
};


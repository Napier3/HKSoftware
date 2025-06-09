#pragma once
#include "IECCfgDataGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGOUTData.h"

#define IECCFG_COL_ID_GOUTCH_DESC     1
#define IECCFG_COL_ID_GOUTCH_CHTYPE   2
#define IECCFG_COL_ID_GOUTCH_APPCH    3
#define IECCFG_COL_ID_GOUTCH_VALUE    4
#define IECCFG_COL_ID_GOUTCH_DESCEXTERNAL  5
#define IECCFG_COL_ID_GOUTCH_ADDREXTERNAL  6

#define IECCFG_COLS_GOUTCH            7

class CIECCfgGoutDataChsGrid : public CIECCfgDataChsGridBase
{
public:
	CIECCfgGoutDataChsGrid();
	virtual ~CIECCfgGoutDataChsGrid();
	
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

protected:
	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_ChDataType_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_AppCh_Gout (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20200105 ����DevChʹ��
	static void EndEditCell_AppCh_GoutDefaultValue(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);//zhouhj 20210912 ���ӶԲ�ͬ�������͵ĳ�ʼֵ���ж�
	virtual void  ShowCfgCh_DefValue(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrValue);
};


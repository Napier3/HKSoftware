#pragma once
#include "IecCfgDataChsGridBase.h"


class CIecCfgSmvDataChsGridBase : public CIecCfgDataChsGridBase
{
public:
	CIecCfgSmvDataChsGridBase();
	virtual ~CIecCfgSmvDataChsGridBase();

	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);

	virtual void  ShowCfgCh_Type(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrChType,const CString &strDataType, BOOL bSetColor=TRUE);
	static void EndEditCell_ChType (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

	virtual long GetAppChColIndex()	= 0;

public:
	void SetAbc(BOOL bSetU, BOOL bSetI);
	void SetPabc(BOOL bSetU, BOOL bSetI);
	void SetSabc(BOOL bSetU, BOOL bSetI);
	void SetTabc(BOOL bSetU, BOOL bSetI);
	void Setabc5(BOOL bSetU, BOOL bSetI);//zhouhj20210924
	void Setabc6(BOOL bSetU, BOOL bSetI);//zhouhj20210924

};


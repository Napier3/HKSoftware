#ifndef IECCFGSMVFT3InCHSGRID_H
#define IECCFGSMVFT3InCHSGRID_H

#include "IecCfgChsGridBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonChIn.h"


#define IECCFGSMVFT3InCHS_GRID_COLS		7

class CIecCfgSmvFT3InChsGrid : public CIecCfgChsGridBase
{
	Q_OBJECT

public:
	CIecCfgSmvFT3InChsGrid(QWidget* pparent);
	virtual ~CIecCfgSmvFT3InChsGrid();

protected:
	QExBaseListComBoxDelegBase *m_pBitLen_DelegBase;
	QExBaseListComBoxDelegBase *m_pChAccLevelDelegate;
	CDataType* m_pGinAppChDataType;
public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void UpdateChLength(CExBaseObject *pData, int& nRow, long nChLength, BOOL bInsertRow=TRUE);//2023-12-5 zhou yangyong 更新位宽
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfg6044CommonChIn *pIecCfgSmvFT3Ch,int nRow);
	void ShowCommonBinMap_StaticString(CExBaseObject *pData, int nRow);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
//	virtual void  ShowCfgCh_AppCh(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pstrAppCh,const CString &strDataType, BOOL bSetColor=TRUE);
//	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);

	void ShowCommonBinMap(CIecCfgDataSmvChBase *pIecCfgDataSmvChBase, CString &strShowString);
	void UpdateChBinMap(CIecCfg6044CommonCh *pIecCfgSmvFT3Ch,int nRow);
public:
	//编辑处理函数
	static void EndEditCell_SmvFT3ChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_SmvFT3ChMapSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

public slots:
//		void slot_BinMap_doubleClicked(int nRow,int nCol);
		void slot_BinMap_Clicked(int nRow,int nCol);
signals:
		void sig_UpdateBinMapEnabled(bool isBinMapEnabled);
};

#endif // IECCFGSMV92CHSGRID_H

#ifndef SttIecCbGrid_H
#define SttIecCbGrid_H

#include "../../UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"


#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceSmvCh.h"
#include "../../../../Module/SmartCap/61850Cap/CapDevice/CapDeviceGooseCh.h"

//表格显示类型分为两种,即9-2,GOOSE； FT3，两者需要显示的列不同
#define STT_IECCBGRID_SHOW_TYPE_61850                  0
#define STT_IECCBGRID_SHOW_TYPE_60044                  1





class CSttIecCbGrid : public QExBaseListGridBase
{
public:
	CSttIecCbGrid(QWidget* pparent);
	virtual ~CSttIecCbGrid();

	BOOL m_bViewSmv;
	BOOL m_bViewGoose;
	BOOL m_bViewFT3;
	CExBaseList *m_pAllSelCBs;  //所有选择的控制块
	long m_nIecCbShowType;
public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	virtual void Show_Mac(CExBaseObject *pStData, const int& nRow, const int& nCol, BYTE *pMac);
	virtual void Show_61850Type(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nType);
	virtual void Show_Fiber(CExBaseObject *pStData, const int& nRow, const int& nCol, UINT nFiberIndex);
	virtual void UpdateDatas();
	void AddCapDevice(CExBaseObject *pCapDevice);
	void UpdateCapDevice(CExBaseObject *pCapDevice);//更新表格中的某一行
	void SelectRecordDevice(CExBaseObject *pStData, BOOL bSel);

	//该UpdateData函数，改到基类了 shaolei 20220902
	//virtual BOOL UpdateData(CExBaseObject *pData);

	void UpdateCapDeviceLinkState();
	CExBaseObject* GetCurrSelData_BySelect();
	CExBaseList* GetAllSelectedCbs();

	static void EndEditCell_SelectCB(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	void InitGridTitle_61850();
	void InitGridTitle_60044();

	void ShowData_61850(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowData_60044(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};

void ShowColorRow(QExBaseListGridBase* pGridCtrl, int nMatchState, int nRow, int nCols);

#endif // SttIecCbGrid_H

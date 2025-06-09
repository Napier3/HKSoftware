#ifndef SttIecSmvGrid_HarmAnalyze_H
#define SttIecSmvGrid_HarmAnalyze_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"


class CSttIecSmvGrid_HarmAnalyze : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_HarmAnalyze(QWidget* pparent);
	virtual ~CSttIecSmvGrid_HarmAnalyze();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();
	virtual void UpdateDatas();
	void UpdateDataset_MUTestCB(CString strChannelID,CString strValue);

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	void ShowDataEx(CDvmData *pChData, int nRow);
	void ShowBaseActualValue(CDvmData *pChData, int nRow);
	static void EndEditCell_BaseLimitValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

};

#endif

#ifndef SttIecSmvGrid_Power_H
#define SttIecSmvGrid_Power_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//SMV   ¹¦ÂÊ
class CSttIecSmvGrid_Power : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_Power(QWidget* pparent);
	virtual ~CSttIecSmvGrid_Power();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

	virtual BOOL NeedNextAndPrev();
	virtual void NextPage();
	virtual void PrevPage();

	CDvmDataset *m_pDvmDataset_Power;
	CDvmData *m_pCurrPower;
	long m_nCurrPowerIndex;

public:
	virtual void InitGridTitle();
	void ShowCurrPower();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE){};

	void ShowCurrPower_Ch(CDvmValue *pChABC, long nRow, long nCol);
	CDvmDataset* GetDvmDataset();
};

#endif // SttIecSmvGrid_Power_H

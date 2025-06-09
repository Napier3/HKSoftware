#ifndef SttIecSmvGrid_AD_H
#define SttIecSmvGrid_AD_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//SMV   AD
class CSttIecSmvGrid_AD : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_AD(QWidget* pparent);
	virtual ~CSttIecSmvGrid_AD();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

public:
	virtual void InitGridTitle();

	//virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	void ShowDataEx(CDvmData *pChData, int nRow);
	CDvmDataset* GetDvmDataset();
	//virtual void UpdateDatas();

	//CDvmData* FindAD(CDvmData *pChData, CExBaseList *pDvmDataset);
	//void CalAD1_AD2(float &fValue1, float &fValue2, float &fValue3, CDvmData *pAD1, CDvmData *pAD2);
};

#endif // SttIecSmvGrid_AD_H

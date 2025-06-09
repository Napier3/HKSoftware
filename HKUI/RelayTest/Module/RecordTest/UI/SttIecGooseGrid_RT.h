#ifndef SttIecGooseGrid_RT_H
#define SttIecGooseGrid_RT_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//GOOSE   
class CSttIecGooseGrid_RT : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecGooseGrid_RT(QWidget* pparent);
	virtual ~CSttIecGooseGrid_RT();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();
	virtual BOOL NeedAddToSubPub(){return TRUE;}

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowDataEx(CDvmData *pChData, int nRow);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
};

#endif // SttIecGooseGrid_RT_H

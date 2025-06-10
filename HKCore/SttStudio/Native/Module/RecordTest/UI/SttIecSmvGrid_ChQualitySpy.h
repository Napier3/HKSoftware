#ifndef SttIecSmvGrid_ChSpy_H
#define SttIecSmvGrid_ChSpy_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"
#define SmvGrid_ChQualitySpy_MAX_ROW_NUM      4

//SMV   Õ®µ¿º‡ ”
class CSttIecSmvGrid_ChQualitySpy : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_ChQualitySpy(QWidget* pparent);
	virtual ~CSttIecSmvGrid_ChQualitySpy();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	virtual void ShowSpy(CCapDeviceSmvCh *pSmvChData,int& nRow);
};

#endif // SttIecSmvGrid_ChSpy_H

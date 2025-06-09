#ifndef SttIecGooseGrid_PkgStc_H
#define SttIecGooseGrid_PkgStc_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//SMV   报文统计
class CSttIecGooseGrid_PkgStc : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecGooseGrid_PkgStc(QWidget* pparent);
	virtual ~CSttIecGooseGrid_PkgStc();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	CDvmData* GetDvmData(CDvmDataset *pGooseErr);
};

#endif // SttIecGooseGrid_PkgStc_H

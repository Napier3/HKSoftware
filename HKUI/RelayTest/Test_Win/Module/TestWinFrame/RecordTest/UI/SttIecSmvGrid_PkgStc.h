#ifndef SttIecSmvGrid_PkgStc_H
#define SttIecSmvGrid_PkgStc_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//SMV   报文统计
class CSttIecSmvGrid_PkgStc : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_PkgStc(QWidget* pparent);
	virtual ~CSttIecSmvGrid_PkgStc();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	//CDvmData* GetDvmData(CDvmDataset *pSVErr);
};

#endif // SttIecSmvGrid_PkgStc_H

#ifndef SttIecSmvGrid_Harm_H
#define SttIecSmvGrid_Harm_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//SMV   谐波
class CSttIecSmvGrid_Harm : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_Harm(QWidget* pparent);
	virtual ~CSttIecSmvGrid_Harm();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	void ShowDataEx(CDvmData *pChData, int nRow);
};

#endif // SttIecSmvGrid_Harm_H

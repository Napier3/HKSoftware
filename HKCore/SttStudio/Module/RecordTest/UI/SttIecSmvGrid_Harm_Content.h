#ifndef SttIecSmvGrid_Harm_Content
#define SttIecSmvGrid_Harm_Content

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"


class CSttIecSmvGrid_Harm_Content : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_Harm_Content(QWidget* pparent);
	virtual ~CSttIecSmvGrid_Harm_Content();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	void ShowDataEx(CDvmData *pChData, int nRow);
	virtual void ShowAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision);
};

#endif 

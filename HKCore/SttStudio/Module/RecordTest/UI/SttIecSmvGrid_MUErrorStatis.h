#ifndef SttIecSmvGrid_MUErrorStatis_H
#define SttIecSmvGrid_MUErrorStatis_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

#define SmvGrid_MUErrorStatis_MAX_ROW_NUM      7

//SMV   ˫MUErrorStatis
class CSttIecSmvGrid_MUErrorStatis : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_MUErrorStatis(QWidget* pparent);
	virtual ~CSttIecSmvGrid_MUErrorStatis();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();
	virtual void Config();//页面功能配置
	virtual void UpdateChName();

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void UpdateDatas();
	void ShowDataEx(CDvmData *pChData, int nRow);
	void ShowAttrValue_ErrorStatis(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision = -1);
};

#endif // SttIecSmvGrid_MUErrorStatis_H

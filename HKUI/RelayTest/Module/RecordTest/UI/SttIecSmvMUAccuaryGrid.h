#ifndef STTIECSMVMUACCUARYGRID_H
#define STTIECSMVMUACCUARYGRID_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"


class CSttIecSmvMUAccuracyGrid : public CSttIecChsGridBase
{
public:
	CSttIecSmvMUAccuracyGrid(QWidget* pparent);
	virtual ~CSttIecSmvMUAccuracyGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowDataEx(CDvmData *pChData, int nRow);	
	void ShowValueString(CDvmData *pChData, int nRow, int nCol, CString strValue);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	void UpdateChName();
	void UpdataGridHeaders();
	virtual void UpdateDatas();
	virtual void resizeEvent(QResizeEvent *);

	CExBaseList *m_pCapDevice;

protected:
	void Update_StaticStringColor(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString,long nResult);
	void ShowAttrValueRatError(CDvmData *pData, int nRow);
	void ShowAttrValueAngError(CDvmData *pData, int nRow);
	void ShowAttrValueCompError(CDvmData *pData, int nRow);
	void ShowAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision = -1);
	long GetCurrItemColor(CDvmData *pData,double dValue,long nErrorType);

	BOOL m_bOutPutValueMode;//标识:输出值
	BOOL m_bOutPutPhaseMode;//标识:输出相位
	BOOL m_bChannelDelayMode;//标识:通道延迟
	BOOL m_bZeroDriftMode;//标识是否为零漂模式

	CString m_astrGridTitle[10];;

};
#endif

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

	BOOL m_bOutPutValueMode;//��ʶ:���ֵ
	BOOL m_bOutPutPhaseMode;//��ʶ:�����λ
	BOOL m_bChannelDelayMode;//��ʶ:ͨ���ӳ�
	BOOL m_bZeroDriftMode;//��ʶ�Ƿ�Ϊ��Ưģʽ

	CString m_astrGridTitle[10];;

};
#endif

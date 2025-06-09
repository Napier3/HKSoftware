#ifndef SttIecSmvGrid_MUAccuracy_H
#define SttIecSmvGrid_MUAccuracy_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

#define SmvGrid_MUAccuracy_MAX_ROW_NUM      8


//SMV   MUAccuracy
class CSttIecSmvGrid_MUAccuracy : public CSttIecChsGridBase
{
public:
	CSttIecSmvGrid_MUAccuracy(QWidget* pparent);
	virtual ~CSttIecSmvGrid_MUAccuracy();
public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	virtual void UpdateDatas();
	void ShowDataEx(CDvmData *pChData, int nRow);
	void ShowValueString(CDvmData *pChData, int nRow, int nCol, CString strValue);
	void UpdataGridHeaders();
	void UpdateChName();

	CExBaseList *m_pCapDevice;

protected:
	void Update_StaticStringColor(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString,long nResult);
	void ShowAttrValueRatError(CDvmData *pData, int nRow);
	void ShowAttrValueAngError(CDvmData *pData, int nRow);
	void ShowAttrValueCompError(CDvmData *pData, int nRow);
	CString GetVolChStdErrorValueDesc(long nAccurLevel);
	CString GetCurrChStdErrorValueDesc(long nAccurLevel);
	long GetCurrItemColor(CDvmData *pData,double dValue,long nErrorType);
	
	CDataType *m_pCurrLevelDataType;
	CDataType *m_pVolLevelDataType;
	BOOL m_bZeroDriftMode;//标识是否为零漂模式
	CString m_astrGridTitle[SmvGrid_MUAccuracy_MAX_ROW_NUM];;
};

#endif // SttIecSmvGrid_MUAccuracy_H

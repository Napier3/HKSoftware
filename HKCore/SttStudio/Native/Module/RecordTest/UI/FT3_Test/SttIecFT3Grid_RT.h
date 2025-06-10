#ifndef SttIecFT3Grid_RT_H
#define SttIecFT3Grid_RT_H

#include "../SttIecChsGridBase.h"
#include "../SttIecRcdFuncInterface.h"
#include "../../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

//GOOSE   ʵʱֵ
class CSttIecFT3Grid_RT : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecFT3Grid_RT(QWidget* pparent);
	virtual ~CSttIecFT3Grid_RT();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();
//	virtual BOOL NeedAddToSubPub(){return TRUE;}

	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual CExBaseList* GetCurrCapDevice();

	bool eventFilter(QObject *obj, QEvent *event);//20240325 suyang 将双击改单击
	BOOL m_bRunning;

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void ShowDataEx(CDvmData *pChData, int nRow);
	virtual void UpdateData(CExBaseObject *pData, int nRow);

	CIecCfgChsBase *m_pCfgChsRef;
	void UpdateData_ByDataType(CDvmData *pData, CIecCfg6044CommonCh *pIecCfgFT3Ch,int nRow);
	CString GetDataTypeValue(CString strDataType, CString *pstrValue);

	double GetChValue(CDvmData *pDvmData,CIecCfg6044CommonCh *pIecCfgFT3Ch);
	void ShowData_AnalogChValue(CDvmData *pChData, int nRow,CIecCfg6044CommonCh *pIecCfgFT3Ch,BOOL bIsDcCh);
};

#endif // SttIecFT3Grid_RT_H

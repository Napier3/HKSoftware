#pragma once
#include "../../RecordTest/UI/SttIecChsGridBase.h"
#include "../../RecordTest/UI/SttIecRcdFuncInterface.h"
#include <QPixmap>
class CSttBinRecord_RT : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttBinRecord_RT(QWidget* pparent);
	virtual ~CSttBinRecord_RT();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual void Release();

	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	bool eventFilter(QObject *obj, QEvent *event);//将双击改单击

	virtual CExBaseList* GetCurrCapDevice();
	BOOL m_bRunning;
	CString m_strPixPathOpen;
	CString m_strPixPathClose;

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);//2024-10-12zhouyangyong 新增用于解决有效值不刷新的问题
	void showEType(CExBaseObject *pData, int& nRow);
	void showChMap(CExBaseObject *pData, int& nRow);
	void showChValue(CExBaseObject *pData, int& nRow);
	void showChfValue(CExBaseObject *pData, int& nRow);
};


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
	bool eventFilter(QObject *obj, QEvent *event);//��˫���ĵ���

	virtual CExBaseList* GetCurrCapDevice();
	BOOL m_bRunning;
	CString m_strPixPathOpen;
	CString m_strPixPathClose;

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);//2024-10-12zhouyangyong �������ڽ����Чֵ��ˢ�µ�����
	void showEType(CExBaseObject *pData, int& nRow);
	void showChMap(CExBaseObject *pData, int& nRow);
	void showChValue(CExBaseObject *pData, int& nRow);
	void showChfValue(CExBaseObject *pData, int& nRow);
};


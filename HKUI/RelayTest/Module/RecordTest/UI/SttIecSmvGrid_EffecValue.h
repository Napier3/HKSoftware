#ifndef SttIecSmvGrid_EffecValue_H
#define SttIecSmvGrid_EffecValue_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"

//SMV   有效值 
class CSttIecSmvGrid_EffecValue : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
	Q_OBJECT
public:
	CSttIecSmvGrid_EffecValue(QWidget* pparent);
	virtual ~CSttIecSmvGrid_EffecValue();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Release();
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);

	//bool eventFilter(QObject *obj, QEvent *event);
// 	BOOL m_bRunning;

public:
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	virtual CExBaseList* GetCurrCapDevice();

public slots:
	void slot_doubleClicked(int nRow,int nCol);	
};

#endif // SttIecSmvGrid_EffecValue_H

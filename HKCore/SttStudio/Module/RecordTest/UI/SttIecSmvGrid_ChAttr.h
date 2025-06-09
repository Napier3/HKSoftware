#ifndef SttIecSmvGrid_ChAttr_H
#define SttIecSmvGrid_ChAttr_H

#include "SttIecChsGridBase.h"
#include "SttIecRcdFuncInterface.h"
#include "../../UI/Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

//SMV   有效值 
class CSttIecSmvGrid_ChAttr : public CSttIecChsGridBase, public CSttIecRcdFuncInterface
{
public:
	CSttIecSmvGrid_ChAttr(QWidget* pparent);
	virtual ~CSttIecSmvGrid_ChAttr();

	virtual void IecRcdFunc(CCapDeviceBase *pCapDevice);
	virtual void IecRcdFuncUpdate(CCapDeviceBase *pCapDevice);
	virtual BOOL NeedConfig(){return TRUE;}
	virtual void Config();//页面功能配置
	virtual void Release();

public:
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void UpdateData(CExBaseObject *pData, int nRow);
	void UpdateCoefDatas();

	void UpdateChAngTypeChanged(int& nRow);
	void UpdateChTypeChanged(int& nRow);
	void Show_ChAngType(CCapDeviceSmvCh *pSmvCh,int& nRow);

	static void EndEditCell_Value_Coef(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	//编辑处理函数
	static void EndEditCell_Smv92ChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_Smv92ChAngTypeChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual CExBaseList* GetCurrCapDevice();

protected:
	QExBaseListComBoxDelegBase *m_pChType_DelegBase;
	QExBaseListComBoxDelegBase *m_pChAngType_DelegBase;
	BOOL m_bRunning;

};

#endif // SttIecSmvGrid_ChAttr_H

#ifndef SCLCTRLSGRIDBASE_H
#define SCLCTRLSGRIDBASE_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"


class CSclCtrlsGridBase : public QExBaseListGridBase
{
	Q_OBJECT//zhouhj 20210715 要使用信号、槽必须要加此
public:
	CSclCtrlsGridBase(QWidget* pparent);
	virtual ~CSclCtrlsGridBase();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

	void UpdateSelectedState();
	//参数3标记是否更新控制块选择表格
	virtual void UpdatePubSubCfg(CSclCtrlBase *pSclCtrlBase,int nRow,BOOL UpdateCtrlSelectGrid = FALSE);//更新订阅发布配置
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

	void Attach_SelCtrlsRef(CExBaseList *pSelectedSclCtrlsRef)
	{
		m_pSelectedSclCtrlsRef = pSelectedSclCtrlsRef;
	}

	//2023/9/16 wjs 添加更新数据函数
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);

public:
	//编辑处理函数
	static void EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20211027 处理勾选改变

	//控制块被勾选选中后加入到该链表中
	CExBaseList *m_pSelectedSclCtrlsRef;

protected:
	QExBaseListComBoxDelegBase *m_pTypeSel_DelegBase;
	BOOL m_bRunning;

signals:
	void sig_UpdateSelectCtrlsGrid();

};

#endif // SCLCTRLSGRIDBASE_H

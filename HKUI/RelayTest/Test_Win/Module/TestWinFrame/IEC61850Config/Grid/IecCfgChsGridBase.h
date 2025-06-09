#ifndef IECCFGCHSGRIDBASE_H
#define IECCFGCHSGRIDBASE_H

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../CommonCtrl_QT/QIecWidgetDelegate.h"
class QIecCfgChsComBoxDelegBase : public QExBaseListComBoxDelegBase
{
public:
	//设置Data节点，代理会自动获取当前行和列，并设置值
	QIecCfgChsComBoxDelegBase(QObject *parent=NULL);
	virtual ~QIecCfgChsComBoxDelegBase();

	virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, 
		const QModelIndex &index ) const;

};

class CIecCfgChsGridBase : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CIecCfgChsGridBase(QWidget* pparent);
	virtual ~CIecCfgChsGridBase();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void UpdateChLength(CExBaseObject *pData, int& nRow, long nChLength, BOOL bInsertRow=TRUE);
	void UpdateChLengths(CExBaseList *pDatas, long nChLength, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);

	void UpdateSelectedState();
#ifdef _PSX_QT_LINUX_
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
#endif
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
	virtual void ShowCommonBinMap_StaticString(CExBaseObject *pData, int nRow){}//20240201 suyang FT3订阅 开入映射按钮设置后无法更新表格数据，转换成虚函数

public:
	//编辑处理函数

protected:
	QIecCfgChsComBoxDelegBase *m_pChType_DelegBase;
	QIecCfgChsComBoxDelegBase *m_pChMap_DelegBase;
	BOOL m_bRunning;

public slots:
	void slot_doubleClicked(int nRow,int nCol);
};

#endif // IECCFGCHSGRIDBASE_H

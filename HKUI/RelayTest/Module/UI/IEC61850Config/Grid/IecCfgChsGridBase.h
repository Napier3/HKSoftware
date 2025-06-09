#ifndef IECCFGCHSGRIDBASE_H
#define IECCFGCHSGRIDBASE_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"
//#include "../../Module/ScrollCtrl/ScrollComboBox.cpp"
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
	void UpdateChLengths(CExBaseList *pDatas, long nChLength, BOOL bResetScrollBars=TRUE);//2023-12-05 zhou yangyong 添加用于单独刷新字宽列
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
	void UpdateSelectedState();
	bool eventFilter(QObject *obj, QEvent *event);
	//virtual void mousePressEvent(QMouseEvent *);
    virtual void mouseReleaseEvent(QMouseEvent *);//add wangtao 20240508 用realease触发点击，目的是触屏落点在下拉框时能够滑动界面
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
    virtual void ShowCommonBinMap_StaticString(CExBaseObject *pData, int nRow)//20240308 suyang FT3订阅 开入映射按钮设置后无法更新表格数据，转换成虚函数
    {
#ifdef _PSX_IDE_QT_
        (void)pData;
        (void)nRow;
#endif

    }

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

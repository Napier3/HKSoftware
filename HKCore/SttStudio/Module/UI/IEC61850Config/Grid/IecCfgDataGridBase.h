#ifndef IECCFGDATAGRIDBASE_H
#define IECCFGDATAGRIDBASE_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDataBase.h"

class QFiberSelectedComBoxDelegBase : public QExBaseListComBoxDelegBase
{	
	Q_OBJECT
public:
	QFiberSelectedComBoxDelegBase(QObject *parent=NULL);
	~QFiberSelectedComBoxDelegBase();

	virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CIecCfgDataGridBase : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CIecCfgDataGridBase(QWidget* pparent);
	virtual ~CIecCfgDataGridBase();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol){}
	virtual CString GetAppPortDataType()	{	return g_strAppPortDataType_Fiber;	}
	void AttachRefChsGrid(QExBaseListGridBase *pRefChsGrid)		{	m_pRefChsGrid = pRefChsGrid;	}
	void UpdateSelectedState();
	virtual BOOL IsCfgData(CExBaseObject *pIecCfgDataBase){return FALSE;}
	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
public:
	//编辑处理函数
	static void EndEditCell_ChNum (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_SampleDelay (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_CheckChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20211029 处理勾选改变
	static void EndEditCell_ChLenthChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhou yangyong 处理采样位宽改变
	static void EndEditCell_TextChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//2023-12-29 suyang 处理修改完成后为空情况下恢复原来值
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	QExBaseListGridBase* GetRefChsGrid()
	{
		return m_pRefChsGrid;
	}

protected:
	QExBaseListGridBase *m_pRefChsGrid;

	QExBaseListCheckBoxDelegate *m_pCtrlBlockSelectDelegate;
	QIecNumberEditDelegate *m_pDesMacAddrDelegate;
	QIecNumberEditDelegate *m_pAppIDDelegate;
	QExBaseListComBoxDelegBase *m_pFiberSelected_DelegBase;
	QIecNumberEditDelegate *m_pVersionNODelegate;
	BOOL m_bRunning;

signals:
	void sig_UpdateCheckState(CIecCfgDataBase *pIecCfgDataBase,int nRow);
	void sig_FiberSelUpdate(CIecCfgDataBase *pIecCfgDataBase,int nRow);//FT3光口选择更新

public slots:
	virtual void slot_doubleClicked(int nRow,int nCol);
	void slot_UpdateCheckState(CIecCfgDataBase *pIecCfgDataBase,int nRow);
	virtual void slot_FiberSelUpdate(CIecCfgDataBase *pIecCfgDataBase,int nRow){};
};


#endif // IECCFGDATAGRIDBASE_H

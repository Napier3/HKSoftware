#ifndef IECCFGGINCHSGRID_H
#define IECCFGGINCHSGRID_H

#include "IecCfgChsGridBase.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGinCh.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgGinDatas.h"


#define IECCFGGINCHS_GRID_COLS		3

//////////////////////////////////////////////////////////////////////////
class QIecCfgGinChsComBoxDelegate : public QIecCfgChsComBoxDelegBase
{
public:
	//����Data�ڵ㣬������Զ���ȡ��ǰ�к��У�������ֵ
	QIecCfgGinChsComBoxDelegate(QObject *parent=NULL);
	~QIecCfgGinChsComBoxDelegate();

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};


//////////////////////////////////////////////////////////////////////////

class CIecCfgGinChsGrid : public CIecCfgChsGridBase
{
public:
	CIecCfgGinChsGrid(QWidget* pparent);
	virtual ~CIecCfgGinChsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfgGinCh *pIecCfgGinCh,int nRow);

public:
	//�༭������
	static void EndEditCell_GinChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
};

#endif // IECCFGGINCHSGRID_H

#pragma once
#include <QWidget>
#include "..\Module\QExBaseListGridBase\QExBaseListGridBase.h"
#include "..\Module\QExBaseListGridBase\QExBaseListComBoxDelegBase.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgDataGooseChBase.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgGinCh.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgGoutCh.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgGinDatas.h"
#include "IecCfgChsGridBase.h"

#define  CIECCFGCHSGRID_COL	3
#define  IECCFGGINCHSGRID   0
#define  IECCFGGOUTCHSGRID  1

class QIecCfgGinChsComBoxDelegate : public QIecCfgChsComBoxDelegBase
{
public:
	//����Data�ڵ㣬������Զ���ȡ��ǰ�к��У�������ֵ
	QIecCfgGinChsComBoxDelegate(QObject *parent=NULL);
	~QIecCfgGinChsComBoxDelegate();

	virtual void setEditorData(QWidget * ditor, const QModelIndex &index) const;
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
};

class CIecCfgChsGrid:public QExBaseListGridBase
{
public:
	CIecCfgChsGrid(long nType,QWidget* pparent = NULL);
	virtual ~CIecCfgChsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void InitData(CIecCfgChsBase *pIecCfgChs);
// 	void UpdateData_ByDataType(CIecCfgDataGooseChBase *pIecCfgCh,int nRow);
// 	void UpdateData_ByChMap(CIecCfgDataGooseChBase *pIecCfgCh,int nRow);//ͨ��ӳ��ı��

	void UpdateGinData_ByDataType(CIecCfgGinCh *pIecCfgGinCh,int nRow);//��ʾ��Goose������ӳ��
	void UpdateGoutData_ByDataType(CIecCfgGoutCh *pIecCfgGoutCh, int nRow);//��ʾ��Goose������ӳ��

public:
	static void EndEditCell_GoutChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_GinChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

	void UpdateChDatas( CExBaseList *pCurrSelData );
	CIecCfgChsBase *m_pIecCfgChs;
	virtual CDataType* FindDataType(const CString &strDataType);
protected:
	QIecCfgChsComBoxDelegBase *m_pChType_DelegBase;
	QIecCfgGinChsComBoxDelegate *m_pChMap_DelegBase;
	QIecCfgChsComBoxDelegBase *m_pChOutType_DelegBase;
	long m_nType;

	QExBaseListComBoxDelegBase *m_pValue_DelegBase;
};

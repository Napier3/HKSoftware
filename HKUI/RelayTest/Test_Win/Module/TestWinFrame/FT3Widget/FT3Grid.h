#ifndef FT3GRID_H
#define FT3GRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonCh.h"
#include "../../Define.h"
#define FT3CHS_GRID_COLS		6


//2024-6-1 wuxinyi 添加下拉框筛选
class QFT3GridComBoxDelegBase : public QExBaseListComBoxDelegBase
{	
	Q_OBJECT
public:
	QFT3GridComBoxDelegBase(QObject *parent=NULL);
	~QFT3GridComBoxDelegBase();
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;
};

class FT3Grid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	FT3Grid(QWidget* pParent);
	virtual ~FT3Grid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strChType);
	void UpdateData_ByDataType(CIecCfg6044CommonCh *pCommonCh,int nRow);	
	void UpdateData_ByChMap(CIecCfg6044CommonCh *pCommonCh,int nRow);
	void UpdateDatas_Setting();
	void SetRunState(long nRunState);

	virtual void Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc);


protected:
	QExBaseListComBoxDelegBase *m_pChType_DelegBase;
	QExBaseListComBoxDelegBase *m_pMap_DelegBase;
	QExBaseListComBoxDelegBase *m_pBitLen_DelegBase;
	QExBaseListComBoxDelegBase *m_pSetting_DelegBase;
	
public:
	static void EndEditCell_FT3ChSelChanged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_FT3Value(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

public slots:
	void Slot_Setting_Clicked(int nRow,int nCol);

signals:
	void sig_Ft3Value_Changed();	
};
#endif




















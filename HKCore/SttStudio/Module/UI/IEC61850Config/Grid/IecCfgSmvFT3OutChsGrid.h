#ifndef IECCFGSMVFT3OutCHSGRID_H
#define IECCFGSMVFT3OutCHSGRID_H

#include "IecCfgChsGridBase.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfg6044CommonCh.h"


#define IECCFGSMVFT3OutCHS_GRID_COLS		6

class QFT3OutChMapComBoxDelegBase : public QIecCfgChsComBoxDelegBase
{	
	Q_OBJECT
public:
	QFT3OutChMapComBoxDelegBase(QObject *parent=NULL);
	~QFT3OutChMapComBoxDelegBase();
	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	virtual void setEditorData(QWidget * editor, const QModelIndex &index) const;
};
/////////////////////////////////////////

class CIecCfgSmvFT3OutChsGrid : public CIecCfgChsGridBase
{
	Q_OBJECT

public:
	CIecCfgSmvFT3OutChsGrid(QWidget* pparent);
	virtual ~CIecCfgSmvFT3OutChsGrid();
protected:
	QExBaseListComBoxDelegBase *m_pBitLen_DelegBase;
	QIecNumberEditDelegate *m_pInitValue_Delegate;
public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void UpdateChLength(CExBaseObject *pData, int& nRow, long nChLength, BOOL bInsertRow=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateData_ByDataType(CIecCfg6044CommonCh *pIecCfgSmvFT3Ch,int nRow);
	void UpdateChInitValue(CIecCfg6044CommonCh *pIecCfgSmvFT3Ch,int nRow);
	virtual void GridDoubleClicked_ShowKeyBoard(int nRow,int nCol);
//	virtual void OnDataSelChanged(int nRow=-1, int nCol=-1);
	void  Show_DataType_Val(CExBaseObject *pData, const int& nRow, const int& nCol, CDataType *pDataType, CString *pstrValue, GRID_CELL_EDIT_FUNC pFunc);

	void SetInitValue(int nRow,int nCol);//20240120 suyang 增加点击初值窗体弹出初值设置界面设置初值
public:
	//编辑处理函数
	static void EndEditCell_SmvFT3ChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_SmvFT3ChMapSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

public slots:
	void slot_SetInitValueBtn_Clicked(int nRow,int nCol);

signals:
	void sig_UpdateInitValueBtnEnabled(bool bSetInitValue);

};

#endif // IECCFGSMV92CHSGRID_H

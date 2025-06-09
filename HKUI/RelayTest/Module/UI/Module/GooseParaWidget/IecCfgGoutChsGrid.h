#ifndef CIECCFGGOUTCHSGRID_H
#define CIECCFGGOUTCHSGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutCh.h"

#define IECCFGGOUTCHSGRID_GRID_COLS		5


class QIecCfgGoutChsCheckBoxDelegate : public QExBaseListCheckBoxDelegate
{
public:
	QIecCfgGoutChsCheckBoxDelegate(QObject *parent=NULL);
	~QIecCfgGoutChsCheckBoxDelegate();

private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
		const QStyleOptionViewItem & option, const QModelIndex & index);

	QPixmap m_oEmptyPixmap;
};

class CIecCfgGoutChsGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CIecCfgGoutChsGrid(QWidget* pparent);
	virtual ~CIecCfgGoutChsGrid();

	BOOL m_bIsUpdateParas;//判断当前是否在更新参数;避免在下发更新参数命令时,CtickCount命令调用DoEvents函数,导致重复发送更新参数命令  20220816 zhouhj

public:
	void SetRunState(long nRunState);//设置表格状态,分为3种:1、停止输出状态(可修改数据类型、通道映射值等);2、一般运行状态(可实时修改数据值);3、递变状态(表格完全不可编辑)
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void ShowCheck_BOOLEAN(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void ShowCheck_Dbpos(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);

	void EnableInverseCol(BOOL bEnable);

	bool eventFilter(QObject *obj, QEvent *event);
//	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
public:
	//编辑处理函数
	static void EndEditCell_GoutChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_GoutDefaultValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20210912 增加对不同数据类型的初始值的判断

	void UpdateData_AllValues(long nCheckState);//根据当前选择状态,更新全部值
protected:
	void UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_ByChMap(CIecCfgGoutCh *pGoutCh,int nRow);//通道映射改变后
	void UpdateData_Value(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_Inverse(QGV_ITEM *pCell,int nRow);
	BOOL IsCheckedState_ChValue(const CString &strChValue);

private:
	QExBaseListComBoxDelegBase *m_pDataType_DelegBase;
	QExBaseListComBoxDelegBase *m_pMap_DelegBase;
	QExBaseListComBoxDelegBase *m_pValue_DelegBase;
	QExBaseListCheckBoxDelegate *m_pExBaseListCheckBoxDelegate;

signals:
//	void sig_Iec61850Cfg_Changed();//发送61850配置更改信号
	void sig_GoutValue_Changed();//发送Goose发布值更改信号
	void sig_GoutMap_Changed();//增加用于开出数据类型改变或者开出映射改变

 protected slots:
 	void slot_GridCellClicked(int row, int column);
};


#endif // CHMAPSGRID_H

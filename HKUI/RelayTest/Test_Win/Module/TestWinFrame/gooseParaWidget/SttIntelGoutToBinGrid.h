#ifndef CSTTINTELGOUTTOBINGRID_H
#define CSTTINTELGOUTTOBINGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGoutCh.h"

#define STTINTELGOUTTOBINGRID_GRID_COLS		6

class QSttIntelGoutToBinCheckBoxDelegate : public QExBaseListCheckBoxDelegate
{
public:
	QSttIntelGoutToBinCheckBoxDelegate(QObject *parent=NULL);
	~QSttIntelGoutToBinCheckBoxDelegate();

	void InitStyleSheet();
private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;
	virtual bool editorEvent(QEvent * event, QAbstractItemModel * model,
		const QStyleOptionViewItem & option, const QModelIndex & index);

	QPixmap m_oEmptyPixmap;
	QPixmap m_oSelectedPixmap;
	QPixmap m_oUnselectedPixmap;
};
class CSttIntelGoutToBinGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttIntelGoutToBinGrid(QWidget* pparent);
	virtual ~CSttIntelGoutToBinGrid();

public:
	void SetRunState(long nRunState);//设置表格状态,分为3种:1、停止输出状态(可修改数据类型、通道映射值等);2、一般运行状态(可实时修改数据值);3、递变状态(表格完全不可编辑)
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	void UpdateDatas_Revert();
	virtual CDataType* FindDataType(const CString &strDataType);
	void GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex);
	void setGooseResultVlaues();
	void startInit();

	virtual void ShowCheck_BOOLEAN(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);
	virtual void ShowCheck_Dbpos(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString, GRID_CELL_EDIT_FUNC pFunc=NULL);

	void EnableInverseCol(BOOL bEnable);
public:
	//编辑处理函数
	static void EndEditCell_GoutChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_GoutDefaultValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);//zhouhj 20210912 增加对不同数据类型的初始值的判断

	BOOL IsCheckedState_ChValue(const CString &strChValue);

protected:
	void UpdateData_ByDataType(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateDatas_ByRevert(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_Value(CIecCfgGoutCh *pGoutCh,int nRow);
	void UpdateData_Inverse(QGV_ITEM *pCell,int nRow);
	void UpdateData_ByInverse(QGV_ITEM *pCell,int nRow);

private:
	QExBaseListComBoxDelegBase *m_pDataType_DelegBase;
	QExBaseListComBoxDelegBase *m_pValue_DelegBase;
	QSttIntelGoutToBinCheckBoxDelegate *m_pCheckBoxDelegateBase;

	int m_nRowIndex;
	CString m_strResultVlaues;
signals:
//	void sig_Iec61850Cfg_Changed();//发送61850配置更改信号
	void sig_GoutValue_Changed();//发送Goose发布值更改信号
	void sig_GoutRowIndex(int nRowIndex);

 protected slots:
 	void slot_GridCellClicked(int row, int column);
	
};


#endif // CSTTINTELGOUTTOBINGRID_H

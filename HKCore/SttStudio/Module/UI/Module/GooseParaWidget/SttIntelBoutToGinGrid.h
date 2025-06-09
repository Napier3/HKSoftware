#ifndef CSTTINTELBOUTTOGINGRID_H
#define CSTTINTELBOUTTOGINGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../../../61850/Module/CfgDataMngr/IecCfgGinCh.h"
#include "../../IEC61850Config/Grid/IecCfgGinChsGrid.h"

#define STTINTELBOUTTOGINGRID_GRID_COLS		6

class CSttIntelBoutToGinGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	CSttIntelBoutToGinGrid(QWidget* pparent);
	virtual ~CSttIntelBoutToGinGrid();

public:
	virtual void SetRunState(long nRunState);//设置表格状态,分为3种:1、停止输出状态(可修改数据类型、通道映射值等);2、一般运行状态(可实时修改数据值);3、递变状态(表格完全不可编辑)
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);
	void GridCellResultVlaues(float fResultTimeVlaue,char strCharacterIndex);
	void UpdateState(int nStateValue);//快速开出状态值
	void startInit();

	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *);

public:
	//编辑处理函数
	static void EndEditCell_GinChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_AppCh_GinDefaultValue(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

protected:
	void UpdateData_ByDataType(CIecCfgGinCh *pGoutCh,int nRow);
	void UpdateData_Inverse(QGV_ITEM *pCell,int nRow);

private:
	QExBaseListComBoxDelegBase *m_pDataType_DelegBase;
	QExBaseListComBoxDelegBase *m_pMap_DelegBase;
	QExBaseListComBoxDelegBase *m_pValue_DelegBase;

	int m_nCheckState;
	BOOL m_bBinFlag;
	BOOL m_bGooseFlag;
signals:
//	void sig_Iec61850Cfg_Changed();//发送61850配置更改信号
	void sig_GoutValue_Changed();//发送Goose发布值更改信号
	void sig_GinRowIndex(int nRowIndex,float fActTime);
};


#endif // CSTTINTELBOUTTOGINGRID_H

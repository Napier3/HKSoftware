#ifndef SttCmdWzdGrid_DsData_H
#define SttCmdWzdGrid_DsData_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"

#define DSDATA_GRID_TYPE_SRC  0
#define DSDATA_GRID_TYPE_DES  1

//该表格用于显示，write指令，关联的数据集的数据
class CSttCmdWzdGrid_DsData : public QExBaseListGridBase
{
public:
	CSttCmdWzdGrid_DsData(QWidget* pparent);
	virtual ~CSttCmdWzdGrid_DsData();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	UINT m_nGridType; //用于区分是SRC表，还是DES表。DES表值可编辑

};

#endif // SttCmdWzdGrid_Read_H

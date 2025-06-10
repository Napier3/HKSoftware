#ifndef CDeviceAttrsGrid_H
#define CDeviceAttrsGrid_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"

#define CDEVICE_ATTRS_GRID_COLS		2

class CDeviceAttrsGrid : public QExBaseListGridBase
{
public:
	CDeviceAttrsGrid(QWidget* pparent);
	virtual ~CDeviceAttrsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void SelectRow(int nRow);
};

#endif // CDeviceAttrsGrid_H

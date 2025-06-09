#ifndef CSttModuleAttrsGrid_H
#define CSttModuleAttrsGrid_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

#define CDEVICE_MODULE_ATTRS_GRID_COLS		2

class CSttModuleAttrsGrid : public QExBaseListGridBase
{
public:
	CSttModuleAttrsGrid(QWidget* pparent);
	virtual ~CSttModuleAttrsGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
protected:
};

#endif // CSttModuleAttrsGrid_H

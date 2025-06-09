#ifndef CSttModulesGrid_H
#define CSttModulesGrid_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

#define CDEVICE_MODULES_GRID_COLS		7

class CSttModulesGrid : public QExBaseListGridBase
{
public:
	CSttModulesGrid(QWidget* pparent);
	virtual ~CSttModulesGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void SelectRow(int nRow);

	void ShowAttrCol(CDataGroup *pDataGroup, const CString &strDataID, long nRow, long nCol);

protected:
	CString m_strModuleAttr[CDEVICE_MODULES_GRID_COLS];
};

#endif // CSttModulesGrid_H

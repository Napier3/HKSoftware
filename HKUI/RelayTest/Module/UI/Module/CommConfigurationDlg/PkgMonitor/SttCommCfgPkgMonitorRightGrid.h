#ifndef SttCCommCfgPkgMonitorRightGrid_H
#define SttCCommCfgPkgMonitorRightGrid_H

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../SttCmd/SttParas.h"
#define STTCCOMMCFGPKGMONITORRIGHTGRID_COLS		1

class SttCCommCfgPkgMonitorRightGrid : public QExBaseListGridBase
{
public:
	SttCCommCfgPkgMonitorRightGrid (QWidget* pparent);
	virtual ~SttCCommCfgPkgMonitorRightGrid ();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void SelectRow(int nRow);

	void ShowData(CSttParas *pData, int nRow);
};

#endif // SttCCommCfgPkgMonitorRightGrid_H 

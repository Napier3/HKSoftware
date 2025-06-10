#ifndef SttCCommCfgPointTblFileImportGrid_H
#define SttCCommCfgPointTblFileImportGrid_H

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define STTCMCFGPOINTTBLFILEIMPORTGRID_COLS		3  

class SttCCommCfgPointTblFileImportGrid  : public QExBaseListGridBase
{
public:
	SttCCommCfgPointTblFileImportGrid (QWidget* pparent);
	virtual ~SttCCommCfgPointTblFileImportGrid ();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void SelectRow(int nRow);
};

#endif // SttCCommCfgPointTblFileImportGrid 

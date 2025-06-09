#ifndef SttCCommCfgProtocolTemplateGrid_H
#define SttCCommCfgProtocolTemplateGrid_H

#include "../../QExBaseListGridBase/QExBaseListGridBase.h"

#define STTCCOMMCFGPROTOCOLTEMPLATE_COLS		3  

class SttCCommCfgProtocolTemplateGrid : public QExBaseListGridBase
{
public:
	SttCCommCfgProtocolTemplateGrid(QWidget* pparent);
	virtual ~SttCCommCfgProtocolTemplateGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void SelectRow(int nRow);
};

#endif // SttCCommCfgProtocolTemplateGrid

#ifndef QAINDATAMAPDATASETGRID_H
#define QAINDATAMAPDATASETGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

class QAinDataMapDataSetGrid: public QExBaseListGridBase
{
	Q_OBJECT

public:
	QAinDataMapDataSetGrid(QWidget* pParent);
	virtual ~QAinDataMapDataSetGrid();

	virtual void InitDataSetGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

};

#endif //QAINDATAMAPDATASETGRID_H
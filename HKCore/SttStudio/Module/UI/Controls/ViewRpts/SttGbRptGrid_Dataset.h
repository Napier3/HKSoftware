#ifndef SttGbRptGrid_Dataset_H
#define SttGbRptGrid_Dataset_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../Module/DataMngr/DvmDataset.h"

//////////////////////////////////////////////////////////////////////////
//
class CSttGbRptGrid_Dataset : public QExBaseListGridBase
{
public:
	CSttGbRptGrid_Dataset(QWidget* pparent);
	virtual ~CSttGbRptGrid_Dataset();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

#endif // SttGbRptGrid_Dataset_H

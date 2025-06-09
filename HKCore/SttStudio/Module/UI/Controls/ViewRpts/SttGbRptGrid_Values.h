#ifndef SttGbRptGrid_Values_H
#define SttGbRptGrid_Values_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"

//该表格用于显示，write指令，关联的数据集的数据
class CSttGbRptGrid_Values : public QExBaseListGridBase
{
public:
	CSttGbRptGrid_Values(QWidget* pparent);
	virtual ~CSttGbRptGrid_Values();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
};

#endif // SttGbRptGrid_Values_H

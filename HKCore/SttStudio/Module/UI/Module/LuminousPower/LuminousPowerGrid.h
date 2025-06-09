#ifndef QLUMINOUSPOWERGRID_H
#define QLUMINOUSPOWERGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

class QLuminousPowerGrid: public QExBaseListGridBase
{
	Q_OBJECT

public:
	QLuminousPowerGrid(QWidget* pParent);
	virtual ~QLuminousPowerGrid();

	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	CString m_strPicPath_Green;
	CString m_strPicPath_Black;

};

#endif //QLUMINOUSPOWERGRID_H
#ifndef  _QSttLicenseFileGrid_h__
#define  _QSttLicenseFileGrid_h__

#include "../../../../Module/UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"


class QSttLicenseFileGrid :public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttLicenseFileGrid(QWidget *parent = NULL);
	virtual ~QSttLicenseFileGrid();

    virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);


};


#endif

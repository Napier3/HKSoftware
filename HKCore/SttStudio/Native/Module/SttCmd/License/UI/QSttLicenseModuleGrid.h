#ifndef  _QSttLicenseModuleGrid_h__
#define  _QSttLicenseModuleGrid_h__

#include "../../../Module/UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"

class QSttLicenseModuleGrid :public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttLicenseModuleGrid(QWidget *parent = NULL);
	virtual ~QSttLicenseModuleGrid();

    virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);


};


#endif

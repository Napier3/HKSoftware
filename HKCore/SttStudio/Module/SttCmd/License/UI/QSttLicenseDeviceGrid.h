#ifndef  _QSttLicenseDeviceGrid_h__
#define  _QSttLicenseDeviceGrid_h__

#include "../../../Module/UI/Module/QExBaseListGridBase/QExBaseListGridBase.h"

class QSttLicenseDeviceGrid :public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSttLicenseDeviceGrid(QWidget *parent = NULL);
	virtual ~QSttLicenseDeviceGrid();

    virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow = TRUE);


};


#endif

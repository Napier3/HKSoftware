#ifndef QDATATYPECOMBOBOX_H
#define QDATATYPECOMBOBOX_H

#include "../../../../../Module/DataMngr/DataType.h"
#include "../../../../../Module/BaseClass/QT/ExBaseListComboBox.h"

class QDataTypeComboBox : public CExBaseListComboBox
{
	Q_OBJECT

public:
	QDataTypeComboBox(QWidget *parent);
	virtual ~QDataTypeComboBox();

public:
	void ShowDataType(CDataType *pDataType);

	CString GetSelectIndex();
	long GetSelectIndex2();

	BOOL SetSelByIndex(const CString &strIndex);
	BOOL SetSelByIndex(long nIndex);

	virtual CExBaseObject* GetSelectObject();
//	virtual long AddObj(CExBaseObject *pObj);	
};

#endif // QDATATYPECOMBOBOX_H

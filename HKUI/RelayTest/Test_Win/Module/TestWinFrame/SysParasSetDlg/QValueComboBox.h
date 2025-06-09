#ifndef QVALUECOMBOBOX_H
#define QVALUECOMBOBOX_H

#include <QComboBox>
#include "../../../../../Module/DataMngr/DataType.h"
#include <QLineEdit>
class QValueComboBox : public QComboBox
{
	Q_OBJECT

public:
	QValueComboBox(QWidget *parent);
	~QValueComboBox();

	void SetValue(CDataType *pList);
	void SetIndex(int *pIndex); //改变被绑定的变量
	void SetEditingFinished();

protected slots:
	void slot_currentIndexChanged(int);
	void slot_EditingFinished();

private:
	CDataType *m_pList;
	int *m_pIndex;
	
};

#endif 

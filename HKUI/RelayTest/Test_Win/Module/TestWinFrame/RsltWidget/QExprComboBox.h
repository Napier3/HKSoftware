#ifndef QExprCOMBOBOX_H
#define QExprCOMBOBOX_H

#include <QComboBox>
#include "../../../../../Module/DataMngr/DataGroup.h"
#include <QLineEdit>
class QExprComboBox : public QComboBox
{
	Q_OBJECT

public:
	QExprComboBox(CDataGroup *pList, char *pszExprRef, QWidget *parent);
	~QExprComboBox();

	void SetExprGroup(CDataGroup *pList);
	void SetExprRef(char *pszExprRef); //改变被绑定的变量
	void SetEditingFinished();
	
protected slots:
	void slot_currentIndexChanged(int);
	void slot_EditingFinished();

private:
	CDataGroup *m_pList;
	char *m_pszExprRef;
	
};

#endif // 

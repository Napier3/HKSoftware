#ifndef QSCLCTRLCHSGRIDBASE_H
#define QSCLCTRLCHSGRIDBASE_H

#include "../../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../../Module/CommonCtrl_QT/QIecWidgetDelegate.h"


class QSclCtrlChsGridBase : public QExBaseListGridBase
{
	Q_OBJECT
public:
	QSclCtrlChsGridBase(QWidget* pparent);
	virtual ~QSclCtrlChsGridBase();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual CDataType* FindDataType(const CString &strDataType);

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void OnDataSelChanged(int nRow, int nCol);

	void Attach_SelCtrlsRef(CExBaseList *pSelectedSclCtrlsRef)
	{
		m_pSelectedSclCtrlsRef = pSelectedSclCtrlsRef;
	}

	CExBaseList *m_pSelectedSclCtrlsRef;

public:
	//±à¼­´¦Àíº¯Êý

};

#endif // QSCLCTRLCHSGRIDBASE_H

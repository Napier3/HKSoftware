#ifndef QSTATEEDITDLG_H
#define QSTATEEDITDLG_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include <QDialog>
#include <QPushButton>
class QStateEditGrid : public QExBaseListGridBase
{
	Q_OBJECT
public:
	QStateEditGrid(QWidget* pParent);
	virtual ~QStateEditGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	void SelectedAll();  //	全选
	void UnSelectedAll(); //全不选
	void ReverseSelection();	//反选
	
	void UpdateSelectCol();
	
private:
	QExBaseListCheckBoxDelegate *m_pSelectSclIedDelegate;
	
		
};

class QStateEditDlg : public QDialog
{
	Q_OBJECT
public:
	CExBaseList* m_pStateList;
	QStateEditGrid* m_pEditGrid;
	

	QStateEditDlg(QWidget *parent = 0);
	virtual ~QStateEditDlg();
	
	
	
 
private slots:
	void slot_SelectedAll();
	void slot_UnSelectedAll();
	void slot_ReverseSelect();
};

#endif
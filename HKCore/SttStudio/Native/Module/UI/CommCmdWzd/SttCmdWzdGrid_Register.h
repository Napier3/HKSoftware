#ifndef CSttCmdWzdGrid_Register_H
#define CSttCmdWzdGrid_Register_H

#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class QSttCmdWzdGrid_Register_CheckBoxDelegate : public QExBaseListCheckBoxDelegate
{
public:
	QSttCmdWzdGrid_Register_CheckBoxDelegate(QObject *parent=NULL);
	~QSttCmdWzdGrid_Register_CheckBoxDelegate();

	CDataGroup *m_pCmdGrpRef;

private:
	virtual void paint(QPainter * painter, const QStyleOptionViewItem & option,
		const QModelIndex & index) const;

	QPixmap m_oEmptyPixmap;
};

class CSttCmdWzdGrid_Register : public QExBaseListGridBase
{
public:
	CSttCmdWzdGrid_Register(QWidget* pparent);
	virtual ~CSttCmdWzdGrid_Register();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

public:
	QExBaseListCheckBoxDelegate *m_pSelect;
	QSttCmdWzdGrid_Register_CheckBoxDelegate *m_pQuality;
	QSttCmdWzdGrid_Register_CheckBoxDelegate *m_pChange;
	QSttCmdWzdGrid_Register_CheckBoxDelegate *m_pPeriod;


	static void EndEditCell_Select(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
};

#endif // CSttCmdWzdGrid_Register_H

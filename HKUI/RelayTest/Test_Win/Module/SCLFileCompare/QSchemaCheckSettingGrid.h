#ifndef QSCHEMACHECKSETTINGGRID_H
#define QSCHEMACHECKSETTINGGRID_H
#include "../TestWinFrame/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../TestWinFrame/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include <QAction>
#include <QMenu>
#include <QMouseEvent>

#define SCHEMACHECKSETTINGGRID_COLS  5

class QSchemaCheckSettingGrid: public QExBaseListGridBase
{
	Q_OBJECT

public:
	QSchemaCheckSettingGrid(QWidget* pparent = NULL);
	virtual ~QSchemaCheckSettingGrid();
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
	QExBaseListComBoxDelegBase *m_pDelegVersion;
	QExBaseListComBoxDelegBase *m_pDelegXmlMethod;

	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual CDataType* FindDataType(const CString &strDataType);
	long m_nIndex;

protected:
	void mousePressEvent(QMouseEvent *event);

private:
	QMenu *m_TestMenu;
	QAction *m_SelectAll;
	QAction *m_UnSelectAll;
	QAction *m_Reverse;

public slots:
	void slot_SelectAll();
	void slot_UnSelectAll();
	void slot_Reverse();

signals:
	void sig_SelectAll();
	void sig_UnSelectAll();
	void sig_Reverse();
};

#endif
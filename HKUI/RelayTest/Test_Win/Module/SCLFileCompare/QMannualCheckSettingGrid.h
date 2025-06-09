#ifndef QMANNUALCHECKSETTINGGRID_H
#define QMANNUALCHECKSETTINGGRID_H
#include "../TestWinFrame/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../TestWinFrame/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"
#include <QAction>
#include <QMenu>
#include <QMouseEvent>

#define MANNUALCHECKSETTINGGRID_COLS  4

class QMannualCheckSettingGrid: public QExBaseListGridBase
{
	Q_OBJECT

public:
	QMannualCheckSettingGrid(QWidget* pparent = NULL);
	virtual ~QMannualCheckSettingGrid();
	QExBaseListCheckBoxDelegate *m_pCheckBoxDelegateBase;
	QExBaseListComBoxDelegBase *m_pDelegTokenType;


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
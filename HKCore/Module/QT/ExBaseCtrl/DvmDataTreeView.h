#ifndef QSMVPACKETANALYSISTREEVIEW_H
#define QSMVPACKETANALYSISTREEVIEW_H

#include <QTreeView>
#include"baseui/QSMVSnifferChildInterface.h"
#include "treemodel.h"

class QSMVPacketAnalysisTreeView : public QTreeView,public QSMVSnifferChildInterface
{
	Q_OBJECT
public:
	explicit QSMVPacketAnalysisTreeView(QWidget *parent = 0);

	virtual void Updatedata();
	void InitTreeMode();

private:
	TreeModel *m_model;

signals:

public slots:

protected:
	void showEvent(QShowEvent *);
	void hideEvent(QHideEvent *);
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent ( QMouseEvent * event );
	void mouseReleaseEvent ( QMouseEvent * event );
    void keyPressEvent(QKeyEvent *event);
private:
	void UpdateScroll();
	void InitPara();

	int GetTotalChildCount(QModelIndex parent);
	int GetTotalChildCount(QModelIndex parent, QModelIndex toChild, bool &bReach);
	int GetTotalRowCount();
	int GetCurrentRow();

	int  m_TotalRow;
	bool m_mousePressing;
	bool m_scribbling;
	int  m_scrDis;       //ª¨∂Øæ‡¿Î
	int  m_diff;
	int  m_rowHeight;
	QPoint m_lastPoint;
	QPoint m_currentPoint;

	bool m_bMove;
	QPoint m_ptPressed;
};

#endif // QSMVPACKETANALYSISTREEVIEW_H

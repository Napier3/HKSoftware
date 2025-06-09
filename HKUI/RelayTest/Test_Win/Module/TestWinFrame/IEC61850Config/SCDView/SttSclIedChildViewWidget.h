#ifndef STTSCLIEDCHILDVIEWWIDGET_H
#define STTSCLIEDCHILDVIEWWIDGET_H


#include <QScrollArea>
#include <QtGui/QApplication>
#include <QtGui>
#include <QMainWindow>
#include <QToolBar>
#include <QList>
#include <QToolButton>
#include <QTreeWidgetItem>
#include <QString>
#include <QTreeWidget>
#include <QStringList>
#include <QTextCodec>
#include <QDialog>
#include <QDesktopWidget>
#include <QTreeView>
#include <QComboBox>
#include <QLineEdit>

#include <QScrollBar>
#include <QPushButton>
#include <QBoxLayout>
#include <QObject>
#include <QMessageBox>
#include <QProgressDialog>
#include <QHBoxLayout>
#include <QDir>
#include <QList>
#include <QFileDialog>
#include <QSettings>
//#include <ActiveQt/QAxWidget>
//#include <ActiveQt/QAxObject>

#include <QMainWindow>

#include "SttSclCommonComponent.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#ifdef _PSX_QT_LINUX_
#include "../../../UI/Module/ScrollCtrl/ScrollCtrlInterface.h"
#endif
class QwtPlot;

#ifdef _PSX_QT_LINUX_
class QSttSclIedChildViewWidget : public QWidget, public CScrollCtrlInterface
#else
class QSttSclIedChildViewWidget : public QWidget
#endif
{
	Q_OBJECT

public:
	QSttSclIedChildViewWidget(QWidget *parent = 0,QWidget* root=NULL);
	~QSttSclIedChildViewWidget();

	void InitScrollData(QScrollBar* pScollBar);

	void InitData(CSclIed *pSclIed, double &_canvasHeight);

	//释放内存
	void Clear();

	//缩放
	void ZoomIn(float _factor);

	//导出图片
	void ExportPicture(double _width, double _height);

	QWidget* m_pRoot;

private:
	void InitUI();

	CRectMark *rectMark;
	QwtPlot *m_plot;

	QList<CSmallRect * > m_rectList;
	QList<CArrow * > m_arrowList;

	Rect_Struct m_data;

	const double m_coordWidth;      //X轴坐标
	double m_coordHeight;           //Y轴坐标，以左上角为原点
	const double m_minCoordHeight;  //最小高度
	double m_pointFWidth;           //字体大小

private slots:
	void OnMoved(const QPoint &pos);
	void OnAppand(const QPoint &pos);

signals:
	void IEDClickedSignal(int index);

protected:
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	//virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
};

void lastFillGseRecInexList();
void lastFillSmvRecInexList();


#endif // SCDVIEW_H

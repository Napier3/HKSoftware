#ifndef STTSCLIEDVIEWWIDGET_H  
#define STTSCLIEDVIEWWIDGET_H

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


#include "SttSclIedChildViewWidget.h"
#include "../../../../../../61850/Module/SCL/SclIecCfgDatas.h"
class QSttSclIedViewWidget : public QWidget
{
	Q_OBJECT
public:
	QSttSclIedViewWidget(QWidget *parent=NULL);
	~QSttSclIedViewWidget();

	//绘制IED
	void ShowIED(CSclIed *pSclIed);

	virtual void resizeEvent ( QResizeEvent * event );

	QWidget* m_pRoot;

protected:
	virtual void wheelEvent(QWheelEvent *event);
	

private:
	void zoomIn();
	void zoomOut();
	void scaleImage(double factor);
	void adjustScrollBar(QScrollBar *scrollBar, double factor);

	QSttSclIedChildViewWidget *m_scdView;
	QScrollArea *scrollArea;
	int m_zoomCount;
	QSize m_size;

	double m_canvasWidth;      //画布的坐标
	double m_canvasHeight;
	double m_minCanvasWidth;   //最小值
	double m_minCanvasHeight;

	double m_factor;

private slots:
	void OnIEDClicked(int index);
	void OnExportBtnClicked();
	void OnZoomInBtnClicked();
	void OnZoomOutBtnClicked();

signals:
	void IEDClickedSignal(int index);
};

#endif // VIEWERTAB_H

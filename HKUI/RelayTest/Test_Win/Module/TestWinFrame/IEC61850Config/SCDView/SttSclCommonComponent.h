#ifndef STTSCLCOMMONCOMPONENT_H
#define STTSCLCOMMONCOMPONENT_H

//0.SingleTon.h
//1.qwtheader.h
//2.liedialog.ha
//3.arrow.h
//4.small_rect.h
//5.Rect_Mark.h

/////===========================================================================================================
//0.SingleTon.h

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


//------------------------------------------------------------------------/////////////////////////////////////////
//1.qwtheader.h
#include <qwt_plot.h>
#include <qwt_plot_panner.h>
#include <qwt_plot_zoomer.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_picker.h>
#include <qwt_plot_scaleitem.h>
#include <qwt_scale_draw.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_item.h>
#include <qwt_legend_label.h>
#include <qwt_legend.h>
#include <qwt_plot_magnifier.h>
#include <qwt_picker.h>
#include <qwt_picker_machine.h>
////#include "SingleTon.h"
#include <QCursor>
#include "../../../../../Module/OSInterface/OSInterface.h"
#include "../../../../../61850/Module/SCL/SclIecCfgDatas.h"
#ifdef _PSX_QT_LINUX_
#include "../../../UI/Module/ScrollCtrl/ScrollCtrlInterface.h"
#endif

const int g_canvas_width = 1000;	    //画布X轴坐标
const int g_canvas_heigh = 520;
const int g_mainRect_width = 124;       //主矩形框的宽度
//--------------------------------------------------------------------------------


//订阅信息
typedef struct  _SUB_REC_INFO
{
	//内部虚端子信息
	QString ref;
	QString desc;

	//外部虚端子信息
	QString sub_IED_name;
	QString sub_ldInst;
	QString sub_ref;

	int index_IED;
	int index_GSE_SMV;
	int index_Rec;

	QString ExtMineOutAppid;
	int ExtCHIndex;
	int ExtCHOutIndex;

}_SUB_REC_INFO;

//发布信息
typedef struct _CONNECT_PUB_INFO
{
	int index_IED;
	int index_Rec;
}_CONNECT_PUB_INFO;

typedef struct  _PUB_REC_INFO
{
	QString ref;
	QString desc;
	QString bType;
	//一条信息发布给多个IED
	QList<_CONNECT_PUB_INFO> recPubList;
}_PUB_REC_INFO;

//GOOSE发送数据块
typedef struct _GSE_INFO
{
	QString apName;    //访问点名称
	QString apDesc;

	QString cbName;    //控制块名称
	QString ldInst;    //逻辑设备
	QString desc;      //控制块注释
	//Address
	QString MAC_Adress;
	QString VLAN_ID;
	QString VLAN_PRIORITY;
	CString APPID;

	int MinTime;
	int MaxTime;

	QString datSet;    //数据集名称
	QString confRev;    //版本号
	QString appID;    //goID

	int recNum;    //数据集通道个数
	QString DataSetDesc;    //数据集注释

	//一个控制块，多条记录
	QList<_PUB_REC_INFO> pubList;
}_GSE_INFO;

//SMV发送数据块
typedef struct _SMV_INFO
{
	QString apName;
	QString apDesc;

	QString cbName;
	QString ldInst;
	QString desc;
	//Address
	QString MAC_Adress;
	QString VLAN_ID;
	CString APPID;
	QString VLAN_PRIORITY;

	//SampledValueControl
	QString datSet;
	QString confRev;
	QString SmvID;
	//  QString multicast;    //暂时不用
	int smpRate;
	int nofASDU;

	//SmvOpts
	bool refreshTime;    //刷新时间
	bool sampleSynchronized;    //同步采样
	bool sampleRate;    //采样速率
	bool security;    //完全
	bool dataRef;    //数据引用

	int recNum;
	QString DataSetDesc;

	//一个控制块，多条记录
	QList<_PUB_REC_INFO> pubList;
}_SMV_INFO;

//IED的信息
typedef struct _IED_INFO
{
	QString name;
	QString type;
	QString manufacturer;
	QString configVersion;
	QString desc;

	QList<_GSE_INFO> GSEList;
	QList<_SMV_INFO> SMVList;

	QList<_SUB_REC_INFO> GOSubList;
	QList<_SUB_REC_INFO> SVSubList;
}_IED_INFO;

///////////////////////////////////////////////////////////////////////////////////////////////
//2.linedialog.h



struct Arrow_Struct
{
	int ied_index;           //当前IED索引
	QPointF startPointF;     //屏幕点
	QPointF endPointF;

	enum
	{
		POSITION_LEFT,
		POSITION_RIGHT
	}pos;                   //用于判断连线是在左边还是右边，从而决定起点和终点的赋值

	enum
	{
		ARROW_GSE,
		ARROW_SMV,
		ARROW_GOOSE_SUB,
		ARROW_SMV_SUB
	}type;                   //线类型，用于弹出窗口显示数据用

	union
	{
		struct
		{
			int block;
			int subIED;
		}pub;                //发布数据结构

		struct
		{
			int subIED;
			int subBlock;
		}sub;                //订阅数据结构
	}dat;                   //数据

	Arrow_Struct()
	{
		ied_index = -1;
		startPointF.setX(0);
		startPointF.setY(0);
		endPointF.setX(100);
		endPointF.setY(100);

		pos = POSITION_LEFT;
		type = ARROW_GSE;
		dat.pub.subIED = -1;
		dat.pub.block = -1;
	}
};

#ifdef _PSX_QT_LINUX_
class CLineDialog : public QDialog, public CScrollCtrlInterface
#else
class CLineDialog : public QDialog
#endif
{
	Q_OBJECT
public:
	CLineDialog(Arrow_Struct *_pData,QWidget *parent=NULL);
	~CLineDialog();
	void InitScrollData();
	void InitData();
private:
	void InitUI();
	Arrow_Struct *m_pData;
	QScrollArea *m_scrollArea;
	QSize m_size;
	QWidget *m_widget;
	int m_zoomCount;
	QwtPlot *m_plot;
	double factor;
	double m_pointWidth;

	const double m_coordWidth; //X轴坐标
	double m_coordHeight;      //Y轴坐标，以左上角为原点
	const double m_minCoordHeight; 
	double m_canvasWidth;      //画布的坐标
	double m_canvasHeight;

protected:
	virtual void wheelEvent(QWheelEvent *event);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	//virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);

private slots:
	void OnZoomInBtnClicked();
	void OnZoomOutBtnClicked();

};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//3.arrow.h


class CArrow : public QObject
{
	Q_OBJECT
public:
	CArrow(Arrow_Struct *_pData,QWidget* parent);
	~CArrow(void);
	
	void Draw(QPainter *painter);

	//判断当前点，是否在线上面
	bool Contains(const QPointF &_point);

	//判断当前点，是否在线上面
	bool LeftButtonClicked(const QPointF &_point);

	//先复原颜色
	void Recover();
	QWidget* m_pParentWgt;

signals:
	void arrow_SigBtnClicked();
protected slots:
	void slot_ArrowBtnClicked();

private:
	double m_width;
	double m_heigh;
	QColor m_color;
	double m_pointSizeF;

	QPointF m_startPointF;	//起点和终点，用于鼠标位置判断
	QPointF m_endPointF;

	const double m_errorDis;  //误差值，当前点与线的距离在此范围，认为是选中

	Arrow_Struct *m_pData;
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////
//4.small_rect.h


struct Block_Struct
{
	int block_index;         //控制块的索引，如果是接收则为-1
	enum
	{
		BLOCK_GSE,
		BLOCK_SMV,
		BLOCK_SUB            //控制块类型为接收
	}type; 
	QList<Arrow_Struct *> arrowList;   //该控制块关联的箭头的索引，
	//订阅IED-如果是发送类型的话，对应的连线就是一条；如果是接收的话，那么就有可能多个，即IED多个控制块发给这个IED
	//本IED-只能是发送类型，发送可能对应多条线，即一个控制块发给多个IED的情况

    Block_Struct()
	{
		block_index = -1;
		arrowList.clear();
	};
};

struct SmallRect_Struct
{
	int ied_index;    //发布方或者订阅方的IED索引
	enum
	{
		POSITION_LEFT,	//左边的小矩形框
		POSITION_RIGHT	//右边的小矩形框
	}pos;
	QList<Block_Struct > blockList;     //这个IED控制块的个数

	SmallRect_Struct()
	{
		ied_index = -1;
		pos = POSITION_LEFT;
		blockList.clear();
	}
};

class CSmallRect
{
public:
	CSmallRect(SmallRect_Struct *_pData, QwtPlot *_plot);
	~CSmallRect(void);

	//根据文字和控制块的个数，确定矩形的高度
	double Heigh();

	//绘制小矩形
	void Draw(QPainter *painter, double _yValue, 
		const QwtScaleMap &xMap, const QwtScaleMap &yMap);

	bool Contains(const QPoint &pos);

	int LeftButtonClicked(const QPoint &pos);

private:
	void DrawLeft(QPainter *painter, double _yValue, 
		const QwtScaleMap &xMap, const QwtScaleMap &yMap);

	void DrawRight(QPainter *painter, double _yValue, 
		const QwtScaleMap &xMap, const QwtScaleMap &yMap);

	QRectF m_blockRectF;
	QString m_text;

	QwtPlot *m_plot;

	int m_margin; //距离左边画布的距离
	int m_width;  //矩形框的宽度
	
	int m_textMargin; //文字的间隔
	int m_textWidth;

	int m_blockWidth; //控制块矩形框的宽度
	int m_blockHeight; //控制块矩形框的高度
	int m_blockMargin; //控制块矩形框之间的间隔

	double m_blockTotalHeight; //控制块占用的总长度

	double m_textHeight;

	SmallRect_Struct *m_pData;
};

////////////////////////////////////////////////////////////////////////////////////////////

//5.RectMark.h



struct Rect_Struct
{
	int ied_index;                               //IED的索引
	QList<Block_Struct > blockList;              //IED图形下部的控制块
	QList<SmallRect_Struct > smallBlockList;     //左右矩形
	QList<Arrow_Struct *> arrowList;             //所有的箭头

	Rect_Struct()
	{
		ied_index = -1;
		blockList.clear();
		smallBlockList.clear();
		arrowList.clear();
	}
};

class CRectMark : public QwtPlotItem
{
public:
	CRectMark(Rect_Struct *_pData,QWidget* parent);
	~CRectMark();

	QWidget* m_pParentWgt;

	//将小矩形以IED分类，并返回左边和右边小矩形框的最大高度
	double InitData();

	//释放空间
	void Clear();

	//矩形框与画布边界的间隔
	void SetMargin(int _margin);

	//设置矩形框的宽度
	void SetWidth(int _width);
	
	//矩形框内控制块名称之间的间隔
	void SetBlockMargin(int _margin);

	virtual int rtti() const;

	virtual void draw( QPainter *,
		const QwtScaleMap &, const QwtScaleMap &, const QRectF & ) const;

	//响应鼠标移动事件
	void Contains(const QPoint &pos);

	//响应鼠标点击事件
	int LeftButtonClicked(const QPoint &pos);

	//获取矩形框最小高度
	double MinHeight() const;

//signals:
//	void rectmark_SigBtnClicked();
//protected slots:
//	void slot_rectmarkBtnClicked();

private:
	QList<CSmallRect* > m_leftRectList;    //左边小矩形
	QList<CSmallRect* > m_rightRectList;   //右边小矩形
	double m_leftTotalHeight;              //左边小矩形的总高度
	double m_rightTotalHeight;

	QList<CArrow* > m_arrowList;           //所有的箭头

	QString m_text;
	int m_blockMargin;
	int m_blockHeight;
	int m_blockWidth;

	int m_margin;
	int m_width;

	int m_textMargin;
	int m_textWidth;

	int m_rectMargin; //小矩形框的间隔

	Rect_Struct *m_data;
};

void Global_SclIed_To_IedInfor(CSclIed *pSclIed,_IED_INFO* refiedInfo);
int Global_FindSclIedIndex(CString search);

extern QList<_IED_INFO*> g_oTotalIEDList;
extern QList<CString> g_oGloalIEDNameList;
extern QHash<QString,int>  g_oIED_Hash;
////////////////////////////////////////////////////////////////////////////////////////////

#endif
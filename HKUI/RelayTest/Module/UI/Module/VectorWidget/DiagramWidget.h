#ifndef DiagramWidget_H
#define DiagramWidget_H

#include <QWidget>
#include <QPen>
#include <QResizeEvent>
#include <QPen>
#include <QList>
#include <QStringList>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QMenu>
#include <QPushButton>

#include "../CommonMethod/commonMethod.h"
#include "../../Module/SttTestBase/SttComplexp.h"
#include "../ScrollCtrl/ScrollTableWidget.h"
#include "../../../../../Module/OSInterface/OSInterface.h"

#define U_MAX  300
#define I_MAX  20
#define STT_COMMON_VECTOR      0   //0-普通矢量图
#define STT_LowVolDvdt_VECTOR      1  //1-dvdt
#define STT_LowFreqDfdt_VECTOR      2 //2-dfdt

enum LineType{
	Line_U = 0,
	Line_I = 1
};

struct LineInfo
{
	QString m_UIType;		//向量名称
	float m_RealValue;		//真实值
	float m_XW;				//相位
	float m_Fre;			//频率
	bool m_bShowOrHide;		//显示或隐藏
	QPen m_Color;			//颜色
	float m_ChangeFactor;	
	LineType m_lineType;	//电压或者电流
	QString m_strTableName; //table中的名称

	LineInfo()
	{
		m_UIType = " ";
		m_RealValue = 0.0;
		m_XW = 0.0;
		m_Fre = 0.0;
		m_bShowOrHide = false;
		m_Color = QPen(Qt::white);
		m_lineType = Line_U;
		m_strTableName = " ";
	}

	LineInfo &operator = (const LineInfo &right)
	{
		m_UIType = right.m_UIType;
		m_RealValue = right.m_RealValue;
		m_XW = right.m_XW;
		m_Fre = right.m_Fre;
		m_bShowOrHide = right.m_bShowOrHide;
		m_Color = right.m_Color;
		m_ChangeFactor = right.m_ChangeFactor;
		m_lineType = right.m_lineType;
		m_strTableName = right.m_strTableName;
		return *this;
	}
};

class Diagram : public QWidget
{
	Q_OBJECT
public:
	explicit Diagram(QWidget *parent = 0);
	void initTable(int RowNum);
	void updateTable();
	void setSize(int m_Height,int m_Width);
	virtual void resizeEvent(QResizeEvent *);
	void updateDiagram();
	
	void creatPbn();
	void setHeader(QStringList headerList);
	void setColumnWidth(int nCol,int nWidth);
	void setUIMax(float fUMax,float fIMax);
	void setLineInfos(QList<LineInfo> infoList);
	void setTableInfos(QList<LineInfo> infoList);
	void setLegends(QStringList nameList,QList<QPen> colorList);
	void setLineValue(float *fAmp,float *fPhe);
	void drawSector(float startAngle,float endAngle);//逆时针方向
	void drawMTALine(float mtaAngle);//绘制最大灵敏角对应的线
	void drawSearchLine(float angle);//逆时针方向 0-360
	void drawSearchArc(float startAngle,float endAngle);//绘制搜多弧线边界
	void setIsDrawSectorFlag(bool flag);
	void setSectorAngle(float startangle,float endangle);
	void setSearchArcAngle(float startangle,float endangle);
	void setMTAAngle(float mtaangle);
	void setSearchAngle(float angle);
	void setStartSearch(bool b);
	void setPbnDisp(bool b);
	void setlabNumText(QString str);
	void InsertNewLineOfTable(QStringList str,bool bUse);//20211020 sf 复压闭锁 用其他不用

protected:
	void mousePressEvent(QMouseEvent *event);
	
public:
	int m_PicHeight;
	int m_PicWidth;
	static int m_l;
	static float m_a;
	QVector<LineInfo> m_LineVector;
	float GetDistance(float flStartx,float flStarty,float flEndx,float flEndy);

protected:
	void paintEvent(QPaintEvent *);
	void drawBackground(QPainter *painter);
	void drawVector(QPainter *painter);

signals:
	void sig_Pbn_NextClicked();
	void sig_Pbn_PreClicked();
	
private slots:
	void slot_UZoomOutClicked();
	void slot_IZoomOutClicked();
	void slot_UZoomInClicked();
	void slot_IZoomInClicked();
	void slot_Pbn_NextClicked();
	void slot_Pbn_PreClicked();

private:
	void updateTableRowHightSize(int height);
	void drawCircle(QPainter *painter);
	void drawGrid(QPainter *painter);
	void drawDesText(QPainter *painter);
	
	QPointF getLineTopPoint(float angle); 
	enum { Margin = 8 };
	QPixmap m_pixmap;
	float m_Radius;  //半径
	int m_ZJoffset;
	float m_MidX,m_MidY;
	QPointF m_CenterPos;

	int curZoom;
	QRect rubberBandRect;

	int m_nRowHeight;//wangtao 20240522 将行高定义为成员变量

public:
	QScrollTableWidget *m_TableData;
	QMenu *m_TestMenu;
	QAction *m_UZoomOutAction;
	QAction *m_IZoomOutAction;
	QAction *m_UZoomInAction;
	QAction *m_IZoomInAction;

	float m_fUMax;
	float m_fIMax;

	QStringList m_headerList;
	QList<LineInfo> m_infoList;
	QList<LineInfo> m_infoTable;
	QStringList m_LegendNameList;
	QList<QPen> m_LegendColorList;

	bool bIsDrawSector;
	float fstartAngle;
	float fendAngle;
	float fMTAangle;
	float fSrarchAngle;
	float fstartAngle_arc;
	float fendAngle_arc;
	bool bStartSearch;

	QPushButton *m_pbnNext;
	QPushButton *m_pbnPre;
	QLabel *m_labNum;
	QLabel *m_btnInstruction;

	bool m_bhasRadio;
	int m_UnitDispMode;

	int m_nRowNum;

	QStringList m_strDataEx;//复压闭锁额外显示 sf 20211019
	bool m_bUse;

	int m_VectorType; //2023.7.18 zhangyq 矢量图类别-是否添加滑差行
	double m_dCurrSearchValue;  //当前滑差值
};

extern CFont *g_pSttGlobalFont;  

#endif 

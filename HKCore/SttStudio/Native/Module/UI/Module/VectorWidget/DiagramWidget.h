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

#ifdef _PSX_QT_LINUX_
#include <pthread.h>
#else
#include <QMutex>
#endif

#include "../CommonMethod/commonMethod.h"
#include "../Module/SttTestBase/SttComplexp.h"
#include "../ScrollCtrl/ScrollTableWidget.h"

#define U_MAX  300
#define I_MAX  20
#define STT_COMMON_VECTOR      0   //0-��ͨʸ��ͼ
#define STT_LowVolDvdt_VECTOR      1  //1-dvdt
#define STT_LowFreqDfdt_VECTOR      2 //2-dfdt

enum LineType{
	Line_U = 0,
	Line_I = 1
};

struct LineInfo
{
	QString m_UIType;		//��������
	float m_RealValue;		//��ʵֵ
	float m_XW;				//��λ
	float m_Fre;			//Ƶ��
	bool m_bShowOrHide;		//��ʾ������
	QPen m_Color;			//��ɫ
	float m_ChangeFactor;	
	LineType m_lineType;	//��ѹ���ߵ���
	QString m_strTableName; //table�е�����

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
    virtual ~Diagram();
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
	void drawSector(float startAngle,float endAngle);//��ʱ�뷽��
	void drawMTALine(float mtaAngle);//������������Ƕ�Ӧ����
	void drawSearchLine(float angle);//��ʱ�뷽�� 0-360
	void drawSearchArc(float startAngle,float endAngle);//�����Ѷ໡�߽߱�
	void setIsDrawSectorFlag(bool flag);
	void setSectorAngle(float startangle,float endangle);
	void setSearchArcAngle(float startangle,float endangle);
	void setMTAAngle(float mtaangle);
	void setSearchAngle(float angle);
	void setStartSearch(bool b);
	void setPbnDisp(bool b);
	void setlabNumText(QString str);
	void InsertNewLineOfTable(QStringList str,bool bUse);//20211020 sf ��ѹ���� ����������
	void setUnitOfTable(QStringList str);//20240918 suyang ����һ��/����ֵ��λת����ʾ

protected:
	void mousePressEvent(QMouseEvent *event);
	
public:
	int m_PicHeight;
	int m_PicWidth;
	static int m_l;
	static float m_a;
//#ifdef USE_pthread_mutex_lock//zhouhj 2025.1.10 ��Linux�²��ô˷�ʽ,��������
//    pthread_mutex_t m_oMutex_Diagram;
//#else
//	QMutex m_oMutex_Diagram;//zhouhj 2025.1.10 ��ȫ�ֱ�����Ϊ��Ա����
//#endif
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
	float m_Radius;  //�뾶
	int m_ZJoffset;
	float m_MidX,m_MidY;
	QPointF m_CenterPos;

	int curZoom;
	QRect rubberBandRect;

	int m_nRowHeight;//wangtao 20240522 ���и߶���Ϊ��Ա����

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
	int m_nParaSetSecondValue;

	int m_nRowNum;

	QStringList m_strDataEx;//��ѹ����������ʾ sf 20211019
	bool m_bUse;

	int m_VectorType; //2023.7.18 zhangyq ʸ��ͼ���-�Ƿ���ӻ�����
	float fCurrSearchValue;  //��ǰ����ֵ
};

extern QFont *g_pSttGlobalFont;  

#endif 

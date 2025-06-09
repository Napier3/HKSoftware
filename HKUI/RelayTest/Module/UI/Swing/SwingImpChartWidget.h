#ifndef QSWINGIMPCHARTWIDGET
#define QSWINGIMPCHARTWIDGET

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include "../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"
#include "SwingImpChartDrawView.h"
#include <QWheelEvent>

#define STT_Charact_ToolBtn_Width                  40//右侧放大、缩小、上移、下移等按钮的宽度  20230206 zhouhj

class QSwingImpChartWidget : public QWidget
{
    Q_OBJECT

public:
	//lijunqing 2021-10-28  lijunqing  
	//bUseOptrButtons=是否使用图形操作按钮
	//bUseMouseMoveChar=是否使用鼠标移动图形，对于反时限等，是不需要移动图形的
    explicit QSwingImpChartWidget(QWidget *parent = 0, bool bUseOptrButtons=FALSE, BOOL bUseMouseMoveChar=FALSE);
    ~QSwingImpChartWidget();
	void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);
	void EnableSetting(BOOL bUseMouseMoveChar);
	void SetImpDatas();	//配置阻抗图数据
	void SetTestPoint(double dX, double dY);	//设置测试点

private:
	BOOL UpdateDrawCharacters();

	BOOL m_bUseMouseMoveChar;
	QList<QPushButton*> m_listDrawOptrBtn;//动态创建按钮的列表
	QPushButton* AddDrawOptrBtn(const CString &strID, long nIndex);
	void UpdateDrawOptrBtns();
	void AddDrawOptrBtns();
	void ResizeUI(int nWidth,int nHeight);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);

    virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

    virtual void wheelEvent(QWheelEvent *event);

public:
	CSwingImpChartDrawView *m_pCharacterDrawView;
	CCharacteristics *m_pCharacteristics;
	CString m_strXAxis, m_strYAxis , m_strTitle;	//兼容反时限标题 20211013 sf

private:
	void initPlot();
	bool m_bUseOptrButtons;
	bool m_bUseAddButtons;
	BOOL m_bViewTestLines;

	QMenu *m_TestMenu; 
	QAction *m_TestAddAction;//20211028 sf 右键点击添加试验
	QAction *m_ZoomInAction;
	QAction *m_ZoomOutAction;
	QAction *m_ResetAction;
	float m_fx;	//记录右键点击的坐标
	float m_fy;
	BOOL m_bHasResize;

signals:
	void sig_PlotDoubleClicked(float fx,float fy);
	void sig_UpdatePointLocation(float fx,float fy);
	void sig_AddPointLocation(float fx,float fy);
	void sig_LeftButtonDown();

public slots:
	void slot_UpdateDrawCharacters(CExBaseObject *pCharacteristic);	//20210915
	void slot_ZKDel(int);
	void slotDrawOptr_ZoomIn();	//2021-10-26  lijunqing
	void slotDrawOptr_ZoomOut();	
	void slotDrawOptr_Reset();	
	void slotDrawOptr_MouseZoom();	
	void slotDrawOptr_MoveUp();	
	void slotDrawOptr_MoveDown();	
	void slotDrawOptr_MoveLeft();	
	void slotDrawOptr_MoveRight();	

	void slot_ActionTestAddClicked(); //20211028 sf
};

#endif // QSWINGIMPCHARTWIDGET

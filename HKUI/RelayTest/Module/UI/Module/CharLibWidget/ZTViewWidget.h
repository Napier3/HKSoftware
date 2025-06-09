#pragma once

#include <QMouseEvent>
#include "../../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"
#include "./QImpCharactWidget.h"
#include "ZTCharDrawView.h"
#include "../../../XLangResource_Native.h"
#include "../../../../../Module/Axis/DescartesAxis.h"

#include "./InternationalZTInterface.h"

class QZTViewWidget: public QWidget,public CInternationalZTInterface
{

	 Q_OBJECT
public:
	explicit QZTViewWidget(QWidget *parent = 0);
	~QZTViewWidget();

	CZTCharDrawView *m_pZTDrawView;

private:
	//更新界面
	BOOL UpdateDrawCharacters();
	void ResizeUI(int nWidth,int nHeight);
    void initPlot();
    QPushButton* AddDrawOptrBtn(const CString &strImg, long nIndex);
    void UpdateDrawOptrBtns();
    void AddDrawOptrBtns();

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);

	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

	virtual void UpdateZTViewDraw(int nNum, CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[]);
public:
	//是否开始测试
	void setbStart(bool b){m_bStart = b;}
	//右击菜单是否新增添加测试点
	void IsHaveAddAct();
	//设置是否为阻抗 默认为非阻抗
	virtual void SetImpTestLines(BOOL b=FALSE);
    //传入ZT视图线段对应参数
	virtual void UpdateZTViewDraw(CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[]);
	//设置页面显示角度与故障类型
	virtual void SetAngleAndFaultype(const CString &strAngle, const CString &strFaultype);

	virtual void AddOneTestPoint(const CString &strIDPath,const CString &strFaultType, double dX, double dY);//添加测试点
	virtual void DeleteTestPoint(const CString &strIDPath);//删除测试点
	virtual void UpdateTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY, bool bSelPonit = false);//更新测试点状态

private:
	bool m_bStart;
	bool m_bUseAddButtons;
	BOOL m_ImpSearch;//横线显示误差范围(TRUE)或竖线显示误差范围(FALSE)

	QMenu *m_TestMenu; 
	QAction *m_TestAddAction;//20211028 sf 右键点击添加试验
	QAction *m_ZoomInAction;
	QAction *m_ZoomOutAction;
	QAction *m_ResetAction;
	float m_fx;	//记录右键点击的坐标
	float m_fy;

	double m_dplus;
	double m_dminus;

//	double m_dMax_XAxis;
//	double m_dMax_YAxis;
//	double m_dMin_XAxis;
//	double m_dMin_YAxis;
	double m_dYMax;

    QList<QPushButton*> m_listDrawOptrBtn;//动态创建按钮的列表

signals:
	void sig_AddPointLocation(float fx,float fy);
	void sig_LeftButtonDown();

public slots:
	void slotDrawOptr_ZoomIn();	//2021-10-26  lijunqing
	void slotDrawOptr_ZoomOut();	
	void slotDrawOptr_Reset();	
	void slot_ActionTestAddClicked();

	void slotDrawOptr_MoveUp();
	void slotDrawOptr_MoveDown();
	void slotDrawOptr_MoveLeft();
	void slotDrawOptr_MoveRight();
};

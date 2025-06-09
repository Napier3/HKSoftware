#ifndef QCHARACTWIDGETFORTEST_H
#define QCHARACTWIDGETFORTEST_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include "../../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"

#include "InternationalCharDrawView.h"
#include "InternationalCharactInterface.h"
#include "CharCircleWidget_Syn.h"

//extern class QSttTestCntrFrameBase;
class QCharactWidgetForTest : public QWidget, public CInternationalCharactInterface
{
    Q_OBJECT

public:
    explicit QCharactWidgetForTest(QWidget *parent = 0,  BOOL bUseMouseMoveChar=FALSE,BOOL bUseOptrButtons = FALSE);
    virtual ~QCharactWidgetForTest();

	double m_dMax_XAxis;
	double m_dMax_YAxis;
	double m_dMin_XAxis;
	double m_dMin_YAxis;

public:
    void InitCharacteristic(const CString &strMacroID, BOOL bClearTestData); //20240822 wanmj 添加参数，判断是否清空特性图测试点/线
	BOOL IsInternationalMode(const CString &strMacroID); //20240806 zhangyq 判断是否为国际版本

	void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);
	void UpdateCurrTestPoint(const CString &strCharaID,const CString &strIndex,
		double dX,double dY);//更新测试点,参数1:曲线相别LN/LL/ALL 参数2:曲线ID对应I/II/III段
	void AddTestResultPoint(CExBaseList* pValue);//添加测试结果点
	void ClearSearchPoints();
	void ClearSearchPoint(long nPtIndex);
	void ClearSearchPointsFrom(long nPtIndex);
	BOOL IsViewTestLines();
    void SetUseOptrButtons(BOOL bUseOptrButtons);

    CCharacteristics *m_pCharacteristics;
    CInternationalCharDrawView *m_pCharacterDrawView;
	QCharCircleWidget_Syn *m_pCircleWidget;//20240731 gongyp 自动准同期(国际版)的圆形图案绘制

	CString m_strXAxis, m_strYAxis , m_strTitle;	//兼容反时限标题 20211013 sf

	// 删除测试点 / 线
	virtual void DeleteTestData(const CString &strIDPath);
	//添加距离保护单个测试项对应测试点,参数1传递当前测试项路径,参数2、3对应电阻值、电抗值、参数4对应故障类型，参数5对应区段
	virtual void AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState = -1);

	virtual void UpdateTestCharParas_Syn(double dX, double dY);
    //20240821 wanmj 添加测试项的测试线到特性曲线图
    virtual void AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState = -1);

	//更新指定特性曲线,对于测试功能对应单个特性曲线的情况,如差动比率制动\谐波制动 ////add wangtao 20240925新增参数区分特性曲线单独绘制测试线/点还是全部
	virtual void UpdateCharacteristic(const CString &strCharID, int nTestObjDrawMode = CHAR_TEST_OBJECT_DRAW_ALL);

	//add wangtao 20240918 添加差动测试线/点到特性曲线图, 刷新单个特性曲线
	virtual void AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState = -1);
	//add wangtao 20240924 添加差动测试点到特性曲线图, 刷新单个特性曲线
	virtual void AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);

	virtual void UpdateCharacterisByFaultType(int nFaultType);//20241012 luozibing 未添加测试点时更新界面显示曲线故障类型
protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);
	virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

	CString GetAxisType(const CString &strMacroID); //20240806 zhangyq 获取各个模块的坐标类型
	BOOL IsLockXY(const CString &strMacroID);
	void UpdateCircleWidget_Syn(const CString &strMacroID);
	void UpdateAxisType(const CString& strAxis, BOOL bLockXY);

	QMenu *m_TestMenu; 
	QAction *m_TestAddAction;//20240717 luozibing 右键点击添加试验
	QAction *m_ZoomInAction;
	QAction *m_ZoomOutAction;
	QAction *m_ResetAction;
	float m_fx;	//记录右键点击的坐标
	float m_fy;

private:
	void initPlot();
	void initInternationalPlot();
	void InitTestMenu();
	BOOL UpdateDrawCharacters();
	void UpdateCharDesc(const CString &strMacroID, const CString &strCharID);
	BOOL m_bUseMouseMoveChar;
	 CCharacteristic *m_pCurrCharacteristic;
	 CString m_strCurrMacroID;
	 BOOL m_bCharHasChanged;//标记当前坐标轴已改变,需要刷新特性曲线
    bool m_bUseOptrButtons;
	BOOL m_bCharHasSynChanged;//标记自动准同期当前坐标轴已改变,需要刷新特性曲线
    BOOL m_bAddTestLineFromChar; //20240918 wanmj 是否在特性图鼠标绘制测试线
    BOOL m_bKeepAxisZoom;   //20241011 wanmj 刷新特性曲线图保持原有缩放
//	CString m_strCurrShowCharaID;//add wangtao 20240923记录存在多个曲线的模块当前功能ID,如差动模块每次只需要显示其中一条曲线,如果该ID为空则显示全部曲线
    QList<QPushButton*> m_listDrawOptrBtn;//动态创建按钮的列表
    QPushButton* AddDrawOptrBtn(const CString &strID, long nIndex);
    void UpdateDrawOptrBtns();
    void AddDrawOptrBtns();
    void ResizeUI(int nWidth,int nHeight);
signals:
	 void sig_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY);

	 void sizeChanged();  

public slots:
	void slot_UpdateCurrTestPoint(QString strCharaID,QString strIndex,double dX,double dY);
    virtual void slot_UpdateDrawCharacters();	//20210915

	void slotDrawOptr_ZoomIn();
	void slotDrawOptr_ZoomOut();	
	void slotDrawOptr_Reset();	
	void slot_ActionTestAddClicked();
    void slotDrawOptr_MoveUp();
    void slotDrawOptr_MoveDown();
    void slotDrawOptr_MoveLeft();
    void slotDrawOptr_MoveRight();
	void updateButtonPosition();
	void slotDrawOptr_SynReset();
};

#endif // QCHARACTWIDGETFORTEST_H

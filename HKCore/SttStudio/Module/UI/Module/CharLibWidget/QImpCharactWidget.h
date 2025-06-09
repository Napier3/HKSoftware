#ifndef DLGCHARDRAW_H
#define DLGCHARDRAW_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include "../../../../../AutoTest/Module/Characteristic/CharacteristicLib.h"
#include "PsuCharDrawView.h"

#define STT_Charact_ToolBtn_Width                  45//�Ҳ�Ŵ���С�����ơ����ƵȰ�ť�Ŀ��  20230206 zhouhj

class QImpCharactWidget : public QWidget
{
    Q_OBJECT

public:
	//lijunqing 2021-10-28  lijunqing  
	//bUseOptrButtons=�Ƿ�ʹ��ͼ�β�����ť
	//bUseMouseMoveChar=�Ƿ�ʹ������ƶ�ͼ�Σ����ڷ�ʱ�޵ȣ��ǲ���Ҫ�ƶ�ͼ�ε�
    explicit QImpCharactWidget(QWidget *parent = 0, bool bUseOptrButtons=FALSE, BOOL bUseMouseMoveChar=FALSE);
    ~QImpCharactWidget();
	CCharacteristic *m_pCharacteristic;
    CCharacteristics *m_pCharacteristics;
    CPsuCharDrawView *m_pCharacterDrawView;

	CString m_strXAxis, m_strYAxis , m_strTitle;	//���ݷ�ʱ�ޱ��� 20211013 sf

	void UI_SetActiveElement(CXDrawElement *pElement);

private:
	BOOL UpdateDrawCharacters();
    //CDC *m_pDC;

	BOOL m_bUseMouseMoveChar;
	QList<QPushButton*> m_listDrawOptrBtn;//��̬������ť���б�
	QPushButton* AddDrawOptrBtn(const CString &strID, long nIndex);
	void UpdateDrawOptrBtns();
	void AddDrawOptrBtns();

	void ResizeUI(int nWidth,int nHeight);

protected:
//	virtual bool eventFilter( QObject *, QEvent * );
	virtual void mouseDoubleClickEvent(QMouseEvent *);
	virtual void mouseMoveEvent(QMouseEvent *);
	virtual void mousePressEvent(QMouseEvent *);
	virtual void mouseReleaseEvent(QMouseEvent *);
	virtual void wheelEvent(QWheelEvent *);

    virtual void paintEvent(QPaintEvent *event);
	virtual void resizeEvent(QResizeEvent *);

public:
	void setbStart(bool b){m_bStart = b;}
//	void clearResult(TestInfo info);//�����ǰ���
	void ClearSearchPoints();
	void clearPos();

// 	void addOneTest(TestInfo &info);
// 	void updatePlot(TestInfo info);
// 	void updataPlotColor(TestInfo info);

	QString exportPlot(QString name);
	void SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle);
	void IsHaveAddAct();
	void EnableSetting(BOOL bUseMouseMoveChar);
	void CalPointVertHorzLine(long nIndex = 0, CString strType = CHAR_TESTLINE_MODE_ID_VERT);
	void UpdateVertLine(double dXValue);
	void UpdateHorzLine(double dYValue);
	CXDrawLine* GetLeftButtonLine();
	void SetViewTestLines(BOOL b=TRUE)	{	m_bViewTestLines = b;	}

private:
	CXDrawPoint* CreateNewDrawPoint(const double &dR,const double &dX);
	void initPlot();

//	QMap<int,sZKCircle> m_mapMyCircle;

// 	QList<ZKPos_TestPoint> m_PlotPosList;
//	TestInfo m_CurTestInfo;
	float m_fk;
	bool m_bStart;
	bool m_bUseOptrButtons;
	bool m_bUseAddButtons;
	BOOL m_bViewTestLines;

	QMenu *m_TestMenu; 
	QAction *m_TestAddAction;//20211028 sf �Ҽ�����������
	QAction *m_ZoomInAction;
	QAction *m_ZoomOutAction;
	QAction *m_ResetAction;
	float m_fx;	//��¼�Ҽ����������
	float m_fy;
	BOOL m_bHasResize;

signals:
	void sig_PlotDoubleClicked(float fx,float fy);
	void sig_UpdatePointLocation(float fx,float fy);
	void sig_AddPointLocation(float fx,float fy);
	void sig_LeftButtonDown();

public slots:
// 	void slot_AddOneTest(TestInfo &info);
// 	void slot_DelOneTest(TestInfo &);
// 	void slot_DelAllTest(TestInfo &);

//	void slot_ZKFinshed(RoundPara para);
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

#endif // DLGCHARDRAW_H

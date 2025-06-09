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
	//���½���
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
	//�Ƿ�ʼ����
	void setbStart(bool b){m_bStart = b;}
	//�һ��˵��Ƿ�������Ӳ��Ե�
	void IsHaveAddAct();
	//�����Ƿ�Ϊ�迹 Ĭ��Ϊ���迹
	virtual void SetImpTestLines(BOOL b=FALSE);
    //����ZT��ͼ�߶ζ�Ӧ����
	virtual void UpdateZTViewDraw(CString strName[], double dZSeting[], double dTSeting[], double dPlus[], double dMinus[]);
	//����ҳ����ʾ�Ƕ����������
	virtual void SetAngleAndFaultype(const CString &strAngle, const CString &strFaultype);

	virtual void AddOneTestPoint(const CString &strIDPath,const CString &strFaultType, double dX, double dY);//��Ӳ��Ե�
	virtual void DeleteTestPoint(const CString &strIDPath);//ɾ�����Ե�
	virtual void UpdateTestPoint(const CString &strIDPath, const CString &strFaultType, double dX, double dY, bool bSelPonit = false);//���²��Ե�״̬

private:
	bool m_bStart;
	bool m_bUseAddButtons;
	BOOL m_ImpSearch;//������ʾ��Χ(TRUE)��������ʾ��Χ(FALSE)

	QMenu *m_TestMenu; 
	QAction *m_TestAddAction;//20211028 sf �Ҽ�����������
	QAction *m_ZoomInAction;
	QAction *m_ZoomOutAction;
	QAction *m_ResetAction;
	float m_fx;	//��¼�Ҽ����������
	float m_fy;

	double m_dplus;
	double m_dminus;

//	double m_dMax_XAxis;
//	double m_dMax_YAxis;
//	double m_dMin_XAxis;
//	double m_dMin_YAxis;
	double m_dYMax;

    QList<QPushButton*> m_listDrawOptrBtn;//��̬������ť���б�

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

#ifndef QSTTPANELBASE_H
#define QSTTPANELBASE_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTextEdit>
#include "../Config/Frame/SttFrame_XBar.h"
#include "SttToolButton.h"
#include "SttDataButtons.h"
#include "../../TestClient/SttMacroTestInterface.h"

#define SttFrame_Interval 5

extern long SttFrame_Vert_Gap;  //框架按钮垂直方向上的间隔，系统为工具栏、状态栏绘制边框
extern long SttFrame_Line_Pix;    //绘制边框的像素点

class QSttPanelBase : public QWidget
{
    Q_OBJECT

public:
	explicit QSttPanelBase(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr, QFont font,QWidget *parent = 0);
	virtual ~QSttPanelBase();
    virtual void CreateByData(QSttBarDataBtnsMngr &oDataBunsMngr);
    QSttToolButtonBase* CreateButton(CExBaseObject *pObject);
    virtual int AdjustCtrls();
	virtual void UpdateEnableState(const CString &strState);

    QFont m_font;
    int m_nWidth;
    CSttFrame_Panal *m_pPanel;
    QList<QSttToolButtonBase*> m_listCtrls;
};

class QSttFloatPanelBase : public QSttPanelBase
{
	Q_OBJECT

public:
	explicit QSttFloatPanelBase(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr, QFont font,QWidget *parent);

	virtual int AdjustCtrls();

	long m_nFloatWidth;
};

class QSttFloatPanel : public QSttFloatPanelBase
{
    Q_OBJECT

public:
    explicit QSttFloatPanel(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr, QFont font,QWidget *parent);
    virtual void CreateByData(QSttBarDataBtnsMngr &oDataBunsMngr);
    virtual int AdjustCtrls();
	bool SetBtnIndex_LeftMove();//设置m_nBtnIndex 左移
	bool SetBtnIndex_RightMove();//设置m_nBtnIndex 右移
	void EnableLeftRightMoveBtn();
	void UpdateCurrShowButton();

public:
    QPushButton *m_pBtnMoveLeft;//左移按钮
    QPushButton *m_pBtnMoveRight;//右移按钮
    int m_nBtnIndex;//当前从第几个显示
    bool m_bCanRightMove;//可以向右移动的标志
	int m_nCurrShowBtnNum;//当前显示的按钮个数
	int m_nCurrIntervalHideBtnNum;//当前区间隐藏的按钮数量

signals:

public slots:
    void slot_FloatLeftMove();//浮动按钮向左移动
    void slot_FloatRightMove();//浮动按钮向右移动
};

class QSttResultPanel : public QSttPanelBase, CTestEventBaseInterface
{
	Q_OBJECT

public:
	explicit QSttResultPanel(CSttFrame_Panal *pPanel,QSttBarDataBtnsMngr &oDataBunsMngr, QFont font,QWidget *parent);

	virtual int AdjustCtrls();
	virtual void LogString(long nLevel, const CString &strMsg);
	void ClearAll();
	void InitUI();

	virtual long OnRecvLiveUpdate(CSttSysState &oSysState);

protected:
	QVBoxLayout *m_pMainLayout;
	QTextEdit *m_pTextEdit;
	QTextCharFormat m_oErrorFormat;
	QTextCharFormat m_oNormalFormat;

signals:
	void sig_refreshLog(long nLevel,QString strLog);
	void sig_ClearAll();

public slots:
	void slot_refreshOutput(long nLevel,QString strLog);
	void slot_ClearAll();
};

class QSttBarBase : public QWidget
{
    Q_OBJECT

public:
    explicit QSttBarBase(CSttFrame_BarBase *pBarBase, QSttBarDataBtnsMngr &oDataBunsMngr,QFont font, QWidget *parent = 0);

    void CreatByData(CSttFrame_BarBase *pToolBar,QSttBarDataBtnsMngr &oDataBunsMngr);
    void AdjustPanels();
    QSttFloatPanelBase* FindFloatPanel();
	QSttResultPanel* FindResultPanel();

	virtual void UpdateEnableState(const CString &strState);

public slots:
	//线程调用的时候会奔溃，改成信号槽的形式 sf 20220218
	void on_UpdateEnableState(const CString &strState);

protected:
    virtual void paintEvent(QPaintEvent *event) ;

public:
    QFont m_font;
    CSttFrame_BarBase *m_pToolBar;
    QList<QSttPanelBase*> m_plistPanel;
	BOOL m_bDrawFrame;
};

#endif // QSTTPANELBASE_H

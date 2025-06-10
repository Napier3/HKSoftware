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

extern long SttFrame_Vert_Gap;  //��ܰ�ť��ֱ�����ϵļ����ϵͳΪ��������״̬�����Ʊ߿�
extern long SttFrame_Line_Pix;    //���Ʊ߿�����ص�

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
	bool SetBtnIndex_LeftMove();//����m_nBtnIndex ����
	bool SetBtnIndex_RightMove();//����m_nBtnIndex ����
	void EnableLeftRightMoveBtn();
	void UpdateCurrShowButton();

public:
    QPushButton *m_pBtnMoveLeft;//���ư�ť
    QPushButton *m_pBtnMoveRight;//���ư�ť
    int m_nBtnIndex;//��ǰ�ӵڼ�����ʾ
    bool m_bCanRightMove;//���������ƶ��ı�־
	int m_nCurrShowBtnNum;//��ǰ��ʾ�İ�ť����
	int m_nCurrIntervalHideBtnNum;//��ǰ�������صİ�ť����

signals:

public slots:
    void slot_FloatLeftMove();//������ť�����ƶ�
    void slot_FloatRightMove();//������ť�����ƶ�
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
	//�̵߳��õ�ʱ��ᱼ�����ĳ��źŲ۵���ʽ sf 20220218
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

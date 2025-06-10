#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>

#include "../../Module/UI/Webkit/SttMacroParaEditViewHtml.h"
#include "../../Module/UI/Config/Frame/SttFrameConfig.h"
#include "../../Module/UI/Config/MacroTestUI/SttMacroTestUI_TestMacroUIDB.h"
#include "../../Module/UI/Controls/qsttguidebooktreectrl.h"
#include "../../Module/UI/Controls/QSttPanelBase.h"


class QSttTestCntrFramBase : public QMainWindow, public CLogBase
{
    Q_OBJECT

public:
    explicit QSttTestCntrFramBase(QWidget *parent = 0);
    ~QSttTestCntrFramBase();

public:
    void InitConfig();//初始化配置
    void ReleaseConfig();

    void Test(QString str);
public://界面
    void InitUI();

public://界面相关变量
    QWidget *m_MainWidget;
    QWidget *m_centerWidget;
    QHBoxLayout *m_pHBoxLayoutCenter;
    CSttFrameConfig *m_pSttFrameConfig;
    QFont m_gFont;

    QSttBarBase *m_pToolBar;
    QSttBarBase *m_pStatusBar;
    QSttBarDataBtnsMngr m_oDataBtnsMngr;


public:
	QSttMacroParaEditViewHtml *m_pParaEdit;


public:
    virtual void LogString(long nLevel, const CString &strMsg);
    virtual void LogString(long nLevel, const char *strMsg);

//private slots:
//    void on_btnSetDatas_clicked();

//private:
//    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

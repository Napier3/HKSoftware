#ifndef QSttXMainFRAMEBASE_H
#define QSttXMainFRAMEBASE_H

#include <QMainWindow>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "../../../Module/Log/LogPrint.h"
#include "Module/SttWgtCmdExecTool.h"
#include "SttXuiData/SttXMainConfigGlobal.h"
#include "SttXuiData/SttXuiDataMainConfig.h"

class QSttXMainFrameBase : public QMainWindow, public CLogBase
{
    Q_OBJECT

protected:
	QSttWgtCmdExecTool m_oCmdTool;//������Ӧ����cmd


public:
    explicit QSttXMainFrameBase(QWidget *parent, CString strConfigFile = "");
    ~QSttXMainFrameBase();

	void InitResource();
	void ReleaseResource();

	void InitUI(CString strConfigFile = "");
	void CreateCloseHidingBtns();
    void CreateCloseBtns();
	QFont m_gFont;
	CSttXuiDataMainConfig* m_pMainConfig;

signals:

public slots:
	void slot_CloseApp();
	void slot_HideApp();
};

extern QSttXMainFrameBase *g_theSttXMainFrame;
extern double g_dUIShowCoef; // ������ʾ���ű���


#endif // QSttXMainFRAMEBASE_H

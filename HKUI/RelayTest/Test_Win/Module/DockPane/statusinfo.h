#ifndef STATUSINFO_H
#define STATUSINFO_H

#include <QWidget>
#include <QToolButton>
#include <QBoxLayout>
//#include "../../../../../../SttStudio/Module/SttTest/Common/tmt_result_def.h"
//#include "../../../../../../SttStudio/Module/SttTest/Common/tmt_common_def.h"

namespace Ui {
class StatusInfo;
}

class StatusInfo : public QWidget
{
    Q_OBJECT

public:
    explicit StatusInfo(QWidget *parent = 0);
    ~StatusInfo();
	
    void setRuning(bool bRun);
    void setDC(bool bDC);
	bool getDCState();
 
	void init();
	void initSwitchButton();
	void initToolbutton(QToolButton *pToolBtn,const QString &strTitle,const QString &strPicName);
	void setSwitchStatus(/*CEventResult *pEventResult*/);	//设置状态灯

private:
    Ui::StatusInfo *ui;
/*
	QToolButton *m_A;
	QToolButton *m_B;
	QToolButton *m_C;
	QToolButton *m_D;
	QToolButton *m_E;
	QToolButton *m_F;
	QToolButton *m_G;
	QToolButton *m_H;

	QToolButton *m_1;
	QToolButton *m_2;
	QToolButton *m_3;
	QToolButton *m_4;
	QToolButton *m_5;
	QToolButton *m_6;
	QToolButton *m_7;
	QToolButton *m_8;

	QToolButton *m_IA;
	QToolButton *m_IB;
	QToolButton *m_IC;
	QToolButton *m_I0;

	QToolButton *m_V;
	QToolButton *m_OV;
	QToolButton *m_OI;
	QToolButton *m_OH;

	QToolButton *m_Run;
	QToolButton *m_DCurrent;
*/
	bool m_bBlink;
	QHBoxLayout *layout;

	bool m_bDCState;
};

#endif // STATUSINFO_H

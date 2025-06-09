#ifndef QSTTASSISTMSGWIDGET_H
#define QSTTASSISTMSGWIDGET_H

#include <QWidget>
#include "SttAssistWndDynEffectBase.h"

namespace Ui {
class QSttAssistMsgWidget;
}

class QSttAssistMsgWidget : public QWidget, public CSttAssistWndDynEffectBase
{
    Q_OBJECT

public:
    explicit QSttAssistMsgWidget(QWidget *parent = 0);
    ~QSttAssistMsgWidget();

	void ShowMsg(const CString &strMsg, long nShowTimeLong);
	void ShowMsgEx(const CString &strWndID, const CString &strMsg, long nShowTimeLong);

private:
	QRect CalTextRect(const CString &strWndID, const CString &strMsg);

public:
	//��̬Ч��ִ�к���
	virtual void ast_Exec(long nTimeGap);

	//ֹͣ��̬Ч��ִ��
	virtual void ast_Stop();

private:
    Ui::QSttAssistMsgWidget *ui;
};

#endif // QSTTASSISTMSGWIDGET_H

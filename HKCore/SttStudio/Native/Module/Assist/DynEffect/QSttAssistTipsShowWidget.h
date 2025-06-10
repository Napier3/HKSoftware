#ifndef QSttAssistTipsShowWidget_H
#define QSttAssistTipsShowWidget_H

#include <QWidget>
#include "SttAssistWndDynEffectBase.h"

//2022-12-26  lijunqing  暂时实现

namespace Ui {
class QSttAssistTipsShowWidget;
}

class QSttAssistTipsShowWidget : public QWidget, public CSttAssistWndDynEffectBase
{
    Q_OBJECT

public:
    explicit QSttAssistTipsShowWidget(QWidget *parent = 0);
    ~QSttAssistTipsShowWidget();

	CDataGroup m_oTipsConfig;
private:
	QRect CalWidgetRect();

public:
	//动态效果执行函数
	virtual void ast_Exec(long nTimeGap);

	//停止动态效果执行
	virtual void ast_Stop();

private slots:
        void on_m_chkShowAtStart_clicked();
        void on_m_btnNext_clicked();
        void on_m_btnPrev_clicked();
        void on_m_btnClose_clicked();

private:
    Ui::QSttAssistTipsShowWidget *ui;
};

#endif // QSttAssistTipsShowWidget_H

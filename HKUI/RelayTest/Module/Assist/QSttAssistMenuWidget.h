#ifndef QSttAssistMenuWidget_H
#define QSttAssistMenuWidget_H

#include <QWidget>

namespace Ui {
class QSttAssistMenuWidget;
}

class QSttAssistMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QSttAssistMenuWidget(QWidget *parent = 0);
    ~QSttAssistMenuWidget();

	void ShowMenu();

private slots:
    void on_m_btnHelp_clicked();
    void on_m_btnTestTeach_clicked();
    void on_m_ChkShowTips_clicked();

private:
	QRect CalWidgetRect();

protected:
	virtual bool event(QEvent *event);

private:
    Ui::QSttAssistMenuWidget *ui;
};

#endif // QSttAssistMenuWidget_H

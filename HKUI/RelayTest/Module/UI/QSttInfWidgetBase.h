#ifndef QSttInfWidgetBase_H
#define QSttInfWidgetBase_H

#include <QWidget>
#include <QVBoxLayout>

class QSttInfWidgetBase : public QWidget
{
public:
	explicit QSttInfWidgetBase(QWidget *parent=0);
	~QSttInfWidgetBase();

protected:
	QVBoxLayout *m_pMainLayout;

	void InitSttInfWidget(QWidget *pInfWidget);

};

#endif // VECTORWIDGET_H

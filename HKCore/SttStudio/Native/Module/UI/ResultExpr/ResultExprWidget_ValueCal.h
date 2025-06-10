#ifndef RESULTEXPRWIDGET_VALUECAL_H
#define RESULTEXPRWIDGET_VALUECAL_H

#include "ResultExprWidget.h"
#include <QWidget>

namespace Ui {
class QResultExprWidget_ValueCal;
}

class QResultExprWidget_ValueCal : public QResultExprWidget
{
    Q_OBJECT

public:
    explicit QResultExprWidget_ValueCal(QWidget *parent = NULL);
    virtual ~QResultExprWidget_ValueCal();

	virtual void SaveExprBase();
	virtual void LoadExprBase(CXExprBase* pExprBase);

private:
	void InitUI();
	void InitConnect();
	void InitLanguage();

private:
    Ui::QResultExprWidget_ValueCal *ui;

private slots:
	void OnSelectExpr();
	void OnDelectExpr();
};

#endif // RESULTEXPRWIDGET_RANGE_H

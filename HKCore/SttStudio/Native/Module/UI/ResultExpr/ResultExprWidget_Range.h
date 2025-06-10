#ifndef RESULTEXPRWIDGET_RANGE_H
#define RESULTEXPRWIDGET_RANGE_H

#include "ResultExprWidget.h"
#include <QWidget>

namespace Ui {
class QResultExprWidget_Range;
}

class QResultExprWidget_Range : public QResultExprWidget
{
    Q_OBJECT

public:
    explicit QResultExprWidget_Range(QWidget *parent = NULL);
    virtual ~QResultExprWidget_Range();

	virtual void SaveExprBase();
	virtual void LoadExprBase(CXExprBase* pExprBase);

private:
	void InitUI();
	void InitConnect();
	void InitLanguage();

private:
    Ui::QResultExprWidget_Range *ui;

private slots:
	void OnSelectExpr();
	void OnDelectExpr();
};

#endif // RESULTEXPRWIDGET_RANGE_H

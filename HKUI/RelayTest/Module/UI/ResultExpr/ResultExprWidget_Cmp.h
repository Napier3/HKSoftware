#ifndef RESULTEXPRWIDGET_CMP_H
#define RESULTEXPRWIDGET_CMP_H

#include "ResultExprWidget.h"
#include <QWidget>

namespace Ui {
class QResultExprWidget_Cmp;
}

class QResultExprWidget_Cmp : public QResultExprWidget
{
    Q_OBJECT

private:
    void InitUI();
    void InitConnect();
	void InitLanguage();

public:
    explicit QResultExprWidget_Cmp(QWidget *parent = NULL);
    virtual ~QResultExprWidget_Cmp();

	virtual void SaveExprBase();
	virtual void LoadExprBase(CXExprBase* pExprBase);

private:
    Ui::QResultExprWidget_Cmp *ui;

private slots:
	void OnDelectExpr();
	void OnSelectExpr();
};

#endif // RESULTEXPRWIDGET_CMP_H

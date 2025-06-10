#ifndef RESULTEXPRWIDGET_ERROR_H
#define RESULTEXPRWIDGET_ERROR_H

#include "ResultExprWidget.h"
#include <QWidget>

namespace Ui {
class QResultExprWidget_Error;
}

class QResultExprWidget_Error : public QResultExprWidget
{
    Q_OBJECT

private:
	void InitUI();
	void InitConnect();
	void InitLanguage();
	QStringList m_cbbExprTypeList;

public:
    explicit QResultExprWidget_Error(QWidget *parent = NULL);
    virtual ~QResultExprWidget_Error();

	virtual void SaveExprBase();
	virtual void LoadExprBase(CXExprBase* pExprBase);

private:
    Ui::QResultExprWidget_Error *ui;

private slots:
	void OnSelectExpr();
	void OnDelectExpr();
};

#endif // RESULTEXPRWIDGET_ERROR_H

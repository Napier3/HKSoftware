#ifndef RESULTEXPRWIDGET_NODE_H
#define RESULTEXPRWIDGET_NODE_H

#include "ResultExprWidget.h"
#include <QWidget>
#include <QMenu>

namespace Ui {
class QResultExprWidget_Node;
}

class QResultExprWidget_Node : public QResultExprWidget
{
    Q_OBJECT

public:
	QResultExprWidgetContainer* m_pContainer;

    explicit QResultExprWidget_Node(QWidget *parent = NULL);
    virtual ~QResultExprWidget_Node();

	virtual void SaveExprBase();
	virtual void LoadExprBase(CXExprBase* pExprBase);
	virtual bool IsResultExprNode();

private:
	void InitUI();
    void InitConnect();
    void InitLanguage();

private slots:
    void OnSelectExpr();
	void OnDelectExpr();
	void OnExpand();
    void on_m_btnAdd_clicked();
    void slot_Add(bool bCheck);

private:
    Ui::QResultExprWidget_Node *ui;
};

#endif // RESULTEXPRWIDGET_NODE_H

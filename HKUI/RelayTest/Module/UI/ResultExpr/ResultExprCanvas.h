#ifndef QRESULTEXPRCANVAS_H
#define QRESULTEXPRCANVAS_H

#include <QWidget>
#include "ResultExprWidget_Node.h"
#include "ResultExprWidget_Cmp.h"
#include "ResultExprWidget_Error.h"
#include "ResultExprWidget_Range.h"
#include "ResultExprWidget_ValueCal.h"

class QResultExprCanvas : public QResultExprWidget
{
	Q_OBJECT
private:
	CSttItemRsltExpr* m_pRsltExpr;
    QResultExprWidget_Node* m_pRoot;

public:
	QResultExprCanvas(QWidget* parent = NULL);
	virtual ~QResultExprCanvas();

	CSttItemRsltExpr* NewRoot(CSttItemRsltExpr* pItemBase, CSttItemBase* pSttItemBase, CSttReports* pReports, CSttGuideBook* pGuideBook, CTestMacros* pTestMacros);
	virtual void SaveExprBase();
	virtual void LoadExprBase(CXExprBase* pExprBase);
	virtual void UpdateArea();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif

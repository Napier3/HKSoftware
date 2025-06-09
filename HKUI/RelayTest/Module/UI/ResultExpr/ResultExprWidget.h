#ifndef RESULTEXPRWIDGET_H
#define RESULTEXPRWIDGET_H

#include "ResultExprDlg_Data.h"
#include "ResultExprWidgetItem.h"
#include "../../SttCmd/GuideBook/SttItemRsltExpr.h"
#include <QWidget>

#define SPACING 5

namespace Ui {
class QResultExprWidget;
}

class QResultExprWidget : public QWidget
{
    Q_OBJECT

private:
	QColor m_clrForegroundColor;
	QColor m_clrBackgroundColor;

protected:
	CXExprBase* m_pExprBase;
    QResultExprWidget* m_pParentExprWidget;
	QResultExprWidget* m_pCanvasWidget;
    QList<QResultExprWidget*> m_listChildren;

public:
    explicit QResultExprWidget(QWidget *parent = NULL);
    virtual ~QResultExprWidget();

	void showShadow();

	void setForegroundColor(const QColor &color);
	QColor foregroundColor() const;

	void setBackgroundColor(const QColor &color);
	QColor backgroundColor() const;

    virtual void useErrorTheme();
    virtual void useDefaultTheme();

	virtual void UpdateArea();
    void SetParentExprWidget(QResultExprWidget* pWidget);
	void SetCanvasWidget(QResultExprWidget* pWidget);
	virtual void SetReportDatas(CSttReports* pReports);
	virtual void SetSttItemBase(CSttItemBase* pSttItemBase);
	virtual void SetGuideBookDatas(CSttGuideBook* pGuideBook);
	virtual void SetTestMacros(CTestMacros* pTestMacros);
	void SetExprBase(CXExprBase* pExprBase);
	virtual void SaveExprBase();
	virtual void LoadExprBase(CXExprBase* pExprBase);
	void CloseChild(QResultExprWidget* pWidget);
	long CalChildOffset();
	virtual bool IsResultExprNode();

protected:
	void paintEvent(QPaintEvent *event);

	BOOL OnSelectExpr_Data(QResultExprWidgetButtonLine* pEdit);
	BOOL OnSelectExpr_Report(QResultExprWidgetButtonLine* pEdit);
	void OnSelectExprFillEdit(QResultExprDlg_Data* dlg, QResultExprWidgetButtonLine* pEdit);

	void UpdateExprValue(CXExprValue* pValue, QResultExprWidgetButtonLine* pEdit, BOOL bEnable = TRUE);

	void LoadExprBase_Edit(QLineEdit* pEdit, CXExprValue* pValue);
	void LoadExprBase_ComboBox(QComboBox* pEdit, const CString& strText);
	void LoadExprBase_ComboBox(QComboBox* pEdit, long nIndex);

protected slots:
	void OnClose();

protected:
	CSttItemBase* m_pSttItemBase;
	CSttReports* m_pReports;
	CSttGuideBook* m_pGuideBook;
	CTestMacros* m_pTestMacros;

    Ui::QResultExprWidget *ui;
};

#endif // RESULTEXPRWIDGET_H

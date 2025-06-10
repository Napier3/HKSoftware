#ifndef QRESULTEXPRWIDGETITEM_H
#define QRESULTEXPRWIDGETITEM_H

#include "../../../../Module/DataMngr/DvmValue.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QAction>

#define STR_AND			"与"
#define STR_OR			"或"
#define STR_DATASET		"数据集"
#define STR_SYSPARAS	"系统参数"
#define STR_GLOBALPARAS "全局参数"
#define STR_RPTDATA		"报告数据"
#define STR_VALUE		"数值"
#define STR_CAL			"计算公式"

#define STR_ABS			"绝对误差"
#define STR_REAL		"相对误差"

#define EXPRTYPE_AND		"and"
#define EXPRTYPE_OR			"or"
#define EXPRTYPE_DATASET	"dataset"
#define EXPRTYPE_SYSPARA	"sys-para"
#define EXPRTYPE_GLOBALPARA "global-para"
#define EXPRTYPE_REPORT		"report"
#define EXPRTYPE_NUMBER		"number"
#define EXPRTYPE_SCRIPT		"script"
#define EXPRTYPE_ABS		"abs"
#define EXPRTYPE_REAL		"real"

class QResultExprWidgetButtonLine : public QLineEdit
{
    Q_OBJECT
public:
	CString m_strType;
	CDvmValue* m_pBandValue;

    QResultExprWidgetButtonLine(QWidget *parent = NULL);
    virtual ~QResultExprWidgetButtonLine();

    virtual void mousePressEvent(QMouseEvent *) override;
	void Clear();

signals:
    void clicked();
};

class QResultExprWidgetValueComboBox : public QComboBox
{
    Q_OBJECT
public:
    QResultExprWidgetValueComboBox(QWidget *parent = NULL);
    virtual ~QResultExprWidgetValueComboBox();

	void InitUI();
};

class QResultExprWidgetExprComboBox : public QComboBox
{
    Q_OBJECT
public:
    enum tagShowType
    {
        AllExpr,
        LittleExpr,
        BigExpr,
		Cal
    };

public:
    QResultExprWidgetExprComboBox(QWidget *parent = NULL);
    virtual ~QResultExprWidgetExprComboBox();

    void setShowType(tagShowType type);
};

//控件容器,是一个Node及其子节点的布局类
class QResultExprWidgetContainer : public QWidget
{
	Q_OBJECT
public:
	QResultExprWidgetContainer(QWidget *parent = NULL);
	virtual ~QResultExprWidgetContainer();

	void SetRootNode(QWidget* pWidget);
	void AddChildNode(QWidget* pWidget);
	bool IsShowChild();
	void ShowChild();
	void HideChild();

private:
	QHBoxLayout* m_pHLayout;
	QVBoxLayout* m_pVLayout;

	void InitUI();
	void paintEvent(QPaintEvent *event);
};

//用作检视
void ResultExpr_SetTagType(QAction* pObj, long nType);
long ResultExpr_GetTagType(QAction* pObj);

CString ResultExpr_GetSelectExpr(const CString& strUIText);
CString ResultExpr_GetSelectText(const CString& strDataText);

#endif // QRESULTEXPRWIDGETITEM_H

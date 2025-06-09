#ifndef QRESULTEXPRWIDGETITEM_H
#define QRESULTEXPRWIDGETITEM_H

#include "../../../../Module/DataMngr/DvmValue.h"
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QAction>

#define STR_AND			"��"
#define STR_OR			"��"
#define STR_DATASET		"���ݼ�"
#define STR_SYSPARAS	"ϵͳ����"
#define STR_GLOBALPARAS "ȫ�ֲ���"
#define STR_RPTDATA		"��������"
#define STR_VALUE		"��ֵ"
#define STR_CAL			"���㹫ʽ"

#define STR_ABS			"�������"
#define STR_REAL		"������"

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

//�ؼ�����,��һ��Node�����ӽڵ�Ĳ�����
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

//��������
void ResultExpr_SetTagType(QAction* pObj, long nType);
long ResultExpr_GetTagType(QAction* pObj);

CString ResultExpr_GetSelectExpr(const CString& strUIText);
CString ResultExpr_GetSelectText(const CString& strDataText);

#endif // QRESULTEXPRWIDGETITEM_H

#include "ResultExprWidgetItem.h"

QResultExprWidgetButtonLine::QResultExprWidgetButtonLine(QWidget *parent) : QLineEdit(parent)
{
	m_pBandValue = NULL;
    setReadOnly(true);
}

QResultExprWidgetButtonLine::~QResultExprWidgetButtonLine()
{

}

void QResultExprWidgetButtonLine::mousePressEvent(QMouseEvent* event)
{
    QLineEdit::mousePressEvent(event);
    emit clicked();
}

void QResultExprWidgetButtonLine::Clear()
{
	m_pBandValue = NULL;
	m_strType = "";
	setText("");
}

QResultExprWidgetValueComboBox::QResultExprWidgetValueComboBox(QWidget *parent) : QComboBox(parent)
{
     InitUI();
}

void QResultExprWidgetValueComboBox::InitUI()
{

}

QResultExprWidgetValueComboBox::~QResultExprWidgetValueComboBox()
{

}

QResultExprWidgetExprComboBox::QResultExprWidgetExprComboBox(QWidget *parent) : QComboBox(parent)
{

}

QResultExprWidgetExprComboBox::~QResultExprWidgetExprComboBox()
{

}

void QResultExprWidgetExprComboBox::setShowType(tagShowType type)
{
    clear();
    switch (type)
    {
    case AllExpr:
        addItem("==");
        addItem(">=");
        addItem(">");
        addItem("<=");
        addItem("<");
        break;
    case LittleExpr:
        addItem("<=");
        addItem("<");
        break;
    case BigExpr:
        addItem(">=");
        addItem(">");
        break;
	case Cal:
		addItem("+");
		addItem("-");
		addItem("*");
		addItem("/");
		break;
    default:
        break;
    }
}

QResultExprWidgetContainer::QResultExprWidgetContainer(QWidget *parent) : QWidget(parent)
{
	InitUI();
}

QResultExprWidgetContainer::~QResultExprWidgetContainer()
{

}

void QResultExprWidgetContainer::InitUI()
{
	//绑定了layout后不需要手动析构,窗口析构时qt自动析构
	m_pHLayout = new QHBoxLayout;
	setLayout(m_pHLayout);
	m_pVLayout = new QVBoxLayout;
	m_pHLayout->addLayout(m_pVLayout);
	m_pVLayout->setSizeConstraint(QLayout::SetFixedSize);
	m_pHLayout->setSizeConstraint(QLayout::SetFixedSize);
	m_pHLayout->setMargin(0);

}

void QResultExprWidgetContainer::SetRootNode(QWidget* pWidget)
{
	m_pHLayout->insertWidget(0, pWidget);
	adjustSize();
}

void QResultExprWidgetContainer::AddChildNode(QWidget* pWidget)
{
	m_pVLayout->addWidget(pWidget);
	adjustSize();
}

bool QResultExprWidgetContainer::IsShowChild()
{
	if(m_pVLayout->count())
	{
		return m_pVLayout->itemAt(0)->widget()->isVisible();
	}
	return false;
}

void QResultExprWidgetContainer::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)
	QPainter painter(this);
	painter.setPen(QColor("blue"));

	QLayoutItem* pItem = m_pHLayout->itemAt(0);
	QWidget* pWidget = pItem->widget();
	QRect rc = pWidget->geometry();

	painter.drawLine(rc.left(), rc.top(), rc.right(), 0);
	painter.drawLine(rc.right(), 0, width() - 1, 0);
	painter.drawLine(rc.left(), rc.bottom(), rc.right(), height() - 1);
	painter.drawLine(rc.right(), height() - 1, width() - 1, height() - 1);
	painter.drawLine(width() - 1, 0, width() - 1, height() - 1);
}

void QResultExprWidgetContainer::ShowChild()
{
	for (int i = 0; i < m_pVLayout->count(); i++)
	{
		m_pVLayout->itemAt(i)->widget()->show();
	}
}

void QResultExprWidgetContainer::HideChild()
{
	for (int i = 0; i < m_pVLayout->count(); i++)
	{
		m_pVLayout->itemAt(i)->widget()->hide();
	}
}

CString ResultExpr_GetSelectExpr(const CString& strUIText)
{
	CString strText;
	if(strUIText == STR_DATASET)
	{
		strText = EXPRTYPE_DATASET;
	}
	else if(strUIText == STR_SYSPARAS)
	{
		strText = EXPRTYPE_SYSPARA;
	}
	else if(strUIText == STR_GLOBALPARAS)
	{
		strText = EXPRTYPE_GLOBALPARA;
	}
	else if(strUIText == STR_RPTDATA)
	{	
		strText = EXPRTYPE_REPORT;
	}
	else if(strUIText == STR_VALUE)
	{	
		strText = EXPRTYPE_NUMBER;
	}
	else if(strUIText == STR_CAL)
	{	
		strText = EXPRTYPE_SCRIPT;
	}
	return strText;
}

CString ResultExpr_GetSelectText(const CString& strDataText)
{
	CString strText;
	if(strDataText == EXPRTYPE_DATASET)
	{
		strText = STR_DATASET;
	}
	else if(strDataText == EXPRTYPE_SYSPARA)
	{
		strText = STR_SYSPARAS;
	}
	else if(strDataText == EXPRTYPE_GLOBALPARA)
	{
		strText = STR_GLOBALPARAS;
	}
	else if(strDataText == EXPRTYPE_NUMBER)
	{
		strText = STR_VALUE;
	}
	else if(strDataText == EXPRTYPE_REPORT)
	{	
		strText = STR_RPTDATA;
	}
	else if(strDataText == EXPRTYPE_AND)
	{	
		strText = STR_AND;
	}
	else if(strDataText == EXPRTYPE_OR)
	{	
		strText = STR_OR;
	}
	else if(strDataText == EXPRTYPE_ABS)
	{	
		strText = STR_ABS;
	}
	else if(strDataText == EXPRTYPE_REAL)
	{	
		strText = STR_REAL;
	}
	else if(strDataText == EXPRTYPE_SCRIPT)
	{	
		strText = STR_CAL;
	}
	return strText;
}


void ResultExpr_SetTagType(QAction* pObj, long nType)
{
	pObj->setData(QVariant::fromValue(nType));
}

long ResultExpr_GetTagType(QAction* pObj)
{
	return pObj->data().toInt();
}
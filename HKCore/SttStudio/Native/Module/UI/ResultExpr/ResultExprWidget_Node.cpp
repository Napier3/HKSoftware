#include "ResultExprWidget_Node.h"
#include "ResultExprWidget_Cmp.h"
#include "ResultExprWidget_Error.h"
#include "ResultExprWidget_Range.h"
#include "ResultExprWidget_ValueCal.h"
#include "ui_ResultExprWidget_Node.h"
#include "ResultExprDlg_Data.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

QResultExprWidget_Node::QResultExprWidget_Node(QWidget *parent) :
    QResultExprWidget(parent),
    ui(new Ui::QResultExprWidget_Node)
{
    ui->setupUi(this);

	m_pContainer = new QResultExprWidgetContainer(parent);
	m_pContainer->SetRootNode(this);
    setBackgroundColor(QColor(245, 250, 130));

	InitUI();
    InitConnect();
	InitLanguage();
}

QResultExprWidget_Node::~QResultExprWidget_Node()
{
    delete ui;
}

void QResultExprWidget_Node::InitLanguage()
{
	xlang_SetLangStrToWidget_Txt(ui->m_editTrue,g_sLangTxt_Native_notcalculated,XLang_Ctrls_QPushButton);
	xlang_SetLangStrToWidget_Txt(ui->m_btnAdd,g_sLangTxt_Add,XLang_Ctrls_QPushButton);
}

void QResultExprWidget_Node::InitUI()
{
	
}

void QResultExprWidget_Node::InitConnect()
{
    connect(ui->m_editExpr, SIGNAL(clicked()), this, SLOT(OnSelectExpr()));
	connect(ui->m_btnDel, SIGNAL(clicked()), this, SLOT(OnDelectExpr()));
	connect(ui->m_btnClose, SIGNAL(clicked()), this, SLOT(OnClose()));
	connect(ui->m_btnExpand, SIGNAL(clicked()), this, SLOT(OnExpand()));
}

void QResultExprWidget_Node::OnSelectExpr()
{
	long nResult = OnSelectExpr_Report(ui->m_editExpr);
	UpdateExprValue(((CXExprNode*)m_pExprBase)->GetValueRslt(), ui->m_editExpr, nResult);
}

void QResultExprWidget_Node::OnDelectExpr()
{
	ui->m_editExpr->m_pBandValue = NULL;
	ui->m_editExpr->setText("");

	UpdateExprValue(((CXExprNode*)m_pExprBase)->GetValueRslt(), NULL); 
}

void QResultExprWidget_Node::OnExpand()
{
	if(m_pContainer->IsShowChild())
	{
		ui->m_btnExpand->setText("+");
		m_pContainer->HideChild();
	}
	else
	{
		ui->m_btnExpand->setText("-");
		m_pContainer->ShowChild();
	}
}

void QResultExprWidget_Node::on_m_btnAdd_clicked()
{
    QList<QAction*> listAct;
    QMenu* pMenu = new QMenu(this);
	CString strStdValue = "基础数值比较";
    QAction* pAction = new QAction(strStdValue, this);
	ResultExpr_SetTagType(pAction, XEXPRCLASSID_CXEXPRCMP);
    connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_Add(bool)));
    listAct.append(pAction);
	CString strError = "误差判断";
    pAction = new QAction(strError, this);
	ResultExpr_SetTagType(pAction, XEXPRCLASSID_CXEXPRERROR);
    connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_Add(bool)));
    listAct.append(pAction);
	CString strRange = "数值范围比较";
    pAction = new QAction(strRange, this);
	ResultExpr_SetTagType(pAction, XEXPRCLASSID_CXEXPRRANGE);
    connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_Add(bool)));
    listAct.append(pAction);
	CString strValCal = "数据运算";
	pAction = new QAction(strValCal, this);
	ResultExpr_SetTagType(pAction, XEXPRCLASSID_CXEXPRVALUECAL);
	connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_Add(bool)));
	listAct.append(pAction);
	CString strNode = "结果判断节点";
    pAction = new QAction(strNode, this);
	ResultExpr_SetTagType(pAction, XEXPRCLASSID_CXEXPRNODE);
    connect(pAction, SIGNAL(triggered(bool)), this, SLOT(slot_Add(bool)));
    listAct.append(pAction);
    pMenu->addActions(listAct);
    pMenu->show();
    pMenu->move(cursor().pos());
}

void QResultExprWidget_Node::slot_Add(bool bCheck)
{
    QAction* pAction = (QAction*)sender();
	long nType = ResultExpr_GetTagType(pAction);
    QResultExprWidget* pWidget = NULL;
	CXExprBase* pExpr = NULL;
    if(nType == XEXPRCLASSID_CXEXPRCMP)
    {
        pWidget = new QResultExprWidget_Cmp(m_pContainer);
		m_pContainer->AddChildNode(pWidget);
		pExpr = new CXExprCmp;
    }
    else if(nType == XEXPRCLASSID_CXEXPRERROR)
    {
        pWidget = new QResultExprWidget_Error(m_pContainer);
		m_pContainer->AddChildNode(pWidget);
		pExpr = new CXExprError;
    }
    else if(nType == XEXPRCLASSID_CXEXPRRANGE)
    {
        pWidget = new QResultExprWidget_Range(m_pContainer);
		m_pContainer->AddChildNode(pWidget);
		pExpr = new CXExprRange;
    }
	else if(nType == XEXPRCLASSID_CXEXPRVALUECAL)
	{
		pWidget = new QResultExprWidget_ValueCal(m_pContainer);
		m_pContainer->AddChildNode(pWidget);
		pExpr = new CXExprValueCal;
	}
    else if(nType == XEXPRCLASSID_CXEXPRNODE)
    {
        pWidget = new QResultExprWidget_Node(m_pContainer);
		m_pContainer->AddChildNode(((QResultExprWidget_Node*)pWidget)->m_pContainer);
		pExpr = new CXExprNode;
    }
    else
    {
        return;
    }

	m_pExprBase->AddNewChild(pExpr);
	pWidget->SetExprBase(pExpr);

    pWidget->SetParentExprWidget(this);
	pWidget->SetGuideBookDatas(m_pGuideBook);
	pWidget->SetReportDatas(m_pReports);
	pWidget->SetSttItemBase(m_pSttItemBase);
	pWidget->SetTestMacros(m_pTestMacros);
	pWidget->SetCanvasWidget(m_pCanvasWidget);

    m_listChildren.push_back(pWidget);
}

void QResultExprWidget_Node::SaveExprBase()
{
	if(ui->m_cbbExpr->currentIndex() == 0)
	{
		((CXExprNode*)m_pExprBase)->m_strLogic = EXPRTYPE_AND;
	}
	else
	{
		((CXExprNode*)m_pExprBase)->m_strLogic = EXPRTYPE_OR;
	}
	
	for (int i = 0; i < m_listChildren.size(); i++)
	{
		QResultExprWidget* pWidget = m_listChildren[i];
		pWidget->SaveExprBase();
	}
}

bool QResultExprWidget_Node::IsResultExprNode()
{
	return true;
}

void QResultExprWidget_Node::LoadExprBase(CXExprBase* pExprBase)
{
	if(!pExprBase)
	{
		return;
	}


	if(((CXExprNode*)pExprBase)->m_strLogic == "and")
	{
		LoadExprBase_ComboBox(ui->m_cbbExpr, 0);
	}
	else
	{
		LoadExprBase_ComboBox(ui->m_cbbExpr, 1);
	}

	LoadExprBase_Edit(ui->m_editExpr, ((CXExprNode*)pExprBase)->GetValueRslt());

	POS pos = pExprBase->GetHeadPosition();
	while (pos)
	{
		CXExprBase* pChild = (CXExprBase*)pExprBase->GetNext(pos);
		QResultExprWidget* pChildWidgt = NULL;
		switch(pChild->GetClassID())
		{
		case XEXPRCLASSID_CXEXPRCMP:
			pChildWidgt = new QResultExprWidget_Cmp(m_pContainer);
			m_pContainer->AddChildNode(pChildWidgt);
			break;
		case XEXPRCLASSID_CXEXPRERROR:
			pChildWidgt = new QResultExprWidget_Error(m_pContainer);
			m_pContainer->AddChildNode(pChildWidgt);
			break;
		case XEXPRCLASSID_CXEXPRRANGE:
			pChildWidgt = new QResultExprWidget_Range(m_pContainer);
			m_pContainer->AddChildNode(pChildWidgt);
			break;
		case XEXPRCLASSID_CXEXPRNODE:
			pChildWidgt = new QResultExprWidget_Node(m_pContainer);
			m_pContainer->AddChildNode(((QResultExprWidget_Node*)pChildWidgt)->m_pContainer);
			break;
		case XEXPRCLASSID_CXEXPRVALUECAL:
			pChildWidgt = new QResultExprWidget_ValueCal(m_pContainer);
			m_pContainer->AddChildNode(pChildWidgt);
			break;
		default:
			break;
		}

		if(pChildWidgt)
		{
			pChildWidgt->SetExprBase(pChild);
			pChildWidgt->SetParentExprWidget(this);
			pChildWidgt->SetGuideBookDatas(m_pGuideBook);
			pChildWidgt->SetSttItemBase(m_pSttItemBase);
			pChildWidgt->SetTestMacros(m_pTestMacros);
			pChildWidgt->SetReportDatas(m_pReports);
			pChildWidgt->LoadExprBase(pChild);	
			pChildWidgt->SetCanvasWidget(m_pCanvasWidget);
			m_listChildren.push_back(pChildWidgt);
		}
	}

	CXExprValueRslt* pRslt = ((CXExprNode*)m_pExprBase)->GetValueRslt();
	if(pRslt->m_strValue == "0")
	{
		CString strText = "不合格";
		ui->m_editTrue->setText(strText);
		setBackgroundColor(QColor(255, 0, 0));
	}
	else if(pRslt->m_strValue == "1")
	{
		CString strText = "合格";
		ui->m_editTrue->setText(strText);
	}
}
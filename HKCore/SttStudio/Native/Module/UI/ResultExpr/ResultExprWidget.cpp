#include "ResultExprWidget.h"
#include "ui_ResultExprWidget.h"
#include "ResultExprCanvas.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/DvmLogicDevice.h"

#include <QGraphicsEffect>
#include <QPainter>

extern CGbSmartGenWzd *g_theGbSmartGenWzd;

QResultExprWidget::QResultExprWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QResultExprWidget)
{
    ui->setupUi(this);

	m_pSttItemBase = NULL;
	m_pExprBase = NULL;
	m_pReports = NULL;
	m_pGuideBook = NULL;
	m_pTestMacros = NULL;
    m_pParentExprWidget = NULL;
	m_pCanvasWidget = NULL;
}

QResultExprWidget::~QResultExprWidget()
{
    delete ui;
}

void QResultExprWidget::showShadow()
{
	QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
	effect->setBlurRadius(11);
	effect->setColor(QColor(0, 0, 0, 50));
	effect->setOffset(0, 5);
	setGraphicsEffect(effect);
}

void QResultExprWidget::setForegroundColor(const QColor &color)
{
	m_clrForegroundColor = color;
	update();
}

QColor QResultExprWidget::foregroundColor() const
{
	return m_clrForegroundColor;
}

void QResultExprWidget::setBackgroundColor(const QColor &color)
{
	m_clrBackgroundColor = color;
	update();
}

QColor QResultExprWidget::backgroundColor() const
{
	return m_clrBackgroundColor;
}

void QResultExprWidget::useErrorTheme()
{
    setBackgroundColor(QColor(255, 0, 0));
    setForegroundColor(QColor(255, 255, 255));
}

void QResultExprWidget::useDefaultTheme()
{
    setBackgroundColor(QColor(255, 255, 255));
    setForegroundColor(QColor(0, 0, 0));
}

void QResultExprWidget::SetReportDatas(CSttReports* pReports)
{
	m_pReports = pReports;
}

void QResultExprWidget::SetGuideBookDatas(CSttGuideBook* pGuideBook)
{
	m_pGuideBook = pGuideBook;
}

void QResultExprWidget::SetTestMacros(CTestMacros* pTestMacros)
{
	m_pTestMacros = pTestMacros;
}

void QResultExprWidget::SetSttItemBase(CSttItemBase* pSttItemBase)
{
	m_pSttItemBase = pSttItemBase;
}

void QResultExprWidget::SetParentExprWidget(QResultExprWidget* pWidget)
{
    m_pParentExprWidget = pWidget;
}

void QResultExprWidget::UpdateArea()
{
	m_pCanvasWidget->UpdateArea();
}

void QResultExprWidget::SetCanvasWidget(QResultExprWidget* pWidget)
{
	m_pCanvasWidget = pWidget;
}

void QResultExprWidget::SetExprBase(CXExprBase* pExprBase)
{
	m_pExprBase = pExprBase;
}

void QResultExprWidget::paintEvent(QPaintEvent *event)
{
	Q_UNUSED(event)
	QPainter painter(this);
	painter.fillRect(rect(), backgroundColor());
	painter.setPen(QColor("black"));
	painter.drawRect(0, 0, width() - 1, height() - 1);
}

void QResultExprWidget::UpdateExprValue(CXExprValue* pValue, QResultExprWidgetButtonLine* pEdit, BOOL bEnable)
{
	if(!bEnable)
	{
		return;
	}

	if(pValue && pEdit)
	{
		if(pEdit->m_pBandValue)
		{
			pValue->m_strType = pEdit->m_strType;
			pValue->m_strValue = pEdit->m_pBandValue->m_strValue;
			pValue->m_strValueID = pEdit->m_pBandValue->m_strID;
		}
		else
		{
			pValue->m_strType = pEdit->m_strType;
			pValue->m_strValue = pEdit->text();
			pValue->m_strValueID = "";
		}
	}
	else
	{
		pValue->m_strType = "";
		pValue->m_strValue = "";
		pValue->m_strValueID = "";
	}
}

void QResultExprWidget::LoadExprBase_Edit(QLineEdit* pEdit, CXExprValue* pValue)
{
	if(pValue->m_strType == EXPRTYPE_NUMBER)
	{
		pEdit->setText(pValue->m_strValue);
	}
	else
	{
		if(pValue->m_strValueID.GetLength())
		{
			CString strName;
			if(pValue->m_strType == EXPRTYPE_DATASET)
			{
				CDvmDevice* pDevice = g_theGbSmartGenWzd->m_pDvmDevice;
				POS pos = pDevice->GetHeadPosition();
				CExBaseObject* pObj = NULL;
				while(pos)
				{
					CDvmLogicDevice* pLogicDevice = (CDvmLogicDevice*)pDevice->GetNext(pos);
					POS childPos = pLogicDevice->GetHeadPosition();
					while(childPos)
					{
						CDvmDataset* pDataset = (CDvmDataset*)pLogicDevice->GetNext(childPos);
						if (pObj = pDataset->FindByID(pValue->m_strValueID))
						{
							strName = pObj->m_strName;
							break;
						}
					}

					if(pObj)
					{
						break;
					}
				}
			}
			else if (pValue->m_strType == EXPRTYPE_SYSPARA)
			{
				CSttDevice* pDevice = m_pGuideBook->GetDevice();
				CExBaseObject* pObj = pDevice->GetSysPara(FALSE)->FindByID(pValue->m_strValueID);
				strName = pObj ? pObj->m_strName : "";

			}
			else if (pValue->m_strType == EXPRTYPE_GLOBALPARA)
			{
				CExBaseObject* pObj = m_pGuideBook->GetGlobalDatas()->FindByID(pValue->m_strValueID);
				strName = pObj ? pObj->m_strName : "";
			}
			else if (pValue->m_strType == EXPRTYPE_REPORT)
			{
				if (m_pReports)
				{
					CSttReport* pReport = (CSttReport*)m_pReports->GetTail();

					if (pReport != NULL)
					{
						CExBaseObject* pObj = pReport->m_pValues->FindByID(pValue->m_strValueID);
						strName = pObj ? pObj->m_strName : "";
					}
				}	
			}

			QString strText;
			if(strName.GetLength())
			{
				strText = QString("%1 = %2").arg(strName).arg(pValue->m_strValue);
			}
			else
			{
				strText = QString("%1 = %2").arg(pValue->m_strValueID).arg(pValue->m_strValue);
			}
			pEdit->setText(strText);
		}
	}
}

void QResultExprWidget::LoadExprBase_ComboBox(QComboBox* pEdit, const CString& strText)
{
	pEdit->setCurrentIndex(pEdit->findText(strText));
}

void QResultExprWidget::LoadExprBase_ComboBox(QComboBox* pEdit, long nIndex)
{
	pEdit->setCurrentIndex(nIndex);
}

void QResultExprWidget::OnClose()
{
	long nSize = m_listChildren.size();
	for (int i = nSize - 1; i >= 0; i--)
	{
		m_listChildren[i]->OnClose();
	}
	m_listChildren.clear();

 	if(m_pParentExprWidget)
 	{
		((CExBaseList*)m_pExprBase->GetParent())->Delete(m_pExprBase);
		m_pExprBase = NULL;
 		m_pParentExprWidget->CloseChild(this);
 	}
}

void QResultExprWidget::CloseChild(QResultExprWidget* pWidget)
{
	m_listChildren.removeOne(pWidget);
	delete pWidget;
}

bool QResultExprWidget::IsResultExprNode()
{
	return false;
}

long QResultExprWidget::CalChildOffset()
{
	if(m_listChildren.size())
	{
		QResultExprWidget* pWidget = m_listChildren.at(m_listChildren.size() - 1);
		return pWidget->pos().y() + pWidget->height();
	}
	return 0;
}

void QResultExprWidget::OnSelectExprFillEdit(QResultExprDlg_Data* dlg, QResultExprWidgetButtonLine* pEdit)
{
	pEdit->m_pBandValue = dlg->m_pCurSelValue;
	CString strText = dlg->m_pCurSelValue->m_strID;
	if(dlg->m_pCurSelValue->m_strValue.GetLength())
	{
		if (dlg->m_pCurSelValue->m_strName.GetLength())
		{
			strText = QString("%1 = %2").arg(dlg->m_pCurSelValue->m_strName).arg(dlg->m_pCurSelValue->m_strValue);
		}
		else
		{
			strText = QString("%1 = %2").arg(dlg->m_pCurSelValue->m_strID).arg(dlg->m_pCurSelValue->m_strValue);
		}
	}
	pEdit->setText(strText);
}

BOOL QResultExprWidget::OnSelectExpr_Data(QResultExprWidgetButtonLine* pEdit)
{
	QResultExprDlg_Data dlg;
	if(pEdit->text().indexOf("=") == -1)
	{
		dlg.m_strCurValue = pEdit->text();
	}
	dlg.InitDlg(m_pSttItemBase, m_pReports, m_pGuideBook, m_pTestMacros);
	
	if(dlg.exec() == QDialog::Accepted)
	{
		if(dlg.m_pCurSelValue)
		{
			OnSelectExprFillEdit(&dlg, pEdit);
		}
		else
		{
			pEdit->Clear();
			pEdit->setText(dlg.m_strCurValue);
		}
		pEdit->m_strType = dlg.m_strCurType;
		return TRUE;
	}

	return FALSE;
}

BOOL QResultExprWidget::OnSelectExpr_Report(QResultExprWidgetButtonLine* pEdit)
{
	QResultExprDlg_Data dlg;
	dlg.InitDlg(m_pSttItemBase, m_pReports, m_pGuideBook, m_pTestMacros);

	if(m_pReports)
	{
		CSttReport* pReport = (CSttReport*)m_pReports->GetTail();

		if (pReport == NULL)
		{
			dlg.ShowDatas(NULL);
		}

		dlg.ShowDatas(pReport->m_pValues);
	}
	else
	{
		dlg.ShowDatas(NULL);
	}

	if(dlg.exec() == QDialog::Accepted)
	{
		pEdit->m_strType = EXPRTYPE_REPORT;
		OnSelectExprFillEdit(&dlg, pEdit);
		return TRUE;
	}

	return FALSE;
}

void QResultExprWidget::SaveExprBase()
{

}

void QResultExprWidget::LoadExprBase(CXExprBase* pExprBase)
{
	
}

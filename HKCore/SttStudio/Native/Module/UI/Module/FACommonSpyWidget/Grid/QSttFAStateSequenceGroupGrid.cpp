#include "QSttFAStateSequenceGroupGrid.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../SttTestCntrFrameBase.h"
#include "../../../../SttGlobalDef.h"
#include"../Module/XLangResource_Native.h"
#include "../../../Module/XLanguage/XLanguageResource.h"
#include "../../../../UI/FA/QSttMacroParaEditViewVolTimeTypeSec.h"
#include <QHeaderView>

QSttFAStateSequenceGroupGrid::QSttFAStateSequenceGroupGrid(QWidget *parent )
:QExBaseListGridBase(parent)
{
	installEventFilter(this);
}

QSttFAStateSequenceGroupGrid::~QSttFAStateSequenceGroupGrid()
{

}

void QSttFAStateSequenceGroupGrid::InitGrid()
{
	InitGridTitle();
	setFont(*g_pSttGlobalFont);
	verticalHeader()->setVisible(false);
}

void QSttFAStateSequenceGroupGrid::InitGridTitle()
{
	// 禁止表头点击
	horizontalHeader()->setSectionsClickable(false);
	// 禁止表头大小修改
	horizontalHeader()->setSectionsMovable(false);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	horizontalHeader()->setFont(*g_pSttGlobalFont);

	CString astrGridTitle[QSTTFASTATEGRIDCOL] = {_T("名称"),_T("Ua(V)"),_T("Uc(V)"),_T("Ia(A)"),_T("状态"),_T("触发条件"),_T("参数(s)"),_T("结果")};
	int siColType[QSTTFASTATEGRIDCOL]={QT_GVET_EDITBOX, QT_GVET_EDITBOX,QT_GVET_EDITBOX,QT_GVET_EDITBOX,QT_GVET_EDITBOX,QT_GVET_EDITBOX};
	int iGridWidth[QSTTFASTATEGRIDCOL]={65, 80, 80, 80, 60, 115, 80, 80};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QSTTFASTATEGRIDCOL);
}

void QSttFAStateSequenceGroupGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pData);
	CDataGroup *pDataGroup = (CDataGroup*)pData;
	if (pDataGroup->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return;
	}
	CString strName;
	long nIndex = CString_To_long(pDataGroup->m_strID.Right(1));
	strName.Format(_T("状态%ld"),nIndex+1);
	Show_StaticString(pDataGroup, nRow, 0, /*pDataGroup->m_strName*/strName);//添加多个模块获取不到name
	ShowChildren(pDataGroup, nRow);
	nRow++;
}

void QSttFAStateSequenceGroupGrid::ShowChildren(CDataGroup *pDataGroup, int& nRow, BOOL bInsertRow /*= TRUE*/)
{
	ASSERT(pDataGroup);
	CDvmData *pDvmValue = NULL;
	CString strDesc = _T("");
	BOOL bTime = NULL;
	pDvmValue = (CDvmData *)pDataGroup->FindChildByID("U1mag");
	if(pDvmValue != NULL)
	{
		if (pDvmValue->m_strValue == "ResidualVoltage")
		{
			Show_StaticString(pDvmValue, nRow, 1, QString::number(g_pVolTimeTypeSecTestMain->fVoltage,'f',1));
		}
		else
		{
			Show_StaticString(pDvmValue, nRow, 1, &pDvmValue->m_strValue);
		}
	}
	pDvmValue = (CDvmData *)pDataGroup->FindChildByID("U3mag");
	if(pDvmValue != NULL)
	{
		if (pDvmValue->m_strValue == "ResidualVoltage")
		{
			Show_StaticString(pDvmValue, nRow, 2, QString::number(g_pVolTimeTypeSecTestMain->fVoltage,'f',1));
		}
		else
		{
			Show_StaticString(pDvmValue, nRow, 2, &pDvmValue->m_strValue);
		}
	}
	pDvmValue = (CDvmData *)pDataGroup->FindChildByID("I1mag");
	if(pDvmValue != NULL)
	{
		setColumnHidden(3, FALSE);
		if (pDvmValue->m_strValue == "FaultCurrent")
		{
			Show_StaticString(pDvmValue, nRow, 3, QString::number(g_pVolTimeTypeSecTestMain->fCurrent,'f',1));
		}
		else
		{
			Show_StaticString(pDvmValue, nRow, 3, &pDvmValue->m_strValue);
		}
	}
	else 
	{
		setColumnHidden(3, TRUE);
	}
	pDvmValue = (CDvmData *)pDataGroup->FindChildByID("State");
	if(pDvmValue != NULL)
	{
		if (pDvmValue->m_strValue == _T("0"))
		{
			strDesc = _T("分位");
		}
		else if(pDvmValue->m_strValue == _T("1"))
		{
			strDesc = _T("合位");
		}	
		Show_StaticString(pDvmValue, nRow, 4, strDesc);
	}
	pDvmValue = (CDvmData *)pDataGroup->FindChildByID("EndMode");
	if(pDvmValue != NULL)
	{
		strDesc = _T("");
		if (pDvmValue->m_strValue == _T("0"))
		{
			strDesc = _T("时间触发");
			bTime = true;
		}
		else if(pDvmValue->m_strValue == _T("1"))
		{
			strDesc = _T("合闸");
			bTime = false;
		}
		else if (pDvmValue->m_strValue == _T("2"))
		{
			strDesc = _T("分闸");
			bTime = false;
		}

		Show_StaticString(pDvmValue, nRow, 5, strDesc);
	}
	pDvmValue = (CDvmData *)pDataGroup->FindChildByID("LastT");
	if(pDvmValue != NULL)
	{
		if (bTime)
		{
			if (pDvmValue->m_strValue == "FaultCurrentDuration")
			{
				Show_StaticString(pDvmValue, nRow, 6, QString::number(g_pVolTimeTypeSecTestMain->fDuration,'f',1));
			} 
			else
			{
				Show_String(pDvmValue, nRow, 6, &pDvmValue->m_strValue,EndEditCell_String);
			}
			SetItemFgColour(nRow,6,qRgb(0, 0, 0)); 
		}
		else
		{
			float fLastT = CalExpression(pDvmValue->m_strValue);
			Show_StaticString(pDvmValue, nRow, 6, QString::number(fLastT,'f',1));
			SetItemFgColour(nRow,6,qRgb(128, 128, 128)); //不可编辑灰色
		}
	}
	pDvmValue = (CDvmData *)pDataGroup->FindChildByID("ActTime");
	if (pDvmValue != NULL)
	{
		if (pDvmValue->m_strValue != _T("") && IsStringNumber(pDvmValue->m_strValue))
		{
			double dActTime = CString_To_double(pDvmValue->m_strValue);
			Show_StaticString(pDvmValue, nRow, 7, QString::number(dActTime,'f',1));
		}
		else
		{
			Show_StaticString(pDvmValue, nRow, 7, pDvmValue->m_strValue);
		}
	}
}


bool QSttFAStateSequenceGroupGrid::eventFilter( QObject *obj, QEvent *event )
{
	if (event->type()==QEvent::MouseButtonDblClick)
		{
		QMouseEvent *pMouseEvent = (QMouseEvent*)event;
		mouseDoubleClickEvent((QMouseEvent*)pMouseEvent);
		return true;
		}

	return QExBaseListGridBase::eventFilter(obj,event);
}

void QSttFAStateSequenceGroupGrid::mouseReleaseEvent( QMouseEvent *event )
{
#ifdef _PSX_QT_LINUX_
	if (!IsScrollMoving())
#endif
			{
		QMouseEvent *pEvent0 = new QMouseEvent(QEvent::MouseButtonDblClick, event->pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
		QApplication::postEvent(this, pEvent0);
			}

	QExBaseListGridBase::mouseReleaseEvent(event);
}

void QSttFAStateSequenceGroupGrid::EndEditCell_String( int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid )
{
	CString strID = pGrid->GetDatas()->m_strID;
	double fMinValue = 0,fMaxValue = 60;

	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	CEpExpression oEpExp;

	CDvmData *pMinT = (CDvmData *)((CDataGroup *)(pVCellData->pObj->GetParent()))->FindChildByID("MinT");
	if(pMinT != NULL) 
	{
		fMinValue = CalExpression(pMinT->m_strValue);
	}
	CDvmData *pMaxT = (CDvmData *)((CDataGroup *)(pVCellData->pObj->GetParent()))->FindChildByID("MaxT");
	if(pMaxT != NULL)
	{
		fMaxValue = CalExpression(pMaxT->m_strValue);
	}

	if (*pVCellData->pString != pCell->text())
	{
		CString strTmp;
		strTmp = pCell->text();
		float fValue = strTmp.toFloat();
		fValue = setLimit(fMinValue,fMaxValue,fValue);

		(*pVCellData->pString).Format(_T("%.1f"),fValue);

		if (strTmp != (*pVCellData->pString))
		{
			pCell->setText(*pVCellData->pString);
		}
	}
}

void QSttFAStateSequenceGroupGrid::StartInit()
{
	CString strText,strStateID;
	strText = _T("");
	for (int row = 0; row < this->rowCount(); ++row)
	{
		QGV_ITEM *pItem = GetCell(row,7); 

		if (pItem == NULL)
	{
			continue;
	}

		pItem->setText(strText);
	}
}

double QSttFAStateSequenceGroupGrid::CalExpression(CString strExpression)
{
	double fCalResult = 0;
	CEpExpression oEpExp;
	if (oEpExp.ChangeEpExpression(strExpression) != -1)
	{
		POS pos = oEpExp.GetHeadPosition();
		CEpExpVariable *pExpVar = NULL;
		while (pos != NULL)
		{
			pExpVar = oEpExp.GetNext(pos);

			if(pExpVar->m_strVarID == "XTime")
			{
				pExpVar->m_dValue = g_pVolTimeTypeSecTestMain->m_fTimeValues[0];
			}
			else if(pExpVar->m_strVarID == "YTime")
			{
				pExpVar->m_dValue = g_pVolTimeTypeSecTestMain->m_fTimeValues[1];
			}
			else if(pExpVar->m_strVarID == "ZTime")
			{
				pExpVar->m_dValue = g_pVolTimeTypeSecTestMain->m_fTimeValues[2];
			}
			else if(pExpVar->m_strVarID == "STime")
			{
				pExpVar->m_dValue = g_pVolTimeTypeSecTestMain->m_fTimeValues[3];
			}
			else if(pExpVar->m_strVarID == "XLTime")
			{
				pExpVar->m_dValue = g_pVolTimeTypeSecTestMain->m_fTimeValues[4];
			}
			else if(pExpVar->m_strVarID == "X2Time")
			{
				pExpVar->m_dValue = g_pVolTimeTypeSecTestMain->m_fTimeValues[5];
			}
		}
	}
	oEpExp.Value(fCalResult);

	return fCalResult;
}

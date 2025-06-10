#include "QTerminalGooseGrid.h"
#include "../SttMacroParaEditViewTerminalAutoTest.h"

QTerminalGooseGrid::QTerminalGooseGrid(QWidget* pParent) : QExBaseListGridBase(pParent)
{
	
}

QTerminalGooseGrid::~QTerminalGooseGrid()
{
	m_pGooseOutData.clear();
	m_pGooseInData.clear();
}


void QTerminalGooseGrid::InitGrid()
{
	InitGridTitle();
	SetDefaultRowHeight(50);
	SetEditable(FALSE);
}

void QTerminalGooseGrid::InitGridTitle()
{
	CString astrGridTitle[4];
	astrGridTitle[0]= _T("描述");  
	//astrGridTitle[1]= _T("初始值"); 
	astrGridTitle[1]= _T("实测值"); 
	astrGridTitle[2]= _T("测试结果"); 

	int iGridWidth[3]={250/*, 150*/, 150,170};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void QTerminalGooseGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData == NULL)
	{
		return;
	}
	if (pData->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
	{
		CIecCfgGoutCh *pIecCfgGoutCh = (CIecCfgGoutCh*)pData;
		Show_String(pData,nRow,0,&pIecCfgGoutCh->m_strName);
		//Show_String(pData,nRow,1,&pIecCfgGoutCh->m_strDefaultValue); 
		Show_StaticString(pData,nRow,1,_T("---")); 
		Show_StaticString(pData,nRow,2,_T("---")); 
	}
	
	if(pData->GetClassID() == CFGCLASSID_CIECCFGGINCH)
	{
		CIecCfgGinCh *pIecCfgGinCh = (CIecCfgGinCh*)pData;
		Show_String(pData,nRow,0,&pIecCfgGinCh->m_strName);
		//UpdateData_ByDataType(pIecCfgGinCh,nRow);
		Show_StaticString(pData,nRow,1,_T("---")); 
		Show_StaticString(pData,nRow,2,_T("---"));
	}	

	nRow++;
}


void QTerminalGooseGrid::BoutToGinResultVlaues(float fResultTimeVlaue,char strCharacterIndex)
{
	if (m_pDatas == NULL)
	{
		return;
	}
	CString strResultVlaue;
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)m_pDatas;
	strResultVlaue.Format(_T("%.3fs"),fResultTimeVlaue);
	for (int i = 0;i< m_pDatas->GetCount();i++)
	{
		CIecCfgDataGooseChBase *pIecCfgCh = NULL;
		POS pos = g_TerminalAutoTest->m_pGinMapChs->GetHeadPosition();
		while(pos)
		{
			pIecCfgCh = (CIecCfgDataGooseChBase *)g_TerminalAutoTest->m_pGinMapChs->GetNext(pos);
// 			QGV_ITEM *pCell = (QGV_ITEM *)item(i,0);
// 			CString strName = pCell->text();
			CString strID = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oGooseBinList[i]->m_strID;
			if (pIecCfgCh->m_strID == strID)
			{
				CString strDevID = pIecCfgCh->m_strDevChID;
				char displayChar = char('A' + (strDevID.right(1).toInt() - 1));
				if (displayChar == strCharacterIndex)
				{
					Show_StaticString(pGinCh,i,1,_T("动作"));
					Show_StaticString(pGinCh,i,2,strResultVlaue);

					QPair<CString, float> pair(strID, fResultTimeVlaue);
					m_pGooseInData.append(pair);
					return;
				}
			}
		}	
			}
}

void QTerminalGooseGrid::GoutToBinResultVlaues( float fResultTimeVlaue,char strCharacterIndex )
{
	if (m_pDatas == NULL)
	{
		return;
	}
	CString strResultVlaue;		
	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)m_pDatas;
	strResultVlaue.Format(_T("%.3fs"),fResultTimeVlaue);
	for (int i = 0;i< m_pDatas->GetCount();i++)
	{
		CIecCfgDataGooseChBase *pIecCfgCh = NULL;
		POS pos = g_TerminalAutoTest->m_pGoutMapChs->GetHeadPosition();
		while(pos)
		{
			pIecCfgCh = (CIecCfgDataGooseChBase *)g_TerminalAutoTest->m_pGoutMapChs->GetNext(pos);
// 			QGV_ITEM *pCell = (QGV_ITEM *)item(i,0);
// 			CString strName = pCell->text();
			CString strID = g_TerminalAutoTest->m_pMuTerminalTabWidget->m_oBoutGooseList[i]->m_strID;
			if (pIecCfgCh->m_strID == strID)
			{
				CString strDevID = pIecCfgCh->m_strDevChID;
				char displayChar = char('A' + (strDevID.right(1).toInt() - 1));
				if (displayChar == strCharacterIndex)
				{
					Show_StaticString(pGoutCh,i,1,_T("动作"));
					Show_StaticString(pGoutCh,i,2,strResultVlaue);
					
					QPair<CString, float> pair(strID, fResultTimeVlaue);
					m_pGooseOutData.append(pair);
					return;
				}
			}
				}
	}
}


void QTerminalGooseGrid::ClearBoutToGinResultData()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	m_pGooseInData.clear();
	
	CIecCfgGinCh *pGinCh = (CIecCfgGinCh*)m_pDatas;
	for (int i = 0;i < m_pDatas->GetCount(); i++)
	{
		Show_StaticString(pGinCh,i,1,_T("---")); 
		Show_StaticString(pGinCh,i,2,_T("---")); 
	}
}

void QTerminalGooseGrid::ClearGoutToBinResultData()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	m_pGooseOutData.clear();

	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)m_pDatas;
	for (int i = 0; i< m_pDatas->GetCount(); i++)
	{
		Show_StaticString(pGoutCh,i,1,_T("---")); 
		Show_StaticString(pGoutCh,i,2,_T("---")); 
	}
}

void QTerminalGooseGrid::UpdateBoutToGinGrid(long nIndex)
{
	if (m_pDatas == NULL)
	{
		return;
	}


	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)m_pDatas;
	for (int i = 0; i< m_pDatas->GetCount(); i++)
	{
		if (i == nIndex)
		{
		Show_StaticString(pGoutCh,i,1,_T("未动作")); 
		Show_StaticString(pGoutCh,i,2,_T("---")); 
	}
	}
}

void QTerminalGooseGrid::UpdateGoutToBinGrid(long nIndex)
{
	if (m_pDatas == NULL)
	{
		return;
	}

	CIecCfgGoutCh *pGoutCh = (CIecCfgGoutCh*)m_pDatas;
	for (int i = 0; i< m_pDatas->GetCount(); i++)
	{
		if (i == nIndex)
		{
			Show_StaticString(pGoutCh,i,1,_T("未动作")); 
			Show_StaticString(pGoutCh,i,2,_T("---")); 
		}
	}
}



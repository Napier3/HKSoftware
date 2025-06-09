#include "InternationalCharDrawView.h"
#include "../../SttTestCntrFrameAPI.h"
#include "./InternationalCharactInterface.h"

CInternationalCharDrawView::CInternationalCharDrawView(void)
{
}

CInternationalCharDrawView::~CInternationalCharDrawView(void)
{
}
void CInternationalCharDrawView::ClearSearchPoints(long nPtIndex)//20240819 luozibing 清空测试点时设置当前选中测试点为空
{
	SetCurTestPoint(NULL,FALSE);
	CPsuCharDrawView::ClearSearchPoints(nPtIndex);
}
void CInternationalCharDrawView::SetCurTestPoint(CXDrawPoint *pCurrTestPoint, BOOL bUpdateInstruct)
{
	//if (m_pCurrTestPoint == pCurrTestPoint)
	//{
	//	return;
	//}

	//if (m_pCurrTestPoint != NULL)
	//{
	//	if (m_pCurrTestPoint->GetClassID() == DWCLASSID_CXDRAWTESTPOINT)
	//	{
	//		((CXDrawTestPoint*)m_pCurrTestPoint)->m_nTestState &= 0xFF;
	//		((CXDrawTestPoint*)m_pCurrTestPoint)->UpdateColorByTestState();
	//	}
	//}

	//m_pCurrTestPoint = pCurrTestPoint;

	//if (m_pCurrTestPoint == NULL)
	//{
	//	return;
	//}

	//m_oTestPoints.BringToTail(pCurrTestPoint);//将当前选择测试点移动到最后，否则会被覆盖

	//if (bUpdateInstruct)
	//{
	//	m_oAxisInstruct_Point.m_fX = m_pCurrTestPoint->m_fX;
	//	m_oAxisInstruct_Point.m_fY = m_pCurrTestPoint->m_fY;
	//}
}

void CInternationalCharDrawView::DeleteTestData(const CString &strIDPath)
{
	m_pCharacteristics->DeleteTestData(strIDPath);
	//20240703 luozibing 特性图删除测试点
	//CXDrawPoint *pPoint	 = (CXDrawPoint *)m_oTestPoints.FindByID(strIDPath);

	//if (pPoint != NULL)
	//{
	//	CXDrawPoint *pPointSel = GetCurTestPoint();

	//	if (pPointSel == pPoint)
	//	{
	//		//SetCurTestPoint(NULL, FALSE);
	//	}

	//	m_oTestPoints.Delete(pPoint);
	//}
}
BOOL CInternationalCharDrawView::AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState)
{
	
	m_pCharacteristics->AddUpdateTestPoint_Imp(strIDPath, dX, dY, nFaultType, nZoneType, nState);
	//20241028 luozibing 更新选中测试点故障类型改变
	if (nFaultType != m_nFaultType&&nState == CHAR_TEST_OBJECT_STATE_SELECT)
	{//m_nFaultType与nFaultType不同时更新页面显示
		m_nFaultType = nFaultType;
	}


//	CXDrawPoint *pPointOldSel = GetCurTestPoint();
//	CXDrawTestPoint *pPoint = (CXDrawTestPoint *)m_oTestPoints.FindByID(strIDPath);
//	if(pPoint == NULL)
//	{
//		//添加阻抗测试点 根据id路径查找是否存在相同id路径的测试点，不存在则添加
//		pPoint = new CXDrawTestPoint();
////		pPoint->SetTestPoint(dX, dY, strIDPath, nFaultType, XDRAW_TEST_STATE_NORMAL, nZoneType);
//		m_oTestPoints.AddNewChild(pPoint);
//	}
//
//	
//	if ((nState&&XDRAW_TEST_STATE_SELECT))
// 		{
//// 		if (pPointOldSel != NULL&&pPointOldSel != pPoint)
//// 		{
//// 			CXDrawTestPoint *pPointOld = (CXDrawTestPoint *)pPointOldSel;
//// 			pPointOld->ReturnSelBrforeState();
//// 		}
//
//		SetCurTestPoint(pPoint,FALSE);
//		m_nCurFaultType = nFaultType;
// 		}
//
//	pPoint->SetTestPoint(dX, dY, strIDPath, nFaultType, nState, nZoneType);
	return TRUE;
}
//void CInternationalCharDrawView::AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, bool nState)
//{
//	m_pCharacteristics->AddUpdateTestPoint_Imp(strIDPath, dX, dY, nFaultType, -1, nState);
//	if (nFaultType != m_nFaultType)
//	{//m_nFaultType与nFaultType不同时更新页面显示
//		m_nFaultType = nFaultType;
//	}
////	CXDrawPoint *pPointOldSel = GetCurTestPoint();
////	CXDrawTestPoint *pPoint = (CXDrawTestPoint *)m_oTestPoints.FindByID(strIDPath);
////
////	if (pPoint == NULL)
////	{
////		//添加阻抗测试点 根据id路径查找是否存在相同id路径的测试点，不存在则添加
////		pPoint = new CXDrawTestPoint();
//////		pPoint->SetTestPoint(dX, dY, strIDPath, nFaultType, XDRAW_TEST_STATE_NORMAL, -1);
////		m_oTestPoints.AddNewChild(pPoint);
////	}
////
////	if ((nState&&XDRAW_TEST_STATE_SELECT))
////	{
////		SetCurTestPoint(pPoint, FALSE);
////		m_nCurFaultType = nFaultType;
////	}
////
////	pPoint->SetTestPoint(dX, dY, strIDPath, nFaultType, nState, -1);
//}

void CInternationalCharDrawView::AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState)
{
    m_nFaultType = nFaultType;
    m_pCharacteristics->AddUpdateTestLine_Imp(strIDPath, dBegX, dBegY, dEndX, dEndY, nFaultType, nZoneType, nState);

//    return;
}

BOOL CInternationalCharDrawView::AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState)
{
	m_nFaultType = nFaultType;
	m_pCharacteristics->AddUpdateTestLine(strIDPath, dBegX, dBegY, dEndX, dEndY, nFaultType, nState);

	return TRUE;
}

BOOL CInternationalCharDrawView::AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState)
{
	m_nFaultType = nFaultType;
	m_pCharacteristics->AddUpdateTestPoint(strIDPath, dX, dY, nFaultType, nState);

	return TRUE;
}

void CInternationalCharDrawView::DrawAxisTestPoints(CDC *pDC,float fZoomRatio,CPoint ptOffset)
{
	//CAxisInterface *pAxisInterface = NULL;
	//m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
	//if(pAxisInterface)
	//{
	//	if(m_oTestPoints.GetCount() != 0)
	//	{
	//		//画过程中点
	//		POS pos = m_oTestPoints.GetHeadPosition();
	//		while (pos)
	//		{
	//			CXDrawTestPoint* pt = (CXDrawTestPoint*)m_oTestPoints.GetNext(pos);
	//			if (pt->m_nFaultType == m_nCurFaultType)//根据当前选中测试项故障类型进行判断 只显示相同故障类型的测试点
	//			{
	//				pt->LogicPointToDevicePoint(pAxisInterface);
	//				pt->Draw(pDC, fZoomRatio, ptOffset);
	//			}
	//		}
	//	}
	//}
}

//20241010 gongyiping 自动准同期获取pCharArea
CCharacterArea *CInternationalCharDrawView::GetElementLined_Syn(CCharacteristics *pCharacteristics, int nindex)
{
	CCharacteristic* pCurrCharacteristic = (CCharacteristic*)pCharacteristics->GetAtIndex_Char(nindex);
	if (pCurrCharacteristic == NULL)
	{
		return NULL;
	}
	CCharacterArea *pCharArea = pCurrCharacteristic->GetCharacterArea();
	if (pCharArea == NULL)
	{
		return NULL;
	}
	return pCharArea;
}

//20241010 gongyiping 更改由界面显示的线段出现错乱问题
BOOL CInternationalCharDrawView::UpdateTestUI_Syn(CCharacteristics *pCharacteristics,double dX, double dY)
{

	CCharacterArea *pCharArea = GetElementLined_Syn(pCharacteristics, 0);
	if (pCharArea == NULL)
		return FALSE;

	int nindex = 0;
	POS pos = pCharArea->GetHeadPosition();
	if (pCharArea->GetCount()<2)
	{
		return FALSE;
	}
	while (pos)
	{
		CCharElementLined *m_pCurrElementLined = (CCharElementLined*)pCharArea->GetNext(pos);
		if (nindex == 0)
		{
			m_pCurrElementLined->m_strXb.Format(_T("%.3f"), dX);
			m_pCurrElementLined->m_strXe.Format(_T("%.3f"), dX);

			m_pCurrElementLined->m_strYb.Format(_T("%.3f"), dY);
			m_pCurrElementLined->m_strYe.Format(_T("%.3f"), -dY);
		}
		else if (nindex == 1)
		{
			m_pCurrElementLined->m_strXb.Format(_T("%.3f"), -dX);
			m_pCurrElementLined->m_strXe.Format(_T("%.3f"), -dX);

			m_pCurrElementLined->m_strYb.Format(_T("%.3f"), -dY);
			m_pCurrElementLined->m_strYe.Format(_T("%.3f"), dY);
			
		}
		
		nindex++;
	}

	pCharArea = GetElementLined_Syn(pCharacteristics, 1);
	if (pCharArea == NULL)
		return FALSE;

	pos = pCharArea->GetHeadPosition();
	nindex = 0;
	while (pos)
	{
		CCharElementLined *m_pCurrElementLined = (CCharElementLined*)pCharArea->GetNext(pos);
	
		 if (nindex == 0)
		{
			m_pCurrElementLined->m_strXb.Format(_T("%.3f"), dX);
			m_pCurrElementLined->m_strXe.Format(_T("%.3f"), -dX);

			m_pCurrElementLined->m_strYb.Format(_T("%.3f"), -dY);
			m_pCurrElementLined->m_strYe.Format(_T("%.3f"), -dY);

		}
		else if (nindex == 1)
		{
			m_pCurrElementLined->m_strXb.Format(_T("%.3f"), -dX);
			m_pCurrElementLined->m_strXe.Format(_T("%.3f"), dX);

			m_pCurrElementLined->m_strYb.Format(_T("%.3f"), dY);
			m_pCurrElementLined->m_strYe.Format(_T("%.3f"), dY);

		}
		nindex++;
	}
	return TRUE;
}

//20240829 wanmj 特性曲线显示测试点/线
DWORD CInternationalCharDrawView::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd, BOOL bViewTestLines, BOOL bCalCharTemp)
{
	DWORD nRet = CPsuCharDrawView::XCreateElement(pData, pParentWnd, bViewTestLines, bCalCharTemp);
    if (nRet == XCREATE_FAIL)
    {
        return XCREATE_FAIL;
    }

	if (m_pXDrawMngr_Axis == NULL)
	{
		return XCREATE_FAIL;
	}

    UINT nClassID = pData->GetClassID();
	CXDrawList* pCharDrawList = NULL;
	if (nClassID == CHARCLASSID_CCHARACTERISTICS)
    {
		pCharDrawList = m_pCharacteristics->InitCharDrawTestObj_ForDraw(m_nFaultType);
    }
	else if (nClassID == CHARCLASSID_CCHARACTERISTIC)//add wangtao 20240927 新增支持Characteristic类型显示测试点/线
	{
		pCharDrawList = m_pCharacteristics->InitCharDrawTestObj_ForDraw((CCharacteristic*)pData,
			m_nFaultType);
	}

	if (pCharDrawList != NULL)
		m_pXDrawMngr_Axis->AddNewChild(pCharDrawList);

    return XCREATE_SUCC;
}

//zhouhj 2024.9.21 去除该重载，讨论确认后，修改
//DWORD CInternationalCharDrawView::XCreateElement(CExBaseObject *pData, CWnd *pParentWnd)
//{
//	if (pData == NULL)
//	{
//		return XCREATE_FAIL;
//	}
//
//	UINT nClassID = pData->GetClassID();
//	//创建坐标系和绘图数据
//	if (nClassID == CHARCLASSID_CCHARACTERISTIC)
//	{
//		return CCharacterDrawView::XCreateElement(pData, pParentWnd);
//	}
//
//	if (m_pXDrawMngr_Axis != NULL)
//	{
//		m_pXDrawMngr_Axis->DeleteAll();
//		//delete m_pXDrawMngr_Axis;
//		//m_pXDrawMngr_Axis = NULL;
//	}
//
//	if (nClassID == CHARCLASSID_CCHARACTERISTICS)
//	{
//		m_pCharacteristics = (CCharacteristics*)pData;
//		CCharacteristic *pCharTemp = NULL;
//		POS pos = m_pCharacteristics->GetHeadPosition();
//
//
//		while (pos != NULL)
//		{
//			pCharTemp = (CCharacteristic*)m_pCharacteristics->GetNext(pos);
//			if (pCharTemp->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
//				continue;
//			if (m_bShowAllCharacts)
//			{//显示全部曲线
//				InitCharDrawView((CCharacteristic*)pCharTemp, pParentWnd);
//			}
//			else
//			{
//				if (pCharTemp->m_nAutoClose == 1)//不显示全部曲线时 只显示勾选使用的曲线 20240919 luozibing
//				{
//					InitCharDrawView((CCharacteristic*)pCharTemp, pParentWnd);
//				}
//			}
//		}
//
//	}
//
//	//2021-9-17  lijunqing  创建缺省的默认坐标系
//	if (m_pXDrawMngr_Axis == NULL)
//	{
//		CreateXDrawMngr(m_strAxis);
//	}
//
//	//CalLayout
//	CSize szView(0, 0);
//	szView = CalLayout(szView);
//
//	//调整位置
//	CPoint pt(0, 0);
//	Layout(pt);
//
//	return XCREATE_SUCC;
//}

void CInternationalCharDrawView::Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset)
{
    CPsuCharDrawView::Draw(pDC, fZoomRatio,ptOffset);

    if(fabs(m_oTestLineFromChar.m_fXb - m_oTestLineFromChar.m_fXe) > 0.001
            || fabs(m_oTestLineFromChar.m_fYb - m_oTestLineFromChar.m_fYe) > 0.001)
    {
        CAxisInterface *pAxisInterface = NULL;
        m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);
        if(NULL == pAxisInterface)
            return;

        m_oTestLineFromChar.LogicPointToDevicePoint(pAxisInterface);
        m_oTestLineFromChar.m_crForeColor = RGB(255, 0, 0);;
        m_oTestLineFromChar.Draw(pDC, fZoomRatio, ptOffset);
    }

}

void CInternationalCharDrawView::SetTestLineBegin(const CPoint &point)
{
    ASSERT(m_pXDrawMngr_Axis);
    CAxisInterface *pAxisInterface = NULL;
    m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

    if (pAxisInterface != NULL)
    {
        pAxisInterface->DevicePointToLogicPoint(point, &m_dBegX, &m_dBegY);
        CString strX, strY;
        strX.setNum(m_dBegX);
        strY.setNum(m_dBegY);
        //CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("begX = %s, begY = %s \n"), strX.GetString(), strY.GetString());
    }
}

void CInternationalCharDrawView::SetTestLineEnd(const CPoint &point)
{
    ASSERT(m_pXDrawMngr_Axis);
    CAxisInterface *pAxisInterface = NULL;
    m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

    if (pAxisInterface != NULL)
    {
        pAxisInterface->DevicePointToLogicPoint(point, &m_dEndX, &m_dEndY);
        CString strX, strY;
        strX.setNum(m_dEndX);
        strY.setNum(m_dEndY);
        //CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("endX = %s, endY = %s \n"), strX.GetString(), strY.GetString());
    }

    if(fabs(m_dBegX - m_dEndX) > 0.001 || fabs(m_dBegY - m_dEndY) > 0.001)
    {
        m_oTestLineFromChar.SetBeginPoint(m_dBegX, m_dBegY);
        m_oTestLineFromChar.SetEndPoint(m_dEndX, m_dEndY);
    }
}

BOOL CInternationalCharDrawView::GetTestLineBegEndPos(double &dBegX, double &dBegY, double &dEndX, double &dEndY)
{
    //如果起点终点坐标相同，则不添加测试线
    if(fabs(m_oTestLineFromChar.m_fXb - m_oTestLineFromChar.m_fXe) < 0.001 &&
            fabs(m_oTestLineFromChar.m_fYb - m_oTestLineFromChar.m_fYe) < 0.001)
        return FALSE;

    dBegX = m_oTestLineFromChar.m_fXb;
    dBegY = m_oTestLineFromChar.m_fYb;
    dEndX = m_oTestLineFromChar.m_fXe;
    dEndY = m_oTestLineFromChar.m_fYe;

    return TRUE;
}

 void CInternationalCharDrawView::ClearTestLine()
 {
     m_oTestLineFromChar.SetBeginPoint(0, 0);
     m_oTestLineFromChar.SetEndPoint(0, 0);
 }

 void CInternationalCharDrawView::GetAxisMinMax(double &dXmin, double &dYmin, double &dXmax, double &dYmax)
 {
     CAxisInterface *pAxisInterface = NULL;
     m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

     if (pAxisInterface == NULL)
     {
         return;
     }

     pAxisInterface->GetAxisMinMax(dXmin, dYmin, dXmax, dYmax);
 }

 void CInternationalCharDrawView::SetAxisMinMax(double dXmin, double dYmin, double dXmax, double dYmax)
 {
     CAxisInterface *pAxisInterface = NULL;
     m_pXDrawMngr_Axis->GetAxisInterface(&pAxisInterface);

     if (pAxisInterface == NULL)
     {
         return;
     }

     pAxisInterface->SetAxisMinMax(dXmin, dYmin, dXmax, dYmax);
     if (m_pXDrawMngr_Axis != NULL)
     {
         m_pXDrawMngr_Axis->LogicPointToDevicePoint();
     }
 }

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristics.cpp  CCharacteristics


#include "stdafx.h"
#include "Characteristics.h"
#include <cmath>

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
BOOL Global_GetZSettingValueFromCharacteristics(CCharacteristics *pCCharacteristics, long nZone, long nFaultType, double dZAngle, double &dZSePara)
{//通过通过区段、故障类型、阻抗角，获取当前阻抗定值等参数
	//根据区段和故障类型查找对应曲线
	CString strCharId,strCharIndex;
	strCharId = Global_GetCharFaultTypeStringByFaultType(nFaultType);
	strCharIndex.Format(_T("%d"), nZone);

	CCharacteristic* pChar = pCCharacteristics->FindCharByID_Index(strCharId, strCharIndex);
	if (pChar == NULL)
	{
		return FALSE;
	}
	return Global_GetZSettingValueFromCharacteristic(pChar, dZAngle, dZSePara);
}
BOOL Global_GetZSettingValueFromCharacteristic(CCharacteristic* pChar, double dZAngle, double &dZSePara)
{//通过阻抗角，获取交点，并通过交点获取对应阻抗定值
	//20240929 luozibing 根据角阻抗设置一条线段
	double dY, dX, dbX, dbY;
	dY = 65535 * sin(dZAngle*3.14159 / 180.0);
	dX = 65535 * cos(dZAngle*3.14159 / 180.0);

	dbX = 0.001;
	dbY = 0.001;
	int nquadrant = 1;
	//根据阻抗角判断象限  默认为1象限
	if ((dZAngle >= 0 && dZAngle<90) || (dZAngle <= -270 && dZAngle>-360))
	{
		dbX = 0.001;
		dbY = 0.001;
		nquadrant = 1;
	}
	else if ((dZAngle >= 90 && dZAngle<180) || (dZAngle <= -180 && dZAngle>-270))
	{
		dbX = -0.001;
		dbY = 0.001;
		nquadrant = 2;
	}
	else if ((dZAngle >= 180 && dZAngle < 270) || (dZAngle <= -90 && dZAngle >-180))
	{
		dbX = -0.001;
		dbY = -0.001;
		nquadrant = 3;
	}
	else
	{
		dbX = 0.001;
		dbY = -0.001;
		nquadrant = 4;
	}

	CXDrawDatas oList, oPointList;
	pChar->GetIntersectPoint(dbX, dbY, dX, dY, oList);//获取线段与曲线的交点
	if (oList.GetCount() == 0)
	{
		return FALSE;
	}
	//获取非零交点
	POS pos = oList.GetHeadPosition();
	while (pos)
	{
		CXDrawData_Point *pPoint = (CXDrawData_Point *)oList.GetNext(pos);
		if (abs(pPoint->m_fX) == 0 && abs(pPoint->m_fY) == 0)
		{
			continue;
		}
		oPointList.AddTail(pPoint);
		oList.Remove(pPoint);
	}
	if (oPointList.GetCount() == 0)
	{
		return FALSE;
	}
	else if (oPointList.GetCount() == 1)
	{//存在一个交点
		CXDrawData_Point *pPoint = (CXDrawData_Point *)oPointList.GetHead();
		dX = pPoint->m_fX;
		dY = pPoint->m_fY;
	}
	else
	{//存在多个交点 获取阻抗角相同象限值的交点
		dX = dY = 0;
		pos = oPointList.GetHeadPosition();
		while (pos)
		{
			CXDrawData_Point *pPoint = (CXDrawData_Point *)oPointList.GetNext(pos);
			if (abs(dX - pPoint->m_fX) > 0.001 || abs(dY - pPoint->m_fY) > 0.001)
			{
				if (pPoint->m_fX > 0 && pPoint->m_fY > 0 && nquadrant == 1)
				{
					dX = pPoint->m_fX;
					dY = pPoint->m_fY;
				}
				else if (pPoint->m_fX < 0 && pPoint->m_fY > 0 && nquadrant == 2)
				{
					dX = pPoint->m_fX;
					dY = pPoint->m_fY;
				}
				else if (pPoint->m_fX < 0 && pPoint->m_fY < 0 && nquadrant == 3)
				{
					dX = pPoint->m_fX;
					dY = pPoint->m_fY;
				}
				else if (pPoint->m_fX > 0 && pPoint->m_fY < 0 && nquadrant == 4)
				{
	dX = pPoint->m_fX;
	dY = pPoint->m_fY;
				}
			}
		}
	}

	dZSePara = hypot(dY, dX);
	return TRUE;
}
CString Global_GetCharFaultTypeStringByFaultType(int nFaultValue)
{//20240911 luozibing 根据故障类型值获得曲线故障类型
	CString strFaultType;
	if (nFaultValue < 3)
	{
		strFaultType = CHAR_DISTANCE_FAULT_TYPE_LN;//距离保护故障类型-单相接地故障/单相阻抗
	}
	else if (nFaultValue < 6)
	{
		strFaultType = CHAR_DISTANCE_FAULT_TYPE_LL;//距离保护故障类型-相间故障
	}
	else if (nFaultValue < 9)
	{
		strFaultType = CHAR_DISTANCE_FAULT_TYPE_LLN;//距离保护故障类型-相间接地故障
	}
	else if (nFaultValue == 9)
	{
		strFaultType = CHAR_DISTANCE_FAULT_TYPE_LLL;//距离保护故障类型-三相故障
	}
	else
	{
		strFaultType = CHAR_DISTANCE_FAULT_TYPE_LN;//距离保护故障类型-单相接地故障/单相阻抗
	}
	return strFaultType;
}

CCharacteristics::CCharacteristics()
{
	//初始化属性

#ifndef NOT_USE_XLANGUAGE
	m_strName = g_sLangTxt_ChrctCurDefn/*_T("特性曲线定义")*/;
#else
	m_strName = _T("特性曲线定义");
#endif
	m_strID = _T("_characteristics");

	//初始化成员变量
    m_pTestObjects = NULL;
    m_pCurTestObj = NULL;
	m_nTestObjDrawMode = CHAR_TEST_OBJECT_DRAW_ALL;

    m_dMaxSensAng = 78;
}

CCharacteristics::~CCharacteristics()
{
}

long CCharacteristics::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
    xml_GetAttibuteValue(pXmlKeys->m_strMaxSensAng, oNode, m_dMaxSensAng);
	return 0;
}

long CCharacteristics::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
    xml_SetAttributeValue(pXmlKeys->m_strMaxSensAng, oElement, m_dMaxSensAng);
	return 0;
}

void CCharacteristics::InitAfterRead()
{
	char_CChaTmplate_to_Characteristic(this);
	m_pTestObjects = (CCharTestObjects*)FindByClassID(CHARCLASSID_CCHARTESTOBJECTS);

//     POS pos = GetHeadPosition();
//     UINT nClassID = 0;
//     CExBaseObject *pObj = NULL;
// 
//     while (pos != NULL)
//     {
//         pObj = GetNext(pos);
//         nClassID = pObj->GetClassID();
// 
//         if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
//         {
//             m_pTestObjects = (CCharTestObjects *)pObj;
//         }
//     }
}

BOOL CCharacteristics::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharacteristics *p = (CCharacteristics*)pObj;

	return TRUE;
}

BOOL CCharacteristics::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}
    CExBaseObject::CopyOwn(pDest);//2024-8-23 wangsen 补充基类属性值Name和ID
	CCharacteristics *p = (CCharacteristics*)pDest;
	p->m_dMaxSensAng = m_dMaxSensAng;

	return TRUE;
}

CBaseObject* CCharacteristics::Clone()
{
	CCharacteristics *p = new CCharacteristics();
	Copy(p);
	return p;
}

BOOL CCharacteristics::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharacteristics::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCCharacteristicTmplateKey)
	{
		pNew = new CCharacteristicTmplate();
	}
	else if (strClassID == pXmlKeys->m_strCCharacteristicKey)
	{
		pNew = new CCharacteristic();
	}
    else if (strClassID == pXmlKeys->m_strCCharTestObjectsKey)
    {
        pNew = new CCharTestObjects();
		m_pTestObjects = (CCharTestObjects *)pNew;
    }

	return pNew;
}

CExBaseObject* CCharacteristics::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CHARCLASSID_CCHARACTERISTICTMPLATE)
	{
		pNew = new CCharacteristicTmplate();
	}
	else if (nClassID == CHARCLASSID_CCHARACTERISTIC)
	{
		pNew = new CCharacteristic();
	}
    else if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
    {
        pNew = new CCharTestObjects();
		m_pTestObjects = (CCharTestObjects *)pNew;
    }

	return pNew;
}

long CCharacteristics::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseList::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_dMaxSensAng);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_dMaxSensAng);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_dMaxSensAng);
	}

	return 0;
}

void CCharacteristics::InitVariableValues()
{
	POS pos = GetHeadPosition();
	CExBaseList *pCharTempl = NULL;

	while (pos != NULL)
	{
		pCharTempl = (CExBaseList*)GetNext(pos);

		if (pCharTempl->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
		{
			continue;
		}
		
		((CCharacteristic*)pCharTempl)->InitVariableValues();
	}
}

void CCharacteristics::CalCharElement(CExBaseList *pDrawList)
{
	POS pos = GetHeadPosition();
    CExBaseList *pCharTempl = NULL;

	while (pos != NULL)
	{
        pCharTempl = (CExBaseList *)GetNext(pos);
        if(pCharTempl->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
        {
            ((CCharacteristic *)pCharTempl)->CalCharElement(pDrawList);
        }
	}
}

BOOL CCharacteristics::IsCharTempExist(CCharacteristic *pCharTmp)
{
	POS pos = GetHeadPosition();
	CExBaseList *p = NULL;
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CExBaseList *)GetNext(pos);

		if (p->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		if (p->IsEqual(pCharTmp))
		{
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}

CCharacteristic* CCharacteristics::GetAtIndex_Char(long nIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nCurrIndex = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		if (nCurrIndex == nIndex)
		{
			return (CCharacteristic*)p;
		}

		nCurrIndex++;
	}

	return NULL;
}

CCharacteristic* CCharacteristics::GetTail_Char()
{
	POS pos = GetTailPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetPrev(pos);

		if (p->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		return (CCharacteristic*)p;
	}

	return NULL;
}

CCharacteristic* CCharacteristics::FindByID_Char(const CString &strID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		if (p->m_strID == strID)
		{
			return (CCharacteristic*)p;
		}
	}

	return NULL;
}

BOOL CCharacteristics::AddCharTempClone(CCharacteristic *pCharTmp)
{
	if (IsCharTempExist(pCharTmp))
	{
		return FALSE;
	}

	CCharacteristic *pNew = (CCharacteristic*)pCharTmp->Clone();
	AddNewChild(pNew);

	return TRUE;
}

CCharacteristic* CCharacteristics::FindChar(CDvmData *pAttrs)
{
	POS pos = GetHeadPosition();
	CExBaseList *p = NULL;
	CCharacteristic *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseList *)GetNext(pos);

		if (p->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		if (((CCharacteristic*)p)->CmpAttrs(pAttrs))
		{
			pFind = (CCharacteristic*)p;
			break;
		}
	}

	return pFind;
}

//2021-9-17  初始化空的特性曲线
void CCharacteristics::InitEmptyCharacter(const CString &strAxis)
{
	if (GetCount() > 0)
	{
		return;
	}

	CCharacteristic *pCharTemp = new CCharacteristic();
	pCharTemp->m_strAxis = strAxis;
	AddNewChild(pCharTemp);
}

//2023-2-15  shaolei   通过id和index，结合查找特性曲线
CCharacteristic* CCharacteristics::FindCharByID_Index(const CString &strID, const CString &strIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CCharacteristic *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;
		if (p->m_strID == CHAR_DISTANCE_FAULT_TYPE_ALL && ((CCharacteristic*)p)->m_strIndex == strIndex)
		{//20241011 luozibing 为ALL类型时index相等 找到对应曲线
			pFind = (CCharacteristic*)p;
			break;
		}
		else
		{
		if (p->m_strID == strID
			&& ((CCharacteristic*)p)->m_strIndex == strIndex)
		{
			pFind = (CCharacteristic*)p;
			break;
		}
	}

	}

	return pFind;
}


void CCharacteristics::DeleteTestData(const CString &strIDPath)
{
    POS pos = GetHeadPosition();
    while (pos != NULL)
    {
        CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
        if(pCharTemp->GetClassID() == CHARCLASSID_CCHARTESTOBJECTS)
        {
            pCharTemp->DeleteByID(strIDPath);
        }
        else if(pCharTemp->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
        {
            CCharTestObjects* pTestObjects = ((CCharacteristic*)pCharTemp)->GetTestObjects();
            pTestObjects->DeleteByID(strIDPath);
        }

    }
}

void CCharacteristics::ClearTestData()
{
    POS pos = GetHeadPosition();
    while (pos != NULL)
    {
        CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
        if(pCharTemp->GetClassID() == CHARCLASSID_CCHARTESTOBJECTS)
        {
            pCharTemp->DeleteAll();
        }
        else if(pCharTemp->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
        {
            CCharTestObjects* pTestObjects = ((CCharacteristic*)pCharTemp)->GetTestObjects();
            pTestObjects->DeleteAll();
        }
    }
//    return;
}

CCharTestObjects* CCharacteristics::GetTestObjects()
{
	//获取时,再次查找,防止链表删除时,该指针未清空
	m_pTestObjects = (CCharTestObjects*)FindByClassID(CHARCLASSID_CCHARTESTOBJECTS);
	return m_pTestObjects;
}

void CCharacteristics::CalCharErrBandLen()
{
    POS pos = GetHeadPosition();
    CExBaseList *pCharTempl = NULL;

    while (pos != NULL)
    {
        pCharTempl = (CExBaseList *)GetNext(pos);
        if(pCharTempl->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
        {
            ((CCharacteristic *)pCharTempl)->CalCharErrBandLen(m_dMaxSensAng);
        }
    }
}

void CCharacteristics::SetIsShowErrorBand(BOOL bShow)
{
    POS pos = GetHeadPosition();
    CExBaseList *pCharTempl = NULL;

    while (pos != NULL)
    {
        pCharTempl = (CExBaseList *)GetNext(pos);
        if(pCharTempl->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
        {
            ((CCharacteristic *)pCharTempl)->SetIsShowErrorBand(bShow);
        }
    }
}

void CCharacteristics::AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState)
{ 
    CString strFaultType;
    strFaultType = Global_GetCharFaultTypeStringByFaultType(nFaultType);

    POS pos = GetHeadPosition();
    BOOL bCharaExisted = FALSE;
    while (pos != NULL)
    {
        CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
        if(pCharTemp->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
            continue;

        CCharacteristic *pChar = (CCharacteristic*)pCharTemp;
        CCharTestObjects* pTestObjects = pChar->GetTestObjects();
        CCharTestLine* pTestLine = (CCharTestLine*)pTestObjects->FindByID(strIDPath);

        if(pChar->m_strID != strFaultType || CString_To_long(pChar->m_strIndex) != nZoneType)
        {
            /*测试项数据更新后和原来的特性曲线故障类型区段不匹配*/
            if(pTestLine != NULL)
                DeleteTestData(strIDPath);
        }
        else
        {
            if(pTestLine == NULL)
            {
                pTestLine = (CCharTestLine*)pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTLINE);
                pTestObjects->AddNewChild(pTestLine);
            }
            pTestLine->m_strID = strIDPath;
            pTestLine->m_nFaultType = nFaultType;
            pTestLine->m_fXb = dBegX;
            pTestLine->m_fYb = dBegY;
            pTestLine->m_fXe = dEndX;
            pTestLine->m_fYe = dEndY;
            bCharaExisted = TRUE;
            m_pCurTestObj = pTestLine;
            break;
        }
    }

    if(!bCharaExisted)
    {
		GetTestObjects();

        if(m_pTestObjects == NULL)
        {
            m_pTestObjects = (CCharTestObjects*)CreateNewChild(CHARCLASSID_CCHARTESTOBJECTS);
            AddNewChild(m_pTestObjects);
        }
        CCharTestLine* pTestLine = (CCharTestLine*)m_pTestObjects->FindByID(strIDPath);
        if(pTestLine == NULL)
        {
            pTestLine = (CCharTestLine*)m_pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTLINE);
            m_pTestObjects->AddNewChild(pTestLine);
        }
        pTestLine->m_strID = strIDPath;
        pTestLine->m_nFaultType = nFaultType;
        pTestLine->m_fXb = dBegX;
        pTestLine->m_fYb = dBegY;
        pTestLine->m_fXe = dEndX;
        pTestLine->m_fYe = dEndY;
        m_pCurTestObj = pTestLine;
    }

//    return;
}

void CCharacteristics::AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState)
{
	POS pos = GetHeadPosition();
	BOOL bCharaExisted = FALSE;
	while (pos != NULL)
	{
		CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
		if (pCharTemp->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		CCharacteristic *pChar = (CCharacteristic*)pCharTemp;
		if (pChar->m_nUse == 0)
		{
			continue;
		}

		CCharTestObjects* pTestObjects = pChar->GetTestObjects();
		CCharTestLine* pTestLine = (CCharTestLine*)pTestObjects->FindByID(strIDPath);

		if (pTestLine == NULL)
		{
			pTestLine = (CCharTestLine*)pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTLINE);
			pTestObjects->AddNewChild(pTestLine);
		}
		pTestLine->m_strID = strIDPath;
		pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;//add wangtao 20241016 测试线为user属性
		pTestLine->m_nFaultType = nFaultType;
		pTestLine->m_fXb = dBegX;
		pTestLine->m_fYb = dBegY;
		pTestLine->m_fXe = dEndX;
		pTestLine->m_fYe = dEndY;
		bCharaExisted = TRUE;
		m_pCurTestObj = pTestLine;
		break;
		
	}

	if (!bCharaExisted)
	{
		GetTestObjects();

		if (m_pTestObjects == NULL)
		{
			m_pTestObjects = (CCharTestObjects*)CreateNewChild(CHARCLASSID_CCHARTESTOBJECTS);
			AddNewChild(m_pTestObjects);
		}
		CCharTestLine* pTestLine = (CCharTestLine*)m_pTestObjects->FindByID(strIDPath);
		if (pTestLine == NULL)
		{
			pTestLine = (CCharTestLine*)m_pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTLINE);
			m_pTestObjects->AddNewChild(pTestLine);
		}
		pTestLine->m_strID = strIDPath;
		pTestLine->m_strType = CHAR_TEST_LINE_TYPE_USER;//add wangtao 20241016 测试点为user属性
		pTestLine->m_nFaultType = nFaultType;
		pTestLine->m_fXb = dBegX;
		pTestLine->m_fYb = dBegY;
		pTestLine->m_fXe = dEndX;
		pTestLine->m_fYe = dEndY;
		m_pCurTestObj = pTestLine;
	}
}
//20240822 wanmj
CXDrawList* CCharacteristics::InitCharDrawTestObj_ForDraw(int nFaultType)
{
    if(nFaultType == -1)
        return NULL;

    CXDrawList* pDrawList = new CXDrawList();
    POS pos = GetHeadPosition();
    while (pos != NULL)
    {
        CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
        if(pCharTemp->GetClassID() == CHARCLASSID_CCHARTESTOBJECTS)
        {
			((CCharTestObjects*)pCharTemp)->InitCharDrawTestObj_ForDraw(pDrawList, nFaultType, m_pCurTestObj, m_nTestObjDrawMode);
        }
        else if(pCharTemp->GetClassID() == CHARCLASSID_CCHARACTERISTIC)
        {
			((CCharacteristic*)pCharTemp)->InitCharDrawTestObj_ForDraw(pDrawList, nFaultType, m_pCurTestObj, m_nTestObjDrawMode);
        }

    }

    return pDrawList;
}

CXDrawList* CCharacteristics::InitCharDrawTestObj_ForDraw(CCharacteristic *pCharact, int nFaultType)
{
	if (nFaultType == -1)
		return NULL;

	if (pCharact == NULL)
	{
		return NULL;
	}

	CXDrawList* pDrawList = new CXDrawList();
	pCharact->InitCharDrawTestObj_ForDraw(pDrawList, nFaultType,
		m_pCurTestObj, m_nTestObjDrawMode);
	return pDrawList;
}

BOOL CCharacteristics::AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState)
{
	//CString strFaultType;
	//if (nFaultType == 0/*("A相接地")*/ || nFaultType == 1/*("B相接地")*/ || nFaultType == 2/*("C相接地")*/ ||
	//	nFaultType == 6/*("AB接地短路")*/ || nFaultType == 7/*("BC接地短路")*/ || nFaultType == 8/*("CA接地短路")*/)
	//{
	//	strFaultType = "LN";
	//}
	//else
	//{
	//	strFaultType = "LL";
	//}
	GetTestObjects();
	if (m_pTestObjects == NULL)
	{
		m_pTestObjects = (CCharTestObjects*)CreateNewChild(CHARCLASSID_CCHARTESTOBJECTS);
		AddNewChild(m_pTestObjects);
	}
	CCharTestPoint* pTestPonit_NoChar = (CCharTestPoint*)m_pTestObjects->FindByID(strIDPath);

	CString strFaultType;
	strFaultType = Global_GetCharFaultTypeStringByFaultType(nFaultType);//20240906 luozibing 使用新增全局函数

	POS pos = GetHeadPosition();
	BOOL bCharaExisted = FALSE;
	while (pos != NULL)
	{
		CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
		if (pCharTemp->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		CCharTestObjects* pTestObjects = ((CCharacteristic*)pCharTemp)->GetTestObjects();
		CCharTestPoint* pTestPonit = (CCharTestPoint*)pTestObjects->FindByID(strIDPath);

		if (((CCharacteristic*)pCharTemp)->m_strID != strFaultType || CString_To_long(((CCharacteristic*)pCharTemp)->m_strIndex) != nZoneType)
		{
			/*测试项数据更新后和原来的特性曲线故障类型区段不匹配*/
			if (pTestPonit != NULL)
				DeleteTestData(strIDPath);
		}
		else
		{
			//20241008 luozibing 更新测试点到对应曲线CCharTestObjects时，还存在相同id测试点在m_pTestObjects中，则删除m_pTestObjects中测试点
			if (pTestPonit_NoChar != NULL)
			{
				DeleteTestData(strIDPath);
			}
			if (pTestPonit == NULL)
			{
				pTestPonit = (CCharTestPoint*)pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTPOINT);
				pTestObjects->AddNewChild(pTestPonit);
			}
			pTestPonit->SetTestPoint(strIDPath, dX, dY, nFaultType, nState, nZoneType);
			if (nState == CHAR_TEST_OBJECT_STATE_SELECT)//20241025 luozibing 当前状态为选中时设置
			{
			m_pCurTestObj = pTestPonit;
			}
			bCharaExisted = TRUE;
		}
	}
	if (!bCharaExisted)
	{
	if (pTestPonit_NoChar == NULL)
	{
		pTestPonit_NoChar = (CCharTestPoint*)m_pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTPOINT);
		m_pTestObjects->AddNewChild(pTestPonit_NoChar);
	}
	pTestPonit_NoChar->SetTestPoint(strIDPath, dX, dY, nFaultType, nState, nZoneType);
	if (nState == CHAR_TEST_OBJECT_STATE_SELECT)//20241025 luozibing 当前状态为选中时设置
	{
	m_pCurTestObj = pTestPonit_NoChar;
	}
	}
	return TRUE;
}
void CCharacteristics::AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState)
{
	POS pos = GetHeadPosition();
	BOOL bCharaExisted = FALSE;
	while (pos != NULL)
	{
		CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
		if (pCharTemp->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;
		CCharacteristic *pChar = (CCharacteristic*)pCharTemp;
		if (pChar->m_nUse == 0)
		{
			continue;
		}
		CCharTestObjects* pTestObjects = pChar->GetTestObjects();
		CCharTestPoint* pTestPonit = (CCharTestPoint*)pTestObjects->FindByID(strIDPath);

		
		if (pTestPonit == NULL)
		{
			pTestPonit = (CCharTestPoint*)pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTPOINT);
			pTestObjects->AddNewChild(pTestPonit);
		}
		pTestPonit->SetTestPoint(strIDPath, dX, dY, nFaultType, nState);
		m_pCurTestObj = pTestPonit;
		
	}

	GetTestObjects();

	if (m_pTestObjects == NULL)
	{
		m_pTestObjects = (CCharTestObjects*)CreateNewChild(CHARCLASSID_CCHARTESTOBJECTS);
		AddNewChild(m_pTestObjects);
	}

	CCharTestPoint* pTestPonit = (CCharTestPoint*)m_pTestObjects->FindByID(strIDPath);
	if (pTestPonit == NULL)
	{
		pTestPonit = (CCharTestPoint*)m_pTestObjects->CreateNewChild(CHARCLASSID_CCHARTESTPOINT);
		m_pTestObjects->AddNewChild(pTestPonit);
	}
	pTestPonit->SetTestPoint(strIDPath, dX, dY, nFaultType, nState);
	m_pCurTestObj = pTestPonit;
}
void CCharacteristics::UpdateCurrTestPoint(double fXact, double fYact, long nActState)
{
	if (m_pCurTestObj &&m_pCurTestObj->GetClassID() == CHARCLASSID_CCHARTESTLINE)
	{
		((CCharTestLine*)m_pCurTestObj)->m_fXact = fXact;
		((CCharTestLine*)m_pCurTestObj)->m_fYact = fYact;
		((CCharTestLine*)m_pCurTestObj)->m_nActState = nActState;
	}
}
void CCharacteristics::UpdateTestPointState(CString strPointID, long nState)
{//20241028 luozibing 更新测试点状态
	if (m_pTestObjects == NULL)
	{
		m_pTestObjects = (CCharTestObjects*)CreateNewChild(CHARCLASSID_CCHARTESTOBJECTS);
		AddNewChild(m_pTestObjects);
	}

	POS pos = GetHeadPosition();
	BOOL bCharaExisted = FALSE;
	while (pos != NULL)
	{
		CExBaseList* pCharTemp = (CExBaseList*)GetNext(pos);
		if (pCharTemp->GetClassID() != CHARCLASSID_CCHARACTERISTIC)
			continue;

		CCharTestObjects* pTestObjects = ((CCharacteristic*)pCharTemp)->GetTestObjects();
		CCharTestPoint* pTestPonit = (CCharTestPoint*)pTestObjects->FindByID(strPointID);
		if (pTestPonit != NULL)
		{
			pTestPonit->m_nTestState = nState;
			bCharaExisted = TRUE;
		}
	}
	if (!bCharaExisted)
	{
		CCharTestPoint* pTestPonit_NoChar = (CCharTestPoint*)m_pTestObjects->FindByID(strPointID);
		if (pTestPonit_NoChar != NULL)
		{
			pTestPonit_NoChar->m_nTestState = nState;
		}
		
	}
}
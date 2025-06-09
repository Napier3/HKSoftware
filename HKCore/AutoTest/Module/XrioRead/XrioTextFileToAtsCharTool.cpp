// XrioCustomBlock.cpp : 实现文件
//

#include "stdafx.h"
#include "XrioTextFileToAtsCharTool.h"


CXrioTextFileToAtsCharTool::CXrioTextFileToAtsCharTool()
{
	m_pCharacteristicsRef = NULL;
}

CXrioTextFileToAtsCharTool::~CXrioTextFileToAtsCharTool()
{

}

BOOL CXrioTextFileToAtsCharTool::ImportCharsFromRioFile(const CString &strRioFile)
{
	CXrioTextFile oXrioTxtFile;
	
	if (!oXrioTxtFile.ReadXrioTextFile(strRioFile))
	{
		return FALSE;
	}

	ParseGroup(&oXrioTxtFile);

	return TRUE;
}

BOOL CXrioTextFileToAtsCharTool::ImportCharsFromRioFile(CCharacteristics *pChars, const CString &strRioFile)
{
	m_pCharacteristicsRef = pChars;
	return ImportCharsFromRioFile(strRioFile);
}

BOOL CXrioTextFileToAtsCharTool::ImportCharFromRioGroup(CCharacteristic *pChar, CXrioGroup *pGroup)
{
	if (pGroup == NULL || pChar == NULL)
	{
		return FALSE;
	}

	if (pGroup->GetClassID() != XRIOCLASSID_RIO_GROUP)
	{
		return FALSE;
	}

	if (pGroup->m_strName == RIO_KEY_ZONE)
	{
		InitChar_Zone(pGroup, pChar);
		return TRUE;
	}
	else if (pGroup->m_strName == RIO_KEY_DIFFBIAS)
	{
		InitChar_DiffBias(pGroup, pChar);
		return TRUE;
	}

	return FALSE;
}

void CXrioTextFileToAtsCharTool::ParseGroup(CXrioGroup *pGroup)
{
	if (pGroup->m_strName == RIO_KEY_ZONE)
	{
		AddChar_Zone(pGroup);
		return;
	}
	else if (pGroup->m_strName == RIO_KEY_DIFFBIAS)
	{
		AddChar_DiffBias(pGroup);
		return;
	}

	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pGroup->GetNext(pos);

		if (p->GetClassID() == XRIOCLASSID_RIO_GROUP)
		{
			ParseGroup((CXrioGroup*)p);
		}
	}
}

void CXrioTextFileToAtsCharTool::InitChar_Zone(CXrioGroup *pGroup, CCharacteristic *pChar)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmData *pCharAttrs = pChar->GetAttrs(TRUE);

	while (pos != NULL)
	{
		p = (CExBaseObject *)pGroup->GetNext(pos);

		if (p->GetClassID() == XRIOCLASSID_RIO_GROUP)
		{//Xrio Group Object
			AddChar_Zone_Group((CXrioGroup*)p ,pChar);
		}
		else
		{//Xrio Data Object
			InitChar_ZoneAttrs((CXrioData*)p, pChar, pCharAttrs);
		}
	}
}

void CXrioTextFileToAtsCharTool::AddChar_Zone(CXrioGroup *pGroup)
{
	CCharacteristic *pNew = new CCharacteristic();
	m_pCharacteristicsRef->AddNewChild(pNew);
	InitChar_Zone(pGroup, pNew);
}

void CXrioTextFileToAtsCharTool::InitChar_ZoneAttrs(CXrioData *pData, CCharacteristic *pChar, CDvmData *pCharAttrs)
{
	CXrioAttr *pAttr = (CXrioAttr*)pData->GetHead();
	
	if (pAttr == NULL)
	{
		return;
	}

	pCharAttrs->AddValue(pData->m_strName, pAttr->m_strName);

	if (pData->m_strName == RIO_KEY_LABEL || pData->m_strName == RIO_KEY_NAME)
	{
		pChar->m_strName = pAttr->m_strName;
		pChar->m_strID = pAttr->m_strName;
	}
}

void CXrioTextFileToAtsCharTool::AddChar_Zone_Group(CXrioGroup *pGroup, CCharacteristic *pChar)
{
	if (pGroup->m_strName == RIO_KEY_SHAPE)
	{
		AddChar_Zone_Shape(pGroup, pChar);
	}
	else if (pGroup->m_strName == RIO_KEY_MHOSHAPE)
	{
		AddChar_Zone_Mho(pGroup, pChar);
	}
	else if (pGroup->m_strName == RIO_KEY_LENSTOMATOSHAPE)
	{
		AddChar_Zone_Lens(pGroup, pChar);
	}
	else if (pGroup->m_strName == RIO_KEY_TRIPCHAR)
	{
		AddChar_Zone_TripChar(pGroup, pChar);
	}
}

/*
BEGIN SHAPE
	LINE    0, 0, -30, LEFT
	ARCP    0, 0, 10, -30, 135, CCW, LEFT
	LINE    0, 0, -45, LEFT
	AUTOCLOSE    YES
	INVERT    NO
END SHAPE

BEGIN SHAPE
	LINE    0.1, 0, -73.5, LEFT
	ARCP    20.615, -13.963, 25, 151.486, 176.55, CCW, LEFT
	LINE    0.1, 0, 214.5, LEFT
	ARCP    5, 70.5, 15, -133.98, -84.4257, CCW, LEFT
	LINE    0.1, 0, 106.5, LEFT
	ARCP    20.6155, 137.96, 25, -47.7652, -19.0365, CCW, LEFT
	LINE    0.1, 0, 34.5, LEFT
	ARCP    5, 70.5, 15, 22.9803, 117.426, CCW, LEFT
	AUTOCLOSE    YES
	INVERT    NO
END SHAPE
*/
void CXrioTextFileToAtsCharTool::AddChar_Zone_Shape(CXrioGroup *pGroup, CCharacteristic *pChar)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *p = NULL;
	CCharacterArea *pArea = pChar->GetCharacterArea();

	while (pos != NULL)
	{
		p = (CExBaseObject *)pGroup->GetNext(pos);
		ASSERT (p->GetClassID() == XRIOCLASSID_RIO_DATA);
		
		if (p->m_strName == RIO_KEY_LINE)
		{
			AddChar_Element_Line((CXrioData*)p, pArea);
		}
		else if (p->m_strName == RIO_KEY_LINEP)
		{
			AddChar_Element_Linep((CXrioData*)p, pArea);
		}
		else if (p->m_strName == RIO_KEY_ARC)
		{
			AddChar_Element_Arc((CXrioData*)p, pArea);
		}
		else if (p->m_strName == RIO_KEY_ARCP)
		{
			AddChar_Element_Arcp((CXrioData*)p, pArea);
		}
		else if (p->m_strName == RIO_KEY_AUTOCLOSE)
		{
			pChar->m_nAutoClose = rio_get_key_value_yes_no(((CXrioData*)p)->GetAttr(0));
		}
		else if (p->m_strName == RIO_KEY_INVERT)
		{
		}
		else
		{
			ASSERT (FALSE);
		}
	}
}

/*
BEGIN MHOSHAPE
	ANGLE    75
	OFFSET    0
	REACH    6
	INVERT    NO
END MHOSHAPE
*/
void CXrioTextFileToAtsCharTool::AddChar_Zone_Mho(CXrioGroup *pGroup, CCharacteristic *pChar)
{
	CCharacterArea *pArea = pChar->GetCharacterArea();
	CCharElementMho *pMho = new CCharElementMho();
	pArea->AddNewChild(pMho);

	pGroup->GetData(RIO_KEY_ANGLE, pMho->m_strAngle);
	pGroup->GetData(RIO_KEY_OFFSET, pMho->m_strOffset);
	pGroup->GetData(RIO_KEY_REACH, pMho->m_strForwardReach);
}

/*
BEGIN LENSTOMATOSHAPE
	ANGLE    75
	OFFSET    5
	REACH    10
	INVERT    NO
	WIDTH    10
END LENSTOMATOSHAPE
*/
void CXrioTextFileToAtsCharTool::AddChar_Zone_Lens(CXrioGroup *pGroup, CCharacteristic *pChar)
{
	CCharacterArea *pArea = pChar->GetCharacterArea();
	CCharElementLens *pLens = new CCharElementLens();
	pArea->AddNewChild(pLens);

	pGroup->GetData(RIO_KEY_ANGLE, pLens->m_strAngle);
	pGroup->GetData(RIO_KEY_OFFSET, pLens->m_strOffset);
	pGroup->GetData(RIO_KEY_REACH, pLens->m_strForwardReach);
	pGroup->GetData(RIO_KEY_WIDTH, pLens->m_strWidth);
}

void CXrioTextFileToAtsCharTool::AddChar_Zone_TripChar(CXrioGroup *pGroup, CCharacteristic *pChar)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *p = NULL;
	CCharacterArea *pArea = pChar->GetCharacterArea();
	CCharElementLined *pLined = NULL;
	CCharElementLined *pLined1 = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pGroup->GetNext(pos);
		ASSERT (p->GetClassID() == XRIOCLASSID_RIO_DATA);

		if (p->m_strName == RIO_KEY_START)
		{
			pLined = AddChar_Element_Start((CXrioData*)p, pArea);
			pLined1 = pLined;
		}
		else if (p->m_strName == RIO_KEY_LINE)
		{
			pLined = AddChar_Element_Line((CXrioData*)p, pArea, pLined);
		}
		else if (p->m_strName == RIO_KEY_STOP)
		{
			pLined = AddChar_Element_Stop((CXrioData*)p, pArea, pLined);
		}
		else if (p->m_strName == RIO_KEY_CLOSE)
		{//曲线封闭：此处不知道是否理解正确
			pLined->m_strXe = pLined1->m_strXb;
			pLined->m_strYe = pLined1->m_strYb;
		}
		else
		{
			ASSERT (FALSE);
		}
	}
}

/*
LINE    0.1, 0, -73.5, LEFT
*/
CCharElement* CXrioTextFileToAtsCharTool::AddChar_Element_Line(CXrioData *pData, CCharacterArea *pArea)
{
	ASSERT (pData->GetCount() == 4);

	CCharElementLine *pLine = new CCharElementLine();
	pArea->AddNewChild(pLine);

	pData->GetAttr(0, pLine->m_strX);
	pData->GetAttr(1, pLine->m_strY);
	pData->GetAttr(2, pLine->m_strAngle);
	pData->GetAttr(3, pLine->m_strDir);

	return pLine;
}

/*
LINE    2, 0.62
*/
CCharElementLined* CXrioTextFileToAtsCharTool::AddChar_Element_Line(CXrioData *pData, CCharacterArea *pArea, CCharElementLined *pLinedPrev)
{
	ASSERT (pData->GetCount() == 2);
	ASSERT (pLinedPrev != NULL);

	pData->GetAttr(0, pLinedPrev->m_strXe);
	pData->GetAttr(1, pLinedPrev->m_strYe);

	CCharElementLined *pLined = new CCharElementLined();
	pArea->AddNewChild(pLined);
	pLined->m_strXb = pLinedPrev->m_strXe;
	pLined->m_strYb = pLinedPrev->m_strYe;

	return pLined;
}

/*
LINEP    0, 0, -45, LEFT
*/
CCharElement* CXrioTextFileToAtsCharTool::AddChar_Element_Linep(CXrioData *pData, CCharacterArea *pArea)
{
	CCharElementLinep *pLinep = new CCharElementLinep();
	pArea->AddNewChild(pLinep);

	pData->GetAttr(0, pLinep->m_strZ);
	pData->GetAttr(1, pLinep->m_strPh);
	pData->GetAttr(2, pLinep->m_strAngle);
	pData->GetAttr(3, pLinep->m_strDir);

	return pLinep;
}

/*
ARC    1.15, 0, 1.76, 0, 360, CCW, LEFT
*/
CCharElement* CXrioTextFileToAtsCharTool::AddChar_Element_Arc(CXrioData *pData, CCharacterArea *pArea)
{
	CCharElementArc *pArc = new CCharElementArc();
	pArea->AddNewChild(pArc);

	pData->GetAttr(0, pArc->m_strXCenter);
	pData->GetAttr(1, pArc->m_strYCenter);
	pData->GetAttr(2, pArc->m_strRadius);
	pData->GetAttr(3, pArc->m_strAngleBegin);
	pData->GetAttr(4, pArc->m_strAngleEnd);
	pData->GetAttr(5, pArc->m_strClockwise);
	pData->GetAttr(6, pArc->m_strDir);

	return pArc;
}

/*
ARCP    20.6155, 137.96, 25, -47.7652, -19.0365, CCW, LEFT
*/
CCharElement* CXrioTextFileToAtsCharTool::AddChar_Element_Arcp(CXrioData *pData, CCharacterArea *pArea)
{
	CCharElementArcp *pArcp = new CCharElementArcp();
	pArea->AddNewChild(pArcp);

	pData->GetAttr(0, pArcp->m_strZ);
	pData->GetAttr(1, pArcp->m_strPh);
	pData->GetAttr(2, pArcp->m_strRadius);
	pData->GetAttr(3, pArcp->m_strAngleBegin);
	pData->GetAttr(4, pArcp->m_strAngleEnd);
	pData->GetAttr(5, pArcp->m_strClockwise);
	pData->GetAttr(6, pArcp->m_strDir);

	return pArcp;
}

CCharElementLined* CXrioTextFileToAtsCharTool::AddChar_Element_Start(CXrioData *pData, CCharacterArea *pArea)
{
	CCharElementLined *pLined = new CCharElementLined();
	pArea->AddNewChild(pLined);
	pData->GetAttr(0, pLined->m_strXb);
	pData->GetAttr(1, pLined->m_strYb);

	return pLined;
}

CCharElementLined* CXrioTextFileToAtsCharTool::AddChar_Element_Stop(CXrioData *pData, CCharacterArea *pArea, CCharElementLined *pLinedPrev)
{
	ASSERT (pData->GetCount() == 2);
	ASSERT (pLinedPrev != NULL);

	pData->GetAttr(0, pLinedPrev->m_strXe);
	pData->GetAttr(1, pLinedPrev->m_strYe);

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//Diff
void CXrioTextFileToAtsCharTool::AddChar_DiffBias(CXrioGroup *pGroup)
{
	
}

void CXrioTextFileToAtsCharTool::InitChar_DiffBias(CXrioGroup *pGroup, CCharacteristic *pChar)
{

}

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

BOOL CXrioTextFileToAtsCharTool::ImportCharsFromRioFile(const CString &strRioFile, CDvmDevice *pDvmDevice,CCharacteristicLib *pCharacteristicLib)
{
    CXrioTextFile oXrioTxtFile;

    if (!oXrioTxtFile.ReadXrioTextFile(strRioFile))
    {
        return FALSE;
    }

    pDvmDevice->DeleteAll();

    CDvmLogicDevice *pRioLogicDevice = pDvmDevice->AddNewLogicDevice();
    pRioLogicDevice->SetAttr(_T("name"), XRIO_DEVICE_MODEL_ID_RIO);
    pRioLogicDevice->SetAttr(_T("id"), XRIO_DEVICE_MODEL_ID_RIO);

    pCharacteristicLib->DeleteChildren();

    ParseGroup(&oXrioTxtFile,pRioLogicDevice,pCharacteristicLib);

    return TRUE;
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

void CXrioTextFileToAtsCharTool::ParseGroup(CXrioGroup *pGroup,CDvmLogicDevice *pSrcLogicDevice,CCharacteristicLib *pCharacteristicLib)
{
    if (pGroup->m_strName == XRIO_DEVICE_MODEL_ID_DEVICE)
    {
        CDvmDataset *pCDvmDataset = (CDvmDataset*)pSrcLogicDevice->CreateNewChild(DVMCLASSID_CDVMDATASET);

        pSrcLogicDevice->AddNewChild(pCDvmDataset);//此处必须用AddNewChild

        pCDvmDataset->SetAttr(_T("name"), XRIO_DEVICE_MODEL_ID_DEVICE);
        pCDvmDataset->SetAttr(_T("id"), XRIO_DEVICE_MODEL_ID_DEVICE);

        CStringArray strArrayDataNodes;
        strArrayDataNodes.Add(XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE);
        strArrayDataNodes.Add(XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION);
        strArrayDataNodes.Add(XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES);
        strArrayDataNodes.Add(XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS);
        strArrayDataNodes.Add(XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS);
        strArrayDataNodes.Add(XRIO_DEVICE_MODEL_ID_DEVICE_MISC);

        for(int i = 0; i < strArrayDataNodes.GetCount(); ++i)
        {
            CDvmData *pDvmData = pCDvmDataset->AddNewData();
            pDvmData->SetAttr(_T("name"),strArrayDataNodes.GetAt(i));
            pDvmData->SetAttr(_T("id"),strArrayDataNodes.GetAt(i));
        }

        AddDvm_Device(pGroup,pCDvmDataset);
        return;
    }
    else if (pGroup->m_strName == RIO_KEY_DISTANCE)
    {
        CString strActive = pGroup->GetData(RIO_KEY_ACTIVE);
        if(strActive == RIO_KEY_NO)
        {
            return;
        }
        CCharacterFolder *pNewFolder = new CCharacterFolder();
        pNewFolder->m_strID = XRIO_DEVICE_MODEL_ID_DISTANCE;
        pNewFolder->m_strName = XRIO_DEVICE_MODEL_ID_DISTANCE;
        pCharacteristicLib->AddNewChild(pNewFolder);

        CDvmDataset *pCDvmDataset = pSrcLogicDevice->AddNewDataset();

        pCDvmDataset->SetAttr(_T("name"), XRIO_DEVICE_MODEL_ID_DISTANCE);
        pCDvmDataset->SetAttr(_T("id"), XRIO_DEVICE_MODEL_ID_DISTANCE);
        pCDvmDataset->m_strDataType = XRIO_DEVICE_MODEL_DATA_TYPE_DISTANCE;

        POS pos = pGroup->GetHeadPosition();
        CExBaseObject *p = NULL;

        while (pos != NULL)
        {
            p = pGroup->GetNext(pos);

            if(p->GetClassID() == XRIOCLASSID_RIO_GROUP && p->m_strName == RIO_KEY_ZONE)
            {
                CCharacteristic *pCharacteristicNew = new CCharacteristic();
                pCharacteristicNew->m_strID = XRIO_DEVICE_MODEL_ID_DISTANCE;
                pCharacteristicNew->m_strName = XRIO_DEVICE_MODEL_ID_DISTANCE;
                pCharacteristicNew->m_strAxis = "cartes";
                pNewFolder->AddNewChild(pCharacteristicNew);
                InitChar_Zone((CXrioGroup*)p, pCharacteristicNew);
            }
        }
        return;
    }
    else if (pGroup->m_strName == RIO_KEY_DIFFERENTIAL)
    {
        CString strActive = pGroup->GetData(RIO_KEY_ACTIVE);
        if(strActive == RIO_KEY_NO)
        {
            return;
        }
        CCharacterFolder *pNewFolder = new CCharacterFolder();
        pNewFolder->m_strID = XRIO_DEVICE_MODEL_ID_DIFFERENTIAL;
        pNewFolder->m_strName = XRIO_DEVICE_MODEL_ID_DIFFERENTIAL;
        pCharacteristicLib->AddNewChild(pNewFolder);

        CDvmDataset *pCDvmDataset = pSrcLogicDevice->AddNewDataset();

        pCDvmDataset->SetAttr(_T("name"), XRIO_DEVICE_MODEL_ID_DIFFERENTIAL);
        pCDvmDataset->SetAttr(_T("id"), XRIO_DEVICE_MODEL_ID_DIFFERENTIAL);
        pCDvmDataset->m_strDataType = XRIO_DEVICE_MODEL_DATA_TYPE_DIFFERENTIAL;

        POS pos = pGroup->GetHeadPosition();
        CExBaseObject *p = NULL;

        while (pos != NULL)
        {
            p = pGroup->GetNext(pos);

            if (p->GetClassID() == XRIOCLASSID_RIO_GROUP && p->m_strName == RIO_KEY_DIFFBIAS)
            {
                CCharacteristic *pCharacteristicNew = new CCharacteristic();
                pCharacteristicNew->m_strID = XRIO_DEVICE_MODEL_ID_DIFFERENTIAL;
                pCharacteristicNew->m_strName = XRIO_DEVICE_MODEL_ID_DIFFERENTIAL;
                pCharacteristicNew->m_strAxis = "cartes";
                pNewFolder->AddNewChild(pCharacteristicNew);
                InitChar_DiffBias((CXrioGroup*)p, pCharacteristicNew);
            }
        }
        return;
    }
    else if (pGroup->m_strName == RIO_KEY_OVERCURRENT)
    {
        CString strActive = pGroup->GetData(RIO_KEY_ACTIVE);
        if(strActive == RIO_KEY_NO)
        {
            return;
        }

        CCharacterFolder *pNewFolder = new CCharacterFolder();
        pNewFolder->m_strID = XRIO_DEVICE_MODEL_ID_OVERCURRENT;
        pNewFolder->m_strName = XRIO_DEVICE_MODEL_ID_OVERCURRENT;
        pCharacteristicLib->AddNewChild(pNewFolder);

        CDvmDataset *pCDvmDataset = pSrcLogicDevice->AddNewDataset();

        pCDvmDataset->SetAttr(_T("name"), XRIO_DEVICE_MODEL_ID_OVERCURRENT);
        pCDvmDataset->SetAttr(_T("id"), XRIO_DEVICE_MODEL_ID_OVERCURRENT);
        pCDvmDataset->m_strDataType = XRIO_DEVICE_MODEL_DATA_TYPE_OVERCURRENT;

        POS pos = pGroup->GetHeadPosition();
        CExBaseObject *p = NULL;

        while (pos != NULL)
        {
            p = pGroup->GetNext(pos);

            if (p->GetClassID() == XRIOCLASSID_RIO_GROUP && p->m_strName == RIO_KEY_GROUP)
            {
                InitChar_Overcurrent((CXrioGroup*)p, pNewFolder);
            }
        }
        return;
    }

    POS pos = pGroup->GetHeadPosition();
    CExBaseObject *p = NULL;

    while (pos != NULL)
    {
        p = pGroup->GetNext(pos);

        if (p->GetClassID() == XRIOCLASSID_RIO_GROUP)
        {
            ParseGroup((CXrioGroup*)p,pSrcLogicDevice,pCharacteristicLib);
        }
    }
}

void CXrioTextFileToAtsCharTool::AddDvm_Device(CXrioGroup *pGroup, CDvmDataset *pCDvmDataset)
{
    if (pGroup->m_strName == XRIO_DEVICE_MODEL_ID_DEVICE)
    {
        POS pos = pGroup->GetHeadPosition();
        CExBaseObject *p = NULL;

        while (pos!= NULL)
        {
            p = (CExBaseObject *)pGroup->GetNext(pos);
            p->m_strName.Replace(_T('-'), _T('_'));//替换-为_
            //            CDvmData* pChildData = pCDvmDataset->AddNewData(p->m_strName, p->m_strName, _T(""), ((CXrioData*)p)->GetAttr(0));
            if(p->m_strName == _T("NAME") || p->m_strName == XRIO_DEVICE_MODEL_ID_MANUFACTURER ||
                    p->m_strName == XRIO_DEVICE_MODEL_ID_DEVICE_TYPE || p->m_strName == XRIO_DEVICE_MODEL_ID_SERIALNR ||
                    p->m_strName == XRIO_DEVICE_MODEL_ID_ADDITIONAL_INFO2)
            {
                AddDvm_Value(p,pCDvmDataset,XRIO_DEVICE_MODEL_ID_DEVICE_NAMEPLATE);
            }
            else if(p->m_strName == XRIO_DEVICE_MODEL_ID_DEVICE_ADDRESS || p->m_strName == XRIO_DEVICE_MODEL_ID_SUBSTATION ||
                    p->m_strName == XRIO_DEVICE_MODEL_ID_SUBSTATION_ADDRESS || p->m_strName == XRIO_DEVICE_MODEL_ID_BAY ||
                    p->m_strName == XRIO_DEVICE_MODEL_ID_BAY_ADDRESS || p->m_strName == XRIO_DEVICE_MODEL_ID_PROTECTED_OBJECT_NAME)
            {
                AddDvm_Value(p,pCDvmDataset,XRIO_DEVICE_MODEL_ID_DEVICE_LOCATION);
            }
            else if(p->m_strName == XRIO_DEVICE_MODEL_ID_PHASES || p->m_strName == XRIO_DEVICE_MODEL_ID_FNOM ||
                    p->m_strName == XRIO_DEVICE_MODEL_ID_VNOM || p->m_strName == XRIO_DEVICE_MODEL_ID_VPRIM_LL ||
                    p->m_strName == XRIO_DEVICE_MODEL_ID_INOM || p->m_strName == XRIO_DEVICE_MODEL_ID_IPRIM)
            {
                AddDvm_Value(p,pCDvmDataset,XRIO_DEVICE_MODEL_ID_DEVICE_NOMINALVALUES);
            }
            else if(p->m_strName == XRIO_DEVICE_MODEL_ID_VLNVN || p->m_strName == XRIO_DEVICE_MODEL_ID_ININOM)
            {
                AddDvm_Value(p,pCDvmDataset,XRIO_DEVICE_MODEL_ID_DEVICE_RESIDUALFACTORS);
            }
            else if(p->m_strName == XRIO_DEVICE_MODEL_ID_VMAX_LL || p->m_strName == XRIO_DEVICE_MODEL_ID_IMAX)
            {
                AddDvm_Value(p,pCDvmDataset,XRIO_DEVICE_MODEL_ID_DEVICE_LIMITS);
            }
            else if(p->m_strName == XRIO_DEVICE_MODEL_ID_DEBOUNCETIME || p->m_strName == XRIO_DEVICE_MODEL_ID_DEGLITCHTIME ||
                    p->m_strName == XRIO_DEVICE_MODEL_ID_OVERLOADSUPTIME)
            {
                AddDvm_Value(p,pCDvmDataset,XRIO_DEVICE_MODEL_ID_DEVICE_MISC);
            }
        }
    }
}

void CXrioTextFileToAtsCharTool::AddDvm_Value(CExBaseObject *p,CDvmDataset *pCDvmDataset,const CString& strDataID)
{
    CDvmData *pDvmData = (CDvmData*)pCDvmDataset->FindByID(strDataID);
    if(pDvmData != NULL)
    {
        CDvmValue *pDvmValue = pDvmData->AddNewValue();
        if(p->m_strName == _T("NAME"))
        {
            pDvmValue->m_strName = XRIO_DEVICE_MODEL_ID_DEVICE_MODEL;
            pDvmValue->m_strID = pDvmData->m_strID + CString("$") + CString(XRIO_DEVICE_MODEL_ID_DEVICE_MODEL);
        }
        else
        {
            pDvmValue->m_strName = p->m_strName;
            pDvmValue->m_strID = pDvmData->m_strID + CString("$") + p->m_strName;
        }
        pDvmValue->m_strDataType = _T("");
        pDvmValue->m_strValue = ((CXrioData*)p)->GetAttr(0);
    }
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

    while (pos!= NULL)
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
    //补充函数内容,原有文件中该函数为空
    POS pos = pGroup->GetHeadPosition();
    CExBaseObject *p = NULL;
    CDvmData *pCharAttrs = pChar->GetAttrs(TRUE);

    while (pos != NULL)
    {
        p = (CExBaseObject *)pGroup->GetNext(pos);
        if (p->GetClassID() == XRIOCLASSID_RIO_GROUP)
        {//Xrio Group Object
            AddChar_DiffBias_Group((CXrioGroup*)p ,pChar);
        }
        else
        {//Xrio Data Object
            InitChar_DiffBiasAttrs((CXrioData*)p, pChar, pCharAttrs);
        }
    }
}

void CXrioTextFileToAtsCharTool::InitChar_DiffBiasAttrs(CXrioData *pData, CCharacteristic *pChar, CDvmData *pCharAttrs)
{
    CXrioAttr *pAttr = (CXrioAttr*)pData->GetHead();

    if (pAttr == NULL)
    {
        return;
    }

    pCharAttrs->AddValue(pData->m_strName, pAttr->m_strName);

    if (/*pData->m_strName == RIO_KEY_OBJECT_TYPE || */pData->m_strName == RIO_KEY_NAME)
    {
        pChar->m_strName = pAttr->m_strName;
        pChar->m_strID = pAttr->m_strName;
    }
}

void CXrioTextFileToAtsCharTool::AddChar_DiffBias_Group(CXrioGroup *pGroup, CCharacteristic *pChar)
{
    if (pGroup->m_strName == RIO_KEY_TRIPCHAR)
    {
        AddChar_Zone_TripChar(pGroup, pChar);
    }
}

void CXrioTextFileToAtsCharTool::InitChar_Overcurrent(CXrioGroup *pGroup, CCharacterFolder *pNewFolder)
{
    POS pos = pGroup->GetHeadPosition();
    CExBaseObject *p = NULL;

    while (pos != NULL)
    {
        p = (CExBaseObject *)pGroup->GetNext(pos);

        if (p->GetClassID() == XRIOCLASSID_RIO_GROUP)
        {//Xrio Group Object
            AddChar_Overcurrent_Group((CXrioGroup*)p ,pNewFolder);
        }
    }
}

void CXrioTextFileToAtsCharTool::AddChar_Overcurrent_Group(CXrioGroup *pGroup, CCharacterFolder *pNewFolder)
{
    if (pGroup->m_strName == RIO_KEY_UNIT)
    {
        CCharacteristic *pCharacteristicNew = new CCharacteristic();
        pCharacteristicNew->m_strID = XRIO_DEVICE_MODEL_ID_OVERCURRENT;
        pCharacteristicNew->m_strName = XRIO_DEVICE_MODEL_ID_OVERCURRENT;
        pCharacteristicNew->m_strAxis = "logarithm";
        pNewFolder->AddNewChild(pCharacteristicNew);
        AddChar_Overcurrent_Unit(pGroup, pCharacteristicNew);
    }
}

void CXrioTextFileToAtsCharTool::AddChar_Overcurrent_Unit(CXrioGroup *pGroup, CCharacteristic *pChar)
{
    POS pos = pGroup->GetHeadPosition();
    CExBaseObject *p = NULL;
    CCharacterArea *pArea = pChar->GetCharacterArea();
    CString m_sIPickUp;
    CString m_sTIndex;
    CString m_sActive;

    while (pos != NULL)
    {
        p = (CExBaseObject *)pGroup->GetNext(pos);
        ASSERT (p->GetClassID() == XRIOCLASSID_RIO_DATA);

        if (p->m_strName == RIO_KEY_NAME)
        {
            pChar->m_strName = ((CXrioData*)p)->GetAttr(0);
        }
        else if (p->m_strName == RIO_KEY_ACTIVE)
        {
            m_sActive = ((CXrioData*)p)->GetAttr(0);
            //AddChar_Element_Linep((CXrioData*)p, pArea);
        }
        else if (p->m_strName == RIO_KEY_IPICKUP)
        {
            m_sIPickUp = ((CXrioData*)p)->GetAttr(0);
        }
        else if (p->m_strName == RIO_KEY_TINDEX)
        {
            m_sTIndex = ((CXrioData*)p)->GetAttr(0);
        }
        else if (p->m_strName == RIO_KEY_PREDEFCHAR)
        {
            if(((CXrioData*)p)->GetAttr(0) == "INVERSE")
            {
                AddChar_Element_Invers(m_sTIndex, pArea);
            }
            else if(((CXrioData*)p)->GetAttr(0) == "DEFTIME")
            {
                AddChar_Element_DefTime(m_sTIndex, pArea);
            }
        }
        else if(p->m_strName == RIO_KEY_CHAR)
        {
            AddChar_Element_Invers(m_sTIndex,(CXrioData*)p,pArea);
        }
        else
        {
            ASSERT (FALSE);
        }
    }
}

CCharElement *CXrioTextFileToAtsCharTool::AddChar_Element_Invers(CString m_sTIndex, CCharacterArea *pArea)
{
    CCharElementIEEE *pIEEE = new CCharElementIEEE();
    pArea->AddNewChild(pIEEE);

    pIEEE->m_strTp = m_sTIndex;
    pIEEE->m_strA = "0.14";
    pIEEE->m_strB = "0.00";
    pIEEE->m_strP = "0.02";
    pIEEE->m_strQ = "1.00";
    pIEEE->m_strK1 = "0.00";
    pIEEE->m_strK2 = "0.00";

    return pIEEE;
}

CCharElement *CXrioTextFileToAtsCharTool::AddChar_Element_DefTime(CString m_sTIndex, CCharacterArea *pArea)
{
    CCharElementIEEE *pIEEE = new CCharElementIEEE();
    pArea->AddNewChild(pIEEE);

    pIEEE->m_strTp = m_sTIndex;
    pIEEE->m_strA = "1.00";
    pIEEE->m_strB = "0.00";
    pIEEE->m_strP = "0.00";
    pIEEE->m_strQ = "0.00";
    pIEEE->m_strK1 = "0.00";
    pIEEE->m_strK2 = "0.00";

    return pIEEE;
}

CCharElement *CXrioTextFileToAtsCharTool::AddChar_Element_Invers(CString m_sTIndex,CXrioData *pData, CCharacterArea *pArea)
{
    ASSERT (pData->GetCount() == 7);
    CCharElementIEEE *pIEEE = new CCharElementIEEE();
    pArea->AddNewChild(pIEEE);

    CCharacteristic *pCharacteristic = (CCharacteristic*)pArea->GetParent();
    pData->GetAttr(0, pCharacteristic->m_strID);

    pIEEE->m_strTp = m_sTIndex;
    pData->GetAttr(1, pIEEE->m_strA);
    pData->GetAttr(2, pIEEE->m_strB);
    pData->GetAttr(3, pIEEE->m_strP);
    pData->GetAttr(4, pIEEE->m_strQ);
    pData->GetAttr(5, pIEEE->m_strK1);
    pData->GetAttr(6, pIEEE->m_strK2);

    return pIEEE;
}

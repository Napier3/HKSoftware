#include "XrioToCharacterTool.h"
#include "stdafx.h"
// CXrioToCharacterTool

CXrioToCharacterTool::CXrioToCharacterTool()
{

}

CXrioToCharacterTool::~CXrioToCharacterTool()
{

}


BOOL CXrioToCharacterTool::XrioToCharacter(CXrio* pXrio, CCharacteristicLib *pCharacterLib)
{
    pCharacterLib->DeleteAll();
    CXrioRio *pXrioRio = pXrio->GetXrioRio();
    if(pXrioRio == NULL)
    {
        return FALSE;
    }
    POS RioPos = pXrioRio->GetHeadPosition();
    CExBaseObject *pObj= NULL;
    while(RioPos)
    {
        pObj = pXrio->GetNext(RioPos);
        if(pObj->GetClassID() == XRIOCLASSID_DISTANCE)
        {
            ParseXrioDistance(pObj, pCharacterLib);
        }
        else if(pObj->GetClassID() == XRIOCLASSID_DIFFERENTIAL)
        {
            ParseXrioDifferential(pXrio, pObj, pCharacterLib);
        }
        else if(pObj->GetClassID() == XRIOCLASSID_OVERCURRENT)
        {
            ParseRioOverCurrent(pObj, pCharacterLib);
        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::UpdateCharacterByXrioFile(CXrio *pXrio, CCharacteristicLib *pCharacterLib)
{
    CCharacteristicLib pCharacterLibTemp;
    XrioToCharacter(pXrio,&pCharacterLibTemp);
    CExBaseObject *pObj = NULL;
    CExBaseObject *pFind = NULL;
    POS pos = pCharacterLibTemp.GetHeadPosition();

    while (pos != NULL)
    {
        pObj = pCharacterLibTemp.GetNext(pos);
        ASSERT(pObj != NULL);
        pFind = (CExBaseObject*)pCharacterLib->FindByID(pObj->m_strID);
        if (pFind != NULL)
        {
            ((CCharacterFolder*)pFind)->DeleteAll();
            ((CCharacterFolder*)pFind)->Append((CCharacterFolder*)pObj);
        }
    }
    pCharacterLibTemp.RemoveAll();
    return TRUE;
}

void CXrioToCharacterTool::GetMultiDiffExpr(CCharElementExpr *pCharElementExpr)
{
    //"(2*BP+2*sqrt(BP^2-(1-2*S2^2)*(BP^2*(1+2*S2^2-4*S1^2)-2*P^2)))/(2*(1-2*S2^2))";
    double fBP,fS2,fS1,fP,fX;
    CCharacteristic *pCharTemp = (CCharacteristic*)pCharElementExpr->GetAncestor(CHARCLASSID_CCHARACTERISTIC);
    ASSERT( pCharTemp != NULL );
    CCharInterface* pCharInterface = pCharTemp->GetCharInterface();
    CCharInterfaceVariable *pVariable = NULL;
    for(int i = 0 ; i < pCharElementExpr->m_strArrayExprRefIDs.GetCount();++i)
    {
//        if(pCharElementExpr->m_strArrayExprRefIDs.GetAt(i).GetAt(0) != _T('X'))
//        {
            pVariable = (CCharInterfaceVariable*)pCharInterface->FindByID(pCharElementExpr->m_strArrayExprRefIDs.GetAt(i));
            if(pVariable != NULL)
            {
                if(pVariable->m_strID == _T("BP"))
                {
                    fBP = pVariable->m_strValue.toDouble();
                }
                else if(pVariable->m_strID == _T("S1"))
                {
                    fS1 = pVariable->m_strValue.toDouble();
                }
                else if(pVariable->m_strID == _T("S2"))
                {
                    fS2 = pVariable->m_strValue.toDouble();
                }
                else if(pVariable->m_strID == _T("P"))
                {
                    fP = pVariable->m_strValue.toDouble();
                }
                else if(pVariable->m_strID.GetAt(0) == _T('X'))
                {
                    fX = pVariable->m_strValue.toDouble();
                }
            }
//        }
    }
    double fIL = (2*fBP+2*sqrt(pow(fBP,2)-(1-2*pow(fS2,2))*(pow(fBP,2)*(1+2*pow(fS2,2)-4*pow(fS1,2))-2*pow(fP,2))))/(2*(1-2*pow(fS2,2)));
//    qDebug()<<fIL;
//    qDebug()<<fBP;
    if(/*pCharElementExpr->m_strXb.toDouble()*/fX <= fBP)
    {
        pCharElementExpr->m_strExpr = _T("ABS(X-((2*X-2*SQRT(X^2-(1-2*(S1)^2)*(X^2-2*S1^2*X^2-2*P^2)))/(2*(1-2*(S1)^2))))");
    }
    else if((/*pCharElementExpr->m_strXb.toDouble() */fX > fBP) && (/*pCharElementExpr->m_strXb.toDouble()*/fX <= fIL))
    {
        pCharElementExpr->m_strExpr = _T("ABS(X-((2*X-2*SQRT(X^2-(1-2*(S1)^2)*(X^2-2*S2^2*X^2-2*P^2-2*BP^2*(S1^2-S2^2))))/(2*(1-2*(S1)^2))))");
    }
    else if(/*pCharElementExpr->m_strXb.toDouble()*/fX > fIL)
    {
        pCharElementExpr->m_strExpr = _T("ABS(X-((2*X-2*SQRT(X^2-(1-2*(S2)^2)*(X^2-2*S2^2*X^2-2*P^2-4*BP^2*(S1^2-S2^2))))/(2*(1-2*(S2)^2))))");
    }
}

CXrioCustomParameter *CXrioToCharacterTool::FindRefByIDPath(const CString &strings,CXrioCustom* pXrioCustom)
{
    CExBaseObject* target = NULL;
    CExBaseObject* tmpTarget = NULL;
    CStringArray strArray;
    SplitCStringToArray(strings,strArray);
    if(strArray.GetAt(0) == _T("CUSTOM"))
    {
        for (int i = 1; i < strArray.GetSize(); ++i)
        {
            if(i == 1)
            {
                tmpTarget = pXrioCustom->FindByID(strArray.GetAt(i));
                if(tmpTarget != NULL)
                {
                    target = tmpTarget;
                }
                continue;
            }
            tmpTarget = ((CXrioCustomBlock*)target)->FindByID(strArray.GetAt(i));
            if(tmpTarget != NULL)
            {
                target = tmpTarget;
            }
        }
    }
    return (CXrioCustomParameter*)target;
}

BOOL CXrioToCharacterTool::InitAttr(CString &strDesAttrID, const CString &strDesAttrValue, const CString &strSrcAttrValue)
{
    if(strSrcAttrValue.isEmpty())
    {
        strDesAttrID = strDesAttrValue;
    }
    else
    {
        strDesAttrID = strSrcAttrValue;
    }
    return TRUE;
}

CXrioToCharacterTool::CurveType CXrioToCharacterTool::CheckValueFormula(CXrio* pXrio,const CString& strValueFormula,CXrioValueRefList *pValueRefList)
{
    CXrioCustom *pXrioCustom = pXrio->GetXrioCustom();
    CExBaseObject* pObj = NULL;
    CXrioRefParam *pRefParam = NULL;
    CXrioRefEnum *pRefEnum = NULL;
    if(pValueRefList->GetCount() == 1)
    {
        CXrioRefParam *pXrioRefParam = (CXrioRefParam*)pValueRefList->FindByClassID(XRIOCLASSID_REFPARAM);
        if(pXrioRefParam->m_strRefID == strValueFormula) //节点数量是1并且和公式相等，设置为线段。
        {
            return Lined;
        }
        else
        {
            CXrioCustomParameter *pCustomParameter = FindRefByIDPath(pXrioRefParam->m_strName,pXrioCustom);
            if(pCustomParameter != NULL)//节点数量是1并且和公式不相等，寻址参数中存在X，设置为寻址表达式。
            {
                CXrioValueRefList *pParaValueRefList = (CXrioValueRefList*)pCustomParameter->FindByClassID(XRIOCLASSID_VALUEREFLIST);
                POS pos = pParaValueRefList->GetHeadPosition();
                while(pos)
                {
                    pObj = pParaValueRefList->GetNext(pos);
                    if(pObj->GetClassID() == XRIOCLASSID_REFPARAM)
                    {
                        pRefParam = (CXrioRefParam*)pObj;
                        if (pRefParam->m_strRefID.GetAt(0) == _T('X'))
                        {
                            return AdrExpr;
                        }
                    }
                    else if(pObj->GetClassID() == XRIOCLASSID_REFENUM)
                    {
                        pRefEnum = (CXrioRefEnum*)pObj;
                        if (pRefParam->m_strRefID.GetAt(0) == _T('X'))
                        {
                            return AdrExpr;
                        }
                    }
                }

            }
            return Lined; //节点数量是1并且和公式不相等，寻址参数中不存在X，设置为线段。
        }
    }
    else
    {
        POS pos = pValueRefList->GetHeadPosition();
        while(pos)
        {
            pObj = pValueRefList->GetNext(pos);
            if(pObj->GetClassID() == XRIOCLASSID_REFPARAM)
            {
                pRefParam = (CXrioRefParam*)pObj;
                if (pRefParam->m_strRefID.GetAt(0) == _T('X'))//字符串以大写'X'开头，证明存在了X变量，这样的情况设置为非寻址表达式
                {
                    return NAdrExpr;
                }
            }
            else if(pObj->GetClassID() == XRIOCLASSID_REFENUM)
            {
                pRefEnum = (CXrioRefEnum*)pObj;
                if (pRefParam->m_strRefID.GetAt(0) == _T('X'))//字符串以大写'X'开头，证明存在了X变量，这样的情况设置为非寻址表达式
                {
                    return NAdrExpr;
                }
            }
        }
        return Lined; //如果当中不存在X变量，这样的情况设置为线段
    }
}

BOOL CXrioToCharacterTool::ParseXrioDistance(CExBaseObject *pObj, CCharacteristicLib *pCharacterLib)
{
    CRioDistance *pRioDistance = NULL;
    //floder节点DISTANCE
    CCharacterFolder *pCharacterFolder= new CCharacterFolder();
    pCharacterLib->AddNewChild(pCharacterFolder);
    pRioDistance = (CRioDistance*)pObj;
    InitAttr(pCharacterFolder->m_strName,XRIO_DEVICE_MODEL_ID_DISTANCE,pRioDistance->m_strName);
    InitAttr(pCharacterFolder->m_strID,XRIO_DEVICE_MODEL_ID_DISTANCE,pRioDistance->m_strID);
    pObj = pRioDistance->FindByClassID(XRIOCLASSID_PROTECTIONDEVICE);
    if(pObj != NULL)
    {
        ParseDistanceZone(pObj,pCharacterFolder);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CXrioToCharacterTool::ParseXrioDifferential(CXrio* pXrio, CExBaseObject *pObj, CCharacteristicLib *pCharacterLib)
{
    CRioDifferential *pDifferential = NULL;
    //floder节点DIFFERENTIAL
    CCharacterFolder *pCharacterFolder= new CCharacterFolder();
    pCharacterLib->AddNewChild(pCharacterFolder);
    InitAttr(pCharacterFolder->m_strName,XRIO_DEVICE_MODEL_ID_DIFFERENTIAL,pObj->m_strName);
    InitAttr(pCharacterFolder->m_strID,XRIO_DEVICE_MODEL_ID_DIFFERENTIAL,pObj->m_strID);
    pDifferential = (CRioDifferential*)pObj;
    pObj = pDifferential->FindByClassID(XRIOCLASSID_DIFFBIAS);
    if(pObj != NULL)
    {
        ParseDifferentialDiffBias(pXrio,pObj,pCharacterFolder);
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToCharacterTool::ParseDifferentialDiffBias(CXrio* pXrio,CExBaseObject *pObj,CCharacterFolder *pCharacterFolder)
{
    CRioDiffBias *pDiffBias = NULL;
    pDiffBias = (CRioDiffBias*)pObj;
    CRioActive *pActive = NULL;
    CRioTripChar *pTripChar = NULL;
    //    //Characteristic节点
    //    CCharacteristic *pCharacteristic= new CCharacteristic();
    //    pCharacterFolder->AddNewChild(pCharacteristic);
    //    pCharacteristic->m_strName=  /*_T("多边形特性");*/pDiffBias->m_strName;
    //    pCharacteristic->m_strID=  /*_T("多边形特性");*/pDiffBias->m_strID;
    //    pCharacteristic->m_strAxis=  _T("cartes");
    //    //character-area节点
    //    CCharacterArea *pCharacterArea= new CCharacterArea();
    //    pCharacteristic->AddNewChild(pCharacterArea);
    //    //char-interface节点
    //    CCharInterface *pCharInterface= new CCharInterface();
    //    pCharacteristic->AddNewChild(pCharInterface);

    //    pActive = (CRioActive*)pDiffBias->FindByClassID(XRIOCLASSID_ACTIVE);
    //    if(pActive == NULL)
    //    {
    //        return FALSE;
    //    }

    //    if(pActive->m_strValue == _T("false"))
    //    {
    //        return FALSE;
    //    }

    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName=  /*_T("多边形特性");*/pDiffBias->m_strName;
    pCharacteristic->m_strID=  /*_T("多边形特性");*/pDiffBias->m_strID;
    pCharacteristic->m_strAxis=  _T("cartes");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea();*/pCharacteristic->GetCharacterArea();
//    pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface();*/pCharacteristic->GetCharInterface();
//    pCharacteristic->AddNewChild(pCharInterface);

    pObj = pDiffBias->FindByClassID(XRIOCLASSID_TRIPCHAR);
    if(pObj != NULL)
    {
        pTripChar = (CRioTripChar*)pObj;
        DeleteINFPoints(pTripChar);//删除X或者Y坐标是INF的点
        POS TripCharPos = pTripChar->GetHeadPosition();
        while(TripCharPos)
        {
            if(TripCharPos == pTripChar->GetTailPosition())
            {
                break;
            }
            pObj = pTripChar->GetNext(TripCharPos);
            if(pObj->GetClassID() == XRIOCLASSID_POINT)
            {
                ParseDifferentialPoint(pXrio,pObj,pCharInterface,pCharacterArea);
            }
            pObj = pTripChar->GetNext(TripCharPos);
            if(pObj->GetClassID() == XRIOCLASSID_POINT)
            {
                ParseDifferentialPoint(pObj,pCharacterArea);
            }
            if(TripCharPos != NULL)
            {
                pTripChar->GetPrev(TripCharPos);
            }
        }
        if(pCharInterface->GetCount() > 0)
        {
            pObj = pCharInterface->FindByID(_T("X"));
            if(pObj == NULL)
            {
                CCharInterfaceVariable *pCharInterfaceVariable= new CCharInterfaceVariable();
                pCharInterface->AddNewChild(pCharInterfaceVariable);
                pCharInterfaceVariable->m_strName = _T("X");
                pCharInterfaceVariable->m_strID = _T("X");
            }
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToCharacterTool::ParseDifferentialPoint(CXrio* pXrio,CExBaseObject *pObj,CCharInterface *pCharInterface,CCharacterArea *pCharacterArea)
{
    CXrioRioConverter *pConverter = NULL;
    CXrioScript* pScript = NULL;
    pConverter = pXrio->GetXrioRioConverter();
    if(pConverter != NULL)
    {
        pScript = (CXrioScript*)pConverter->FindByClassID(XRIOCLASSID_Script);
    }

    CRioDiffPoint *pDiffPoint = NULL;
    CRioPointX *pPointX = NULL;
    CRioPointY *pPointY = NULL;
    CCharElementExpr *pCharElementExpr = NULL;
    CCharElementLined *pCharElementLined = NULL;
    CXrioCustomParameter *pXrioCustomParameter = NULL;
    CXrioRefParam *pXrioRefParam = NULL;
    pDiffPoint = (CRioDiffPoint*)pObj;
    pPointY = (CRioPointY*)pDiffPoint->FindByClassID(XRIOCLASSID_POINT_Y);
    if(pPointY != NULL)
    {
        CXrioValueRefList *pValueRefList = (CXrioValueRefList*)pPointY->FindByClassID(XRIOCLASSID_VALUEREFLIST);
        if(CheckValueFormula(pXrio,pPointY->m_strValueFormula,pValueRefList) == Lined)
        {
            pCharElementLined = new CCharElementLined();
            pCharacterArea->AddNewChild(pCharElementLined);
            pCharElementLined->m_strYb = pPointY->m_strValue;
            //test节点
            for(int i = 1;i < 5; ++i)
            {
                CCharTestLine  *pCharTestLine= new CCharTestLine();
                pCharElementLined->AddNewChild(pCharTestLine);
                pCharTestLine->m_fPos = i;
            }
        }
        else if(CheckValueFormula(pXrio,pPointY->m_strValueFormula,pValueRefList) == AdrExpr)
        {
            pCharElementExpr= new CCharElementExpr();
            pCharacterArea->AddNewChild(pCharElementExpr);
            pCharElementExpr->m_strYb = pPointY->m_strValue;
            if(pScript != NULL)
            {
                pCharElementExpr->m_strScript = pScript->m_strCDATA;
            }

            //test节点
            for(int i = 1;i < 5; ++i)
            {
                CCharTestLine  *pCharTestLine= new CCharTestLine();
                pCharElementExpr->AddNewChild(pCharTestLine);
                pCharTestLine->m_fPos = i;
            }

            pXrioRefParam = (CXrioRefParam*)pValueRefList->FindByClassID(XRIOCLASSID_REFPARAM);
            if(pXrioRefParam != NULL)
            {
                pXrioCustomParameter = FindRefByIDPath(pXrioRefParam->m_strName,pXrio->GetXrioCustom());
                if(pXrioCustomParameter != NULL)
                {
                    int Pos = pXrioCustomParameter->m_strValueFormula.Find(_T("Idiff"));
                    if(Pos != -1)
                    {
                        Pos = pXrioCustomParameter->m_strValueFormula.Find(_T('P'));
                        if(Pos != -1)
                        {
                            pCharElementExpr->m_strExpr = XRIO_CHARACTER_DIFF_EXPR_SECOND;
                        }
                        else
                        {
                            pCharElementExpr->m_strExpr = XRIO_CHARACTER_DIFF_EXPR_FIRST;
                        }
                        pCharElementExpr->m_bIsStdExpr = FALSE;
                    }
                    else
                    {
                        pCharElementExpr->m_strExpr = pXrioCustomParameter->m_strValueFormula;
                        pCharElementExpr->m_bIsStdExpr = TRUE;
                    }
//                    pCharElementExpr->m_strExpr = pXrioCustomParameter->m_strValueFormula;
                    CXrioValueRefList *pValueRefList = (CXrioValueRefList*)pXrioCustomParameter->FindByClassID(XRIOCLASSID_VALUEREFLIST);
                    if(pValueRefList != NULL)
                    {
                        ParseDifferentialPointFormula(pXrio,pValueRefList,pCharInterface,pCharElementExpr);
                    }
                }
            }
        }
        else if(CheckValueFormula(pXrio,pPointY->m_strValueFormula,pValueRefList) == NAdrExpr)
        {
            pCharElementExpr= new CCharElementExpr();
            pCharacterArea->AddNewChild(pCharElementExpr);
            pCharElementExpr->m_strYb = pPointY->m_strValue;
//            pCharElementExpr->m_strExpr = pPointY->m_strValueFormula;
            int Pos = pPointY->m_strValueFormula.Find(_T("Idiff"));
            if(Pos != -1)
            {
                Pos = pPointY->m_strValueFormula.Find(_T('P'));
                if(Pos != -1)
                {
                    pCharElementExpr->m_strExpr = XRIO_CHARACTER_DIFF_EXPR_SECOND;
                }
                else
                {
                    pCharElementExpr->m_strExpr = XRIO_CHARACTER_DIFF_EXPR_FIRST;
                }
                pCharElementExpr->m_bIsStdExpr = FALSE;
            }
            else
            {
                pCharElementExpr->m_strExpr = pPointY->m_strValueFormula;
                pCharElementExpr->m_bIsStdExpr = TRUE;
            }

            if(pScript != NULL)
            {
                pCharElementExpr->m_strScript = pScript->m_strCDATA;
            }

            //test节点
            for(int i = 1;i < 5; ++i)
            {
                CCharTestLine  *pCharTestLine= new CCharTestLine();
                pCharElementExpr->AddNewChild(pCharTestLine);
                pCharTestLine->m_fPos = i;
            }
            ParseDifferentialPointFormula(pXrio,pValueRefList,pCharInterface,pCharElementExpr);
        }
    }
    pPointX= (CRioPointX*)pDiffPoint->FindByClassID(XRIOCLASSID_POINT_X);
    if(pPointX != NULL)
    {
        if(pCharElementExpr != NULL)
        {
            pCharElementExpr->m_strXb = pPointX->m_strValue;
        }
        else if(pCharElementLined != NULL)
        {
            pCharElementLined->m_strXb = pPointX->m_strValue;
        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseDifferentialPoint(CExBaseObject *pObj, CCharacterArea *pCharacterArea)
{
    CRioDiffPoint *pDiffPoint = NULL;
    pDiffPoint = (CRioDiffPoint*)pObj;
    CRioPointX *pPointX = NULL;
    CRioPointY *pPointY = NULL;
    CCharElementExpr *pCharElementExpr = NULL;
    CCharElementLined *pCharElementLined = NULL;
    pObj = pCharacterArea->GetTail();
    if(pObj->GetClassID() == CHARCLASSID_CCHARELEMENTEXPR)
    {
        pCharElementExpr = (CCharElementExpr*)pObj;
        if(XRIO_CHARACTER_DIFF_EXPR_SECOND == pCharElementExpr->m_strExpr)
        {
            GetMultiDiffExpr(pCharElementExpr);
        }
    }
    else if(pObj->GetClassID() == CHARCLASSID_CCHARELEMENTLINED)
    {
        pCharElementLined = (CCharElementLined*)pObj;
    }

    pPointX = (CRioPointX*)pDiffPoint->FindByClassID(XRIOCLASSID_POINT_X);
    if(pPointX != NULL)
    {
        if(pCharElementExpr != NULL)
        {
            pCharElementExpr->m_strXe = pPointX->m_strValue;
        }
        else if(pCharElementLined != NULL)
        {
            pCharElementLined->m_strXe = pPointX->m_strValue;
        }
    }
    pPointY = (CRioPointY*)pDiffPoint->FindByClassID(XRIOCLASSID_POINT_Y);
    if(pPointY != NULL)
    {
        if(pCharElementExpr != NULL)
        {
            pCharElementExpr->m_strYe = pPointY->m_strValue;
        }
        else if(pCharElementLined != NULL)
        {
            pCharElementLined->m_strYe = pPointY->m_strValue;
        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseDifferentialPointFormula(CXrio* pXrio,CXrioValueRefList *pValueRefList,CCharInterface *pCharInterface,CCharElementExpr *pCharElementExpr)
{
    GetCurrExprRefsID(pValueRefList,pCharElementExpr);
    CXrioCustom* pXrioCustom = pXrio->GetXrioCustom();
    CXrioRefParam *pXrioRefParam = NULL;
    CXrioCustomParameter *pXrioCustomParameter = NULL;
    CExBaseObject *pObj = NULL;
    CXrioRefEnum *pRefEnum = NULL;
    POS pos = pValueRefList->GetHeadPosition();
    while(pos)
    {
        pObj = pValueRefList->GetNext(pos);
        if(pObj->GetClassID() == XRIOCLASSID_REFPARAM)
        {
            pXrioRefParam = (CXrioRefParam*)pObj;
            pObj = pCharInterface->FindByID(pXrioRefParam->m_strRefID);
            if(pObj != NULL)
            {
                continue;
            }
            CCharInterfaceVariable *pCharInterfaceVariable= new CCharInterfaceVariable();
            pCharInterface->AddNewChild(pCharInterfaceVariable);
            pCharInterfaceVariable->m_strName = pXrioRefParam->m_strRefID;
            pCharInterfaceVariable->m_strID = pXrioRefParam->m_strRefID;
            pXrioCustomParameter = FindRefByIDPath(pXrioRefParam->m_strName,pXrioCustom);
            if(pXrioCustomParameter != NULL)
            {
                pCharInterfaceVariable->m_strValue = pXrioCustomParameter->m_strValue;
            }
        }
        else if(pObj->GetClassID() == XRIOCLASSID_REFENUM)
        {
            pRefEnum = (CXrioRefEnum*)pObj;
            pObj = pCharInterface->FindByID(pXrioRefParam->m_strRefID);
            if(pObj != NULL)
            {
                continue;
            }
            CCharInterfaceVariable *pCharInterfaceVariable= new CCharInterfaceVariable();
            pCharInterface->AddNewChild(pCharInterfaceVariable);
            pCharInterfaceVariable->m_strName = pRefEnum->m_strRefID;
            pCharInterfaceVariable->m_strID = pRefEnum->m_strRefID;
            pXrioCustomParameter = FindRefByIDPath(pRefEnum->m_strName,pXrioCustom);
            if(pXrioCustomParameter != NULL)
            {
                pCharInterfaceVariable->m_strValue = pXrioCustomParameter->m_strValue;
            }
        }
    }
    return TRUE;
}

void CXrioToCharacterTool::GetCurrExprRefsID(CXrioValueRefList *pValueRefList, CCharElementExpr *pCharElementExpr)
{
    long nCount = pValueRefList->GetCount();
//    DiffExprRefsSetptr pDiffExprRefsSet = new DiffExprRefsSet[nCount];
    POS pos = pValueRefList->GetHeadPosition();
    int Position;
    CExBaseObject *pObj = NULL;
    CXrioRefParam *pRefParam = NULL;
    CXrioRefEnum *pRefEnum = NULL;
    for(int i = 0; i < nCount ;++i)
    {
        pObj = pValueRefList->GetNext(pos);
        if(pObj->GetClassID() == XRIOCLASSID_REFPARAM)
        {
            pRefParam = (CXrioRefParam*)pObj;
            pCharElementExpr->m_strArrayExprRefIDs.Add(pRefParam->m_strRefID);
//            Position = pCharElementExpr->m_strExpr.Find(pRefParam->m_strRefID);
//            if(Position != -1)
//            {
//                pDiffExprRefsSet[i].DiffExprRef = pRefParam->m_strRefID;
//                pDiffExprRefsSet[i].Position = Position;
//            }
        }
        else if(pObj->GetClassID() == XRIOCLASSID_REFENUM)
        {
            pRefEnum = (CXrioRefEnum*)pObj;
            pCharElementExpr->m_strArrayExprRefIDs.Add(pRefEnum->m_strRefID);
//            Position = pCharElementExpr->m_strExpr.Find(pRefEnum->m_strRefID);
//            if(Position != -1)
//            {
//                pDiffExprRefsSet[i].DiffExprRef = pRefEnum->m_strRefID;
//                pDiffExprRefsSet[i].Position = Position;
//            }
        }
    }

//    std::sort(pDiffExprRefsSet, pDiffExprRefsSet + nCount, &CXrioToCharacterTool::CompareByPosition);

//    for(int k = 0; k < nCount ; ++k)
//    {
//        pCharElementExpr->m_strArrayExprRefIDs.Add(pDiffExprRefsSet[k].DiffExprRef);
//    }

//    delete []pDiffExprRefsSet;
}

void CXrioToCharacterTool::DeleteINFPoints(CRioTripChar *pTripChar)
{
    POS pos = pTripChar->GetHeadPosition();
    CExBaseObject *pObj = NULL;
    CRioDiffPoint *pDiffPoint = NULL;
    while(pos)
    {
        pObj = pTripChar->GetNext(pos);
        if(pObj->GetClassID() == XRIOCLASSID_POINT)
        {
            pDiffPoint = (CRioDiffPoint*)pObj;
            if(IsINFPoint(pDiffPoint))
            {
                //pTripChar->DeleteByID(pDiffPoint->m_strID);
                pTripChar->Delete(pDiffPoint);
            }
        }
    }
}

BOOL CXrioToCharacterTool::IsINFPoint(CRioDiffPoint *pDiffPoint)
{
    CRioPointX *pPointX = NULL;
    CRioPointY *pPointY = NULL;
    pPointX = (CRioPointX*)pDiffPoint->FindByClassID(XRIOCLASSID_POINT_X);
    if(pPointX != NULL)
    {
        if(pPointX->m_strValue.CompareNoCase(XRIO_DEVICE_MODEL_POSITIVE_INF_STRING) || pPointX->m_strValue.CompareNoCase(_T("+inf")))
        {
            return TRUE;
        }
    }
    pPointY = (CRioPointY*)pDiffPoint->FindByClassID(XRIOCLASSID_POINT_Y);
    if(pPointY != NULL)
    {
        if(pPointY->m_strValue.CompareNoCase(XRIO_DEVICE_MODEL_POSITIVE_INF_STRING) || pPointY->m_strValue.CompareNoCase(_T("+inf")))
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL CXrioToCharacterTool::ParseRioOverCurrent(CExBaseObject *pObj, CCharacteristicLib *pCharacterLib)
{
    CRioOverCurrent *pRioOverCurrent = NULL;
    pRioOverCurrent = (CRioOverCurrent*)pObj;
    CRioOverCurrentElements *pOverCurrentElements = NULL;
    //floder节点OVERCURRENT
    CCharacterFolder *pCharacterFolder= new CCharacterFolder();
    pCharacterLib->AddNewChild(pCharacterFolder);
    InitAttr(pCharacterFolder->m_strName,XRIO_DEVICE_MODEL_ID_OVERCURRENT,pRioOverCurrent->m_strName);
    InitAttr(pCharacterFolder->m_strID,XRIO_DEVICE_MODEL_ID_OVERCURRENT,pRioOverCurrent->m_strID);
    //    pCharacterFolder->m_strName =  _T("反时限");
    //    pCharacterFolder->m_strID =  _T("反时限");

    pOverCurrentElements = (CRioOverCurrentElements*)pRioOverCurrent->FindByClassID(XRIOCLASSID_OVERCURRENTELEMENTS);
    if(pOverCurrentElements != NULL)
    {
        POS OverCurrentElementsPos = pOverCurrentElements->GetHeadPosition();
        while(OverCurrentElementsPos)
        {
            pObj = pOverCurrentElements->GetNext(OverCurrentElementsPos);
            if(pObj->GetClassID() == XRIOCLASSID_TIMEDOVERCURRENTELEMENT && ((CRioTimedOverCurrentElement*)pObj)->m_strEnabled != _T("false"))
            {
                ParseOverCurrentTimedOverCurrentElement(pObj,pCharacterFolder);
            }
        }
    }

    POS OverCurrentPos = pRioOverCurrent->GetHeadPosition();
    while(OverCurrentPos)
    {
        pObj = pRioOverCurrent->GetNext(OverCurrentPos);
        if(pObj->GetClassID() == XRIOCLASSID_OVERCURRENT_GROUP)
        {
            ParseOverCurrentGroup(pObj,pCharacterFolder);
        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentGroup(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder)
{
    CRioOverCurrentGroup *pOverCurrentGroup = NULL;
    pOverCurrentGroup = (CRioOverCurrentGroup*)pObj;
    POS OverCurrentGroupPos = pOverCurrentGroup->GetHeadPosition();
    CRioOverCurrentUnit *pOverCurrentUnit = NULL;
    CRioTIndex* pTIndex = NULL;
    CString strTp;
    while(OverCurrentGroupPos)
    {
        pObj = pOverCurrentGroup->GetNext(OverCurrentGroupPos);
        if(pObj->GetClassID() == XRIOCLASSID_OVERCURRENT_UNIT)
        {
            pOverCurrentUnit = (CRioOverCurrentUnit*)pObj;
            //            pObj = pOverCurrentUnit->FindByClassID(XRIOCLASSID_ACTIVE);
            //            if(pObj == NULL)
            //            {
            //                continue;
            //            }
            //            if(((CRioActive*)pObj)->m_strValue == _T("false"))
            //            {
            //                continue;
            //            }
            pTIndex = (CRioTIndex*)pOverCurrentUnit->FindByClassID(XRIOCLASSID_TINDEX);
            if(pTIndex != NULL)
            {
                strTp = pTIndex->m_strValue;
            }
            POS OverCurrentUnitPos = pOverCurrentUnit->GetHeadPosition();
            while(OverCurrentUnitPos)
            {
                pObj = pOverCurrentUnit->GetNext(OverCurrentUnitPos);
                if(pObj->GetClassID() == XRIOCLASSID_OVERCURRENT_TABLE && ((CRioOverCurrentTable*)pObj)->m_strEnabled != _T("false"))
                {
                    ParseOverCurrentTable(pObj,pCharacterFolder);
                }
                else if(pObj->GetClassID() == XRIOCLASSID_OVERCURRENT_CHAR && ((CRioOverCurrentChar*)pObj)->m_strEnabled != _T("false") )
                {
                    ParseOverCurrentChar(pObj,pCharacterFolder,strTp);
                }
                else if(pObj->GetClassID() == XRIOCLASSID_OVERCURRENT_CHARI2T && ((CRioOverCurrentCharI2T*)pObj)->m_strEnabled != _T("false"))
                {
                    ParseOverCurrentCharI2T(pObj,pCharacterFolder,strTp);
                }
            }
        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentTable(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder)
{
    CRioOverCurrentTable *pOverCurrentTable = NULL;
    pOverCurrentTable = (CRioOverCurrentTable*)pObj;
    POS OverCurrentTablePos = pOverCurrentTable->GetHeadPosition();

    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName=  /*_T("反时限折线");*/pOverCurrentTable->m_strName;
    pCharacteristic->m_strID=  /*_T("反时限折线");*/pOverCurrentTable->m_strID;
    pCharacteristic->m_strAxis=  _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);

    CCharElementInvOwnDef *pCharElementInvOwnDef = new CCharElementInvOwnDef;
    pCharacterArea->AddNewChild(pCharElementInvOwnDef);
        for(int i = 1;i < 5; i++)
        {
            CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementInvOwnDef->AddNewChild(pCharTestLine);
            pCharTestLine->m_fPos = i;
        }

    while(OverCurrentTablePos)
    {
        pObj = pOverCurrentTable->GetNext(OverCurrentTablePos);
        if(pObj->GetClassID() == XRIOCLASSID_POINT)
        {
            ParseOverCurrentTablePoint(pObj,pCharElementInvOwnDef->m_strPoints);
        }
        }

//    while(OverCurrentTablePos)
//    {
//        if(OverCurrentTablePos == pOverCurrentTable->GetTailPosition())
//        {
//            break;
//        }
//        CCharElementLined *pCharElementLined= new CCharElementLined();
//        pCharacterArea->AddNewChild(pCharElementLined);
//        for(int i = 1;i < 5; i++)
//        {
//            CCharTestLine  *pCharTestLine= new CCharTestLine();
//            pCharElementLined->AddNewChild(pCharTestLine);
//            pCharTestLine->m_fPos = i;
//        }
//        pObj = pOverCurrentTable->GetNext(OverCurrentTablePos);
//        if(pObj->GetClassID() == XRIOCLASSID_POINT)
//        {
//            ParseOverCurrentTablePoint(pObj,pCharElementLined->m_strXb,pCharElementLined->m_strYb);
//        }
//        pObj = pOverCurrentTable->GetNext(OverCurrentTablePos);
//        if(pObj->GetClassID() == XRIOCLASSID_POINT)
//        {
//            ParseOverCurrentTablePoint(pObj,pCharElementLined->m_strXe,pCharElementLined->m_strYe);
//        }
//        if(OverCurrentTablePos != NULL)
//        {
//            pOverCurrentTable->GetPrev(OverCurrentTablePos);
//        }
//    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentTablePoint(CExBaseObject *pObj, CString &strPoints)
{
    CRioDiffPoint *pTablePoint = NULL;
    pTablePoint = (CRioDiffPoint*)pObj;
    CRioPointX *pPointX = NULL;
    CRioPointY *pPointY = NULL;
    CString strPointX = _T("0");
    CString strPointY = _T("0");
    pPointX = (CRioPointX*)pTablePoint->FindByClassID(XRIOCLASSID_POINT_X);
    if(pPointX != NULL)
        {
        strPointX = pPointX->m_strValue;
        }
    pPointY = (CRioPointY*)pTablePoint->FindByClassID(XRIOCLASSID_POINT_Y);
    if(pPointY != NULL)
        {
        strPointY = pPointY->m_strValue;
    }
    strPoints += _T("{") + strPointX + _T(",") + strPointY+ _T("}");
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentChar(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP)
{
    CRioOverCurrentChar *pOverCurrentChar = NULL;
    pOverCurrentChar = (CRioOverCurrentChar*)pObj;
    //    POS OverCurrentCharPos = pOverCurrentChar->GetHeadPosition();

    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName=  /*_T("反时限IEEE");*/pOverCurrentChar->m_strName;
    pCharacteristic->m_strID=  /*_T("反时限IEEE");*/pOverCurrentChar->m_strID;
    pCharacteristic->m_strAxis=  _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);

    CRioOverCurrentCharA *pOverCurrentCharA = NULL;
    CRioOverCurrentCharB *pOverCurrentCharB = NULL;
    CRioOverCurrentCharP *pOverCurrentCharP = NULL;
    CRioOverCurrentCharQ *pOverCurrentCharQ = NULL;
    CRioOverCurrentCharK1 *pOverCurrentCharK1 = NULL;
    CRioOverCurrentCharK2 *pOverCurrentCharK2 = NULL;
    CCharElementIEEE *pCharElementIEEE= new CCharElementIEEE();
    pCharacterArea->AddNewChild(pCharElementIEEE);

    pCharElementIEEE->m_strTp = strTP;
    pOverCurrentCharA = (CRioOverCurrentCharA*)pOverCurrentChar->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_A);
    if(pOverCurrentCharA != NULL)
    {
        pCharElementIEEE->m_strA = pOverCurrentCharA->m_strValue;
    }

    pOverCurrentCharB = (CRioOverCurrentCharB*)pOverCurrentChar->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_B);
    if(pOverCurrentCharB != NULL)
    {
        pCharElementIEEE->m_strB = pOverCurrentCharB->m_strValue;
    }

    pOverCurrentCharP = (CRioOverCurrentCharP*)pOverCurrentChar->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_P);
    if(pOverCurrentCharP != NULL)
    {
        pCharElementIEEE->m_strP = pOverCurrentCharP->m_strValue;
    }

    pOverCurrentCharQ = (CRioOverCurrentCharQ*)pOverCurrentChar->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_Q);
    if(pOverCurrentCharQ != NULL)
    {
        pCharElementIEEE->m_strQ = pOverCurrentCharQ->m_strValue;
    }

    pOverCurrentCharK1 = (CRioOverCurrentCharK1*)pOverCurrentChar->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_K1);
    if(pOverCurrentCharK1 != NULL)
    {
        pCharElementIEEE->m_strK1 = pOverCurrentCharK1->m_strValue;
    }

    pOverCurrentCharK2 = (CRioOverCurrentCharK2*)pOverCurrentChar->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_K2);
    if(pOverCurrentCharK2 != NULL)
    {
        pCharElementIEEE->m_strK2 = pOverCurrentCharK2->m_strValue;
    }
    // test节点
    for(int i = 1;i < 5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementIEEE->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentCharI2T(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP)
{
    CRioOverCurrentCharI2T *pOverCurrentCharI2T = NULL;
    pOverCurrentCharI2T = (CRioOverCurrentCharI2T*)pObj;
    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName= /* _T("反时限I2T");*/pOverCurrentCharI2T->m_strName;
    pCharacteristic->m_strID=  /*_T("反时限I2T");*/pOverCurrentCharI2T->m_strID;
    pCharacteristic->m_strAxis=  _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);

    CRioOverCurrentCharA *pOverCurrentCharA = NULL;
    CRioOverCurrentCharP *pOverCurrentCharP = NULL;
    CRioOverCurrentCharQ *pOverCurrentCharQ = NULL;
    CCharElementI2TEx *pCharElementI2TEx= new CCharElementI2TEx();
    pCharacterArea->AddNewChild(pCharElementI2TEx);

    pCharElementI2TEx->m_strTp = strTP;
    pOverCurrentCharA = (CRioOverCurrentCharA*)pOverCurrentCharI2T->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_A);
    if(pOverCurrentCharA != NULL)
    {
        pCharElementI2TEx->m_strA = pOverCurrentCharA->m_strValue;
    }

    pOverCurrentCharP = (CRioOverCurrentCharP*)pOverCurrentCharI2T->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_P);
    if(pOverCurrentCharP != NULL)
    {
        pCharElementI2TEx->m_strP = pOverCurrentCharP->m_strValue;
    }

    pOverCurrentCharQ = (CRioOverCurrentCharQ*)pOverCurrentCharI2T->FindByClassID(XRIOCLASSID_OVERCURRENT_CHAR_Q);
    if(pOverCurrentCharQ != NULL)
    {
        pCharElementI2TEx->m_strQ = pOverCurrentCharQ->m_strValue;
    }
    // test节点
    for(int i = 1;i < 5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementI2TEx->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentTimedOverCurrentElement(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder)
{
    CString strTP;
    CRioTimedOverCurrentElement *pTimedOverCurrentElement = NULL;
    CRioActive *pActive = NULL;
    pTimedOverCurrentElement = (CRioTimedOverCurrentElement*)pObj;
    //    pActive = (CRioActive*)pTimedOverCurrentElement->FindByClassID(XRIOCLASSID_ACTIVE);
    //    if(pActive == NULL)
    //    {
    //        return FALSE;
    //    }

    //    if(pActive->m_strValue == _T("false"))
    //    {
    //        return FALSE;
    //    }

    pObj = pTimedOverCurrentElement->FindByClassID(XRIOCLASSID_TIMEMULTIPLIER);
    if(pObj != NULL)
    {
        ParseOverCurrentTimeMultiplier(pObj,strTP);
    }

    pObj = pTimedOverCurrentElement->FindByClassID(XRIOCLASSID_OPERATINGCURVES);

    if(pObj != NULL)
    {
        ParseOverCurrentOperatingCurves(pObj,pCharacterFolder,strTP);
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentOperatingCurves(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder, const CString& strTP)
{
    CRioOperatingCurves *pOperatingCurves = NULL;
    pOperatingCurves = (CRioOperatingCurves*)pObj;
    POS OperatingCurvesPos = pOperatingCurves->GetHeadPosition();
    while(OperatingCurvesPos)
    {
        pObj = pOperatingCurves->GetNext(OperatingCurvesPos);
        if(pObj->GetClassID() == XRIOCLASSID_INVERSEPARAMETERCURVE && ((CRioInverseParameterCurve*)pObj)->m_strEnabled !=  _T("false"))
        {
            ParseOverCurrentInverseParameterCurve(pObj,pCharacterFolder,strTP);
        }
        else if(pObj->GetClassID() == XRIOCLASSID_STANDARDCURVE && ((CRioStandardCurve*)pObj)->m_strEnabled !=  _T("false"))
        {
            ParseOverCurrentStandardCurve(pObj,pCharacterFolder,strTP);
        }
        else if(pObj->GetClassID() == XRIOCLASSID_I2TPARAMETERCURVE && ((CRioI2TParameterCurve*)pObj)->m_strEnabled !=  _T("false"))
        {
            ParseOverCurrentI2TParameterCurve(pObj,pCharacterFolder,strTP);
        }
        else if(pObj->GetClassID() == XRIOCLASSID_CUSTOMCURVE && ((CRioCustomCurve*)pObj)->m_strEnabled !=  _T("false"))
        {
            ParseOverCurrentCustomCurve(pObj,pCharacterFolder);
        }
        else if(pObj->GetClassID() == XRIOCLASSID_IACPARAMETERCURVE && ((CRioIACParameterCurve*)pObj)->m_strEnabled !=  _T("false"))
        {
            ParseOverCurrentIACParameterCurve(pObj,pCharacterFolder,strTP);
        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentTimeMultiplier(CExBaseObject *pObj, CString &strTP)
{
    CRioTimeMultiplier *pTimeMultiplier = NULL;
    pTimeMultiplier = (CRioTimeMultiplier*)pObj;
    CRioTimeMultiplierNomval *pTimeMultiplierNomval = NULL;
    pTimeMultiplierNomval = (CRioTimeMultiplierNomval*)pTimeMultiplier->FindByClassID(XRIOCLASSID_TIMEMULTIPLIER_NOMVAL);
    if(pTimeMultiplierNomval != NULL)
    {
        strTP = pTimeMultiplierNomval->m_strValue;
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentInverseParameterCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP)
{
    CRioInverseParameterCurve *pInverseParameterCurve = NULL;
    pInverseParameterCurve = (CRioInverseParameterCurve*)pObj;
    //    //Characteristic节点
    //    CCharacteristic *pCharacteristic= new CCharacteristic();
    //    pCharacterFolder->AddNewChild(pCharacteristic);
    //    pCharacteristic->m_strName = pInverseParameterCurve->m_strName;
    //    pCharacteristic->m_strID = /*_T("IEEE");*/pInverseParameterCurve->m_strID;
    //    pCharacteristic->m_strAxis = _T("logarithm");
    //    //character-area节点
    //    CCharacterArea *pCharacterArea= new CCharacterArea();
    //    pCharacteristic->AddNewChild(pCharacterArea);
    //    //char-interface节点
    //    CCharInterface *pCharInterface= new CCharInterface();
    //    pCharacteristic->AddNewChild(pCharInterface);
    //    //IEEE节点
    //    CCharElementIEEE *pCharElementIEEE= new CCharElementIEEE();
    //    pCharacterArea->AddNewChild(pCharElementIEEE);
    CRioParameterA *pParameterA = NULL;
    CRioParameterB *pParameterB = NULL;
    CRioParameterC *pParameterC = NULL;
    CRioParameterD *pParameterD = NULL;
    CRioParameterE *pParameterE = NULL;
    CRioParameterF *pParameterF = NULL;
    CRioActive *pActive = NULL;
    //    pActive = (CRioActive*)pInverseParameterCurve->FindByClassID(XRIOCLASSID_ACTIVE);
    //    if(pActive == NULL)
    //    {
    //        return FALSE;
    //    }

    //    if(pActive->m_strValue == _T("false"))
    //    {
    //        return FALSE;
    //    }

    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName = pInverseParameterCurve->m_strName;
    pCharacteristic->m_strID = /*_T("IEEE");*/pInverseParameterCurve->m_strID;
    pCharacteristic->m_strAxis = _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);
    //IEEE节点
    CCharElementIEEE *pCharElementIEEE= new CCharElementIEEE();
    pCharacterArea->AddNewChild(pCharElementIEEE);

    pCharElementIEEE->m_strTp = strTP;
    pParameterA = (CRioParameterA*)pInverseParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERA);
    if(pParameterA != NULL)
    {
        pCharElementIEEE->m_strA = pParameterA->m_strValue;
    }

    pParameterB = (CRioParameterB*)pInverseParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERB);
    if(pParameterB != NULL)
    {
        pCharElementIEEE->m_strB = pParameterB->m_strValue;
    }

    pParameterC = (CRioParameterC*)pInverseParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERC);
    if(pParameterC != NULL)
    {
        pCharElementIEEE->m_strP = pParameterC->m_strValue;
    }

    pParameterD = (CRioParameterD*)pInverseParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERD);
    if(pParameterD != NULL)
    {
        pCharElementIEEE->m_strQ = pParameterD->m_strValue;
    }

    pParameterE = (CRioParameterE*)pInverseParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERE);
    if(pParameterE != NULL)
    {
        pCharElementIEEE->m_strK1 = pParameterE->m_strValue;
    }

    pParameterF = (CRioParameterF*)pInverseParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERF);
    if(pParameterF != NULL)
    {
        pCharElementIEEE->m_strK2 = pParameterF->m_strValue;
    }
    for(int i = 1;i < 5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementIEEE->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentI2TParameterCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP)
{
    CRioI2TParameterCurve *pI2TParameterCurve = NULL;
    pI2TParameterCurve = (CRioI2TParameterCurve*)pObj;
    //    //Characteristic节点
    //    CCharacteristic *pCharacteristic= new CCharacteristic();
    //    pCharacterFolder->AddNewChild(pCharacteristic);
    //    pCharacteristic->m_strName = pI2TParameterCurve->m_strName;
    //    pCharacteristic->m_strID = /*_T("IEEE");*/pI2TParameterCurve->m_strID;
    //    pCharacteristic->m_strAxis=  _T("logarithm");
    //    //character-area节点
    //    CCharacterArea *pCharacterArea= new CCharacterArea();
    //    pCharacteristic->AddNewChild(pCharacterArea);
    //    //char-interface节点
    //    CCharInterface *pCharInterface= new CCharInterface();
    //    pCharacteristic->AddNewChild(pCharInterface);
    //    //I2T节点
    //    CCharElementI2TEx *pCharElementI2TEx= new CCharElementI2TEx();
    //    pCharacterArea->AddNewChild(pCharElementI2TEx);
    //    pCharElementI2TEx->m_strTp = m_strTP;
    CRioParameterA *pParameterA = NULL;
    CRioParameterB *pParameterB = NULL;
    CRioParameterC *pParameterC = NULL;
    CRioActive *pActive = NULL;

    //    pActive = (CRioActive*)pI2TParameterCurve->FindByClassID(XRIOCLASSID_ACTIVE);
    //    if(pActive == NULL)
    //    {
    //        return FALSE;
    //    }

    //    if(pActive->m_strValue == _T("false"))
    //    {
    //        return FALSE;
    //    }

    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName = pI2TParameterCurve->m_strName;
    pCharacteristic->m_strID = /*_T("IEEE");*/pI2TParameterCurve->m_strID;
    pCharacteristic->m_strAxis=  _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);
    //I2T节点
    CCharElementI2TEx *pCharElementI2TEx= new CCharElementI2TEx();
    pCharacterArea->AddNewChild(pCharElementI2TEx);
    pCharElementI2TEx->m_strTp = strTP;

    pParameterA = (CRioParameterA*)pI2TParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERA);
    if(pParameterA != NULL)
    {
        pCharElementI2TEx->m_strA = pParameterA->m_strValue;
    }

    pParameterB = (CRioParameterB*)pI2TParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERB);
    if(pParameterB != NULL)
    {
        pCharElementI2TEx->m_strP = pParameterB->m_strValue;
    }

    pParameterC = (CRioParameterC*)pI2TParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERC);
    if(pParameterC != NULL)
    {
        pCharElementI2TEx->m_strQ = pParameterC->m_strValue;
    }
    for(int i = 1;i < 5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementI2TEx->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentIACParameterCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder, const CString &strTP)
{
    CRioIACParameterCurve *pIACParameterCurve = NULL;
    pIACParameterCurve = (CRioIACParameterCurve*)pObj;
    //    //Characteristic节点
    //    CCharacteristic *pCharacteristic= new CCharacteristic();
    //    pCharacterFolder->AddNewChild(pCharacteristic);
    //    pCharacteristic->m_strID= /* _T("IAC");*/pIACParameterCurve->m_strID;
    //    pCharacteristic->m_strName= pIACParameterCurve->m_strName;
    //    pCharacteristic->m_strAxis=  _T("logarithm");
    //    //character-area节点
    //    CCharacterArea *pCharacterArea= new CCharacterArea();
    //    pCharacteristic->AddNewChild(pCharacterArea);
    //    //char-interface节点
    //    CCharInterface *pCharInterface= new CCharInterface();
    //    pCharacteristic->AddNewChild(pCharInterface);
    //    //IAC节点
    //    CCharElementIAC *pCharElementIAC= new CCharElementIAC();
    //    pCharacterArea->AddNewChild(pCharElementIAC);
    //    pCharElementIAC->m_strTp = m_strTP;
    //    pCharElementIAC->m_strBeta = "1";
    CRioParameterA *pParameterA = NULL;
    CRioParameterB *pParameterB = NULL;
    CRioParameterC *pParameterC = NULL;
    CRioParameterD *pParameterD = NULL;
    CRioParameterE *pParameterE = NULL;
    CRioActive *pActive = NULL;

    //    pActive = (CRioActive*)pIACParameterCurve->FindByClassID(XRIOCLASSID_ACTIVE);
    //    if(pActive == NULL)
    //    {
    //        return FALSE;
    //    }

    //    if(pActive->m_strValue == _T("false"))
    //    {
    //        return FALSE;
    //    }

    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strID= /* _T("IAC");*/pIACParameterCurve->m_strID;
    pCharacteristic->m_strName= pIACParameterCurve->m_strName;
    pCharacteristic->m_strAxis=  _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);
    //IAC节点
    CCharElementIAC *pCharElementIAC= new CCharElementIAC();
    pCharacterArea->AddNewChild(pCharElementIAC);
    pCharElementIAC->m_strTp = strTP;
    pCharElementIAC->m_strBeta = _T("1");

    pParameterA = (CRioParameterA*)pIACParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERA);
    if(pParameterA != NULL)
    {
        pCharElementIAC->m_strA = pParameterA->m_strValue;
    }

    pParameterB = (CRioParameterB*)pIACParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERB);
    if(pParameterB != NULL)
    {
        pCharElementIAC->m_strB = pParameterB->m_strValue;
    }

    pParameterC = (CRioParameterC*)pIACParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERC);
    if(pParameterC != NULL)
    {
        pCharElementIAC->m_strC = pParameterC->m_strValue;
    }

    pParameterD = (CRioParameterD*)pIACParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERD);
    if(pParameterD != NULL)
    {
        pCharElementIAC->m_strD = pParameterD->m_strValue;
    }

    pParameterE = (CRioParameterE*)pIACParameterCurve->FindByClassID(XRIOCLASSID_PARAMETERE);
    if(pParameterE != NULL)
    {
        pCharElementIAC->m_strE = pParameterE->m_strValue;
    }

    for(int i = 1;i < 5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementIAC->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentStandardCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP)
{
    CRioStandardCurve *pStandardCurve = NULL;
    pStandardCurve = (CRioStandardCurve*)pObj;

    CRioActive *pActive = NULL;
    //    pActive = (CRioActive*)pStandardCurve->FindByClassID(XRIOCLASSID_ACTIVE);
    //    if(pActive == NULL)
    //    {
    //        return FALSE;
    //    }

    //    if(pActive->m_strValue == _T("false"))
    //    {
    //        return FALSE;
    //    }
    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName = pStandardCurve->m_strName;
    pCharacteristic->m_strID = /*_T("IEEE");*/pStandardCurve->m_strID;
    pCharacteristic->m_strAxis=  _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);

    CCharElementIEEE *pCharElementIEEE = new CCharElementIEEE();
    pCharacterArea->AddNewChild(pCharElementIEEE);

    pCharElementIEEE->m_strTp = strTP;
    pCharElementIEEE->m_strA = "1.00";
    pCharElementIEEE->m_strB = "0.00";
    pCharElementIEEE->m_strP = "0.00";
    pCharElementIEEE->m_strQ = "0.00";
    pCharElementIEEE->m_strK1 = "0.00";
    pCharElementIEEE->m_strK2 = "0.00";

    for(int i = 1;i < 5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementIEEE->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }

    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentCustomCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder)
{
    CRioCustomCurve *pCustomCurve = NULL;
    pCustomCurve = (CRioCustomCurve*)pObj;
    CRioActive *pActive = NULL;
    //    pActive = (CRioActive*)pCustomCurve->FindByClassID(XRIOCLASSID_ACTIVE);
    //    if(pActive == NULL)
    //    {
    //        return FALSE;
    //    }

    //    if(pActive->m_strValue == _T("false"))
    //    {
    //        return FALSE;
    //    }

    CRioCurvePoints *pCurvePoints = NULL;
    //Characteristic节点
    CCharacteristic *pCharacteristic= new CCharacteristic();
    pCharacterFolder->AddNewChild(pCharacteristic);
    pCharacteristic->m_strName = /* _T("IEEE折线");*/pCustomCurve->m_strName;
    pCharacteristic->m_strID =  /*_T("IEEE折线");*/pCustomCurve->m_strID;
    pCharacteristic->m_strAxis =  _T("logarithm");
    //character-area节点
    CCharacterArea *pCharacterArea= /*new CCharacterArea()*/pCharacteristic->GetCharacterArea();
    //pCharacteristic->AddNewChild(pCharacterArea);
    //char-interface节点
    CCharInterface *pCharInterface= /*new CCharInterface()*/pCharacteristic->GetCharInterface();
    //pCharacteristic->AddNewChild(pCharInterface);

    pCurvePoints = (CRioCurvePoints*)pCustomCurve->FindByClassID(XRIOCLASSID_CURVEPOINTS);
    if(pCurvePoints == NULL)
    {
        return FALSE;
    }
    CCharElementInvOwnDef *pCharElementInvOwnDef = new CCharElementInvOwnDef;
    pCharacterArea->AddNewChild(pCharElementInvOwnDef);
    for(int i = 1;i < 5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementInvOwnDef->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    POS CurvePointsPos = pCurvePoints->GetHeadPosition();
    while(CurvePointsPos)
    {
        pObj = pCurvePoints->GetNext(CurvePointsPos);
        if(pObj->GetClassID() == XRIOCLASSID_CURVEPOINT)
        {
            ParseOverCurrentCustomCurvePointEx(pObj,pCharElementInvOwnDef->m_strPoints);
        }
//        if(CurvePointsPos == pCurvePoints->GetTailPosition())
//        {
//            break;
//        }
//        CCharElementLined *pCharElementLined= new CCharElementLined();
//        pCharacterArea->AddNewChild(pCharElementLined);
//        for(int i = 1;i < 5; i++)
//        {
//            CCharTestLine  *pCharTestLine= new CCharTestLine();
//            pCharElementLined->AddNewChild(pCharTestLine);
//            pCharTestLine->m_fPos = i;
//        }
//        pObj = pCurvePoints->GetNext(CurvePointsPos);
//        if(pObj->GetClassID() == XRIOCLASSID_CURVEPOINT)
//        {
//            ParseOverCurrentCustomCurvePoint(pObj,pCharElementLined->m_strXb,pCharElementLined->m_strYb);
//        }
//        pObj = pCurvePoints->GetNext(CurvePointsPos);
//        if(pObj->GetClassID() == XRIOCLASSID_CURVEPOINT)
//        {
//            ParseOverCurrentCustomCurvePoint(pObj,pCharElementLined->m_strXe,pCharElementLined->m_strYe);
//        }
//        if(CurvePointsPos != NULL)
//        {
//            pCurvePoints->GetPrev(CurvePointsPos);
//        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentCustomCurvePoint(CExBaseObject *pObj, CString &strRefX, CString &strRefY)
{
    CRioCurvePoint *pCurvePoint = NULL;
    pCurvePoint = (CRioCurvePoint*)pObj;
    CRioPointX *pPointX = NULL;
    CRioPointY *pPointY = NULL;
    pPointX= (CRioPointX*)pCurvePoint->FindByClassID(XRIOCLASSID_POINT_X);
    if(pPointX != NULL)
    {
        strRefX = pPointX->m_strValue;
    }
    pPointY = (CRioPointY*)pCurvePoint->FindByClassID(XRIOCLASSID_POINT_Y);
    if(pPointY != NULL)
    {
        strRefY = pPointY->m_strValue;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentCustomCurvePointEx(CExBaseObject *pObj, CString& strPoints)
{
    CRioCurvePoint *pCurvePoint = NULL;
    pCurvePoint = (CRioCurvePoint*)pObj;
    CRioPointX *pPointX = NULL;
    CRioPointY *pPointY = NULL;
    CString strPointX = _T("0");
    CString strPointY = _T("0");
    pPointX = (CRioPointX*)pCurvePoint->FindByClassID(XRIOCLASSID_POINT_X);
    if(pPointX != NULL)
    {
        strPointX = pPointX->m_strValue;
    }
    pPointY = (CRioPointY*)pCurvePoint->FindByClassID(XRIOCLASSID_POINT_Y);
    if(pPointY != NULL)
    {
        strPointY = pPointY->m_strValue;
    }
    strPoints += _T("{") + strPointX + _T(",") + strPointY+ _T("}");
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseOverCurrentTablePoint(CExBaseObject *pObj, CString &strRefX, CString &strRefY)
{
    CRioDiffPoint *pPoint = NULL;
    CRioPointX *pPointX = NULL;
    CRioPointY *pPointY = NULL;

    pPoint = (CRioDiffPoint*)pObj;

    pPointX= (CRioPointX*)pPoint->FindByClassID(XRIOCLASSID_POINT_X);
    if(pPointX != NULL)
    {
        strRefX = pPointX->m_strValue;
    }
    pPointY = (CRioPointY*)pPoint->FindByClassID(XRIOCLASSID_POINT_Y);
    if(pPointY != NULL)
    {
        strRefY = pPointY->m_strValue;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::ParseDistanceZone(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder)
{
    CRioDistanceProtectionDevice *pDistanceProtectionDevice = NULL;
    pDistanceProtectionDevice = (CRioDistanceProtectionDevice*)pObj;

    CRioZone *pZone= NULL;
    CRioActive *pActive = NULL;
    //    CRioFaultLoop *pFaultLoop = NULL;
    //    CRioIndex *pIndex = NULL;
    CRioZones *pZones= NULL;
    pZones = (CRioZones*)pDistanceProtectionDevice->FindByClassID(XRIOCLASSID_ZONES);
    if(pZones != NULL)
    {
        POS ZonesPos = pZones->GetHeadPosition();
        while(ZonesPos)
        {
            pObj = pZones->GetNext(ZonesPos);
            if(pObj->GetClassID() != XRIOCLASSID_ZONE)
            {
                continue;
            }
            if(((CRioZone*)pObj)->m_strEnabled == _T("false"))
            {
                continue;
            }

            pZone = (CRioZone*)pObj;
            //            pActive = (CRioActive*)pZone->FindByClassID(XRIOCLASSID_ACTIVE);
            //            if(pActive == NULL)
            //            {
            //                continue;
            //            }

            //            if(pActive->m_strValue == _T("false"))
            //            {
            //                continue;
            //            }

            //Characteristic节点
            CCharacteristic *pCharacteristic= new CCharacteristic();
            pCharacterFolder->AddNewChild(pCharacteristic);
            pCharacteristic->m_strName = pZone->m_strName;
            pCharacteristic->m_strID = pZone->m_strID;
            pCharacteristic->m_strAxis = _T("cartes");
            //character-area节点
            CCharacterArea *pCharacterArea= /*new CCharacterArea();*/pCharacteristic->GetCharacterArea();
            //pCharacteristic->AddNewChild(pCharacterArea);
            //char-interface节点
            CCharInterface *pCharInterface= /*new CCharInterface();*/pCharacteristic->GetCharInterface();
            //pCharacteristic->AddNewChild(pCharInterface);
            //            pFaultLoop = (CRioFaultLoop*)pZone->FindByClassID(XRIOCLASSID_FAULTLOOP);
            //            if(pFaultLoop == NULL)
            //            {
            //                continue;
            //            }
            //            if(pFaultLoop->m_strValue == _T("LL"))
            //            {
            //                pIndex = (CRioIndex*)pZone->FindByClassID(XRIOCLASSID_INDEX);
            //                if(pIndex == NULL)
            //                {
            //                    continue;
            //                }
            //                AddCharInterfaceVariable_LL(pZone,pCharInterface,CString_To_long(pIndex->m_strValue));
            //            }
            //            else if(pFaultLoop->m_strValue == _T("LN"))
            //            {
            //                pIndex = (CRioIndex*)pZone->FindByClassID(XRIOCLASSID_INDEX);
            //                if(pIndex == NULL)
            //                {
            //                    continue;
            //                }
            //                AddCharInterfaceVariable_LN(pZone,pCharInterface,CString_To_long(pIndex->m_strValue));
            //            }
            ParseDistanceShape(pObj, pCharacterArea);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToCharacterTool::ParseDistanceShape(CExBaseObject *pObj, CCharacterArea *pCharacterArea)
{
    CRioZone *pZone= NULL;
    pZone = (CRioZone*)pObj;
    pObj = pZone->FindByClassID(XRIOCLASSID_GENERICSHAPE);
    if(pObj != NULL)
    {
        AddDistanceGenericshape(pObj,pCharacterArea);
        return TRUE;
    }

    pObj = pZone->FindByClassID(XRIOCLASSID_MHOSHAPE);
    if(pObj != NULL)
    {
        AddDistanceMhoshape(pObj,pCharacterArea);
        return TRUE;
    }
    return FALSE;
}

BOOL CXrioToCharacterTool::AddDistanceGenericshape(CExBaseObject *pObj, CCharacterArea *pCharacterArea)
{
    CRioGenricShape *pGenricShape= NULL;
    CRioAutoClose *pAutoClose = NULL;
    pGenricShape = (CRioGenricShape*)pObj;
    pAutoClose = (CRioAutoClose*)pGenricShape->FindByClassID(XRIOCLASSID_AUTOCLOSE);
    if(pAutoClose != NULL)
    {
        CCharacteristic *pCharacteristic = (CCharacteristic*)pCharacterArea->GetParent();
        if(pAutoClose->m_strValue ==  _T("false"))
        {
            pCharacteristic->m_nAutoClose = 1;
        }
        else
        {
            pCharacteristic->m_nAutoClose = 0;
        }
    }

    POS GenricShapePos = pGenricShape->GetHeadPosition();
    while(GenricShapePos)
    {
        pObj = pGenricShape->GetNext(GenricShapePos);
        if(pObj->GetClassID() == XRIOCLASSID_LINE && ((CRioLine*)pObj)->m_strEnabled !=  _T("false"))
        {
            AddDistanceLine(pObj, pCharacterArea);
        }
        else if(pObj->GetClassID() == XRIOCLASSID_ARC && ((CRioArc*)pObj)->m_strEnabled !=  _T("false"))
        {
            AddDistanceArc(pObj, pCharacterArea);
        }
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::AddDistanceMhoshape(CExBaseObject *pObj, CCharacterArea *pCharacterArea)
{
    CRioMhoShape *pMhoShape= NULL;
    //Mho节点
    CCharElementMho *pCharElementMho= new CCharElementMho();
    pCharacterArea->AddNewChild(pCharElementMho);
    pMhoShape = (CRioMhoShape*)pObj;
    CRioAngle *pAngle = NULL;
    CRioMhoReach *pMhoReach = NULL;
    CRioMhoOffset *pMhoOffset = NULL;
    pAngle = (CRioAngle*)pMhoShape->FindByClassID(XRIOCLASSID_ANGLE);
    if(pAngle != NULL)
    {
        pCharElementMho->m_strAngle = pAngle->m_strValue;
    }

    pMhoReach = (CRioMhoReach*)pMhoShape->FindByClassID(XRIOCLASSID_REACH);
    if(pMhoReach != NULL)
    {
        pCharElementMho->m_strForwardReach = pMhoReach->m_strValue;
    }

    pMhoOffset = (CRioMhoOffset*)pMhoShape->FindByClassID(XRIOCLASSID_OFFSET);
    if(pMhoOffset != NULL)
    {
        pCharElementMho->m_strOffset = pMhoOffset->m_strValue;
    }
    //test节点
    for(int i = 1;i <5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementMho->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::AddDistanceLine(CExBaseObject *pObj, CCharacterArea *pCharacterArea)
{
    CRioLine *pLine= NULL;
    //line节点
    CCharElementLine *pCharElementLine= new CCharElementLine();
    pCharacterArea->AddNewChild(pCharElementLine);
    pLine = (CRioLine*)pObj;
    CRioRefPointR *pRefPointR = NULL;
    CRioRefPointX *pRefPointX = NULL;
    CRioAngle *pAngle = NULL;
    CRioInside *pInside = NULL;

    pRefPointR = (CRioRefPointR*)pLine->FindByClassID(XRIOCLASSID_REFPOINT_R);
    if(pRefPointR != NULL)
    {
        pCharElementLine->m_strX = pRefPointR->m_strValue;
    }

    pRefPointX = (CRioRefPointX*)pLine->FindByClassID(XRIOCLASSID_REFPOINT_X);
    if(pRefPointX != NULL)
    {
        pCharElementLine->m_strY = pRefPointX->m_strValue;
    }

    pAngle = (CRioAngle*)pLine->FindByClassID(XRIOCLASSID_ANGLE);
    if(pAngle != NULL)
    {
        pCharElementLine->m_strAngle = pAngle->m_strValue;
    }

    pInside = (CRioInside*)pLine->FindByClassID(XRIOCLASSID_INSIDE);
    if(pInside != NULL)
    {
        pCharElementLine->m_strDir = pInside->m_strValue;
    }
    //test节点
    for(int i = 1;i < 5; i++)
    {
        CCharTestLine *pCharTestLine= new CCharTestLine();
        pCharElementLine->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

BOOL CXrioToCharacterTool::AddDistanceArc(CExBaseObject *pObj, CCharacterArea *pCharacterArea)
{
    CRioArc *pArc= NULL;
    //arc节点
    CCharElementArcp *pCharElementArcp= new CCharElementArcp();
    pCharacterArea->AddNewChild(pCharElementArcp);
    pArc = (CRioArc*)pObj;
    CRioRefPointMag *pRefPointMag = NULL;
    CRioRefPointAngle *pRefPointAngle = NULL;
    CRioRadius *pRadius = NULL;
    CRioStartAngle *pStartAngle = NULL;
    CRioEndAngle *pEndAngle = NULL;
    CRioDir *pDir = NULL;

    pRefPointMag = (CRioRefPointMag*)pArc->FindByClassID(XRIOCLASSID_REFPOINT_MAG);
    if(pRefPointMag != NULL)
    {
        pCharElementArcp->m_strZ = QString::number(((pRefPointMag->m_strValue).toDouble()),'f',2);
    }

    pRefPointAngle = (CRioRefPointAngle*)pArc->FindByClassID(XRIOCLASSID_REFPOINT_ANGLE);
    if(pRefPointAngle != NULL)
    {
        pCharElementArcp->m_strPh = pRefPointAngle->m_strValue;
    }

    pRadius = (CRioRadius*)pArc->FindByClassID(XRIOCLASSID_REFPOINT_RADIUS);
    if(pRadius != NULL)
    {
        pCharElementArcp->m_strRadius = pRadius->m_strValue;
    }

    pStartAngle = (CRioStartAngle*)pArc->FindByClassID(XRIOCLASSID_REFPOINT_STARTANGLE);
    if(pStartAngle != NULL)
    {
        pCharElementArcp->m_strAngleBegin = QString::number(((pStartAngle->m_strValue).toDouble()),'f',2);
    }

    pEndAngle = (CRioEndAngle*)pArc->FindByClassID(XRIOCLASSID_REFPOINT_ENDANGLE);
    if(pEndAngle != NULL)
    {
        pCharElementArcp->m_strAngleEnd = QString::number(((pEndAngle->m_strValue).toDouble()),'f',2);
    }

    pDir = (CRioDir*)pArc->FindByClassID(XRIOCLASSID_REFPOINT_DIR);
    if(pDir != NULL)
    {
        pCharElementArcp->m_strAngleBegin = QString::number(((pStartAngle->m_strValue).toDouble()),'f',2);
    }
    //test节点
    for(int i = 1;i <5; i++)
    {
        CCharTestLine  *pCharTestLine= new CCharTestLine();
        pCharElementArcp->AddNewChild(pCharTestLine);
        pCharTestLine->m_fPos = i;
    }
    return TRUE;
}

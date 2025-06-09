//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharTestObjects.cpp  CCharTestObjects


#include "stdafx.h"
#include "CharTestObjects.h"
#include "CharElementLine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharTestObjects::CCharTestObjects()
{
	//初始化属性
	m_pTestPoints = NULL;
}

CCharTestObjects::~CCharTestObjects()
{
}

long CCharTestObjects::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CCharTestObjects::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CCharTestObjects::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharTestObjects *p = (CCharTestObjects*)pObj;

	return TRUE;
}

BOOL CCharTestObjects::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharTestObjects *p = (CCharTestObjects*)pDest;

	return TRUE;
}

CBaseObject* CCharTestObjects::Clone()
{
	CCharTestObjects *p = new CCharTestObjects();
	Copy(p);
	return p;
}

CBaseObject* CCharTestObjects::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CCharTestObjects *p = new CCharTestObjects();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CCharTestObjects::CanPaste(UINT nClassID)
{
	if (nClassID == CHARCLASSID_CCHARTESTOBJECTS)
	{
		return TRUE;
	}

    if (nClassID == CHARCLASSID_CCharElementPointS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CCharTestObjects::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;


    if (strClassID == pXmlKeys->m_strCCharTestLineKey)
	{
        pNew = new CCharTestLine();
	}
    else if (strClassID == pXmlKeys->m_strCCharElementPointsKey)
	{
        pNew = new CCharTestPoints();
	}
	else if (strClassID == pXmlKeys->m_strCCharTestPointKey)
	{
		pNew = new CCharTestPoint();
	}
	
	return pNew;
}

CExBaseObject* CCharTestObjects::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

    if (nClassID == CHARCLASSID_CCharElementPointS)
	{
        pNew = new CCharTestPoints();
	}
    else if (nClassID == CHARCLASSID_CCHARTESTLINE)
	{
        pNew = new CCharTestLine();
	}
	else if (nClassID == CHARCLASSID_CCHARTESTPOINT)
	{
		pNew = new CCharTestPoint();
	}
	
	return pNew;
}

void CCharTestObjects::InitAfterRead()
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

        if (nClassID == CHARCLASSID_CCharElementPointS)
		{
            CCharTestPoints *pTestPoints = (CCharTestPoints *)pObj;
			m_pTestPoints = pTestPoints;
		}
	}

	if (m_pTestPoints == NULL)
	{
        m_pTestPoints = new CCharTestPoints;
		AddNewChild(m_pTestPoints);
	}
}

//20240822 wanmj
void CCharTestObjects::InitCharDrawTestObj_ForDraw(CExBaseList *pDrawList, int nFaultType, CExBaseObject *pCurTestObj,int nTestObjDrawMode)
{
    POS pos = GetHeadPosition();
    while (pos != NULL)
    {
        CExBaseObject* pTestLineTemp = (CExBaseObject*)GetNext(pos);
        if(pTestLineTemp->GetClassID() == CHARCLASSID_CCHARTESTLINE)
        {
			if (nTestObjDrawMode == CHAR_TEST_OBJECT_DRAW_POINT)
			{
				continue;
			}
            CCharTestLine* pTestLine = (CCharTestLine*)pTestLineTemp;
            if(pTestLine->m_nFaultType != nFaultType)
                continue;

            pTestLine->GetXDrawElement((CXDrawList*)pDrawList);
            if(pTestLine == pCurTestObj)    //如果是选中的测试线
            {
				pTestLine->m_pDrawLineRef->m_crForeColor = RGB(0, 255, 255);
            }
        }
        else if(pTestLineTemp->GetClassID() == CHARCLASSID_CCharElementPointS)
        {

        }
		else if (pTestLineTemp->GetClassID() == CHARCLASSID_CCHARTESTPOINT)
		{
			if (nTestObjDrawMode == CHAR_TEST_OBJECT_DRAW_LINE)
			{
				continue;
			}
		//20240902 luozibing 获取特性曲线对应故障类型测试点
			CCharTestPoint * pTestPoint = (CCharTestPoint*)pTestLineTemp;
			if (pTestPoint->m_nFaultType != nFaultType)
				continue;
			pTestPoint->GetXDrawElement((CXDrawList*)pDrawList);
			if (pTestPoint == pCurTestObj)    //如果是选中的测试点
			{
				pTestPoint->m_pDrawPointRef->m_crForeColor = RGB(0, 255, 255);
			}
		}
    }
    return;
}

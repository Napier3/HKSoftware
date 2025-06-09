//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementInverse.cpp  CCharElementInverse


#include "stdafx.h"
#include "CharElementInverse.h"
#include "Characteristic.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementInverse::CCharElementInverse()
{
	m_nUseSection[0] = 0;
	m_nUseSection[1] = 0;
	m_nUseSection[2] = 0;
	m_nUseSection[3] = 0;

	//初始化属性
	m_strValSection[3] = _T("0.2");
	m_strValSection[2] = _T("1.01");
	m_strValSection[1] = _T("10");
	m_strValSection[0] = _T("20");

	m_strTmSection[3] = _T("100");
	m_strTmSection[2] = _T("1.000	");
	m_strTmSection[1] = _T("0.1");
	m_strTmSection[0] = _T("0.05");

	m_fValSection[3] = 0.2;	
	m_fValSection[2] = 1.01;	
	m_fValSection[1] = 10.0;
	m_fValSection[0] = 20.0;

	//速段时间
	m_fTmSection[2] = 100.0;	
	m_fTmSection[2] = 1.0;	
	m_fTmSection[1] = 0.1;	
	m_fTmSection[0] = 0.05;	

	m_strTmax = _T("3000");
	m_strXmax = _T("30");
	m_fTmax = 3000;
	m_fXmax = 30;
}

CCharElementInverse::~CCharElementInverse()
{
}

long CCharElementInverse::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlReadOwn(oNode, pXmlRWKeys);

	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;
	
	xml_GetAttibuteValue(pXmlKeys->m_strTmaxKey, oNode, m_strTmax);
	xml_GetAttibuteValue(pXmlKeys->m_strXmaxKey, oNode, m_strXmax);

	xml_GetAttibuteValue(pXmlKeys->m_strUseSection1Key, oNode, m_nUseSection[0]);
	xml_GetAttibuteValue(pXmlKeys->m_strUseSection2Key, oNode, m_nUseSection[1]);
	xml_GetAttibuteValue(pXmlKeys->m_strUseSection3Key, oNode, m_nUseSection[2]);
	xml_GetAttibuteValue(pXmlKeys->m_strUseStartUpKey, oNode, m_nUseSection[3]);

	xml_GetAttibuteValue(pXmlKeys->m_strValSection1Key, oNode, m_strValSection[0]);
	xml_GetAttibuteValue(pXmlKeys->m_strValSection2Key, oNode, m_strValSection[1]);
	xml_GetAttibuteValue(pXmlKeys->m_strValSection3Key, oNode, m_strValSection[2]);
	xml_GetAttibuteValue(pXmlKeys->m_strStartUpKey, oNode, m_strValSection[3]);

	xml_GetAttibuteValue(pXmlKeys->m_strTSection1Key, oNode, m_strTmSection[0]);
	xml_GetAttibuteValue(pXmlKeys->m_strTSection2Key, oNode, m_strTmSection[1]);
	xml_GetAttibuteValue(pXmlKeys->m_strTSection3Key, oNode, m_strTmSection[2]);
	xml_GetAttibuteValue(pXmlKeys->m_strTStartUpKey, oNode, m_strTmSection[3]);

	return 0;
}

long CCharElementInverse::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCharElement::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCharacteristicXmlRWKeys *pXmlKeys = (CCharacteristicXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTmaxKey, oElement, m_strTmax);
	xml_SetAttributeValue(pXmlKeys->m_strXmaxKey, oElement, m_strXmax);

	xml_SetAttributeValue(pXmlKeys->m_strUseSection1Key, oElement, m_nUseSection[0]);
	xml_SetAttributeValue(pXmlKeys->m_strUseSection2Key, oElement, m_nUseSection[1]);
	xml_SetAttributeValue(pXmlKeys->m_strUseSection3Key, oElement, m_nUseSection[2]);
	xml_SetAttributeValue(pXmlKeys->m_strUseStartUpKey, oElement, m_nUseSection[3]);

	xml_SetAttributeValue(pXmlKeys->m_strValSection1Key, oElement, m_strValSection[0]);
	xml_SetAttributeValue(pXmlKeys->m_strValSection2Key, oElement, m_strValSection[1]);
	xml_SetAttributeValue(pXmlKeys->m_strValSection3Key, oElement, m_strValSection[2]);
	xml_SetAttributeValue(pXmlKeys->m_strStartUpKey, oElement, m_strValSection[3]);

	xml_SetAttributeValue(pXmlKeys->m_strTSection1Key, oElement, m_strTmSection[0]);
	xml_SetAttributeValue(pXmlKeys->m_strTSection2Key, oElement, m_strTmSection[1]);
	xml_SetAttributeValue(pXmlKeys->m_strTSection3Key, oElement, m_strTmSection[2]);
	xml_SetAttributeValue(pXmlKeys->m_strTStartUpKey, oElement, m_strTmSection[3]);

	return 0;
}

void CCharElementInverse::InitAfterRead()
{
}

BOOL CCharElementInverse::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CCharElementInverse *p = (CCharElementInverse*)pObj;


	return TRUE;
}

BOOL CCharElementInverse::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CCharElementInverse *p = (CCharElementInverse*)pDest;
	CCharElement::CopyOwn(pDest);

	p->m_nUseSection[0] = m_nUseSection[0];
	p->m_nUseSection[1] = m_nUseSection[1];
	p->m_nUseSection[2] = m_nUseSection[2];
	p->m_nUseSection[3] = m_nUseSection[3];
	p->m_strValSection[0] = m_strValSection[0];
	p->m_strValSection[1] = m_strValSection[1];
	p->m_strValSection[2] = m_strValSection[2];
	p->m_strValSection[3] = m_strValSection[3];
	p->m_strTmSection[0] = m_strTmSection[0];
	p->m_strTmSection[1] = m_strTmSection[1];
	p->m_strTmSection[2] = m_strTmSection[2];
	p->m_strTmSection[3] = m_strTmSection[3];

	p->m_strTmax = m_strTmax;
	p->m_strXmax = m_strXmax;

	return TRUE;
}

long CCharElementInverse::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CCharElement::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strTmax);
		BinarySerializeCalLen(oBinaryBuffer, m_strXmax);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseSection[1]);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseSection[0]);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseSection[1]);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseSection[2]);
		BinarySerializeCalLen(oBinaryBuffer, m_nUseSection[3]);
		BinarySerializeCalLen(oBinaryBuffer, m_strValSection[0]);
		BinarySerializeCalLen(oBinaryBuffer, m_strValSection[1]);
		BinarySerializeCalLen(oBinaryBuffer, m_strValSection[2]);
		BinarySerializeCalLen(oBinaryBuffer, m_strValSection[3]);
		BinarySerializeCalLen(oBinaryBuffer, m_strTmSection[0]);
		BinarySerializeCalLen(oBinaryBuffer, m_strTmSection[1]);
		BinarySerializeCalLen(oBinaryBuffer, m_strTmSection[2]);
		BinarySerializeCalLen(oBinaryBuffer, m_strTmSection[3]);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strTmax);
		BinarySerializeRead(oBinaryBuffer, m_strXmax);
		BinarySerializeRead(oBinaryBuffer, m_nUseSection[0]);
		BinarySerializeRead(oBinaryBuffer, m_nUseSection[1]);
		BinarySerializeRead(oBinaryBuffer, m_nUseSection[2]);
		BinarySerializeRead(oBinaryBuffer, m_nUseSection[3]);
		BinarySerializeRead(oBinaryBuffer, m_strValSection[0]);
		BinarySerializeRead(oBinaryBuffer, m_strValSection[1]);
		BinarySerializeRead(oBinaryBuffer, m_strValSection[2]);
		BinarySerializeRead(oBinaryBuffer, m_strValSection[3]);
		BinarySerializeRead(oBinaryBuffer, m_strTmSection[0]);
		BinarySerializeRead(oBinaryBuffer, m_strTmSection[1]);
		BinarySerializeRead(oBinaryBuffer, m_strTmSection[2]);
		BinarySerializeRead(oBinaryBuffer, m_strTmSection[3]);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strTmax);
		BinarySerializeWrite(oBinaryBuffer, m_strXmax);
		BinarySerializeWrite(oBinaryBuffer, m_nUseSection[0]);
		BinarySerializeWrite(oBinaryBuffer, m_nUseSection[1]);
		BinarySerializeWrite(oBinaryBuffer, m_nUseSection[2]);
		BinarySerializeWrite(oBinaryBuffer, m_nUseSection[3]);
		BinarySerializeWrite(oBinaryBuffer, m_strValSection[0]);
		BinarySerializeWrite(oBinaryBuffer, m_strValSection[1]);
		BinarySerializeWrite(oBinaryBuffer, m_strValSection[2]);
		BinarySerializeWrite(oBinaryBuffer, m_strValSection[3]);
		BinarySerializeWrite(oBinaryBuffer, m_strTmSection[0]);
		BinarySerializeWrite(oBinaryBuffer, m_strTmSection[1]);
		BinarySerializeWrite(oBinaryBuffer, m_strTmSection[2]);
		BinarySerializeWrite(oBinaryBuffer, m_strTmSection[3]);
	}

	return 0;
}

CString CCharElementInverse::ReturnXml()
{
	ASSERT (FALSE);
	CString str;
//	str.Format(_T("Inverse angle=\"%s\" forward-reach=\"%s\" offset=\"%s\""),m_strAngle.GetString(),m_strForwardReach.GetString(),m_strOffset.GetString());
	return str;
}

void CCharElementInverse::Draw(CDC *pDC)   //圆特性曲线
{

}


CXDrawBase* CCharElementInverse::CreateDrawElement()
{	
	CXDrawPolyline *pNew = new CXDrawPolyline();
	m_pDataRef = pNew;	

	CXDrawData_Points::DataCopy(pNew);

	return (CXDrawBase*)m_pDataRef;
}

void CCharElementInverse::CalInversePolyline()
{
	m_nPoints = 0;//每次计算，需要将当前使用的点数清零，否则就持续累加
	double dx = 0, dTime = 0;
	SetPointsMax(200); //初始化为200点
	BOOL bTrue = TRUE;

	//计算反时限部分
	while (bTrue)
	{
		bTrue = IncreaseX(dx);
		dTime = CalInverse(dx);

		if (dTime < 0)
		{
			continue;
		}

		if (dTime > m_fTmax)
		{
			continue;
		}

		if (!HasPoints())
		{
			ExpandPointsMax(50);
		}

		AddPoint(dx, dTime);
	}

	AddSectionPoints();
}

void CCharElementInverse::AddSectionPoints()
{
	if (m_nUseSection[2])
	{
		AddPointEx(m_fValSection[2], m_fTmSection[2]);
		AddPointEx(m_fValSection[1], m_fTmSection[2]);
		AddPointEx(m_fValSection[1], m_fTmSection[1]);
		AddPointEx(m_fValSection[0], m_fTmSection[1]);
		AddPointEx(m_fValSection[0], m_fTmSection[0]);
		AddPointEx(m_fValSection[0]*10, m_fTmSection[0]);
	}	
	else if (m_nUseSection[1])
	{
		AddPointEx(m_fValSection[1], m_fTmSection[1]);
		AddPointEx(m_fValSection[0], m_fTmSection[1]);
		AddPointEx(m_fValSection[0], m_fTmSection[0]);
		AddPointEx(m_fValSection[0]*10, m_fTmSection[0]);
	}	
	else if (m_nUseSection[0])
	{
		AddPointEx(m_fValSection[0], m_fTmSection[0]);
		AddPointEx(m_fValSection[0]*10, m_fTmSection[0]);
	}	
}

void CCharElementInverse::CalByExpression(BOOL bCalLines, CExBaseList *pDrawList)
{
	CCharacteristic *pChar = (CCharacteristic*)GetAncestor(CHARCLASSID_CCHARACTERISTIC);
	m_bIsAutoClose = pChar->m_nAutoClose;

	//计算自身数据
	CalCharElementExpression(m_strValSection[0], m_fValSection[0], TRUE);
	CalCharElementExpression(m_strValSection[1], m_fValSection[1], TRUE);
	CalCharElementExpression(m_strValSection[2], m_fValSection[2], TRUE);
	CalCharElementExpression(m_strTmSection[0], m_fTmSection[0], TRUE);
	CalCharElementExpression(m_strTmSection[1], m_fTmSection[1], TRUE);
	CalCharElementExpression(m_strTmSection[2], m_fTmSection[2], TRUE);
	CalCharElementExpression(m_strTmax, m_fTmax, TRUE);
	CalCharElementExpression(m_strXmax, m_fXmax, TRUE);

	CalInversePolyline();
}

BOOL CCharElementInverse::IncreaseX(double &dValX)
{
	double dStand;

	if (m_nUseSection[2] == 1)
	{
		dStand = m_fValSection[2];
	}
	else if (m_nUseSection[1] == 1)
	{
		dStand = m_fValSection[1];
	}
	else if (m_nUseSection[0] == 1)
	{
		dStand = m_fValSection[0];
	}
	else
	{
		dStand = 1;
	}

	if (dValX > m_fXmax)
	{//最大值限制
		return FALSE;
	}

	if (dValX > dStand && dStand != 1)	//20211027 SF
	{
		return FALSE;
	}

	if (dValX <= dStand)
	{
		dValX += 0.02*dStand;
	}
	else if (dValX <= dStand*10)
	{
		dValX += 0.2*dStand;
	}
	else if (dValX <= dStand*100)
	{
		dValX += 2*dStand;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

void CCharElementInverse::CalTestLines(UINT nTestLineMode)
{
	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dValue1 = 0.0f,dValue2 = 0.0f;

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);

		pTestLine->m_fXset = pTestLine->m_fPos;
		pTestLine->m_fXb = pTestLine->m_fPos;

		if(pTestLine->m_fPos > m_fValSection[0]
		&& m_nUseSection[0])
		{
			pTestLine->m_fYset = m_fTmSection[0];
		}
		else if(pTestLine->m_fPos < m_fValSection[0]
		&& pTestLine->m_fPos > m_fValSection[1]
		&& m_nUseSection[1])
		{
			pTestLine->m_fYset = m_fTmSection[1];
		}
		else if(pTestLine->m_fPos < m_fValSection[1]
		&& pTestLine->m_fPos > m_fValSection[2]
		&& m_nUseSection[2])
		{
			pTestLine->m_fYset = m_fTmSection[2];
		}
		else
		{
			pTestLine->m_fYset = CalInverse(pTestLine->m_fPos);
		}

//		pTestLine->m_fYb = pTestLine->m_fYset;
		pTestLine->m_fXe = pTestLine->m_fPos;
//		pTestLine->m_fYe = pTestLine->m_fYset;

		dValue1 = log10(pTestLine->m_fYset);
		dValue2 = dValue1 + CharElementInverse_ErrorLenth/2;
		pTestLine->m_fYb = pow(10,dValue2)/* pPoint->m_fY + pCharElementInverse->GetErrorLength()*/;
		dValue2 = dValue1 - CharElementInverse_ErrorLenth/2;
		pTestLine->m_fYe = pow(10,dValue2)/*pPoint->m_fY - pCharElementInverse->GetErrorLength()*/;

		pTestLine->m_fXact = pTestLine->m_fPos;
		pTestLine->m_fYact = pTestLine->m_fYset;
	}
}

/*
<character-area>
	<tests>
		<points from="BeginValue" to="EndValue" step="StepValue"/>
		<test type="user" pos="1.2" rotate-angle="0" angle-def=""/>
	</tests>
	<IEEE dir="" test-points="4" err-len="0.2" err-len-type="0" t-max="3000" x-max="200" use-Section1="1" use-Section2="1" use-Section3="1" use-start="0" Set1="20.000" Set2="10" Set3="1.01" start="0.2" Tset1="0.05" Tset2="0.2" Tset3="1" t-start="100" Tp="39" A="1.0" B="0" P="2.0" Q="1.1025" K1="0" K2="0">
	</IEEE>
</character-area>
*/
//反时限特性，需要根据tests下的points和test，进行曲线计算 
void CCharElementInverse::BeforeCalTestLines()
{
	DeleteAll();
	CCharacterArea *pCharArea = (CCharacterArea *)GetParent();
	CCharElementTestLines *pTestLines = pCharArea->GetCharElementTestLines();

	if (pTestLines == NULL)
	{
		return;
	}

	//根据始值、终止、步长添加测试点
	CXCharElementTestPoints *pTestPoints = pTestLines->GetCharElementTestPoints();
	double dBegin = pTestPoints->m_dFrom;
	double dEnd = pTestPoints->m_dTo;
	double dPos = dBegin;

	if (dBegin > dEnd)
	{
		while (TRUE)
		{
			CCharElementTestLine *pTestLine = new CCharElementTestLine;
			AddNewChild(pTestLine);

			if (dPos <= dEnd)
			{
				pTestLine->m_fPos = dEnd;
				break;
			}

			pTestLine->m_fPos = dPos;
			dPos -= pTestPoints->m_dStep;
		}
	}
	else if(dBegin < dEnd)
	{
		while (TRUE)
		{
			CCharElementTestLine *pTestLine = new CCharElementTestLine;
			AddNewChild(pTestLine);

			if (dPos >= dEnd)
			{
				pTestLine->m_fPos = dEnd;
				break;
			}

			pTestLine->m_fPos = dPos;
			dPos += pTestPoints->m_dStep;
		}
	}
	else
	{
		CCharElementTestLine *pTestLine = new CCharElementTestLine;
		AddNewChild(pTestLine);
		pTestLine->m_fPos = dBegin;
	}

	//添加用户自定义的测试点
	POS pos = pTestLines->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	long nUserPointNum = 0;

	while (pos != NULL)
	{
		pObj = pTestLines->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID != CHARCLASSID_CCHARELEMENTTESTLINE)
		{
			continue;
		}

		nUserPointNum++;
		CCharElementTestLine *pTestLine = (CCharElementTestLine *)pObj;
		CCharElementTestLine *pNew = new CCharElementTestLine;
		pTestLine->CopyOwn(pNew);
		pTestLine->m_nTestLineID = char_GetTestLineID(this,nUserPointNum);
		AddNewChild(pNew);
	}

	SetUserTestPoint(nUserPointNum);
}
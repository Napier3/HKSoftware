//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestBenchs.cpp  CAtsSvrTestBenchs


#include "stdafx.h"
#include "AtsSvrTestBenchs.h"

CAtsSvrTestBenchs::CAtsSvrTestBenchs()
{
	//初始化属性

	//初始化成员变量
}

CAtsSvrTestBenchs::~CAtsSvrTestBenchs()
{
}

long CAtsSvrTestBenchs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestBenchs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CAtsSvrTestBenchs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CAtsSvrTestBenchs::InitAfterRead()
{
}

BOOL CAtsSvrTestBenchs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CAtsSvrTestBenchs *p = (CAtsSvrTestBenchs*)pObj;

	return TRUE;
}

BOOL CAtsSvrTestBenchs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CAtsSvrTestBenchs *p = (CAtsSvrTestBenchs*)pDest;

	return TRUE;
}

CBaseObject* CAtsSvrTestBenchs::Clone()
{
	CAtsSvrTestBenchs *p = new CAtsSvrTestBenchs();
	Copy(p);
	return p;
}

BOOL CAtsSvrTestBenchs::CanPaste(UINT nClassID)
{
	if (nClassID == ATSVRCLASSID_CATSSVRTESTBENCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CAtsSvrTestBenchs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CAtsServiceXmlRWKeys *pXmlKeys = (CAtsServiceXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCAtsSvrTestBenchKey)
	{
		pNew = new CAtsSvrTestBench();
	}

	return pNew;
}

CExBaseObject* CAtsSvrTestBenchs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == ATSVRCLASSID_CATSSVRTESTBENCH)
	{
		pNew = new CAtsSvrTestBench();
	}

	return pNew;
}

void CAtsSvrTestBenchs::CreateAtsServiceMqttClient()
{
	POS pos = GetHeadPosition();
	CAtsSvrTestBench *p = NULL;

	while (pos != NULL)
	{
		p = (CAtsSvrTestBench*)GetNext(pos);

		//测试台SN/AtsCmd/#
		if (!p->CreateAtsServiceMqttClient(_T("#")))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Bench:[%s][%s] Create Failed"), p->m_strName, p->m_strID);
		}
	}
}

CAtsSvrTestBench* CAtsSvrTestBenchs::FindBenchByDeviceSN(const CString &strDeviceSN)
{
	CAtsSvrTestBench *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CAtsSvrTestBench *)GetNext(pos);

		if (p->FindDvmDevice(strDeviceSN) != NULL)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

CAtsSvrTestBench* CAtsSvrTestBenchs::AddNewBench(const CString &strDeviceSN)
{
	CAtsSvrTestBench *p = new CAtsSvrTestBench();
	p->InitAfterRead();
	AddNewChild(p);
	return p;
}
//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpDevice101.cpp  CEpDevice101


#include "stdafx.h"
#include "EpDevice101.h"

CEpDevice101::CEpDevice101()
{
	//初始化属性

	//初始化成员变量
	m_pYc = NULL;
	m_pYk = NULL;
	m_pYt = NULL;
	m_pYx = NULL;
}

CEpDevice101::~CEpDevice101()
{
}

long CEpDevice101::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CEpDevice::XmlReadOwn(oNode, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDevice101::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CEpDevice::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CEpDevice101::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CEpDevice::SerializeOwn(oBinaryBuffer);

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

void CEpDevice101::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == EPDCLASSID_CEPDEVICENODE101YC)
		{
			m_pYc = (CEpDeviceNode101Yc*)p;
		}
		else if (nClassID == EPDCLASSID_CEPDEVICENODE101YK)
		{
			m_pYk = (CEpDeviceNode101Yk*)p;
		}
		else if (nClassID == EPDCLASSID_CEPDEVICENODE101YT)
		{
			m_pYt = (CEpDeviceNode101Yt*)p;
		}
		else if (nClassID == EPDCLASSID_CEPDEVICENODE101YX)
		{
			m_pYx = (CEpDeviceNode101Yx*)p;
		}
	}

	if (m_pYc == NULL)
	{
		m_pYc = (CEpDeviceNode101Yc*)AddNewChild(new CEpDeviceNode101Yc());
	}

	if (m_pYk == NULL)
	{
		m_pYk = (CEpDeviceNode101Yk*)AddNewChild(new CEpDeviceNode101Yk());
	}

	if (m_pYt == NULL)
	{
		m_pYt = (CEpDeviceNode101Yt*)AddNewChild(new CEpDeviceNode101Yt());
	}

	if (m_pYx == NULL)
	{
		m_pYx = (CEpDeviceNode101Yx*)AddNewChild(new CEpDeviceNode101Yx());
	}

}

BOOL CEpDevice101::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CEpDevice::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CEpDevice101 *p = (CEpDevice101*)pObj;

	return TRUE;
}

BOOL CEpDevice101::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CEpDevice::CopyOwn(pDest);

	CEpDevice101 *p = (CEpDevice101*)pDest;

	return TRUE;
}

CBaseObject* CEpDevice101::Clone()
{
	CEpDevice101 *p = new CEpDevice101();
	Copy(p);
	return p;
}

BOOL CEpDevice101::CanPaste(UINT nClassID)
{
	if (nClassID == EPDCLASSID_CEPDEVICENODE101YC)
	{
		return TRUE;
	}

	if (nClassID == EPDCLASSID_CEPDEVICENODE101YK)
	{
		return TRUE;
	}

	if (nClassID == EPDCLASSID_CEPDEVICENODE101YT)
	{
		return TRUE;
	}

	if (nClassID == EPDCLASSID_CEPDEVICENODE101YX)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CEpDevice101::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CEpDevice_101XmlRWKeys *pXmlKeys = (CEpDevice_101XmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCEpDeviceNode101YcKey)
	{
		pNew = new CEpDeviceNode101Yc();
	}
	else if (strClassID == pXmlKeys->m_strCEpDeviceNode101YkKey)
	{
		pNew = new CEpDeviceNode101Yk();
	}
	else if (strClassID == pXmlKeys->m_strCEpDeviceNode101YtKey)
	{
		pNew = new CEpDeviceNode101Yt();
	}
	else if (strClassID == pXmlKeys->m_strCEpDeviceNode101YxKey)
	{
		pNew = new CEpDeviceNode101Yx();
	}

	return pNew;
}

CExBaseObject* CEpDevice101::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == EPDCLASSID_CEPDEVICENODE101YC)
	{
		pNew = new CEpDeviceNode101Yc();
	}
	else if (nClassID == EPDCLASSID_CEPDEVICENODE101YK)
	{
		pNew = new CEpDeviceNode101Yk();
	}
	else if (nClassID == EPDCLASSID_CEPDEVICENODE101YT)
	{
		pNew = new CEpDeviceNode101Yt();
	}
	else if (nClassID == EPDCLASSID_CEPDEVICENODE101YX)
	{
		pNew = new CEpDeviceNode101Yx();
	}

	return pNew;
}

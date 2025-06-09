//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RtDataTestApp.cpp  CIot_RtDataTestApp


#include "stdafx.h"
#include "Iot_RtDataTestApp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RtDataTestApp::CIot_RtDataTestApp()
{
	//初始化属性
	m_nIndex_Testapp_Data = 0;
	m_nIndex_Testapp = 0;
	::GetLocalTime(&m_tmTime);
	m_nIndex_Data1 = 0;
	m_nIndex_Data2 = 0;
	m_nIndex_Data3 = 0;
	m_nIndex_Data4 = 0;
	m_nIndex_Data5 = 0;
	m_nIndex_Data6 = 0;
	m_nIndex_Data7 = 0;
	m_nIndex_Data8 = 0;
	m_nIndex_Data9 = 0;
	m_nIndex_Data10 = 0;
	m_nIndex_Data11 = 0;
	m_nIndex_Data12 = 0;
	m_nIndex_Data13 = 0;
	m_nIndex_Data14 = 0;
	m_nIndex_Data15 = 0;
	m_nIndex_Data16 = 0;
	m_nIndex_Data17 = 0;
	m_nIndex_Data18 = 0;
	m_nIndex_Data19 = 0;
	m_nIndex_Data20 = 0;

	//初始化成员变量
}

CIot_RtDataTestApp::~CIot_RtDataTestApp()
{
}

long CIot_RtDataTestApp::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Testapp_DataKey, oNode, m_nIndex_Testapp_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_TestappKey, oNode, m_nIndex_Testapp);
	xml_GetAttibuteValue(pXmlKeys->m_strTimeKey, oNode, m_tmTime);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data1Key, oNode, m_nIndex_Data1);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data1Key, oNode, m_strValue_Data1);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data2Key, oNode, m_nIndex_Data2);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data2Key, oNode, m_strValue_Data2);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data3Key, oNode, m_nIndex_Data3);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data3Key, oNode, m_strValue_Data3);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data4Key, oNode, m_nIndex_Data4);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data4Key, oNode, m_strValue_Data4);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data5Key, oNode, m_nIndex_Data5);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data5Key, oNode, m_strValue_Data5);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data6Key, oNode, m_nIndex_Data6);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data6Key, oNode, m_strValue_Data6);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data7Key, oNode, m_nIndex_Data7);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data7Key, oNode, m_strValue_Data7);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data8Key, oNode, m_nIndex_Data8);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data8Key, oNode, m_strValue_Data8);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data9Key, oNode, m_nIndex_Data9);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data9Key, oNode, m_strValue_Data9);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data10Key, oNode, m_nIndex_Data10);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data10Key, oNode, m_strValue_Data10);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data11Key, oNode, m_nIndex_Data11);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data11Key, oNode, m_strValue_Data11);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data12Key, oNode, m_nIndex_Data12);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data12Key, oNode, m_strValue_Data12);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data13Key, oNode, m_nIndex_Data13);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data13Key, oNode, m_strValue_Data13);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data14Key, oNode, m_nIndex_Data14);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data14Key, oNode, m_strValue_Data14);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data15Key, oNode, m_nIndex_Data15);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data15Key, oNode, m_strValue_Data15);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data16Key, oNode, m_nIndex_Data16);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data16Key, oNode, m_strValue_Data16);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data17Key, oNode, m_nIndex_Data17);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data17Key, oNode, m_strValue_Data17);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data18Key, oNode, m_nIndex_Data18);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data18Key, oNode, m_strValue_Data18);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data19Key, oNode, m_nIndex_Data19);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data19Key, oNode, m_strValue_Data19);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data20Key, oNode, m_nIndex_Data20);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data20Key, oNode, m_strValue_Data20);
	return 0;
}

long CIot_RtDataTestApp::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Testapp_DataKey, oElement, m_nIndex_Testapp_Data);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_TestappKey, oElement, m_nIndex_Testapp);
	xml_SetAttributeValue(pXmlKeys->m_strTimeKey, oElement, m_tmTime);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data1Key, oElement, m_nIndex_Data1);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data1Key, oElement, m_strValue_Data1);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data2Key, oElement, m_nIndex_Data2);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data2Key, oElement, m_strValue_Data2);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data3Key, oElement, m_nIndex_Data3);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data3Key, oElement, m_strValue_Data3);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data4Key, oElement, m_nIndex_Data4);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data4Key, oElement, m_strValue_Data4);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data5Key, oElement, m_nIndex_Data5);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data5Key, oElement, m_strValue_Data5);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data6Key, oElement, m_nIndex_Data6);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data6Key, oElement, m_strValue_Data6);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data7Key, oElement, m_nIndex_Data7);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data7Key, oElement, m_strValue_Data7);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data8Key, oElement, m_nIndex_Data8);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data8Key, oElement, m_strValue_Data8);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data9Key, oElement, m_nIndex_Data9);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data9Key, oElement, m_strValue_Data9);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data10Key, oElement, m_nIndex_Data10);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data10Key, oElement, m_strValue_Data10);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data11Key, oElement, m_nIndex_Data11);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data11Key, oElement, m_strValue_Data11);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data12Key, oElement, m_nIndex_Data12);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data12Key, oElement, m_strValue_Data12);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data13Key, oElement, m_nIndex_Data13);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data13Key, oElement, m_strValue_Data13);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data14Key, oElement, m_nIndex_Data14);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data14Key, oElement, m_strValue_Data14);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data15Key, oElement, m_nIndex_Data15);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data15Key, oElement, m_strValue_Data15);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data16Key, oElement, m_nIndex_Data16);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data16Key, oElement, m_strValue_Data16);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data17Key, oElement, m_nIndex_Data17);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data17Key, oElement, m_strValue_Data17);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data18Key, oElement, m_nIndex_Data18);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data18Key, oElement, m_strValue_Data18);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data19Key, oElement, m_nIndex_Data19);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data19Key, oElement, m_strValue_Data19);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data20Key, oElement, m_nIndex_Data20);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data20Key, oElement, m_strValue_Data20);
	return 0;
}

long CIot_RtDataTestApp::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Testapp_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeCalLen(oBinaryBuffer, m_tmTime);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data1);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data1);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data2);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data2);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data3);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data3);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data4);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data4);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data5);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data5);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data6);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data6);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data7);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data7);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data8);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data8);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data9);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data9);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data10);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data10);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data11);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data11);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data12);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data12);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data13);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data13);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data14);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data14);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data15);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data15);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data16);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data16);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data17);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data17);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data18);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data18);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data19);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data19);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data20);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data20);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Testapp_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeRead(oBinaryBuffer, m_tmTime);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data1);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data1);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data2);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data2);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data3);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data3);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data4);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data4);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data5);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data5);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data6);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data6);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data7);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data7);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data8);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data8);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data9);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data9);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data10);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data10);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data11);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data11);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data12);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data12);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data13);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data13);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data14);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data14);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data15);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data15);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data16);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data16);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data17);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data17);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data18);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data18);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data19);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data19);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data20);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data20);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Testapp_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Testapp);
		BinarySerializeWrite(oBinaryBuffer, m_tmTime);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data1);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data1);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data2);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data2);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data3);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data3);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data4);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data4);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data5);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data5);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data6);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data6);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data7);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data7);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data8);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data8);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data9);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data9);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data10);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data10);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data11);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data11);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data12);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data12);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data13);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data13);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data14);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data14);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data15);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data15);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data16);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data16);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data17);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data17);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data18);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data18);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data19);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data19);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data20);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data20);
	}
	return 0;
}

void CIot_RtDataTestApp::InitAfterRead()
{
}

BOOL CIot_RtDataTestApp::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RtDataTestApp *p = (CIot_RtDataTestApp*)pObj;

	if(m_nIndex_Testapp_Data != p->m_nIndex_Testapp_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Testapp != p->m_nIndex_Testapp)
	{
		return FALSE;
	}

	if(m_nIndex_Data1 != p->m_nIndex_Data1)
	{
		return FALSE;
	}

	if(m_strValue_Data1 != p->m_strValue_Data1)
	{
		return FALSE;
	}

	if(m_nIndex_Data2 != p->m_nIndex_Data2)
	{
		return FALSE;
	}

	if(m_strValue_Data2 != p->m_strValue_Data2)
	{
		return FALSE;
	}

	if(m_nIndex_Data3 != p->m_nIndex_Data3)
	{
		return FALSE;
	}

	if(m_strValue_Data3 != p->m_strValue_Data3)
	{
		return FALSE;
	}

	if(m_nIndex_Data4 != p->m_nIndex_Data4)
	{
		return FALSE;
	}

	if(m_strValue_Data4 != p->m_strValue_Data4)
	{
		return FALSE;
	}

	if(m_nIndex_Data5 != p->m_nIndex_Data5)
	{
		return FALSE;
	}

	if(m_strValue_Data5 != p->m_strValue_Data5)
	{
		return FALSE;
	}

	if(m_nIndex_Data6 != p->m_nIndex_Data6)
	{
		return FALSE;
	}

	if(m_strValue_Data6 != p->m_strValue_Data6)
	{
		return FALSE;
	}

	if(m_nIndex_Data7 != p->m_nIndex_Data7)
	{
		return FALSE;
	}

	if(m_strValue_Data7 != p->m_strValue_Data7)
	{
		return FALSE;
	}

	if(m_nIndex_Data8 != p->m_nIndex_Data8)
	{
		return FALSE;
	}

	if(m_strValue_Data8 != p->m_strValue_Data8)
	{
		return FALSE;
	}

	if(m_nIndex_Data9 != p->m_nIndex_Data9)
	{
		return FALSE;
	}

	if(m_strValue_Data9 != p->m_strValue_Data9)
	{
		return FALSE;
	}

	if(m_nIndex_Data10 != p->m_nIndex_Data10)
	{
		return FALSE;
	}

	if(m_strValue_Data10 != p->m_strValue_Data10)
	{
		return FALSE;
	}

	if(m_nIndex_Data11 != p->m_nIndex_Data11)
	{
		return FALSE;
	}

	if(m_strValue_Data11 != p->m_strValue_Data11)
	{
		return FALSE;
	}

	if(m_nIndex_Data12 != p->m_nIndex_Data12)
	{
		return FALSE;
	}

	if(m_strValue_Data12 != p->m_strValue_Data12)
	{
		return FALSE;
	}

	if(m_nIndex_Data13 != p->m_nIndex_Data13)
	{
		return FALSE;
	}

	if(m_strValue_Data13 != p->m_strValue_Data13)
	{
		return FALSE;
	}

	if(m_nIndex_Data14 != p->m_nIndex_Data14)
	{
		return FALSE;
	}

	if(m_strValue_Data14 != p->m_strValue_Data14)
	{
		return FALSE;
	}

	if(m_nIndex_Data15 != p->m_nIndex_Data15)
	{
		return FALSE;
	}

	if(m_strValue_Data15 != p->m_strValue_Data15)
	{
		return FALSE;
	}

	if(m_nIndex_Data16 != p->m_nIndex_Data16)
	{
		return FALSE;
	}

	if(m_strValue_Data16 != p->m_strValue_Data16)
	{
		return FALSE;
	}

	if(m_nIndex_Data17 != p->m_nIndex_Data17)
	{
		return FALSE;
	}

	if(m_strValue_Data17 != p->m_strValue_Data17)
	{
		return FALSE;
	}

	if(m_nIndex_Data18 != p->m_nIndex_Data18)
	{
		return FALSE;
	}

	if(m_strValue_Data18 != p->m_strValue_Data18)
	{
		return FALSE;
	}

	if(m_nIndex_Data19 != p->m_nIndex_Data19)
	{
		return FALSE;
	}

	if(m_strValue_Data19 != p->m_strValue_Data19)
	{
		return FALSE;
	}

	if(m_nIndex_Data20 != p->m_nIndex_Data20)
	{
		return FALSE;
	}

	if(m_strValue_Data20 != p->m_strValue_Data20)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RtDataTestApp::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RtDataTestApp *p = (CIot_RtDataTestApp*)pDest;

	p->m_nIndex_Testapp_Data = m_nIndex_Testapp_Data;
	p->m_nIndex_Testapp = m_nIndex_Testapp;
	p->m_tmTime = m_tmTime;
	p->m_nIndex_Data1 = m_nIndex_Data1;
	p->m_strValue_Data1 = m_strValue_Data1;
	p->m_nIndex_Data2 = m_nIndex_Data2;
	p->m_strValue_Data2 = m_strValue_Data2;
	p->m_nIndex_Data3 = m_nIndex_Data3;
	p->m_strValue_Data3 = m_strValue_Data3;
	p->m_nIndex_Data4 = m_nIndex_Data4;
	p->m_strValue_Data4 = m_strValue_Data4;
	p->m_nIndex_Data5 = m_nIndex_Data5;
	p->m_strValue_Data5 = m_strValue_Data5;
	p->m_nIndex_Data6 = m_nIndex_Data6;
	p->m_strValue_Data6 = m_strValue_Data6;
	p->m_nIndex_Data7 = m_nIndex_Data7;
	p->m_strValue_Data7 = m_strValue_Data7;
	p->m_nIndex_Data8 = m_nIndex_Data8;
	p->m_strValue_Data8 = m_strValue_Data8;
	p->m_nIndex_Data9 = m_nIndex_Data9;
	p->m_strValue_Data9 = m_strValue_Data9;
	p->m_nIndex_Data10 = m_nIndex_Data10;
	p->m_strValue_Data10 = m_strValue_Data10;
	p->m_nIndex_Data11 = m_nIndex_Data11;
	p->m_strValue_Data11 = m_strValue_Data11;
	p->m_nIndex_Data12 = m_nIndex_Data12;
	p->m_strValue_Data12 = m_strValue_Data12;
	p->m_nIndex_Data13 = m_nIndex_Data13;
	p->m_strValue_Data13 = m_strValue_Data13;
	p->m_nIndex_Data14 = m_nIndex_Data14;
	p->m_strValue_Data14 = m_strValue_Data14;
	p->m_nIndex_Data15 = m_nIndex_Data15;
	p->m_strValue_Data15 = m_strValue_Data15;
	p->m_nIndex_Data16 = m_nIndex_Data16;
	p->m_strValue_Data16 = m_strValue_Data16;
	p->m_nIndex_Data17 = m_nIndex_Data17;
	p->m_strValue_Data17 = m_strValue_Data17;
	p->m_nIndex_Data18 = m_nIndex_Data18;
	p->m_strValue_Data18 = m_strValue_Data18;
	p->m_nIndex_Data19 = m_nIndex_Data19;
	p->m_strValue_Data19 = m_strValue_Data19;
	p->m_nIndex_Data20 = m_nIndex_Data20;
	p->m_strValue_Data20 = m_strValue_Data20;
	return TRUE;
}

CBaseObject* CIot_RtDataTestApp::Clone()
{
	CIot_RtDataTestApp *p = new CIot_RtDataTestApp();
	Copy(p);
	return p;
}

CBaseObject* CIot_RtDataTestApp::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RtDataTestApp *p = new CIot_RtDataTestApp();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RtDataTestApp::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Testapp_DataKey, m_nIndex_Testapp_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->GetFieldValue(pXmlKeys->m_strTimeKey, m_tmTime);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data1Key, m_nIndex_Data1);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data1Key, m_strValue_Data1);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data2Key, m_nIndex_Data2);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data2Key, m_strValue_Data2);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data3Key, m_nIndex_Data3);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data3Key, m_strValue_Data3);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data4Key, m_nIndex_Data4);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data4Key, m_strValue_Data4);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data5Key, m_nIndex_Data5);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data5Key, m_strValue_Data5);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data6Key, m_nIndex_Data6);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data6Key, m_strValue_Data6);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data7Key, m_nIndex_Data7);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data7Key, m_strValue_Data7);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data8Key, m_nIndex_Data8);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data8Key, m_strValue_Data8);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data9Key, m_nIndex_Data9);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data9Key, m_strValue_Data9);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data10Key, m_nIndex_Data10);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data10Key, m_strValue_Data10);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data11Key, m_nIndex_Data11);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data11Key, m_strValue_Data11);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data12Key, m_nIndex_Data12);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data12Key, m_strValue_Data12);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data13Key, m_nIndex_Data13);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data13Key, m_strValue_Data13);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data14Key, m_nIndex_Data14);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data14Key, m_strValue_Data14);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data15Key, m_nIndex_Data15);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data15Key, m_strValue_Data15);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data16Key, m_nIndex_Data16);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data16Key, m_strValue_Data16);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data17Key, m_nIndex_Data17);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data17Key, m_strValue_Data17);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data18Key, m_nIndex_Data18);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data18Key, m_strValue_Data18);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data19Key, m_nIndex_Data19);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data19Key, m_strValue_Data19);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data20Key, m_nIndex_Data20);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data20Key, m_strValue_Data20);
	return 0;
}

long CIot_RtDataTestApp::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Testapp_DataKey, m_nIndex_Testapp_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_TestappKey, m_nIndex_Testapp);
	pRecordset->SetFieldValue(pXmlKeys->m_strTimeKey, m_tmTime);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data1Key, m_nIndex_Data1);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data1Key, m_strValue_Data1);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data2Key, m_nIndex_Data2);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data2Key, m_strValue_Data2);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data3Key, m_nIndex_Data3);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data3Key, m_strValue_Data3);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data4Key, m_nIndex_Data4);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data4Key, m_strValue_Data4);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data5Key, m_nIndex_Data5);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data5Key, m_strValue_Data5);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data6Key, m_nIndex_Data6);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data6Key, m_strValue_Data6);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data7Key, m_nIndex_Data7);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data7Key, m_strValue_Data7);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data8Key, m_nIndex_Data8);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data8Key, m_strValue_Data8);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data9Key, m_nIndex_Data9);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data9Key, m_strValue_Data9);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data10Key, m_nIndex_Data10);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data10Key, m_strValue_Data10);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data11Key, m_nIndex_Data11);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data11Key, m_strValue_Data11);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data12Key, m_nIndex_Data12);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data12Key, m_strValue_Data12);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data13Key, m_nIndex_Data13);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data13Key, m_strValue_Data13);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data14Key, m_nIndex_Data14);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data14Key, m_strValue_Data14);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data15Key, m_nIndex_Data15);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data15Key, m_strValue_Data15);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data16Key, m_nIndex_Data16);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data16Key, m_strValue_Data16);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data17Key, m_nIndex_Data17);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data17Key, m_strValue_Data17);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data18Key, m_nIndex_Data18);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data18Key, m_strValue_Data18);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data19Key, m_nIndex_Data19);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data19Key, m_strValue_Data19);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data20Key, m_nIndex_Data20);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data20Key, m_strValue_Data20);
	return 0;
}

BOOL CIot_RtDataTestApp::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	return TRUE;
}


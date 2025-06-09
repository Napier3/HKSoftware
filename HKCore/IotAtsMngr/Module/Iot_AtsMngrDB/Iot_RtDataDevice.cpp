//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RtDataDevice.cpp  CIot_RtDataDevice


#include "stdafx.h"
#include "Iot_RtDataDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIot_RtDataDevice::CIot_RtDataDevice()
{
	//初始化属性
	m_nIndex_Sample_Data = 0;
	m_nIndex_Sample = 0;
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
	m_nIndex_Data21 = 0;
	m_nIndex_Data22 = 0;
	m_nIndex_Data23 = 0;
	m_nIndex_Data24 = 0;
	m_nIndex_Data25 = 0;
	m_nIndex_Data26 = 0;
	m_nIndex_Data27 = 0;
	m_nIndex_Data29 = 0;
	m_nIndex_Data30 = 0;

	//初始化成员变量
}

CIot_RtDataDevice::~CIot_RtDataDevice()
{
}

long CIot_RtDataDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Sample_DataKey, oNode, m_nIndex_Sample_Data);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_SampleKey, oNode, m_nIndex_Sample);
	xml_GetAttibuteValue(pXmlKeys->m_strNumber_Sample_DevKey, oNode, m_strNumber_Sample_Dev);
	xml_GetAttibuteValue(pXmlKeys->m_strSn_Sample_DevKey, oNode, m_strSn_Sample_Dev);
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
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data21Key, oNode, m_nIndex_Data21);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data21Key, oNode, m_strValue_Data21);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data22Key, oNode, m_nIndex_Data22);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data22Key, oNode, m_strValue_Data22);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data23Key, oNode, m_nIndex_Data23);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data23Key, oNode, m_strValue_Data23);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data24Key, oNode, m_nIndex_Data24);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data24Key, oNode, m_strValue_Data24);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data25Key, oNode, m_nIndex_Data25);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data25Key, oNode, m_strValue_Data25);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data26Key, oNode, m_nIndex_Data26);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data26Key, oNode, m_strValue_Data26);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data27Key, oNode, m_nIndex_Data27);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data27Key, oNode, m_strValue_Data27);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data28Key, oNode, m_strIndex_Data28);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data28Key, oNode, m_strValue_Data28);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data29Key, oNode, m_nIndex_Data29);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data29Key, oNode, m_strValue_Data29);
	xml_GetAttibuteValue(pXmlKeys->m_strIndex_Data30Key, oNode, m_nIndex_Data30);
	xml_GetAttibuteValue(pXmlKeys->m_strValue_Data30Key, oNode, m_strValue_Data30);
	return 0;
}

long CIot_RtDataDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIndex_Sample_DataKey, oElement, m_nIndex_Sample_Data);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_SampleKey, oElement, m_nIndex_Sample);
	xml_SetAttributeValue(pXmlKeys->m_strNumber_Sample_DevKey, oElement, m_strNumber_Sample_Dev);
	xml_SetAttributeValue(pXmlKeys->m_strSn_Sample_DevKey, oElement, m_strSn_Sample_Dev);
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
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data21Key, oElement, m_nIndex_Data21);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data21Key, oElement, m_strValue_Data21);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data22Key, oElement, m_nIndex_Data22);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data22Key, oElement, m_strValue_Data22);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data23Key, oElement, m_nIndex_Data23);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data23Key, oElement, m_strValue_Data23);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data24Key, oElement, m_nIndex_Data24);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data24Key, oElement, m_strValue_Data24);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data25Key, oElement, m_nIndex_Data25);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data25Key, oElement, m_strValue_Data25);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data26Key, oElement, m_nIndex_Data26);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data26Key, oElement, m_strValue_Data26);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data27Key, oElement, m_nIndex_Data27);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data27Key, oElement, m_strValue_Data27);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data28Key, oElement, m_strIndex_Data28);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data28Key, oElement, m_strValue_Data28);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data29Key, oElement, m_nIndex_Data29);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data29Key, oElement, m_strValue_Data29);
	xml_SetAttributeValue(pXmlKeys->m_strIndex_Data30Key, oElement, m_nIndex_Data30);
	xml_SetAttributeValue(pXmlKeys->m_strValue_Data30Key, oElement, m_strValue_Data30);
	return 0;
}

long CIot_RtDataDevice::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Sample_Data);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Sample);
		BinarySerializeCalLen(oBinaryBuffer, m_strNumber_Sample_Dev);
		BinarySerializeCalLen(oBinaryBuffer, m_strSn_Sample_Dev);
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
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data21);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data21);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data22);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data22);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data23);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data23);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data24);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data24);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data25);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data25);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data26);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data26);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data27);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data27);
		BinarySerializeCalLen(oBinaryBuffer, m_strIndex_Data28);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data28);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data29);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data29);
		BinarySerializeCalLen(oBinaryBuffer, m_nIndex_Data30);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue_Data30);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Sample_Data);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Sample);
		BinarySerializeRead(oBinaryBuffer, m_strNumber_Sample_Dev);
		BinarySerializeRead(oBinaryBuffer, m_strSn_Sample_Dev);
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
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data21);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data21);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data22);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data22);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data23);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data23);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data24);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data24);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data25);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data25);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data26);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data26);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data27);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data27);
		BinarySerializeRead(oBinaryBuffer, m_strIndex_Data28);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data28);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data29);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data29);
		BinarySerializeRead(oBinaryBuffer, m_nIndex_Data30);
		BinarySerializeRead(oBinaryBuffer, m_strValue_Data30);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Sample_Data);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Sample);
		BinarySerializeWrite(oBinaryBuffer, m_strNumber_Sample_Dev);
		BinarySerializeWrite(oBinaryBuffer, m_strSn_Sample_Dev);
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
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data21);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data21);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data22);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data22);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data23);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data23);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data24);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data24);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data25);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data25);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data26);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data26);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data27);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data27);
		BinarySerializeWrite(oBinaryBuffer, m_strIndex_Data28);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data28);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data29);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data29);
		BinarySerializeWrite(oBinaryBuffer, m_nIndex_Data30);
		BinarySerializeWrite(oBinaryBuffer, m_strValue_Data30);
	}
	return 0;
}

void CIot_RtDataDevice::InitAfterRead()
{
}

BOOL CIot_RtDataDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIot_RtDataDevice *p = (CIot_RtDataDevice*)pObj;

	if(m_nIndex_Sample_Data != p->m_nIndex_Sample_Data)
	{
		return FALSE;
	}

	if(m_nIndex_Sample != p->m_nIndex_Sample)
	{
		return FALSE;
	}

	if(m_strNumber_Sample_Dev != p->m_strNumber_Sample_Dev)
	{
		return FALSE;
	}

	if(m_strSn_Sample_Dev != p->m_strSn_Sample_Dev)
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

	if(m_nIndex_Data21 != p->m_nIndex_Data21)
	{
		return FALSE;
	}

	if(m_strValue_Data21 != p->m_strValue_Data21)
	{
		return FALSE;
	}

	if(m_nIndex_Data22 != p->m_nIndex_Data22)
	{
		return FALSE;
	}

	if(m_strValue_Data22 != p->m_strValue_Data22)
	{
		return FALSE;
	}

	if(m_nIndex_Data23 != p->m_nIndex_Data23)
	{
		return FALSE;
	}

	if(m_strValue_Data23 != p->m_strValue_Data23)
	{
		return FALSE;
	}

	if(m_nIndex_Data24 != p->m_nIndex_Data24)
	{
		return FALSE;
	}

	if(m_strValue_Data24 != p->m_strValue_Data24)
	{
		return FALSE;
	}

	if(m_nIndex_Data25 != p->m_nIndex_Data25)
	{
		return FALSE;
	}

	if(m_strValue_Data25 != p->m_strValue_Data25)
	{
		return FALSE;
	}

	if(m_nIndex_Data26 != p->m_nIndex_Data26)
	{
		return FALSE;
	}

	if(m_strValue_Data26 != p->m_strValue_Data26)
	{
		return FALSE;
	}

	if(m_nIndex_Data27 != p->m_nIndex_Data27)
	{
		return FALSE;
	}

	if(m_strValue_Data27 != p->m_strValue_Data27)
	{
		return FALSE;
	}

	if(m_strIndex_Data28 != p->m_strIndex_Data28)
	{
		return FALSE;
	}

	if(m_strValue_Data28 != p->m_strValue_Data28)
	{
		return FALSE;
	}

	if(m_nIndex_Data29 != p->m_nIndex_Data29)
	{
		return FALSE;
	}

	if(m_strValue_Data29 != p->m_strValue_Data29)
	{
		return FALSE;
	}

	if(m_nIndex_Data30 != p->m_nIndex_Data30)
	{
		return FALSE;
	}

	if(m_strValue_Data30 != p->m_strValue_Data30)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIot_RtDataDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIot_RtDataDevice *p = (CIot_RtDataDevice*)pDest;

	p->m_nIndex_Sample_Data = m_nIndex_Sample_Data;
	p->m_nIndex_Sample = m_nIndex_Sample;
	p->m_strNumber_Sample_Dev = m_strNumber_Sample_Dev;
	p->m_strSn_Sample_Dev = m_strSn_Sample_Dev;
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
	p->m_nIndex_Data21 = m_nIndex_Data21;
	p->m_strValue_Data21 = m_strValue_Data21;
	p->m_nIndex_Data22 = m_nIndex_Data22;
	p->m_strValue_Data22 = m_strValue_Data22;
	p->m_nIndex_Data23 = m_nIndex_Data23;
	p->m_strValue_Data23 = m_strValue_Data23;
	p->m_nIndex_Data24 = m_nIndex_Data24;
	p->m_strValue_Data24 = m_strValue_Data24;
	p->m_nIndex_Data25 = m_nIndex_Data25;
	p->m_strValue_Data25 = m_strValue_Data25;
	p->m_nIndex_Data26 = m_nIndex_Data26;
	p->m_strValue_Data26 = m_strValue_Data26;
	p->m_nIndex_Data27 = m_nIndex_Data27;
	p->m_strValue_Data27 = m_strValue_Data27;
	p->m_strIndex_Data28 = m_strIndex_Data28;
	p->m_strValue_Data28 = m_strValue_Data28;
	p->m_nIndex_Data29 = m_nIndex_Data29;
	p->m_strValue_Data29 = m_strValue_Data29;
	p->m_nIndex_Data30 = m_nIndex_Data30;
	p->m_strValue_Data30 = m_strValue_Data30;
	return TRUE;
}

CBaseObject* CIot_RtDataDevice::Clone()
{
	CIot_RtDataDevice *p = new CIot_RtDataDevice();
	Copy(p);
	return p;
}

CBaseObject* CIot_RtDataDevice::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIot_RtDataDevice *p = new CIot_RtDataDevice();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CIot_RtDataDevice::DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Sample_DataKey, m_nIndex_Sample_Data);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_SampleKey, m_nIndex_Sample);
	pRecordset->GetFieldValue(pXmlKeys->m_strNumber_Sample_DevKey, m_strNumber_Sample_Dev);
	pRecordset->GetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
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
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data21Key, m_nIndex_Data21);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data21Key, m_strValue_Data21);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data22Key, m_nIndex_Data22);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data22Key, m_strValue_Data22);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data23Key, m_nIndex_Data23);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data23Key, m_strValue_Data23);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data24Key, m_nIndex_Data24);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data24Key, m_strValue_Data24);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data25Key, m_nIndex_Data25);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data25Key, m_strValue_Data25);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data26Key, m_nIndex_Data26);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data26Key, m_strValue_Data26);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data27Key, m_nIndex_Data27);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data27Key, m_strValue_Data27);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data28Key, m_strIndex_Data28);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data28Key, m_strValue_Data28);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data29Key, m_nIndex_Data29);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data29Key, m_strValue_Data29);
	pRecordset->GetFieldValue(pXmlKeys->m_strIndex_Data30Key, m_nIndex_Data30);
	pRecordset->GetFieldValue(pXmlKeys->m_strValue_Data30Key, m_strValue_Data30);
	return 0;
}

long CIot_RtDataDevice::DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;

	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Sample_DataKey, m_nIndex_Sample_Data);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_SampleKey, m_nIndex_Sample);
	pRecordset->SetFieldValue(pXmlKeys->m_strNumber_Sample_DevKey, m_strNumber_Sample_Dev);
	pRecordset->SetFieldValue(pXmlKeys->m_strSn_Sample_DevKey, m_strSn_Sample_Dev);
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
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data21Key, m_nIndex_Data21);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data21Key, m_strValue_Data21);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data22Key, m_nIndex_Data22);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data22Key, m_strValue_Data22);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data23Key, m_nIndex_Data23);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data23Key, m_strValue_Data23);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data24Key, m_nIndex_Data24);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data24Key, m_strValue_Data24);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data25Key, m_nIndex_Data25);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data25Key, m_strValue_Data25);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data26Key, m_nIndex_Data26);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data26Key, m_strValue_Data26);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data27Key, m_nIndex_Data27);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data27Key, m_strValue_Data27);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data28Key, m_strIndex_Data28);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data28Key, m_strValue_Data28);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data29Key, m_nIndex_Data29);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data29Key, m_strValue_Data29);
	pRecordset->SetFieldValue(pXmlKeys->m_strIndex_Data30Key, m_nIndex_Data30);
	pRecordset->SetFieldValue(pXmlKeys->m_strValue_Data30Key, m_strValue_Data30);
	return 0;
}

BOOL CIot_RtDataDevice::DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue)
{
	CIot_AtsMngrXmlRWKeys *pXmlKeys = (CIot_AtsMngrXmlRWKeys*)pXmlRWKeys;


	return TRUE;
}


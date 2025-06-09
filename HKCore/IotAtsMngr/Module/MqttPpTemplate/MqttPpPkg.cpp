//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpPkg.cpp  CMqttPpPkg


#include "stdafx.h"
#include "MqttPpPkg.h"
#include "../SensorProtocol/SttGlobalSensorDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpPkg::CMqttPpPkg()
{
	//初始化属性

	//初始化成员变量
}

CMqttPpPkg::~CMqttPpPkg()
{
}

long CMqttPpPkg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmData::XmlReadOwn(oNode, pXmlRWKeys);
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDsKey, oNode, m_strDs);
	return 0;
}

long CMqttPpPkg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CMqttPpCfgXmlRWKeys *pXmlKeys = (CMqttPpCfgXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDsKey, oElement, m_strDs);
	return 0;
}

long CMqttPpPkg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDvmData::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDs);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strDs);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDs);
	}
	return 0;
}

void CMqttPpPkg::InitAfterRead()
{
}

BOOL CMqttPpPkg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDvmData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMqttPpPkg *p = (CMqttPpPkg*)pObj;

	if(m_strDs != p->m_strDs)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CMqttPpPkg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmData::CopyOwn(pDest);

	CMqttPpPkg *p = (CMqttPpPkg*)pDest;

	p->m_strDs = m_strDs;
	return TRUE;
}

CBaseObject* CMqttPpPkg::Clone()
{
	CMqttPpPkg *p = new CMqttPpPkg();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpPkg::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpPkg *p = new CMqttPpPkg();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpPkg::CanPaste(UINT nClassID)
{
	return FALSE;
}

BOOL CMqttPpPkg::IsMatchPkg(int nPkgType,int nCtrlType,int nRequestSetFlag)
{
	long nPkgType2 = 0,nCtrlType2 = 0,nRequestSetFlag2 = 0;

	GetValueByID(SENSOR_MODEL_ID_PacketType,nPkgType2);
	GetValueByID(SENSOR_MODEL_ID_CtrlType,nCtrlType2);
	GetValueByID(SENSOR_MODEL_ID_RequestSetFlag,nRequestSetFlag2);

	if(nPkgType != nPkgType2)
	{
		return FALSE;
	}

	if (IsPacketMonitorType(nPkgType))
	{//如果是监测或报警报文
		return TRUE;
	}

	//类型相等且但不是监测或报警报文，则控制类型是否相等
	if(nCtrlType != nCtrlType2)
	{
		return FALSE;
	}

	if (nRequestSetFlag == nRequestSetFlag2)
	{
		return TRUE;
	}

	//类型和控制类型相同，但是参数配置类型不等
	if (IsPacketCtrlType(nPkgType))
	{
		if((nCtrlType == SENSOR_PKG_CTRLTYPE_MONITORQUERY)
			|| (nCtrlType == SENSOR_PKG_CTRLTYPE_RESET)
			|| (nCtrlType == SENSOR_PKG_CTRLTYPE_REQUESTADJUSTTIME))
		{//监测数据查询、复位、请求校时，参数配置类型无效
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMqttPpPkg::IsReadAinPkg()
{
	long nPkgType = 0;

	GetValueByID(SENSOR_MODEL_ID_PacketType,nPkgType);

	return IsPacketMonitorType(nPkgType);
}
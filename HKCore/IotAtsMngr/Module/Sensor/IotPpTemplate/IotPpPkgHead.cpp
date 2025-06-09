//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IotPpPkgHead.cpp  CIotPpPkgHead


#include "stdafx.h"
#include "IotPpPkgHead.h"
#include "../SensorProtocol/SttGlobalSensorDef.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CIotPpPkgHead::CIotPpPkgHead()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIotPpPkgHead::~CIotPpPkgHead()
{
}

long CIotPpPkgHead::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDsKey, oNode, m_strDs);
	return 0;
}

long CIotPpPkgHead::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDsKey, oElement, m_strDs);
	return 0;
}

long CIotPpPkgHead::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CIotPpPkgHead::InitAfterRead()
{
}

BOOL CIotPpPkgHead::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIotPpPkgHead *p = (CIotPpPkgHead*)pObj;

	if(m_strDs != p->m_strDs)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIotPpPkgHead::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIotPpPkgHead *p = (CIotPpPkgHead*)pDest;

	p->m_strDs = m_strDs;
	return TRUE;
}

CBaseObject* CIotPpPkgHead::Clone()
{
	CIotPpPkgHead *p = new CIotPpPkgHead();
	Copy(p);
	return p;
}

CBaseObject* CIotPpPkgHead::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CIotPpPkgHead *p = new CIotPpPkgHead();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CIotPpPkgHead::CanPaste(UINT nClassID)
{
	if (nClassID == IOTCLASSID_CIOTPPVALUE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CIotPpPkgHead::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIOTPPXmlRWKeys *pXmlKeys = (CIOTPPXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIotPpValueKey)
	{
		pNew = new CIotPpValue();
	}

	return pNew;
}

CExBaseObject* CIotPpPkgHead::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IOTCLASSID_CIOTPPVALUE)
	{
		pNew = new CIotPpValue();
	}

	return pNew;
}

BOOL CIotPpPkgHead::IsMatchPkg(int nPkgType,int nCtrlType,int nRequestSetFlag)
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
	{//����Ǽ��򱨾�����
		return TRUE;
	}

	//��������ҵ����Ǽ��򱨾����ģ�����������Ƿ����
	if(nCtrlType != nCtrlType2)
	{
		return FALSE;
	}

	if (nRequestSetFlag == nRequestSetFlag2)
	{
		return TRUE;
	}

	//���ͺͿ���������ͬ�����ǲ����������Ͳ���
	if (IsPacketCtrlType(nPkgType))
	{
		if((nCtrlType == SENSOR_PKG_CTRLTYPE_MONITORQUERY)
			|| (nCtrlType == SENSOR_PKG_CTRLTYPE_RESET)
			|| (nCtrlType == SENSOR_PKG_CTRLTYPE_REQUESTADJUSTTIME))
		{//������ݲ�ѯ����λ������Уʱ����������������Ч
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CIotPpPkgHead::GetValueByID(const CString &strValueID, long &nValue)
{
	CIotPpValue *pValue = (CIotPpValue *)FindByID(strValueID);
	if (pValue == NULL)
	{
		return FALSE;
	}

	nValue = CString_To_long(pValue->m_strValue);
	return TRUE;
}
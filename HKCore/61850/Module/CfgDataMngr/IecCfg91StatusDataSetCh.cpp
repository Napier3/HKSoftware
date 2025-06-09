//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StatusDataSetCh.cpp  CIecCfg91StatusDataSetCh


#include "stdafx.h"
#include "IecCfg91StatusDataSetCh.h"

CIecCfg91StatusDataSetCh::CIecCfg91StatusDataSetCh()
{
	//初始化属性
	m_nSValue = 0;
	m_nIndex = 0;
	m_nQValue = 0;
	m_nQValue = 0;

	//初始化成员变量
}

CIecCfg91StatusDataSetCh::~CIecCfg91StatusDataSetCh()
{
}

long CIecCfg91StatusDataSetCh::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSValueKey, oNode, m_nSValue);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strQValueKey, oNode, m_nQValue);

	if (m_strID.GetLength() == 0)
	{
		m_strID = m_strName;
	}

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CIecCfg91StatusDataSetCh::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSValueKey, oElement, m_nSValue);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strQValueKey, oElement, m_nQValue);
	return 0;
}

BOOL CIecCfg91StatusDataSetCh::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfg91StatusDataSetCh *p = (CIecCfg91StatusDataSetCh*)pObj;

	if(m_nSValue != p->m_nSValue)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_nQValue != p->m_nQValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg91StatusDataSetCh::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg91StatusDataSetCh *p = (CIecCfg91StatusDataSetCh*)pDest;

	p->m_nSValue = m_nSValue;
	p->m_nIndex = m_nIndex;
	p->m_strName = m_strName;
	p->m_nQValue = m_nQValue;
	return TRUE;
}

CBaseObject* CIecCfg91StatusDataSetCh::Clone()
{
	CIecCfg91StatusDataSetCh *p = new CIecCfg91StatusDataSetCh();
	Copy(p);
	return p;
}


/*
hbo_x	<	0xF0, hardware binary channel number is hcn_x
hbo_x:			the value is 0 ~ 3 or 12 ~ 23
	=	0	the hardware binary channel output 1
	=	1	the hardware binary channel output 2
	…
hbo_x	≥	0xF0, no hardware binary channel to be mapped to status data
hbo_x	=	0xF0, the status data will be set to 0
	=	0xF2, the status data is set by user
*/

/*
<value id="none" name="不使用" index="0"/> 
<value id="val-0" name="0" index="1"/> 
<value id="val-1" name="1" index="2"/> 
<value id="BOut1" name="开出量1" index="3"/> 
<value id="BOut2" name="开出量2" index="4"/> 
<value id="BOut3" name="开出量3" index="5"/> 
<value id="BOut4" name="开出量4" index="6"/>
*/

WORD CIecCfg91StatusDataSetCh::Get_hbo()
{
// 	CDataType *pDataType = CIecGlobalDataMngr::GetBOutChDataType();
// 	ASSERT(pDataType != NULL);
//	CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByIndex( m_nSValue );

	if (m_nSValue == 0)
	{
		return 0xF0;
	}
	else if (m_nSValue == 1)
	{
		return 0xF0;
	}
	else if (m_nSValue == 2)
	{
		return 0xF2;
	}
	else if (m_nSValue <= 6)
	{
		return (WORD)(m_nSValue - 3);
	}
	else
	{
		return 0xF0;
	}
}


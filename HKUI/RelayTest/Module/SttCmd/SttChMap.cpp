//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttChMap.cpp  CSttChMap


#include "stdafx.h"
#include "SttChMap.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttChMap::CSttChMap()
{
	//初始化属性

	//初始化成员变量
	m_nRsIndex = -1;
}

CSttChMap::~CSttChMap()
{
}

long CSttChMap::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAliasKey, oNode, m_strAlias);
	xml_GetAttibuteValue(pXmlKeys->m_strRsIndexKey, oNode, m_nRsIndex);
	GetRsIndexFromID();//对于老的配置文件，不包含re-index属性的，需要从m_strID中获取

	return 0;
}

long CSttChMap::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strAliasKey, oElement, m_strAlias);
	GetRsIndexFromID();//对于为-1，需要从m_strID中获取
	xml_SetAttributeValue(pXmlKeys->m_strRsIndexKey, oElement, m_nRsIndex);
	return 0;
}

long CSttChMap::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strAlias);
		BinarySerializeCalLen(oBinaryBuffer, m_nRsIndex);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strAlias);
		BinarySerializeRead(oBinaryBuffer, m_nRsIndex);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strAlias);
		BinarySerializeWrite(oBinaryBuffer, m_nRsIndex);
	}
	return 0;
}

void CSttChMap::InitAfterRead()
{
}

BOOL CSttChMap::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttChMap *p = (CSttChMap*)pObj;

	if(m_strAlias != p->m_strAlias)
	{
		return FALSE;
	}

	if(m_nRsIndex != p->m_nRsIndex)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttChMap::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttChMap *p = (CSttChMap*)pDest;

	p->m_strAlias = m_strAlias;
	p->m_nRsIndex = m_nRsIndex;
	return TRUE;
}

CBaseObject* CSttChMap::Clone()
{
	CSttChMap *p = new CSttChMap();
	Copy(p);
	return p;
}

CBaseObject* CSttChMap::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttChMap *p = new CSttChMap();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttChMap::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTHDCHS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttChMap::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttHdChsKey)
	{
		pNew = new CSttHdChs();
	}

	return pNew;
}

CExBaseObject* CSttChMap::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTHDCHS)
	{
		pNew = new CSttHdChs();
	}

	return pNew;
}

long CSttChMap::GetRsIndexFromID()
{
	if (m_strID.IsEmpty())
	{
		m_nRsIndex = -1;
		return m_nRsIndex;
	}

	CString strTmp;
	strTmp = m_strID.Mid(1);
	m_nRsIndex = CString_To_long(strTmp);
	return m_nRsIndex;
}

long CSttChMap::GetMapChsType()
{
	POS pos = GetHeadPosition();
	CSttHdChs *pHdChs = NULL;
//	CString strName;
	long nType = 0;
	int nIndex = 0;

	while(pos)
	{
		pHdChs = (CSttHdChs *)GetNext(pos);

		if (pHdChs->GetCount()<=0)
		{
			continue;
		}

		if (pHdChs->m_strID == STT_MODULETYPE_ID_ANALOG)
			{
			nType += 1;
		}
		else if (pHdChs->m_strID == STT_MODULETYPE_ID_DIGITAL)
		{
			nType += 2;
			}
		else if (pHdChs->m_strID == STT_MODULETYPE_ID_WEEK)
			{
			nType += 4;
			}

	}
	return nType;

}

long Global_GetCurrChType_Single(long nMixChType,long nHasAnalog,long nHasDigital,long nWeek)
{
	if ((nMixChType%2) == 0)
	{
		nHasAnalog = 0;
	}

	if (((nMixChType>>1)%2) == 0)
	{
		nHasDigital = 0;
	}

	if (((nMixChType>>2)%2) == 0)
	{
		nWeek = 0;
	}

	if ((nHasAnalog + nHasDigital + nWeek)>1)
	{
		return MACROTYPE_Mix;
	}
	else if (nHasAnalog)
	{
		return MACROTYPE_Analog;
	}
	else if (nHasDigital)
	{
		return MACROTYPE_Digital;
	}
	else if (nWeek)
	{
		return MACROTYPE_Week;
	}


	return 0;

}

BOOL CSttChMap::HasHdCh(const CString &strType, const CString &strChID)
{
	CSttHdChs *pHdChs = (CSttHdChs*)FindByID(strType);

	if (pHdChs == NULL)
	{
		return FALSE;
	}

	CSttHdCh *pFind = (CSttHdCh*)pHdChs->FindByID(strChID);

	return (pFind != NULL);
}

BOOL CSttChMap::HasHdCh()
{
	BOOL bHasFind = FALSE;
	POS pos = GetHeadPosition();
	CSttHdChs *pHdChs = NULL;

	while(pos)
	{
		pHdChs = (CSttHdChs *)GetNext(pos);

		if (pHdChs->GetCount()>0)
		{
			bHasFind = TRUE;
			break;
		}
	}

	return bHasFind;
}

CSttHdCh* CSttChMap::FindHdCh(const CString &strType, const CString &strChID)
{
	CSttHdChs *pHdChs = (CSttHdChs*)FindByID(strType);

	if (pHdChs == NULL)
	{
		return NULL;
	}

	CSttHdCh *pFind = (CSttHdCh*)pHdChs->FindByID(strChID);

	return pFind;
}

CSttHdCh* CSttChMap::AddHdMapCh(const CString &strHdChsID,const CString &strHdRsName,const CString &strHdRsID)
{
	CSttHdChs *pChild = (CSttHdChs*)FindByID(strHdChsID);

	if (pChild == NULL)
	{
		pChild = new CSttHdChs;
		pChild->m_strID = strHdChsID;
		pChild->m_strName = strHdChsID;
		AddNewChild(pChild);
	}

	return pChild->AddHdCh(strHdRsName,strHdRsID);
}
BOOL CSttChMap::HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek)
{
	CSttHdChs *pHdChs = NULL;

	if (nHasAnalog&&(HasMapHdResource(STT_MODULETYPE_ID_ANALOG)))
	{
		return TRUE;
	}

	if (nHasDigital&&(HasMapHdResource(STT_MODULETYPE_ID_DIGITAL)))
	{
		return TRUE;
	}

	if (nHasWeek&&(HasMapHdResource(STT_MODULETYPE_ID_WEEK)))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CSttChMap::HasMapHdResource(const CString &strHdChsID)
{
	CSttHdChs *pHdChs = (CSttHdChs*)FindByID(strHdChsID);

	if (pHdChs == NULL)
	{
		return FALSE;
	}

	return (pHdChs->GetCount()>0);
}

BOOL CSttChMap::HasMapHdResource( const char* cHdChsID )
{
	CString strHdChsID;
	strHdChsID.Format(_T("%s"),cHdChsID);

	return HasMapHdResource(strHdChsID);
}

CSttHdChs* CSttChMap::GetHdChs(const CString &strHdChsID)
{
	CSttHdChs *pHdChs = (CSttHdChs*)FindByID(strHdChsID);
	return pHdChs;
}

CSttHdChs* CSttChMap::GetHdChs( const char* cHdChsID )
{
	CString strHdChsID;
	strHdChsID.Format(_T("%s"),cHdChsID);

	return GetHdChs(strHdChsID);
}

void CSttChMap::SetWeakRateValue(float fWeakRateValue,BOOL bPrimaryValue)
{
	CSttHdChs *pHdChs = GetHdChs(STT_MODULETYPE_ID_WEEK);

	if (pHdChs == NULL)
	{
		return;
	}

	POS pos = pHdChs->GetHeadPosition();
	CSttHdCh *pHdCh = NULL;

	while(pos)
	{
		pHdCh = (CSttHdCh *)pHdChs->GetNext(pos);
		pHdCh->SetWeakRateValue(fWeakRateValue,bPrimaryValue);
	}
}

BOOL CSttChMap::IsVoltageCh()
{
	return m_strID.GetAt(0) == 'U';
}

BOOL CSttChMap::IsCurrentCh()
{
	return m_strID.GetAt(0) == 'I';
}

CString CSttChMap::GetHdChsString(const CString &strHdChsID)
{
	CSttHdChs *pHdChs = (CSttHdChs*)FindByID(strHdChsID);

	if (pHdChs == NULL)
	{
		return _T("");
	}

	CString strHdChs;
	POS pos = pHdChs->GetHeadPosition();
	CSttHdCh *pObj = NULL;

	while(pos)
	{
		pObj = (CSttHdCh*)pHdChs->GetNext(pos);

		if (pHdChs->m_strID == STT_MODULETYPE_ID_DIGITAL)
		{
			strHdChs.AppendFormat(_T("%s;"),pObj->m_strID.GetString());
		} 
		else
		{
			strHdChs.AppendFormat(_T("%s;"),pObj->m_strID.GetString());
		}
	}

	return strHdChs;
}

void CSttChMap::InitHdChs_ByString(CString &strHdChsString,const CString &strHdChsID)
{
	CSttHdChs *pHdChs = (CSttHdChs*)FindByID(strHdChsID);

	if (pHdChs == NULL)
	{
		pHdChs = new CSttHdChs;
		pHdChs->m_strID = strHdChsID;
		pHdChs->m_strName = strHdChsID;
		AddNewChild(pHdChs);
	}

	char zfChType= m_strID.GetAt(0);
	pHdChs->InitHdChsByString(zfChType,strHdChsString);
}

BOOL CSttChMap::HasAnalogCurrModuleHdCh(long nModuleIndex)
{
	CSttHdChs *pHdChs = GetHdChs(STT_MODULETYPE_ID_ANALOG);

	if (pHdChs == NULL)
	{
		return FALSE;
	}

	return pHdChs->HasAnalogCurrModuleHdCh(nModuleIndex);
}

BOOL CSttChMap::GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur)
{
	CSttHdChs *pHdChs = GetHdChs(STT_MODULETYPE_ID_WEEK);

	if (pHdChs == NULL)
	{
		return FALSE;
	}

	POS pos = pHdChs->GetHeadPosition();
	CSttHdCh *pHdCh = NULL;
	BOOL bHasSet = FALSE;
	double dTmpValue = 0.0f;

	while(pos)
	{
		pHdCh = (CSttHdCh *)pHdChs->GetNext(pos);
		dTmpValue = pHdCh->GetPrimaryValue_Float();

		if (IsVoltageCh()&&(dMaxVol < dTmpValue))
		{
			dMaxVol = dTmpValue;
			bHasSet = TRUE;
		}
		else if (IsCurrentCh()&&(dMaxCur < dTmpValue))
		{
			dMaxCur = dTmpValue;
			bHasSet = TRUE;
		}
	}

	return bHasSet;
}

void CSttChMap::UpdateWeekRateValue()
{
	CSttHdChs *pHdChs = GetHdChs(STT_MODULETYPE_ID_WEEK);

	if (pHdChs == NULL)
	{
        return;
	}

	POS pos = pHdChs->GetHeadPosition();
	CSttHdCh *pHdCh = NULL;

	while(pos)
	{
		pHdCh = (CSttHdCh *)pHdChs->GetNext(pos);
		pHdCh->UpdateWeekRateValue();
	}
}

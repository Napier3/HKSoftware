//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttChMaps.cpp  CSttChMaps


#include "stdafx.h"
#include "SttChMaps.h"
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttChMaps::CSttChMaps()
{
	//��ʼ������

	//��ʼ����Ա����
}

CSttChMaps::~CSttChMaps()
{
}

long CSttChMaps::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttChMaps::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttChMaps::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CSttChMaps::InitAfterRead()
{
}

BOOL CSttChMaps::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttChMaps *p = (CSttChMaps*)pObj;

	return TRUE;
}

BOOL CSttChMaps::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttChMaps *p = (CSttChMaps*)pDest;

	return TRUE;
}

CBaseObject* CSttChMaps::Clone()
{
	CSttChMaps *p = new CSttChMaps();
	Copy(p);
	return p;
}

CBaseObject* CSttChMaps::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttChMaps *p = new CSttChMaps();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttChMaps::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTCHMAP)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttChMaps::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttChMapKey)
	{
		pNew = new CSttChMap();
	}

	return pNew;
}

CExBaseObject* CSttChMaps::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTCHMAP)
	{
		pNew = new CSttChMap();
	}

	return pNew;
}


CSttChMap* CSttChMaps::FindByHdCh(long nType, const CString &strChID)
{
	char *pszType = stt_get_module_id_by_type(nType);
	CString strType;
	strType = pszType;

	return FindByHdCh(strType, strChID);
}

CSttChMap* CSttChMaps::FindByHdCh(const CString &strType, const CString &strChID)
{
	POS pos = GetHeadPosition();
	CSttChMap *pChMap = NULL;
	CSttChMap *pChMapFind = NULL;
	CSttHdCh *pHdCh = NULL;

	while (pos != NULL)
	{
		pChMap = (CSttChMap *)GetNext(pos);

		if (pChMap->HasHdCh(strType, strChID))
		{
			pChMapFind = pChMap;
			break;
		}
	}

	return pChMapFind;
}

CSttChMap* CSttChMaps::FindByHdCh(const CString &strType, const CString &strChID,float &fHdChCoef)
{
	POS pos = GetHeadPosition();
	CSttChMap *pChMap = NULL;
	CSttChMap *pChMapFind = NULL;
	CSttHdCh *pHdCh = NULL;

	while (pos != NULL)
	{
		pChMap = (CSttChMap *)GetNext(pos);
		pHdCh = pChMap->FindHdCh(strType, strChID);

		if (pHdCh != NULL)
		{
			pChMapFind = pChMap;
			fHdChCoef = pHdCh->m_fCoef;
			break;
		}
	}

	return pChMapFind;
}

CSttChMap* CSttChMaps::GetChMap(const CString &strSoftRsID)
{
	CSttChMap* pChild = (CSttChMap*)FindByID(strSoftRsID);
	return pChild;
}

CSttChMap* CSttChMaps::AddChMap(const CString &strSoftRsName,const CString &strSoftRsID)
{
	CSttChMap* pChild = new CSttChMap;
	pChild->m_strName = strSoftRsName;
	pChild->m_strAlias = strSoftRsName;
	pChild->m_strID = strSoftRsID;
	pChild->GetRsIndexFromID();
	AddNewChild(pChild);
	return pChild;
}

CSttChMap* CSttChMaps::AddChMap_FindByID(const CString &strSoftRsName,const CString &strSoftRsID)
{
	CSttChMap* pChild = (CSttChMap*)FindByID(strSoftRsID);

	if (pChild == NULL)
	{
		pChild = new CSttChMap;
		AddNewChild(pChild);
	}

	pChild->m_strName = strSoftRsName;
	pChild->m_strAlias = strSoftRsName;
	pChild->m_strID = strSoftRsID;
	pChild->GetRsIndexFromID();
	return pChild;
}

void CSttChMaps::SetChCountU(long nChNum)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	long nChIndex = 0;
	CString strTmp;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.GetAt(0) == 'U')
		{
			strTmp = pSttChMap->m_strID.Mid(1);
			nChIndex = CString_To_long(strTmp);

			if (nChIndex>nChNum)
			{
				Delete(pSttChMap);
			}
		}
	}
}

void CSttChMaps::SetChCountI(long nChNum)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	long nChIndex = 0;
	CString strTmp;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.GetAt(0) == 'I')
		{
			strTmp = pSttChMap->m_strID.Mid(1);
			nChIndex = CString_To_long(strTmp);

			if (nChIndex>nChNum)
			{
				Delete(pSttChMap);
			}
		}
	}
}

BOOL CSttChMaps::OpenChMapsFile(const CString &strChMapsPath)
{
	DeleteAll();
	return OpenXmlFile(strChMapsPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

BOOL CSttChMaps::SaveChMapsFile(const CString &strChMapsPath)
{
	return SaveXmlFile(strChMapsPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

BOOL CSttChMaps::HasAnalogCurrModuleHdCh(long nModuleIndex)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	long nChIndex = 0;
	CString strTmp;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.GetAt(0) == 'I')
		{
			if (pSttChMap->HasAnalogCurrModuleHdCh(nModuleIndex))
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

void CSttChMaps::SortByRsIndex()
{
	POS pos1 = GetHeadPosition();
	POS pos2 = pos1;
	CSttChMap *p1 = NULL, *p2 = NULL;
	BOOL bNeedChangePos = FALSE;

	while (pos1 != NULL)
	{
		p1 = (CSttChMap*)GetAt(pos1);
		pos2 = pos1;
		GetNext(pos2);//�ӵ�ǰͨ���������

		while (pos2 != NULL)
		{
			p2  = (CSttChMap*)GetAt(pos2);
			bNeedChangePos = FALSE;

			if (p1->m_strID.GetAt(0) == p2->m_strID.GetAt(0))//���ͨ��������ͬ
			{
				if (p1->m_nRsIndex > p2->m_nRsIndex)//��һ����RsIndex���ڵڶ���,����Ҫ����
				{
					bNeedChangePos = TRUE;
				}
			}
			else if (p1->IsCurrentCh())//��ͨ�����Ͳ�ͬ�������,���p1Ϊ����ͨ��,��Ҳ��Ҫ����λ��
			{
				bNeedChangePos = TRUE;
			}

			if (bNeedChangePos)//�����Ҫ����λ�ã������λ�ý���
			{
				SetAt(pos1, p2);
				SetAt(pos2, p1);
				p1 = p2;
			}

			GetNext(pos2);//�����ƶ�һ������֤��ǰ�����е�Moduleλ��Ϊ��С��
		}

		GetNext(pos1);
	}
}

BOOL CSttChMaps::HasMapHdResource(long nHasAnalog,long nHasDigital,long nHasWeek)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	BOOL bHasFind = FALSE;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->HasMapHdResource(nHasAnalog,nHasDigital,nHasWeek))
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CSttChMaps::GetMaxValue_WeekRates(double &dMaxVol,double &dMaxCur)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	BOOL bHasSet = FALSE;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->GetMaxValue_WeekRates(dMaxVol,dMaxCur))
		{
			bHasSet = TRUE;
		}
	}

	return bHasSet;
}

BOOL CSttChMaps::SetChMapsString(const CString &strChMaps)
{
	DeleteAll();
	return SetXml(strChMaps, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

long CSttChMaps::GetChNum(const CString &strChID)
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	long nNum = 0;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);

		if (pSttChMap->m_strID.Find(strChID) == 0)
		{
			nNum++;
		}
	}

	return nNum;
}

void CSttChMaps::UpdateWeekRateValue()
{
	POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);
		pSttChMap->UpdateWeekRateValue();
	}
}
void CSttChMaps::UpdateAliasByName()
{
    POS pos = GetHeadPosition();
	CSttChMap *pSttChMap = NULL;

	while(pos)
	{
		pSttChMap = (CSttChMap *)GetNext(pos);
        pSttChMap->m_strAlias = pSttChMap->m_strName;
	}
}
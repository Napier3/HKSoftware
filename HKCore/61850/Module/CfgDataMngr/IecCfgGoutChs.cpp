//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChsGout.cpp  CIecCfgChsGout


#include "stdafx.h"
#include "IecCfgGoutChs.h"

CIecCfgGoutChs::CIecCfgGoutChs()
{
	//��ʼ������

	//��ʼ����Ա����
}

CIecCfgGoutChs::~CIecCfgGoutChs()
{
}

long CIecCfgGoutChs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgGoutChs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfgGoutChs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgGoutChs *p = (CIecCfgGoutChs*)pObj;

	return TRUE;
}

BOOL CIecCfgGoutChs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgGoutChs *p = (CIecCfgGoutChs*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgGoutChs::Clone()
{
	CIecCfgGoutChs *p = new CIecCfgGoutChs();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgGoutChs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgGoutChKey)
	{
		pNew = new CIecCfgGoutCh();
	}

	return pNew;
}

CExBaseObject* CIecCfgGoutChs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGGOUTCH)
	{
		pNew = new CIecCfgGoutCh();
	}

	return pNew;
}


CIecCfgDataChBase* CIecCfgGoutChs::CreateChannel()
{
	CIecCfgDataChBase *pNew = new CIecCfgGoutCh();
	return pNew;
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfgGoutChs::SetAT02D_ChannelID(CExBaseList *pGoutList,long &nCBIndex)//�ܺ�� 20200616  ����AT02����
{
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
//	long nChIndex = 1;
	long nChannelIndex = 1;
	CString strAT02D_ID;

	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
		{
			pIecCfgGoutCh = (CIecCfgGoutCh*)pCurObj;
			pIecCfgGoutCh->m_strID.Format(_T("Gout%ld_%ld"),nCBIndex,nChannelIndex);
			nChannelIndex++;
		}
	}
}
#endif
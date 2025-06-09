//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChsGin.cpp  CIecCfgChsGin


#include "stdafx.h"
#include "IecCfgGinChs.h"

CIecCfgGinChs::CIecCfgGinChs()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgGinChs::~CIecCfgGinChs()
{
}

long CIecCfgGinChs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgGinChs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfgGinChs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgGinChs *p = (CIecCfgGinChs*)pObj;

	return TRUE;
}

BOOL CIecCfgGinChs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgGinChs *p = (CIecCfgGinChs*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgGinChs::Clone()
{
	CIecCfgGinChs *p = new CIecCfgGinChs();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgGinChs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgGinChKey)
	{
		pNew = new CIecCfgGinCh();
	}

	return pNew;
}

CExBaseObject* CIecCfgGinChs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFGGINCH)
	{
		pNew = new CIecCfgGinCh();
	}

	return pNew;
}


CIecCfgDataChBase* CIecCfgGinChs::CreateChannel()
{
	CIecCfgDataChBase *pNew = new CIecCfgGinCh();
	return pNew;
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfgGinChs::SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	long nChannelIndex = 1;

	CString strAT02D_ID;  

	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH)
		{
			pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;
			pIecCfgGinCh->m_strID.Format(_T("Gin%ld_%ld"),nCBIndex,nChannelIndex);
			nChannelIndex++;
		}
	}
}
#endif

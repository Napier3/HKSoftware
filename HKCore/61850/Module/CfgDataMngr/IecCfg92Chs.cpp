//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChs92.cpp  CIecCfgChs92


#include "stdafx.h"
#include "IecCfg92Chs.h"

CIecCfg92Chs::CIecCfg92Chs()
{
	//初始化属性

	//初始化成员变量
}

CIecCfg92Chs::~CIecCfg92Chs()
{
}

long CIecCfg92Chs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfg92Chs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfg92Chs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfg92Chs *p = (CIecCfg92Chs*)pObj;

	return TRUE;
}

BOOL CIecCfg92Chs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg92Chs *p = (CIecCfg92Chs*)pDest;

	return TRUE;
}

CBaseObject* CIecCfg92Chs::Clone()
{
	CIecCfg92Chs *p = new CIecCfg92Chs();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg92Chs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfg92ChKey)
	{
		pNew = new CIecCfg92Ch();
	}

	return pNew;
}

CExBaseObject* CIecCfg92Chs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFG92CH)
	{
		pNew = new CIecCfg92Ch();
	}

	return pNew;
}


CIecCfgDataChBase* CIecCfg92Chs::CreateChannel()
{
	CIecCfgDataChBase *pNew = new CIecCfg92Ch();
	return pNew;
}

void CIecCfg92Chs::SetSelState_SelectAll()
{
	CIecCfgDataChBase *pIecCfgCh = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pIecCfgCh = (CIecCfgDataChBase*)GetNext(pos);
		pIecCfgCh->m_nUseFlag = 1;
	}
}

void CIecCfg92Chs::SetSelState_UnSelectAll()
{
	CIecCfgDataChBase *pIecCfgCh = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pIecCfgCh = (CIecCfgDataChBase*)GetNext(pos);
		pIecCfgCh->m_nUseFlag = 0;
	}
}

void CIecCfg92Chs::SetSelState_SelProtCurrAll()
{
	CIecCfgDataSmvChBase *pIecCfgSmvCh = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pIecCfgSmvCh = (CIecCfgDataSmvChBase*)GetNext(pos);

		if ((pIecCfgSmvCh->m_strChType == iecfg_SmvChDataType_Val_Curr)&&(pIecCfgSmvCh->m_strName.Find(_T("测量")) == -1))
		{
			pIecCfgSmvCh->m_nUseFlag = 1;
		}
	}
}

void CIecCfg92Chs::SetSelState_SelMeasCurrAll()
{
	CIecCfgDataSmvChBase *pIecCfgSmvCh = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pIecCfgSmvCh = (CIecCfgDataSmvChBase*)GetNext(pos);

		if ((pIecCfgSmvCh->m_strChType == iecfg_SmvChDataType_Val_Curr)&&(pIecCfgSmvCh->m_strName.Find(_T("测量"))>=0))
		{
			pIecCfgSmvCh->m_nUseFlag = 1;
		}
	}
}

void CIecCfg92Chs::SetSelState_SelVolAll()
{
	CIecCfgDataSmvChBase *pIecCfgSmvCh = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pIecCfgSmvCh = (CIecCfgDataSmvChBase*)GetNext(pos);

		if (pIecCfgSmvCh->m_strChType == iecfg_SmvChDataType_Val_Vol)
		{
			pIecCfgSmvCh->m_nUseFlag = 1;
		}
	}
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfg92Chs::SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Ch *pIecCfg92Ch = NULL;

	long nDelayIndex = 1;
	long nCurChannelIndex = 1;
	long nVolChannelIndex = 1;
// 	long nCurIndex = 1;
// 	long nVolIndex = 1;
	CString strAT02D_ID;

	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CH)
		{
			pIecCfg92Ch = (CIecCfg92Ch*)pCurObj;

			if (pIecCfg92Ch->m_strChType == _T("Curr"))
			{
				strAT02D_ID.Format(_T("SV%ld_I%ld"),nCBIndex,nCurChannelIndex);
				nCurChannelIndex++;

				if (!pIecCfg92Ch->m_strAppChID.IsEmpty())
				{
					strAT02D_ID += _T("_");
					strAT02D_ID += pIecCfg92Ch->m_strAppChID;
				}

				pIecCfg92Ch->m_strID = strAT02D_ID;
			}
			else if (pIecCfg92Ch->m_strChType == _T("Vol"))
			{
				strAT02D_ID.Format(_T("SV%ld_U%ld"),nCBIndex,nVolChannelIndex);
				nVolChannelIndex++;

				if (!pIecCfg92Ch->m_strAppChID.IsEmpty())
				{
//					strAT02D_ID.AppendFormat(_T("_%s"),pIecCfg92Ch->m_strAppChID);

					strAT02D_ID += _T("_");
					strAT02D_ID += pIecCfg92Ch->m_strAppChID;
				}

				pIecCfg92Ch->m_strID = strAT02D_ID;
			}
			else if (pIecCfg92Ch->m_strChType == _T("UTCTime"))
			{
				pIecCfg92Ch->m_strID.Format(_T("SV%ld_T%ld_DelayTRtg"),nCBIndex,nDelayIndex);
				nDelayIndex++;
			}
			else
			{
				pIecCfg92Ch->m_strID = _T("");
			}
		}
	}
}
#endif
//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChs6044.cpp  CIecCfgChs6044


#include "stdafx.h"
#include "IecCfg6044Chs.h"
#include "IecCfg6044CommonChIn.h"

CIecCfg6044Chs::CIecCfg6044Chs()
{
	//初始化属性

	//初始化成员变量
}

CIecCfg6044Chs::~CIecCfg6044Chs()
{
}

long CIecCfg6044Chs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfg6044Chs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfg6044Chs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfg6044Chs *p = (CIecCfg6044Chs*)pObj;

	return TRUE;
}

BOOL CIecCfg6044Chs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg6044Chs *p = (CIecCfg6044Chs*)pDest;

	return TRUE;
}

CBaseObject* CIecCfg6044Chs::Clone()
{
	CIecCfg6044Chs *p = new CIecCfg6044Chs();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg6044Chs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfg6044ChKey)
	{
		pNew = new CIecCfg6044Ch();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfg6044CommonChKey)
	{
		pNew = new CIecCfg6044CommonCh();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfg6044CommonChInKey)
	{
		pNew = new CIecCfg6044CommonChIn();
	}

	return pNew;
}

CExBaseObject* CIecCfg6044Chs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFG6044CH)
	{
		pNew = new CIecCfg6044Ch();
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044COMMONCH)
	{
		pNew = new CIecCfg6044CommonCh();
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044COMMONCHIN)
	{
		pNew = new CIecCfg6044CommonChIn();
	}

	return pNew;
}

CIecCfgDataChBase* CIecCfg6044Chs::CreateChannel()
{
	CIecCfgDataChBase *pNew = NULL;

	if (m_pParent->GetClassID() == CFGCLASSID_CIECCFG6044DATA)
	{
		pNew = new CIecCfg6044Ch();
	}
	else if (m_pParent->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
	{
		pNew = new CIecCfg6044CommonCh();
	}
	else if (m_pParent->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA)
	{
		pNew = new CIecCfg6044CommonChIn();
	}
	else if (m_pParent->GetClassID() == CFGCLASSID_CIECCFG2MDATA)
	{
		pNew = new CIecCfg6044CommonCh();
	}
	else if (m_pParent->GetClassID() == CFGCLASSID_CIECCFG2MINDATA)
	{
		pNew = new CIecCfg6044CommonCh();
	}	
	ASSERT(pNew);
	return pNew;
}


void CIecCfg6044Chs::InitAfterRead()
{
//	SetChannelNum(22);   周宏军  20200510  无需将通道数固定为22通道
}

CString CIecCfg6044Chs::CreateVolCurrChID_AT02D(CExBaseList *pHasModifiedChListRef,const CString &strPrefix,const CString &strSuffix,
												const CString &strChTypeID,long nChProtMeasType)
{
	CString strNewChID;
	long nIndex = 1;

	while(1)
	{
		if (!strSuffix.IsEmpty())
		{
			if (nChProtMeasType == 1)
			{
				strNewChID.Format("%s_%sp%ld_%s",strPrefix.GetString(),strChTypeID.GetString(),nIndex,strSuffix.GetString());
			}
			else if (nChProtMeasType == 2)
			{
				strNewChID.Format("%s_%sm%ld_%s",strPrefix.GetString(),strChTypeID.GetString(),nIndex,strSuffix.GetString());
			}
			else
			{
				strNewChID.Format("%s_%s%ld_%s",strPrefix.GetString(),strChTypeID.GetString(),nIndex,strSuffix.GetString());
			}
		}
		else
		{
			strNewChID.Format("%s_%s%ld",strPrefix.GetString(),strChTypeID.GetString(),nIndex);
		}

		if (pHasModifiedChListRef->FindByID(strNewChID) == NULL)//如果当前ID不存在,则为有效ID
		{
			break;
		}

		nIndex++;
	}

	return strNewChID;
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfg6044Chs::SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex)
{
	CExBaseObject *pCurObj = NULL;
	CIecCfg6044CommonCh *pIecCfg6044CommonCh = NULL;

	long nBinaryIndex = 1;
	long nOtherIndex = 1;
// 	long nCurChannelIndex = 1;
// 	long nVolChannelIndex = 1;
	CString strAT02D_ID,strPrefix,strSuffix;
	strPrefix.Format(_T("SV%ld"),nCBIndex);
	CExBaseList oHasModifiedChListRef;//已经修改ID对应通道链表

	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if ((pCurObj->GetClassID() != CFGCLASSID_CIECCFG6044COMMONCH) &&
			(pCurObj->GetClassID() != CFGCLASSID_CIECCFG6044COMMONCHIN))
		{
			continue;
		}

		pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pCurObj;
		strSuffix = "";

		if ((pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_DCCur)
			||(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
			||(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
			||(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Curr)
			||(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure))
		{
//			nCurChannelIndex++;

			if (!pIecCfg6044CommonCh->m_strAppChID.IsEmpty())
			{
//				strAT02D_ID += _T("_");
				strSuffix = pIecCfg6044CommonCh->m_strAppChID;
			}

			if ((pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)||
				(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure))
			{
				pIecCfg6044CommonCh->m_strID = CreateVolCurrChID_AT02D(&oHasModifiedChListRef,strPrefix,strSuffix,"I",2);
			} 
			else
			{
				pIecCfg6044CommonCh->m_strID = CreateVolCurrChID_AT02D(&oHasModifiedChListRef,strPrefix,strSuffix,"I",1);
			}
		}
		else if ((pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Vol)
			||(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_DCVol)
			||(pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_6Vol))
		{
// 			strAT02D_ID.Format(_T("SV%ld_U%ld"),nCBIndex,nVolChannelIndex);
// 			nVolChannelIndex++;

			if (!pIecCfg6044CommonCh->m_strAppChID.IsEmpty())
			{
// 				strAT02D_ID += _T("_");
// 				strAT02D_ID += pIecCfg6044CommonCh->m_strAppChID;
				strSuffix = pIecCfg6044CommonCh->m_strAppChID;
			}

			pIecCfg6044CommonCh->m_strID = CreateVolCurrChID_AT02D(&oHasModifiedChListRef,strPrefix,strSuffix,"U");
		}
		else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_StateValue)
		{
			pIecCfg6044CommonCh->m_strID.Format(_T("SV%ld_B%ld"),nCBIndex,nBinaryIndex);
			nBinaryIndex++;
		}
		else if (pIecCfg6044CommonCh->m_strChType == iecfg_SmvChDataType_Val_Other)
		{
			pIecCfg6044CommonCh->m_strID.Format(_T("SV%ld_O%ld"),nCBIndex,nOtherIndex);
			nOtherIndex++;
		}
		else
		{
			pIecCfg6044CommonCh->m_strID = _T("");
		}

		oHasModifiedChListRef.AddTail(pCurObj);
	}

	oHasModifiedChListRef.RemoveAll();
}
#endif
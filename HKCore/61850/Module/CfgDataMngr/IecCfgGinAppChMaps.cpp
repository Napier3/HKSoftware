//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfgChsGin.cpp  CIecCfgChsGin


#include "stdafx.h"
#include "IecCfgGinAppChMaps.h"
#include "../../../Module/System/StringTokenizerU.h"

CIecCfgGinAppChMaps::CIecCfgGinAppChMaps()
{
	
}

CIecCfgGinAppChMaps::~CIecCfgGinAppChMaps()
{
}

void CIecCfgGinAppChMaps::ReleaseMaps()
{
	POS pos = GetHeadPosition();
	CIecCfgGinAppChMap *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CIecCfgGinAppChMap *)GetNext(pos);
		pMap->m_pIecCfgGinCh = NULL;
	}
}

void CIecCfgGinAppChMaps::InitDataTypes()
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(iecfg_GinAppChDataType);
	ASSERT (pDataType != NULL);

	if (pDataType == NULL)
	{
		return;
	}

	POS pos = pDataType->GetHeadPosition();
	CDataTypeValue *pValue = NULL;
	CIecCfgGinAppChMap *pNew = NULL;
	CExBaseObject *pCurrChMap = NULL;

	pValue = (CDataTypeValue *)pDataType->GetHead();

	if (pValue != NULL)
	{
		if (pValue->m_strID == g_strAppChID_None)
		{
			pValue = (CDataTypeValue *)pDataType->GetNext(pos);
		}
	}

	while (pos != NULL)
	{
		pValue = (CDataTypeValue *)pDataType->GetNext(pos);
		pCurrChMap = FindByID(pValue->m_strID);

		if (pCurrChMap == NULL)//zhouhj 20220218 ��ֹ�ظ����
		{
			pNew = new CIecCfgGinAppChMap();
			pNew->InitByDataTypeValue(pValue);
			AddNewChild(pNew);
		}
		else
		{
			pCurrChMap->m_strName = pValue->m_strName;//20220505 zhouhj  ���л�iecfg�ļ�ʱ,�л���ͨ��ӳ������,����¶�Ӧ����
		}
	}
}

CIecCfgGinAppChMap* CIecCfgGinAppChMaps::Bind(const CString &strBin, CIecCfgGinCh *pGinCh)
{
	CIecCfgGinAppChMap *pMap = (CIecCfgGinAppChMap*)FindByID(strBin);

	if (pMap == NULL)
	{
		return NULL;
	}

	pMap->m_pIecCfgGinCh = pGinCh;

	return pMap;
}

void CIecCfgGinAppChMaps::InitMaps(CExBaseList *pGinDatas)
{
	POS pos = pGinDatas->GetHeadPosition();
	CExBaseObject *pData = NULL;

	while (pos != NULL)
	{
		pData = pGinDatas->GetNext(pos);

		if (pData->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			InitMaps((CIecCfgGinData*)pData);
		}
	}
}

void CIecCfgGinAppChMaps::InitMaps(CIecCfgGinData *pGinData)
{
	CIecCfgGinChs *pChs = (CIecCfgGinChs*)pGinData->m_pCfgChs;
	POS pos = pChs->GetHeadPosition();
	CIecCfgGinCh *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfgGinCh *)pChs->GetNext(pos);
		InitMaps(pGinData, pCh);
	}
}

void CIecCfgGinAppChMaps::InitMaps(CIecCfgGinData *pGinData, CIecCfgGinCh *pGinCh)
{
	CIecCfgGinAppChMap *pMap = NULL;
	CStringTokenizerU oToken;

	if (pGinCh->m_strAppChID == g_strAppChID_None)
	{
		return;
	}

	if (pGinCh->m_strAppChID == _T("0"))
	{
		pGinCh->m_strAppChID == g_strAppChID_None;
		return;
	}

	if (pGinCh->m_strAppChID.Find(_T(";")) == -1)//zhouhj 20201230 Ϊ�� ֱ�ӷ��أ����ڷֶ�ʱ��û��";"��β
	{
		pGinCh->m_strAppChID == g_strAppChID_None;
//        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰͨ��ӳ�����(%s),ȱ��\';\'��ʶ��."),pGinCh->m_strAppChID.GetString());
		return;
	}

	oToken.Init(pGinCh->m_strAppChID, ';');
	const wchar_t *pBinID = NULL;
	long nIndex = 0;
	DWORD dwBinValue = 0;
	CString strBinID;

	while (oToken.HasMoreElements())
	{
		pBinID = oToken.NextToken();
		strBinID = pBinID;

		pMap = (CIecCfgGinAppChMap*)FindByID(strBinID);
		//ASSERT (pMap != NULL);

		if (pMap != NULL)
		{
			if (pMap->m_pIecCfgGinCh != NULL)//����ÿ����Ѿ�ӳ����ĳ��ͨ��,���ܽ����ظ�ӳ��
			{
				CIecCfgGinData *p = (CIecCfgGinData*)pGinCh->GetAncestor(CFGCLASSID_CIECCFGGINDATA);

#ifdef NOT_USE_XLANGUAGE
                CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��%s$%s���롾%s$%s��ʹ����ͬ�Ŀ��롾%s��")
                    , pGinData->m_strName.GetString(), pGinCh->m_strName.GetString(), p->m_strName.GetString()
                    , pMap->m_pIecCfgGinCh->m_strName.GetString(), strBinID.GetString());
#else
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_SameOpening.GetString()/* _T("��%s$%s���롾%s$%s��ʹ����ͬ�Ŀ��롾%s��")*/
					, pGinData->m_strName.GetString(), pGinCh->m_strName.GetString(), p->m_strName.GetString(), pMap->m_pIecCfgGinCh->m_strName.GetString(), strBinID.GetString());
#endif
			}
			else
			{
				pMap->m_pIecCfgGinCh = pGinCh;
			}

		}
	}
}



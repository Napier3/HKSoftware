//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvSequence.cpp  CDsvSequence


#include "stdafx.h"
#include "DsvSequence.h"

#include "DsvElement.h"
#include "DsvChoice.h"
#include "../../XLanguage/XLanguageResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDsvSequence::CDsvSequence()
{
	//初始化属性

	//初始化成员变量
}

CDsvSequence::~CDsvSequence()
{
}

long CDsvSequence::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDsvBase::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvSequence::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDsvBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDsvSequence::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDsvBase::SerializeOwn(oBinaryBuffer);
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

void CDsvSequence::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posCurr = pos;
	CDsvElement *pElement = NULL;
	CDsvAnyElement *pAnyElement = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		p = GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDSVELEMENT)
		{
			pElement = (CDsvElement*)p;

			if (pElement->IsAnyDsvObjectEx())
			{
				pAnyElement = new CDsvAnyElement();
				pAnyElement->m_strName = pElement->m_strName;
				pAnyElement->m_strID = pElement->m_strID;
				pAnyElement->m_strMode = pElement->m_strMode;
				SetAt(posCurr, pAnyElement);
				delete pElement;
			}
		}
	}
}

BOOL CDsvSequence::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDsvBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvSequence *p = (CDsvSequence*)pObj;

	return TRUE;
}

BOOL CDsvSequence::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDsvBase::CopyOwn(pDest);

	CDsvSequence *p = (CDsvSequence*)pDest;

	return TRUE;
}

CBaseObject* CDsvSequence::Clone()
{
	CDsvSequence *p = new CDsvSequence();
	Copy(p);
	return p;
}

BOOL CDsvSequence::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDSVELEMENT)
	{
		return TRUE;
	}

	if (nClassID == DVMCLASSID_CDSVSEQUENCE)
	{
		return TRUE;
	}

	if (nClassID == DVMCLASSID_CDSVCHOICE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDsvSequence::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDsvElementKey)
	{
		pNew = new CDsvElement();
	}
	else if (strClassID == pXmlKeys->m_strCDsvAnyElementKey)
	{
		pNew = new CDsvAnyElement();
	}
	else if (strClassID == pXmlKeys->m_strCDsvSequenceKey)
	{
		pNew = new CDsvSequence();
	}
	else if (strClassID == pXmlKeys->m_strCDsvChoiceKey)
	{
		pNew = new CDsvChoice();
	}

	return pNew;
}

CExBaseObject* CDsvSequence::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DVMCLASSID_CDSVELEMENT)
	{
		pNew = new CDsvElement();
	}
	else if (nClassID == DVMCLASSID_CDSVANYELEMENT)
	{
		pNew = new CDsvAnyElement();
	}
	else if (nClassID == DVMCLASSID_CDSVSEQUENCE)
	{
		pNew = new CDsvSequence();
	}
	else if (nClassID == DVMCLASSID_CDSVCHOICE)
	{
		pNew = new CDsvChoice();
	}

	return pNew;
}

CDsvAnyElement* CDsvSequence::AddAnyElement(const CString &strText, long nOption, long nUnbound)
{
	CDsvAnyElement *pNew = new CDsvAnyElement();

	pNew->m_strMode = strText;
	pNew->m_nMinOcc = nOption;
	pNew->m_nMaxOcc = nUnbound;
	pNew->m_strName = g_sLangTxt_ArbitrElement/*_T("任意元素")*/;
	AddNewChild(pNew);
	
	return pNew;
}

CDsvElement* CDsvSequence::AddElement(const CString &strText, long nOption, long nUnbound)
{
	CDsvElement *pNew = new CDsvElement();

	pNew->m_strMode = strText;
	pNew->m_nMinOcc = nOption;
	pNew->m_nMaxOcc = nUnbound;
	AddNewChild(pNew);

	return pNew;
}
CDsvChoice*  CDsvSequence::AddChoice(long nOption, long nUnbound)
{
	CDsvChoice *pNew = new CDsvChoice();

	pNew->m_nMinOcc = nOption;
	pNew->m_nMaxOcc = nUnbound;
	AddNewChild(pNew);

	return pNew;
}

CDsvSequence* CDsvSequence::AddSequence(long nOption, long nUnbound)
{
	CDsvSequence *pNew = new CDsvSequence();

	pNew->m_nMinOcc = nOption;
	pNew->m_nMaxOcc = nUnbound;
	AddNewChild(pNew);

	return pNew;
}

BOOL CDsvSequence::DsValidate(CDvmDataset *pDataset, POS &posDataset, CValues *pRptValues, CDsvBase *pPrevAnlyDsvObj)
{
	m_bDsvSucc = TRUE;

	if (posDataset == NULL)
	{
		if (m_nMinOcc > 0)
		{
			m_bDsvSucc = FALSE;
		}

		return m_bDsvSucc;
	}

	POS posDsv = GetHeadPosition();
	CDsvBase *pDsv = NULL;
	POS posBack = posDataset;
	POS posPrev = NULL;

	while (posDsv != NULL)
	{
		pDsv = (CDsvBase *)GetNext(posDsv);

		//如果是“任意元素”的element，则进行下一个验证
		if (pDsv->IsAnyDsvObject())
		{
			pPrevAnlyDsvObj = pDsv;
			continue;
		}

		posPrev = posDataset;

		if (!pDsv->DsValidate(pDataset, posDataset, pRptValues, pPrevAnlyDsvObj))
		{
			m_bDsvSucc = FALSE;
			//验证不成功，跳过当前，继续下一个Dsv验证
			posDataset = posPrev;
		}
		else
		{
		}
	}

	return m_bDsvSucc;
}


BOOL CDsvSequence::DsvQuery(CDvmDataset *pDataset, CValues *pRptValues)
{
	m_bDsvSucc = TRUE;
	POS posDsv = GetHeadPosition();
	CDsvBase *pDsv = NULL;

	if (pDataset->GetCount() == 0)
	{
		if (posDsv != NULL)
		{
			if (m_nMinOcc > 0)
			{
				m_bDsvSucc = FALSE;
			}
		}

		return m_bDsvSucc;
	}


	while (posDsv != NULL)
	{
		pDsv = (CDsvBase *)GetNext(posDsv);

		//如果是“任意元素”的element，则进行下一个验证
		if (pDsv->IsAnyDsvObject())
		{
			continue;
		}

		if (!pDsv->DsvQuery(pDataset, pRptValues))
		{
			m_bDsvSucc = FALSE;
		}
	}

	return m_bDsvSucc;
}

BOOL CDsvSequence::DsValidate(CDvmDataset *pDataset, CValues *pRptValues, BOOL bValidateHead)
{
	POS pos = pDataset->GetHeadPosition();
	BOOL bTrue = FALSE;

	if (pos == NULL)
	{
		POS posDsv = GetHeadPosition();
		CDsvBase *pDsv = NULL;
		bTrue = TRUE;

		while (posDsv != NULL)
		{
			pDsv = (CDsvBase *)GetNext(posDsv);

			if (pDsv->IsAnyDsvObject())
			{
				continue;
			}

			if (pDsv->m_nMinOcc > 0)
			{
				bTrue = FALSE;
				break;
			}
		}

		return bTrue;
	}

	//从第一个DvmData开始验证
	if (bValidateHead)
	{
		bTrue = DsValidate(pDataset, pos, pRptValues);
	}
	else
	{
		CDsvElement *pFirst = (CDsvElement*)GetFirstDsvElement();

		//没有找到第一个DsvElement，则结束
		if (pFirst == NULL)
		{
			m_bDsvSucc = FALSE;
			bTrue = FALSE;
		}
		else
		{
			if (pFirst->IsAnyDsvObject())
			{
				bTrue = DsValidate(pDataset, pos, pRptValues);
			}
			else
			{
				CDvmData *pDvmData = NULL;

				//从数据集中找到第一个DsvElement能够匹配的数据位置
				while (pos != NULL)
				{
					pDvmData = (CDvmData*)pDataset->GetAt(pos);

					//第一个DsvElement能够匹配的数据位置
					if (pFirst->ValidateData(pDvmData, pRptValues))
					{
						bTrue = DsValidate(pDataset, pos, pRptValues);
						break;
					}
					else
					{
						pDvmData = (CDvmData*)pDataset->GetNext(pos);
					}
				}
			}
			
		}
	}

	return bTrue;
}


void CDsvSequence::GetNameAndValueText(CString &strText, BOOL bAddValue)
{
	POS posDsv = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (posDsv != NULL)
	{
		p = GetNext(posDsv);
		nClassID = p->GetClassID();
		
		if (nClassID == DVMCLASSID_CDSVELEMENT || nClassID == DVMCLASSID_CDSVSEQUENCE || nClassID == DVMCLASSID_CDSVCHOICE)
		{
			CDsvBase *pDsv = (CDsvBase*)p;

			if (!pDsv->IsAnyDsvObject())
			{
				pDsv->GetNameAndValueText(strText, bAddValue);
			}
		}
	}
}

long CDsvSequence::FindDsvElementIndex(CExBaseObject *pElement)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p == pElement)
		{
			break;
		}

		if ((p->GetClassID() == DVMCLASSID_CDSVELEMENT) || (p->GetClassID() == DVMCLASSID_CDSVANYELEMENT) )
		{
			nIndex++;
		}
	}

	return nIndex;
}

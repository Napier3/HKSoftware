//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvScript.cpp  CDsvScript


#include "stdafx.h"
#include "DsvScript.h"

#include "DsvElement.h"
#include "DsvChoice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDsvScript::CDsvScript()
{
	//初始化属性

	//初始化成员变量
	m_pDsvEliminate = NULL;
	m_pDsvAppearForErr = NULL;
	m_pDsvSrc = NULL;
	m_strInDatasetMode = DSVSCRIPT_INDS_MODEID_ONLY_DSV_DSDATAS;
}

CDsvScript::~CDsvScript()
{
	m_listRefDataset.RemoveAll();
	m_listDsvFinal.RemoveAll();
	m_dsDsvAll.RemoveAll();

	m_listMiss.RemoveAll();
	m_listMore.RemoveAll();
	m_listAnyDsvMatch.RemoveAll();
	m_listAppearForErr.RemoveAll();
}

void CDsvScript::InitInDstasetMode()
{
	if (m_strInDatasetMode == DSVSCRIPT_INDS_MODEID_ONLY_DSV_DSDATAS)
	{
		m_nInDstasetMode = DSVSCRIPT_INDS_MODEINDEX_ONLY_DSV_DSDATAS;
	}
	else if (m_strInDatasetMode == DSVSCRIPT_INDS_MODEID_DATAS_ALL_IN_DS)
	{
		m_nInDstasetMode = DSVSCRIPT_INDS_MODEINDEX_DATAS_ALL_IN_DS;
	}
	else
	{
		m_nInDstasetMode = DSVSCRIPT_INDS_MODEINDEX_ONLY_DSV_DSDATAS;
	}
}

CBaseObject* CDsvScript::Clone()
{
	CDsvScript *p = new CDsvScript();
	Copy(p);
	return p;
}

long CDsvScript::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDsvSequence::XmlReadOwn(oNode, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strInDatasetKey, oNode, m_strInDataset);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strDsvType);

	return 0;
}

long CDsvScript::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDsvSequence::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strInDatasetKey, oElement, m_strInDataset);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strDsvType);

	return 0;
}

long CDsvScript::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDsvSequence::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strInDataset);
		BinarySerializeCalLen(oBinaryBuffer, m_strDsvType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strInDataset);

		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_3)
		{
			BinarySerializeRead(oBinaryBuffer, m_strDsvType);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strInDataset);
		BinarySerializeWrite(oBinaryBuffer, m_strDsvType);
	}

	return 0;
}

void CDsvScript::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	CExBaseList oList;

	while(pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case DVMCLASSID_CDSVELIMINATE:
			oList.AddTail(p);
			m_pDsvEliminate = (CDsvEliminate *)p;
			break;
		case DVMCLASSID_CDSVAPPEARFORERR:
			m_pDsvAppearForErr = (CDsvAppearForErr*)p;
			break;
		}
	}

	pos = oList.Find(m_pDsvEliminate);

	if (pos != NULL)
	{
		oList.RemoveAt(pos);
	}

	pos = oList.GetHeadPosition();

	while(pos != NULL)
	{
		p = oList.GetNext(pos);
		Delete(p);
	}

	oList.RemoveAll();

	CDsvSequence::InitAfterRead();

	InitInDstasetMode();
}

BOOL CDsvScript::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDsvSequence::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CDsvScript *p = (CDsvScript*)pObj;

	return TRUE;
}

BOOL CDsvScript::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDsvSequence::CopyOwn(pDest);

	CDsvScript *p = (CDsvScript*)pDest;
	p->m_strInDataset = m_strInDataset;
	p->m_strDsvType     = m_strDsvType;

	return TRUE;
}

BOOL CDsvScript::CanPaste(UINT nClassID)
{
	return CDsvSequence::CanPaste(nClassID);
}

CExBaseObject* CDsvScript::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = CDsvSequence::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);

	if (pNew != NULL)
	{
		return pNew;
	}

	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDsvEliminateKey)
	{
		ASSERT( m_pDsvEliminate == NULL);
		m_pDsvEliminate = new CDsvEliminate();
		pNew = m_pDsvEliminate;
	}
	else if (strClassID == pXmlKeys->m_strCDsvAppearForErrKey)
	{
		ASSERT( m_pDsvAppearForErr == NULL);
		m_pDsvAppearForErr = new CDsvAppearForErr();
		pNew = m_pDsvAppearForErr;
	}

	return pNew;
}

CExBaseObject* CDsvScript::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = CDsvSequence::CreateNewChild(nClassID);

	if (pNew != NULL)
	{
		return pNew;
	}

	if (nClassID == DVMCLASSID_CDSVELIMINATE)
	{
		m_pDsvEliminate = new CDsvEliminate();
		pNew = m_pDsvEliminate;
	}
	else if (nClassID == DVMCLASSID_CDSVAPPEARFORERR)
	{
		m_pDsvAppearForErr = new CDsvAppearForErr();
		pNew = m_pDsvAppearForErr;
	}

	return pNew;
}

long CDsvScript::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{

	return CDsvSequence::XmlWriteChildren(oXMLDoc, oElement, pXmlRWKeys);
}

long CDsvScript::SerializeChildren(CBinarySerialBuffer &oBinaryBuffer)
{
	return CDsvSequence::SerializeChildren(oBinaryBuffer);
}

BOOL CDsvScript::CopyChildren(CBaseObject* pDest)
{
	BOOL b = CDsvSequence::CopyChildren(pDest);

	return b;
}

//在待验证的数据集合中，检索属于关联的数据集的数据对象
void CDsvScript::QueryInRefDataset(CDvmDataset *pDsForValidate, CDvmDataset *pDestDataset)
{
	ASSERT (pDestDataset != NULL);

	POS pos = m_listRefDataset.GetHeadPosition();
	CExBaseList *pDsIn = NULL;

	//遍历每一个关联的数据集，检索相关的数据
	while (pos != NULL)
	{
		pDsIn = (CExBaseList *)m_listRefDataset.GetNext(pos);
		QueryInRefDataset(pDsForValidate, pDestDataset, pDsIn);
	}
}

void CDsvScript::QueryInRefDataset(CDvmDataset *pDsForValidate, CDvmDataset *pDestDataset, CExBaseList *pInDataset)
{
	POS pos = pDsForValidate->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;

	while (pos != NULL)
	{
		p = pDsForValidate->GetNext(pos);
		pFind = pInDataset->FindByID(p->m_strID);

		//在此添加排除报文的代码

		if (pFind != NULL)
		{
			pDestDataset->AddTail(p);
		}
	}
}

CDsvEliminate* CDsvScript::GetDsvEliminate()
{
	if (m_pDsvEliminate == NULL)
	{
		m_pDsvEliminate = new CDsvEliminate();
		m_pDsvEliminate->SetParent(this);
		AddNewChild(m_pDsvEliminate);
	}

	return m_pDsvEliminate;
}

CDsvAppearForErr* CDsvScript::GetDsvAppearForErr()
{
	if (m_pDsvAppearForErr == NULL)
	{
		m_pDsvAppearForErr = new CDsvAppearForErr();
		m_pDsvAppearForErr->SetParent(this);
		AddNewChild(m_pDsvAppearForErr);
	}

	return m_pDsvAppearForErr;
}


void CDsvScript::EmptyRefDatasets()
{
	m_listRefDataset.RemoveAll();
}

void CDsvScript::InitRefDataset(CDvmDevice *pDevice)
{
	
}

void CDsvScript::SetRefDataset(CExBaseList *pDataset)
{
	m_listRefDataset.AddTail(pDataset);
}

//设置待验证的数据集中数据的验证状态，如果某一个数据对象没有匹配成功，则属于多出来的报文
//设置过程中，要排除数据对象
BOOL CDsvScript::InitDsValidateState(CDvmDataset *pDsDataset, CExBaseList *pListMatch, CExBaseList *pListAnyMatch)
{
	POS pos = pDsDataset->GetHeadPosition();
	CExBaseObject *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = pDsDataset->GetNext(pos);

		if (pListMatch->Find(p) != NULL)// || pListAnyMatch->Find(p) != NULL)
		{
			//此数据匹配成功
			p->m_dwReserved = 1;
		}
		else if ( pListAnyMatch->Find(p) != NULL)
		{
			if (p->m_dwReserved == 0)
			{
				m_listMore.AddTail(p);
				nCount++;
			}
		}
		else
		{
			//排除项目
			if (m_pDsvEliminate != NULL)
			{
				if (m_pDsvEliminate->FindByID(p->m_strID))
				{
					//属于排除对象中的数据，则此数据验证成功
					p->m_dwReserved = 1;
					continue;;
				}
				else
				{
					//表示多出来的data
					m_listMore.AddTail(p);
					p->m_dwReserved = 0;
					nCount++;
				}
			}
			else
			{
				//表示多出来的data
				m_listMore.AddTail(p);
				p->m_dwReserved = 0;
				nCount++;
			}
		}
// 		else
// 		{
// 			//此数据匹配成功
// 			p->m_dwReserved = 1;
// 		}
	}

	return (nCount == 0);
}

//初始化数据集每个data对象的状态
void CDsvScript::InitDsValidateState(CDvmDataset *pDsDataset)
{
	POS pos = pDsDataset->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pDsDataset->GetNext(pos);
		p->m_dwReserved = 0x0FFFFFFF;
	}
}

void CDsvScript::InitErrrorDsvObjcts(CExBaseList *pListDest)
{
	CExBaseList listDsv;
	QueryAllElement(this, &listDsv);

	POS pos = listDsv.GetHeadPosition();
	CDsvBase *pDsv = NULL;

	while (pos != NULL)
	{
		pDsv = (CDsvBase *)listDsv.GetNext(pos);
		
		if (pDsv->IsAnyDsvObject())
		{
			continue;
		}

		if ( pDsv->IsValidateSucc() )
		{
			continue;
		}

		long nCount = pDsv->m_listDsvMatch.GetCount();

		if (m_strDsvType == DSVSCRIPT_TYPE_ID_ELEMENT_QUERY)
		{
			if (nCount < pDsv->m_nMinOcc)
			{
				pListDest->AddTail(pDsv);
			}
		}
		else
		{
			if (nCount < pDsv->m_nMinOcc || nCount > pDsv->m_nMaxOcc)
			{
				pListDest->AddTail(pDsv);
			}
		}
	}

	listDsv.RemoveAll();
}

void CDsvScript::InitAnlyElementListMatch(CDvmDataset *pDataset)
{
	CExBaseList listAllElement;
	QueryAllElement(this, &listAllElement);

	InitAnlyElementListMatch(&listAllElement, pDataset);

	listAllElement.RemoveAll();
}

void CDsvScript::InitAnlyElementListMatch(CExBaseList *pListDsv, CDvmDataset *pDataset)
{
	POS pos = pListDsv->GetHeadPosition();
	CDsvBase *pDsv = NULL;
	POS posDataset= pDataset->GetHeadPosition();
	CDvmData *pPrevData=NULL, *pNextData=NULL;

	if (posDataset == NULL)
	{
		return;
	}

	while (pos != NULL)
	{
		pDsv = (CDsvBase *)pListDsv->GetNext(pos);

		if (pDsv->IsAnyDsvObject())
		{
			GetAnyElementPrevNextDvmData(pListDsv, pDsv, &pPrevData, &pNextData);
			InitAnlyElementListMatch(pDsv, pDataset, pPrevData, pNextData);
			((CDsvAnyElement*)pDsv)->DsValidate(*pListDsv);
		}
	}
}

void CDsvScript::InitAnlyElementListMatch(CDsvBase *pAnly, CDvmDataset *pDataset, CDvmData *pPrev, CDvmData *pNext)
{
	long nIndexFrom=0, nIndexTo=0;
	ASSERT(pAnly->IsAnyDsvObject());

	if (pPrev == NULL)
	{
		nIndexFrom=0;
	}
	else
	{
		nIndexFrom = pDataset->FindIndex(pPrev)+1;
	}

	if (pNext == NULL)
	{
		nIndexTo = pDataset->GetCount() - 1;
	}
	else
	{
		nIndexTo = pDataset->FindIndex(pNext) - 1;
	}

	long nIndex = 0;
	CDvmData *pDvmData = NULL;

	for (nIndex=nIndexFrom; nIndex <= nIndexTo; nIndex++)
	{
		pDvmData = (CDvmData *)pDataset->GetAtIndex(nIndex);
		pAnly->m_listDsvMatch.AddTail(pDvmData);
	}
}

void CDsvScript::QueryAllElement(CExBaseList *pListDsv, CExBaseList *pListElement)
{
	POS pos = pListDsv->GetHeadPosition();
	CDsvBase *pDsv = NULL;

	while (pos != NULL)
	{
		pDsv = (CDsvBase *)pListDsv->GetNext(pos);

		if (pDsv->IsElement())
		{
			pListElement->AddTail(pDsv);
		}
		else
		{
			if (pDsv->IsBaseList())
			{
				QueryAllElement((CExBaseList*)pDsv, pListElement);
			}
		}
	}
}

void CDsvScript::GetAnyElementPrevNextDvmData(CExBaseList *pListDsv, CDsvBase *pAnly, CDvmData **ppPrev, CDvmData **ppNext)
{
	POS pos = pListDsv->Find(pAnly);
	POS posNext = pos;
	ASSERT( pos != NULL);
	CDsvBase *p = NULL;

	*ppPrev = NULL;
	*ppNext = NULL;

	if (pos == NULL)
	{
		return;
	}

	while (pos != NULL)
	{
		pListDsv->GetPrev(pos);

		if (pos == NULL)
		{
			break;
		}

		p = (CDsvBase*)pListDsv->GetAt(pos);

		if (!p->IsAnyDsvObject())
		{
			if (p->m_listDsvMatch.GetCount() > 0)
			{
				*ppPrev = (CDvmData*)p->m_listDsvMatch.GetTail();
				break;
			}
		}
	}

	while (posNext != NULL)
	{
		pListDsv->GetNext(posNext);

		if (posNext == NULL)
		{
			break;
		}

		p = (CDsvBase*)pListDsv->GetAt(posNext);

		if (!p->IsAnyDsvObject())
		{
			if (p->m_listDsvMatch.GetCount() > 0)
			{
				*ppNext = (CDvmData*)p->m_listDsvMatch.GetHead();
				break;
			}
		}
	}
}

BOOL CDsvScript::DsValidate(CDvmDataset *pDataset, CValues *pRptValues, BOOL bValidateHead)
{
	m_listDsvMatch.RemoveAll();
	m_listDsvFinal.RemoveAll();
	m_dsDsvAll.RemoveAll();
	m_listMiss.RemoveAll();
	m_listAppearForErr.RemoveAll();
	m_listMore.RemoveAll();
	m_listAnyDsvMatch.RemoveAll();

	m_pDsvSrc = pDataset;

	if (m_pDsvEliminate != NULL)
	{
		Remove(m_pDsvEliminate);
	}

	if (m_pDsvAppearForErr != NULL)
	{
		Remove(m_pDsvAppearForErr);
	}

	BOOL bSucc = TRUE;

	if (m_strDsvType == DSVSCRIPT_TYPE_ID_SEQUENCE)
	{
		bSucc = DsValidate_Sequence(pDataset, pRptValues, bValidateHead);
	}
	else if (m_strDsvType == DSVSCRIPT_TYPE_ID_ELEMENT_QUERY)
	{
		bSucc = DsValidate_Query(pDataset, pRptValues, bValidateHead);
	}
	else
	{
		bSucc = DsValidate_Sequence(pDataset, pRptValues, bValidateHead);
	}

	//在此排除m_listMore的部分
	DsvRemoveEliminageFromMore();


	if (m_strDsvType != DSVSCRIPT_TYPE_ID_ELEMENT_QUERY)
	{
		if (GetCount() > 0)
		{
			if (m_listMiss.GetCount() > 0 || m_listMore.GetCount() > 0)
			{
				bSucc = FALSE;
			}
		}
	}
	else
	{
		if (m_listMiss.GetCount() > 0)
		{
			bSucc = FALSE;
		}
	}

	if (m_pDsvEliminate != NULL)
	{
		AddNewChild(m_pDsvEliminate);
	}

	if (m_pDsvAppearForErr != NULL)
	{
		AddNewChild(m_pDsvAppearForErr);
	}

	//执行出现即不合格的判断
	if (!ValidateAppearForErr(pDataset, pRptValues))
	{
		bSucc = FALSE;
	}

	m_bDsvSucc = bSucc;

	return bSucc;
}

void CDsvScript::DsvRemoveEliminageFromMore()
{
	POS pos = m_listMore.GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		p = m_listMore.GetNext(pos);

		if (m_pDsvEliminate->FindByID(p->m_strID))
		{
			m_listMore.RemoveAt(posPrev);
		}
	}
}

BOOL CDsvScript::ValidateAppearForErr(CDvmDataset *pDataset, CValues *pRptValues)
{
	if (m_pDsvAppearForErr == NULL)
	{
		return TRUE;
	}

	if (m_pDsvAppearForErr->GetCount() == 0)
	{
		return TRUE;
	}

	return m_pDsvAppearForErr->DsValidate(pDataset, pRptValues, m_listAppearForErr);
}

BOOL CDsvScript::DsValidate_Sequence(CDvmDataset *pDataset, CValues *pRptValues, BOOL bValidateHead)
{
	m_listMiss.RemoveAll();
	m_listMore.RemoveAll();
	m_listAnyDsvMatch.RemoveAll();

	m_listDsvFinal.RemoveAll();
	BOOL bSucc = FALSE;
	//初始化待验证的数据集的每个data的状态为：m_dwReserved = 0x0FFFFFFF;
	InitDsValidateState(pDataset);

	if (m_listRefDataset.GetCount() > 0)
	{
		//检索待验证的pDataset，检索出所有关联数据集中的DvmData，结果保存在oDvmDataset中
		//使用oDvmDataset进行验证，此方式排除其他数据对象
		QueryInRefDataset(pDataset, &m_dsDsvAll);
		bSucc = CDsvSequence::DsValidate(&m_dsDsvAll,pRptValues, bValidateHead);

		//初始化anly-element关联的对象
		InitAnlyElementListMatch(pDataset);

		//CExBaseList m_listDsvMatch;
		GetAllMatchObjects(m_listDsvMatch, m_listAnyDsvMatch); //获得所有匹配成功的数据对象

		//对待验证的报文进行检验，查找多出来的报文
		BOOL bSucc = InitDsValidateState(&m_dsDsvAll, &m_listDsvMatch, &m_listAnyDsvMatch);

		//将验证不正确的报文添加到m_listErrorDsvObj
		InitErrrorDsvObjcts(&m_listMiss);

		m_listDsvFinal.Append(&m_dsDsvAll);

		//listAllMatch.RemoveAll();
		//oDvmDataset.RemoveAll();

		m_bDsvSucc = IsValidateSucc() && bSucc;
	}
	else
	{
		m_dsDsvAll.Append(pDataset);

		if (GetCount() == 0)
		{
			bSucc = TRUE;
		}
		else
		{
			bSucc = CDsvSequence::DsValidate(pDataset, pRptValues, bValidateHead);
		}

		//初始化anly-element关联的对象
		InitAnlyElementListMatch(pDataset);

		//CExBaseList listAllMatch;
		GetAllMatchObjects(m_listDsvMatch, m_listAnyDsvMatch);

		InitDsValidateState(pDataset, &m_listDsvMatch,&m_listAnyDsvMatch);

		//将验证不正确的报文添加到m_listErrorDsvObj
		InitErrrorDsvObjcts(&m_listMiss);

		m_listDsvFinal.Append(&m_listDsvMatch);

		//listAllMatch.RemoveAll();
		m_bDsvSucc = IsValidateSucc();
	}

	return bSucc;
}

BOOL CDsvScript::DsValidate_Query(CDvmDataset *pDataset, CValues *pRptValues, BOOL bValidateHead)
{
	m_listMiss.RemoveAll();
	m_listMore.RemoveAll();

	m_listDsvFinal.RemoveAll();
	BOOL bSucc = FALSE;
	//初始化待验证的数据集的每个data的状态为：m_dwReserved = 0x0FFFFFFF;
	InitDsValidateState(pDataset);

	if (m_listRefDataset.GetCount() > 0)
	{
		//CDvmDataset oDvmDataset;

		//检索待验证的pDataset，检索出所有关联数据集中的DvmData，结果保存在oDvmDataset中
		//使用oDvmDataset进行验证，此方式排除其他数据对象
		QueryInRefDataset(pDataset, &m_dsDsvAll);
		bSucc = CDsvSequence::DsvQuery(&m_dsDsvAll,pRptValues);

		//CExBaseList m_listDsvMatch;
		GetAllMatchObjects(m_listDsvMatch, m_listAnyDsvMatch); //获得所有匹配成功的数据对象

		//对待验证的报文进行检验，查找多出来的报文
		BOOL bSucc = InitDsValidateState(&m_dsDsvAll, &m_listDsvMatch, &m_listAnyDsvMatch);

		//将验证不正确的报文添加到m_listErrorDsvObj
		InitErrrorDsvObjcts(&m_listMiss);

		//初始化anly-element关联的对象
		//InitAnlyElementListMatch(pDataset);

		m_listDsvFinal.Append(&m_dsDsvAll);

		//listAllMatch.RemoveAll();
		//oDvmDataset.RemoveAll();

		m_bDsvSucc = IsValidateSucc() && bSucc;
	}
	else
	{
		m_dsDsvAll.Append(pDataset);
		bSucc = CDsvSequence::DsvQuery(pDataset, pRptValues);
		//CExBaseList m_listDsvMatch;
		GetAllMatchObjects(m_listDsvMatch, m_listAnyDsvMatch);
		InitDsValidateState(pDataset, &m_listDsvMatch, &m_listAnyDsvMatch);

		//将验证不正确的报文添加到m_listErrorDsvObj
		InitErrrorDsvObjcts(&m_listMiss);

		//初始化anly-element关联的对象
		//InitAnlyElementListMatch(pDataset);

		m_listDsvFinal.Append(&m_listDsvMatch);

		//listAllMatch.RemoveAll();
		m_bDsvSucc = IsValidateSucc();
	}

	return bSucc;
}

// long CDsvScript::FindDsvElementIndex(CExBaseObject *pElement)
// {
// 	POS pos = GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 	long nIndex = 0;
// 
// 	while (pos != NULL)
// 	{
// 		p = GetNext(pos);
// 
// 		if (p == pElement)
// 		{
// 			break;
// 		}
// 
// 		if ((p->GetClassID() == DVMCLASSID_CDSVELEMENT) || (p->GetClassID() == DVMCLASSID_CDSVANYELEMENT) )
// 		{
// 			nIndex++;
// 		}
// 	}
// 
// 	return nIndex;
// }

void CDsvScript::GetDsv_AddData(CDvmData *pDvmData, CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime)
{
	if (bIsDsvTextWithUtcTime)
	{
        strText += pDvmData->GetTime();
	}

    strText += pDvmData->m_strName;

	if (bIsDsvTextWithValue)
	{
        strText += pDvmData->m_strValue;
	}

	strText += _T("\r\n");
}

void CDsvScript::GetDsv_All(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime)
{
	POS pos = m_dsDsvAll.GetHeadPosition();
	CDvmData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmData*)m_dsDsvAll.GetNext(pos);
		GetDsv_AddData(p, strText, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);
	}

	strText.Trim();
}

void CDsvScript::GetDsv_All_ByValue(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime, const CString &strValue)
{
	POS pos = m_dsDsvAll.GetHeadPosition();
	CDvmData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmData*)m_dsDsvAll.GetNext(pos);

		if (p->m_strValue == strValue)
		{
			GetDsv_AddData(p, strText, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);
		}
	}

	strText.Trim();
}

void CDsvScript::GetDsv_All_Match(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime)
{
	POS pos = m_listDsvMatch.GetHeadPosition();
	CDvmData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmData*)m_listDsvMatch.GetNext(pos);
		GetDsv_AddData(p, strText, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);
	}

	strText.Trim();
}

void CDsvScript::GetDsv_All_More(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime)
{
	POS pos = m_listMore.GetHeadPosition();
	CDvmData *p = NULL;
	strText.Empty();

	while (pos != NULL)
	{
		p = (CDvmData*)m_listMore.GetNext(pos);
		GetDsv_AddData(p, strText, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);
	}

	strText.Trim();
}

void CDsvScript::GetDsv_All_Miss(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime)
{
	POS pos = m_listMiss.GetHeadPosition();
	CDsvBase *p = NULL;
	strText.Empty();

	while (pos != NULL)
	{
		p = (CDsvBase*)m_listMiss.GetNext(pos);

		if (bIsDsvTextWithValue)
		{
            strText.AppendFormat(_T("%s(%s)\r\n"), p->m_strName.GetString(), p->GetValueAttr().GetString());
		}
		else
		{
            strText.AppendFormat(_T("%s\r\n"), p->m_strName.GetString());
		}
	}

	strText.Trim();
}


void CDsvScript::GetDsv_AppearForErr(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime)
{
	POS pos = m_listAppearForErr.GetHeadPosition();
	CDvmData *p = NULL;
	strText.Empty();

	while (pos != NULL)
	{
		p = (CDvmData*)m_listAppearForErr.GetNext(pos);
		GetDsv_AddData(p, strText, bIsDsvTextWithValue, bIsDsvTextWithUtcTime);
	}

	strText.Trim();
}


void CDsvScript::GetDsv_Std(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime)
{
	strText.Empty();

	GetNameAndValueText(strText, bIsDsvTextWithValue);

	strText.Trim();
}


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttGdGridInst.cpp  CSttGdGridInst


#include "stdafx.h"
#include "SttGdGridInst.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttGdGridInst::CSttGdGridInst()
{
	//��ʼ������
	m_pSttGdInst_Cols = NULL;

	//��ʼ����Ա����
}

CSttGdGridInst::~CSttGdGridInst()
{
}

long CSttGdGridInst::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridInst::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttGdGridInst::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttGdGridInst::InitAfterRead()
{
}

BOOL CSttGdGridInst::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttGdGridInst *p = (CSttGdGridInst*)pObj;

	return TRUE;
}

BOOL CSttGdGridInst::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttGdGridInst *p = (CSttGdGridInst*)pDest;

	return TRUE;
}

CBaseObject* CSttGdGridInst::Clone()
{
	CSttGdGridInst *p = new CSttGdGridInst();
	Copy(p);
	return p;
}

CBaseObject* CSttGdGridInst::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttGdGridInst *p = new CSttGdGridInst();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttGdGridInst::CanPaste(UINT nClassID)
{
	if (nClassID == MNGRCLASSID_CSTTGDINST_COLS)
	{
		return TRUE;
	}

	if (nClassID == MNGRCLASSID_CSTTGDCONDITION)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttGdGridInst::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestGridDefineXmlRWKeys *pXmlKeys = (CSttTestGridDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttGdInst_ColsKey)
	{
		pNew = new CSttGdInst_Cols();
	}
	else if (strClassID == pXmlKeys->m_strCSttGdConditionKey)
	{
		pNew = new CSttGdCondition();
	}

	return pNew;
}

CExBaseObject* CSttGdGridInst::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MNGRCLASSID_CSTTGDINST_COLS)
	{
		pNew = new CSttGdInst_Cols();
	}
	else if (nClassID == MNGRCLASSID_CSTTGDCONDITION)
	{
		pNew = new CSttGdCondition();
	}

	return pNew;
}

long CSttGdGridInst::GetColCount()
{
	if (m_pSttGdInst_Cols == NULL)
	{
		m_pSttGdInst_Cols = (CSttGdInst_Cols*)FindByClassID(MNGRCLASSID_CSTTGDINST_COLS);
	}

	if (m_pSttGdInst_Cols == NULL)
	{
		return 0;
	}

	return m_pSttGdInst_Cols->GetCount();
}
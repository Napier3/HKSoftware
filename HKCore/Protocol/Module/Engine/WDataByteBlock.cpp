#include "StdAfx.h"
#include "WDataByteBlock.h"
#include "../XLanguageResourcePp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CWDataByteBlock::CWDataByteBlock(void)
{
	m_strName = /*_T("数据字节块")*/g_sLangTxt_DataByteBlock;
	m_strID = _T("ID");
	m_nLength = 0;
}

CWDataByteBlock::~CWDataByteBlock(void)
{
}

CPpScript* CWDataByteBlock::CreateScript()
{
	if (m_pScript == NULL)
	{
#ifdef UNICODE
		m_pScript = new CPpScript(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey);
#else
		m_pScript = new CPpScript(CString(CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey));
#endif
		AddTail(m_pScript);
		m_pScript->SetParent(this);
		//m_pScript->m_strScript = L"--在此编写数据对象打包脚本";
	}

	return m_pScript;
}

long CWDataByteBlock::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataByteBlock::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CWDataByteBlock::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDataByteBlock::XmlWriteOwn(oXMLDoc,oElement,pXmlRWKeys);
	return 0;
}

long CWDataByteBlock::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{

	return 0;
}


CExBaseObject* CWDataByteBlock::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	//if(strClassID==CProtocolXmlRWKeys::g_pXmlRWKeys->m_strScriptKey)
	//{
	//	m_pScript = new CPpScript(strClassID);
	//	return m_pScript;
	//}

	return CDataByteBlock::CreateNewChild(strClassID,bAddToTail,pXmlRWKeys);
}

CExBaseObject* CWDataByteBlock::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	
	return NULL;
}

DWORD CWDataByteBlock::Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)
{
	DWORD nResult = 0;

	// 获取字节块字节长度
	m_nLength = GetByteBlockLength();

	if (m_nLength <= 0)
	{
		return PpProduceError();
	}

	AllocBuffer(m_nLength);

	// 解析该字节块数据
	if (m_pScript != NULL)
	{
		//CString strVariables;
		//strVariables.Format(L"nValue=%s\r\n", m_strValue);
		m_pScript->Run();

// 		if (m_pScript->m_dwReturn == 0)
// 		{// 如果脚本解析错误
// 			FreeBuffer();
// 			return PpParseError();
// 		}
	}
	
	// 将数据填充至二进制数据流
	//memcpy(oPkgBufPos.pBuffer+oPkgBufPos.nBuffer1BeginPos+oPkgBufPos.nIndex, m_pBuffer, m_nLength*sizeof(BYTE));
	oPkgBufPos.nIndex += m_nLength;

	// 克隆该数据
	CByteBlock *pByteBlock = NULL;
	pByteBlock = (CByteBlock*)Clone();
	pByteBlock->SetBuffer(DetachBuffer());

	// 将该数据添加到pDetail中
	pByteBlock->SetParent(pDetail);
	pDetail->AddTail(pByteBlock);

	return nResult;
}

//////////////////////////////////////////////////////////////////////////
//复制 克隆 对比
BOOL CWDataByteBlock::IsEqualOwn(CBaseObject* pObj)
{
	ASSERT (pObj == NULL);

	if (pObj == NULL)
	{
		return FALSE;
	}

	if (this == pObj)
	{
		return TRUE;
	}

	return CDataByteBlock::IsEqualOwn(pObj);
}

CBaseObject* CWDataByteBlock::Clone()
{
	CWDataByteBlock* pNew = new CWDataByteBlock();
	Copy(pNew);
	return pNew;
}

BOOL CWDataByteBlock::CopyOwn(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return TRUE;
	}

	return CDataByteBlock::CopyOwn(pDest);
}
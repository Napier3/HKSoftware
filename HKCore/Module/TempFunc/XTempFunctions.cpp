
#include "stdafx.h"
#include "XTempFunctions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CXTempFunctions::CXTempFunctions()
{
	//初始化属性
	m_pdwFuncRefBuffer = NULL;
	//初始化成员变量
}


CXTempFunctions::~CXTempFunctions()
{
	FreeFuncRefBuffer();
}

long CXTempFunctions::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;

	return 0;
}

long CXTempFunctions::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;

	return 0;
}

long CXTempFunctions::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
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

void CXTempFunctions::InitAfterRead()
{
}

BOOL CXTempFunctions::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CXTempFunctions *p = (CXTempFunctions*)pObj;

	return TRUE;
}

BOOL CXTempFunctions::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CXTempFunctions *p = (CXTempFunctions*)pDest;

	return TRUE;
}

CBaseObject* CXTempFunctions::Clone()
{
	CXTempFunctions *p = new CXTempFunctions();
	Copy(p);
	return p;
}

BOOL CXTempFunctions::CanPaste(UINT nClassID)
{
	if (nClassID == KTFCLASSID_CXSCENEBASE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXTempFunctions::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTempFuncXmlRWFuncs *pXmlKeys = (CTempFuncXmlRWFuncs*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXTempFuncsScene)
	{
		pNew = new CXTFSceneBase();
	}
	return pNew;
}

void CXTempFunctions::OpenTempFuncFile(const CString &strFileName, const CString &strPath)
{
	CString strFile;

	if (strPath.GetLength() < 2)
	{
		strFile = _P_GetLibraryPath();
	}

	if (strFileName.GetLength() < 5)
	{
		strFile += _T("RelayTest_TemplateforFunction.xml");
	}
	else
	{
		strFile += strFileName;
	}

	OpenTempFuncFile(strFile);
}

void CXTempFunctions::OpenTempFuncFile(const CString &strFilePath)
{
	DeleteAll();
	OpenXmlFile(strFilePath, CTempFuncXmlRWFuncs::CXTempFuncsTempF(), CTempFuncXmlRWFuncs::g_pXmlFuncs);
	InitFuncRefBuffer();
	//m_strXKeyDbFile = strFilePath;
}

void CXTempFunctions::FreeFuncRefBuffer()
{
	if (m_pdwFuncRefBuffer != NULL)
	{
		delete m_pdwFuncRefBuffer;
		m_pdwFuncRefBuffer = NULL;
	}

	m_nFuncRefCount = 0;
}

void CXTempFunctions::InitFuncRefBuffer(CExBaseList *pList, CExBaseList *pListDst) //保存关键字序列及对应测试字模板
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == KTFCLASSID_CXKEYBASE)
		{
			pListDst->AddTail(p);
		}
		else if (nClassID == KTFCLASSID_CXTEMPBASE)
		{
			pListDst->AddTail(p);
		}
		else if (nClassID == KTFCLASSID_CXFUNCBASE)
		{
			InitFuncRefBuffer((CExBaseList*)p, pListDst);
		}
		else if (nClassID == KTFCLASSID_CXKEYSBASE)
		{
			InitFuncRefBuffer((CExBaseList*)p, pListDst);
		}
	}
	//计算匹配度并保留最大值的字模板
}

void CXTempFunctions::InitFuncRefBuffer()
{
	FreeFuncRefBuffer();
	CExBaseList oListTemp;
	InitFuncRefBuffer(this, &oListTemp);
	m_nKeyTempCount = oListTemp.GetCount();
	/*m_pdwKeyRefBuffer = new DWORD [m_nKeyRefCount+10];
	CExBaseObject *p = NULL;
	POS pos = oListTemp.GetHeadPosition();
	long nIndex = 0;

	while (pos != NULL)
	{
		p = oListTemp.GetNext(pos);
		m_pdwKeyRefBuffer[nIndex] = (DWORD)p;
		nIndex++;
	}
*/
	oListTemp.RemoveAll();
}

long CXTempFunctions::QueryByKeys(CXKeyMatchRefList *pKeysList, CExBaseList &listTemplate)
{
	if (m_pCurrFilterScence != NULL)
	{
		return m_pCurrFilterScence->QueryByKeys(pKeysList, listTemplate);
	}

	POS pos = GetHeadPosition();    //第一级，Templates-Functions
	CXTFSceneBase *pScence = NULL;
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		ASSERT (p->GetClassID() == KTFCLASSID_CXSCENEBASE);
		pScence =  (CXTFSceneBase *)p;

		pScence->QueryByKeys(pKeysList, listTemplate);
	}


// 	CXTFFuncBase *pTempFunc = NULL;
// 
// 	CExBaseObject *p = NULL;
// 	CExBaseObject *p1 = NULL;
// 	CExBaseObject *p2 = NULL;
// 	CExBaseObject *p3 = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = GetNext(pos);
// 
// 		if (p->GetClassID() == KTFCLASSID_CXSCENEBASE)
// 		{
// 			CXTFSceneBase* pTest_Scene = (CXTFSceneBase*)p;
// 			POS pos1 = pTest_Scene->GetHeadPosition();       //第二级，Test-Scene     
// 
// 			while (pos1 != NULL)
// 			{
// 				p1 = pTest_Scene->GetNext(pos1);
// 
// 				if (p1->GetClassID()==KTFCLASSID_CXFUNCBASE)
// 				{
// 					pTempFunc = (CXTFFuncBase *)p1;
// 					if (pTempFunc->XMatch(pKeysList))
// 					{
// 						listTemplate.AddTail(pTempFunc);
// 					}
// 				}
// 
// 				else if (p1->GetClassID()==KTFCLASSID_CXFOLDERBASE)
// 				{
// 					CXTFFolderBase* pFolder = (CXTFFolderBase*)p1;
// 					POS pos2 = pFolder->GetHeadPosition();       //第三级，Folder
// 
// 					while (pos2 !=NULL)
// 					{
// 						p2 = pFolder->GetNext(pos2);
// 
// 						if (p2->GetClassID()==KTFCLASSID_CXFUNCBASE)
// 						{
// 							pTempFunc = (CXTFFuncBase *)p2;
// 							if (pTempFunc->XMatch(pKeysList))
// 							{
// 								listTemplate.AddTail(pTempFunc);
// 							}
// 						}
// 
// 						else if (p2->GetClassID()==KTFCLASSID_CXFOLDERBASE)
// 						{
// 							CXTFFolderBase* pFolder2 = (CXTFFolderBase*)p2;
// 							POS pos3 = pFolder2->GetHeadPosition();       //第四级，Folder
// 
// 							while (pos3 !=NULL)
// 							{
// 								p3 = pFolder2->GetNext(pos3);
// 
// 								if (p3->GetClassID()==KTFCLASSID_CXFUNCBASE)
// 								{
// 									pTempFunc = (CXTFFuncBase *)p3;
// 
// 									if (pTempFunc->XMatch(pKeysList))
// 									{
// 										listTemplate.AddTail(pTempFunc);
// 									}
// 
// 								}
// 							}
// 						}		
// 					}
// 				}
// 			}
// 		}
// 	}

	return listTemplate.GetCount();
}


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttHdChs.cpp  CSttHdChs


#include "stdafx.h"
#include "SttHdChs.h"
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttHdChs::CSttHdChs()
{
	//初始化属性

	//初始化成员变量
}

CSttHdChs::~CSttHdChs()
{
}

long CSttHdChs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttHdChs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSttHdChs::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CSttHdChs::InitAfterRead()
{
}

BOOL CSttHdChs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttHdChs *p = (CSttHdChs*)pObj;

	return TRUE;
}

BOOL CSttHdChs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttHdChs *p = (CSttHdChs*)pDest;

	return TRUE;
}

CBaseObject* CSttHdChs::Clone()
{
	CSttHdChs *p = new CSttHdChs();
	Copy(p);
	return p;
}

CBaseObject* CSttHdChs::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttHdChs *p = new CSttHdChs();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttHdChs::CanPaste(UINT nClassID)
{
	if (nClassID == STTCMDCLASSID_CSTTHDCH)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttHdChs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttHdChKey)
	{
		pNew = new CSttHdCh();
	}

	return pNew;
}

CExBaseObject* CSttHdChs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == STTCMDCLASSID_CSTTHDCH)
	{
		pNew = new CSttHdCh();
	}

	return pNew;
}

CSttHdCh* CSttHdChs::AddHdCh(const CString &strHdRsName,const CString &strHdRsID,float fHdChCoef)
{
	CSttHdCh *pNew = new CSttHdCh();
	pNew->m_strName = strHdRsName;
	pNew->m_strID = strHdRsID;
	pNew->m_fCoef = fHdChCoef;
	AddNewChild(pNew);
	return pNew;
}

CSttHdCh* CSttHdChs::FindAddHdCh(const CString &strHdRsName,const CString &strHdRsID,float fHdChCoef)
{
	CSttHdCh *pNew = (CSttHdCh*)FindByID(strHdRsID);

	if (pNew == NULL)
	{
		pNew = new CSttHdCh();
		pNew->m_strName = strHdRsName;
		pNew->m_strID = strHdRsID;
		AddNewChild(pNew);
	}

	pNew->m_fCoef = fHdChCoef;
	return pNew;
}

void CSttHdChs::InitHdChsByString(char zfChType,CString &strHdChsString)
{
	if (m_strID == STT_MODULETYPE_ID_ANALOG)
	{
		InitHdChsByString_Analog(zfChType,strHdChsString);
	}
	else if (m_strID == STT_MODULETYPE_ID_DIGITAL)
	{
		InitHdChsByString_Digital(zfChType,strHdChsString);
	}
	else if (m_strID == STT_MODULETYPE_ID_WEEK)
	{
		InitHdChsByString_Weak(zfChType,strHdChsString);
	}
}

void CSttHdChs::InitHdChsByString_Analog(char zfChType,CString &strHdChsString)
{
	DeleteAll();
	CString strNewText = _T("");
	char zfText[300];
	memset(zfText,0,300);
	ASSERT(strHdChsString.GetLength()<300);
	CString_to_char(strHdChsString,zfText);
	char *pBeginPos = zfText;
	char *pEndPos = pBeginPos;
	long nCurLenth = 0;
	CString strHdRsID;

	while(TRUE)
	{
#ifdef _UNICODE  //sf 20211122 兼容Unicode
		CString strTemp = _T(";");
		char *pchTemp = NULL;
		CString_to_char(strTemp,&pchTemp);
		pEndPos = strstr(pBeginPos,pchTemp);
#else
		pEndPos = strstr(pBeginPos,_T(";"));
#endif // _UNICODE
		
		if (pEndPos == NULL)
		{
			break;
		}

		*pEndPos = 0;
		nCurLenth = pEndPos-pBeginPos;

		if (nCurLenth<4)//长度必然大于4
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

		if ((pBeginPos[0] != zfChType))//必然以U或I开头
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

		if ((pBeginPos[1] < '1')||(pBeginPos[1] > '9'))//必然为数字
		{
			pBeginPos = (pEndPos+1);
			continue;
		}
#ifdef _UNICODE  //sf 20211122 兼容Unicode
		strTemp = _T("_");
		pchTemp = NULL;
		CString_to_char(strTemp,&pchTemp);
		if (strstr(pBeginPos,pchTemp) == NULL)//硬件资源标识中间必然有'_'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}
#else
		if (strstr(pBeginPos,_T("_")) == NULL)//硬件资源标识中间必然有'_'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}
#endif // _UNICODE
		
		strHdRsID = pBeginPos;

		if (FindByID(strHdRsID) == NULL)
		{
			AddHdCh(strHdRsID,strHdRsID);
			strNewText.AppendFormat(_T("%s;"),strHdRsID.GetString());
		}

		pBeginPos = (pEndPos+1);
	}

	strHdChsString = strNewText;
}

void CSttHdChs::InitHdChsByString_Digital(char zfChType,CString &strHdChsString)
{
	DeleteAll();
	CString strNewText = _T("");
	char zfText[300];
	memset(zfText,0,300);
	ASSERT(strHdChsString.GetLength()<300);
	CString_to_char(strHdChsString,zfText);
	char *pBeginPos = zfText;
	char *pEndPos = pBeginPos;
	long nCurLenth = 0;
	CString strHdRsID;

	while(TRUE)
	{
#ifdef _UNICODE  //sf 20211122 兼容Unicode
		CString strTemp = _T(";");
		char *pchTemp = NULL;
		CString_to_char(strTemp,&pchTemp);
		pEndPos = strstr(pBeginPos,pchTemp);
#else
		pEndPos = strstr(pBeginPos,_T(";"));
#endif // _UNICODE

		if (pEndPos == NULL)
		{
			break;
		}

		*pEndPos = 0;
		nCurLenth = pEndPos-pBeginPos;

		if (nCurLenth<5)//长度必然大于5
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

		if ((pBeginPos[0] != zfChType))//必然以U或I开头
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

		if (pBeginPos[1] != 'd')//必然为'd'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

#ifdef _UNICODE  //sf 20211122 兼容Unicode
		strTemp = _T("_");
		pchTemp = NULL;
		CString_to_char(strTemp,&pchTemp);
		if (strstr(pBeginPos,pchTemp) == NULL)//硬件资源标识中间必然有'_'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}
#else
		if (strstr(pBeginPos,_T("_")) == NULL)//硬件资源标识中间必然有'_'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}
#endif // _UNICODE

		strHdRsID = pBeginPos;

		if (FindByID(strHdRsID) == NULL)
		{
			AddHdCh(strHdRsID,strHdRsID);
			strNewText.AppendFormat(_T("%s;"),strHdRsID.GetString());
		}

		pBeginPos = (pEndPos+1);
	}

	strHdChsString = strNewText;
}

void CSttHdChs::InitHdChsByString_Weak(char zfChType,CString &strHdChsString)
{
	DeleteAll();
	CString strNewText = _T("");
	char zfText[300];
	memset(zfText,0,300);
	ASSERT(strHdChsString.GetLength()<300);
	CString_to_char(strHdChsString,zfText);
	char *pBeginPos = zfText;
	char *pEndPos = pBeginPos;
	long nCurLenth = 0;
	CString strHdRsID;

	while(TRUE)
	{
#ifdef _UNICODE  //sf 20211122 兼容Unicode
		CString strTemp = _T(";");
		char *pchTemp = NULL;
		CString_to_char(strTemp,&pchTemp);
		pEndPos = strstr(pBeginPos,pchTemp);
#else
		pEndPos = strstr(pBeginPos,_T(";"));
#endif // _UNICODE

		if (pEndPos == NULL)
		{
			break;
		}

		*pEndPos = 0;
		nCurLenth = pEndPos-pBeginPos;

		if (nCurLenth<5)//长度必然大于5
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

		if ((pBeginPos[0] != 'U'))//必然以U开头
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

		if (pBeginPos[1] != 'w')//必然为'w'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}

#ifdef _UNICODE  //sf 20211122 兼容Unicode
		strTemp = _T("_");
		pchTemp = NULL;
		CString_to_char(strTemp,&pchTemp);
		if (strstr(pBeginPos,pchTemp) == NULL)//硬件资源标识中间必然有'_'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}
#else
		if (strstr(pBeginPos,_T("_")) == NULL)//硬件资源标识中间必然有'_'
		{
			pBeginPos = (pEndPos+1);
			continue;
		}
#endif // _UNICODE

		strHdRsID = pBeginPos;

		if (FindByID(strHdRsID) == NULL)
		{
			AddHdCh(strHdRsID,strHdRsID);
			strNewText.AppendFormat(_T("%s;"),strHdRsID.GetString());
		}

		pBeginPos = (pEndPos+1);
	}

	strHdChsString = strNewText;
}

BOOL CSttHdChs::HasHdCh(char zfChType,const long &nModuleIndex,long nChIndex)
{
	CString strHdChID;
	CExBaseObject *pCh = NULL;

	if (m_strID == STT_MODULETYPE_ID_ANALOG)
	{
		strHdChID.Format(_T("%c%ld_%ld"),zfChType,nModuleIndex,nChIndex);
		pCh = FindByID(strHdChID);
		return (pCh != NULL);
	}
	else if (m_strID == STT_MODULETYPE_ID_DIGITAL)
	{
		strHdChID.Format(_T("%cd%ld_%ld"),zfChType,nModuleIndex,nChIndex);
		pCh = FindByID(strHdChID);
		return (pCh != NULL);
	}
	else if (m_strID == STT_MODULETYPE_ID_WEEK)
	{
		strHdChID.Format(_T("%cw%ld_%ld"),zfChType,nModuleIndex,nChIndex);
		pCh = FindByID(strHdChID);
		return (pCh != NULL);
	}

	return FALSE;
}


BOOL CSttHdChs::HasAnalogCurrModuleHdCh(long nModuleIndex)
{
	CString strTmp;
	strTmp.Format(_T("I%ld_"),nModuleIndex);
	CSttHdCh *pHdCh = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pHdCh = (CSttHdCh *)GetNext(pos);

		if (pHdCh->m_strID.Find(strTmp) == 0)
		{
			return TRUE;
		}
	}

	return FALSE;
}


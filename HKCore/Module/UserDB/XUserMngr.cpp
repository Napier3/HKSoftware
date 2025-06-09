//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XUserMngr.cpp  CXUserMngr


#include "stdafx.h"
#include "XUserMngr.h"

CXUserMngr::CXUserMngr()
{
	CXUser::InitAdminUserAndPSW();
	m_pXUserAdmin = new CXUser();
	m_pXUserAdmin->m_strName = CXUser::g_strAdminID;
	m_pXUserAdmin->m_strID = CXUser::g_strAdminID;
	m_pXUserAdmin->m_strPSW = CXUser::g_strAdminPSW;

	//初始化属性

	//初始化成员变量
	m_dwErrorMsg = 0;
}

CXUserMngr::~CXUserMngr()
{
}

long CXUserMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CUserDBXmlRWKeys *pXmlKeys = (CUserDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CXUserMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CUserDBXmlRWKeys *pXmlKeys = (CUserDBXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CXUserMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
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

void CXUserMngr::InitAfterRead()
{
}

BOOL CXUserMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CXUserMngr *p = (CXUserMngr*)pObj;

	return TRUE;
}

BOOL CXUserMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CXUserMngr *p = (CXUserMngr*)pDest;

	return TRUE;
}

CBaseObject* CXUserMngr::Clone()
{
	CXUserMngr *p = new CXUserMngr();
	Copy(p);
	return p;
}

BOOL CXUserMngr::CanPaste(UINT nClassID)
{
	if (nClassID == USRDCLASSID_CXUSER)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CXUserMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CUserDBXmlRWKeys *pXmlKeys = (CUserDBXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCXUserKey)
	{
		pNew = new CXUser();
	}

	return pNew;
}

CExBaseObject* CXUserMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == USRDCLASSID_CXUSER)
	{
		pNew = new CXUser();
	}

	return pNew;
}

CString CXUserMngr::GetUserDBFile()
{
	CString strFile;
	strFile = _P_GetLibraryPath();
	strFile += _T("UserMngr.xml");

	return strFile;
}

void CXUserMngr::OpenUserDB()
{
	Remove(m_pXUserAdmin);
	DeleteAll();

	OpenXmlFile(GetUserDBFile(), GetXmlElementKey(), CUserDBXmlRWKeys::g_pXmlKeys);

	CXUser *pFind = (CXUser*)FindByID(m_pXUserAdmin->m_strID);
	
	if (pFind == NULL)
	{
		AddNewChild(m_pXUserAdmin);
	}
	else
	{
		delete m_pXUserAdmin;
		m_pXUserAdmin = pFind;
	}
}

void CXUserMngr::SaveUserDB()
{
	SaveXmlFile(GetUserDBFile(), CUserDBXmlRWKeys::g_pXmlKeys);
}

CXUser* CXUserMngr::Login_Admin(const CString &strPSW)
{
	CXUser *pFind = FindUserByName(m_pXUserAdmin->m_strID);

	if (pFind == NULL)
	{
		if (strPSW == m_pXUserAdmin->m_strPSW)
		{
			return m_pXUserAdmin;
		}
	}

	m_dwErrorMsg = XUSER_ERRORID_PSWERROR;

	return NULL;
}

CXUser* CXUserMngr::Login(const CString &strUser, const CString &strPSW)
{
	CString strUser2 = xdes_Encrypt(strUser);
	CString strPSW2 = xdes_Encrypt(strPSW);

// 	AfxMessageBox(strUser2);
// 	AfxMessageBox(strPSW2);

	if (strUser2 == m_pXUserAdmin->m_strID)
	{
		return Login_Admin(strPSW2);
	}

	POS pos = GetHeadPosition();
	CXUser *p     = NULL;
	CXUser *pFind = NULL;
	m_dwErrorMsg = 0;

	while (pos != NULL)
	{
		p = (CXUser *)GetNext(pos);

		if (p->m_strID == strUser2)
		{
			if (p->m_strPSW == strPSW2)
			{
				pFind = p;
			}
			else
			{
				m_dwErrorMsg = XUSER_ERRORID_PSWERROR;
			}

			break;
		}
	}

	if (pFind == NULL)
	{
		if (m_dwErrorMsg != 0)
		{
			m_dwErrorMsg = XUSER_ERRORID_NOUSER;
		}
	}

	return pFind;
}

CXUser* CXUserMngr::FindUserByName(const CString &strUserName)
{
// 	CXAes oXAes;
// 	CString strTemp = oXAes.Cipher(strUserName);
	CString strTemp = xdes_Encrypt(strUserName);
	CXUser *pFind = (CXUser*)FindByName(strTemp);

	return pFind;
}

CXUser* CXUserMngr::FindUserByID(const CString &strUserID)
{
// 	CXAes oXAes;
// 	CString strTemp = oXAes.Cipher(strUserID);
	CString strTemp = xdes_Decrypt(strUserID);

	CXUser *pFind = (CXUser*)FindByID(strTemp);

	return pFind;
}

void CXUserMngr::AddUser(CXUser *pUser)
{
	AddNewChild(pUser);
	SaveUserDB();
}

void CXUserMngr::DeleteUser(CXUser *pUser)
{
	Delete(pUser);
	SaveUserDB();
}



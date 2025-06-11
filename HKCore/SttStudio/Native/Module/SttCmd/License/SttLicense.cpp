//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttLicense.cpp  CSttLicense


#include "stdafx.h"
#include "SttLicense.h"
#include "../../SttGlobalDef.h"

CSttLicense::CSttLicense()
{
	//初始化属性

	//初始化成员变量
}

CSttLicense::~CSttLicense()
{
}

long CSttLicense::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	return 0;
}

long CSttLicense::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	return 0;
}

long CSttLicense::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strType);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strType);
	}
	return 0;
}

void CSttLicense::InitAfterRead()
{
}

BOOL CSttLicense::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSttLicense *p = (CSttLicense*)pObj;

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttLicense::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSttLicense *p = (CSttLicense*)pDest;

	p->m_strType = m_strType;
	return TRUE;
}

CBaseObject* CSttLicense::Clone()
{
	CSttLicense *p = new CSttLicense();
	Copy(p);
	return p;
}

CExBaseObject* CSttLicense::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttCmdDefineXmlRWKeys *pXmlKeys = (CSttCmdDefineXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttLicenseModuleKey)
	{
		pNew = new CSttLicenseModule();
	}

	return pNew;
}

CExBaseObject* CSttLicense::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


    if (nClassID == STTCMDCLASSID_CSTTLICENSEMODULE)
	{
		pNew = new CSttLicenseModule();
	}

	return pNew;
}

#include "../../../../Module/API/GlobalConfigApi.h"
void CSttLicense::OpenLicenseFile()
{
    DeleteAll();
    CString strFile;
    strFile = _P_GetConfigPath();
    strFile += STT_SYS_License_File;
    OpenXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

void CSttLicense::SaveLicenseFile()
{
    CString strFile;
    strFile = _P_GetConfigPath();
    strFile += STT_SYS_License_File;
    SaveXmlFile(strFile, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
}

bool CSttLicense::AddLicense(CSttLicense *pSrc)
{
    POS pos = pSrc->GetHeadPosition();
    CSttLicenseModule *p = NULL;
    CSttLicenseModule *pFind = NULL;
    bool bModify = false;

    while (pos != NULL)
    {
        p = (CSttLicenseModule*)pSrc->GetNext(pos);
        pFind = (CSttLicenseModule*)FindByID(p->m_strID);

        if (pFind != NULL)
        {
            if (pFind->m_strKey != p->m_strKey)
            {
                pFind->m_strKey = p->m_strKey;
                bModify = true;
            }
        }
        else
        {
            pFind = (CSttLicenseModule*)p->Clone();
            AddNewChild(pFind);
            bModify = true;
        }
    }

    return bModify;
}

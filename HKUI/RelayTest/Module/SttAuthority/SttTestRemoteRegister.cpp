#include "stdafx.h"
#include "SttTestRemoteRegister.h"
#include "../SttGlobalDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CSttTestRemoteRegister::CSttTestRemoteRegister()
{

}

CSttTestRemoteRegister::CSttTestRemoteRegister(CExBaseObject *pData)
{
	Init(pData);
}

CSttTestRemoteRegister::~CSttTestRemoteRegister()
{

}

void CSttTestRemoteRegister::Init(CExBaseObject *pData)
{
	if (pData == NULL)
	{
		return;
	}

	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	Init((CDvmData*)pData);
}

void CSttTestRemoteRegister::Init(CDvmData *pDvmData)
{
	pDvmData->Copy(this);
}

CString CSttTestRemoteRegister::Code_Register()
{
	return GetValueByID(ID_STT_USER_ATTR_Code_Register);
}

void CSttTestRemoteRegister::Code_Register(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_Code_Register, strValue);
}

CString CSttTestRemoteRegister::SN_TestApp()
{
	return GetValueByID(ID_STT_USER_ATTR_SN_TestApp);
}

void CSttTestRemoteRegister::SN_TestApp(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_SN_TestApp, strValue);
}

CString CSttTestRemoteRegister::Model_TestApp()
{
	return GetValueByID(ID_STT_REGISTER_ATTR_Model_TestApp);
}

void CSttTestRemoteRegister::Model_TestApp(const CString &strValue)
{
	SetValue(ID_STT_REGISTER_ATTR_Model_TestApp, strValue);
}

CString CSttTestRemoteRegister::Model_Dv()
{
	return GetValueByID(ID_STT_REGISTER_ATTR_Model_Dv);
}

void CSttTestRemoteRegister::Model_Dv(const CString &strValue)
{
	SetValue(ID_STT_REGISTER_ATTR_Model_Dv, strValue);
}

CString CSttTestRemoteRegister::Name_Cop()
{
	return GetValueByID(ID_STT_USER_ATTR_Name_Cop);
}

void CSttTestRemoteRegister::Name_Cop(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_Name_Cop, strValue);
}

CString CSttTestRemoteRegister::Name_User()
{
	return GetValueByID(ID_STT_USER_ATTR_Name_User);
}

void CSttTestRemoteRegister::Name_User(const CString &strValue)
{
	SetValue(ID_STT_USER_ATTR_Name_User, strValue);
}

CString CSttTestRemoteRegister::Description()
{
	return GetValueByID(ID_STT_REGISTER_ATTR_Description);
}

void CSttTestRemoteRegister::Description(const CString &strValue)
{
	SetValue(ID_STT_REGISTER_ATTR_Description, strValue);
}

CString CSttTestRemoteRegister::Ver(const CString &strVerID)
{
	return GetValueByID(strVerID);
}

void CSttTestRemoteRegister::Ver(const CString &strVerID, const CString &strValue)
{
	SetValue(strVerID, strValue);
}

BOOL CSttTestRemoteRegister::HasRegister()
{
	return Code_Register().GetLength() > 0;
}


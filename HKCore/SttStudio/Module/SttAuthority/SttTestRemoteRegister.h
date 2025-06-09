#pragma once
#include "../../../Module/DataMngr/DvmData.h"


class CSttTestRemoteRegister : public CDvmData
{
public:
	CSttTestRemoteRegister();
	CSttTestRemoteRegister(CExBaseObject *pData);
	virtual ~CSttTestRemoteRegister();

	void Init(CExBaseObject *pData);
	void Init(CDvmData *pDvmData);

public:
	CString Code_Register();
	void Code_Register(const CString &strValue);
	CString SN_TestApp();
	void SN_TestApp(const CString &strValue);
	CString Model_TestApp();
	void Model_TestApp(const CString &strValue);
	CString Model_Dv();
	void Model_Dv(const CString &strValue);
	CString Name_Cop();
	void Name_Cop(const CString &strValue);
	CString Name_User();
	void Name_User(const CString &strValue);
	CString Description();
	void Description(const CString &strValue);
	CString Ver(const CString &strVerID);
	void Ver(const CString &strVerID, const CString &strValue);

	BOOL HasRegister();
};
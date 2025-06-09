//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacrosFileMngr.h  CTestMacrosFileMngr

#pragma once

#include "TestMacroGlobal.h"


#include "TestMacrosFile.h"

#define TEST_MACRO_FILE_MNGR_VERSION_1    1
#define TEST_MACRO_FILE_MNGR_VERSION_2    2

#define TEST_MACRO_FILE_MNGR_VERSION    TEST_MACRO_FILE_MNGR_VERSION_2

class CTestMacrosFileMngr : public CExBaseList
{
private:
	CTestMacrosFileMngr();
	virtual ~CTestMacrosFileMngr();

public:
	static CTestMacrosFileMngr* Create(BOOL bUseAts=FALSE);
	static void Release();
	static CTestMacrosFileMngr* g_pTestMacrosFileMngr;

	static CString GetActiveMacroTestProgID(const CString &strFile, const CString &strType);
	static void GetAllIecConfigFileType(CDataType *pDataType);
	static void AdjustToNewVersion();
	static void InitByAuthoritys(const CString &strAuthoritys);

	static CString g_strDefaultMacroTestEngineProgID;
	static CString g_strDefaultIecConfigFile;

protected:
	static long  g_nTestMacrosFileMngrRef;
	static const CString g_strTestMacrosFileMngrFile;

//重载函数
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTESTMACROSFILEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTestMacrosFileMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	void OpenXmlFile(BOOL bUseAts);
	void SaveXmlFile();
	CTestMacrosFile* FindByFile(const CString &strFile);
	CTestMacrosFile* FindByFile(const CString &strMacroFile, const CString &strCommCmdFile);
	CString In_GetActiveMacroTestProgID(const CString &strFile, const CString &strType);
	void In_GetAllIecConfigFileType(CDataType *pDataType);
	void In_AdjustToNewVersion();
	void In_InitByAuthoritys(const CString &strAuthoritys);

//私有成员变量
private:
	long m_nVersion;


//私有成员变量访问方法
public:
	static CString FindTestMacroFileByID(const CString &strTestMacroFileID, CTestMacrosFile **ppMacroFile);
	static CString FindTestMacroFileByID_Old(const CString &strTestMacroFileID, CTestMacrosFile **ppMacroFile);
};


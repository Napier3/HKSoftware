//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUIDB.h  CSttMacroTestUI_TestMacroUIDB

#pragma once

#include "SttTestCtrrlMacroTestUIMngrGlobal.h"


#include "SttMacroTestUI_TestMacroUIs.h"
#include "SttMacroTestUI_TestMacroUIMngr.h"

/*
<test-macro-ui-db macro-file="EvdTestMacro.xml" macro-id="Evd">
	<test-macro-uis>
		<test-macro-ui name="硬件配置" id="HDConfig" gen-file="" ui-file="" ui-para-file="HDConfig.xml" report-file="HDConfig_Report.html"/>
		<test-macro-ui name="状态序列" id="StateTest" gen-file="" ui-file="" ui-para-file="Zero_Paras.xml" report-file="Zero_Report.html"/>
		<test-macro-ui name="零序保护定值测试" id="ZeroTest" gen-file="Zero_GbGen.xml" ui-file="Zero_UI.html" ui-para-file="Zero_Paras.xml" report-file="Zero_Report.html"/>
		<test-macro-ui name="差动保护测试" id="Diff" gen-file="Diff_GbGen.xml" ui-file="Diff_UI.html" ui-para-file="Diff_Paras.xml" report-file="Diff_Report.html"/>
	</test-macro-uis>
	<test-macro-ui-mngr>
		<test-macro-ui-ref id="HDConfig"/>
		<test-macro-ui-ref id="State"/>
		<group name="线路保护" id="Line">
			<test-macro-ui-ref id="ZeroTest"/>
		</group>
		<group name="变压器保护" id="Trans">
			<group name="主保护" id="Main">
			<test-macro-ui-ref id="Diff"/>
		</group>
		<group name="后备保护" id="Back">
			<test-macro-ui-ref id="ZeroTest"/>
		</group>
		</group>
	</test-macro-ui-mngr>
</test-macro-ui-db>
*/
class CSttMacroTestUI_TestMacroUIDB : public CExBaseList
{
public:
	CSttMacroTestUI_TestMacroUIDB();
	virtual ~CSttMacroTestUI_TestMacroUIDB();

public:
	static CSttMacroTestUI_TestMacroUIDB* g_pSttTestMacroUIDB;
	static long g_nSttTestMacroUIDBRef;
	static CString g_strMacroFileID;//zhouhj 20221207 用于指定当前使用的测试功能文件

	static CSttMacroTestUI_TestMacroUIDB* Create(const CString &strSysPath=_T(""));
	static void Release();

	CString	 m_strFile;        //当前打开的配置的文件名
	CString  m_strMacroFile;   //测试功能文件，对应TestMacro.xml
	CString  m_strMacroID;     //测试功能文件的相对路径，相对Config文件夹
//重载函数
public:
	virtual UINT GetClassID() {    return MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIDB;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrrlMacroTestUIMngrXmlRWKeys::CSttMacroTestUI_TestMacroUIDBKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CSttMacroTestUI_TestMacroUIMngr *m_pTestMacroUIMngr;
	CSttMacroTestUI_TestMacroUIs *m_pTestMacroUIs;

//私有成员变量访问方法
public:
	CSttMacroTestUI_TestMacroUIMngr* GetTestMacroUIMngr()	{	return m_pTestMacroUIMngr;	}
	void SetTestMacroUIMngr(CSttMacroTestUI_TestMacroUIMngr* pTestMacroUIMngr)	{	m_pTestMacroUIMngr = pTestMacroUIMngr;	}
	CSttMacroTestUI_TestMacroUIs* GetTestMacroUIs()	{	return m_pTestMacroUIs;	}
	void SetTestMacroUIs(CSttMacroTestUI_TestMacroUIs* pTestMacroUIs)	{	m_pTestMacroUIs = pTestMacroUIs;	}

	//2022-1-9   lijunqing
	static CSttMacroTestUI_TestMacroUI* FindTestMacroUI(const CString &strMacroUiId);

//属性变量访问方法
public:
	BOOL Open(const CString &strSysPath);
	BOOL OpenFile(const CString &strFile);
};


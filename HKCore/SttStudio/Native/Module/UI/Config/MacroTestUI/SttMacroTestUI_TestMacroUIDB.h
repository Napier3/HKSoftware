//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttMacroTestUI_TestMacroUIDB.h  CSttMacroTestUI_TestMacroUIDB

#pragma once

#include "SttTestCtrrlMacroTestUIMngrGlobal.h"


#include "SttMacroTestUI_TestMacroUIs.h"
#include "SttMacroTestUI_TestMacroUIMngr.h"

/*
<test-macro-ui-db macro-file="EvdTestMacro.xml" macro-id="Evd">
	<test-macro-uis>
		<test-macro-ui name="Ӳ������" id="HDConfig" gen-file="" ui-file="" ui-para-file="HDConfig.xml" report-file="HDConfig_Report.html"/>
		<test-macro-ui name="״̬����" id="StateTest" gen-file="" ui-file="" ui-para-file="Zero_Paras.xml" report-file="Zero_Report.html"/>
		<test-macro-ui name="���򱣻���ֵ����" id="ZeroTest" gen-file="Zero_GbGen.xml" ui-file="Zero_UI.html" ui-para-file="Zero_Paras.xml" report-file="Zero_Report.html"/>
		<test-macro-ui name="���������" id="Diff" gen-file="Diff_GbGen.xml" ui-file="Diff_UI.html" ui-para-file="Diff_Paras.xml" report-file="Diff_Report.html"/>
	</test-macro-uis>
	<test-macro-ui-mngr>
		<test-macro-ui-ref id="HDConfig"/>
		<test-macro-ui-ref id="State"/>
		<group name="��·����" id="Line">
			<test-macro-ui-ref id="ZeroTest"/>
		</group>
		<group name="��ѹ������" id="Trans">
			<group name="������" id="Main">
			<test-macro-ui-ref id="Diff"/>
		</group>
		<group name="�󱸱���" id="Back">
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
	static CString g_strMacroFileID;//zhouhj 20221207 ����ָ����ǰʹ�õĲ��Թ����ļ�

	static CSttMacroTestUI_TestMacroUIDB* Create(const CString &strSysPath=_T(""));
	static void Release();

	CString	 m_strFile;        //��ǰ�򿪵����õ��ļ���
	CString  m_strMacroFile;   //���Թ����ļ�����ӦTestMacro.xml
	CString  m_strMacroID;     //���Թ����ļ������·�������Config�ļ���
//���غ���
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

//˽�г�Ա����
private:
	CSttMacroTestUI_TestMacroUIMngr *m_pTestMacroUIMngr;
	CSttMacroTestUI_TestMacroUIs *m_pTestMacroUIs;

//˽�г�Ա�������ʷ���
public:
	CSttMacroTestUI_TestMacroUIMngr* GetTestMacroUIMngr()	{	return m_pTestMacroUIMngr;	}
	void SetTestMacroUIMngr(CSttMacroTestUI_TestMacroUIMngr* pTestMacroUIMngr)	{	m_pTestMacroUIMngr = pTestMacroUIMngr;	}
	CSttMacroTestUI_TestMacroUIs* GetTestMacroUIs()	{	return m_pTestMacroUIs;	}
	void SetTestMacroUIs(CSttMacroTestUI_TestMacroUIs* pTestMacroUIs)	{	m_pTestMacroUIs = pTestMacroUIs;	}

	//2022-1-9   lijunqing
	static CSttMacroTestUI_TestMacroUI* FindTestMacroUI(const CString &strMacroUiId);

//���Ա������ʷ���
public:
	BOOL Open(const CString &strSysPath);
	BOOL OpenFile(const CString &strFile);
};


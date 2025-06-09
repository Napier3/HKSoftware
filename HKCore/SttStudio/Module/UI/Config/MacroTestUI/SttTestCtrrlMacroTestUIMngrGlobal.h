//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttTestCtrrlMacroTestUIMngrGlobal.h

#pragma once

#include "../../../../../Module/BaseClass/ExBaseList.h"

#define MACROTESTUIMngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MACROTESTUIMngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIDB       (MACROTESTUIMngrCLASSID_EXLISTCLASS + 0X00000000)
#define MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIS       (MACROTESTUIMngrCLASSID_EXLISTCLASS + 0X00000001)
#define MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUI       (MACROTESTUIMngrCLASSID_BASECLASS + 0X00000002)
#define MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIMNGR       (MACROTESTUIMngrCLASSID_EXLISTCLASS + 0X00000003)
#define MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIREF       (MACROTESTUIMngrCLASSID_BASECLASS + 0X00000004)
#define MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_GROUP       (MACROTESTUIMngrCLASSID_EXLISTCLASS + 0X00000005)

class CSttTestCtrrlMacroTestUIMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys();
	virtual ~CSttTestCtrrlMacroTestUIMngrXmlRWKeys();
	static long g_nMACROTESTUIMngrRef;

public:
	static CSttTestCtrrlMacroTestUIMngrXmlRWKeys* g_pXmlKeys;
	static CSttTestCtrrlMacroTestUIMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCSttMacroTestUI_GroupKey; //group
	BSTR m_strCSttMacroTestUI_TestMacroUIRefKey; //test-macro-ui-ref
	BSTR m_strCSttMacroTestUI_TestMacroUIMngrKey; //test-macro-ui-mngr
	BSTR m_strCSttMacroTestUI_TestMacroUIKey; //test-macro-ui
	BSTR m_strCSttMacroTestUI_TestMacroUIsKey; //test-macro-uis
	BSTR m_strCSttMacroTestUI_TestMacroUIDBKey; //test-macro-ui-db
	BSTR m_strMacro_FileKey; //macro-file
	BSTR m_strMacro_IdKey; //macro-id
	BSTR m_strGen_FileKey; //gen-file
	BSTR m_strGirdFileKey; //grid-file
	BSTR m_strUi_FileKey; //ui-file
	BSTR m_strUi_Para_FileKey; //ui-para-file
	BSTR m_strReport_FileKey; //report-file
	BSTR m_strHd_Rs_FileKey; //hd-rs-file
	BSTR m_strCharLib_FileKey;  //charlib-file
	BSTR m_strUi_IdKey; //ui-id

	//shaolei 2023-6-20
	BSTR m_strRptDataCfgFileKey;  //rpt-data-cfg-file
	BSTR m_strRepeatTimesKey;   //repeat-times

public:
	static BSTR CSttMacroTestUI_GroupKey()  {   return g_pXmlKeys->m_strCSttMacroTestUI_GroupKey;  }
	static BSTR CSttMacroTestUI_TestMacroUIRefKey()  {   return g_pXmlKeys->m_strCSttMacroTestUI_TestMacroUIRefKey;  }
	static BSTR CSttMacroTestUI_TestMacroUIMngrKey()  {   return g_pXmlKeys->m_strCSttMacroTestUI_TestMacroUIMngrKey;  }
	static BSTR CSttMacroTestUI_TestMacroUIKey()  {   return g_pXmlKeys->m_strCSttMacroTestUI_TestMacroUIKey;  }
	static BSTR CSttMacroTestUI_TestMacroUIsKey()  {   return g_pXmlKeys->m_strCSttMacroTestUI_TestMacroUIsKey;  }
	static BSTR CSttMacroTestUI_TestMacroUIDBKey()  {   return g_pXmlKeys->m_strCSttMacroTestUI_TestMacroUIDBKey;  }
	static BSTR Macro_FileKey()  {   return g_pXmlKeys->m_strMacro_FileKey;  }
	static BSTR Macro_IdKey()  {   return g_pXmlKeys->m_strMacro_IdKey;  }
	static BSTR Gen_FileKey()  {   return g_pXmlKeys->m_strGen_FileKey;  }
	static BSTR Ui_FileKey()  {   return g_pXmlKeys->m_strUi_FileKey;  }
	static BSTR Ui_Para_FileKey()  {   return g_pXmlKeys->m_strUi_Para_FileKey;  }
	static BSTR Report_FileKey()  {   return g_pXmlKeys->m_strReport_FileKey;  }
	static BSTR Hd_Rs_FileKey()  {   return g_pXmlKeys->m_strHd_Rs_FileKey;  }
	static BSTR Ui_IdKey()  {   return g_pXmlKeys->m_strUi_IdKey;  }
	static BSTR Charlib_FileKey()  {   return g_pXmlKeys->m_strCharLib_FileKey;  }
};



class CSttTestCtrrlMacroTestUIMngrConstGlobal
{
private:
	CSttTestCtrrlMacroTestUIMngrConstGlobal();
	virtual ~CSttTestCtrrlMacroTestUIMngrConstGlobal();

public:
	static CSttTestCtrrlMacroTestUIMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CSttTestCtrrlMacroTestUIMngrConstGlobal *g_pGlobal;

private:
//����ȫ�ֳ��������������  CExBaseList m_oVariableDataTypes

//����ȫ�ֳ�����������ʼ������������  void InitVariableDataTypes()

public:
//����ȫ�ֳ������������ʺ���������  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//����ȫ�ֳ���������  static CString g_pstrVariableType_CString;

};


//��������ļ������·��
#define STT_MACROTEST_UI_REALPATH_UI          _T("ui")
#define STT_MACROTEST_UI_REALPATH_ATSGEN      _T("atsgen")
#define STT_MACROTEST_UI_REALPATH_PARAS       _T("paras")
#define STT_MACROTEST_UI_REALPATH_TEMPLATE    _T("template")
#define STT_MACROTEST_UI_REALPATH_Device      _T("Device")

#define STT_ITEMS_Name_COMM_BFT     _T("����ǰ׼��")
#define STT_ITEMS_Name_COMM_AFT     _T("���Ժ�ָ�")
#define STT_ITEMS_Name_DEVRESET     _T("����װ�ø���̬")
#define STT_ITEMS_ID_COMM_BFT     _T("_Comm_BFT_")
#define STT_ITEMS_ID_COMM_AFT     _T("_Comm_AFT_")
#define STT_ITEMS_ID_BEFORETEST   _T("_BeforeTest_")	
#define STT_ITEMS_ID_AFTERTEST   _T("_AfterTest_")
#define STT_ITEMS_ID_DEVRESET   _T("_DevReset_")   //����װ�ø���̬����ֵ��ȫ�ˡ���ֵȫ��Ϊ���ֵ��ѹ��ȫ��
#define STT_REPORT_ID_INIT   _T("_Init_")	 //����ģ��ʱ����������Ŀ���ɵ�Ĭ�ϱ����ID���̶�ID
//
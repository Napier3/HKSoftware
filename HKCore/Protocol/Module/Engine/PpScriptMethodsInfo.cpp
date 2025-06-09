#include "stdafx.h"
#include "PpScriptMethodsInfo.h"

CString CPpScriptMethodInfo::GetMethodString()
{
	CString strMethodString;
	
    strMethodString.Format(_T("�������ƣ�%s\n ����ֵ��%s\n �����б�%s\n ����˵����%s\n")
        , m_strMethodName.GetString(),m_strReturnType.GetString()
        ,m_strParaList.GetString(),m_strMethodInfo.GetString());

	return strMethodString;
}

long CPpScriptMethodsInfo::g_nRef = 0;
CPpScriptMethodsInfo* CPpScriptMethodsInfo::g_pPpScriptMethods = NULL;

CPpScriptMethodsInfo::CPpScriptMethodsInfo()
{
	//���캯������ʼ������Lua�󶨺���

	//1	data
	CPpScriptMethodInfo* pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetValDataType");
	pMethod->m_strMethodInfo = _T("��ȡ��ǰ���������ݵ���������");
	pMethod->m_strParaList = _T("��");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//2
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetValDataLen");
	pMethod->m_strMethodInfo = _T("��ȡ��ǰ���������ݵ����ݳ���");
	pMethod->m_strParaList = _T("��");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//3	Byte/long
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValLong");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex,long nBytes");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValLong1");
	pMethod->m_strMethodInfo = _T("����2���ֽڵ���������λ�ֽ���ǰ����λ�ֽ��ں�");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValLong2");
	pMethod->m_strMethodInfo = _T("����4���ֽڵ���������λ�ֽ���ǰ����λ�ֽ��ں�");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//4	string
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValLong");
	pMethod->m_strMethodInfo = _T("���õ�ǰByteBlock�Ļ�������  nIndexΪ����ֵ����1��ʼ���");
	pMethod->m_strParaList = _T("long nIndex, long nValue, long nBytes");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValLong1");
	pMethod->m_strMethodInfo = _T("���õ�ǰByteBlock�Ļ�������  nIndexΪ����ֵ����1��ʼ���  ����2���ֽڵ���������λ�ֽ���ǰ����λ�ֽ��ں�");
	pMethod->m_strParaList = _T("long nIndex, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValLong2");
	pMethod->m_strMethodInfo = _T("���õ�ǰByteBlock�Ļ�������  nIndexΪ����ֵ����1��ʼ���  ����4���ֽڵ���������λ�ֽ���ǰ����λ�ֽ��ں�");
	pMethod->m_strParaList = _T("long nIndex, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//5
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pString, long nBytes");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//6
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, long nBytes");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbFdataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//7
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValFloat");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, float nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//8
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValFloat");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex");
	pMethod->m_strReturnType = _T("float");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbValByte");
	pMethod->m_strMethodInfo = _T("���õ�ǰByteBlock�Ļ������ݣ�nIndexΪ����ֵ��pString����ʵ�ʱ��ģ���FF F1 00��,����nBytes�ֽ�");
	pMethod->m_strParaList = _T("long nIndex, const char* pString, long nBytes");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbValByte");
	pMethod->m_strMethodInfo = _T("��ȡ��ǰByteBlock�Ļ������ݣ���nIndex����ȡnBytes�ֽڣ����ر��ĵ�����");
	pMethod->m_strParaList = _T("long nIndex, long nBytes");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//9
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LAnd");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal1, long nVal2");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//10
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LOr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal1, long nVal2");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//11
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LNot");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//11
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LComp");
	pMethod->m_strMethodInfo = _T("����");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LComp2");
	pMethod->m_strMethodInfo = _T("��short����");
	pMethod->m_strParaList = _T("short nVal");
	pMethod->m_strReturnType = _T("short");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LComp1");
	pMethod->m_strMethodInfo = _T("��char����");
	pMethod->m_strParaList = _T("char nVal");
	pMethod->m_strReturnType = _T("char");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//11
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LRComp");
	pMethod->m_strMethodInfo = _T("����");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//12
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LShift");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//13
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("RShift");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//14
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("MkWord");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nHigh, long nLow");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////15 time
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetYear");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////16 
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetMonth");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////17
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDay");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////18
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetHour");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////19
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetMinute");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////20
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSecond");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////21
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetMSecond");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	////21
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSystemTime");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//22 BCD/HEX
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("BcdToHex");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//23 
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("HexToBcd");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nVal");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//24
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("StrBcdToHex");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char*");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//25
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("StrHexToBcd");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char*");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//26 byteblock
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbEnable");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID, long nShow");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//27
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetByteBlockEnable2");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//28
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBbLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID, long nLen");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//29
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBbLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszBbID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

// 	//30 timer
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("KillTimer");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("const char *pszTimerID");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//31
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("ResetTimer");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("const char *pszTimerID");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//32
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("SetTimerLong");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("const char *pszTimerID, long nMs");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//33 ����ֵ
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("SetMatchResult");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("long nResult");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);
// 
// 	//34
// 	pMethod = new CPpScriptMethodInfo();
// 	pMethod->m_strMethodName = _T("SetParseResult");
// 	pMethod->m_strMethodInfo = _T("");
// 	pMethod->m_strParaList = _T("long nResult");
// 	pMethod->m_strReturnType = _T("void");
// 	AddTail(pMethod);
// 	pMethod->SetParent(this);

	//35 ��ȡ����
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetValue");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//���������2015.05.13
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetValueStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID");
	pMethod->m_strReturnType = _T("const char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//36
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetValueLong");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetValueDouble");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetValueStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char *pszVariableID, const char* strValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//37
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetPkgLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nLen");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetPkgValid");
	pMethod->m_strMethodInfo = _T("���ñ��Ķ������Ч״̬");
	pMethod->m_strParaList = _T("long nValid");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//38
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgLen");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgParsePos");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgCurrBufVal");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nOffset");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//39
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgNum");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//40
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetWBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID, long nValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//40
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("InsertBindData");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nTableRowIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("InsertBindDataset");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nTableRowIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("InsertBindLogicDevice");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nTableRowIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//41
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetWBindDataL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//42
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetWBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//43
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID");
	pMethod->m_strReturnType = _T("double");
	AddTail(pMethod);
	pMethod->SetParent(this);
	
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("SetNdDatasAttr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, double dValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);
	
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetNdDataAttrL");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, long nItemIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetNdDataAttrD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, long nItemIndex");
	pMethod->m_strReturnType = _T("double");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_ALL);
	pMethod->m_strMethodName = _T("GetNextNdDataByAttr");
	pMethod->m_strMethodInfo = _T("��ȡ���ݼ�����һ������ֵ���ڴ������ֵ��item-index");
	pMethod->m_strParaList = _T("const char* pszPath, const char* pszAttrID, double dValue, long nCurrItemIndex");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetWBindDataD");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID");
	pMethod->m_strReturnType = _T("double");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetBindDataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID");
	pMethod->m_strReturnType = _T("char*");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetWBindDataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("long nIndex, const char* pszAttrID");
	pMethod->m_strReturnType = _T("char*");
	AddTail(pMethod);
	pMethod->SetParent(this);
	//43
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDataStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, const char* pszValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindDatasetStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, const char* pszValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetBindLogicDeviceStr");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("const char* pszAttrID, const char* pszValue");
	pMethod->m_strReturnType = _T("void");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//44
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetPkgMaxLen");
	pMethod->m_strMethodInfo = _T("��ȡ��ǰ��Լ֧�ֵ���󳤶�");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("long");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("AdBindDataList");
	pMethod->m_strMethodInfo = _T("��ӵ�ǰ�󶨵����ݵ������У��������YX����ʱ����SOE��");
	pMethod->m_strParaList = _T("����1���豸����ģ���µ���ʱ����");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetMEA");
	pMethod->m_strMethodInfo = _T("��ӵ�ǰ�󶨵����ݵ������У��������YX����ʱ����SOE��");
	pMethod->m_strParaList = _T("����1���豸����ģ���µ���ʱ����");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("CalMEA");
	pMethod->m_strMethodInfo = _T("����MEAֵ");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("FireDataMsg");
	pMethod->m_strMethodInfo = _T("");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetCP24Time2a");
	pMethod->m_strMethodInfo = _T("���㵱ǰ�󶨵����ݶ����ֵ������ֵΪ24λ��ʾ��ǰʱ��");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP24Time2a");
	pMethod->m_strMethodInfo = _T("�����ֽڿ��ֵ����24λ�ĵ�ǰʱ���������");
	pMethod->m_strParaList = _T("����1�����ֽڿ黺����������ʼλ��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	
	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetCP32Time2a");
	pMethod->m_strMethodInfo = _T("���㵱ǰ�󶨵����ݶ����ֵ������ֵΪ32λ��ʾ��ǰʱ��");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP32Time2a");
	pMethod->m_strMethodInfo = _T("�����ֽڿ��ֵ����32λ�ĵ�ǰʱ���������");
	pMethod->m_strParaList = _T("����1�����ֽڿ黺����������ʼλ��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	
	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("GetCP56Time2a");
	pMethod->m_strMethodInfo = _T("���㵱ǰ�󶨵����ݶ����ֵ������ֵΪ56λ��ʾ��ǰʱ��");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP56Time2a");
	pMethod->m_strMethodInfo = _T("�����ֽڿ��ֵ����56λ�ĵ�ǰʱ���������");
	pMethod->m_strParaList = _T("����1�����ֽڿ黺����������ʼλ��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SetCP56Time2aEx");
	pMethod->m_strMethodInfo = _T("�����ֽڿ��ֵ����56λ�ĵ�ǰʱ���������");
	pMethod->m_strParaList = _T("����1�����ֽڿ黺����������ʼλ��,����2��ʱ���ı�������2015-4-23 8:00");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("BindItemIndex");
	pMethod->m_strMethodInfo = _T("�����ݶ������Ŀ�ţ�����ϵͳ���õİ�");
	pMethod->m_strParaList = _T("��������Ŀ�ŵ���ֵ");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitInLong16");
	pMethod->m_strMethodInfo = _T("��ȡ16λ����ָ��λ��ֵ");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�16λ����������2��������λ����");
	pMethod->m_strReturnType = _T("ָ��λ��ֵ��0����1");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetBitInLong16");
	pMethod->m_strMethodInfo = _T("����16λ������ָ��λ����1");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�16λ����������2��������λ����");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�16λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearBitInLong16");
	pMethod->m_strMethodInfo = _T("����16λ������ָ��λ����0");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�16λ����������2��������λ����");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�16λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);		

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitInLong32");
	pMethod->m_strMethodInfo = _T("��ȡ32λ����ָ��λ��ֵ");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�32λ����������2��������λ����");
	pMethod->m_strReturnType = _T("ָ��λ��ֵ��0����1");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetBitInLong32");
	pMethod->m_strMethodInfo = _T("����32λ������ָ��λ����1");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�32λ����������2��������λ����");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearBitInLong32");
	pMethod->m_strMethodInfo = _T("����32λ������ָ��λ����0");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�32λ����������2��������λ����");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitInLong8");
	pMethod->m_strMethodInfo = _T("��ȡ8λ����ָ��λ��ֵ");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�8λ����������2��������λ����");
	pMethod->m_strReturnType = _T("ָ��λ��ֵ��0����1");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetBitInLong8");
	pMethod->m_strMethodInfo = _T("����8λ������ָ��λ����1");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�8λ����������2��������λ����");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�8λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);
	
	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearBitInLong8");
	pMethod->m_strMethodInfo = _T("����8λ������ָ��λ����0");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�8λ����������2��������λ����");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�8λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetBitRangeInLong8");
	pMethod->m_strMethodInfo = _T("��ȡ8λ����ָ��λ��Χ��ֵ");
	pMethod->m_strParaList = _T("����1��Դ���ݣ�8λ����������2��������λ������ʼλ�ã�����3��������λ��������λ��");
	pMethod->m_strReturnType = _T("ָ��λ��Χ��ֵ");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfCalFloat");
	pMethod->m_strMethodInfo = _T("�ķ����������㷽������������ת��Ϊ3�ֽ�����");
	pMethod->m_strParaList = _T("��������Ҫת���ĸ�����");
	pMethod->m_strReturnType = _T("����ת���ɹ���DWORD����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	//
	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfGetAna24Float");
	pMethod->m_strMethodInfo = _T("�ķ����������㷽������3�ֽ�����ת��Ϊ������");
	pMethod->m_strParaList = _T("����1���ֽڿ黺������λ��");
	pMethod->m_strReturnType = _T("���ظ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfGetBcd24Float");
	pMethod->m_strMethodInfo = _T("�ķ����������㷽������3�ֽ�BCD����ת��Ϊ������");
	pMethod->m_strParaList = _T("����1���ֽڿ黺������λ��");
	pMethod->m_strReturnType = _T("���ظ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfSetBcd24Float");
	pMethod->m_strMethodInfo = _T("��������д��3�ֽ�BCD���ݻ�����");
	pMethod->m_strParaList = _T("����1��������������2���ֽڿ黺��������ʼλ��");
	pMethod->m_strReturnType = _T("������");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PKG);
	pMethod->m_strMethodName = _T("SfSetBcd24FloatEx");
	pMethod->m_strMethodInfo = _T("��������д��3�ֽ�BCD���ݻ��������������С�����������㡿");
	pMethod->m_strParaList = _T("����1��������������2���ֽڿ黺��������ʼλ��");
	pMethod->m_strReturnType = _T("������");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetGlobal");
	pMethod->m_strMethodInfo = _T("��ȡȫ�ֱ���");
	pMethod->m_strParaList = _T("����1������ID");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetGlobal");
	pMethod->m_strMethodInfo = _T("����ȫ�ֱ���");
	pMethod->m_strParaList = _T("����1������ID������2�� ֵ");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AddGlobal");
	pMethod->m_strMethodInfo = _T("����ȫ�ֱ�����ֵ����һ����ֵ");
	pMethod->m_strParaList = _T("����1������ID������2�� ֵ");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SubGlobal");
	pMethod->m_strMethodInfo = _T("����ȫ�ֱ�����ֵ����һ����ֵ");
	pMethod->m_strParaList = _T("����1������ID������2�� ֵ");
	pMethod->m_strReturnType = _T("");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetIP");
	pMethod->m_strMethodInfo = _T("��ȡͨѶͨ������IP��ַ");
	pMethod->m_strParaList = _T("��������������ͨѶ�ķ�ʽ��Ϊ�ı�\"udp\"��\"tcp\"");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ������IP��ַ����������ڣ�����192.168.1.10");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetRemoteIP");
	pMethod->m_strMethodInfo = _T("��ȡͨѶͨ��Զ��IP��ַ");
	pMethod->m_strParaList = _T("��������������ͨѶ�ķ�ʽ��Ϊ�ı�\"udp\"��\"tcp\"");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ������IP��ַ����������ڣ�����192.168.1.10");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("SetPpRunState");
	pMethod->m_strMethodInfo = _T("���ù���ִ�е�״̬");
	pMethod->m_strParaList = _T("����������ִ�е�״̬��0=����������1=ͨѶ����2=ͨѶ��λ");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ���");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("SetPpValid");
	pMethod->m_strMethodInfo = _T("���ù�����Ч��״̬");
	pMethod->m_strParaList = _T("������������Ч��״̬��0=��Ч��1=��Ч��");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ���");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDeviceAddr");
	pMethod->m_strMethodInfo = _T("��ȡ�豸��ַ");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDeviceAttrL");
	pMethod->m_strMethodInfo = _T("��ȡ�豸��������");
	pMethod->m_strParaList = _T("���Ե�ID,�ַ���");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDeviceAttrStr");
	pMethod->m_strMethodInfo = _T("��ȡ�豸��������");
	pMethod->m_strParaList = _T("���Ե�ID,�ַ���");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ��ַ���");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDeviceAttrL");
	pMethod->m_strMethodInfo = _T("�����豸��������");
	pMethod->m_strParaList = _T("����1�����Ե�ID,�ַ���������2����������ֵ");
	pMethod->m_strReturnType = _T("������");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDeviceAttrStr");
	pMethod->m_strMethodInfo = _T("�����豸��������");
	pMethod->m_strParaList = _T("����1�����Ե�ID,�ַ���������2�������ַ���ֵ");
	pMethod->m_strReturnType = _T("������");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetCmmMode");
	pMethod->m_strMethodInfo = _T("��ȡͨѶģʽ");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetPort");
	pMethod->m_strMethodInfo = _T("��ȡͨѶ�Ķ˿�");
	pMethod->m_strParaList = _T("������ͨѶģʽ");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSystemPara");
	pMethod->m_strMethodInfo = _T("��ȡϵͳ�Ĳ���");
	pMethod->m_strParaList = _T("������ID");
	pMethod->m_strReturnType = _T("���ؽ�����ݣ�32λ����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("LogPrint");
	pMethod->m_strMethodInfo = _T("��ӡ����");
	pMethod->m_strParaList = _T("����1������ַ�������2�� ֵ");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ShowMsg");
	pMethod->m_strMethodInfo = _T("����ı���Ϣ");
	pMethod->m_strParaList = _T("����1������ı���Ϣ�ַ���");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("Run");
	pMethod->m_strMethodInfo = _T("���й���");
	pMethod->m_strParaList = _T("����������ID");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("Connect");
	pMethod->m_strMethodInfo = _T("����");
	pMethod->m_strParaList = _T("��������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo(SCRIPT_FUN_PROCEDURE);
	pMethod->m_strMethodName = _T("DisConnect");
	pMethod->m_strMethodInfo = _T("�Ͽ�����");
	pMethod->m_strParaList = _T("��������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	//////////////////////////////////////////////////////////////////////////
	//
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CombineDsPathStr");
	pMethod->m_strMethodInfo = _T("���·�������������һ���ַ���·��");
	pMethod->m_strParaList = _T("����1������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CombineDsPathL");
	pMethod->m_strMethodInfo = _T("���·�������������һ������·��");
	pMethod->m_strParaList = _T("����1������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearDsPath");
	pMethod->m_strMethodInfo = _T("���������ϵ��ַ���·��������");
	pMethod->m_strParaList = _T("��������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsPath");
	pMethod->m_strMethodInfo = _T("��ȡ��ϵ�����·��");
	pMethod->m_strParaList = _T("��������");
	pMethod->m_strReturnType = _T("����·���ַ���");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertDsData");
	pMethod->m_strMethodInfo = _T("�����ݼ��в���һ�����ݶ���");
	pMethod->m_strParaList = _T("����1������·�������硰Device1$CPU1$dsEna��������2�����������ţ�����3�������ݵ���Ŀ��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataCount");
	pMethod->m_strMethodInfo = _T("��ȡ���ݼ����ݶ�����Ŀ");
	pMethod->m_strParaList = _T("����1������·�������硰Device1$CPU1$dsEna����");
	pMethod->m_strReturnType = _T("���ݼ���Ŀ");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataCount");
	pMethod->m_strMethodInfo = _T("��ȡ���ݼ����ݶ�����Ŀ");
	pMethod->m_strParaList = _T("����1������·�������硰Device1$CPU1$dsEna����");
	pMethod->m_strReturnType = _T("���ݼ���Ŀ");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("ClearDsDatas");
	pMethod->m_strMethodInfo = _T("������ݼ����ݶ���");
	pMethod->m_strParaList = _T("����1������·�������硰Device1$CPU1$dsEna����");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertDataset");
	pMethod->m_strMethodInfo = _T("���߼��豸�в���һ�����ݼ�");
	pMethod->m_strParaList = _T("����1������·�������硰Device1$CPU1��������2�����������ţ�����3�������ݵ���Ŀ��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertLogicDevice");
	pMethod->m_strMethodInfo = _T("���豸�в���һ���߼��豸");
	pMethod->m_strParaList = _T("����1������·�������硰Device1��������2�����������ţ�����3�������ݵ���Ŀ��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("InsertDevice");
	pMethod->m_strMethodInfo = _T("����豸����ģ�������һ���µ��豸");
	pMethod->m_strParaList = _T("����1���豸ID�����Σ�����2���豸����");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataL");
	pMethod->m_strMethodInfo = _T("������������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������2������ID�����硰value��������3������ֵ������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataD");
	pMethod->m_strMethodInfo = _T("������������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������2������ID�����硰value��������3������ֵ��������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataDEx");
	pMethod->m_strMethodInfo = _T("������������ֵ");
	pMethod->m_strParaList = _T("����1��װ������������2������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������3������ID�����硰value��������4������ֵ��������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataDBatch");
	pMethod->m_strMethodInfo = _T("������������ֵ");
	pMethod->m_strParaList = _T("����1�����ݼ�ID������YC��������2������ID�����硰YC001��������3������ID�����硰value��������4������ֵ��������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDsDataStr");
	pMethod->m_strMethodInfo = _T("������������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������2������ID�����硰value��������3������ֵ���ַ���");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetDatasetStr");
	pMethod->m_strMethodInfo = _T("�������ݼ�������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1$dsEna��������2������ID�����硰name��������3������ֵ���ַ���");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SetLogicDeviceStr");
	pMethod->m_strMethodInfo = _T("�����߼��豸������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1��������2������ID�����硰name��������3������ֵ���ַ���");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CountDsData");
	pMethod->m_strMethodInfo = _T("ͳ�����ݼ�����Ҫ������ݵĸ���");
	pMethod->m_strParaList = _T("����1������·����������ID·����CPU1$dsEna$Yb000�����������·����1$23$2�����������ݱ�š�����ȫ�ֱ�����ID��������2������ID�����硰value��������3����������ID�����ֵ");
	pMethod->m_strReturnType = _T("�������ԣ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	
	
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CountDsDataEx");
	pMethod->m_strMethodInfo = _T("ͳ�����ݼ�����Ҫ������ݵĸ���");
	pMethod->m_strParaList = _T("����1������·����������ID·����CPU1$dsEna$Yb000�����������·����1$23$2�����������ݱ�š�����ȫ�ֱ�����ID��������2�����Ե�ʽ�����硾change=1;datatype-id=3;��");
	pMethod->m_strReturnType = _T("�������ԣ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSequenceDsDatas");
	pMethod->m_strMethodInfo = _T("ͳ�����ݼ�����Ҫ������ݵĸ���");
	pMethod->m_strParaList = _T("����1������·����������ID·����CPU1$dsEna$Yb000�����������·����1$23$2�����������ݱ�š�����ȫ�ֱ�����ID��������2������ID�����硰value��������3����������ID�����ֵ������4����ʼ�����ŵ�ȫ�ֱ���������5����ֹ�����ŵ�ȫ������������6�����ͳ�Ƹ���");
	pMethod->m_strReturnType = _T("�������ԣ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataL");
	pMethod->m_strMethodInfo = _T("��ȡ��������ֵ");
	pMethod->m_strParaList = _T("����1������·����������ID·����CPU1$dsEna$Yb000�����������·����1$23$2�����������ݱ�š�����ȫ�ֱ�����ID��������2������ID�����硰value��");
	pMethod->m_strReturnType = _T("�������ԣ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataD");
	pMethod->m_strMethodInfo = _T("��ȡ��������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������2������ID�����硰value��");
	pMethod->m_strReturnType = _T("�������ԣ�������");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataDEx");
	pMethod->m_strMethodInfo = _T("��ȡ��������ֵ");
	pMethod->m_strParaList = _T("����1��װ�������ţ�����2������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������3������ID�����硰value��");
	pMethod->m_strReturnType = _T("�������ԣ�������");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetDsDataStr");
	pMethod->m_strMethodInfo = _T("��ȡ��������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������2������ID�����硰value��");
	pMethod->m_strReturnType = _T("�������ԣ��ַ���ֵ");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("SumDsDataD");
	pMethod->m_strMethodInfo = _T("��ȡ��������ֵ");
	pMethod->m_strParaList = _T("����1������·�������硰CPU1$dsEna$Yb000�����ߡ����ݱ�š�������2������ID�����硰value��������3��װ�õ���ʼ����������4��װ�õ���ֹ����");
	pMethod->m_strReturnType = _T("�������ԣ�������");
	AddTail(pMethod);
	pMethod->SetParent(this);	


	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AdDsDataList");
	pMethod->m_strMethodInfo = _T("������ݶ��󵽱������ݼ���");
	pMethod->m_strParaList = _T("����1�����ݶ����·��������2���������ݼ���ID");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AdDsPkgDetail");
	pMethod->m_strMethodInfo = _T("������ݼ���������ݶ��󵽵�ǰ�ı��Ķ�����");
	pMethod->m_strParaList = _T("����1�����ݶ����·��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AdValPkgDetail");
	pMethod->m_strMethodInfo = _T("������ݶ��󵽵�ǰ�ı��Ķ�����");
	pMethod->m_strParaList = _T("����1���������ƣ��ַ���������2������ID���ַ���������3������ֵ���ַ���");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetRcvIdle");
	pMethod->m_strMethodInfo = _T("��ȡû�н��յ����ĵ�ʱ�䳤��");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("ʱ�䳤�ȣ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("GetSendIdle");
	pMethod->m_strMethodInfo = _T("��ȡû�б��ı��ĵ�ʱ�䳤��");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("ʱ�䳤�ȣ�����");
	AddTail(pMethod);
	pMethod->SetParent(this);	

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("AddSectionData");
	pMethod->m_strMethodInfo = _T("��ӱ������ݵ�һ�������б��У�����������������洢Ϊ�ļ�");
	pMethod->m_strParaList = _T("����1����ӵ����ֽ�����������������2����ӵ��ֽ���������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("Fis103SaveRCDFile");
	pMethod->m_strMethodInfo = _T("�������б��е����ݴ洢Ϊ¼���ļ�");
	pMethod->m_strParaList = _T("����1���洢��·�����ַ���������2��������¼���ļ����ĳ���");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("Fis103SaveCommonFile");
	pMethod->m_strMethodInfo = _T("�������б��е����ݴ洢Ϊ��ͨ�ļ�");
	pMethod->m_strParaList = _T("����1���洢��·�����ַ���������2���������ļ����ĳ���");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	//	RegisterHostAPIFunc (-1, "CreateFile", xvm_script_CreateFile);
	//RegisterHostAPIFunc (-1, "WriteFile", xvm_script_WriteFile);
	//RegisterHostAPIFunc (-1, "CloseFile", xvm_script_CloseFile);
	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CreateFile");
	pMethod->m_strMethodInfo = _T("�����ļ�");
	pMethod->m_strParaList = _T("����1���洢��·�����ַ���������2���ļ�����");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("WriteFile");
	pMethod->m_strMethodInfo = _T("д�ļ�");
	pMethod->m_strParaList = _T("����1���ֽڿ쿪ʼ�ֽڱ�ţ�����������2���ֽ���Ŀ������");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CloseFile");
	pMethod->m_strMethodInfo = _T("�ر��ļ�");
	pMethod->m_strParaList = _T("��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcClear");
	pMethod->m_strMethodInfo = _T("���CRCУ���û�����");
	pMethod->m_strParaList = _T("");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcPush");
	pMethod->m_strMethodInfo = _T("��CRCУ���û��������һ��BYTE");
	pMethod->m_strParaList = _T("����1��BYTE��ֵ");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcPushBb");
	pMethod->m_strMethodInfo = _T("��CRCУ���û��������һ��BYTE");
	pMethod->m_strParaList = _T("����1���ֽڿ黺�����ı��");
	pMethod->m_strReturnType = _T("��");
	AddTail(pMethod);
	pMethod->SetParent(this);

	pMethod = new CPpScriptMethodInfo();
	pMethod->m_strMethodName = _T("CrcSf2000");
	pMethod->m_strMethodInfo = _T("���㻺������CRC��ֵ");
	pMethod->m_strParaList = _T("��");
	pMethod->m_strReturnType = _T("����Word");
	AddTail(pMethod);
	pMethod->SetParent(this);
}

CPpScriptMethodsInfo* CPpScriptMethodsInfo::Create()
{
	g_nRef ++;

	if(g_nRef == 1)
	{
		g_pPpScriptMethods = new CPpScriptMethodsInfo();
	}

	return g_pPpScriptMethods;
}

void CPpScriptMethodsInfo::Release()
{
	g_nRef -- ;

	if(g_nRef == 0)
	{
		delete g_pPpScriptMethods;
		g_pPpScriptMethods = NULL;
	}
}

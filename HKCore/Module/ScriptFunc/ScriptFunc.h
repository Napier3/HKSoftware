//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ScriptFunc.h  CScriptFunc

#pragma once

#include "ScriptFuncGlobal.h"


#include "ScriptFuncPara.h"

class CScriptFunc : public CExBaseList
{
public:
	CScriptFunc();
	virtual ~CScriptFunc();


	CString  m_strReturn;
	CString  m_strType;
	CString  m_strText;

//���غ���
public:
	virtual UINT GetClassID() {    return SFNCLASSID_CSCRIPTFUNC;   }
	virtual BSTR GetXmlElementKey()  {      return CScriptFuncXmlRWKeys::CScriptFuncKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//�ű��������󣬹���ʱֻ���������������Ӷ���������� 
	//20200204  shaolei 
	virtual DWORD Filter(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD Filter_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200204 id��nameͬʱ���ˣ�id����
	virtual DWORD Filter_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200306 id��nameͬʱ���ˣ�id���ȣ������ִ�Сд
	virtual DWORD Filter_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


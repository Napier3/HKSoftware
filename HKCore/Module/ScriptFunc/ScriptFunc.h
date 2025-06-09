//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
public:
	virtual UINT GetClassID() {    return SFNCLASSID_CSCRIPTFUNC;   }
	virtual BSTR GetXmlElementKey()  {      return CScriptFuncXmlRWKeys::CScriptFuncKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//脚本函数对象，过滤时只过滤自身，不过滤子对象，因此重载 
	//20200204  shaolei 
	virtual DWORD Filter(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	virtual DWORD Filter_ID(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200204 id、name同时过滤，id优先
	virtual DWORD Filter_ID_Name(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);
	//shaolei 20200306 id、name同时过滤，id优先，不区分大小写
	virtual DWORD Filter_ID_Name_NoCase(const CString &strTxtFilter, DWORD dwMode=FILTERMODE_HAS);

//私有成员变量
private:

//私有成员变量访问方法
public:
};


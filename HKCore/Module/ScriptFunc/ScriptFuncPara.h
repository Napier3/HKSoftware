//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ScriptFuncPara.h  CScriptFuncPara

#pragma once

#include "ScriptFuncGlobal.h"



class CScriptFuncPara : public CExBaseObject
{
public:
	CScriptFuncPara();
	virtual ~CScriptFuncPara();


	CString  m_strType;
//���غ���
public:
	virtual UINT GetClassID() {    return SFNCLASSID_CSCRIPTFUNCPARA;   }
	virtual BSTR GetXmlElementKey()  {      return CScriptFuncXmlRWKeys::CScriptFuncParaKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


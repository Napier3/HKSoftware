//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbUIMacro.h  CGbUIMacro

#pragma once

#include "MacroScriptMngrGlobal.h"



class CGbUIMacro : public CExBaseObject
{
public:
	CGbUIMacro();
	virtual ~CGbUIMacro();


	CString  m_strDLL;
//���غ���
public:
	virtual UINT GetClassID() {    return TMSCLASSID_CGBUIMACRO;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CGbUIMacroKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


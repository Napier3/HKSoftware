//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbUIMacroConfig.h  CGbUIMacroConfig

#pragma once

#include "MacroScriptMngrGlobal.h"


#include "GbUIMacro.h"

class CGbUIMacroConfig : public CExBaseList
{
public:
	static CGbUIMacroConfig* g_pGbUIMacroConfig;
	static CGbUIMacroConfig* Create();
	static void Release();

private:
	CGbUIMacroConfig();
	virtual ~CGbUIMacroConfig();
	static long g_nRef;


//���غ���
public:
	virtual UINT GetClassID() {    return TMSCLASSID_CGBUIMACROCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroScriptMngrXmlRWKeys::CGbUIMacroConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


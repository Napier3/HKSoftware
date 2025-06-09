//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg91StateWordMngr.h  CIecCfg91StateWordMngr

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfg91StateWord.h"

class CIecCfg91StateWordMngr : public CExBaseList
{
public:
	CIecCfg91StateWordMngr();
	virtual ~CIecCfg91StateWordMngr();

	CIecCfg91StateWord *m_pStateWord;
	CDataTypes *m_pStDataTypeMngr;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91STATEWORDMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg91StateWordMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long XmlReadChildren(CXmlRWNodeListBase &oNodes, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CIecCfg91StateWord* GetIecCfg91StateWord();
	CDataTypes* GetStDataTypeMngr();

	BOOL InitStateWordMngr();
};


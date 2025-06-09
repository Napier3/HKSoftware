//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ParaMap.h  CParaMap

#pragma once

#include "MacroMapMngrGlobal.h"


#include "ValueMap.h"

class CParaMap : public CExBaseList
{
public:
	CParaMap();
	virtual ~CParaMap();


	CString  m_strMapName;
	CString  m_strMapID;
	long  m_nUse;
//���غ���
public:
	virtual UINT GetClassID() {    return MPCLASSID_CPARAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroMapMngrXmlRWKeys::CParaMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CValueMap* AddNewValueMap();
	BOOL GetMapValue(CString &strValue);
	
};


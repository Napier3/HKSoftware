//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ValueMap.h  CValueMap

#pragma once

#include "MacroMapMngrGlobal.h"



class CValueMap : public CExBaseObject
{
public:
	CValueMap();
	virtual ~CValueMap();

	//CString  m_strSrcName; //PowerTest����ֵ������ name
	CString  m_strMapName; //Ats����ֵ������
	//CString  m_strSrcValue; //PowerTest����ֵ id
	CString  m_strMapID; //Ats����ֵ
//���غ���
public:
	virtual UINT GetClassID() {    return MPCLASSID_CVALUEMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroMapMngrXmlRWKeys::CValueMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//ParaMapExpr.h  CParaMapExpr

#pragma once

#include "MacroMapMngrGlobal.h"


#include "ParaMap.h"

class CParaMapCal : public CExBaseObject
{
public:
	CParaMapCal();
	virtual ~CParaMapCal();


	CString  m_strMapName;
	CString  m_strMapID;
	CString  m_strScript;

//���غ���
public:
	virtual UINT GetClassID() {    return MPCLASSID_CPARAMAPCAL;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroMapMngrXmlRWKeys::CParaMapCalKey();     }
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


class CParaMapExpr : public CExBaseList
{
public:
	CParaMapExpr();
	virtual ~CParaMapExpr();


	CString  m_strExpr;

//���غ���
public:
	virtual UINT GetClassID() {    return MPCLASSID_CPARAMAPEXPR;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroMapMngrXmlRWKeys::CParaMapExprKey();     }
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
	CParaMapCal* AddNewParaMapCal();
	
};

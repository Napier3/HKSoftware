//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MacroMap.h  CMacroMap

#pragma once

#include "MacroMapMngrGlobal.h"


#include "ParaMap.h"
#include "ParaMapExpr.h"

class CMacroMap : public CExBaseList
{
public:
	CMacroMap();
	virtual ~CMacroMap();


	CString  m_strMapName;
	CString m_strMapID;
//���غ���
public:
	virtual UINT GetClassID() {    return MPCLASSID_CMACROMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CMacroMapMngrXmlRWKeys::CMacroMapKey();     }
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
	BOOL MapPara(const CString &strPttParaID, const CString &strPttParaValue, CString &strAtsParaID, CString &strAtsValue);
	BOOL MapPara(const CString &strPttParaID, CString &strAtsParaID);

	CParaMapExpr* AddNewParaMapExpr();

};


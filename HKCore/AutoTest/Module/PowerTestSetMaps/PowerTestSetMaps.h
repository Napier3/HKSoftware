//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PowerTestSetMaps.h  CPowerTestSetMaps

#pragma once

#include "PowerTestSetMapsGlobal.h"


#include "SetMap.h"
#include "SysParaMap.h"

class CPowerTestSetMaps : public CExBaseList
{
public:
	CPowerTestSetMaps();
	virtual ~CPowerTestSetMaps();


//���غ���
public:
	virtual UINT GetClassID() {    return SETMAPMNGRCLASSID_CPOWERTESTSETMAPS;   }
	virtual BSTR GetXmlElementKey()  {      return CPowerTestSetMapsXmlRWKeys::CPowerTestSetMapsKey();     }
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
	virtual BOOL SaveXmlFile(const CString &strFile);
	CSetMap* FindSetMapByFullPath(const CString &strFullPath);
	CSysParaMap* FindSysParaMapByFullPath(const CString &strFullPath);
};


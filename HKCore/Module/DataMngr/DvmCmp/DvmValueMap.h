//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmValueMap.h  CDvmValueMap

#pragma once

#include "../DvmValue.h"
#include "DvmMapObject.h"


class CDvmValueMap : public CDvmMapObject
{
public:
	CDvmValueMap();
	virtual ~CDvmValueMap();


//���غ���
public:
	virtual UINT GetClassID() {    return DMPCLASSID_CDVMVALUEMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmValueMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual CDvmMapObject* CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CDvmValueMap* AddDvmMap(CDvmValue *pStand, CDvmValue *pDest);
	virtual BOOL CanFindDvmMapChild(UINT nClassID);

	virtual void SetMap0(CExBaseObject *pMap);
	virtual void SetStand0(CExBaseObject *pStand);

	CString GetMapID();
	CString GetMapIDBySameName();
	
};


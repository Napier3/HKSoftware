//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmValueMap.h  CDvmValueMap

#pragma once

#include "../DvmValue.h"
#include "DvmMapObject.h"


class CDvmValueMap : public CDvmMapObject
{
public:
	CDvmValueMap();
	virtual ~CDvmValueMap();


//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:
	CDvmValueMap* AddDvmMap(CDvmValue *pStand, CDvmValue *pDest);
	virtual BOOL CanFindDvmMapChild(UINT nClassID);

	virtual void SetMap0(CExBaseObject *pMap);
	virtual void SetStand0(CExBaseObject *pStand);

	CString GetMapID();
	CString GetMapIDBySameName();
	
};


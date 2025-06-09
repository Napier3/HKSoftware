//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDataMap.h  CDvmDataMap

#pragma once

#include "../DvmData.h"
#include "DvmValueMap.h"


class CDvmDataMap : public CDvmMapObject
{
public:
	CDvmDataMap();
	virtual ~CDvmDataMap();


//重载函数
public:
	virtual UINT GetClassID() {    return DMPCLASSID_CDVMDATAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDataMapKey();     }
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
	CDvmValueMap* FindByMap(const CString &strMapID);

	CDvmValueMap* AddDvmMap(CDvmValue *pStand, CDvmValue *pDest);

	//20231103 huangliang 
	CDvmValueMap* AddDvmMap(CDvmValue *pStand, CDvmData *pDest);

	virtual BOOL CanFindDvmMapChild(UINT nClassID);
	virtual void SetMap0(CExBaseObject *pMap);
	virtual void SetStand0(CExBaseObject *pStand);
};

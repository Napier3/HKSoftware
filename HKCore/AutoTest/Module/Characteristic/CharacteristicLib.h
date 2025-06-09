//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicLib.h  CCharacteristicLib

#pragma once

#include "CharacteristicGlobal.h"
#include "CharacteristicTmplate.h"
#include "CharacterFolder.h"


class CCharacteristicLib : public CCharacterFolder
{
public:
	CCharacteristicLib();
	virtual ~CCharacteristicLib();

	static const CString g_strDefaultLibFile;

	static CCharacterArea* GetGlobalCharAreaSrc();
	static void CreateGlobalCharAreaSrc();
	static void ReleaseGlobalCharAreaSrc();

protected:
	static long g_nGlobalCharAreaSrcRef;
	static CCharacterArea *g_pGlobalCharAreaSrc;


//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTICLIB;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicLibKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:
	CString m_strLibFile;

//私有成员变量访问方法
public:
	CString GetLibFile(const CString &strLibFile);

	BOOL OpenCharLibFile(const CString &strLibFile);
	BOOL SaveCharLibFile(const CString &strLibFile);
};


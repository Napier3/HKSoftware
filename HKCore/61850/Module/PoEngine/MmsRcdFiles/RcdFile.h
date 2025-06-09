//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RcdFile.h  CRcdFile

#pragma once

#include "MmsRcdFilesMngrGlobal.h"



class CRcdFile : public CExBaseObject
{
public:
	CRcdFile();
	virtual ~CRcdFile();


	long  m_nFileSize;
	double  m_fFileTime;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRCDFILE;   }
	virtual BSTR GetXmlElementKey()  {      return CMmsRcdFilesMngrXmlRWKeys::CRcdFileKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};


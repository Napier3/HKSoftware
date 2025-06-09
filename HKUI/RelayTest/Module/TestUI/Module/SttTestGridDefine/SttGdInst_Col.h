//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdInst_Col.h  CSttGdInst_Col

#pragma once

#include "SttTestGridDefineGlobal.h"
#include "SttGdColDef.h"


class CSttGdInst_Col : public CExBaseObject
{
public:
	CSttGdInst_Col();
	virtual ~CSttGdInst_Col();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDINST_COL;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdInst_ColKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CSttGdColDef *m_pSttGdColDef_Ref;
};


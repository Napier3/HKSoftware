//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg91StateWord.h  CIecCfg91StateWord

#pragma once

#include "IecCfgDataMngrGlobal.h"


#include "IecCfg91StateWordBit.h"

class CIecCfg91StateWord : public CExBaseList
{
public:
	CIecCfg91StateWord();
	virtual ~CIecCfg91StateWord();


//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG91STATEWORD;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CIecCfg91StateWordKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	void SetWord(DWORD dwStateWord);
	DWORD GetWord();
};


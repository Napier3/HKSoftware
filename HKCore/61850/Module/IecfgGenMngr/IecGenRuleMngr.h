//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecGenRuleMngr.h  CIecGenRuleMngr

#pragma once

#include "IecfgGenMngrGlobal.h"
#include "IecDeviceRule.h"

#define IECFG_GEN_MNGR_FILE_NAME_DEFAULT                  _T("iecfg-generate-mngr.xml")                  



class CIecGenRuleMngr : public CExBaseList
{
public:
	CIecGenRuleMngr();
	virtual ~CIecGenRuleMngr();


	CString  m_strNetDesc;
//重载函数
public:
	virtual UINT GetClassID() {    return GENRATECLASSID_CIECGENRULEMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CIecfgGenMngrXmlRWKeys::CIecGenRuleMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL OpenIecfgGenMnrFile(const CString &strIecfgGenMnrFile = NULL);
};

extern CIecGenRuleMngr g_oIecfgGenMngr;
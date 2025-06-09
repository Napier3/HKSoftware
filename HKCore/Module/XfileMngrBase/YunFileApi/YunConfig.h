//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//YunConfig.h  CYunConfig

#pragma once

#include "YunConfigGlobal.h"



class CYunConfig : public CExBaseObject
{
public:
	CYunConfig();
	virtual ~CYunConfig();


	CString  m_strProgID;
//重载函数
public:
	virtual UINT GetClassID() {    return YUNCLASSID_CYUNCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CYunConfigXmlRWKeys::CYunConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//私有成员变量
private:

//私有成员变量访问方法
public:
};


//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DmdtNodeData.h  CDmdtNodeData

#pragma once

#include "DmDataTemplateGlobal.h"



class CDmdtNodeData : public CExBaseObject
{
public:
	CDmdtNodeData();
	virtual ~CDmdtNodeData();


	CString  m_strIndex;
	CString  m_strUnit;
//重载函数
public:
	virtual UINT GetClassID() {    return DMDTCLASSID_CDMDTNODEDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CDmDataTemplateXmlRWKeys::CDmdtNodeDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	static long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//私有成员变量
private:

//私有成员变量访问方法
public:
};


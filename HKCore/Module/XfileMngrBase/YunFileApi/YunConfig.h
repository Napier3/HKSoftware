//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//YunConfig.h  CYunConfig

#pragma once

#include "YunConfigGlobal.h"



class CYunConfig : public CExBaseObject
{
public:
	CYunConfig();
	virtual ~CYunConfig();


	CString  m_strProgID;
//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


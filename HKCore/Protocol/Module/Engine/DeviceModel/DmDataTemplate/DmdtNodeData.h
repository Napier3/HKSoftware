//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};


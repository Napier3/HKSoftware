//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttXuiDataTabs.h  CSttXuiDataTabs

#pragma once

#include "SttXMainConfigGlobal.h"

#include "SttXuiDataBase.h"

#include "SttXuiDataTab.h"

class CSttXuiDataTabs : public CSttXuiDataBase
{
public:
	CSttXuiDataTabs();
	virtual ~CSttXuiDataTabs();


	long  m_nX;
	long  m_nY;
	long  m_nCy;
	long  m_nCx;
	CString m_strFont;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTXUIDATATABS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttXMainConfigXmlRWKeys::CSttXuiDataTabsKey();     }
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};


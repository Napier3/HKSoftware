//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttXuiDataBtnsGroup.h  CSttXuiDataBtnsGroup

#pragma once

#include "SttXMainConfigGlobal.h"

#include "SttXuiDataBase.h"

#include "SttXuiDataButton.h"

class CSttXuiDataBtnsGroup : public CSttXuiDataBase
{
public:
	CSttXuiDataBtnsGroup();
	virtual ~CSttXuiDataBtnsGroup();


	long  m_nX;
	long  m_nY;
	long  m_nCx;
	long  m_nCy;
	long  m_nInset;
	CString  m_strType;
	CString  m_strFrom;
	CString  m_strFont;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTXUIDATABTNSGROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CSttXMainConfigXmlRWKeys::CSttXuiDataBtnsGroupKey();     }
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


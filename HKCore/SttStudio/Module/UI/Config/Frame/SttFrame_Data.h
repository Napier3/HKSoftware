//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttFrame_Data.h  CSttFrame_Data

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"



class CSttFrame_Data : public CExBaseObject
{
public:
	CSttFrame_Data();
	virtual ~CSttFrame_Data();


	long  m_nWidth;
	CString  m_strIcon;
	CString  m_strType;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_DATA;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_DataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};


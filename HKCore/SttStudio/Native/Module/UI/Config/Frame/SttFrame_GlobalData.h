//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CSttFrame_GlobalData.h  CSttFrame_GlobalData

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"



class CSttFrame_GlobalData : public CExBaseObject
{
public:
	CSttFrame_GlobalData();
	virtual ~CSttFrame_GlobalData();


	CString  m_strDataType;
	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_GLOBALDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_GlobalDataKey();     }
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
};


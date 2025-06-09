//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttIotCmd.h  CSttIotCmd

#pragma once

#include "SttCmdDefineGlobal.h"

#include "SttCmdBase.h"

class CSttIotCmd : public CSttCmdBase, public CXObjectRefBase
{
public:
	CSttIotCmd();
	virtual ~CSttIotCmd();

	CString  m_strTestor;
//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTIOTCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttIotCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

//���Ա������ʷ���
public:

	static CXObjectRefBase* New()
	{
		return new CSttIotCmd();
	}
};


class CSttIotCmdDriver : public CXObjectRefDriver
{
public:
	CSttIotCmdDriver();
	virtual ~CSttIotCmdDriver();

	CSttIotCmd* NewSttIotCmd(void *pCmmInterface)	;
	CSttIotCmd* SttIotCmd()	{	return (CSttIotCmd*)GetXObjectRef();	}

	//2022-10-19 lijunqing
	virtual CXObjectRefDriver* Clone();
};


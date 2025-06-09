//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAtsCmd.h  CSttAtsCmd

#pragma once

#include "SttCmdDefineGlobal.h"

#include "SttCmdBase.h"
class CSttSocketDataBase;

//2021-7-17  lijunqing
class CSttAtsCmd : public CSttCmdBase, public CXObjectRefBase
{
public:
	CSttAtsCmd();
    CSttAtsCmd(const CString &strID);
    virtual ~CSttAtsCmd();

	static CXObjectRefBase* New()
	{
		return new CSttAtsCmd();
	}

	CString  m_strTestor;
//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTATSCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttAtsCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

	//2020-10-20  lijunqing
// private:
// 	CSttSocketDataBase *m_pRefSocketDataBase;
// 
// 	//˽�г�Ա�������ʷ���
// public:
// 	void SetRefSocketData(CSttSocketDataBase *pSocket)  {   m_pRefSocketDataBase = pSocket; }
// 	CSttSocketDataBase* GetRefSocketData()  {   return m_pRefSocketDataBase;    }

//���Ա������ʷ���
public:
};


//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttTestCmd.h  CSttTestCmd

#pragma once

#include "SttCmdDefineGlobal.h"

#include "SttCmdBase.h"

class CSttSocketDataBase;

class CSttTestCmd : public CSttCmdBase, public CXObjectRefBase
{
public:
	CSttTestCmd();
	virtual ~CSttTestCmd();

	static CXObjectRefBase* New()
	{
		return new CSttTestCmd();
	}

	CString  m_strTestor;
//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTTESTCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttTestCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

	//2020-10-20  lijunqing
/*
//˽�г�Ա����
private:
    CSttSocketDataBase *m_pRefSocketDataBase;

//˽�г�Ա�������ʷ���
public:
    void SetRefSocketData(CSttSocketDataBase *pSocket)  {   m_pRefSocketDataBase = pSocket; }
    CSttSocketDataBase* GetRefSocketData()  {   return m_pRefSocketDataBase;    }
*/

//���Ա������ʷ���
// public:
// 	void SetParameter(const CString &strMacroID, CDataGroup *pParas);
};


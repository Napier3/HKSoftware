//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAdjustCmd.h  CSttAdjustCmd

#pragma once

#include "SttCmdDefineGlobal.h"
#include "SttCmdBase.h"


class CSttAdjustCmd : public CSttCmdBase
{
public:
	CSttAdjustCmd();
	virtual ~CSttAdjustCmd();


	CString  m_strTestor;
	//���غ���
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTADJUSTCMD;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttAdjustCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//���Ա������ʷ���
// public:
// 	void SetParameter(const CString &strMacroID, CDataGroup *pParas);
};


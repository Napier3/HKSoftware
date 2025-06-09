//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PNTplElement.h  CPNTplElement

#pragma once

#include "PNTplMngrGlobal.h"


#include "PNTplEquation.h"
#include "PNTplGroup.h"
#include "PNTplText.h"

class CPNTplElement : public CExBaseList
{
public:
	CPNTplElement();
	virtual ~CPNTplElement();

	CString m_strElementData;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPNTPLELEMENT;   }
	virtual BSTR GetXmlElementKey()  {      return CPNTplMngrXmlRWKeys::CPNTplElementKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CPNTplEquation* FindEquation(const CString &strVarID);
	CPNTplEquation* FindEquationEx(const CString &strVarID);
	CPNTplGroup* FindGroupByValueID(const CString &strVarID);
	CPNTplEquation* FindEquationByValue(const CString &strValue);

	BOOL HasProtectionRelayParent();
	BOOL IsRepeatNode(const CString &strCurNodeName);//���ڲ���ģ���ظ���������<ReportBegin>���������������zhouhj
};


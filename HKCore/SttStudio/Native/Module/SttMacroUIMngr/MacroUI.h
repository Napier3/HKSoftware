//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//MacroUI.h  MacroUI

#pragma once

#include "SttTestMacroUIMngrGlobal.h"



class CMacroUI : public CExBaseObject
{
public:
	CMacroUI();
	virtual ~CMacroUI();


	CString  m_strUIType;
	CString  m_strFile;
	CString  m_strTemplateGen;
//���غ���
public:
	virtual UINT GetClassID() {    return UIMNGRCLASSID_MACROUI;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestMacroUIMngrXmlRWKeys::MacroUIKey();     }
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


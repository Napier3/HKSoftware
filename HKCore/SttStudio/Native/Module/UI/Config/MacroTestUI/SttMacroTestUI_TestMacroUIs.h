//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttMacroTestUI_TestMacroUIs.h  CSttMacroTestUI_TestMacroUIs

#pragma once

#include "SttTestCtrrlMacroTestUIMngrGlobal.h"


#include "SttMacroTestUI_TestMacroUI.h"

class CSttMacroTestUI_TestMacroUIs : public CExBaseList
{
public:
	CSttMacroTestUI_TestMacroUIs();
	virtual ~CSttMacroTestUI_TestMacroUIs();


//���غ���
public:
	virtual UINT GetClassID() {    return MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrrlMacroTestUIMngrXmlRWKeys::CSttMacroTestUI_TestMacroUIsKey();     }
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


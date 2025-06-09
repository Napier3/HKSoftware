//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttFrame_MacroParaView.h  CSttFrame_MacroParaView

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"


#include "SttFrame_Font.h"

class CSttFrame_MacroParaView : public CExBaseList
{
public:
	CSttFrame_MacroParaView();
	virtual ~CSttFrame_MacroParaView();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_MACROPARAVIEW;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_MacroParaViewKey();     }
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
	CSttFrame_Font *m_pFont;

//˽�г�Ա�������ʷ���
public:
	CSttFrame_Font* GetFont()	{	return m_pFont;	}
	void SetFont(CSttFrame_Font* pFont)	{	m_pFont = pFont;	}

//���Ա������ʷ���
public:
};


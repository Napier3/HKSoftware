//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttFrame_StatusBar.h  CSttFrame_StatusBar

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"


#include "SttFrame_Panal.h"

class CSttFrame_BarBase : public CExBaseList
{
public:
	CSttFrame_BarBase();
	virtual ~CSttFrame_BarBase();

	//ͼ���λ�ã���������(top)����(bottom)����(left)����(right)
	CString  m_strIconPos;

	long m_nWidth;//��С sf 20220105
	long m_nHeight;
//���غ���
public:
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
	CSttFrame_Panal *m_pPanal;

//˽�г�Ա�������ʷ���
public:
	CSttFrame_Panal* GetPanal()	{	return m_pPanal;	}
	void SetPanal(CSttFrame_Panal* pPanal)	{	m_pPanal = pPanal;	}

//���Ա������ʷ���
public:
	CSttFrame_Button* FindBtnByID(const CString &strBtnID);
	long GetBtnHeight();  //2023-2-26 lijunqing
};


class CSttFrame_ToolBar : public CSttFrame_BarBase
{
public:
	CSttFrame_ToolBar();
	virtual ~CSttFrame_ToolBar(){ };

public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_TOOLBAR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_ToolBarKey();     }

};


class CSttFrame_StatusBar : public CSttFrame_BarBase
{
public:
	CSttFrame_StatusBar();
	virtual ~CSttFrame_StatusBar(){	};

public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_STATUSBAR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_StatusBarKey();     }

};

class CSttFrame_ResultBar : public CSttFrame_BarBase
{
public:
	CSttFrame_ResultBar();
	virtual ~CSttFrame_ResultBar(){	};

public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_RESULTBAR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_ResultBarKey();     }

};


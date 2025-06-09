//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndMain.h  CUIWndMain

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowList.h"
#include "UIWndPage.h"
#include "UIWndPagesDef.h"

class CUIWndMain : public CUIWindowList
{
public:
	CUIWndMain();
	virtual ~CUIWndMain();

	static CString g_strMainPageFile;
	CString  m_strStartPage;
	long  m_nUseFrame;

//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDMAIN;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndMainKey();     }
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
	CUIWndPagesDef *m_pPagesDef;

	CUIWndPage   *m_pActivePage;//��ǰ�Ļҳ��
	CExBaseList  m_oUIHistoryPage;//��ʾ����ҳ���������,��������Ϊ����ʾ���Ⱥ�˳����ӵĽ���Page,���ƶ�ջ,�ȴ򿪵ĺ�ر�

//˽�г�Ա�������ʷ���
public:
	virtual BOOL Destroy();
	void Load(const CString &strMainPageFile);

	BOOL ClosePage(const CString &strPageID);
	BOOL ClosePage();
	BOOL ClosePage(CUIWndPage *pPage, BOOL bPostExitMsg=TRUE);
	BOOL ShowPage(const CString &strPageID,long nShow);
};


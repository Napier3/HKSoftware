#pragma once

#include "TempFuncGlobal.h "
#include "XTFFuncBase.h"
#include "XTFSceneBase.h"
#include "..\DataMngr\DvmAnalyse\DvmDataAnalyse.h"

// using namespace std;

//���� ��XTempFunctions�����ڶ�ȡ����ģ����������XML�ļ�
class CXTempFunctions : public CExBaseList, public CDvmAnalyseQueryInterface
{
public:
	CXTempFunctions();
	virtual ~CXTempFunctions();

//���غ���
public:
	virtual UINT GetClassID() {    return KTFCLASSID_CXTEMPFUNC;   }
	virtual BSTR GetXmlElementKey()  {      return CTempFuncXmlRWFuncs::CXTempFuncsTempF();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//˽�г�Ա����


private:
	long  m_nKeyTempCount;

public:
	void OpenTempFuncFile(const CString &strFileName, const CString &strPath);
	void OpenTempFuncFile(const CString &strFilePath);

	void InitFuncRefBuffer();

private:
	DWORD *m_pdwFuncRefBuffer;
	long  m_nFuncRefCount;

	void InitFuncRefBuffer(CExBaseList *pList, CExBaseList *pListDst);
	void FreeFuncRefBuffer();

public:
	virtual long QueryByKeys(CXKeyMatchRefList *pKeysList, CExBaseList &listTemplate);

	void SetCurrFilterScence(CXTFSceneBase *pCurrScence) {	m_pCurrFilterScence = pCurrScence;	}
	CXTFSceneBase *GetCurrFilterScence() {	return m_pCurrFilterScence; }
protected:
	CXTFSceneBase *m_pCurrFilterScence;		//��ǰ�������˽ڵ�
};
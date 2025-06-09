#pragma once

#include "GbWzdAiParasBase.h"

/*
Tool�����Ӷ���ΪPara�����Լ�Switch����
switch��������ִ�з��������µĸ�����֧��ִ��
*/

//////////////////////////////////////////////////////////////////////////
class CGbWzdAiTool : public CGbWzdAiParasBase
{
public:
	CGbWzdAiTool();
	virtual ~CGbWzdAiTool();

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiTool;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiKey ;	}

protected:
	CXKeyDB *m_pKeyDB;
	CDataGroup *m_pMacroParas;
	CDvmDevice *m_pDevice;
	CSttGuideBook *m_pSttGuideBook;

	//��չ�ؼ��֣����磺��ѹ�������ĸ�ѹ��󱸱��������ڹ����豸����ģ�͵Ķ�ֵ
	CXKeyMatchRefList m_listExtendXKeys;

	CXMatchList m_oParameterMatchList;  //����װ�ò����Ĺؼ��ֱ�
	CXMatchList m_oDvmMatchList;  //����ģ�����ݣ���ֵ���Ĺؼ��ֱ�
	CXMatchList m_oDvmMatchListFilter;  //����m_listExtendXKeys���˺�Ĺؼ��ֱ�
	CString m_strCurrAiFile;

public:
	void SetSttGuideBook(CSttGuideBook *pSttGuideBook)	{	m_pSttGuideBook = pSttGuideBook;	}
	void SetXKeyDB(CXKeyDB *pKeyDB);
	void SetDvmDevice(CDvmDevice *pDevice);
	void OpenGbWzdAiFile(const CString &strAiFile);
	void OpenGbWzdFileByMacroParaFile(const CString &strUIFile);
	void SetExtendKeys(const CString &strExtendKeys);
	void AddExtendKeys(const CString &strExtendKeys);
	void SetMacroParasByAI(CDataGroup *pMacroParas);
	void DvmFilterByExtendKeys();

	//�ܵĽӿ�
	BOOL GbWzdAi(const CString &strAiFile, CDataGroup *pMacroParas);

protected:
	void InitGbAiDataKey();
	void InitDvmMatchList(CDvmDataset *pDvmDataset);

	//�����Ҫ�ڶ��ֽ������ݴ���ģ�����switch/case
	//Para���󣬲����ش˺���������ֻ��switch/case����
	virtual DWORD ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};

extern CGbWzdAiTool *g_theGbWzdAiTool;

void Create_GbWzdAiTool();
void Release_GbWzdAiTool();

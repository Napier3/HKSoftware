#pragma once

#include "GbWzdAiParasBase.h"

/*
Tool对象，子对象为Para对象以及Switch对象
switch对象，用于执行符合条件下的各个分支的执行
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

	//扩展关键字，例如：变压器保护的高压侧后备保护，用于过滤设备数据模型的定值
	CXKeyMatchRefList m_listExtendXKeys;

	CXMatchList m_oParameterMatchList;  //所有装置参数的关键字表
	CXMatchList m_oDvmMatchList;  //所有模型数据（定值）的关键字表
	CXMatchList m_oDvmMatchListFilter;  //经过m_listExtendXKeys过滤后的关键字表
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

	//总的接口
	BOOL GbWzdAi(const CString &strAiFile, CDataGroup *pMacroParas);

protected:
	void InitGbAiDataKey();
	void InitDvmMatchList(CDvmDataset *pDvmDataset);

	//针对需要第二轮进行数据处理的，例如switch/case
	//Para对象，补重载此函数，所以只有switch/case处理
	virtual DWORD ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);

};

extern CGbWzdAiTool *g_theGbWzdAiTool;

void Create_GbWzdAiTool();
void Release_GbWzdAiTool();

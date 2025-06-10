#pragma once

#include "../GbSmartGenWzdGlobal.h"
#include "../../Module/KeyDb/XKeyDB.h"
#include "../../Module/KeyDb/XMatchList.h"
#include "../../Module/DataMngr/DvmDevice.h"
#include "../Module/SttCmd/GuideBook/SttGuideBook.h"

class CGbAiDataKey :public CExBaseObject
{
public:
	CGbAiDataKey(void);
	virtual ~CGbAiDataKey(void);

	CXKeyMatchRef *m_pKeyMatchRef;  //关键字关联的XKeyRref，用于匹配关键字
public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDATAKEY;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataKeyKey ;	}

	virtual CBaseObject* Clone();

public:
	//初始化接口
	void InitGbAiDataKey(CXKeyDB *pKeyDB);
	BOOL Match(CXMatchObject *pXMatchObj);
};


class CGbAiOptrInterface : public CExBaseList
{
public:
	CGbAiOptrInterface(void);
	virtual ~CGbAiOptrInterface(void);

	DWORD m_dwValue;

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook) = 0;
	virtual void InitGbAiDataKey(CXKeyDB *pKeyDB);
	virtual void InitMacroPara(CDataGroup *pMacroParas);
	virtual void ClearScptState();

	//针对需要第二轮进行数据处理的，例如switch/case
	virtual DWORD ScptCalEx(CXMatchList *pDvmMatchListFilter, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
};

//////////////////////////////////////////////////////////////////////////
class CGbAiOptrBase :public CGbAiOptrInterface
{
public:
	CGbAiOptrBase(void);
	virtual ~CGbAiOptrBase(void);

public:
	//Serialize mathods
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual UINT GetClassID()		{		return GBCLASSID_GbWzdAiDATASCPTOPTR;		}
	virtual BSTR GetXmlElementKey() {		return CGbSmartGenWzdXmlRWKeys::g_pGbSmartGenWzdKeys->m_strGbWzdAiDataOptrtKey ;	}

public:
	virtual DWORD ScptCal(CXMatchObject *pXMatchObj, BOOL bAllMatchMode, CSttGuideBook *pSttGuideBook);
	virtual void ClearScptState();

};

CDvmData* GbAiGetMacroPara(CExBaseObject *pGbAiObj);

//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdData.h  CSttCmdData

#pragma once

#include "SttCmdDefineGlobal.h"
#include "SttParas.h"
#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
#include "SttMacro.h"
#endif
#include "SttMsgs.h"

#ifndef STT_CMD_NOT_USE_IOT
#include "SttIotTopo.h"
#include "SttIotDevices.h"
#endif


class CSttCmdData : public CExBaseList
{
public:
	CSttCmdData();
	virtual ~CSttCmdData();

	//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTCMDBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttCmdDataKey();     }
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

	virtual void GetXml(CXmlRWKeys *pXmlRWKeys, CString &bstrXml,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual long GetXml(CXmlRWKeys *pXmlRWKeys, char **ppszRetBuffer, long nOffset=0,const long &nXmlRWType = _PUGI_XML_TYPE_);

	//2023-9-9
	virtual CSttParas* NewSttParas();
	//私有成员变量
protected:
	CSttParas *m_pSttParas;

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	CSttMacro *m_pSttMacro;
#endif

	CSttMsgs *m_pSttMsgs;

#ifndef STT_CMD_NOT_USE_IOT
	CSttIotTopo *m_pSttIotTopo;
	CSttIotDevices *m_pSttIotDevices;
#endif

	//私有成员变量访问方法
public:
	CSttParas* GetSttParas();
	BOOL HasSttParas();    //2023-3-12  lijunqing  为空命令的判断方法，用于Socket断开时等效close-device指令

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
	CSttMacro* GetSttMacro(BOOL bInitParas=FALSE, BOOL bInitResults=FALSE,BOOL bInitSearchResults = FALSE);//zhouhj 20210925 增加搜索点结果
	
	//2023-6-18  lijunqing
	BOOL HasSttMacro()	{	return m_pSttMacro != NULL;	} 
	CSttMacro*SttMacro()	{	return m_pSttMacro;	}
#endif
	
	CSttMsgs* GetSttMsgs();

#ifndef STT_CMD_NOT_USE_IOT
	CSttIotTopo* GetSttIotTopo();
	CSttIotDevices* GetSttIotDevices();
#endif
	void Free();

public:
	BOOL SetXml(char *pszBuffer, long nLen, wchar_t *pwszDestBuffer);

	BOOL GetParasDataValueByID(const char* strValueID, CString &strValue);
	BOOL GetParasDataValueByID(const char* strValueID, long &nValue);
	BOOL GetParasDataValueByID(const char* strValueID, int &nValue);
	BOOL GetParasDataValueByID(const char* strValueID, DWORD &nValue);
	BOOL GetParasDataValueByID(const CString &strValueID, CString &strValue);
	BOOL GetParasDataValueByID(const CString &strValueID, long &nValue);
	BOOL GetParasDataValueByID(const CString &strValueID, DWORD &nValue);
	long GetParaValue(const CString &strValueID, long nDefaultValue);
	CDvmData* AddNewParasData(const CString &strID, const CString &strValue);
	CDvmData* AddNewParasData(const CString &strID, long nValue);
	CDvmData* SetParasDataAttr(const CString &strID, const CString &strValue);
	CDvmData* SetParasDataAttr(const CString &strID, long nValue);
	void AppendParas(CSttCmdData &oSrcCmd);
	void AppendParas2(CExBaseList &oList, BOOL bClone=FALSE);
	void AppendMsgs(CExBaseList &oList);
	void AddNewParas(CExBaseList *pList);
	void RemoveMsgs();
	void DeleteParasDataByID(const CString &strValueID);
	CDvmData *FindParasDataByID(const CString &strValueID);
    CDvmDataset* GetDataset();
	CDvmDatasetGroup* GetDatasetGroup();

	//2021-8-4  lijunqing
	CExBaseObject *FindInParasByID(const CString &strID);

	//20210902
	BOOL SetParasDataValueByID(const CString &strValueID, const CString &strValue);

	//2023-2-2  lijunqing
	void AddMsg(const CString &strID, const CString &strMsg);
};


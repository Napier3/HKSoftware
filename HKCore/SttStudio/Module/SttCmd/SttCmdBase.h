//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdBase.h  CSttCmdBase

#pragma once

#include "SttCmdData.h"
#include "../../Module/SttGlobalDef.h"
#include "../SttSocket/SttCmdOverTimeMngr.h"
#include "../../../Module/BaseClass/XObjectRefBase.h"

#include "../CmmInterface/SttCmmInterface.h"

//测试程序的IDSoft:Ats,Test,Debug,Record,必须初始化
// #define STT_SOFT_ID_ATS			_T("ATS")
// #define STT_SOFT_ID_TEST			_T("TEST")
// #define STT_SOFT_ID_DEBUG		_T("DEBUG")
// #define STT_SOFT_ID_RECORD		_T("RECORD")
extern CString g_strIDSoft;

class CSttSocketDataBase;

class CSttCmdBase : public CSttCmdData
{
public:
	CSttCmdBase();
	virtual ~CSttCmdBase();

	CString m_strToSN;   //2021-8-22  lijunqing
	CString m_strFromSN;  //2021-8-22  lijunqing

	//long m_nFrameHead;		//帧头标识
	long m_nType_Cmd;		//命令类型
//     long m_nSrcID;		//源端标识
//     long m_nDestID;		//目标标识
	DWORD m_nIDTester;		//测试端标识
    long m_nPkgSendIndex;		//发送序号
	long m_nCompress;		//是否压缩
	long m_nDataLen;		//数据长度	

	long m_nMid;
	CString m_strTime;

    void Set_Xml_Pkg_With_Name(BOOL b)      {   m_bXml_Pkg_With_Name = b;   }
	long Get_Xml_Pkg_With_Name(){return m_bXml_Pkg_With_Name;}
protected:
    long m_bXml_Pkg_With_Name;
//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTCMDBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttCmdBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	bool m_bCreateMacroChild;

//私有成员变量访问方法
public:
	void SetCreateMacroChild(bool bCreateMacroChild)	{	m_bCreateMacroChild = bCreateMacroChild;	}

public:
	//2022-10-22  lijunqing  函数增加格式，没有采用缺省值，编译的时候会导致语法错误，从强制修改，实现代码的统一
	BOOL GetXml_Pkg(char **ppszBuffer, long &nLen, long nSttCmdDataFormat);
    BOOL ParsePkgHead(BYTE *pPkgBuffer);

	//2022-10-22 lijunqing 增加数据格式参数
    BOOL ParsePkgXml(BYTE *pPkgBuffer, long nLen, char *pwszDestBuffer, const long &nXmlRWType = _PUGI_XML_TYPE_);
    char* ParsePkgOnly(BYTE *pPkgBuffer);

    void ProducePkgHead(BYTE *pPkgBuffer);

	long GetCmdType();//这个函数其实是可以做成虚函数的
	DWORD GetIDTest();	

public:
	//pRetData!=NULL则返回应答结果
	long DoWait(CSttSocketDataBase_File *pSocket,STT_CMD_INFO *pCmdInfo,long nTimeOut = -1,CSttCmdData *pRetData=NULL,BOOL bDoEvents=TRUE);

//2020-10-20  lijunqing
private:
	//2021-7-21  lijunqing 暂时保留这个变量，后续去掉，采用统一的标准的接口
	CSttSocketDataBase *m_pRefSocketDataBase; 

	//2021-7-21  lijunqing 新的接口变量，后续使用这个接口
	void *m_pCmmOptrInterface;   //2022-10-19  lijunqing  由g改为void*

	//私有成员变量访问方法
public:
	//2021-7-21  lijunqing 暂时保留这个变量，后续去掉，采用统一的标准的接口
	void SetRefSocketData(CSttSocketDataBase *pSocket)  {   m_pRefSocketDataBase = pSocket; }
	CSttSocketDataBase* GetRefSocketData()  {   return m_pRefSocketDataBase;    }

	//2021-7-21  lijunqing 新的接口变量，后续使用这个接口
	void SetSttCmmOptrInterface(void *pCmmOptrInterface)  {   m_pCmmOptrInterface = pCmmOptrInterface; }
	void* GetSttCmmOptrInterface()  {   return m_pCmmOptrInterface;    }

public:
	void PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer,const CString &strFormat=MQTT_DATA_FORMAT_XML);
	void PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer, UINT nFormatType=_PUGI_XML_TYPE_);

	virtual void SetParameter(const CString &strMacroID, CDataGroup *pParas);
};


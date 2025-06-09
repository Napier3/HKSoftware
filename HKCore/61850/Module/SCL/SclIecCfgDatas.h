#pragma once

#include "../../../Module/DataMngr/DvmDevice.h"
#include "../CfgDataMngr/IecCfgDataMngrGlobal.h"
// extern BOOL g_pIedFile_Abstract;

#define SCLIECCLASSID_BASECLASS   (CLASSID_BASECLASS   + 0X00910000)
#define SCLIECCLASSID_LISTCLASS   (CLASSID_EXLISTCLASS + 0X00910000)

#define SCLIECCLASSID_IED            (SCLIECCLASSID_LISTCLASS+1)

#define SCLIECCLASSID_CTRLS_SMV_OUT  (SCLIECCLASSID_LISTCLASS+2)
#define SCLIECCLASSID_CTRLS_SMV_IN   (SCLIECCLASSID_LISTCLASS+3)
#define SCLIECCLASSID_CTRLS_GS_OUT   (SCLIECCLASSID_LISTCLASS+4)
#define SCLIECCLASSID_CTRLS_GS_IN    (SCLIECCLASSID_LISTCLASS+5)

#define SCLIECCLASSID_CTRL_SMV_OUT   (SCLIECCLASSID_LISTCLASS+6)
#define SCLIECCLASSID_CTRL_SMV_IN    (SCLIECCLASSID_LISTCLASS+7)
#define SCLIECCLASSID_CTRL_GS_OUT    (SCLIECCLASSID_LISTCLASS+8)
#define SCLIECCLASSID_CTRL_GS_IN     (SCLIECCLASSID_LISTCLASS+9)

#define SCLIECCLASSID_CH_SMV_OUT     (SCLIECCLASSID_BASECLASS+10)
#define SCLIECCLASSID_CH_SMV_IN      (SCLIECCLASSID_BASECLASS+11)
#define SCLIECCLASSID_CH_GS_OUT      (SCLIECCLASSID_BASECLASS+12)
#define SCLIECCLASSID_CH_GS_IN       (SCLIECCLASSID_BASECLASS+13)

#define SCLIECCLASSID_STATION  (SCLIECCLASSID_BASECLASS+14)

#define SCLIECCLASSID_CTRL_GS    (SCLIECCLASSID_LISTCLASS+15)
#define SCLIECCLASSID_CTRL_SMV    (SCLIECCLASSID_LISTCLASS+16)

#define WM_SCLIECCFGCTRLS_SELECTED  (WM_USER+1419)
#define WM_SCLIECIED_SELECTED       (WM_USER+1420)
#define WM_SCLIECCFGCTRL_SELECTED   (WM_USER+1421)//zhouhj 20211027  �������ƿ鱻ѡ��

#define DEVICE_type    _T("type")
#define  DEVICE_manufacturer  _T("manufacturer")
#define DEVICE_desc _T("desc")
#define STATION_FILE_POSTFIX  _T("tscd")

#define IedTypeIndex_ProtMeas   0
#define IedTypeIndex_Meas       1
#define IedTypeIndex_Prot       2
#define IedTypeIndex_RPITMU     3
#define IedTypeIndex_RPIT       4
#define IedTypeIndex_MU         5
#define IedTypeIndex_SCD        6
#define IedTypeIndex_NETGAT     7
#define IedTypeIndex_PROTINFO   8
#define IedTypeIndex_Other      9
#define IedTypeIndex_MAX        10

#define SCL_IECFG_CTRL_TYPE_GS_SUB                       0x0001
#define SCL_IECFG_CTRL_TYPE_GS_PUB                       0x0002
#define SCL_IECFG_CTRL_TYPE_SMV                          0x0004//SMV����
#define SCL_IECFG_CTRL_TYPE_SMVSUB                       0x0008// 20220802 zhouhj ��������SMV����


//////////////////////////////////////////////////////////ͨ����Ϣ////////////////////////////////////////////////////////////////////////////////////////////////
//����������ͨ�����ݣ�����OUTͨ����������fcda_*****���ݣ�����INͨ�����򶼱����Ӧ��OUTͨ��
class CSclChBase  : public CExBaseObject
{
public:
	CSclChBase();
	virtual ~CSclChBase();

	//�������ݶ�������ָ��
	//SCLͨ��֮������ù�ϵ����Ҫ���GsIn��SvInͨ��
	CExBaseObject *m_pCfgDataRef;    


public:
	CString fcda_lndesc;
	CString fcda_dodesc;
	CString fcda_desc;
	CString fcda_name;

// 	CString inLNDesc;
// 	CString inDODesc;
// 	CString inDADesc;

public:
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CString* GetName();
};

class CSclChSmv  : public CSclChBase
{
public:
	CSclChSmv();
	virtual ~CSclChSmv();

public:
// 	CString fcda_lndesc;
// 	CString fcda_dodesc;
// 	CString fcda_desc;
// 	CString fcda_name;
	CString fcda_DOType;
	CString fcda_cdc;

public:
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);

};

class CSclChSmvOut : public CSclChSmv
{
public:
	CSclChSmvOut();
	virtual ~CSclChSmvOut();

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CH_SMV_OUT;	}

public:
// 	CString fcda_lndesc;
// 	CString fcda_dodesc;
// 	CString fcda_desc;
// 	CString fcda_name;
	CExBaseList m_oChInRefs;


	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclSvOutChKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};


class CSclChSmvIn : public CSclChSmv
{
public:
	CSclChSmvIn();
	virtual ~CSclChSmvIn();

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CH_SMV_IN;	}

public:

	CString inLNDesc;
	CString inDODesc;
	CString inDADesc;
	long    inIndex;
	long    outIndex;
	CString inPath;

	CString inputRef_cdc;
	CString inputRef_DOType;

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclSvInChKey();    }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual CString* GetName();

};

class CSclChGs  : public CSclChBase
{
public:
	CSclChGs();
	virtual ~CSclChGs();

public:
// 	CString fcda_lndesc;
// 	CString fcda_dodesc;
// 	CString fcda_desc;
// 	CString fcda_name;
	CString fcda_type;

public:
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);

};

class CSclChGsOut  : public CSclChGs
{
public:
	CSclChGsOut();
	virtual ~CSclChGsOut();

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CH_GS_OUT;	}

public:
// 	CString fcda_lndesc;
// 	CString fcda_dodesc;
// 	CString fcda_desc;
// 	CString fcda_type;
// 	CString fcda_name;
	CExBaseList m_oChInRefs;

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclGsOutChKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	CStringArray m_astrGinChs;  //zhouhj  ���ڴ洢ȫ���������ⲿ�����
	CString m_strGinPath;   //���ڴ洢���һ���ҵ��Ĺ����ⲿ�����
};

class CSclChGsIn : public CSclChGs
{
public:
	CSclChGsIn();
	virtual ~CSclChGsIn();

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CH_GS_IN;	}

public:
// 	CString fcda_type;
// 	CString fcda_lndesc;
// 	CString fcda_dodesc;
// 	CString fcda_desc;
// 	CString fcda_name;		

	CString fcda_map;
	long    outIndex;
	CString inLNDesc;
	CString inDODesc;
	CString inDADesc;
	long    inIndex;
	CString inPath;

	CString inputRef_type;

	CString GetFcdaDesc() {return fcda_desc;}


	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclGsInChKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};

/////////////////////////////////////////////////////////////////////SV��GOOSE��Ϣ////////////////////////////////////////////////////////////////////////////////////////////////////
class CSclCtrlBase : public CExBaseList
{
public:
	CSclCtrlBase();
	virtual ~CSclCtrlBase();

	long    m_nSelect;
	CString ldName;
	CString lnName;
	CString m_strDataSet;
	CString m_strDataSetPath;
	CString m_strDataSetDesc;
	CString apName;
	CString m_strMac;
	long m_nChnCount;
	long m_nFiberIndex;//20221220 zhouhj �������ڼ�¼��ں�

	CString m_strLDdesc;
	DWORD m_dwAppID;//zhouhj 20221218 Smv��GOOSE����,ͳһ�Ƶ��˴�

	CExBaseObject *m_pCfgDataRef;
	BOOL m_bSaveCBChs;//�洢xml�ļ�ʱ,�Ƿ񱣴�ͨ������

public:
	virtual CSclChBase* CreateNewCh() = 0;
	virtual CString GetInIedString()	{	return _T("");	}
	virtual CString GetInIedExtName()	{	return _T("");	}
	virtual CString GetIedString();
	virtual CString ldname_own()     {	return ldName;	}
	virtual CString lnname_own()     {	return lnName;	}
	virtual CString apname_own()     {	return apName;	}
	virtual CString iedname_own()    {	return _T("");	}


	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual DWORD GetAppID() {return 0;}

public:
	CSclChBase* FindBy_fcda_name(const CString &fcda_name);
	void SetSaveCBChs(BOOL bSaveChs);//���ñ���xml�ļ�ʱ�Ƿ񱣴�����ƿ��ͨ����Ϣ

};

class CSclCtrlSmv : public CSclCtrlBase
{
public:
	CSclCtrlSmv();
	virtual ~CSclCtrlSmv();


public:
	long scl_svcb_smpRate;
	CString m_strSVID;
	long scl_svcb_nofASDU;
	long scl_svcb_confRev;
//	DWORD m_dwAppID;
	DWORD scl_smv_VLANID;
	DWORD scl_smv_VLANPRI;

	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRL_SMV;	}
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	//virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual DWORD GetAppID() {return m_dwAppID;}

};

class CSclCtrlSmvOut : public CSclCtrlSmv
{
public:
	CSclCtrlSmvOut();
	virtual ~CSclCtrlSmvOut();

	BOOL m_bInitChInRefs;

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRL_SMV_OUT;	}
public:
	virtual CSclChBase* CreateNewCh() 	{	return (CSclChBase*)AddNewChild(new CSclChSmvOut);	}

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlSvOutKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);


	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};

class CSclCtrlSmvIn : public CSclCtrlSmv
{
public:
	CSclCtrlSmvIn();
	virtual ~CSclCtrlSmvIn();

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRL_SMV_IN;	}
public:
	virtual CSclChBase* CreateNewCh()	{	return (CSclChBase*)AddNewChild(new CSclChSmvIn);	}
	virtual CString GetInIedString()	{	return iedStr;	}
	virtual CString GetInIedExtName()	{	return iedExtName;	}

public:
	CString iedStr;
	CString iedExtName;

	CString ldName_own;
	CString lnName_own;
	CString scl_datset_own;
	CString apName_own;
	long m_nChnRefCount;

	CString m_strExLDdesc;
	CString m_strExIedDesc;//���Ϳ��ƿ��IED��Desc��Ϣ 20230509 zhouhj

	virtual CString ldname_own()     {	return ldName_own;	}
	virtual CString lnname_own()     {	return lnName_own;	}
	virtual CString apname_own()     {	return apName_own;	}
	virtual CString iedname_own()    {	return _T("");	}

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlSvInKey();     }

	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);


	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};

class CSclCtrlGs : public CSclCtrlBase
{
public:
	CSclCtrlGs();
	virtual ~CSclCtrlGs();


public:
	CString gocbref;
	CString m_strgocbRef;
	long m_dwVersion;
	CString m_strGooseId;
	DWORD m_dwVLandID;
	long m_dwVLandPriority;
	long scl_gse_MinTime;
	long scl_gse_MaxTime;

	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRL_GS;	}
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlGsKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual DWORD GetAppID() {return m_dwAppID;}

};

class CSclCtrlGsIn : public CSclCtrlGs
{
public:
	CSclCtrlGsIn();
	virtual ~CSclCtrlGsIn();

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRL_GS_IN;	}
public:
	virtual CSclChBase* CreateNewCh()	{	return (CSclChBase*)AddNewChild(new CSclChGsIn);	}
	virtual CString GetInIedString()	{	return m_strIedDesc;	}
	virtual CString GetInIedExtName()	{	return m_strIedID;	}

public:
	CString m_strIedDesc;
	CString m_strIedID;
	long m_nChnRefCount;

	CString ldName_own;
	CString lnName_own;
	CString scl_datset_own;
	CString apName_own;

	CString m_strExLDdesc;
	CString m_strExIedDesc;//���Ϳ��ƿ��IED��Desc��Ϣ 20230509 zhouhj

	virtual CString ldname_own()     {	return ldName_own;	}
	virtual CString lnname_own()     {	return lnName_own;	}
	virtual CString apname_own()     {	return apName_own;	}
	virtual CString iedname_own()    {	return _T("");	}

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlGsInKey();     }

	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	CSclChGsIn* FindByInPath(const CString &strPath);
};


class CSclCtrlGsOut : public CSclCtrlGs
{
public:
	CSclCtrlGsOut();
	virtual ~CSclCtrlGsOut();
	BOOL m_bInitChInRefs;

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRL_GS_OUT;	}
public:
	virtual CSclChBase* CreateNewCh()	{	return (CSclChBase*)AddNewChild(new CSclChGsOut);	}

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlGsOutKey();     }

	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);	
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);


	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};

class CSclCtrls : public CExBaseList
{
public:
	CSclCtrls();
	virtual ~CSclCtrls();

protected:
	BOOL m_bRead;

public:
	BOOL IsRead();
	void SetRead();
	void SetNoRead();

	virtual CSclCtrlBase* CreateCtrl();
	virtual BOOL IsExist(const CString &iedName, const CString &ldName, const CString &lnName, const CString &scl_datSet);
	virtual void GetAllSelectedDatas(CExBaseList &oList);

	virtual long GetCurSelCB_Num();
	virtual BOOL SetSelectNum(long nNum);
	void SetAllItemData(DWORD dwValue);
	void SetSelectAll(BOOL bSelected);
	BOOL IsAllSelected();
	void SetSaveCBChs(BOOL bSaveChs);//���ñ���xml�ļ�ʱ�Ƿ񱣴�����ƿ��ͨ����Ϣ
};

class CSclCtrlsSmvOut : public CSclCtrls
{
public:
	CSclCtrlsSmvOut();
	virtual ~CSclCtrlsSmvOut();

	CSclCtrlSmvOut* FindCrl_SmvOutput(const CString &strSvID);
	CSclCtrlBase* FindSclCtrlByAppID(DWORD dwAppID);
	CSclCtrlBase* FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac = _T(""));

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRLS_SMV_OUT;	}
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlsSvOutKey()  ;   }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};

class CSclCtrlsSmvIn : public CSclCtrls
{
public:
	CSclCtrlsSmvIn();
	virtual ~CSclCtrlsSmvIn();

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRLS_SMV_IN;	}
	virtual BOOL IsExist(const CString &iedName, const CString &ldName, const CString &lnName, const CString &scl_datSet);

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlsSvInKey()  ;   }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);  

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	void GetAllChs(CExBaseList &listChs);
	CSclCtrlBase* FindSclCtrlByAppID(DWORD dwAppID); 
	CSclCtrlBase* FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac = _T("")); 
	CSclCtrlBase* FindSclCtrlBySvID_DesMac(const CString &strSVID,const CString &strDesMac); 


protected:
	void AddCh(CExBaseList &listChs, CSclChSmvIn *pCh);

};

class CSclCtrlsGsIn : public CSclCtrls
{
public:
	CSclCtrlsGsIn();
	virtual ~CSclCtrlsGsIn();


public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRLS_GS_IN;	}
	virtual BOOL IsExist(const CString &iedName, const CString &ldName, const CString &lnName, const CString &scl_datSet);

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlsGsInKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	///*virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	*/


	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	CSclCtrlGsIn* FindByGsID(const CString &strGsID);

	void GetAllChs(CExBaseList &listChs);
	CSclCtrlBase* FindSclCtrlByAppID(DWORD dwAppID); 
	CSclCtrlBase* FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac = _T(""));
	CSclCtrlBase* FindSclCtrlByAppID_DesMac(DWORD dwAppID,const CString &strDesMac = _T(""));

	CSclCtrlBase* FindSclCtrlByGoID_DesMac(const CString &strGooseID,const CString &strDesMac); 

protected:
	void AddCh(CExBaseList &listChs, CSclChGsIn *pCh);
};

class CSclCtrlsGsOut : public CSclCtrls
{
public:
	CSclCtrlsGsOut();
	virtual ~CSclCtrlsGsOut();

	CSclCtrlGsOut*  FindCrl_GooseOutput(const CString &strGsID);
	CSclCtrlGsOut*  FindCrlByGooseRefPath_GooseOutput(const CString &strgocbRef);

public:
	virtual UINT GetClassID()	{	return SCLIECCLASSID_CTRLS_GS_OUT;	}

	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclCtrlsGsOutKey();     }
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	CSclCtrlBase* FindSclCtrlByAppID(DWORD dwAppID);
	CSclCtrlBase* FindSclCtrlByAppID_DesMac(const CString &strAppID,const CString &strDesMac = _T(""));
	CSclCtrlBase* FindSclCtrlByAppID_DesMac(DWORD dwAppID,const CString &strDesMac = _T(""));
	void AddGsOut_NoRepeat(CSclCtrlsGsOut *pSclCtrlsGsOut);
};

///////////////////////////////////////////////����IED�ļ���Ϣ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSclIed : public CExBaseList
{
public:
	CSclIed();
	virtual ~CSclIed();

	CDvmDevice *m_pDvmDevice;
	LPVOID m_pRefItemData;//����SCD���������Ϣ��ָ��

	CString m_strIP;
	CString m_strIP_SUBNET;
	CString m_strIP_GATEWAY;

	CString m_strManufacturer;
	CString m_strIedType;
	CString m_strIedTypeLabel;
	CString m_strModel;
	CString m_strDvmFilePath;   //��¼���ɵ�ģ���ļ���·��

	BOOL LDTYPE_PROT;
	BOOL LDTYPE_MEAS;
	BOOL LDTYPE_CTRL;
	BOOL LDTYPE_RPIT;
	BOOL LDTYPE_MU;

	long m_nSelected;//�������ڽ�IED��ʾ�������ʱ,�ж��Ƿ�ѡ��

	void SetLDType(char* pLDType);
	void SetIedType();
	void SetSaveCBChs(BOOL bSaveChs);//���ñ���xml�ļ�ʱ�Ƿ񱣴�����ƿ��ͨ����Ϣ

public:
	void DeleteCtrls(CExBaseList *pCtrls);
	CSclCtrls* GetFirstCtrlObj();

	CSclCtrlGsOut*  FindCrl_GooseOutput(const CString &strGsID);
	CSclCtrlSmvOut* FindCrl_SmvOutput(const CString &strSvID);
	CSclCtrlBase* FindCtrl_GsOutSmvOut(DWORD dwAppID,BOOL bSmv);//20221218 ͨ��AppID���Ҷ�Ӧ��Smv��Goose�Ŀ��ƿ�
	BOOL IsAllCtrlsSelected();
	void ClearAll();//���ȫ��

protected:
	CSclCtrlsSmvOut *m_pSmvOuts;
	CSclCtrlsSmvIn  *m_pSmvins;
	CSclCtrlsGsOut  *m_pGsOuts;
	CSclCtrlsGsIn   *m_pGsIns;

public:
	CSclCtrlsSmvOut* GetSmvOuts();
	CSclCtrlsSmvIn*  GetSmvIns();
	CSclCtrlsGsOut*  GetGsOuts();
	CSclCtrlsGsIn*   GetGsIns();
	CDvmDevice*      GetDvmDevice();


	BOOL HasSmvOuts()		{	return m_pSmvOuts != NULL;	}
	BOOL HasSmvIns()		{	return m_pSmvins != NULL;	}
	BOOL HasGsOuts()		{	return m_pGsOuts != NULL;	}
	BOOL HasGsIns()			{	return m_pGsIns != NULL;	}

	CString  test_men;
	CString model_test;
	CString vcnln_test;
	CString  macro_test;

public:
	void SaveIedFile();
	void SaveIedFile(const CString &strSavePath);//��չ��Ϊ"*.xml"
	void SaveIedFile2(const CString &strFile);
	void SaveSiedFile(const CString &strSavePath);//��չ��Ϊ"*.sied"

	virtual UINT GetClassID()	{	return SCLIECCLASSID_IED;	}
	virtual BSTR GetXmlElementKey(){return CCfgDataMngrXmlRWKeys::CSclIedKey();} 
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void InitAfterRead();
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	void InitDatasetPath();//zhouhj 20180628  TSCD�����󲿷����ݲ��������ڴ˴����丳ֵ
	CString GetSCDFilePath();//�ܺ�� 2020611

	BOOL IsIed_RPIT_MU();
	BOOL IsIed_MU();
	BOOL IsIed_RPIT();
	BOOL IsIed_Prot_Meas();
	BOOL IsIed_Prot();
	BOOL IsIed_Meas();
public:
	static const CString g_astrIedType[IedTypeIndex_MAX];
	static const CString g_astrIedTypeDesc[IedTypeIndex_MAX];

	static CString GetIedTypeDesc(const CString &strIedType);
	static BOOL IsProtNetGate(const CString &strType);
};




/////////////////////////////////////////////////��������Ϣ///////////////////////////////////////////////////////////////////////////////////////////
class CSclIedRef : public CExBaseObject
{
public:
	CSclIedRef();
	virtual ~CSclIedRef();
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CSCLIEDREF  ; }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclIedRefKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
};

class CSclBayVLevel : public CExBaseList
{
public:
	CSclBayVLevel ();
	virtual ~CSclBayVLevel();
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CSCLBAYVLEVEL;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclBayVLevelKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};

class CSclBay : public CExBaseList
{
public:
	CSclBay();
	virtual ~CSclBay();
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CSCLBAY;   }
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclBayKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};
///////////////////////////////////////////��վ�ļ�/////////////////////////////////////////////////////////////////////////////////


class CSclStation : public CExBaseList
{
public:
	CSclStation();
	virtual ~CSclStation();

	BOOL IsDatasReadFinish(CExBaseList *pDatas);

	CSclCtrlGsOut* FindGooseOutput(const CString &strIedName, const CString &strGsID);
	CSclCtrlGsOut* FindGooseOutput(const CString &strIedName, const CString &strGsID ,const CString &strGocbRef);//zhouhj 20190115 �й����Ժ ���ֳ���scd�в��ҳ��������(��Ҫ�����ж�����)
	CSclCtrlSmvOut* FindSmvOutput(const CString &strIedName, const CString &strSmvID);

	CSclCtrlSmvOut* FindSmvInput(CSclCtrlSmvOut *pSclCtrlSmvOut);
	CSclCtrlGsOut* FindGsInput(CSclCtrlGsOut *pSclCtrlGsOut);

	CSclCtrlGsOut*  FindCrl_GooseOutput(const CString &strIedName, const CString &strGsID);
	CSclCtrlSmvOut* FindCrl_SmvOutput(const CString &strIedName, const CString &strSvID);
	CSclCtrlGsOut*  FindCrl_GooseOutput(const CString &strGsID);
	CSclCtrlSmvOut* FindCrl_SmvOutput(const CString &strSvID);

	CSclCtrlBase* FindCtrl_GsOutSmvOut(DWORD dwAppID,BOOL bSmv);//20221218 ͨ��AppID���Ҷ�Ӧ��Smv��Goose�Ŀ��ƿ�

	CSclCtrlGsOut*  FindCrlByGooseRefPath_GooseOutput(const CString &strIedName, const CString &strgocbRef);

	void FindGSSVControl(CSclIed *pIed, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut);
	void FindGSSVControl(CSclCtrls *pCtrls);
	BOOL FindGSSVControl(CExBaseList *pList);

	void GetAll92Ref(CSclCtrlsSmvIn *pSMV92List);
	void GetAll92Ref(CSclCtrlsSmvOut *pSMV92List);
	void GetAllGinRef(CSclCtrlsGsIn *pGinList);
	void GetAllGoutRef(CSclCtrlsGsOut *pGoutList);
	void AddIedsByGinParas(CExBaseList *pIedListRef,const CString &strMac,DWORD dwAppID);

	void InitGoutCh_VirtualTerminals();//  zhouhongjun   20200622
	CSclChGsOut* FindGoutCh(const CString &strFCDA_Path);

	void SetScdFile(const CString &strScdFile)	{	m_strScdFile = strScdFile;	}
	CString GetScdFile()						{	return m_strScdFile;		}

public:
	CString m_strScdFile;	
	CString m_strTscdFile;

public:

	virtual UINT GetClassID()	{	return SCLIECCLASSID_STATION;	}
	virtual BSTR GetXmlElementKey()  {      return CCfgDataMngrXmlRWKeys::CSclStationKey();     }

	BOOL OpenSclStationFile(const CString &strFile);
	BOOL OpenSiedFile(CSclIed *pSclIed);
#ifdef USE_WAITINGTIMEDLG_FOR_SCLCOMPARECHECK
	void OpenSclFileByThr(const CString &strFile);
	static UINT OpenSclFileThread(LPVOID pParam);
#endif

	BOOL SaveIedFiles();
	BOOL SaveIedFiles(const CString &strSavePath);
	BOOL SaveAbstractFile();
	BOOL SaveAbstractFile(const CString &strSavePath);
	BOOL SaveStationFile();
	BOOL SaveSsclFiles(const CString &strSaveSsclFilePath);//����"*.sscl"�ļ�,�Լ���IED��Ӧ��"*.sied"�ļ�

	CSclIed * GetRefIed(const char  *strIedName);//����һ��IED���Ʒ��ظ�IED
	CSclIed* GetSelectedIed();   //��ȡѡ���IED

	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void InitAfterRead();
//��ʼ���������ö���
public:
	void InitSvGsIns();

private:
	void InitGsIns(CSclCtrlsGsIn *pSclCtrlsGsIn);
	void InitSvIns(CSclCtrlsSmvIn *pSclCtrlsSmvIn);
	void InitGsIn(CSclCtrlGsIn *pSclCtrlGsIn);
	void InitSvIn(CSclCtrlSmvIn *pSclCtrlSmvIn);
	void SetSaveCBChs(BOOL bSaveChs);//���ñ���xml�ļ�ʱ�Ƿ񱣴�����ƿ��ͨ����Ϣ
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



CSclIed* scl_GetIed(CExBaseObject *p);
BOOL   scl_IsGsOutCh(CExBaseObject *p);
BOOL   scl_IsGsInCh(CExBaseObject *p);
BOOL   scl_IsSmvOutCh(CExBaseObject *p);
BOOL   scl_IsSmvInCh(CExBaseObject *p);

BOOL   scl_IsGsOuts(CExBaseObject *p);
BOOL   scl_IsGsIns(CExBaseObject *p);
BOOL   scl_IsSmvOuts(CExBaseObject *p);
BOOL   scl_IsSmvIns(CExBaseObject *p);

void scl_SetMac(unsigned char *pDest, unsigned char *pSrc);
void scl_SetMac(CString &strMacDest, unsigned char *pSrc);

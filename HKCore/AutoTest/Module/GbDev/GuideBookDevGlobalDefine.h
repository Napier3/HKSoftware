#pragma once

// #include "../../../Module/FileMngr/FileMngrXMLKeys.h"
#include "GbDevXMLKeys.h"
#include "../GuideBook/GuideBookDefine.h"

#include "../Characteristic/CharacteristicGlobal.h"
#include "../../../Module/API/FileApi.h"

//���οؼ��Ҽ��˵����Ӷ���optrbar��ť��ID
#define ID_NEW_DEVICE					1000
#define ID_NEW_ITEMS						1001
#define ID_NEW_SAFETY					1002
#define ID_NEW_CPU							1003
#define ID_NEW_MACROTEST		1004				//�½���������Ŀ
#define ID_NEW_COMMCMD			1005
#define ID_NEW_SYSPARAEDIT		1006
#define ID_NEW_MSG							1007
#define ID_NEW_SET							1008
#define ID_NEW_ANALOG					1009
#define ID_NEW_SOFTSWITCH		1010
#define ID_NEW_SOE							1011
#define ID_NEW_BINARY					1012 
#define ID_NEW_CTRLWORD			1013
#define ID_NEW_BINARYIN				1014
#define ID_NEW_BINARYOUT			1015
#define ID_NEW_SYSPARA				1016
#define ID_NEW_CHAR			1017
#define ID_NEW_DATAOBJ			1018
#define ID_NEW_MACROCHARTEST			1019
#define ID_NEW_HDRESREQ			1020

const CString g_strSeparator = _T("Separator");

#define ID_BASE_MENU_COPY		2000
#define ID_BASE_MENU_PASTE		2001
#define ID_BASE_MENU_DELETE	2002
#define ID_BASE_MENU_IMPORT	2003
#define ID_BASE_MENU_EXPORT	2004


#define ID_BASE_MENU_MOVE_UP 2200
#define ID_BASE_MENU_MOVE_DOWN 2201

#define  WM_LIST_CHANGE_POSITION WM_USER + 7710

#define ID_BASE_MENU_SEPARATOR		-1

//����ScriptDialog������Grid����
#define  GRIDANALOGS			0x00000001
#define  GRIDSETS				0x00000002
#define  GRIDSOES				0x00000004
#define  GRIDSOFTSWITCHS		0x00000008
#define  GRIDMACROFAULTPARAS	0x00000010
#define  GRIDMACRORESULTS		0x00000020
#define  GRIDSAFETYDATAS		0x00000040
#define  GRIDSYSPARAS			0x00000080
#define  GRIDTESTPARAS			0x00000100
#define  GRIDMACROSYSPARAS		0x00000200
#define  GRIDCOMMCMD			0x00000400
#define  GRIDSAFETYRESULTDATAS	0x00000800
//����ScriptDialog����
#define  SAFETYRESULTDLG			 0
#define  SAFETYINITDLG				1
#define  MACROTESTPARADLG			2
#define  MACROTESTRESULTDLG			3
#define  COMCMDMACROTESTRESULTDLG	4
#define  COMCMDRESULTDLG			5


static const CString g_strGbDevItemFileMngrXMLFile = _T("GbDevItemFileMngr.xml");
static const CString g_strGbDevItemFileMngr = _T("GbDevItemFileMngr");
static const CString g_strGbDevItemSavePath = _T("GbDev");

static const CString g_strGuideBookMngrXMLFile = _T("GbFileMngr.xml");
static const CString g_strGuideBookMngr = _T("GbFileMngr");
static const CString g_strTCtrlCntrTemplate = _T("Template");
static const CString g_strTemplateType = _T("����ģ��");

static const CString g_strGbNodeConfigXMLFile = _T("GbNodeConfig.xml");
    
//���뵼��ģ���õ��ĸ�����ͬ�����ļ���׺����
static const CString g_strDevicePostfix = _T("dvc");
static const CString g_strDeviceType = _T("�豸");
// static const CString g_strDeviceRemark = _T("�豸(*.dvc)");																		//Remark��ʾ�������е�����˵������

static const CString g_strJobGuidePostfix = _T("jbg");
static const CString g_strJobGuideType = _T("��ҵָ��");
// static const CString g_strJobGuideRemark = _T("��ҵָ��(*.jbg)");																		//Remark��ʾ�������е�����˵������

static const CString g_strItemsPostfix = _T("itms");
static const CString g_strItemsType = _T("������Ŀ����");
// static const CString g_strItemsRemark = _T("������Ŀ����(*.itms)");																		//Remark��ʾ�������е�����˵������

static const CString g_strSafetyPostfix = _T("sfty");
static const CString g_strSafetyType = _T("��ȫ��ʩ");
// static const CString g_strSafetyRemark = _T("��ȫ��ʩ(*.sfty)");

static const CString g_strMacroTestPostfix = _T("mtst");
static const CString g_strMacroTestType = _T("��������Ŀ");
// static const CString g_strMacroTestRemark = _T("��������Ŀ(*.mtst)"); 

static const CString g_strMacroCharTestPostfix = _T("mctst");
static const CString g_strMacroCharTestType = _T("�߽����");
// static const CString g_strMacroCharTestRemark = _T("�߽����(*.mctst)"); 

static const CString g_strCommCmdPostfix = _T("cmcd");
static const CString g_strCommCmdType = _T("ͨѶ����");
// static const CString g_strCommCmdRemark = _T("ͨѶ����(*.cmcd)");

static const CString g_strSysParaEditPostfix = _T("spdt");
static const CString g_strSysParaEditType = _T("ϵͳ�����༭");
// static const CString g_strSysParaEditRemark = _T("ϵͳ�����༭(*.spdt)");

static const CString g_strAnalogsPostfix = _T("anlg");
static const CString g_strAnalogsType = _T("ģ��������");
// static const CString g_strAnalogsRemark = _T("ģ��������(*.anlg)");

static const CString g_strSetsPostfix = _T("sets");
static const CString g_strSetsType = _T("����ֵ����");
// static const CString g_strSetsRemark = _T("����ֵ����(*.sets)");

static const CString g_strCtrlWordsPostfix = _T("ctrl");
static const CString g_strCtrlWordsType = _T("�����ּ���");
// static const CString g_strCtrlWordsRemark = _T("�����ּ���(*.ctrl)");

static const CString g_strSoftSwitchsPostfix = _T("stsw");
static const CString g_strSoftSwitchsType = _T("��ѹ�弯��");
// static const CString g_strSoftSwitchsRemark = _T("��ѹ�弯��(*.stsw)");

static const CString g_strBinaryInsPostfix = _T("bnis");
static const CString g_strBinaryInsType = _T("����������");
// static const CString g_strBinaryInsRemark = _T("����������(*.bnis)");

static const CString g_strBinaryOutsPostfix = _T("bnos");
static const CString g_strBinaryOutsType = _T("����������");
// static const CString g_strBinaryOutsRemark = _T("����������(*.bnos)");

static const CString g_strSoesPostfix = _T("soes");
static const CString g_strSoesType = _T("SOE����");
// static const CString g_strSoesRemark = _T("SOE����(*.soes)");

static const CString g_strBinarysPostfix = _T("bnys");
static const CString g_strBinarysType = _T("����������");
// static const CString g_strBinarysRemark = _T("����������(*.bnys)");

static const CString g_strScriptMngrPostfix = _T("scpt");
static const CString g_strScriptMngrType = _T("���ýű�����");
// static const CString g_strScriptMngrRemark = _T("���ýű�����(*.scpt)");

static const CString g_strCPUPostfix = _T("cpu");
static const CString g_strCPUType = _T("CPU");
// static const CString g_strCPURemark = _T("CPU(*.cpu)");

static const CString g_strCPUSType = _T("CPUS");
static const CString g_strCPUSPostfix = _T("xml");
// static const CString g_strCPUSRemark = _T("�豸����ģ���ļ�(*.xml)");

//static const CString g_strSysParasPostfix = _T("sysp");
//static const CString g_strSysParasType = _T("ϵͳ����");
//static const CString g_strSysParasRemark = _T("ϵͳ����(*.sysp)");
//
//static const CString g_strTestParasPostfix = _T("tstp");
//static const CString g_strTestParasType = _T("���Բ���");
//static const CString g_strTestParasRemark = _T("���Բ���(*.tstp)");

static const CString g_strSysParasPostfix = _T("sprs");
static const CString g_strSysParasType = _T("ϵͳ/���Բ���");
// static const CString g_strSysParasRemark = _T("ϵͳ/���Բ���(*.sprs)");

inline CString GetGbNodeConfigFile()
{
	CString strFile;
	strFile.Format(_T("%s%s"),(CString)_P_GetConfigPath(),g_strGbNodeConfigXMLFile);

	return strFile;
}

inline CString GetGbDevTemplatePath(BOOL bUseAts=FALSE)
{
	CString strFile;

	if (bUseAts)
	{
		strFile = _P_GetInstallPath();
		strFile += _T("e-Report\\");
	}
	else
	{
		strFile = _P_GetSystemPath();
	}

	strFile.AppendFormat(_T("%s\\"), g_strTCtrlCntrTemplate);

	return strFile;
}

inline CString GetGbDevItemFilePath()
{
	CString strFilePath;
	strFilePath.Format(_T("%s%s\\"),(CString)_P_GetLibraryPath(),g_strGbDevItemSavePath);
	
	return strFilePath;
}

inline BOOL Gb_Node_ReadBinaryFile(CExBaseObject* pObj,const CString& strFileName)
{
	CBinarySerialBuffer oBuffer;
	//Gb_InitGuideBookFileVersion(oBuffer.m_chPrefix, oBuffer.m_dwVersion);
	Gb_InitGuideBookFileVersion(oBuffer);
	BOOL bFlag = oBuffer.OpenFromFile(strFileName);

	oBuffer.ReadVersion();
	oBuffer.SetVersionFindByID(g_dwDataMngrVersionID);

	if(bFlag)
	{
		oBuffer.SetReadMode();
		pObj->Serialize(oBuffer);
	}
	
	return bFlag;
}

inline BOOL Gb_Node_WriteBinaryFile(CExBaseObject* pObj,const CString& strFileName)
{
	CBinarySerialBuffer oBuffer;
	//Gb_InitGuideBookFileVersion(oBuffer.m_chPrefix, oBuffer.m_dwVersion);
	Gb_InitGuideBookFileVersion(oBuffer);

	oBuffer.SetCalSizeMode();
	oBuffer.WriteVersion();
	pObj->Serialize(oBuffer);
	oBuffer.AllocBuffer(0);

	oBuffer.SetWriteMode();
	oBuffer.WriteVersion();
	pObj->Serialize(oBuffer);

	oBuffer.SaveToFile(strFileName);

	return TRUE;
}


inline BOOL Gb_Node_ReadXmlFile(CExBaseObject* pObj,const CString& strFileName)
{
	BOOL bFlag = pObj->OpenXmlFile(strFileName, CGbXMLKeys::g_pGbXMLKeys);
	return bFlag;
}

inline BOOL Gb_Node_WriteXmlFile(CExBaseObject* pObj,const CString& strFileName)
{
	pObj->SaveXmlFile(strFileName, CGbXMLKeys::g_pGbXMLKeys);

	return TRUE;
}

inline BOOL Gb_Node_ReadFile(CExBaseObject* pObj,const CString& strFileName)
{
	CString strFilePostfix = ParseFilePostfix(strFileName);

	if (strFilePostfix.GetAt(0) == 'x')
	{
		return Gb_Node_ReadXmlFile(pObj, strFileName);
	}
	else
	{
		return Gb_Node_ReadBinaryFile(pObj, strFileName);
	}
}

inline BOOL Gb_Node_WriteFile(CExBaseObject* pObj,const CString& strFileName)
{
	CString strFilePostfix = ParseFilePostfix(strFileName);

	if (strFilePostfix.GetAt(0) == 'x')
	{
		return Gb_Node_WriteXmlFile(pObj, strFileName);
	}
	else
	{
		return Gb_Node_WriteBinaryFile(pObj, strFileName);
	}
}

//ClassID����

//GuideBook�ļ�����
#define GB_DEV_GUIDEBOOK_FILE									(CLASSID_XFILE + 0x00000011)
#define GB_DEV_GUIDEBOOK_FOLDER							(CLASSID_XFOLDER + 0x00000012)
#define GB_DEV_GUIDEBOOK_FILE_MNGR					(CLASSID_XFOLDER + 0x00000013)

//���뵼������
#define GB_DEV_ITEM_FILE												(CLASSID_XFILE + 0x00000014)	
#define GB_DEV_ITEM_FOLDER										(CLASSID_XFOLDER + 0x00000015)
#define GB_DEV_ITEM_FILE_MNGR									(CLASSID_XFOLDER + 0x00000016)
		
//Gb�����ģ��ClassID
#define GBECLASSID_CLASSMNGR									(CLASSID_EXLISTCLASS + 0x00000021)
#define GBECLASSID_CLASS													(CLASSID_EXLISTCLASS + 0x00000022)
#define GBECLASSID_CHILDOPTRBUTTONS				(CLASSID_EXLISTCLASS + 0x00000023)
#define GBECLASSID_CHILDOPTRBUTTON					(CLASSID_BASECLASS + 0x00000024)
#define GBECLASSID_CHILDGRIDCOLS							(CLASSID_EXLISTCLASS + 0x00000025)
#define GBECLASSID_CHILDGRIDCOL								(CLASSID_BASECLASS + 0x00000026)
#define GBECLASSID_OWNPOPMENUITEMS				(CLASSID_EXLISTCLASS + 0x00000027)
#define GBECLASSID_OWNPOPMENUITEM				(CLASSID_BASECLASS + 0x00000028)

//��Ϣ����
#define WM_GBNODE_CHILDBUTTON_CLICK			WM_USER + 4001
#define WM_GBNODE_SELCHANGED				WM_USER + 4002
#define WM_GBNODE_ATTR_SAVE					WM_USER + 4003				//���CGbNodeAttributeView�ϵ�Save��ť���͵���Ϣ
#define WM_GBNODE_CHILDGRID_SELCHANGED		WM_USER + 4004				//CGbNodeChildrenGridѡ��ı���Ϣ
#define WM_GBNODE_CHILDGRID_EDITCHANGED		WM_USER + 4005				//CGbNodeChildrenGrid���ݱ仯����༭�ı����޸�comboѡ��ʹ���ݸı�
#define WM_GBNODE_DELETE					WM_USER + 4006				//ɾ��GbNode��Ϣ
#define WM_GBNODE_IMPORT					WM_USER + 4007				//������Ϣ


BOOL GbUI_HasSameChildGrid(CExBaseObject *pGbNode1, CExBaseObject *pGbNode2);
BOOL GbUI_HasSameChildOptrBar(CExBaseObject *pGbNode1, CExBaseObject *pGbNode2);

//CExBaseList�������class CReports�⣬ͬʱ����class CSysParas���̳���CExBaseObject��
inline BOOL Gb_IsItemVisibleInTree(UINT nClassID)
{
	if (nClassID == GBCLASSID_CPUS || nClassID == GBCLASSID_CPU 
		|| nClassID == GBCLASSID_DEVICE_SYSPARAS || nClassID == GBCLASSID_DEVICE_TESTPARAS
		|| nClassID == CHARCLASSID_CCHARACTERISTICS
		|| nClassID == GBCLASSID_GBTDATAINTERFACES || nClassID == GBCLASSID_GBTDATAS 
		|| nClassID == GBCLASSID_GBTDATAINTERFACE)
	{
		return TRUE;
	}

	if (Gb_IsItemBaseClassID(nClassID))
	{
		return TRUE;
	}

	if (nClassID == GBCLASSID_DATASET || nClassID == GBCLASSID_DATASETGROUP
		|| nClassID == GBCLASSID_ANALOGS || nClassID == GBCLASSID_SETS || nClassID == GBCLASSID_CTRLWORDS
		|| nClassID == GBCLASSID_SOFTSWITCHS || nClassID == GBCLASSID_BINARYS || nClassID == GBCLASSID_SOES
		|| nClassID == GBCLASSID_BINARYINS || nClassID == GBCLASSID_BINARYOUTS || nClassID == GBCLASSID_DATASET)
	{
		return TRUE;
	}

	if (nClassID == GBCLASSID_CMD || nClassID == GBCLASSID_MACROPARA || nClassID == GBCLASSID_SCRIPTTEXT)
	{
		return FALSE;
	}

	if (nClassID == GBCLASSID_SCRIPT_TEXT_MNGR)
	{
		return FALSE;
	}

// 	if (((nClassID & CLASSID_EXLISTCLASS) == CLASSID_EXLISTCLASS) && (nClassID != GBCLASSID_REPORTS))
// 	{
// 		return TRUE;
// 	}

	return FALSE;
}

inline BOOL Gb_IsItemExpandInTree(UINT nClassID)
{
	switch (nClassID)
	{
	//case GBCLASSID_SAFETY:
	//case GBCLASSID_MACROTEST:
	//case GBCLASSID_SYSPARAEDIT:
	case GBCLASSID_COMMCMDS:
	case GBCLASSID_COMMCMD:
		//case GBCLASSID_DEVICE_PARAS:
		return FALSE;
	default:
		return ((nClassID & CLASSID_EXLISTCLASS) == CLASSID_EXLISTCLASS);
	}
}

////�ж��û������id�Ƿ���Ч
//BOOL GbUI_IDIsValid(CWnd* pWnd,CExBaseObject* pItem,CWnd* pEdit);
//BOOL GbUI_IDIsValid(CWnd* pWnd,CExBaseObject* pItem,const CString& strInputID);
//
////�ж��û������name�Ƿ���Ч
//BOOL GbUI_NameIsValid(CWnd* pWnd,CExBaseObject* pItem,CWnd* pEdit);
//BOOL GbUI_NameIsValid(CWnd* pWnd,CExBaseObject* pItem,const CString& strInputName);

//�޸����ƺ�ID��������
BOOL Gb_AvoidSameIDName(CExBaseList* pParent,CExBaseObject* pObj);

//�ж�ѡ�еĽڵ��Ƿ��ܹ�ɾ�����������ɾ��ʹ��Ӧ���Ҽ��˵��Ͱ�ť��Ч
BOOL GBUI_NodeCanDelete(CExBaseObject* pObj);

BOOL GBUI_UpdateJobGuidePaste(CExBaseObject* pCurSel,CExBaseObject* pObj);

void FormatScriptString(CString& strDefine,CString& strFunc,CString strID, CString strPath);


class CGbNodeAttrEditWndInterface
{
public:
	CGbNodeAttrEditWndInterface(CExBaseObject* pNode,CWnd* pParent)
	{
		m_pItem = pNode;
		m_pParent = pParent;
	}
	virtual ~CGbNodeAttrEditWndInterface()
	{

	}

public:
	CExBaseObject* m_pItem;
	CWnd*		m_pParent;

protected:
	//BOOL m_bModified;

public:
	virtual void SetModified(BOOL bFlag)
	{
		Gb_SetGbModifiedFlag(m_pItem, bFlag);
	}
	virtual BOOL GetModified()	
	{
		return Gb_GetGbModifiedFlag(m_pItem);;
	}

	virtual BOOL Save()
	{
		return TRUE;
	}//����༭

	virtual void NewEdit()
	{		

	}//�½�

	//��ʾ
	virtual void ShowGbNode(CExBaseObject* pObj) = 0;
	virtual void Show() = 0;
	virtual void Hide() = 0;
	virtual void AdjustSize(CRect rect) = 0;
	virtual void CreateEx() = 0;
	//virtual void Refresh() = 0;

};

class CGbNodeAttrEditWndInterfaceMap
{
public:
	CGbNodeAttrEditWndInterfaceMap()
	{
		m_nClassID = 0;
		m_pCGbNodeAttrEditWnd = NULL;
	}
	virtual ~CGbNodeAttrEditWndInterfaceMap()
	{
		delete m_pCGbNodeAttrEditWnd;
		m_pCGbNodeAttrEditWnd = NULL;
	}

	UINT m_nClassID;
	CGbNodeAttrEditWndInterface *m_pCGbNodeAttrEditWnd;
};

class CGbNodeAttrEditWndInterfaceMaps : public CTLinkListEx<CGbNodeAttrEditWndInterfaceMap> 
{
public:
	CGbNodeAttrEditWndInterface* FindGbNodeAttrEditWnd(UINT nClassID)
	{
		CGbNodeAttrEditWndInterfaceMap *p = NULL;
		CGbNodeAttrEditWndInterfaceMap *pFind = NULL;
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			p = (CGbNodeAttrEditWndInterfaceMap *)GetNext(pos);

			if (p->m_nClassID == nClassID)
			{
				pFind = p;
				break;
			}
		}

		if (pFind != NULL)
		{
			return pFind->m_pCGbNodeAttrEditWnd;
		}
		else
		{
			return NULL;
		}
	}

	void AddGbNodeAttrEditWnd(UINT nClassID, CGbNodeAttrEditWndInterface *pCGbNodeAttrEditWnd)
	{
		CGbNodeAttrEditWndInterfaceMap *pNew = new CGbNodeAttrEditWndInterfaceMap();
		pNew->m_nClassID = nClassID;
		pNew->m_pCGbNodeAttrEditWnd = pCGbNodeAttrEditWnd;
		AddTail(pNew);
	}
};

//lijq 2020-03-03  ���Լ�����ҵָ����ڵ���ʾ��ʱ��
extern BOOL g_bLogGbNodeShowTimeLong;
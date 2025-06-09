#pragma once

// #include "../../../Module/FileMngr/FileMngrXMLKeys.h"
#include "GbDevXMLKeys.h"
#include "../GuideBook/GuideBookDefine.h"

#include "../Characteristic/CharacteristicGlobal.h"
#include "../../../Module/API/FileApi.h"

//树形控件右键菜单和子对象optrbar按钮的ID
#define ID_NEW_DEVICE					1000
#define ID_NEW_ITEMS						1001
#define ID_NEW_SAFETY					1002
#define ID_NEW_CPU							1003
#define ID_NEW_MACROTEST		1004				//新建电气量项目
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

//定义ScriptDialog包含的Grid类型
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
//定义ScriptDialog类型
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
static const CString g_strTemplateType = _T("测试模板");

static const CString g_strGbNodeConfigXMLFile = _T("GbNodeConfig.xml");
    
//导入导出模块用到的各个不同种类文件后缀名称
static const CString g_strDevicePostfix = _T("dvc");
static const CString g_strDeviceType = _T("设备");
// static const CString g_strDeviceRemark = _T("设备(*.dvc)");																		//Remark表示下拉框中的类型说明文字

static const CString g_strJobGuidePostfix = _T("jbg");
static const CString g_strJobGuideType = _T("作业指导");
// static const CString g_strJobGuideRemark = _T("作业指导(*.jbg)");																		//Remark表示下拉框中的类型说明文字

static const CString g_strItemsPostfix = _T("itms");
static const CString g_strItemsType = _T("测试项目集合");
// static const CString g_strItemsRemark = _T("测试项目集合(*.itms)");																		//Remark表示下拉框中的类型说明文字

static const CString g_strSafetyPostfix = _T("sfty");
static const CString g_strSafetyType = _T("安全措施");
// static const CString g_strSafetyRemark = _T("安全措施(*.sfty)");

static const CString g_strMacroTestPostfix = _T("mtst");
static const CString g_strMacroTestType = _T("电气量项目");
// static const CString g_strMacroTestRemark = _T("电气量项目(*.mtst)"); 

static const CString g_strMacroCharTestPostfix = _T("mctst");
static const CString g_strMacroCharTestType = _T("边界测试");
// static const CString g_strMacroCharTestRemark = _T("边界测试(*.mctst)"); 

static const CString g_strCommCmdPostfix = _T("cmcd");
static const CString g_strCommCmdType = _T("通讯命令");
// static const CString g_strCommCmdRemark = _T("通讯命令(*.cmcd)");

static const CString g_strSysParaEditPostfix = _T("spdt");
static const CString g_strSysParaEditType = _T("系统参数编辑");
// static const CString g_strSysParaEditRemark = _T("系统参数编辑(*.spdt)");

static const CString g_strAnalogsPostfix = _T("anlg");
static const CString g_strAnalogsType = _T("模拟量集合");
// static const CString g_strAnalogsRemark = _T("模拟量集合(*.anlg)");

static const CString g_strSetsPostfix = _T("sets");
static const CString g_strSetsType = _T("整定值集合");
// static const CString g_strSetsRemark = _T("整定值集合(*.sets)");

static const CString g_strCtrlWordsPostfix = _T("ctrl");
static const CString g_strCtrlWordsType = _T("控制字集合");
// static const CString g_strCtrlWordsRemark = _T("控制字集合(*.ctrl)");

static const CString g_strSoftSwitchsPostfix = _T("stsw");
static const CString g_strSoftSwitchsType = _T("软压板集合");
// static const CString g_strSoftSwitchsRemark = _T("软压板集合(*.stsw)");

static const CString g_strBinaryInsPostfix = _T("bnis");
static const CString g_strBinaryInsType = _T("开入量集合");
// static const CString g_strBinaryInsRemark = _T("开入量集合(*.bnis)");

static const CString g_strBinaryOutsPostfix = _T("bnos");
static const CString g_strBinaryOutsType = _T("开出量集合");
// static const CString g_strBinaryOutsRemark = _T("开出量集合(*.bnos)");

static const CString g_strSoesPostfix = _T("soes");
static const CString g_strSoesType = _T("SOE集合");
// static const CString g_strSoesRemark = _T("SOE集合(*.soes)");

static const CString g_strBinarysPostfix = _T("bnys");
static const CString g_strBinarysType = _T("开关量集合");
// static const CString g_strBinarysRemark = _T("开关量集合(*.bnys)");

static const CString g_strScriptMngrPostfix = _T("scpt");
static const CString g_strScriptMngrType = _T("引用脚本管理");
// static const CString g_strScriptMngrRemark = _T("引用脚本管理(*.scpt)");

static const CString g_strCPUPostfix = _T("cpu");
static const CString g_strCPUType = _T("CPU");
// static const CString g_strCPURemark = _T("CPU(*.cpu)");

static const CString g_strCPUSType = _T("CPUS");
static const CString g_strCPUSPostfix = _T("xml");
// static const CString g_strCPUSRemark = _T("设备数据模型文件(*.xml)");

//static const CString g_strSysParasPostfix = _T("sysp");
//static const CString g_strSysParasType = _T("系统参数");
//static const CString g_strSysParasRemark = _T("系统参数(*.sysp)");
//
//static const CString g_strTestParasPostfix = _T("tstp");
//static const CString g_strTestParasType = _T("测试参数");
//static const CString g_strTestParasRemark = _T("测试参数(*.tstp)");

static const CString g_strSysParasPostfix = _T("sprs");
static const CString g_strSysParasType = _T("系统/测试参数");
// static const CString g_strSysParasRemark = _T("系统/测试参数(*.sprs)");

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

//ClassID定义

//GuideBook文件管理
#define GB_DEV_GUIDEBOOK_FILE									(CLASSID_XFILE + 0x00000011)
#define GB_DEV_GUIDEBOOK_FOLDER							(CLASSID_XFOLDER + 0x00000012)
#define GB_DEV_GUIDEBOOK_FILE_MNGR					(CLASSID_XFOLDER + 0x00000013)

//导入导出功能
#define GB_DEV_ITEM_FILE												(CLASSID_XFILE + 0x00000014)	
#define GB_DEV_ITEM_FOLDER										(CLASSID_XFOLDER + 0x00000015)
#define GB_DEV_ITEM_FILE_MNGR									(CLASSID_XFOLDER + 0x00000016)
		
//Gb类管理模块ClassID
#define GBECLASSID_CLASSMNGR									(CLASSID_EXLISTCLASS + 0x00000021)
#define GBECLASSID_CLASS													(CLASSID_EXLISTCLASS + 0x00000022)
#define GBECLASSID_CHILDOPTRBUTTONS				(CLASSID_EXLISTCLASS + 0x00000023)
#define GBECLASSID_CHILDOPTRBUTTON					(CLASSID_BASECLASS + 0x00000024)
#define GBECLASSID_CHILDGRIDCOLS							(CLASSID_EXLISTCLASS + 0x00000025)
#define GBECLASSID_CHILDGRIDCOL								(CLASSID_BASECLASS + 0x00000026)
#define GBECLASSID_OWNPOPMENUITEMS				(CLASSID_EXLISTCLASS + 0x00000027)
#define GBECLASSID_OWNPOPMENUITEM				(CLASSID_BASECLASS + 0x00000028)

//消息定义
#define WM_GBNODE_CHILDBUTTON_CLICK			WM_USER + 4001
#define WM_GBNODE_SELCHANGED				WM_USER + 4002
#define WM_GBNODE_ATTR_SAVE					WM_USER + 4003				//点击CGbNodeAttributeView上的Save按钮发送的消息
#define WM_GBNODE_CHILDGRID_SELCHANGED		WM_USER + 4004				//CGbNodeChildrenGrid选择改变消息
#define WM_GBNODE_CHILDGRID_EDITCHANGED		WM_USER + 4005				//CGbNodeChildrenGrid数据变化，如编辑文本，修改combo选项使数据改变
#define WM_GBNODE_DELETE					WM_USER + 4006				//删除GbNode消息
#define WM_GBNODE_IMPORT					WM_USER + 4007				//导入消息


BOOL GbUI_HasSameChildGrid(CExBaseObject *pGbNode1, CExBaseObject *pGbNode2);
BOOL GbUI_HasSameChildOptrBar(CExBaseObject *pGbNode1, CExBaseObject *pGbNode2);

//CExBaseList的子类除class CReports外，同时包含class CSysParas（继承于CExBaseObject）
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

////判断用户输入的id是否有效
//BOOL GbUI_IDIsValid(CWnd* pWnd,CExBaseObject* pItem,CWnd* pEdit);
//BOOL GbUI_IDIsValid(CWnd* pWnd,CExBaseObject* pItem,const CString& strInputID);
//
////判断用户输入的name是否有效
//BOOL GbUI_NameIsValid(CWnd* pWnd,CExBaseObject* pItem,CWnd* pEdit);
//BOOL GbUI_NameIsValid(CWnd* pWnd,CExBaseObject* pItem,const CString& strInputName);

//修改名称和ID避免重名
BOOL Gb_AvoidSameIDName(CExBaseList* pParent,CExBaseObject* pObj);

//判断选中的节点是否能够删除，如果不能删除使对应的右键菜单和按钮无效
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
	}//保存编辑

	virtual void NewEdit()
	{		

	}//新建

	//显示
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

//lijq 2020-03-03  调试监视作业指导书节点显示的时间
extern BOOL g_bLogGbNodeShowTimeLong;
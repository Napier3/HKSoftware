//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CSttFrame_GlobalDatas.h  CSttFrame_GlobalDatas

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"
#include "SttFrame_GlobalData.h"
#include "../../../../../Module/DataMngr/DataGroup.h"

#define    STTFRAME_GLOBALDATA_TabHeight_ID                _T("TabHeight")
#define    STTFRAME_GLOBALDATA_ComBoxItemHeight_ID         _T("ComBoxItemHeight")
#define    STTFRAME_GLOBALDATA_TableVertScrollWidth_ID         _T("TableVertScrollWidth")
#define    STTFRAME_GLOBALDATA_TableHorizontalScrollHeight_ID         _T("TableHorizontalScrollHeight")
#define    STTFRAME_GLOBALDATA_TreeVertScrollWidth_ID         _T("TreeVertScrollWidth")
#define    STTFRAME_GLOBALDATA_TreeHorizontalScrollHeight_ID         _T("TreeHorizontalScrollHeight")
#define    STTFRAME_GLOBALDATA_ComBoxVertScrollWidth_ID          _T("ComBoxVertScrollWidth")

/*#define    STTFRAME_GLOBALDATA_VertScrollWidth_ID          _T("VertScrollWidth")
#define    STTFRAME_GLOBALDATA_LevelScrollHeight_ID          _T("LevelScrollHeight")
#define    STTFRAME_GLOBALDATA_ComBoxVertScrollWidth_ID          _T("ComBoxVertScrollWidth")
#define    STTFRAME_GLOBALDATA_QTreeWidgetVertScrollWidth_ID          _T("QTreeWidgetVertScrollWidth")
#define    STTFRAME_GLOBALDATA_QTreeWidgetLevelScrollWidth_ID          _T("QTreeWidgetLevelScrollWidth")
#define    STTFRAME_GLOBALDATA_GooseVertScrollWidth          _T("GooseVertScrollWidth")
#define    STTFRAME_GLOBALDATA_GooseLevelScrollWidth          _T("GooseLevelScrollWidth")
#define    STTFRAME_GLOBALDATA_CustomSetVertScrollWidth          _T("CustomSetVertScrollWidth")
#define    STTFRAME_GLOBALDATA_CustomSetLevelScrollWidth          _T("CustomSetLevelScrollWidth")
#define    STTFRAME_GLOBALDATA_LeadingInVertScrollWidth          _T("LeadingInVertScrollWidth")
#define    STTFRAME_GLOBALDATA_LeadingLevelScrollWidth         _T("LeadingLevelScrollWidth")
*/

class CSttFrame_GlobalDatas : public CDataGroup
{
public:
	CSttFrame_GlobalDatas();
	virtual ~CSttFrame_GlobalDatas();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_GLOBALDATAS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_GlobalDatasKey();     }
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

//私有成员变量
private:
	CSttFrame_GlobalData* m_pGlobalData;
//私有成员变量访问方法
public:
	CSttFrame_GlobalData *GetGlobalData() { return m_pGlobalData; }
	void SetGloabalData(CSttFrame_GlobalData *pGloabalData){ m_pGlobalData =pGloabalData; }
	long GetTabHeight();//获取Tab的高度
	long GetComBoxItemHeight();//获取Combox控件单个Item高度
	long GetTableVertScrollWidth();//获取Table类控件竖直滑动块宽度
	long GetTableHorizontalScrollHeight();//获取Table类控件水平滑动块宽度
	long GetTreeVertScrollWidth(); //获取Tree类控件竖直滑动块宽度
	long GetTreeHorizontalScrollHeight(); //获取Tree类控件水平滑动块宽度
	long GetComBoxVertScrollWidth();//获取Combobox控件下拉框竖直滑动块宽度

};


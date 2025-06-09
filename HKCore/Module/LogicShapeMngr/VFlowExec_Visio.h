//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//VFlowExec_Visio.h  CVFlowExec_Visio

#pragma once

#include "LogicShapeMngrGlobal.h"


#include "VFlowShapeLines.h"
#include "VFlowShapes.h"

#include "../Visio/VisioReadWrite.h"
#include "../DataMngr/DvmDataset.h"


/*
第一步：打开Visio图文件调用 OpenVisioFile
第二步：根据Visio中当前页面Index或name设置当前激活的Sheet页  调用InitFlowShapesFromPage函数，在该函数中完成对当前激活sheet也中所有图形形状的类对象的创建、各种功能初始化
第三步：需要外部模块将所有数据的数据类型和单位存入m_oOrigDataDataset对象中，只有属性原始数据需要从外部获取数据类型，因属性中无法判断具体数据类型
第四步：调用UpdataDataTypeUnit_AllOrigDatas函数完成对属性类原始数据，数据类型和单位的幅值
第五步：调用UpdataValue_AllOrigDatas函数完成对所有原始数据的赋值
第六步：调用UpdateAllShapes函数，更新当前激活界面

中途更新图形显示步骤：
第一步：外部模块更新m_oOrigDataDataset中数据值，并加更新的DvmData中m_nIndex设置为1
第二步：调用UpdataValue_AllOrigDatas函数完成对所有原始数据的赋值(上述步骤五)
第三步：调用UpdateAllShapes函数，更新当前激活界面(上述步骤六)

*/




class CVFlowExec_Visio : public CExBaseList
{
public:
	CVFlowExec_Visio();
	virtual ~CVFlowExec_Visio();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CVFLOWEXEC_VISIO;   }
	virtual BSTR GetXmlElementKey()  {      return CLogicShapeMngrXmlRWKeys::CVFlowExec_VisioKey();     }
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

//私有成员变量访问方法
public:
//属性变量访问方法
	BOOL OpenVisioFile(const CString &strVisioFilePath, BOOL bVisible = TRUE);//打开当前Visio图
	BOOL SaveVisioFile(); //保存当前Visio图
	void CloseFile();  //关闭当前文档
	void QuitApp();
	BOOL InitFlowShapesFromPage(const CString &strPageName);//根据Page名称，查找对应的page，并将该页设置为当前页，用当前页中所用形状初始化所用链表
	BOOL InitFlowShapesFromPage(long nPageIndex);//根据Page标识，查找对应的page，并将该页设置为当前页，用当前页中所用形状初始化所用链表,从1开始计数

	BOOL UpdataValue_AllOrigDatas();//更新所有的原始数据值
	BOOL UpdataDataTypeUnit_AllOrigDatas();//更新所有的原始数据对应的数据类型及单位
	BOOL UpdateAllShapes();//根据当前值,更新全部Shape、Line

	BOOL SetOrigDataValue(const CString &strOrigDataRef,const CString &strValue);//更新单个原始数据,只更新数据值,不更新界面,对于属性类数据固定更新Visio界面
	BOOL GetOrigDataValue(const CString &strOrigDataRef,CString &strValue);//获取单个原始数据,只从内存获取,不从实际界面获取
	BOOL SetOrigDataValue_UI(const CString &strOrigDataRef,const CString &strValue);//更新单个原始数据,只更新数据值,同时更新界面
	BOOL GetOrigDataValue_UI(const CString &strOrigDataRef,CString &strValue);//获取单个原始数据,从界面获取

	BOOL SetShapeValueByID(const CString &strShapeID,const CString &strValue);//设置形状值、根据形状的ID
	BOOL GetShapeValueByID(const CString &strShapeID,CString &strValue);//获取形状值、根据形状的ID

	CVFlowShape* FindShapeByID(const CString &strShapeID);
	CVisioReadWrite* GetVisioReadWrite()	{	return &m_oVisioReadWrite;	}
	CExBaseList* GetPagesList()	{	return m_oVisioReadWrite.GetPageList();	}
	void ActivePage(const CString &strPage); //根据名称，激活页面


	CDvmDataset m_oOrigDataDataset;//该数据集中的数据对象CDvmData描述了原始数据的信息,其中m_strID为原始数据ID、m_strName为原始数据路径;
	//m_strDataType、m_strUnit、m_strValue从外部获取,与该数据的实际数据类型、单位、值一致，m_nIndex标识该数据是否被修改,更新参数后，将该值设置为0
protected:
	void DeleteAllCalcShapes();//删除基类链表中用于运算的集合对象,该对象的链表中的形状在m_oShapes、m_oLines中，防止重复删除
	BOOL CreateAllShapesLines();//获取全部Shape、Line，并将其放入对应成员变量链表中
	BOOL CreateAllPropertys(); //创建所有属性,Shapes中所有形状的属性，暂不考虑line
// 	BOOL AttachAllShapeLineInOut();//关联所有形状的输入、输出节点
// 	BOOL AttachShapesInOut();//关联Shapes中所有的输入、输出节点
	BOOL AttachLinesInOut();//关联Lines中所有的输入、输出节点
	void InitOrigDataShapesPropertys();//初始化原始数据Shapes、Propertys链表
	void AttachLineInOut(CVFlowShapeLine *pShapeLineData,const long &nBeginShapeID,const long &nEndShapeID);//创建单个线条的输入输出关联
	BOOL CreateCalcFlowShapes();//创建算法运算用的Shapes
	void CreateCalcFlowShapes(CVFlowShapes *pSrcCalcShapes);//创建算法运算用的Shapes
	void GetAllInShapes(CVFlowShapes *pSrcShapes,CVFlowShapes *pDstShapesRef);//获取全部与输入端相连的Shape

	CVFlowShape m_oOrigDataPropertysRef;//全部带有索引的属性(即需要更新的原始数据属性)
	CVFlowShapes m_oOrigDataShapesRef;//全部带有索引的原始数据节点(应该是所有原始数据都应该带有索引路径)

	CVFlowShapes m_oShapes;//全部的Shape节点
	CVFlowShapeLines m_oLines;//全部的Line节点

private:
	CVisioReadWrite m_oVisioReadWrite;
};


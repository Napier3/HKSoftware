//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristic.h  CCharacteristic

#pragma once

#include "CharacteristicGlobal.h"


#include "CharacterArea.h"
#include "CharInterface.h"

class CCharacteristic : public CExBaseList
{
public:
	CCharacteristic();
	virtual ~CCharacteristic();

	static CCharacteristic* _New(CBaseObject *pParent=NULL)
	{
		CCharacteristic *pNew = new CCharacteristic();
		pNew->SetParent(pParent);
		return pNew;
	}

	BOOL m_bOldVersion;

	long m_nUse;//20240923 luozibing 曲线使用 缺省为使用(1)
	long  m_nAutoClose;
	CString  m_strAxis;
	CString  m_strXMin;
	CString  m_strXMax;
	CString  m_strYMin;
	CString  m_strYMax;
	CString  m_strTestLineMode;
	CString	 m_strIndex;	//20210913 sf  单机软件用得到，自动测试暂时用不到

	double  m_fXMin;
	double  m_fXMax;
	double  m_fYMin;
	double  m_fYMax;

	BOOL  m_bXMin;
	BOOL  m_bXMax;
	BOOL  m_bYMin;
	BOOL  m_bYMax;

	//2020-3-13  特性曲线表示，用于检索特性曲线，暂时不用，保留为将来的需求
	//不增加属性变量的目的，是为了能够兼容之前的版本
	CDvmData *m_pCharAttrs;

	//lijunqing 2024-9-24  定义特性曲线误差带长度
	double m_fErrorBandLen;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTIC;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

//私有成员变量
private:
	CCharacterArea *m_pArea;
	CCharInterface *m_pCharacteristicInterface;
    CCharTestObjects *m_pTestObjects;

//私有成员变量访问方法
public:
	BOOL IsAutoclose()	{	return m_nAutoClose;	}
	CCharacterArea* GetCharacterArea();
	CCharInterface* GetCharInterface();
    CCharTestObjects* GetTestObjects();
	CExBaseList* GetCurDrawList();
	BOOL CalCharElementExpression(const CString &strExpress, double &dValue, BOOL bLogError);
	void AttachCCharInterface(CCharInterface *pCharInterface);
    void AppendClone(CExBaseList *pListSrc, BOOL bSetParent);

	void InitVariableValues();
	void CalCharElement(CExBaseList *pDrawList);
	void CalTestLines(CExBaseList *pDrawList);
	void GetAllMacroTestLines(CExBaseList *pList);

	void InitCharDrawTestObj_ForDraw(CExBaseList *pDrawList, int nFaultType, CExBaseObject *pCurTestObj, int nTestObjDrawMode);   //20240822 wanmj 添加m_pTestObjects的测试线到drawlist  //add wangtao 20240925新增参数区分特性曲线单独绘制测试线/点还是全部
    void CalCharErrBandLen(double dMaxSensAngle);   //20241014 wanmj 计算特性曲线误差带
    void SetIsShowErrorBand(BOOL bShow);    //20241015 wanmj 设置是否显示误差带
	BOOL CmpAttrs(CDvmData *pAttrs);
	CDvmData* GetAttrs(BOOL bCreateNew);

	//添加特性曲线与测试测试项目的接口
	//2020-3-19
	void DeleteAllTestLines();
	void AddTestLines(CXDrawData_Line *pValRange, double dLenStep);
	void AddTestLine(CXDrawData_Line *pCurrValLine);

	//2020-08-07  lijunqing
	CXDrawList* InitCharDrawElement_ForDraw();
	CXDrawList* InitCharDrawElement_ForCalOnly();

	//2022-7-24  lijunqing
	void InitAllMacroTestLinesID();
	CCharTestLine* FindTestLine(const CString &strID);

	//2024-9-26 lijunqing 求取线段与曲线的交点
	void GetIntersectPoint(double x1, double y1, double x2, double y2, CXDrawDatas &oList);
	void GetIntersectPoint(CXDrawData_Line *pLine, CXDrawDatas &oList);

	bool IsPointInErrBand(double x, double y);

	//2024.10.10 wanmj  待增加测试线计算交点的功能
	//返回值：测试线和曲线是否存在交点；参数1：起点横坐标；参数2：起点纵坐标；参数3：终点横坐标；参数4：终点纵坐标；参数5：两个点或者一条线（测试项的首端末端阻抗）
	bool GetIntersectLine(double dBegX, double dBegY, double dEndX, double dEndY, CExBaseList &oList);
	//返回值：测试线和曲线是否存在交点；参数1：起点横坐标；参数2：起点纵坐标；参数3：角度；参数5：两个点或者一条线（测试项的首端末端阻抗）
	bool GetIntersectLine(double dBegX, double dBegY, double dAng, CExBaseList &oList);		// oList是两个点或者一条线
	
	//返回的是搜索线对象，使用下面的接口比较好，返回CCharTestLine对象
	bool GetIntersectTestLine(double dBegX, double dBegY, double dEndX, double dEndY, CExBaseList &oList);
	bool GetIntersectTestLine(double dBegX, double dBegY, double dAng, CExBaseList &oList);	
};


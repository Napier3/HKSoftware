//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Characteristics.h  CCharacteristics

#pragma once

#include "CharacteristicGlobal.h"


#include "CharacteristicTmplate.h"

class CCharacteristics : public CExBaseList
{
public:
	CCharacteristics();
	virtual ~CCharacteristics();


//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERISTICS;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacteristicsKey();     }
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

	//20240902 luozibing 添加更新测试点
	virtual BOOL AddUpdateTestPoint_Imp(const CString &strIDPath, double dX, double dY, int nFaultType, int nZoneType, int nState = -1);
    //20240822 wanmj
    void AddUpdateTestLine_Imp(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nZoneType, int nState = -1);
    void DeleteTestData(const CString &strIDPath);
    void ClearTestData();
    CXDrawList* InitCharDrawTestObj_ForDraw(int nFaultType = -1); //20240822 wanmj 添加测试线到drawlist
	CXDrawList* InitCharDrawTestObj_ForDraw(CCharacteristic *pCharact,int nFaultType = -1);
	CCharTestObjects*GetTestObjects();//获取当前测试对象

    void CalCharErrBandLen();   //20241014 wanmj 计算特性曲线误差带
    void SetIsShowErrorBand(BOOL bShow);    //20241015 wanmj 设置是否显示误差带

	//add wangtao 20240927 存在多特性曲线情况下,添加更新测试线
	void AddUpdateTestLine(const CString &strIDPath, double dBegX, double dBegY, double dEndX, double dEndY, int nFaultType, int nState = -1);
	//add wangtao 20240927 存在多特性曲线情况下,添加更新测试点
	void AddUpdateTestPoint(const CString &strIDPath, double dX, double dY, int nFaultType, int nState = -1);
//私有成员变量
private:
    CCharTestObjects *m_pTestObjects;
    CExBaseObject *m_pCurTestObj;  //20240920 wanmj 记录当前选中测试点/线

public:
    double m_dMaxSensAng;   //20241014 wanmj 最大灵敏角

//私有成员变量访问方法
public:
	void InitVariableValues();
	void CalCharElement(CExBaseList *pDrawList);

	BOOL IsCharTempExist(CCharacteristic *pCharTmp);
	BOOL AddCharTempClone(CCharacteristic *pCharTmp);
	CCharacteristic* GetAtIndex_Char(long nIndex);
	CCharacteristic* GetTail_Char();
	CCharacteristic* FindByID_Char(const CString &strID);

	CCharacteristic* FindChar(CDvmData *pAttrs);

	//2021-9-17  初始化空的特性曲线
	void InitEmptyCharacter(const CString &strAxis);
	//2023-2-15  shaolei   通过id和index，结合查找特性曲线
	CCharacteristic* FindCharByID_Index(const CString &strID, const CString &strIndex);
	int m_nTestObjDrawMode; // 区分特性曲线 单独绘制测试线/点，或全部绘制
	void UpdateCurrTestPoint(double fXact, double fYact, long nActState = 1);//add wangtao 20241021 绘制测试过程中的搜索点
	void UpdateTestPointState(CString strPointID, long nState = 1);//add luozibing 20241028 更新测试点状态
};
BOOL Global_GetZSettingValueFromCharacteristics(CCharacteristics *pCCharacteristics, long nZone, long nFaultType, double dZAngle,double &dZSePara);//20240906 luozibing 通过通过区段、故障类型、阻抗角，获取当前阻抗定值
BOOL Global_GetZSettingValueFromCharacteristic(CCharacteristic* pChar, double dZAngle, double &dZSePara);//20241014 luozibing 通过阻抗角计算曲线对应阻抗定值
CString Global_GetCharFaultTypeStringByFaultType(int nFaultValue);//20240905 luozibing 根据故障参数值找到曲线id 


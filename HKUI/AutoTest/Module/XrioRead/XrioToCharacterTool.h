#pragma once
#include "XrioListCfg.h"
#include "XrioObjectCfg.h"
#include "XrioCustomBlock.h"
#include "XrioCustomParameter.h"
#include "../../Module/XrioRead/XDeviceModel/XDeviceModel.h"

class CXrioToCharacterTool
{
public:
    CXrioToCharacterTool();
    virtual ~CXrioToCharacterTool();
    //重载函数
public:
    BOOL XrioToCharacter(CXrio* pXrio,CCharacteristicLib* pCharacterLib);
    BOOL UpdateCharacterByXrioFile(CXrio* pXrio, CCharacteristicLib* pCharacterLib);//更新Xrio文件后同步更新相对应转换后Character对象
private:
    //差动
    void GetMultiDiffExpr(CCharElementExpr *pCharElementExpr);
    enum CurveType{Lined, AdrExpr,NAdrExpr}; //用于表示当前的两点之间的曲线类型是线段还是表达式。//AdrExpr为寻址表达式，这样的表达式需要在XRIO文件中查找 //NAdrExpr非寻址表达式，这样的表达式不需要在XRIO文件中查找，POINT节点直接存在
    typedef struct DiffExprRefsSet
    {
        int Position;
        CString DiffExprRef;
    }DiffExprRefsSet,*DiffExprRefsSetptr;//表示当前VB.NET函数的参数和位置顺序
private:
    static BOOL CompareByPosition(const DiffExprRefsSet& Prev, const DiffExprRefsSet& Next) { return Prev.Position < Next.Position; }
    //寻址
    CXrioCustomParameter* FindRefByIDPath(const CString& strings,CXrioCustom* pXrioCustom);
    BOOL InitAttr(CString &strDesAttrID, const CString &strDesAttrValue, const CString &strSrcAttrValue);
    CurveType CheckValueFormula(CXrio* pXrio,const CString& strValueFormula,CXrioValueRefList *pValueRefList);
    //距离
    BOOL ParseXrioDistance(CExBaseObject *pObj, CCharacteristicLib *pCharacterLib);//距离
    BOOL ParseDistanceZone(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder);//距离下的ZONE节点
    BOOL ParseDistanceShape(CExBaseObject *pObj, CCharacterArea *pCharacterArea);//ZONE节点下判断Genericshape还是Mhoshape
    BOOL AddDistanceGenericshape(CExBaseObject *pObj, CCharacterArea *pCharacterArea);//Genericshape
    BOOL AddDistanceMhoshape(CExBaseObject *pObj, CCharacterArea *pCharacterArea);//Mhoshape
    BOOL AddDistanceLine(CExBaseObject *pObj, CCharacterArea *pCharacterArea);//Genericshape下的线
    BOOL AddDistanceArc(CExBaseObject *pObj, CCharacterArea *pCharacterArea);//Genericshape下的弧

    //差动
    BOOL ParseXrioDifferential(CXrio* pXrio, CExBaseObject *pObj, CCharacteristicLib *pCharacterLib);//差动
    BOOL ParseDifferentialDiffBias(CXrio* pXrio,CExBaseObject *pObj,CCharacterFolder *pCharacterFolder);//vector中取坐标写入xml
    BOOL ParseDifferentialPoint(CXrio* pXrio,CExBaseObject *pObj,CCharInterface *pCharInterface,CCharacterArea *pCharacterArea);//提取坐标点数存到vector
    BOOL ParseDifferentialPoint(CExBaseObject *pObj, CCharacterArea *pCharacterArea);
    BOOL ParseDifferentialPointFormula(CXrio* pXrio, CXrioValueRefList *pValueRefList,CCharInterface *pCharInterface,CCharElementExpr *pCharElementExpr);//判断Y坐标的公式，有公式就寻址提取公式的参数
    void GetCurrExprRefsID(CXrioValueRefList *pValueRefList,CCharElementExpr *pCharElementExpr);
    void DeleteINFPoints(CRioTripChar *pTripChar);
    BOOL IsINFPoint(CRioDiffPoint *pDiffPoint);

    //反时限
    BOOL ParseRioOverCurrent(CExBaseObject *pObj, CCharacteristicLib *pCharacterLib);//反时限
    BOOL ParseOverCurrentGroup(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder);//反时限下group节点下判断Table、Char、I2T
    BOOL ParseOverCurrentTable(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder);//Table，存放点坐标，图像是线段
    BOOL ParseOverCurrentTablePoint(CExBaseObject *pObj, CString& strPoints);
    BOOL ParseOverCurrentChar(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP);//CHar，IEEE类曲线
    BOOL ParseOverCurrentCharI2T(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP);//I2T，I2T类曲线
    BOOL ParseOverCurrentTimedOverCurrentElement(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder);//反时限下TimedOverCurrentElement节点
    BOOL ParseOverCurrentOperatingCurves(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString& strTP);//TimedOverCurrentElement节点下OperatingCurves节点，判断InverseParameterCurve、I2T、IAC、Standard、Custom
    BOOL ParseOverCurrentTimeMultiplier(CExBaseObject *pObj, CString &strTP);//取TP，时间指数
    BOOL ParseOverCurrentInverseParameterCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP);//InverseParameterCurve，IEEE类
    BOOL ParseOverCurrentI2TParameterCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP);//I2T
    BOOL ParseOverCurrentIACParameterCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP);//IAC
    BOOL ParseOverCurrentStandardCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder,const CString &strTP);//标准曲线，但是没参数
    BOOL ParseOverCurrentCustomCurve(CExBaseObject *pObj, CCharacterFolder *pCharacterFolder);//CustomCurve，图像是线段
    BOOL ParseOverCurrentCustomCurvePoint(CExBaseObject *pObj, CString &strRefX, CString &strRefY);//存取CustomCurve的坐标点
    BOOL ParseOverCurrentCustomCurvePointEx(CExBaseObject *pObj, CString& strPoints);//存取CustomCurve的坐标点
    BOOL ParseOverCurrentTablePoint(CExBaseObject *pObj, CString &strRefX, CString &strRefY);
};


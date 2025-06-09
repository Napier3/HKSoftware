#pragma once
#include "RioDevice.h"
#include "XrioListCfg.h"
#include "XrioObjectCfg.h"
#include "XrioCustomBlock.h"
#include "XrioCustomParameter.h"
#include "../../Module/XrioRead/XDeviceModel/XDeviceModel.h"
#include "../XLanguageResourceAts.h"
class CXrioToDeviceModelTool
{
public:
    CXrioToDeviceModelTool();
    virtual ~CXrioToDeviceModelTool();
	//重载函数
public:
    BOOL XrioToDeviceModel(CXrio* pXrio, CDvmDevice* pDvmDevice);//Xrio转换为DeviceModel对象
    //更新文件csv、txt、set文件会打印出具体的更新情况，但是当前如果是xrio文件更新的话暂不考虑打印出具体更新情况。
    BOOL UpdateDeviceModelByXrioFile(CXrio* pXrio, CDvmDevice* pDvmDevice);//更新Xrio文件后同步更新相对应转换后DeviceModel对象
    BOOL IsXrioDataset_Device(CExBaseObject *pCurrObj);//判断传入节点是否为Device对象
	BOOL IsXrioDataset_CBCONFIGURATION(CExBaseObject *pCurrObj);//判断传入节点是否为CBCONFIGURATION对象
	BOOL IsXrioDataset_Characteristic(CExBaseObject *pCurrObj);//判断传入节点是否为特性曲线对象
private:
    //初始化 数据类型，值，单位，单位小数点位数，最小值，最大值
    void InitDataType(CString& strDataType, CExBaseObject *pObj);
    void InitValueByDataType(CString& strValue, const CString& strDataType, CExBaseList *pList);
    void InitUnitByDataType(CString& strUnitValue ,const CString& strDataType);
    void InitUnitDecPlacesByDataType(CString& strUnitDecPlacesValue ,const CString& strDataType);
    void InitMinByDataType(CString& strMinValue ,const CString& strDataType, CExBaseObject *pObj);
    void InitMaxByDataType(CString& strMaxValue ,const CString& strDataType, CExBaseObject *pObj);
    void InitDvmDataAttrNormalize(CDvmData *pData);
    void InitDvmValueAttrNormalize(CDvmValue *pValue);

	//增加距离、差动、反时限Dataset节点
	BOOL AddCharacteristicNode(CDvmLogicDevice *pSrcLogicDevice,CExBaseObject* pObj);
    BOOL InitCharacterNodeAttr(CDvmDataset *pCDvmDataset,CExBaseObject* pObj);
    BOOL InitCharacterNodeAttrWithKey(CDvmDataset *pCDvmDataset,const CString& strIDValue,const CString& strDataType,CExBaseObject* pObj);
    BOOL InitAttr(CString &strDesAttrID, const CString &strDesAttrValue, const CString &strSrcAttrValue);
    //XrioToDeviceModel
    BOOL ParseXrioCustomBlock(CXrioCustomBlock* pXrioCustomBlock,CDvmDataset *pDataset);//解析XRIO文件CUSTOM节点下Block对象
    BOOL ParseXrioCustomParameter(CXrioCustomBlock* pXrioCustomBlock,CDvmData *pData);//解析XRIO文件CUSTOM节点下Parameter对象
    BOOL RecursionXrioCustomParameter(CXrioCustomBlock *pChildXrioCustomBlock, CDvmValue *pValue);//递归解析XRIO文件CUSTOM节点下Parameter对象
    BOOL SupplementEmptyNodeAttributes(CDvmValue *pValue);

    BOOL AddParameterForeignId(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//增加Data节点的ForeignId属性
    BOOL AddParameterForeignId(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的ForeignId属性
    BOOL AddParameterDescription(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//增加Data节点的Description属性
    BOOL AddParameterDescription(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的Description属性

    BOOL AddParameterUnit(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的Unit属性
    BOOL AddParameterMinValue(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的Min属性
    BOOL AddParameterMaxValue(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的Max属性

    BOOL AddParameterValueFormula(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//增加Data节点的ValueFormula属性
    BOOL AddParameterValueFormula(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的ValueFormula属性

    //2024-9-27补充小数点位数节点,该节点增加不影响之前的内容。
    BOOL AddParameterUnitDecimalPlaces(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//增加Data节点的Unit属性对应的小数点位数
    BOOL AddParameterUnitDecimalPlaces(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的Unit属性对应的小数点位数

    BOOL AddParameterValue(CXrioCustomParameter* pXrioCustomParameter,CDvmValue *pValue);//增加Value节点的参考值对象
    BOOL AddParameterValue(CXrioCustomParameter* pXrioCustomParameter,CDvmData *pData);//增加Data节点的参考值对象

    //XRIO_RIO_DEVICE 解析Rio节点中Device节点的DeviceNamePlate DeviceLocation DeviceNominalValues DeviceResiDualfactors DeviceLimits DeviceMisc对象
    BOOL ParseXrioRioDevice(CDvmLogicDevice *pSrcLogicDevice,CExBaseObject* pObj);
    BOOL ParseXrioRioDeviceNamePlate(CRioNameplate *pRioNameplate,CDvmData *pData);//DeviceNamePlate
    BOOL ParseXrioRioDeviceLocation(CRioLocation *pRioLocation,CDvmData *pData);//DeviceLocation
    BOOL ParseXrioRioDeviceNominalValues(CRioNominalValues *pRioNominalValues,CDvmData *pData);//DeviceNominalValues
    BOOL ParseXrioRioDeviceResiDualfactors(CRioResidualFactors *pRioResidualFactors,CDvmData *pData);//DeviceResiDualfactors
    BOOL ParseXrioRioDeviceLimits(CRioLimits *pRioLimits,CDvmData *pData);//DeviceLimits
    BOOL ParseXrioRioDeviceMisc(CRioMisc *pRioMisc,CDvmData *pData);//DeviceMisc

    //XRIO_RIO_CB 解析Rio节点中CB节点的Triptime Closetime P52AB对象
    BOOL ParseXrioRioCBConfiguration(CDvmLogicDevice *pSrcLogicDevice, CExBaseObject* pObj);
    BOOL ParseXrioRioCBConfigurationTriptime(CRioTripTime *pRioTripTime,CDvmData *pData);
    BOOL ParseXrioRioCBConfigurationClosetime(CRioCloseTime *pRioCloseTime,CDvmData *pData);
    BOOL ParseXrioRioCBConfigurationP52AB(CRioP52AB *pRioP52AB,CDvmData *pData);

    //UpdateDeviceModelByXrioFile
    BOOL UpdateDeviceModelInDvmDataset(CDvmDataset *pSrcDataset,CDvmDataset *pDesDataset);//更新Xrio文件后，在Dataset节点中查找
    BOOL UpdateDeviceModelInDvmData(CDvmData *pSrcDvmData,CDvmData *pDesDvmData);//更新Xrio文件后，在Data节点中查找
    BOOL UpdateDeviceModelInDvmValue(CDvmValue *pSrcDvmValue,CDvmValue *pDesDvmValue);//更新Xrio文件后，在Value节点中查找
    BOOL AddAdditionalAttributes(CDvmValue* pSrcValue,CDvmValue* pDesValue,const CString& strID);
    BOOL AddMultipleValues(CDvmValue* pSrcValue,CDvmValue* pDesValue,const CString& strID);

    //UpdateDeviceModelInRioDevice 更新Xrio文件后，在RIO节点的Device节点中查找
    BOOL UpdateDeviceModelInRioDevice(CDvmDataset *pSrcRioDevice,CDvmDataset *pDesRioDevice);
    BOOL UpdateDeviceModelInRioNameplate(CDvmData *pSrcRioNameplate,CDvmData *pDesRioNameplate);
    BOOL UpdateDeviceModelInRioLocation(CDvmData *pSrcRioLocation,CDvmData *pDesRioLocation);
    BOOL UpdateDeviceModelInRioNominalValues(CDvmData *pSrcRioNominalValues,CDvmData *pDesRioNominalValues);
    BOOL UpdateDeviceModelInRioResidualFactors(CDvmData *pSrcRioResidualFactors,CDvmData *pDesRioResidualFactors);
    BOOL UpdateDeviceModelInRioLimits(CDvmData *pSrcRioLimits,CDvmData *pDesRioLimits);
    BOOL UpdateDeviceModelInRioMisc(CDvmData *pSrcRioMisc,CDvmData *pDesRioMisc);
    //UpdateDeviceModelInRioCBConfig 更新Xrio文件后，在RIO节点的CB节点中查找
    BOOL UpdateDeviceModelInRioCBConfig(CDvmDataset *pSrcRioCBConfig,CDvmDataset *pDesRioCBConfig);
    BOOL UpdateDeviceModelInRioTripTime(CDvmData *pSrcRioTripTime,CDvmData *pDesRioTripTime);
    BOOL UpdateDeviceModelInRioCloseTime(CDvmData *pSrcRioCloseTime,CDvmData *pDesRioCloseTime);
    BOOL UpdateDeviceModelInRioP52AB(CDvmData *pSrcRioP52AB,CDvmData *pDesRioP52AB);

    BOOL IsFatherNode(CExBaseObject*pNode);
    BOOL UpdateOwnAttrVal(const CString& strSrcValue,CString& strDesValue);
    BOOL UpdateDataNode(CDvmData*pSrcDataNode,CDvmData*pDesDataNode);
    BOOL UpdateValueNode(CDvmValue*pSrcValueNode,CDvmValue*pDesValueNode);
    //更新辅助函数
    //该函数指针调用UpdateValue_DataType_Double和UpdateValue_DataType_Int
    typedef BOOL(CXrioToDeviceModelTool::*UPDATE_VALUE_DATATYPE_FUNC)(const CString&, CString&);
    BOOL UpdateAdditionalAttributes(CExBaseList* pSrcList, CExBaseList* pDesList, const CString& strID, BOOL bIsNormal = TRUE, UPDATE_VALUE_DATATYPE_FUNC pFunc = NULL);
    BOOL UpdateEnumerationValues(CExBaseList* pSrcList,CExBaseList* pDesList);
    BOOL UpdateValue_DataType_Double(const CString& strSrcValue ,CString& strDesValue);
    BOOL UpdateValue_DataType_Int(const CString& strSrcValue ,CString& strDesValue);


    BOOL UpdateCustomLogicDeviceObject(CDvmDevice *pSrcDeviceObject, CDvmDevice *pDesDeviceObject,const CString& strID);
    BOOL UpdateRioLogicDeviceObject(CDvmDevice *pSrcDeviceObject, CDvmDevice *pDesDeviceObject,const CString& strID);
    BOOL UpdateRioDatasetObject(CDvmLogicDevice *pSrcLogicDeviceObject,CDvmLogicDevice *pDesLogicDeviceObject,const CString& strID);
    BOOL UpdateRioDatasetObject(CDvmLogicDevice *pSrcLogicDeviceObject,CDvmLogicDevice *pDesLogicDeviceObject);


    BOOL UpdateRioDataObject(CDvmDataset *pSrcDatasetObject,CDvmDataset *pDesDatasetObject,const CString& strID);
    BOOL UpdateRioDeviceValueObject(CDvmData* pSrcDataObject,CDvmData* pDesDataObject,const CString &strID);
    BOOL UpdateRioCBConfigValueObject(CDvmData* pSrcDataObject,CDvmData* pDesDataObject);
};


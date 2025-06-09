#ifndef DISTANCESEARCHCOMMON_H
#define DISTANCESEARCHCOMMON_H

#include "../../../../Module/OSInterface/QT/CString_QT.h"
#include "../../../../Module/BaseClass/ExBaseList.h"

CString DistanceSearchValueCheck(CString strValue,float nMax,float nMin,int nAfterPoint);
void DistanceSearchCheckParaExist(CExBaseList *pParas,CString strID);

/*从特性曲线图测试线添加测试项所需接口
返回值 是否可以添加测试项
参数1 故障类型(LN/LL/LLL)
参数2 起始点横坐标
参数3 起始点纵坐标
参数4 终点横坐标
参数5 终点纵坐标
参数6 首段阻抗数组(传出)
参数7 首段阻抗角数组(传出)
参数8 末端阻抗数组(传出)
参数9 末端阻抗角数组(传出)
参数10 区段数组(传出)
参数11 时间定值数组(传出)
参数12 相对误差数组(传出)
参数13 绝对误差数组(传出)
参数14 误差类型数组(传出)*/
BOOL CalDistanceSearchItemParas(CString strFaultType, double dBegX, double dBegY, double dEndX, double dEndY,
                                QVector<double> &dBegZArr, QVector<double> &dBegAngArr, QVector<double> &EndZArr, QVector<double> &dEndAngArr,
                                QVector<int> &nZoneTypeArr, QVector<double> &dTSettingArr, QVector<double> &dRelErrArr, QVector<double> &dAbsErrArr,
                                QVector<int> &nErrTypeArr);

/*添加系列-快速添加所需接口
返回值 是否可以添加测试项
参数1 故障类型(LN/LL/LLL)
参数2 起始点横坐标
参数3 起始点纵坐标
参数4 直线角度
参数5 首段阻抗数组(传出)
参数6 首段阻抗角数组(传出)
参数7 末端阻抗数组(传出)
参数8 末端阻抗角数组(传出)
参数9 区段数组(传出)
参数10 时间定值数组(传出)
参数11 相对误差数组(传出)
参数12 绝对误差数组(传出)
参数13 误差类型数组(传出)*/
BOOL CalDistanceSearchItemParas(CString strFaultType, double dBegX, double dBegY, double dAng,
                                QVector<double> &dBegZArr, QVector<double> &dBegAngArr, QVector<double> &dEndZArr, QVector<double> &dEndAngArr,
                                QVector<int> &nZoneTypeArr, QVector<double> &dTSettingArr, QVector<double> &dRelErrArr, QVector<double> &dAbsErrArr,
                                QVector<int> &nErrTypeArr);

/*添加系列-添加系列所需接口
返回值 是否可以添加测试项
参数1 故障类型(LN/LL/LLL)
参数2 区段
参数3 起始点横坐标
参数4 起始点纵坐标
参数5 终点横坐标
参数6 终点纵坐标
参数7 首段阻抗(传出)
参数8 首段阻抗角(传出)
参数9 末端阻抗(传出)
参数10 末端阻抗角(传出)
参数11 时间定值数组(传出)
参数12 相对误差数组(传出)
参数13 绝对误差数组(传出)
参数14 误差类型数组(传出)*/
BOOL CalDistanceSearchItemParas(CString strFaultType, int nZoneType, double dBegX, double dBegY, double dEndX, double dEndY,
                                QVector<double> &dBegZArr, QVector<double> &dBegAngArr, QVector<double> &dEndZArr, QVector<double> &dEndAngArr,
                                QVector<double> &dTSettingArr, QVector<double> &dRelErrArr, QVector<double> &dAbsErrArr, QVector<int> &nErrTypeArr);


/*获取测试线和特性曲线交点（理论动作值）
返回值 是否有交点
参数1 故障类型
参数2 区段
参数3 起始点横坐标
参数4 起始点纵坐标
参数5 终点横坐标
参数6 终点纵坐标
参数7 待测阻抗定值(传出)
参数8 待测阻抗角定值(传出)*/
BOOL CalDistanceSearchValSetting(int nFaultType, int nZoneType, double dBegZ, double dBegZAng,
                                 double dEndZ, double dEndZAng, double &dValSetting, double &dValSettingAng);
#endif //DISTANCESEARCHCOMMON_H

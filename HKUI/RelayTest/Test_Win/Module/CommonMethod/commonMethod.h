#ifndef COMMONMETHOND_H
#define COMMONMETHOND_H
#include <QtGui>
#include <QString>
#include <QToolButton>
#include <vector>
#include <cmath>
#include <complex>
#include "../Define.h"
#include "../../../Module/SttTest/Common/tmt_common_def.h"
#include "../../../Module/Engine/SttPowerTestEngineBase.h"

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include<QtWidgets>
#endif

#define SINCOUNT 200000
extern float sinData[SINCOUNT*2+4];
void generagelsinData();

bool ping_ip(QString ip);

//bool cacuIFMAX3000(float fstart,float fend,float fstep);
float getMaxFormThreeValue(float f1,float f2,float f3);
float getMinFormThreeValue(float f1,float f2,float f3);

ErrorType getErrorTypeEnumByIndex(int index);
PTPhase getPTPhaseByIndex(int index); 
QString getErrorTypeStringByEnum(ErrorType type);
QString getErrorTypeResultStringByEnum( ErrorType type );
bool isPosiDigitstr(QString str);
void initToolbutton(QToolButton *btn,QString strName,QString pic_name);
bool ping_ip(QString ip);
void initPositiveIntegerLne(QLineEdit *lne);  //限制正整数
void initPositiveIntegerCombobox(QComboBox *cmb);
void initMaxLineEdit(QLineEdit *lne);       //限制浮点数输入范围为[-999.999.999,999.999.999] 小数点三位默认
void initMaxLineEdit_four(QLineEdit *lne);  //限制浮点数输入范围为[-999.999.9999,999.999.9999] 小数点四位
void initMaxEdit(QLineEdit *lne);   

void initMaxPositiveEdit(QLineEdit *lne);   //限制大于0,三位小数
void initMaxPositiveEdit_Three(QLineEdit *lne);//限制大于0,三位小数
void initMaxPositiveEdit_four(QLineEdit*lne);
void initMaxPositiveCombox(QComboBox *cmb);
void initMaxPositiveCombox_four(QComboBox *cmb);
void initMaxPositiveComboxNoLimit(QComboBox *cmb);

void init360LineEdit(QLineEdit *lne);       //限制-180 +180之间
void initMaxV(QLineEdit* lne);       //电压最大450V 电流最大10A 频率最大5000Hz
void initMaxV(QComboBox *ccmb);
void initMaxI(QLineEdit* lne);
void initMaxI(QComboBox *cmb);
void initMaxHz(QLineEdit *lne);
void initMaxHYL(QLineEdit *lne);
double R180(double val );
double roudVal(double val, double maxV, double minV, double cycle );
double GetAmp( const std::complex<double>& c1 );
double GetAngle( const std::complex<double>& c1 );  // 角度
void Delay_MSec(unsigned int msec);
QString comparaSwitchStatus(int ch[],int ch2[],int num);
QString compareSwitchStatusBynSource(int v);
float setLimit(float min,float max,float val);
float setAngleLimit(float val);
float setAngleLimitEx(float val);//(-360~360) sf 20210805
void initMaxEdit_one(QLineEdit *lne);//0~999.9 一位小数

//递变
para_type getParaTypeByInt(int iVar);
//序分量
Sequence_type getParaTypeByIndex(int iVar);
changed_type getChangeTypeByIndex( int index );

//cl20230921过负荷
DCOverLoad_type getDCCurrTypeByIndex(int index);
OverLoad_type getCurrTypeByIndex(int index);

void LimitAngle360(float &fAngle);
void LimitAngle180(float &fAngle);

//功率、线电压、序分量计算
PowerValue GetPowerValue(bool isDC, tmt_Channel*pUa, tmt_Channel*pUb, tmt_Channel*pUc, tmt_Channel*pIa, tmt_Channel*pIb, tmt_Channel*pIc);

SeqValue GetZeroSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC );
SeqValue GetPositiveSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC );
SeqValue GetNegativeSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC );

CString getDCCurrIndexByType(CString strAPPChID);
CString getDCVolIndexByType(CString strAPPChID);
CString getDCUnbalanceCurrIndexByType(CString strAPPChID);

double roudVal( double val, double maxV, double minV, double cycle );
double R180( double val );

double GetASubBAmp( tmt_Channel*pA, tmt_Channel*pB );
double GetASubBAngle( tmt_Channel*pA, tmt_Channel*pB);

unsigned int GetIntByBits(long arrSwitch[],int nCount);
QString compareSwitchStatusByInput(int nInput);

void CalcPhrasePArr(int nABCSel,float fSelAngle,float *pCalcPhraseArr);
void CalcPhraseNArr(int nABCSel,float fSelAngle,float *pCalcPhraseArr);

//其它
void GetAnalogUIStringList(QStringList &oList,MOUDLEType moduleType);
void GetAnalogUIStringList(int nGroupIndex,int nGroupChNum,QStringList &oList,const QString &strUI);

extern STT_SystemParas g_oSystemParas;
#endif

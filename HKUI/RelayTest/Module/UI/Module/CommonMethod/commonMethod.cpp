#include "stdafx.h"
#include "commonMethod.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"
#include "../../../Module/XLangResource_Native.h"
float sinData[SINCOUNT*2+4];

//
#include "../../../SttTestSysGlobalPara.h"
#ifdef _USE_SoftKeyBoard_
#include "../../SoftKeyboard/SoftKeyBoard.h"
#endif

#include <QProcess>
#include <qmath.h>
#include<QDir>

void generagelsinData()
{
    int nCnt = SINCOUNT*2+2;
    float fVal = 2*pi/SINCOUNT;

    for(int i=0; i<nCnt; i++)
    {
        sinData[i] = sin(i*fVal);
    }
}

bool ping_ip( QString ip )
{
    //ip ="192.168.1.133";
    int exitCode = -1;
#ifdef _TTY_ARMV4_
    QString strArg = "ping -s 1 -c 1 " + ip;       //linux
#else
    QString strArg = "ping " + ip + " -n 1 -i 2";  //windows
#endif

    exitCode = QProcess::execute(strArg);
    if(0 == exitCode)
    {
//		qDebug() << "shell ping " + ip + " sucessed!";
        return true;
    }
    else
    {
//		qDebug() << "shell ping " + ip + " failed!";
        return false;
    }
}

bool isPosiDigitstr( QString str )
{
    QByteArray ba = str.toLatin1();//QString  char*
    const char *s = ba.data();
    int dot = 0;
    int fDigNum = 0;
    while(*s)
    {
        if(*s == '.' && fDigNum != 0)
        {
            if(dot == 0)
            {
                dot++;
                s++;
                continue;
            }
            else
            {
                return false;
            }
        }

        if(*s >='0' && *s<='9')
        {
        }
        else
        {
            return false;
        }
        s++;
        fDigNum++;
    }

    return true;
}

void initToolbutton( QToolButton *btn,QString strName,QString pic_name )
{
    //
    QPalette text_palette = btn->palette();
    text_palette.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    btn->setPalette(text_palette);

    //
    QFont &text_font = const_cast<QFont &>(btn->font());
    text_font.setWeight(QFont::Bold);

    btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    //
    QPixmap pixmap(pic_name);
    btn->setIcon(pixmap);
    btn->setIconSize(pixmap.size());
    btn->setText(strName);

    //С
    btn->setFixedWidth(pixmap.width());
    btn->setAutoRaise(true);

    btn->setStyleSheet("background:transparent;");
}

ErrorType getErrorTypeEnumByIndex( int index )
{
    switch(index)
    {
    case 0:
        {
            return Error_A_JD;
        }
        break;
    case 1:
        {
            return Error_B_JD;
        }
        break;
    case 2:
        {
            return Error_C_JD;
        }
        break;
    case 3:
        {
            return Error_AB_DL;
        }
        break;
    case 4:
        {
            return Error_BC_DL;
        }
        break;
    case 5:
        {
            return Error_CA_DL;
        }
        break;
    case 6:
        {
            return Error_AB_JDDL;
        }
        break;
    case 7:
        {
            return Error_BC_JDDL;
        }
        break;
    case 8:
        {
            return Error_CA_JDDL;
        }
        break;
    case 9:
        {
            return Error_ABC_DL;
        }
        break;
    case 10:
        {
            return Error_SINGLE_ZK;
        }
        break;
    default:
        return Error_A_JD;
        break;
    }
}

QString getErrorTypeStringByEnum( ErrorType type )
{
    QStringList errorTypeList;
// 	errorTypeList<<QObject::tr("A")<<QObject::tr("B")<<QObject::tr("C")<<QObject::tr("AB·")<<QObject::tr("BC·")\
// 		<<QObject::tr("CA·")<<QObject::tr("AB·")<<QObject::tr("BC·")\
// 		<<QObject::tr("CA·")<<QObject::tr("ABC·")<<QObject::tr("迹");
    errorTypeList<<g_sLangTxt_Native_GndA<<g_sLangTxt_Native_GndB<<g_sLangTxt_Native_GndC<<g_sLangTxt_Native_ShortAB<<g_sLangTxt_Native_ShortBC\
        <<g_sLangTxt_Native_ShortCA<<g_sLangTxt_Native_GndShortAB<<g_sLangTxt_Native_GndShortBC\
        <<g_sLangTxt_Native_GndShortCA<<g_sLangTxt_Native_ShortABC<<g_sLangTxt_State_SinglephaseImpedance; //lcq 3.15

    return errorTypeList.at(type);
}

QString getErrorTypeResultStringByEnum( ErrorType type )
{
    QStringList List;
    List<</*QObject::tr("   A ")*/g_sLangTxt_Gradient_JumpA<</*QObject::tr("   B ")*/g_sLangTxt_Gradient_JumpB<</*QObject::tr("   C ")*/g_sLangTxt_Gradient_JumpC<<g_sLangTxt_State_Coincidence<<g_sLangTxt_State_RearAcceleration;//lcq

    return List.at(0);
}

PTPhase getPTPhaseByIndex(int index)
{
    PTPhase t;
    switch(index)
    {
    case 0:
        {
            t = Phase_A;
        }
        break;
    case 1:
        {
            t = Phase_B;
        }
        break;
    case 2:
        {
            t = Phase_C;
        }
        break;
    case 3:
        {
            t = Phase_AB;
        }
        break;
    case 4:
        {
            t = Phase_BC;
        }
        break;
    case 5:
        {
            t = Phase_CA;
        }
        break;
    case 6:
        {
            t = Phase_ABC;
        }
        break;
    default:
        break;
    }

    return t;
}

changed_type getChangeTypeByIndex( int index )
{
    changed_type t;
    switch(index)
    {
    case 0:
        {
            t = amplitude_type;
        }
        break;
    case 1:
        {
            t = phasor_type;
        }
        break;
    case 2:
        {
            t = fre_type;
        }
        break;
    default:
        break;
    }

    return t;
}

void initMaxLineEdit( QLineEdit *lne )
{
    QRegExp rx("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,3})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, lne);
    lne->setValidator(pReg);
}

void initMaxLineEdit_four( QLineEdit *lne )
{
    QRegExp rx("^(-?[0]|-?[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, lne);
    lne->setValidator(pReg);
}

extern void init360LineEdit( QLineEdit *lne )
{
    QRegExp rx("(^-?180$)|(^-?1[0-7]\\d$)|(^-?[1-9]\\d$)|(^-?[1-9]$)|^0$");
    QRegExpValidator *pReg = new QRegExpValidator(rx, lne);
    lne->setValidator(pReg);
}

extern void initMaxPositiveEdit( QLineEdit *lne )
{
    QRegExp rx("^[|0-9|(.)]{1,16}|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, lne);
    lne->setValidator(pReg);
}

extern void initMaxEdit(QLineEdit *lne)
{
    QRegExp rx("^[-|0-9|(.)]{1,16}|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, lne);
    lne->setValidator(pReg);
}

extern void initMaxPositiveCombox( QComboBox *cmb )
{
    QRegExp rx("^([0]|[1-9][0-9]{0,5})(?:\\.\\d{1,3})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, cmb);
    cmb->setValidator(pReg);
}

extern void initMaxPositiveEdit_Three(QLineEdit *lne)
{
    QRegExp rx("^([0]|[1-9][0-9]{0,5})(?:\\.\\d{1,3})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, lne);
    lne->setValidator(pReg);
}

extern void initMaxPositiveEdit_four( QLineEdit*lne )
{
    QRegExp rx("^([0]|[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, lne);
    lne->setValidator(pReg);
}

extern void initMaxPositiveCombox_four( QComboBox *cmb )
{
    QRegExp rx("^([0]|[1-9][0-9]{0,5})(?:\\.\\d{1,4})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, cmb);
    cmb->setValidator(pReg);
}

extern void initMaxPositiveComboxNoLimit(QComboBox *cmb)
{
    QRegExp rx("^([0]|[1-9][0-9]{0,5})(?:\\.\\d{1,9})?$|(^\\t?$)");
    QRegExpValidator *pReg = new QRegExpValidator(rx, cmb);
    cmb->setValidator(pReg);
}

extern void initPositiveIntegerLne( QLineEdit *lne )
{
    QValidator* validator = new QIntValidator( 1, 99999, lne );
    lne->setValidator( validator );
}

extern void initPositiveIntegerCombobox( QComboBox *cmb )
{
    QValidator* validator = new QIntValidator( 1, 99999, cmb );
    cmb->setValidator( validator );
}

void initMaxV(QLineEdit* lne)       //450V 10A 5000Hz
{
    if (lne->text().toFloat() >=450)
    {
        lne->setText("450");
    }
}

void initMaxV(QComboBox *cmb)
{
    if (cmb->currentText().toFloat() >= 450)
    {
        cmb->setEditText("450");
    }
}

void initMaxI(QLineEdit* lne)
{
    if (lne->text().toFloat() >=10)
    {
        lne->setText("10");
    }
}

void initMaxI(QComboBox *cmb)
{
    if (cmb->currentText().toFloat() >= 10)
    {
        cmb->setEditText("10");
    }
}

void initMaxHz(QLineEdit *lne)
{
    if (lne->text().toFloat() >=60)
    {
        lne->setText("60");
    }
}

void initMaxHYL(QLineEdit *lne)
{
    if (lne->text().toFloat() >=40)
    {
        lne->setText("40");
    }
}

double roudVal(double val, double maxV, double minV, double cycle )
{
    while ( val > maxV )
    {
        val = val - cycle;
    }
    while ( val < minV )
    {
        val = val + cycle;
    }
    return val;
}

double R180(double val )
{
    return roudVal( val, 180, -180, 360);
}

double GetAmp( const std::complex<double>& c1 )
{
    return qSqrt( c1.imag()*c1.imag() + c1.real()*c1.real() );
}

double GetAngle( const std::complex<double>& c1 )
{
    double PI = 3.1415926;
    if ( c1.real() == 0  )
    {
        if ( c1.imag() > 0 )
        {
            return 90;
        }
        else if (c1.imag() < 0 )
        {
            return -90;
        }
        else
        {
            return 0;
        }
    }
    else if ( c1.imag() == 0  )
    {
        if ( c1.real() >= 0 )
        {
            return 0;
        }
        else if (c1.real() < 0 )
        {
            return -180;
        }
    }
    else if ( c1.real()  > 0 )
    {
        return qAtan( c1.imag()/c1.real()  )*180/PI;
    }
    return R180( qAtan( c1.imag()/c1.real() )*180/PI + 180 ) ;
}

/*
extern bool cacuIFMAX3000( float fstart,float fend,float fstep )
{
    if ((int)(fabs(fstart-fend)/fstep) > 3000)
    {
        //emit sig_AddLog(LEVEL_WARN,tr("3000"));
        return false;
    }
    else
    {
        //emit sig_AddLog(LEVEL_COMMON,tr(""));
        return true;
    }
}
*/

extern float getMaxFormThreeValue( float f1,float f2,float f3 )
{
    float max;
    if( f1>f2)    max = f1;
    else        max = f2;
    if( f3>max)  max = f3;

    return max;
}

extern float getMinFormThreeValue( float f1,float f2,float f3 )
{
    float min;
    if( f1<f2)    min = f1;
    else        min = f2;
    if( f3<min)  min = f3;

    return min;
}

// void Delay_MSec(unsigned int msec)  //zhouhj 2-24.5.6 delete
// {
// 	QTime _Timer = QTime::currentTime().addMSecs(msec);
// 	while( QTime::currentTime() < _Timer )
// 		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
// }

extern QString comparaSwitchStatus( int ch[],int ch2[],int num )
{
    int a[10];
    int b[10];
    for (int i=0;i<num;i++)
    {
        a[i] = *ch;
        b[i] = *ch2;
        ch++;
        ch2++;
    }
    QString str;

    if (b[0] != a[0])
    {
        str = /*QObject::tr("A")*/g_sLangTxt_Gradient_Jjump + 'A'; //lcq
        return str;
    }

    if (b[1] != a[1])
    {
        str = /*QObject::tr("B")*/g_sLangTxt_Gradient_Jjump + 'B';//lcq
        return str;
    }

    if (b[2] != a[2])
    {
        str = /*QObject::tr("C")*/g_sLangTxt_Gradient_Jjump + 'C';//lcq
        return str;
    }

    if (b[3] != a[3])
    {
        str = /*QObject::tr("D")*/g_sLangTxt_Gradient_Jjump + 'D'; //lcq
        return str;
    }

    if (b[4] != a[4])
    {
        str = /*QObject::tr("E")*/g_sLangTxt_Gradient_Jjump + 'E'; //lcq
        return str;
    }

    if (b[5] != a[5])
    {
        str = /*QObject::tr("F")*/g_sLangTxt_Gradient_Jjump + 'F'; //lcq
        return str;
    }

    if (b[5] != a[5])
    {
        str = /*QObject::tr("G")*/g_sLangTxt_Gradient_Jjump + 'G'; //lcq
        return str;
    }

    if (b[6] != a[6])
    {
        str = /*QObject::tr("H")*/g_sLangTxt_Gradient_Jjump + 'H'; //lcq
        return str;
    }

    if (b[7] != a[7])
    {
        str = /*QObject::tr("I")*/g_sLangTxt_Gradient_Jjump + 'I'; //lcq
        return str;
    }

    if (b[8] != a[8])
    {
        str = /*QObject::tr("J")*/g_sLangTxt_Gradient_Jjump + 'J';//lcq
        return str;
    }

    if (b[9] != a[9])
    {
        str = /*QObject::tr("K")*/g_sLangTxt_Gradient_Jjump + 'K'; //lcq
        return str;
    }

    return "";

}

extern QString compareSwitchStatusBynSource( int v )
{
    QString tempStr[10];
    QString str;
    int ch2[32];
    for (int k=0;k<32;k++)
    {
        ch2[k] = -1;
    }

    for ( int k=31; k>=0; k-- )
    {
        ch2[k] = (v&0x80000000)==0?0:1;
        v = v<<1;
    }

    if (ch2[0] == 1)
    {
        str = /*QObject::tr("A")*/g_sLangTxt_Gradient_Jjump + 'A'; //lcq
        tempStr[0] = str;
    }

    if (ch2[1] == 1)
    {
        str = /*QObject::tr("B")*/g_sLangTxt_Gradient_Jjump + 'B'; //lcq
        tempStr[1] = str;
    }

    if (ch2[2] == 1)
    {
        str = /*QObject::tr("C")*/g_sLangTxt_Gradient_Jjump + 'C'; //lcq
        tempStr[2] = str;
    }

    if (ch2[3] == 1)
    {
        str = /*QObject::tr("D")*/g_sLangTxt_Gradient_Jjump + 'D'; //lcq
        tempStr[3] = str;
    }

    if (ch2[4] == 1)
    {
        str = /*QObject::tr("E")*/g_sLangTxt_Gradient_Jjump + 'E'; //lcq
        tempStr[4] = str;
    }

    if (ch2[5] == 1)
    {
        str = /*QObject::tr("F")*/g_sLangTxt_Gradient_Jjump + 'F'; //lcq
        tempStr[5] = str;
    }

    if (ch2[6] == 1)
    {
        str = /*QObject::tr("G")*/g_sLangTxt_Gradient_Jjump + 'G'; //lcq
        tempStr[6] = str;
    }

    if (ch2[7] == 1)
    {
        str = /*QObject::tr("H")*/g_sLangTxt_Gradient_Jjump + 'H'; //lcq
        tempStr[7] = str;
    }

    if (ch2[8] == 1)
    {
        str = /*QObject::tr("I")*/g_sLangTxt_Gradient_Jjump + 'I'; //lcq
        tempStr[8] = str;
    }

    if (ch2[9] == 1)
    {
        str = /*QObject::tr("J")*/g_sLangTxt_Gradient_Jjump + 'J'; //lcq
        tempStr[9] = str;
    }
    str.clear();
    for (int i = 0;i<10;i++)
    {
        if (tempStr[i]!="")
        {
            if (str=="")
            {
                str.append(tempStr[i]);
            }
            else
            {
                str.append(",");
                str.append(tempStr[i]);
            }
        }
    }

    return str;
}

float setLimit(float min,float max,float val)
{
    if (val<min)
    {
        val = min;
    }
    else if (val>max)
    {
        val = max;
    }
    return val;
}

float setAngleLimit(float val)
{
    if (val<0)
    {
        val = 0;
    }
    else if (val>360)
    {
        val = val-(int)(val/360)*360;
    }
    return val;
}
float setAngleLimitEx(float val)
{
    if (val<0)
    {
        val = val+(int)((-val)/360)*360;
    }
    else if (val>360)
    {
        val = val-(int)(val/360)*360;
    }
    return val;
}

extern void initMaxEdit_one(QLineEdit *lne)
{
    QDoubleValidator *pDoubleValidator = new QDoubleValidator(0,999.9,1,lne);
    pDoubleValidator->setNotation(QDoubleValidator::StandardNotation);
    lne->setValidator(pDoubleValidator);
}

// float GetLowAcVMax(bool bMin)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSVModuleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSVoltPT1MaxList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSVModuleNum;i++)
// 		{
// 			if (bMin)
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSVoltPT1MaxList[i]);
// 			}
// 			else
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSVoltPT1MaxList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
//
// float GetLowAcIMax(bool bMin)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSIMoudleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSCurrCT1MaxList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSIMoudleNum;i++)
// 		{
// 			if (bMin)
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSCurrCT1MaxList[i]);
// 			}
// 			else
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSCurrCT1MaxList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
//
// float GetLowAcVMin(bool bMax)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSVModuleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSVoltPT1MinList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSVModuleNum;i++)
// 		{
// 			if (bMax)
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSVoltPT1MinList[i]);
// 			}
// 			else
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSVoltPT1MinList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
//
// float GetLowAcIMin(bool bMax)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSIMoudleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSCurrCT1MinList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSIMoudleNum;i++)
// 		{
// 			if (bMax)
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSCurrCT1MinList[i]);
// 			}
// 			else
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSCurrCT1MinList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
//
// float GetLowAcZeroVMax(bool bMin)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSVModuleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSZeroVoltPT1MaxList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSVModuleNum;i++)
// 		{
// 			if (bMin)
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSZeroVoltPT1MaxList[i]);
// 			}
// 			else
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSZeroVoltPT1MaxList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
//
// float GetLowAcZeroIMax(bool bMin)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSIMoudleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSZeroCurrCT1MaxList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSIMoudleNum;i++)
// 		{
// 			if (bMin)
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSZeroCurrCT1MaxList[i]);
// 			}
// 			else
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSZeroCurrCT1MaxList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
//
// float GetLowAcZeroVMin(bool bMax)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSVModuleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSZeroVoltPT1MinList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSVModuleNum;i++)
// 		{
// 			if (bMax)
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSZeroVoltPT1MinList[i]);
// 			}
// 			else
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSZeroVoltPT1MinList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
//
// float GetLowAcZeroIMin(bool bMax)
// {
// 	float fv = 0;
// 	if(g_oLocalSysPara.LowSIMoudleNum > 0)
// 	{
// 		fv = g_oLocalSysPara.LowSZeroCurrCT1MinList[0];
// 		for (int i=1;i<g_oLocalSysPara.LowSIMoudleNum;i++)
// 		{
// 			if (bMax)
// 			{
// 				fv = max(fv,g_oLocalSysPara.LowSZeroCurrCT1MinList[i]);
// 			}
// 			else
// 			{
// 				fv = min(fv,g_oLocalSysPara.LowSZeroCurrCT1MinList[i]);
// 			}
// 		}
// 	}
//
// 	return fv;
// }
Sequence_type getParaTypeByIndex(int iVar)
{
    Sequence_type type=v11_type;
    switch(iVar)
    {
    case 0:
        type = v11_type;
        break;
    case 1:
        type = v12_type;
        break;
    case 2:
        type = v10_type;
        break;
    case 3:
        type = v21_type;
        break;
    case 4:
        type = v22_type;
        break;
    case 5:
        type = v20_type;
        break;
    case 6:
        type = i11_type;
        break;
    case 7:
        type = i12_type;
        break;
    case 8:
        type = i10_type;
        break;
    case 9:
        type = i21_type;
        break;
    case 10:
        type = i22_type;
        break;
    case 11:
        type = i20_type;
        break;
    default:
        break;
    }

    return type;
}

LineVolt_type getParaTypeByVIndex(int iVar)
{
    LineVolt_type type=LineVolt_vab1_type;
    switch(iVar)
    {
    case 0:
        type = LineVolt_vab1_type;
        break;
    case 1:
        type = LineVolt_v1_0_type;
        break;
    case 2:
        type = LineVolt_vab2_type;
        break;
    case 3:
        type = LineVolt_v2_0_type;
        break;
    case 4:
        type = LineVolt_ia1_type;
        break;
    case 5:
        type = LineVolt_ib1_type;
        break;
    case 6:
        type = LineVolt_ic1_type;
        break;
    case 7:
        type = LineVolt_ia2_type;
        break;
    case 8:
        type = LineVolt_ib2_type;
        break;
    case 9:
        type = LineVolt_ic2_type;
        break;
    case 10:
        type = LineVolt_iabc1_type;
        break;
    case 11:
        type = LineVolt_iabc2_type;
        break;
    default:
        break;
    }

    return type;
}

para_type getParaTypeByInt(int iVar)
{
    para_type type = va1_type;
    switch(iVar)
    {
    case 0:
        type = va1_type;
        break;
    case 1:
        type = vb1_type;
        break;
    case 2:
        type = vc1_type;
        break;
    case 4:
        type = vab1_type;
        break;
    case 5:
        type = vbc1_type;
        break;
    case 6:
        type = vca1_type;
        break;
    case 7:
        type = vabc1_type;
        break;
    case 8:
        type = va2_type;
        break;
    case 9:
        type = vb2_type;
        break;
    case 10:
        type = vc2_type;
        break;
    case 11:
        type = vabc2_type;
        break;
    case 12:
        type = ia1_type;
        break;
    case 13:
        type = ib1_type;
        break;
    case 14:
        type = ic1_type;
        break;
    case 15:
        type = iab1_type;
        break;
    case 16:
        type = ibc1_type;
        break;
    case 17:
        type = ica1_type;
        break;
    case 18:
        type = iabc1_type;
        break;
    case 19:
        type = ia2_type;
        break;
    case 20:
        type = ib2_type;
        break;
    case 21:
        type = ic2_type;
        break;
    case 22:
        type = iabc2_type;
        break;
    case 23:
        type = vall_type;
        break;
    case 24:
        type = iall_type;
        break;
    case 25:
        type = vdc_type;
        break;
    case 26:
        type = vz_type;
        break;
    case 27:
        type = vab2_type;
        break;
    case 28:
        type = vbc2_type;
        break;
    case 29:
        type = vca2_type;
        break;
    case 30:
        type = iab2_type;
        break;
    case 31:
        type = ibc2_type;
        break;
    case 32:
        type = ica2_type;
        break;
    case 33:
        type = iabcAdd_type;
        break;
    case 34:
        type = ia2b2c2Add_type;
        break;
    case 35:
        type = vabcAdd_type;
        break;
    case 36:
        type = va2b2c2Add_type;
        break;
    case 37:
        type = freAll_type;
        break;
    case 38:
        type = iaia2Add_type;
        break;
    case 39:
        type = ibib2Add_type;
        break;
    case 40:
        type = icic2Add_type;
        break;
    case 41:
        type = iaia2Add_ibib2Add_icic2Add_type;
        break;
    case 42:
        type = iaia2ibib2icic2Add_type;
        break;
    default:
        break;
    }

    return type;
}

void LimitAngle360(float &fAngle)
{
// 	if (fAngle >= 360)
// 	{
// 		fAngle = 360;
// 	}
//
// 	if (fAngle  < -360)
// 	{
// 		fAngle = -360;
// 	}
// 	return;

    if ((fAngle>36000000)||(fAngle<-36000000))
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("λ(%f).")*/g_sLangTxt_Gradient_CurPhaseErr.GetString(),fAngle); //lcq
        fAngle = 0;
        return;
    }

    while(fAngle < 0)
    {
        fAngle += 360;
    }
    while(fAngle >= 360)
    {
        fAngle -= 360;
    }
}

void LimitAngle180(float &fAngle)
{
// 	if (fAngle >= 360)
// 	{
// 		fAngle = 360;
// 	}
//
// 	if (fAngle  < -360)
// 	{
// 		fAngle = -360;
// 	}
// 	return;

    if ((fAngle>36000000)||(fAngle<-36000000))
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("λ(%f).")*/g_sLangTxt_Gradient_CurPhaseErr.GetString(),fAngle); //lcq
        fAngle = 0;
        return;
    }

    while(fAngle < -180)
    {
        fAngle += 360;
    }
    while(fAngle >= 180)
    {
        fAngle -= 360;
    }
}

//
PowerValue GetPowerValue(bool isDC, tmt_Channel*pUa, tmt_Channel*pUb, tmt_Channel*pUc, tmt_Channel*pIa, tmt_Channel*pIb, tmt_Channel*pIc)
{
    PowerValue ret = {0};

    if ( !isDC )
    {
        ret.FactorA = qCos( (pUa->Harm[1].fAngle - pIa->Harm[1].fAngle )*pi/180 );
        ret.FactorB = qCos( (pUb->Harm[1].fAngle - pIb->Harm[1].fAngle )*pi/180 );
        ret.FactorC = qCos( (pUc->Harm[1].fAngle - pIc->Harm[1].fAngle )*pi/180 );

        ret.PA = pUa->Harm[1].fAmp*pIa->Harm[1].fAmp*ret.FactorA;
        ret.PB = pUb->Harm[1].fAmp*pIb->Harm[1].fAmp*ret.FactorB;
        ret.PC = pUc->Harm[1].fAmp*pIc->Harm[1].fAmp*ret.FactorC;
        ret.PSum = ret.PA + ret.PB + ret.PC;

        ret.QA = pUa->Harm[1].fAmp*pIa->Harm[1].fAmp*qSin( (pUa->Harm[1].fAngle - pIa->Harm[1].fAngle )*pi/180 );
        ret.QB = pUb->Harm[1].fAmp*pIb->Harm[1].fAmp*qSin( (pUb->Harm[1].fAngle - pIb->Harm[1].fAngle )*pi/180 );
        ret.QC = pUc->Harm[1].fAmp*pIc->Harm[1].fAmp*qSin( (pUc->Harm[1].fAngle - pIc->Harm[1].fAngle )*pi/180 );
        ret.QSum = ret.QA + ret.QB + ret.QC;

        ret.SA = pUa->Harm[1].fAmp*pIa->Harm[1].fAmp;
        ret.SB = pUb->Harm[1].fAmp*pIb->Harm[1].fAmp;
        ret.SC = pUc->Harm[1].fAmp*pIc->Harm[1].fAmp;
        ret.SSum = ret.SA + ret.SB + ret.SC;
    }
    else
    {
        ret.FactorA = 1;
        ret.FactorB = 1;
        ret.FactorC = 1;

        ret.PA = pUa->Harm[1].fAmp*pIa->Harm[1].fAmp*ret.FactorA;
        ret.PB = pUb->Harm[1].fAmp*pIb->Harm[1].fAmp*ret.FactorB;
        ret.PC = pUc->Harm[1].fAmp*pIc->Harm[1].fAmp*ret.FactorC;
        ret.PSum = ret.PA + ret.PB + ret.PC;

        ret.QA = pUa->Harm[1].fAmp*pIa->Harm[1].fAmp*0;
        ret.QB = pUb->Harm[1].fAmp*pIb->Harm[1].fAmp*0;
        ret.QC = pUc->Harm[1].fAmp*pIc->Harm[1].fAmp*0;
        ret.QSum = ret.QA + ret.QB + ret.QC;

        ret.SA = pUa->Harm[1].fAmp*pIa->Harm[1].fAmp;
        ret.SB = pUb->Harm[1].fAmp*pIb->Harm[1].fAmp;
        ret.SC = pUc->Harm[1].fAmp*pIc->Harm[1].fAmp;
        ret.SSum = ret.SA + ret.SB + ret.SC;
    }

    return ret;
}

SeqValue GetZeroSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC )
{
    std::complex<double> a1( pA->Harm[1].fAmp*qCos( pA->Harm[1].fAngle*pi/180), pA->Harm[1].fAmp*qSin( pA->Harm[1].fAngle*pi/180) );
    std::complex<double> b1( pB->Harm[1].fAmp*qCos( pB->Harm[1].fAngle*pi/180), pB->Harm[1].fAmp*qSin( pB->Harm[1].fAngle*pi/180) );
    std::complex<double> c1( pC->Harm[1].fAmp*qCos( pC->Harm[1].fAngle*pi/180), pC->Harm[1].fAmp*qSin( pC->Harm[1].fAngle*pi/180) );
    std::complex<double> result = (a1 + b1 + c1)/3.0;
    SeqValue ret = {0};
    ret.amp = GetAmp(result);
    ret.phase = GetAngle(result);
    return ret;
}

SeqValue GetPositiveSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC )
{
    const  std::complex<double> alpha( qCos( 120*pi/180), qSin( 120*pi/180));

    std::complex<double> a1( pA->Harm[1].fAmp*qCos( pA->Harm[1].fAngle*pi/180), pA->Harm[1].fAmp*qSin( pA->Harm[1].fAngle*pi/180) );
    std::complex<double> b1( pB->Harm[1].fAmp*qCos( pB->Harm[1].fAngle*pi/180), pB->Harm[1].fAmp*qSin( pB->Harm[1].fAngle*pi/180) );
    std::complex<double> c1( pC->Harm[1].fAmp*qCos( pC->Harm[1].fAngle*pi/180), pC->Harm[1].fAmp*qSin( pC->Harm[1].fAngle*pi/180) );
    std::complex<double> result = (a1 + alpha*b1 + alpha*alpha*c1)/3.0;
    SeqValue ret = {0};
    ret.amp = GetAmp(result);
    ret.phase = GetAngle(result);
    return ret;
}

SeqValue GetNegativeSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC )
{
    const  std::complex<double> alpha( qCos( 120*pi/180), qSin( 120*pi/180));
    std::complex<double> a1( pA->Harm[1].fAmp*qCos( pA->Harm[1].fAngle*pi/180), pA->Harm[1].fAmp*qSin( pA->Harm[1].fAngle*pi/180) );
    std::complex<double> b1( pB->Harm[1].fAmp*qCos( pB->Harm[1].fAngle*pi/180), pB->Harm[1].fAmp*qSin( pB->Harm[1].fAngle*pi/180) );
    std::complex<double> c1( pC->Harm[1].fAmp*qCos( pC->Harm[1].fAngle*pi/180), pC->Harm[1].fAmp*qSin( pC->Harm[1].fAngle*pi/180) );
    std::complex<double> result = (a1 + alpha*alpha*b1 + alpha*c1)/3.0;
    SeqValue ret = {0};
    ret.amp = GetAmp(result);
    ret.phase = GetAngle(result);
    return ret;
}

double GetASubBAngle( tmt_Channel*pA, tmt_Channel*pB )
{
    double PI = 3.1415926;
    std::complex<double> a1( pA->Harm[1].fAmp*qCos( pA->Harm[1].fAngle*pi/180), pA->Harm[1].fAmp*qSin( pA->Harm[1].fAngle*pi/180) );
    std::complex<double> b1( pB->Harm[1].fAmp*qCos( pB->Harm[1].fAngle*pi/180), pB->Harm[1].fAmp*qSin( pB->Harm[1].fAngle*pi/180) );
    std::complex<double> c1 = a1 - b1;
    return GetAngle(c1 );
}

double  GetASubBAmp( tmt_Channel*pA, tmt_Channel*pB )
{
    double PI = 3.1415926;
    std::complex<double> a1( pA->Harm[1].fAmp*qCos( pA->Harm[1].fAngle*pi/180), pA->Harm[1].fAmp*qSin( pA->Harm[1].fAngle*pi/180) );
    std::complex<double> b1( pB->Harm[1].fAmp*qCos( pB->Harm[1].fAngle*pi/180), pB->Harm[1].fAmp*qSin( pB->Harm[1].fAngle*pi/180) );
    std::complex<double> c1 = a1 - b1;
    return GetAmp( c1);
}

unsigned int GetIntByBits(long arrSwitch[],int nCount)
{
    unsigned int tempBits = 0;
    for (int i=0;i<nCount;i++)
    {
        if (arrSwitch[i]==1)
        {
            tempBits |= (1<<i);
        }
    }

    return tempBits;
}

QString compareSwitchStatusByInput(int nInput)
{
    QString str="";
    QString tempStr[8];
;
    int ch[32];
    for (int k=0;k<32;k++)
    {
        ch[k] = -1;
    }

    for ( int k=31; k>=0; k-- )
    {
        ch[k] = (nInput&0x80000000)==0?0:1;
        nInput = nInput<<1;
    }

    if (ch[0] == 1)
    {
        tempStr[0] = /*QObject::tr("A")*/g_sLangTxt_Gradient_Jjump + 'A';
    }

    if (ch[1] == 1)
    {
        tempStr[1] = /*QObject::tr("B")*/g_sLangTxt_Gradient_Jjump + 'B';
    }

    if (ch[2] == 1)
    {
        tempStr[2] = /*QObject::tr("C")*/g_sLangTxt_Gradient_Jjump + 'C';
    }

    if (ch[3] == 1)
    {
        tempStr[3] = /*QObject::tr("D")*/g_sLangTxt_Gradient_Jjump + 'D';
    }

    if (ch[4] == 1)
    {
        tempStr[4] = /*QObject::tr("E")*/g_sLangTxt_Gradient_Jjump + 'E';
    }

    if (ch[5] == 1)
    {
        tempStr[5] = /*QObject::tr("F")*/g_sLangTxt_Gradient_Jjump + 'F';
    }

    if (ch[6] == 1)
    {
        tempStr[6] = /*QObject::tr("G")*/g_sLangTxt_Gradient_Jjump + 'G';
    }

    if (ch[7] == 1)
    {
        tempStr[7] = /*QObject::tr("H")*/g_sLangTxt_Gradient_Jjump + 'H';
    }

    str.clear();
    for (int i = 0;i<8;i++)
    {
        if (tempStr[i]!="")
        {
            if (str=="")
            {
                str.append(tempStr[i]);
            }
            else
            {
                str.append(",");
                str.append(tempStr[i]);
            }

        }
    }

    return str;
}

void CalcPhrasePArr(int nABCSel,float fSelAngle,float *pCalcPhraseArr)
{//
    float fVal1 = 0,fVal2 = 0;
    switch(nABCSel)
    {
    case 0:
        fVal1 = fSelAngle-120;
        fVal2 = fSelAngle+120;
        LimitAngle180(fVal1);
        LimitAngle180(fVal2);
        pCalcPhraseArr[0] = fSelAngle;
        pCalcPhraseArr[1] = fVal1;
        pCalcPhraseArr[2] = fVal2;
        break;
    case 1:
        fVal1 = fSelAngle+120;
        fVal2 = fSelAngle+240;
        LimitAngle180(fVal1);
        LimitAngle180(fVal2);
        pCalcPhraseArr[0] = fVal1;
        pCalcPhraseArr[1] = fSelAngle;
        pCalcPhraseArr[2] = fVal2;
        break;
    case 2:
        fVal1 = fSelAngle-120;
        fVal2 = fSelAngle-240;
        LimitAngle180(fVal1);
        LimitAngle180(fVal2);
        pCalcPhraseArr[0] = fVal1;
        pCalcPhraseArr[1] = fVal2;
        pCalcPhraseArr[2] = fSelAngle;
        break;
    default:
        break;
    }
}

void CalcPhraseNArr(int nABCSel,float fSelAngle,float *pCalcPhraseArr)
{
    float fVal1 = 0,fVal2 = 0;
    switch(nABCSel)
    {
    case 0:
        fVal1 = fSelAngle+120;
        fVal2 = fSelAngle-120;
        LimitAngle180(fVal1);
        LimitAngle180(fVal2);
        pCalcPhraseArr[0] = fSelAngle;
        pCalcPhraseArr[1] = fVal1;
        pCalcPhraseArr[2] = fVal2;
        break;
    case 1:
        fVal1 = fSelAngle-120;
        fVal2 = fSelAngle-240;
        LimitAngle180(fVal1);
        LimitAngle180(fVal2);
        pCalcPhraseArr[0] = fVal1;
        pCalcPhraseArr[1] = fSelAngle;
        pCalcPhraseArr[2] = fVal2;
        break;
    case 2:
        fVal1 = fSelAngle+120;
        fVal2 = fSelAngle+240;
        LimitAngle180(fVal1);
        LimitAngle180(fVal2);
        pCalcPhraseArr[0] = fVal1;
        pCalcPhraseArr[1] = fVal2;
        pCalcPhraseArr[2] = fSelAngle;
        break;
    default:
        break;
    }
}

// void GetAnalogUIStringList(QStringList &oList,MOUDLEType moduleType)
// {
// 	CExBaseList* pChDatas = NULL;
// 	CExBaseObject *pCh = NULL;
// 	ASSERT(g_oSttTestResourceMngr.m_pTestResouce != NULL);
//
// 	oList.clear();
// 	if (moduleType == Moudle_U)
// 	{
// 		pChDatas = &g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef;
// 	}
// 	else if (moduleType == Moudle_I)
// 	{
// 		pChDatas = &g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef;
// 	}
//
// 	if (pChDatas && pChDatas->GetCount()>0)
// 	{
// 		POS pos = pChDatas->GetHeadPosition();
// 		while(pos)
// 		{
// 			pCh = pChDatas->GetNext(pos);
// 			oList.append(pCh->m_strName);
// 		}
// 	}
// }
//
// void GetAnalogUIStringList(int nGroupIndex,int nGroupChNum,QStringList &oList,const QString &strUI)
// {
// 	if (nGroupIndex == 0)
// 	{
// 		switch(nGroupChNum)
// 		{
// 		case 1:
// 			oList<< QString("%1a").arg(strUI);
// 			break;
// 		case 2:
// 			oList<< QString("%1a").arg(strUI)<< QString("%1b").arg(strUI);
// 			break;
// 		case 3:
// 			oList<< QString("%1a").arg(strUI)<< QString("%1b").arg(strUI)<< QString("%1c").arg(strUI);
// 			break;
// 		case 4:
// 			oList<< QString("%1a").arg(strUI)<< QString("%1b").arg(strUI)<< QString("%1c").arg(strUI);
// 			if (strUI == "U")
// 			{
// 				oList<< "Uz";
// 			}
// 			else
// 			{
// 				oList<< "I0";
// 			}
// 			break;
// 		default:
// 			{
// 				for(int i=1; i<= nGroupChNum; i++)
// 				{
// 					oList << QString("%1%2").arg(strUI).arg(i);
// 				}
// 				break;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		switch(nGroupChNum)
// 		{
// 		case 1:
// 			oList<< QString("%1a%2").arg(strUI).arg(nGroupIndex);
// 			break;
// 		case 2:
// 			oList<< QString("%1a%2").arg(strUI).arg(nGroupIndex)<< QString("%1b%2").arg(strUI).arg(nGroupIndex);
// 			break;
// 		case 3:
// 			oList<< QString("%1a%2").arg(strUI).arg(nGroupIndex)<< QString("%1b%2").arg(strUI).arg(nGroupIndex)<< QString("%1c%2").arg(strUI).arg(nGroupIndex);
// 			break;
// 		case 4:
// 			oList<< QString("%1a%2").arg(strUI).arg(nGroupIndex)<< QString("%1b%2").arg(strUI).arg(nGroupIndex)<< QString("%1c%2").arg(strUI).arg(nGroupIndex);
// 			if (strUI == "U")
// 			{
// 				oList<< QString("Uz%1").arg(nGroupIndex);
// 			}
// 			else
// 			{
// 				oList<< QString("I0%1").arg(nGroupIndex);
// 			}
// 			break;
// 		default:
// 			{
// 				for(int i=1; i<= nGroupChNum; i++)
// 				{
// 					oList << QString("I%1%1").arg(i).arg(nGroupIndex);
// 				}
// 				break;
// 			}
// 		}
// 	}
// }


void CreateKeyBoardWidget()
{
#ifdef _USE_SoftKeyBoard_
    if(g_pSoftKeyBoard == NULL)
    {
        g_pSoftKeyBoard = new QSoftKeyBoard;
    }
#endif

}

void ReleaseKeyboardWidget()
{
#ifdef _USE_SoftKeyBoard_
    if(g_pSoftKeyBoard)
    {
        delete g_pSoftKeyBoard;
        g_pSoftKeyBoard = NULL;
    }
#endif
}

void ExitHideKeyboardWidget()
{

}

void GetWidgetBoard_DigitData(long nType,QString& strText,CCommonCtrlInterface *pCommonCtrl,QWidget *parent,int bTableWidget)
{
#ifdef _USE_SoftKeyBoard_
    if(nType == 4)
    {
        QSoftKeyBoard::DisableUserFunc();
    }
#endif

}

void GetWidgetBoard_DigitData(long nType,QString& strText,QWidget *parent)
{

}

void Global_SoftKeyBoardAttachObj(QWidget *pParentWidget,long nKeyBoardType)
{
#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::AttachObj(pParentWidget,(Keyboard::tagMode)nKeyBoardType);
#endif
}

//
void GetEngWidgetBoard_DigitData(QString& strText,QWidget *parent)
{
#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::SetLanguageKeyboard();
#endif
}

void GetChsWidgetBoard_DigitData(QString& strText, QWidget *parent, QRect rc)
{
#ifdef _USE_SoftKeyBoard_
    QSoftKeyBoard::SetLanguageKeyboard();
#endif
}

CString Global_GetSaveAsRootPath()
{
    CString strPath;

    if (Global_GetUsbRootFolderPath(strPath))
    {
        return strPath;
    }

    strPath = _P_GetLibraryPath();
    return strPath;
}

//#define _PSX_OS_CENTOS_

BOOL Global_GetUsbRootFolderPath(CString &strUsbRootFolderPath)
{
#ifdef _PSX_QT_LINUX_
    CString strPath,strTmpFolderFileName,strTmpFolderPath;
    CString strAbsFolderPath;
#ifdef _PSX_OS_CENTOS_
    strAbsFolderPath = "/run/media/root/";
#else
    strAbsFolderPath = _P_GetSystemPath();
    strAbsFolderPath += "Usb/";
#endif
    QDir dir(strAbsFolderPath);

    //filesб
    QStringList astrChildFolders,atrFolderFilters,astrTmp;
    astrChildFolders = dir.entryList(atrFolderFilters, QDir::Dirs| QDir::NoDotAndDotDot);

    if(astrChildFolders.size() == 0)
    {
        return FALSE;
    }

    for (int nIndex = 0;nIndex<astrChildFolders.size();nIndex++)
    {
        strTmpFolderFileName = astrChildFolders.at(nIndex);
        strTmpFolderPath.Format(_T("%s%s/"),strAbsFolderPath.GetString(),strTmpFolderFileName.GetString());
        QDir dirTmp(strTmpFolderPath);

        astrTmp = dirTmp.entryList(atrFolderFilters, QDir::Dirs| QDir::Files| QDir::NoDotAndDotDot);

        if(astrTmp.size()>0)//USB,
        {
            strUsbRootFolderPath = strTmpFolderPath;
            return TRUE;
        }
    }

    strTmpFolderFileName = astrChildFolders.at(0);//,
    strUsbRootFolderPath.Format(_T("%s%s/"),strAbsFolderPath.GetString(),strTmpFolderFileName.GetString());
    return TRUE;
 #else
    return FALSE;
 #endif
}


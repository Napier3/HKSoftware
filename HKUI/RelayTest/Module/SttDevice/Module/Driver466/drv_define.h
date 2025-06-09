#ifndef _DRV_DEFINE_H__
#define _DRV_DEFINE_H__

//递变相关
#define GRADIENT_MAX_COUNT			3000// 最大递变点数
#define GRADIENT_SMV_PARA_CNT	    111 //(37*3)
#define GRADIENT_ALG_PARA_CNT	    24 //6+6*3
#define GRADIENT_PARAM_MAX		    74 //(37*2)

#define CHANNEL_A     0
#define CHANNEL_B     1
#define CHANNEL_C     2

#define DrvPos_Ang    0
#define DrvPos_Fre    1
#define DrvPos_Amp    2

#define TmtPos_Amp    0
#define TmtPos_Ang    1
#define TmtPos_Fre    2

#define TMT_UA_POS    0
#define TMT_UB_POS    1
#define TMT_UC_POS    2
#define TMT_UA2_POS   3
#define TMT_UB2_POS   4
#define TMT_UC2_POS   5

#define TMT_IA_POS    0
#define TMT_IB_POS    1
#define TMT_IC_POS    2
#define TMT_IA2_POS   3
#define TMT_IB2_POS   4
#define TMT_IC2_POS   5

//振荡
#define NANOSECOND             1.0e9
#define SHAKE_ALG_PARA_CNT        24//6+6*3
#define SHAKE_DIG_PARA_CNT        75
#define SHAKE_MAX               5000


#define GRADIENT_AMP      0
#define GRADIENT_ANG      1
#define GRADIENT_FRE      2

#define GRADIENT_UA               0
#define GRADIENT_UB               1
#define GRADIENT_UC               2
#define GRADIENT_UABC             3
#define GRADIENT_IA               4
#define GRADIENT_IB               5
#define GRADIENT_IC               6
#define GRADIENT_IABC             7
#define GRADIENT_UA2              8
#define GRADIENT_UB2              9
#define GRADIENT_UC2             10
#define GRADIENT_UABC2           11
#define GRADIENT_IA2             12
#define GRADIENT_IB2             13
#define GRADIENT_IC2             14
#define GRADIENT_IABC2           15
#define GRADIENT_UABC_UABC2      16
#define GRADIENT_IABC_IABC2      17
#define GRADIENT_UABC_IABC_1     18
#define GRADIENT_UABC_IABC_2     19
#define GRADIENT_UAB             20
#define GRADIENT_UBC             21
#define GRADIENT_UCA             22
#define GRADIENT_UAB2            23
#define GRADIENT_UBC2            24
#define GRADIENT_UCA2            25
#define GRADIENT_IAB             26
#define GRADIENT_IBC             27
#define GRADIENT_ICA             28
#define GRADIENT_IAB2            29
#define GRADIENT_IBC2            30
#define GRADIENT_ICA2            31

#define GRADIENT_RESULT_START	         1
#define GRADIENT_RESULT_STOP	         2
#define GRADIENT_RESULT_CHANGE	         3
#define GRADIENT_RESULT_DI_CHANGE	     4
#define GRADIENT_RESULT_RETURN	         5
#define GRADIENT_RESULT_GO_FAULT	     6
#define GRADIENT_RESULT_SHAKE	         7
#define GRADIENT_RESULT_SHAKE_FAULT	     8


//状态相关
#define STATE_RAMP_TYPE_NULL         0
#define STATE_RAMP_TYPE_SLIP_VAL     1
#define STATE_RAMP_TYPE_SLIP_FRE     2
#define STATE_RAMP_TYPE_NORMAL       3

//#define STATE_RESULT_START                 1
//#define STATE_RESULT_STOP                  2
//#define STATE_RESULT_CHANGE                3
//#define STATE_RESULT_DI_CHANGE             4
//#define STATE_RESULT_GRADIENT              5
//#define STATE_RESULT_GOOSE_CHANGED         6
//#define STATE_RESULT_GRADIENTVALUE         7
//#define STATE_RESULT_BOCHANGED             8
//#define STATE_RESULT_GRADIENTEND          10

/******structDegUnit
		 xw   pl   fz
Ua1      0    1    2
Ub1      1*3  4    5
Uc1      2*3  7    8

Uz       3*3  10   11

Ua2      4*3  13   14
Ub2      5*3  16   17
Uc2      6*3  19   20
Ua3      7*3
Ub3      8*3
Uc3      9*3
Ua4      10*3
Ub4      11*3
Uc4      12*3

Ia1      13*3 40   41
Ib1      14*3 43   44
Ic1      15*3 46   47
Ia2      16*3 49   50
Ib2      17*3 52   53
Ic2      18*3 55   56
Ia3      19*3
Ib3      20*3
Ic3      21*3
Ia4      22*3
Ib4      23*3
Ic4      24*3 73   74

Ua5      25*3 76   77
Ub5      26*3 79   80
Uc5      27*3 82   83
Ua6      28*3 85   86
Ub6      29*3 88   89
Uc6      30*3 91   92

Ia5      31*3
Ib5      32*3
Ic5      33*3
Ia6      34*3
Ib6      35*3
Ic6      36*3
*****/
#endif // _DRV_DEFINE_H__


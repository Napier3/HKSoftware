#ifndef STTDEFINE_H
#define STTDEFINE_H
#include <QMap>
#include <QString>
#include <QPen>
#include <QMetaType>

#define STT_UI_RUN_STATE_Stoped                              0
#define STT_UI_RUN_STATE_StateTested_NotEditable             1
#define STT_UI_RUN_STATE_StateTested_Editable                2

//�������� �����ƶ� ����г���ƶ� ���г���ƶ� �ٶϵ��� ��������
enum ErrorType {Error_A_JD=0,Error_B_JD,Error_C_JD,Error_AB_DL,Error_BC_DL,Error_CA_DL,\
	Error_AB_JDDL,Error_BC_JDDL,Error_CA_JDDL,Error_ABC_DL,Error_SINGLE_ZK};
enum PTPhase {Phase_A=1,Phase_B,Phase_C,Phase_AB,Phase_BC,Phase_CA,Phase_ABC};
enum PhaseType{Phase_P=0,Phase_N,Phase_Z};
enum MOUDLEType{Moudle_U=0,Moudle_I};
enum ZKType {TYPE_LINE=0,TYPE_CIRCLE,TYPE_EDGE}; //�ߡ�Բ����

enum Value_TypeMarkDisp {MarkDispType_Int = 0, MarkDispType_UnInt,MarkDispType_Float};

enum changed_type
{
	amplitude_type = 0,
	phasor_type = 1,
	fre_type = 2
};

enum plugin_type{
	P_Analog = 0,
	P_Digit,
	P_LowSignal,
	P_Common,
	P_Harm
};

Q_DECLARE_METATYPE(ErrorType); 
Q_DECLARE_METATYPE(MOUDLEType);

#define CIRCLECOUNT 2000
#define CHANLEPOINT 4000
#define RADIO 1.4
#define HARMNUMBER 51   //32
#define MAXHARMCOUNT 51  //32

#define MAXHZ 3000
#define HKpi 3.14159265357979823846
#define G3 1.7320508
#define G2 1.4142135623731
#define FRADIO 1.1

#define EPSINON 0.00000001

#define Postfix_StateTest		"sttxml"
#define Postfix_ManualTest		"mntxml"
#define Postfix_HarmTest		"hrmxml"
#define Postfix_SoeTest			"soexml"
#define Postfix_SystemParas		"sysxml"
#define Postfix_GradientTest	"grtxml"
#define Postfix_CBOperateTest	"cbtxml"
#define Postfix_DistanceTest	"dttxml"
#define Postfix_ZeroSequenceTest "zstxml"
#define Postfix_Reclose			"rctxml"
#define Postfix_OverCurrentTest  "octxml"
#define Postfix_DifferTest		"dftxml"

struct LineInfor
{
	QString m_UIType;
	float m_RealValue;
	float m_XW;
	bool m_bShowOrHide;
	QPen m_Color;
	float m_ChangeFactor;
};

struct ShortCalcuPara
{
	int nRadio;
	bool bZPhi;
	bool bRX;
	bool bPrimaryPara;
	int nFaultType;
	float fZ;
	float fR;
	float fX;
	float fPhi;

	float fImax;
	float fVmax;
	float fKr;
	float fKx;
	float fDLI;
	float fDLV;
	float fZSZL;
	int nCalMode;
	int nCalType;
	float fVnom;

	bool bFaultDir;
	bool bCTPoint;
	float fIfh;			//���ɵ���
	float fPowerAngle;  //���ɹ���

	ShortCalcuPara()
	{
		nRadio = 0;
		bZPhi = true;;
		bRX = false;
		bPrimaryPara = false;
		nFaultType = 0;
		fZ = 1;
		fR = 0;
		fX  = 1;
		fPhi = 90;

		fImax = 5000;
		fVmax = 5000000;
		fKr=0.67;
		fKx=0;
		fDLI = 5;
		fDLV = 0;
		fZSZL=0;
		nCalMode=0;
		nCalType=0;
		fVnom=57.74;

		bFaultDir=1;
		bCTPoint=1;
		fIfh=0;
		fPowerAngle=0;
	}

	ShortCalcuPara &operator = (const ShortCalcuPara &right)
	{
		nRadio = right.nRadio;
		bZPhi = right.bZPhi;
		bRX = right.bRX;
		bPrimaryPara = right.bPrimaryPara;
		nFaultType = right.nFaultType;
		fZ = right.fZ;
		fR = right.fR;
		fX  = right.fX;
		fPhi = right.fPhi;

		fImax = right.fImax;
		fVmax = right.fVmax;
		fKr=right.fKr;
		fKx=right.fKx;
		fDLI = right.fDLI;
		fDLV = right.fDLV;
		fZSZL= right.fZSZL;
		nCalMode=right.nCalMode;
		nCalType=right.nCalType;
		fVnom=right.fVnom;

		bFaultDir=right.bFaultDir;
		bCTPoint=right.bCTPoint;
		fIfh=right.fIfh;
		fPowerAngle=right.fPowerAngle;
		return *this;
	}

	bool isSame(const ShortCalcuPara &right)
	{
        bool bSame = true;
		if(nRadio != right.nRadio || bZPhi != right.bZPhi || bRX != right.bRX || bPrimaryPara != right.bPrimaryPara
		   || nFaultType != right.nFaultType || fZ != right.fZ || fR != right.fR || fX != right.fX || fPhi != right.fPhi
		   || fImax != right.fImax || fVmax != right.fVmax || fKr != right.fKr || fKx != right.fKx || fDLI != right.fDLI
		   || fDLV != right.fDLV || fZSZL != right.fZSZL || nCalMode != right.nCalMode || nCalType != right.nCalType
		   || fVnom !=right.fVnom || bFaultDir != right.bFaultDir || bCTPoint != right.bCTPoint || fIfh != right.fIfh
		   || fPowerAngle != right.fPowerAngle)
		{
			bSame = !bSame;
		}
		return bSame;
	}
};

struct GPSDATA
{
	int nSecond;
	int nNanoSec;					
	GPSDATA()
	{
		nSecond  = 0;
		nNanoSec = 0;
	}

	GPSDATA &operator = (const GPSDATA &right)
	{
		if (this == &right)
		{
			return *this;
		}
		nSecond = right.nSecond;
		nNanoSec = right.nNanoSec;

		return *this;
	}
};

Q_DECLARE_METATYPE(GPSDATA);
Q_DECLARE_METATYPE(ShortCalcuPara);

//��·����
typedef enum tag_FaultType          // ��������
{
	PHASE_A_GROUNDING       = 0,    // A��ӵ�
	PHASE_B_GROUNDING       = 1,    // B��ӵ�
	PHASE_C_GROUNDING       = 2,    // C��ӵ�
	PHASE_AB_SHORT_CIRCUIT  = 3,    // AB��·
	PHASE_BC_SHORT_CIRCUIT  = 4,    // BC��·
	PHASE_CA_SHORT_CIRCUIT  = 5,    // CA��·
	PHASE_AB_GROUND_SHORT   = 6,    // AB�ӵض�·
	PHASE_BC_GROUND_SHORT   = 7,    // BC�ӵض�·
	PHASE_CA_GROUND_SHORT   = 8,    // CA�ӵض�·
	PHASE_ABC_SHORT_CIRCUIT = 9,    // ABC�����·
	SINGLE_PHASE_FAULT      = 10    // ����ϵͳ
}FaultType;

typedef enum tag_ImpedanceMode    // �迹������ʽ
{
	Z_PHI_MODE = 0,   // Z, Phi ��ʽ
	R_X_MODE   = 1,   // R, X ��ʽ
}ImpedanceMode;

typedef struct tag_ValuePair
{
	union
	{
		double Z;
		double R;
		double Kr;
		double Amp;
	};
	union
	{
		double Phi;
		double X;
		double Kx;
	};
} ValuePair;

typedef struct tag_ImpedanceInfo
{
	ImpedanceMode mode;      // �迹������ʽ
	ValuePair Z_Phi;         // Z, Phi ��ʽ
	ValuePair R_X;           // R, X ��ʽ
}ImpedanceInfo;

typedef enum tag_ShortcutComputationalModel
{
	KEEP_CURRENT_CONST     = 0,     // ��������
	KEEP_VOLTAGE_CONST     = 1,     // ��ѹ����
	KEEP_IMPEDANCE_CONST   = 2      // ϵͳ�迹����
}ShortcutComputationalModel;

typedef struct tag_ShortcutComputationalInfo
{
	ShortcutComputationalModel mode;      // ����ģ������
	double Current;      // ���ֲ���ĵ���ֵ
	double Voltage;      // ���ֲ���ĵ�ѹֵ
	double Impedance;      // ���ֲ����|ZS/ZL|ֵ
}ShortcutComputationalInfo;

typedef enum tag_ZeroSeqCompensateCoefMode    // ���򲹳�ϵ���ļ��㷽��
{
	ZERO_SEQ_COMP_KL    = 0,      // KL
	ZERO_SEQ_COMP_KR_KX = 1,      // Kr,Kx
	ZERO_SEQ_COMP_Z0_Z1 = 2       // Z0,Z1
}ZeroSeqCompensateCoefMode;

typedef struct tag_ZeroSeqCompensateCoefInfo
{
	ZeroSeqCompensateCoefMode mode;   // ����ģ������
	ValuePair KL;                     // KL
	ValuePair Kr_Kx;                  // Kr,Kx
	ValuePair Z0_Z1;                  // Z0,Z1
}ZeroSeqCompensateCoefInfo;

typedef struct tag_ShortcutCalcInfo
{
	FaultType                  Mode;
	ImpedanceInfo              Impedance;
	bool                       FaultIsPositiveDirection;
	bool                       CTIsBusDirection;
	ShortcutComputationalInfo  ShortcutCompute;
	ZeroSeqCompensateCoefInfo  ZeroSeqCompensateCoef;  // ���򲹳�ϵ��
	double                     LoadCurrent;            // ���ɵ���
	double                     LoadAngle;              // ���ɹ���
} ShortcutCalcInfo;

//���ʡ���������ߵ�ѹ����
typedef struct tag_PowerValue
{
	double FactorA;
	double FactorB;
	double FactorC;
	double PA;
	double PB;
	double PC;
	double PSum;
	double QA;
	double QB;
	double QC;
	double QSum;
	double SA;
	double SB;
	double SC;
	double SSum;
} PowerValue;

typedef struct tag_SeqValue
{
	double amp;
	double phase;
} SeqValue;

#endif

/*  This file created from input file '..\..\mvl\usr\uca_srvr\uca_obj.odf'
    Leaf Access Parameter (LAP) File: '..\..\mvl\usr\uca_srvr\leafmap.xml'
	Created Sat Apr 21 18:35:37 2012
*/

#ifndef FOUNDRY_OUTPUT_HEADER_INCLUDED
#define FOUNDRY_OUTPUT_HEADER_INCLUDED

#include "mvl_uca.h"

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* MVL Type Control Information */
extern MVL_TYPE_CTRL *mvl_type_ctrl;
extern ST_INT mvl_num_types;

/************************************************************************/


/* MVL Type ID's */
#define UTC_TM_TYPEID		0
#define DI_TYPEID		1
#define RTYP_BOOL_TYPEID		2
#define RTYP_BTIME6_TYPEID		3
#define RTYP_BSTR6_TYPEID		4
#define RTYP_BSTR8_TYPEID		5
#define RTYP_BSTR9_TYPEID		6
#define RTYP_BVSTR6_TYPEID		7
#define RTYP_BVSTR8_TYPEID		8
#define RTYP_BVSTR10_TYPEID		9
#define RTYP_INT8U_TYPEID		10
#define RTYP_INT16U_TYPEID		11
#define RTYP_OSTR8_TYPEID		12
#define RTYP_VSTR32_TYPEID		13
#define RTYP_VSTR65_TYPEID		14
#define RTYP_OBJREF_TYPEID		15
#define RTYP_INT32U_TYPEID		16
#define GLOBE_TYPEID		17
#define PBRO_TYPEID		18
#define IEC_LPHD_TYPEID		19
#define IEC_LLN0_TYPEID		20
#define IEC_POPF_TYPEID		21
#define IEC_PUPF_TYPEID		22
#define IEC_MHAN_TYPEID		23
#define I16_TYPEID		24
#define U32_TYPEID		25
#define array_type1_TYPEID		26
#define array_type2_TYPEID		27
#define array_type3_TYPEID		28
#define array_type4_TYPEID		29


/************************************************************************/

/************************************************************************/


/*	Common Strings Index Defines	*/

#ifndef USE_RT_TYPE_2

#define FO_NAME_STRING_INDEX	 1
#define FO_CLASS_STRING_INDEX	 2
#define FO_D_STRING_INDEX	 3
#define FO_OWN_STRING_INDEX	 4
#define FO_LOC_STRING_INDEX	 5
#define FO_VNDID_STRING_INDEX	 6
#define FO_VND_STRING_INDEX	 7
#define FO_MDL_STRING_INDEX	 8
#define FO_DEVMDLS_STRING_INDEX	 9
#define FO_SERNUM_STRING_INDEX	 10
#define FO_HWREV_STRING_INDEX	 11
#define FO_SFTREV_STRING_INDEX	 12
#define FO_COMMID_STRING_INDEX	 13
#define FO_COMMADR_STRING_INDEX	 14
#define FO_COMMREV_STRING_INDEX	 15
#define FO_PRO_STRING_INDEX	 16
#define FO_MED_STRING_INDEX	 17
#define FO_MAC_STRING_INDEX	 18
#define FO_ST_STRING_INDEX	 19
#define FO_MODEDS_STRING_INDEX	 20
#define FO_B2_STRING_INDEX	 21
#define FO_Q_STRING_INDEX	 22
#define FO_T_STRING_INDEX	 23
#define FO_LOCREMDS_STRING_INDEX	 24
#define FO_ACTSG_STRING_INDEX	 25
#define FO_EDITSG_STRING_INDEX	 26
#define FO_AUXIN01_STRING_INDEX	 27
#define FO_SP_STRING_INDEX	 28
#define FO_PRESETDNA_STRING_INDEX	 29
#define FO_FORDNA_STRING_INDEX	 30
#define FO_DEFDNA_STRING_INDEX	 31
#define FO_CO_STRING_INDEX	 32
#define FO_COPYSG_STRING_INDEX	 33
#define FO_SAVESG_STRING_INDEX	 34
#define FO_INDRS_STRING_INDEX	 35
#define FO_AUXOUT16_STRING_INDEX	 36
#define FO_CF_STRING_INDEX	 37
#define FO_IMG_STRING_INDEX	 38
#define FO_BLOB_STRING_INDEX	 39
#define FO_STATE_STRING_INDEX	 40
#define FO_TIMOUT_STRING_INDEX	 41
#define FO_FMT_STRING_INDEX	 42
#define FO_CLOCKTOD_STRING_INDEX	 43
#define FO_SELOUTDNA_STRING_INDEX	 44
#define FO_SELINDNA_STRING_INDEX	 45
#define FO_NEUTREF_STRING_INDEX	 46
#define FO_CTRAT_STRING_INDEX	 47
#define FO_PRIF_STRING_INDEX	 48
#define FO_SECF_STRING_INDEX	 49
#define FO_RATIOF_STRING_INDEX	 50
#define FO_VTRAT_STRING_INDEX	 51
#define FO_DC_STRING_INDEX	 52
#define FO_AX_STRING_INDEX	 53
#define FO_SGEDITOR_STRING_INDEX	 54
#define FO_TAGID_STRING_INDEX	 55
#define FO_TAGTYP_STRING_INDEX	 56
#define FO_TAGD_STRING_INDEX	 57
#define FO_TAGOWN_STRING_INDEX	 58
#define FO_RP_STRING_INDEX	 59
#define FO_BRCBST_STRING_INDEX	 60
#define FO_RPTENA_STRING_INDEX	 61
#define FO_RPTID_STRING_INDEX	 62
#define FO_DATSET_STRING_INDEX	 63
#define FO_OPTFLDS_STRING_INDEX	 64
#define FO_BUFTIM_STRING_INDEX	 65
#define FO_TRGS_STRING_INDEX	 66
#define FO_SQNUM_STRING_INDEX	 67
#define FO_TRGOPS_STRING_INDEX	 68
#define FO_RBEPD_STRING_INDEX	 69
#define FO_INTGPD_STRING_INDEX	 70
#define FO_GOOSE_STRING_INDEX	 71
#define FO_SENDINGIED_STRING_INDEX	 72
#define FO_STNUM_STRING_INDEX	 73
#define FO_HOLDTIM_STRING_INDEX	 74
#define FO_BACKTIM_STRING_INDEX	 75
#define FO_PHSID_STRING_INDEX	 76
#define FO_DNA_STRING_INDEX	 77
#define FO_USERST_STRING_INDEX	 78
#define FO_OUT_STRING_INDEX	 79
#define FO_TAR_STRING_INDEX	 80
#define FO_FCTDS_STRING_INDEX	 81
#define FO_AUXIN1_STRING_INDEX	 82
#define FO_PUGRP_STRING_INDEX	 83
#define FO_SG_STRING_INDEX	 84
#define FO_PU_STRING_INDEX	 85
#define FO_PHSI_STRING_INDEX	 86
#define FO_PHSF_STRING_INDEX	 87
#define FO_NEUTI_STRING_INDEX	 88
#define FO_NEUTF_STRING_INDEX	 89
#define FO_CLDLODI_STRING_INDEX	 90
#define FO_CLDLODF_STRING_INDEX	 91
#define FO_HZI_STRING_INDEX	 92
#define FO_HZF_STRING_INDEX	 93
#define FO_PUDELTIM_STRING_INDEX	 94
#define FO_DODELTIM_STRING_INDEX	 95
#define FO_ENADISFCT_STRING_INDEX	 96
#define FO_OPERDEV_STRING_INDEX	 97
#define FO_SBO_STRING_INDEX	 98
#define FO_RSTAR_STRING_INDEX	 99
#define FO_B1_STRING_INDEX	 100
#define FO_RSLAT_STRING_INDEX	 101
#define FO_ENALATRS_STRING_INDEX	 102
#define FO_AUXOUT1_STRING_INDEX	 103
#define FO_S_STRING_INDEX	 104
#define FO_O_STRING_INDEX	 105
#define FO_U_STRING_INDEX	 106
#define FO_DB_STRING_INDEX	 107
#define FO_MIN_STRING_INDEX	 108
#define FO_MAX_STRING_INDEX	 109
#define FO_INCR_STRING_INDEX	 110
#define FO_MXTYP_STRING_INDEX	 111
#define FO_MXREF_STRING_INDEX	 112
#define FO_MXLOC_STRING_INDEX	 113
#define FO_SMPRATE_STRING_INDEX	 114
#define FO_NUMSMP_STRING_INDEX	 115
#define FO_PP_STRING_INDEX	 116
#define FO_ONDUR_STRING_INDEX	 117
#define FO_OFFDUR_STRING_INDEX	 118
#define FO_PHYHEALTH_STRING_INDEX	 119
#define FO_STVAL_STRING_INDEX	 120
#define FO_OUTOV_STRING_INDEX	 121
#define FO_PROXY_STRING_INDEX	 122
#define FO_INOV_STRING_INDEX	 123
#define FO_NUMPWRUP_STRING_INDEX	 124
#define FO_WRMSTR_STRING_INDEX	 125
#define FO_WACTRG_STRING_INDEX	 126
#define FO_PWRUP_STRING_INDEX	 127
#define FO_PWRDN_STRING_INDEX	 128
#define FO_PWRSUPALM_STRING_INDEX	 129
#define FO_RSSTAT_STRING_INDEX	 130
#define FO_ORIGIN_STRING_INDEX	 131
#define FO_ORCAT_STRING_INDEX	 132
#define FO_ORIDENT_STRING_INDEX	 133
#define FO_CTLNUM_STRING_INDEX	 134
#define FO_STSELD_STRING_INDEX	 135
#define FO_SBOW_STRING_INDEX	 136
#define FO_CTLVAL_STRING_INDEX	 137
#define FO_OPERTM_STRING_INDEX	 138
#define FO_T_STRING_INDEX	 139
#define FO_TEST_STRING_INDEX	 140
#define FO_CHECK_STRING_INDEX	 141
#define FO_OPER_STRING_INDEX	 142
#define FO_CANCEL_STRING_INDEX	 143
#define FO_PULSECONFIG_STRING_INDEX	 144
#define FO_CMDQUAL_STRING_INDEX	 145
#define FO_ONDUR_STRING_INDEX	 146
#define FO_OFFDUR_STRING_INDEX	 147
#define FO_NUMPLS_STRING_INDEX	 148
#define FO_CTLMODEL_STRING_INDEX	 149
#define FO_SBOTIMEOUT_STRING_INDEX	 150
#define FO_SBOCLASS_STRING_INDEX	 151
#define FO_PHYNAM_STRING_INDEX	 152
#define FO_VENDOR_STRING_INDEX	 153
#define FO_HWREV_STRING_INDEX	 154
#define FO_SWREV_STRING_INDEX	 155
#define FO_SERNUM_STRING_INDEX	 156
#define FO_MODEL_STRING_INDEX	 157
#define FO_LOCATION_STRING_INDEX	 158
#define FO_DU_STRING_INDEX	 159
#define FO_URCBST_STRING_INDEX	 160
#define FO_RESV_STRING_INDEX	 161
#define FO_CONFREV_STRING_INDEX	 162
#define FO_BUFTM_STRING_INDEX	 163
#define FO_GI_STRING_INDEX	 164
#define FO_BR_STRING_INDEX	 165
#define FO_PURGEBUF_STRING_INDEX	 166
#define FO_ENTRYID_STRING_INDEX	 167
#define FO_TIMEOFENTRY_STRING_INDEX	 168
#define FO_SV_STRING_INDEX	 169
#define FO_SUBENA_STRING_INDEX	 170
#define FO_SUBVAL_STRING_INDEX	 171
#define FO_SUBQ_STRING_INDEX	 172
#define FO_SUBID_STRING_INDEX	 173
#define FO_EX_STRING_INDEX	 174
#define FO_CDCNS_STRING_INDEX	 175
#define FO_CDCNAME_STRING_INDEX	 176
#define FO_DATANS_STRING_INDEX	 177
#define FO_MOD_STRING_INDEX	 178
#define FO_BEH_STRING_INDEX	 179
#define FO_HEALTH_STRING_INDEX	 180
#define FO_OPTMH_STRING_INDEX	 181
#define FO_DIAG_STRING_INDEX	 182
#define FO_LEDRS_STRING_INDEX	 183
#define FO_MINVAL_STRING_INDEX	 184
#define FO_MAXVAL_STRING_INDEX	 185
#define FO_STEPSIZE_STRING_INDEX	 186
#define FO_NAMPLT_STRING_INDEX	 187
#define FO_CONFIGREV_STRING_INDEX	 188
#define FO_LDNS_STRING_INDEX	 189
#define FO_LNNS_STRING_INDEX	 190
#define FO_OPCNTRS_STRING_INDEX	 191
#define FO_STR_STRING_INDEX	 192
#define FO_GENERAL_STRING_INDEX	 193
#define FO_DIRGENERAL_STRING_INDEX	 194
#define FO_PHSA_STRING_INDEX	 195
#define FO_DIRPHSA_STRING_INDEX	 196
#define FO_PHSB_STRING_INDEX	 197
#define FO_DIRPHSB_STRING_INDEX	 198
#define FO_PHSC_STRING_INDEX	 199
#define FO_DIRPHSC_STRING_INDEX	 200
#define FO_NEUT_STRING_INDEX	 201
#define FO_DIRNEUT_STRING_INDEX	 202
#define FO_OP_STRING_INDEX	 203
#define FO_BLKA_STRING_INDEX	 204
#define FO_BLKV_STRING_INDEX	 205
#define FO_STRVAL_STRING_INDEX	 206
#define FO_UNITS_STRING_INDEX	 207
#define FO_SIUNIT_STRING_INDEX	 208
#define FO_MULTIPLIER_STRING_INDEX	 209
#define FO_SVC_STRING_INDEX	 210
#define FO_SCALEFACTOR_STRING_INDEX	 211
#define FO_OFFSET_STRING_INDEX	 212
#define FO_I_STRING_INDEX	 213
#define FO_F_STRING_INDEX	 214
#define FO_OPDLTMMS_STRING_INDEX	 215
#define FO_RSDLTMMS_STRING_INDEX	 216
#define FO_BLKVALA_STRING_INDEX	 217
#define FO_BLKVALV_STRING_INDEX	 218
#define FO_SETMAG_STRING_INDEX	 219
#define FO_SETVAL_STRING_INDEX	 220
#define FO_SE_STRING_INDEX	 221
#define FO_MX_STRING_INDEX	 222
#define FO_HZ_STRING_INDEX	 223
#define FO_INSTMAG_STRING_INDEX	 224
#define FO_MAG_STRING_INDEX	 225
#define FO_RANGE_STRING_INDEX	 226
#define FO_HAAMP_STRING_INDEX	 227
#define FO_HAR_STRING_INDEX	 228
#define FO_ANG_STRING_INDEX	 229
#define FO_HAWATT_STRING_INDEX	 230
#define FO_HAVOLAMPR_STRING_INDEX	 231
#define FO_HAVOLAMP_STRING_INDEX	 232
#define FO_HARMSAMP_STRING_INDEX	 233
#define FO_HARMSVOL_STRING_INDEX	 234
#define FO_HATUWATT_STRING_INDEX	 235
#define FO_HATSWATT_STRING_INDEX	 236
#define FO_HAAMPTM_STRING_INDEX	 237
#define FO_HAKFACT_STRING_INDEX	 238
#define FO_HATDFACT_STRING_INDEX	 239
#define FO_THDAMP_STRING_INDEX	 240
#define FO_THDODDAMP_STRING_INDEX	 241
#define FO_THDEVNAMP_STRING_INDEX	 242
#define FO_TDDAMP_STRING_INDEX	 243
#define FO_TDDODDAMP_STRING_INDEX	 244
#define FO_TDDEVNAMP_STRING_INDEX	 245
#define FO_THDVOL_STRING_INDEX	 246
#define FO_THDODDVOL_STRING_INDEX	 247
#define FO_THDEVNVOL_STRING_INDEX	 248
#define FO_HACFAMP_STRING_INDEX	 249
#define FO_HACFVOL_STRING_INDEX	 250
#define FO_HATIFACT_STRING_INDEX	 251
#define FO_EEHEALTH_STRING_INDEX	 252
#define FO_ZERODB_STRING_INDEX	 253
#define FO_RANGEC_STRING_INDEX	 254
#define FO_HHLIM_STRING_INDEX	 255
#define FO_HLIM_STRING_INDEX	 256
#define FO_LLIM_STRING_INDEX	 257
#define FO_LILIM_STRING_INDEX	 258
#define FO_SMPRATE_STRING_INDEX	 259
#define FO_NUMHAR_STRING_INDEX	 260
#define FO_NUMCYC_STRING_INDEX	 261
#define FO_EVALTM_STRING_INDEX	 262
#define FO_FREQUENCY_STRING_INDEX	 263
#define FO_HVREF_STRING_INDEX	 264
#define FO_RMSCYC_STRING_INDEX	 265
#define FO_HZSET_STRING_INDEX	 266
#define FO_NUMCYC_STRING_INDEX	 267
#define FO_THDAVAL_STRING_INDEX	 268
#define FO_THDVVAL_STRING_INDEX	 269
#define FO_THDATMMS_STRING_INDEX	 270
#define FO_THDVTMMS_STRING_INDEX	 271
#define FO_NOMA_STRING_INDEX	 272
#define FO_EENAME_STRING_INDEX	 273
#define FO_URCBMX_STRING_INDEX	 274
#define FO_BRCBMX_STRING_INDEX	 275
#define FO_SUBMAG_STRING_INDEX	 276
#define FO_ARR_INT_STRING_INDEX	 277
#define FO_ARR_FLOAT_STRING_INDEX	 278
#define FO_ARR_BVSTR_STRING_INDEX	 279
#define FO_ARR_OVSTR_STRING_INDEX	 280
#define FO_ARR_BSTR_STRING_INDEX	 281
#define FO_ARR_OSTR_STRING_INDEX	 282
#define FO_ARR_BT6_STRING_INDEX	 283
#define FO_ARR_BT4_STRING_INDEX	 284
#define FO_BT4_STRING_INDEX	 285
#define FO_ARR_T_STRING_INDEX	 286
#endif


/************************************************************************/
/* TYPEDEFS for MMS TYPES	                                              */
/************************************************************************/

/* Use ":CF", "-notypedefs" in the ODF file to not include this line */
#define USE_MMS_TYPEDEFS

#if defined (USE_MMS_TYPEDEFS)

typedef MMS_UTC_TIME UTC_TM_TDEF;

typedef struct
  {
  ST_CHAR Name[33];
  ST_CHAR Class[33];
  ST_CHAR d[33];
  ST_CHAR Own[33];
  ST_CHAR Loc[129];
  struct
    {
    ST_CHAR Vnd[33];
    ST_CHAR Mdl[129];
    ST_CHAR DevMdls[129];
    ST_CHAR SerNum[33];
    ST_CHAR HwRev[9];
    ST_CHAR SftRev[9];
    } VndID;
  struct
    {
    ST_CHAR CommAdr[17];
    ST_CHAR CommRev[9];
    ST_INT8 Pro;
    ST_INT8 Med;
    ST_UINT8 MAC;
    } CommID;
  } DI_TDEF;

typedef ST_BOOLEAN RTYP_BOOL_TDEF;

typedef MMS_BTIME6 RTYP_BTIME6_TDEF;

typedef ST_UCHAR RTYP_BSTR6_TDEF[1];  /* Bitstring */

typedef ST_UCHAR RTYP_BSTR8_TDEF[1];  /* Bitstring */

typedef ST_UCHAR RTYP_BSTR9_TDEF[2];  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[1];
  }  RTYP_BVSTR6_TDEF;  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[1];
  }  RTYP_BVSTR8_TDEF;  /* Bitstring */

typedef struct     /* BVstring */
  {
  ST_INT16 len_1;
  ST_UCHAR data_1[2];
  }  RTYP_BVSTR10_TDEF;  /* Bitstring */

typedef ST_UINT8 RTYP_INT8U_TDEF;

typedef ST_UINT16 RTYP_INT16U_TDEF;

typedef ST_UCHAR RTYP_OSTR8_TDEF[8];  /* Octetstring */

typedef ST_CHAR RTYP_VSTR32_TDEF[33];  /* Visible String */

typedef ST_CHAR RTYP_VSTR65_TDEF[66];  /* Visible String */

typedef ST_CHAR RTYP_OBJREF_TDEF[130];  /* Visible String */

typedef ST_UINT32 RTYP_INT32U_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      ST_UCHAR b2[1];
      ST_UCHAR q[2];
      MMS_BTIME6 t;
      } ModeDS;
    struct
      {
      ST_UCHAR b2[1];
      ST_UCHAR q[2];
      MMS_BTIME6 t;
      } LocRemDS;
    ST_UINT8 ActSG;
    ST_UINT8 EditSG;
    ST_UCHAR AuxIn01[2];
    } ST;
  struct
    {
    ST_UCHAR PreSetDNA[8];
    ST_UCHAR ForDNA[8];
    ST_UCHAR DefDNA[8];
    } SP;
  struct
    {
    ST_UINT8 CopySG;
    ST_UINT8 SaveSG;
    ST_UINT8 ActSG;
    ST_BOOLEAN IndRs;
    ST_BOOLEAN AuxOut16[16];
    } CO;
  struct
    {
    struct
      {
      ST_CHAR BLOB[65];
      ST_BOOLEAN State;
      ST_UINT32 TimOut;
      ST_INT8 Fmt;
      } Img;
    MMS_BTIME6 ClockTOD;
    ST_UCHAR SelOutDNA[8];
    ST_UCHAR SelInDNA[8];
    ST_BOOLEAN NeutRef;
    struct
      {
      ST_FLOAT Prif;
      ST_FLOAT Secf;
      ST_FLOAT Ratiof;
      } CTRat;
    struct
      {
      ST_FLOAT Prif;
      ST_FLOAT Secf;
      ST_FLOAT Ratiof;
      } VTRat;
    } CF;
  struct
    {
    struct
      {
      ST_CHAR d[33];
      } ModeDS;
    struct
      {
      ST_CHAR d[33];
      } LocRemDS;
    struct
      {
      ST_CHAR d[33];
      } ActSG;
    struct
      {
      ST_CHAR d[33];
      } EditSG;
    struct
      {
      ST_CHAR d[33];
      } AuxIn01;
    } DC;
  struct
    {
    struct
      {
      ST_UINT8 TagID;
      ST_UCHAR TagTyp[1];
      ST_CHAR TagD[129];
      ST_CHAR TagOwn[33];
      } SGEditor;
    } AX;
  struct
    {
    struct
      {
      ST_BOOLEAN RptEna;
      ST_CHAR RptID[33];
      ST_CHAR DatSet[66];
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } OptFlds;
      ST_UINT32 BufTim;
      ST_UINT16 Trgs;
      ST_UINT8 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 RBEPd;
      ST_UINT32 IntgPd;
      } brcbST;
    struct
      {
      ST_CHAR SendingIED[66];
      MMS_BTIME6 t;
      ST_UINT32 SqNum;
      ST_UINT32 StNum;
      ST_UINT32 HoldTim;
      ST_UINT32 BackTim;
      ST_UINT16 PhsID;
      ST_UCHAR DNA[8];
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[32];
        } UserSt;
      } GOOSE;
    } RP;
  } GLOBE_TDEF;

typedef struct
  {
  struct
    {
    ST_BOOLEAN Out;
    ST_INT8 Tar;
    struct
      {
      ST_UCHAR b2[1];
      ST_UCHAR q[2];
      MMS_BTIME6 t;
      } FctDS;
    ST_UCHAR AuxIn1[2];
    ST_UINT8 PuGrp;
    } ST;
  struct
    {
    struct
      {
      ST_INT16 Phsi;
      ST_FLOAT Phsf;
      ST_INT16 Neuti;
      ST_FLOAT Neutf;
      ST_INT16 CldLodi;
      ST_FLOAT CldLodf;
      ST_INT16 Hzi;
      ST_FLOAT Hzf;
      } Pu;
    ST_UINT32 PuDelTim;
    ST_UINT32 DODelTim;
    } SG;
  struct
    {
    struct
      {
      ST_UCHAR OperDev[1];
      ST_CHAR SBO[66];
      } EnaDisFct;
    struct
      {
      ST_UCHAR b1[1];
      ST_CHAR SBO[66];
      } RsTar;
    struct
      {
      ST_UCHAR b1[1];
      ST_CHAR SBO[66];
      } RsLat;
    struct
      {
      ST_UCHAR b1[1];
      ST_CHAR SBO[66];
      } EnaLatRs;
    ST_BOOLEAN AuxOut1[16];
    } CO;
  struct
    {
    struct
      {
      ST_FLOAT s;
      ST_FLOAT o;
      ST_INT16 u;
      ST_UINT16 db;
      ST_FLOAT min;
      ST_FLOAT max;
      ST_FLOAT Incr;
      ST_INT8 MxTyp;
      ST_INT8 MxRef;
      ST_INT8 MxLoc;
      ST_UINT16 SmpRate;
      ST_UINT16 NumSmp;
      ST_BOOLEAN pp;
      } Pu;
    struct
      {
      ST_FLOAT s;
      ST_FLOAT o;
      ST_INT16 u;
      ST_UINT16 db;
      ST_FLOAT min;
      ST_FLOAT max;
      ST_FLOAT Incr;
      ST_INT8 MxTyp;
      ST_INT8 MxRef;
      ST_INT8 MxLoc;
      ST_UINT16 SmpRate;
      ST_UINT16 NumSmp;
      ST_BOOLEAN pp;
      } PuDelTim;
    struct
      {
      ST_FLOAT s;
      ST_FLOAT o;
      ST_INT16 u;
      ST_UINT16 db;
      ST_FLOAT min;
      ST_FLOAT max;
      ST_FLOAT Incr;
      ST_INT8 MxTyp;
      ST_INT8 MxRef;
      ST_INT8 MxLoc;
      ST_UINT16 SmpRate;
      ST_UINT16 NumSmp;
      ST_BOOLEAN pp;
      } DODelTim;
    struct
      {
      ST_UINT32 OnDur;
      ST_UINT32 OffDur;
      } EnaDisFct;
    struct
      {
      ST_UINT32 OnDur;
      ST_UINT32 OffDur;
      } RsTar;
    struct
      {
      ST_UINT32 OnDur;
      ST_UINT32 OffDur;
      } RsLat;
    struct
      {
      ST_UINT32 OnDur;
      ST_UINT32 OffDur;
      } EnaLatRs;
    struct
      {
      ST_UINT32 OnDur;
      ST_UINT32 OffDur;
      } AuxOut1;
    } CF;
  struct
    {
    struct
      {
      ST_CHAR d[33];
      } Out;
    struct
      {
      ST_CHAR d[33];
      } Tar;
    struct
      {
      ST_CHAR d[33];
      } FctDS;
    struct
      {
      ST_CHAR d[33];
      } AuxIn1;
    struct
      {
      ST_CHAR d[33];
      } PuGrp;
    struct
      {
      ST_CHAR d[33];
      } EnaDisFct;
    struct
      {
      ST_CHAR d[33];
      } RsTar;
    struct
      {
      ST_CHAR d[33];
      } RsLat;
    struct
      {
      ST_CHAR d[33];
      } EnaLatRs;
    struct
      {
      ST_CHAR d[33];
      } AuxOut1;
    } DC;
  } PBRO_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } PhyHealth;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } OutOv;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Proxy;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } InOv;
    struct
      {
      ST_INT32 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } NumPwrUp;
    struct
      {
      ST_INT32 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } WrmStr;
    struct
      {
      ST_INT32 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } WacTrg;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } PwrUp;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } PwrDn;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } PwrSupAlm;
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } RsStat;
    } ST;
  struct
    {
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } RsStat;
    } CO;
  struct
    {
    struct
      {
      struct
        {
        ST_INT8 cmdQual;
        ST_UINT32 onDur;
        ST_UINT32 offDur;
        ST_UINT32 numPls;
        } pulseConfig;
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      } RsStat;
    } CF;
  struct
    {
    struct
      {
      ST_CHAR vendor[256];
      ST_CHAR hwRev[256];
      ST_CHAR swRev[256];
      ST_CHAR serNum[256];
      ST_CHAR model[256];
      ST_CHAR location[256];
      } PhyNam;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } PhyHealth;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } OutOv;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Proxy;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } InOv;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } NumPwrUp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } WrmStr;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } WacTrg;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } PwrUp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } PwrDn;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } PwrSupAlm;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } RsStat;
    } DC;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_BOOLEAN Resv;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT8 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      } urcbST;
    } RP;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT16 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      ST_BOOLEAN PurgeBuf;
      ST_UCHAR EntryID[8];
      MMS_BTIME6 TimeofEntry;
      } brcbST;
    } BR;
  struct
    {
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } PhyHealth;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } OutOv;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Proxy;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } InOv;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT32 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } NumPwrUp;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT32 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } WrmStr;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT32 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } WacTrg;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } PwrUp;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } PwrDn;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } PwrSupAlm;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } RsStat;
    } SV;
  struct
    {
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } PhyNam;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } PhyHealth;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } OutOv;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Proxy;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } InOv;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } NumPwrUp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } WrmStr;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } WacTrg;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } PwrUp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } PwrDn;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } PwrSupAlm;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } RsStat;
    } EX;
  } IEC_LPHD_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } Mod;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Beh;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Health;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Loc;
    struct
      {
      ST_INT32 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } OpTmh;
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } Diag;
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } LEDRs;
    } ST;
  struct
    {
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } Mod;
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } Diag;
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_BOOLEAN ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } LEDRs;
    } CO;
  struct
    {
    struct
      {
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      ST_INT8 minVal;
      ST_INT8 maxVal;
      ST_UINT32 stepSize;
      } Mod;
    struct
      {
      struct
        {
        ST_INT8 cmdQual;
        ST_UINT32 onDur;
        ST_UINT32 offDur;
        ST_UINT32 numPls;
        } pulseConfig;
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      } Diag;
    struct
      {
      struct
        {
        ST_INT8 cmdQual;
        ST_UINT32 onDur;
        ST_UINT32 offDur;
        ST_UINT32 numPls;
        } pulseConfig;
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      } LEDRs;
    } CF;
  struct
    {
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Mod;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Beh;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Health;
    struct
      {
      ST_CHAR vendor[256];
      ST_CHAR swRev[256];
      ST_CHAR d[256];
      ST_CHAR dU[512];
      ST_CHAR configRev[256];
      } NamPlt;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Loc;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } OpTmh;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Diag;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } LEDRs;
    } DC;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_BOOLEAN Resv;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT8 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      } urcbST;
    } RP;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT16 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      ST_BOOLEAN PurgeBuf;
      ST_UCHAR EntryID[8];
      MMS_BTIME6 TimeofEntry;
      } brcbST;
    } BR;
  struct
    {
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Mod;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Beh;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Health;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Loc;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT32 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } OpTmh;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Diag;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } LEDRs;
    } SV;
  struct
    {
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Mod;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Beh;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Health;
    struct
      {
      ST_CHAR ldNs[256];
      ST_CHAR lnNs[256];
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } NamPlt;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Loc;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } OpTmh;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Diag;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } LEDRs;
    } EX;
  } IEC_LLN0_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } Mod;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Beh;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Health;
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_INT32 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } OpCntRs;
    struct
      {
      ST_BOOLEAN general;
      ST_INT8 dirGeneral;
      ST_BOOLEAN phsA;
      ST_INT8 dirPhsA;
      ST_BOOLEAN phsB;
      ST_INT8 dirPhsB;
      ST_BOOLEAN phsC;
      ST_INT8 dirPhsC;
      ST_BOOLEAN neut;
      ST_INT8 dirNeut;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Str;
    struct
      {
      ST_BOOLEAN general;
      ST_BOOLEAN phsA;
      ST_BOOLEAN phsB;
      ST_BOOLEAN phsC;
      ST_BOOLEAN neut;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Op;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } BlkA;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } BlkV;
    } ST;
  struct
    {
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } Mod;
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_INT32 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_INT32 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_INT32 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } OpCntRs;
    } CO;
  struct
    {
    struct
      {
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      ST_INT8 minVal;
      ST_INT8 maxVal;
      ST_UINT32 stepSize;
      } Mod;
    struct
      {
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } OpCntRs;
    struct
      {
      MMS_UTC_TIME operTm;
      } Op;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } StrVal;
    struct
      {
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } OpDlTmms;
    struct
      {
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } BlkValV;
    } CF;
  struct
    {
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Mod;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Beh;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Health;
    struct
      {
      ST_CHAR vendor[256];
      ST_CHAR swRev[256];
      ST_CHAR d[256];
      ST_CHAR dU[512];
      ST_CHAR configRev[256];
      } NamPlt;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } OpCntRs;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Str;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Op;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkA;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkV;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } StrVal;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } OpDlTmms;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } RsDlTmms;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkValA;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkValV;
    } DC;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } StrVal;
    struct
      {
      ST_INT32 setVal;
      } OpDlTmms;
    struct
      {
      ST_INT32 setVal;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValV;
    } SP;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } StrVal;
    struct
      {
      ST_INT32 setVal;
      } OpDlTmms;
    struct
      {
      ST_INT32 setVal;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValV;
    } SG;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_BOOLEAN Resv;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT8 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      } urcbST;
    } RP;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT16 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      ST_BOOLEAN PurgeBuf;
      ST_UCHAR EntryID[8];
      MMS_BTIME6 TimeofEntry;
      } brcbST;
    } BR;
  struct
    {
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Mod;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Beh;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Health;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT32 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } OpCntRs;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } BlkA;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } BlkV;
    } SV;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } StrVal;
    struct
      {
      ST_INT32 setVal;
      } OpDlTmms;
    struct
      {
      ST_INT32 setVal;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValV;
    } SE;
  struct
    {
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Mod;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Beh;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Health;
    struct
      {
      ST_CHAR ldNs[256];
      ST_CHAR lnNs[256];
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } NamPlt;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } OpCntRs;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Str;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Op;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkA;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkV;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } StrVal;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } OpDlTmms;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } RsDlTmms;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkValA;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkValV;
    } EX;
  } IEC_POPF_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } Mod;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Beh;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Health;
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_INT32 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } OpCntRs;
    struct
      {
      ST_BOOLEAN general;
      ST_INT8 dirGeneral;
      ST_BOOLEAN phsA;
      ST_INT8 dirPhsA;
      ST_BOOLEAN phsB;
      ST_INT8 dirPhsB;
      ST_BOOLEAN phsC;
      ST_INT8 dirPhsC;
      ST_BOOLEAN neut;
      ST_INT8 dirNeut;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Str;
    struct
      {
      ST_BOOLEAN general;
      ST_BOOLEAN phsA;
      ST_BOOLEAN phsB;
      ST_BOOLEAN phsC;
      ST_BOOLEAN neut;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Op;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } BlkA;
    struct
      {
      ST_BOOLEAN stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } BlkV;
    } ST;
  struct
    {
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } Mod;
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_INT32 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_INT32 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_INT32 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } OpCntRs;
    } CO;
  struct
    {
    struct
      {
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      ST_INT8 minVal;
      ST_INT8 maxVal;
      ST_UINT32 stepSize;
      } Mod;
    struct
      {
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } OpCntRs;
    struct
      {
      MMS_UTC_TIME operTm;
      } Op;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } StrVal;
    struct
      {
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } OpDlTmms;
    struct
      {
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } BlkValV;
    } CF;
  struct
    {
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Mod;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Beh;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Health;
    struct
      {
      ST_CHAR vendor[256];
      ST_CHAR swRev[256];
      ST_CHAR d[256];
      ST_CHAR dU[512];
      ST_CHAR configRev[256];
      } NamPlt;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } OpCntRs;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Str;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Op;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkA;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkV;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } StrVal;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } OpDlTmms;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } RsDlTmms;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkValA;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } BlkValV;
    } DC;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } StrVal;
    struct
      {
      ST_INT32 setVal;
      } OpDlTmms;
    struct
      {
      ST_INT32 setVal;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValV;
    } SP;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } StrVal;
    struct
      {
      ST_INT32 setVal;
      } OpDlTmms;
    struct
      {
      ST_INT32 setVal;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValV;
    } SG;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_BOOLEAN Resv;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT8 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      } urcbST;
    } RP;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT16 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      ST_BOOLEAN PurgeBuf;
      ST_UCHAR EntryID[8];
      MMS_BTIME6 TimeofEntry;
      } brcbST;
    } BR;
  struct
    {
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Mod;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Beh;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Health;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT32 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } OpCntRs;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } BlkA;
    struct
      {
      ST_BOOLEAN subEna;
      ST_BOOLEAN subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } BlkV;
    } SV;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } StrVal;
    struct
      {
      ST_INT32 setVal;
      } OpDlTmms;
    struct
      {
      ST_INT32 setVal;
      } RsDlTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValA;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } BlkValV;
    } SE;
  struct
    {
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Mod;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Beh;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Health;
    struct
      {
      ST_CHAR ldNs[256];
      ST_CHAR lnNs[256];
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } NamPlt;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } OpCntRs;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Str;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Op;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkA;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkV;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } StrVal;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } OpDlTmms;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } RsDlTmms;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkValA;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } BlkValV;
    } EX;
  } IEC_PUPF_TDEF;

typedef struct
  {
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Hz;
    struct
      {
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } mag;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } ang;
        } har[16];
      } HaAmp;
    struct
      {
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } mag;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } ang;
        } har[16];
      } HaWatt;
    struct
      {
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } mag;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } ang;
        } har[16];
      } HaVolAmpr;
    struct
      {
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } mag;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } ang;
        } har[16];
      } HaVolAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaRmsAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaRmsVol;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaTuWatt;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaTsWatt;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaAmpTm;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaKFact;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaTdFact;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } ThdAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } ThdOddAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } ThdEvnAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } TddAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } TddOddAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } TddEvnAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } ThdVol;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } ThdOddVol;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } ThdEvnVol;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaCfAmp;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaCfVol;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } instMag;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } mag;
      ST_INT8 range;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } HaTiFact;
    } MX;
  struct
    {
    struct
      {
      struct
        {
        ST_INT8 orCat;
        struct     /* OVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[64];
          } orIdent;
        } origin;
      ST_UINT8 ctlNum;
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      ST_BOOLEAN stSeld;
      } Mod;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Beh;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } Health;
    struct
      {
      ST_INT8 stVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } q;
      MMS_UTC_TIME t;
      } EEHealth;
    } ST;
  struct
    {
    struct
      {
      ST_CHAR SBO[130];
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } SBOw;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        struct     /* BVstring */
          {
          ST_INT16 len_1;
          ST_UCHAR data_1[1];
          } Check;
        } Oper;
      struct
        {
        ST_INT8 ctlVal;
        MMS_UTC_TIME operTm;
        struct
          {
          ST_INT8 orCat;
          struct     /* OVstring */
            {
            ST_INT16 len_1;
            ST_UCHAR data_1[64];
            } orIdent;
          } origin;
        ST_UINT8 ctlNum;
        MMS_UTC_TIME T;
        ST_BOOLEAN Test;
        } Cancel;
      } Mod;
    } CO;
  struct
    {
    struct
      {
      ST_INT8 ctlModel;
      ST_UINT32 sboTimeout;
      ST_INT8 sboClass;
      ST_INT8 minVal;
      ST_INT8 maxVal;
      ST_UINT32 stepSize;
      } Mod;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } Hz;
    struct
      {
      ST_UINT16 numHar;
      ST_UINT16 numCyc;
      ST_UINT16 evalTm;
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 smpRate;
      ST_FLOAT frequency;
      ST_INT8 hvRef;
      ST_UINT16 rmsCyc;
      } HaAmp;
    struct
      {
      ST_UINT16 numHar;
      ST_UINT16 numCyc;
      ST_UINT16 evalTm;
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 smpRate;
      ST_FLOAT frequency;
      ST_INT8 hvRef;
      ST_UINT16 rmsCyc;
      } HaWatt;
    struct
      {
      ST_UINT16 numHar;
      ST_UINT16 numCyc;
      ST_UINT16 evalTm;
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 smpRate;
      ST_FLOAT frequency;
      ST_INT8 hvRef;
      ST_UINT16 rmsCyc;
      } HaVolAmpr;
    struct
      {
      ST_UINT16 numHar;
      ST_UINT16 numCyc;
      ST_UINT16 evalTm;
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 smpRate;
      ST_FLOAT frequency;
      ST_INT8 hvRef;
      ST_UINT16 rmsCyc;
      } HaVolAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaRmsAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaRmsVol;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaTuWatt;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaTsWatt;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaAmpTm;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaKFact;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaTdFact;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } ThdAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } ThdOddAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } ThdEvnAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } TddAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } TddOddAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } TddEvnAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } ThdVol;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } ThdOddVol;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } ThdEvnVol;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaCfAmp;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaCfVol;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      ST_UINT32 db;
      ST_UINT32 zeroDb;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hhLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } hLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lLim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } lILim;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } min;
        struct
          {
          ST_INT32 i;
          ST_FLOAT f;
          } max;
        } rangeC;
      ST_UINT32 smpRate;
      } HaTiFact;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } HzSet;
    struct
      {
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } NumCyc;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } ThdAVal;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } ThdVVal;
    struct
      {
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } ThdATmms;
    struct
      {
      ST_INT32 minVal;
      ST_INT32 maxVal;
      ST_UINT32 stepSize;
      } ThdVTmms;
    struct
      {
      struct
        {
        ST_INT8 SIUnit;
        ST_INT8 multiplier;
        } units;
      struct
        {
        ST_FLOAT scaleFactor;
        ST_FLOAT offset;
        } sVC;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } minVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } maxVal;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } stepSize;
      } NomA;
    } CF;
  struct
    {
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Mod;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Beh;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Health;
    struct
      {
      ST_CHAR vendor[256];
      ST_CHAR swRev[256];
      ST_CHAR d[256];
      ST_CHAR dU[512];
      ST_CHAR configRev[256];
      } NamPlt;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } EEHealth;
    struct
      {
      ST_CHAR vendor[256];
      ST_CHAR hwRev[256];
      ST_CHAR swRev[256];
      ST_CHAR serNum[256];
      ST_CHAR model[256];
      ST_CHAR location[256];
      } EEName;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } Hz;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaWatt;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaVolAmpr;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaVolAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaRmsAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaRmsVol;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaTuWatt;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaTsWatt;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaAmpTm;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaKFact;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaTdFact;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdOddAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdEvnAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } TddAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } TddOddAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } TddEvnAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdVol;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdOddVol;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdEvnVol;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaCfAmp;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaCfVol;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HaTiFact;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } HzSet;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } NumCyc;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdAVal;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdVVal;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdATmms;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } ThdVTmms;
    struct
      {
      ST_CHAR d[256];
      ST_CHAR dU[512];
      } NomA;
    } DC;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } HzSet;
    struct
      {
      ST_INT32 setVal;
      } NumCyc;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } ThdAVal;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } ThdVVal;
    struct
      {
      ST_INT32 setVal;
      } ThdATmms;
    struct
      {
      ST_INT32 setVal;
      } ThdVTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } NomA;
    } SP;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } HzSet;
    struct
      {
      ST_INT32 setVal;
      } NumCyc;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } ThdAVal;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } ThdVVal;
    struct
      {
      ST_INT32 setVal;
      } ThdATmms;
    struct
      {
      ST_INT32 setVal;
      } ThdVTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } NomA;
    } SG;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_BOOLEAN Resv;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT8 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      } urcbMX;
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_BOOLEAN Resv;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT8 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      } urcbST;
    } RP;
  struct
    {
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT16 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      ST_BOOLEAN PurgeBuf;
      ST_UCHAR EntryID[8];
      MMS_BTIME6 TimeofEntry;
      } brcbMX;
    struct
      {
      ST_CHAR RptID[66];
      ST_BOOLEAN RptEna;
      ST_CHAR DatSet[130];
      ST_UINT32 ConfRev;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } OptFlds;
      ST_UINT32 BufTm;
      ST_UINT16 SqNum;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[1];
        } TrgOps;
      ST_UINT32 IntgPd;
      ST_BOOLEAN GI;
      ST_BOOLEAN PurgeBuf;
      ST_UCHAR EntryID[8];
      MMS_BTIME6 TimeofEntry;
      } brcbST;
    } BR;
  struct
    {
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Mod;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Beh;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Health;
    struct
      {
      ST_BOOLEAN subEna;
      ST_INT8 subVal;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } EEHealth;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } Hz;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaRmsAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaRmsVol;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaTuWatt;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaTsWatt;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaAmpTm;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaKFact;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaTdFact;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } ThdAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } ThdOddAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } ThdEvnAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } TddAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } TddOddAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } TddEvnAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } ThdVol;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } ThdOddVol;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } ThdEvnVol;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaCfAmp;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaCfVol;
    struct
      {
      ST_BOOLEAN subEna;
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } subMag;
      struct     /* BVstring */
        {
        ST_INT16 len_1;
        ST_UCHAR data_1[2];
        } subQ;
      ST_CHAR subID[65];
      } HaTiFact;
    } SV;
  struct
    {
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } HzSet;
    struct
      {
      ST_INT32 setVal;
      } NumCyc;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } ThdAVal;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } ThdVVal;
    struct
      {
      ST_INT32 setVal;
      } ThdATmms;
    struct
      {
      ST_INT32 setVal;
      } ThdVTmms;
    struct
      {
      struct
        {
        ST_INT32 i;
        ST_FLOAT f;
        } setMag;
      } NomA;
    } SE;
  struct
    {
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Mod;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Beh;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Health;
    struct
      {
      ST_CHAR ldNs[256];
      ST_CHAR lnNs[256];
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } NamPlt;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } EEHealth;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } EEName;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } Hz;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaWatt;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaVolAmpr;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaVolAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaRmsAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaRmsVol;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaTuWatt;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaTsWatt;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaAmpTm;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaKFact;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaTdFact;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdOddAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdEvnAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } TddAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } TddOddAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } TddEvnAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdVol;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdOddVol;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdEvnVol;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaCfAmp;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaCfVol;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HaTiFact;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } HzSet;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } NumCyc;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdAVal;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdVVal;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdATmms;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } ThdVTmms;
    struct
      {
      ST_CHAR cdcNs[256];
      ST_CHAR cdcName[256];
      ST_CHAR dataNs[256];
      } NomA;
    } EX;
  } IEC_MHAN_TDEF;

typedef ST_INT16 I16_TDEF;

typedef ST_UINT32 U32_TDEF;

typedef MMS_UTC_TIME array_type1_TDEF[5];

typedef MMS_BTIME6 array_type2_TDEF[5];

typedef ST_INT16 array_type3_TDEF[5];

typedef struct
  {
  ST_INT32 arr_int[5];
  ST_FLOAT arr_float[5];
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } arr_bvstr[5];
  struct     /* OVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[54];
    } arr_ovstr[5];
  struct     /* BVstring */
    {
    ST_INT16 len_1;
    ST_UCHAR data_1[2];
    } bvstr_1[5];
  struct     /* OVstring */
    {
    ST_INT16 len_2;
    ST_UCHAR data_2[54];
    } ovstr_2[5];
  ST_UCHAR arr_bstr[5][7];
  ST_UCHAR arr_ostr[5][54];
  MMS_BTIME6 arr_bt6[5];
  ST_INT32 arr_bt4[5];
  ST_INT32 bt4;
  MMS_UTC_TIME arr_t[5];
  MMS_UTC_TIME arr_3[5];
  MMS_UTC_TIME arr_4[5];
  MMS_UTC_TIME utc_5;
  MMS_UTC_TIME utc_6;
  ST_INT32 i32_7;
  ST_INT32 i32_8;
  ST_INT32 arr_9[5];
  ST_INT32 arr_10[5];
  } array_type4_TDEF;

typedef struct
  {
  ST_CHAR SrcName[9];
  ST_UINT16 SrcPhsCT;
  ST_UINT16 SrcGndCT;
  ST_UINT16 SrcPhsVT;
  } SRCCONFIG_TDEF[6];

typedef struct
  {
  ST_INT16 a;
  ST_INT32 b;
  ST_INT16 c[5];
  struct
    {
    ST_INT16 da;
    ST_INT32 db;
    } d[2];
  } ARR_TYPE_TDEF;

/************************************************************************/
#endif /* if defined (USE_MMS_TYPEDEFS) */
/************************************************************************/

/************************************************************************/
/* UCA Runtime Type Function Indexes                                    */
/* These are generated by Foundry and should not be changed             */

#define U_STRING_OFFSET_RD_IND_FUN_INDEX	0
#define U_UINT8_OFFSET_RD_IND_FUN_INDEX	1
#define MVLU_NULL_RD_IND_INDEX	2
#define MVLU_RPTENA_RD_IND_FUN_INDEX	3
#define MVLU_RPTID_RD_IND_FUN_INDEX	4
#define MVLU_DATSETNA_RD_IND_FUN_INDEX	5
#define MVLU_OPTFLDS_RD_IND_FUN_INDEX	6
#define MVLU_BUFTIM_RD_IND_FUN_INDEX	7
#define MVLU_TRGS_RD_IND_FUN_INDEX	8
#define MVLU_SQNUM_RD_IND_FUN_INDEX	9
#define MVLU_TRGOPS_RD_IND_FUN_INDEX	10
#define MVLU_RBEPD_RD_IND_FUN_INDEX	11
#define MVLU_INTGPD_RD_IND_FUN_INDEX	12
#define U_PBRO_ST_OUT_RD_IND_FUN_INDEX	13
#define U_PBRO_ST_TAR_RD_IND_FUN_INDEX	14
#define U_PBRO_ST_FCTDS_B2_RD_IND_FUN_INDEX	15
#define U_PBRO_ST_FCTDS_Q_RD_IND_FUN_INDEX	16
#define U_PBRO_ST_FCTDS_T_RD_IND_FUN_INDEX	17
#define U_PBRO_ST_AUXIN1_RD_IND_FUN_INDEX	18
#define U_PBRO_ST_PUGRP_RD_IND_FUN_INDEX	19
#define U_PBRO_SG_PU_PHSI_RD_IND_FUN_INDEX	20
#define U_PBRO_SG_PU_NEUTI_RD_IND_FUN_INDEX	21
#define U_PBRO_SG_PU_HZI_RD_IND_FUN_INDEX	22
#define U_NO_READ_ALLOWED_INDEX	23
#define MVLU_SBO_SELECT_RD_IND_INDEX	24
#define MVLU_RESV_RD_IND_FUN_INDEX	25
#define MVLU_CONFREV_RD_IND_INDEX	26
#define MVLU_GI_RD_IND_INDEX	27
#define MVLU_SQNUM_INT16U_RD_IND_FUN_INDEX	28
#define MVLU_PURGEBUF_RD_IND_INDEX	29
#define MVLU_ENTRYID_RD_IND_INDEX	30
#define MVLU_TIMEOFENTRY_RD_IND_INDEX	31
#define HAR_MAG_I_RD_IND_INDEX	32
#define HAR_MAG_F_RD_IND_INDEX	33
#define HAR_ANG_I_RD_IND_INDEX	34
#define HAR_ANG_F_RD_IND_INDEX	35
#define U_INT32_OFFSET_RD_IND_FUN_INDEX	36


#define U_NO_WRITE_ALLOWED_INDEX	0
#define MVLU_NULL_WR_IND_INDEX	1
#define MVLU_RPTENA_WR_IND_FUN_INDEX	2
#define MVLU_RPTID_WR_IND_FUN_INDEX	3
#define MVLU_OPTFLDS_WR_IND_FUN_INDEX	4
#define MVLU_BUFTIM_WR_IND_FUN_INDEX	5
#define MVLU_TRGS_WR_IND_FUN_INDEX	6
#define MVLU_SQNUM_WR_IND_FUN_INDEX	7
#define MVLU_TRGOPS_WR_IND_FUN_INDEX	8
#define MVLU_RBEPD_WR_IND_FUN_INDEX	9
#define MVLU_INTGPD_WR_IND_FUN_INDEX	10
#define MVLU_SBO_OPERATE_WR_IND_INDEX	11
#define MVLU_RESV_WR_IND_FUN_INDEX	12
#define MVLU_GI_WR_IND_INDEX	13
#define MVLU_PURGEBUF_WR_IND_INDEX	14
#define MVLU_ENTRYID_WR_IND_INDEX	15
#define U_INT32_OFFSET_WR_IND_FUN_INDEX	16

/************************************************************************/
/* UCA Read/Write Indication function external declarations */
/* These functions must be provided externally              */

ST_VOID u_string_offset_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_uint8_offset_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_null_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_rptena_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_rptid_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_datsetna_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_optflds_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_buftim_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_trgs_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_sqnum_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_trgops_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_rbepd_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_intgpd_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_st_out_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_st_tar_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_st_fctds_b2_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_st_fctds_q_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_st_fctds_t_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_st_auxin1_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_st_pugrp_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_sg_pu_phsi_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_sg_pu_neuti_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_pbro_sg_pu_hzi_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_no_read_allowed (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_sbo_select_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_resv_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_confrev_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_gi_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_sqnum_int16u_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_purgebuf_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_entryid_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID mvlu_timeofentry_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID har_mag_i_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID har_mag_f_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID har_ang_i_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID har_ang_f_rd_ind (MVLU_RD_VA_CTRL *mvluRdVaCtrl);
ST_VOID u_int32_offset_rd_ind_fun (MVLU_RD_VA_CTRL *mvluRdVaCtrl);

ST_VOID u_no_write_allowed (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_null_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_rptena_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_rptid_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_optflds_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_buftim_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_trgs_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_sqnum_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_trgops_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_rbepd_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_intgpd_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_sbo_operate_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_resv_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_gi_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_purgebuf_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID mvlu_entryid_wr_ind (MVLU_WR_VA_CTRL *mvluWrVaCtrl);
ST_VOID u_int32_offset_wr_ind_fun (MVLU_WR_VA_CTRL *mvluWrVaCtrl);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef FOUNDRY_OUTPUT_HEADER_INCLUDED */

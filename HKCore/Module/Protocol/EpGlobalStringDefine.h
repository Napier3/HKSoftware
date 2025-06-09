// EpGlobalDefine.h
//////////////////////////////////////////////////////////////////////

#if !defined(_EPGLOBALSTRINGDEFINE_H__)
#define _EPGLOBALSTRINGDEFINE_H__


//////////////////////////////////////////////////////////////////////////
//规约标示ID
static const CString g_strEpFrameLength    = _T("len");
static const CString g_strEpFrameStart     = _T("start");
static const CString g_strEpFrameControl   = _T("control");
static const CString g_strEpFrameLinkAddr  = _T("link-addr");
static const CString g_strEpFrameEnd       = _T("end");
static const CString g_strEpFrameSumChk    = _T("sum-chk");
static const CString g_strEpAsduType       = _T("type");
static const CString g_strEpAsduVSQ        = _T("vsq");
static const CString g_strEpAsduCOT        = _T("cot");
static const CString g_strEpAsduAddr       = _T("addr");
static const CString g_strEpAsduTime       = _T("tm");

static const CString g_strEpQDS          = _T("QDS");
static const CString g_strEpQDS_OV       = _T("OV");
static const CString g_strEpQDS_BL       = _T("BL");
static const CString g_strEpQDS_SB       = _T("SB");
static const CString g_strEpQDS_NT       = _T("NT");
static const CString g_strEpQDS_IV       = _T("IV");

static const CString g_strEpQOS          = _T("QOS");
static const CString g_strEpQOS_SE       = _T("SE");
static const CString g_strEpQOS_QL       = _T("QL");

static const CString g_strEpQOI          = _T("QOI");

static const CString g_strEpFloat        = _T("float");

static const CString g_strEpDeviceAddr   = _T("dv-addr");
static const CString g_strEpFuncCode     = _T("func-code");
static const CString g_strEpCRC          = _T("crc");
static const CString g_strEpLRC          = _T("lrc");
static const CString g_strEpCount        = _T("Count");
static const CString g_strEpSQ        = _T("SQ");
static const CString g_strEpAsduInfOAddr = _T("o-addr");
static const CString g_strEpAsduSIQ      = _T("siq");
static const CString g_strEpAsduSPI      = _T("SPI");

void Ep_InitGetFrameAnalyse();
CString Ep_GetFrameAnalyseString(const CString &strID);
CString Ep_GetFrameAnalyseStringValue(const CString &strID, const CString &strValue);
// CString Ep_GetFrameAnalyseStringValue(const CString &strID, long nValue);

#endif // !defined(_EPGLOBALSTRINGDEFINE_H__)

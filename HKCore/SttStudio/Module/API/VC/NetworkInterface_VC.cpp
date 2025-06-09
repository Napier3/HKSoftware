
#include "../NetworkInterface.h"


long stt_net_get_ip(CStringArray &astrIP, CStringArray &astrMask)
{
	astrIP.Add(_T("192.168.1.103"));
	astrIP.Add(_T("192.168.100.10"));

	astrMask.Add(_T("255.255.255.0"));
	astrMask.Add(_T("255.255.255.0"));

	return 2;
}

long stt_net_set_ip(CStringArray &atrIP, CStringArray &astrMask, long nIPBeginIndex)
{

	return 1;
}

long stt_net_set_gateway(const CStringArray &astrGateWay,long* nMetric)
{
	return 1;
}
void stt_file_get_deviceip(CString &strIP, CString &strMask)
{

}
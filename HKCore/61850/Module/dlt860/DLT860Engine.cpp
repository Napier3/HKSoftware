#include "stdafx.h"
#include "DLT860Engine.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"

#ifdef USE_61850CLient_STRCUT

void mms_u64Time_to_utc_time(uint64_t u64Time, MMS_UTC_TIME  &utctime)
{
	MMS_BTIME6 bTm6;
	MMS_BTOD btod;
	asn1_convert_timet_to_btime6(u64Time/1000, &bTm6);
	btod.form = MMS_BTOD6;
	btod.day = bTm6.day;
	btod.ms = bTm6.ms;
	btod.ms += u64Time%1000;

	asn1_convert_btod_to_utc(&btod, &utctime);
}

#endif


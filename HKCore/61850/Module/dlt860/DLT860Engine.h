#pragma once

#include "../61850ClientConfig/61850ClientConfig.h"

#ifdef USE_61850CLient_STRCUT
void mms_u64Time_to_utc_time(uint64_t u64Time, MMS_UTC_TIME  &utctime);
#endif
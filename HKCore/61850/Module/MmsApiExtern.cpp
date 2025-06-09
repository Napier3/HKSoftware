// MmsApi.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MmsApi.h"
#include "EnumType.h"
#include "MmsGlobal.h"
#include "../../Module/System/TickCount32.h"
#include "../../Module/GpsPcTime/GpsPcTime.h"
#include "XLanguageResourcePp_Mms.h"
#include "../../../sm4.h"
#include "../../Module/API/FileApi.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
#include "../../Module/API/StringConvert/String_Gbk_To_Utf8.h"
#include "MmsWriteXml.h"



void mms_UpdateDeviceState(long nDeviceIndex)
{

}

void mms_UpdateDeviceState(ACSI_NODE *pDevice)
{

}

void mms_UpdateDatasetState(long nDeviceIndex, long nLDIndex, long nDsIndex)
{

}

void mms_UpdateDatasetState(LD_DATASET_INFO *pLD_INFO)
{

}


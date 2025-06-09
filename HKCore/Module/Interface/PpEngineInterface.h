//////////////////////////////////////////////////////////////////////////
//PpEngineInterface.h
//规约引擎组件的接口定义和扩展文件

#ifndef _PPENGINE_INTERFACE_H__
#define _PPENGINE_INTERFACE_H__

static const BSTR g_bstrPpEngineTag_Name = L"name";
static const BSTR g_bstrPpEngineTag_Value = L"value";
static const BSTR g_bstrPpEngineTag_ItemIndex = L"item-index";
static const BSTR g_bstrPpEngineTag_ID = L"id";

//#define _use_PpEngine_import

#ifdef _use_PpEngine_import
#import "PpEngine.tlb"
#else
#include "PpEngineClass.h"
#endif

#endif

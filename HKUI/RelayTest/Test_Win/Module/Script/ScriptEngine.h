#ifndef __PONOVO_SCRIPT_ENGINE_2018_H__
#define __PONOVO_SCRIPT_ENGINE_2018_H__


#ifdef SCRIPT_ENGINE_EXPORTS
#define SCRIPT_ENGINE_API extern "C" __declspec(dllexport)
#else
#define SCRIPT_ENGINE_API  extern "C" __declspec(dllimport)
#endif

typedef enum tagLanguage
{
	LT_UNKNOWN_SCRIPT = 0,
	LT_VB_SCRIPT ,
	LT_JSCRIPT,
} LanguageType;

typedef const unsigned short* LPCTSTR;

// 创建脚本引擎的句柄,后续函数都需要这个句柄
SCRIPT_ENGINE_API void*  CreateScriptEngine( LanguageType language );

// 获取当前的脚本引擎语言
SCRIPT_ENGINE_API LanguageType  GetScriptLanguage(void* handle );

// 获取脚本中的函数的个数
SCRIPT_ENGINE_API int  GetScriptFunctionCount(void* handle);

// 使用索引方式获取函数的名称
SCRIPT_ENGINE_API LPCTSTR  GetScriptFunctionNameAt(void* handle, int index);

// 重置或者复位脚本引擎
SCRIPT_ENGINE_API void  ResetScriptEngine(void* handle);

// 加载脚本字符串
SCRIPT_ENGINE_API bool  LoadScript(void* handle, LPCTSTR szScriptText );

// 运行脚本中的函数
SCRIPT_ENGINE_API double  ExecuteScriptFunction(void* handle, LPCTSTR szFunctionName, const double* paramList, int paramCnt, bool* pErr );

// 销毁脚本引擎
SCRIPT_ENGINE_API void DestroyScriptEngine(  void* handle );


#endif 

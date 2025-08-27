#pragma once
#include "PluginTCalcFunc.h"

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
	__declspec(dllexport) BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun);
#ifdef __cplusplus
}
#endif //__cplusplus
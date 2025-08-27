#include "windows.h"
#include "Export.h"
#include "PluginFuncs.h"

//¼ÓÔØµÄº¯Êý
PluginTCalcFuncInfo g_CalcFuncSets[] =
{
	{1,(pPluginFUNC)&B1ColseVolumeCheck},
	{0,NULL},
};


BOOL RegisterTdxFunc(PluginTCalcFuncInfo** pFun)
{
	if (*pFun == NULL)
	{
		(*pFun) = g_CalcFuncSets;
		return TRUE;
	}
	return FALSE;
}


BOOL APIENTRY DllMain(HANDLE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	return TRUE;
}
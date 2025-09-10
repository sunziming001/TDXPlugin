#include "windows.h"
#include "Export.h"
#include "PluginFuncs.h"

//¼ÓÔØµÄº¯Êý
PluginTCalcFuncInfo g_CalcFuncSets[] =
{
	{1,(pPluginFUNC)&B1ColseVolumeView},
	{2,(pPluginFUNC)&LoseShareRate},
	{3,(pPluginFUNC)&B1ColseVolumeCheck},
	{4,(pPluginFUNC)&AverageLoseRateFromPreHigh},
	{100,(pPluginFUNC)&SetArgs0_1_2},
	{101,(pPluginFUNC)&SetArgs3_4_5},
	{102,(pPluginFUNC)&SetArgs6_7_8},
	{0,NULL}
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
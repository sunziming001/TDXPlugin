#pragma once
#include "PluginTCalcFunc.h"

typedef struct _GlobalArgument {
	int dataCnt = 0;
	float* data = nullptr;
}GlobalArgument;



void SetArgs0_1_2(int cnt, float* output, float* arg0, float* arg1, float* arg2);
void SetArgs3_4_5(int cnt, float* output, float* arg3, float* arg4, float* arg5);
void SetArgs6_7_8(int cnt, float* output, float* arg6, float* arg7, float* arg8);

/*!
@brief B1买点的有效性检查，创出新高后，所有的阴量应该都是缩量，新高前量能应有异动
@param cnt 周期数量
@param output 输出数组，当天周期有效为1.0，无效为0.0
@param high 最高价数组
@param colse 收盘价数组
@param volume 成交量数组
@param arg0 阴量缩量偏差，默认为1.1
@param arg1 新高前的异动观察周期，默认为10
@param arg2 新高前的异动最低次数，默认为4
*/
void B1ColseVolumeView(int cnt, float* output, float* high, float* close, float* volume);

/*!
@brief B1买点的有效性检查，创出新高后，所有的阴量应该都是缩量，新高前量能应有异动
@param cnt 周期数量
@param output 输出数组，当天周期有效为1.0，无效为0.0(为了方便检查，如果检查期间有一天无效，则后面的即使缩量也判断为无效)
@param high 最高价数组
@param colse 收盘价数组
@param volume 成交量数组
@param arg0 阴量缩量偏差，默认为1.1
@param arg1 新高前的异动观察周期，默认为10
@param arg2 新高前的异动最低次数，默认为4
*/
void B1ColseVolumeCheck(int cnt, float* output, float* high, float* close, float* volume);


void LoseShareRate(int cnt, float* output, float* high, float* low, float* close);
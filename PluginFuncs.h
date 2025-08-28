#pragma once
#include "PluginTCalcFunc.h"

void SetArgs0_1_2(int cnt, float* output, float* arg0, float* arg1, float* arg2);
void SetArgs3_4_5(int cnt, float* output, float* arg3, float* arg4, float* arg5);
void SetArgs6_7_8(int cnt, float* output, float* arg6, float* arg7, float* arg8);

void B1ColseVolumeView(int cnt, float* output, float* close, float* volume, float* uk2);
void B1ColseVolumeCheck(int cnt, float* output, float* close, float* volume, float* uk2);
void LoseShareRate(int cnt, float* output, float* high, float* low, float* close);
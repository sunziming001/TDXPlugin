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
@brief B1������Ч�Լ�飬�����¸ߺ����е�����Ӧ�ö����������¸�ǰ����Ӧ���춯
@param cnt ��������
@param output ������飬����������ЧΪ1.0����ЧΪ0.0
@param high ��߼�����
@param colse ���̼�����
@param volume �ɽ�������
@param arg0 ��������ƫ�Ĭ��Ϊ1.1
@param arg1 �¸�ǰ���춯�۲����ڣ�Ĭ��Ϊ10
@param arg2 �¸�ǰ���춯��ʹ�����Ĭ��Ϊ4
*/
void B1ColseVolumeView(int cnt, float* output, float* high, float* close, float* volume);

/*!
@brief B1������Ч�Լ�飬�����¸ߺ����е�����Ӧ�ö����������¸�ǰ����Ӧ���춯
@param cnt ��������
@param output ������飬����������ЧΪ1.0����ЧΪ0.0(Ϊ�˷����飬�������ڼ���һ����Ч�������ļ�ʹ����Ҳ�ж�Ϊ��Ч)
@param high ��߼�����
@param colse ���̼�����
@param volume �ɽ�������
@param arg0 ��������ƫ�Ĭ��Ϊ1.1
@param arg1 �¸�ǰ���춯�۲����ڣ�Ĭ��Ϊ10
@param arg2 �¸�ǰ���춯��ʹ�����Ĭ��Ϊ4
*/
void B1ColseVolumeCheck(int cnt, float* output, float* high, float* close, float* volume);


void LoseShareRate(int cnt, float* output, float* high, float* low, float* close);
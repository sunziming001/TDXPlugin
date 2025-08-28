#include "PluginFuncs.h"
static float g_arg[9] = { 0.0f };


void resetAllArgs()
{
	for (int i = 0; i < sizeof(g_arg) / sizeof(float); i++)
	{
		g_arg[i] = 0.0f;
	}
}


void resetOutput(float* output, int cnt, float val = 0.0f)
{
	for (int i = 0; i < cnt; i++)
	{
		output[i] = val;
	}
}

int findHighest(float* intput, int cnt, int startIndex, int endIndex)
{
	int ret = -1;
	if (startIndex >= 0
		&& endIndex <= cnt - 1)
	{
		ret = startIndex;
		for (int i = startIndex; i <= endIndex; i++)
		{
			if (intput[ret] <= intput[i])
			{
				ret = i;
			}
		}
	}
	return ret;
}

int findLowest(float* intput, int cnt, int startIndex, int endIndex)
{
	int ret = -1;
	if (startIndex >= 0
		&& endIndex <= cnt - 1)
	{
		ret = startIndex;
		for (int i = startIndex; i <= endIndex; i++)
		{
			if (intput[ret] >= intput[i])
			{
				ret = i;
			}
		}
	}
	return ret;
}

int findPreHighest(float* high, int cnt, int preStartIndex, int preEndIndex)
{
	int preHighestIdx = -1;
	float preHighest = 0.0;
	int notHighestCnt = 0;
	int maxNotHighestCnt = 10;
	if (preStartIndex >= 0 && preEndIndex <= cnt - 1)
	{
		for (int i = preEndIndex; i >= preStartIndex; i--)
		{
			if (preHighest <= high[i])
			{
				preHighest = high[i];
				preHighestIdx = i;
				notHighestCnt = 0;
			}
			else
			{
				notHighestCnt++;
				if (notHighestCnt >= maxNotHighestCnt)
				{
					break;
				}
			}
		}

	}
	return preHighestIdx;
}

void SetArgs0_1_2(int cnt, float* output, float* arg0, float* arg1, float* arg2)
{
	if (cnt > 0)
	{
		g_arg[0] = arg0[0];
		g_arg[1] = arg1[0];
		g_arg[2] = arg2[0];
	}

}

void SetArgs3_4_5(int cnt, float* output, float* arg3, float* arg4, float* arg5)
{
	if (cnt > 0)
	{
		g_arg[3] = arg3[0];
		g_arg[4] = arg4[0];
		g_arg[5] = arg5[0];
	}
}

void SetArgs6_7_8(int cnt, float* output, float* arg6, float* arg7, float* arg8)
{
	if (cnt > 0)
	{
		g_arg[6] = arg6[0];
		g_arg[7] = arg7[0];
		g_arg[8] = arg8[0];
	}
}

void B1ColseVolumeView(int cnt, float* output, float* high, float* close, float* volume)
{
	int obsWidth = 40;
	int highestIdx = -1;
	float curClose = 0.0f;
	float curVolume = 0.0f;
	float preClose = 0.0f;
	float preVolume = 0.0f;
	resetOutput(output, cnt);

	for (int j = cnt - 1; j >= 0; j--)
	{
		highestIdx = findPreHighest(high, cnt, j - obsWidth, j);
		j = highestIdx;
		if (highestIdx >= 0 && highestIdx < cnt - 1)
		{
			for (int i = highestIdx + 1; i <= cnt - 1; i++)
			{
				curClose = close[i];
				curVolume = volume[i];
				preClose = close[i - 1];
				preVolume = volume[i - 1];
				if (curClose < preClose)	//阴量
				{
					if (curVolume <= 1.10f * preVolume)
					{
						output[i] = 1.0f;

					}
					else {
						output[i] = 0.0f;
					}
				}
				else {						//阳量
					output[i] = 1.0f;
				}
			}
		}

	}

	resetAllArgs();
}


void B1ColseVolumeCheck(int cnt, float* output, float* high, float* close, float* volume)
{
	int obsWidth = 40;
	int highestIdx = -1;
	float curClose = 0.0f;
	float curVolume = 0.0f;
	float preClose = 0.0f;
	float preVolume = 0.0f;
	resetOutput(output, cnt);

	for (int j = cnt - 1; j >= 0; j--)
	{
		highestIdx = findPreHighest(high, cnt, j - obsWidth, j);
		j = highestIdx;
		if (highestIdx >= 0 && highestIdx < cnt - 1)
		{
			for (int i = highestIdx + 1; i <= cnt - 1; i++)
			{
				curClose = close[i];
				curVolume = volume[i];
				preClose = close[i - 1];
				preVolume = volume[i - 1];
				if (curClose < preClose)	//阴量
				{
					if (curVolume <= 1.10f * preVolume)
					{
						output[i] = 1.0f;

					}
					else {
						output[i] = 0.0f;
						break;
					}
				}
				else {						//阳量
					output[i] = 1.0f;
				}
			}
		}

	}

	resetAllArgs();
}

void LoseShareRate(int cnt, float* output, float* high, float* low, float* close)
{
	int obsWidth = 40;
	float loseRate = 0.99f;

	int highestIdx = -1;
	int lowestIdx = -1;
	float curHigh = 0.0f;
	float curLow = 0.0f;
	float curClose = 0.0f;
	float rate = 0.0f;

	resetOutput(output, cnt);

	if (g_arg[0] != 0.0f)
	{
		loseRate = g_arg[0];
	}

	for (int i = cnt - 1; i >= 0; i--)
	{
		highestIdx = findPreHighest(high, cnt, i-obsWidth, i);
		lowestIdx = findLowest(low, cnt, highestIdx, i);

		if (highestIdx >= 0 && lowestIdx >= 0)
		{
			curHigh = high[highestIdx];
			curLow = low[lowestIdx] * loseRate;
			curClose = close[i];
			rate = (curHigh - curClose) / (curClose - curLow);
			output[i] = rate;
		}	
	}

	//resetAllArgs();
}
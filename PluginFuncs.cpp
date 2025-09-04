#include "PluginFuncs.h"


static GlobalArgument g_arg[9] = { 0.0f };


void resetAllArgs()
{
	for (int i = 0; i < sizeof(g_arg) / sizeof(GlobalArgument); i++)
	{
		memset(g_arg[i].data, 0, sizeof(float) * g_arg[i].dataCnt);
	}
}

void setGlobalArgument(GlobalArgument& arg, int cnt, float* data)
{
	if (arg.dataCnt < cnt)
	{
		if (arg.data != nullptr)
		{
			free(arg.data);
		}

		arg.data = (float*)calloc(1, cnt * sizeof(float));
	}

	if (arg.data != nullptr)
	{
		memset(arg.data, 0, arg.dataCnt * sizeof(float));

		memcpy(arg.data, data, cnt * sizeof(float));
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

float average(float* data, int cnt, int idx, int dur)
{
	float ret = 0.0f;
	float sum = 0.0f;
	int trueCnt = 0;
	for (int i = idx - dur+1; i <= idx; i++)
	{
		if (i >= 0 && i < cnt)
		{
			sum += data[i];
			trueCnt++;
		}
	}

	ret = sum / trueCnt;
	return ret;
}


int calcTransactionCnt(float* volume, int cnt, int idx, int dur,int obsWidth)
{
	int ret = 0;
	float tmpAverage = 0.0f;
	for (int i = idx - obsWidth + 1; i <= idx; i++)
	{
		tmpAverage = average(volume, cnt, idx, dur);
		if (volume[i] >= tmpAverage)
		{
			ret++;
		}
	}

	return ret;
}


void SetArgs0_1_2(int cnt, float* output, float* arg0, float* arg1, float* arg2)
{
	if (cnt > 0)
	{
		setGlobalArgument(g_arg[0], cnt, arg0);
		setGlobalArgument(g_arg[1], cnt, arg1);
		setGlobalArgument(g_arg[2], cnt, arg2);
	}

}

void SetArgs3_4_5(int cnt, float* output, float* arg3, float* arg4, float* arg5)
{
	if (cnt > 0)
	{
		setGlobalArgument(g_arg[3], cnt, arg3);
		setGlobalArgument(g_arg[4], cnt, arg4);
		setGlobalArgument(g_arg[5], cnt, arg5);
	}
}

void SetArgs6_7_8(int cnt, float* output, float* arg6, float* arg7, float* arg8)
{
	if (cnt > 0)
	{
		setGlobalArgument(g_arg[6], cnt, arg6);
		setGlobalArgument(g_arg[7], cnt, arg7);
		setGlobalArgument(g_arg[8], cnt, arg8);
	}
}

void B1ColseVolumeView(int cnt, float* output, float* high, float* close, float* volume)
{
	int obsWidth = 40;
	int highestIdx = -1;
	int lastHighestIdx = cnt - 1;
	float curClose = 0.0f;
	float curVolume = 0.0f;
	float preClose = 0.0f;
	float preVolume = 0.0f;
	float deviation = 1.10f;
	int transactionCnt = 0;
	int transactionObsWidth = 10;
	int minTransactionCnt = 4;

	resetOutput(output, cnt);

	if (g_arg[0].data[0] != 0.0f)
	{
		deviation = g_arg[0].data[0];
	}

	if (g_arg[1].data[0] != 0.0f)
	{
		transactionObsWidth = static_cast<int>(g_arg[1].data[0]);
	}

	if (g_arg[2].data[0] != 0.0f)
	{
		minTransactionCnt = static_cast<int>(g_arg[2].data[0]);
	}


	for (int j = cnt - 1; j >= 0; j--)
	{
		highestIdx = findPreHighest(high, cnt, j - obsWidth, j);
		transactionCnt = calcTransactionCnt(volume, cnt, highestIdx, 5, transactionObsWidth);
		j = highestIdx;
		if (highestIdx >= 0 && highestIdx < cnt - 1)
		{
			for (int i = highestIdx + 1; i <= lastHighestIdx; i++)
			{
				curClose = close[i];
				curVolume = volume[i];
				preClose = close[i - 1];
				preVolume = volume[i - 1];
				if (curClose < preClose)	//阴量
				{
					if (curVolume <= deviation * preVolume && transactionCnt>= minTransactionCnt)
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
			lastHighestIdx = highestIdx;
		}

	}

	resetAllArgs();
}


void B1ColseVolumeCheck(int cnt, float* output, float* high, float* close, float* volume)
{
	int obsWidth = 40;
	int highestIdx = -1;
	int lastHighestIdx = cnt - 1;
	float curClose = 0.0f;
	float curVolume = 0.0f;
	float preClose = 0.0f;
	float preVolume = 0.0f;
	float deviation = 1.10f;
	int transactionCnt = 0;
	int transactionObsWidth = 10;
	int minTransactionCnt = 4;

	resetOutput(output, cnt);

	if (g_arg[0].data[0] != 0.0f)
	{
		deviation = g_arg[0].data[0];
	}

	if (g_arg[0].data[0] != 0.0f)
	{
		deviation = g_arg[0].data[0];
	}

	if (g_arg[1].data[0] != 0.0f)
	{
		transactionObsWidth = static_cast<int>(g_arg[1].data[0]);
	}

	if (g_arg[2].data[0] != 0.0f)
	{
		minTransactionCnt = static_cast<int>(g_arg[2].data[0]);
	}

	for (int j = cnt - 1; j >= 0; j--)
	{
		highestIdx = findPreHighest(high, cnt, j - obsWidth, j);
		transactionCnt = calcTransactionCnt(volume, cnt, highestIdx, 5, transactionObsWidth);

		j = highestIdx;
		if (highestIdx >= 0 && highestIdx < cnt-1)
		{
			for (int i = highestIdx + 1; i <= lastHighestIdx; i++)
			{
				curClose = close[i];
				curVolume = volume[i];
				preClose = close[i - 1];
				preVolume = volume[i - 1];
				if (curClose < preClose)	//阴量
				{
					if (curVolume <= deviation * preVolume && transactionCnt >= minTransactionCnt)
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
		lastHighestIdx = highestIdx;

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

	if (g_arg[0].data[0] != 0.0f)
	{
		loseRate = g_arg[0].data[0];
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
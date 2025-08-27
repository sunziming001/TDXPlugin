#include "PluginFuncs.h"

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

void B1ColseVolumeCheck(int cnt, float* output, float* high, float* close, float* volume)
{
	int obsWidth = 40;
	int highestIdx = -1;
	float curClose = 0.0f;
	float curVolume = 0.0f;
	float preClose = 0.0f;
	float preVolume = 0.0f;
	resetOutput(output, cnt);
	if (cnt >= obsWidth+1)
	{
		highestIdx = findHighest(high, cnt, cnt - obsWidth, cnt-1);
		if (highestIdx >= 0 && highestIdx<cnt-1)
		{
			for (int i = highestIdx+1; i < cnt - 1; i++)
			{
				curClose = close[i];
				curVolume = volume[i];
				preClose = close[i - 1];
				preVolume = volume[i - 1];
				if (curClose < preClose)	//ÒõÁ¿
				{
					if (curVolume <= preVolume)
					{
						output[i] = 1.0f;
					}
					else {
						output[i] = 0.0f;
						break;
					}
				}
				else {						//ÑôÁ¿
					output[i] = 1.0f;
				}

			}

		}
	}
}

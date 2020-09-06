#define YYYY 0
#define MM 1
#define DD 2
#define HH 3
#define mm 4
#define SS 5

//----------
//WARNING:大写MM代表月份，小写mm代表分钟！切勿混用！
//----------


//x86/x64平台的int为4位


//每月天数
int dayOfMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//二月按28算的




//时钟缓冲区
int timeBuffer[6];

/*
解析时间戳信息到年月日时分秒
@param ts 10位时间戳信息,4字节
@param timeZone 时区,相对格林威治时间的偏移
@param *buffer 用于存储转换结果的缓冲区,转换后的结果每位占2字节
*/
int praseTimestamp(int timeStamp, float timeZone, int timeBuffer[])
{
	//闰年标记
	int leapYear = 0;
	unsigned char i = 0;

	//中国区需要补28800秒，即8小时
	//计算时间戳的天数
	int days =(int)(timeStamp + 3600 * timeZone) / 86400 + 1;
	//四年周期数
	int year4 = (int)(days / 1461);
	//不足四年周期剩下的天数
	int remain = (int)(days % 1461);

	//得到时间戳范围内满足四年周期的年数
	timeBuffer[YYYY] = 1970 + year4 * 4;

	//剩下的天数小于一年@365不处理
	if (remain < 365)
	{
		//@占位保留
	//第二年@365+365
	}
	else if (remain < 730)
	{
		timeBuffer[YYYY]++;
		remain -= 365;
		//第三年@365+365+365
	}
	else if (remain < 1095)
	{
		timeBuffer[YYYY] += 2;
		remain -= 730;
		//第四年
	}
	else
	{
		timeBuffer[YYYY] += 3;
		remain -= 1095;
		leapYear = 1;
	}

	//剩下一年内的天数 用12个月天数循环减
	//直到剩下天数<=0 则找到对应月份
	//剩下天数则为日期
	for (i = 0; i < 12; i++) {

		//year4复用于暂存每月天数
		//闰年2月补一天
		year4 = (i == 1 && leapYear) ? (dayOfMonth[i] + 1) : dayOfMonth[i];

		//days复用于暂存减去当前月份天数的剩余天数
		days = remain - year4;

		if (days <= 0)
		{

			timeBuffer[MM] = i + 1;
			if (days == 0)
			{
				timeBuffer[DD] = year4;

			}
			else
			{
				timeBuffer[DD] = remain;
			}
			break;
		}
		remain = (int)days;
	}

	timeBuffer[SS] = (int)(timeStamp % 60);

	timeBuffer[mm] = (int)(timeStamp / 60 % 60);

	while (timeStamp > 86400)
	{
		timeStamp -= 86400;
	}

	if (timeStamp == 86400)
	{
		timeBuffer[HH] = 0;
	}
	else
	{
		//中国区需要+8h
		timeBuffer[HH] = (int)(timeStamp / 3600) + timeZone;
		//这里如果是非整数的timeZone将出现进一的情况，暂不处理
	}

	if (timeBuffer[HH] >= 24)
	{
		timeBuffer[HH] -= 24;
	}
	return 0;
}

/*
将时间信息转换成时间戳
@param timeZone 时区,相对格林威治时间的偏移
@param *buffer 本地时间记录缓冲区
*/
int makeTimestamp(int timeZone, int *timeBuffer) 
{
	int timeStamp;
	int remain;//干嘛的？
	int circle;//干嘛的？
	int leapYear = 0;
	int i = 0;

	//1970平,1971平,1972闰,1973平,

	leapYear = ((timeBuffer[YYYY] & 3) == 0) ? 1 : 0;

	circle = timeBuffer[YYYY] - 1970;
	timeStamp = 126230400L * (circle / 4);

	remain = circle % 4;

	//0年(当前年)不处理

	if (remain == 1)
	{
		//+365*24*3600
		timeStamp += 31536000L;
	}
	else if (remain == 2)
	{
		//+365*2*24*3600
		timeStamp += 63072000L;
	}
	else if (remain == 3)
	{
		//+365*2*24*3600+366*24*3600
		timeStamp += 94694400L;
	}

	//处理当前月之前月份的天数的秒数
	for (i = 0; i < timeBuffer[MM] - 1; i++)
	{
		if (i == 1 && leapYear) {
			timeStamp += (dayOfMonth[i] + 1) * 86400L;
		}
		else {
			timeStamp += dayOfMonth[i] * 86400L;
		}
	}

	//处理当前日期之前的天数的秒数
	timeStamp += 86400L * (timeBuffer[DD] - 1);

	//处理当前天小时的秒数
	timeStamp += 3600L * (timeBuffer[HH]);

	//处理当前天分钟的秒数
	timeStamp += 60L * (timeBuffer[mm]);

	//加上当前天的秒数
	timeStamp += timeBuffer[SS];

	//减去时区差
	timeStamp -= (timeZone * 3600);

	return timeStamp;
}
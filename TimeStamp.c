#define YYYY 0
#define MM 1
#define DD 2
#define HH 3
#define mm 4
#define SS 5

//----------
//WARNING:��дMM�����·ݣ�Сдmm������ӣ�������ã�
//----------


//x86/x64ƽ̨��intΪ4λ


//ÿ������
int dayOfMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
//���°�28���




//ʱ�ӻ�����
int timeBuffer[6];

/*
����ʱ�����Ϣ��������ʱ����
@param ts 10λʱ�����Ϣ,4�ֽ�
@param timeZone ʱ��,��Ը�������ʱ���ƫ��
@param *buffer ���ڴ洢ת������Ļ�����,ת����Ľ��ÿλռ2�ֽ�
*/
int praseTimestamp(int timeStamp, float timeZone, int timeBuffer[])
{
	//������
	int leapYear = 0;
	unsigned char i = 0;

	//�й�����Ҫ��28800�룬��8Сʱ
	//����ʱ���������
	int days =(int)(timeStamp + 3600 * timeZone) / 86400 + 1;
	//����������
	int year4 = (int)(days / 1461);
	//������������ʣ�µ�����
	int remain = (int)(days % 1461);

	//�õ�ʱ�����Χ�������������ڵ�����
	timeBuffer[YYYY] = 1970 + year4 * 4;

	//ʣ�µ�����С��һ��@365������
	if (remain < 365)
	{
		//@ռλ����
	//�ڶ���@365+365
	}
	else if (remain < 730)
	{
		timeBuffer[YYYY]++;
		remain -= 365;
		//������@365+365+365
	}
	else if (remain < 1095)
	{
		timeBuffer[YYYY] += 2;
		remain -= 730;
		//������
	}
	else
	{
		timeBuffer[YYYY] += 3;
		remain -= 1095;
		leapYear = 1;
	}

	//ʣ��һ���ڵ����� ��12��������ѭ����
	//ֱ��ʣ������<=0 ���ҵ���Ӧ�·�
	//ʣ��������Ϊ����
	for (i = 0; i < 12; i++) {

		//year4�������ݴ�ÿ������
		//����2�²�һ��
		year4 = (i == 1 && leapYear) ? (dayOfMonth[i] + 1) : dayOfMonth[i];

		//days�������ݴ��ȥ��ǰ�·�������ʣ������
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
		//�й�����Ҫ+8h
		timeBuffer[HH] = (int)(timeStamp / 3600) + timeZone;
		//��������Ƿ�������timeZone�����ֽ�һ��������ݲ�����
	}

	if (timeBuffer[HH] >= 24)
	{
		timeBuffer[HH] -= 24;
	}
	return 0;
}

/*
��ʱ����Ϣת����ʱ���
@param timeZone ʱ��,��Ը�������ʱ���ƫ��
@param *buffer ����ʱ���¼������
*/
int makeTimestamp(int timeZone, int *timeBuffer) 
{
	int timeStamp;
	int remain;//����ģ�
	int circle;//����ģ�
	int leapYear = 0;
	int i = 0;

	//1970ƽ,1971ƽ,1972��,1973ƽ,

	leapYear = ((timeBuffer[YYYY] & 3) == 0) ? 1 : 0;

	circle = timeBuffer[YYYY] - 1970;
	timeStamp = 126230400L * (circle / 4);

	remain = circle % 4;

	//0��(��ǰ��)������

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

	//����ǰ��֮ǰ�·ݵ�����������
	for (i = 0; i < timeBuffer[MM] - 1; i++)
	{
		if (i == 1 && leapYear) {
			timeStamp += (dayOfMonth[i] + 1) * 86400L;
		}
		else {
			timeStamp += dayOfMonth[i] * 86400L;
		}
	}

	//����ǰ����֮ǰ������������
	timeStamp += 86400L * (timeBuffer[DD] - 1);

	//����ǰ��Сʱ������
	timeStamp += 3600L * (timeBuffer[HH]);

	//����ǰ����ӵ�����
	timeStamp += 60L * (timeBuffer[mm]);

	//���ϵ�ǰ�������
	timeStamp += timeBuffer[SS];

	//��ȥʱ����
	timeStamp -= (timeZone * 3600);

	return timeStamp;
}
//UncertaintyFrame-MainCalculator

#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932354626
#define MAXNUM 1000

int ModeIO = -1;
//��A�಻ȷ����1����B2��ABΪ3
int ModeDebug = -1;
//ģʽ˵����Debugģʽ1,����Ϊ0
int ModeCSV = -1;
//�ļ��������ģʽ1
//���ڼ�⵽û�ж�Ӧ�ļ���ʱ���Զ��ͷ�һ��HELP.txtд�����������ʽ
//���ж�ӦIN.txt����IN.csv��ʱ������ִ�����OUT.csv

int main(int argc,char* argv[])
{
	printf("��ӭʹ�ò�ȷ���ȼ�����\n");
	printf("���ֵ����󱦱�\n");

	int timestampBufferTest[50];
	int timenumber = 1234567890;

	float timeZone = 8.0;
	int ptimebuffer = &timestampBufferTest;

	praseTimestamp(timenumber, timeZone, timestampBufferTest);
	
	printf("YYYYMMDDHHmmss%d%d%d%d%d%d", timestampBufferTest[0], timestampBufferTest[1], timestampBufferTest[2], timestampBufferTest[3], timestampBufferTest[4], timestampBufferTest[5]);



	int NumOfData = 0;//��������
	int InputLineMode = 0;//��������1����������2
	while (NumOfData <= 0 && NumOfData > MAXNUM)
	{
		printf("�����������ݵ�����\n");
		scanf("%d", &NumOfData);
		if (NumOfData <= 0)
		{
			printf("�����������С�ڵ���0�����������룡\n");//ERROR
		}
		else if (NumOfData > MAXNUM)
		{
			printf("������������������󣨲�����%d�������������룡\n",MAXNUM);//ERROR
		}
		else
		{
			break;
		}
	}
	while (InputLineMode != 1 && InputLineMode != 2)
	{
		printf("��ѡ���������������ݻ��Ƕ������룿\n");
		printf("��������1����������2\n");
		scanf("%d", &InputLineMode);
		if (InputLineMode != 1 && InputLineMode != 2)
		{
			printf("������ĵ���/����ģʽ���벻�Ϸ������������룡\n");//ERROR
		}
		else
		{
			break;
		}
	}
	//��������
	if (InputLineMode == 1)
	{
		printf("���������ݣ�ÿ�����ݼ��ÿո����\n");
		//
	}
	//��������
	//�û����Զ���ÿ������������Լ�����
	if (InputLineMode == 2)
	{
		printf("��������ÿ������ĸ���\n");
		int NumOfDataPerLine = 0;//ÿ�и���
		scanf("%d", &NumOfDataPerLine);
		int NumOfLine = (int)NumOfData / NumOfDataPerLine;//����=����/ÿ�и���
		int TempCount = 0;//�ֲ���������
		int Tempindex = 0;//�ֲ�ѭ������i
		int Tempjndex = 0;//�ֲ�ѭ������j
		for (Tempindex = 0; Tempindex < NumOfLine; ++Tempindex)
		{
			if (Tempindex != NumOfLine - 1)//�������һ��
			{
				for (Tempjndex = 0; Tempjndex < NumOfDataPerLine; ++Tempjndex)
				{

				}
			}
			else//�����һ��
			{

			}
		}
	}






	return 0;
}

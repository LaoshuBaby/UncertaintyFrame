//UncertaintyFrame-MainCalculator

#include <stdio.h>
#include <math.h>

#define PI 3.1415926535897932354626
#define MAXNUM 1000

int ModeIO = -1;
//仅A类不确定度1，仅B2，AB为3
int ModeDebug = -1;
//模式说明：Debug模式1,否则为0
int ModeCSV = -1;
//文件输入输出模式1
//会在检测到没有对应文件的时候自动释放一个HELP.txt写明输入输出格式
//在有对应IN.txt或者IN.csv的时候正常执行输出OUT.csv

int main(int argc,char* argv[])
{
	printf("欢迎使用不确定度计算器\n");
	printf("快乐的老鼠宝宝\n");

	int timestampBufferTest[50];
	int timenumber = 1234567890;

	float timeZone = 8.0;
	int ptimebuffer = &timestampBufferTest;

	praseTimestamp(timenumber, timeZone, timestampBufferTest);
	
	printf("YYYYMMDDHHmmss%d%d%d%d%d%d", timestampBufferTest[0], timestampBufferTest[1], timestampBufferTest[2], timestampBufferTest[3], timestampBufferTest[4], timestampBufferTest[5]);



	int NumOfData = 0;//数据总数
	int InputLineMode = 0;//单行输入1，多行输入2
	while (NumOfData <= 0 && NumOfData > MAXNUM)
	{
		printf("请您输入数据的总数\n");
		scanf("%d", &NumOfData);
		if (NumOfData <= 0)
		{
			printf("您输入的数据小于等于0，请重新输入！\n");//ERROR
		}
		else if (NumOfData > MAXNUM)
		{
			printf("您输入的数据总数过大（不超过%d），请重新输入！\n",MAXNUM);//ERROR
		}
		else
		{
			break;
		}
	}
	while (InputLineMode != 1 && InputLineMode != 2)
	{
		printf("您选择单行输入所有数据还是多行输入？\n");
		printf("单行输入1，多行输入2\n");
		scanf("%d", &InputLineMode);
		if (InputLineMode != 1 && InputLineMode != 2)
		{
			printf("您输入的单行/多行模式代码不合法，请重新输入！\n");//ERROR
		}
		else
		{
			break;
		}
	}
	//单行输入
	if (InputLineMode == 1)
	{
		printf("请输入数据，每个数据间用空格隔开\n");
		//
	}
	//多行输入
	//用户可自定义每行输入的数量以及总数
	if (InputLineMode == 2)
	{
		printf("请您输入每行输入的个数\n");
		int NumOfDataPerLine = 0;//每行个数
		scanf("%d", &NumOfDataPerLine);
		int NumOfLine = (int)NumOfData / NumOfDataPerLine;//行数=总数/每行个数
		int TempCount = 0;//局部计数变量
		int Tempindex = 0;//局部循环变量i
		int Tempjndex = 0;//局部循环变量j
		for (Tempindex = 0; Tempindex < NumOfLine; ++Tempindex)
		{
			if (Tempindex != NumOfLine - 1)//不是最后一行
			{
				for (Tempjndex = 0; Tempjndex < NumOfDataPerLine; ++Tempjndex)
				{

				}
			}
			else//是最后一行
			{

			}
		}
	}






	return 0;
}

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
int qNO;	//前回の問題数
int QNO;	//今回の問題数


int get_data(void)	//前回の記録を読み取る
{
	FILE *fp;
	int best;

	if ((fp = fopen("SCORE.txt", "r")) == NULL)
	{
		printf("初回なのでスコアファイルを新規作成します。\n");
		best = 0;
	}
	else
	{
		int year, month, day, hour, minute, second;
		fscanf(fp, "%d%d%d%d%d%d", &year, &month, &day ,&hour, &minute, &second);
		fscanf(fp, "%d%d", &best, &qNO);

		printf("前回の最高得点は\n%04d年%02d月%02d日%02d時%02d分%02d秒の\n", year, month, day, hour, minute, second);
		printf("%d問中%d問でした。", qNO, best);

		fclose(fp);
	}

	return (best);
}

void put_data(int best)	//今回の時間更新
{
	FILE *fp;
	time_t t = time(NULL);
	struct tm *local = localtime(&t);

	fp = fopen("SCOR.txt", "w");

	fprintf(fp,"%d%d%d%d%d%d\n",local-> tm_year + 1900, local->tm_mon + 1,
				local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
	fprintf(fp, "%d %d\n", best, QNO);

	fclose(fp);
}

int game(void)	//文章表示とスコア計算
{
	int count = 0, Linecount = 1,score=0;
	int anser, CorrectAns;
	FILE *fp;
	char str[256];

	printf("難易度を選択してください。\n1.準2級　2.2級　3.準1級");

	printf("これから問題が表示されます。\n選択肢の先頭の数字を入力して下さい。\n\n");
	printf("Start!!\n");

	if ((fp = fopen("Quiz.txt", "r")) == NULL)
	{
		printf("file not open !\n");
		return -1;
	}

	while (fgets(str, 256, fp) != NULL)
	{

		if (count % 3 == 0)
		{
			CorrectAns = atoi(str);
			scanf("%d", &anser);
			if (CorrectAns == anser)
			{
				printf("正解！！\n");
				count++;
				score++;
			}
			else
			{
				printf("残念！！");
				printf("%s", str);
			}
		}

		else
		{
			printf("%s\n", str);
		}

		count++;
	}

	return(score);

}

void result(int best, int score)
{
	printf("\nあなたは%d問中%d問正解でした!\n", QNO, score);
	printf("前回は%d問中%d問正解でした。\n", qNO, best);
}

int main(void)
{
	int score;
	int best;

	best = get_data();

	score = game();
	result(best, score);

	if (score > best) {
		printf("最高得点を更新しました!!\n");
		best = score;
	}

	put_data(best);

	return (0);
}
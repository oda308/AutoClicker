#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

unsigned char MonitorKeyInput(void);
int SwitchActionTimer(unsigned int msec);
void RecordTime(int time);

unsigned long record_time;

/*****************************************/
/*Name : main							 */
/*****************************************/

int main()
{
	unsigned char input = 0;
	POINT pt;
	unsigned int i;
	char flags = FALSE;
	char click_flags = FALSE;
	char click_switch = FALSE;
	unsigned int start = clock();

	printf("クリック連打プログラムを開始\n");
	printf(" z でマウスカーソル座標決定\n");
	printf(" y でクリック連打開始\n");
	printf(" x で連打終了\n");
	printf(" ESC でプログラム終了\n");

	while(1)
	{
		input = MonitorKeyInput();
		
		/* ESC押下でプログラム終了 */
		if(input == 0x18)
		{
			break;
		}
		/* zボタン押下で現在のマウスカーソルの位置を取得し、登録する */
		else if(input == 'z')
		{
			GetCursorPos(&pt);
			printf("x = [%d] , y = [%d]\n",pt.x,pt.y);
		}
		/* 登録した座標でマウスのクリック連打開始 */
		else if(input == 'y')
		{
			printf("連打開始\n");
			flags = TRUE;

		}
		else if(input == 'x')
		{
			printf("連打終了\n");
			flags = FALSE;			  
		}
		else
		{
			/* Do nothing */
		}

		if(flags == TRUE)
		{
			/* クリックの頻度はココを変更する(ms)↓ */
			click_flags = SwitchActionTimer(50);
			
			if(click_flags==TRUE)
			{
				if(click_switch == FALSE)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN,MOUSEEVENTF_ABSOLUTE ,pt.x,pt.y,0);
				}
				else
				{
					mouse_event(MOUSEEVENTF_LEFTUP,MOUSEEVENTF_ABSOLUTE ,pt.x,pt.y,0);
				}
			}
			else
			{
				/* Do nothing */
			}

		}
		else
		{
			/* Do Nothing */
		}

	}
	return 0;

}

/*****************************************/
/*Name : MonitorKeyInput				 */
/*****************************************/
/* detail: conio.hをincludeすること		 */

unsigned char MonitorKeyInput(void)
{	
	unsigned char CheckKey = kbhit();
	unsigned char input_key;

	if(CheckKey == TRUE)
	{
		input_key = getch();
		printf("input_key == %d\n",input_key);
	}
	else
	{
		/* Do nothing */
	}

	return input_key;
}

/*****************************************/
/*Name : SwitchActionTimer				 */
/*****************************************/
/* detail: time.hをincludeすること。引数はmsec。セットした時間になるとflagを切り替える */
int SwitchActionTimer(unsigned int msec)
{
	unsigned long time = clock();
	int flags = FALSE;
	unsigned int check_time = 0;
	
	check_time = (time - record_time);
	
	if(check_time < msec)
	{
		/* 前回記録した値から引数のmsec経っていなかった場合flagをFALSEに。 */
		flags = FALSE;
	}
	else
	{
		/* 前回の記録から引数のmsec経っていた場合、flagsをTRUEに */
		RecordTime(time); 
		flags = TRUE;
	}

	return flags;

}

/*****************************************/
/*Name : RecordTime						 */
/*****************************************/
void RecordTime(int time)
{
	record_time = time;
}
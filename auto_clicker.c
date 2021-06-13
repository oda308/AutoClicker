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

	printf("�N���b�N�A�Ńv���O�������J�n\n");
	printf(" z �Ń}�E�X�J�[�\�����W����\n");
	printf(" y �ŃN���b�N�A�ŊJ�n\n");
	printf(" x �ŘA�ŏI��\n");
	printf(" ESC �Ńv���O�����I��\n");

	while(1)
	{
		input = MonitorKeyInput();
		
		/* ESC�����Ńv���O�����I�� */
		if(input == 0x18)
		{
			break;
		}
		/* z�{�^�������Ō��݂̃}�E�X�J�[�\���̈ʒu���擾���A�o�^���� */
		else if(input == 'z')
		{
			GetCursorPos(&pt);
			printf("x = [%d] , y = [%d]\n",pt.x,pt.y);
		}
		/* �o�^�������W�Ń}�E�X�̃N���b�N�A�ŊJ�n */
		else if(input == 'y')
		{
			printf("�A�ŊJ�n\n");
			flags = TRUE;

		}
		else if(input == 'x')
		{
			printf("�A�ŏI��\n");
			flags = FALSE;			  
		}
		else
		{
			/* Do nothing */
		}

		if(flags == TRUE)
		{
			/* �N���b�N�̕p�x�̓R�R��ύX����(ms)�� */
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
/* detail: conio.h��include���邱��		 */

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
/* detail: time.h��include���邱�ƁB������msec�B�Z�b�g�������ԂɂȂ��flag��؂�ւ��� */
int SwitchActionTimer(unsigned int msec)
{
	unsigned long time = clock();
	int flags = FALSE;
	unsigned int check_time = 0;
	
	check_time = (time - record_time);
	
	if(check_time < msec)
	{
		/* �O��L�^�����l���������msec�o���Ă��Ȃ������ꍇflag��FALSE�ɁB */
		flags = FALSE;
	}
	else
	{
		/* �O��̋L�^���������msec�o���Ă����ꍇ�Aflags��TRUE�� */
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
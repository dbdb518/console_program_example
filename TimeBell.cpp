#include <iostream>
#include "windows.h"
#include "time.h"
#include "conio.h"

void initialDisplay();
BOOL inputTime();
void moveCoordTo(int x, int y);
int calLeftMinutes();
void alarmBell();

int inputHour;
int inputMinute;
int nowHour;
int nowMinute;

time_t t;
tm st = {0, };

int main()
{
    system("cls");

    for (;;) 
    {
        initialDisplay();

        if (!inputTime()) continue;

        while ((inputHour != st.tm_hour) || (inputMinute != st.tm_min))
        {
            time(&t);
            localtime_s(&st, &t);

            system("cls");
            printf("######################################\n");
            printf("현재 시간 : %2d시 %2d분\n", st.tm_hour, st.tm_min);
            printf("남은 시간 : %4d분\n", calLeftMinutes());
            printf("######################################\n");
            Sleep(2000);
        }

        alarmBell();
    }
}

void initialDisplay()
{
    system("cls");
    printf("################################\n");
    printf("        시간을 입력하세요.\n");
    printf("################################\n");
    printf("\n\n");
}

BOOL inputTime()
{
    moveCoordTo(1, 5);
    printf("___시 ___분");

    moveCoordTo(2, 5);
    scanf_s("%d", &inputHour);

    if (inputHour < 0 || inputHour > 23)
    {
        printf("\n\n\n");
        printf("시간(시)을 바르게 입력하세요.");
        Sleep(3000);
        return FALSE;
    }

    moveCoordTo(8, 5);
    scanf_s("%d", &inputMinute);

    if (inputMinute < 0 || inputMinute > 59)
    {
        printf("\n\n\n");
        printf("시간(분)을 바르게 입력하세요.");
        Sleep(3000);
        return FALSE;
    }

    return TRUE;
}

void moveCoordTo(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int calLeftMinutes()
{
    int leftHour = 0;
    int leftMin = 0;

    leftHour = inputHour - st.tm_hour;
    leftMin = inputMinute - st.tm_min;

    if (leftHour < 0)
    {
        printf("\n\n\n\n\n");
        printf("현재시간을 확인 후 다시 실행하세요.");
        Sleep(2000);
        printf("\n\n\n\n\n");
        printf("프로그램을 종료합니다.");
        Sleep(2000);
        exit(0);
    }

    if (leftHour == 0 && leftMin < 0)
    {
        printf("\n\n\n\n\n");
        printf("현재시간을 확인 후 다시 실행하세요.");
        Sleep(2000);
        printf("\n\n\n\n\n");
        printf("프로그램을 종료합니다.");
        Sleep(2000);
        exit(0);
    }

    if (leftMin < 0)
    {
        return ((leftHour - 1) * 60) + (60 + leftMin);
    }
    else
    {
        return (leftHour * 60) + leftMin;
    }
}

void alarmBell()
{
    BOOL ring = TRUE;
    while (ring)
    {
        printf("\a");
        Sleep(200);
        printf("\a");
        Sleep(200);
        printf("\a");
        Sleep(200);
        printf("\a");
        Sleep(200);

        if (_kbhit()) ring = FALSE;

        Sleep(500);
    }
}
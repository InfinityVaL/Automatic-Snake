#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define Visible 0; /* An initial values for the program. */
#define LIMIT 10000 /* Limit for main array containing each snake's move. */
#define Step 20     /* 10, 20 */    /* Dimension of unit of one step and one cell of the field. */
#define X_Length 28 /* 58, 28 */    /* Dimension of X axis in Steps. */
#define Y_Length 18 /* 28, 18 */    /* Dimension of Y axis in Steps. */
int Stop=0;
struct Snake
{
    int x1, x2, y1, y2; /* Base structure containing dimensions snake's head, tail, the field and positions of snake's meal. */
};
void F_Start(HANDLE,int *,int *,int *,int *,int *,int *,struct Snake *,struct Snake *,struct Snake *);
void F_Stop_1(HANDLE); /* Text and menu when the program stops due to collision snake's head with borders or tail. */
void F_Stop_2(HANDLE); /* Text and menu when the program stops due to filled of the main array. */
void F_Farewell(HANDLE); /* Text before exit the program. */
void F_Borders(HDC,HBRUSH,int *,int *); /* Borders of the field. */
void F_SnakeMoves(HANDLE,int *,int *,int *,int *,int *,HDC,HBRUSH,HBRUSH,HBRUSH,struct Snake *,struct Snake *); /* Function makes snake's move. */
void F_SnakeEats(HANDLE,HDC,HBRUSH,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,struct Snake *,struct Snake *,struct Snake *,struct Snake *,struct Snake *); // The function makes snake getting meal.
void F_Indicators(int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,\
                  char *,char *,struct Snake *,struct Snake *,struct Snake *,struct Snake *,struct Snake *,struct Snake *); /* Special indicators defining position of the snake. */
void F_Checking_1(int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,char *,char *);
void F_Checking_2(int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,int *,char *,char *);
void F_Checking_3(int *,int *,int *,int *,int *,int *,int *,int *,int *,char *,char *);
void F_Checking_4(int *,int *,int *,int *,int *,int *,char *,char *); /* Checking of the indicators defining behaviour of the snake (4 levels of checking). */
int main()
{
    struct Snake Head, Tail[LIMIT], Field[X_Length*Y_Length+1], Up, Down, Left, Right, Meal, Check;
    HWND hwnd=GetConsoleWindow();
    HDC hdc=GetDC(hwnd);
    HANDLE Descr1=GetStdHandle(STD_OUTPUT_HANDLE);

    int Left_Border,Right_Border,Top_Border,Bottom_Border;
    int Coord,RandCoord,Chain,Delay,Count,Score,Key,Invisible,OrangeTail,Stepback,WallPer,WallTan,\
        WallPerStep,WallTanStep,TailPer,TailTan,Deadlock,WallLoopNear,WallLoopFar,SelfLoop,MealWall;
    char Vector,Between;
    clock_t ClockTime;

    Left_Border=Step;
    Right_Border=Step*X_Length;
    Top_Border=Step;
    Bottom_Border=Step*Y_Length;
    Mark_1:
    system("cls");
    Vector='0';
    Between='0';
    Delay=0;
    WallPer=0;
    WallTan=0;
    TailPer=0;
    TailTan=0;
    WallPerStep=0;
    WallTanStep=0;
    WallLoopNear=0;
    WallLoopFar=0;
    MealWall=0;
    SelfLoop=0;
    Deadlock=0;
    Invisible=0;
    OrangeTail=0;
    Count=Score=Stepback=Visible; /* Stepback is a number of visible tail elements (without head) which increases by one element each time snake gets a meal. */
    COORD CursorPos_1={14,12};
    COORD CursorPos_2={5,10};
    COORD CursorPos_3={75,3};
    COORD CursorPos_4={75,1};
    COORD CursorPos_5={75,5};
    HBRUSH Brush_1, Brush_2, Brush_3, Brush_4, Brush_5;
    Brush_1=CreateSolidBrush(RGB(255,120,0));
    Brush_2=CreateSolidBrush(RGB(0,255,255));
    Brush_3=CreateSolidBrush(RGB(12,12,12));
    Brush_4=CreateSolidBrush(RGB(0,255,100));
    Brush_5=CreateSolidBrush(RGB(255,255,255));
    F_Start(Descr1,&Coord,&RandCoord,&Left_Border,&Right_Border,&Top_Border,&Bottom_Border,&Head,&Check,&Field[0]);
    while(Key=_getch())
    {
        if(Key=='1') /* Case 1, for manual snake. */
        {
            system("cls");
            SetConsoleCursorPosition(Descr1,CursorPos_1);
            printf(" Use \"a\", \"d\", \"s\", \"w\" to move The Snake (English layout without \"Caps Lock\").""\n\n");
            printf("               Press any key.");
            if(Key=_getch())
            {
                system("cls");
                SetConsoleCursorPosition(Descr1,CursorPos_3);
                printf("Score: 0 ");
                SetConsoleCursorPosition(Descr1,CursorPos_4);
                printf("Steps: 0 ");
                F_SnakeEats(Descr1,hdc,Brush_2,&Left_Border,&Right_Border,&Top_Border,&Bottom_Border,\
                            &Coord,&Stepback,&Count,&Chain,&Score,&RandCoord,&MealWall,&Head,&Check,&Meal,&Tail[0],&Field[0]);
                while(Key=_getch())
                {
                    if(Key=='d' || Key=='a' || Key=='w' || Key=='s')
                    {
                        F_Checking_1(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                        F_Checking_2(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                        F_Checking_3(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&SelfLoop,&Deadlock,&Vector,&Between);
                        F_Checking_4(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&Vector,&Between);
                        F_SnakeMoves(Descr1,&Key,&Count,&Invisible,&OrangeTail,&Stepback,hdc,Brush_1,Brush_3,Brush_5,&Head,&Tail[0]);
                        F_Indicators(&Count,&Chain,&Stepback,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,\
                                    &Left_Border,&Right_Border,&Top_Border,&Bottom_Border,&Vector,&Between,&Head,&Up,&Down,&Left,&Right,&Tail[0]);
                        F_SnakeEats(Descr1,hdc,Brush_2,&Left_Border,&Right_Border,&Top_Border,&Bottom_Border,\
                                    &Coord,&Stepback,&Count,&Chain,&Score,&RandCoord,&MealWall,&Head,&Check,&Meal,&Tail[0],&Field[0]);
                        F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                        SetConsoleCursorPosition(Descr1,CursorPos_5);
                        ClockTime=clock()/(CLOCKS_PER_SEC/1000);
                        printf("Time: %d ms",(int)ClockTime);
                    }

                    if((Stop==1)||(Head.x1<Left_Border || Head.x1>Right_Border || Head.y1<Top_Border || Head.y1>Bottom_Border))
                    {
                        Stop=0;
                        F_Stop_1(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }

                    if(Count==99999)
                    {
                        F_Stop_2(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }
                }
            }
        }
        if(Key=='2') /* Case 2, for automatic snake. */
        {
            system("cls");
            SetConsoleCursorPosition(Descr1,CursorPos_2);
            printf("Set Snake's speed inputting value in milliseconds from 10 ms to 100 ms,\n\n     and press \"Enter\". \n\n\n");
            printf("     Value: ");
            scanf("%d",&Delay);
            if(Delay<10)
                Delay=10;
            if(Delay>100)
                Delay=100;
            system("cls");
            SetConsoleCursorPosition(Descr1,CursorPos_3);
            printf("Score: 0 ");
            SetConsoleCursorPosition(Descr1,CursorPos_4);
            printf("Steps: 0 ");
            F_SnakeEats(Descr1,hdc,Brush_2,&Left_Border,&Right_Border,&Top_Border,&Bottom_Border,\
                        &Coord,&Stepback,&Count,&Chain,&Score,&RandCoord,&MealWall,&Head,&Check,&Meal,&Tail[0],&Field[0]);
            while(Stop==0)
            {
                F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);

                while(Head.x1>Meal.x1)
                {
                    Key='a';
                    SetConsoleTitle("<- Left");
                    F_Checking_1(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_2(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_3(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_4(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&Vector,&Between);
                    F_SnakeMoves(Descr1,&Key,&Count,&Invisible,&OrangeTail,&Stepback,hdc,Brush_1,Brush_3,Brush_5,&Head,&Tail[0]);
                    F_Indicators(&Count,&Chain,&Stepback,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,\
                                &Left_Border,&Right_Border,&Top_Border,&Bottom_Border,&Vector,&Between,&Head,&Up,&Down,&Left,&Right,&Tail[0]);
                    Sleep(Delay);
                    SelectObject(hdc, Brush_2);
                    Ellipse(hdc, Meal.x1, Meal.y1, Meal.x2, Meal.y2);
                    F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                    SetConsoleCursorPosition(Descr1,CursorPos_5);
                    ClockTime=clock()/(CLOCKS_PER_SEC/1000);
                    printf("Time: %d ms",(int)ClockTime);
                    if((Stop==1)||(Head.x1<Left_Border || Head.x1>Right_Border || Head.y1<Top_Border || Head.y1>Bottom_Border))
                    {
                        Stop=0;
                        F_Stop_1(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }

                    if(Count==99999)
                    {
                        F_Stop_2(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }
                }

                while(Head.x1<Meal.x1)
                {
                    Key='d';
                    F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                    SetConsoleTitle("Right ->");
                    F_Checking_1(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_2(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_3(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_4(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&Vector,&Between);
                    F_SnakeMoves(Descr1,&Key,&Count,&Invisible,&OrangeTail,&Stepback,hdc,Brush_1,Brush_3,Brush_5,&Head,&Tail[0]);
                    F_Indicators(&Count,&Chain,&Stepback,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,\
                                &Left_Border,&Right_Border,&Top_Border,&Bottom_Border,&Vector,&Between,&Head,&Up,&Down,&Left,&Right,&Tail[0]);
                    Sleep(Delay);
                    SelectObject(hdc, Brush_2);
                    Ellipse(hdc, Meal.x1, Meal.y1, Meal.x2, Meal.y2);
                    F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                    SetConsoleCursorPosition(Descr1,CursorPos_5);
                    ClockTime=clock()/(CLOCKS_PER_SEC/1000);
                    printf("Time: %d ms",(int)ClockTime);
                    if((Stop==1)||(Head.x1<Left_Border || Head.x1>Right_Border || Head.y1<Top_Border || Head.y1>Bottom_Border))
                    {
                        Stop=0;
                        F_Stop_1(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }

                    if(Count==99999)
                    {
                        F_Stop_2(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }
                }

                while(Head.y1>Meal.y1)
                {
                    Key='w';
                    F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                    SetConsoleTitle("Up ^");
                    F_Checking_1(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_2(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_3(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_4(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&Vector,&Between);
                    F_SnakeMoves(Descr1,&Key,&Count,&Invisible,&OrangeTail,&Stepback,hdc,Brush_1,Brush_3,Brush_5,&Head,&Tail[0]);
                    F_Indicators(&Count,&Chain,&Stepback,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,\
                                    &Left_Border,&Right_Border,&Top_Border,&Bottom_Border,&Vector,&Between,&Head,&Up,&Down,&Left,&Right,&Tail[0]);
                    Sleep(Delay);
                    SelectObject(hdc, Brush_2);
                    Ellipse(hdc, Meal.x1, Meal.y1, Meal.x2, Meal.y2);
                    F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                    SetConsoleCursorPosition(Descr1,CursorPos_5);
                    ClockTime=clock()/(CLOCKS_PER_SEC/1000);
                    printf("Time: %d ms",(int)ClockTime);
                    if((Stop==1)||(Head.x1<Left_Border || Head.x1>Right_Border || Head.y1<Top_Border || Head.y1>Bottom_Border))
                    {
                        Stop=0;
                        F_Stop_1(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }

                    if(Count==99999)
                    {
                        F_Stop_2(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }
                }

                while(Head.y1<Meal.y1)
                {
                    Key='s';
                    F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                    SetConsoleTitle("Down v");
                    F_Checking_1(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_2(&Key,&Stepback,&MealWall,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_3(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&WallLoopNear,&SelfLoop,&Deadlock,&Vector,&Between);
                    F_Checking_4(&Key,&Stepback,&WallPer,&WallTan,&TailPer,&TailTan,&Vector,&Between);
                    F_SnakeMoves(Descr1,&Key,&Count,&Invisible,&OrangeTail,&Stepback,hdc,Brush_1,Brush_3,Brush_5,&Head,&Tail[0]);
                    F_Indicators(&Count,&Chain,&Stepback,&WallPer,&WallTan,&WallPerStep,&WallTanStep,&TailPer,&TailTan,&WallLoopNear,&WallLoopFar,&SelfLoop,&Deadlock,\
                                    &Left_Border,&Right_Border,&Top_Border,&Bottom_Border,&Vector,&Between,&Head,&Up,&Down,&Left,&Right,&Tail[0]);
                    Sleep(Delay);
                    SelectObject(hdc, Brush_2);
                    Ellipse(hdc, Meal.x1, Meal.y1, Meal.x2, Meal.y2);
                    F_Borders(hdc,Brush_4,&Right_Border,&Bottom_Border);
                    SetConsoleCursorPosition(Descr1,CursorPos_5);
                    ClockTime=clock()/(CLOCKS_PER_SEC/1000);
                    printf("Time: %d ms",(int)ClockTime);
                    if((Stop==1)||(Head.x1<Left_Border || Head.x1>Right_Border || Head.y1<Top_Border || Head.y1>Bottom_Border))
                    {
                        Stop=0;
                        F_Stop_1(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }

                    if(Count==99999)
                    {
                        F_Stop_2(Descr1);
                        while(Key=_getch())
                            if(Key==' ')
                                goto Mark_1;
                            else if(Key==27)
                                goto Mark_2;
                    }
                }
                F_SnakeEats(Descr1,hdc,Brush_2,&Left_Border,&Right_Border,&Top_Border,&Bottom_Border,\
                            &Coord,&Stepback,&Count,&Chain,&Score,&RandCoord,&MealWall,&Head,&Check,&Meal,&Tail[0],&Field[0]);
            }
        }
        if(Key==27) /* Case 3, for exit the program. */
        {
            Mark_2:
            system("cls");
            F_Farewell(Descr1);
            break;
        }
    }
    Sleep(2000);
    ReleaseDC(NULL, hdc);
    return 0;
}

void F_Start(HANDLE Descr1,int *Coord,int *RandCoord,int *Left_Border,int *Right_Border,int *Top_Border,int *Bottom_Border,struct Snake *Head,struct Snake *Check,struct Snake *Field)
{
    COORD CursorPos={25,8};
    SetConsoleTitle("Start!");
    SetConsoleTextAttribute(Descr1,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(Descr1,CursorPos);
    printf("Press \"1\" for manual snake.\n\n");
    printf("                        Press \"2\" for automatic snake.\n\n");
    printf("                             Press \"Esc\" to exit.");

    Check->x1=*Left_Border;
    Check->x2=Check->x1+Step;
    Check->y1=*Top_Border;
    Check->y2=Check->y1+Step;
    for(*Coord=0, Field[*Coord]=*Check; Check->y1<=*Bottom_Border;) /* Loop to fill the field and then choose one random point for the first meal appearing. */
    {
        if(Check->x1==*Left_Border && Check->y1<=*Bottom_Border)
            while(Check->x1<*Right_Border)
            {
                (Check->x1+=Step);
                (Check->x2+=Step);
                Field[++(*Coord)]=*Check;
            }
        (Check->y1+=Step);
        (Check->y2+=Step);
        if(Check->y1<=*Bottom_Border)
            Field[++(*Coord)]=*Check;
        if(Check->x1==*Right_Border && Check->y1<=*Bottom_Border)
            while(Check->x1>*Left_Border)
            {
                (Check->x1-=Step);
                (Check->x2-=Step);
                Field[++(*Coord)]=*Check;
            }
        (Check->y1+=Step);
        (Check->y2+=Step);
        if(Check->y1<=*Bottom_Border)
            Field[++(*Coord)]=*Check;
    }
    srand(time(NULL));
    *RandCoord = rand() % *Coord;

    Head->x1=*Right_Border%2;
    if(Head->x1==0)
        Head->x1=*Right_Border/2;
    else Head->x1=*Right_Border/2+0.5;
    Head->x2=Head->x1+Step;

    Head->y1=*Bottom_Border%2;
    if(Head->y1==0)
        Head->y1=*Bottom_Border/2;
    else Head->y1=*Bottom_Border/2+0.5;
    Head->y2=Head->y1+Step; /* Setting of the first snake's head appearing. */
}

void F_Stop_1(HANDLE Descr1)
{
    COORD CursorPos_1={30,10};
    COORD CursorPos_2={15,12};
    printf("\a");
    SetConsoleTitle("Stop");
    SetConsoleCursorPosition(Descr1,CursorPos_1);
    printf("THE SNAKE HAS BEEN BROKEN!\n");
    SetConsoleTextAttribute(Descr1,FOREGROUND_GREEN);
    SetConsoleCursorPosition(Descr1,CursorPos_2);
    printf("Press \"Space\" to start the new game or \"Esc\" to exit.""\n");
}

void F_Stop_2(HANDLE Descr1)
{
    COORD CursorPos_1={30,10};
    COORD CursorPos_2={14,12};
    system("cls");
    printf("\a");
    SetConsoleTitle("Stop");
    SetConsoleCursorPosition(Descr1,CursorPos_1);
    printf("  ARRAY IS OVERFILLED!\n");
    SetConsoleTextAttribute(Descr1,FOREGROUND_GREEN);
    SetConsoleCursorPosition(Descr1,CursorPos_2);
    printf("Press \"Double Space\" to start a new game or \"Esc\" to exit.""\n");
}

void F_Farewell(HANDLE Descr1)
{
    COORD CursorPos={30,10};
    SetConsoleCursorPosition(Descr1,CursorPos);
    SetConsoleTextAttribute(Descr1,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    printf("See you next time!\n\n\n\n\n\n\n\n\n\n");
    SetConsoleTextAttribute(Descr1,FOREGROUND_INTENSITY);
}

void F_Borders(HDC hdc,HBRUSH Brush_4,int *Right_Border,int *Bottom_Border)
{
    SelectObject(hdc,Brush_4);
    Rectangle(hdc,Step-3,Step-3,(*Right_Border)+Step+3,Step);   /* Top border */
    Rectangle(hdc,Step-3,Step-3,Step,(*Bottom_Border)+Step+3);    /* Left border */
    Rectangle(hdc,(*Right_Border)+Step,(*Bottom_Border)+Step+3,(*Right_Border)+Step+3,Step-3); /* Right border */
    Rectangle(hdc,Step-3,(*Bottom_Border)+Step,(*Right_Border)+Step+3,(*Bottom_Border)+Step+3); /* Lower border */
}

void F_SnakeMoves(HANDLE Descr1,int *Key,int *Count,int *Invisible,int *OrangeTail,int *Stepback,HDC hdc,HBRUSH Brush_1,HBRUSH Brush_3,HBRUSH Brush_5,\
                  struct Snake *Head,struct Snake *Tail)
{
    if(*Key=='d')
    {
        (Head->x1)+=Step;
        (Head->x2)+=Step;
        SetConsoleTitle("Right ->");
    }

    if(*Key=='s')
    {
        (Head->y1)+=Step;
        (Head->y2)+=Step;
        SetConsoleTitle("Down v");
    }

    if(*Key=='a')
    {
        (Head->x1)-=Step;
        (Head->x2)-=Step;
        SetConsoleTitle("<- Left");
    }

    if(*Key=='w')
    {
        (Head->y1)-=Step;
        (Head->y2)-=Step;
        SetConsoleTitle("Up ^");
    }

    SelectObject(hdc, Brush_5);
    Ellipse(hdc, Head->x1, Head->y1, Head->x2, Head->y2);
    Tail[++(*Count)]=*Head;
    SelectObject(hdc, Brush_3);
    if((*Invisible)<(*Count)-(*Stepback)) /* An invisible part of snake (black tail) remaining after itself. */
    {
        Ellipse(hdc, Tail[*Invisible].x1, Tail[*Invisible].y1, Tail[*Invisible].x2, Tail[*Invisible].y2);
        ++(*Invisible);
    }

    for(*OrangeTail=*Invisible; *OrangeTail<*Count; ++(*OrangeTail)) /* Color of snake's tail (orange). */
    {
       SelectObject(hdc, Brush_1);
       Ellipse(hdc, Tail[*OrangeTail].x1, Tail[*OrangeTail].y1, Tail[*OrangeTail].x2, Tail[*OrangeTail].y2);
    }
    COORD CursorPos_1={75,1};
    SetConsoleCursorPosition(Descr1,CursorPos_1);
    printf("Steps: %d ",*Count);
    COORD CursorPos_2={75,2};
    SetConsoleCursorPosition(Descr1,CursorPos_2);
    printf("Head: X %d | Y %d ",Head->x1,Head->y1);
}

void F_SnakeEats(HANDLE Descr1,HDC hdc,HBRUSH Brush_2,int *Left_Border,int *Right_Border,int *Top_Border,int *Bottom_Border,\
                 int *Coord,int *Stepback,int *Count,int *Chain,int *Score,int *RandCoord,int *MealWall,\
                 struct Snake *Head,struct Snake *Check,struct Snake *Meal,struct Snake *Tail,struct Snake *Field)
{
    SelectObject(hdc, Brush_2);
    COORD CursorPos_4={75,6};
    SetConsoleCursorPosition(Descr1,CursorPos_4);
    printf("RandCoord:      ");

    if(Field[*RandCoord].x1==Head->x1 && Field[*RandCoord].y1==Head->y1) /* Avoiding the very first appearing meal on a head of snake. */
         Field[++(*RandCoord)];

    if(Head->x1==Meal->x1 && Head->y2==Meal->y2) /* If snake gets meal. */
    {
        ++(*Stepback);
        ++(*Score);
        srand((*Score)+(*Count)+(Head->x1)*time(NULL));
        *RandCoord = rand() % *Coord;
        *Chain=(*Count)+1;
        while(((*Chain)--)>=(*Count)-(*Stepback))
        {
            if(Field[*RandCoord].x1==Tail[*Chain].x1 && Field[*RandCoord].y1==Tail[*Chain].y1)
            {
                Check->x1=*Left_Border;
                Check->x2=Check->x1+Step;
                Check->y1=*Top_Border;
                Check->y2=Check->y1+Step;
                *Coord=0;
                Field[*Coord]=*Check;
                *Chain=(*Count)+1;
                while(((*Chain)--)>=(*Count)-(*Stepback))
                    if(Field[*Coord].x1==Tail[*Chain].x1 && Field[*Coord].y1==Tail[*Chain].y1)
                        --(*Coord);
                while(Check->y1<=*Bottom_Border)
                {

                    if(Check->x1==*Left_Border && Check->y1<=*Bottom_Border)
                        while(Check->x1<*Right_Border)
                        {
                            (Check->x1+=Step);
                            (Check->x2+=Step);
                            Field[++(*Coord)]=*Check;
                            *Chain=(*Count)+1;
                            while(((*Chain)--)>=(*Count)-(*Stepback))
                                if((Check->x1==Tail[*Chain].x1 && Check->y1==Tail[*Chain].y1))
                                    --(*Coord);
                        }

                    (Check->y1+=Step);
                    (Check->y2+=Step);

                    if(Check->y1<=*Bottom_Border)
                    {
                        Field[++(*Coord)]=*Check;
                        *Chain=(*Count)+1;
                        while(((*Chain)--)>=(*Count)-(*Stepback))
                            if((Check->x1==Tail[*Chain].x1 && Check->y1==Tail[*Chain].y1))
                                --(*Coord);
                    }

                    if(Check->x1==*Right_Border && Check->y1<=*Bottom_Border)
                        while(Check->x1>*Left_Border)
                        {
                            (Check->x1-=Step);
                            (Check->x2-=Step);
                            Field[++(*Coord)]=*Check;
                            *Chain=(*Count)+1;
                            while(((*Chain)--)>=(*Count)-(*Stepback))
                                if((Check->x1==Tail[*Chain].x1 && Check->y1==Tail[*Chain].y1))
                                    --(*Coord);
                        }

                    (Check->y1+=Step);
                    (Check->y2+=Step);

                    if(Check->y1<=*Bottom_Border)
                    {
                        Field[++(*Coord)]=*Check;
                        *Chain=(*Count)+1;
                        while(((*Chain)--)>=(*Count)-(*Stepback))
                            if((Check->x1==Tail[*Chain].x1 && Check->y1==Tail[*Chain].y1))
                                --(*Coord);
                    }

                }

                srand((*Score)+(*Count)+(Head->x1)*time(NULL));
                *RandCoord = rand() % *Coord;
                SetConsoleCursorPosition(Descr1,CursorPos_4);
                printf("RandCoord: %d ",*RandCoord);
                break;
            }
        }
        *Meal=Field[*RandCoord];
        COORD CursorPos={75,3};
        SetConsoleCursorPosition(Descr1,CursorPos);
        printf("Score: %d ",*Score);
    }
    else *Meal=Field[*RandCoord];

    *MealWall=0; /* Indicator to recognize position of meal relative to the borders. */
    if(Meal->x1==*Left_Border)
        *MealWall=9;
    if(Meal->x1==*Right_Border)
        *MealWall=3;
    if(Meal->y1==*Top_Border)
        *MealWall=12;
    if(Meal->y1==*Bottom_Border)
        *MealWall=6;
    if(Meal->x1==*Left_Border && Meal->y1==*Top_Border)
        *MealWall=912;
    if(Meal->x1==*Left_Border && Meal->y1==*Bottom_Border)
        *MealWall=96;
    if(Meal->x1==*Right_Border && Meal->y1==*Top_Border)
        *MealWall=312;
    if(Meal->x1==*Right_Border && Meal->y1==*Bottom_Border)
        *MealWall=36;

    Ellipse(hdc, Meal->x1, Meal->y1, Meal->x2, Meal->y2);
    COORD CursorPos_2={75,4};
    SetConsoleCursorPosition(Descr1,CursorPos_2);
    printf("Meal: X %d | Y %d ",Meal->x1,Meal->y1);
    COORD CursorPos_3={75,21};
    SetConsoleCursorPosition(Descr1,CursorPos_3);
    printf("MealWall........ %d ",*MealWall);
}

void F_Indicators(int *Count,int *Chain,int *Stepback,int *WallPer,int *WallTan,int *WallPerStep,int *WallTanStep,int *TailPer,int *TailTan,int *WallLoopNear,int *WallLoopFar,int *SelfLoop,int *Deadlock,\
                  int *Left_Border,int *Right_Border,int *Top_Border,int *Bottom_Border,char *Vector,char *Between,\
                  struct Snake *Head,struct Snake *Up,struct Snake *Down,struct Snake *Left,struct Snake *Right,struct Snake *Tail)
{
    int LRlr, i, c, l, r, L, R;
/* ........................................................................................ Checking if snake's head gets snake's tail. */
    *Chain=(*Count);
    while(((*Chain)--)>=(*Count)-(*Stepback))
    {
        if(Head->x1==Tail[*Chain].x1 && Head->y1==Tail[*Chain].y1)
        Stop=1;
    }
/* ........................................................................................ Indicator of a snake's direction. */
    if(Tail[(*Count)-1].x1==Head->x1+Step)
        *Vector='L';
    if(Tail[(*Count)-1].x1==Head->x1-Step)
        *Vector='R';
    if(Tail[(*Count)-1].y1==Head->y1+Step)
        *Vector='U';
    if(Tail[(*Count)-1].y1==Head->y1-Step)
        *Vector='D';
/* ........................................................................................ Indicator of a snake's position when head is next to wall and it is going towards the wall. */
    *WallPer=0;
    if(Head->x1==*Left_Border && *Vector=='L')
        *WallPer=9;
    if(Head->x1==*Right_Border && *Vector=='R')
        *WallPer=3;
    if(Head->y1==*Top_Border && *Vector=='U')
        *WallPer=12;
    if(Head->y1==*Bottom_Border && *Vector=='D')
        *WallPer=6;
/* ........................................................................................ Indicator of a snake's position when head is next to wall and when it is going along the wall. */
    *WallTan=0;
    if(Head->x1==*Left_Border && (*Vector=='U' || *Vector=='D'))
        *WallTan=9;
    if(Head->x1==*Right_Border && (*Vector=='U' || *Vector=='D'))
        *WallTan=3;
    if(Head->y1==*Top_Border && (*Vector=='L' || *Vector=='R'))
        *WallTan=12;
    if(Head->y1==*Bottom_Border && (*Vector=='L' || *Vector=='R'))
        *WallTan=6;
/* ........................................................................................ Indicator of a snake's position when head is next to wall+step and it is going towards the wall. */
    *WallPerStep=0;
    if(Head->x1==*Left_Border+Step && (*Vector=='L' || *Vector=='R'))
        *WallPerStep=9;
    if(Head->x1==*Right_Border-Step && (*Vector=='R' || *Vector=='L'))
        *WallPerStep=3;
    if(Head->y1==*Top_Border+Step && (*Vector=='U' || *Vector=='D'))
        *WallPerStep=12;
    if(Head->y1==*Bottom_Border-Step && (*Vector=='D' || *Vector=='U'))
        *WallPerStep=6;
/* ........................................................................................ Indicator of a snake's position when head is next to wall+step and it is going along the wall. */
    *WallTanStep=0;
    if(Head->x1==*Left_Border+Step && (*Vector=='U' || *Vector=='D'))
        *WallTanStep=9;
    if(Head->x1==*Right_Border-Step && (*Vector=='U' || *Vector=='D'))
        *WallTanStep=3;
    if(Head->y1==*Top_Border+Step && (*Vector=='L' || *Vector=='R'))
        *WallTanStep=12;
    if(Head->y1==*Bottom_Border-Step && (*Vector=='L' || *Vector=='R'))
        *WallTanStep=6;
/* ........................................................................................ Indicator of a snake's position when head is next to tail and it is going towards the tail. */
    *TailPer=0;
    *Chain=(*Count);
    while(((*Chain)--)>=(*Count)-(*Stepback))
    {
        if(Tail[*Chain].x1==Head->x1-Step && Tail[*Chain].y1==Head->y1 && *Vector=='L')
            {*TailPer=9;break;}
        if(Tail[*Chain].x1==Head->x1+Step && Tail[*Chain].y1==Head->y1 && *Vector=='R')
            {*TailPer=3;break;}
        if(Tail[*Chain].x1==Head->x1 && Tail[*Chain].y1==Head->y1-Step && *Vector=='U')
            {*TailPer=12;break;}
        if(Tail[*Chain].x1==Head->x1 && Tail[*Chain].y1==Head->y1+Step && *Vector=='D')
            {*TailPer=6;break;}
    }
/* ........................................................................................ Indicator of a snake's position when head is next to tail and it is going along the tail. */
    *TailTan=0;
    *Chain=(*Count);
    while(((*Chain)--)>=(*Count)-(*Stepback))
    {
        if(Tail[*Chain].x1==Head->x1-Step && Tail[*Chain].y1==Head->y1 && (*Vector=='U' || *Vector=='D'))
            {*TailTan=9;break;}
        if(Tail[*Chain].x1==Head->x1+Step && Tail[*Chain].y1==Head->y1 && (*Vector=='U' || *Vector=='D'))
            {*TailTan=3;break;}
        if(Tail[*Chain].x1==Head->x1 && Tail[*Chain].y1==Head->y1-Step && (*Vector=='L' || *Vector=='R'))
            {*TailTan=12;break;}
        if(Tail[*Chain].x1==Head->x1 && Tail[*Chain].y1==Head->y1+Step && (*Vector=='L' || *Vector=='R'))
            {*TailTan=6;break;}
    }
/* ........................................................................................ Indicator of a snake's position when head is between two parts of a tail. */
    *Between='0';
    *Chain=(*Count);
    while(((*Chain)--)>=(*Count)-(*Stepback))
    {
        if(Tail[*Chain].x1==Head->x1-Step && Tail[*Chain].y1==Head->y1 && *TailTan==3)
            {*Between='V';break;}
        if(Tail[*Chain].x1==Head->x1+Step && Tail[*Chain].y1==Head->y1 && *TailTan==9)
            {*Between='V';break;}
        if(Tail[*Chain].x1==Head->x1 && Tail[*Chain].y1==Head->y1-Step && *TailTan==6)
            {*Between='H';break;}
        if(Tail[*Chain].x1==Head->x1 && Tail[*Chain].y1==Head->y1+Step && *TailTan==12)
            {*Between='H';break;}
        else *Between='0';
    }
/* ........................................................................................ Indicator of a snake's position when head has a minimum diagonal with tail. */
    L=0;R=0;l=0;r=0;LRlr=0;
    *Chain=(*Count);
    while(((*Chain)--)>=(*Count)-(*Stepback) && *TailPer==0)
    {
        if((Tail[*Chain].y1==Head->y1-Step && Tail[*Chain].x1==Head->x1-Step) && (*Vector=='L' || *Vector=='U'))
            {l=1; LRlr=1;}
        if((Tail[*Chain].y1==Head->y1-Step && Tail[*Chain].x1==Head->x1+Step) && (*Vector=='R' || *Vector=='U'))
            {r=1; LRlr=1;}
        if((Tail[*Chain].y1==Head->y1+Step && Tail[*Chain].x1==Head->x1-Step) && (*Vector=='L' || *Vector=='D'))
            {L=1; LRlr=1;}
        if((Tail[*Chain].y1==Head->y1+Step && Tail[*Chain].x1==Head->x1+Step) && (*Vector=='R' || *Vector=='D'))
            {R=1; LRlr=1;}
    }
/* ........................................................................................ Indicator of a snake's position when a situation, where snake may be in a hopeless loop constrained by tail only, has recognized. */
    *SelfLoop=0;
    *Chain=(*Count);
    while((((*Chain)--)>=(*Count)-(*Stepback)) && (*TailPer!=0 || *WallPer!=0 || LRlr!=0))
    {
        *Up=*Head;
        *Down=*Head;
        *Left=*Head;
        *Right=*Head;

        while((*Vector=='L' || *Vector=='R') && LRlr==0)
        {
            Up->y1-=Step;
            if(Up->x1==Tail[*Chain].x1 && Up->y1==Tail[*Chain].y1)
                {*SelfLoop=12;break;}
            if(Up->y1<=*Top_Border)
                break;
        }

        while((*Vector=='L' || *Vector=='R') && LRlr!=0)
        {
            Up->y1-=Step;
            if(Up->x1==Tail[*Chain].x1 && Up->y1==Tail[*Chain].y1)
                {*SelfLoop=12;break;}
            if(Up->y1<=*Top_Border)
                break;
        }

        while((*Vector=='L' || *Vector=='R') && LRlr==0)
        {
            Down->y1+=Step;
            if(Down->x1==Tail[*Chain].x1 && Down->y1==Tail[*Chain].y1)
                {*SelfLoop=6;break;}
            if(Down->y1>=*Bottom_Border)
                break;
        }

        while((*Vector=='L' || *Vector=='R') && LRlr!=0)
        {
            Down->y1+=Step;
            if(Down->x1==Tail[*Chain].x1 && Down->y1==Tail[*Chain].y1)
                {*SelfLoop=6;break;}
            if(Down->y1>=*Bottom_Border)
                break;
        }

        while((*Vector=='U' || *Vector=='D') && LRlr==0)
        {
            Left->x1-=Step;
            if(Left->x1==Tail[*Chain].x1 && Left->y1==Tail[*Chain].y1)
                {*SelfLoop=9;break;}
            if(Left->x1<=*Left_Border)
                break;
        }

        while((*Vector=='U' || *Vector=='D') && LRlr!=0)
        {
            Left->x1-=Step;
            if(Left->x1==Tail[*Chain].x1 && Left->y1==Tail[*Chain].y1)
                {*SelfLoop=9;break;}
            if(Left->x1<=*Left_Border)
                break;
        }

        while((*Vector=='U' || *Vector=='D') && LRlr==0)
        {
            Right->x1+=Step;
            if(Right->x1==Tail[*Chain].x1 && Right->y1==Tail[*Chain].y1)
                {*SelfLoop=3;break;}
            if(Right->x1>=*Right_Border)
                break;
        }

        while((*Vector=='U' || *Vector=='D') && LRlr!=0)
        {
            Right->x1+=Step;
            if(Right->x1==Tail[*Chain].x1 && Right->y1==Tail[*Chain].y1)
                {*SelfLoop=3;break;}
            if(Right->x1>=*Right_Border)
                break;
        }

        if(*SelfLoop!=0)
            break;
    }
/* ........................................................................................ Indicator of a snake's position when a situation, where snake may be between two parts of tail and can't escape from this situation, has recognized. */
    *Deadlock=0;
    if((*SelfLoop==12 && L==1) || (*SelfLoop==6 && l==1))
        *Deadlock=9;
    if((*SelfLoop==12 && R==1) || (*SelfLoop==6 && r==1))
        *Deadlock=3;
    if((*SelfLoop==3 && l==1) || (*SelfLoop==9 && r==1))
        *Deadlock=12;
    if((*SelfLoop==3 && L==1) || (*SelfLoop==9 && R==1))
        *Deadlock=6;
/* ........................................................................................ Indicator of a snake's position when a situation, where snake may be in a hopeless loop constrained by tail and wall */
/*                                                                                          if an angle between two constraining walls is 90 degrees, has recognized. */
    *WallLoopNear=0;
    *Chain=(*Count);
    i=0;
    c=0;
    while((*Chain>=(*Count)-(*Stepback) && *WallPer!=0))
    {
        --(*Chain);
        ++i;

        if(Tail[*Chain].x1==*Left_Border)
            while(((*Chain)--)>=(*Count)-(*Stepback))
            {
                c++;
                if(i<=c)
                    *WallLoopNear=9;
            }

        if(Tail[*Chain].x1==*Right_Border)
            while(((*Chain)--)>=(*Count)-(*Stepback))
            {
                c++;
                if(i<=c)
                    *WallLoopNear=3;
            }

        if(Tail[*Chain].y1==*Top_Border)
            while(((*Chain)--)>=(*Count)-(*Stepback))
            {
                c++;
                if(i<=c)
                    *WallLoopNear=12;
            }

        if(Tail[*Chain].y1==*Bottom_Border)
            while(((*Chain)--)>=(*Count)-(*Stepback))
            {
                c++;
                if(i<=c)
                    *WallLoopNear=6;
            }
    }
/* ........................................................................................ Indicator of a snake's position when a situation, where snake may be in a hopeless loop constrained by tail and wall */
/*                                                                                          if an angle between two constraining walls is 180 degrees, has recognized. */
    *WallLoopFar=0;
    *Chain=(*Count);
    i=0;
    c=0;
    while((*Chain>=(*Count)-(*Stepback) && *WallPer!=0))
    {
        --(*Chain);
        ++i;

        if(*WallPer==6)
            if(Tail[*Chain].y1==*Top_Border && (Tail[*Chain].x1<*Right_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=9;
                }

        if(*WallPer==12)
            if(Tail[*Chain].y1==*Bottom_Border && (Tail[*Chain].x1<*Right_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=9;
                }

        if(*WallPer==6)
            if(Tail[*Chain].y1==*Top_Border && (Tail[*Chain].x1>*Right_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=3;
                }

        if(*WallPer==12)
            if(Tail[*Chain].y1==*Bottom_Border && (Tail[*Chain].x1>*Right_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=3;
                }

        if(*WallPer==9)
            if(Tail[*Chain].x1==*Right_Border && (Tail[*Chain].y1<*Bottom_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=12;
                }

        if(*WallPer==3)
            if(Tail[*Chain].x1==*Left_Border && (Tail[*Chain].y1<*Bottom_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=12;
                }

        if(*WallPer==9)
            if(Tail[*Chain].x1==*Right_Border && (Tail[*Chain].y1>*Bottom_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=6;
                }

        if(*WallPer==3)
            if(Tail[*Chain].x1==*Left_Border && (Tail[*Chain].y1>*Bottom_Border/2))
                while(((*Chain)--)>=(*Count)-(*Stepback))
                {
                    c++;
                    if(i<=c)
                        *WallLoopFar=6;
                }
    }
/*......................................................................................................*/
    HANDLE Descr1=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPos_2={75,9};
    SetConsoleCursorPosition(Descr1,CursorPos_2);
    printf("Vector.......... %c ",*Vector);

    COORD CursorPos_3={75,10};
    SetConsoleCursorPosition(Descr1,CursorPos_3);
    printf("Between......... %c ",*Between);

    COORD CursorPos_4={75,11};
    SetConsoleCursorPosition(Descr1,CursorPos_4);
    printf("WallPer......... %d ",*WallPer);

    COORD CursorPos_5={75,12};
    SetConsoleCursorPosition(Descr1,CursorPos_5);
    printf("WallTan......... %d ",*WallTan);

    COORD CursorPos_6={75,13};
    SetConsoleCursorPosition(Descr1,CursorPos_6);
    printf("WallPerStep..... %d ",*WallPerStep);

    COORD CursorPos_7={75,14};
    SetConsoleCursorPosition(Descr1,CursorPos_7);
    printf("WallTanStep..... %d ",*WallTanStep);

    COORD CursorPos_8={75,15};
    SetConsoleCursorPosition(Descr1,CursorPos_8);
    printf("TailPer......... %d ",*TailPer);

    COORD CursorPos_10={75,16};
    SetConsoleCursorPosition(Descr1,CursorPos_10);
    printf("TailTan......... %d ",*TailTan);

    COORD CursorPos_11={75,17};
    SetConsoleCursorPosition(Descr1,CursorPos_11);
    printf("SelfLoop........ %d ",*SelfLoop);

    COORD CursorPos_12={75,18};
    SetConsoleCursorPosition(Descr1,CursorPos_12);
    printf("WallLoopNear.... %d   ",*WallLoopNear);

    COORD CursorPos_13={75,19};
    SetConsoleCursorPosition(Descr1,CursorPos_13);
    printf("WallLoopFar..... %d   ",*WallLoopFar);

    COORD CursorPos_14={75,20};
    SetConsoleCursorPosition(Descr1,CursorPos_14);
    printf("Deadlock........ %d ",*Deadlock);

    COORD CursorPos_15={75,22};
    SetConsoleCursorPosition(Descr1,CursorPos_15);
    printf("l: %d, r: %d, L: %d, R: %d ",l,r,L,R);
}

void F_Checking_1(int *Key,int *Stepback,int *MealWall,int *WallPer,int *WallTan,int *WallPerStep,int *WallTanStep,int *TailPer,int *TailTan,int *WallLoopNear,int *WallLoopFar,int *SelfLoop,int *Deadlock,char *Vector,char *Between)
{
    if(*Key=='d')
    {
        if((*Vector!='L' || *Stepback==0) && *WallPer!=3 && *WallTan!=3 && (*WallPerStep!=3 || (*WallPerStep==3 && (*MealWall==3 || *MealWall==312 || *MealWall==36))) && (*WallTanStep!=3 || (*WallTanStep==3 && (*MealWall==3 || *MealWall==312 || *MealWall==36))) && *TailPer!=3 && *TailTan!=3 && *WallLoopNear!=3 && *WallLoopFar!=3 && *SelfLoop!=3 && *Deadlock!=3 && *Between!='V')
        *Key='d';
        else *Key='s';
    }

    if(*Key=='s')
    {
        if((*Vector!='U' || *Stepback==0) && *WallPer!=6 && *WallTan!=6 && (*WallPerStep!=6 || (*WallPerStep==6 && (*MealWall==6 || *MealWall==96 || *MealWall==36))) && (*WallTanStep!=6 || (*WallTanStep==6 && (*MealWall==6 || *MealWall==96 || *MealWall==36))) && *TailPer!=6 && *TailTan!=6 && *WallLoopNear!=6 && *WallLoopFar!=6 && *SelfLoop!=6 && *Deadlock!=6 && *Between!='H')
        *Key='s';
        else *Key='a';
    }

    if(*Key=='a')
    {
        if((*Vector!='R' || *Stepback==0) && *WallPer!=9 && *WallTan!=9 && (*WallPerStep!=9 || (*WallPerStep==9 && (*MealWall==9 || *MealWall==912 || *MealWall==96))) && (*WallTanStep!=9 || (*WallTanStep==9 && (*MealWall==9 || *MealWall==912 || *MealWall==96))) && *TailPer!=9 && *TailTan!=9 && *WallLoopNear!=9 && *WallLoopFar!=9 && *SelfLoop!=9 && *Deadlock!=9 && *Between!='V')
        *Key='a';
        else *Key='w';
    }

    if(*Key=='w')
    {
        if((*Vector!='D' || *Stepback==0) && *WallPer!=12 && *WallTan!=12 && (*WallPerStep!=12 || (*WallPerStep==12 && (*MealWall==12 || *MealWall==912 || *MealWall==312))) && (*WallTanStep!=12 || (*WallTanStep==12 && (*MealWall==12 || *MealWall==912 || *MealWall==312))) && *TailPer!=12 && *TailTan!=12 && *WallLoopNear!=12 && *WallLoopFar!=12 && *SelfLoop!=12 && *Deadlock!=12 && *Between!='H')
        *Key='w';
        else *Key='d';
    }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(*Key=='d')
    {
        if((*Vector!='L' || *Stepback==0) && *WallPer!=3 && *WallTan!=3 && (*WallPerStep!=3 || (*WallPerStep==3 && (*MealWall==3 || *MealWall==312 || *MealWall==36))) && (*WallTanStep!=3 || (*WallTanStep==3 && (*MealWall==3 || *MealWall==312 || *MealWall==36))) && *TailPer!=3 && *TailTan!=3 && *WallLoopNear!=3 && *WallLoopFar!=3 && *SelfLoop!=3 && *Deadlock!=3 && *Between!='V')
        *Key='d';
        else *Key='s';
    }

    if(*Key=='s')
    {
        if((*Vector!='U' || *Stepback==0) && *WallPer!=6 && *WallTan!=6 && (*WallPerStep!=6 || (*WallPerStep==6 && (*MealWall==6 || *MealWall==96 || *MealWall==36))) && (*WallTanStep!=6 || (*WallTanStep==6 && (*MealWall==6 || *MealWall==96 || *MealWall==36))) && *TailPer!=6 && *TailTan!=6 && *WallLoopNear!=6 && *WallLoopFar!=6 && *SelfLoop!=6 && *Deadlock!=6 && *Between!='H')
        *Key='s';
        else *Key='a';
    }

    if(*Key=='a')
    {
        if((*Vector!='R' || *Stepback==0) && *WallPer!=9 && *WallTan!=9 && (*WallPerStep!=9 || (*WallPerStep==9 && (*MealWall==9 || *MealWall==912 || *MealWall==96))) && (*WallTanStep!=9 || (*WallTanStep==9 && (*MealWall==9 || *MealWall==912 || *MealWall==96))) && *TailPer!=9 && *TailTan!=9 && *WallLoopNear!=9 && *WallLoopFar!=9 && *SelfLoop!=9 && *Deadlock!=9 && *Between!='V')
        *Key='a';
        else *Key='w';
    }

    if(*Key=='w')
    {
        if((*Vector!='D' || *Stepback==0) && *WallPer!=12 && *WallTan!=12 && (*WallPerStep!=12 || (*WallPerStep==12 && (*MealWall==12 || *MealWall==912 || *MealWall==312))) && (*WallTanStep!=12 || (*WallTanStep==12 && (*MealWall==12 || *MealWall==912 || *MealWall==312))) && *TailPer!=12 && *TailTan!=12 && *WallLoopNear!=12 && *WallLoopFar!=12 && *SelfLoop!=12 && *Deadlock!=12 && *Between!='H')
        *Key='w';
        else *Key='d';
    }
}

void F_Checking_2(int *Key,int *Stepback,int *MealWall,int *WallPer,int *WallTan,int *TailPer,int *TailTan,int *WallLoopNear,int *WallLoopFar,int *SelfLoop,int *Deadlock,char *Vector,char *Between)
{
    if(*Key=='d')
    {
        if((*Vector!='L' || *Stepback==0) && *WallPer!=3 && *WallTan!=3 && *TailPer!=3 && *TailTan!=3 && *WallLoopNear!=3 && *WallLoopFar!=3 && *SelfLoop!=3 && *Deadlock!=3 && *Between!='V')
        *Key='d';
        else *Key='s';
    }

    if(*Key=='s')
    {
        if((*Vector!='U' || *Stepback==0) && *WallPer!=6 && *WallTan!=6 && *TailPer!=6 && *TailTan!=6 && *WallLoopNear!=6 && *WallLoopFar!=6 && *SelfLoop!=6 && *Deadlock!=6 && *Between!='H')
        *Key='s';
        else *Key='a';
    }

    if(*Key=='a')
    {
        if((*Vector!='R' || *Stepback==0) && *WallPer!=9 && *WallTan!=9 && *TailPer!=9 && *TailTan!=9 && *WallLoopNear!=9 && *WallLoopFar!=9 && *SelfLoop!=9 && *Deadlock!=9 && *Between!='V')
        *Key='a';
        else *Key='w';
    }

    if(*Key=='w')
    {
        if((*Vector!='D' || *Stepback==0) && *WallPer!=12 && *WallTan!=12 && *TailPer!=12 && *TailTan!=12 && *WallLoopNear!=12 && *WallLoopFar!=12 && *SelfLoop!=12 && *Deadlock!=12 && *Between!='H')
        *Key='w';
        else *Key='d';
    }
}

void F_Checking_3(int *Key,int *Stepback,int *WallPer,int *WallTan,int *TailPer,int *TailTan,int *WallLoopNear,int *SelfLoop,int *Deadlock,char *Vector,char *Between)
{
    if(*Key=='d')
    {
        if((*Vector!='L' || *Stepback==0) && *WallPer!=3 && *WallTan!=3 && *TailPer!=3 && *TailTan!=3 && *WallLoopNear!=3 && *SelfLoop!=3 && *Deadlock!=3 && *Between!='V')
        *Key='d';
        else *Key='s';
    }

    if(*Key=='s')
    {
        if((*Vector!='U' || *Stepback==0) && *WallPer!=6 && *WallTan!=6 && *TailPer!=6 && *TailTan!=6 && *WallLoopNear!=6 && *SelfLoop!=6 && *Deadlock!=6 && *Between!='H')
        *Key='s';
        else *Key='a';
    }

    if(*Key=='a')
    {
        if((*Vector!='R' || *Stepback==0) && *WallPer!=9 && *WallTan!=9 && *TailPer!=9 && *TailTan!=9 && *WallLoopNear!=9 && *SelfLoop!=9 && *Deadlock!=9 && *Between!='V')
        *Key='a';
        else *Key='w';
    }

    if(*Key=='w')
    {
        if((*Vector!='D' || *Stepback==0) && *WallPer!=12 && *WallTan!=12 && *TailPer!=12 && *TailTan!=12 && *WallLoopNear!=12 && *SelfLoop!=12 && *Deadlock!=12 && *Between!='H')
        *Key='w';
        else *Key='d';
    }
}

void F_Checking_4(int *Key,int *Stepback,int *WallPer,int *WallTan,int *TailPer,int *TailTan,char *Vector,char *Between)
{
     if(*Key=='d')
    {
        if((*Vector!='L' || *Stepback==0) && *WallPer!=3 && *WallTan!=3 && *TailPer!=3 && *TailTan!=3 && *Between!='V')
        *Key='d';
        else *Key='s';
    }

    if(*Key=='s')
    {
        if((*Vector!='U' || *Stepback==0) && *WallPer!=6 && *WallTan!=6 && *TailPer!=6 && *TailTan!=6 && *Between!='H')
        *Key='s';
        else *Key='a';
    }

    if(*Key=='a')
    {
        if((*Vector!='R' || *Stepback==0) && *WallPer!=9 && *WallTan!=9 && *TailPer!=9 && *TailTan!=9 && *Between!='V')
        *Key='a';
        else *Key='w';
    }

    if(*Key=='w')
    {
        if((*Vector!='D' || *Stepback==0) && *WallPer!=12 && *WallTan!=12 && *TailPer!=12 && *TailTan!=12 && *Between!='H')
        *Key='w';
        else *Key='d';
    }
}

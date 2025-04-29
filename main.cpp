#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <graphics.h>
#include <math.h>
#define bool char
#define PI 3.14


enum betGrades {BET_1, BET_2, BET_5, BET_10, BET_50, BET_100};
enum endings {NONE, CASINO_ENDING, CAT_ENDING};
int betGradesValues[] = {1, 2, 5, 10, 50, 100};
char betOffsets[] = {0, 2, 4, 6, 9, 12};
char betWidths[] = {1, 1, 1, 2, 2, 3};
const int offsetx = 100, offsety = 100; // положение относительно левого верхнего угла
const int tileSize = 96; //размер слота (квадратного)
const int spaceBetween = 40; //промежуток между слотами

const int paddingX = 40, paddingY = 40; //padding для таблички, где располагаются слоты


const int tableSizeX = paddingX * 2 + spaceBetween * 2 + tileSize * 3,
          tableSizeY = paddingY * 2 + tileSize;

char slots[3] = {'X', 'X', 'X'};
char statusString[100];


int max(int a, int b) {return a > b ? a : b;}
int min(int a, int b) {return a < b ? a : b;}


void barsize(int x, int y, int w, int h)
{
    bar(x, y, x + w, y + h);
}

void rectsize(int x, int y, int w, int h)
{
    rectangle(x, y, x + w, y + h);
}

void scramble()
{
    for (int i = 0; i < 3; i++)
        slots[i] = (1 + rand() % 9) + '0';
}


void cat(int x, int y, char happy=1)
{
    setcolor(WHITE);
    circle(x, y, 20);
    line(x - 20, y, x - 20, y - 30);
    line(x - 20, y - 30, x - 10, y - 17);
    line(x + 20, y, x + 20, y - 30);
    line(x + 20, y - 30, x + 10, y - 17);
    ellipse(x + 66, y + 22, 0, 360, 60, 20);
    rectsize(x + 16, y + 34, 10, 40);
    rectsize(x + 105, y + 34, 10, 40);

    if (happy)
    {
        arc(x - 7, y + 7, 180, 360, 7);
        arc(x + 7, y + 7, 180, 360, 7);
    }
    else
    {
        arc(x - 5, y + 14, 0, 180, 5);
        arc(x + 5, y + 14, 0, 180, 5);


        arc(x - 10, y, 180, 360, 4);
        line(x - 6, y, x - 10, y - 6);
        line(x - 14, y, x - 10, y - 6);

    }
    circle(x, y + 5, 2);
    circle(x - 10, y - 10, 4);
    circle(x + 10, y - 10, 4);

    int usix = x - 5, usiy = y + 5, usilen = 27;
    printf("%d", (int)(cos(PI / 6) * 10));
    line(usix, usiy, usix - (int)(cos(PI / 6) * usilen ), usiy + (int)(sin(PI / 6) * usilen));
    line(usix, usiy, usix - usilen, usiy);
    line(usix, usiy, usix - (int)(cos(-PI / 6) * usilen), usiy + (int)(sin(-PI / 6) * usilen));
    usix += 10;
    line(usix, usiy, usix + (int)(cos(PI / 6) * usilen ), usiy + (int)(sin(PI / 6) * usilen));
    line(usix, usiy, usix + usilen, usiy);
    line(usix, usiy, usix + (int)(cos(-PI / 6) * usilen), usiy + (int)(sin(-PI / 6) * usilen));

}
void sadcat(int x, int y)
{
    setcolor(WHITE);
    circle(x, y, 20);
    line(x - 20, y, x - 20, y - 30);
    line(x - 20, y - 30, x - 10, y - 17);
    line(x + 20, y, x + 20, y - 30);
    line(x + 20, y - 30, x + 10, y - 17);
    ellipse(x + 66, y + 22, 0, 360, 60, 20);
    rectsize(x + 16, y + 34, 10, 40);
    rectsize(x + 105, y + 34, 10, 40);

    arc(x - 5, y + 14, 0, 180, 5);
    arc(x + 5, y + 14, 0, 180, 5);
    circle(x, y + 5, 2);
    circle(x - 10, y - 10, 4);
    circle(x + 10, y - 10, 4);

    arc(x - 10, y, 180, 360, 4);
    line(x - 6, y, x - 10, y - 6);
    line(x - 14, y, x - 10, y - 6);

    int usix = x - 5, usiy = y + 5, usilen = 27;
    printf("%d", (int)(cos(PI / 6) * 10));
    line(usix, usiy, usix - (int)(cos(PI / 6) * usilen ), usiy + (int)(sin(PI / 6) * usilen));
    line(usix, usiy, usix - usilen, usiy);
    line(usix, usiy, usix - (int)(cos(-PI / 6) * usilen), usiy + (int)(sin(-PI / 6) * usilen));
    usix += 10;
    line(usix, usiy, usix + (int)(cos(PI / 6) * usilen ), usiy + (int)(sin(PI / 6) * usilen));
    line(usix, usiy, usix + usilen, usiy);
    line(usix, usiy, usix + (int)(cos(-PI / 6) * usilen), usiy + (int)(sin(-PI / 6) * usilen));

}

void fish(int x, int y)
{
    ellipse(x, y, 0, 360, 20, 8);
    line(x + 20, y, x + 30, y - 8);
    line(x + 20, y, x + 30, y + 8);
    line(x + 30, y - 8, x + 30, y + 8);
}


void lose()
{
    outtextxy(0, 0, "Вы проиграли все деньги и теперь вам нельзя играть в казино :(");
    outtextxy(0, 0 + textheight("1"), "но котик вас любит, вне зависимости от материального состояния <3");
    cat(offsetx, offsety + textheight("1") + 50);
}
void wincasino()
{
    outtextxy(0, 0, "На выигранные деньги вы купили казино и делаете состояние на чужом горе");
    outtextxy(0, 0 + textheight("1"), "котик отвернулся от вас :((((");
    sadcat(offsetx, offsety + textheight("1") + 50);
}
void wincat()
{
    outtextxy(0, 0, "На выигранные деньги вы купили еду котику, как и хотели");
    outtextxy(0, 0 + textheight("1"), "Поздравляем!");
    cat(100, 100);
    for (int i = 0; i < 5; i++)
        fish(60 + rand() % 200, 60 + rand() % 200);
}
void intro()
{
    outtextxy(0, 0, "Из любви к своему котику вы решили купить ему кучу вкусностей");
    outtextxy(0, 0 + textheight("1"), "но у вас совсем немного денег, поэтому вы решили их преумножить");
    outtextxy(0, 0 + 2 * textheight("1"), "сомнительным путем... В казино!");
    outtextxy(0, 0 + 4 * textheight("1"), "Нажмите любую клавишу для продолжения...");

    cat(50, 0 + 10 * textheight("1"));
}


int betGrade = BET_1;
int ending = NONE;
int balance = 50, bet = 1;
bool wasSpinned = false;




int main()
{
    int gdriver=DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    intro();
    getch();
    cleardevice();

    while (1)
    {

        if (wasSpinned)
        {
            wasSpinned = FALSE;
            if (slots[0] == slots[1] && slots[1] == slots[2])
            {
                balance += bet * 5;
                setfillstyle(SOLID_FILL, YELLOW);
                sprintf(statusString, "Вы выбили 3 топора и умножили ставку впятеро!!!\0");
                for (int i = 0; i < 10; i++)
                {
                    outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 6, statusString);
                    Sleep(60);
                    barsize(offsetx, offsety + tableSizeY + textheight("1") * 6, textwidth(statusString),textheight("1"));
                    Sleep(60);
                }
                goto evaluation;
            }
            for (int i = 0; i < 3; i++)
                for (int j = i; j < 3; j++)
                    if (slots[i] == slots[j] && i != j)
                    {
                        balance += bet * 2;
                        setfillstyle(SOLID_FILL, MAGENTA);
                        sprintf(statusString, "2 совпадения - ставка увеличилась вдвое!\0");
                        for (int i = 0; i < 6; i++)
                        {
                            outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 6, statusString);
                            Sleep(60);
                            barsize(offsetx, offsety + tableSizeY + textheight("1") * 6, textwidth(statusString),textheight("1"));
                            Sleep(60);
                        }
                        goto evaluation;
                    }
            balance -= bet;
            sprintf(statusString, "Ставка потеряна...\0");
        }

        evaluation:
        if (balance <= 0)
        {
            setcolor(GREEN);
            outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 7, "Черт, я все проиграл...");
            setcolor(WHITE);
            Sleep(3000);
            cleardevice();
            lose();
            getch();
            goto exitCycle;
        }

        if (balance >= 3000)
        {
            switch(ending)
            {
                case CASINO_ENDING:
                    cleardevice();
                    wincasino();
                    getch();
                    goto exitCycle;
                break;
                case CAT_ENDING:
                    cleardevice();
                    wincat();
                    getch();
                    goto exitCycle;
                break;
            }

        }



        cleardevice();

        setfillstyle(SOLID_FILL, RED);
        barsize(offsetx, offsety, tableSizeX, tableSizeY);

        setfillstyle(SOLID_FILL, WHITE);
        setbkcolor(WHITE);
        setcolor(BLACK);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, tileSize / 8);
        for (int i = 0; i < 3; i++)
        {
            char slotNumber[2];
            slotNumber[0] = slots[i];
            slotNumber[1] = '\0';
            int xpos = offsetx + paddingX + i * (tileSize + spaceBetween), ypos = offsety + paddingY;
            barsize(xpos, ypos, tileSize, tileSize);
            outtextxy(xpos + (tileSize - textwidth("X")) / 2, offsety + paddingY, slotNumber);
        }
        setbkcolor(BLACK);
        setcolor(WHITE);
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        outtextxy(offsetx, offsety + tableSizeY, "Изменить ставку на: 1 2 5 10 50 100 (стрелки лево право)");
        rectsize(offsetx + textwidth("Изменить ставку на: ") + textwidth("1") * betOffsets[betGrade], offsety + tableSizeY,
                 textwidth("1") * betWidths[betGrade], textheight("1"));
                 outtextxy(offsetx, offsety + tableSizeY + textheight("1"), "A - уменьшить, S - увеличить ставку на выдел.значение");
        outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 2, "Z - поделить ставку, X - умножить ставку | вдвое");
        outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 3, "C - сбросить ставку(до 1)");
        outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 4, "Крутить барабан - SPACE!!!");

        outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 6, statusString);

        char balanceString[50];
        sprintf(balanceString, "Ваш баланс: %d    Ваша ставка: %d\0", balance, bet);
        outtextxy(offsetx, offsety - textheight("1"), balanceString);

        if (balance >= 3000)
        {
            setcolor(GREEN);
            outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 7, "Черт, да я могу купить это казино! (F - купить)");
            setcolor(DARKGRAY);
            outtextxy(offsetx, offsety + tableSizeY + textheight("1") * 8, "Или же... (G)");
            setcolor(WHITE);
        }

        char answer = getch();
        if (answer >= 'A' && answer <= 'Z')
            answer = tolower(answer);
        printf("%d\n", answer);
        switch (answer)
        {
            case 32: //space
                wasSpinned = TRUE;
                scramble();
                break;
            case 109: //right arrow
                betGrade = min(betGrade + 1, 5);
                break;
            case 107: //left arrow
                betGrade = max(0, betGrade - 1);
                break;
            case 'a':
                bet -= betGradesValues[betGrade];
                if (bet <= 0)
                    bet = 1;
                break;
            case 's':
                bet += betGradesValues[betGrade];
                if (bet >= balance)
                    bet = balance;
                break;
            case 'z':
                bet /= 2;
                if (bet <= 0)
                    bet = 1;
                break;
            case 'x':
                bet *= 2;
                if (bet >= balance)
                    bet = balance;
                break;
            case 'c':
                bet = 1;
                break;
            case 'l':
                balance = 10000;
                break;
            case 'f':
                if (balance >= 3000) ending = CASINO_ENDING;
                break;
            case 'g':
                if (balance >= 3000) ending = CAT_ENDING;
                break;


            case 27: //esc
                goto exitCycle;
        }
        Sleep(100);
        //cleardevice();
    }

    exitCycle:
    closegraph();

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include <string.h>
#define BLACK 0
#define WHITE 7
int nitem = 0, num = 8, budget = 0, count = 0;
void SetColor(int color, int bgcolor); // 글자 색과 배경 색을 변경한다. 
void gotoxy(int x, int y); // 커서의 위치를 이동시킨다.
void CursorView(char show); //커서숨기기 
void display(int x, int y, char *text, int foreColor, int bgColor);
void displayInt(int x, int y, int num, int foreColor, int bgColor);
typedef struct ITEM {  //품목을 나타내는 구조체 ITEM 정의 (살 품목)
	char name[100];
	int price;
	int num;
} Item;
typedef struct { // 가계부 전용 구조체
	char date[100]; // 날짜
	int  n; // 수입은 1 , 지출은 0
	int money; // 돈 내놔!
	char title[100]; //제목
	char content[100]; // 내용
}Book;
int main() {

	Item * item = (Item *)malloc(sizeof(Item) * num); // 일정 저장 구조체 선언 
	Book * book = (Book *)malloc(sizeof(Book) * num);

	int i;
	char str[32];
	CursorView(0);
	FILE *fp;
	fp = fopen("item1.txt", "r");
	if (fp == NULL) {
		printf("item1.txt - 파일을 찾을 수 없습니다.\n");
		printf("파일 추가후 다시 시작하세요.\n");
		Sleep(3000);
		return 0;
	}
	
	while (!feof(fp)) {
		fgets(str, 100, fp);
		nitem++;
	}
	nitem--;
	nitem /= 2;
	while (nitem > num) { // 일정 개수가 할당된 크기보다 큰 경우 

		num *= 2; // 일정 저장 개수 2배로 곱하기 
		item = (Item *)realloc(item, sizeof(Item) * num); // 일정 저장 구조체 선언 
		book = (Book *)realloc(book, sizeof(Book) * num);
	}
	rewind(fp);

	fscanf(fp, "%d\n", &budget);
	//////////////////
	for (count = 0; count<nitem*2; count++) {
		if (count % 2 == 0) {
			fgets(item[count/2].name, 100, fp);/////////////////////
		}
		else if (count % 2 == 1) {
			fscanf(fp, "%d %d\n", &item[count/2].num, &item[count/2].price);
		}
	}
	fclose(fp);
	fp = fopen("item2.txt", "r");
	//////////////////////////
	int nitem2 = 0;
	if (fp == NULL) {
		printf("item2.txt - 파일을 찾을 수 없습니다.\n");
		printf("파일 추가후 다시 시작하세요.\n");
		Sleep(3000);
		return 0;
	}

	while (!feof(fp)) {
		fgets(str, 100, fp);
		nitem2++;
	}
	while (nitem2 > num) { // 일정 개수가 할당된 크기보다 큰 경우 

		num *= 2; // 일정 저장 개수 2배로 곱하기 
		item = (Item *)realloc(item, sizeof(Item) * num); // 일정 저장 구조체 선언 
		book = (Book *)realloc(book, sizeof(Book) * num);
	}
	rewind(fp);

	for (count = 0; count<nitem2; count++) {
		fscanf(fp, "%s %d %d %s %s", book[count].date, &book[count].n, &book[count].money, book[count].title, book[count].content);
	}
	int key;
	int mode = 0;
	display(50, 2, "장보기 프로그램", BLACK, WHITE);
	display(0, 3, "------------------------------------------------------------------------------------------------------------------------", WHITE, BLACK);
	display(0, 4, "MAIN MENU     ", WHITE, BLACK);
	display(0, 5, " 가계부", BLACK, WHITE);
	display(0, 6, " 구매 리스트", WHITE, BLACK);
	while (1) {
		key = getch();
		if (key == 224) {
			key = getch();
			if (key == 72)
				mode++;
			if (key == 80)
				mode--;
		}
		if (key == ' ') {
			if (mode % 2 == 0) {
				display(0, 4, " 가계부          ", WHITE, BLACK);
				display(0, 5, "                 ", WHITE, BLACK);
				printf("잔여 금액은 %d원입니다.", budget);
				display(0, 6, "                 ", WHITE, BLACK);
				for (int z = 0; z < nitem; z++) {
					display(0, z + 6, item[z].name, WHITE, BLACK);
					displayInt(30, z + 6, item[z].price, WHITE, BLACK);
				}
				while (1) {
					if (getch() == ' ') {
						display(0, 4, "MAIN MENU", WHITE, BLACK);
						break;
					}
				}
			}
			if (abs(mode) % 2 == 1) {

				///////////
				display(0, 4, " 지출 리스트      ", WHITE, BLACK);
				display(0, 5, "                 ", WHITE, BLACK);
				display(0, 6, "                 ", WHITE, BLACK);
				for (int z = 0; z < nitem; z++) {
					display(0, z + 5, item[z].name, WHITE, BLACK);
				}
				while (1) {
					if (getch() == ' ') {
						display(0, 4, "MAIN MENU      ", WHITE, BLACK);
						break;
					}
				}

			}
		}
		if (mode % 2 == 0) {
			display(0, 5, " 가계부", BLACK, WHITE);
			display(0, 6, " 구매 리스트", WHITE, BLACK);
		}
		if (abs(mode) % 2 == 1) {
			display(0, 5, " 가계부", WHITE, BLACK);
			display(0, 6, " 구매 리스트", BLACK, WHITE);
		}

	}

}
/* 여기에 있는 내용은 WINDOWS API에 있는 내용으로 windows 운영체제에서만 사용 가능하게 됩니다. - 시작 */

void SetColor(int text, int bgcolor) // 글자 색과 배경 색을 변경한다. 
{
	int color = (bgcolor << 4) | text;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y) // 커서의 위치를 이동시킨다. 
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void CursorView(char show) //커서숨기기
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}
void display(int x, int y, char *text, int foreColor, int bgColor) {
	gotoxy(x, y);
	SetColor(foreColor, bgColor);
	printf("%s", text);
}
void displayInt(int x, int y, int num, int foreColor, int bgColor) {
	gotoxy(x, y);
	SetColor(foreColor, bgColor);
	printf("%d", num);
}


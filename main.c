#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <Windows.h>
#include <string.h>
int nitem = 0;

void SetColor(int color, int bgcolor); // 글자 색과 배경 색을 변경한다. 
void gotoxy(int x, int y); // 커서의 위치를 이동시킨다.
void CursorView(char show); //커서숨기기 
void display(int x, int y, char *text, int foreColor, int bgColor);

typedef struct ITEM{  //품목을 나타내는 구조체 ITEM 정의 (살 품목)
       char* name;
       int price;
       int num;
} Item;

typedef struct { // 가계부 전용 구조체
        char *date; // 날짜
        int  n; // 수입은 1 , 지출은 0
        int money; // 돈 내놔!
        char * title; //제목
        char * content; // 내용
}Book;

int main(){
             int i,n,num=8;
    
         CursorView(0);
         	int j, k;
		char str[300];
		struct ITEM *thing[5]; 

	FILE *fp;
	fp = fopen("item.txt","r");
	
	if(fp == NULL)
		printf("파일을 찾을 수 없습니다.\n");
		
	int count[5];
	
	for(i=0; i<5; i++)
		count[i] = 0;

//줄 수를 인식해서 nitem에 저장한다 
	while (getc(fp) != EOF) {// 파일 끝인지 확인한다  
		fgets(str, 300, fp);
		nitem++;
	}
	
	rewind(fp); // 파일 포인터를 처음으로 되돌린다  
	
	// 입력 파일로 부터 일정 데이터를 입력 받는다 
	for(k=0; k<nitem; k++) {
		fgets(str, 300, fp);
		j = count[i];
		
		sscanf(str, "%6s %6d", thing[i][j].price, thing[i][j].num);
		count[i]++;
		
	} 
         FILE * read1 = fopen("input.txt", "r"); // 파일과의 스트림 헤제         
        n = 0;
        char buf[1000]; // 일정의 개수를 파악하기 위한 버퍼
        while(fgets(buf, 1000, read1) != NULL) {
                n++;
        }
        
        while(n > num){ // 일정 개수가 할당된 크기보다 큰 경우 
        
                num *= 2; // 일정 저장 개수 2배로 곱하기 
                //크기  할당 부탁 
        }
         
        fclose(read1); // read1 헤제 (파일 읽는 위치 초기화를 위해)        
    return 0;
}

/* 여기에 있는 내용은 WINDOWS API에 있는 내용으로 windows 운영체제에서만 사용 가능하게 됩니다. - 시작 */
 
void SetColor(int text, int bgcolor) // 글자 색과 배경 색을 변경한다. 
{
        int color= (bgcolor << 4) | text;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
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


/* -끝- */ 

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <string.h>

#define black 0 // 색상 정의 (매크로) 
#define blue 1
#define green 2
#define blue_green 3
#define red 4
#define purple 5
#define yellow 6
#define white 7
#define color_bright 8
typedef struct { // 일정 저장용 구조체 
	char *date;
	char * clock;
	int  important_level;
	int  group;
	char * title;
	char * content;
} Plan;

int n=0,num = 8,location_cursor=1; // 기본 일정 저장 개수 정하기 

int keyboard_input(); // 키보드 처리 받기 
void SetColor(int color, int bgcolor); // 글자 색과 배경 색을 변경한다. 
void gotoxy(int x, int y); // 커서의 위치를 이동시킨다.
void CursorView(char show); //커서숨기기 
void put_cursor(int x); // 보여주는 ( 특수문자 )  커서의 위치 변경 및 잘못된 키보드 입력시 작동 

int main(void) {
 	int i;
 	Plan * arr = (Plan *) malloc(sizeof(Plan) * num); // 일정 저장 구조체 선언 
	Plan * group0 = (Plan *) malloc(sizeof(Plan) * num); int group0_n = 0;
	Plan * group1 = (Plan *) malloc(sizeof(Plan) * num); int group1_n = 0;
	Plan * group2 = (Plan *) malloc(sizeof(Plan) * num); int group2_n = 0;
	Plan * group3 = (Plan *) malloc(sizeof(Plan) * num); int group3_n = 0;
	Plan * group4 = (Plan *) malloc(sizeof(Plan) * num); int group4_n = 0;
 	 	
 	CursorView(0);
 	FILE * read1 = fopen("input.txt", "r"); // 파일과의 스트림 헤제 	
	n = 0;
	char buf[1000]; // 일정의 개수를 파악하기 위한 버퍼
	while(fgets(buf, 1000, read1) != NULL) {
		n++;
	}
	
	while(n > num){ // 일정 개수가 할당된 크기보다 큰 경우 
	
		num *= 2; // 일정 저장 개수 2배로 곱하기 
		arr = (Plan *)realloc(arr,sizeof(Plan ) * num); // 크기 재할당하기 
		group0 = (Plan *)realloc(group0,sizeof(Plan ) * num); // 크기 재할당하기 
		group1 = (Plan *)realloc(group1,sizeof(Plan ) * num); // 크기 재할당하기 
		group2 = (Plan *)realloc(group2,sizeof(Plan ) * num); // 크기 재할당하기 
		group3 = (Plan *)realloc(group3,sizeof(Plan ) * num); // 크기 재할당하기 
		group4 = (Plan *)realloc(group4,sizeof(Plan ) * num); // 크기 재할당하기 
	}
	 
	fclose(read1); // read1 헤제 (파일 읽는 위치 초기화를 위해)	

	FILE * read2 = fopen("input.txt", "r"); // read2 선언  (파일 읽는 위치 초기화를 위해)
	for(i=0;i<n;i++){
		arr[i].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
		arr[i].clock = (char *) malloc(sizeof(char) * 10);
		arr[i].title = (char *) malloc(sizeof(char) * 300);
		arr[i].content = (char *) malloc(sizeof(char) * 300);
		fscanf(read2,"%s %s %d %d %s %s",arr[i].date,arr[i].clock,&arr[i].important_level,&arr[i].group,arr[i].title,arr[i].content); // 입력 받기 
	}
	fclose(read2); // read2 헤제 (파일 읽는 위치 초기화를 위해) 
	
	for(i=0;i<n;i++){
		char tmp_date[10],tmp_clock[5];
		strcpy(tmp_date,arr[i].date); // 각각 날짜, 시간을 복사 하여 임시 배열에 저장 
		strcpy(tmp_clock,arr[i].clock); 
		arr[i].date[4] = '.';  // 모든 값 변경 
		arr[i].date[5] = tmp_date[4];
		arr[i].date[6] = tmp_date[5];
		arr[i].date[7] = '.';
		arr[i].date[8] = tmp_date[6];
		arr[i].date[9] = tmp_date[7];
		arr[i].date[10] = '.';
		arr[i].date[11] = 0;
		arr[i].clock[2]= ':';
		arr[i].clock[3] = tmp_clock[2];
		arr[i].clock[4] = tmp_clock[3];
		arr[i].clock[5] = 0;
	}
	
	for(i=0;i<n;i++){
	
		switch(arr[i].group){
			case 0:
				group0[i].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
				group0[i].clock = (char *) malloc(sizeof(char) * 10);
				group0[i].title = (char *) malloc(sizeof(char) * 300);
				group0[i].content = (char *) malloc(sizeof(char) * 300);
				strcpy(group0[i].date, arr[i].date); // 모든 문자열을 복사한다
				strcpy(group0[i].clock, arr[i].clock);
				strcpy(group0[i].title, arr[i].title);
				strcpy(group0[i].content, arr[i].content);
				group0[i].important_level = arr[i].important_level; // 모든 값을 복사한다
				group0[i].group = arr[i].group;
				group0_n++; // 그룹의 일정 개수에 1을 더한다. 
				break;		
			
			case 1:
				group1[group1_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
				group1[group1_n].clock = (char *) malloc(sizeof(char) * 10);
				group1[group1_n].title = (char *) malloc(sizeof(char) * 300);
				group1[group1_n].content = (char *) malloc(sizeof(char) * 300);
				strcpy(group1[group1_n].date, arr[i].date); // 모든 문자열을 복사한다
				strcpy(group1[group1_n].clock, arr[i].clock);
				strcpy(group1[group1_n].title, arr[i].title);
				strcpy(group1[group1_n].content, arr[i].content);
				group1[group1_n].important_level = arr[i].important_level; // 모든 값을 복사한다
				group1[group1_n].group = arr[i].group;
				group1_n++; // 그룹의 일정 개수에 1을 더한다.
				break;
					
			case 2:
				group2[group2_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
				group2[group2_n].clock = (char *) malloc(sizeof(char) * 10);
				group2[group2_n].title = (char *) malloc(sizeof(char) * 300);
				group2[group2_n].content = (char *) malloc(sizeof(char) * 300);
				strcpy(group2[group2_n].date, arr[i].date); // 모든 문자열을 복사한다
				strcpy(group2[group2_n].clock, arr[i].clock);
				strcpy(group2[group2_n].title, arr[i].title);
				strcpy(group2[group2_n].content, arr[i].content);
				group2[group2_n].important_level = arr[i].important_level; // 모든 값을 복사한다 
				group2[group2_n].group = arr[i].group;
				group2_n++; // 그룹의 일정 개수에 1을 더한다.
				break;	
				
			case 3:
				group3[group3_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
				group3[group3_n].clock = (char *) malloc(sizeof(char) * 10);
				group3[group3_n].title = (char *) malloc(sizeof(char) * 300);
				group3[group3_n].content = (char *) malloc(sizeof(char) * 300);
				strcpy(group3[group3_n].date, arr[i].date); // 모든 문자열을 복사한다
				strcpy(group3[group3_n].clock, arr[i].clock);
				strcpy(group3[group3_n].title, arr[i].title);
				strcpy(group3[group3_n].content, arr[i].content);
				group3[group3_n].important_level = arr[i].important_level; // 모든 값을 복사한다
				group3[group3_n].group = arr[i].group;
				group3_n++; // 그룹의 일정 개수에 1을 더한다. 
					break;	
				
			case 4:
				group4[group4_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
				group4[group4_n].clock = (char *) malloc(sizeof(char) * 10);
				group4[group4_n].title = (char *) malloc(sizeof(char) * 300);
				group4[group4_n].content = (char *) malloc(sizeof(char) * 300);
				strcpy(group4[group4_n].date, arr[i].date); // 모든 문자열을 복사한다
				strcpy(group4[group4_n].clock, arr[i].clock);
				strcpy(group4[group4_n].title, arr[i].title);
				strcpy(group4[group4_n].content, arr[i].content);
				group4[group4_n].important_level = arr[i].important_level; // 모든 값을 복사한다
				group4[group4_n].group = arr[i].group;
				group4_n++; // 그룹의 일정 개수에 1을 더한다. 
				break;	
		}
		
	}

		printf("위치 |    날짜     |  시간 | 중요도|  그룹명 |     제목 &  내용 \n");
		
			for(i=0;i<n;i++){
				if( location_cursor-1 == i ) SetColor(red,blue + color_bright);
				switch(arr[i].group){
					case 0:
						printf("     | %s | %s | %d번째 | 공부(0) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;
					 
					case 1:
						printf("     | %s | %s | %d번째 | 상담(1) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break; 
					
					case 2:
						printf("     | %s | %s | %d번쨰 | 약속(2) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 3:
						printf("     | %s | %s | %d번쨰 | 휴식(3) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 4:
						printf("     | %s | %s | %d번째 | 여행(4) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	 
				}
				SetColor(white,black);
		}
	put_cursor(1);
	
	while(1){
		put_cursor(1);
		system("cls");
			printf("위치 |    날짜     |  시간 | 중요도|  그룹명 |     제목 &  내용 \n");
		
			for(i=0;i<n;i++){
				if( location_cursor-1 == i ) SetColor(red,blue + color_bright);
				switch(arr[i].group){
					case 0:
						printf("     | %s | %s | %d번째 | 공부(0) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;
					 
					case 1:
						printf("     | %s | %s | %d번째 | 상담(1) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break; 
					
					case 2:
						printf("     | %s | %s | %d번쨰 | 약속(2) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 3:
						printf("     | %s | %s | %d번쨰 | 휴식(3) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 4:
						printf("     | %s | %s | %d번째 | 여행(4) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	 
				}
				SetColor(white,black);
		}
		put_cursor(1);
		int input = keyboard_input(); // 키보드 입력! 
		if(input == 1){
			if(location_cursor > 1){
				put_cursor(-1);
				location_cursor--;
				put_cursor(1);
			}
		}
		else if (input == -1){
			if(location_cursor < n){
				put_cursor(-1);
				location_cursor++;
				put_cursor(1);
			}
		}
		else if (input == 0){
			system("cls");
			switch(arr[location_cursor-1].group){
				case 0:
					printf("%d번째 일정\n일시(날짜) : %s \n일시(시간) :  %s \n중요도 : %d번째\n 그룹 :  공부(0) \n제목 : %s \n내용 : %s\n",location_cursor,arr[location_cursor-1].date,arr[location_cursor-1].clock,arr[location_cursor-1].important_level,arr[location_cursor-1].title,arr[location_cursor-1].content); // 모두 출력 
					break;
					 
				case 1:
					printf("%d번째 일정\n일시(날짜) : %s \n일시(시간) :  %s \n중요도 : %d번째\n 그룹 :  상담(1) \n제목 : %s \n내용 : %s\n",location_cursor,arr[location_cursor-1].date,arr[location_cursor-1].clock,arr[location_cursor-1].important_level,arr[location_cursor-1].title,arr[location_cursor-1].content); // 모두 출력
					break; 
					
				case 2:
					printf("%d번째 일정\n일시(날짜) : %s \n일시(시간) :  %s \n중요도 : %d번째\n 그룹 :  약속(2) \n제목 : %s \n내용 : %s\n",location_cursor,arr[location_cursor-1].date,arr[location_cursor-1].clock,arr[location_cursor-1].important_level,arr[location_cursor-1].title,arr[location_cursor-1].content); // 모두 출력
					break;
					
				case 3:
					printf("%d번째 일정\n일시(날짜) : %s \n일시(시간) :  %s \n중요도 : %d번째\n 그룹 :  휴식(3) \n제목 : %s \n내용 : %s\n",location_cursor,arr[location_cursor-1].date,arr[location_cursor-1].clock,arr[location_cursor-1].important_level,arr[location_cursor-1].title,arr[location_cursor-1].content); // 모두 출력
					break;
					
				case 4:
					printf("%d번째 일정\n일시(날짜) : %s \n일시(시간) :  %s \n중요도 : %d번째\n 그룹 :  여행(4) \n제목 : %s \n내용 : %s\n",location_cursor,arr[location_cursor-1].date,arr[location_cursor-1].clock,arr[location_cursor-1].important_level,arr[location_cursor-1].title,arr[location_cursor-1].content); // 모두 출력
					break;
				}
				while(1){
					int input = keyboard_input();
					if(input == -2) break;
				}
				system("cls");
				printf("위치 |    날짜     |  시간 | 중요도|  그룹명 |     제목 &  내용 \n");
				for(i=0;i<n;i++){
				if( location_cursor-1 == i ) SetColor(red,blue + color_bright);
				switch(arr[i].group){
					case 0:
						printf("     | %s | %s | %d번째 | 공부(0) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;
					 
					case 1:
						printf("     | %s | %s | %d번째 | 상담(1) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break; 
					
					case 2:
						printf("     | %s | %s | %d번쨰 | 약속(2) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 3:
						printf("     | %s | %s | %d번쨰 | 휴식(3) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 4:
						printf("     | %s | %s | %d번째 | 여행(4) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력
					
					SetColor(white,black); 	 
				}		 
			}
			
			
		}
		else if(input == 2){
			
			char tmp[50];
			system("cls");
			if(n+1 >= num){ // 일정 개수가 할당된 크기보다 큰 경우 
			num *= 2; // 일정 저장 개수 2배로 곱하기 
			arr = (Plan *)realloc(arr,sizeof(char *) * num); // 크기 재할당하기 
			group0 = (Plan *)realloc(group0,sizeof(char *) * num); // 크기 재할당하기 
			group1 = (Plan *)realloc(group1,sizeof(char *) * num); // 크기 재할당하기 
			group2 = (Plan *)realloc(group2,sizeof(char *) * num); // 크기 재할당하기 
			group3 = (Plan *)realloc(group3,sizeof(char *) * num); // 크기 재할당하기 
			group4 = (Plan *)realloc(group4,sizeof(char *) * num); // 크기 재할당하기 
			}
			
			arr[n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
			arr[n].clock = (char *) malloc(sizeof(char) * 10);
			arr[n].title = (char *) malloc(sizeof(char) * 300);
			arr[n].content = (char *) malloc(sizeof(char) * 300);
			printf("일정을 추가합니다.\n");
			printf("날짜를 입력하세요. 입력 : ");
			scanf("%s",arr[n].date);
			printf("시각을 입력하세요. 입력 : ");
			scanf("%s",arr[n].clock);
			printf("중요도를 입력하세요. 입력 : "); 
			scanf("%d",&arr[n].important_level);
			printf("그룹명을 입력하세요. 입력 : ");
			scanf("%s",tmp);
			if(!strcmp(tmp,"공부")) arr[n].group=0; 
			if(!strcmp(tmp,"상담")) arr[n].group=1; 
			if(!strcmp(tmp,"약속")) arr[n].group=2; 
			if(!strcmp(tmp,"휴식")) arr[n].group=3; 
			if(!strcmp(tmp,"여행")) arr[n].group=4; 
			printf("일정의 제목을 입력하세요. 입력 : "); 
			scanf("%s",arr[n].title);
			printf("일정의 내용을 입력하세요. 입력 : "); 
			scanf("%s",arr[n].content);
			FILE * write1 = fopen("input.txt", "a"); // write1 선언  (파일 읽는 위치 초기화를 위해) 
			fprintf(write1, "\n%s %s %d %d %s %s",arr[n].date,arr[n].clock,arr[n].important_level,arr[n].group,arr[n].title,arr[n].content);
			fclose(write1);
			printf("abc"); 
			char tmp_date[10],tmp_clock[5];
			strcpy(tmp_date,arr[n].date); // 각각 날짜, 시간을 복사 하여 임시 배열에 저장 
			strcpy(tmp_clock,arr[n].clock); 
			arr[n].date[4] = '.';  // 모든 값 변경 
		arr[n].date[5] = tmp_date[4];
		arr[n].date[6] = tmp_date[5];
		arr[n].date[7] = '.';
		arr[n].date[8] = tmp_date[6];
		arr[n].date[9] = tmp_date[7];
		arr[n].date[10] = '.';
		arr[n].date[11] = 0;
		arr[n].clock[2]= ':';
		arr[n].clock[3] = tmp_clock[2];
		arr[n].clock[4] = tmp_clock[3];
		arr[n].clock[5] = 0;
		
		n++;
			system("cls");
			printf("위치 |    날짜     |  시간 | 중요도|  그룹명 |     제목 &  내용 \n");
			 
				for(i=0;i<n;i++){
					if( location_cursor-1 == i ) SetColor(red,blue + color_bright);
				switch(arr[i].group){
					case 0:
						printf("     | %s | %s | %d번째 | 공부(0) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;
					 
					case 1:
						printf("     | %s | %s | %d번째 | 상담(1) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break; 
					
					case 2:
						printf("     | %s | %s | %d번쨰 | 약속(2) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 3:
						printf("     | %s | %s | %d번쨰 | 휴식(3) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 4:
						printf("     | %s | %s | %d번째 | 여행(4) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;	 
				}
				
				SetColor(white,black);
			}
		}
		else if (input == 3){
			
			system("cls");
			char tmp[300],tmp_date[10],tmp_clock[5];
			printf("일정 변경을 선택하셨습니다. 일정 변경 진행합니다. (변경하고 싶지 않으시다면 공백으로 두십시오!)\n");
			printf("변경하실 일정의 날짜를 입력해 주십시오. 입력 : ");
			tmp_date[1] = 120;
			gets(tmp_date);
			
			printf("변경하실 일정의 시각을 입력해 주십시오. 입력 : ");
			tmp_clock[1] = 120;
			gets(tmp_clock);
			
			printf("변경하실 일정의 중요도를 입력해 주십시오. 입력 : ");
			tmp[1] = 120;
			gets(tmp);
			if(tmp[1] != 120)  arr[location_cursor-1].important_level = atoi(tmp);
			
			printf("그룹명을 입력하세요. 입력 : ");
			tmp[1] = 120;
			gets(tmp);
			if(tmp[1] != 120){
				if(!strcmp(tmp,"공부")) arr[location_cursor-1].group=0; 
				if(!strcmp(tmp,"상담")) arr[location_cursor-1].group=1; 
				if(!strcmp(tmp,"약속")) arr[location_cursor-1].group=2; 
				if(!strcmp(tmp,"휴식")) arr[location_cursor-1].group=3; 
				if(!strcmp(tmp,"여행")) arr[location_cursor-1].group=4; 
			}
			
			printf("변경하실 일정의 제목을 입력해 주십시오. 입력 : ");
			tmp[1] = 120;
			gets(tmp);
			if(tmp[1] != 120){
				strcpy(arr[location_cursor-1].title,tmp);
			} 
			
			printf("변경하실 일정의 내용을 입력해 주십시오. 입력 : ");
			tmp[1] = 120;
			gets(tmp);
			if(tmp[1] != 120){
				strcpy(arr[location_cursor-1].content,tmp);
			} 
			
			if(tmp_date[1] != 120){
				arr[location_cursor-1].date[4] = '.';  // 모든 값 변경 
				arr[location_cursor-1].date[5] = tmp_date[4];
				arr[location_cursor-1].date[6] = tmp_date[5];
				arr[location_cursor-1].date[7] = '.';
				arr[location_cursor-1].date[8] = tmp_date[6];
				arr[location_cursor-1].date[9] = tmp_date[7];
				arr[location_cursor-1].date[10] = '.';
				arr[location_cursor-1].date[11] = 0;
			}
			
			if(tmp_clock[1] != 120){
				arr[location_cursor-1].clock[2]= ':';
				arr[location_cursor-1].clock[3] = tmp_clock[2];
				arr[location_cursor-1].clock[4] = tmp_clock[3];
				arr[location_cursor-1].clock[5] = 0;
			}
			
			FILE * write2 = fopen("input.txt", "w"); // write2 선언  (파일 읽는 위치 초기화를 위해) 
			i = 0; // arr에는 벌써 .,:이 다 찍혀 있어서 하나씩(날짜, 시각) 
			fprintf(write2, "%c%c%c%c%c%c%c%c %c%c%c%c %d %d %s %s",arr[i].date[0],arr[i].date[1],arr[i].date[2],arr[i].date[3],arr[i].date[5],arr[i].date[6],arr[i].date[8],arr[i].date[9],arr[i].clock[0],arr[i].clock[1],arr[i].clock[3],arr[i].clock[4],arr[i].important_level,arr[i].group,arr[i].title,arr[i].content);
			for(i=1;i<n;i++) {
				fprintf(write2, "\n%c%c%c%c%c%c%c%c %c%c%c%c %d %d %s %s",arr[i].date[0],arr[i].date[1],arr[i].date[2],arr[i].date[3],arr[i].date[5],arr[i].date[6],arr[i].date[8],arr[i].date[9],arr[i].clock[0],arr[i].clock[1],arr[i].clock[3],arr[i].clock[4],arr[i].important_level,arr[i].group,arr[i].title,arr[i].content);
			}
			fclose(write2); // 파일 다 쓰면 닫자! 
		
		free(group1);
		free(group2);
		free(group3);
		free(group4);
		free(group0);
	
		Plan * group0 = (Plan *) malloc(sizeof(Plan) * num);  group0_n = 0; // 다 닫고 새롭게 다시 쓰는 거야! 
		Plan * group1 = (Plan *) malloc(sizeof(Plan) * num);  group1_n = 0;
		Plan * group2 = (Plan *) malloc(sizeof(Plan) * num); group2_n = 0;
		Plan * group3 = (Plan *) malloc(sizeof(Plan) * num); group3_n = 0;
		Plan * group4 = (Plan *) malloc(sizeof(Plan) * num); group4_n = 0;
		for(i=0;i<n;i++){
	
			switch(arr[i].group){
				case 0:
					group0[i].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group0[i].clock = (char *) malloc(sizeof(char) * 10);
					group0[i].title = (char *) malloc(sizeof(char) * 300);
					group0[i].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group0[i].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group0[i].clock, arr[i].clock);
					strcpy(group0[i].title, arr[i].title);
					strcpy(group0[i].content, arr[i].content);
					group0[i].important_level = arr[i].important_level; // 모든 값을 복사한다
					group0[i].group = arr[i].group;
					group0_n++; // 그룹의 일정 개수에 1을 더한다. 
					break;		
			
				case 1:
					group1[group1_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group1[group1_n].clock = (char *) malloc(sizeof(char) * 10);
					group1[group1_n].title = (char *) malloc(sizeof(char) * 300);
					group1[group1_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group1[group1_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group1[group1_n].clock, arr[i].clock);
					strcpy(group1[group1_n].title, arr[i].title);
					strcpy(group1[group1_n].content, arr[i].content);
					group1[group1_n].important_level = arr[i].important_level; // 모든 값을 복사한다
					group1[group1_n].group = arr[i].group;
					group1_n++; // 그룹의 일정 개수에 1을 더한다.
					break;
					
				case 2:
					group2[group2_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group2[group2_n].clock = (char *) malloc(sizeof(char) * 10);
					group2[group2_n].title = (char *) malloc(sizeof(char) * 300);
					group2[group2_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group2[group2_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group2[group2_n].clock, arr[i].clock);
					strcpy(group2[group2_n].title, arr[i].title);
					strcpy(group2[group2_n].content, arr[i].content);
					group2[group2_n].important_level = arr[i].important_level; // 모든 값을 복사한다 
					group2[group2_n].group = arr[i].group;
					group2_n++; // 그룹의 일정 개수에 1을 더한다.
					break;	
				
				case 3:
					group3[group3_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group3[group3_n].clock = (char *) malloc(sizeof(char) * 10);
					group3[group3_n].title = (char *) malloc(sizeof(char) * 300);
					group3[group3_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group3[group3_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group3[group3_n].clock, arr[i].clock);
					strcpy(group3[group3_n].title, arr[i].title);
					strcpy(group3[group3_n].content, arr[i].content);
					group3[group3_n].important_level = arr[i].important_level; // 모든 값을 복사한다
					group3[group3_n].group = arr[i].group;
					group3_n++; // 그룹의 일정 개수에 1을 더한다. 
					break;	
				
				case 4:
					group4[group4_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group4[group4_n].clock = (char *) malloc(sizeof(char) * 10);
					group4[group4_n].title = (char *) malloc(sizeof(char) * 300);
					group4[group4_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group4[group4_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group4[group4_n].clock, arr[i].clock);
					strcpy(group4[group4_n].title, arr[i].title);
					strcpy(group4[group4_n].content, arr[i].content);
					group4[group4_n].important_level = arr[i].important_level; // 모든 값을 복사한다
					group4[group4_n].group = arr[i].group;
					group4_n++; // 그룹의 일정 개수에 1을 더한다. 
					break;	
			}
		
	}
			system("cls");
			
			printf("위치 |    날짜     |  시간 | 중요도|  그룹명 |     제목 &  내용 \n");
			for(i=0;i<n;i++){
				if( location_cursor-1 == i ) SetColor(red,blue + color_bright);
				
				switch(arr[i].group){
					case 0:
						printf("     | %s | %s | %d번째 | 공부(0) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;
					 
					case 1:
						printf("     | %s | %s | %d번째 | 상담(1) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break; 
					
					case 2:
						printf("     | %s | %s | %d번쨰 | 약속(2) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 3:
						printf("     | %s | %s | %d번쨰 | 휴식(3) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 4:
						printf("     | %s | %s | %d번째 | 여행(4) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;	 
				}
				SetColor(white,black);
			}
			 
		}
		
		if(input == -3){
			int now_delete = location_cursor-1;
			if( n == location_cursor ) location_cursor--;
			for(i=now_delete + 1;i<n;i++){
				strcpy(arr[i-1].date,arr[i].date);
				strcpy(arr[i-1].clock,arr[i].clock);
				arr[i-1].important_level = arr[i].important_level;
				arr[i-1].group = arr[i].group;
				strcpy(arr[i-1].title,arr[i].title);
				strcpy(arr[i-1].content,arr[i].content);
			}
			
				FILE * write2 = fopen("input.txt", "w"); // write2 선언  (파일 읽는 위치 초기화를 위해) 
			i = 0; // arr에는 벌써 .,:이 다 찍혀 있어서 하나씩(날짜, 시각) 
			fprintf(write2, "%c%c%c%c%c%c%c%c %c%c%c%c %d %d %s %s",arr[i].date[0],arr[i].date[1],arr[i].date[2],arr[i].date[3],arr[i].date[5],arr[i].date[6],arr[i].date[8],arr[i].date[9],arr[i].clock[0],arr[i].clock[1],arr[i].clock[3],arr[i].clock[4],arr[i].important_level,arr[i].group,arr[i].title,arr[i].content);
			for(i=1;i<n;i++) {
				fprintf(write2, "\n%c%c%c%c%c%c%c%c %c%c%c%c %d %d %s %s",arr[i].date[0],arr[i].date[1],arr[i].date[2],arr[i].date[3],arr[i].date[5],arr[i].date[6],arr[i].date[8],arr[i].date[9],arr[i].clock[0],arr[i].clock[1],arr[i].clock[3],arr[i].clock[4],arr[i].important_level,arr[i].group,arr[i].title,arr[i].content);
			}
			fclose(write2); // 파일 다 쓰면 닫자! 
		
		free(group1);
		free(group2);
		free(group3);
		free(group4);
		free(group0);
	
		Plan * group0 = (Plan *) malloc(sizeof(Plan) * num);  group0_n = 0; // 다 닫고 새롭게 다시 쓰는 거야! 
		Plan * group1 = (Plan *) malloc(sizeof(Plan) * num);  group1_n = 0;
		Plan * group2 = (Plan *) malloc(sizeof(Plan) * num); group2_n = 0;
		Plan * group3 = (Plan *) malloc(sizeof(Plan) * num); group3_n = 0;
		Plan * group4 = (Plan *) malloc(sizeof(Plan) * num); group4_n = 0;
		for(i=0;i<n;i++){
			if( location_cursor-1 == i ) SetColor(red,blue + color_bright);
			switch(arr[i].group){
				case 0:
					group0[i].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group0[i].clock = (char *) malloc(sizeof(char) * 10);
					group0[i].title = (char *) malloc(sizeof(char) * 300);
					group0[i].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group0[i].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group0[i].clock, arr[i].clock);
					strcpy(group0[i].title, arr[i].title);
					strcpy(group0[i].content, arr[i].content);
					group0[i].important_level = arr[i].important_level; // 모든 값을 복사한다
					group0[i].group = arr[i].group;
					group0_n++; // 그룹의 일정 개수에 1을 더한다. 
					break;		
			
				case 1:
					group1[group1_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group1[group1_n].clock = (char *) malloc(sizeof(char) * 10);
					group1[group1_n].title = (char *) malloc(sizeof(char) * 300);
					group1[group1_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group1[group1_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group1[group1_n].clock, arr[i].clock);
					strcpy(group1[group1_n].title, arr[i].title);
					strcpy(group1[group1_n].content, arr[i].content);
					group1[group1_n].important_level = arr[i].important_level; // 모든 값을 복사한다
					group1[group1_n].group = arr[i].group;
					group1_n++; // 그룹의 일정 개수에 1을 더한다.
					break;
					
				case 2:
					group2[group2_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group2[group2_n].clock = (char *) malloc(sizeof(char) * 10);
					group2[group2_n].title = (char *) malloc(sizeof(char) * 300);
					group2[group2_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group2[group2_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group2[group2_n].clock, arr[i].clock);
					strcpy(group2[group2_n].title, arr[i].title);
					strcpy(group2[group2_n].content, arr[i].content);
					group2[group2_n].important_level = arr[i].important_level; // 모든 값을 복사한다 
					group2[group2_n].group = arr[i].group;
					group2_n++; // 그룹의 일정 개수에 1을 더한다.
					break;	
				
				case 3:
					group3[group3_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group3[group3_n].clock = (char *) malloc(sizeof(char) * 10);
					group3[group3_n].title = (char *) malloc(sizeof(char) * 300);
					group3[group3_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group3[group3_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group3[group3_n].clock, arr[i].clock);
					strcpy(group3[group3_n].title, arr[i].title);
					strcpy(group3[group3_n].content, arr[i].content);
					group3[group3_n].important_level = arr[i].important_level; // 모든 값을 복사한다
					group3[group3_n].group = arr[i].group;
					group3_n++; // 그룹의 일정 개수에 1을 더한다. 
					break;	
				
				case 4:
					group4[group4_n].date = (char *) malloc(sizeof(char) * 13); // 각각 배열에 메모리 할당 
					group4[group4_n].clock = (char *) malloc(sizeof(char) * 10);
					group4[group4_n].title = (char *) malloc(sizeof(char) * 300);
					group4[group4_n].content = (char *) malloc(sizeof(char) * 300);
					strcpy(group4[group4_n].date, arr[i].date); // 모든 문자열을 복사한다
					strcpy(group4[group4_n].clock, arr[i].clock);
					strcpy(group4[group4_n].title, arr[i].title);
					strcpy(group4[group4_n].content, arr[i].content);
					group4[group4_n].important_level = arr[i].important_level; // 모든 값을 복사한다
					group4[group4_n].group = arr[i].group;
					group4_n++; // 그룹의 일정 개수에 1을 더한다. 
					break;	
			}
			SetColor(white,black);
	}
			system("cls");
			n--;
			printf("위치 |    날짜     |  시간 | 중요도|  그룹명 |     제목 &  내용 \n");
			for(i=0;i<n;i++){
				if( location_cursor-1 == i ) SetColor(red,blue + color_bright);
				switch(arr[i].group){
					case 0:
						printf("     | %s | %s | %d번째 | 공부(0) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;
					 
					case 1:
						printf("     | %s | %s | %d번째 | 상담(1) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break; 
					
					case 2:
						printf("     | %s | %s | %d번쨰 | 약속(2) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 3:
						printf("     | %s | %s | %d번쨰 | 휴식(3) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 	
						break;
					
					case 4:
						printf("     | %s | %s | %d번째 | 여행(4) | %s | %s |\n",arr[i].date,arr[i].clock,arr[i].important_level,arr[i].title,arr[i].content); // 모두 출력 
						break;	 
				}
				SetColor(white,black);
			}
		}
		else if(input == -10){
			put_cursor(-10);
			printf("사용 가능 키는 | '스페이스' | '위쪽 화살표 키' | '아래쪽 화살표 키' | 'e','i','d' 키 |입니다." );
			Sleep(1500);
			put_cursor(-10);
			printf("                                                                                                    ");
		}
		
	}
      for(i=0;i<n;i++){ //메모리 해제를 진행한다. 
		free(arr[i].date);
		free(arr[i].clock);
		free(arr[i].content);
		free(arr[i].title);
	}
	
	free(arr); //메모리 해제
	free(group1);
	free(group2);
	free(group3);
	free(group4);
	free(group0);
	return 0;
}

int keyboard_input(){ // 키보드 처리 받기 
	int key = getch(); // 화살표의 1바이트 받기 - 방향키는 이곳에 224가 들어간다. 
    if(key == 224) // 화살표는 2바이트 확장 코드이다.  
	{
    	key = getch(); // 화살표의 그다음 1 바이트 받기 - 여것으로 방향이 결정된다. 

    	switch(key)
   		{
        	case 72: // 위쪽 화살표 키를 눌렀을 때 
            	return 1; // 1 반환 
            	break;
        	case 80: // 아래쪽 화살표 키를 눌렀을 때 
            	return -1; // -1 반환 
            	break;
        	default: // 두 키 모두 해당되지 않을 경우 
        		return -10;  // -10 (제작자가 임의로 정한 이 함수의 '없음 값') 반환 
            	break;
    	}
	}
	else if (key == 32) return 0; // 스페이스 키를 눌렀을 떄
	else if (key == 'i') return 2; 
	else if (key == 'q') return -2; 
	else if (key == 'e') return 3;
	else if (key == 'd') return -3;
	else return -10; // -10 (제작자가 임의로 정한 이 함수의 '없음 값') 반환 
}

void put_cursor(int x){
	if(x == 1){ // 입력 
		SetColor(red,blue + color_bright); 
		gotoxy(2,location_cursor); // 위치 이동 
		printf("⇒");// 화살표 입력 
		SetColor(white,black);
	}
	else if(x == -1){ // 제거 
		SetColor(white,black);
		gotoxy(2,location_cursor); // 위치 이동 
		printf("  "); // 화살표 제거
	}
	
	else if (x == -10){
		gotoxy(0,n+1);
	}
	

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

/* -끝- */ 

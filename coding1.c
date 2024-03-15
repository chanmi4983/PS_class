// Enter your student ID and Fullname
//22200240 나찬미

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct st_class{
	int code;		// class code
	char name[30]; 	// class name
	int unit;		// credites
	int grading;	// grading (1:A+~F, 2:P/F)
};

char kname[2][10] = {"A+~F", "P/F"}; // String for grading

// Functions provided
int loadData(struct st_class* c[]); // Load all class list from data file.
void printAllClasses(struct st_class* c[], int csize); // Print all class list
void findClasses(char* name, struct st_class* c[], int csize); // Search a class by name from the list
void saveAllClasses(struct st_class* c[], int csize); // Save all class list

// Functions for modifying
int addNewClass(struct st_class* c[], int csize); // Add a class into the list
void editClass(struct st_class* c[], int csize); // Modify a class in the list

// Functions for making
int applyMyClasses(int my[], int msize, struct st_class* c[], int csize); // Apply a class
void printMyClasses(int my[], int msize, struct st_class* c[], int csize); // Print my classes
void saveMyClass(int my[], int msize, struct st_class* c[], int csize); // Save my classes


int main(void) {
	int no;	// menu number 
	struct st_class* classes[50]; // Class list (max. 50 classes)

	int myclass[10]; // My classes (max. 10 classes of code)
	int mycount = 0; // Amount of my classes

	srand(time(0));
	int count = loadData(classes);
	printf("> Load %d classes.\n", count);

	while(1){
		printf("\n> Menu 1.List 2.Add 3.Modify 4.Search 5.Apply 6.My classes 7.Save 0.Quit\n");
		printf(">> Menu? > ");
		scanf("%d", &no);

		if(no == 1){ 
			printf("> 1.Class list (%d classes)\n", count);
			printAllClasses(classes, count);
		}
		else if(no == 2){ 
			printf("> 2.Add a Class\n");
			count = addNewClass(classes, count);
		}
		else if(no == 3){ 
			printf("> 3.Modify a Class\n");
			editClass(classes, count);
		}
		else if(no == 4){
			printf("> 4.Search a Class\n");
			printf(">> Enter class name > ");
			char name[30];
			scanf("%s", name);
			findClasses(name, classes, count);
		}
		else if(no == 5){
			printf("> 5.Apply a class\n");
			mycount = applyMyClasses(myclass, mycount, classes, count);
			printf("%d classes has been applied.\n", mycount);
		}
		else if(no == 6){
			printf("> 6.My classes\n");
			printMyClasses(myclass, mycount, classes, count);
		}
		else if(no == 7){
			printf("> 7.Save\n");
			saveMyClass(myclass, mycount, classes, count);
			printf("\n> All my classes ware saved to my_classes.txt.\n");
			saveAllClasses(classes, count);
			printf("\n> All of class list ware saved to classes.txt.\n");
		}
		else break;
	}
	return 0;
}

int loadData(struct st_class* c[]){
	int count=0;
	FILE* file;

	file=fopen("classes.txt", "r");
	while(!feof(file)){
		c[count] = (struct st_class*)malloc(sizeof(struct st_class));
		int r = fscanf(file, "%d %s %d %d", &(c[count]->code),c[count]->name, &(c[count]->unit), &(c[count]->grading));
		if(r < 4) break;
		count++;
	}
	fclose(file);
	return count;
}

void printAllClasses(struct st_class* c[], int csize){
	for(int i=0; i<csize; i++){
		printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
	}
}

void saveAllClasses(struct st_class* c[], int csize){
	FILE* file;
	file = fopen("classes.txt", "w");
	for(int i=0; i<csize; i++){
		fprintf(file, "%d %s %d %d\n",c[i]->code, c[i]->name, c[i]->unit, c[i]->grading);
	}
	fclose(file);	
}

void findClasses(char* name, struct st_class* c[], int csize){
	int count = 0;

	printf("Searching (keyword : %s)\n", name);
	for(int i=0; i<csize; i++){
		if(strstr(c[i]->name, name)){
			printf("[%d] %s [credit %d - %s]\n",c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading-1]);
			count++;
		}
	}
	printf("%d classes found.\n", count);
}

// You must complete these functions.
int addNewClass(struct st_class* c[], int csize){
// Caution : Don't allow the duplicate class code.
// You must complete this function.

/*comment
메모리가 할당된 p는 새롭게 할당된 것이다.

교과목 목록에 새로운 과목 추가
과목 추가시에 이미 등록된 과목코드가 추가되지않도록 해야한다.
구조체 	c를 받을 때 있는지 조사
중복이 있는지 체크하기
첫번째로 for문으로 돌리고 그 안에서 중복되는 코드가 있는지 if문으로 체크 해야한다. 
있다면 동적으로 할당된 메모리를 해제한다
할당된 메모리가 해제될 경우 > 그 데이터가 손실되므로 업데이트가 되지않고
기존의 과목개수를 반환해야한다
*/

	struct st_class* p = (struct st_class*)malloc(sizeof(struct st_class));

	printf(">> code number > ");
	scanf("%d", &(p->code));

	//중복인지 체크
	for(int i = 0; i < csize; i++){
		if(p->code == c[i]->code){
			printf(">> Code duplicated! Retry.\n");
			free(p); //데이터가 있을 경우 메모리를 해제
			return csize; //추가되지않은 현재 과목개수 반환
		}
	}

	printf(">> class name > ");
	scanf("%s", p->name);
	printf(">> credits > ");
	scanf("%d", &(p->unit));
	printf(">> grading (1: A+~F, 2: P/F) > ");
	scanf("%d", &(p->grading));

	c[csize] = p;
	return csize+1;
}

void editClass(struct st_class* c[], int csize){
	struct st_class* p = NULL;
	int code;
	printf(">> Enter a code of class > ");
	scanf("%d", &code);

	
	// You must complete this section.
	/*comment

	요구사항: 과목코드를 입력받은 후 수정작업을 진행하기 위해 과목구조체 포인터의 값을 할당. 존재하지 않는 경우도 처리
	과목코드 입력 

	과목코드 일치하는 과목을 찾아야 한다. 
	for문으로 일치하는 코드를 찾고 그것을 가리키는 포인터를 설정한다. 

	만약에 찾지 못한 경우도 if문으로 함수를 그냥 종료 시켜야 한다. 

	
	*/

	for(int i = 0; i < csize; i++){
		if(c[i]->code == code){ //일치하는 것이 있다면 
		p = c[i]; //포인터 설정한다
		break;
		}
	}

	// 과목을 찾지 못한 경우
    if (p == NULL) {
        printf("> No such class.\n");
        return;
    }


	
	printf("> Current: [%d] %s [credits %d - %s]\n",p->code, p->name, p->unit, kname[p->grading-1]);
	printf("> Enter new class name > ");
	scanf("%s", p->name);
	printf("> Enter new credits > ");
	scanf("%d", &(p->unit));
	printf("> Enter new grading(1:Grade, 2: P/F) > ");
	scanf("%d", &(p->grading));

	printf("> Modified.\n");

}


// You must make all these functions.

int applyMyClasses(int my[], int msize, struct st_class* c[], int csize){
/*
	내 수강과목 등록하기 
	1. 코드 입력 > 코드 프린트 
	2. 더 추가할지 물어봐야 한다. 

	while문으로 멈추기 전까지 받아야 한다. 
	더 추가 할지 말지의 여부를 if문으로 둬서 break; 해줘야 한다. 

	2. 입력된 코드가 실제로 있는 것인지 체크해야 한다. 
	인덱스를 설정해서 그 값을 변경하여 있다면 1로 표시하고 아닌경우는 0이다. 
	있다면 그 과목에 해당하는 정보를 출력해줘여 한다. 
	없는 경우 >> No such code of class. 이렇게 프린트 

	3. 계속 내 수강 목록을 받을 건지 물아봐야 하므로 그것을 1, 2로 입력받아서 2인경우 break한다

*/
    int code;
    int count = 0; // 추가된 수강 과목 개수

    while (1) {
        printf(">> Enter a class code > ");
        scanf("%d", &code);

        // 입력된 코드가 실제 과목 목로에 있는지 체크한다.
        int idx = 0;

        for (int i = 0; i < csize; ++i) {
            if (c[i]->code == code) {
                idx = 1; // 입력된 코드가 있다고 바꿔주고 
				// 그 과목에 관한 정보를 프린트 해줘야한다.
                printf(">> [%d] %s [credit %d - %s]\n", c[i]->code, c[i]->name, c[i]->unit, kname[c[i]->grading - 1]);

                // 내 수강 과목 배열에 추가
                my[count++] = code;
                break; // 코드가 유효한 경우에만 반복문을 종료
            }
        }

        // 입력한 코드가 없다면
        if (!idx) {
            printf(">> No such code of class.\n");
        }

        // 더 추가할지 물어보고 추가할지 결정
        printf(">> Add more? (1:Yes 2:No) > ");
        int choice;
        scanf("%d", &choice);

        if (choice != 1) {
            break; // 추가하지 않을 경우 반복문 종료
        }
    }

    return count; // 최종 등록된 내 수강 과목의 개수 반환
	
	return 0;
}

void printMyClasses(int my[], int msize, struct st_class* c[], int csize){
/*
	요구사항 : 
	수강신청한 과목의 모든 정보를 출력한다
	전체 학점을 계산해야한다 

	for문으로 내 수강과목가 일치하는 것이 있는지 일치하면 
	정보를 출려개야한다.

*/

    int credits = 0; // 전체 학점 

    for (int i = 0; i < msize; ++i) {
        int code = my[i];

        // 해당 과목 코드와 일치하는 과목 정보를 찾아 출력
        for (int j = 0; j < csize; ++j) {
            if (c[j]->code == code) {
                printf("%d. [%d] %s [credit %d - %s]\n", i + 1, c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
                credits += c[j]->unit; // 학점을 합산
                break; // 과목을 찾았으므로 반복 종료
            }
        }
    }
    printf("All : %d credits\n", credits);

}

void saveMyClass(int my[], int msize, struct st_class* c[], int csize){

/*
	요구사항: 내 수강과목 정보를 파일로 저장
	1. 파일쓰기모드 
	2. 파일에 수강과목정보를 저장하기 위해서 for문으로 해당 과목코드일치하는 정보를 if문으로 찾는다
	그리고 나서 파일에 저장한다 
	3. 수강학점을 계산 
	for문으로 코드에 내 수강을 불러온다음 코드가 일치한 경우인 if문으로 쓰면서 저장한다
	4. 파일에 fprintf로 저장한다
	5.파일 닫기
*/
	    FILE* file = fopen("my_classes.txt", "w");

    // 파일에 나의 수강 과목 정보를 저장
    for (int i = 0; i < msize; ++i) {
        int code = my[i];

        // 해당 과목 코드와 일치하는 교과목 정보를 찾음
        for (int j = 0; j < csize; ++j) {
            if (c[j]->code == code) {
                // 과목 정보를 파일에 저장
                fprintf(file, "[%d] %s [credit %d - %s]\n", c[j]->code, c[j]->name, c[j]->unit, kname[c[j]->grading - 1]);
                break; // 과목을 찾았으므로 반복 종료
            }
        }
    }

    // 총 수강학점을 계산
    int totalCredits = 0;
    for (int i = 0; i < msize; ++i) {
        int code = my[i];
        for (int j = 0; j < csize; ++j) {
            if (c[j]->code == code) {
                totalCredits += c[j]->unit;
                break;
            }
        }
    }

    // 파일에 총 수강학점 정보 저장
    fprintf(file, "Total credits: %d\n", totalCredits);

    fclose(file);

}
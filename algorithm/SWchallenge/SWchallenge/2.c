#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_valid_roomnumber(char roomname, int roomnumber) {
	int answer = 0;
	switch (roomname) {
	case 'p':
		if (roomnumber == 1)
			answer = 1;
		break;
	case 's':
		if (roomnumber >=1 &&roomnumber<=3)
			answer = 1;
		break;
	case 'd':
		if (roomnumber >= 1 && roomnumber <= 6)
			answer = 1;
		break;
	default:
		break;
	}
	return answer;
}

void reserveRoom(char **roommap, char roomname, int roomnumber, char r) {
	if (roomname == 'p') 
		roomnumber -= 1;
	else if (roomname == 'd')
		roomnumber += 3;

	char name[21];
	gets(name);
	
	int i;
	if (r == 'y') {
		for (i = 0; i < 10; i++) {
			if (strcmp(roommap[i], name) == 0) {
				printf("please input another name\n");
				return;
			}
		}
	}

	for (i = 0; i < 10; i++) {
		if (strcmp(roommap[i], name) == 0) {
			*(roommap + i) = "0";
		}
	}

	strcpy(*(roommap+roomnumber),name);
}

void numberSelect(char** roommap, char roomname, char r) {
	int roomnumber;
	scanf("%d", &roomnumber);
	int valid = is_valid_roomnumber(roomname, roomnumber);
	if (valid) {
		if (strcmp(roommap[roomnumber - 1], "0") != 0) {
			printf("please select another room\n");
		}
		else{
		reserveRoom(roommap, roomname, roomnumber, r);
		}
	}
	else {
		printf("please input correctly\n");
	}
}

void roomSelect(char** roommap, char r) {
	char roomname;
	scanf("%c", &roomname);
	if (roomname == 'p'|| roomname == 's' || roomname =='d') {
		numberSelect(roommap, roomname, r);
	}
	else
		printf("please input correctly\n");
}

void reserveMenu(char **roommap) {
	char r;
	scanf("%c", &r);
	if (r == 'y') {
		roomSelect(roommap, r);
	}
	else if (r == 'c') {
		roomSelect(roommap, r);
	}
	else if (r == 'n')
		exit(0);
	else
		printf("please input correctly\n");
}

int main() {
	char* roommap[10];

	int i;
	for (i = 0; i < 10; i++) {
		roommap[i] = "0";
	}

	while (1)
	{
		reserveMenu(roommap);
		getchar();
		for (i = 0; i < 10; i++)
			printf("%s ", roommap[i]);
		printf("\n");
	}
}
#include <stdio.h>
#include <string.h>
#include <windows.h>

void welcome_msg();
void chose_route();
int get_n_seat();

char routes[2][100] = {"Chashara to Signboard", "Chashara to Gulisthan"};
char destination[50];
int n_seat= 0;

int main() {
	welcome_msg();
	// ask name
	char name[50];
	printf("Enter your name: ");
	gets(name);
	//get route
	chose_route();
	get_n_seat();



}


int get_n_seat() {
	// get num of sets
	printf("How many seats you want to book: ");
	scanf("%d", &n_seat);
}


void chose_route() {
	printf("Available Routes:\n");
	for(int i = 0; i< 2; i++) {

		printf("%d) %s\n", i+1, routes[i]);
	}

	int i;
	while(1) {
		printf("Chose your destination:\n");
		scanf("%d", &i);
		if(i == 1) {
			strcpy(destination, routes[i-1]);
			break;
		} else if (i == 2) {
			strcpy(destination, routes[i-1]);
			break;
		} else {
			printf("Please enter valid choice!\n");
			continue;
		}
	}
}

void welcome_msg() {
	printf("Welcome to the ticket booking system\n");
}

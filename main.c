#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <windows.h>

#define TOTAL_SEATS 20
#define TOTAL_ROUTES 3

void welcome_msg();		 // welcome message
void chose_route();		 // chose route
int get_n_seat();		 // get number of seats
void book_seat();		 // book seats
void available_routes(); // available routes
void clr();				 // clear screen

char name[50];
char routes[TOTAL_ROUTES][100] = {"Chashara to Signboard", "Chashara to Gulisthan", "Earth to Mars        "};
int cost[TOTAL_ROUTES] = {40, 60, 11};
char destination[50];
int check_seat[TOTAL_SEATS];
int available_seats = 20;
int booked_seats = 0;
int n_seat;

int main()
{

	for (int i = 0; i < TOTAL_SEATS; i++)
	{
		check_seat[i] = 1; // 1 means available
	}

	welcome_msg();

	// ask name
	printf("\tEnter your name: \n");
	printf("\t>> ");
	fgets(name, sizeof(name), stdin);
	clr();
	available_routes(); // show available routes
	chose_route();		// get destination
	get_n_seat();		// get number of seats
	book_seat();		// book seats

	// print booked seats
	printf("Booked seats:\n");
	for (int i = 0; i < TOTAL_SEATS; i++)
	{
		if (check_seat[i] == 0)
		{
			printf("%d ", i + 1);
		}
	}
	printf("\n");

	return 0;
}
void clr()
{
	system("clear");
}

void book_seat()
{
	int seat_no;
	while (n_seat > 0)
	{

		// visualize seats
		printf("\n\tAvailable seats:\t\n\n");
		printf("\t\t============================\n");
		for (int i = 0; i < TOTAL_SEATS; i += 4)
		{
			printf("\t\t------------\t------------\n");
			if (check_seat[i] == 1)
			{
				printf("\t\t (%d)  ", i + 1);
			}
			else
			{
				printf("\t\t (X)  ", i + 1);
			}

			if (check_seat[i + 1] == 1)
			{
				printf("(%d) \t ", i + 2);
			}
			else
			{
				printf("(X) \t ", i + 2);
			}

			if (check_seat[i + 2] == 1)
			{
				printf("(%d)  ", i + 3);
			}
			else
			{
				printf("(X)  ", i + 3);
			}
			if (check_seat[i + 3] == 1)
			{
				printf("(%d) \n", i + 4);
			}
			else
			{
				printf("(X) \n", i + 4);
			}

			printf("\t\t------------\t------------\n");
		}
		printf("\t\t============================\n\n");

		printf("\tEnter a seat number to book:\n");
		printf("\t>> ");

		scanf("%d", &seat_no);
		if (seat_no > TOTAL_SEATS || seat_no < 0)
		{
			printf("Please enter valid seat number!\n");
			continue;
		}

		// check if seat is booked or not
		if (check_seat[seat_no - 1] == 0)
		{
			printf("This seat is already booked,\nPlease choose another seat!\n");
			continue;
		}
		else
		{
			check_seat[seat_no - 1] = 0;
			booked_seats++;
			available_seats--;
			n_seat--;
		}
	}
}

int get_n_seat()
{
	while (1)
	{
		clr();
		printf("\tHow many seat you want to book:\n");
		printf("\t>> ");
		scanf("%d", &n_seat);
		if (n_seat > available_seats)
		{
			printf("Sorry! Only %d seats are available!\n", available_seats);
			continue;
		}
		else
		{
			break;
		}
	}
}

void available_routes()
{
	printf("\tAvailable Routes: \n");
	printf("\t---------------------------------------\n");
	printf("\t| SN |        Destinations     | Cost |\n");
	printf("\t---------------------------------------\n");

	for (int i = 0; i < TOTAL_ROUTES; i++)
	{

		printf("\t| %d | %s    | %dtk |\n", i + 1, routes[i], cost[i]);
		printf("\t---------------------------------------\n");
	}
}

void chose_route()
{

	int i;
	while (1)
	{

		printf("\n\tChose your destination: \n");
		printf("\t>> ");
		scanf("%d", &i);
		if (i > 0 && i <= TOTAL_ROUTES)
		{
			strcpy(destination, routes[i - 1]);
			break;
		}
		else
		{

			printf("\n\tInvalid choice!\n");
			printf("\tPlease chose from the table avobe.\n");
			// available_routes();
			continue;
		}
	}
}

void welcome_msg()
{
	clr();
	printf("\t==========================================\n");
	printf("\t=====~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~=====\n");
	printf("\t|    Welcome to Chashara Bus Terminal    |\n");
	printf("\t=====~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~=====\n");
	printf("\t==========================================\n\n");

	printf("\tPress 'Enter' to continue...\n");
	getchar();
	fflush(stdin);
	clr();
}

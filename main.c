#include <stdio.h>
#include <string.h>
// #include <windows.h>

#define TOTAL_SEATS 20

void welcome_msg(); // welcome message
void chose_route(); // chose route
int get_n_seat();	// get number of seats
void book_seat();	// book seats

char routes[2][100] = {"Chashara to Signboard", "Chashara to Gulisthan"};
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
	char name[50];
	printf("Enter your name: ");
	fgets(name, sizeof(name), stdin);
	// get route
	chose_route();
	get_n_seat();
	book_seat();

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

void book_seat()
{

	// book seats

	int seat_no;
	while (n_seat > 0)
	{
		// visualize seats
		printf("Available seats:\n");
		printf("...............\n");
		for (int j = 0; j < TOTAL_SEATS; j++)
		{
			if (check_seat[j] == 1)
			{
				printf("%d ", j + 1);
			}
			else
			{
				printf("X ");
			}
		}
		printf("\n...............\n\n");

		printf("Enter a seat number to book: ");
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
		printf("How many seats you want to book: ");
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

void chose_route()
{
	printf("Available Routes:\n");
	for (int i = 0; i < 2; i++)
	{

		printf("%d) %s\n", i + 1, routes[i]);
	}

	int i;
	while (1)
	{
		printf("Chose your destination:\n");
		scanf("%d", &i);
		if (i == 1)
		{
			strcpy(destination, routes[i - 1]);
			break;
		}
		else if (i == 2)
		{
			strcpy(destination, routes[i - 1]);
			break;
		}
		else
		{
			printf("Please enter valid choice!\n");
			continue;
		}
	}
}

void welcome_msg()
{
	printf("Welcome to the ticket booking system\n");
}

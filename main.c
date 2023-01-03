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
int init();				 // necessary initializations
void admin_panel();		 // admin panel
char *gen_token(char name[50], char destination[100], int n_seats);
void view_booked_seats(int c_count); // view booked seats

struct data
{
	char name[50];
	char destination[100];
	int cost_per_seat;
	int n_seats;
	int booked_seats[TOTAL_SEATS];
	char token[7];
};

struct data c_data[TOTAL_SEATS]; // to store customer data
// char token[7];
// char name[50];
char routes[TOTAL_ROUTES][100] = {"Chashara to Signboard", "Chashara to Gulisthan", "Earth to Mars        "};
int cost[TOTAL_ROUTES] = {40, 60, 11};
// char destination[50];
int check_seat[TOTAL_SEATS];
int available_seats = 20;
int booked_seats = 0;
int n_seat;
int c_count = 0;

int main()
{
	int choice;
	init();
	welcome_msg();
	while (1)
	{
		printf("\tEnter your choice:\n");
		printf("\t1. Book a seat\n");
		printf("\t2. Admin panel\n");
		printf("\t3. Exit\n");
		printf("\n\t>> ");
		scanf("%d", &choice);
		getchar();
		fflush(stdin);
		clr();
		if (choice == 1)
		{

			book_seat(); // book seats
		}
		else if (choice == 2)
		{
			admin_panel();
		}
		else if (choice == 3)
		{
			printf("\tBe aware: By exiting you will lose all your data!\n\n");
			printf("\t-> Press 'ctrl + c' anytime to terminate the program (lose runtime data).\n");
			printf("\t-> Press 'enter' to continue using the program (keep runtime data).\n");
			printf("\n\t");
			getchar();
			fflush(stdin);
			clr();
		}
		else
		{
			printf("\tInvalid choice!\n\n");
			printf("\tPress 'enter' to continue!\n");
			printf("\t");
			getchar();
			fflush(stdin);
			clr();
			continue;
		}
	}

	return 0;
}

char *gen_token(char name[50], char destination[100], int n_seats)
{
	char token[7] = "";
	char c_count_str[3];
	sprintf(c_count_str, "%02d", c_count + 1);
	strcat(token, c_count_str);
	strncat(token, name, 1);
	strncat(token, destination, 1);
	char n_seats_str[3];
	sprintf(n_seats_str, "%02d", n_seats);
	strcat(token, n_seats_str);
	return strcpy(c_data[c_count].token, token);
}
int init()
{
	{
		for (int i = 0; i < TOTAL_SEATS; i++)
		{
			check_seat[i] = 1; // 1 means available
		}
	}
}

void admin_panel()
{
	int choice;
	while (1)
	{
		printf("\t1. View all booked seats\n");
		// printf("\t2. Delete a booked seat\n");
		printf("\t3. Back\n");
		printf("\n\t>> ");
		scanf("%d", &choice);
		getchar();
		fflush(stdin);

		if (choice == 1)
		{
			clr();
			view_booked_seats(c_count);
			// printf("\n\tPress 'enter' to continue!\n");
			// printf("\t>> ");
			// getchar();
			// fflush(stdin);
			// clr();
		}
		else if (choice == 2)
		{
		}
		else if (choice == 3)
		{
			clr();
			break;
		}
		else
		{
			printf("\tInvalid choice!\n\n");
			printf("\tPress 'enter' to continue!\n");
			printf("\t");
			getchar();
			fflush(stdin);
			clr();
		}
	}
}

void view_booked_seats(int c_count)
{
	if (c_count == 0)
	{
		printf("\tNo seats booked yet!\n\n");
		printf("\tPress 'enter' to continue!\n");
		printf("\t");
		getchar();
		fflush(stdin);
		clr();
	}
	else
	{
		printf("\n\t(Serial No. > Token No. > Booked by > Destination > No. of booked seats)\n\n");
		printf("\t------------------------------------------------------------------------\n\n");
		for (int i = 0; i < c_count; i++)
		{
			printf("\t\t%d. > %s > %s > %s > %d\n\n", (i+1), c_data[i].token, c_data[i].name, c_data[i].destination, c_data[i].n_seats);
		}
		printf("\t------------------------------------------------------------------------\n\n");
		printf("\n");
		printf("\tPress 'enter' to continue!\n");
		printf("\t");
		getchar();
		fflush(stdin);
		clr();
	}
}

void clr()
{
	system("clear");
}

void book_seat()
{
	int seat_no;

	printf("\tEnter your name: \n");
	printf("\t>> ");
	fgets(c_data[c_count].name, sizeof(c_data[c_count].name), stdin);
	c_data[c_count].name[strlen(c_data[c_count].name) - 1] = '\0';
	clr();
	chose_route(); // get destination
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
			c_data[c_count].n_seats = n_seat;
			break;
		}
	}

	while (n_seat > 0)
	{
		clr();
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
				printf("\t\t (X)  ");
			}

			if (check_seat[i + 1] == 1)
			{
				printf("(%d) \t ", i + 2);
			}
			else
			{
				printf("(X) \t ");
			}

			if (check_seat[i + 2] == 1)
			{
				printf("(%d)  ", i + 3);
			}
			else
			{
				printf("(X)  ");
			}
			if (check_seat[i + 3] == 1)
			{
				printf("(%d) \n", i + 4);
			}
			else
			{
				printf("(X) \n");
			}

			printf("\t\t------------\t------------\n");
		}
		printf("\t\t============================\n\n");

		printf("\tEnter a seat number to book:\n");
		printf("\t>> ");
		scanf("%d", &seat_no);
		getchar();
		fflush(stdin);
		if (seat_no > TOTAL_SEATS || seat_no < 0)
		{
			printf("\tInvalid seat number!\n\n");
			printf("\tPress 'enter' to continue!\n");
			printf("\t");
			getchar();
			fflush(stdin);
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
			c_data[c_count].booked_seats[c_data[c_count].n_seats - n_seat] = seat_no;
			check_seat[seat_no - 1] = 0;
			booked_seats++;
			available_seats--;
			n_seat--;
		}
	}
	clr();
	// confirmation of booking
	printf("\n");
	printf("\tName: \t%s\n", c_data[c_count].name);
	printf("\tDestination: %s\n", c_data[c_count].destination);
	printf("\tNumber of seats: %d\n", c_data[c_count].n_seats);
	printf("\tSeats for booking: ");
	for (int i = 0; i < c_data[c_count].n_seats; i++)
	{
		printf("%d, ", c_data[c_count].booked_seats[i]);
	}
	printf("\n");
	printf("\tTotal cost: %dtk\n", c_data[c_count].n_seats * c_data[c_count].cost_per_seat);
	printf("\n\tDo you want to confirm booking? (y/n)\n");
	printf("\t>> ");
	char ch;
	while (1)
	{
		fflush(stdin);
		scanf("%c", &ch);
		getchar();
		fflush(stdin);
		clr();

		if (ch == 'y' || ch == 'Y')
		{
			// generate token number
			*gen_token(c_data[c_count].name, c_data[c_count].destination, c_data[c_count].n_seats);
			// clr();
			c_count++;
			printf("\n\tBooking confirmed!\n\n");
			printf("\tYour token number is: %s", c_data[c_count - 1].token);
			printf("\n\t(Please keep this token number safe!)\n\n");

			printf("\tPress 'Enter' to continue...\n");
			printf("\t");
			getchar();
			clr();
			fflush(stdin);
			break;
		}
		else if (ch == 'n' || ch == 'N')
		{
			// cancel booking
			for (int i = 0; i < c_data[c_count].n_seats; i++)
			{
				check_seat[c_data[c_count].booked_seats[i] - 1] = 1;
			}
			clr();
			printf("\tBooking canceled!\n\n");
			printf("\tPress 'Enter' to continue...\n");
			printf("\t");
			getchar();
			fflush(stdin);
			break;
		}
		else
		{
			printf("\n\tInvalid input!\n\n");
			printf("\t(if it is Yes enter 'y' or 'Y' and if it is No enter 'n' or 'N')\n\n");
			printf("\tDo you want to confirm booking? (y/n)\n");
		}
		printf("\t>> ");
	}
}

void chose_route()
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

	int i;
	while (1)
	{

		printf("\n\tChose your destination: \n");
		printf("\t>> ");
		scanf("%d", &i);
		getchar();
		fflush(stdin);
		clr();
		if (i > 0 && i <= TOTAL_ROUTES)
		{
			strcpy(c_data[c_count].destination, routes[i - 1]);
			c_data[c_count].cost_per_seat = cost[i - 1];
			break;
		}
		else
		{

			printf("\n\tInvalid choice!\n");
			printf("\tPlease chose from the table above!\n\n");
			printf("\tPress 'Enter' to continue!\n");
			printf("\t");
			getchar();
			fflush(stdin);
			clr();
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
	printf("\t");
	getchar();
	fflush(stdin);
	clr();
}

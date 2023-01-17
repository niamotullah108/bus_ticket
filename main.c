#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// check OS for platform specific things
#if defined(_WIN32)
#include <windows.h>		// necessary header for windows
#define clr() system("cls") // clear terminal for windows
#else
#define clr() system("clear") // clear terminal for linux
#endif

#define TOTAL_SEATS 20
#define TOTAL_ROUTES 3
#define PASS_LEN 13

int init();													// necessary initializations
void welcome_msg();											// welcome message
void chose_route();											// chose route
void book_seat();											// book seats
void admin_panel();											// admin panel
char gen_token(char *name, char *destination, int n_seats); // generate token
void view_booked_seats(int c_count);						// view booked seats
void delete_by_token(char *token);							// delete booked seat
int check_admin_pass();										// check admin password
void change_admin_pass();									// change password
int search_by_token(char *token);							// search/view booking using token

struct data // to store customer data
{
	char name[50];
	char destination[100];
	int cost_per_seat;
	int n_seats;
	int booked_seats[TOTAL_SEATS];
	char token[7];
};
struct data c_data[TOTAL_SEATS]; // create a array of struct data

char routes[TOTAL_ROUTES][100] = {"Chashara to Signboard", "Chashara to Gulisthan", "Earth to Mars        "};
int cost[TOTAL_ROUTES] = {40, 60, 11};
int check_seat[TOTAL_SEATS];
int available_seats = TOTAL_SEATS;
int booked_seats = 0;
int n_seat;
int c_count = 0;
int c_existence[TOTAL_SEATS];
char admin_pass[PASS_LEN] = "admin";

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
			switch (check_admin_pass())
			{
			case 1:
				admin_panel();
				break;
			}
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
int search_by_token(char *token)
{
	for (int i = 0; i < TOTAL_SEATS; i++) // loop through all struct array
	{
		if (strcmp(token, c_data[i].token) == 0 && c_existence[i] == 1) // check if match with any booked customer
		{
			printf("\tToken No.: %s\n", c_data[i].token);
			printf("\tName: \t%s\n", c_data[i].name);
			printf("\tDestination: %s\n", c_data[i].destination);
			printf("\tNumber of seats: %d\n", c_data[i].n_seats);
			printf("\tBooked seats No.: ");
			for (int j = 0; j < c_data[i].n_seats; j++)
			{
				printf("%d, ", c_data[i].booked_seats[j]);
			}
			printf("\n");
			printf("\tTotal cost: %dtk\n", c_data[i].n_seats * c_data[i].cost_per_seat);
			return 1;
		}
	}
	return 0;
}
void change_admin_pass()
{
	char pass[50] = "";
	printf("\tEnter current password:\n");
	printf("\t>> ");
	fgets(pass, sizeof(pass), stdin);
	pass[strlen(pass) - 1] = '\0'; // remove newline character
	fflush(stdin);
	clr();

	if (strcmp(pass, admin_pass) == 0)
	{
		printf("\n\t(Password matched!)\n\n");
		while (1)
		{
			printf("\tEnter new password [>4,<8]:\n");
			printf("\t>> ");
			fgets(pass, sizeof(pass), stdin);
			pass[strlen(pass) - 1] = '\0'; // remove newline character
			fflush(stdin);
			clr();
			if (strlen(pass) < 4 || strlen(pass) > PASS_LEN - 1)
			{
				printf("\tPassword must have to be between 4 and 12 characters long!\n\n");
				printf("\tPress 'enter' to continue!\n");
				printf("\t");
				getchar();
				fflush(stdin);
				clr();
				continue;
			}
			else
			{
				strcpy(admin_pass, pass); // save new password
				break;
			}
		}
		printf("\tPassword changed successfully!\n\n");
		printf("\tPress 'enter' to continue!\n");
		printf("\t");
		getchar();
		fflush(stdin);
		clr();
	}
	else
	{
		clr();
		printf("\tWrong password!\n\n");
		printf("\tPress 'enter' to continue!\n");
		printf("\t");
		getchar();
		fflush(stdin);
		clr();
	}
}
int check_admin_pass()
{
	char pass[9];
	printf("\tEnter password:\n");
	printf("\t>> ");
	fgets(pass, sizeof(pass), stdin);
	pass[strlen(pass) - 1] = '\0'; // remove newline character
	fflush(stdin);
	clr();

	if (strcmp(pass, admin_pass) == 0)
	{
		return 1;
	}
	else
	{
		printf("\tWrong password!\n\n");
		printf("\tPress 'enter' to continue!\n");
		printf("\t");
		getchar();
		fflush(stdin);
		clr();
		return 0;
	}
}

void delete_by_token(char *token)
{
	int digit;
	digit = ((token[0] - 48) * 10) + (token[1] - 48);
	if (c_existence[digit - 1] == 0)
	{
		clr();
		printf("\tInvalid token!\n\n");
	}
	else if (strcmp(token, c_data[digit - 1].token) == 0)
	{
		c_existence[digit - 1] = 0; // set existence to 0/false
		// delete booked seats
		for (int i = 0; i < c_data[digit - 1].n_seats; i++)
		{
			check_seat[c_data[digit - 1].booked_seats[i] - 1] = 1; // set seat to available
		}
		available_seats += c_data[digit - 1].n_seats; // add available seats
		booked_seats -= c_data[digit - 1].n_seats;	  // remove booked seats
		c_count--;									  // decrease customer count
		c_data[digit - 1].token[0] = '\0';			  // clear token
		clr();
		printf("\tDeleted successfully!\n\n");
	}
	else
	{
		clr();
		printf("\tNo such token exists!\n\n");
	}
}

char gen_token(char *name, char *destination, int n_seats)
{
	char c_count_str[3];
	sprintf(c_count_str, "%02d", c_count + 1);
	strcat(c_data[c_count].token, c_count_str);
	strncat(c_data[c_count].token, name, 1);
	strncat(c_data[c_count].token, destination, 1);
	char n_seats_str[3];
	sprintf(n_seats_str, "%02d", n_seats);
	strcat(c_data[c_count].token, n_seats_str);
}
int init()
{
	{ // to check bus seats availability
		for (int i = 0; i < TOTAL_SEATS; i++)
		{
			check_seat[i] = 1; // 1 means available
		}
	}

	{ // to do list booked customers
		for (int i = 0; i < TOTAL_SEATS; i++)
		{
			c_existence[i] = 0; // 0 means doesn't exists
		}
	}
}

void admin_panel()
{
	int choice;
	while (1)
	{
		printf("\t1. View all booked seats\n");
		printf("\t2. Search/View Ticket (Using Token)\n");
		printf("\t3. Cancel Ticket (Using Token)\n");
		printf("\t4. Change password\n");
		printf("\t5. Back\n");
		printf("\n\t>> ");
		scanf("%d", &choice);
		getchar();
		fflush(stdin);
		if (choice == 1)
		{
			clr();
			view_booked_seats(c_count);
		}
		else if (choice == 2)
		{
			clr();
			if (c_count > 0)
			{
				char token[7];
				printf("\tEnter token No.:\n");
				printf("\t>> ");
				fgets(token, sizeof(token), stdin);
				getchar();
				fflush(stdin);
				clr();

				if (search_by_token(token))
				{
					printf("\tPress 'enter' to continue...\n");
					printf("\t");
					getchar();
					fflush(stdin);
				}
				else
				{
					printf("\tNo such token exists!\n\n");
					printf("\tPress 'enter' to continue!\n");
					printf("\t");
					getchar();
					fflush(stdin);
				}
				clr();
			}
			else
			{
				printf("\tNo seats booked yet!\n\n");
				printf("\tPress 'enter' to continue!\n");
				printf("\t");
				getchar();
				fflush(stdin);
				clr();
			}
		}
		else if (choice == 3)
		{
			// get token input
			clr();
			if (c_count > 0)
			{
				char token[7];
				printf("\tEnter token No.:\n");
				printf("\t>> ");
				fgets(token, sizeof(token), stdin);
				fflush(stdin);
				getchar();
				clr();
				delete_by_token(token); // pass the token to another function
				printf("\tPress 'enter' to continue...\n");
				printf("\t");
				getchar();
				fflush(stdin);
				clr();
			}
			else
			{
				clr();
				printf("\tNo seats booked yet!\n\n");
				printf("\tPress 'enter' to continue!\n");
				printf("\t");
				getchar();
				fflush(stdin);
				clr();
			}
		}
		else if (choice == 4)
		{
			clr();
			change_admin_pass();
			break;
		}
		else if (choice == 5)
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
		// show all booked seats
		for (int i = 0, j = 0; i < TOTAL_SEATS && j < c_count; i++)
		{
			if (c_existence[i] == 1)
			{
				// show only if customer exists
				printf("\t\t%d. > %s > %s > %s > %d\n\n", (j + 1), c_data[i].token, c_data[i].name, c_data[i].destination, c_data[i].n_seats);
				j++; // only increment if customer exists
			}
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
			printf("\tSorry! Only %d seats are available!\n\n", available_seats);
			continue;
		}
		else
		{
			c_data[c_count].n_seats = n_seat;
			clr();
			break;
		}
	}

	while (n_seat > 0)
	{
		// visualize seats
		printf("\n\tAvailable seats:\t\n\n");
		printf("\t============================\n");
		for (int i = 0; i < TOTAL_SEATS; i += 4)
		{
			printf("\t------------\t------------\n");
			if (check_seat[i] == 1)
			{
				printf("\t (%d)  ", i + 1);
			}
			else
			{
				printf("\t (X)  ");
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

			printf("\t------------\t------------\n");
		}
		printf("\t============================\n\n");

		printf("\tEnter a seat number to book:\n");
		printf("\t>> ");
		scanf("%d", &seat_no);
		getchar();
		fflush(stdin);
		clr();

		if (seat_no > TOTAL_SEATS || seat_no < 0)
		{
			printf("\tInvalid seat number!\n\n");
			printf("\tPress 'enter' to show available seats...\n");
			printf("\t");
			getchar();
			fflush(stdin);
			clr();
			continue;
		}
		// check if seat is booked or not
		else if (check_seat[seat_no - 1] == 0)
		{
			clr();
			printf("\tThis seat is already booked,\n\tPlease choose another seat!\n");
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
		clr();
	}
	// confirmation of booking

	printf("\n");
	/* idk what causing a bug here, which including a '>>' while entering multiple seats together
	to solve that i had to include this linebreak. which seems to work */

	clr();
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
		scanf("%c", &ch);
		getchar();
		fflush(stdin);

		if (ch == 'y' || ch == 'Y')
		{
			clr();
			// generate token number
			gen_token(c_data[c_count].name, c_data[c_count].destination, c_data[c_count].n_seats);
			// make customer existence 1/true
			c_existence[c_count] = 1;
			// increase customer count
			c_count++;
			// print confirmation message
			printf("\n\tBooking confirmed!\n\n");
			printf("\tYour token number is: %s", c_data[c_count - 1].token);
			printf("\n\t(Please keep this token number safe!)\n\n");
			printf("\tPress 'Enter' to continue...\n");
			printf("\t");
			getchar();
			fflush(stdin);
			clr();
			break;
		}
		else if (ch == 'n' || ch == 'N') // cancel booking
		{
			clr();

			// reset check_seat array
			for (int i = 0; i < c_data[c_count].n_seats; i++)
			{
				check_seat[c_data[c_count].booked_seats[i] - 1] = 1;
			}

			// reset variables
			booked_seats -= c_data[c_count].n_seats;
			available_seats += c_data[c_count].n_seats;

			printf("\tBooking canceled!\n\n");
			printf("\tPress 'Enter' to continue...\n");
			printf("\t");
			getchar();
			fflush(stdin);
			clr();
			break;
		}
		else
		{
			printf("\n\tInvalid input!\n\n");
			fflush(stdin);
			printf("\t(if it is Yes enter 'y' or 'Y' and if it is No enter 'n' or 'N')\n\n");
			printf("\tDo you want to confirm booking? (y/n)\n");
			printf("\t>> ");
		}
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

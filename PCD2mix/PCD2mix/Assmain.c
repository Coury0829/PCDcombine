#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#pragma warning (disable: 4996)


//---Staff-(LEE JONG YEN)----------------------------------------------------------------------------

struct User {
	char userID[50];
	char username[50];
	char password[50];
	char recoverypass[50];
	char position[50];
};
#define quantity  100
int staffQuantity = 0;

struct User users[quantity] = {
	{"1","1","1"},
	{"ST101", "Lee", "p1"},
	{"ST102", "Tan", "p2"},
	{"ST103", "Wong", "p3"}
};
struct User s[quantity];

int staff();
void addStaff();
void searchStaff();
void modifyStaff();
void displayStaff();
void stafflogo();
void deleteStaff();
void reportStaff();

// main function here ------------------------------------------------------------------------------- 
int staff() {
	int choice;
	char userId[50], username[50], password[50];

	int maxAttempts = 3;
	int attempts = 0;

	stafflogo();

	while (attempts < maxAttempts) {
		printf("Enter userID: ");
		scanf("%s", userId);
		printf("Enter username: ");
		scanf("%s", username);
		printf("Enter password: ");
		scanf("%s", password);

		int i;
		for (i = 0; i < quantity; i++) {
			if (strcmp(userId, users[i].userID) == 0 &&
				strcmp(username, users[i].username) == 0 &&
				strcmp(password, users[i].password) == 0) {
				printf("\nLogin successful!!!!\n");

				do {
					printf("\n");
					printf("\t\t<<   <<Staff Module>>  >>\n");
					printf("\t\t\t1. Add staff\n");
					printf("\t\t\t2. Search staff\n");
					printf("\t\t\t3. Modify staff\n");
					printf("\t\t\t4. Display staff\n");
					printf("\t\t\t5. Delete staff\n");
					printf("\t\t\t6. Staff Report staff\n");
					printf("\t\t\t7. Exit\n");
					printf("\n\t\tEnter your choice: ");
					scanf("%d", &choice);

					switch (choice) {
					case 1:
						addStaff();
						break;
					case 2:
						searchStaff();
						break;
					case 3:
						modifyStaff();
						break;
					case 4:
						displayStaff();
						break;
					case 5:
						deleteStaff();
						break;
					case 6:
						reportStaff();
						break;
					case 7:
						printf("\nExiting staff module...\n");
						break;
					default:
						printf("\nInvalid choice. Please try again.....\n\n");
						break;
					}
				} while (choice != 7);


				return 0;
			}
		}

		printf("Incorrect. Please try again.\n\n");
		attempts++;

	}

	printf("Max attempts reached. Login failed.\n\n");
	return 0;

}

//add staff function here --------------------------------------------------------------------------- 
void addStaff() {
	FILE* fp;
	char ans;

	do {
		fp = fopen("staff.txt", "a");
		if (fp == NULL) {
			printf("Error opening file!\n");
			return;
		}

		for (int i = 0; i < 1; i++) {
			printf("\n\tEnter staff id: ");
			scanf(" %[^\n]", s[staffQuantity].userID);

			printf("\tEnter staff name: ");
			scanf(" %[^\n]", s[staffQuantity].username);

			printf("\tEnter Password: ");
			scanf(" %[^\n]", s[staffQuantity].password);

			printf("\tEnter Recovery password: ");
			scanf(" %[^\n]", s[staffQuantity].recoverypass);

			printf("\tEnter Position Exp(Administrator) :");
			scanf(" %[^\n]", s[staffQuantity].position);



			fprintf(fp, "%s %s %s %s %s \n", s[staffQuantity].userID, s[staffQuantity].username,
				s[staffQuantity].password, s[staffQuantity].recoverypass, s[staffQuantity].position);

			staffQuantity++;
		}
		fclose(fp);

		printf("\n\tStaff added successfully\n");
		printf("\tDo you want to continue to Add Staff? (y/n): ");
		scanf(" %c", &ans);

	} while (ans == 'y' || ans == 'Y');
}

//search function here ------------------------------------------------------------------------------ 
void searchStaff() {
	FILE* fp;
	char id[20];
	int found = 0;

	fp = fopen("staff.txt", "r");
	if (fp == NULL) {
		printf("File not found or could not be opened.\n");
		return;
	}

	printf("\n\tEnter staff ID to search: ");
	scanf(" %[^\n]", id);

	while (fscanf(fp, "%s %s %s %s %s", s[staffQuantity].userID, s[staffQuantity].username,
		s[staffQuantity].password, s[staffQuantity].recoverypass, s[staffQuantity].position) != EOF) {
		if (strcmp(id, s[staffQuantity].userID) == 0) {
			found = 1;
			printf("\n\t>> Staff found <<\n");
			printf("\t     ID : %s\n", s[staffQuantity].userID);
			printf("\t     Name : %s\n", s[staffQuantity].username);
			printf("\t     Position : %s\n", s[staffQuantity].position);
			break;
		}
	}

	fclose(fp);

	if (!found) {
		printf("\tStaff with ID %s not found.....\n", id);
	}
}

//modify function here ------------------------------------------------------------------------------ 
void modifyStaff() {
	FILE* fp;
	FILE* modifyFile;
	char id[20];
	int found = 0;
	int answer = 0;
	char ans;

	fp = fopen("staff.txt", "r");

	modifyFile = fopen("modify.txt", "w");

	printf("\n\tEnter staff ID to update: ");
	rewind(stdin);
	scanf("%[^\n]", id);

	while (fscanf(fp, "%s %s %s %s %s", s[staffQuantity].userID, s[staffQuantity].username, s[staffQuantity].password,
		s[staffQuantity].recoverypass, s[staffQuantity].position) != EOF) {
		if (strcmp(s[staffQuantity].userID, id) == 0) {
			found = 1;

			do {
				printf("\n\tSelect which part to modify:\n");
				printf("\t1. Staff ID\n");
				printf("\t2. Staff Name\n");
				printf("\t3. Password\n");
				printf("\tEnter your choice: ");
				scanf("%d", &answer);

				switch (answer) {
				case 1:
					printf("\tEnter new staff ID: ");
					scanf("%s", s[staffQuantity].userID);
					break;
				case 2:
					printf("\tEnter new staff name: ");
					scanf("%s", s[staffQuantity].username);
					break;
				case 3:
					printf("\tEnter new password: ");
					scanf("%s", s[staffQuantity].password);
					break;
				default:
					printf("\n\tINVALID choice. Please try again.\n");
					break;
				}

				printf("\n\tDo you want to continue modifying (y/n): ");
				scanf(" %c", &ans);
			} while (ans == 'y' || ans == 'Y');
		}

		fprintf(modifyFile, "%s %s %s %s %s\n", s[staffQuantity].userID, s[staffQuantity].username,
			s[staffQuantity].password, s[staffQuantity].recoverypass, s[staffQuantity].position);
	}

	fclose(fp);
	fclose(modifyFile);

	remove("staff.txt");

	rename("modify.txt", "staff.txt");

	if (found) {
		printf("\tStaff with ID %s updated successfully.\n", id);
	}
	else {
		printf("\n\t%s does not exist.\n", id);
	}
}

//logo here ----------------------------------------------------------------------------------------- 
void stafflogo() {

	printf("   _____ __        ________   ___                            \n");
	printf("  / ___// /_____ _/ __/ __/  /   |  ________  ____ _         \n");
	printf("  \\__ \\/ __/ __ `/ /_/ /_   / /| | / ___/ _ \\/ __ `/      \n");
	printf(" ___/ / /_/ /_/ / __/ __/  / ___ |/ /  /  __/ /_/ /          \n");
	printf("/____/\\__/\\__,_/_/ /_/    /_/  |_/_/   \\___/\\__,_/       \n");
	printf("                                                             \n");

	printf("=================================================================\n");
	printf("                   S T A F F   L O G I N                           \n");
	printf("===================================================================\n");
}

//display function here ----------------------------------------------------------------------------- 
void displayStaff() {
	FILE* fp;
	int count = 0;

	fp = fopen("staff.txt", "r");

	if (fp == NULL) {
		printf("Error opening file!\n");
		return;
	}

	printf("\n");
	printf("Staff ID    Name    Pass  RecPass     Posison");
	printf("\n====================================================================================================================\n");

	while (fscanf(fp, "%s %s %s %s %s", s[staffQuantity].userID, s[staffQuantity].username,
		s[staffQuantity].password, s[staffQuantity].recoverypass, s[staffQuantity].position) != EOF) {
		printf("   %s      %s     %s     %s       %s \n", s[staffQuantity].userID, s[staffQuantity].username,
			s[staffQuantity].password, s[staffQuantity].recoverypass, s[staffQuantity].position);
		count++;
	}

	printf("====================================================================================================================\n");
	printf("\t\tTotal number of staff: %d\n", count);
	printf("====================================================================================================================\n");

	fclose(fp);

}

// extra funxtion (Delete Staff) -------------------------------------------------------------------- 
void deleteStaff() {
	FILE* fp;
	FILE* tempFile;
	char id[50];
	int index = 0;

	fp = fopen("staff.txt", "r");
	if (fp == NULL) {
		printf("Error opening file.\n");
		return;
	}

	tempFile = fopen("temp.txt", "w");
	if (tempFile == NULL) {
		printf("Error opening temporary file.\n");
		fclose(fp);
		return;
	}

	printf("\n\tEnter staff id to delete: ");
	scanf("%s", id);

	while (fscanf(fp, "%s %s %s %s %s", s[index].userID, s[index].username,
		s[index].password, s[index].recoverypass, s[index].position) == 5) {
		if (strcmp(s[index].userID, id) != 0) {
			fprintf(tempFile, "%s %s %s %s %s\n", s[index].userID, s[index].username,
				s[index].password, s[index].recoverypass, s[index].position);
		}
		index++;
	}

	fclose(fp);
	fclose(tempFile);

	remove("staff.txt");
	rename("temp.txt", "staff.txt");
	printf("\tStaff with ID %s deleted successfully......\n", id);
}

// extra funxtion (Reportstaff Staff) --------------------------------------------------------------- 
void reportStaff() {
	FILE* fp;
	char id[20];
	int found = 0;

	fp = fopen("staff.txt", "r");
	if (fp == NULL) {
		printf("File not found or could not be opened.\n");
		return;
	}

	printf("\n\tEnter staff ID to Print Report: ");
	scanf(" %[^\n]", id);

	while (fscanf(fp, "%s %s %s %s %s", s[staffQuantity].userID, s[staffQuantity].username,
		s[staffQuantity].password, s[staffQuantity].recoverypass, s[staffQuantity].position) != EOF) {
		if (strcmp(id, s[staffQuantity].userID) == 0) {
			found = 1;
			printf("\n\t>> %s report in here <<\n", id);
			printf("\t     ID : %s\n", s[staffQuantity].userID);
			printf("\t     Name : %s\n", s[staffQuantity].username);
			printf("\t     Password : %s\n", s[staffQuantity].password);
			printf("\t     Recovery Password : %s\n", s[staffQuantity].recoverypass);
			printf("\t     Position : %s\n", s[staffQuantity].position);
			break;
		}
	}

	fclose(fp);

	if (!found) {
		printf("\tStaff with ID %s not found.....\n", id);
	}
}





//----------Schedule-(Yap Ming Hong)---------------------------------------------------------------------
#define max_members_InSchedule 50

struct data_members {
	int station;
	char trainid[30], departstation[30], arrivalstation[30];
};
struct data_members member[max_members_InSchedule];
int num_ScheduleMem = 0;

// Function prototypes
int main_schedule();
void Logo_Schedule();
void add_schedule();
void display_all();
void delete_schedule();
void modify_schedule();
void write_to_file();
void read_from_file();
void search_schedule();

int main_schedule() {
	int choiseSchedule;
	char memchoiseS;
    Logo_Schedule();

	read_from_file();
	do {
		printf("________________________________________\n");
		printf("\t1. Insert Train Details\n");
		printf("\t2. Display Member Schedule\n");
		printf("\t3. Search Schedule\n");
		printf("\t4. Modify Schedule\n");
		printf("\t5. Delete Schedule\n");
		printf("\t6. Exit\n");
		printf("----------------------------------------\n");
		printf("\tEnter your choice: ");
		scanf("%d", &choiseSchedule);

		switch (choiseSchedule) {
		case 1:
			add_schedule();
			break;
		case 2:
			Logo_Schedule();
			display_all();
			break;
		case 3:
			search_schedule();
			break;
		case 4:
			modify_schedule();
			break;
		case 5:
			delete_schedule();
			break;
		case 6:
			break;
		default:
			printf("Invalid choice! Please enter a valid option.\n");
		}

		printf("\tDo you want to go back to Schedule Menu? (Y/N): ");
		scanf(" %c", &memchoiseS);
		printf("-----------------------------------------------\n");
		printf("\n\n");

	} while (memchoiseS == 'Y' || memchoiseS == 'y');

	write_to_file();

	return 0;
}


void add_schedule() {
	char choise;
	do {
		printf("\n\tEnter Train ID (e.g. T001): ");
		scanf("%s", member[num_ScheduleMem].trainid);

		printf("\tEnter departure station (e.g. KL or KualaLumpur): ");
		scanf("%s", member[num_ScheduleMem].departstation);

		printf("\tEnter arrival station (e.g. subang): ");
		scanf("%s", member[num_ScheduleMem].arrivalstation);

		printf("\tEnter number of stations to go through: ");
		scanf(" %d", &member[num_ScheduleMem].station);

		num_ScheduleMem++;
		printf("\nSchedule added successfully.\n");

		printf("\tDo you want insert more? (Y/N): ");
		scanf(" %c", &choise);
		printf("-----------------------------------------------\n");
		printf("\n");
	} while (choise == 'Y' || choise == 'y');
}

void display_all() {
	printf("\n_______________________________________________");
	printf("\n\t\tAll MEMBER INFO \n\n");
	printf("One stations to go through = 5m\n");
	for (int i = 0; i < num_ScheduleMem; i++) {
		int adjusted_station = member[i].station * 5; // Adjusted station according to your requirement
		printf("\t\tTrainID: %s \n\t Depart station: %s \n\tArrival station: %s \n\tNeed go through: %d \n     Time to go through: %d\n\n",
			member[i].trainid, member[i].departstation, member[i].arrivalstation, member[i].station, adjusted_station);
	}
	printf("-----------------------------------------------\n\n");
}

void modify_schedule() {
	char trainid_to_modify[5];
	printf("\nEnter Train ID to modify: ");
	scanf("%4s", trainid_to_modify);

	int found = 0;
	printf("\nModify Schedule:\n");
	for (int i = 0; i < num_ScheduleMem; i++) {
		if (strcmp(member[i].trainid, trainid_to_modify) == 0) {
			printf("\t\tTrainID: %s \n\t Depart station: %s \n\tArrival station: %s \n\tNeed go through: %d\n\n",
				member[i].trainid, member[i].departstation, member[i].arrivalstation, member[i].station);
			found = 1;
			// Prompt user to modify which information
			int modify_choice;
			printf("What do you want to modify?\n");
			printf("\t1. Train ID\n");
			printf("\t2. Departure station\n");
			printf("\t3. Arrival station\n");
			printf("\t4. Number of stations\n");
			printf("\t5. Exit Modify\n");
			printf("Enter your choice: ");
			scanf("%d", &modify_choice);
			switch (modify_choice) {
			case 1:
				printf("Enter new Train ID: ");
				scanf("%s", member[i].trainid);
				break;
			case 2:
				printf("Enter new Departure station: ");
				scanf("%s", member[i].departstation);
				break;
			case 3:
				printf("Enter new Arrival station: ");
				scanf("%s", member[i].arrivalstation);
				break;
			case 4:
				printf("Enter new Number of stations: ");
				scanf("%d", &member[i].station);
				break;
			case 5:
				break;
			default:
				printf("Invalid choice!\n");
			}
			printf("Schedule modified successfully.\n");
			// Write the updated data back to file
			write_to_file();
		}
	}

	if (!found) {
		printf("\nSchedule with Train ID ( %s ) not found.\n", trainid_to_modify);
	}
}


void delete_schedule() {
	char trainid_to_delete[5];
	printf("\nEnter Train ID to delete: ");
	scanf("%4s", trainid_to_delete);

	int found = 0;
	printf("\nSchedule to delete:\n");
	for (int i = 0; i < num_ScheduleMem; i++) {
		if (strcmp(member[i].trainid, trainid_to_delete) == 0) {
			printf("\t\tTrainID: %s \n\t Depart station: %s \n\tArrival station: %s \n\tNeed go through: %d\n\n",
				member[i].trainid, member[i].departstation, member[i].arrivalstation, member[i].station);
			found = 1;
			// Ask for confirmation
			char confirm;
			printf("Do you want to delete this schedule? (Y/N): ");
			scanf(" %c", &confirm);
			if (confirm == 'Y' || confirm == 'y') {
				for (int j = i; j < num_ScheduleMem - 1; j++) {
					member[j] = member[j + 1];
				}
				num_ScheduleMem--;
				printf("\nSchedule deleted successfully.\n");
			}
			else {
				printf("\nDeletion canceled.\n");
			}
			break;
		}
	}

	if (!found) {
		printf("\nSchedule with Train ID ( %s ) not found.\n", trainid_to_delete);
		rewind(stdin);
	}
}

void search_schedule() {
	char trainid_to_search[5];
	printf("\nEnter Train ID to search: ");
	scanf("%s", trainid_to_search);

	int found = 0;
	printf("\nSearch Results:\n");
	for (int i = 0; i < num_ScheduleMem; i++) {
		if (strcmp(member[i].trainid, trainid_to_search) == 0) {
			printf("\t\tTrainID: %s \n\t Depart station: %s \n\tArrival station: %s \n\tNeed go through: %d\n\n",
				member[i].trainid, member[i].departstation, member[i].arrivalstation, member[i].station);
			found = 1;
		}
	}

	if (!found) {
		printf("\nSchedule with Train ID ( %s ) not found.\n", trainid_to_search);
	}
}

void write_to_file() {
	FILE* file_schedule;
	file_schedule = fopen("schedule.bin", "wb");
	if (file_schedule == NULL) {
		printf("Error opening the file.\n");
		return;
	}

	fwrite(member, sizeof(struct data_members), num_ScheduleMem, file_schedule);

	fclose(file_schedule);
	printf("________________________________________\n");
	printf("Data written to file successfully.\n");
	printf("----------------------------------------\n\n");
}

void read_from_file() {
	FILE* file_schedule;
	file_schedule = fopen("schedule.bin", "rb");
	if (file_schedule == NULL) {
		printf("\nFile not found or empty.\n\n");
		return;
	}

	num_ScheduleMem = fread(member, sizeof(struct data_members), max_members_InSchedule, file_schedule);

	fclose(file_schedule);
	printf("________________________________________\n");
	printf(" Data loaded from file successfully.\n");
	printf("----------------------------------------\n\n");
}

void Logo_Schedule() {
	printf("  ______           _          _____      __             __      ___                   \n");
	printf(" /_  __/________ _(_)___     / ___/_____/ /_  ___  ____/ /_  __/ (_)___  ____ _       \n");
	printf("  / / / ___/ __ `/ / __ \\    \\__ \\/ ___/ __ \\/ _ \\/ __  / / / / / / __ \\/ __ `/ \n");
	printf(" / / / /  / /_/ / / / / /   ___/ / /__/ / / /  __/ /_/ / /_/ / / / / / / /_/ /        \n");
	printf("/_/ /_/   \\__,_/_/_/ /_/   /____/\\___/_/ /_/\\___/\\__,_/\\__,_/_/_/_/ /_/\\__, /   \n");
	printf("                                                                      /____/          \n");
}





//---Ticket Booking-((Yap Yao Chung))---------------------------------------------------------------------
#define max_member 50

#define MAX_TICKETS 100

struct Ticket {
	int month;
	int quantityTicket;
};

struct time
{
	int day;
	int month;
	int year;
};

//Define a structer
struct data_Members {
	char bookingID[10];
	char memberID[10];
	char trainID[10];
	struct time bookingDate;
	struct time departureDate;
	char seatNumber[5];
	char coach;
	int quantityData;
	char paymentInfo[30];
	double amount;
	char ticketStatus[10];
};

void logo();
void add();
void displayticket();
void search();
void modify();
void delete();
void report();
void mainticket();;

void logo()
{

	printf("  _______      __        __     ____              __   _                     \n");
	printf(" /_  __(_)____/ /_____  / /_   / __ )____  ____  / /__(_)___  ____ _         \n");
	printf("  / / / / ___/ //_/ _ \\/ __/  / __  / __ \\/ __ \\/ //_/ / __ \\/ __ `/      \n");
	printf(" / / / / /__/ ,< /  __/ /_   / /_/ / /_/ / /_/ / ,< / / / / / /_/ /          \n");
	printf("/_/ /_/\\___/_/|_|\\___/\\__/  /_____/\\____/\\____/_/|_/_/_/ /_/\\__, /     \n");
	printf("                                                           /____/            \n");

};

void add() {
	FILE* ticket;
	struct data_Members member[max_member];
	char ans;
	int num_member = 0;

	printf("\n");
	do {
		// Open the text file in append mode
		ticket = fopen("ticket.txt", "a");
		if (ticket == NULL) {
			printf("File open error...");
			exit(-1);
		}

		printf("Enter Booking ID\t(eg.B1001)\t\t:");
		scanf("%s", member[num_member].bookingID);
		rewind(stdin);

		printf("Enter Member ID\t\t(eg.M1001)\t\t:");
		scanf("%[^\n]", member[num_member].memberID);
		rewind(stdin);

		printf("Enter Train ID\t\t(eg.T1001)\t\t:");
		scanf("%[^\n]", member[num_member].trainID);
		rewind(stdin);

		printf("Enter Booking Date (DD MM YYYY): ");
		scanf("%d %d %d", &member[num_member].bookingDate.day, &member[num_member].bookingDate.month, &member[num_member].bookingDate.year);
		rewind(stdin);

		printf("Enter Departure Date (DD MM YYYY): ");
		scanf("%d %d %d", &member[num_member].departureDate.day, &member[num_member].departureDate.month, &member[num_member].departureDate.year);
		rewind(stdin);

		printf("Enter Seat Number\t(eg.14A)\t\t:");
		scanf("%s", member[num_member].seatNumber);
		rewind(stdin);

		printf("Enter Coach\t\t(eg.B)\t\t\t:");
		scanf(" %c", &member[num_member].coach);
		rewind(stdin);

		printf("Enter Quantity\t\t(eg.1)\t\t\t:");
		scanf("%d", &member[num_member].quantityData);
		rewind(stdin);

		printf("Enter Payment Info\t(eg.CreditCard)\t:");
		scanf("%s", member[num_member].paymentInfo);
		rewind(stdin);

		printf("Enter Amount\t\t(eg.65.00)\t\t:");
		scanf("%lf", &member[num_member].amount);
		rewind(stdin);

		printf("Enter Ticket Status\t(eg.Booked)\t\t:");
		scanf("%s", member[num_member].ticketStatus);
		rewind(stdin);


		// Write the ticket info to text file
		fprintf(ticket, "%s %s %s %02d/%02d/%04d %02d/%02d/%04d %s %c %d %s %.2lf %s\n",
			member[num_member].bookingID,
			member[num_member].memberID,
			member[num_member].trainID,
			member[num_member].bookingDate.day, member[num_member].bookingDate.month, member[num_member].bookingDate.year,
			member[num_member].departureDate.day, member[num_member].departureDate.month, member[num_member].departureDate.year,
			member[num_member].seatNumber,
			member[num_member].coach,
			member[num_member].quantityData,
			member[num_member].paymentInfo,
			member[num_member].amount,
			member[num_member].ticketStatus);
		num_member++;

		fclose(ticket);

		printf("\n");
		printf("Ticket already added successfully\n");
		printf("Do you want to continue to Add Ticket (y/n): ");
		scanf(" %c", &ans);
	} while (ans == 'y' || ans == 'Y');
}

void displayticket()
{
	FILE* ticket;
	struct data_Members member;
	int count = 0;

	ticket = fopen("ticket.txt", "r");
	if (ticket == NULL) {
		printf("File open error...");
		exit(-1);
	}


	printf("\n");
	printf("+---------------------------------------------------------------------------------------------------------------------------------------+\n");
	printf("| BookingID   MemberID   TrainID  Booking Date  Departure Date       SeatNum   Coach   Quantity   Payment Info   Amount   TicketStatus  |\n");
	printf("+---------------------------------------------------------------------------------------------------------------------------------------+\n");


	while (fscanf(ticket, "%s %s %s %d/%d/%d %d/%d/%d %s %c %d %s %lf %s\n",
		member.bookingID,
		member.memberID,
		member.trainID,
		&member.bookingDate.day, &member.bookingDate.month, &member.bookingDate.year,
		&member.departureDate.day, &member.departureDate.month, &member.departureDate.year,
		member.seatNumber,
		&member.coach,
		&member.quantityData,
		member.paymentInfo,
		&member.amount,
		member.ticketStatus) != EOF) {
		printf("  %-10s   %-10s %-10s %02d/%02d/%04d   %02d/%02d/%04d %14s %6c %10d %15s %9.2f %10s\n",
			member.bookingID,
			member.memberID,
			member.trainID,
			member.bookingDate.day, member.bookingDate.month, member.bookingDate.year,
			member.departureDate.day, member.departureDate.month, member.departureDate.year,
			member.seatNumber,
			member.coach,
			member.quantityData,
			member.paymentInfo,
			member.amount,
			member.ticketStatus);
		count++;
	}

	printf("\n");
	printf("+------------------+\n");
	printf("| Total ticket: %d  |\n", count);
	printf("+------------------+\n");


	fclose(ticket);

};

void search()
{
	FILE* ticket;
	struct data_Members member;
	int found = 0;
	char id[20];

	//open text file in read mode
	ticket = fopen("ticket.txt", "r");
	if (ticket == NULL) {
		printf("File open error...");
		exit(-1);
	}

	printf("\n");
	printf("Enter Booking ID to search:");
	scanf(" %s", id);
	rewind(stdin);
	printf("\n");

	while (fscanf(ticket, "%s %s %s %d/%d/%d %d/%d/%d %s %c %d %s %lf %s\n",
		member.bookingID,
		member.memberID,
		member.trainID,
		&member.bookingDate.day, &member.bookingDate.month, &member.bookingDate.year,
		&member.departureDate.day, &member.departureDate.month, &member.departureDate.year,
		member.seatNumber,
		&member.coach,
		&member.quantityData,
		member.paymentInfo,
		&member.amount,
		member.ticketStatus
	) != EOF) {
		if (strcmp(id, member.bookingID) == 0) {
			found = 1;

			printf("+-----------------+-------------+\n");
			printf("| Ticket found    |             |\n");
			printf("+-----------------+-------------+\n");
			printf("| Booking ID      |  %s\t|\n", member.bookingID);
			printf("| Member ID       |  %s\t|\n", member.memberID);
			printf("| Train ID        |  %s\t|\n", member.trainID);
			printf("| Booking Date    |  %02d/%02d/%04d\t|\n", member.bookingDate.day, member.bookingDate.month, member.bookingDate.year);
			printf("| Departure Date  |  %02d/%02d/%04d\t|\n", member.departureDate.day, member.departureDate.month, member.departureDate.year);
			printf("| Seat Number     |  %s        |\n", member.seatNumber);
			printf("| Coach           |  %c\t\t|\n", member.coach);
			printf("| Quantity        |  %d\t\t|\n", member.quantityData);
			printf("| Payment Info    |  %s |\n", member.paymentInfo);
			printf("| Amount          |  %.2f\t|\n", member.amount);
			printf("| Ticket Status   |  %s     |\n", member.ticketStatus);
			printf("+-----------------+-------------+\n");
			break;
		}

	}

	fclose(ticket);
};

void modify() {
	FILE* ticket, * modifyFile;
	int found = 0;
	char id[10];
	char ans;
	struct data_Members member;

	ticket = fopen("ticket.txt", "r");
	if (ticket == NULL) {
		printf("Error opening ticket.txt\n");
		return;
	}

	modifyFile = fopen("modify.txt", "w");
	if (modifyFile == NULL) {
		printf("Error creating modify.txt\n");
		fclose(ticket);
		return;
	}

	printf("Enter Ticket Booking ID: ");
	scanf("%s", id);

	while (fscanf(ticket, "%s %s %s %d/%d/%d %d/%d/%d %s %c %d %s %lf %s\n",
		member.bookingID,
		member.memberID,
		member.trainID,
		&member.bookingDate.day, &member.bookingDate.month, &member.bookingDate.year,
		&member.departureDate.day, &member.departureDate.month, &member.departureDate.year,
		member.seatNumber,
		&member.coach,
		&member.quantityData,
		member.paymentInfo,
		&member.amount,
		member.ticketStatus
	) != EOF) {

		if (strcmp(member.bookingID, id) == 0) {
			found = 1;
			do {
				printf("+---------------------------------------+\n");
				printf("| Select which part you want to change: |\n");
				printf("+---------------------------------------+\n");
				printf("| 1. Booking ID                         |\n");
				printf("| 2. Member ID                          |\n");
				printf("| 3. Train ID                           |\n");
				printf("| 4. Seat Number                        |\n");
				printf("| 5. Coach                              |\n");
				printf("| 6. Quantity                           |\n");
				printf("| 7. Payment Info                       |\n");
				printf("| 8. Amount                             |\n");
				printf("| 9. Ticket Status                      |\n");
				printf("| a. Booking Date                       |\n");
				printf("| b. Departure Date                     |\n");
				printf("| x. Exit                               |\n");
				printf("+---------------------------------------+\n");

				printf("Enter your choice: ");
				scanf(" %c", &ans);
				rewind(stdin);

				switch (ans) {
				case '1':
					printf("Enter New Booking ID: ");
					scanf("%s", member.bookingID);
					break;
				case '2':
					printf("Enter New Member ID: ");
					scanf("%s", member.memberID);
					break;
				case '3':
					printf("Enter New Train ID: ");
					scanf("%s", member.trainID);
					break;
				case '4':
					printf("Enter New Seat Number: ");
					scanf("%s", member.seatNumber);
					break;
				case '5':
					printf("Enter New Coach: ");
					scanf(" %c", &member.coach);
					break;
				case '6':
					printf("Enter New Quantity: ");
					scanf("%d", &member.quantityData);
					break;
				case '7':
					printf("Enter New Payment Info: ");
					scanf("%s", member.paymentInfo);
					break;
				case '8':
					printf("Enter New Amount: ");
					scanf("%lf", &member.amount);
					break;
				case '9':
					printf("Enter New Ticket Status: ");
					scanf("%s", member.ticketStatus);
					break;
				case 'a':
					printf("Enter New Booking Date (DD MM YYYY): ");
					scanf("%d %d %d", &member.bookingDate.day, &member.bookingDate.month, &member.bookingDate.year);
					break;
				case 'b':
					printf("Enter New Departure Date (DD MM YYYY): ");
					scanf("%d %d %d", &member.departureDate.day, &member.departureDate.month, &member.departureDate.year);
					break;
				case 'x':
					printf("Exiting modification.\n");
					break;
				default:
					printf("Invalid choice\n");
				}

				printf("Do you want to continue modifying? (y/n): ");
				scanf(" %c", &ans);

			} while (ans == 'y' || ans == 'Y');
		}

		fprintf(modifyFile, "%s %s %s %02d/%02d/%04d %02d/%02d/%04d %s %c %d %s %.2lf %s\n",
			member.bookingID,
			member.memberID,
			member.trainID,
			member.bookingDate.day, member.bookingDate.month, member.bookingDate.year,
			member.departureDate.day, member.departureDate.month, member.departureDate.year,
			member.seatNumber,
			member.coach,
			member.quantityData,
			member.paymentInfo,
			member.amount,
			member.ticketStatus
		);
	}

	fclose(ticket);
	fclose(modifyFile);

	remove("ticket.txt");
	rename("modify.txt", "ticket.txt");

	if (found) {
		printf("Ticket with ID %s updated successfully.\n", id);
	}
	else {
		printf("Ticket with ID %s not found.\n", id);
	}
}

void delete() {
	FILE* ticket, * historyFile;
	struct data_Members member;
	char id[10];
	int index = 0;
	char ans;

	ticket = fopen("ticket.txt", "r");
	if (ticket == NULL) {
		printf("File open error...");
		exit(-1);
	}

	historyFile = fopen("history.txt", "w");
	if (historyFile == NULL) {
		printf("File open error...");
		exit(-1);
	}

	printf("\n");
	scanf("%c", &ans);

	do {
		printf("Enter Ticket ID To Delete: ");
		scanf("%s", id);
		while (fscanf(ticket, "%s %s %s %d/%d/%d %d/%d/%d %s %c %d %s %lf %s\n",
			member.bookingID,
			member.memberID,
			member.trainID,
			&member.bookingDate.day, &member.bookingDate.month, &member.bookingDate.year,
			&member.departureDate.day, &member.departureDate.month, &member.departureDate.year,
			member.seatNumber,
			&member.coach,
			&member.quantityData,
			member.paymentInfo,
			&member.amount,
			member.ticketStatus) == 15) {
			if (strcmp(member.bookingID, id) != 0) {
				fprintf(historyFile, "%s %s %s %02d/%02d/%04d %02d/%02d/%04d %s %c %d %s %lf %s\n",
					member.bookingID,
					member.memberID,
					member.trainID,
					member.bookingDate.day, member.bookingDate.month, member.bookingDate.year,
					member.departureDate.day, member.departureDate.month, member.departureDate.year,
					member.seatNumber,
					member.coach,
					member.quantityData,
					member.paymentInfo,
					member.amount,
					member.ticketStatus
				);
				index++;
			}
		}
	} while (ans == 'y' || ans == 'Y');

	fclose(ticket);
	fclose(historyFile);

	remove("ticket.txt");
	rename("history.txt", "ticket.txt");
	printf("Ticket deleted...");
}

void report() {
	FILE* ticket;
	struct Ticket tickets[MAX_TICKETS] = { 0 };
	int num_tickets = 0;

	ticket = fopen("ticket.txt", "r");
	if (ticket == NULL) {
		printf("Error opening ticket file.\n");
		return;
	}

	// Read ticket data and count ticket sales by month
	int month, quantityReport;
	while (fscanf(ticket, "%*s %*s %*s %*d/%d/%*d %*d/%*d/%*d %*s %*c %d %*s %*lf %*s\n", &month, &quantityReport) == 2) {
		// Find existing entry for the month or create a new one
		int i;
		for (i = 0; i < num_tickets; ++i) {
			if (tickets[i].month == month) {
				tickets[i].quantityTicket += quantityReport;
				break;
			}
		}
		if (i == num_tickets) {
			tickets[num_tickets].month = month;
			tickets[num_tickets].quantityTicket = quantityReport;
			++num_tickets;
		}
	}

	fclose(ticket);

	// Display the bar chart
	printf("\nTicket Sales Report:\n");
	for (int i = 0; i < num_tickets; ++i) {
		printf("%02d Ticket sold:%d | ", tickets[i].month, tickets[i].quantityTicket);
		for (int j = 0; j < tickets[i].quantityTicket; ++j) {
			printf("*");
		}
		printf("\n");
	}
}

void mainticket() {
	int choice;

	logo();

	do {
		printf("\n");
		printf("====================================================================================================\n");
		printf("+-------------------+   \n");
		printf("|   Select 1 - 7    |   \n");
		printf("+-------------------+   \n");
		printf("| 1. Add Ticket     |   \n");
		printf("| 2. Display Ticket |   \n");
		printf("| 3. Search Ticket  |   \n");
		printf("| 4. Modify Ticket  |   \n");
		printf("| 5. Delete Ticket  |   \n");
		printf("| 6. Report Ticket  |   \n");
		printf("| 7. Exit           |   \n");
		printf("+-------------------+   \n");
		printf("\tEnter your choice :");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			add();
			break;
		case 2:
			displayticket();
			break;
		case 3:
			search();
			break;
		case 4:
			modify();
			break;
		case 5:
			delete();
			break;
		case 6:
			report();
			break;
		case 7:
			printf("+---------------------------+\n");
			printf("| Exiting Ticket Booking... |\n");
			printf("+---------------------------+\n");
			break;
		default:
			printf("Invalid choice. Please enter valid choice...\n");

		}

	} while (choice != 7);

	system("pause");
}
//----------------------------------------------------------------







int main() {
	int choice;

	do {

		printf("    ___    __      __          _____                          ______           _               \n");
		printf("   /   |  / /___  / /_  ____ _/ ___/____  ____ _________     /_  __/________ _(_)___           \n");
		printf("  / /| | / / __ \\/ __ \\/ __ `/\\__ \\/ __ \\/ __ `/ ___/ _ \\     / / / ___/ __ `/ / __ \\   \n");
		printf(" / ___ |/ / /_/ / / / / /_/ /___/ / /_/ / /_/ / /__/  __/    / / / /  / /_/ / / / / /          \n");
		printf("/_/  |_/_/ .___/_/ /_/\\__,_//____/ .___/\\__,_/\\___/\\___/    /_/ /_/   \\__,_/_/_/ /_/      \n");
		printf("        /_/                     /_/                                                            \n");

		printf("\n");


		printf("1.Staff Function\n");
		printf("2.Ticket Booking Function\n");
		printf("3.Train Schedule Funciton\n");
		printf("4.Exit\n");
		printf("\n\t\tEnter your choice: ");
		scanf("%d", &choice);

		printf("\n");
		switch (choice)
		{
		case 1:
			staff();
			break;
		case 2:
			mainticket();
			break;
		case 3:
			main_schedule();
			break;
		case 4:
			printf("Exinting AlphaSpace Train...\n");
			printf("\n");
			printf("-----------------------------------------------------------------------------------\n");
			printf("|     TQ for using AlphaSpace Train system , have a good day bye.............      |\n");
			printf("-----------------------------------------------------------------------------------\n");
			break;
		default:
			printf("Invalid choice. Please try again...\n");
			break;
		}

		printf("\n");

	} while (choice != 4);


	system("pause");
}
//---------------------------------------------------------------

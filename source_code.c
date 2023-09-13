#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STATIONS 10
#define MAX_TRAINS 10
#define MAX_NAME_LENGTH 50
#define MAX_TICKETS 100

struct Station {
    char name[MAX_NAME_LENGTH];
};

struct Train {
    int number;
    char name[MAX_NAME_LENGTH];
    struct Station from_station;
    struct Station to_station;
    int total_seats;
    int seats_available;
};

struct Ticket {
    int train_number;
    char passenger_name[MAX_NAME_LENGTH];
    int seat_number;
    int passenger_age;
    char passenger_sex;
};

void initializeData(struct Train trains[], struct Station stations[], int* num_trains, int* num_stations) {
    struct Station s1 = {"Delhi"};
    struct Station s2 = {"Chennai"};
    struct Station s3 = {"Jaipur"};
    struct Station s4 = {"Mumbai"};

    stations[0] = s1;
    stations[1] = s2;
    stations[2] = s3;
    stations[3] = s4;
    *num_stations = 4;

    struct Train t1 = {5482, "Rajdhani Express", s1, s3, 50, 50};
    struct Train t2 = {8265, "MAS LTT Express", s2, s4, 100, 100};
    struct Train t3 = {9216, "Paschim Express", s1, s4, 80, 80};
    struct Train t4 = {8513, "Shatabdi Express", s2, s3, 70, 70};
    struct Train t5 = {3964, "Jodhpur Express", s3, s4, 120, 120};

    trains[0] = t1;
    trains[1] = t2;
    trains[2] = t3;
    trains[3] = t4;
    trains[4] = t5;
    *num_trains = 5;
}

int displayMenu() {
    int choice;
    printf("\nMenu:\n");
    printf("1. Show Available Trains\n");
    printf("2. Book a Ticket\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void showTrains(struct Train *trains, int num_trains) {
    printf("\nAvailable Trains:\n");
    printf("Train No.\t\tTrain Name\tFrom Station\t\tTo Station\t\tTotal "
           "Seats\tSeats Available\n");
    for (int i = 0; i < num_trains; i++) {
        printf("%d\t\t%s\t\t%s\t\t%s\t\t\t%d\t\t\t%d\n", trains[i].number,
               trains[i].name, trains[i].from_station.name,
               trains[i].to_station.name, trains[i].total_seats,
               trains[i].seats_available);
    }
}

int isAlphabetic(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i])) {
            return 0; // Not alphabetic
        }
    }
    return 1; // Alphabetic
}

void printTicketDetails(struct Ticket ticket, struct Train train) {
    printf("\nTicket Details:\n");
    printf("Train Number: %d\n", ticket.train_number);
    printf("Train Name: %s\n", train.name);
    printf("From Station: %s\n", train.from_station.name);
    printf("To Station: %s\n", train.to_station.name);
    printf("Passenger Name: %s\n", ticket.passenger_name);
    printf("Passenger Age: %d\n", ticket.passenger_age);
    printf("Passenger Gender: %c\n", ticket.passenger_sex);
    printf("Seat Number: %d\n", ticket.seat_number);
}

void bookTicket(struct Train *trains, int num_trains, struct Ticket tickets[], int *num_tickets) {
    int train_number, seat_number;
    char passenger_name[MAX_NAME_LENGTH];
    int passenger_age;
    char passenger_sex;

    showTrains(trains, num_trains);

    printf("\nEnter the Train Number: ");
    scanf("%d", &train_number);

    int train_index = -1;
    for (int i = 0; i < num_trains; i++) {
        if (trains[i].number == train_number) {
            train_index = i;
            break;
        }
    }

    if (train_index == -1) {
        printf("Invalid Train Number.\n");
        return;
    }

    if (trains[train_index].seats_available <= 0) {
        printf("No seats available for the selected train.\n");
        return;
    }

    while (1) {
        printf("Enter passenger name: ");
        scanf(" %[^\n]s", passenger_name);
        if (isAlphabetic(passenger_name)) {
            break; // Valid name, exit the loop
        } else {
            printf("Invalid name! Please enter alphabetic characters only.\n");
        }
    }

    while (1) {
        printf("Enter passenger age: ");
        scanf("%d", &passenger_age);
        if (passenger_age >= 0 && passenger_age <= 150) {
            break; // Valid age, exit the loop
        } else {
            printf("Invalid age! Please enter a valid age (0-150).\n");
        }
    }

    while (1) {
        printf("Enter passenger gender (M/F): ");
        scanf(" %c", &passenger_sex);
        passenger_sex = toupper(passenger_sex);
        if (passenger_sex == 'M' || passenger_sex == 'F') {
            break; // Valid sex, exit the loop
        } else {
            printf("Invalid gender! Please enter 'M' or 'F' only.\n");
        }
    }

    trains[train_index].seats_available--;
    struct Ticket new_ticket = {
        train_number,
        "",
        trains[train_index].total_seats - trains[train_index].seats_available,
        passenger_age,
        passenger_sex
    };
    strcpy(new_ticket.passenger_name, passenger_name);

    tickets[*num_tickets] = new_ticket;
    (*num_tickets)++;

    printf("\nTicket Booked Successfully!\n");
    printf("\n");
    printf("-----------------------------------------------------------------\n");
    printf("\t\t\t\t\t\tTICKET DETAILS\n");
    printTicketDetails(new_ticket, trains[train_index]);
    printf("-----------------------------------------------------------------\n");
    printf("\n");
}

int main() {
    struct Train trains[MAX_TRAINS];
    int num_trains = 0;
    struct Station stations[MAX_STATIONS];
    int num_stations = 0;
    struct Ticket tickets[MAX_TICKETS];
    int num_tickets = 0;

    initializeData(trains, stations, &num_trains, &num_stations);

    int choice;
    do {
        choice = displayMenu();

        switch (choice) {
        case 1:
            showTrains(trains, num_trains);
            break;
        case 2:
            bookTicket(trains, num_trains, tickets, &num_tickets);
            break;
        case 3:
            printf("\nThank you for using the Railway Reservation System.\n");
            break;
        default:
            printf("\nInvalid choice. Please try again.\n");
            break;
        }
    } while (choice != 3);

    return 0;
}

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

struct Appointment {
  char name[50];
  char surname[50];
  int day;
  int time;
};

int numAppointments = 0;
struct Appointment appointments[100];

void load_appointments() {
  // Read file content and load into array
  FILE * fl = fopen("appointments.txt", "r");

  while (fscanf(fl, "%s %[^,]%*c %d %*[,] %d", appointments[numAppointments].name, appointments[numAppointments].surname, & appointments[numAppointments].day, & appointments[numAppointments].time) == 4) {

    numAppointments++;
  }
  fclose(fl);
}

void save_appointments() {
  // Write array to file
  FILE * fl = fopen("appointments.txt", "w");
  for (int i = 0; i < numAppointments; i++) {
    fprintf(fl, "%s %s, %d, %d\n", appointments[i].name, appointments[i].surname, appointments[i].day, appointments[i].time);
  }
  fclose(fl);
}

void show_appointments() {
  // Show all appointments
  for (int i = 0; i < numAppointments; i++) {
    printf("%s %s %d %d\n", appointments[i].name, appointments[i].surname, appointments[i].day, appointments[i].time);
  }
}

int main() {
  int size = 20;

  char name[50];
  char surname[50];
  int day;
  int time;

  char deletedName[50];
  char deletedSurname[50];

  load_appointments();

  while (1) {
    printf("\nMenü:\n");
    printf("1. Show Appointments\n");
    printf("2. Search Appointments\n");
    printf("3. Make an Appointment\n");
    printf("4. Delete an appointment\n");
    printf("5. Exit\n\n");

    int choice;
    printf("Your choice: ");
    scanf("%d", & choice);

    switch (choice) {
    case 1: // Show Appointments
      show_appointments();
      break;

    case 2:

      printf("1. Search appointments by name\n");
      printf("2. Search appointments by day\n");
      printf("3. Back to the Menu\n");

      int choice2;
      printf("\nYour choice: ");
      scanf("%d", & choice2);

      switch (choice2) {
      case 1:
        printf("Patient name: ");
        scanf("%s %s", name, surname);

        int patient_exist = 0;

        // Search appointments by patient name
        for (int i = 0; i < numAppointments; i++) {
          if (strcmp(appointments[i].name, name) == 0 && strcmp(appointments[i].surname, surname) == 0) {
            printf("\n%s %s %d %d\n", appointments[i].name, appointments[i].surname, appointments[i].day, appointments[i].time);
            patient_exist = 1;
            break;
          }
        }
        printf(patient_exist ? "" : "\nPatient Not Found!\n");
        break;

      case 2:
        printf("Day (1-31): ");
        scanf("%d", & day);
        if (day >= 1 && day <= 31) {
          // Search appointments by day
          for (int i = 0; i < numAppointments; i++) {
            if (appointments[i].day == day) {
              printf("%s %s %d %d\n", appointments[i].name, appointments[i].surname, appointments[i].day, appointments[i].time);
            }
          }
        } else {
          printf("\nYou entered an invalid day!\n");
        }

        break;
      case 3:
        break;

      default:
        printf("Invalid selection. Please try again!\n");
      }
      break;

    case 3:

      printf("Patient Name: ");
      scanf("%s %s", name, surname);

      printf("Appointment Day (1-31): ");
      scanf("%d", & day);

      if (day < 1 || day > 31) {
        printf("You entered an invalid day!");
        break;
      }

      printf("Appointment Time (9-17): ");
      scanf("%d", & time);

      if (time < 9 || time > 17) {
        printf("You entered an invalid time!");
        break;
      }

      // Check the appointments
      int appointmentExists = 0;
      for (int i = 0; i < numAppointments; i++) {
        if (appointments[i].day == day && appointments[i].time == time) {
          appointmentExists = 1;
          break;
        }
      }

      if (appointmentExists) {
        printf("Sorry, appointments are full for that day and time. Please select another day and time!\n");
      } else {
        //If struct size is full, size is increased by 10 with malloc
        if (numAppointments >= size) {
          size += 10;
          struct Appointment * appointments = malloc(size * sizeof(struct Appointment));
        }

        // Randevuyu ekle
        strcpy(appointments[numAppointments].name, name);
        strcpy(appointments[numAppointments].surname, surname);
        appointments[numAppointments].day = day;
        appointments[numAppointments].time = time;
        numAppointments++;
        save_appointments();
        printf("Appointment successfully added!\n");
      }
      break;

    case 4:
      printf("Enter the name of the patient you want to delete: ");
      scanf("%s %s", deletedName, deletedSurname);

      int patient_exist = 0;

      //Deleting an Appointment
      for (int i = 0; i < numAppointments; i++) {
        if (strcmp(appointments[i].name, deletedName) == 0 && strcmp(appointments[i].surname, deletedSurname) == 0) {
          for (int j = i; j < numAppointments - 1; j++) {
            strcpy(appointments[j].name, appointments[j + 1].name);
            strcpy(appointments[j].surname, appointments[j + 1].surname);
            appointments[j + 1].day = appointments[j].day;
            appointments[j + 1].time = appointments[j].time;
          }
          numAppointments--;
          patient_exist = 1;
          save_appointments();
          printf("The appointment has been deleted!\n");
          break;
        }
      }
      printf(patient_exist ? "" : "\nPatient Not Found!\n");
      break;

    case 5:
      save_appointments();
      printf("Exit...\n");
      return 0;
      break;

    default:
      printf("Invalid selection. Please try again!\n");
    }
  }
  return 0;
}

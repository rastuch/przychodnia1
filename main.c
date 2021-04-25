#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#include "patients.h"
#include "doctors.h"
#include "visits.h"

struct Patient {
    char name[200];
    char secondName[200];
    char pesel[50];
    char birthDate[200];
    char address[200];
    char email[200];
    char phone[50];
    char weight[200];
    char height[200];
    char nfz[200];
};

struct Doctor {
    int id;
    char name[200];
    char secondName[200];
    char pesel[50];
    char pwzNumber[50];
    char title[200];
    char specialization[200];
    char email[200];
    char birthDate[200];
    char address[200];
    char phone[50];
    char weight[200];
    char height[200];
    char nfz[200];
};

struct Visit {
    int id;
    char patientId[50];
    char doctorId[50];
    char date[50];
    char time[50];
    char duration[50];
    char status[200];
};


struct Doctor doc;

struct Patient pat;

struct Visit vis;

void choicePatientList() {
    printf("\n");

    showAllpatients(); // funkcja odowłująca się do bazy

    printf("\n\n");

}

void choiceAddPatient() {
    /* Narazie zahardkodowane, domyślnie należy pobrać te wartości od użytkownika */
    strcpy(pat.name, "Antoni");
    strcpy(pat.secondName, "Kowalski");
    strcpy(pat.pesel, "9324523002");
    strcpy(pat.birthDate, "19-12-2008");
    strcpy(pat.address, "kielce");
    strcpy(pat.email, "antoni.kowalski@student.tu.kielce.pl");
    strcpy(pat.phone, "731800932");
    strcpy(pat.weight, "86");
    strcpy(pat.height, "186");
    strcpy(pat.nfz, "GOS Kielce 13/a");

    addPatient(pat); //

    printf("\nDodano pacjenta!");
    printf("\n\n");
}

void choiceDeletePatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    deletePatientById(id); // funkcja odowłująca się do bazy

    printf("\nUsunieto pacjenta\n\n");
}

void choiceShowPatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    struct Patient myPatient = getPatientById(id); // funkcja odowłująca się do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nImie: %s,  Nazwisko: %s,  PESEL: %s itd....",
             myPatient.name, myPatient.secondName, myPatient.pesel);
    printf("%s", message);
    printf("\n\n");
}


void choiceActionPatient() {

    printf("\nWybierz akcje ktora chcesz wykonac\n");
    printf("\n1.Pokaz liste pacjentow");
    printf("\n2.Dodaj pacjenta Antoni Kowalski");
    printf("\n3.Usun pacjenta o wybranym id");
    printf("\n4.Pokaz pacjenta o wybranym id");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            choicePatientList();
            choiceActionPatient();
            break;

        case 2:
            choiceAddPatient();
            choiceActionPatient();
            break;

        case 3:
            choiceDeletePatient();
            choiceActionPatient();
            break;

        case 4:
            choiceShowPatient();
            choiceActionPatient();
            break;

        default:
            printf("\nPodano nieprawidlowy wybor!\n");
            choiceActionPatient();
            break;
    }
}


int main() {
    printf("Hello, Przychodnio!\n");
    choiceActionPatient();
    return 0;
}

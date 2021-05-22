#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#include "patients.h"
#include "doctors.h"
#include "visits.h"

//Struct representing patient table in database
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

//Struct representing doctor table in database
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

//Struct representing patient Visits in database
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
        const char *table;
        table = columnNamePatientChoice();
        const char *order;
        order = sortPatientOrder();

        showAllpatients(table, order); // funkcja odow³uj¹ca siê do bazy

        printf("\n\n");

}

void choiceDoctorList() {
    printf("\n");
    const char *table;
    table = columnNameDoctorChoice();
    const char *order;
    order = sortDoctorOrder();

    showAllDoctors(table, order); // funkcja odow³uj¹ca siê do bazy

    printf("\n\n");

}

void choiceAddDoctor() {
    /* Narazie zahardkodowane, domyœlnie nale¿y pobraæ te wartoœci od u¿ytkownika */
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
    printf("Podaj imie\n");
    scanf("%s", name);
    strcpy(doc.name, name);
    printf("Podaj nazwisko\n");
    scanf("%s", secondName);
    strcpy(doc.secondName, secondName);
    printf("Podaj pesel\n");
    scanf("%s", pesel);
    strcpy(doc.pesel, pesel);
    printf("Podaj date urodzin\n");
    scanf("%s", birthDate);
    strcpy(doc.birthDate, birthDate);
    printf("Podaj adres\n");
    scanf("%s", address);
    strcpy(doc.address, address);
    printf("Podaj e-maila\n");
    scanf("%s", email);
    strcpy(doc.email, email);
    printf("Podaj numer telefonu\n");
    scanf("%s", phone);
    strcpy(doc.phone, phone);
    printf("Podaj wage\n");
    scanf("%s", weight);
    strcpy(doc.weight, weight);
    printf("Podaj wzrost\n");
    scanf("%s", height);
    strcpy(doc.height, height);

    addDoctor(doc); //

    printf("\nDodano lekarza!");
    printf("\n\n");
}

void choiceAddPatient() {
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
    printf("Podaj imie\n");
    scanf("%s", name);
    strcpy(pat.name, name);
    printf("Podaj nazwisko\n");
    scanf("%s", secondName);
    strcpy(pat.secondName, secondName);
    printf("Podaj pesel\n");
    scanf("%s", pesel);
    strcpy(pat.pesel, pesel);
    printf("Podaj date urodzin\n");
    scanf("%s", birthDate);
    strcpy(pat.birthDate, birthDate);
    printf("Podaj adres\n");
    scanf("%s", address);
    strcpy(pat.address, address);
    printf("Podaj e-maila\n");
    scanf("%s", email);
    strcpy(pat.email, email);
    printf("Podaj numer telefonu\n");
    scanf("%s", phone);
    strcpy(pat.phone, phone);
    printf("Podaj wage\n");
    scanf("%s", weight);
    strcpy(pat.weight, weight);
    printf("Podaj wzrost\n");
    scanf("%s", height);
    strcpy(pat.height, height);
    printf("Podaj nfz\n");
    scanf("%s2", nfz);
    strcpy(pat.nfz, nfz);

    addPatient(pat); //

    printf("\nDodano pacjenta!");
    printf("\n\n");
}

void choiceDeletePatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    deletePatientById(id); // funkcja odow³uj¹ca siê do bazy

    printf("\nUsunieto pacjenta\n\n");
}

void choiceDeleteDoctor() {
    printf("\nPodaj id lekarza:\n");
    char id[50];
    scanf("%s", &id);

    deleteDoctorById(id); // funkcja odow³uj¹ca siê do bazy

    printf("\nUsunieto lekarza\n\n");
}

void choiceShowPatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    struct Patient myPatient = getPatientById(id); // funkcja odow³uj¹ca siê do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nImie: %s,  Nazwisko: %s,  PESEL: %s,Data urodzin: %s,Adres: %s,E-maila: %s,"
                                       "Numer telefonu: %s,Waga: %s,Wzrost: %s,NFZ: %s,", myPatient.name,
             myPatient.secondName,
             myPatient.pesel, myPatient.birthDate, myPatient.address, myPatient.email, myPatient.phone,
             myPatient.weight, myPatient.height, myPatient.nfz);
    printf("%s", message);
    printf("\n\n");

}

void choiceShowDoctor() {
    printf("\nPodaj id lekarza:\n");
    char id[50];
    scanf("%s", &id);

    struct Doctor myDoctor = getDoctorById(id); // funkcja odow³uj¹ca siê do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nImie: %s,  Nazwisko: %s,  PESEL: %s,Data urodzin: %s,Adres: %s,E-maila: %s,"
                                       "Numer telefonu: %s,Waga: %s,Wzrost: %s,NFZ: %s,", myDoctor.name,
             myDoctor.secondName,
             myDoctor.pesel, myDoctor.birthDate, myDoctor.address, myDoctor.email, myDoctor.phone,
             myDoctor.weight, myDoctor.height, myDoctor.nfz);
    printf("%s", message);
    printf("\n\n");

}

void choiceEditPatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    struct Patient myPatient = getPatientById(id); // funkcja odow³uj¹ca siê do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nImie: %s,  Nazwisko: %s,  PESEL: %s,Data urodzin: %s,Adres: %s,E-maila: %s,"
                                       "Numer telefonu: %s,Waga: %s,Wzrost: %s,NFZ: %s,", myPatient.name,
             myPatient.secondName,
             myPatient.pesel, myPatient.birthDate, myPatient.address, myPatient.email, myPatient.phone,
             myPatient.weight, myPatient.height, myPatient.nfz);
    printf("%s", message);
    printf("\n\n");

    printf("Czy chcesz zmienic imie pacjenta?  1 - tak, 0 - nie\n");
    int choice;
    scanf("%i", &choice);
    if (choice == 1) {
        char name[200];
        printf("Podaj nowe imie\n");
        scanf("%s", name);
        strcpy(myPatient.name, name);
    }
    printf("Czy chcesz zmienic nazwisko pacjenta?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char secondName[200];
        printf("Podaj nowe nazwisko\n");
        scanf("%s", secondName);
        strcpy(myPatient.secondName, secondName);
    }
    printf("Czy chcesz zmienic pesel pacjenta?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char pesel[50];
        printf("Podaj nowy pesel\n");
        scanf("%s", pesel);
        strcpy(myPatient.pesel, pesel);
    }
    printf("Czy chcesz zmienic e-mail pacjenta?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char email[200];
        printf("Podaj nowy e-mail\n");
        scanf("%s", email);
        strcpy(myPatient.email, email);
    }
    printf("Czy chcesz zmienic numer telefonu pacjenta?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char phone[50];
        printf("Podaj nowy numer telefonu\n");
        scanf("%s", phone);
        strcpy(myPatient.phone, phone);
    }
    printf("Czy chcesz zmienic wage pacjenta?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char weight[200];
        printf("Podaj nowa wage\n");
        scanf("%s", weight);
        strcpy(myPatient.weight, weight);
    }
    printf("Czy chcesz zmienic wzrost pacjenta?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char height[200];
        printf("Podaj nowy wzrost\n");
        scanf("%s", height);
        strcpy(myPatient.height, height);
    }
    printf("Czy chcesz zmienic nfz pacjenta?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char nfz[200];
        printf("Podaj nowy nfz\n");
        scanf("%s", nfz);
        strcpy(myPatient.nfz, nfz);
    }

    updatePatientById(id, myPatient); //
}

void choiceEditDoctor() {
    printf("\nPodaj id lekarza:\n");
    char id[50];
    scanf("%s", &id);

    struct Doctor myDoctor = getDoctorById(id); // funkcja odow³uj¹ca siê do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nImie: %s,  Nazwisko: %s,  PESEL: %s,Data urodzin: %s,Adres: %s,E-maila: %s,"
                                       "Numer telefonu: %s,Waga: %s,Wzrost: %s,NFZ: %s,", myDoctor.name,
             myDoctor.secondName,
             myDoctor.pesel, myDoctor.birthDate, myDoctor.address, myDoctor.email, myDoctor.phone,
             myDoctor.weight, myDoctor.height, myDoctor.nfz);
    printf("%s", message);
    printf("\n\n");

    printf("Czy chcesz zmienic imie lekarza?  1 - tak, 0 - nie\n");
    int choice;
    scanf("%i", &choice);
    if (choice == 1) {
        char name[200];
        printf("Podaj nowe imie\n");
        scanf("%s", name);
        strcpy(myDoctor.name, name);
    }
    printf("Czy chcesz zmienic nazwisko lekarza?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char secondName[200];
        printf("Podaj nowe nazwisko\n");
        scanf("%s", secondName);
        strcpy(myDoctor.secondName, secondName);
    }
    printf("Czy chcesz zmienic pesel lekarza?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char pesel[50];
        printf("Podaj nowy pesel\n");
        scanf("%s", pesel);
        strcpy(myDoctor.pesel, pesel);
    }
    printf("Czy chcesz zmienic e-mail lekarza?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char email[200];
        printf("Podaj nowy e-mail\n");
        scanf("%s", email);
        strcpy(myDoctor.email, email);
    }
    printf("Czy chcesz zmienic numer telefonu lekarza?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char phone[50];
        printf("Podaj nowy numer telefonu\n");
        scanf("%s", phone);
        strcpy(myDoctor.phone, phone);
    }
    printf("Czy chcesz zmienic wage lekarza?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char weight[200];
        printf("Podaj nowa wage\n");
        scanf("%s", weight);
        strcpy(myDoctor.weight, weight);
    }
    printf("Czy chcesz zmienic wzrost lekarza?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char height[200];
        printf("Podaj nowy wzrost\n");
        scanf("%s", height);
        strcpy(myDoctor.height, height);
    }

    updateDoctorById(id, myDoctor); //
}


void choiceActionDoctor() {
    printf("\nWybierz akcje ktora chcesz wykonac\n");
    printf("\n1.Dodaj lekarza");
    printf("\n2.Usun lekarza o wybranym id");
    printf("\n3.Pokaz liste lekarzy");
    printf("\n4.Edytuj lekarza o wybranym id");
    printf("\n5.Pokaz lekarza o wybranym id");
    printf("\n6.Powrót do wyboru sekcji");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            choiceAddDoctor();
            choiceActionDoctor();
            break;

        case 2:
            choiceDeleteDoctor();
            choiceActionDoctor();
            break;

        case 3:
            choiceDoctorList();
            choiceActionDoctor();
            break;

        case 4:
            choiceEditDoctor();
            choiceActionDoctor();
            break;

        case 5:
            choiceShowDoctor();
            choiceActionDoctor();
            break;
        case 6:
            break;
        default:
            printf("\nPodano nieprawidlowy wybor!\n\n\n");
            choiceActionDoctor();
    }
}

void choiceActionPatient() {

    printf("\nWybierz akcje ktora chcesz wykonac\n");
    printf("\n1.Pokaz liste pacjentow");
    printf("\n2.Dodaj pacjenta");
    printf("\n3.Usun pacjenta o wybranym id");
    printf("\n4.Pokaz pacjenta o wybranym id");
    printf("\n5.Edytuj pacjenta o wybranym id");
    printf("\n6.Powrót do wyboru sekcji");
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

        case 5:
            choiceEditPatient();
            choiceActionPatient();
            break;
        case 6:
            break;
        default:
            printf("\nPodano nieprawidlowy wybor!\n");
            choiceActionPatient();
            break;
    }
}

void choiceActionTable() {
    printf("\nWybierz akcje ktora chcesz wykonac\n\n");
    printf("\n1.Sekcja Pacjenta");
    printf("\n2.Sekcja Lekarza");
    printf("\n3.Sekcja Wizyt");

    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            choiceActionPatient();
            break;
        case 2:
            choiceActionDoctor();
            break;
        default:
            printf("\nPodano nieprawidlowy wybor!\n\n\n");
            choiceActionTable();
    }
}

int main() {
    printf("Hello, Przychodnio!\n");
    while(1) {
        choiceActionTable();
    }
    return 0;
}
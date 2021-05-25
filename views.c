//
// Created by programista on 25.05.2021.
//

#include "views.h"
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include <string.h>
#include "patients.h"
#include "doctors.h"
#include "visits.h"

/**
 * Struktura reprezentujaca tabele Pacjenta w bazie danych
  */
struct Patient {
    char name[200]; /**< Imie */
    char secondName[200]; /**< Nazwisko */
    char pesel[50]; /**< Numer pesel jako tablia znakow */
    char birthDate[200]; /**< data urodzenia w formacje DD-MM-YYYY */
    char address[200]; /**< Adres */
    char email[200]; /**< Email */
    char phone[50]; /**< Numer telefonu */
    char weight[200]; /**< Waga w kg */
    char height[200]; /**< Wzrost w cm */
    char nfz[200]; /**< NFZ */
};

/**
 * Struktura reprezentujaca tabele Lekarza w bazie danych
  */
struct Doctor {
    int id; /**< Identyfikator */
    char name[200]; /**< Imie */
    char secondName[200]; /**< Nazwisko */
    char pesel[50]; /**< Numer PESEL */
    char pwzNumber[50]; /**< Numer PWZ */
    char title[200]; /**< Tytul naukowy */
    char specialization[200]; /**< Specjalizacja */
    char email[200]; /**< Email */
    char birthDate[200]; /**< Data urodzenia w formacie DD-MM-YYYY */
    char address[200]; /**< Adres */
    char phone[50]; /**< Numer telefonu */
    char weight[200]; /**< Waga */
    char height[200]; /**< Wzrost */
    char nfz[200]; /**< NFZ */
};

//Struct representing patient Visits in database
struct Visit {
    int id; /**< Identyfikator */
    char patientId[50]; /**< Identyfikator pacjenta */
    char doctorId[50]; /**< Identyfikator lekarza */
    char date[50]; /**< Data urodzenia w formacie DD-MM-YYYY */
    char time[50]; /**< Godzina wizyty w formacie GG:MM */
    char duration[50]; /**< Czas trwania wizyty w formacie GG:MM */
    char status[200]; /**< Status wizyty */
};

/*!
 * Zmienna pomocnicza z aktualnym lekarzem
 */
struct Doctor doc;

/*!
 * Zmienna pomocnicza z aktualnym pacjentem
 */
struct Patient pat;


/*!
 * Zmienna pomocnicza z aktualna wizyta
 */
struct Visit vis;

/*!
 * Wyswietlenie wszystkich pacjentow
 * @note konsolowe GUI
 */
void choicePatientList() {
    printf("\n");
    const char *table;
    table = columnNamePatientChoice();
    const char *order;
    order = sortPatientOrder();

    showAllpatients(table, order); // funkcja odowłująca się do bazy

    printf("\n\n");

}

/*!
 * Wyswietlenie wszystkich lekarzy
 * @note konsolowe GUI
 */
void choiceDoctorList() {
    printf("\n");
    const char *table;
    table = columnNameDoctorChoice();
    const char *order;
    order = sortDoctorOrder();

    showAllDoctors(table, order); // funkcja odowłująca się do bazy

    printf("\n\n");

}

/*!
 * Wyszukanie pacjentów
 * @note konsolowe GUI
 */
void choiceSearchPatient(){
    char imie[100];
    printf("\nPoddaj imie lub nazwisko pacjenta: \n");
    scanf("%s",&imie);
    searchPatients(imie);
    printf("\n\n");
}

/*!
 * Wyszukanie lekarzy
 * @note konsolowe GUI
 */
void choiceSearchDoctors(){
    char imie[100];
    printf("\nPoddaj imie lub nazwisko lekarza: \n");
    scanf("%s",&imie);
    searchDoctors(imie);
    printf("\n\n");
}

/*!
 * Dodanie lekarza
 * @note konsolowe GUI
 */
void choiceAddDoctor() {
    /* Narazie zahardkodowane, domyślnie należy pobrać te wartości od użytkownika */
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

/*!
 * Dodanie pacjenta
 * @note konsolowe GUI
 */
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

/*!
 * Usunięcie pacjenta
 * @note konsolowe GUI
 */
void choiceDeletePatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    deletePatientById(id); // funkcja odowłująca się do bazy

    printf("\nUsunieto pacjenta\n\n");
}

/*!
 * Usunięcie lekarza
 * @note konsolowe GUI
 */
void choiceDeleteDoctor() {
    printf("\nPodaj id lekarza:\n");
    char id[50];
    scanf("%s", &id);

    deleteDoctorById(id); // funkcja odowłująca się do bazy

    printf("\nUsunieto lekarza\n\n");
}


/*!
 * Wyświetlenie pacjenta
 * @note konsolowe GUI
 */
void choiceShowPatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    struct Patient myPatient = getPatientById(id); // funkcja odowłująca się do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nImie: %s,  Nazwisko: %s,  PESEL: %s,Data urodzin: %s,Adres: %s,E-maila: %s,"
                                       "Numer telefonu: %s,Waga: %s,Wzrost: %s,NFZ: %s,", myPatient.name,
             myPatient.secondName,
             myPatient.pesel, myPatient.birthDate, myPatient.address, myPatient.email, myPatient.phone,
             myPatient.weight, myPatient.height, myPatient.nfz);
    printf("%s", message);
    printf("\n\n");

}

/*!
 * Wyświetlenie lekarza
 * @note konsolowe GUI
 */
void choiceShowDoctor() {
    printf("\nPodaj id lekarza:\n");
    char id[50];
    scanf("%s", &id);

    struct Doctor myDoctor = getDoctorById(id); // funkcja odowłująca się do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nImie: %s,  Nazwisko: %s,  PESEL: %s,Data urodzin: %s,Adres: %s,E-maila: %s,"
                                       "Numer telefonu: %s,Waga: %s,Wzrost: %s,NFZ: %s,", myDoctor.name,
             myDoctor.secondName,
             myDoctor.pesel, myDoctor.birthDate, myDoctor.address, myDoctor.email, myDoctor.phone,
             myDoctor.weight, myDoctor.height, myDoctor.nfz);
    printf("%s", message);
    printf("\n\n");

}

/*!
 * Edycja pacjenta
 * @note konsolowe GUI
 */
void choiceEditPatient() {
    printf("\nPodaj id pacjenta:\n");
    char id[50];
    scanf("%s", &id);

    struct Patient myPatient = getPatientById(id); // funkcja odowłująca się do bazy

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

/*!
 * Edycja lekarza
 * @note konsolowe GUI
 */
void choiceEditDoctor() {
    printf("\nPodaj id lekarza:\n");
    char id[50];
    scanf("%s", &id);

    struct Doctor myDoctor = getDoctorById(id); // funkcja odowłująca się do bazy

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

/*!
* Wyswietlenie wszystkich Visyt
* @note konsolowe GUI
*/
void choiceVisitList() {
    printf("\n");
    showAllVisits(); // funkcja odowłująca się do bazy
    printf("\n\n");
}

/*!
 * Dodanie Wizyty
 * @note konsolowe GUI
 */
void choiceAddVisit() {

    char patientId[50]; /**< Identyfikator pacjenta */
    char doctorId[50]; /**< Identyfikator lekarza */
    char date[50]; /**< Data urodzenia w formacie DD-MM-YYYY */
    char time[50]; /**< Godzina wizyty w formacie GG:MM */
    char duration[50]; /**< Czas trwania wizyty w formacie GG:MM */
    char status[200]; /**< Status wizyty */

    printf("Podaj id Pacjenta\n");
    scanf("%s", patientId);
    strcpy(vis.patientId, patientId);

    printf("Podaj id Lekarza\n");
    scanf("%s", doctorId);
    strcpy(vis.doctorId, doctorId);

    printf("Podaj termin wizyty DD-MM-YYYY\n");
    scanf("%s", date);
    strcpy(vis.date, date);

    printf("Podaj godzine w formacie GG:MM\n");
    scanf("%s", time);
    strcpy(vis.time, time);

    printf("Podaj czas trwania wizyty\n");
    scanf("%s", duration);
    strcpy(vis.duration, duration);

    printf("Podaj czy wizyta jest zaplanowana czy niezaplanowana\n");
    scanf("%s", status);
    strcpy(vis.status, status);

    addVisit(vis);

    printf("\nDodano Wizyte!");
    printf("\n\n");
}

/*!
 * Edycja Wizyt
 * @note konsolowe GUI
 */
void choiceUpdateVisitById(){
    printf("\nPodaj id Wizyty:\n");
    char id[50];
    scanf("%s", &id);

    struct Visit myVisit = getVisitById(id); // funkcja odowłująca się do bazy

    char message[400];
    snprintf(message, sizeof(message), "\n\nId_Pacjenta: %s,  Id_Doktora: %s,  Data: %s,Godzina: %s,Czas Trwania: %s,Status: %s,", myVisit.patientId,
             myVisit.doctorId,myVisit.date, myVisit.time, myVisit.duration, myVisit.status);
    printf("%s", message);
    printf("\n\n");

    printf("Czy chcesz zmienic id Pacjenta?  1 - tak, 0 - nie\n");
    int choice;
    scanf("%i", &choice);
    if (choice == 1) {
        char patientId[200];
        printf("Podaj nowe id\n");
        scanf("%s", patientId);
        strcpy(myVisit.patientId, patientId);
    }
    printf("Czy chcesz zmienic id lekarza?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char doctorId[200];
        printf("Podaj nowe Id lekarza\n");
        scanf("%s", doctorId);
        strcpy(myVisit.doctorId, doctorId);
    }
    printf("Czy chcesz zmienic termin wizyty?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char date[50];
        printf("Podaj nowy Termin DD-MM-YYYY\n");
        scanf("%s", date);
        strcpy(myVisit.date, date);
    }
    printf("Czy chcesz zmienic godzine wizyty?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char time[200];
        printf("Podaj nowa godzine\n");
        scanf("%s", time);
        strcpy(myVisit.time, time);
    }
    printf("Czy chcesz zmienic czas trwania wizyty?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char duration[200];
        printf("Podaj nowy czas trwania wizyty\n");
        scanf("%s", duration);
        strcpy(myVisit.duration, duration);
    }
    printf("Czy chcesz zmienic status wizyty?  1 - tak, 0 - nie\n");

    scanf("%i", &choice);
    if (choice == 1) {
        char status[50];
        printf("Podaj nowy Status wizyty\n");
        scanf("%s", status);
        strcpy(myVisit.status, status);
    }

    updateVisitById(id, myVisit); //

    printf("\nZaktualizowano Wizyte!");
    printf("\n\n");

}

/*!
 * Usunięcie Wizyty
 * @note konsolowe GUI
 */
void choiceDeleteVisitById(){
    printf("\nPodaj id Wizyty:\n");
    char id[50];
    scanf("%s", &id);

    deleteVisitById(id); // funkcja odowłująca się do bazy

    printf("\nUsunieto Wizyte\n\n");

}

/*!
 * Wybor akcji na tabeli lekarzy
 * @note konsolowe GUI
 */
void choiceActionDoctor() {
    printf("\nWybierz akcje ktora chcesz wykonac\n");
    printf("\n1.Dodaj lekarza");
    printf("\n2.Usun lekarza o wybranym id");
    printf("\n3.Pokaz liste lekarzy");
    printf("\n4.Edytuj lekarza o wybranym id");
    printf("\n5.Pokaz lekarza o wybranym id");
    printf("\n6.Wyszukaj lekarza");
    printf("\n7.Powrót do wyboru sekcji");
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
            choiceSearchDoctors();
            choiceActionDoctor();
            break;

        case 7:
            break;
        default:
            printf("\nPodano nieprawidlowy wybor!\n\n\n");
            choiceActionDoctor();
    }
}

/*!
 * Wybor akcji na tabeli pacjenta
 * @note konsolowe GUI
 */
void choiceActionPatient() {

    printf("\nWybierz akcje ktora chcesz wykonac\n");
    printf("\n1.Pokaz liste pacjentow");
    printf("\n2.Dodaj pacjenta");
    printf("\n3.Usun pacjenta o wybranym id");
    printf("\n4.Pokaz pacjenta o wybranym id");
    printf("\n5.Edytuj pacjenta o wybranym id");
    printf("\n6.Wyszukiwanie pacjenta");
    printf("\n7.Powrót do wyboru sekcji");
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
            choiceSearchPatient();
            choiceActionPatient();
            break;
        case 7:
            break;
        default:
            printf("\nPodano nieprawidlowy wybor!\n");
            choiceActionPatient();
            break;
    }
}

/*!
 * Wybor akcji na tabeli visyt
 * @note konsolowe GUI
 */
void choiceActionVisit() {

    printf("\nWybierz akcje ktora chcesz wykonac\n");
    printf("\n1.Dodanie wizyty");
    printf("\n2.Edycja wizyty");
    printf("\n3.Usunięcie wizyty");
    printf("\n4.Wyswietalanie wizyt");
    printf("\n5.Powrót do wyboru sekcji");
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            choiceAddVisit();
            choiceActionVisit();
            break;

        case 2:
            choiceUpdateVisitById();
            choiceActionVisit();
            break;

        case 3:
            choiceDeleteVisitById();
            choiceActionVisit();
            break;

        case 4:
            choiceVisitList();
            choiceActionVisit();
            break;

        case 5:
            break;
        default:
            printf("\nPodano nieprawidlowy wybor!\n");
            choiceActionPatient();
            break;
    }
}

/*!
 * Wybor sekcji
 * @note konsolowe GUI
 * @return int jesli wyniesie 0, aplikacje zostaje wylaczona;
 */
int choiceActionTable() {
    printf("\nWybierz akcje ktora chcesz wykonac\n\n");
    printf("\n1.Sekcja Pacjenta");
    printf("\n2.Sekcja Lekarza");
    printf("\n3.Sekcja Wizyt");
    printf("\n\n4.Zamknij");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            choiceActionPatient();
            break;
        case 2:
            choiceActionDoctor();
            break;
        case 3:
            choiceActionVisit();
            break;
        case 4:
            return 0;
        default:
            printf("\nPodano nieprawidlowy wybor!\n\n\n");
            choiceActionTable();
    }
}
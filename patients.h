//
// Created by programista on 09.03.2021.
//

#ifndef PRZYCHODNIA_PATIENTS_H
#define PRZYCHODNIA_PATIENTS_H

/* Deklaracja funkcji typu CRUD dla struktury "Patient" */

struct Patient getPatientObject();

const char* columnNamePatientChoice();

const char* sortPatientOrder();

void addPatient(struct Patient newPatient);

struct Patient getPatientById(char id[50]);

void updatePatientById(char id[50], struct Patient newPatient);

void deletePatientById(char id[50]);

void showAllpatients();

int insertData();






#endif //PRZYCHODNIA_PATIENTS_H

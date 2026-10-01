#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "patients.dat"
#define MAX_PATIENTS 100

typedef struct {
    int id;
    char name[90];
    int age;
    char disease[50];
} Patient;

void insert_patient();
void update_patient();
void delete_patient();
void display_patient();
void search_patient();
void save_patient(Patient patient);
void load_patients(Patient patients[], int *count);
void save_all_patients(Patient patients[], int count);

int main()
{
    int choice;

    while (1) {
        printf("\nPatient Management System\n");
        printf("1. Insert patient\n");
        printf("2. Update patient\n");
        printf("3. Delete patient\n");
        printf("4. Display patients\n");
        printf("5. Search patient\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                insert_patient();
                break;
            case 2:
                update_patient();
                break;
            case 3:
                delete_patient();
                break;
            case 4:
                display_patient();
                break;
            case 5:
                search_patient();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

void insert_patient()
{
    Patient patient;

    printf("Enter patient ID: ");
    scanf("%d", &patient.id);
    getchar();

    printf("Enter patient name: ");
    fgets(patient.name, sizeof(patient.name), stdin);
    patient.name[strcspn(patient.name, "\n")] = 0;

    printf("Enter patient age: ");
    scanf("%d", &patient.age);
    getchar();

    printf("Enter patient disease: ");
    fgets(patient.disease, sizeof(patient.disease), stdin);
    patient.disease[strcspn(patient.disease, "\n")] = 0;

    save_patient(patient);
    printf("Patient record inserted successfully.\n");
}

void update_patient()
{
    int id, i, found = 0;
    Patient patients[MAX_PATIENTS];
    int count = 0;

    load_patients(patients, &count);

    printf("Enter patient ID to update: ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < count; i++) {
        if (patients[i].id == id) {
            found = 1;

            printf("Enter new name: ");
            fgets(patients[i].name, sizeof(patients[i].name), stdin);
            patients[i].name[strcspn(patients[i].name, "\n")] = 0;

            printf("Enter new disease: ");
            fgets(patients[i].disease, sizeof(patients[i].disease), stdin);
            patients[i].disease[strcspn(patients[i].disease, "\n")] = 0;
            break;
        }
    }

    if (found) {
        save_all_patients(patients, count);
        printf("Patient record updated successfully.\n");
    } else {
        printf("Patient ID not found.\n");
    }
}

void delete_patient()
{
    int id, i, j, found = 0;
    Patient patients[MAX_PATIENTS];
    int count = 0;

    load_patients(patients, &count);

    printf("Enter patient ID to delete: ");
    scanf("%d", &id);
    getchar();

    for (i = 0; i < count; i++) {
        if (patients[i].id == id) {
            found = 1;
            for (j = i; j < count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            count--;
            break;
        }
    }

    if (found) {
        save_all_patients(patients, count);
        printf("Patient record deleted successfully.\n");
    } else {
        printf("Patient ID not found.\n");
    }
}

void display_patient()
{
    Patient patients[MAX_PATIENTS];
    int count = 0;

    load_patients(patients, &count);

    printf("\nPatient records:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Name: %s, Age: %d, Disease: %s\n",
               patients[i].id, patients[i].name,
               patients[i].age, patients[i].disease);
    }
}

void search_patient()
{
    int id, found = 0;
    Patient patients[MAX_PATIENTS];
    int count = 0;

    load_patients(patients, &count);

    printf("Enter patient ID to search: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            printf("Patient found:\n");
            printf("ID: %d, Name: %s, Age: %d, Disease: %s\n",
                   patients[i].id, patients[i].name,
                   patients[i].age, patients[i].disease);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Patient ID not found.\n");
    }
}

void save_patient(Patient patient)
{
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&patient, sizeof(Patient), 1, file);
    fclose(file);
}

void load_patients(Patient patients[], int *count)
{
    *count = 0;
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        return;
    }
    while (*count < MAX_PATIENTS &&
           fread(&patients[*count], sizeof(Patient), 1, file)) {
        (*count)++;
    }
    fclose(file);
}

void save_all_patients(Patient patients[], int count)
{
    FILE *file = fopen(FILE_NAME, "wb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(patients, sizeof(Patient), count, file);
    fclose(file);
}

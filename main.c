#include <stdio.h>
#include <string.h>
#include <stdlib.h>>

#define MAX 100

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Structs

typedef struct {
    int id;
    char name[50];
    int priority; 
    char symptoms[100];
} Patient;

typedef struct {
    int id;              
    char patientName[50]; 
    char diagnosis[100]; 
    char treatment[100];
} MedicalRecord;

typedef struct {
    int id;                
    char name[50];        
    char specialty[50];
    int experience;       
    struct Doctor *next;
} Doctor;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Structs Stack, Queue and List
typedef struct {
    Patient patients[MAX];
    int front;
    int rear;
    int count;
} PatientQueue;


typedef struct {
    MedicalRecord records[MAX];
    int top;
} MedicalRecordStack;

typedef struct {
    Doctor *start;
} DoctorList;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Functions base data structs 

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Queue functions

// Initialize the queue
void initializePatientQueue(PatientQueue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

// Verify if is empty
int isPatientQueueEmpty(PatientQueue *q) {
    return (q->count == 0);
}

// search for a patient with a specific ID
int searchPatientId(PatientQueue *q, int id) {
    if (isPatientQueueEmpty(q)) {
        return 0; 
    }

    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % MAX;
        if (q->patients[index].id == id) {
            return 1; 
        }
    }
    return 0; 
}

// Verify if is full
int isPatientQueueFull(PatientQueue *q) {
    return (q->count == MAX);
}

// Insert patient (enqueue)
int insertPatient(PatientQueue *q, Patient p) {
    if (isPatientQueueFull(q)) {
        printf("Erro: fila de pacientes cheia!\n");
        return 0;
    }

    if (searchPatientId(q, p.id)) {
        printf("Erro: Ja existe um paciente com o ID %d na fila.\n", p.id);
        return 0;
    }
    q->patients[q->rear] = p;
    q->rear = (q->rear + 1) % MAX;
    q->count++;
    return 1;
}

// assists patient (dequeue)
int servePatient(PatientQueue *q, Patient *p) {
    if (isPatientQueueEmpty(q)) {
        printf("Erro: fila de pacientes vazia!\n");
        return 0;
    }
    *p = q->patients[q->front];
    q->front = (q->front + 1) % MAX;
    q->count--;
    return 1;
}

// Consult first patient
int consultPatient(PatientQueue *q, Patient *p) {
    if (isPatientQueueEmpty(q)) {
        printf("Fila de pacientes vazia!\n");
        return 0;
    }
    *p = q->patients[q->front];
    return 1;
}

// display all patients
void displayPatients(PatientQueue *q) {
    if (isPatientQueueEmpty(q)) {
        printf("Nenhum paciente na fila.\n");
        return;
    }

    printf("\n--- Fila de Pacientes ---\n");
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % MAX;
        printf("ID: %d | Nome: %s | Prioridade: %d | Sintomas: %s\n",
               q->patients[index].id,
               q->patients[index].name,
               q->patients[index].priority,
               q->patients[index].symptoms);
    }
}

// extra: critic patients
int countCriticalPatients(PatientQueue *q) {
    if (isPatientQueueEmpty(q)) {
        return 0;
    }

    int count = 0;
    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % MAX;
        if (q->patients[index].priority == 3) { // supondo que prioridade 3 seja crítico
            count++;
        }
    }
    return count;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// stack functions

// Inicialize stack
void initializeMedicalRecordStack(MedicalRecordStack *s) {
    s->top = -1;
}

// Verify if is empty
int isMedicalRecordStackEmpty(MedicalRecordStack *s) {
    return (s->top == -1);
}

// Verifica if is full
int isMedicalRecordStackFull(MedicalRecordStack *s) {
    return (s->top == MAX - 1);
}

// Insert medical record (push)
int insertMr(MedicalRecordStack *s, MedicalRecord r) {
    if (isMedicalRecordStackFull(s)) {
        printf("Erro: pilha de prontuários cheia!\n");
        return 0;
    }
    s->records[++(s->top)] = r;
    return 1;
}

// Remove medical record (pop)
int removeMr(MedicalRecordStack *s, MedicalRecord *r) {
    if (isMedicalRecordStackEmpty(s)) {
        printf("Erro: pilha de prontuários vazia!\n");
        return 0;
    }
    *r = s->records[(s->top)--];
    return 1;
}

// Consult last medical record (top)
int consultLastMr(MedicalRecordStack *s, MedicalRecord *r) {
    if (isMedicalRecordStackEmpty(s)) {
        printf("Nenhum prontuário na pilha!\n");
        return 0;
    }
    *r = s->records[s->top];
    return 1;
}

// display all medical records
void displayMr(MedicalRecordStack *s) {
    if (isMedicalRecordStackEmpty(s)) {
        printf("Nenhum prontuário armazenado.\n");
        return;
    }

    printf("\n--- Pilha de Prontuários ---\n");
    for (int i = s->top; i >= 0; i--) {
        printf("ID: %d | Paciente: %s | Diagnóstico: %s | Tratamento: %s\n",
               s->records[i].id,
               s->records[i].patientName,
               s->records[i].diagnosis,
               s->records[i].treatment);
    }
}

// Extra: invert stack
void reverseMr(MedicalRecordStack *s) {
    if (isMedicalRecordStackEmpty(s)) {
        printf("A pilha está vazia, não pode ser invertida.\n");
        return;
    }
    int i = 0, j = s->top;
    while (i < j) {
        MedicalRecord temp = s->records[i];
        s->records[i] = s->records[j];
        s->records[j] = temp;
        i++;
        j--;
    }
    printf("A pilha foi invertida!\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
// list functions

// Inicialize list doctors
void initializeDoctorList(DoctorList *list) {
    list->start = NULL;
}

// Insert doctor in the begin
void insertDoctor(DoctorList *list, Doctor d) {
    Doctor *newDoctor = (Doctor*)malloc(sizeof(Doctor));
    *newDoctor = d;
    newDoctor->next = list->start;
    list->start = newDoctor;
    printf("Médico inserido com sucesso!\n");
}

// Remove doctor with id
int removeDoctor(DoctorList *list, int id) {
    Doctor *current = list->start;
    Doctor *prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Médico com ID %d não encontrado.\n", id);
        return 0;
    }

    if (prev == NULL) { // remove in the begin
        list->start = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Médico removido com sucesso!\n");
    return 1;
}

// search doctor (id)
Doctor* searchDoctor(DoctorList *list, int id) {
    Doctor *current = list->start;
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// display all doctors
void displayDoctors(DoctorList *list) {
    if (list->start == NULL) {
        printf("Nenhum médico cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Médicos ---\n");
    Doctor *current = list->start;
    while (current != NULL) {
        printf("ID: %d | Nome: %s | Especialidade: %s | Experiência: %d anos\n",
               current->id,
               current->name,
               current->specialty,
               current->experience);
        current = current->next;
    }
}

// Extra: search doctor specialty
void searchSpecDoctor(DoctorList *list, char *specialty) {
    int found = 0;
    Doctor *current = list->start;
    while (current != NULL) {
        if (strcmp(current->specialty, specialty) == 0) {
            printf("ID: %d | Nome: %s | Especialidade: %s | Experiência: %d anos\n",
                   current->id,
                   current->name,
                   current->specialty,
                   current->experience);
            found = 1;
        }
        current = current->next;
    }
    if (!found) {
        printf("Nenhum médico encontrado com a especialidade: %s\n", specialty);
    }
}


//------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Functions

void menu(PatientQueue *q, MedicalRecordStack *s, DoctorList *l){
    int option = -1;

    do
    {   
        printf("\n========================================\n");
        printf("\n     SISTEMA HOSPITALAR RUBRO NEGRO\n");
        printf("\n========================================\n");

        printf("\nEscolha a estrutura de dados:"
                "\n1. Fila de Pacientes (atendimentos por ordem de chegada)"
                "\n2. Pilha de Prontuarios (armazenamento temporario de documentos)"
                "\n3. Lista de Medicos (lista dinamica de profissionais cadastrados)"
                "\n0. Sair\n"
                "\n========================================\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            printf("\n========================================\n");
            printf("\n            FILA DE PACIENTES\n");
            printf("\n========================================\n");

            printf("\n1. Inserir paciente na fila"
                    "\n2. Atender (remover paciente da fila)"
                    "\n3. Consultar primeiro paciente da fila"
                    "\n4. Exibir todos os pacientes na fila"
                    "\n5. [Operacao adicional] Contar pacientes em estado critico"
                    "\n6. Voltar ao menu principal\n"
                    "\n========================================\n");

                    printf("Digite a opcao desejada: ");
                    scanf("%d", &option);

                    switch (option)
                    {
                        case 1: {
                        Patient newPatient;

                        printf("\nDigite o ID do paciente: ");
                        scanf("%d", &newPatient.id);

                        printf("\nDigite o nome do paciente: ");
                        scanf(" %[^\n]", newPatient.name);

                        printf("\nDigite a prioridade do paciente (1. Normal, 2. Medio, 3. Emergencia): ");
                        scanf("%d", &newPatient.priority);

                        printf("\nDigite os sintomas do paciente: ");
                        scanf(" %[^\n]", newPatient.symptoms);

                        if(insertPatient(q, newPatient)){
                            printf("\nPaciente inserido na fila com sucesso!!");
                        }
                    
                        break;
                    }
                    case 2: {
                        Patient servedPatient;
                        if(servePatient(q, &servedPatient)){
                            printf("Paciente atendido:\n");
                            printf("ID: %d | Nome: %s | Prioridade: %d | Sintomas: %s\n",
                            servedPatient.id, servedPatient.name, servedPatient.priority, servedPatient.symptoms);
                        }
                        break;
                    }
                    case 3: {
                        Patient firstPatient;

                        if(consultPatient(q, &firstPatient)){
                            printf("Paciente atendido:\n");
                            printf("ID: %d | Nome: %s | Prioridade: %d | Sintomas: %s\n",
                            firstPatient.id, firstPatient.name, firstPatient.priority, firstPatient.symptoms);
                        }    
                        break;
                    }
                    case 4: {
                        displayPatients(q);
                        break;
                    }
                    case 5: {
                        int criticalCount = countCriticalPatients(q);
                        printf("\nNumero de pacientes no estado critico: %d", criticalCount);
                        break;
                    }
                    default:
                        break;
                    }
            break;
        
        case 2:
            printf("\n========================================\n");
            printf("\n          PILHA DE PRONTUARIOS\n");
            printf("\n========================================\n");
            printf("\n1. Inserir prontuario (push)"
                    "\n2. Remover prontuario (pop)"
                    "\n3. Consultar ultimo prontuário (topo da pilha)"
                    "\n4. Exibir todos os prontuarios"
                    "\n5. [Operacao adicional] Inverter ordem da pilha"
                    "\n6. Voltar ao menu principal\n"
                    "\n========================================\n");

                    printf("Digite a opcao desejada: ");
                    scanf("%d", &option);

                    switch (option)
                    {
                    case 1:
                        /* code */
                        break;

                    case 2:
                        /* code */
                        break;

                    case 3:
                        /* code */
                        break;

                    case 4:
                        /* code */
                        break;

                    case 5:
                        /* code */
                        break;
                    
                    default:
                        break;
                    }

            break;
        case 3:
            printf("\n========================================\n");
            printf("\n            LISTA DE MEDICOS\n");
            printf("\n========================================\n");
            printf("\n1. Inserir medico na lista"
                    "\n2. Remover medico da lista"
                    "\n3. Consultar medico por ID"
                    "\n4. Exibir todos os medicos cadastrados"
                    "\n5. [Operacao adicional] Buscar medico por especialidade"
                    "\n6. Voltar ao menu principal\n"
                    "\n========================================\n");

                    printf("Digite a opcao desejada: ");
                    scanf("%d", &option);

                    switch (option)
                    {
                    case 1:
                        /* code */
                        break;

                    case 2:
                        /* code */
                        break;

                    case 3:
                        /* code */
                        break;

                    case 4:
                        /* code */
                        break;

                    case 5:
                        /* code */
                        break;
                    
                    default:
                        break;
                    }

            break;

        default:
            break;
        }
        
    } while (option!=0);
    


}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

int main(){
    PatientQueue patientQueue;
    MedicalRecordStack medicalRecordStack;
    DoctorList doctorList;
    initializePatientQueue(&patientQueue);
    initializeMedicalRecordStack(&medicalRecordStack);
    initializeDoctorList(&doctorList);
    menu(&patientQueue, &medicalRecordStack, &doctorList);

    return 0;
}
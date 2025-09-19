#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* Função: initializePatientQueue
* Descrição: Inicializa a fila de pacientes, configurando os ponteiros de início e fim e o contador.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes a ser inicializada.
* Retorna:
*   void
*/
void initializePatientQueue(PatientQueue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

/*
* Função: isPatientQueueEmpty
* Descrição: Verifica se a fila de pacientes está vazia.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
* Retorna:
*   1 se a fila estiver vazia, 0 caso contrário.
*/
int isPatientQueueEmpty(PatientQueue *q) {
    return (q->count == 0);
}

/*
* Função: searchPatientId
* Descrição: Busca um paciente na fila por um ID específico.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
*   id: O ID do paciente a ser buscado.
* Retorna:
*   1 se o ID for encontrado, 0 caso contrário.
*/
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

/*
* Função: isPatientQueueFull
* Descrição: Verifica se a fila de pacientes está cheia.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
* Retorna:
*   1 se a fila estiver cheia, 0 caso contrário.
*/
int isPatientQueueFull(PatientQueue *q) {
    return (q->count == MAX);
}

/*
* Função: insertPatient
* Descrição: Insere um novo paciente no final da fila.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
*   p: A estrutura Patient contendo os dados do novo paciente.
* Retorna:
*   1 se a inserção for bem-sucedida, 0 caso contrário.
*/
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

/*
* Função: servePatient
* Descrição: Remove o paciente que está no início da fila (atende).
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
*   p: Ponteiro para a estrutura Patient que irá receber os dados do paciente removido.
* Retorna:
*   1 se a remoção for bem-sucedida, 0 caso contrário.
*/
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

/*
* Função: consultPatient
* Descrição: Consulta os dados do paciente que está no início da fila sem removê-lo.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
*   p: Ponteiro para a estrutura Patient que irá receber os dados do paciente consultado.
* Retorna:
*   1 se a consulta for bem-sucedida, 0 caso contrário.
*/
int consultPatient(PatientQueue *q, Patient *p) {
    if (isPatientQueueEmpty(q)) {
        printf("Fila de pacientes vazia!\n");
        return 0;
    }
    *p = q->patients[q->front];
    return 1;
}

/*
* Função: displayPatients
* Descrição: Exibe todos os pacientes na fila em ordem de atendimento.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
* Retorna:
*   void
*/
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

/*
* Função: countCriticalPatients (FUNCIONALIDADE EXTRA)
* Descrição: Conta o número de pacientes na fila que estão em estado crítico (prioridade 3).
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
* Retorna:
*   O número de pacientes com prioridade 3.
*/
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

/*
* Função: searchPatientByName (COMPLEMENTO)
* Descrição: Busca um paciente na fila por uma string (nome ou parte do nome).
* Parâmetros:
*   q: A fila de pacientes a ser pesquisada.
*   nameToSearch: A string contendo o nome ou parte do nome a ser buscado.
* Retorna:
*   1 se pelo menos um paciente for encontrado, 0 caso contrário.
*/
int searchPatientByName(PatientQueue *q, char *nameToSearch) {
    if (isPatientQueueEmpty(q)) {
        printf("Fila de pacientes vazia!\n");
        return 0;
    }

    int found = 0;
    printf("\n--- Pacientes encontrados com o nome '%s' ---\n", nameToSearch);

    for (int i = 0; i < q->count; i++) {
        int index = (q->front + i) % MAX;
        if (strstr(q->patients[index].name, nameToSearch) != NULL) {
            printf("ID: %d | Nome: %s | Prioridade: %d | Sintomas: %s\n",
                   q->patients[index].id,
                   q->patients[index].name,
                   q->patients[index].priority,
                   q->patients[index].symptoms);
            found = 1;
        }
    }

    if (!found) {
        printf("Nenhum paciente encontrado.\n");
    }
    return found;
}


/*
* Função: sortPatientQueueByPriority (COMPLEMENTO)
* Descrição: Ordena a fila de pacientes com base na prioridade, colocando os pacientes com maior prioridade primeiro.
* Parâmetros:
*   q: A fila de pacientes a ser ordenada.
* Retorna:
*   void
*/
void sortPatientQueueByPriority(PatientQueue *q) {
    if (isPatientQueueEmpty(q) || q->count == 1) {
        printf("A fila tem 0 ou 1 paciente. Nao e necessario ordenar.\n");
        return;
    }

    for (int i = 0; i < q->count - 1; i++) {
        for (int j = 0; j < q->count - i - 1; j++) {
            int current_index = (q->front + j) % MAX;
            int next_index = (q->front + j + 1) % MAX;
            
    
            if (q->patients[current_index].priority < q->patients[next_index].priority) {
                Patient temp = q->patients[current_index];
                q->patients[current_index] = q->patients[next_index];
                q->patients[next_index] = temp;
            }
        }
    }

    printf("A fila de pacientes foi ordenada por prioridade!\n");
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

// stack functions

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* Função: initializeMedicalRecordStack
* Descrição: Inicializa a pilha de prontuários, configurando o ponteiro de topo.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários a ser inicializada.
* Retorna:
*   void
*/
void initializeMedicalRecordStack(MedicalRecordStack *s) {
    s->top = -1;
}

/*
* Função: isMedicalRecordStackEmpty
* Descrição: Verifica se a pilha de prontuários está vazia.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários.
* Retorna:
*   1 se a pilha estiver vazia, 0 caso contrário.
*/
int isMedicalRecordStackEmpty(MedicalRecordStack *s) {
    return (s->top == -1);
}

/*
* Função: isMedicalRecordStackFull
* Descrição: Verifica se a pilha de prontuários está cheia.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários.
* Retorna:
*   1 se a pilha estiver cheia, 0 caso contrário.
*/
int isMedicalRecordStackFull(MedicalRecordStack *s) {
    return (s->top == MAX - 1);
}

/*
* Função: searchMrId
* Descrição: Busca um prontuário na pilha por um ID específico.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários.
*   id: O ID do prontuário a ser buscado.
* Retorna:
*   1 se o ID for encontrado, 0 caso contrário.
*/
int searchMrId(MedicalRecordStack *s, int id) {
    if (isMedicalRecordStackEmpty(s)) {
        return 0; // The stack is empty, so the ID is not there.
    }
    
    // Iterate through the stack from top to bottom
    for (int i = s->top; i >= 0; i--) {
        if (s->records[i].id == id) {
            return 1; // Found the ID, return true
        }
    }
    return 0; // Did not find the ID, return false
}

/*
* Função: insertMr
* Descrição: Insere um novo prontuário no topo da pilha.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários.
*   r: A estrutura MedicalRecord contendo os dados do novo prontuário.
* Retorna:
*   1 se a inserção for bem-sucedida, 0 caso contrário.
*/
int insertMr(MedicalRecordStack *s, MedicalRecord r) {
    if (isMedicalRecordStackFull(s)) {
        printf("Erro: pilha de prontuarios cheia!\n");
        return 0;
    }

    if (searchMrId(s, r.id)) {
        printf("Erro: Ja existe um prontuario com o ID %d na pilha.\n", r.id);
        return 0;
    }
    
    s->records[++(s->top)] = r;
    return 1;
}

/*
* Função: removeMr
* Descrição: Remove o prontuário que está no topo da pilha.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários.
*   r: Ponteiro para a estrutura MedicalRecord que irá receber os dados do prontuário removido.
* Retorna:
*   1 se a remoção for bem-sucedida, 0 caso contrário.
*/
int removeMr(MedicalRecordStack *s, MedicalRecord *r) {
    if (isMedicalRecordStackEmpty(s)) {
        printf("Erro: pilha de prontuarios vazia!\n");
        return 0;
    }
    *r = s->records[(s->top)--];
    return 1;
}

/*
* Função: consultLastMr
* Descrição: Consulta os dados do prontuário que está no topo da pilha sem removê-lo.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários.
*   r: Ponteiro para a estrutura MedicalRecord que irá receber os dados do prontuário consultado.
* Retorna:
*   1 se a consulta for bem-sucedida, 0 caso contrário.
*/
int consultLastMr(MedicalRecordStack *s, MedicalRecord *r) {
    if (isMedicalRecordStackEmpty(s)) {
        printf("Nenhum prontuário na pilha!\n");
        return 0;
    }
    *r = s->records[s->top];
    return 1;
}

/*
* Função: displayMr
* Descrição: Exibe todos os prontuários armazenados na pilha, do topo para a base.
* Parâmetros:
*   s: Ponteiro para a pilha de prontuários.
* Retorna:
*   void
*/
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

/*
* Função: reverseMr (FUNCIONALIDADE EXTRA)
* Descrição: Inverte a ordem dos prontuários na pilha.
* Parâmetros:
*   s: A pilha de prontuários.
* Retorna:
*   void
*/
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

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* Função: initializeDoctorList
* Descrição: Inicializa a lista de médicos, configurando o ponteiro de início.
* Parâmetros:
*   list: Ponteiro para a lista de médicos.
* Retorna:
*   void
*/
void initializeDoctorList(DoctorList *list) {
    list->start = NULL;
}

/*
* Função: searchDoctor
* Descrição: Busca um médico na lista por um ID específico.
* Parâmetros:
*   list: Ponteiro para a lista de médicos.
*   id: O ID do médico a ser buscado.
* Retorna:
*   Um ponteiro para a estrutura Doctor se o médico for encontrado, NULL caso contrário.
*/
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

/*
* Função: insertDoctor
* Descrição: Insere um novo médico no início da lista.
* Parâmetros:
*   list: Ponteiro para a lista de médicos.
*   d: A estrutura Doctor contendo os dados do novo médico.
* Retorna:
*   void
*/
void insertDoctor(DoctorList *list, Doctor d) {

    if (searchDoctor(list, d.id) != NULL) {
        printf("Erro: Medico com o ID %d ja existe na lista.\n", d.id);
        return; // Retorna sem inserir o médico
    }

    Doctor *newDoctor = (Doctor*)malloc(sizeof(Doctor));
    *newDoctor = d;
    newDoctor->next = list->start;
    list->start = newDoctor;
    printf("Medico inserido com sucesso!\n");
}

/*
* Função: removeDoctor
* Descrição: Remove um médico da lista com base em um ID específico.
* Parâmetros:
*   list: Ponteiro para a lista de médicos.
*   id: O ID do médico a ser removido.
* Retorna:
*   1 se a remoção for bem-sucedida, 0 caso contrário.
*/
int removeDoctor(DoctorList *list, int id) {
    Doctor *current = list->start;
    Doctor *prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Medico com ID %d não encontrado.\n", id);
        return 0;
    }

    if (prev == NULL) { // remove in the begin
        list->start = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Medico removido com sucesso!\n");
    return 1;
}

/*
* Função: displayDoctors
* Descrição: Exibe todos os médicos cadastrados na lista.
* Parâmetros:
*   list: Ponteiro para a lista de médicos.
* Retorna:
*   void
*/
void displayDoctors(DoctorList *list) {
    if (list->start == NULL) {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    printf("\n--- Lista de Médicos ---\n");
    Doctor *current = list->start;
    while (current != NULL) {
        printf("ID: %d | Nome: %s | Especialidade: %s | Experiencia: %d anos\n",
               current->id,
               current->name,
               current->specialty,
               current->experience);
        current = current->next;
    }
}

/*
* Função: searchSpecDoctor
* Descrição: Busca e exibe médicos com uma especialidade específica na lista.
* Parâmetros:
*   list: A lista de médicos.
*   specialty: A string contendo a especialidade a ser buscada.
* Retorna:
*   void
*/
void searchSpecDoctor(DoctorList *list, char *specialty) {
    int found = 0;
    Doctor *current = list->start;
    while (current != NULL) {
        if (strcmp(current->specialty, specialty) == 0) {
            printf("ID: %d | Nome: %s | Especialidade: %s | Experiencia: %d anos\n",
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

/*
* Função: menu
* Descrição: Exibe o menu principal e gerencia a interação do usuário com as estruturas de dados.
* Parâmetros:
*   q: Ponteiro para a fila de pacientes.
*   s: Ponteiro para a pilha de prontuários.
*   l: Ponteiro para a lista de médicos.
* Retorna:
*   void
*/
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
        case 1: {
            int queueOption;
            do{
            printf("\n========================================\n");
            printf("\n            FILA DE PACIENTES\n");
            printf("\n========================================\n");

            printf("\n1. Inserir paciente na fila"
                    "\n2. Atender (remover paciente da fila)"
                    "\n3. Consultar primeiro paciente da fila"
                    "\n4. Exibir todos os pacientes na fila"
                    "\n5. [Complemento] Buscar paciente por nome ou parte do nome"
                    "\n6. [Complemento] Ordenar por prioridade"
                    "\n7. [Operacao adicional] Contar pacientes em estado critico"
                    "\n8. Voltar ao menu principal\n"
                    "\n========================================\n");

                    printf("Digite a opcao desejada: ");
                    scanf("%d", &queueOption);

                    switch (queueOption)
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
                        char nameToSearch[50];
                        printf("\nDigite o nome ou parte do nome do paciente: ");
                        scanf(" %[^\n]", nameToSearch);
                        searchPatientByName(q, nameToSearch);
                        break;
                    }
                    case 6: {
                        sortPatientQueueByPriority(q);
                        break;
                    }
                    case 7: {
                        int criticalCount = countCriticalPatients(q);
                        printf("\nNumero de pacientes no estado critico: %d", criticalCount);
                        break;
                    }
                    case 8: {
                        printf("Voltando ao menu principal");
                        break;
                    }
                    default:
                        printf("Opcao invalida, tente novamente!");
                        break;
                    }
                }while(queueOption != 8);
            break;
            }

        case 2: {
            int stackOption;

            do{
            printf("\n========================================\n");
            printf("\n          PILHA DE PRONTUARIOS\n");
            printf("\n========================================\n");
            printf("\n1. Inserir prontuario (push)"
                    "\n2. Remover prontuario (pop)"
                    "\n3. Consultar ultimo prontuario (topo da pilha)"
                    "\n4. Exibir todos os prontuarios"
                    "\n5. [Operacao adicional] Inverter ordem da pilha"
                    "\n6. Voltar ao menu principal\n"
                    "\n========================================\n");

                    printf("Digite a opcao desejada: ");
                    scanf("%d", &stackOption);

                    switch (stackOption)
                    {
                    case 1: {
                        MedicalRecord newRecord;

                        printf("\nDigite o ID do paciente: ");
                        scanf("%d", &newRecord.id);

                        printf("\nDigite o nome do paciente: ");
                        scanf(" %[^\n]", newRecord.patientName);

                        printf("\nDigite o diagnostico do paciente: ");
                        scanf(" %[^\n]", newRecord.diagnosis);

                        printf("\nDigite o tratamento: ");
                        scanf(" %[^\n]", newRecord.treatment);

                        if(insertMr(s, newRecord)){
                            printf("\nProntuario inserido na pilha com sucesso!!");
                        }
                        break;
                    }
                    case 2: {
                        MedicalRecord removedMr;

                        if(removeMr(s, &removedMr)){
                            printf("Prontuario removido:\n");
                            printf("ID: %d | Nome: %s | Diagnostico: %s | Tratamento: %s\n",
                            removedMr.id, removedMr.patientName, removedMr.diagnosis, removedMr.treatment);                           
                        }
                        break;
                    }
                    case 3: {
                        MedicalRecord topRecord;
                        if(consultLastMr(s, &topRecord)){
                            printf("Prontuario que esta no topo:\n");
                            printf("ID: %d | Nome: %s | Diagnostico: %s | Tratamento: %s\n",
                            topRecord.id, topRecord.patientName, topRecord.diagnosis, topRecord.treatment);
                        }
                        break;
                    }
                    case 4: {
                        displayMr(s);
                        break;
                    }    
                    case 5: {
                        reverseMr(s);
                        break;
                    }
                    case 6: {
                        printf("Voltando ao menu principal");
                        break;
                    }
                    default:
                        printf("Opcao invalida, tente novamente!!");
                        break;
                    }
                }while(stackOption != 6);

            break;
                }
        case 3: {
            int listOption;
            
            do{
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
                    scanf("%d", &listOption);

                    switch (listOption)
                    {
                    case 1: {
                        Doctor newDoctor;

                        printf("\nDigite o ID do medico: ");
                        scanf("%d", &newDoctor.id);

                        printf("\nDigite o nome do medico: ");
                        scanf(" %[^\n]", newDoctor.name);

                        printf("\nDigite a especialidade do medico: ");
                        scanf(" %[^\n]", newDoctor.specialty);

                        printf("\nDigite os anos de experiencia do medico: ");
                        scanf("%d", &newDoctor.experience);

                        insertDoctor(l, newDoctor);
                        break;
                    }
                    case 2: {
                        int idToRemove;

                        printf("\nDigite o id do medico a ser removido: ");
                        scanf("%d", &idToRemove);

                        removeDoctor(l, idToRemove);
                        
                        break;
                    }
                    case 3: {
                        int idToSearch;

                        printf("Digite o ID do medico a ser consultado: ");
                        scanf("%d", &idToSearch);
                        Doctor *foundDoctor = searchDoctor(l, idToSearch);
                        if (foundDoctor != NULL) {
                            printf("\nMedico encontrado:\n");
                            printf("ID: %d | Nome: %s | Especialidade: %s | Experiencia: %d anos\n",
                                foundDoctor->id, foundDoctor->name, foundDoctor->specialty, foundDoctor->experience);
                        } else {
                            printf("Medico com ID %d nao encontrado.\n", idToSearch);
                        
                        }
                        break;
                    }
                    case 4: {
                        displayDoctors(l);   
                        break;
                    }
                    case 5: { 
                        char searchSpecialty[30];
                        printf("\nDigite a especialidade do medico a ser consultado: ");
                        scanf(" %[^\n]", searchSpecialty);

                        searchSpecDoctor(l, searchSpecialty);

                        break;
                    }
                    case 6: {
                        printf("Voltando ao menu");
                        break;
                    }

                    default:
                        printf("Opcao invalida, tente novamente!!");
                        break;
                    }
                }while(listOption != 6);
            break;
                }            
        default:
            break;
        }
        
    } while (option!=0);
    


}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
* Função: main
* Descrição: Função principal do programa. Inicializa as estruturas de dados e chama a função de menu.
* Parâmetros:
*   Nenhum.
* Retorna:
*   0 ao finalizar a execução.
*/
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
// Bibliotecas utilizadas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Definição de constantes
#define MAX 100

// Definição das structs
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
} Prescription;

typedef struct {
    int id;
    char name[50];
    char specialty[50];
    int experience;
    struct Doctor *next;
} Doctor;

// Definição das structs Stack (pilha), Queue (fila) e List (lista)
typedef struct {
    Patient patients[MAX];
    int front;
    int rear;
    int count;
} PatientQueue;

typedef struct {
    Prescription records[MAX];
    int top;
} PrescriptionStack;

typedef struct {
    Doctor *start;
} DoctorList;

// Definição das funções da fila de pacientes
void initializePatientQueue(PatientQueue *queue) {
    /*
     * Função: initializePatientQueue
     * Descrição: Inicializa a fila de pacientes, configurando os ponteiros de início e fim e o contador.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes a ser inicializada.
     * Retorna:
     *   void
     */

    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;
}

int isPatientQueueEmpty(PatientQueue *queue) {
    /*
     * Função: isPatientQueueEmpty
     * Descrição: Verifica se a fila de pacientes está vazia.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     * Retorna:
     *   1 se a fila estiver vazia, 0 caso contrário.
     */

    return (queue->count == 0);
}

int searchPatientId(PatientQueue *queue, int id) {
    /*
     * Função: searchPatientId
     * Descrição: Busca um paciente na fila por um ID específico.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     *   id: O ID do paciente a ser buscado.
     * Retorna:
     *   1 se o ID for encontrado, 0 caso contrário.
     */

    if (isPatientQueueEmpty(queue)) {
        return 0;
    }

    for (int i = 0; i < queue->count; i++) {
        int index = (queue->front + i) % MAX;

        if (queue->patients[index].id == id) {
            return 1;
        }
    }
    return 0;
}

int isPatientQueueFull(PatientQueue *queue) {
    /*
     * Função: isPatientQueueFull
     * Descrição: Verifica se a fila de pacientes está cheia.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     * Retorna:
     *   1 se a fila estiver cheia, 0 caso contrário.
     */

    return (queue->count == MAX);
}

int insertPatient(PatientQueue *queue, Patient patient) {
    /*
     * Função: insertPatient
     * Descrição: Insere um novo paciente no final da fila.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     *   patient: A estrutura Patient contendo os dados do novo paciente.
     * Retorna:
     *   1 se a inserção for bem-sucedida, 0 caso contrário.
     */

    if (isPatientQueueFull(queue)) {
        printf("<* Fila de pacientes cheia! *>\n");
        return 0;
    }

    if (searchPatientId(queue, patient.id)) {
        printf("<* Paciente ja existente! *>\n");
        return 0;
    }

    queue->patients[queue->rear] = patient;
    queue->rear = (queue->rear + 1) % MAX;
    queue->count++;
    return 1;
}

int attendPatient(PatientQueue *queue, Patient *patient) {
    /*
     * Função: attendPatient
     * Descrição: Remove o paciente que está no início da fila (atende).
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     *   patient: Ponteiro para a estrutura Patient que irá receber os dados do paciente removido.
     * Retorna:
     *   1 se a remoção for bem-sucedida, 0 caso contrário.
     */

    if (isPatientQueueEmpty(queue)) {
        printf("<* Fila de pacientes vazia! *>\n");
        return 0;
    }

    *patient = queue->patients[queue->front];
    queue->front = (queue->front + 1) % MAX;
    queue->count--;
    return 1;
}

int consultPatient(PatientQueue *queue, Patient *patient) {
    /*
     * Função: consultPatient
     * Descrição: Consulta os dados do paciente que está no início da fila sem removê-lo.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     *   patient: Ponteiro para a estrutura Patient que irá receber os dados do paciente consultado.
     * Retorna:
     *   1 se a consulta for bem-sucedida, 0 caso contrário.
     */

    if (isPatientQueueEmpty(queue)) {
        printf("<* Fila de pacientes vazia! *>\n");
        return 0;
    }

    *patient = queue->patients[queue->front];
    return 1;
}

void displayPatients(PatientQueue *queue) {
    /*
     * Função: displayPatients
     * Descrição: Exibe todos os pacientes na fila em ordem de atendimento.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     * Retorna:
     *   void
     */

    if (isPatientQueueEmpty(queue)) {
        printf("<* Fila de pacientes vazia! *>\n");
        return;
    }

    printf(
        "\n+--------------------------------+"
        "\n|        FILA DE PACIENTES       |"
        "\n+--------------------------------+"
        "\n"
    );

    for (int i = 0; i < queue->count; i++) {
        int index = (queue->front + i) % MAX;

        printf(
            "\nPaciente %s:"
            "\nID: %d"
            "\nPrioridade: %d"
            "\nSintomas: %s"
            "\n",
            queue->patients[index].name,
            queue->patients[index].id,
            queue->patients[index].priority,
            queue->patients[index].symptoms
        );
    }
}

int countCriticalPatients(PatientQueue *queue) {
    /*
     * Função: countCriticalPatients (COMPLEMENTO)
     * Descrição: Conta o número de pacientes na fila que estão em estado crítico (prioridade 3).
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     * Retorna:
     *   O número de pacientes com prioridade 3.
     */

    if (isPatientQueueEmpty(queue)) {
        return 0;
    }

    int count = 0;

    for (int i = 0; i < queue->count; i++) {
        int index = (queue->front + i) % MAX;

        if (queue->patients[index].priority == 3) {
            count++;
        }
    }

    return count;
}

int searchPatientByName(PatientQueue *queue, char *patientName) {
    /*
     * Função: searchPatientByName (COMPLEMENTO)
     * Descrição: Busca um paciente na fila por uma string (nome ou parte do nome).
     * Parâmetros:
     *   queue: A fila de pacientes a ser pesquisada.
     *   patientName: A string contendo o nome ou parte do nome a ser buscado.
     * Retorna:
     *   1 se pelo menos um paciente for encontrado, 0 caso contrário.
     */

    if (isPatientQueueEmpty(queue)) {
        printf("<* Fila de pacientes vazia! *>\n");
        return 0;
    }

    int found = 0;

    printf(
        "\n+-------------------------------+"
        "\n|           RESULTADOS          |"
        "\n+-------------------------------+"
        "\n"
    );

    for (int i = 0; i < queue->count; i++) {
        int index = (queue->front + i) % MAX;

        if (strstr(queue->patients[index].name, patientName) != NULL) {
            printf(
                "\nPaciente %s:"
                "\nID: %d"
                "\nPrioridade: %d"
                "\nSintomas: %s"
                "\n",
                queue->patients[index].name,
                queue->patients[index].id,
                queue->patients[index].priority,
                queue->patients[index].symptoms
            );

            found = 1;
        }
    }

    if (!found) {
        printf("<* Nenhum paciente encontrado! *>\n");
    }

    return found;
}

void sortPatientQueueByPriority(PatientQueue *queue) {
    /*
     * Função: sortPatientQueueByPriority (COMPLEMENTO)
     * Descrição: Ordena a fila de pacientes com base na prioridade, colocando os pacientes com maior prioridade (3) primeiro.
     * Parâmetros:
     *   queue: A fila de pacientes a ser ordenada.
     * Retorna:
     *   void
     */

    if (isPatientQueueEmpty(queue) || queue->count == 1) {
        printf("<* Nao e necessario ordenar! *>\n");
        return;
    }

    for (int i = 0; i < queue->count - 1; i++) {
        for (int j = 0; j < queue->count - i - 1; j++) {
            int nextIndex = (queue->front + j + 1) % MAX;
            int currentIndex = (queue->front + j) % MAX;

            if (queue->patients[currentIndex].priority < queue->patients[nextIndex].priority) {
                Patient temp = queue->patients[currentIndex];

                queue->patients[currentIndex] = queue->patients[nextIndex];
                queue->patients[nextIndex] = temp;
            }
        }
    }

    printf("<* A fila foi ordenada por prioridade! *>\n");
}

// Definição das funções da pilha de prontuários médicos
void initializePrescriptionStack(PrescriptionStack *stack) {
    /*
     * Função: initializePrescriptionStack
     * Descrição: Inicializa a pilha de prontuários, configurando o ponteiro de topo.
     * Parâmetros:
     *   s: Ponteiro para a pilha de prontuários a ser inicializada.
     * Retorna:
     *   void
     */

    stack->top = -1;
}

int isPrescriptionStackEmpty(PrescriptionStack *stack) {
    /*
     * Função: isPrescriptionStackEmpty
     * Descrição: Verifica se a pilha de prontuários está vazia.
     * Parâmetros:
     *   stack: Ponteiro para a pilha de prontuários.
     * Retorna:
     *   1 se a pilha estiver vazia, 0 caso contrário.
     */

    return (stack->top == -1);
}

int isPrescriptionStackFull(PrescriptionStack *stack) {
    /*
     * Função: isPrescriptionStackFull
     * Descrição: Verifica se a pilha de prontuários está cheia.
     * Parâmetros:
     *   stack: Ponteiro para a pilha de prontuários.
     * Retorna:
     *   1 se a pilha estiver cheia, 0 caso contrário.
     */

    return (stack->top == MAX - 1);
}

int searchPrescriptionId(PrescriptionStack *stack, int id) {
    /*
     * Função: searchPrescriptionId
     * Descrição: Busca um prontuário na pilha por um ID específico.
     * Parâmetros:
     *   stack: Ponteiro para a pilha de prontuários.
     *   id: O ID do prontuário a ser buscado.
     * Retorna:
     *   1 se o ID for encontrado, 0 caso contrário.
     */

    if (isPrescriptionStackEmpty(stack)) {
        return 0;
    }

    for (int i = stack->top; i >= 0; i--) {
        if (stack->records[i].id == id) {
            return 1;
        }
    }

    return 0;
}

int insertPrescription(PrescriptionStack *stack, Prescription prescription) {
    /*
     * Função: insertPrescription
     * Descrição: Insere um novo prontuário no topo da pilha.
     * Parâmetros:
     *   stack: Ponteiro para a pilha de prontuários.
     *   prescription: A estrutura MedicalRecord contendo os dados do novo prontuário.
     * Retorna:
     *   1 se a inserção for bem-sucedida, 0 caso contrário.
     */

    if (isPrescriptionStackFull(stack)) {
        printf("<* Pilha de prontuarios cheia! *>\n");
        return 0;
    }

    if (searchPrescriptionId(stack, prescription.id)) {
        printf("<* Prontuario ja existente! *>\n");
        return 0;
    }

    stack->records[++(stack->top)] = prescription;
    return 1;
}

int removePrescription(PrescriptionStack *stack, Prescription *prescription) {
    /*
     * Função: removePrescription
     * Descrição: Remove o prontuário que está no topo da pilha.
     * Parâmetros:
     *   stack: Ponteiro para a pilha de prontuários.
     *   prescription: Ponteiro para a estrutura MedicalRecord que irá receber os dados do prontuário removido.
     * Retorna:
     *   1 se a remoção for bem-sucedida, 0 caso contrário.
     */

    if (isPrescriptionStackEmpty(stack)) {
        printf("<* Nenhum prontuario cadastrado! *>\n");
        return 0;
    }

    *prescription = stack->records[(stack->top)--];
    return 1;
}

int consultLastPrescription(PrescriptionStack *stack, Prescription *prescription) {
    /*
     * Função: consultLastPrescription
     * Descrição: Consulta os dados do prontuário que está no topo da pilha sem removê-lo.
     * Parâmetros:
     *   stack: Ponteiro para a pilha de prontuários.
     *   prescription: Ponteiro para a estrutura MedicalRecord que irá receber os dados do prontuário consultado.
     * Retorna:
     *   1 se a consulta for bem-sucedida, 0 caso contrário.
     */

    if (isPrescriptionStackEmpty(stack)) {
        printf("<* Nenhum prontuario encontrado! *>\n");
        return 0;
    }

    *prescription = stack->records[stack->top];
    return 1;
}

void displayPrescription(PrescriptionStack *stack) {
    /*
     * Função: displayPrescription
     * Descrição: Exibe todos os prontuários armazenados na pilha, do topo para a base.
     * Parâmetros:
     *   stack: Ponteiro para a pilha de prontuários.
     * Retorna:
     *   void
     */

    if (isPrescriptionStackEmpty(stack)) {
        printf("<* Nenhum prontuario cadastrado! *>\n");
        return;
    }

    printf(
        "\n+--------------------------------+"
        "\n|      PILHA DE PRONTUARIOS      |"
        "\n+--------------------------------+"
        "\n"
    );

    for (int i = stack->top; i >= 0; i--) {
        printf(
            "\nMedico %s:"
            "\nID: %d"
            "\nPaciente: %s"
            "\nDiagnostico: %d"
            "\nTratamento: %s"
            "\n",
            stack->records[i].id,
            stack->records[i].patientName,
            stack->records[i].diagnosis,
            stack->records[i].treatment
        );
    }
}

void reversePrescription(PrescriptionStack *stack) {
    /*
     * Função: reversePrescription (COMPLEMENTO)
     * Descrição: Inverte a ordem dos prontuários na pilha.
     * Parâmetros:
     *   stack: A pilha de prontuários.
     * Retorna:
     *   void
     */

    if (isPrescriptionStackEmpty(stack)) {
        printf("<* A pilha esta vazia! *>\n");
        return;
    }

    int i = 0, j = stack->top;

    while (i < j) {
        Prescription temp = stack->records[i];
        stack->records[i] = stack->records[j];
        stack->records[j] = temp;
        i++;
        j--;
    }

    printf("<* A pilha foi invertida! *>\n");
}

// Definição das funções da lista de médicos
void initializeDoctorList(DoctorList *list) {
    /*
     * Função: initializeDoctorList
     * Descrição: Inicializa a lista de médicos, configurando o ponteiro de início.
     * Parâmetros:
     *   list: Ponteiro para a lista de médicos.
     * Retorna:
     *   void
     */

    list->start = NULL;
}

Doctor* searchDoctor(DoctorList *list, int id) {
    /*
     * Função: searchDoctor
     * Descrição: Busca um médico na lista por um ID específico.
     * Parâmetros:
     *   list: Ponteiro para a lista de médicos.
     *   id: O ID do médico a ser buscado.
     * Retorna:
     *   Um ponteiro para a estrutura Doctor se o médico for encontrado, NULL caso contrário.
     */

    Doctor *current = list->start;

    while (current != NULL) {
        if (current->id == id) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void insertDoctor(DoctorList *list, Doctor doctor) {
    /*
     * Função: insertDoctor
     * Descrição: Insere um novo médico no início da lista.
     * Parâmetros:
     *   list: Ponteiro para a lista de médicos.
     *   doctor: A estrutura Doctor contendo os dados do novo médico.
     * Retorna:
     *   void
     */

    if (searchDoctor(list, doctor.id) != NULL) {
        printf("<* Medico ja existente! *>\n");
        return;
    }

    Doctor *newDoctor = (Doctor*)malloc(sizeof(Doctor));
    *newDoctor = doctor;
    newDoctor->next = list->start;
    list->start = newDoctor;

    printf("<* Medico inserido com sucesso! *>\n");
}

int removeDoctor(DoctorList *list, int id) {
    /*
     * Função: removeDoctor
     * Descrição: Remove um médico da lista com base em um ID específico.
     * Parâmetros:
     *   list: Ponteiro para a lista de médicos.
     *   id: O ID do médico a ser removido.
     * Retorna:
     *   1 se a remoção for bem-sucedida, 0 caso contrário.
     */

    Doctor *current = list->start;
    Doctor *prev = NULL;

    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("<* Medico nao econtrado! *>\n");
        return 0;
    }

    if (prev == NULL) {
        list->start = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);

    printf("<* Medico removido com sucesso! *>\n");
    return 1;
}

void displayDoctors(DoctorList *list) {
    /*
     * Função: displayDoctors
     * Descrição: Exibe todos os médicos cadastrados na lista.
     * Parâmetros:
     *   list: Ponteiro para a lista de médicos.
     * Retorna:
     *   void
     */

    if (list->start == NULL) {
        printf("<* Nenhum medico cadastrado! *>\n");
        return;
    }

    printf(
        "\n+--------------------------------+"
        "\n|        LISTA DE MEDICOS        |"
        "\n+--------------------------------+"
        "\n"
    );

    Doctor *current = list->start;

    while (current != NULL) {
        printf(
            "\nMedico %s:"
            "\nID: %d"
            "\nEspecialidade: %s"
            "\nExperiencia: %d anos"
            "\n",
            current->name,
            current->id,
            current->specialty,
            current->experience
        );

        current = current->next;
    }
}

void searchSpecialtyDoctor(DoctorList *list, char *specialty) {
    /*
     * Função: searchSpecialtyDoctor
     * Descrição: Busca e exibe médicos com uma especialidade específica na lista.
     * Parâmetros:
     *   list: A lista de médicos.
     *   specialty: A string contendo a especialidade a ser buscada.
     * Retorna:
     *   void
     */

    int found = 0;

    Doctor *current = list->start;

    while (current != NULL) {
        if (strcmp(current->specialty, specialty) == 0) {
            printf(
                "\n+------------------------------+"
                "\n|           RESULTADO          |"
                "\n+------------------------------+"
                "\n"
                "\nMedico encontrado:"
                "\nID: %d"
                "\nNome: %s"
                "\nEspecialidade: %s"
                "\nExperiencia: %d anos",
                current->id,
                current->name,
                current->specialty,
                current->experience
            );

            found = 1;
        }

        current = current->next;
    }

    if (!found) {
        printf("<* Medico nao econtrado! *>\n");
    }
}

//  Definição da função do menu principal
void menu(PatientQueue *queue, PrescriptionStack *stack, DoctorList *list){
    /*
     * Função: menu
     * Descrição: Exibe o menu principal e gerencia a interação do usuário com as estruturas de dados.
     * Parâmetros:
     *   queue: Ponteiro para a fila de pacientes.
     *   stack: Ponteiro para a pilha de prontuários.
     *   list: Ponteiro para a lista de médicos.
     * Retorna:
     *   void
     */

    int option;

    do {
        printf(
            "\n+---------------------------+"
            "\n|         HOSPITECH         |"
            "\n+---------------------------+"
            "\n"
            "\n-> Escolha o setor"
            "\n"
            "\n  > 1. Fila de Pacientes"
            "\n  > 2. Pilha de Prontuarios"
            "\n  > 3. Lista de Medicos"
            "\n  > 4. Sair"
            "\n============================="
            "\nSetor >> "
        );
        scanf("%d", &option);

        switch (option) {
            case 1: {
                int queueOption;

                do {
                    printf(
                        "\n+-------------------------------+"
                        "\n|       FILA DE PACIENTES       |"
                        "\n+-------------------------------+"
                        "\n"
                        "\n-> Escolha a operacao"
                        "\n"
                        "\n  > 1. Inserir paciente"
                        "\n  > 2. Atender paciente"
                        "\n  > 3. Consultar 1 paciente"
                        "\n  > 4. Exibir pacientes"
                        "\n  > 5. Buscar paciente"
                        "\n  > 6. Ordenar por prioridade"
                        "\n  > 7. Contar pacientes criticos"
                        "\n  > 8. Voltar ao menu"
                        "\n================================="
                        "\nOperacao >> "
                    );
                    scanf("%d", &queueOption);

                    switch (queueOption) {
                        case 1: {
                            Patient newPatient;

                            printf(
                                "\n+----------------------------+"
                                "\n|     ADICIONAR PACIENTE     |"
                                "\n+----------------------------+"
                                "\n"
                            );

                            printf("\nID >> ");
                            scanf("%d", &newPatient.id);

                            printf("Nome >> ");
                            scanf(" %[^\n]", newPatient.name);

                            printf(
                                "(1. Normal, 2. Medio, 3. Emergencia)"
                                "\nPrioridade >> "
                            );
                            scanf("%d", &newPatient.priority);

                            printf("Sintomas >> ");
                            scanf(" %[^\n]", newPatient.symptoms);

                            if(insertPatient(queue, newPatient)){
                                printf("<* Paciente inserido com sucesso! *>\n");
                            }

                            break;
                        }
                        case 2: {
                            Patient attendedPatient;

                            if(attendPatient(queue, &attendedPatient)){
                                printf(
                                    "\n+---------------------------+"
                                    "\n|        ATENDIMENTO        |"
                                    "\n+---------------------------+"
                                    "\n"
                                    "\nPaciente %s atendido"
                                    "\nID: %d"
                                    "\nPrioridade: %d"
                                    "\nSintomas: %s"
                                    "\n",
                                    attendedPatient.name,
                                    attendedPatient.id,
                                    attendedPatient.priority,
                                    attendedPatient.symptoms
                                );
                            }

                            break;
                        }
                        case 3: {
                            Patient firstPatient;

                            if(consultPatient(queue, &firstPatient)){
                                printf(
                                    "\n+----------------------------+"
                                    "\n|          CONSULTA          |"
                                    "\n+----------------------------+"
                                    "\n"
                                    "\n1 paciente da fila"
                                    "\nID: %d"
                                    "\nNome: %s"
                                    "\nPrioridade: %d"
                                    "\nSintomas: %s",
                                    firstPatient.id,
                                    firstPatient.name,
                                    firstPatient.priority,
                                    firstPatient.symptoms
                                );
                            }

                            break;
                        }
                        case 4: {
                            displayPatients(queue);

                            break;
                        }
                        case 5: {
                            char patientName[50];

                            printf(
                                "\n+---------------------------+"
                                "\n|           BUSCA           |"
                                "\n+---------------------------+"
                                "\n"
                                "\nNome do paciente >> "
                            );
                            scanf(" %[^\n]", patientName);

                            searchPatientByName(queue, patientName);

                            break;
                        }
                        case 6: {
                            sortPatientQueueByPriority(queue);

                            break;
                        }
                        case 7: {
                            int criticalCount = countCriticalPatients(queue);

                            printf(
                                "\n+---------------------------+"
                                "\n|        ATENDIMENTO        |"
                                "\n+---------------------------+"
                                "\n"
                                "\nPacientes criticos: %d",
                                criticalCount
                            );

                            break;
                        }
                        case 8: {
                            printf(
                                "-> Retornando ao menu"
                                "\n"
                            );

                            break;
                        }
                    default:
                        printf("<* Operacao invalida! *>\n");

                        break;
                    }
                } while(queueOption != 8);
            break;
            }
            case 2: {
                int stackOption;

                do {
                    printf(
                        "\n+---------------------------+"
                        "\n|    PILHA DE PRONTUARIOS   |"
                        "\n+---------------------------+"
                        "\n"
                        "\n-> Escolha a operacao"
                        "\n"
                        "\n  > 1. Inserir prontuario"
                        "\n  > 2. Remover prontuario"
                        "\n  > 3. Ver ultimo prontuario"
                        "\n  > 4. Exibir prontuarios"
                        "\n  > 5. Inverter ordem"
                        "\n  > 6. Voltar ao menu"
                        "\n============================="
                        "\nOperacao >> "
                    );
                    scanf("%d", &stackOption);

                    switch (stackOption) {
                        case 1: {
                            Prescription newPrescription;

                            printf("\nID >> ");
                            scanf("%d", &newPrescription.id);

                            printf("Nome >> ");
                            scanf(" %[^\n]", newPrescription.patientName);

                            printf("Diagnostico >> ");
                            scanf(" %[^\n]", newPrescription.diagnosis);

                            printf("Tratamento >> ");
                            scanf(" %[^\n]", newPrescription.treatment);

                            if(insertPrescription(stack, newPrescription)){
                                printf("<* Prontuario inserido com sucesso! *>\n");
                            }

                            break;
                        }
                        case 2: {
                            Prescription removedPrescription;

                            if(removePrescription(stack, &removedPrescription)){
                                printf(
                                    "\n+----------------------------+"
                                    "\n|          DELEÇÃO           |"
                                    "\n+----------------------------+"
                                    "\n"
                                    "\nProntuario removido:"
                                    "\nID: %d"
                                    "\nNome: %s"
                                    "\nDiagnostico: %d"
                                    "\nTratamento: %s",
                                    removedPrescription.id,
                                    removedPrescription.patientName,
                                    removedPrescription.diagnosis,
                                    removedPrescription.treatment
                                );
                            }

                            break;
                        }
                        case 3: {
                            Prescription topPrescription;

                            if(consultLastPrescription(stack, &topPrescription)){
                                printf(
                                    "\n+----------------------------+"
                                    "\n|          CONSULTA          |"
                                    "\n+----------------------------+"
                                    "\n"
                                    "\nProntuario no topo"
                                    "\nID: %d"
                                    "\nNome: %s"
                                    "\nPrioridade: %d"
                                    "\nSintomas: %s",
                                    topPrescription.id,
                                    topPrescription.patientName,
                                    topPrescription.diagnosis,
                                    topPrescription.treatment
                                );
                            }

                            break;
                        }
                        case 4: {
                            displayPrescription(stack);

                            break;
                        }
                        case 5: {
                            reversePrescription(stack);

                            break;
                        }
                        case 6: {
                            printf(
                                "-> Retornando ao menu"
                                "\n"
                            );

                            break;
                        }
                    default:
                        printf("<* Operacao invalida! *>\n");

                        break;
                    }
                } while(stackOption != 6);

                break;
            }
            case 3: {
                int listOption;

                do {
                    printf(
                        "\n+-------------------------------+"
                        "\n|        LISTA DE MEDICOS       |"
                        "\n+-------------------------------+"
                        "\n"
                        "\n-> Escolha a operacao"
                        "\n"
                        "\n  > 1. Inserir medico"
                        "\n  > 2. Remover medico"
                        "\n  > 3. Consultar medico (ID)"
                        "\n  > 4. Exibir medicos"
                        "\n  > 5. Consultar medico (espec)"
                        "\n  > 6. Voltar ao menu"
                        "\n================================="
                        "\nOperacao >> "
                    );
                    scanf("%d", &listOption);

                    switch (listOption) {
                        case 1: {
                            Doctor newDoctor;

                            printf(
                                "\n+----------------------------+"
                                "\n|      ADICIONAR MEDICO      |"
                                "\n+----------------------------+"
                                "\n"
                            );

                            printf("\nID >> ");
                            scanf("%d", &newDoctor.id);

                            printf("Nome >> ");
                            scanf(" %[^\n]", newDoctor.name);

                            printf("Especialidade >> ");
                            scanf(" %[^\n]", newDoctor.specialty);

                            printf("Experiencia >> ");
                            scanf("%d", &newDoctor.experience);

                            insertDoctor(list, newDoctor);

                            break;
                        }
                        case 2: {
                            int idToRemove;

                            printf(
                                "\n+----------------------------+"
                                "\n|          DELEÇÃO           |"
                                "\n+----------------------------+"
                                "\n"
                                "\nID >> "
                            );
                            scanf("%d", &idToRemove);

                            removeDoctor(list, idToRemove);

                            break;
                        }
                        case 3: {
                            int idToSearch;

                            printf(
                                "\n+----------------------------+"
                                "\n|          CONSULTA          |"
                                "\n+----------------------------+"
                                "\n"
                                "\nID >> "
                            );
                            scanf("%d", &idToSearch);

                            Doctor *foundDoctor = searchDoctor(list, idToSearch);

                            if (foundDoctor != NULL) {
                                printf(
                                    "\n+------------------------------+"
                                    "\n|           RESULTADO          |"
                                    "\n+------------------------------+"
                                    "\n"
                                    "\nMedico encontrado:"
                                    "\nID: %d"
                                    "\nNome: %s"
                                    "\nEspecialidade: %s"
                                    "\nExperiencia: %d anos",
                                    foundDoctor->id,
                                    foundDoctor->name,
                                    foundDoctor->specialty,
                                    foundDoctor->experience
                                );
                            } else {
                                printf("<* Medico nao encontrado! *>\n");
                            }

                            break;
                        }
                        case 4: {
                            displayDoctors(list);

                            break;
                        }
                        case 5: {
                            char searchSpecialty[30];

                            printf(
                                "\n+----------------------------+"
                                "\n|          CONSULTA          |"
                                "\n+----------------------------+"
                                "\n"
                                "\nEspecialidade >> "
                            );
                            scanf(" %[^\n]", searchSpecialty);

                            searchSpecialtyDoctor(list, searchSpecialty);

                            break;
                        }
                        case 6: {
                            printf(
                                "-> Retornando ao menu"
                                "\n"
                            );

                            break;
                        }
                        default:
                            printf("<* Operacao invalida! *>\n");

                            break;
                        }
                } while(listOption != 6);

                break;
                }
            case 4: {
                printf("-> Saindo do sistema\n");

                break;
            }
            default:
                printf("<* Setor invalido! *>\n");

                break;
        }
    } while (option != 4);
}

int main(){
    /*
     * Função: main
     * Descrição: Função principal do programa. Inicializa as estruturas de dados e chama a função de menu.
     * Parâmetros:
     *   Nenhum.
     * Retorna:
     *   0 ao finalizar a execução.
     */

    PatientQueue patientQueue;
    PrescriptionStack medicalRecordStack;
    DoctorList doctorList;
    initializePatientQueue(&patientQueue);
    initializePrescriptionStack(&medicalRecordStack);
    initializeDoctorList(&doctorList);
    menu(&patientQueue, &medicalRecordStack, &doctorList);

    return 0;
}
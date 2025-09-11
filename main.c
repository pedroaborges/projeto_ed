#include <stdio.h>

void insertPatient(){}
void servePatient(){}
void consultPatient(){}
void displayPatients(){}
void countPatients(){}
void insertMr(){}
void removeMr(){}
void consultLastMr(){}
void displayMr(){}
void reverseMr(){}
void insertDoctor(){}
void removeDoctor(){}
void searchDoctor(){}
void displayDoctors(){}
void searchSpecDoctor(){}

void menu(){
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

int main(){
    menu();
}
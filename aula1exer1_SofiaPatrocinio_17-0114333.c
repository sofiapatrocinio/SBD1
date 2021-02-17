#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct car {
    char license_plate[8];
    char RENAVAM[20];
    char model[20];
    char color[10];
    char brand[10];
};

struct proprietary {
    char name[50];
    char CPF[12];
    char birth_date[11];
    struct car Car;
};

void open_file(FILE **file) {
    *file = fopen("database.txt", "a");
    if (*file == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }    
}

void show_file(FILE **file) {
    char Rows[200];
    char *result;
    *file = fopen("database.txt", "rt");
    if (*file == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    while (!feof(*file)) {
        result = fgets(Rows, 200, *file);
        if (result) {
            printf("%s", Rows);
        }
    }
    fclose(*file);
}

void delete_file(FILE **file) {
    *file = fopen("database.txt", "w");
    if (*file == NULL) {
        printf("Erro ao abrir arquivo\n");
        return;
    }
}


int verify_RENAVAM(char *RENAVAM , FILE **file){
   char Rows[200];
   char line_ren[20];
   strcat(line_ren,"RENAVAM:");
   strcat(line_ren, RENAVAM);
   *file = fopen("database.txt", "r") ;
   while (fgets(Rows , sizeof(Rows) , *file )!= NULL)
   {
      if (strstr(Rows , line_ren )!= NULL)
      {
         printf("Carro já cadastrado\n");
         return 0;
      }
   }
   fclose(*file);
   return 1;
}

void menu() {
    printf("*** CADASTRO DE AUTOMÓVEIS ***\n");
    printf("1 - CADASTRAR AUTOMÓVEL \n2 - EXIBIR AUTOMÓVEIS CADASTRADOS \n3 - APAGAR AUTOMÓVEIS CADASTRADOS \n4 - SAIR\n");
}

int main(void) {
    struct proprietary proprietary1;
    struct car car1;
    FILE *file = NULL;
    int option;
    char option_delete;

    START:
    do {
        menu();
        scanf("%d", &option);
        if (option < 0 || option > 4) {
            printf("Você deve escolher uma opção válida.\n");
        }
        switch(option){
            case 1:
                open_file(&file);

                printf("Marca do carro:\n");
                scanf("%s", car1.brand);
                printf("Modelo do carro:\n");
                scanf("%s", car1.model);
                printf("Placa do carro:\n");
                scanf("%s", car1.license_plate);
                printf("RENAVAM do carro:\n");
                scanf("%s", car1.RENAVAM);
                if(verify_RENAVAM(car1.RENAVAM, &file) == 0) {
                    goto START;
                }
                open_file(&file);
                printf("Cor do carro:\n");
                scanf("%s", car1.color);
                fprintf(file, "Carro:\nMarca:%s\nModelo:%s\nPlaca:%s\nRENAVAM:%s\nCor:%s\n", car1.brand, car1.model, car1.license_plate, car1.RENAVAM, car1.color);

                printf("Nome do(a) proprietário(a):\n");
                scanf(" %[^\n]", proprietary1.name);
                scanf("%*[^\n]"); scanf("%*c");
                printf("CPF do(a) proprietário(a):\n");
                scanf(" %s", proprietary1.CPF);
                printf("Data de nascimento do(a) proprietário(a):\n");
                scanf(" %s", proprietary1.birth_date);
                fprintf(file, "Nome do(a) proprietário(a): %s\nCPF: %s\nData de nascimento: %s\n", proprietary1.name, proprietary1.CPF, proprietary1.birth_date);
                fprintf(file, "\n");

                printf("Dados submetidos com sucesso!\n");
                fclose(file);
                goto START;

            case 2:
                show_file(&file);
                goto START;

            case 3:
                printf("Você tem certeza que deseja apagar todos dados cadastros? [s/n]\n");
                scanf(" %c", &option_delete);
                if(option_delete != 's' && option_delete != 'n') {
                    printf("Você deve escolher 's' para apagar ou 'n' para cancelar\n");
                    scanf("%c", &option_delete);
                }
                if(option_delete == 's') {
                    delete_file(&file);
                }
                 if(option_delete == 'n') {
                    goto START;
                }
        }
    } while (option != 4);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct car
{
    char license_plate[8];
    char RENAVAM[20];
    char model[20];
    char brand[10];
    char owner_CPF[12];
} Car;

typedef struct proprietary
{
    char name[50];
    char CPF[12];
} Proprietary;

int car_qty;
int proprietary_qty;

Car *cars;
Proprietary *proprietaries;

void show_file(FILE **file)
{
    char Rows[200];
    char *result;
    *file = fopen("database.txt", "rt");
    if (*file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    while (!feof(*file))
    {
        result = fgets(Rows, 200, *file);
        if (result)
        {
            printf("%s", Rows);
        }
    }
    fclose(*file);
}

void delete_file(FILE **file)
{
    *file = fopen("database.txt", "w");
    if (*file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }
}

void addProprietary(Proprietary proprietary)
{
    proprietary_qty++;
    proprietaries = realloc(proprietaries, sizeof(Proprietary) * 2 * proprietary_qty);
    proprietaries[proprietary_qty - 1] = proprietary;
    strcpy(proprietaries[proprietary_qty].name, proprietary.name);
    strcpy(proprietaries[proprietary_qty].CPF, proprietary.CPF);
}

void saveProprietary()
{
    FILE *file = fopen("database.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    for (int i = 0; i < proprietary_qty; i++)
    {
        fprintf(file, "Nome do(a) proprietário(a): %s\nCPF: %s\n", proprietaries[i].name, proprietaries[i].CPF);
    }
    fprintf(file, "\n");
    fclose(file);
}

void addCar(Car car)
{
    car_qty++;
    cars = realloc(cars, sizeof(Car) * 2 *  car_qty);
    cars[car_qty - 1] = car;
    strcpy(cars[car_qty].brand, car.brand);
    strcpy(cars[car_qty].model, car.model);
    strcpy(cars[car_qty].license_plate, car.license_plate);
    strcpy(cars[car_qty].RENAVAM, car.RENAVAM);
    strcpy(cars[car_qty].owner_CPF, car.owner_CPF);
}

void saveCar()
{
    FILE *file = fopen("database.txt", "a");
    if (file == NULL)
    {
        printf("Erro ao abrir arquivo\n");
        return;
    }
    for (int i = 0; i < car_qty; i++)
    {
        fprintf(file, "Marca do Carro:%s\nModelo:%s\nPlaca:%s\nRENAVAM:%s\nCPF do(a) proprietário(a):%s\n", cars[i].brand, cars[i].model, cars[i].license_plate, cars[i].RENAVAM, cars[i].owner_CPF);
    }
    fclose(file);
}

int compare_proprietaries(const void *a, const void *b)
{
    return strcmp(((Proprietary *)a)->CPF, ((Proprietary *)b)->CPF);
}

int compare_cars(const void *a, const void *b)
{
    return strcmp(((Car *)a)->RENAVAM, ((Car *)b)->RENAVAM);
}

void sort_array(void)
{
    qsort(proprietaries, proprietary_qty, sizeof(Proprietary), compare_proprietaries);
    qsort(cars, car_qty, sizeof(Car), compare_cars);
}

int verify_RENAVAM(char *RENAVAM)
{
    for (int i = 0; i < car_qty; i++)
    {
        if (strcmp(RENAVAM, cars[i].RENAVAM) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void menu()
{
    printf("*** CADASTRO DE AUTOMÓVEIS ***\n");
    printf("1 - CADASTRAR AUTOMÓVEL \n2 - EXIBIR AUTOMÓVEIS CADASTRADOS \n3 - APAGAR AUTOMÓVEIS CADASTRADOS \n4 - SAIR\n");
}

int main(void)
{
    Proprietary proprietary1;
    Car car1;
    FILE *file = NULL;
    int option;
    char option_delete;

START:
    do
    {
        menu();
        scanf("%d", &option);
        if (option < 0 || option > 4)
        {
            printf("Você deve escolher uma opção válida.\n");
        }
        switch (option)
        {
        case 1:
            printf("Nome do(a) proprietário(a):\n");
            scanf(" %[^\n]", proprietary1.name);
            scanf("%*[^\n]");
            scanf("%*c");
            printf("CPF do(a) proprietário(a):\n");
            scanf(" %s", proprietary1.CPF);

            printf("Marca do carro:\n");
            scanf("%s", car1.brand);
            printf("Modelo do carro:\n");
            scanf("%s", car1.model);
            printf("Placa do carro:\n");
            scanf("%s", car1.license_plate);
            printf("RENAVAM do carro:\n");
            scanf("%s", car1.RENAVAM);
            if (verify_RENAVAM(car1.RENAVAM) == 0)
            {
                printf("Carro já cadastrado\n");
                goto START;
            }
            strcpy(car1.owner_CPF, proprietary1.CPF);
            addProprietary(proprietary1);
            addCar(car1);
            sort_array();
            saveProprietary();
            saveCar();

            printf("Dados submetidos com sucesso!\n");
            goto START;

        case 2:
            show_file(&file);
            goto START;

        case 3:
            printf("Você tem certeza que deseja apagar todos dados cadastros? [s/n]\n");
            scanf(" %c", &option_delete);
            if (option_delete != 's' && option_delete != 'n')
            {
                printf("Você deve escolher 's' para apagar ou 'n' para cancelar\n");
                scanf("%c", &option_delete);
            }
            if (option_delete == 's')
            {
                delete_file(&file);
            }
            if (option_delete == 'n')
            {
                goto START;
            }
        }
    } while (option != 4);
    return 0;
}
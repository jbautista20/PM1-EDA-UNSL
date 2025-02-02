#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
PMI 1 - GRUPO 3
INTEGRANTES:
 Rio, Sofia
 Montenegro, Juan Bautista
*/

#define MAX 111
#define INFINITO 99999999
/**rango valido: 0 < dni < infinito*/

typedef struct {
    int DNI;
    char nombreApellido[81];
    char servicios[121];
    char domicilio[81];
    char mail[51];
    char telefono[31];
} Prestadores;

/*PROTOTIPOS*/
int localizarPrestador();
int insertarPrestador();
void mostrarLista();
int eliminarElemento();
void memorizacionPrevia();
int modificar();
Prestadores evocacion();

int main(){
    Prestadores lso[MAX];
    lso[0].DNI=INFINITO;
    int cantcargados=0;
    int op;
    do{
        system("cls");
        printf("------------MENU DE OPCIONES------------\n");
        printf("1. Ingreso de nuevos prestadores\n");
        printf("2. Eliminar prestadores existentes\n");
        printf("3. Modificar datos de un prestador\n");
        printf("4. Consultar la informacion completa de un prestador\n");
        printf("5. Memorizacion Previa\n");
        printf("6. Mostrar Estructura\n");
        printf("7. Salir\n");
        printf("----------------------------------------\n");
        printf("Seleccione una opcion (1-7): ");
        scanf("%d", &op);
        switch(op){
            case 1:
                if(cantcargados==MAX-1){
                    printf("No se pueden insertar mas prestadores,la lista esta llena.\n");
                    system("pause");
                }
                else{
                    system("cls");
                    printf("\nIngrese DNI: ");
                    Prestadores nuevo;
                    scanf("%d", &nuevo.DNI);
                    while(nuevo.DNI >= INFINITO || nuevo.DNI < 1){
                        printf("Error: DNI ingresado no es valido. Ingreselo nuevamente\n");
                        scanf("%d", &nuevo.DNI);
                    }
                    printf("Ingrese nombre y apellido: ");
                    scanf(" %[^\n]", nuevo.nombreApellido);
                    printf("Ingrese servicios: ");
                    scanf(" %[^\n]", nuevo.servicios);
                    printf("Ingrese domicilio: ");
                    scanf(" %[^\n]", nuevo.domicilio);
                    printf("Ingrese correo electronico: ");
                    scanf(" %[^\n]", nuevo.mail);
                    printf("Ingrese telefono: ");
                    scanf(" %[^\n]", nuevo.telefono);
                    int exito2=insertarPrestador(lso, nuevo, &cantcargados);
                    if(exito2==1){
                        printf("El nuevo prestador con DNI %d fue insertado con exito.\n", nuevo.DNI);
                        system("pause");
                        }
                    else{
                        if((exito2==0)){
                            printf("El prestador con DNI %d ya pertenece a la lista.\n", nuevo.DNI);
                            system("pause");
                        }
                    }
                }
                break;
            case 2:
                if(cantcargados<1){
                    printf("No se puede eliminar porque no hay prestadores cargados.\n");
                    system("pause");
                }
                else{
                    system("cls");
                    printf("\nIngrese DNI del prestador que desea eliminar: ");
                    int eliminar;
                    scanf("%d", &eliminar);
                    while(eliminar >= INFINITO || eliminar < 1){
                        printf("Error: DNI ingresado no es valido. Ingreselo nuevamente\n");
                        scanf("%d", &eliminar);
                    }
                    int elim=eliminarElemento(lso, eliminar, &cantcargados);
                    if (elim==1){
                        printf("Se elimino con exito.\n");
                        system("pause");
                    }
                    else {
                        printf("No se elimino el prestador.\nPresiona una tecla para continuar..."); getch();
                    }
                }
                break;
            case 3:
                if(!cantcargados){
                    printf("No se puede eliminar porque no hay prestadores cargados.\n");
                    system("pause");
                }else{
                    system("cls");
                    printf("Ingrese DNI del Prestador del cual desea modificar su informacion: ");
                    int dnimodif;
                    scanf("%d", &dnimodif);
                    while(dnimodif >= INFINITO || dnimodif < 1){
                        printf("El dni ingresado no es valido. Intente nuevamente: \n");
                        scanf("%d",&dnimodif);
                    }
                    int exito=modificar(lso, dnimodif, &cantcargados);
                    if(exito==1){
                        printf("Se modifico con exito.\n");
                        system("pause");
                    }
                    else {
                        if(exito == -1){
                        printf("No se encontro un prestador con DNI %d.", dnimodif);
                        system("pause");
                        }
                        else {
                            printf("Se cancelo la modificacion. \nPresione una tecla para continuar..."); getch();
                        }
                    }
                }

                break;
            case 4:
                if(cantcargados==0){
                    printf("Aun no hay prestadores cargados.\n");
                    system("pause");
                }
                else{
                    int dnievoc;
                    int op1=1;
                    do{
                        system("cls");
                        printf("ingrese DNI de un prestador para consultar su informacion: ");
                        scanf("%d", &dnievoc);
                        while(dnievoc >= INFINITO || dnievoc < 1){
                            printf("El dni ingresado no es valido. Intente nuevamente: \n");
                            scanf("%d",&dnievoc);
                        }
                        int e=0;
                        Prestadores temp;
                        temp = evocacion(lso, dnievoc, &e);
                        if(e==1){
                            printf("----------Informacion asociada al prestador con DNI %d----------\n", dnievoc);
                            printf("Nombre y apellido: %s\nServicios: %s\nDomicilio: %s\nMail: %s\nTelefono: %s\n-----------------------------------------------------------------------\n",
                            temp.nombreApellido,temp.servicios,temp.domicilio,temp.mail,temp.telefono);
                            printf("Si desea consultar la informacion de otro prestador ingrese '1', para salir ingrese '0': ");
                            scanf("%d", &op1);
                        } else {
                            printf("No se encontro un prestador con DNI: %d \n", dnievoc);
                            printf("Si desea consultar la informacion de otro prestador ingrese '1', para salir ingrese '0': ");
                            scanf("%d", &op1);
                        }
                    }while(op1!=0);
                }
                break;
            case 5:
                memorizacionPrevia(lso, &cantcargados);
                break;
            case 6:
                if(cantcargados<1){
                    printf("No se puede mostrar porque no hay prestadores cargados.\n");
                    system("pause");
                }else{
                    mostrarLista(lso, cantcargados);
                }
                break;
            case 7:
                printf("Saliendo del programa...\n");
                exit(0);
            default:
                printf("Opcion invalida. Por favor, intente de nuevo.\n"); getch();
                break;
        }/**FIN SWITCH*/

    }while(op!=7);
    return 0;
}

/**retorna 1 si lo encontro y 0 si no*/
int localizarPrestador(int dni, Prestadores lso[],int *pos){
    int i=0;
    while ((lso[i].DNI)<dni){
        i=i+1;
    }
    *pos=i;
    if ((lso[i].DNI)==dni)
        return 1;
    return 0;
}

/**Retorna 1 si se insertó, -1 si está llena y 0 si ya estaba*/
int insertarPrestador(Prestadores lso[], Prestadores elem, int *cargados){
    if(*cargados==MAX-1){
        return -1;
    }
    int pos=0;
    if ((localizarPrestador(elem.DNI, lso, &pos))==1){
        return 0;
    }
    int i;
    for(i=*cargados;i>=pos;i--){
        lso[i+1]=lso[i];
    }
    lso[pos]=elem;
    *cargados+=1;
    return 1;
}

void mostrarLista(Prestadores lista[], int cargados){
    int i, mod;
     /*PARA QUE VAYA MOSTRANDO DE A 5*/
    for(i=0;i<cargados;i+=5){
        system("cls");
        printf("--------------AGENDA DE PRESTADORES--------------\n");
        for(mod=i; mod<i+5 && mod<cargados; mod++){
            printf("Prestador %d:\n", mod);
            printf("DNI: %d\n", lista[mod].DNI);
            printf("Nombre y Apellido: %s\n", lista[mod].nombreApellido);
            printf("Servicio: %s\n", lista[mod].servicios);
            printf("Domicilio: %s\n", lista[mod].domicilio);
            printf("Correo electronico: %s\n", lista[mod].mail);
            printf("Telefono: %s\n", lista[mod].telefono);
            printf("-------------------------------------------------\n");
        }
        system("pause");
    }
}

/**Retorna 1 si se pudo eliminar y 0 si no se pudo*/
int eliminarElemento(Prestadores lso[], int dni, int *cargados){
    int pos;
    if(localizarPrestador(dni, lso, &pos)){
        int res;
        printf("-----------------Informacion de Prestador------------------\nNombre y Apellido: %s.\nServicio: %s.\nDomicilio: %s.\nMail: %s\nTelefono: %s.\n-----------------------------------------------------------\n", lso[pos].nombreApellido, lso[pos].servicios, lso[pos].domicilio, lso[pos].mail, lso[pos].telefono);
        printf("Para eliminarlo ingrese '1', en otro caso '0': ");
        scanf("%d", &res);
        while(res!=0 && res!=1){
            printf("Por favor ingrese 1 o 0.\n");
            scanf("%d", &res);
        }
        if(res == 1){
            int i=pos;
            for(i;i<(*cargados);i++){
                lso[i]=lso[i+1];
            }
            *cargados-=1;
            return 1;
        }
      } else {
        printf("No se encontro un prestador con DNI %d\n",dni);
      }
        return 0;
}

void memorizacionPrevia(Prestadores lso[],int *cargados){
    FILE *archivo;
    int carg=0; /**Cuenta cantidad de Prestadores que se cargaron del archivo*/
    Prestadores aux;
    archivo=fopen("Prestadores.txt", "r");
    if(archivo == NULL){
        perror("Error al abrir el archivo"); system("pause");
        return;
    }
    int confirmar,carga=0;
    printf("---------------------------------------------------------------");
    while (!feof(archivo)) {
        if(*cargados<MAX){
            fscanf(archivo, "%d",&aux.DNI);
            fscanf(archivo, " %[^\n]", aux.nombreApellido);
            fscanf(archivo, " %[^\n]", aux.servicios);
            fscanf(archivo, " %[^\n]", aux.domicilio);
            fscanf(archivo, " %[^\n]", aux.mail);
            fscanf(archivo, " %[^\n]", aux.telefono);
            if(aux.DNI < INFINITO && aux.DNI >0){
                confirmar=insertarPrestador(lso, aux, cargados);// Llamar a la función alta para almacenar los datos
                if(confirmar==0){
                    printf("\nEl prestador con DNI %d no se pudo cargar porque ya existia en la lista.", aux.DNI);
                }else{
                    if(confirmar==1){
                        printf("\nSe cargo con exito el prestador con DNI %d.", aux.DNI);
                        carg++;
                        } else {
                            printf("\nLa lista esta llena. No fue posible cargar el prestador con DNI %d.", aux.DNI);
                    }
                }
            }else {
                printf("\nNo se pudo cargar: El DNI %d es INVALIDO.", aux.DNI);}
            } //fin if cargados
    } //fin while
    printf("\n---------------------------------------------------------------\n");
    if(carg!=0)
        printf("Se cargaron con exito %d Prestador/es.\n", carg);
    else{
        printf("\nNo se cargo ningun prestador.\n");
    }
    system("pause");
    fclose(archivo);
}//fin funcion

/**retorna 1 si se modifico algun campo. 0 si se cancelo la operacion. -1 si no se encontro el prestador a modificar*/
int modificar(Prestadores lso[],int dnimodif, int *cargados){
    int posicion=0, estado =0;
    int exito=localizarPrestador(dnimodif, lso,&posicion);
    if(exito==0)
        return -1;
    else{
        if(exito==1){
            int campomodif;
            printf("\n----------------------------------------------------\n");
            printf("\nLa informacion actual del Prestador con DNI %d es:\n", lso[posicion]);
            do {
                printf("1.Nombre y Apellido: %s.\n2.Servicio: %s.\n3.Domicilio: %s.\n4.Mail: %s\n5.Telefono: %s\n", lso[posicion].nombreApellido, lso[posicion].servicios, lso[posicion].domicilio, lso[posicion].mail, lso[posicion].telefono);
                printf("\n----------------------------------------------------\n");
                printf("\nIngrese el numero del campo que desea cambiar(Si quiere salir presione 0): ");
                scanf("%d",&campomodif);
                switch(campomodif){
                    case 0:
                        break;
                    case 1:
                        printf("Ingrese el nuevo nombre y apellido: ");
                        scanf(" %[^\n]",lso[posicion].nombreApellido);
                        estado = 1;
                        break;
                    case 2:
                        printf("Ingrese el nuevo servicio: ");
                        scanf(" %[^\n]",lso[posicion].servicios);
                        estado = 1;
                        break;
                    case 3:
                        printf("Ingrese el nuevo domicilio: ");
                        scanf(" %[^\n]",lso[posicion].domicilio);
                        estado = 1;
                        break;
                    case 4:
                        printf("Ingrese el nuevo mail: ");
                        scanf(" %[^\n]",lso[posicion].mail);
                        estado = 1;
                        break;
                    case 5:
                        printf("Ingrese el nuevo telefono: ");
                        scanf(" %[^\n]",lso[posicion].telefono);
                        estado = 1;
                        break;
                    default:
                        printf("Opcion invalida. Por favor, intente de nuevo.\n");
                        break;
                    }
            }while(campomodif!=0);
        }//FIN IF
        return estado;
    }/**FIN ELSE*/
}

Prestadores evocacion(Prestadores lso[], int dni, int *e){
    int pos;
    *e=localizarPrestador(dni, lso,&pos);
    return lso[pos];
}

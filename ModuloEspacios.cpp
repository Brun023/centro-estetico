#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fecha
{
	int dia, mes, anio;
};

struct profesional
{
	int Matricula;
	char contra[10];
};

struct prof
{
	char username[10];
	int IdProfesional;
	int Dni;
	char Telefono [25];
	char password [10];
	int atendidos;
	char ApellidoyNombre [60];
};

struct paciente
{
	char ApellidoyNombre[60];
	char domicilio[60];
	int DNI;
	char localidad[60];
	fecha fec;
	int edad;
	float peso;
	char telefono[25];
};

struct turnos
{
	int IdProfesional;
	fecha fec;
	int DNIc;
	char progreso[380];
};

int Menu();
bool iniciarse(FILE *f, int &IdProfesional);
void lista(FILE *f);
bool evolucion(FILE *f);
void incontador(FILE *f, int IdProfesional);

main()
{
	FILE *PACIENTE = fopen("pacientes.dat", "a+b");
	FILE *turnos = fopen("turnos.dat", "rb");
	FILE *PROFESIONALES = fopen("profesionales.dat", "rb");

	if(PROFESIONALES == NULL)
	{
		printf("profesionales.dat no ha sido creado.\n\n");
		system("pause");
		exit(1);
	}

	bool inicio = false, borrar = false;
	int IdProfesional;
	
	int opc;
	do
	{
		opc = Menu();
		switch(opc)
		{
			case 1:	
			inicio = iniciarse(PROFESIONALES, IdProfesional);		 	 
			break;
					 
			case 2:	
			if(inicio == true)
			{
				lista(turnos);
			}
			else
			{
				printf("\n Primero debe Iniciar sesion\n");
			}
			break;
					 
			case 3:
			if(inicio == true)
			{
				borrar = evolucion(turnos);
			}
			else
			{
				printf("\n Primero debe Iniciar sesion\n");
			}
			if(borrar == true) incontador(PROFESIONALES, IdProfesional);
			break;			 
		}
		printf("\n");
		system("pause");
	}
	while(opc != 4);
	
	fclose(PACIENTE);
	fclose(turnos);
	fclose(PROFESIONALES);
}

int Menu()
{
	system("cls");
	printf("\n\t\t\t Modulo Espacios");
	printf("\n\t\t\t ========================");
	printf("\n\t\t\t 1.- Iniciar Sesion.");
	printf("\n\t\t\t 2.- Visualizar lista de turnos (informe).");	
	printf("\n\t\t\t 3.- Mostrar evolucion del tratamiento.\n");
	printf("\n\t\t\t 4.- Cerrar la aplicacion. \n");
	printf("\n\t\t\t Ingrese una opcion: ");
	int opc;
	scanf("%d", &opc);
	return opc;
}
bool iniciarse(FILE *f, int &IdProfesional)
{
	rewind(f);
	profesional log;
	prof p;
	bool iniciado = false;
	int valor;
	system("cls");
	
	do
	{
		printf("\n - Ingrese numero de matricula: ");
		scanf("%d", &log.Matricula);
	}
	while (log.Matricula >= 9999);
	IdProfesional = log.Matricula;

	printf("\n - Ingrese la contrasena: ");
	_flushall();
	gets(log.contra);
	
    fread(&p, sizeof(prof), 1, f);
    while(!feof(f))
    {
        valor = strcmp(log.contra, p.password);
        
        if(log.Matricula == p.IdProfesional)
		{
			if(valor == 0)
			{	
				printf("\n Sesion iniciada correctamente \n");
				printf("- Bienvenido/a %s \n\n", p.ApellidoyNombre);
				iniciado = true;
			}

		}
        fread(&p, sizeof(prof), 1, f);
    }
    if(iniciado == false) printf("\n\n El nombre de usuario y/o contrasena no coinciden\n\n");
    return iniciado;
}

void lista(FILE *f)
{
	rewind(f);
	system("cls");
	turnos tur;
	int c=0;
	int nada;


	fread(&tur, sizeof(turnos), 1, f);
	while(!feof(f))
	{
		nada = strcmp(tur.progreso, "");

		if(nada == 0)
		{	printf("Lista de turnos en espera: \n\n");
			printf("\n - Turno %d:\n\n", c+1);

			printf("\n - Matricula del profesional: %d", tur.IdProfesional);
			printf("\n - Fecha: %d/%d/%d",tur.fec.dia, tur.fec.mes, tur.fec.anio);
			printf("\n - DNI(dueno): %d", tur.DNIc);
			fread(&tur, sizeof(turnos), 1, f);
		}
		else fread(&tur, sizeof(turnos), 1, f);;
	}
}

bool evolucion(FILE *f)
{	
	fclose(f);
	f = fopen("turnos.dat", "r+b");
	FILE *auxtur = fopen("auxiliar.dat", "a+b");
	system("cls");
	turnos tur;
	bool borrar = false;
	int dni, dia, mes, anio;


	printf("Ingrese: DNI:  ");
	printf("\n DNI:  ");
	scanf("%d",&dni);
	printf("\n Fecha de atencion");
	printf("\n - Dia: ");
	scanf("%d",&dia);
	printf("\n - Mes: ");
	scanf("%d",&mes);
	printf("\n - Anio: ");
	scanf("%d",&anio);
	
	system("cls");

	fread(&tur, sizeof(turnos), 1, f);
	while(!feof(f) && !borrar)
	{
		if(dni == tur.DNIc && dia == tur.fec.dia && mes == tur.fec.mes && anio == tur.fec.anio)
		{
			printf("\n - Detalle de atencion:");
			_flushall();
			gets(tur.progreso);
			borrar = true;
			
			fwrite(&tur, sizeof(turnos), 1, auxtur);
		}
		else
		{
			fwrite(&tur, sizeof(turnos), 1, auxtur);
		} 
		fread(&tur, sizeof(turnos), 1, f);
	}
	if(borrar == true) printf("\n - Evolucion registrada \n");
		

	else printf("\n - Evolucion no registrada");
	
	fclose(f);
	fclose(auxtur);
	
	remove("turnos.dat");
	rename("auxiliar.dat","turnos.dat");
	f = fopen("turnos.dat", "rb");
	return borrar;
}
void incontador(FILE *f, int IdProfesional)
{	fclose(f);
	f = fopen("profesionales.dat", "r+b");
	FILE *aux = fopen("auxiliar.dat", "a+b");
	
	prof reg;
	fread(&reg, sizeof(prof), 1, f);
	while(!feof(f))
	{
		if(IdProfesional == reg.IdProfesional)
		{
			reg.atendidos++;

			fwrite(&reg, sizeof(prof), 1, aux);
		}
		else
		{
			fwrite(&reg, sizeof(prof), 1, aux);
		}
		fread(&reg, sizeof(prof), 1, f);
	}
	fclose(f);
	fclose(aux);
	
	remove("profesionales.dat");
	rename("auxiliar.dat","profesionales.dat");
	fopen("profesionales.dat", "rb");
}

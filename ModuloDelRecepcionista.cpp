#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct fecha
{
	int dia, mes, anio;
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

struct recep
{
	char username[10];
	char password[10];
	char ApellidoyNombre[60];
	
};

struct usuario
{
	char usuario[10];
	char contra[10];
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
bool iniciars(FILE *f);
void regpaciente(FILE *f);
void regturnos(FILE *t, FILE *f, FILE *M);
void listatencion(FILE *t, FILE *M);

main()
{
	FILE *pacientes = fopen("pacientes.dat", "a+b");
	FILE *turnos = fopen("turnos.dat", "a+b");
	FILE *recep = fopen("recep.dat", "rb");
	FILE *profesionales = fopen("profesionales.dat", "rb");
	
	if(profesionales == NULL)
	{
		printf("profesionales.dat no ha sido creado.\n\n");
		system("pause");
		exit(1);
	}
	bool iniciado = false;
	
	int opc;
	do{
		opc = Menu();
		switch(opc)
		{
			case 1:	
			iniciado = iniciars(recep);			 	 
			break;
					 
			case 2:	
			if(iniciado == true)
			{
				regpaciente(pacientes);
			}
			else
			{
				printf("\n Primero debe Iniciar sesion\n");
			} 
			break;
					 
			case 3: 
			if(iniciado == true)
			{
				regturnos(turnos, profesionales, pacientes);
			}
			else
			{
				printf("\n Primero debe Iniciar sesion\n");
			}	 
			break;
					 
			case 4: 
			if(iniciado == true)
			{
				listatencion(turnos, pacientes);
			}
			else
			{
				printf("\n Primero debe Iniciar sesion\n");
			}
            break;
		}
		printf("\n");
		system("pause");
	}
	while(opc != 5);
	
	fclose(pacientes);
	fclose(turnos);
	fclose(recep);
	fclose(profesionales);
}

int Menu()
{
	system("cls");
	printf("\n\t\t\t Modulo del recepcionista");
	printf("\n\t\t\t ========================");
	printf("\n\t\t\t 1.- Iniciar Sesion.");
	printf("\n\t\t\t 2.- Registrar cliente.");	
	printf("\n\t\t\t 3.- Registrar turno.");
	printf("\n\t\t\t 4.- Listado de atenciones por profesional y fecha.\n");
	printf("\n\t\t\t 5.- Cerrar la aplicacion. \n");
	printf("\n\t\t\t Ingrese una opcion: ");
	int opc;
	scanf("%d", &opc);
	return opc;
}

bool iniciars(FILE *f)
{
	prof login;
	recep us;
	bool iniciado = false;
	int valor, valor2;
	system("cls");
	
	printf("- Ingrese el nombre de usuario: ");
	_flushall();
	gets(login.username);
	printf("\n- Ingrese la contrasena: ");
	gets(login.password);
	
    rewind(f);
    fread(&us, sizeof(recep), 1, f);
    while(!feof(f))
    {
        valor = strcmp(login.username, us.username);
        valor2 = strcmp(login.password, us.password);
        
        if(valor == 0 && valor2 == 0)
		{
			printf("\n Sesion iniciada correctamente. \n");
			iniciado = true;
		}
        fread(&us, sizeof(recep), 1, f);
    }
    if(iniciado == false) printf("\n\n El nombre de usuario y/o contrasena no coinciden\n\n");
    return iniciado;
}

void regpaciente(FILE *f)
{
	paciente m;
	system("cls");

	printf("\n Registro de pacientes\n");
	printf("\n - Apellido y nombre:  ");
	_flushall();
	gets(m.ApellidoyNombre);

	printf("\n - Domicilio: ");
	gets( m.domicilio);
	printf("\n - DNI: ");
	scanf("%d", &m.DNI);

	printf("\n - Localidad: ");
	_flushall();
	gets(m.localidad);

	printf("\n - Fecha de nacimiento: ");
	printf("\n Dia: ");
	scanf("%d", &m.fec.dia);
	printf("\n Mes: ");
	scanf("%d", &m.fec.mes);
	printf("\n Anio: ");
	do
	{
		scanf("%d", &m.fec.anio);
	} while (m.fec.anio <= 1900 && m.fec.anio >= 2020);
	
	m.edad = 2020 - m.fec.anio;

	printf("\n Peso(Kg): ");
	scanf("%f", &m.peso);

	printf("\n Telefono: ");
	_flushall();
	gets(m.telefono);

	fwrite(&m, sizeof(paciente), 1, f);
}

void regturnos(FILE *t, FILE *f, FILE *M)
{
	fclose(M);
	M = fopen("pacientes.dat", "rb");
	rewind(f);
	
	prof reg;
	turnos tur;
    paciente m;
	bool exito = false;
	system("cls");
	
	printf("\n Registro de Turnos: ");
	printf("\n - Matricula del profesional: ");
	scanf("%d", &tur.IdProfesional);
	
	fread(&reg, sizeof(prof), 1, f);
	while(!feof(f))
	{
		if(tur.IdProfesional == reg.IdProfesional)
		{
			printf("\n Fecha: ");
			printf("\n Dia: ");
			scanf("%d", &tur.fec.dia);
			printf("\n Mes: ");
			scanf("%d", &tur.fec.mes);
			printf("\n Anio: ");
			do
			{
				scanf("%d", &tur.fec.anio);
			}
			while (tur.fec.anio <= 1900 && tur.fec.anio >= 2020);

			fread(&m, sizeof(paciente), 1, M);
			printf("\n DNI: ");
			scanf("%d", &tur.DNIc);
			while(!feof(M))
			{
				if(tur.DNIc == m.DNI)
				{
					strcpy(tur.progreso, "");
					exito = true;	
				}
				fread(&m, sizeof(paciente), 1, M);
			}
		}
		fread(&reg, sizeof(prof), 1, f);
	}


	if(exito == true)
	{
		printf("\n Turno registrado con exito\n");
		fwrite(&tur, sizeof(turnos), 1, t);
	}
	else printf("\nTurno no registrado\n");

	fclose(M);
	M = fopen("pacientes.dat", "a+b");
}

void listatencion(FILE *t, FILE *M)
{
	system("cls");
	fclose(t);
	t = fopen("turnos.dat", "rb");
	fclose(M);
	M = fopen("pacientes.dat", "rb");

	paciente mas;
	turnos tur;
	int matricula, dia, mes, anio, nada;
	bool confirm = false;

	printf("\n Buscar informe de pacientes");
	printf("\n Matricula de profesional: ");
	scanf("%d",&matricula);
	printf("\n Fecha de atencion\n");
	printf("\n - Dia: ");
	scanf("%d",&dia);
	printf("\n - Mes: ");
	scanf("%d",&mes);
	printf("\n - Anio: ");
	scanf("%d",&anio);
	
	rewind(t);
	fread(&tur, sizeof(turnos), 1, t);
	while(!feof(t))
	{
		nada = strcmp(tur.progreso, "");

		if(nada != 0)
		{	
			if(matricula == tur.IdProfesional && dia == tur.fec.dia && mes == tur.fec.mes && anio == tur.fec.anio)
			{
				
				fread(&mas, sizeof(paciente), 1, M);
				while(!feof(M))
				{
					if(tur.DNIc == mas.DNI)
					{
						confirm = true;

						system("cls");
						printf("\n Listado de pacientes atendidas: ");
						printf("\n Paciente: ");
						puts(mas.ApellidoyNombre);
						printf("\n");
						puts(tur.progreso);
					}
					fread(&mas, sizeof(paciente), 1, M);
				}
			}
		}
		fread(&tur, sizeof(turnos), 1, t);
	}

	fclose(t);
	fclose(M);
	t = fopen("turnos.dat", "a+b");
	M = fopen("pacientes.dat", "a+b");
}

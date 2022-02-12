#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int Menu();
void regrecep(bool &admin);
void regprofesionales();
bool checklogin();
void atencion();
void ranking();

main()
{
	bool login = false;
	bool admin = false;
	int opcion;
	do
	{
		opcion = Menu();
		switch(opcion)
		{
			case 1:
			system("cls");
			login = checklogin();
			if(login == true)
			{
				printf("\n -Sesion iniciada correctamente- \n\n");
				system("pause");
				system("cls");
				regprofesionales();
			}
			else
			{
				printf("\nLoguearse es requerido para esta accion!\n\n");
			}
			break;
					 
			case 2:
			if(admin == true)
			{
				login = checklogin();
				if(login == true) regrecep(admin);
			}
			else
			{
				regrecep(admin);
			}
			break;
					 
			case 3:	
			system("cls");
			login = checklogin();
			if(login == true)
			{
				printf("\n -Sesion iniciada correctamente- \n\n");
				system("pause");
				system("cls");
				atencion();
			}
			else
			{
				printf("\nLoguearse es requerido para esta accion!\n\n");
			}
			break;
					 
			case 4:
			system("cls");
			login = checklogin();
			if(login == true)
			{
				printf("\n -Sesion iniciada correctamente- \n\n");
				system("pause");
				system("cls");
				ranking();
			}
			else
			{
				printf("\nLoguearse es requerido para esta accion!\n\n");
			}
            break;
		}
		printf("\n");
		system("pause");
	}
	while(opcion != 5);
	exit(1);
}

int Menu()
{
	system("cls");
	printf("\n\t\t\t Modulo Administracion");
	printf("\n\t\t\t ========================");
	printf("\n\t\t\t 1.- Registrar Profesional.");
	printf("\n\t\t\t 2.- Registrar Usuario Recepcionista.");	
	printf("\n\t\t\t 3.- Atenciones por Profesionales.");
	printf("\n\t\t\t 4.- Ranking de Profesionales por Atenciones.\n");
	printf("\n\t\t\t 5.- Cerrar la aplicacion. \n");
	printf("\n\t\t\t Ingrese una opcion: ");
	int opcion;
	scanf("%d", &opcion);
	return opcion;
}

void regrecep(bool &admin)
{
	FILE *RECEP = fopen("recep.dat", "a+b");
	system("cls");
	recep us;
	bool u = false;
	int mayus=0, digitos=0, opcion, x;

	system("cls");
	if(admin == false)
	{
		printf("*CREAR ADMINISTRADOR*\n\n\n");
		admin = true;
		system("pause");
	}
	do
	{
		do
		{	system("cls");
			printf("\t\t\tCONDICIONES:\n\n");
			printf("-> Entre 6 y 10 caracteres\n\n-> Letras, numeros, simbolos (+,-,/,*,?,�,!,�)\n\n-> Comenzar con letra minuscula\n\n-> Tener al menos 2 letras mayusculas\n\n-> Tener como maximo 3 digitos\n");
			printf("\n\nIngrese nombre de usuario ->  ");
			_flushall();	
			gets(us.username);
			if(strlen(us.username)>= 6 && strlen(us.username) <= 10)
			{
				if(us.username[0] >= 97 && us.username[0] <= 122)
				{
					for(int i=0; i < strlen(us.username); i++)
					{
						if (us.username[i] >=65 && us.username[i] <=90)
						{
							mayus++;
						}
						if (us.username[i] == 43 || us.username[i] == 45 || us.username[i] == 47 || us.username[i] == 42 || us.username[i] == 63 || us.username[i] == 168 || us.username[i] == 173 || us.username[i] == 33 || us.username[i] >= 48 || us.username[i] <= 57)
						{
							digitos++;
						}
						if(mayus >= 2 && digitos <= 3)
						{
							if(us.username[i] >= 65 || us.username[i] <= 90 || us.username[i] >= 97 || us.username[i] <= 122 || us.username[i] >= 48 || us.username[i] <= 57 || us.username[i] == 43 || us.username[i] == 45 || us.username[i] == 47 || us.username[i] == 42 || us.username[i] == 63 || us.username[i] == 168 || us.username[i] == 173 || us.username[i] == 33)
							{
								u = true;
							}
						 }
					}
				}
			}
		}
		while(u == false);
		char contra[15], auxc[15], ull[10];
		int cmin=0, cmay=0, cnum=0, a, b, c1, lon1;
		bool ecar=false, econs=false, error=false, eletconsec=false;
		system("cls");
		printf("\t\t\tCONDICIONES PARA CONTRASENA");
		printf("\n\n-> Contener al menos una letra mayuscula, una minuscula y un numero\n\n-> No contener ningun caracter de puntuacion, ni acentos, ni espacios\n\n-> Solo contener caracteres alfanumericos\n\n-> Tener entre 6 y 32 caracteres\n\n-> No tener mas de 3 caracteres consecutivos\n\n-> No tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas (ascendentemente)\n");
		_flushall();
		do
		{	
			printf("\n- Ingrese su Contrasena: ");
			gets(contra);
			lon1 = strlen(contra);
            strcpy(auxc,contra);
            strlwr(auxc);
            if (lon1>=6 && lon1<=32)
            {  
                for (int i = 0; i < lon1; i++)
                {
                    if((contra[i]>='a') || (contra[i]<'z'))
                    {
                        cmin++;
                    }
                    if ((contra[i]>='A') || (contra[i]<'Z'))
                    {
                        cmay++;
                    }
                    if (contra[i]>=48 && contra[i]<=57)
                    {
                        cnum++;
                    }
                    if ((contra[i]<47 || contra[i]>58) && (contra[i]<65 || contra[i]>90) && (contra[i]<97 || contra[i]>122))
                    {
                        ecar=false;
                    }
                    if (contra[i]>=48 && contra[i]<=57)
                    {
                        a=contra[i];
                        b=a+1;
                        c1=a+2;
						if (contra[i+1]==b && contra[i+2]==c1)
                        {
                            econs=true;
                        }                    
                    }                 
                    if(auxc[i]>96 && auxc[i]<123)
                    {                    
                        a=auxc[i];
                        b=a+1;
                        if(auxc[i+1]==b)
                        {
                            printf("\nLetra 1: %c",auxc[i]);
                            printf("\nLetra: %c",auxc[i+1]);
                            eletconsec=true;
                        }
                    }               
                }
                if (cmin==1)
                {
                    printf("\nDebe tener al menos una letra minuscula!!\n");
                    error=true;
                }
                if (cmay<1)
                {
                    printf("\nDebe tener al menos una letra minuscula!!\n");
                    error=true;
                }
                if (cnum<1)
                {
                    printf("\nDEBE TENER AL MENOS 1 NUMERO!!\n");
                    error=true;
                }
                if(ecar==true)
                {
                    printf("\nDEBE CONTENER SOLO CARACTERES ALFANUMERICOS!!\n");
                    error=true;
                }
                if (econs==true)
                {
                    printf("\nNO DEBE TENER MAS DE 3 NUMEROS CONSECUTIVOS!!\n");
                    error=true;                
                }
                if (eletconsec==true)
                {
                    printf("\nNO DEBE TENER LETRAS CONSECUTIVAS!!\n");
                    error=true;
                }
            }
            else error=true;
        }
		while (error==true);

        if (error==false)
        {       
            strcpy(us.password, contra);
            printf("\n- Ingrese el apellido y nombre: ");        
            _flushall();
            gets(us.ApellidoyNombre);
			fwrite(&us, sizeof(recep), 1, RECEP);
            do
			{
                printf("\n- Desea agregar otro usuario? (SI:1 , NO:0): ");
                scanf("%d" ,&x);
            }
			while (x!=0 && x!=1);
        }
    	printf("\n");
    }
	while (x==1);
	
	fclose(RECEP);
}

void regprofesionales()
{
	FILE *profesionales = fopen("profesionales.dat", "a+b");
	prof profesional;
	int mayus=0, digitos=0, x;
	system("cls");	
	do
	{
		do
		{
			printf("-> Ingrese  el ID Profesional(max. 4 digitos): ");
			scanf("%d", &profesional.IdProfesional);
		}
		while(profesional.IdProfesional > 9999);

		printf("\n-> Ingrese celular: ");
		_flushall();
		gets(profesional.Telefono);
		
		char contra[15], auxc[15], ull[10];
		int cmin=0, cmay=0, cnum=0, a, b, c1, lon1;
		bool ecar=false, econs=false, error=false, eletconsec=false;
		
		system("cls");
		printf("\t\t\tCONDICIONES PARA CONTRASENA");
		printf("\n\n-> Contener al menos una letra mayuscula, una minuscula y un numero\n\n-> No contener ningun caracter de puntuacion, ni acentos, ni espacios\n\n-> Solo contener caracteres alfanumericos\n\n-> Tener entre 6 y 32 caracteres\n\n-> No tener mas de 3 caracteres consecutivos\n\n-> No tener 2 caracteres consecutivos que refieran a letras alfabeticamente consecutivas (ascendentemente)\n");
		_flushall();
		
		do
		{	
			printf("\nIngrese su contrasena ->  ");
			gets(contra);
			lon1 = strlen(contra);
            strcpy(auxc,contra);
            strlwr(auxc);

            if (lon1>=6 && lon1<=32)
            { 	
                for (int i = 0; i < lon1; i++)
                {
                    if((contra[i]>='a') || (contra[i]<'z'))
                    {
                        cmin++;
                    }
                    if ((contra[i]>='A') || (contra[i]<'Z'))
                    {
                        cmay++;
                    }
                    if (contra[i]>=48 && contra[i]<=57)
                    {
                        cnum++;
                    }
                    if ((contra[i]<47 || contra[i]>58) && (contra[i]<65 || contra[i]>90) && (contra[i]<97 || contra[i]>122))
                    {
						ecar=true;
                    }
                    if (contra[i]>=48 && contra[i]<=57)
                    {
                    	a=contra[i];
						b=a+1;
                        c1=a+2;

                        if (contra[i+1]==b && contra[i+2]==c1)
                        {
                            econs=true;
                        }                    
                    } 
                    if(auxc[i]>96 && auxc[i]<123)
                    {                    
                        a=auxc[i];
                        b=a+1;
                        if(auxc[i+1]==b)
                        {
                            printf("\nLetra 1: %c",auxc[i]);
                            printf("\nLetra: %c",auxc[i+1]);
                            eletconsec=true;
                        }
                    }               
                }			
                if (cmin==1)
                {
                    printf("\nDebe tener al menos una letra minuscula!!\n");
                    error=true;
                }
                if (cmay<1)
                {
                    printf("\nDebe tener al menos una letra minuscula!!\n");
                    error=true;
                }
                if (cnum<1)
                {
                    printf("\nDEBE TENER AL MENOS 1 NUMERO!!\n");
                    error=true;
                }
                if(ecar==true)
                {
                    printf("\nDEBE CONTENER SOLO CARACTERES ALFANUMERICOS!!\n");
                    error=true;
                }
                if (econs==true)
                {
                    printf("\nNO DEBE TENER MAS DE 3 NUMEROS CONSECUTIVOS!!\n");
                    error=true;                
                }
                if (eletconsec==true)
                {
                    printf("\nNO DEBE TENER LETRAS CONSECUTIVAS!!\n");
                    error=true;
                }     
            }
            else error=true;    
        }
		while (error==true);

        if (error==false)
        {       
        	profesional.atendidos = 0;
            strcpy(profesional.password, contra);
            printf("\n- Ingrese el apellido y nombre: ");        
            _flushall();
            gets(profesional.ApellidoyNombre);
			fwrite(&profesional, sizeof(prof), 1, profesionales);
            do
			{
                printf("\n- Desea agregar otro Profesional ? (SI:1 , NO:0): ");
                scanf("%d" ,&x);
            }
			while (x!=0 && x!=1);
        }
    	printf("\n");
    }
	while (x==1);
	fclose(profesionales);
}

bool checklogin()
{
	recep check;
	int valor, valor2;
	char usu[10], pass[10];
	bool login = false;
	FILE *RECEP = fopen("recep.dat", "rb");
	if(RECEP == NULL)
	{
		printf("\nusuarios. dat no ha sido creado\n\n");
		system("pause");
		exit(1);
	}
	system("cls");
	printf("* Inicio de Sesion:* \n\n");
	printf("- Ingrese nombre de usuario: ");
	_flushall();
	gets(usu);
	
	printf("\n- Ingrese contrasena: ");
	gets(pass);
	
	fread(&check, sizeof(recep), 1, RECEP);
	while(!feof(RECEP))
	{
		valor = strcmp(usu, check.username);
		valor2 = strcmp(pass, check.password);
		if(valor == 0 && valor2 == 0)
		{
			login = true;
		}
		fread(&check, sizeof(recep), 1, RECEP);
	}
	return login;	
	fclose(RECEP);
}

void atencion()
{
	FILE *f = fopen("profesionales.dat", "rb");
	prof reg;
	system("cls");
	
	printf("Atenciones por Profesional \n\n");
	
	fread(&reg, sizeof(prof), 1, f);
	while(!feof(f))
	{
		printf("Id Profesional: %d\n", reg.IdProfesional);
		printf("PROFESIONAL : %s\n", reg.ApellidoyNombre);
		printf("Cantidad de atenciones: %d\n\n\n", reg.atendidos);

		fread(&reg, sizeof(prof), 1, f);
	}
	fclose(f);
}

void ranking()
{
	FILE *f = fopen("profesionales.dat", "rb");
	prof reg, vector[100], aux;
	int i=0;
	system("cls");
	
	fread(&reg, sizeof(prof), 1, f);
	while(!feof(f))
	{
		vector[i]=reg;
		i++;	
		fread(&reg, sizeof(prof), 1, f);
	}
	int n=i;
	bool band;
	do
	{
		band = false;
		for(i = 0; i < n-1; i++)
		{
			if(vector[i].atendidos < vector[i+1].atendidos)
			{
				aux = vector[i];
				vector[i] = vector[i+1];
				vector[i+1] = aux;
				band = true;
			}
		}
	}
	while(band == true);
	
	printf("Ranking de Profesionales \n\n");
	for(i=0; i<n; i++)
	{
		printf("PROFESIONAL: %s - Atendidos: [%d]\n\n", vector[i].ApellidoyNombre, vector[i].atendidos);
	}
	fclose(f);
}
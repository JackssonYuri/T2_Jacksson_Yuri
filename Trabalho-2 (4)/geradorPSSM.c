#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define tam_seq 4
#define linha 4
#define tam_seq0 5

int main() 
{
	FILE *arq;
	int a =0, c=0, g=0, t=0, seq = 0, i, j, total = 0;
	char string[tam_seq0];
	float PSSM[linha][tam_seq];//Matriz PSSM
	float a_total =0, t_total = 0, g_total = 0, c_total =0;
	double log10(double);
	double log(double);
	for ( i = 0 ; i < linha; i++)  {
     for (j = 0 ; j < tam_seq; j++) {
			 PSSM[i][j] = 0;
		 }
	}
//	Abre o arquivo
	arq = fopen("D.motif", "r");

	if(arq == NULL) {
		printf("Erro na criacao do arquivo");
		exit(1);
	}
  
  while (!feof(arq))
  {
    
		if(fscanf(arq, "%s %d", string, &seq) < 2)
			break;
	
			total += seq;
			

		for( i = 0; i < strlen(string); i++)
		{
				if(string[i] == 'A')
				{
					a++;
					PSSM[0][i] += seq;
				}
				else if(string[i] == 'T')
				{
					t++;
					PSSM[1][i] += seq;
				}
				else if(string[i] == 'G')
				{
					g++;
					PSSM[2][i] += seq;
				}
				else if(string[i] == 'C')
				{
					c++;
					PSSM[3][i] += seq;
				}	
		}
	}	
	//o for contabilizou as variáveis
	//uso elas na matriz agora		
	/*	for ( i = 0 ; i < linha; i++)  {
     for (j = 0 ; j < tam_seq; j++) {

					printf("%-7.2f", PSSM[i][j]) ;
    }
    printf ("\n");
	}		 
*/
//pegar os valores 4, 4 , 0 e tals e dividir por 5 numeros de sequencia
	for( j = 0; j < strlen(string); j++)	{
		PSSM[0 ][j] /= total ;
		PSSM[1 ][j] /= total;
		PSSM[2 ][j] /= total;
		PSSM[3 ][j] /= total;	
	}
/*	for ( i = 0 ; i < linha; i++)  {
    for (j = 0 ; j < tam_seq; j++) { 	
				printf("%-7.2f", PSSM[i][j]) ;
    }	
    printf ("\n");
	}	
	*/
//1º parte feita
//2º parte Normalizar as frequências dividindo as frequências posicionais de cada resíduo pela frequência total
//total = 6;
//preenchendo o vetor de score
float oi = 6;//qntd de nucleotódios, isso é alterado, preciso de pegar os caracteres até o primeiro espaço
float freq_total[4];
for(i = 0; i< linha; i++){
		if(i == 0)
		freq_total[i] = a / ((float)tam_seq * total);
		else if(i == 1)
		freq_total[i] = t / ((float)tam_seq * total);
		else if(i == 2)
		freq_total[i] = g / ((float)tam_seq * total);
		else if(i == 3)
		freq_total[i] = c / ((float)tam_seq * total);
		else 
		break;		
}
//vetor de freq finalizado;
//já contabilizei quantas vezes cada letra aparece nas strings, a, t, g, c
//vou percorrer o vetor normalizando

for( j = 0; j < strlen(string); j++)	{
		PSSM[0 ][j] /= freq_total[0] ;
		PSSM[1][j] /= freq_total[1];
		PSSM[2][j] /= freq_total[2];
		PSSM[3][j] /= freq_total[3];
		
	}
/*	for ( i = 0 ; i < linha; i++)  {
    for (j = 0 ; j < tam_seq; j++) { 	


			
				printf("%-7.2f", PSSM[i][j]) ;
    }	
    printf ("\n");
	}
	*/
	//frequências posicionais normalizadas
	//Converter os scores normalizados para escala logarítmica na base 2.
	for( j = 0; j < strlen(string); j++)	
	{
		if(PSSM[0][j] == 0)
		{
			PSSM[0][j] = -999;
		}else{
			PSSM[0 ][j] = log10(PSSM[0][j]) / log10(2) ;
		}
		
		if(PSSM[1][j] == 0)
		{
			PSSM[1][j] = -999;
		}else{
			PSSM[1][j] = log10(PSSM[1][j]) / log10(2) ;
		}
		
		if(PSSM[2][j] == 0)
		{
			PSSM[2][j] = -999;
		}else{
			PSSM[2][j] = log10(PSSM[2][j]) / log10(2) ;
		}

		if(PSSM[3][j] == 0)
		{
			PSSM[3][j] = -999;
		}else{
			PSSM[3][j] = log10(PSSM[3][j]) / log10(2) ;
		}
		
	}
	
	for ( i = 0 ; i < linha; i++)  {
    for (j = 0 ; j < tam_seq; j++) { 
			
				printf("%9.2lf", PSSM[i][j]) ;
    }	
    printf ("\n\n");
	}
	
	//Finalização da PSSM em escala logaritmica
	fclose(arq);

	arq=fopen("arquivoSaida.PSSM","wb");  
  if (arq==NULL)  
    printf("Erro");  
  else  
    {  
    printf("Arquivo aberto com sucesso\n");  
    fwrite(PSSM,sizeof(float),linha*tam_seq,arq);  
    fclose(arq);  
    }
	
	return 0;
}
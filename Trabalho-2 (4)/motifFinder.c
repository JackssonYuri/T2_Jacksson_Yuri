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
	 int j, i, seq = 0, a = 0, t =0, g=0, c=0;
	 float contador = 0;
	 float PSSM[linha][tam_seq];
	 char string[tam_seq0];
	 
  if((arq = fopen("arquivoSaida.PSSM","rb")) == NULL)
  {
      printf("Erro ao ler\n");
			return 1;
  }
  
  fread(PSSM,sizeof(float),linha * tam_seq,arq);

	for ( i = 0 ; i < linha; i++)  {
    for (j = 0 ; j < tam_seq; j++) { 	
				printf("%9.2lf", PSSM[i][j]) ;
    }	
    printf ("\n");
	}
	fclose(arq);
//lendo arquivo D.motif
	arq = fopen("D.motif", "r");

	if(arq == NULL) {
		printf("Erro na criacao do arquivo");
		exit(1);
	}
  
  while (!feof(arq))
  {    
		if(fscanf(arq, "%s %d", string, &seq) < 2)
			break;
			
			//lê linha por linha
			//lê caractere por caractere
	contador = 0;
	for(i = 0; i < strlen(string); i++){

				if(string[i] == 'A')
				{					
					contador += PSSM[0][i];					
				}
				else if(string[i] == 'T')
				{
					
					contador += PSSM[1][i];
				}
				else if(string[i] == 'G')
				{
					
					contador += PSSM[2][i];
				}
				else if(string[i] == 'C')
				{
					
					contador += PSSM[3][i];
				}
					
	}
	printf("%s %f\n", string, contador);	
}
		
	fclose(arq);
  
	return 0;
	
 }
	
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<locale.h>


int **Alocar_matriz (int m, int n)
{
  int **v;  /* ponteiro para a matriz */
  int   i;    /* vari�vel auxiliar      */
  if (m < 1 || n < 1) 
  	{ /* verifica par�metros recebidos */
     printf ("** Erro: Par�metro inv�lido **\n");
     return (NULL);
	}
  /* aloca as linhas da matriz */
  v = (int **) calloc (m, sizeof(int *));
  if (v == NULL) {
     printf ("** Erro: Mem�ria Insuficiente **");
     return (NULL);
     }
  /* aloca as colunas da matriz */
  for ( i = 0; i < m; i++ ) {
      v[i] = (int*) calloc (n, sizeof(int));
      if (v[i] == NULL) {
         printf ("** Erro: Mem�ria Insuficiente **");
         return (NULL);
         }
      }
  return (v); 
}

int **Liberar_matriz (int m, int n, int **v)
{
  int  i;  /* vari�vel auxiliar */
  if (v == NULL) return (NULL);
  if (m < 1 || n < 1) {  /* verifica par�metros recebidos */
     printf ("** Erro: Par�metro inv�lido **\n");
     return (v);
     }
  for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz */
  return (NULL);
}



int main()
{
	int m,n,q; /* pedidos no enunciado */
	int i,j,k,aux,aux2,QtdElemFecho; /* vari�veis auxiliares*/
	int **rel,**fechoS; /* matrizes a serem alocadas (Rela��o e Fecho) */ 
	int achou,simetrico,repetido; /* a serem utilizadas nos testes l�gicos */
	
	system("color 17");
	setlocale(LC_ALL,"PTB");

	/* Leitura dos par�metros de entrada (m e n - primeiro e �ltimo elemento do Dom�nio), com os limites solicitados no enunciado */
	do{
		printf("Digite o PRIMEIRO e o �LTIMO elemento do Dom�nio da Rela��o (entre 0 e 100): ");
		scanf("%d%d",&m,&n);
		if ((m<0)||(n>100))//limites do primeiro e �ltimo elemento de acordo com o enunciado
		{
			printf("O intervalo deve ser entre 0 e 100!\nDigite novamente!\n");
			system("PAUSE");
			system("cls");
		}
		else
			if(n<=m)
			{
				printf("O primeiro elemento deve ser menor que o �ltimo!\nDigite novamente!\n");//Caso seja informado de maneira invertida
				system("PAUSE");
				system("cls");
			}
	}while ((n<=m)||(m<0)||(n>100));//repete at� que seja informado um par�metro v�lido

	/* Leitura dos par�metros de entrada (q - quantidade de elementos da Rela��o (Qtde m�xima = n**2, onde n=n�mero de elementos do Dom�nio) */
	
	aux=n-m+1; //Calcula a quantidade de elementos do Dom�nio (vari�vel aux)
	
	do{
		system("cls");
		printf("Digite a quantidade de elementos da Rela��o (m�x=10000): ");
		scanf("%d",&q);
		if(q>pow(aux,2))
		{
			printf("A quantidade de elementos deve ser menor ou igual a %.0f!\nDigite novamente!\n",pow(aux,2));//Quantidade m�xima de acordo com a quantidade de termos do Dom�nio
			system("PAUSE");
		}
		else if((q<1)||(q>10000))//Quantidade m�nima e m�xima de acordo com o enunciado
		{
			printf("A quantidade de elementos deve ser maior que 0 e menor ou igual a 10000!\nDigite novamente!\n");
			system("PAUSE");
			system("cls");
		}
		
		
	system("cls");	
	}while (q>pow(aux,2)||(q>10000)||(q<1));//repete at� que seja informado um par�metro v�lido

	rel=Alocar_matriz(q,2); //aloca espa�o para o conjunto RELA��O
	
	srand(time(NULL));


//Gera a Rela��o com os elementos do Dom�nio

	for(i=0;i<q;i++)//q linhas
	{
		for(j=0;j<2;j++)// 2 colunas (par ordenado)
		{
			do
			{
				repetido=0;
				rel[i][j]=m+rand()%(n-m+1); // gera um n�mero aleat�rio entre m e n (inclusive esses)
				if (i>0) // s� compara a partir da digita��o do segundo elemento da rela��o
				{
					for(k=0;k<i;k++)	
					{
						if ((j==1)&&(rel[i][0]==rel[k][0])&&(rel[i][1]==rel[k][1])) //quando gerado o segundo valor do par da rela��o (j==1), faz a compoara��o com todos os outros pares lidos anteriormente
						{
							repetido=1;
							j=0; //possibilita a gera��o de dois novos valores para esse elemento da rela��o
						}
					}
				}
			}while (repetido); // for�a a gera��o de novo par, se o que foi gerado estiver repetido
		}
	}

//Verifica se a Rela��o � sim�trica

	aux=0;
	for(i=0;i<q;i++)
	{
		achou=false;
				
		for(j=0;j<q;j++) // inicia a compara��o
		{
			if (!achou)
				if ((rel[i][0]==rel[i][1])||(((rel[i][0]==rel[j][1])&&(rel[i][1]==rel[j][0]))))
					{
						achou=true;
						aux=aux+1; //conta a quantidade de pares sim�tricos encontrados no conjunto
					}
					else
						achou=false;
		}
	}
	if (aux==q) //caso a quantidade de pares sim�tricos seja igual a quantidade total de elementos do conjunto
		simetrico=true;
	else
	{
		QtdElemFecho=q+(q-aux);//a quantidade de elementos do fecho � o total de elementos da rela��o mais o total de elementos n�o sim�tricos (qtd de elementos adicionais a serem gerados)
		simetrico=false;
	}

	//caso a Rela��o gerada n�o seja sim�trica
	if (!simetrico)
	{
		fechoS=Alocar_matriz(QtdElemFecho,2); //aloca espa�o para o fecho sim�trico da RELA��O
		k=0;
		for(i=0;i<q;i++) //Gera o Fecho Sim�trico
		{
			fechoS[k][0]=rel[i][0];
			fechoS[k][1]=rel[i][1];
			k=k+1;
			achou=false;
				
			for(j=0;j<q;j++)//vai percorrer toda a Rela��o (q elementos) 
			{
				if (!achou) // ainda n�o encontrou o par sim�trico ao que est� sendo testado
					if ((rel[i][0]==rel[i][1])||(((rel[i][0]==rel[j][1])&&(rel[i][1]==rel[j][0]))))// inicia a compara��o para verificar para cada (x,y) se existe (y,x) ou se os elementos s�o iguais
						{
							achou=true; //encontrou o par ordenado sim�trico a ele
						}
						else
							achou=false; // esse par n�o � sim�trico a ele, continua procurando at� chegar ao final dos elementos da Rela��o
			}
			if (!achou) //nenhum dos outros pares da Rela��o s�o sim�tricos ao que est� sendo testado
			{
				//ent�o gera o par ordenado sim�trico ao que est� sendo testado
				fechoS[k][0]=rel[i][1]; //primeiro elemento
				fechoS[k][1]=rel[i][0]; //segundo elemento
				k=k+1; //prepara para o pr�ximo elemento
			}
		}
	
		//Ordenando pelo primeiro elemento
  		for (i = 0; i < (QtdElemFecho-1); i++) 
  	 	{
    		k = i;
   		 	for (j = (i+1); j < QtdElemFecho; j++) 
			{
      		if(fechoS[j][0] < fechoS[k][0]) 
        		k = j;
  		  	}
   		 if (i != k) 
			{
   			aux = fechoS[i][0];
   	   		aux2 = fechoS[i][1];
    	  	fechoS[i][0] = fechoS[k][0];
  	    	fechoS[i][1] = fechoS[k][1];
    	  	fechoS[k][0] = aux;
    	  	fechoS[k][1] = aux2;
 		   	}
 		}

		//Ordenando pelo segundo elemento (fechoS[j][0] == fechoS[k][0])
 		for (i = 0; i < (QtdElemFecho-1); i++) 
   		{
   	 		k = i;
    		for (j = (i+1); j < QtdElemFecho; j++) 
			{
     	 	if((fechoS[j][0] == fechoS[k][0])&&(fechoS[j][1] < fechoS[k][1])) 
        		k = j;
  	  		}
    		if (i != k) 
			{
   	   			aux = fechoS[i][0];
    	  		aux2 = fechoS[i][1];
  	    		fechoS[i][0] = fechoS[k][0];
    	  		fechoS[i][1] = fechoS[k][1];
     	 		fechoS[k][0] = aux;
     	 		fechoS[k][1] = aux2;
 	   		}
 	 	}
	}
	
	//gera a sa�da de acordo com o enunciado
	if (!simetrico) //caso a rela��o n�o seja sim�trica
	{
		printf("\n%d\n",simetrico);                   //imprime o valor 0 (simetrico=false=0)
		for (i=0;i<QtdElemFecho;i++)                  //imprime o Fecho sim�trico gerado   
			printf("%d %d\n",fechoS[i][0],fechoS[i][1]);
	}
	else //caso seja sim�trica
		printf("\n%d\n",simetrico); //imprime o valor 1 e encerra (simetrico=true=1)
	
	

	//libera o espa�o de mem�ria utilizado
	Liberar_matriz(q,2,rel);
	Liberar_matriz(QtdElemFecho,2,fechoS);

	system("PAUSE");
	return(0);
}




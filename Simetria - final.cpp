#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<locale.h>


int **Alocar_matriz (int m, int n)
{
  int **v;  /* ponteiro para a matriz */
  int   i;    /* variável auxiliar      */
  if (m < 1 || n < 1) 
  	{ /* verifica parâmetros recebidos */
     printf ("** Erro: Parâmetro inválido **\n");
     return (NULL);
	}
  /* aloca as linhas da matriz */
  v = (int **) calloc (m, sizeof(int *));
  if (v == NULL) {
     printf ("** Erro: Memória Insuficiente **");
     return (NULL);
     }
  /* aloca as colunas da matriz */
  for ( i = 0; i < m; i++ ) {
      v[i] = (int*) calloc (n, sizeof(int));
      if (v[i] == NULL) {
         printf ("** Erro: Memória Insuficiente **");
         return (NULL);
         }
      }
  return (v); 
}

int **Liberar_matriz (int m, int n, int **v)
{
  int  i;  /* variável auxiliar */
  if (v == NULL) return (NULL);
  if (m < 1 || n < 1) {  /* verifica parâmetros recebidos */
     printf ("** Erro: Parâmetro inválido **\n");
     return (v);
     }
  for (i=0; i<m; i++) free (v[i]); /* libera as linhas da matriz */
  free (v);      /* libera a matriz */
  return (NULL);
}



int main()
{
	int m,n,q; /* pedidos no enunciado */
	int i,j,k,aux,aux2,QtdElemFecho; /* variáveis auxiliares*/
	int **rel,**fechoS; /* matrizes a serem alocadas (Relação e Fecho) */ 
	int achou,simetrico,repetido; /* a serem utilizadas nos testes lógicos */
	
	system("color 17");
	setlocale(LC_ALL,"PTB");

	/* Leitura dos parâmetros de entrada (m e n - primeiro e último elemento do Domínio), com os limites solicitados no enunciado */
	do{
		printf("Digite o PRIMEIRO e o ÚLTIMO elemento do Domínio da Relação (entre 0 e 100): ");
		scanf("%d%d",&m,&n);
		if ((m<0)||(n>100))//limites do primeiro e último elemento de acordo com o enunciado
		{
			printf("O intervalo deve ser entre 0 e 100!\nDigite novamente!\n");
			system("PAUSE");
			system("cls");
		}
		else
			if(n<=m)
			{
				printf("O primeiro elemento deve ser menor que o último!\nDigite novamente!\n");//Caso seja informado de maneira invertida
				system("PAUSE");
				system("cls");
			}
	}while ((n<=m)||(m<0)||(n>100));//repete até que seja informado um parâmetro válido

	/* Leitura dos parâmetros de entrada (q - quantidade de elementos da Relação (Qtde máxima = n**2, onde n=número de elementos do Domínio) */
	
	aux=n-m+1; //Calcula a quantidade de elementos do Domínio (variável aux)
	
	do{
		system("cls");
		printf("Digite a quantidade de elementos da Relação (máx=10000): ");
		scanf("%d",&q);
		if(q>pow(aux,2))
		{
			printf("A quantidade de elementos deve ser menor ou igual a %.0f!\nDigite novamente!\n",pow(aux,2));//Quantidade máxima de acordo com a quantidade de termos do Domínio
			system("PAUSE");
		}
		else if((q<1)||(q>10000))//Quantidade mínima e máxima de acordo com o enunciado
		{
			printf("A quantidade de elementos deve ser maior que 0 e menor ou igual a 10000!\nDigite novamente!\n");
			system("PAUSE");
			system("cls");
		}
		
		
	system("cls");	
	}while (q>pow(aux,2)||(q>10000)||(q<1));//repete até que seja informado um parâmetro válido

	rel=Alocar_matriz(q,2); //aloca espaço para o conjunto RELAÇÃO
	
	srand(time(NULL));


//Gera a Relação com os elementos do Domínio

	for(i=0;i<q;i++)//q linhas
	{
		for(j=0;j<2;j++)// 2 colunas (par ordenado)
		{
			do
			{
				repetido=0;
				rel[i][j]=m+rand()%(n-m+1); // gera um número aleatório entre m e n (inclusive esses)
				if (i>0) // só compara a partir da digitação do segundo elemento da relação
				{
					for(k=0;k<i;k++)	
					{
						if ((j==1)&&(rel[i][0]==rel[k][0])&&(rel[i][1]==rel[k][1])) //quando gerado o segundo valor do par da relação (j==1), faz a compoaração com todos os outros pares lidos anteriormente
						{
							repetido=1;
							j=0; //possibilita a geração de dois novos valores para esse elemento da relação
						}
					}
				}
			}while (repetido); // força a geração de novo par, se o que foi gerado estiver repetido
		}
	}

//Verifica se a Relação é simétrica

	aux=0;
	for(i=0;i<q;i++)
	{
		achou=false;
				
		for(j=0;j<q;j++) // inicia a comparação
		{
			if (!achou)
				if ((rel[i][0]==rel[i][1])||(((rel[i][0]==rel[j][1])&&(rel[i][1]==rel[j][0]))))
					{
						achou=true;
						aux=aux+1; //conta a quantidade de pares simétricos encontrados no conjunto
					}
					else
						achou=false;
		}
	}
	if (aux==q) //caso a quantidade de pares simétricos seja igual a quantidade total de elementos do conjunto
		simetrico=true;
	else
	{
		QtdElemFecho=q+(q-aux);//a quantidade de elementos do fecho é o total de elementos da relação mais o total de elementos não simétricos (qtd de elementos adicionais a serem gerados)
		simetrico=false;
	}

	//caso a Relação gerada não seja simétrica
	if (!simetrico)
	{
		fechoS=Alocar_matriz(QtdElemFecho,2); //aloca espaço para o fecho simétrico da RELAÇÃO
		k=0;
		for(i=0;i<q;i++) //Gera o Fecho Simétrico
		{
			fechoS[k][0]=rel[i][0];
			fechoS[k][1]=rel[i][1];
			k=k+1;
			achou=false;
				
			for(j=0;j<q;j++)//vai percorrer toda a Relação (q elementos) 
			{
				if (!achou) // ainda não encontrou o par simétrico ao que está sendo testado
					if ((rel[i][0]==rel[i][1])||(((rel[i][0]==rel[j][1])&&(rel[i][1]==rel[j][0]))))// inicia a comparação para verificar para cada (x,y) se existe (y,x) ou se os elementos são iguais
						{
							achou=true; //encontrou o par ordenado simétrico a ele
						}
						else
							achou=false; // esse par não é simétrico a ele, continua procurando até chegar ao final dos elementos da Relação
			}
			if (!achou) //nenhum dos outros pares da Relação são simétricos ao que está sendo testado
			{
				//então gera o par ordenado simétrico ao que está sendo testado
				fechoS[k][0]=rel[i][1]; //primeiro elemento
				fechoS[k][1]=rel[i][0]; //segundo elemento
				k=k+1; //prepara para o próximo elemento
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
	
	//gera a saída de acordo com o enunciado
	if (!simetrico) //caso a relação não seja simétrica
	{
		printf("\n%d\n",simetrico);                   //imprime o valor 0 (simetrico=false=0)
		for (i=0;i<QtdElemFecho;i++)                  //imprime o Fecho simétrico gerado   
			printf("%d %d\n",fechoS[i][0],fechoS[i][1]);
	}
	else //caso seja simétrica
		printf("\n%d\n",simetrico); //imprime o valor 1 e encerra (simetrico=true=1)
	
	

	//libera o espaço de memória utilizado
	Liberar_matriz(q,2,rel);
	Liberar_matriz(QtdElemFecho,2,fechoS);

	system("PAUSE");
	return(0);
}




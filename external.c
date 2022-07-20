#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

int compara(const void *e1, const void *e2)
{
	return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}



int main(int argc, char**argv)
{
	FILE *f, *saida;
	Endereco *e;
	long posicao, qtd, tamanhoBloco, tot;
    char nomeArquivo[25], nomeA[12], nomeB[12],cepteste[8];  
    int n;
	double nteste1;
	int nteste2;
    int i;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [N]", argv[0]);
		return 1;
	}


	n = atoi(argv[1]);

	
	nteste1= log2l(n);
	nteste2= log2l(n);

	
	if(nteste1-nteste2==0){
		printf("Potencia de dois\n");
	}else{
		while(nteste1-nteste2!=0){

			n++;
			nteste1= log2l(n);
			nteste2= log2l(n);

		}
		printf("Convertido para %i\n",n);
	}
	

	f = fopen("cep.dat","rb");
	fseek(f,0,SEEK_END);
	posicao = ftell(f);
    rewind(f);
	qtd = posicao/sizeof(Endereco);

	tamanhoBloco= qtd/n;
	

    printf("\n\nSeparando arquivo");
   for(i=0;i<n;i++){
    int s=qtd%n>i?1:0;

    
    
    printf(".");
    e = (Endereco*) malloc((tamanhoBloco+s)*sizeof(Endereco));
	if(fread(e,sizeof(Endereco),tamanhoBloco+s,f) == tamanhoBloco+s)
	{
		printf(".");
	}
    qsort(e,tamanhoBloco+s,sizeof(Endereco),compara);
	printf(".");
    
    sprintf(nomeArquivo, "Cep_%d.dat", i);

    saida = fopen(nomeArquivo, "wb");
    fwrite(e, sizeof(Endereco), tamanhoBloco+s, saida);
    printf(".");
    free(e);
    fclose(saida);
   }
	

	
	
	

	fclose(f);
  	printf("\n\nintercalando");
    FILE *a, *b;
	Endereco ea, eb;
    int aux=0;

    int limite = (n*2)-1;
    
    while(i<limite){
    sprintf(nomeA, "Cep_%d.dat", aux);
    aux++;
    a = fopen(nomeA,"rb");
    sprintf(nomeB, "Cep_%d.dat", aux);
    b = fopen(nomeB,"rb");
    aux++;
	printf(".");
    

    if(i==limite-1){
        sprintf(nomeArquivo, "Cep_ordenado_merge.dat");
	    saida = fopen(nomeArquivo,"wb");
    }else{
    sprintf(nomeArquivo, "Cep_%d.dat", i);
	saida = fopen(nomeArquivo,"wb"); 
    }
    
    i++;
   
	fread(&ea,sizeof(Endereco),1,a);
	fread(&eb,sizeof(Endereco),1,b);

	while(!feof(a) && !feof(b))
	{
		if(compara(&ea,&eb)<0)
		{
			fwrite(&ea,sizeof(Endereco),1,saida);
			fread(&ea,sizeof(Endereco),1,a);
		}
		else
		{
			fwrite(&eb,sizeof(Endereco),1,saida);
			fread(&eb,sizeof(Endereco),1,b);
		}
	}

	while(!feof(a))
	{
		fwrite(&ea,sizeof(Endereco),1,saida);
		fread(&ea,sizeof(Endereco),1,a);		
	}
	while(!feof(b))
	{
		fwrite(&eb,sizeof(Endereco),1,saida);
		fread(&eb,sizeof(Endereco),1,b);		
	}

	remove(nomeA);
	remove(nomeB);
    
	fclose(a);
	fclose(b);
	fclose(saida);
    }

	//em caso de problemas com a remoção de arquivos
	int remover = 0;
	while(remover<limite-1){
		sprintf(nomeA, "Cep_%d.dat", remover);
		remove(nomeA);
		remover++;

	}
   

    printf("\n\nPrograma concluido");
	
}



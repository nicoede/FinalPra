#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mainB.h"

int main(){

	createHeader();
	inserir(4);
	
	return 0;

}

void createHeader(){
    FILE *arqEnt, *configDB;
    char linha[275], entidade[15];
    int nEntidades, tamHeader;
    int i;
    
    configDB=fopen("configDB.txt", "r");
    if(configDB == NULL){
	   	printf("Erro ao abrir arquivo de configuracao do banco de dados\n");
		exit(2);
    }
    fscanf(configDB, "nEntidades=%d\n", &nEntidades);
    
    for(i=0;i<nEntidades;i++){
		fscanf(configDB, "tamHeader=%d", &tamHeader);
		fseek(configDB, -13, SEEK_CUR);
		fread(linha, sizeof(char), tamHeader, configDB);
		linha[tamHeader]='\0';
		sscanf(linha+14, "entidade=[%s ]", entidade);
		arqEnt=fopen(entidade, "r");
		if(arqEnt == NULL){
			arqEnt=fopen(entidade, "w");
			if(arqEnt == NULL){
				printf("Erro ao criar arquivo de entidade\n");
				exit(2);
			}
			fprintf(arqEnt, "CADEABABA\n");
			fprintf(arqEnt, "%s", linha);
		}
		fclose(arqEnt);
		
    }
    
}

void inserir(int opcE){
    char linhaHeader[275];
    char *pos=NULL;
    int i;
    int tamLinhaDados;
    Tabela tab;
    FILE *arqEnt;
    
    switch (opcE){
    	case 1:
    		arqEnt=fopen("Livro", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 2:
    		arqEnt=fopen("Leitor", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 3:
    		arqEnt=fopen("Autor", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 4:
    		arqEnt=fopen("AutorDoLivro", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	case 5:
    		arqEnt=fopen("Emprestimo", "r+");
    		if(arqEnt==NULL){
    			printf("Erro ao abrir arquivo de entidade\n");
    			exit(2);
    		}
    		break;
    	default:
    		printf("Isso nunca deveria aontecer ._.\n");
    		printf("Alguma coisa deu muito errado\n");
    		exit(2);
    }
    fread(linhaHeader, sizeof(char), 10, arqEnt);
    linhaHeader[9]='\0';
    printf("%s\n", linhaHeader);
    if(strcmp(linhaHeader, "CADEABABA")!=0){
    	printf("Arquivo de entidade inválido\n");
    	exit(2);
    }
    
    tab = lerHeader(arqEnt);
    
    printf("%d\n", tab.qtdCampos);
    
    
}

Tabela lerHeader(FILE *arqEnt){
	char linhaHeader[275];
    char *pos=NULL;
    int i;
    Tabela tab;
	
	fscanf(arqEnt, "tamHeader=%d", &(tab.tamHeader));
    
    printf("Leu o tamanho\n");
    printf("tamHeader=%d\n", tab.tamHeader);
	fseek(arqEnt, -13, SEEK_CUR);
	fread(linhaHeader, sizeof(char), tab.tamHeader, arqEnt);
	linhaHeader[tab.tamHeader]='\0';
	
	pos = strstr(linhaHeader, ",qtdCampos=");
	sscanf(pos, ",qtdCampos=[%d]", &tab.qtdCampos);	
	
	pos = strstr(linhaHeader, ",campos=");
	pos+=9;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%s", tab.campos[i]);
		printf("%s\n", tab.campos[i]);
		pos+=(2+strlen(tab.campos[i]));
	}
	
	pos = strstr(linhaHeader, ",tamanho=");
	pos+=10;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%d", &(tab.tamanhos[i]));
		printf("%d\n", tab.tamanhos[i]);
		while((pos[0]!=',')&&(pos[0]!=']')){
			pos++;
		}
		pos++;
	}
	
	pos = strstr(linhaHeader, ",tipo=");
	pos+=7;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%s", tab.tipos[i]);
		printf("%s\n", tab.tipos[i]);
		pos+=(2+strlen(tab.tipos[i]));
	}
    
    pos = strstr(linhaHeader, ",null=");
	pos+=7;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%d", &(tab.null[i]));
		printf("%d\n", tab.null[i]);
		pos+=2;
	}
	
	pos = strstr(linhaHeader, ",autoIncrement=");
	pos+=16;
	for(i=0;i<tab.qtdCampos;i++){
		sscanf(pos, "%d", &(tab.autoInc[i]));
		printf("%d\n", tab.autoInc[i]);
		pos+=2;
	}
	
	pos = strstr(linhaHeader, ",nPk=");
	sscanf(pos, ",nPk=[%d]", &tab.nPk);
	printf("%d\n", tab.nPk);
	
	pos = strstr(linhaHeader, ",pk=");
	pos+=5;
	for(i=0;i<tab.nPk;i++){
		sscanf(pos, "%s", tab.pk[i]);
		printf("%s\n", tab.pk[i]);
		pos+=(2+strlen(tab.pk[i]));
	}
	
	return tab;
}



















#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAM 5000
/*
                        Trabalho 2 de Programação 2
        Alunos: Luiz Gustavo Gomes Damasceno e Pedro Caliman Cecato
                                Turma: V01
                Sistemas de Informação - IFES Campus Colatina
*/

//Criação de structs

typedef struct Fabricante{
    
    char nome[TAM];
    char nacionalidade[TAM]; 
    
}Fabricante;

typedef struct Aviao{

    int ident;
    int ano_elaboracao;
    int ano_fabricacao;
    char modelo[TAM];
    Fabricante *fabricante;

}Aviao;

Fabricante *lerFabricantes(Fabricante *x){

    int i=0;
    int j,contFab=3;

    //Abertura de Arquivo

    FILE * fp = fopen ("fabricantes.txt","r");

    if (!fp)
	    printf ("\nErro na abertura do arquivo.\n");
    else
        printf("\nArquivo aberto com sucesso.\n");
    
    //Leitura de Arquivo

    while(!feof(fp)){
        fscanf(fp, "%s", x[i].nome);
        fscanf(fp, "%s", x[i].nacionalidade);
        i++;
    }
    
    //Fechamento de Arquivo

    if (fclose(fp) == 0)
        printf ("\nArquivo fechado com sucesso\n\n");
    else
        printf("\nErro no fechamento do arquivo\n\n");
        

    return x;
}

int ehSubstring(char *sub, char *fab){
    int i;

    int qt_str=strlen(fab);
    int qt_sub=strlen(sub);
    int qt;

    if(qt_str >= qt_sub)
        qt = qt_sub;
    else
        return 0;
        
    for(i=0;i<qt;i++){
        if(fab[i] != sub[i]){
            return 0;
        }
    }
    return 1;
}

int obterFab(Fabricante *fab, int n, char *nomeFabProc){
    
    int i;
    for(i=0;i<n;i++){
        if(ehSubstring(nomeFabProc,fab[i].nome)){
            return i;
        }
        
    }
    return 0;
}

Aviao * lerAvioes(Fabricante *fabricante, Aviao *avioes, int contFab){
    
    int i = 0;
    int contAviao = 4;
    char nomeFab[50];
    int ind_fab = 0;

    //Abertura de Arquivo

    FILE * fp = fopen ("avioes.txt","r");

    if (!fp)
	    printf ("\nErro na abertura do arquivo.\n");
    else
        printf("\nArquivo aberto com sucesso.\n");
    
    //Leitura de Arquivo

    while(!feof(fp)){


        fscanf(fp, "%d", &(avioes[i].ident));
        fscanf(fp, "%d", &(avioes[i].ano_elaboracao));
        fscanf(fp, "%d", &(avioes[i].ano_fabricacao));
        fscanf(fp, "%s", avioes[i].modelo);
        fscanf(fp, "%s", nomeFab);
        ind_fab = obterFab(fabricante, contFab, nomeFab);
        avioes[i].fabricante = &fabricante[ind_fab];
        
        i++;
    }

    //Fechamento de Arquivo

    if (fclose(fp) == 0)
        printf ("\nArquivo fechado com sucesso\n\n");
    else
        printf("\nErro no fechamento do arquivo\n\n");
        
    return avioes;

    
}

void imprimirFabricantes(Fabricante *x, int n){
    int i;
    for(i=0;i<n;i++)
        printf("O Fabricante é: %s, e sua nacionalidade é: %s\n", x[i].nome,x[i].nacionalidade);
}

void imprimirAviao(Aviao *avioes, int n){
    int i;
    for(i = 0;i < n;i++){
        printf("Referente ao Avião:\nO nº de identificação é: %d\nAno de elaboração do projeto é: %d\nAno de fabricação é: %d\nO modelo do avião é: %s\nO nome do fabricante é: %s\nA nacionalidade do Fabricante é:%s\n\n", avioes[i].ident,avioes[i].ano_elaboracao,avioes[i].ano_fabricacao,avioes[i].modelo,avioes[i].fabricante->nome,avioes[i].fabricante->nacionalidade);
    }
}

int contarAvioesDeFab(Aviao *avioes, char *fab, int contAviao){
    int i,j=0;
    int qtAviao = 0;

    while(j<contAviao){

        if(ehSubstring(fab, avioes[j].fabricante->nome)){
            qtAviao++;
            j++;
        }else
            j++;
    }

    return qtAviao;
}

void imprimirAviaoDeFab(Aviao *avioes, Fabricante *fab, int contFab, int contAviao){
    int i,j;
    int qtAvioes = 0;
    for(i=0;i<contFab;i++){

        qtAvioes = contarAvioesDeFab(avioes,fab[i].nome,contAviao);

        if(qtAvioes < 1)
            printf("O fabricante %s não possui aeronaves\n\n",fab[i].nome);

        else if(qtAvioes == 1)
            printf("O fabricante %s possui 1 aeronave\n\n"
            "Referente ao Avião do fabricante %s:\n\n",fab[i].nome,fab[i].nome);
        else{
        
            printf("O fabricante %s possui %d  aeronaves\n\n"
            "Referente aos Aviões do fabricante %s:\n\n",fab[i].nome, qtAvioes,fab[i].nome);
        }

        for(j=0;j<contAviao;j++){
            if(ehSubstring(fab[i].nome, avioes[j].fabricante->nome)){
                printf("O nº de identificação é: %d\nAno de elaboração do projeto é: %d\nAno de fabricação é: %d\nO modelo do avião é: %s\n\n",avioes[j].ident,avioes[j].ano_elaboracao,avioes[j].ano_fabricacao,avioes[j].modelo);
            }
        }

        printf("------------------------------------------\n\n");    
    }
}

void imprimirItalianos(Aviao *avioes, Fabricante *fab, int contAviao){

    int i;
    int cap=0;

    for(i=0;i<contAviao;i++){
        if((ehSubstring(fab[i].nacionalidade, "Italiana")) && avioes[i].ano_elaboracao == avioes[i].ano_fabricacao){
            printf("O fabricante Italiana é: %s\n"
            "E referente ao Avião com mesmo ano de fabricação e elaboração:\n",fab[i].nome);

            printf("\nO nº de identificação é: %d\nAno de elaboração do projeto é: %d\nAno de fabricação é: %d\nO modelo do avião é: %s\n\n",avioes[i].ident,avioes[i].ano_elaboracao,avioes[i].ano_fabricacao,avioes[i].modelo); 

            cap++;
        }
    }
    if(cap < 1)
        printf("Não existe avião com fabricante Italiana\ne ano de elaboração igual ao ano de fabricação\n\n");
    
    printf("------------------------------------------\n\n");
}

void imprimirEuropeus(Aviao *avioes, Fabricante *fab, int contAviao){

    int i;
    int cap=0;

    for(i=0;i<contAviao;i++){
        if((ehSubstring(fab[i].nacionalidade, "Europeu")) && avioes[i].ident < 1000){
            printf("O fabricante Europeu é: %s\n"
            "E referente ao Avião com Nº de identificação menor que 1000:\n",fab[i].nome);

            printf("\nO nº de identificação é: %d\nAno de elaboração do projeto é: %d\nAno de fabricação é: %d\nO modelo do avião é: %s\n\n",avioes[i].ident,avioes[i].ano_elaboracao,avioes[i].ano_fabricacao,avioes[i].modelo); 

            cap++;
        }
    }
    if(cap < 1)
        printf("Não existe avião com fabricante Europeu\ne Nº de identificação menor que 1000\n\n");

    printf("------------------------------------------\n\n");
}

int temAU(char *modelo){

    int i;
    int qt = strlen(modelo);
    int verifU=0;
    int verifA=0;

    for(i=0;i<qt;i++){

        switch(modelo[i]){
            case 'a':
                verifA++;
            break;

            case 'u':
                verifU++;
            break;
        }
    }

    if((verifA > 0) && (verifU > 0))
        return 1;
    else
        return 0;
}

void imprimirSemAU(Aviao *avioes, Fabricante *fab, int contAviao){

    int i,j;
    int cap=0;

    for(i=0;i<contAviao;i++){

        if(temAU(avioes[i].modelo)){
            printf("O fabricante com modelo 'A' e 'U' é: %s\n"
            "E referente ao Avião com 'a' e 'u' no nome de seu modelo:\n",avioes[i].fabricante->nome);

            printf("\nO nº de identificação é: %d\nAno de elaboração do projeto é: %d\nAno de fabricação é: %d\nO modelo do avião é: %s\n\n",avioes[i].ident,avioes[i].ano_elaboracao,avioes[i].ano_fabricacao,avioes[i].modelo);

            cap++;
        }
    }

    if(cap < 1)
        printf("Não existem fabricantes que tenham aviões que possuam a letra 'a' e a letra 'u' no nome do seu modelo.\n\n");

    printf("------------------------------------------\n\n");
}

int main(){

	setlocale(LC_ALL,"Portuguese");

    //Declaração de Variáveis

    int contFab = 4, contAviao = 4;

    Fabricante fab[contFab];
    Aviao aviao[contAviao];
    
    //Leitura de Dados
    lerFabricantes(fab);
    //imprimirFabricantes(fab,contFab);

    lerAvioes(fab,aviao,contFab);
    //imprimirAviao(aviao,contAviao);

    imprimirAviaoDeFab(aviao, fab, contFab, contAviao);
    imprimirItalianos(aviao,fab,contAviao);
    imprimirEuropeus(aviao,fab,contAviao);
    imprimirSemAU(aviao,fab,contAviao);
    
    return 0;
    
}
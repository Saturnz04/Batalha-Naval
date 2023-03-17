#include <stdio.h>
#include <stdlib.h>
#include<time.h>
// funcao para sortear rand();
// 25 chances
// funcao para ver se o jogador acertou todos ou esgotou de municao, e se acertou retornar onde
//funcão para printar matriz
//clearScreen
int verificarMatrizValida(char M[][10]){
    int w = 0;
    for(int i=0; i<10;i++){
        for(int j=0; j<10; j++){
            if(M[i][j] == 'W'){
                w = w + 1;
            }
        }
    }
    if(w==17){
            return 0;
    }else{
        return 1;
    }
}
void criarNavio(int tamanho, char M[][10]){
    int navioLinha = rand()%10;
    int navioColuna = rand()%(11-tamanho);
    for(int c = 0; c<tamanho; c++){
            M[navioLinha][navioColuna+c] = 'W';
    }

}
void imprimirMatriz(char M[][10]){
    system("cls");
    printf("\tB A T A L H A    N A V A L");
    for(int i=0; i<10;i++)
    {
        printf("\n-----------------------------------------\n");
        for(int j=0; j<10; j++)
        {
            printf("| %c ", M[i][j]);
        }
        printf("|");
    }
    printf("\n-----------------------------------------\n");
}
int permitirTiro(char M[][10], char M2[][10]){
    int n = 0;
    scanf("%i", &n);
    n = n -1;
    int linha = (n - n%10)/10;
    int coluna = n%10;
    int resposta = 0;

    if(n<100&&n>=0){
        if(M[linha][coluna]=='x'||M[linha][coluna]=='o'){
            imprimirMatriz(M);
            printf("\nNUMERO JA ESCOLHIDO! DIGITE OUTRO NUMERO: ");
            resposta = permitirTiro(M, M2);
        } else {
            if(M2[linha][coluna]=='W'){
                M[linha][coluna]='x';
                M2[linha][coluna]='x';
                resposta = 1;
            } else {
                M[linha][coluna]='o';
                resposta = 0;
            }
        }
    }else{
        imprimirMatriz(M);
        printf("\nNUMERO INVALIDO! DIGITE OUTRO NUMERO: ");
        resposta = permitirTiro(M, M2);
    }
    return (resposta);
}

int main(){
    //Criando Matriz
    int pontosRestantes = 17;
    int municaoRestante = 25;
    char M[10][10];
    char M2[10][10];
    for(int i=0; i<10;i++){
        for(int j=0; j<10; j++){
            M[i][j] = ' ';
            M2[i][j]= '~';
        }
    }

    //Criando e Posicionando Navios
    srand(time(NULL));
    criarNavio(4,M2);
    criarNavio(3,M2);
    criarNavio(3,M2);
    criarNavio(2,M2);
    for(int c=0; c<5; c++){
        criarNavio(1, M2);
    }

    //Vendo se tem quantidade certa de navios
    while((verificarMatrizValida(M2))==1){
        criarNavio(1, M2);}

    //GAME START!
    while(municaoRestante>0 && pontosRestantes>0){
        imprimirMatriz(M);
        printf("\nMunicao restante: %i", municaoRestante);
        printf("\n\nDigite o numero que corresponde a onde quer atirar: ");
        pontosRestantes = pontosRestantes - permitirTiro(M, M2);
        municaoRestante = municaoRestante -1;
    }

    if(pontosRestantes==0){
        imprimirMatriz(M2);
        printf("\nMunicao restante: %i", municaoRestante);
        printf("\n\nVOCE GANHOU!!! PARABENS!!!\n");
    } else {
        imprimirMatriz(M2);
        printf("\nSUA MUNICAO ACABOU! TENTE NOVAMENTE \nFALTARAM %i TIROS PARA VOCE GANHAR O JOGO\n", pontosRestantes);
    }
        return 0;

}

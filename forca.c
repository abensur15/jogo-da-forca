#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

char letras[26], palavraSecreta[26], chutesErrados[7];
int chutou[26] = {0};
int tentativas = 0;

//Sorteia uma das palavras a seguir
char* sortearPalavra(){
	char palavras[26][26] = {
		{"ALGORITMO"}, {"BOOLEAN"}, {"CODEBENCH"}, {"CODIGO"}, 
		{"CONDICIONAL"}, {"DESENVOLVEDOR"}, {"DADOS"}, {"ERROS"}, 
		{"ESTRUTURA"}, {"FUNCOES"}, {"HELLOWORLD"}, {"ICOMP"}, 
		{"JAVASCRIPT"}, {"MATRIZ"}, {"PROGRAMACAO"}, {"PONTEIRO"}, 
		{"PROJETO"}, {"PYTHON"}, {"SISTEMA"}, {"SOFTWARE"}, 
		{"STRING"}, {"TERMINAL"}, {"TESTES"}, {"VARIAVEL"}, {"VETOR"}
	};
	
	srand(time(NULL));
	
	int palavraRandomica = rand() % 26;
	
	strcpy(palavraSecreta, palavras[palavraRandomica]);
	
	return palavraSecreta;
}

//Verifica se o caractere eh uma entrada valida
int validarEntrada(char chute){
	if(chute >= 'A' && chute <= 'Z'){
		return 1;
	}
	else{
		printf("Erro! O caractere digitado eh invalido!\n");
		return 0;
	}
}

//Verifica se as letras existem na palavra secreta
int letraExiste(char chute, char *palavraSecreta){
	int acertou = 0;
	
	for(int letra = 0; letra < strlen(palavraSecreta); letra++){
		if(chute == palavraSecreta[letra]){
			chutou[letra] = 1;
			acertou = 1;
		}
	}
	
	if(!acertou){
		chutesErrados[tentativas] = chute;
		tentativas++;
	}
	
	return acertou;
}

//Imprime a situacao do chute
void chutarLetra(char chute, char *palavraSecreta){
	if(letraExiste(chute, palavraSecreta)){
		printf("\nVoce acertou! A letra que voce chutou esta na palavra.\n");
	}
	else{
		printf("\nVoce errou! A letra nao esta na palavra.\n");
	}
}

//Imprime a palavra secreta
void imprimirPalavra(char *palavraSecreta, int *chutou){
	for(int letra = 0; letra < strlen(palavraSecreta); letra++){
		if(chutou[letra]){
			printf("%c ", palavraSecreta[letra]);
		}
		else{
			printf("_ ");
		}
	}
	
	printf("\n");
}

//Imprime as letras que nao existem na palavra secreta
void imprimirErros(char *chutesErrados){
	printf("Chutes errados: ");
	
	for(int letra = 0; letra < tentativas; letra++){
		printf("%c ", chutesErrados[letra]);
	}
	
	printf("\n");
}

//Verifica se o jogador nao acertou a palavra secreta
int naoAcertou(char *palavraSecreta, int *chutou){
	for(int letra = 0; letra < strlen(palavraSecreta); letra++){
		if(!chutou[letra]){
			return 1;
		}
	}
	
	return 0;
}

//Verifica se o jogador foi "enforcado"
int naoEnforcou(int tentativas){
	return tentativas < 7;
}

//Imprime a tela de fim do jogo
void imprimirFim(char *palavraSecreta){
	printf("\nFim de jogo!\n");
	
	if(naoAcertou(palavraSecreta, chutou)){
		printf("Que pena, voce perdeu!\n");
		printf("A palavra secreta era: %s\n", palavraSecreta);
	}
	else{
		printf("Parabens, voce acertou a palavra secreta!\n");
	}
}

//Executa as funcoes do jogo
int main(){
	char chute;
	
	printf("Seja bem-vindo(a) ao Jogo da Forca!\n");
	sortearPalavra();
	
	while(naoAcertou(palavraSecreta, chutou) && naoEnforcou(tentativas)){
		printf("\nDigite uma letra maiuscula: \n");
		scanf(" %c", &chute);
		
		while(!validarEntrada(chute)){
			scanf(" %c", &chute);
		}
		
		chutarLetra(chute, palavraSecreta);

		printf("Palavra: ");
		imprimirPalavra(palavraSecreta, chutou);
		imprimirErros(chutesErrados);
	}
	
	imprimirFim(palavraSecreta);

	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void producoes(int estado, char cadeia[], int i, int tamanho){
	
	int j = 0;
	printf("(q%d,", estado);
	for (j; j <= i; j++){
		printf("%c", cadeia[j]);
	}
	printf(", ");
	for (j; j < tamanho; j++)
	{
		printf("%c", cadeia[j]);
	}
	printf(") ➜ ");
}

void decisao (int dec, char cadeia[], char cadeiaaux[], int tamanho, int i) {
	
	if (dec == 1){
		int j = 0;
		printf("(qSim, ");
		for (j; j <= i; j++){
			printf("%c", cadeia[j]);
		}
		printf(", ");
		for (j; j < tamanho; j++){
			printf("%c", cadeia[j]);
		}
		printf(")\n\n");
		printf("M(%s) = qSim\n\n\n", cadeiaaux);
	}
	else if (dec == -1){
		int j = 0;
		printf("(qNao, ");
		for (j; j <= i; j++){
			printf("%c", cadeia[j]);
		}
		printf(", ");
		for (j; j < tamanho; j++){
			printf("%c", cadeia[j]);
		}
		printf(")\n\n");
		printf("M(%s) = qNao\n\n\n", cadeiaaux);
	}
}


void maquina(char cadeia[], int tamanho, char cadeiaaux[]){
	
	int estado = 0;
	int i = 0;
	producoes(estado, cadeia, i, tamanho);
	
	do{
		if (estado == 0){ //q0	
			if(cadeia[i] == '>'){
				cadeia[i] = '>';
				i++;			
				producoes(estado, cadeia, i, tamanho);
				estado = 0;
			}
			else if(cadeia[i] == '0'){
				cadeia[i] = '>';
				i++;
				producoes(estado, cadeia, i, tamanho);
				estado = 1;

			}
			else if(cadeia[i] == '1'){
				cadeia[i] = '>';
				i++;
				producoes(estado, cadeia, i, tamanho);
				estado = 2;
			}
			else if(cadeia[i] == 'U'){
				cadeia[i] = 'U';
				producoes(estado, cadeia, i, tamanho);
				estado = 6;
				break;
			}
		}
		else if(estado == 1){ //qLi-zero
			if(cadeia[i] == '0'){
				cadeia[i] = '0';
				i++;
				producoes(estado, cadeia, i, tamanho);
				estado = 1;
			}
			else if(cadeia[i] == '1'){
				cadeia[i] = '1';
				i++;
				producoes(estado, cadeia, i, tamanho);
				estado = 1;
			}
			else if(cadeia[i] == 'U'){
				cadeia[i] = 'U';
				i--;	
				producoes(estado, cadeia, i, tamanho);
				estado = 3;
			}
		}
		else if(estado == 2){ //qLi-um			
			if(cadeia[i] == '0'){
				cadeia[i] = '0';
				i++;
				producoes(estado, cadeia, i, tamanho);
				estado = 2;
			}
			else if(cadeia[i] == '1'){
				cadeia[i] = '1';
				i++;
				producoes(estado, cadeia, i, tamanho);
				estado = 2;
			}
			else if(cadeia[i] == 'U'){
				cadeia[i] = 'U';
				i--;				
				producoes(estado, cadeia, i, tamanho);
				estado = 4;
			}
		}
		else if(estado == 3){ //qTeste-zero
			if(cadeia[i] == '>'){
				cadeia[i] = '>';
				producoes(estado, cadeia, i, tamanho);
				estado = 6;
				break;
			}
			else if(cadeia[i] == '0'){
				cadeia[i] = 'U';
				i--;
				producoes(estado, cadeia, i, tamanho);
				estado = 5;
			}
			else if(cadeia[i] == '1'){
				cadeia[i] = '1';
				producoes(estado, cadeia, i, tamanho);
				estado = 7;
				break;
			}			
		}
		else if(estado == 4){ //qTeste-um
			if(cadeia[i] == '>'){
				cadeia[i] = '>';
				producoes(estado, cadeia, i, tamanho);
				estado = 6;
				break;
			}
			else if(cadeia[i] == '0'){
				cadeia[i] = '0';
				producoes(estado, cadeia, i, tamanho);
				estado = 7;
				break;
			}
			else if(cadeia[i] == '1'){
				cadeia[i] = 'U';
				i--;
				producoes(estado, cadeia, i, tamanho);
				estado = 5;
			}			
		}
		else if(estado == 5){ //q←
			if(cadeia[i] == '>'){
				cadeia[i] = '>';
				i++;
				producoes(estado, cadeia, i, tamanho);
				estado = 0;
			}
			else if(cadeia[i] == '0'){
				cadeia[i] = '0';
				i--;
				producoes(estado, cadeia, i, tamanho);
				estado = 5;
			}
			else if(cadeia[i] == '1'){
				cadeia[i] = '1';
				i--;
				producoes(estado, cadeia, i, tamanho);
				estado = 5;
			}			
		}

	}while (estado != 6 && estado != 7);
	
	int dec;
	if (estado == 6){
		dec = 1;
		decisao(dec, cadeia, cadeiaaux, tamanho, i);
	} else{
		dec = -1;
		decisao(dec, cadeia, cadeiaaux, tamanho, i);
	}
}



int main(){
	int op = 2, i, tamanho;
	char cadeia[20], cadeiaaux[19];
	
	do{
		printf("Problema do Palindromo\n\n");
		printf("1 - Inserir uma cadeia de bits\n");
		printf("0 - Sair\n\n");
		
		scanf("%d", &op);
		printf ("\n");
		
		switch (op){
			
			case 1:
			cadeia[0] = '>';
			printf("Digite a cadeia\n");
			scanf("%s", cadeiaaux);
			tamanho = strlen(cadeiaaux);

			for (i = 0; i < tamanho; i++){
				cadeia[(i+1)] = cadeiaaux[i];
			}
			
			i++;
			cadeia[i] = 'U';
			i++;
			cadeia[i] = 'U';
			tamanho += 3;
			printf ("\n");
			maquina(cadeia, tamanho, cadeiaaux);
			break;		
		}	

	}while (op != 0);
}

/*
estado 0 ➜ q0
estado 1 ➜ qLi-zero
estado 2 ➜ qLi-um
estado 3 ➜ qTeste-zero
estado 4 ➜ qTeste-um
estado 5 ➜ q←
estado 6 ➜ qSim
estado 7 ➜ qNao
*/
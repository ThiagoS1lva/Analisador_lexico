#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <bits/stdc++.h> 
#include <algorithm>
using namespace std; 

//TOKENS
#define IF 256;
#define THEN 257;
#define ELSE 258;
#define RELOP 259;
#define ID 260;
#define NUM 261;
#define PROGRAM 262;
#define VAR 263;
#define BEGIN 264;
#define END 265;
#define WHILE 266;
#define DO 267;
#define INT 268;
#define OPERATION 276;
#define PONTUATION 277;
#define PR 282;

//ATRIBUTOS
#define LT 269;
#define LE 270;
#define EQ 271;
#define NE 272;
#define GT 273;
#define GE 274;
#define A 275;
#define SOMA 278;
#define SUBT 279;
#define MULTI 280;
#define DIV 281;
#define ETC 283;



struct Token{
 int nome_token;
 int atributo;
};

int estado = 0;
int partida = 0;
int aux = 0;
int aux1 = 0;
int cont_sim_lido = 0;
char listaN[10];
char listaL[10];
std::vector<std::string> listaR = { "if", "then", "else", "program", "var", "begin", "end" , "while", "do", "int" };
std::vector<std::string> listaID = {};

char *code;
string str = ""; 
int size_arr = sizeof(listaL) / sizeof(char); 


int falhar()
{
	switch(estado)
	{
	case 0: partida = 9; break;

	case 9: partida = 12; break;

	case 12: partida = 17; break;

	case 17: partida = 20; break;
	
	case 20: partida = 29; break;

	case 29:
		//retornar msg de erro caso o caractere não pertença a linguagem
		printf(", Esse caractere nao pertence a linguagem! >\n");
		cont_sim_lido++;
		break;

	default: printf("Erro do compilador");
	}
	return(partida);
}



Token proximo_token()
{
	Token token;
	char c;
	while(code[cont_sim_lido] != EOF)
	{
		switch(estado)
		{
			//Case 0 até Case 8 Analisar os operadores lógicos
			case 0:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else if(c == '<') estado = 1;
				else if(c == '=') estado = 5;
				else if(c == '>') estado = 6;
				else
					{
					 estado = falhar();
					}
				break;

			case 1:
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(c == '=') estado = 2;
				else if(c == '>') estado = 3;
				else estado = 4;
				break;

			case 2:
				cont_sim_lido++;
				printf("<relop, LE>\n");
				token.nome_token = RELOP;
				token.atributo = LE;
				estado = 0;
				return(token);
				break;

			case 3:
				cont_sim_lido++;
				printf("<relop, NE>\n");
				token.nome_token = RELOP;
				token.atributo = NE;
				estado = 0;
				return(token);
				break;

			case 4:
				printf("<relop, LT>\n");
				token.nome_token = RELOP;
				token.atributo = LT;
				estado = 0;
				return(token);
				break;

			case 5:
				cont_sim_lido++;
				printf("<relop, EQ>\n");
				token.nome_token = RELOP;
				token.atributo = EQ;
				estado = 0;
				return(token);
				break;

			case 6:
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if(c == '=') estado = 7;
				else estado = 8;
				break;

			case 7:
				cont_sim_lido++;
				printf("<relop, GE>\n");
				token.nome_token = RELOP;
				token.atributo = GE;
				estado = 0;
				return(token);
				break;

			case 8:
				printf("<relop, GT>\n");
				token.nome_token = RELOP;
				token.atributo = GT;
				estado = 0;
				return(token);
				break;

			//Case 9 até 11 analisa os ID's e as palavras reservadas
			case 9:
				c = code[cont_sim_lido];
				aux1 = 0;
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else if (isalpha(c)) {
						listaL[0] = c;
						estado = 10;
					}
				else {
					estado = falhar();
				}
				break;
				
			case 10:
				cont_sim_lido++;
				c = code[cont_sim_lido];
				
				if ((isalpha(c)) || (isdigit(c))) {
					aux1++;
					listaL[aux1] = c;
					estado = 10;
				} else {
					estado = 11;
				}
				break;
				
			case 11:	
				//Converte um array de char para string
				str = ""; 
				for (int y = 0; y <= aux1; y++) { 
					str = str + listaL[y]; 
				} 
				//Verifica se a palavra digitada é uma reservada, ou seja, se está na lista (listaR)
				if (std::find(listaR.begin(), listaR.end(), str) != listaR.end()){
					printf("<");
					cout << str; 
					printf(" > \n");
				//Se não estiver na lista de palavras reservadas, então é um ID
				} else if (std::find(listaID.begin(), listaID.end(), str) != listaID.end()) {
					//Verifica se o ID já está na lista de ID (listaID)
					auto it = std::find(listaID.begin(), listaID.end(), str);
					if (it != listaID.end()) {
						std::cout << "<ID, " << std::distance(listaID.begin(), it) << ">" << std::endl;
						token.nome_token = ID;
						token.atributo = std::distance(listaID.begin(), it);
					}
				//Se não estiver na listaID, então ela é adicionada.
				} else {
					listaID.push_back(str);
					auto it = std::find(listaID.begin(), listaID.end(), str);
					if (it != listaID.end()) {
						std::cout << "<ID, " << std::distance(listaID.begin(), it) << ">" << std::endl;
						token.nome_token = ID;
						token.atributo = std::distance(listaID.begin(), it);
					}
				}
				if (str == "if") {
					token.nome_token = PR;
					token.atributo = IF;
				} else if (str == "else"){
					token.nome_token = PR;
					token.atributo = ELSE;
				} else if (str == "then"){
					token.nome_token = PR;
					token.atributo = THEN;	
				} else if (str == "program"){
					token.nome_token = PR;
					token.atributo = PROGRAM;
				} else if (str == "var"){
					token.nome_token = PR;
					token.atributo = VAR;
				} else if (str == "begin"){
					token.nome_token = PR;
					token.atributo = BEGIN;
				} else if (str == "end"){
					token.nome_token = PR;
					token.atributo = END;
				} else if (str == "while"){
					token.nome_token = PR;
					token.atributo = WHILE;
				} else if (str == "do"){
					token.nome_token = PR;
					token.atributo = DO;
				} else if (str == "int"){
					token.nome_token = PR;
					token.atributo = INT;
				} 
				
				
				// esvazia listaL				
				for(int i = 0; i < sizeof(listaL); ++i)
				{
				  listaL[i] = (char)0;
				}  
				estado = 0;
				return (token);
				break;
			
			//Case 12 até Case até Case 16 são os operadores matematicos
			case 12:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else if(c == '+') estado = 13;
				else if(c == '-') estado = 14;
				else if(c == '*') estado = 15;
				else if(c == '/') estado = 16;
				
				else
					{
					 estado = falhar();
					}
				break;

			case 13:
				cont_sim_lido++;
				printf("<operation, + >\n");
				token.nome_token = OPERATION;
				token.atributo = SOMA;
				estado = 0;
				return(token);
				break;

			case 14:
				cont_sim_lido++;
				printf("<operation, - >\n");
				token.nome_token = OPERATION;
				token.atributo = SUBT;
				estado = 0;
				return(token);
				break;

			case 15:
				cont_sim_lido++;
				printf("<operation, * >\n");
				token.nome_token = OPERATION;
				token.atributo = MULTI;
				estado = 0;
				return(token);
				break;

			case 16:
				cont_sim_lido++;
				printf("<operation, / >\n");
				token.nome_token = OPERATION;
				token.atributo = DIV;
				estado = 0;
				return(token);
				break;

			//Do case 17 até 19 trata os numeros
			case 17:
				c = code[cont_sim_lido];
				aux = 0;
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else if (isdigit(c)) {
					//Primeiro numero é adicionado a listaN na posição 0.
						listaN[0] = c;
						estado = 18;
					}
				else {
					estado = falhar();
				}
				break;
				
			case 18:
				cont_sim_lido++;
				c = code[cont_sim_lido];
				if (isdigit(c)) {
					aux++;
					//Os proximos numeros é adicionado nas proximas posições
					listaN[aux] = c;
					estado = 18;
				} else {
					estado = 19;
				}
				break;
				
			case 19:				

				str = ""; 
				for (int y = 0; y <= aux; y++) { 
					str = str + listaN[y]; 
				} 
				
				//printa o número digitado de acordo.				
				printf("<Num,");
				cout << str; 
				printf(" > \n");
		
				// esvazia listaN				
				for(int i = 0; i < sizeof(listaN); ++i)
				{
				  listaN[i] = (char)0;
				} 
						
				token.nome_token = NUM;
				token.atributo = stoi(str);
				estado = 0;
				return (token);
				break;
		

			//Do case 20 até o case 28 Trata o parenteses, virgula, ponto e virgula, dois pontos, ponto e sinal de atribuição.
			case 20:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else if(c == '(') estado = 21;
				else if(c == ')') estado = 22;
				else if(c == ',') estado = 23;
				else if(c == ';') estado = 24;
				else if(c == ':') estado = 25;
				else if(c == '.') estado = 28;
				
				else
					{
					 estado = falhar();
					}
				break;
				
			case 21:
				cont_sim_lido++;
				printf("< ( >\n");
				token.nome_token = PONTUATION;
				token.atributo = ETC;
				estado = 0;
				return(token);
				break;

			case 22:
				cont_sim_lido++;
				printf("< ) >\n");
				token.nome_token = PONTUATION;
				token.atributo = ETC;
				estado = 0;
				return(token);
				break;

			case 23:
				cont_sim_lido++;
				printf("< , >\n");
				token.nome_token = PONTUATION;
				token.atributo = ETC;
				estado = 0;
				return(token);
				break;

			case 24:
				cont_sim_lido++;
				printf("< ; >\n");
				token.nome_token = PONTUATION;
				token.atributo = ETC;
				estado = 0;
				return(token);
				break;

			case 25:
				cont_sim_lido++;
				c = code[cont_sim_lido];

				if(c == '=') estado = 26;
				else estado = 27;
				break;
				
			case 26:
				cont_sim_lido++;
				printf("<atribution, := >\n");
				token.nome_token = PONTUATION;
				token.atributo = ETC;
				estado = 0;
				return(token);
				break;
				
			case 27:
				printf("< : >\n");
				token.nome_token = PONTUATION;
				token.atributo = ETC;
				estado = 0;
				return(token);
				break;
			
			case 28:
				cont_sim_lido++;
				printf("< . >\n");
				token.nome_token = PONTUATION;
				token.atributo = ETC;
				estado = 0;
				return(token);
				break;
				
			case 29:
				c = code[cont_sim_lido];
				if((c == ' ')||(c == '\n'))
				{
					estado = 0;
					cont_sim_lido++;
				}
				else
				{
					/*implementar ações referentes aos estado */
					printf("< %c ", c);
					estado = falhar();
					token.nome_token = -1;
					token.atributo = -1;
					return(token);
				}
				break;
		}

	}
	token.nome_token = EOF;
	token.atributo = -1;
	return(token);
}




int main ()
{
     	
	Token token;
    code = "program correto; int a, b; begin a:=-2; b:=10 begin if (a<1) then b:=1 end end. ";
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    token = proximo_token();
    
    //PALAVRAS PRESENTES NA LISTA
    //for (const std::string &palavra : listaID) {
	//std::cout << palavra << std::endl;
	//}
    //...
        
	

}


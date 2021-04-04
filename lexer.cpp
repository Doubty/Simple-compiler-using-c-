#include "lexer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
using std::stringstream;
using std::cout;
extern std::ifstream fin;

// construtor 
Lexer::Lexer()
{
	// insere palavras-reservadas na tabela de id's
    id_table["float"] = Id{ Tag::TYPE, "float" };
	id_table["int"] = Id{ Tag::TYPE, "int" };
	id_table["char"] = Id{ Tag::TYPE, "char" };
	id_table["bool"] = Id{ Tag::TYPE, "bool" };

	// inicia leitura da entrada
	peek = fin.get();
}

// retorna número da linha atual
int Lexer::Lineno()
{
	return line;
}

// retorna tokens para o analisador sintático
Token * Lexer::Scan()
{



  // Removendo espaço, tabulações, quebra de linha e comentários. Refatorei pra essa solução de acordo com o debate no fórum
  // do problema que ascênio falou e tive o mesmo. 
   while(isspace(peek) || peek == '/'){
      
	  if(isspace(peek)){
        if (peek == '\n')
		line += 1;
		peek = fin.get();
	  } 
	  
	  if(peek == '/'){
		
		// próximo caractere
		peek = fin.get();

		if(peek == '/'){
	
	 // remover até a quebra de linha
         	 while(peek != '\n'){
                   
				   peek = fin.get();
				}  
                  // tirar o \n depois que sai do loop
				  peek = fin.get();
   
		}else{

          // caso do comentário /* */ 
			if(peek == '*'){

				bool test = true;

                 while(test){
                    
				peek = fin.get();

					if(peek == '*'){    /**/
                	peek = fin.get(); 
					if(peek == '/'){
				    peek = fin.get(); 
                   test = false;
					}
					}
				 }
				   // tirar o \n depois que sai do loop
				  peek = fin.get();
			}
		}
		
	  }
		  
	  
   }



	// retorna números
	if (isdigit(peek))
	{
		int v = 0;
        int v2 = 0;
		int qtdDigite = 0;
		float result = 0;
		do
		{
			// converte caractere 'n' para o dígito numérico n
			int n = peek - '0';
			v = 10 * v + n;
			peek = fin.get();
		}
 		while (isdigit(peek));

  

  // gambiarra criada para pegar o número francionário
         if( peek == '.'){ 

		 	peek = fin.get();

			 	do
		{
                
			int n = peek - '0';
			v2 = 10 * v2 + n;
			peek = fin.get();

			qtdDigite++;
		     
		}
 		while (isdigit(peek));
        

		result = v2/pow(10, qtdDigite); 
        result = result +v;


			// retorna o token NUM float
		token.n = Num{v, "float", result };
		return &token.n;
		 
  }


		// retorna o token NUM inteiro
		token.n = Num{v, "int", result };
		return &token.n;
	}

	// retorna palavras-chave e identificadores
	if (isalpha(peek))
	{
		stringstream ss;
		do 
		{
			ss << peek;
			peek = fin.get();

			

		} 
		while (isalpha(peek));

		string s = ss.str();
		auto pos = id_table.find(s);

		// se o lexema já está na tabela
		if (pos != id_table.end())
		{
			// retorna o token associado
			token.i = pos->second;
			return &token.i;
		}

		// se o lexema ainda não está na tabela
		Id new_id {Tag::ID, s};
		id_table[s] = new_id;

		// retorna o token ID
		token.i = new_id;
		return &token.i;
	}

	// operadores (e caracteres não alphanuméricos isolados)
	Token op {peek};
	peek = ' ';

	// retorna o token 
	token.t = op;
	return &token.t;
}

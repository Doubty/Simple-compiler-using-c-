#include <iostream>
#include <fstream>
#include <cstring>
#include "parser.h"
#include "error.h"
using namespace std;

// arquivo de entrada
ifstream fin;

// programa pode receber nomes de arquivos
int main(int argc, char **argv)
{
	if ( argc ==2)
	{
		fin.open(argv[1]);

	  string help = argv[1];

		if(help == "--help"){
             cout << "Para usar o tradutor basta apenas executar o programa \ne passar o caminho do arquivo (.math) como o exemplo\na seguir: " <<
			 "./Tradutor /arquivo.math ";
		}else{

		   
		  int tamanho  = strlen(argv[1]);
		  string extensao = argv[1];
		  string result = "";
         
          for(int i =5; i > 0; i--){
             result = result + extensao[tamanho-i];
		  }

        if(result == ".math"){

				if (!fin.is_open())
		{
			cout << "Falha na abertura do arquivo \'" << argv[1] << "\'.\n";
			cout << "Verifique se o nome está correto, ou se é protegido para leitura.\n";
			exit(EXIT_FAILURE);
		}

		Parser tradutor;
		try
		{
			tradutor.Start();
		}
		catch (SyntaxError err)
		{
			err.What();
		}
		
		cout << endl;		
		fin.close();

		}else {

			cout << "Extensão do arquivo inválida! (." << result << ") Necessário extensão (.math)";
		}

				
	

		}

	
	}
}

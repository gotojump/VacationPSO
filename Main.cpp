/*

cd C:\Users\GoTo\Desktop\Programas\IA

del Main.exe

wcl386 Main.cpp TS.cpp -fe=Main.exe

Main.exe

*/

#include "TS.hpp"
#include <time.h>

#define CIDADES_DEFAULT				5
#define CANDIDATOS_DEFAULT		5
#define PATH_DEFAULT					"Grafo.in"
#define LIMITE_DEFAULT				100
#define EPSILON_DEFAULT				3.0
#define TENTATIVAS_DEFAULT		3

// ========================================================================== //

void Generate( Uint Cidades, char *Path, Uint Limite ){
	Uint Nx, Ny;
	float Peso;
	TS Ts;

	printf( "Gerando %d cidades. Peso limite de %d.\nSalvando em %s.\n", Cidades, Limite, Path );
	Ts.Create( Cidades );
	for( Ny = 0 ; Ny < Ts.Cidades ; Ny++ ){
		for( Nx = 0 ; Nx < Ts.Cidades ; Nx++ ){
			Peso = ( rand() % ( Limite * 5 ) ) / 5.0;
			Ts.Set( Peso, Nx, Ny );
		}
	}

	if( Ts.Write( Path ) )
		puts( "Salvo!!" );
	else
		puts( "Falha ao salvar arquivo!!" );
}

// -------------------------------------------------------------------------- //

void Read( String Path, Uint Candidatos, float Epsilon, Uint Tryies ){
	TS Ts;

	printf( "Lendo o arquivo %s!!\n", Path );

	if( !Ts.Read( Path ) ){
		puts( "Não foi possível ler o arquivo de entrada!!" );
		return;
	}

	Ts.PSO( Candidatos, Epsilon, Tryies );
}

// -------------------------------------------------------------------------- //

void Help(){

	puts( "-h / -help : Exibe o menu de ajuda." );
	puts( "-g / -generate : Gera um arquivo de saída aleatoriamente." );
	printf( "-f / -file : Especifica o arquivo de leitura/escrita. (Default = %s)\n", PATH_DEFAULT );
	printf( "-c / -cities : Determina o número de cidades a serem geradas. (Default = %d)\n", CIDADES_DEFAULT);
	printf( "-ca / -candidates : Determina o número de candidatos. (Default = %d)\n", CANDIDATOS_DEFAULT );
	printf( "-l / -limit : Determina o valor limite de um peso entre duas cidades. Utilizado apenas para gerar aleatoriamente um arquivo de saída(Default = %d)\n", LIMITE_DEFAULT );
	printf( "-e / -epsilon : Determina o valor de epsilon, utilizado para determinar a diferença mínima entre os melhores valores de duas gerações(Default = %f)\n", EPSILON_DEFAULT );
	printf( "-t / -tryies : Determina o número de tentativas extras a serem realizadas após haver estabilidade entre os melhores resultados das gerações. (Default = %d)\n", TENTATIVAS_DEFAULT );
}

// -------------------------------------------------------------------------- //

int main( Int Argc, String *Argv ){
	Uint Cidades, Candidatos, Limite;
	String Path = NULL;
	Uint Nn, Ng = 0;
	float Epsilon;
	Uint Tryies;
	TS Ts;

	srand( time( NULL ) );

	Cidades = CIDADES_DEFAULT;
	Candidatos = CANDIDATOS_DEFAULT;
	Limite = LIMITE_DEFAULT;
	Path = (String)PATH_DEFAULT;
	Epsilon = EPSILON_DEFAULT;
	Tryies = TENTATIVAS_DEFAULT;


	for( Nn = 0 ; Argv[ Nn ] ; Nn++ ){
		if( !strcmp( Argv[ Nn ], "-h" ) || !strcmp( Argv[ Nn ], "-help" ) ){
			Help();
			return( 0 );
		}

		if( !strcmp( Argv[ Nn ], "-g" ) || !strcmp( Argv[ Nn ], "-generate" ) ){
			Ng = 1;
		}

		if( !strcmp( Argv[ Nn ], "-f" ) || !strcmp( Argv[ Nn ], "-file" ) ){
			if( Argv[ Nn + 1 ] )
				Path = Argv[ Nn + 1 ];
		}

		if( !strcmp( Argv[ Nn ], "-c" ) || !strcmp( Argv[ Nn ], "-cities" ) ){
			if( Argv[ Nn + 1 ] )
				Cidades = atoi( Argv[ Nn + 1 ] );
		}

		if( !strcmp( Argv[ Nn ], "-ca" ) || !strcmp( Argv[ Nn ], "-candidates" ) ){
			if( Argv[ Nn + 1 ] )
				Candidatos = atoi( Argv[ Nn + 1 ] );
		}

		if( !strcmp( Argv[ Nn ], "-l" ) || !strcmp( Argv[ Nn ], "-limit" ) ){
			if( Argv[ Nn + 1 ] )
				Limite = atoi( Argv[ Nn + 1 ] );
		}

		if( !strcmp( Argv[ Nn ], "-e" ) || !strcmp( Argv[ Nn ], "-epsilon" ) ){
			if( Argv[ Nn + 1 ] )
				Epsilon = atof( Argv[ Nn + 1 ] );
		}

		if( !strcmp( Argv[ Nn ], "-t" ) || !strcmp( Argv[ Nn ], "-Tryies" ) ){
			if( Argv[ Nn + 1 ] )
				Tryies = atoi( Argv[ Nn + 1 ] );
		}
	}

	puts( "Iniciando o programa PSO para o problema do caixeiro viajante (Digite a opção -h para ajuda!!)" );

	if( Ng )
		Generate( Cidades, Path, Limite );
	else
		Read( Path, Candidatos, Epsilon, Tryies );

	return( 0 );
}

// ========================================================================== //

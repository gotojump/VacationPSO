#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

typedef uint32_t		Uint;
typedef int32_t			Int;
typedef uint8_t			Byte;
typedef char*				String;

// ========================================================================== //

class Velocidade{
	public:
		Uint N_Trocas, Tamanho;													// Número de trocas realizadas e tamanho do vetor de trocas, respectivamente
		Uint *Trocas;																		// Vetor de trocas(onde cada troca é representada por um par de inteiros)

	public:
		Velocidade();

		Byte Create();
		void Free();
		void Print();

		Byte Insert( Uint N1, Uint N2 );								// Insere uma nova troca entre duas posições
		Byte Set( Uint Nn, Uint N1, Uint N2 );					// Muda o valor de uma troca
		Byte Get( Uint Nn, Uint *N1, Uint *N2 );				// Retorna o valor de uma troca
		Byte Remove();																	// remove uma troca
		Byte Resize();																	// Dobra o tamanho do vetor de trocas
		Velocidade Copy();															// Copia os valores internos desta classe em uma nova instância
};

// -------------------------------------------------------------------------- //

class Solucao{
	public:
		Uint Cidades;																		// Número de cidades
		Uint *Caminho;																	// Representa um caminho entre as cidades
		Velocidade Vel;																	// Variável que guarda as trocas realizadas no caminho

	public:
		Solucao();

		Byte Create( Uint _Cidades );										// Inicializa as variáveis internas da classe
		void Free();
		void Print();

		Byte Generate();																// Gera um caminho aleatório
		Byte Change( Uint N1, Uint N2 );								// Troca a osição entre duas cidades no caminho(atualizando a velocidade)
		Byte Change( Velocidade _Vel );									// Realiza uma sucessão de trocas
		Byte Undo();																		// Desfaz a última troca
		Byte Clear();																		// Desfaz todas as trocas
		Solucao Copy();																	// Copia os valores internos desta classe em uma nova instância
};

// -------------------------------------------------------------------------- //

class TS{
	public:
		Uint Cidades, Candidatos, Gbest;											// Número de cidades, número de candidatos e o índice do melhor candidato, respectivamente
		Solucao *Solucoes;																		// Vetor com os candidatos a solução
		Solucao *Pbest;
		float *Pesos;																					// Matriz de adjacencia

	public:
		TS();

		Byte Create( Uint _Cidades );													// Cria uma matriz com os pesos das distâncias entre as cidades
		Byte Candidates( Uint _Candidatos );
		void Free();																					// Libera a estrutura de dados
		void Print();																					// Imprime os pesos entre as cidades

		Byte Read( String Path );															// Lê os pesos entre cidades por meio do nome de um arquivo
		Byte Read( FILE* Fl );																// Lê os pesos entre cidades por meio do nome de um FILE*
		Byte Write( String Path );														// Escreve os pesos entre cidades em um arquivo por meio de um nome
		Byte Write( FILE* Fl );																// Escreve os pesos entre cidades em um arquivo por meio de um FILE*

		Byte Set( float Peso, Uint Nx, Uint Ny );							// Seta o peso de uma distância entre duas cidades
		float Get( Uint Nx, Uint Ny );												// Pega o peso de uma distância entre duas cidades
		float Cost( Solucao *Sol );																// Retorna o custo total de se percorrer o caminho de determinado candidato

		Byte Generate();																			// Gera candidatos aleatoriamente
		Byte Better();																				// Determina o melhor candidato
		Byte Next();																					// Gera a geração seguinte
		Byte PSO( Uint _Candidatos, float Eps, Uint Tryies );	// Realiza a função principal
};

// ========================================================================== //

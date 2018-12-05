#include "TS.hpp"

// ========================================================================== //

Velocidade::Velocidade(){

	memset( this, 0, sizeof( Velocidade ) );
}

// -------------------------------------------------------------------------- //

Byte Velocidade::Create(){

	this->Free();

	return( 1 );
}

// -------------------------------------------------------------------------- //

void Velocidade::Free(){

	if( Trocas )
		free( Trocas );
	Trocas = NULL;

	N_Trocas = Tamanho = 0;
}

// -------------------------------------------------------------------------- //

void Velocidade::Print(){
	Uint Nn, N1, N2;

	printf( "%d trocas:", N_Trocas );
	for( Nn = 0 ; Nn < N_Trocas ; Nn++ ){
		this->Get( Nn, &N1, &N2 );
		printf( "(%d - %d) ", N1, N2 );
	}
}

// -------------------------------------------------------------------------- //

Byte Velocidade::Insert( Uint N1, Uint N2 ){

	if( N_Trocas == Tamanho )
		if( !this->Resize() )
			return( 0 );

	Trocas[ N_Trocas * 2 ] = N1;
	Trocas[ N_Trocas * 2 + 1 ] = N2;
	N_Trocas++;

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Velocidade::Set( Uint Nn, Uint N1, Uint N2 ){

	if( Nn >= N_Trocas )
		return( 0 );

	Trocas[ Nn * 2 ] = N1;
	Trocas[ Nn * 2 + 1 ] = N2;

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Velocidade::Get( Uint Nn, Uint *N1, Uint *N2 ){

	if( !N1 || !N2 )
		return( 0 );

	if( Nn >= N_Trocas ){
		*N1 = *N2 = 0;
		return( 0 );
	}

	*N1 = Trocas[ Nn * 2 ];
	*N2 = Trocas[ Nn * 2 + 1 ];

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Velocidade::Remove(){

	if( !N_Trocas )
		return( 0 );

	N_Trocas--;
	Trocas[ N_Trocas * 2 ] = 0;
	Trocas[ N_Trocas * 2 + 1 ] = 0;

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Velocidade::Resize(){
	Uint *Aux = NULL;

	Tamanho = ( Tamanho == 0 ? 1 : Tamanho * 2 );
	Aux = (Uint*)malloc( sizeof( Uint ) * Tamanho * 2 );
	if( !Aux ){
		Tamanho /= 2;
		return( 0 );
	}

	memset( Aux, 0, sizeof( Uint ) * Tamanho * 2 );
	if( Trocas ){
		memcpy( Aux, Trocas, sizeof( Uint ) * N_Trocas * 2 );
		free( Trocas );
	}

	Trocas = Aux;

	return( 1 );
}

// -------------------------------------------------------------------------- //

Velocidade Velocidade::Copy(){
	Velocidade Vel;

	Vel.Trocas = (Uint*)malloc( sizeof( Velocidade ) * Tamanho * 2 );
	if( !Vel.Trocas ){
		exit( 0 );
	}

	memset( Vel.Trocas, 0, sizeof( Velocidade ) * Tamanho * 2 );
	memcpy( Vel.Trocas, Trocas, sizeof( Uint ) * N_Trocas * 2 );
	Vel.N_Trocas = N_Trocas;
	Vel.Tamanho = Tamanho;

	return( Vel );
}

// ========================================================================== //

Solucao::Solucao(){

	memset( this, 0, sizeof( Solucao ) );
}

// -------------------------------------------------------------------------- //

Byte Solucao::Create( Uint _Cidades ){

	this->Free();

	Caminho = (Uint*)malloc( _Cidades * sizeof( Uint ) );
	if( !Caminho )
		return( 0 );

	memset( Caminho, 0, _Cidades * sizeof( Uint ) );
	Cidades = _Cidades;

	return( 1 );
}

// -------------------------------------------------------------------------- //

void Solucao::Free(){

	if( Caminho )
		free( Caminho );

	Vel.Free();
	Caminho = NULL;
	Cidades = 0;
}

// -------------------------------------------------------------------------- //

void Solucao::Print(){
	Uint Nn;

	if( Caminho )
		for( Nn = 0 ; Nn < Cidades ; Nn++ )
			printf( "%d ", Caminho[ Nn ] );
}

// -------------------------------------------------------------------------- //

Byte Solucao::Generate(){
	Uint Nm, No, Nc;

	if( !Caminho )
		return( 0 );

	memset( Caminho, 0, sizeof( Uint ) * Cidades );

	for( Nm = 0 ; Nm < Cidades ; Nm++ ){
		Nc = rand() % Cidades;
		No = 0;

		while( No < Nm ){
			if( Nc == Caminho[ No ] ){
				Nc = rand() % Cidades;
				No = 0;
			}
			else
				No++;
		}

		Caminho[ Nm ] = Nc;
	}

	No = rand() % Cidades;
	for( Nm = 0 ; Nm < No ; Nm++ ){
		this->Change( rand() % Cidades, rand() % Cidades );
	}

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Solucao::Change( Uint N1, Uint N2 ){
	Uint Temp;

	if( !Caminho )
		return( 0 );

	Vel.Insert( N1, N2 );
	Temp = Caminho[ N1 ];
	Caminho[ N1 ] = Caminho[ N2 ];
	Caminho[ N2 ] = Temp;

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Solucao::Change( Velocidade _Vel ){
	Uint Nn, N1, N2;

	if( !Caminho )
		return( 0 );

	this->Clear();
	for( Nn = 0 ; Nn < _Vel.N_Trocas ; Nn++ ){
		_Vel.Get( Nn, &N1, &N2 );
		this->Change( N1, N2 );
	}

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Solucao::Undo(){
	Uint N1, N2;
	Uint Temp;

	if( !Caminho )
		return( 0 );

	Vel.Get( Vel.N_Trocas - 1, &N1, &N2 );
	Vel.Remove();

	Temp = Caminho[ N1 ];
	Caminho[ N1 ] = Caminho[ N2 ];
	Caminho[ N2 ] = Temp;

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte Solucao::Clear(){

	if( !Caminho )
		return( 0 );

	while( Vel.N_Trocas ){
		this->Undo();
	}

	return( 1 );
}

// -------------------------------------------------------------------------- //

Solucao Solucao::Copy(){
	Solucao Sol;

	Sol.Free();

	if( !Cidades )
		return( Sol );

	Sol.Caminho = (Uint*)malloc( sizeof( Uint ) * Cidades );
	if( !Sol.Caminho ){
		exit( 0 );
	}

	memcpy( Sol.Caminho, Caminho, sizeof( Uint ) * Cidades );
	Sol.Cidades = Cidades;
	Sol.Vel = Vel.Copy();

	return( Sol );
}

// ========================================================================== //

TS::TS(){

	memset( this, 0, sizeof( TS ) );
}

// -------------------------------------------------------------------------- //

Byte TS::Create( Uint _Cidades ){
	Uint Nx, Ny;

	if( !_Cidades )
		return( 0 );

	Pesos = (float*)malloc( _Cidades * _Cidades * sizeof( float ) );
	if( !Pesos )
		return( 0 );

	for( Ny = 0 ; Ny < _Cidades ; Ny++ )
		for( Nx = 0 ; Nx < _Cidades ; Nx++ )
			Pesos[ Ny * _Cidades + Nx ] = ( Nx == Ny ? 0.0 : INFINITY );

	Cidades = _Cidades;

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte TS::Candidates( Uint _Candidatos ){
	Uint Nn;

	if( !Cidades )
		return( 0 );

	Solucoes = new Solucao[_Candidatos];
	Pbest = new Solucao[_Candidatos];

	if( !Solucoes || !Pbest )
		return( 0 );

	memset( Pbest, 0, sizeof( Solucao ) * _Candidatos );
	for( Nn = 0 ; Nn < _Candidatos ; Nn++ ){
		if( !Solucoes[ Nn ].Create( Cidades ) )
			return( 0 );
	}

	Candidatos = _Candidatos;

	return( 1 );
}

// -------------------------------------------------------------------------- //

void TS::Free(){
	Uint Nn;

	if( Pesos )
		free( Pesos );

	if( Solucoes ){
		for( Nn = 0 ; Nn < Candidatos ; Nn++ )
			Solucoes[ Nn ].Free();
		free( Solucoes );
	}

	Pesos = NULL;
	Solucoes = NULL;
	Pbest = NULL;
	Cidades = Candidatos = Gbest = 0;
}

// -------------------------------------------------------------------------- //

void TS::Print(){
	Uint Nx, Ny;

	puts("\n   ======================================================================\n");

	printf( "%d Cidades:\n", Cidades );
	for( Ny = 0 ; Ny < Cidades ; Ny++ ){
		for( Nx = 0 ; Nx < Cidades ; Nx++ ){
			printf( "%8.3f ", Pesos[ Ny * Cidades + Nx ] );
		}
		printf("\n");
	}

	printf( "\n%d Candidatos:\n", Candidatos );
	for( Ny = 0 ; Ny < Candidatos ; Ny++ ){
		printf( " [%2d]: ", Ny );
		Solucoes[ Ny ].Print();
		printf( " = %.3f\n", this->Cost( &Solucoes[ Ny ] ) );
	}

	printf( "\nMelhor solução(vinda do candidato %d):\n", Gbest );
	if( Pbest ){
		Pbest[ Gbest ].Print();
		printf( " = %.3f\n", this->Cost( &Pbest[ Gbest ] ) );
	}

	printf( "\nVelocidades:\n" );
	for( Ny = 0 ; Ny < Candidatos ; Ny++ ){
		printf( " [%2d]: ", Ny );
		Solucoes[ Ny ].Vel.Print();
		printf( "\n" );
	}

	puts("\n   ======================================================================\n");

}

// -------------------------------------------------------------------------- //

Byte TS::Read( String Path ){
	FILE* Fl = NULL;
	Byte Result;

	if( !Path )
		return( 0 );

	Fl = fopen( Path, "r" );
	if( !Fl )
		return( 0 );

	Result = this->Read( Fl );
	fclose( Fl );

	return( Result );
}

// -------------------------------------------------------------------------- //

Byte TS::Read( FILE* Fl ){
	Uint _Cidades, Nx, Ny;
	float Peso;

	this->Free();

	fscanf( Fl, "%d\n", &_Cidades );
	if( !this->Create( _Cidades ) )
		return( 0 );

	for( Ny = 0 ; Ny < _Cidades ; Ny++ ){
		for( Nx = 0 ; Nx < _Cidades ; Nx++ ){
			fscanf( Fl, "%f ", &Peso );
			this->Set( Peso, Nx, Ny );
		}
	}

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte TS::Write( String Path ){
	FILE* Fl = NULL;
	Byte Result;

	if( !Path )
		return( 0 );

	Fl = fopen( Path, "w" );
	if( !Fl )
		return( 0 );

	Result = this->Write( Fl );
	fclose( Fl );

	return( Result );
}

// -------------------------------------------------------------------------- //

Byte TS::Write( FILE* Fl ){
	Uint Nx, Ny;

	fprintf( Fl, "%d\n", Cidades );

	for( Ny = 0 ; Ny < Cidades ; Ny++ )
		for( Nx = 0 ; Nx < Cidades ; Nx++ )
			fprintf( Fl, "%f ", this->Get( Nx, Ny ) );

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte TS::Set( float Peso, Uint Nx, Uint Ny ){

	if( ( Nx >= Cidades ) || ( Ny >= Cidades ) )
		return( 0 );

	Pesos[ Ny * Cidades + Nx ] = Pesos[ Nx * Cidades + Ny ] = ( Nx == Ny ? 0 : Peso );

	return( 1 );
}

// -------------------------------------------------------------------------- //

float TS::Get( Uint Nx, Uint Ny ){

	if( ( Nx >= Cidades ) || ( Ny >= Cidades ) )
		return( 0 );

	return( Pesos[ Ny * Cidades + Nx ] );
}

// -------------------------------------------------------------------------- //

float TS::Cost( Solucao* Sol ){
	Uint Nm;
	float Np;

	if( !Sol )
		return( 0.0 );

	Np = 0.0;
	for( Nm = 1 ; Nm < Cidades ; Nm++ )
		Np += this->Get( Sol->Caminho[ Nm ], Sol->Caminho[ Nm - 1 ] );

	Np += this->Get( Sol->Caminho[ Cidades - 1 ], Sol->Caminho[ 0 ] );

	return( Np );
}

// -------------------------------------------------------------------------- //

Byte TS::Generate(){
	Uint Nn;

	if( !Candidatos )
		return( 0 );

	Gbest = 0;

	for( Nn = 0 ; Nn < Candidatos ; Nn++ ){
		Solucoes[ Nn ].Generate();
		Pbest[ Nn ] = Solucoes[ Nn ].Copy();
		if( this->Cost( &Pbest[ Nn ] ) < this->Cost( &Pbest[ Gbest ] ) )
			Gbest = Nn;
	}

	return( 0 );
}

// -------------------------------------------------------------------------- //

Byte TS::Better(){
	float Ps1, Ps2, Pb, Pp;
	Uint Nn;

	if( !Candidatos )
		return( 0 );

	Pb = INFINITY;

	for( Nn = 0 ; Nn < Candidatos ; Nn++ ){
		Ps1 = this->Cost( &Solucoes[ Nn ] );
		Ps2 = this->Cost( &Pbest[ Nn ] );

		if( Ps1 < Ps2 ){
			Pbest[ Nn ].Free();
			Pbest[ Nn ] = Solucoes[ Nn ].Copy();
		}
	}

	Gbest = 0;
	Pb = this->Cost( &Pbest[ 0 ] );

	for( Nn = 1 ; Nn < Candidatos ; Nn++ ){
		Pp = this->Cost( &Pbest[ Nn ] );
		if( Pp < Pb ){
			Gbest = Nn;
			Pb = Pp;
		}
	}

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte TS::Next(){
	Uint Nn, Nm, No;

	if( !Candidatos )
		return( 0 );

	this->Better();

	for( Nn = 0 ; Nn < Candidatos ; Nn++ ){
		if( Nn == Gbest )
			continue;

		Solucoes[ Nn ].Clear();

		No = rand() % Cidades;
		for( Nm = 0 ; Nm < No ; Nm++ ){
			Solucoes[ Nn ].Change( rand() % Cidades, rand() % Cidades );
		}

	}

	this->Better();

	return( 1 );
}

// -------------------------------------------------------------------------- //

Byte TS::PSO( Uint _Candidatos, float Eps, Uint Tryies ){
	float Best, Best_Temp;
	Uint Nn;

	if( !_Candidatos )
		return( 0 );

	this->Candidates( _Candidatos );

	Nn = 0;
	this->Generate();
	Best = this->Cost( &Pbest[ Gbest ] );

	this->Print();

	while( Nn < Tryies ){
		this->Next();
		this->Print();

		Best_Temp = this->Cost( &Pbest[ Gbest ] );
		if( Best - Best_Temp < Eps )
			Nn++;
		else{
			Nn = 0;
			Best = Best_Temp;
		}
	}

	return( 1 );
}

// ========================================================================== //

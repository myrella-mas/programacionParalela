
	 /*-------------------------------------------------------------------------
	 Name        : Practica-Ejercicio1
	 Author      : Myrella Alejandra Mas Bula
	 Version     :
	 Copyright   : Your copyright notice
	 Description : Compute Pi in MPI C++
	 -------------------------------------------------------------------------*/


	#include <stdio.h>
	#include <stdlib.h>
	#include <mpi.h>
	using namespace std;
	int main (int argc, char * argv[]){
	int size,rank; // size indica el tama�o , rank la posicion del proceso
	

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int tam,c,ntam,nfact;
	long long int factorial=1, factorial2;
	if(rank==0){
		cout<<"Ingresar el numero para Factorizar ";
		cin>>tam;	//numero que sera factorizado
		if(tam<size){
			tam=size;
			cout<<"El nuevo factorial es: "<<tam<<endl;
		}else{
			if((tam%size) != 0){
				c=tam/size;
				tam=(c+1)*size;
				cout<<"El nuevo factorial es: "<<tam<<endl;
			}
		}
		ntam=tam/size;	// se calcula un nuevo tama�o del factorial
	
	}
	MPI_Bcast(&tam,1,MPI_INT,0,MPI_COMM_WORLD); //envia mensaje a todos los procesos
	MPI_Bcast(&ntam,1,MPI_INT,0,MPI_COMM_WORLD);//envia mensaje a todos los procesos
	

	nfact=ntam*(rank+1);
	for(int i=0; i<ntam;i++){
		factorial=factorial*(nfact-i);		//calcula el factorial
	}
	

	MPI_Reduce(&factorial,&factorial2,1,MPI_LONG_LONG_INT,MPI_PROD,0,MPI_COMM_WORLD); // utiliza el MPI-PROD para las operaciones
																					//del factorial
	
	if(rank==0){	//si la posicion del proceso  es 0 entonces muestra
		cout<<"El valor del factorial es: "<<factorial2<<endl;
	}
	

	

	

	MPI_Finalize();
	return 0;
	}



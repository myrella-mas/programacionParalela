/*
	 -------------------------------------------------------------------------
	 Name        : Practica-Ejercicio2
	 Author      : Myrella Alejandra Mas Bula
	 Version     :
	 Copyright   : Your copyright notice
	 Description : Compute Pi in MPI C++
	 -------------------------------------------------------------------------
	*/
	#include <stdio.h>
	#include <stdlib.h>
	#include <mpi.h>
	using namespace std;
	int main (int argc, char * argv[]){
	int size,rank; // tamaño y posicion del proceso
	
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	int *vector,*local_vector, tam,c,x,ntam,cont1=0,cont2;	//variables

	if(rank==0){	// si la posicion del proceso es 0
		cout<<"Ingrese el tamaño del vector";	//cantidad de elementos del vector
		cin>>tam;
		cout<<"Ingrese el valor que desea buscar: ";
		cin>>x;
		if(tam<size){
			tam=size;
			cout<<"El nuevo orden del vector es  "<<tam<<endl;
		}else{
			if((tam%size) != 0){
				c=tam/size;
				tam=(c+1)*size;
				cout<<"El nuevo orden del vector es "<<tam<<endl;
			}
		}
		ntam=tam/size	// se calcula un tamaño local
	}
	MPI_Bcast(&tam,1,MPI_INT,0,MPI_COMM_WORLD);	//envia el tamaño del vector a todos los procesos 
	MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);	//envia el valor que se desea buscar a todos los procesos 
	MPI_Bcast(&ntam,1,MPI_INT,0,MPI_COMM_WORLD);//envia el valor local
	vector= new int[tam];

	local_vector = new int [ntam];
	
	if(rank==0){
		cout<<"Vector generado [ ";
		for(int i=0;i<tam;i++){
			vector[i]=rand()%10;
			cout<< vector[i]<<" ";
		}
		cout <<"]"<<endl;
		MPI_Scatter(vector,ntam,MPI_INT,local_vector,ntam,MPI_INT,0,MPI_COMM_WORLD);	 //envia la informacion
	}
	
	MPI_Scatter(vector,ntam,MPI_INT,local_vector,ntam,MPI_INT,0,MPI_COMM_WORLD);
	
	MPI_Barrier(MPI_COMM_WORLD);
	for(int i=0;i<ntam;i++){		// inicia la busqueda en el vector
		if(local_vector[i]==x){
			cont1++;
		}
	}
	MPI_Barrier(MPI_COMM_WORLD);
	
	MPI_Reduce(&cont1, &cont2,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD); 
	

	if(rank==0){
		cout<<"El numero de veces que se encontro "<<x<<" en el vector es: "<<cont2<<endl;
	}
	

	MPI_Finalize();
	delete [] vector;
	delete [] local_vector;
	return 0;
	}




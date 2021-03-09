#include<iostream>
#include<math.h>
#include <fstream>
#include<string>


using namespace std;

#define n_col 30
#define	m_row 150



void prin_matrix(double **s){
	for (int j = 0; j < m_row; ++j)
	{
		for (int i = 0; i < n_col; ++i)
			{
			cout<<s[j][i]<<'\t';
			}
			
		cout<<'\n';	
	}
}

// void sve_matrix(double **s,string file){

// 	for (int j = 0; j < m_row; ++j)
// 	{
// 		for (int i = 0; i < n_col; ++i)
// 		{
// 			<<s[j][i]<<'\t';
// 		}
		
// 		myfile<<'\n';	
// 	}
// }



int main(void){

	ofstream myfile;
	myfile.open ("pft5_0.txt");


	double d_rho,d_z,V_0;
	int itmax,j_1,j_2, N ,it;


	// inicjalizacja parametrów :


	j_1=60;
	j_2=90;
	V_0=10.0;
	itmax = 5000;			
	d_z=0.1;
	d_rho=0.1;
	
	

	double *V[m_row+1];
	for (int i = 0; i <= m_row; ++i)
	{
		V[i]=( double *) malloc ((n_col+1)*sizeof ( double )); // tablica rozwiązań
	}
		
	for (int j = 0; j <= m_row; ++j)
		{
		for (int i = 0; i <=n_col; ++i)
			{
				V[j][i]=0;
			}
			
			
	}

	//inic_end

	for ( it = 0; it <= itmax; it++){

		//poprawianie potencjału
			for (int j = 1; j <= m_row-1; ++j)
			{
				for (int i = 1; i <= n_col-1; ++i)
				{
					V[j][i]=(	1.0/( (2.0/(d_rho*d_rho))+(2.0/(d_z*d_z)) )	)	*	(  ( (V[j][i+1]+V[j][i-1])/(d_rho*d_rho) 	) + (  (V[j][i+1]-V[j][i-1])/(2*d_rho*i*d_rho)  ) + ( 	(V[j+1][i]+V[j-1][i])/(d_z*d_z)   )		);
				
				}

			}



		//  warunki początkowe :


		//obs 1

			for (int j = 0; j <= j_1; ++j)
			{
				V[j][n_col]=V_0;
			}

		// //obs 2

			for (int j = j_1+1; j <= j_2; ++j)
			{
				V[j][n_col]=0;
			}


		// //obs 3

			for (int j = j_2+1; j <= m_row; ++j)
			{
				V[j][n_col]=V_0;
			}

		// //obs 4

			for (int i = 1; i <= n_col-1; ++i)
			{
				V[m_row][i]=V[m_row-1][i];
			}

		// //obs 5

			for (int i = 1; i <= n_col-1; ++i)
			{
				V[0][i]=V[1][i];
			}

		// //obs 6

			for (int j = 1; j <= m_row-1; ++j)
			{
				V[j][0]=V[j][1];
			}

	

	}	

		// zapis
	for (int j = 0; j <= m_row; ++j)
	{
		for (int i = 0; i <= n_col; ++i)
		{
			myfile<<V[j][i]<<'\t';
		}
		
		myfile<<'\n';	
	}


	//prin_matrix(V);

	myfile.close();

return 0;
}

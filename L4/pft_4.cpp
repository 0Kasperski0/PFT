#include<iostream>
#include<math.h>
#include <fstream>

using namespace std;


# define Nat 50
# define alfa 1.0
# define m 1.0
# define delta 0.1


void energie ( double &E , double &T , double &U, const double *s ){
	T=0;
	U=0;

	for(int i=0;i<=Nat;i++){ // v starts at N+1+i
		T+=0.5*m*s[Nat+i+1]*s[Nat+i+1];
	}
	for(int i=1;i<=Nat;i++){ // v starts at N+1+i
		U+=0.5*alfa*(s[i-1]-s[i]+delta)*(s[i-1]-s[i]+delta);
	}
	E=T+U;
	
}	


void pochodne ( double t , double *s , double *k){
	for(int i=1;i<Nat;i++){
		k[i]= s[Nat+1+i];
		k[Nat+1+i]=(alfa/m)*(s[i-1]-2*s[i]+s[i+1]); //v
	}

	k [0]=0;
	k [Nat]=0; 
	k [Nat+1]=0;
	k [2*Nat+1]=0;


}	

void rk4_vec ( double t , double dt , int n, double *s ,void (* f )( double , double * , double *) ){
	# define M 101
	static double k1 [ M ] , k2 [ M ] , k3 [ M ] , k4 [ M ] , w [ M ];
	int i ;



	for (i=0; i<n ; i++) w [i]=s[i];
		f(t,w,k1);
	for (i=0;i < n ; i ++) w [ i ]= s [ i ]+ dt /2* k1 [ i ];
		f(t + dt/2 ,w , k2 );
	for ( i =0; i < n ; i ++) w [ i ]= s [ i ]+ dt /2* k2 [ i ];
		f ( t + dt /2 ,w , k3 );
	for ( i =0; i < n ; i ++) w [ i ]= s [ i ]+ dt * k3 [ i ];
		f ( t + dt ,w , k4 );
	for ( i =0; i < n ; i ++) s [ i ]= s [ i ]+ dt /6*( k1 [ i ]+2* k2 [ i ]+2* k3 [ i ]+ k4 [ i ]);
}

int main(void){
	ofstream myfile;
	myfile.open ("pft4_0.txt");



	double t , dt , tmax , *s,U,E,T;
	int i , n , N ;
	void (* f )( double , double * , double *); // wskaźnik do funkcji

	// inicjalizacja parametrów :

	
	n =2*(Nat+1);		// ilość zmiennych w układzie RRZ1
	N = 5000;			
	dt =0.02;
	//tmax =20;
	//N =( int ) tmax / dt ; 		// ilość kroków czasowych
	t =0;
	f = pochodne ; 				// przypisujemy wskaźnik do funkcji
	

	s =( double *) malloc ( n * sizeof ( double )); // tablica rozwiązań
		// warunki początkowe :

	for (int i = 0; i <= Nat; i++){
		s[i]=delta*i+(delta/3)*exp(	-(	( (delta*i-delta*Nat*0.5)*(delta*i-delta*Nat*0.5)	)/(2*delta*3*delta*3)	));
		s[Nat+1+i]=0;
	}

	

		// symulacja w czasie :
	for ( i =0; i <= N ; i ++){

		rk4_vec (t , dt , n , s , f );
		energie(E,T,U,s);
		t= t + dt ;
		
		myfile<<t<<"\t"<<E<<"\t"<<T<<"\t"<<U<<"\t";
		for (int i = 0; i <=Nat; ++i)
		{
		myfile<<s[i]-delta*i<<'\t';
		}
		myfile<<'\n';
	}	

	
	myfile.close();
return 0;
}

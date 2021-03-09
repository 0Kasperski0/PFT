#include<iostream>
#include<math.h>
#include <fstream>

using namespace std;

# define g 9.81
# define R 1.0
# define m 1.0

void energie ( double &E , double &T , double &U, const double *s ){
	T=m*0.5*(R*R)*(s[1]*s[1]);
	U=-m*g*R*cos(s[0]);
	E=U+T;
}	

double degtorad(double deg){
	return  M_PI*deg/180;
}


void pochodne ( double t , double *s , double * k ){
	k [0]= s [1];
	k [1]= - g / R * sin ( s [0]);

}	

void rk4_vec ( double t , double dt , int n, double *s ,void (* f )( double , double * , double *) ){
	# define M 100
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
	myfile.open ("23232.txt");// t s0 s1 t u e 
	myfile<<"t s0 s1 t u e "<<"\n";
	double t , dt , tmax , * s,U,E,T ;
	int i , n , N ;
	void (* f )( double , double * , double *); // wskaźnik do funkcji

		// inicjalizacja parametrów :
	n =2;					// ilość zmiennych w układzie RRZ1
	dt =0.01;
	tmax =20;
	//N =( int ) tmax / dt ; 		// ilość kroków czasowych
	N = 1000;
	t =0;
	f = pochodne ; 				// przypisujemy wskaźnik do funkcji
	s =( double *) malloc ( n * sizeof ( double )); // tablica rozwiązań
		// warunki początkowe :
	s [0]=degtorad(175); 	//phi
	s [1]=0;		//d phi/dt


		// symulacja w czasie :
	for ( i =1; i <= N ; i ++){
		rk4_vec (t , dt , n , s , f );
		t= t + dt ;
		energie(E,T,U,s);
		myfile<<t<<"\t"<<s[0]<<"\t"<<s[1]<<"\t"<<T<<"\t"<<U<<"\t"<<E<<"\n";
	}	
	cout<<"sgags\n";
	myfile.close();
return 0;
}

#include<iostream>
#include<math.h>
#include <fstream>

using namespace std;

# define A 0.5
# define g 9.81
# define R 1.0
# define m 1.0
# define B 1.0
# define q 1.0


void energie ( double &E , double &T , double &U, const double *s ){
	T=s[3]*s[3]*m/(2*m*m);
	U=+(q/2)*s[0]*B*(s[3]/m);
	//E=U+T;
	E=(1.0/(2*m))*((s[3]*s[3])+((s[4]*s[4])/(s[0]*s[0]))+(s[5]*s[5]))-((s[4]*q*B)/(2*m))+((s[0]*s[0]*q*q*B*B)/(8*m));

}	

double degtorad(double deg){
	return  M_PI*deg/180;
}



void pochodne ( double t , double *s , double * k){
	k [0]= s[3]/m;
	k [1]= s[4]/(m*s[0]*s[0]) - q*B/(2*m);
	k [2]= s[5]/m;
	k [3]= s[4]*s[4]/(s[0]*s[0]*s[0]*m)- q*q*B*B*s[0]/(4*m);
	k [4]=0;
	k [5]=0;

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
	myfile.open ("pft3_2.txt");
	//myfile<<"t s0 s1 s3 s4 t u e "<<"\n";
	double t , dt , tmax , * s,U,E,T;
	int i , n , N ;
	void (* f )( double , double * , double *); // wskaźnik do funkcji

		// inicjalizacja parametrów :

	double wc=q*B/m;
	double Tt=2*M_PI/wc;
	n =6;		// ilość zmiennych w układzie RRZ1
	N = 5000;			
	dt =5*Tt/N;
	tmax =20;
	//N =( int ) tmax / dt ; 		// ilość kroków czasowych
	t =0;
	f = pochodne ; 				// przypisujemy wskaźnik do funkcji
	

	s =( double *) malloc ( n * sizeof ( double )); // tablica rozwiązań
		// warunki początkowe :
	s [0]=2;	
	s [1]=0;		
	s [2]=0;
	s [3]=0;
	s [4]=-q*B*s[0]*s[0]/2;
	s [5]=0;
	
		// symulacja w czasie :
	for ( i =1; i <= N ; i ++){
		rk4_vec (t , dt , n , s , f );
		t= t + dt ;
		energie(E,T,U,s);
		myfile<<t<<"\t"<<s[0]<<"\t"<<s[1]<<"\t"<<s[2]<<"\t"<<s[3]<<"\t"<<s[4]<<"\t"<<s[5]<<"\t"<<E<<"\n";
	}	
	
	myfile.close();
return 0;
}

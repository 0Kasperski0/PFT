#include<iostream>
#include<math.h>
#include <fstream>
#include<string>


using namespace std;

#define mu_0 1
#define eps_0 1
#define R 1
#define sigma 1


int wspolczynnik ( int i , int Na ){
	int k ;
	if ( i ==0 || i == Na ) k =1;
	else if ( i %2==1 ) k =4;
	else if ( i %2==0 ) k =2;
	return k ;
}


void vec_set(double a ,double b ,double c,double g [3]){
	g[0]=a;
	g[1]=b;
	g[2]=c;
}


void fun_diff_vec ( double a [3] , double b [3] , double g [3]){
	for (int i = 0; i < 3; ++i)
	{
		g[i]=a[i]-b[i];
	}
	
}

double vec_len (double g [3]){
	double len=0;
	for (int i = 0; i < 3; ++i)
	{
		len+=g[i]*g[i];
	}
	
	return sqrt(len);
}


void iloczyn_wektorowy ( double a [3] , double b [3] , double g [3]){
	g[0]=a[1]*b[2]-a[2]*b[1];
	g[1]=a[2]*b[0]-a[0]*b[2];
	g[2]=a[0]*b[1]-a[1]*b[0];
}


int main(void){

	ofstream myfile;
	myfile.open ("pft6_pi4.txt");


	double W,d_theta,d_phi,d_x,d_y,alpha,L,K,z,x,y,ex,ey,bx,by,v,theta,phi,x_p,y_p,z_p,value_vec_diff;
	int N,M;
	L=3.0;
	K=41.0;
	N=M=201;
	d_theta=M_PI/N;
	d_phi=2*M_PI/M;
	d_x=2*L/K;
	d_y=d_x;
	alpha=M_PI/4;

	


	double w[3];
	w[0]=sin(alpha);
	w[1]=cos(alpha);
	w[2]=0;

	double r[3]={0};
	double r_p[3]={0};
	double vec_diff[3]={0};
	double g_1[3]={0};
	double g_2[3]={0};
	

	






	for (double x = -L; x <= L; x=x+d_x)
		{

		for (double y = -L; y <= L; y=y+d_x)
			{
					
			z=0;
				//==== zerowanie zmiennych przed całkowaniem
			v=0;
			ex=0;
			ey=0;
			bx=0;
			by=0;
				//========= całkowanie ==================

			for (int i = 0; i <= N; ++i)
				{
				for (int j = 0; j <= M; ++j)
					{
					theta=d_theta*i;
					phi=d_phi*j;
					


					x_p=R*sin(theta)*cos(phi);
					y_p=R*sin(theta)*sin(phi);
					z_p=R*cos(theta); 	

					vec_set(x,y,0,r);
					vec_set(x_p,y_p,z_p,r_p);
					fun_diff_vec(r,r_p,vec_diff);

					value_vec_diff=vec_len(vec_diff);

					W=(sigma*R*R*d_theta*d_phi)/(4*M_PI*3*3);
					v=v+W*wspolczynnik(i,N)*wspolczynnik(j,M)*sin(theta)/(value_vec_diff);
					ex=ex+W*wspolczynnik(i,N)*wspolczynnik(j,M)*sin(theta)*(x-x_p)/(value_vec_diff*value_vec_diff*value_vec_diff);
					ey=ey+W*wspolczynnik(i,N)*wspolczynnik(j,M)*sin(theta)*(y-y_p)/(value_vec_diff*value_vec_diff*value_vec_diff);

					fun_diff_vec(r,r_p,vec_diff);	
					iloczyn_wektorowy(w,r_p,g_1);
					iloczyn_wektorowy(vec_diff,g_1,g_2);

					bx=-(bx+W*wspolczynnik(i,N)*wspolczynnik(j,M)*sin(theta)*g_2[0]/(value_vec_diff*value_vec_diff*value_vec_diff));
					by=-(by+W*wspolczynnik(i,N)*wspolczynnik(j,M)*sin(theta)*g_2[1]/(value_vec_diff*value_vec_diff*value_vec_diff));
				}
			}


			//zapis do pliku
			myfile<<x<<'\t'<<y<<'\t'<<v<<'\t'<<ex<<'\t'<<ey<<'\t'<<bx<<'\t'<<by<<'\n';
			
			}
	}













	// inicjalizacja parametrów :



	

	// double *V[m_row+1];
	// for (int i = 0; i <= m_row; ++i)
	// {
	// 	V[i]=( double *) malloc ((n_col+1)*sizeof ( double )); // tablica rozwiązań
	// }
		
	// for (int j = 0; j <= m_row; ++j)
	// 	{
	// 	for (int i = 0; i <=n_col; ++i)
	// 		{
	// 			V[j][i]=0;
	// 		}
			
			
	// }

	//inic_end





		// zapis
	// for (int j = 0; j <= m_row; ++j)
	// {
	// 	for (int i = 0; i <= n_col; ++i)
	// 	{
	// 		myfile<<V[j][i]<<'\t';
	// 	}
		
	// 	myfile<<'\n';	
	// }


	//prin_matrix(V);

	myfile.close();

return 0;
}

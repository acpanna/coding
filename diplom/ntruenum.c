#define REAL double
#define vec_REAL vec_double
#define to_REAL to_double \

#define EPSILON 0.00001

#include <fstream> 
#include <sstream> 
#include <NTL/new.h> 
#include <NTL/vec_double.h> 
#include <NTL/LLL.h> 
NTL_CLIENT
using namespace std;

struct Lattice{
	mat_ZZ b;
	vec_REAL*bd;
	vec_REAL*mu;
	vec_REAL c;
	vec_REAL N;
	vec_RR rrc;
	mat_RR rrmu;
	vec_long first_nonzero;
	vec_long first_nonzero_in_row;
	vec_long first_p;
	REAL l2_bound;
	REAL l0_bound;
	ZZ zl0_bound;
	long first_nonzero_in_last_row;
};

struct Enumeration{
	long level;
	long level_max;

	vec_long delta;
	vec_long d;
	vec_long eta;

	vec_REAL v;
	vec_REAL us;
	vec_REAL cs;
	vec_REAL y;
	vec_REAL*w;

	long maxsol;
	long nosol;
	ZZ maxit;
	ZZ noit;
	long start_level;
	long df;
	long dg;
};

struct Lattice lattice;
struct Enumeration e;
long nrows;
long ncols;
double elapsedTime;

int hoelder_prune()
{
	REAL cc= e.cs[e.level]/lattice.l0_bound;
	for(int i= 0;i<ncols;i++){
		cc-= abs(e.w[e.level][i]);
	}
	if(cc> EPSILON)return 1;
	else return 0;
}

int last_line_prune()
{
	if(e.level<lattice.first_nonzero_in_last_row
			&&abs(abs(e.w[e.level][ncols-1])-lattice.l0_bound)> 0.5){
		return 1;
	}else{
		return 0;
	}
}

int is_solution(vec_ZZ v)
{
	for(int i= 0;i<ncols;i++){
		if(abs(v[i])!=lattice.zl0_bound){
#if 1
			cerr<<"exact test fails: "<<i<<"\n";
#endif   
			return 0;
		}
	}
#if 0

	{
		int ones= 0;
		int minusones= 0;
		for(int j= 1;j<=(ncols-1)/2;j++){
			if(v(j)==1)ones++;
			if(v(j)==-1)minusones++;
		}
		if(e.df> 0){
			if(v(ncols)==-1&&(ones!=e.df-1||minusones!=e.df))return 0;
			if(v(ncols)==1&&(ones!=e.df||minusones!=e.df-1))return 0;
		}
	}

	{
		int ones= 0;
		int minusones= 0;
		for(int j= (ncols-1)/2+1;j<=ncols-1;j++){
			if(v(j)==1)ones++;
			if(v(j)==-1)minusones++;
		}
		if(e.dg> 0&&(e.dg!=ones||e.dg!=minusones))return 0;
	}

#endif 
	return 1;
}

int main(int argc,char*argv[])
{

	char suffix[1024];

	e.maxsol= 2147483647;
	lattice.l0_bound= 1;
	lattice.zl0_bound= 1;

	e.maxit= -1;
	e.df= 0;
	e.dg= 0;

	for(int i= 1;i<argc;i++){

		for(int j= 1;argv[i][j]!='\0';j++)
			argv[i][j]= (argv[i][j]>='A'&&argv[i][j]<='Z')?
				(argv[i][j]+'a'-'A'):argv[i][j];


		if(strncmp(argv[i],"-maxsol=",8)==0){
			strcpy(suffix,argv[i]+8);
			e.maxsol= atol(suffix);
		}else
			if(strncmp(argv[i],"-df=",4)==0){
				strcpy(suffix,argv[i]+4);
				istringstream iss(suffix,istringstream::in);
				iss>>e.df;
			}else
				if(strncmp(argv[i],"-dg=",4)==0){
					strcpy(suffix,argv[i]+4);
					istringstream iss(suffix,istringstream::in);
					iss>>e.dg;
				}else
					if(strncmp(argv[i],"-iterations=",12)==0){
						strcpy(suffix,argv[i]+12);
						istringstream iss(suffix,istringstream::in);
						iss>>e.maxit;
					}else
						if(strcmp(argv[i],"-?")==0||strcmp(argv[i],"-h")==0){
							cerr<<"\nlatticeenum [-maxsol=* (2^31-1)] ";
							cerr<<"[-df=* (0)] [-dg=* (0)] ";
							cerr<<"[-iterations=*] ";
							cerr<<"< lattice\n\n";
							exit(1);
						}

	}

	cin>>lattice.b;
	nrows= lattice.b.NumRows();
	ncols= lattice.b.NumCols();
	cerr<<"nrows="<<nrows<<"\t";
	cerr<<"ncols="<<ncols<<"\n";

	


	


	ComputeGS(lattice.b,lattice.rrmu,lattice.rrc);
	lattice.c.SetLength(nrows);
	lattice.mu= NTL_NEW_OP vec_REAL[nrows];
	for(int j= 0;j<nrows;j++){
		lattice.mu[j].SetLength(nrows);
		for(int i= 0;i<nrows;i++)lattice.mu[j][i]= to_REAL(lattice.rrmu[j][i]);
		lattice.mu[j][j]= 1.0;
		lattice.c[j]= to_REAL(lattice.rrc[j]);
	}

	
	


	lattice.bd= NTL_NEW_OP vec_REAL[nrows+1];
	for(int i= 0;i<nrows;i++){
		lattice.bd[i].SetLength(ncols);
		for(int k= 0;k<ncols;k++){
			lattice.bd[i][k]= to_REAL(lattice.b[i][k]);
			for(int j= 0;j<i;j++)lattice.bd[i][k]-= lattice.mu[i][j]*lattice.bd[j][k];
		}
	}

	


	for(int i= 0;i<nrows;i++){
		if(lattice.b[i][ncols-1]!=0){
			lattice.first_nonzero_in_last_row= i;
			break;
		}
	}
	lattice.l2_bound= ncols*lattice.l0_bound*lattice.l0_bound;

	



	e.v.SetLength(nrows);
	e.us.SetLength(nrows);
	e.y.SetLength(nrows);
	e.cs.SetLength(nrows+1);
	e.w= NTL_NEW_OP vec_REAL[nrows+1];
	for(int i= 0;i<=nrows;i++){
		e.w[i].SetLength(ncols);
		for(int j= 0;j<ncols;j++)e.w[i][j]= 0;
		e.cs[i]= 0;
	}

	e.delta.SetLength(nrows);
	e.eta.SetLength(nrows);
	e.d.SetLength(nrows);
	for(int i= 0;i<nrows;i++){
		e.eta[i]= e.d[i]= 1;
		e.us[i]= e.v[i]= e.y[i]= e.delta[i]= 0;
	}
	


	e.level= lattice.first_nonzero_in_last_row;
	cerr<<"start level = "<<e.level<<"\n";
	e.level_max= e.level;

	

	e.v[e.level]= 1;
	e.us[e.level]= 1;
	e.nosol= 0;
	e.noit= 0;


	elapsedTime= GetTime();
	cerr<<"Start of loop...\n";
	while(e.level<nrows){
		


		e.noit++;
		if(e.maxit>=0&&e.noit>=e.maxit){
			cerr<<"Maximum number of iterations reached -> exit\n";
			break;
		}

		

		;
		


		REAL dum= e.us[e.level]+e.y[e.level];
		e.cs[e.level]= 
			e.cs[e.level+1]+dum*dum*lattice.c[e.level];

		

		;
		if(e.cs[e.level]> (lattice.l2_bound+EPSILON)){
			e.level++;
			


			if(e.level>=nrows)continue;
			if(e.level_max<e.level){
				e.level_max= e.level;
#if 0
				cerr<<"new max level = "<<e.level_max<<"\n";
#endif  
			}
			if(e.eta[e.level]==0){
				e.delta[e.level]*= -1;
				if(e.delta[e.level]*e.d[e.level]>=0)
					e.delta[e.level]+= e.d[e.level];
			}else{
				e.delta[e.level]+= 
					(e.delta[e.level]*e.d[e.level]>=0)?
					e.d[e.level]:-e.d[e.level];
			}
			e.us[e.level]= e.v[e.level]+to_REAL(e.delta[e.level]);

			

			;
		}else{
			


			for(int j= 0;j<ncols;j++){
				e.w[e.level][j]= 
					e.w[e.level+1][j]+dum*lattice.bd[e.level][j];
			}

			

			;
			if(e.level> 0){
				


				if(last_line_prune()||hoelder_prune()){
					if(e.eta[e.level]==1){
						e.level++;
					}else{
						e.eta[e.level]= 1;
					}
					


					if(e.level>=nrows)continue;
					if(e.level_max<e.level){
						e.level_max= e.level;
#if 0
						cerr<<"new max level = "<<e.level_max<<"\n";
#endif  
					}
					if(e.eta[e.level]==0){
						e.delta[e.level]*= -1;
						if(e.delta[e.level]*e.d[e.level]>=0)
							e.delta[e.level]+= e.d[e.level];
					}else{
						e.delta[e.level]+= 
							(e.delta[e.level]*e.d[e.level]>=0)?
							e.d[e.level]:-e.d[e.level];
					}
					e.us[e.level]= e.v[e.level]+to_REAL(e.delta[e.level]);

					

					;
				}else{
					e.level--;
					e.eta[e.level]= 0;
					e.delta[e.level]= 0;

					


					e.y[e.level]= 0.0;
					for(int i= e.level_max;i> e.level;i--)
						e.y[e.level]+= lattice.mu[i][e.level]*e.us[i];

					

					;
					e.us[e.level]= e.v[e.level]= round(-e.y[e.level]);
					e.d[e.level]= (e.v[e.level]> -e.y[e.level])?-1:1;
				}

				

				;
			}else{
				


				if(!hoelder_prune()){
					vec_ZZ erg;
					erg.SetLength(ncols);

					for(int i= 0;i<nrows;i++)erg+= to_ZZ(e.us[i])*lattice.b[i];

					if(is_solution(erg)){
						e.nosol++;
						


						cerr<<"solution "<<e.nosol<<":\t";
						cerr<<"[";
						long n= erg.length();
						long fak= (erg(n)==1)?-1:1;
						for(int j= 1;j<=n-2;j++)cerr<<(1+fak*erg(j))/2<<" ";
						cerr<<" | "<<erg(n-1)<<" "<<erg(n)<<"]\n";


						

						;
						if(e.nosol>=e.maxsol){
							cerr<<"Maximum number of solutions reached -> exit\n";
							break;
						}
					}
				}else{
#if 0
					cerr<<"nix: "<<e.w[0]<<"\t"<<e.us<<"\n";
#endif  
				}
				


				if(e.level>=nrows)continue;
				if(e.level_max<e.level){
					e.level_max= e.level;
#if 0
					cerr<<"new max level = "<<e.level_max<<"\n";
#endif  
				}
				if(e.eta[e.level]==0){
					e.delta[e.level]*= -1;
					if(e.delta[e.level]*e.d[e.level]>=0)
						e.delta[e.level]+= e.d[e.level];
				}else{
					e.delta[e.level]+= 
						(e.delta[e.level]*e.d[e.level]>=0)?
						e.d[e.level]:-e.d[e.level];
				}
				e.us[e.level]= e.v[e.level]+to_REAL(e.delta[e.level]);

				

				;

				

				;
			}
		}

	}

	

	;
	


	cerr<<"Number of solutions  = "<<e.nosol<<"\n";
	cerr<<"Number of iterations = "<<e.noit<<"\n";
	cerr<<"time: "<<(GetTime()-elapsedTime)<<"sec \n";

	

	;
	cerr<<"\nFinished!!\n";
	return 0;
}



;



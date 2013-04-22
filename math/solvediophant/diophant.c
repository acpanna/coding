#define DEEPINSERT 1
#define DEEPINSERT_CONST 2000
#define VERBOSE 1 \

#define GIVENS 1
#define LASTLINESFACTOR "1"
#define EPSILON 0.000001
#define LLLCONST_LOW 0.75
#define LLLCONST_HIGH 0.99
#define LLLCONST_HIGHER 0.999 \

#define SQRT sqrt
#define DOUBLE double
#define COEFF struct coe \

#define ROUND(r) ceil(r-0.5)  \

#define FINCKEPOHST 1
#define FINCKEPOHSTEXTREME 0 \

/*2:*/
#line 43 "./diophant.w"

/*5:*/
#line 150 "./diophant.w"

#include <stdio.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h> 
#include <malloc.h> 
#include <math.h> 
#include <gmp.h> 
#undef BLAS
#if defined(BLAS)
#include "blas/blas1.h"
#else
#if defined(BLAS2)
#include "blas_intel/cblas.h"
#endif
#endif

/*:5*/
#line 44 "./diophant.w"
;
/*6:*/
#line 168 "./diophant.w"

struct coe{
mpz_t c;
int p;
};

/*:6*/
#line 45 "./diophant.w"
;
/*7:*/
#line 178 "./diophant.w"

mpz_t matrix_factor;
mpz_t max_norm;
mpz_t max_norm_initial;
mpz_t max_up;
mpz_t dummy;
long nom,denom;
mpz_t lastlines_factor;

/*:7*//*8:*/
#line 188 "./diophant.w"

int system_rows,system_columns;
int lattice_rows,lattice_columns;
COEFF**lattice;
int free_RHS;
int iszeroone;
mpz_t*upperbounds;
mpz_t upperbounds_max;
mpz_t upfac;

/*:8*//*9:*/
#line 199 "./diophant.w"

int*original_columns;
int no_original_columns;
int cut_after_coeff;
long stop_after_solutions;
long stop_after_loops;
long nosolutions;
int iterate;
int no_iterates;
int bkz_beta,bkz_p;
int SILENT;
int nboundvars;

/*:9*//*39:*/
#line 723 "./diophant.w"

mpz_t soltest_u;
mpz_t soltest_s;
mpz_t soltest_upfac;
/*:39*//*110:*/
#line 2448 "./diophant.w"

static FILE*fp;

/*:110*/
#line 46 "./diophant.w"
;
/*10:*/
#line 216 "./diophant.w"

#define put_to(i,j,val) mpz_set(lattice[i][j+1].c,val)
#define smult_lattice(i,j,factor) mpz_mul(lattice[i][j+1].c,lattice[i][j+1].c,factor)
#define get_entry(i,j) lattice[i][j+1].c

/*:10*/
#line 47 "./diophant.w"
;
/*28:*/
#line 517 "./diophant.w"

/*29:*/
#line 527 "./diophant.w"

void debug_print(char*m,int l){
#ifndef NO_OUTPUT
if(VERBOSE>=l){
printf("debug>> %s\n",m);fflush(stdout);
}
#endif
return;
}

/*:29*/
#line 518 "./diophant.w"
;
/*30:*/
#line 539 "./diophant.w"

#if 1
void print_lattice(){
int i,j;
for(i= 0;i<lattice_columns;i++){
for(j= 0;j<lattice_rows;j++){
mpz_out_str(NULL,10,get_entry(i,j));
printf(" ");
}
printf("\n");
}
printf("\n");fflush(stdout);
return;
}
#else
void print_lattice(){
int i,j;
for(j= 0;j<lattice_rows;j++){
for(i= 0;i<lattice_columns;i++){
mpz_out_str(NULL,10,get_entry(i,j));
printf(" ");
}
printf("\n");
}
printf("\n");fflush(stdout);
return;
}
#endif

/*:30*/
#line 519 "./diophant.w"
;
/*35:*/
#line 662 "./diophant.w"

void shufflelattice(){
COEFF*tmp;
int i,j,r;

srand((unsigned)(time(0)));
for(j= 0;j<100;j++){
for(i= lattice_columns-2;i> 0;i--){
r= rand()%i;
tmp= lattice[r];
lattice[r]= lattice[i];
lattice[i]= tmp;
}
}
return;
}

/*:35*/
#line 520 "./diophant.w"
;
/*31:*/
#line 570 "./diophant.w"

void print_NTL_lattice(){
int i,j;
#if 1
printf("%d\n",system_rows);
printf("\n[");
for(i= 0;i<lattice_columns-1;i++){
printf("[");
for(j= 0;j<lattice_rows;j++){
mpz_out_str(NULL,10,get_entry(i,j));
printf(" ");
}
printf("]");
printf("\n");
}
printf("]\n");fflush(stdout);
#if 0
printf("\n");
mpz_out_str(NULL,10,upperbounds_max);
printf("\n\n[");
for(i= 0;i<lattice_columns-2;i++){
mpz_out_str(NULL,10,upperbounds[i]);
printf(" ");
}
printf("]\n");fflush(stdout);
#endif
#endif
return;
}

/*:31*/
#line 521 "./diophant.w"
;
/*32:*/
#line 602 "./diophant.w"

long gcd(long n1,long n2){
long a,b,c;

if(n1> n2){
a= n1;b= n2;
}else{
a= n2;b= n1;
}

while((c= a%b)> 0){
a= b;b= c;
}
return b;
}
/*:32*/
#line 522 "./diophant.w"
;
/*33:*/
#line 618 "./diophant.w"

void coeffinit(COEFF*v,int z)
{
short r= 0;
short i;
for(i= z;i>=0;i--){
v[i].p= r;
if(mpz_sgn(v[i].c)!=0)r= i;
}
return;
}

/*:33*/
#line 523 "./diophant.w"
;
/*34:*/
#line 635 "./diophant.w"

int cutlattice(){
int j,i,flag;

/*36:*/
#line 680 "./diophant.w"

j= 0;
do{
if(lattice[j][0].p> system_rows)
j++;
else{
for(i= j+1;i<lattice_columns;i++)lattice[i-1]= lattice[i];
lattice_columns--;
}
}while(j<lattice_columns-1);

/*:36*/
#line 639 "./diophant.w"
;
/*37:*/
#line 694 "./diophant.w"

flag= 0;
for(i= 0;i<lattice_columns;i++)if(mpz_sgn(get_entry(i,lattice_rows-1))!=0){
flag= 1;
break;
}
if(flag==0){
#ifndef NO_OUTPUT
printf("Nonhomogenous solution not possible.\n");fflush(stdout);
#endif
exit(1);
return 0;
}
/*:37*/
#line 640 "./diophant.w"
;

for(j= 0;j<lattice_columns;j++){
if(nboundvars==0){
for(i= system_rows;i<lattice_rows;i++)
put_to(j,i-system_rows,get_entry(j,i));
}else{
for(i= system_rows;i<system_rows+nboundvars;i++)
put_to(j,i-system_rows,get_entry(j,i));
for(i= system_rows+system_columns;i<lattice_rows;i++)
put_to(j,i-system_rows-system_columns+nboundvars,get_entry(j,i));
}
}
lattice_rows-= system_rows;
lattice_rows-= (system_columns-nboundvars);

for(j= 0;j<lattice_columns;j++)coeffinit(lattice[j],lattice_rows);

return 1;
}

/*:34*/
#line 524 "./diophant.w"
;
/*38:*/
#line 708 "./diophant.w"

int solutiontest(int position){
int i,j;
int low,up;
int end;

/*41:*/
#line 733 "./diophant.w"

if(mpz_cmpabs(get_entry(position,lattice_rows-1),max_norm)!=0)return 0;
if(mpz_sgn(get_entry(position,lattice_rows-1-free_RHS))==0)return 0;
/*:41*/
#line 714 "./diophant.w"
;
/*42:*/
#line 743 "./diophant.w"

low= 0;
up= lattice_rows-1-free_RHS;
if(lattice_columns==system_columns+2+free_RHS){
for(i= 0;i<system_rows;i++)
if(mpz_sgn(get_entry(position,i))!=0)return 0;
low= system_rows;
}

if(iszeroone){
for(i= low;i<up;i++){
if(mpz_cmpabs(get_entry(position,i),max_norm)!=0)return 0;
}
}else{
for(i= low;i<up;i++){
if(mpz_cmpabs(get_entry(position,i),max_norm)> 0)return 0;
}
}
/*:42*/
#line 715 "./diophant.w"
;

mpz_set_si(upfac,1);
mpz_divexact(soltest_s,get_entry(position,lattice_rows-1),lastlines_factor);
/*43:*/
#line 764 "./diophant.w"

i= low;
if(cut_after_coeff==-1){
end= no_original_columns;
#if 0
if(nboundvars!=0){
end= nboundvars;
}
#endif
}else{
end= cut_after_coeff;
}

for(j= 0;j<end;j++){
if(original_columns[j]==0){
mpz_set_si(soltest_u,0);
}else{
if(!iszeroone){
if(mpz_cmp_si(upperbounds[i-low],0)!=0){
mpz_divexact(soltest_upfac,upperbounds_max,upperbounds[i-low]);
}else{
mpz_set(soltest_upfac,upperbounds_max);
}
}
mpz_set(soltest_u,get_entry(position,i));
mpz_sub(soltest_u,soltest_u,soltest_s);
mpz_divexact(soltest_u,soltest_u,max_norm_initial);
mpz_divexact(soltest_u,soltest_u,soltest_upfac);
mpz_divexact_ui(soltest_u,soltest_u,denom);
mpz_abs(soltest_u,soltest_u);
i++;
}
mpz_out_str(NULL,10,soltest_u);
printf(" ");
if(stop_after_solutions==1){
mpz_out_str(fp,10,soltest_u);
fprintf(fp," ");
}
}
if(free_RHS){
mpz_divexact(soltest_u,get_entry(position,up),max_up);
mpz_divexact(soltest_u,soltest_u,lastlines_factor);
mpz_abs(soltest_u,soltest_u);
printf(" L = ");
mpz_out_str(NULL,10,soltest_u);
}
printf("\n");fflush(stdout);
if(stop_after_solutions==1)fprintf(fp,"\n");

/*:43*/
#line 719 "./diophant.w"
;
/*44:*/
#line 814 "./diophant.w"

if(stop_after_solutions==1){
#ifndef NO_OUTPUT
printf("Stopped in phase 1 after finding a random solution\n");
#endif
exit(0);
}
/*:44*/
#line 720 "./diophant.w"
;
return 1;
}
/*:38*/
#line 525 "./diophant.w"
;

/*:28*/
#line 48 "./diophant.w"
;
/*45:*/
#line 825 "./diophant.w"

/*63:*/
#line 1156 "./diophant.w"

/*64:*/
#line 1170 "./diophant.w"

DOUBLE scalarproductlfp(COEFF*v,COEFF*w)
{
DOUBLE erg;
long t1,t2;
COEFF*vv,*ww;

erg= 0.0;
t1= v[0].p;
t2= w[0].p;
if((t1==0)||(t2==0))return 0;

do{
if(t2> t1){
t1= v[t2-1].p;
if(t2!=t1){
if(t1==0)break;
t2= w[t2].p;
if(t2==0)break;
}
else goto gleich;
}
else if(t2<t1){
t2= w[t1-1].p;
if(t2!=t1){
if(t2==0)break;
t1= v[t1].p;
if(t1==0)break;
}
else goto gleich;
}
else{
gleich:vv= &(v[t1]);
ww= &(w[t2]);
erg+= (DOUBLE)mpz_get_d(vv->c)*(DOUBLE)mpz_get_d(ww->c);
t1= vv->p;
if(t1==0)break;
t2= ww->p;
if(t2==0)break;
}
}
while(1);

return(erg);
}
/*:64*/
#line 1157 "./diophant.w"
;
/*65:*/
#line 1215 "./diophant.w"

DOUBLE scalarproductfp(DOUBLE*v,DOUBLE*w,int n)
{
DOUBLE r;
#if defined(BLAS)
r= ddot(n,v,1,w,1);
#else
#if defined(BLAS2)
r= cblas_ddot(n,v,1,w,1);
#else
int i;

r= 0.0;
for(i= n-1;i>=0;i--)r+= v[i]*w[i];
#endif
#endif
return r;
}

/*:65*/
#line 1158 "./diophant.w"
;
/*66:*/
#line 1237 "./diophant.w"

int lllalloc(DOUBLE***mu,DOUBLE**c,DOUBLE**N,DOUBLE***bs,int s,int z)
{
int i,m;

if((z<1)||(s<1))return 0;

(*c)= (DOUBLE*)calloc(s,sizeof(DOUBLE));
(*N)= (DOUBLE*)calloc(s,sizeof(DOUBLE));
(*mu)= (DOUBLE**)calloc(s,sizeof(DOUBLE*));
for(i= 0;i<s;i++)(*mu)[i]= (DOUBLE*)calloc(z,sizeof(DOUBLE));

m= (z> s)?z:s;
(*bs)= (DOUBLE**)calloc(m,sizeof(DOUBLE*));

for(i= 0;i<m;i++)
(*bs)[i]= (DOUBLE*)calloc(m,sizeof(DOUBLE));

return 1;
}
/*:66*/
#line 1159 "./diophant.w"
;
/*67:*/
#line 1257 "./diophant.w"

int lllfree(DOUBLE**mu,DOUBLE*c,DOUBLE*N,DOUBLE**bs,int s)
{
int i;

for(i= 0;i<s;++i)free(bs[i]);
free(bs);
for(i= 0;i<s;++i)free(mu[i]);
free(mu);
free(N);
free(c);

return 1;
}

/*:67*/
#line 1160 "./diophant.w"
;

/*:63*/
#line 826 "./diophant.w"
;
/*46:*/
#line 839 "./diophant.w"

#define TWOTAUHALF 67108864.0 
int lllfp(COEFF**b,DOUBLE**mu,DOUBLE*c,DOUBLE*N,DOUBLE**bs,
int start,int s,int z,DOUBLE delta)
{
/*48:*/
#line 899 "./diophant.w"

int i,j,k;
DOUBLE ss;
int counter;
/*:48*//*51:*/
#line 950 "./diophant.w"

int Fc,Fr;
DOUBLE mus,cc;
mpz_t musvl;
mpz_t hv;
DOUBLE*swapd;

/*:51*//*53:*/
#line 971 "./diophant.w"

int ii,iii;
COEFF*swapvl;
COEFF*bb;
/*:53*//*60:*/
#line 1088 "./diophant.w"

int Fi;

/*:60*/
#line 844 "./diophant.w"
;
mpz_init(musvl);
mpz_init(hv);

if((z<=1)||(s<=1)){
#ifndef NO_OUTPUT
printf("Wrong dimensions in lllfp\n");fflush(stdout);
#endif
return(0);
}

k= (start> 1)?start:1;

/*47:*/
#line 889 "./diophant.w"

if(k<1)k= 1;
for(i= k-1;i<s;++i){
ss= 0.0;
for(j= 0;j<z;++j){
bs[i][j]= (DOUBLE)mpz_get_d(b[i][j+1].c);
ss+= bs[i][j]*bs[i][j];
}
N[i]= SQRT(ss);
}
/*:47*/
#line 857 "./diophant.w"
;
counter= 0;
while(k<s){
#if VERBOSE >  3
if((counter%500)==0){
#ifndef NO_OUTPUT
printf("LLL: %d k:%d\n",counter,k);fflush(stdout);
#endif
}
counter++;
#endif
/*49:*/
#line 906 "./diophant.w"

if(k==1)c[0]= N[0]*N[0];
c[k]= N[k]*N[k];
for(j= 0;j<k;j++){
ss= scalarproductfp(bs[k],bs[j],z);
if(fabs(ss)<N[k]*N[j]/TWOTAUHALF){
ss= (DOUBLE)scalarproductlfp(b[k],b[j]);
}
for(i= 0;i<j;i++)ss-= mu[j][i]*mu[k][i]*c[i];
mu[k][j]= ss/c[j];
c[k]-= ss*mu[k][j];
}
/*:49*/
#line 868 "./diophant.w"
;
/*50:*/
#line 932 "./diophant.w"

Fc= Fr= 0;
for(j= k-1;j>=0;j--){
if(fabs(mu[k][j])> 0.5){
/*52:*/
#line 960 "./diophant.w"

mus= ROUND(mu[k][j]);
mpz_set_d(musvl,mus);
if(fabs(mus)> TWOTAUHALF){
Fc= 1;
#if 0
printf("correct possible rounding errors\n");fflush(stdout);
#endif
}


/*:52*/
#line 936 "./diophant.w"
;
Fr= 1;
/*54:*/
#line 984 "./diophant.w"

switch(mpz_get_si(musvl)){
case 1:
/*55:*/
#line 999 "./diophant.w"

i= b[j][0].p;
while(i!=0){
bb= &(b[k][i]);
mpz_sub(bb->c,bb->c,b[j][i].c);
iii= bb->p;
if((b[k][i-1].p!=i)&&(mpz_sgn(bb->c)!=0))
for(ii= i-1;(ii>=0)&&(b[k][ii].p==iii);ii--)b[k][ii].p= i;
else if(mpz_sgn(bb->c)==0){
for(ii= i-1;(ii>=0)&&(b[k][ii].p==i);ii--)b[k][ii].p= iii;
}
i= b[j][i].p;
}
for(i= 0;i<j;i++)mu[k][i]-= mu[j][i];
/*:55*/
#line 987 "./diophant.w"
;
break;

case-1:
/*56:*/
#line 1015 "./diophant.w"

i= b[j][0].p;
while(i!=0){
bb= &(b[k][i]);
mpz_add(bb->c,bb->c,b[j][i].c);
iii= bb->p;
if((b[k][i-1].p!=i)&&(mpz_sgn(bb->c)!=0))
for(ii= i-1;(ii>=0)&&(b[k][ii].p==iii);ii--)b[k][ii].p= i;
else if(mpz_sgn(bb->c)==0){
for(ii= i-1;(ii>=0)&&(b[k][ii].p==i);ii--)b[k][ii].p= iii;
}
i= b[j][i].p;
}
for(i= 0;i<j;i++)mu[k][i]+= mu[j][i];
/*:56*/
#line 991 "./diophant.w"
;
break;

default:
/*57:*/
#line 1031 "./diophant.w"

i= b[j][0].p;
while(i!=0){
bb= &(b[k][i]);
mpz_submul(bb->c,b[j][i].c,musvl);
iii= bb->p;
if((b[k][i-1].p!=i)&&(mpz_sgn(bb->c)!=0))
for(ii= i-1;(ii>=0)&&(b[k][ii].p==iii);ii--)b[k][ii].p= i;
else if(mpz_sgn(bb->c)==0){
for(ii= i-1;(ii>=0)&&(b[k][ii].p==i);ii--)b[k][ii].p= iii;
}
i= b[j][i].p;
}
#if 0
daxpy(j,-mus,mu[k],1,mu[j],1);
#endif
for(i= 0;i<j;i++)mu[k][i]-= mu[j][i]*mus;
/*:57*/
#line 995 "./diophant.w"
;
}
/*:54*/
#line 938 "./diophant.w"
;
mu[k][j]-= mus;
solutiontest(k);
}
}
/*58:*/
#line 1048 "./diophant.w"

{
N[k]= 0.0;
for(i= 0;i<z;i++){
bs[k][i]= (DOUBLE)mpz_get_d(b[k][i+1].c);
N[k]+= bs[k][i]*bs[k][i];
}
N[k]= SQRT(N[k]);
}
/*:58*/
#line 943 "./diophant.w"
;
if(Fc==1){
k= (k-1> 1)?k-1:1;
}else{
/*59:*/
#line 1062 "./diophant.w"

if(N[k]<-EPSILON){
#ifndef NO_OUTPUT
fprintf(stderr,"Nk negativ! contact the author.\n");
fflush(stderr);
printf("Nk negativ! contact the author.\n");fflush(stdout);
#endif
exit(1);
}
if(N[k]<0.5){
swapvl= b[k];
ss= N[k];
swapd= bs[k];
for(i= k+1;i<s;i++){
b[i-1]= b[i];
N[i-1]= N[i];
bs[i-1]= bs[i];
}
b[s-1]= swapvl;
N[s-1]= ss;
bs[s-1]= swapd;
s= s-1;
k= 1;
continue;
}

/*:59*/
#line 947 "./diophant.w"
;
}

/*:50*/
#line 869 "./diophant.w"
;
#if defined(DEEPINSERT)
/*61:*/
#line 1099 "./diophant.w"

cc= N[k]*N[k];
j= 0;
Fi= 0;
while(j<k){
#if 0
if((j> DEEPINSERT_CONST&&j<k-DEEPINSERT_CONST)||delta*c[j]<=cc){
#endif
if(delta*c[j]<=cc){
cc-= mu[k][j]*mu[k][j]*c[j];
j++;
}else{
swapvl= b[k];
ss= N[k];
swapd= bs[k];
for(i= k-1;i>=j;i--){
b[i+1]= b[i];
N[i+1]= N[i];
bs[i+1]= bs[i];
}
b[j]= swapvl;
N[j]= ss;
bs[j]= swapd;

Fi= 1;
break;
}
}
if(Fi==1)k= (j-1> 1)?j-1:1;
else{
k++;
}

/*:61*/
#line 871 "./diophant.w"
;
#else
/*62:*/
#line 1139 "./diophant.w"

if(delta*c[k-1]> c[k]+mu[k][k-1]*mu[k][k-1]*c[k-1]){
swapvl= b[k];
b[k]= b[k-1];
b[k-1]= swapvl;
ss= N[k];
N[k]= N[k-1];
N[k-1]= ss;
swapd= bs[k];
bs[k]= bs[k-1];
bs[k-1]= swapd;

k= (k-1> 1)?k-1:1;
}else k++;

/*:62*/
#line 873 "./diophant.w"
;
#endif
}
mpz_clear(hv);
mpz_clear(musvl);
return(1);

}
/*:46*/
#line 827 "./diophant.w"
;
/*68:*/
#line 1273 "./diophant.w"

double logD(COEFF**lattice,DOUBLE*c,int s,int z){
double d= 0.0;
int i;
for(i= 0;i<s;i++){
d+= log(c[i])*(s-i);
}
d*= 0.5;
return d;
}

/*:68*/
#line 828 "./diophant.w"
;
/*69:*/
#line 1287 "./diophant.w"

double orthogonal_defect(COEFF**lattice,DOUBLE*c,int s,int z){
double defect= 0.0;

#if 0
int i;
for(i= 0;i<s;i++)defect+= log((double)normfp(lattice[i]))
-log((double)c[i]);
#endif
defect/= 2.0;
return defect;
}

/*:69*/
#line 829 "./diophant.w"
;
/*70:*/
#line 1301 "./diophant.w"

void lll(COEFF**b,int s,int z,DOUBLE quality)
{
DOUBLE**mu;
DOUBLE*c;
DOUBLE*N;
DOUBLE**bs;
int r;

lllalloc(&mu,&c,&N,&bs,s,z);
r= lllfp(b,mu,c,N,bs,1,s,z,quality);
lllfree(mu,c,N,bs,s);

return;
}

/*:70*/
#line 830 "./diophant.w"
;
/*71:*/
#line 1321 "./diophant.w"

DOUBLE iteratedlll(COEFF**b,int s,int z,int no_iterates,DOUBLE quality)
{
DOUBLE**mu;
DOUBLE*c;
DOUBLE*N;
DOUBLE**bs;
int r,l,i,j,runs;
COEFF*swapvl;
DOUBLE lD;

lllalloc(&mu,&c,&N,&bs,s,z);
r= lllfp(b,mu,c,N,bs,1,s,z,quality);

lD= logD(b,c,s,z);
#ifndef NO_OUTPUT
printf("   log(D)= %f\n",lD);
fflush(stdout);
#endif

for(runs= 1;runs<no_iterates;runs++){


for(j= s-1;j> 0;j--){
for(l= j-1;l>=0;l--){


if(N[l]> N[j]){
swapvl= b[l];
for(i= l+1;i<=j;i++)b[i-1]= b[i];
b[j]= swapvl;
}
}
}

r= lllfp(b,mu,c,N,bs,1,s,z,quality);
lD= logD(b,c,s,z);
#ifndef NO_OUTPUT
printf("%d: log(D)= %f\n",runs,lD);
fflush(stdout);
#endif
}

lllfree(mu,c,N,bs,s);

return lD;
}

/*:71*/
#line 831 "./diophant.w"
;
/*72:*/
#line 1370 "./diophant.w"

/*83:*/
#line 1788 "./diophant.w"

DOUBLE laurin(DOUBLE x){
static DOUBLE K1= 0.9181938533204672741780329736405620;
static DOUBLE K2= 0.0833333333333333333333333333333333333;
static DOUBLE K3= 0.0027777777777777777777777777777777777;
static DOUBLE K4= 0.000793650793650793650793650793650793650;
static DOUBLE K5= 0.0005952380952380952380952380952380952380;
static DOUBLE K6= 0.000841750841750841750841750841750841750;
static DOUBLE K7= 0.001917526917526917526917526917526917526;
static DOUBLE K8= 0.00641025641025641025641025641025641025;
static DOUBLE K9= 0.0295506529510021209716796875;
static DOUBLE K10= 0.17968122661113739013671875;
static DOUBLE K11= 1.39243221282958984375;
DOUBLE y;

y= 1.0/(x*x);
y= (x-0.5)*log(x)-x+K1+
(1.0/x)*(K2-y*(K3-y*(K4-y*(K5-y*(K6-y*(K7-y*(K8-y*(K9-y*(K10-y*K11)))))))));
return y;
}

DOUBLE log_gamma(DOUBLE x){
DOUBLE y;
int i,n;
static int MM= 13;

if(x<=0.0)return-1.0;

if(x> 100000000.0){
y= x*(log(x)-1.0);
}else{
if(x>=MM){
y= laurin(x);
}else{
n= MM-(int)(floor(x));
y= x-floor(x)+MM;
y= laurin(y);
for(i= 0;i<n;i++)y-= log(y+i);
}
}
return y;
}

/*:83*/
#line 1371 "./diophant.w"
;
/*80:*/
#line 1581 "./diophant.w"

DOUBLE enumerate(DOUBLE**mu,DOUBLE*c,long*u,int s,
int start_block,int end_block,int p)
{
DOUBLE cd,dum;
DOUBLE*y,*cs,*eta;

DOUBLE**sigma;
int*r;

long*us,*delta,*d,*v;
int t,i,t_up,len;
double alpha;
int tmax;
static DOUBLE pi= 3.141592653589793238462643383;
static DOUBLE e= 2.718281828459045235360287471352662497757247093;
int SCHNITT= 40;

if(c[start_block]<=EPSILON){
#ifndef NO_OUTPUT
fprintf(stderr,"Hier ist was faul! start_block=%d %f\n",start_block,
(double)c[start_block]);fflush(stderr);
printf("Hier ist was faul! start_block=%d %f\n",start_block,
(double)c[start_block]);fflush(stdout);
#endif
exit(1);
}

us= (long*)calloc(s+1,sizeof(long));
cs= (DOUBLE*)calloc(s+1,sizeof(DOUBLE));
y= (DOUBLE*)calloc(s+1,sizeof(DOUBLE));
delta= (long*)calloc(s+1,sizeof(long));
d= (long*)calloc(s+1,sizeof(long));
eta= (DOUBLE*)calloc(s+1,sizeof(DOUBLE));
v= (long*)calloc(s+1,sizeof(long));

sigma= (DOUBLE**)calloc(s,sizeof(DOUBLE*));
r= (int*)calloc(s+1,sizeof(int));
for(i= 0;i<s;i++){
sigma[i]= (DOUBLE*)calloc(s,sizeof(DOUBLE));
r[i]= i-1;
}


len= (end_block+1-start_block);
for(i= start_block;i<=end_block+1;i++){
cs[i]= y[i]= 0.0;
u[i]= us[i]= v[i]= delta[i]= 0;
d[i]= 1;
}
us[start_block]= u[start_block]= 1;
cd= c[start_block];

t= tmax= start_block;


/*82:*/
#line 1747 "./diophant.w"

eta[start_block]= 0.0;
if(end_block-start_block<=SCHNITT){
for(i= start_block+1;i<=end_block;i++)eta[i]= 0.0;
}
else{
dum= log(c[start_block]);



#if 0
for(i= start_block+1;i<=end_block;i++){
t_up= i-start_block;
eta[i]= exp((log_gamma(t_up/2.0+1)-p*log(2.0))*2.0/t_up+dum/t_up)/pi;
if(i<end_block)dum+= log(c[i]);
#if 0
if(i==start_block+1)printf("eta: \n");
printf("%0.2lf ",eta[i]);
if(i==end_block)printf("\n");
#endif
}
#else



dum= log(c[start_block]);
for(i= start_block+1;i<=end_block;i++){
t_up= i-start_block;
eta[i]= 0.5*t_up*exp((log(pi*t_up)-2.0*p*log(2.0)+dum)/t_up)/(pi*e);
if(i<end_block)dum+= log(c[i]);
#if 0
if(i==start_block+1)printf("eta: ");
printf("%0.2lf ",eta[i]);
if(i==end_block){
printf("\n");
fflush(stdout);
}
#endif
}
#endif
}
/*:82*/
#line 1637 "./diophant.w"
;
while(t<=end_block){
/*81:*/
#line 1657 "./diophant.w"

{
dum= us[t]+y[t];
cs[t]= cs[t+1]+dum*dum*c[t];

#if 0
if(cs[t]<cd-eta[t]){

#else
if(len<=SCHNITT){
alpha= 1.0;
}else{
alpha= sqrt(1.20*(end_block+1-t)/len);
if(alpha>=1.0)alpha= 1.0;
}
alpha*= cd;



if(cs[t]<alpha-EPSILON){
#endif
if(t> start_block){
t--;
if(r[t+1]> r[t])r[t]= r[t+1];

delta[t]= 0;
for(i= r[t+1];i> t;i--)sigma[i][t]= sigma[i+1][t]+us[i]*mu[i][t];
#if 0
dum= 0.0;
for(i= t+1;i<=tmax;i++)dum+= us[i]*mu[i][t];
if(fabs(dum-sigma[t+1][t])> 0.001){
printf("1diff: %0.6lf %0.6lf %0.8lf\n",dum,sigma[t+1][t],dum-sigma[t+1][t]);
}
#endif
y[t]= sigma[t+1][t];
us[t]= v[t]= (long)(ROUND(-y[t]));
d[t]= (v[t]> -y[t])?-1:1;
}else{
printf("success %0.4lf %0.4lf %0.8lf\n",cd,cs[start_block],cd-cs[start_block]);
cd= cs[start_block];
for(i= start_block;i<=end_block;i++)u[i]= us[i];
goto nextstep;
}
}else{
t++;
r[t]= t;
nextstep:
if(tmax<t)tmax= t;
if(t<tmax)delta[t]= -delta[t];
if(delta[t]*d[t]>=0)delta[t]+= d[t];
us[t]= v[t]+delta[t];
}
}

/*:81*/
#line 1639 "./diophant.w"
;
}
free(us);
free(cs);
free(y);
free(delta);
free(d);
free(eta);
free(v);
for(i= s-1;i>=0;i--){
free(sigma[i]);
}
free(sigma);
free(r);
return(cd);
}

/*:80*/
#line 1372 "./diophant.w"
;
/*73:*/
#line 1391 "./diophant.w"

DOUBLE bkz(COEFF**b,int s,int z,DOUBLE delta,int beta,int p)
{
/*74:*/
#line 1452 "./diophant.w"

DOUBLE**mu,*c,*N;
DOUBLE**bs;
static mpz_t hv;
int zaehler;
int h,i,last;
int start_block,end_block;
long*u;
DOUBLE new_cj;
DOUBLE lD;

mpz_init(hv);

/*:74*//*76:*/
#line 1495 "./diophant.w"

int g,ui,q,j;
COEFF*swapvl;

/*:76*/
#line 1394 "./diophant.w"
;

last= s-2;
if(last<1){
#ifndef NO_OUTPUT
printf("BKZ: the number of basis vectors is too small.\n");
printf("Probably the number of rows is less or equal");
printf(" to number of columns in the original system\n");
printf("Maybe you have to increase c0 (the first parameter)!\n");
#endif
mpz_clear(hv);
return 0.0;
}

u= (long*)calloc(s,sizeof(long));
for(i= 0;i<s;i++)u[i]= 0;

lllalloc(&mu,&c,&N,&bs,s,z);
lllfp(b,mu,c,N,bs,1,s,z,delta);

start_block= zaehler= -1;
while(zaehler<last){

start_block++;
if(start_block==last)start_block= 0;
end_block= (start_block+beta-1<last)?start_block+beta-1:last;

#if 0
printf("start_block=%d, end_block=%d\n",start_block,end_block);
#endif
new_cj= enumerate(mu,c,u,s,start_block,end_block,p);

h= (end_block+1<last)?end_block+1:last;


if(delta*c[start_block]> new_cj){
/*75:*/
#line 1475 "./diophant.w"

#if defined(ORIGINAL_SCHNORR_EUCHNER)
/*78:*/
#line 1551 "./diophant.w"

for(l= 1;l<=z;l++)mpz_set_si(b[last+1][l].c,0);
for(i= start_block;i<=end_block;i++)
for(l= 1;l<=z;l++){
mpz_addmul_si(b[last+1][l].c,b[i][l].c,ui);
}
coeffinit(b[last+1],z);
solutiontest(last+1);
swapvl= b[last+1];
for(i= last;i>=start_block;i--)b[i+1]= b[i];
b[start_block]= swapvl;

/*:78*/
#line 1477 "./diophant.w"
;
#else
/*77:*/
#line 1506 "./diophant.w"

for(j= 1;j<=z;j++)mpz_set_si(b[last+1][j].c,0);
for(i= start_block;i<=end_block;i++){
if(u[i]!=0)for(j= 1;j<=z;j++){
if(u[i]> 0){
mpz_addmul_ui(b[last+1][j].c,b[i][j].c,u[i]);
}else{
mpz_submul_ui(b[last+1][j].c,b[i][j].c,-u[i]);
}
}
}
g= end_block;
while(u[g]==0)g--;

i= g-1;
while(labs(u[g])> 1){
while(u[i]==0)i--;
q= (int)ROUND((1.0*u[g])/u[i]);
ui= u[i];
u[i]= u[g]-q*u[i];
u[g]= ui;

for(j= 1;j<=z;j++){
mpz_set(hv,b[g][j].c);
mpz_mul_si(b[g][j].c,b[g][j].c,(long)q);
mpz_add(b[g][j].c,b[g][j].c,b[i][j].c);
mpz_set(b[i][j].c,hv);
}
coeffinit(b[g],z);
coeffinit(b[i],z);
}

swapvl= b[g];
for(i= g;i> start_block;i--)b[i]= b[i-1];
b[start_block]= b[last+1];
coeffinit(b[start_block],z);

b[last+1]= swapvl;
for(j= 1;j<=z;j++)mpz_set_si(b[last+1][j].c,0);
coeffinit(b[last+1],z);

/*:77*/
#line 1479 "./diophant.w"
;
#endif

lllfp(b,mu,c,N,bs,start_block-1,h+1,z,delta);

if(N[h]<-EPSILON){
#ifndef NO_OUTPUT
fprintf(stderr,"NN negativ\n");fflush(stderr);
printf("NN negativ\n");fflush(stdout);
#endif
exit(1);
}
#if defined(ORIGINAL_SCHNORR_EUCHNER)
/*79:*/
#line 1563 "./diophant.w"

if(N[h]<0.5){
swapvl= b[h];
for(i= h+1;i<=last+1;i++)b[i-1]= b[i];
b[last+1]= swapvl;
}else{
#ifndef NO_OUTPUT
printf("Not linear dependent; %f\n",(double)(N[h-1]));fflush(stdout);
#endif
exit(1);
}

/*:79*/
#line 1492 "./diophant.w"
;
#endif

/*:75*/
#line 1430 "./diophant.w"
;
zaehler= -1;
}
else{
if(h> 0){
lllfp(b,mu,c,N,bs,h-2,h+1,z,delta);

}
zaehler++;
}
}

lD= logD(b,c,s-1,z);
#ifndef NO_OUTPUT
printf("bkz: log(D)= %f\n",lD);
fflush(stdout);
#endif
lllfree(mu,c,N,bs,s);
free(u);
mpz_clear(hv);
return lD;
}
/*:73*/
#line 1373 "./diophant.w"
;

/*:72*/
#line 832 "./diophant.w"
;
/*84:*/
#line 1836 "./diophant.w"

/*85:*/
#line 1889 "./diophant.w"

#if 0
static FILE*fp;
#endif

/*:85*//*89:*/
#line 1984 "./diophant.w"

#if defined(FINCKEPOHST)
DOUBLE**muinv;
#endif

long fipo_success;

/*:89*//*95:*/
#line 2067 "./diophant.w"

DOUBLE dum1,dum2;

/*:95*//*99:*/
#line 2208 "./diophant.w"

long only_zeros_no,only_zeros_success,hoelder_no,hoelder_success;
long cs_success;
long N_success;

/*:99*/
#line 1837 "./diophant.w"
;
/*111:*/
#line 2451 "./diophant.w"

DOUBLE compute_y(DOUBLE**mu,DOUBLE*us,int level,int level_max,DOUBLE**sigma,int*r){
int i;
#if 0
DOUBLE dum;

i= level_max;
dum= 0.0;
while(i>=level+1){
dum+= mu[i][level]*us[i];
i--;
}

if(fabs(dum-sigma[level+1][level])> 0.000001){
printf("diff %0.6lf %0.6lf %0.6lf\n",dum,sigma[level+1][level],fabs(dum-sigma[level+1][level]));
fflush(stdout);
}
return dum;
#else
for(i= r[level+1];i> level;i--)sigma[i][level]= sigma[i+1][level]+us[i]*mu[i][level];
return sigma[level+1][level];
#endif
}

void compute_w(DOUBLE**w,DOUBLE**bd,DOUBLE dum,int level,int rows){
#if defined(BLAS)
dcopy(rows,w[level+1],1,w[level],1);
daxpy(rows,dum,bd[level],1,w[level],1);
#else
#if defined(BLAS2)
cblas_dcopy(rows,w[level+1],1,w[level],1);
cblas_daxpy(rows,dum,bd[level],1,w[level],1);
#else
int l;

l= rows-1;
do{
w[level][l]= w[level+1][l]+dum*bd[level][l];
l--;
}while(l>=0);
#endif
#endif
return;
}

/*:111*/
#line 1838 "./diophant.w"
;
/*112:*/
#line 2498 "./diophant.w"

/*113:*/
#line 2503 "./diophant.w"

void gramschmidt(COEFF**lattice,int columns,int rows,DOUBLE**mu,
DOUBLE**bd,DOUBLE*c,DOUBLE*N,DOUBLE Fq){
int i,l,j;
DOUBLE dum;

for(i= 0;i<columns;i++){
for(l= 0;l<rows;l++)bd[i][l]= (DOUBLE)mpz_get_d(get_entry(i,l));
N[i]= 0.0;
for(j= 0;j<i;j++){
dum= 0.0;
for(l= 0;l<rows;l++)dum+= (DOUBLE)mpz_get_d(get_entry(i,l))*bd[j][l];
mu[i][j]= dum/c[j];
for(l= 0;l<rows;l++)bd[i][l]-= mu[i][j]*bd[j][l];
}

c[i]= scalarproductfp(bd[i],bd[i],rows);
for(l= 0;l<rows;l++)N[i]+= fabs(bd[i][l]);
N[i]/= c[i];
N[i]*= Fq;
#ifndef NO_OUTPUT
#if VERBOSE >  0
printf("%lf ",(double)c[i]);
#endif
#endif

}
#ifndef NO_OUTPUT
#if VERBOSE >  0
printf("\n\n");fflush(stdout);
#endif
#endif
return;
}

/*:113*/
#line 2499 "./diophant.w"
;
/*114:*/
#line 2539 "./diophant.w"

void givens(COEFF**lattice,int columns,int rows,DOUBLE**mu,
DOUBLE**bd,DOUBLE*c,DOUBLE*N,DOUBLE Fq){
int i,l,j;
int mm;
DOUBLE d1,d2;
DOUBLE gc,gs;
DOUBLE t;





for(i= 0;i<columns;i++){
for(l= 0;l<rows;l++){
mu[i][l]= (DOUBLE)mpz_get_d(get_entry(i,l));
}
}

for(i= 0;i<rows;i++){
for(l= 0;l<rows;l++)bd[i][l]= 0.0;
bd[i][i]= 1.0;
}

for(j= 1;j<rows;j++){
mm= (j<columns)?j:columns;
for(i= 0;i<mm;i++){
if(mu[i][j]==0.0){

gc= 1.0;
gs= 0.0;
}else{



if(fabs(mu[i][j])>=fabs(mu[i][i])){
t= mu[i][i]/mu[i][j];
gs= 1.0/SQRT(1.0+t*t);
gc= gs*t;
}else{
t= mu[i][j]/mu[i][i];
gc= 1.0/SQRT(1.0+t*t);
gs= gc*t;
}

for(l= i;l<columns;l++){
d1= mu[l][i];
d2= mu[l][j];
mu[l][i]= gc*d1+gs*d2;
mu[l][j]= -gs*d1+gc*d2;
}

for(l= 0;l<rows;l++){
d1= bd[i][l];
d2= bd[j][l];
bd[i][l]= gc*d1+gs*d2;
bd[j][l]= -gs*d1+gc*d2;
}
}
}
}


for(i= 0;i<columns;i++){
c[i]= mu[i][i]*mu[i][i];
N[i]= 0.0;
for(j= 0;j<rows;j++){
bd[i][j]*= mu[i][i];
N[i]+= fabs(bd[i][j]);
}
N[i]/= c[i];
N[i]*= Fq;



for(j= columns-1;j>=i;j--)mu[j][i]/= mu[i][i];
#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("%6.3f ",(double)c[i]);
if(i> 0&&i%15==0)printf("\n");
#endif
#endif
}
#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("\n\n");fflush(stdout);
#endif
#endif
return;
}
/*:114*/
#line 2500 "./diophant.w"
;

/*:112*/
#line 1839 "./diophant.w"
;
/*115:*/
#line 2630 "./diophant.w"

#if defined(FINCKEPOHST)
void inverse(DOUBLE**mu,DOUBLE**muinv,int columns){
int i,j,k;
DOUBLE sum;
for(j= 0;j<columns;j++)
for(i= j;i>=0;i--){
sum= 0.0;
for(k= i+1;k<columns;k++)sum+= mu[k][i]*muinv[k][j];
if(i==j)
muinv[i][j]= 1.0-sum;
else
muinv[i][j]= -sum;
}
return;
}
#endif

/*:115*/
#line 1840 "./diophant.w"
;
/*116:*/
#line 2649 "./diophant.w"

/*117:*/
#line 2657 "./diophant.w"

int exacttest(DOUBLE*v,int rows,DOUBLE Fq){
int i;
i= rows-1;
do{
if(fabs(v[i])> Fq*(1.0+EPSILON)){
return 0;
}
i--;
}while(i>=0);
return 1;
}

/*:117*/
#line 2650 "./diophant.w"
;
/*118:*/
#line 2671 "./diophant.w"

int prune0(DOUBLE li,DOUBLE re){
if(li> re*(1+EPSILON)){
N_success++;
return 1;
}else{
return 0;
}
}

/*:118*/
#line 2651 "./diophant.w"
;
/*119:*/
#line 2682 "./diophant.w"

int prune(DOUBLE*w,DOUBLE cs,int rows,DOUBLE Fq){
DOUBLE reseite;
#if !defined(BLAS)
int i;
#endif
hoelder_no++;
reseite= (-cs/(1.0+EPSILON))/Fq;

#if defined(BLAS)
reseite+= dasum(rows,w,1);
#else
#if defined(BLAS2)
reseite+= cblas_dasum(rows,w,1);
#else
i= rows-1;
do{
reseite+= fabs(w[i]);
i--;
}while(i>=0);
#endif
#endif
if(0.0<reseite)return 0;

hoelder_success++;
return 1;
}

/*:119*/
#line 2652 "./diophant.w"
;
/*120:*/
#line 2712 "./diophant.w"

int prune_only_zeros(DOUBLE*w,int level,int rows,DOUBLE Fq,
int*first_nonzero_in_column,int*firstp){
int i;
int f;

only_zeros_no++;

if(iszeroone){
for(i= 0;i<first_nonzero_in_column[firstp[level]];i++){
f= first_nonzero_in_column[firstp[level]+1+i];
if(fabs(fabs(w[f])-Fq)> 0.5){
only_zeros_success++;
return 1;
}
}
}else{
for(i= 0;i<first_nonzero_in_column[firstp[level]];i++){
f= first_nonzero_in_column[firstp[level]+1+i];
if(fabs(w[f])> Fq*(1+EPSILON)){
only_zeros_success++;
return 1;
}
}
}
return 0;
}
/*:120*/
#line 2653 "./diophant.w"
;
/*121:*/
#line 2743 "./diophant.w"

int print_solution(DOUBLE*w,int rows,DOUBLE Fq,DOUBLE*us,int columns){
int i,j,k;
int upper;
int end;

#if 0
if(fabs(fabs(w[rows-1])-Fq)> 0.5*Fq*EPSILON){
#else
if(fabs(w[rows-1])> Fq*(1+EPSILON)){
#endif
return 0;
}
upper= rows-1-free_RHS;
#if 0
if(free_RHS&&fabs(fabs(w[upper])-Fq)> 0.5*Fq*EPSILON){
#else
if(free_RHS&&fabs(w[upper])> Fq*(1+EPSILON)){
#endif
return 0;
}

if(!SILENT){
mpz_set_si(soltest_upfac,1);
#if 0
mpz_set_d(soltest_s,ROUND(w[rows-1]));
#else
mpz_set_si(soltest_s,0);
for(k= 0;k<columns;k++){
if(ROUND(us[k])> 0){
mpz_addmul_ui(soltest_s,get_entry(k,rows-1),ROUND(us[k]));
}else{
mpz_submul_ui(soltest_s,get_entry(k,rows-1),-ROUND(us[k]));
}
}
#endif

i= 0;
if(cut_after_coeff==-1){
end= no_original_columns;
#if 0
if(nboundvars!=0){
end= nboundvars;
}
#endif
}else{
end= cut_after_coeff;
}
for(j= 0;j<end;j++){
if(original_columns[j]==0){
mpz_set_si(soltest_u,0);
}else{
if(!iszeroone){
if(mpz_cmp_si(upperbounds[i],0)!=0){
mpz_divexact(soltest_upfac,upperbounds_max,upperbounds[i]);
}else{
mpz_set(soltest_upfac,upperbounds_max);
}
}
mpz_set_si(soltest_u,0);
for(k= 0;k<columns;k++){
if(ROUND(us[k])> 0){
mpz_addmul_ui(soltest_u,get_entry(k,i),ROUND(us[k]));
}else{
mpz_submul_ui(soltest_u,get_entry(k,i),-ROUND(us[k]));
}
}
mpz_sub(soltest_u,soltest_u,soltest_s);
mpz_divexact(soltest_u,soltest_u,max_norm_initial);
mpz_divexact(soltest_u,soltest_u,soltest_upfac);
mpz_divexact_ui(soltest_u,soltest_u,denom);
mpz_abs(soltest_u,soltest_u);
if(!iszeroone&&(mpz_cmp_si(soltest_u,0)<0||mpz_cmp(soltest_u,upperbounds[i])> 0)){
fprintf(stderr," rounding error -> this is not a solutions!\n");
return 0;
}
i++;
}
mpz_out_str(NULL,10,soltest_u);
fflush(stdout);
mpz_out_str(fp,10,soltest_u);
if(!iszeroone){
printf(" ");
fprintf(fp," ");
}
}
if(free_RHS){
mpz_set_d(soltest_u,ROUND(w[i]));
mpz_divexact(soltest_u,soltest_u,max_up);
mpz_abs(soltest_u,soltest_u);
printf(" L = ");
mpz_out_str(NULL,10,soltest_u);
}
printf("\n");fflush(stdout);
fprintf(fp,"\n");fflush(fp);
}

nosolutions++;
#ifndef NO_OUTPUT
if(nosolutions%10000==0){
printf("%ld\n",nosolutions);fflush(stdout);
}
#endif

return 1;
}

/*:121*/
#line 2654 "./diophant.w"
;

/*:116*/
#line 1841 "./diophant.w"
;
/*122:*/
#line 2852 "./diophant.w"

void basis2poly(){
return;
}

/*:122*/
#line 1842 "./diophant.w"
;
/*123:*/
#line 2859 "./diophant.w"

void basis2LP(double*low,double*up){
return;
}

/*:123*/
#line 1843 "./diophant.w"
;

DOUBLE explicit_enumeration(COEFF**lattice,int columns,int rows)
{
/*86:*/
#line 1894 "./diophant.w"

int level,level_max;
int i,j,l;
long loops;

DOUBLE*y,*cs,*us;

long*delta,*d,*eta;
#if 0
mpz_t*v;
#else
long*v;
#endif
int*first_nonzero,*first_nonzero_in_column,*firstp;

DOUBLE*N,**mu,*c,**w,**bd;

DOUBLE Fd,Fq;
DOUBLE dum;
COEFF*swap_vec;

DOUBLE**sigma;
int*r;

#if defined(FINCKEPOHST)
DOUBLE*fipo,*fipo_u,*fipo_l;
#endif

/*:86*/
#line 1847 "./diophant.w"
;

long nlow[1000];
for(i= 0;i<1000;i++)nlow[i]= 0;


/*87:*/
#line 1923 "./diophant.w"

#ifndef NO_OUTPUT
printf("Dimension of solution space (k): %d compared to s-z+2: %d\n",
columns,system_columns-system_rows+1+free_RHS);
fflush(stdout);
#endif

if(columns<system_columns-system_rows+1+free_RHS){
#ifndef NO_OUTPUT
fprintf(stderr,"LLL didn't succeed in computing a basis of the kernel.\n");
fprintf(stderr,"Please increase c0 (the first parameter)!\n");
printf("LLL didn't succeed in computing a basis of the kernel.\n");
printf("Please increase c0 (the first parameter)!\n");
#endif
return 0;
}


/*:87*/
#line 1853 "./diophant.w"
;
/*88:*/
#line 1943 "./diophant.w"

lllalloc(&mu,&c,&N,&bd,columns,rows);

us= (DOUBLE*)calloc(columns+1,sizeof(DOUBLE));
cs= (DOUBLE*)calloc(columns+1,sizeof(DOUBLE));
y= (DOUBLE*)calloc(columns+1,sizeof(DOUBLE));
delta= (long*)calloc(columns+1,sizeof(long));
d= (long*)calloc(columns+1,sizeof(long));
first_nonzero= (int*)calloc(rows,sizeof(int));
first_nonzero_in_column= (int*)calloc(columns+rows+1,sizeof(int));
if(first_nonzero_in_column==NULL)return(0);
firstp= (int*)calloc(columns+1,sizeof(int));

eta= (long*)calloc(columns+1,sizeof(long));
v= (long*)calloc(columns+1,sizeof(long));
w= (DOUBLE**)calloc(columns+1,sizeof(DOUBLE*));
for(i= 0;i<=columns;i++)w[i]= (DOUBLE*)calloc(rows,sizeof(DOUBLE));

sigma= (DOUBLE**)calloc(columns+1,sizeof(DOUBLE*));
r= (int*)calloc(columns+1+1,sizeof(int));
for(i= 0;i<columns+1;i++){
sigma[i]= (DOUBLE*)calloc(columns+1,sizeof(DOUBLE));
r[i]= i-1;
}

#if defined(FINCKEPOHST)
fipo= (DOUBLE*)calloc(columns+1,sizeof(DOUBLE));
fipo_u= (DOUBLE*)calloc(columns+1,sizeof(DOUBLE));
fipo_l= (DOUBLE*)calloc(columns+1,sizeof(DOUBLE));
muinv= (DOUBLE**)calloc(columns,sizeof(DOUBLE*));
for(i= 0;i<columns;++i)muinv[i]= (DOUBLE*)calloc(rows,sizeof(DOUBLE));
#endif
#if 0
upb= (mpz_t*)calloc(columns+1,sizeof(mpz_t));
lowb= (mpz_t*)calloc(columns+1,sizeof(mpz_t));
for(i= 0;i<=columns;i++){
mpz_init(upb[i];
mpz_init(lowb[i];
}
#endif

/*:88*/
#line 1854 "./diophant.w"
;
/*90:*/
#line 1992 "./diophant.w"

for(i= 0;i<=columns;i++){
cs[i]= y[i]= us[i]= 0.0;
delta[i]= 0;
#if 0
mpz_set_si(v[i],0);
#else
v[i]= 0;
#endif
eta[i]= d[i]= 1;
for(l= 0;l<rows;l++)w[i][l]= 0.0;
}

/*:90*/
#line 1855 "./diophant.w"
;
/*93:*/
#line 2035 "./diophant.w"

if(free_RHS){
i= 0;
for(j= columns-1;j>=0;j--)if(mpz_sgn(get_entry(j,rows-2))!=0)i++;
#ifndef NO_OUTPUT
printf("Number of nonzero entries in the second last row: %d\n",i);
fflush(stdout);
#endif
}

i= 0;
for(j= columns-1;j>=0;j--)if(mpz_sgn(get_entry(j,rows-1))!=0)i++;
#ifndef NO_OUTPUT
printf("Number of nonzero entries in the last row: %d\n",i);
fflush(stdout);
#endif

/*:93*/
#line 1856 "./diophant.w"
;
#if 1
/*91:*/
#line 2008 "./diophant.w"

for(j= columns-1;j> 0;j--){
for(l= j-1;l>=0;l--){
if(mpz_cmpabs(get_entry(l,rows-1),get_entry(j,rows-1))> 0){
swap_vec= lattice[l];
for(i= l+1;i<=j;i++)lattice[i-1]= lattice[i];
lattice[j]= swap_vec;
}
}
}

/*:91*/
#line 1858 "./diophant.w"
;
#endif
/*94:*/
#line 2057 "./diophant.w"

Fq= (DOUBLE)mpz_get_d(max_norm);
Fd= (rows*Fq*Fq)*(1.0+EPSILON);
#ifndef NO_OUTPUT
#if VERBOSE >  0
printf("Fq: %f\n",(double)Fq);
printf("Fd: %f\n",(double)Fd);
#endif
#endif

/*:94*/
#line 1860 "./diophant.w"
;
/*96:*/
#line 2070 "./diophant.w"

#if GIVENS
givens(lattice,columns,rows,mu,bd,c,N,Fq);
#else
gramschmidt(lattice,columns,rows,mu,bd,c,N,Fq);
#endif

/*:96*/
#line 1861 "./diophant.w"
;
#if 0
print_lattice();
basis2poly();
#endif

#if defined(FINCKEPOHST)
/*97:*/
#line 2103 "./diophant.w"

fipo_success= 0;
inverse(mu,muinv,columns);

#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("\nFincke-Pohst bounds:\n");fflush(stdout);
#endif
#endif

for(i= 0;i<columns;i++){
#if 0   
fipo[i]= 0.0;
dum1= 0.0;
for(j= 0;j<rows;j++){
dum= 0.0;
for(l= i;l<columns;l++)dum+= muinv[i][l]*bd[l][j]/c[l];
fipo[i]+= dum*dum;
dum1+= fabs(dum);
}
fipo[i]= SQRT(fipo[i]*Fd);

dum1= fabs(dum1*Fq);
if(dum1<fipo[i])fipo[i]= dum1;



#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("%f ",fipo[i]);
#endif
#endif
#else

fipo[i]= 0.0;
fipo_u[i]= 0.0;
fipo_l[i]= 0.0;
dum1= 0.0;
for(j= 0;j<rows;j++){
for(l= i,dum= 0.0;l<columns;l++)dum+= muinv[i][l]*bd[l][j]/c[l];
dum2= muinv[columns-1][columns-1]*bd[columns-1][j]/c[columns-1];
fipo[i]+= dum*dum;
dum1+= fabs(dum);

fipo_u[i]+= fabs(dum+dum2);
fipo_l[i]-= fabs(dum-dum2);
}
fipo[i]= SQRT(fipo[i]*Fd);
dum1= fabs(dum1*Fq);
if(dum1<fipo[i])fipo[i]= dum1;

fipo_u[i]*= Fq;
fipo_l[i]*= Fq;
#if 0
fipo_u[i]-= 1.0;
fipo_l[i]+= 1.0;
if(fipo[i]<fipo_u[i])fipo_u[i]= fipo[i];
if(-fipo[i]> fipo_l[i])fipo_l[i]= -fipo[i];
#endif
fipo_u[i]*= (fipo_u[i]> 0)?(1.0+EPSILON):(1.0-EPSILON);
fipo_l[i]*= (fipo_l[i]> 0)?(1.0-EPSILON):(1.0+EPSILON);
#if 1  
fipo_u[i]= floor(fipo_u[i]);
fipo_l[i]= ceil(fipo_l[i]);
#endif
#ifndef NO_OUTPUT
printf("%03d: %0.3lf\t%0.3lf\n",i,fipo_l[i],fipo_u[i]);
#endif
#endif
}
#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("\n");fflush(stdout);
printf("\n");fflush(stdout);
#endif
#endif

/*:97*/
#line 1868 "./diophant.w"
;
#if FINCKEPOHSTEXTREME
/*92:*/
#line 2020 "./diophant.w"

for(j= columns-3;j> 0;j--){
for(l= j-1;l>=0;l--){
#if 0
if(fipo[l]<fipo[j]){
#else
if(fipo_u[l]-fipo_l[l]<fipo_u[j]-fipo_l[j]){
#endif
swap_vec= lattice[l];
for(i= l+1;i<=j;i++)lattice[i-1]= lattice[i];
lattice[j]= swap_vec;
}
}
}

/*:92*/
#line 1870 "./diophant.w"
;
/*96:*/
#line 2070 "./diophant.w"

#if GIVENS
givens(lattice,columns,rows,mu,bd,c,N,Fq);
#else
gramschmidt(lattice,columns,rows,mu,bd,c,N,Fq);
#endif

/*:96*/
#line 1871 "./diophant.w"
;
/*97:*/
#line 2103 "./diophant.w"

fipo_success= 0;
inverse(mu,muinv,columns);

#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("\nFincke-Pohst bounds:\n");fflush(stdout);
#endif
#endif

for(i= 0;i<columns;i++){
#if 0   
fipo[i]= 0.0;
dum1= 0.0;
for(j= 0;j<rows;j++){
dum= 0.0;
for(l= i;l<columns;l++)dum+= muinv[i][l]*bd[l][j]/c[l];
fipo[i]+= dum*dum;
dum1+= fabs(dum);
}
fipo[i]= SQRT(fipo[i]*Fd);

dum1= fabs(dum1*Fq);
if(dum1<fipo[i])fipo[i]= dum1;



#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("%f ",fipo[i]);
#endif
#endif
#else

fipo[i]= 0.0;
fipo_u[i]= 0.0;
fipo_l[i]= 0.0;
dum1= 0.0;
for(j= 0;j<rows;j++){
for(l= i,dum= 0.0;l<columns;l++)dum+= muinv[i][l]*bd[l][j]/c[l];
dum2= muinv[columns-1][columns-1]*bd[columns-1][j]/c[columns-1];
fipo[i]+= dum*dum;
dum1+= fabs(dum);

fipo_u[i]+= fabs(dum+dum2);
fipo_l[i]-= fabs(dum-dum2);
}
fipo[i]= SQRT(fipo[i]*Fd);
dum1= fabs(dum1*Fq);
if(dum1<fipo[i])fipo[i]= dum1;

fipo_u[i]*= Fq;
fipo_l[i]*= Fq;
#if 0
fipo_u[i]-= 1.0;
fipo_l[i]+= 1.0;
if(fipo[i]<fipo_u[i])fipo_u[i]= fipo[i];
if(-fipo[i]> fipo_l[i])fipo_l[i]= -fipo[i];
#endif
fipo_u[i]*= (fipo_u[i]> 0)?(1.0+EPSILON):(1.0-EPSILON);
fipo_l[i]*= (fipo_l[i]> 0)?(1.0-EPSILON):(1.0+EPSILON);
#if 1  
fipo_u[i]= floor(fipo_u[i]);
fipo_l[i]= ceil(fipo_l[i]);
#endif
#ifndef NO_OUTPUT
printf("%03d: %0.3lf\t%0.3lf\n",i,fipo_l[i],fipo_u[i]);
#endif
#endif
}
#ifndef NO_OUTPUT
#if VERBOSE >  -1
printf("\n");fflush(stdout);
printf("\n");fflush(stdout);
#endif
#endif

/*:97*/
#line 1872 "./diophant.w"
;
#endif
#endif

#if 0
basis2LP(fipo_l,fipo_u);
#endif

/*98:*/
#line 2184 "./diophant.w"

for(l= 0;l<rows;l++){
for(i= 0;i<columns;i++)if(mpz_sgn(get_entry(i,l))!=0){
first_nonzero[l]= i;
break;
}
}
j= 0;
for(l= 0;l<columns;l++){
firstp[l]= j;
first_nonzero_in_column[j]= 0;
j++;
for(i= 0;i<rows;i++){
if(first_nonzero[i]==l){
first_nonzero_in_column[j]= i;
first_nonzero_in_column[firstp[l]]++;
j++;
}
}
}
firstp[columns]= j;
first_nonzero_in_column[j]= 0;


/*:98*/
#line 1880 "./diophant.w"
;
/*100:*/
#line 2213 "./diophant.w"


level= 0;
if(level<0)level= 0;
level_max= level;
us[level]= 1;
#if 0
mpz_set_si(v[level],1);
#else
v[level]= 1;
#endif
only_zeros_no= only_zeros_success= 0;
hoelder_no= hoelder_success= 0;
cs_success= nosolutions= loops= 0;
N_success= 0;

/*:100*/
#line 1881 "./diophant.w"
;
/*102:*/
#line 2263 "./diophant.w"

do{
/*101:*/
#line 2231 "./diophant.w"

loops++;
if((stop_after_loops> 0)&&(stop_after_loops<=loops))goto afterloop;

#ifndef NO_OUTPUT
#if VERBOSE >  -1
if(loops%100000000==0){
#if defined(FINCKEPOHST)
printf("%ld loops, solutions: %ld, fipo: %ld\n",\
loops,nosolutions,fipo_success);







#if 0

for(i= 0;i<level_max;i++){
printf("%03d: %ld\n",i,nlow[i]);
}
#endif
#else
printf("%ld loops, solutions: %ld\n",loops,nosolutions);
#endif
fflush(stdout);
}
#endif
#endif

/*:101*/
#line 2265 "./diophant.w"
;
/*103:*/
#line 2319 "./diophant.w"

dum= us[level]+y[level];
cs[level]= cs[level+1]+dum*dum*c[level];
/*:103*/
#line 2266 "./diophant.w"
;
if((cs[level]<Fd)&&(!prune0(fabs(dum),N[level]))){
#if defined(FINCKEPOHST)
#if 0
if(fabs(us[level])> fipo[level]*(1.0+EPSILON)){
#else
if(level!=columns-1&&
(us[level]> fipo_u[level]||us[level]<fipo_l[level])
){
#endif
fipo_success++;
goto side_step;
}

#endif
compute_w(w,bd,dum,level,rows);

if(level> 0){
/*104:*/
#line 2325 "./diophant.w"

if(prune_only_zeros(w[level],level,rows,Fq,first_nonzero_in_column,firstp))
goto side_step;

if(prune(w[level],cs[level],rows,Fq)){
if(eta[level]==1){
goto step_back;
}
eta[level]= 1;
delta[level]*= -1;
if(delta[level]*d[level]>=0)delta[level]+= d[level];
#if 0
us[level]= mpz_get_d(v[level])+delta[level];
#else
us[level]= v[level]+delta[level];
#endif
}else{
level--;
eta[level]= 0;
delta[level]= 0;
if(r[level+1]> r[level])r[level]= r[level+1];

dum= compute_y(mu,us,level,level_max,sigma,r);
y[level]= dum;
#if 0
mpz_set_d(v[level],ROUND(-dum));
us[level]= mpz_get_si(v[level]);
#else
v[level]= ROUND(-dum);
us[level]= v[level];
#endif
d[level]= (ROUND(-dum)> -y[level])?-1:1;
}

/*:104*/
#line 2284 "./diophant.w"
;
}else{
/*105:*/
#line 2360 "./diophant.w"

if(exacttest(w[0],rows,Fq)==1){
print_solution(w[level],rows,Fq,us,columns);
#if 0
printf("us: ");
for(i= columns-1;i>=0;i--){
printf("%d ",(int)us[i]);
}
printf("after %ld loops\n",loops);
#endif
if((stop_after_solutions> 0)&&(stop_after_solutions<=nosolutions))
goto afterloop;
}
goto side_step;

/*:105*/
#line 2286 "./diophant.w"
;
}
}else{
cs_success++;
step_back:

nlow[level]++;
level++;
r[level]= level;

if(level_max<level)level_max= level;
side_step:




if(eta[level]==0){
delta[level]*= -1;
if(delta[level]*d[level]>=0)delta[level]+= d[level];
}else{
delta[level]+= (delta[level]*d[level]>=0)?d[level]:-d[level];
}
#if 0
us[level]= mpz_get_d(v[level])+delta[level];
#else
us[level]= v[level]+delta[level];
#endif
}
}while(level<columns);
afterloop:

/*:102*/
#line 1882 "./diophant.w"
;

/*106:*/
#line 2376 "./diophant.w"

#ifndef NO_OUTPUT
printf("Prune_cs: %ld\n",cs_success);
printf("Prune_only_zeros: %ld of %ld\n",only_zeros_success,only_zeros_no);
printf("Prune_hoelder: %ld of %ld\n",hoelder_success,hoelder_no);
printf("Prune_N: %ld\n",N_success);
#if defined(FINCKEPOHST)
printf("Fincke-Pohst: %ld\n",fipo_success);
#endif
printf("Loops: %ld\n",loops);
#endif
if((stop_after_solutions<=nosolutions&&stop_after_solutions> 0)||
(stop_after_loops<=loops&&stop_after_loops> 0)){
#ifndef NO_OUTPUT
printf("Stopped after number of solutions: %ld\n",nosolutions);
#endif
if((stop_after_loops<=loops&&stop_after_loops> 0)){
/*109:*/
#line 2444 "./diophant.w"

if(SILENT)fprintf(fp,"%ld solutions\n",nosolutions);
fflush(fp);

/*:109*/
#line 2393 "./diophant.w"
;
exit(0);
}

}else{
#ifndef NO_OUTPUT
printf("Total number of solutions: %ld\n",nosolutions);
#endif
}
#ifndef NO_OUTPUT
printf("\n");fflush(stdout);
#endif

/*:106*/
#line 1884 "./diophant.w"
;
/*107:*/
#line 2406 "./diophant.w"

free(us);
free(cs);
free(y);
free(delta);
free(d);
free(first_nonzero);
free(first_nonzero_in_column);
free(firstp);
free(eta);
free(v);
for(l= 0;l<=columns;l++)free(w[l]);
free(w);
free(original_columns);
for(i= 0;i<columns+1;i++){
free(sigma[i]);
}
free(sigma);
free(r);

#if defined(FINCKEPOHST)
free(fipo);
free(fipo_u);
free(fipo_l);
for(l= 0;l<columns;l++)free(muinv[l]);
free(muinv);
#endif
#if 0
free(upb);
free(lowb);
#endif
lllfree(mu,c,N,bd,columns);

/*:107*/
#line 1885 "./diophant.w"
;
return 1;
}

/*:84*/
#line 833 "./diophant.w"
;

/*:45*/
#line 49 "./diophant.w"
;

/*:2*//*3:*/
#line 52 "./diophant.w"

long diophant(mpz_t**a_input,mpz_t*b_input,mpz_t*upperbounds_input,
int no_columns,int no_rows,
mpz_t factor_input,mpz_t norm_input,
int silent,int iterate,int iterate_no,
int bkz_beta_input,int bkz_p_input,
long stop_after_sol_input,long stop_after_loops_input,
int free_RHS_input,int*org_col_input,int no_org_col_input,
int cut_after,int nboundedvars,FILE*solfile)
{
int i,j;
DOUBLE lD,lDnew;
COEFF*swap_vec;

/*11:*/
#line 223 "./diophant.w"

mpz_init_set(matrix_factor,factor_input);
mpz_init_set(max_norm,norm_input);
mpz_init(lastlines_factor);
mpz_init(upfac);

if(iterate){
no_iterates= iterate_no;
}else{
bkz_beta= bkz_beta_input;
bkz_p= bkz_p_input;
}
SILENT= silent;
stop_after_solutions= stop_after_sol_input;
stop_after_loops= stop_after_loops_input;
free_RHS= free_RHS_input;
nom= 1;
denom= 2;

system_rows= no_rows;
system_columns= no_columns;
nboundvars= nboundedvars;

/*:11*//*40:*/
#line 727 "./diophant.w"

mpz_init(soltest_u);
mpz_init(soltest_s);
mpz_init_set_ui(soltest_upfac,1);

/*:40*/
#line 66 "./diophant.w"
;
/*13:*/
#line 272 "./diophant.w"

lattice_rows= system_rows+system_columns+1;
lattice_columns= system_columns+2;

if(free_RHS){
lattice_rows++;
lattice_columns++;
}else{
#ifndef NO_OUTPUT
fprintf(stderr,"The RHS is fixed !\n");fflush(stderr);
#endif
}
cut_after_coeff= cut_after;

/*:13*/
#line 67 "./diophant.w"
;
/*14:*/
#line 287 "./diophant.w"

lattice= (COEFF**)calloc(lattice_columns,sizeof(COEFF*));
for(j= 0;j<lattice_columns;j++){
lattice[j]= (COEFF*)calloc(lattice_rows+1,sizeof(COEFF));
for(i= 0;i<=lattice_rows;i++)mpz_init(lattice[j][i].c);
}
/*:14*/
#line 68 "./diophant.w"
;
/*15:*/
#line 295 "./diophant.w"

for(j= 0;j<system_rows;j++){
for(i= 0;i<system_columns;i++){
mpz_mul(lattice[i][j+1].c,a_input[j][i],matrix_factor);
}
mpz_mul(lattice[system_columns][j+1].c,b_input[j],matrix_factor);
}
/*:15*/
#line 69 "./diophant.w"
;
/*16:*/
#line 315 "./diophant.w"

mpz_init_set_si(upperbounds_max,1);
iszeroone= 1;
if(upperbounds_input==NULL){
#ifndef NO_OUTPUT
printf("No upper bounds: 0/1 variables are assumed \n");fflush(stdout);
#endif
}else{
upperbounds= (mpz_t*)calloc(system_columns,sizeof(mpz_t));
for(i= 0;i<system_columns;i++)mpz_init_set_si(upperbounds[i],1);
for(i= 0;i<nboundvars;i++){
mpz_set(upperbounds[i],upperbounds_input[i]);
if(mpz_sgn(upperbounds[i])!=0){
mpz_lcm(upperbounds_max,upperbounds_max,upperbounds[i]);
}
}
if(mpz_cmp_si(upperbounds_max,1)> 0)iszeroone= 0;
#ifndef NO_OUTPUT
fprintf(stderr,"upper bounds found. Max=");
mpz_out_str(stderr,10,upperbounds_max);
fprintf(stderr,"\n");
fflush(stderr);
#endif
}
/*:16*/
#line 70 "./diophant.w"
;
/*17:*/
#line 343 "./diophant.w"

if(org_col_input!=NULL)no_original_columns= no_org_col_input;
else no_original_columns= system_columns;

original_columns= (int*)calloc(no_original_columns,sizeof(int));

if(org_col_input!=NULL)
for(i= 0;i<no_original_columns;i++)original_columns[i]= org_col_input[i];
else{
for(i= 0;i<no_original_columns;i++)original_columns[i]= 1;
#ifndef NO_OUTPUT
printf("No preselected columns \n");fflush(stdout);
#endif
}

/*:17*/
#line 71 "./diophant.w"
;
/*18:*/
#line 366 "./diophant.w"

for(j= system_rows;j<lattice_rows;j++){
mpz_mul_si(lattice[j-system_rows][j+1].c,max_norm,denom);
mpz_mul_si(lattice[lattice_columns-2][j+1].c,max_norm,nom);
}
mpz_set(lattice[system_columns+free_RHS][lattice_rows].c,max_norm);

if(free_RHS){
mpz_set_si(lattice[system_columns][lattice_rows-1].c,1);
mpz_set_si(lattice[system_columns+1][lattice_rows-1].c,0);
}
mpz_set(lattice[system_columns+free_RHS][lattice_rows].c,max_norm);
for(i= 0;i<lattice_columns-1;i++)coeffinit(lattice[i],lattice_rows);

/*:18*/
#line 72 "./diophant.w"
;
/*108:*/
#line 2439 "./diophant.w"

fp= solfile;
if(SILENT)fprintf(fp,"SILENT\n");
fflush(fp);

/*:108*/
#line 73 "./diophant.w"
;
#if 0
printf("Before scaling\n");
print_lattice();
#endif
/*19:*/
#line 388 "./diophant.w"

mpz_init_set(max_norm_initial,max_norm);
mpz_init_set_si(max_up,1);
if(!iszeroone){
for(j= 0;j<nboundvars;j++){
if(mpz_sgn(upperbounds[j])!=0){
mpz_divexact(upfac,upperbounds_max,upperbounds[j]);
}else{
mpz_mul(upfac,upperbounds_max,upperbounds_max);
mpz_mul_si(upfac,upfac,10000);
}
smult_lattice(j,j+system_rows,upfac);
smult_lattice(system_columns+free_RHS,j+system_rows,upperbounds_max);
}
mpz_set(max_up,upperbounds_max);
mpz_mul(max_norm,max_norm,max_up);
if(free_RHS)
smult_lattice(system_columns,lattice_rows-2,max_up);

smult_lattice(system_columns+free_RHS,lattice_rows-1,max_up);
}

/*:19*/
#line 78 "./diophant.w"
;
#if 0
printf("After scaling\n");
print_lattice();
#endif

#if 0
print_NTL_lattice();
return 0;
#endif

/*20:*/
#line 413 "./diophant.w"

swap_vec= lattice[lattice_columns-2];
for(i= lattice_columns-2;i> 0;i--)lattice[i]= lattice[i-1];
lattice[0]= swap_vec;

/*:20*/
#line 89 "./diophant.w"
;
#if 0
printf("After permute\n");
print_lattice();
#endif
shufflelattice();
/*21:*/
#line 420 "./diophant.w"

mpz_set_ui(lastlines_factor,1);
#ifndef NO_OUTPUT
printf("\n");fflush(stdout);
#endif
lll(lattice,lattice_columns-1,lattice_rows,LLLCONST_LOW);

/*:21*/
#line 95 "./diophant.w"
;
#if 0
printf("After first reduction\n");
print_lattice();
#endif
/*23:*/
#line 444 "./diophant.w"

if(cutlattice()){
#ifndef NO_OUTPUT
printf("First reduction successful\n");fflush(stdout);
#endif
}else{
#ifndef NO_OUTPUT
printf("First reduction not successful\n");fflush(stdout);
#endif
return 0;
}

for(j= 0;j<lattice_columns-1;j++)solutiontest(j);
/*:23*/
#line 100 "./diophant.w"
;
#if 0
printf("After cutting\n");
print_lattice();
#endif
#if 1
shufflelattice();
/*22:*/
#line 429 "./diophant.w"

mpz_set_ui(lastlines_factor,1);
lll(lattice,lattice_columns-1,lattice_rows,LLLCONST_HIGH);
#ifndef NO_OUTPUT
printf("Second reduction successful\n");fflush(stdout);
#endif

/*:22*/
#line 107 "./diophant.w"
;
#endif
#if 0
printf("After second reduction\n");
print_lattice();
#endif

/*24:*/
#line 465 "./diophant.w"

mpz_set_str(lastlines_factor,LASTLINESFACTOR,10);
for(i= 0;i<lattice_columns;i++)
mpz_mul(lattice[i][lattice_rows].c,lattice[i][lattice_rows].c,lastlines_factor);
if(free_RHS)
for(i= 0;i<lattice_columns;i++)
mpz_mul(lattice[i][lattice_rows-1].c,lattice[i][lattice_rows-1].c,lastlines_factor);

/*:24*/
#line 114 "./diophant.w"
;
/*26:*/
#line 485 "./diophant.w"

#ifndef NO_OUTPUT
printf("\n");fflush(stdout);
#endif
if(iterate){
iteratedlll(lattice,lattice_columns-1,lattice_rows,no_iterates,LLLCONST_HIGH);
}else{
shufflelattice();
lDnew= bkz(lattice,lattice_columns,lattice_rows,LLLCONST_HIGHER,40,bkz_p);

i= 0;
do{
lD= lDnew;
shufflelattice();
lDnew= bkz(lattice,lattice_columns,lattice_rows,LLLCONST_HIGH,bkz_beta,bkz_p);
printf("%0.3lf %0.3lf %0.3lf\n",lD,lDnew,lD-lDnew);
i++;
}
while(i<1&&fabs(lDnew-lD)> 0.01);
}
#ifndef NO_OUTPUT
printf("Third reduction successful\n");fflush(stdout);
#endif

/*:26*/
#line 115 "./diophant.w"
;
/*25:*/
#line 475 "./diophant.w"

for(i= 0;i<lattice_columns;i++)
mpz_divexact(lattice[i][lattice_rows].c,lattice[i][lattice_rows].c,lastlines_factor);
if(free_RHS)
for(i= 0;i<lattice_columns;i++)
mpz_divexact(lattice[i][lattice_rows-1].c,
lattice[i][lattice_rows-1].c,lastlines_factor);

/*:25*/
#line 116 "./diophant.w"
;

#if 0
printf("Before enumeration\n");
print_NTL_lattice();

#endif

/*27:*/
#line 510 "./diophant.w"

#ifndef NO_OUTPUT
printf("\n");fflush(stdout);
#endif
nosolutions= explicit_enumeration(lattice,lattice_columns-1,lattice_rows);

/*:27*/
#line 124 "./diophant.w"
;
/*109:*/
#line 2444 "./diophant.w"

if(SILENT)fprintf(fp,"%ld solutions\n",nosolutions);
fflush(fp);

/*:109*/
#line 125 "./diophant.w"
;
/*12:*/
#line 246 "./diophant.w"

mpz_clear(matrix_factor);
mpz_clear(max_norm);
mpz_clear(lastlines_factor);
mpz_clear(upfac);
mpz_clear(max_norm_initial);
mpz_clear(max_up);
mpz_clear(soltest_u);
mpz_clear(soltest_s);
mpz_clear(soltest_upfac);
mpz_clear(upperbounds_max);

for(j= 0;j<lattice_columns;j++){
for(i= 0;i<=lattice_rows;i++)mpz_clear(lattice[j][i].c);
}
free(lattice);
if(upperbounds!=NULL){
for(i= 0;i<system_columns;i++)mpz_clear(upperbounds[i]);
free(upperbounds);
}

/*:12*/
#line 126 "./diophant.w"
;
return nosolutions;
}

/*:3*/

/*4:*/
#line 132 "./diophant.w"

#ifndef _DIOPHANT_H
#define _DIOPHANT_H
#include <gmp.h> 
#undef BLAS
extern long diophant(mpz_t**a_input,mpz_t*b_input,mpz_t*upperbounds_input,
int no_columns,int no_rows,
mpz_t factor_input,mpz_t norm_input,
int silent,int iterate,int iterate_no,
int bkz_beta_input,int bkz_p_input,
long stop_after_sol_input,long stop_after_loops_input,
int free_RHS_input,int*org_col_input,int no_org_col_input,
int cut_after,int nboundedvars,FILE*solfile);
#endif

/*:4*/

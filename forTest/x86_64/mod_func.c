#include <stdio.h>
#include "hocdec.h"
extern int nrnmpi_myid;
extern int nrn_nobanner_;

extern void _gamma_reg(void);
extern void _gaussian_reg(void);
extern void _poisson_reg(void);

void modl_reg(){
  if (!nrn_nobanner_) if (nrnmpi_myid < 1) {
    fprintf(stderr, "Additional mechanisms from files\n");

    fprintf(stderr," mod/gamma.mod");
    fprintf(stderr," mod/gaussian.mod");
    fprintf(stderr," mod/poisson.mod");
    fprintf(stderr, "\n");
  }
  _gamma_reg();
  _gaussian_reg();
  _poisson_reg();
}

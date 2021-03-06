#include <Rcpp.h>
using namespace Rcpp;

//' @name temporal_beta_core
//'
//' @title Compute the beta diversity two set of sites
//'
//' @description
//' Compute the beta diversity between all sites for a specific presence-absence
//' matrix.
//'
//' @param mat_pa1 presence absence matrix (sites as rows and species as columns) for time 1.
//' @param mat_pa2 presence absence matrix for time 2.
//'
//' @return
//' A dataframe with all the combinaison of sites and the counts associated.
//'
// [[Rcpp::export]]

DataFrame temporal_beta_core(LogicalMatrix mat_pa1, LogicalMatrix mat_pa2) {

    int i, j, sz;
    sz = mat_pa1.nrow(); //number of sites
    IntegerVector site(sz), a(sz), b(sz), c(sz), d(sz);

    for (i=0; i<sz; i++) {
        site(i) = i+1;
        for (j=0; j<mat_pa1.ncol(); j++) {
            if (mat_pa1(i,j)) {
                if (mat_pa2(i,j)) {
                    a(i)++;
                } else {
                    b(i)++;
                }
            } else{
                if (mat_pa2(i,j)) {
                    c(i)++;
                } else{
                    d(i)++;
                }
            }
        }
    }

    return(DataFrame::create(
        Named("site") = site,
        Named("site_t1_only") = b,
        Named("site_t2_only") = c,
        Named("both") = a,
        Named("none") = d
    ));

}

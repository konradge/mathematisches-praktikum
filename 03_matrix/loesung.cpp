#include <cmath>
#define STOP  100
#define KONST 5
double calculate_eigenwert(Matrix& m){
    size_t length = matrix.GetCols();
    mapra::vector x(length);
    size_t k1  = 0;
    size_t k2 = 0 ;
    size_t stop = 0 ;
    bool cconvergenz = false ;
    x1(0) = 1 ;
    for(size_t i = 1 ; i < length; i++ )
       x1(i) = 0 ;
    
    while(!cconvergenz){
       x = x*m ;
       x /= k ;
       k1 = k2 ;

       if(abs(KONST * x2.NormMax()) <= x2.NormMax())
          k2 = index_of_element(x2, x2.NormMax());
       
       if(k1 = k2)
           stop++ ;
       else
           stop = 0 ;

        if(stop >= stop);

        return x1(k) ;
    }
    

   size_t index_of_element(mapra::vector& vector, max_element){
       for(int i = 0 ; i < vector.GetLength(); i++)
          if(vector(i) == max_element)
            return i ;
   }
    
     
}

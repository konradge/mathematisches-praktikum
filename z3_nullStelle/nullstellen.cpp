
// Einbinden der Header-Datei

#include "unit.h"
#include <iostream>
#include <map>
#define G 1/2
std::map<double ,double> function;
void itteration(double &xi, double &fi, double &xiPlus1, double &fiPlus1,int meth );
void andBjrk(double &xi, double &fi, double &xiPlus1, double &fiPlus1 );
void illinois(double &xi, double &fi, double &xiPlus1, double &fiPlus1 );
void pegasus(double &xi, double &fi, double &xiPlus1, double &fiPlus1 );
void regFalsi(double &xi, double &fi, double &xiPlus1, double &fiPlus1 );
void Step(double &xi, double &fi, double &xiPlus1, double &fiPlus1,  int meth );
int main() {
    int ex = 0;
    double xi  = 0;
    double xiPlus1 = 0;
    double fi  = 0;
    double fiPlus1 = 0;
    bool draw =false  ;
    int pause = 0;
   // int meth ;
   
   //std::cout << "enter the number of the example (1....9)" <<std::endl ;
   //std::cin>>ex ;
   //std::cout << "enter the method"  <<"1: Regula Falsi   "<<"2: Illinois  "<<"3: Pegasus   " <<"4: Anderson-Bjoeck"<<std::endl;
   //std::cin>>meth ;
   // getExample(ex,xi, xiPlus1, draw,pause);
   // fi = f(xi);
    //function.insert(std::pair<double , double >(xi,fi));
    //fiPlus1= f(xiPlus1);
    //function.insert(std::pair<double , double >(xiPlus1,fiPlus1));
    
   /* switch (meth)
    {
    case RegFalsi: regFalsi(xi, fi, xiPlus1,fiPlus1 ) ;
      break;
    case Illinois:illinois(xi, fi, xiPlus1,fiPlus1 ) ; 
      break;
    case Pegasus:pegasus(xi, fi, xiPlus1,fiPlus1 ) ; 
      break;
    case AndBjrk :andBjrk(xi, fi, xiPlus1,fiPlus1 ) ;
      break;
        default:
        std::cout<<"this method is not aviable"<<std::endl ;
      break;
    } */   
    std::cout << "enter the number of the example (1....9)" <<std::endl ;
   std::cin>>ex ;
    getExample(ex,xi, xiPlus1, draw,pause);
    fi = f(xi);
    function.insert(std::pair<double , double >(xi,fi));
    fiPlus1= f(xiPlus1);
    function.insert(std::pair<double , double >(xiPlus1,fiPlus1));
    andBjrk(xi, fi, xiPlus1,fiPlus1 );
    
      
    
    
    return 0;
}

void andBjrk(double &xi, double &fi, double &xiPlus1, double &fiPlus1 ){itteration(xi, fi, xiPlus1,fiPlus1,AndBjrk);}
void illinois(double &xi, double &fi, double &xiPlus1, double &fiPlus1 ){itteration(xi, fi, xiPlus1,fiPlus1,Illinois);}
void pegasus(double &xi, double &fi, double &xiPlus1, double &fiPlus1 ){itteration(xi, fi, xiPlus1,fiPlus1,Pegasus);}
void regFalsi(double &xi, double &fi, double &xiPlus1, double &fiPlus1 ){ itteration(xi,fi,xiPlus1,fiPlus1, RegFalsi);}

void itteration(double &xi, double &fi, double &xiPlus1, double &fiPlus1,int meth ){
  bool end = false ;
    
  while (!end){
      Step(xi,  fi, xiPlus1, fiPlus1,  meth );
      
     checkStep(meth,  xi,  fi,xiPlus1,  fiPlus1);
    switch (meth)
    {
    case RegFalsi:
      if((std::abs(fiPlus1 )<= eps) || std::abs(fiPlus1 )== 0)
        end = true ;
      break;
    case  Illinois:
    case Pegasus:
    case AndBjrk:
       if((std::abs(fiPlus1 )<= eps  && std::abs(xiPlus1 - xi )<= eps) || std::abs(fiPlus1 )== 0)
         end = true ;
      break;
    default:
      std::cout<<"this method is not avaible"<<std::endl ;
      break;
    }  
    if((std::abs(fiPlus1 )<= eps && std::abs(xiPlus1 - xi )<= eps) || std::abs(fiPlus1 )== 0){
      end = true ;
    } 
  }
  checkSolution(meth,  xiPlus1);
}



void Step(double &xi, double &fi, double &xiPlus1, double &fiPlus1,  int meth){
    double gamma ; 
    double xim1 =  xi ;
    double fim1 = fi ;
    xi = xiPlus1;
    fi = fiPlus1;
    double a = (fim1 - fi)/(xim1 - xi);   
    xiPlus1 = (xim1 - fim1/a );  
    if(function.find(xiPlus1) == function.end()){
      fiPlus1 = f(xiPlus1);
      function.insert(std::pair<double , double >(xiPlus1,fiPlus1));
    }else{
      fiPlus1 = function.at(xiPlus1);
    }
    
    switch (meth)
    {
    case RegFalsi:gamma = 1 ;
      break;
    case Illinois:gamma = 0.5 ;
      break;
    case Pegasus:gamma = fi/(fi+ fiPlus1) ;
      break;
    case AndBjrk :
         gamma = 1- fi/fiPlus1 ;
          if(gamma <= 0 )
            gamma = 0.5 ;
      break;
        default:
        std::cout<<"this method is not aviable"<<std::endl ;
      break;
    }  
    if(fi * fiPlus1 < 0){
        return ;
    }
    else{
        xi = xim1;
        fi = fim1*gamma ;
        
    }   
}

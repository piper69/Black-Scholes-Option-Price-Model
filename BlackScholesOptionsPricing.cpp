#include <iostream>
#include <math.h>
#include <cmath>
#include <cstdlib>

using namespace std;

double N(double z);

class BlackScholes
{
      public:
      double d1();
      double d2();
      double Price();
      BlackScholes(double callFlagInput, double SInput, double XInput, double rInput, double volInput, double TInput);
      void printTest();
      void ErrorChecker();
      BlackScholes();
      ~BlackScholes();
      double callFlag;
      private:
      double S;
      double X;
      double r;
      double vol;
      double T;
};


BlackScholes::BlackScholes(double callFlagInput, double SInput, double XInput, double rInput, double volInput, double TInput)//Yay constructor ^_^
{
callFlag=callFlagInput;
S=SInput;
X=XInput;
r=rInput/100;
vol=volInput;
T=TInput/365;
}

BlackScholes::BlackScholes()
{
}

double BlackScholes::d1()
{

    return (log(S/X)+(r+pow(vol,2)/2)*T)/(vol*sqrt(T));
}

double BlackScholes::d2()//calculates d2 ^_^
{

    return d1()-vol*sqrt(T);
}

double BlackScholes::Price()
{

    double x=S*N(callFlag*d1());
    double y=X*exp(-1*r*T)*N(callFlag*d2());
    if(callFlag==1)
    {
        cout<<"The price of the call is "<<callFlag*(x-y)<<endl;
    }
    if(callFlag==-1)
    {
        cout<<"The price of the put is "<<callFlag*(x-y)<<endl;
    }
}

void BlackScholes::ErrorChecker()
{
    if(S<=0)
    {
        cout<<"All stocks cost something!  Illegal input!  CRASH!"<<endl;
        exit(1);
    }
    if(X<=0)
    {
        cout<<"No such thing as a strike price of 0!  Illegal input!  CRASH!"<<endl;
        exit(1);
    }
    if(vol<=0)
    {
        cout<<"There's always volatility!  Illegal input!  CRASH!"<<endl;
        exit(1);
    }
    if(T<=0)
    {
        cout<<"You can't go back in time!  Illegal input!  CRASH!"<<endl;
        exit(1);
    }
    if(callFlag!=-1&&callFlag!=1)
    {
        cout<<"Illegal input!  CRASH!"<<endl;
        exit(1);
    }
}

void BlackScholes::printTest()
{
if(callFlag==1)
    {
        cout<<"The option is a call."<<endl;
    }
if(callFlag==-1)
    {
        cout<<"The option is a put."<<endl;
    }
cout<<"The volatility is "<<vol<<endl;
cout<<"The stock price is "<<S<<endl;
cout<<"The strike price is "<<X<<endl;
cout<<"LIBOR is "<<r<<endl;
cout<<"The time in years to expiration is "<<T<<endl;
cout<<"d1 is "<<d1()<<endl;
cout<<"d2 is "<<d2()<<endl;
cout<<"The normalized d1 is "<<N(callFlag*d1())<<endl;
cout<<"The normalized d2 is "<<N(callFlag*d2())<<endl;

}

BlackScholes::~BlackScholes()
{

}

double N(double z)
{
  const double b1 =  0.319381530;
  const double b2 = -0.356563782;
  const double b3 =  1.781477937;
  const double b4 = -1.821255978;
  const double b5 =  1.330274429;
  const double p  =  0.2316419;
  const double c2  =  0.39894228;

  double a=fabs(z);
  double t=1.0/(1.0+a*p);
  double b=c2*exp((-z)*(z/2.0));
  double n=((((b5*t+b4)*t+b3)*t+b2)*t+b1)*t;
  n=1-b*n;
  if(z<0) n=1-n;
  return n;
}

int main(){
    cout<<"I has a black-scholes!"<<endl;
    double callFlag;
    double S;
    double X;
    double r;
    double vol;
    double days;
    cout<<"Please enter -1 if the option is a put or 1 if the option is a call."<<endl;
    cin>>callFlag;
    cout<<"Please enter the stock price."<<endl;
    cin>>S;
    cout<<"Please enter the strike price."<<endl;
    cin>>X;
    cout<<"Please enter LIBOR as a percentage.  (If Libor is 4%, please enter 4.)"<<endl;
    cin>>r;
    cout<<"Please enter the volatility.  Yes, I know, I should calculate the volatility from an array of stock prices.  Oh well.  You do that instead."<<endl;
    cin>>vol;
    cout<<"Please enter the time to expiration in days.  This is because I'm too lazy to import a calendar into the program."<<endl;
    cin>>days;
    BlackScholes IMK(callFlag,S,X,r,vol,days);
    IMK.ErrorChecker();
    IMK.Price();
    int repeat;
    cout<<"Would you like to use the program again?  If so, please press 0."<<endl;
    cin>>repeat;
    if(repeat==0)
    {
        main();
    }
    else
    {
        cout<<"Thanks for using my Black Scholes program.  Bye!"<<endl;
        return(0);
    }
}


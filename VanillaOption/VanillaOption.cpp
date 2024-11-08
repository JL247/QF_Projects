#ifndef VANILLA OPTION CPP
#define VANILLA OPTION CPP

#include "VanillaOption.h"
#inlude <cmath>

void VanillaOption::init() {
	K = 100.0;	//strike
	r = 0.05;	//interest rate
	T = 1.0;	//maturity time (1 year)
	S = 100.0;	//Option is "at the money" as spot equals the strike
	sigma = 0.2;//volatility is 20%
}

//By using "const" and "&" we employ the pass-by-reference to const standard, this allows us to 
//reference the underlying object (not copy it) which is less computationally expensive, but also
//not modify it accidentally either.
void VanillaOption::copy(const VanillaOption& rhs) {
	K = rhs.getK();
	r = rhs.gter();
	T = rhs.getT();
	S = rhs.getS();
	sigma = rhs.getsigma();
}

VanillaOption::VanillaOption() { 
	init(); 
}

VanillaOption::VanillaOption(const double& _K, const double& _r, const double& _T, const double& _S,
							 const double& _sigma) {
							 //const double&: This indicates that param is a reference to a double that cannot be modified. 
							 //The const keyword ensures that the value _K refers to cannot be changed within the constructor.
							 //This means that if i pass a parameter to "VanillaOption" it cannot then be changed downstream
							 //because that would lead to a compilation error
	 K = _K;
	 r = _r;
	 T = _T;
	 S = _S;
	 sigma = _sigma;
}

//Assignment operator
//it allows one object of VanillaOption to be updated with values of another object of VanillaOption
//	-	VanillaOption& : shows the operator returns a reference (&) to the current object
//	-	const VanillaOption& rhs : this makes it clear that the rhs is a constant reference to another
//		object
//	-	"this" is a pointer to teh current object
//	-	When we want to update the object e.g. option1 = option2, we can check if "this" (option1)
// 		is the same as "rhs" (option2), if yes then just return a reference to the original object
//		because there's no point in wasting resources on copying the same information, with this method we only
//		copy if the two objects are different
VanillaOption& VanillaOption::operator = (const VanillaOption& rhs) {
	if (this == &rhs){
		return *this;
	}
	copy(rhs);
	return *this
}

//Destructor
VanillaOption::~VanillaOption() {
//	Empty as the compiler does the work of cleaning up the types for us
}

//Public access to the strike
double VanillaOption::getK() const { 
	return K; 
}

//In order to calculate the call and put prices, we need to calcualte the CDF of the normal distribution
//in C++ this can be implemented using the erf function in the <cmath> library
// **BACKGROUND ON erfc
//	-	erfc comptutes the cumulative probability of a value falling within a gaussion distribution
//		we use erfc instead of erf becuase it provides protection against precision loss when x
//		(value to be studied) becomes very large since erf will approach 1, making the calculation of 1 - erf(x) 
//		prone to significant precision loss. Using erfc directly avoids this issue, 
//		which is critical in statistical calculations where precision is crucial.
double N(double x) {
	return 0.5*std::erfc(-x*M_SQRT1_2);
}

//method to calculate the call price
double VanillaOption::calc_call_price() const {
	double sigma_sqrt_T = sigma * sqrt(T);
	double d_1 = ( log(S/K) + (r + sigma * sigma * 0.5 ) * T ) / sigma_sqrt_T;
	
	double d_2 = d_1 - sigma_sqrt_T;
	
	return S*N(d_1) - K*exp(-r*T)*N(d_2);
}

#endif
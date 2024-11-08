//This creates the "VanillaOption" class, which encapsulates teh necessary data around a Europena vanilla call option derivative. 
//it will use private member data to encode the option parameters and expose access to the data via accessor methods.

//The price of a Eurpoean vanilla option is characterised by five parameters, which will be the classes private member data
//Strike price, K
// - Interest Rate (\risk free rate"), r
// - Expiry time of the option, T
// - Underlying asset price, S
// - Volatility of the underlying, (sigma)
//In addition, European vanilla call and put options are specied by their pay-o functions, f:
// - Call: fC(S) = max(S - K, 0)
// - Put: fP (S) = max(K - S, 0)

#ifndef _VANILLA_OPTION_H
#define _VANILLA_OPTION_H

class VanillaOption {

	private:
		void init();
		void copy(const VanillaOption& rhs);
		
		double K;		//strike price
		double r;		//risk-free rate
		double T;		//maturity time
		double S;		//underlying asset price
		double sigma;	//volatity of the underlying
	
	public:
		VanillaOption();	//Default Constructor
		VanillaOption(const double& _K, const double& _r, const double& _T, const double& _S, const double& _sigma);	//Parameter constructor
		VanillaOption(const VanillaOption& rhs);
		VanillaOption& operator = (const VanillaOption&rhs);	//assignment operator
		virtual VanillaOption();	//virtual destructor
		
		//This set of methods are used to "get" the private member data
		//they are post-marked with const so that they're unable to modify the member data
		double getK() const;
		double getr() const;
		double getT() const;
		double getS() const;
		double getsigma() const;
		
		//Option price calculation methods
		double calc_call_price() const;
		double calc_put_price() const;
		
	};




#endif
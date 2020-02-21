#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <numeric>      // std::accumulate
#include <cmath>

using namespace std;

class Option {

	int daysToExpiration;			// Days before the option expires
	double breakEvenPrice;			// Break even price (not really necessary), but we can use it later to confirm our predictions
	double currentStockPrice;		// current underlying stock price
	double premiumPrice;			// Price to buy the option (for 100 shares)
	double strikePrice;				// price at which the option must go above or below for it not to expire worthless.
	bool isCallOption;		// boolean. TRUE = CALL          FALSE = PUT

	double deltaValue;				// Delta how much change for $1 increase or decrease in underlying stock (VELOCITY)
	double gammaValue;				// change of delta for change of $1 in underlying stock (ACCELERATION)

	// Probability Calculated
	double probabilityOfOutOfTheMoney;	// Probability the price is out of the range of the option;

	// calculate profitablity. for incremental increases above the stock price (Maybe do about 3 standard deviations)	// Maybe make a vector
	// We need to know the probabity of each.
	
	// Overall increase in portfolio value if purchase
	// increase in terms of % if money is invested in the asset



public:
	// Instantiate Option Object
	Option(int daysToExpiration, double breakEvenPrice, double currentStockPrice, 
		double premiumPrice, double strikePrice, bool isCallOption, double deltaValue,
		double gammaValue) : daysToExpiration(daysToExpiration),
		breakEvenPrice(breakEvenPrice), currentStockPrice(currentStockPrice), 
		premiumPrice(premiumPrice), strikePrice(strikePrice), isCallOption(isCallOption), 
		deltaValue(deltaValue), gammaValue(gammaValue) {}

	int getDaysToExpiration();
	double getBreakEvenPrice();
	double getCurrentStockPrice();
	double getPremiumPrice();
	double getStrikePrice();
	bool getIsCallOption();
	double getDeltaValue();
	double getGammaValue();

	// void setProbabilityOTM(double probabilityOfOutOfTheMoney);

};


int Option::getDaysToExpiration() {
	return daysToExpiration;
}

double Option::getBreakEvenPrice() {
	return breakEvenPrice;
}

double Option::getCurrentStockPrice() {
	return currentStockPrice;
}

double Option::getPremiumPrice() {
	return premiumPrice;
}

double Option::getStrikePrice() {
	return strikePrice;
}

bool Option::getIsCallOption() {
	return isCallOption;
}

double Option::getDeltaValue() {
	return deltaValue;
}

double Option::getGammaValue() {
	return gammaValue;
}
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <numeric>  
#include <cmath>

using namespace std;

class Stock {

	// Input values
	string stockName;
	vector<string> date;
	vector<double> dayPrice;

	// Calculated values
	double meanOfAllPrices;

	// Build a vector of differences
	vector <double> vectorOfDifferences;
	double meanOfDifferances;	// mean of change between days (days to expiration)
	
	double standardDeviationVal;
	

public:
	// Instantiate Stock Object
	Stock(string stockName, vector<string> date, vector<double> dayPrice) : stockName(stockName), date(date), dayPrice(dayPrice) {}

	// Calculates the mean of all Prices
	void calculateMeanOfAllPrices();	// calculates, sets, and returns the mean
	double returnMeanOfAllPrices();

	// Calculate the mean of differences and set up the vectorOfDifferences
	void setMeanOfDifferences(int daysToExpiration);
	double getMeanOfDifferences();

	void calculateStandardDeviation();
	double getStandardDeviation();

};


// MEAN OF ALL PRICES
void Stock::calculateMeanOfAllPrices() {
	meanOfAllPrices = (accumulate(dayPrice.begin(), dayPrice.end(), 0.0)) / (dayPrice.size());
}
double Stock::returnMeanOfAllPrices() {
	return meanOfAllPrices;
}

// Creates a vector of differences with the specified daysToExpiration. calculates the mean.
void Stock::setMeanOfDifferences(int daysToExpiration) {
	// returns the price at that day : dayPrice[0];
	for (unsigned int i = 0; i < (dayPrice.size() - daysToExpiration); i++) {
		int j = i + daysToExpiration;
		vectorOfDifferences.push_back(dayPrice[j]- dayPrice[i]);
	}
	// Calculates the mean
	meanOfDifferances = (accumulate(vectorOfDifferences.begin(), vectorOfDifferences.end(), 0.0)) / (vectorOfDifferences.size());
}

double Stock::getMeanOfDifferences() {
	return meanOfDifferances;
}



// STANDARD DEVIATION CALCULATION
void Stock::calculateStandardDeviation() {
	double variance = 0.0;

	// calculate the variance
	for (unsigned int i = 0; i < vectorOfDifferences.size(); i++) {
		variance = variance + pow((vectorOfDifferences[i] - meanOfDifferances),2);
	}
	variance = variance / vectorOfDifferences.size();
	// sqrt of variance is standard deviation val
	standardDeviationVal = sqrt(variance);
}

double Stock::getStandardDeviation() {
	return standardDeviationVal;
}



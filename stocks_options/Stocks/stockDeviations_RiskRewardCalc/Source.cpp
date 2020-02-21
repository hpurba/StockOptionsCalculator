// #pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stockObj.h"
#include "Ztable.h"
#include "optionObj.h"

using namespace std;

int main(int argc, char *argv[]) {

	// Variables
	string nameOfStock;									// String holds the name of the stock
	double dayAverage;									// holds the average for a single day (double)
	vector<string> stockDateVector;						// holds the dates for each entry
	vector<double> dayApproximateAveragePriceVector;	// Holds the approximate average price for each day (Vector)
	vector<Option> vectorOfOptions;						// Holds OPTION objects
	bool enterAnotherOption = true;						// bool to enter another option or not
	string yesOrNoOption;								// Enter another option "y" or "n"

	// USER INPUTS THIS DATA
	int daysToExpiration;		// 2 weeks = 9
	double strikePrice;			// price at which the option must go above or below for it not to expire worthless.
	double currentStockPrice;	// Underlying stock price
	double premiumPrice;		// Price to purchase the option
	double breakEvenPrice;		// Price stock must reach to break even
	double deltaValue;			// "Velocity"
	double gammaValue;			// "Acceleration"
	
	string whichOption;			// stores "call" or "put"
	bool isCallOption = true;	// Are we dealing with a call option (true) or a put option (false)


	// CREATE VECTOR OF OPTION OBJECTS ---------------------------------------------------------
	while (enterAnotherOption) {
	// Days to expiration
		cout << "Enter days to Expiration of Option (Weekdays): ";
		cin >> daysToExpiration;
	// Strike Price
		cout << "Enter Strike Price (price above/below expires worthless): $";
		cin >> strikePrice;
	// current Underlying Stock Price
		cout << "Enter Current Underlying stock price: $";
		cin >> currentStockPrice;
	// Premium Price
		cout << "Enter the premium price for (100 shares) (How much it costs to buy the option): $";
		cin >> premiumPrice;
	// Break Even Price
		cout << "Enter the break even price: $";
		cin >> breakEvenPrice;
	// Delta Value
		cout << "Enter the Delta Value: ";
		cin >> deltaValue;
	// Gamma Value
		cout << "Enter the Gamma Value: ";
		cin >> gammaValue;
		cout << "\n";

		bool expressionNotValid = true;
		while (expressionNotValid) {
			// Is call option?
			cout << "Is the option a CALL or PUT?\nEnter (call) or (put): ";
			cin >> whichOption;

			if (whichOption == "call") {
				isCallOption = true;
				cout << "\n";
				expressionNotValid = false;
			}
			else if (whichOption == "put") {
				isCallOption = false;
				cout << "\n";
				expressionNotValid = false;
			}
			else {
				cout << "Not a valid entry! Try again.\n";
			}
		}

		// BUILD THE OPTION OBJECT
		Option Option(daysToExpiration, breakEvenPrice, currentStockPrice, premiumPrice,
			strikePrice, isCallOption, deltaValue, gammaValue);
		// Add it to the vector of Option objects
		vectorOfOptions.push_back(Option);


		cout << "\n" << "Would you like to enter another option? Enter (y) or (n): ";
		cin >> yesOrNoOption;
		if (yesOrNoOption == "y") {
			// Loop through again
		}
		else if (yesOrNoOption == "n") {
			enterAnotherOption = false;
		}
		else {
			enterAnotherOption = false;
		}
	}

	
	// RETRIEVE DATA FOR STOCK! ---------------------------------------------------------
	string fileName = argv[1];
	ifstream myStream;
	myStream.open(fileName, ifstream::in);

	// Get the name of the stock
	getline(myStream, nameOfStock);
	cout << "Name of Stock: " << nameOfStock << "\n\n";

	char currentChar;
	char nextChar;
	int numEntries = 0;
	// Retrieves all the information form the input file
	// Date,Open,High,Low,Close,Adj Close,Volume
	while (myStream.peek() != EOF) {
		nextChar = myStream.peek();
		numEntries++;
		// cout << "Entry " << numEntries << ".\n";
		currentChar = myStream.get();

		// DATE: ------------------------------------------------------------------------
		// Gets the date
		string stockDate;
		while (currentChar != ',' && currentChar != '\n')
		{
			stockDate = stockDate + currentChar; 
			currentChar = myStream.get();
		}
		// cout << "Stock Date:" << stockDate << "\n";

		// OPEN: ------------------------------------------------------------------------
			// Gets the Opening Price
		string openPrice_S;
		double openPrice_D;
		currentChar = myStream.get();
		while (currentChar != ',' && currentChar != '\n')
		{
			openPrice_S = openPrice_S + currentChar;
			currentChar = myStream.get();
		}
		openPrice_D = stod(openPrice_S);
		// cout << "Open Price: $" << openPrice_D << "\n";

		// HIGH: ------------------------------------------------------------------------
			// Gets the High Price
		string highPrice_S;
		double highPrice_D;
		currentChar = myStream.get();
		while (currentChar != ',' && currentChar != '\n')
		{
			highPrice_S = highPrice_S + currentChar;
			currentChar = myStream.get();
		}
		highPrice_D = stod(highPrice_S);
		// cout << "Price High: $" << highPrice_D << "\n";

		// LOW: ------------------------------------------------------------------------
			// Gets the Low Price
		string lowPrice_S;
		double lowPrice_D;
		currentChar = myStream.get();
		while (currentChar != ',' && currentChar != '\n')
		{
			lowPrice_S = lowPrice_S + currentChar; 
			currentChar = myStream.get();
		}
		lowPrice_D = stod(lowPrice_S);
		// cout << "Price Low: $" << lowPrice_D << "\n";

		// CLOSE: ------------------------------------------------------------------------
			// Gets the Close Price
		string closePrice_S;
		double closePrice_D;
		currentChar = myStream.get();
		while (currentChar != ',' && currentChar != '\n')
		{
			closePrice_S = closePrice_S + currentChar; 
			currentChar = myStream.get();
		}
		closePrice_D = stod(closePrice_S);
		// cout << "Price Close: $" << closePrice_D << "\n";

		// ADJUST CLOSE: -----------------------------------------------------------------
			// Gets the Adjusted Close
		string adjClosePrice_S;
		double adjClosePrice_D;
		currentChar = myStream.get();
		while (currentChar != ',' && currentChar != '\n')
		{
			adjClosePrice_S = adjClosePrice_S + currentChar; 
			currentChar = myStream.get();
		}
		adjClosePrice_D = stod(adjClosePrice_S);
		// cout << "Adjusted Close Price: $" << adjClosePrice_D << "\n";

		// TRADED VOLUME: -----------------------------------------------------------------
			// Gets the traded Volume
		string tradedVolume_S;
		double tradedVolume_D;
		currentChar = myStream.get();
		while (currentChar != ',' && currentChar != '\n')
		{
			currentChar = myStream.get();
			tradedVolume_S = tradedVolume_S + currentChar;
		}
		tradedVolume_D = stod(tradedVolume_S);
		// cout << "Traded Volume: " << tradedVolume_D << "\n";

		// ADDING TO VECTOR: -----------------------------------------------------------------
			// calculate the dayPrice average
			// Add it to a vector of prices
		dayAverage = ( openPrice_D + closePrice_D ) / 2;
		// cout << "Day average (approximation): $" << dayAverage << "\n";
		dayApproximateAveragePriceVector.push_back(dayAverage);
		// pushback date
		stockDateVector.push_back(stockDate);

		// New line detection.
		if (currentChar = '\n') {
			currentChar = myStream.get();
			// cout << "\n\n";
		}
	}
	// CREATE STOCK OBJECT
	Stock Stock(nameOfStock, stockDateVector, dayApproximateAveragePriceVector); // Only need to create one
	



	// OUTPUT SUMMARIZED DETAILS OF INPUT INFORMATION FOR STOCK ------------------------------------------------------------------------------------------------------------------
	cout << "STOCK DETAILS SUMMARIZED: \n";
	// Stock calculate total mean
	Stock.calculateMeanOfAllPrices();
	cout << "Stock price mean of all '" << stockDateVector.size() << "' past prices: $" << Stock.returnMeanOfAllPrices() << "\n\n";

	


	// FOR EACH OPTION
	for (unsigned int i = 0; i < vectorOfOptions.size(); i++) {
		cout << "OPTION (" << (i + 1) << ") INFORMATION:\n";
		// Stock create vectorOfDifferences vector and set the meanOfDifferences between (X)days.
		Stock.setMeanOfDifferences(vectorOfOptions[i].getDaysToExpiration());
		cout << "The mean of differences with '" << vectorOfOptions[i].getDaysToExpiration() << "' days to expiration is: $" << Stock.getMeanOfDifferences() << ".\n";
		cout << "This is the mean for how much the prices changes in '" << vectorOfOptions[i].getDaysToExpiration() << "' days to expiration of the option.\n";

		
		// STANDARD DEVIATION
		Stock.calculateStandardDeviation();
		cout << "The standard deviation for the provided data is: " << Stock.getStandardDeviation() << ".\n";


		// Z value calculation
		double Zvalue = ((vectorOfOptions[0].getStrikePrice() - vectorOfOptions[0].getCurrentStockPrice()) - Stock.getMeanOfDifferences()) / Stock.getStandardDeviation();
		Zvalue = round(Zvalue * 100) / 100;		// round Z value to 2 places
		cout << "The Z value is :" << Zvalue << "\n";


		// We are dealing with a call option										// Know In the money and Out of the Money
		if (isCallOption) {
			double totalGain = 0.0;
			double totalLoss = 0.0;
			double segmentProfitability = 0.0;
			vector<double> profitabilityPerDollarSegment;
			vector<double> probabilityPerDollarSegment;


			// Give a Z value and compute the probability of failure
			Ztable Ztable(Zvalue);

			Ztable.fetchProbabilityLeft();
			cout << "Probability the option is OUT of the money is: " << Ztable.returnProbabilityLeft() * 100 << "%" << "\n";
			
			// Need to get probability and profitability of maybe $1.00 dollar intervals to t
			totalLoss = Ztable.returnProbabilityLeft() * vectorOfOptions[i].getPremiumPrice();
			cout << "Statistical Total Loss: $" << totalLoss << "\n\n";
			
			
			// Gain must be calculated with $1 intervals until Z value is about 3.69 *** No more, if so set equal to 0
			
			for (unsigned int i = 0; i < 100; i++) {
				//Get the probability for a $1 Segment
				double upperZvalueProbability;
				double lowerZvalueProbability;
				double segmentProbability;
				
				// Lower Z value Calculation
				Zvalue = (((vectorOfOptions[0].getStrikePrice() + i) - vectorOfOptions[0].getCurrentStockPrice()) - Stock.getMeanOfDifferences()) / Stock.getStandardDeviation();
				Zvalue = round(Zvalue * 100) / 100;		// round Z value to 2 places
				Ztable.setNewZvalue(Zvalue);
				Ztable.fetchProbabilityLeft();
				lowerZvalueProbability = Ztable.returnProbabilityLeft();
				// cout << "Lower Zvalue Probability: " << lowerZvalueProbability << "\n";

				// Upper Z value Calculation
				Zvalue = (((vectorOfOptions[0].getStrikePrice() + i+ 1) - vectorOfOptions[0].getCurrentStockPrice()) - Stock.getMeanOfDifferences()) / Stock.getStandardDeviation();
				Zvalue = round(Zvalue * 100) / 100;		// round Z value to 2 places
				Ztable.setNewZvalue(Zvalue);
				Ztable.fetchProbabilityLeft();
				upperZvalueProbability = Ztable.returnProbabilityLeft();
				// cout << "Upper Zvalue Probability: " << upperZvalueProbability << "\n";

				segmentProbability = upperZvalueProbability - lowerZvalueProbability;
				cout << "Segment Probability: " << segmentProbability << "\n";

				// Profitability for $1 increase // THIS EQUATION NEEDS HELP
				// HOW CAN I MORE ACCURATELY ESTIMATE HOW MUCH EACH DOLLAR INCREASE CHANGES THE PRICE OF THE OPTION
				segmentProfitability = 100 * i ;// 100 * (deltaValue * (i + 1) + (1 / 2) * gammaValue * ((i + 1) ^ 2));
				cout << "Segment Profitability: $" << segmentProfitability << "\n";

				profitabilityPerDollarSegment.push_back(segmentProfitability);
				probabilityPerDollarSegment.push_back(segmentProbability);

			}

			


			// Calculation of total Gain
			for (unsigned int i = 0; i < profitabilityPerDollarSegment.size(); i++) {
				totalGain = totalGain + (profitabilityPerDollarSegment[i] * probabilityPerDollarSegment[i]);
			}

			cout << "Statistical Total Gain: $" << totalGain << "\n\n";
			// Total Gain - Total Loss
			double totalProfitabilityForThisOptionInvestment;
			totalProfitabilityForThisOptionInvestment = totalGain - totalLoss;
			cout << "Total Profitability: $" << totalProfitabilityForThisOptionInvestment << "\n";

			cout << "Total Profitability for this option Investment as a percentage (totalProfitability / premiumPrice): " << (totalProfitabilityForThisOptionInvestment / premiumPrice) * 100 << "%\n";


		}
		// We are dealing with a put option
		else {
			// Give a Z value and compute the probability of failure (1 - probability)


		}
	}

	

	return 0;
}


/*
// Sample Input for APPLE stock option

For Apple

9
237.5
236.31
353
241.05
0.4660
0.0386
call
n


For Honda
HMC
nov 15 option

24
30
26.33
50
30.25
0.1582
0.0761
call
n



For Netflix
NFLX
october 25 option call buy

9
285
283.17
1455
299.53
0.5108
0.0104
call
n



*/
/*
This program is meant give me a rough estimate of what my monthly income will be after taxes and pre-tax deductions for a range of potential salaries.
*/


#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>


//Containers
#include <list>

//multithreading if needed
#include <thread>


using namespace std;


//Checks Income and sets the appropriate tax bracket.
//Currently has 2019 single filer numbers since they're most relevant to me.
float FedTaxBrackets(float m_Income, float m_fedTaxTotal);

int main()
{
	list<float> annualSalary;
	list<float>::iterator iter;
	int Limit = 20;
	float Income = 30000.0;
	float StateIncTaxRate = 0.051f;
	cout << "Input low-range annual salary: "; cin >> Income; cout << endl;
	cout << "Salaries will be counted in units of 1000.\nInput how many salaries to calculate:"; cin >> Limit; cout << endl;
	


	/*cout << "Input tax rates as a decimal.\n";
	
	float FICA = 0, SocialSecurity = 0.0620, Medicare = 0.0145;
	cout << "Federal Income Tax Rate: "; cin >> FedIncTaxRate; cout << endl;
	cout << "State Income Tax Rate: "; cin >> StateIncTaxRate; cout << endl;
	cout << "Local Income Tax: "; cin >> LocalIncTaxRate; cout << endl;
	cout << "FICA: "; cin >> FICA; cout << endl;
	cout << "Social Security: "; cin >> SocialSecurity; cout << endl;
	cout << "Medicare "; cin >> Medicare; cout << endl;*/


	//Pretax Deductions
	float MedicalIns, DentalIns, VisionIns, F01k, LongTermDisability, LifeIns, CommuterPlan, FSA, HSA = 0;
	cout << "Input any pre-tax deductions as an exact value: " << endl;
	cout << "Medical Insurance: "; cin >> MedicalIns; cout << endl;
	cout << "Dental Insurance: "; cin >> DentalIns; cout << endl;
	cout << "Vision Insurance: "; cin >> VisionIns; cout << endl;
	cout << "401k: "; cin >> F01k; cout << endl;
	cout << "Long Term Disability:  "; cin >> LongTermDisability; cout << endl;
	cout << "Life Insurance: "; cin >> LifeIns; cout << endl;
	cout << "Commuter Plan: "; cin >> CommuterPlan; cout << endl;
	cout << "FSA: "; cin >> FSA; cout << endl;
	cout << "HSA: "; cin >> HSA; cout << endl;


	for (int i = 0; i < Limit; i++)
	{
		float Incriment = 1000.0;
		Income = Income + Incriment;
		annualSalary.push_back(Income);

	}
	cout << "Calculating monthly income for the following salaries: \n";
	for (iter = annualSalary.begin(); iter != annualSalary.end(); iter++)
	{
		cout << *iter << endl;
	}

	//Pretax deductions. Calculates amount to deduct and inserts the result into a new list
	list<float> annualIncomeAfterPreTax;
	cout << "Calculating pre-tax deductions\n";
	for (iter = annualSalary.begin(); iter != annualSalary.end(); iter++)
	{
		float result = 0;
		result = *iter - MedicalIns - DentalIns - VisionIns - F01k - LongTermDisability - LifeIns - CommuterPlan - FSA - HSA;
		annualIncomeAfterPreTax.push_back(result);
	}
	for (iter = annualIncomeAfterPreTax.begin(); iter != annualIncomeAfterPreTax.end(); iter++)
	{
		cout << *iter << endl;
	}



	//Taxes
	list<float>annualIncomeAfterTaxes;

	for (iter = annualIncomeAfterPreTax.begin(); iter != annualIncomeAfterPreTax.end(); iter++)
	{
		float fedTaxTotal = 0;
		fedTaxTotal = FedTaxBrackets(*iter, fedTaxTotal);
		float stateTaxTotal = *iter * StateIncTaxRate;
		float result = 0;
		result = *iter - fedTaxTotal - stateTaxTotal;
		annualIncomeAfterTaxes.push_back(result);
	}
	cout << "Annual Income after taxes\n\n";
	for (iter = annualIncomeAfterTaxes.begin(); iter != annualIncomeAfterTaxes.end(); iter++)
	{
		cout << *iter << endl;
	}




	list<float>MonthlyIncome;
	for (iter = annualIncomeAfterTaxes.begin(); iter != annualIncomeAfterTaxes.end(); iter++)
	{
		float result = 0;
		result = *iter / 12;
		MonthlyIncome.push_back(result);
	}

	for (iter = MonthlyIncome.begin(); iter != MonthlyIncome.end(); iter++)
	{
		cout << "Monthly income after taxes: " << *iter << endl;
	}



}

/*
Checks Income and calculates total federal taxes for the appropriate tax bracket range.
*/
float FedTaxBrackets(float m_Income, float m_fedTaxTotal)
{
	

float firstBracket = 0;
const float Bracket1_Range1 = 0, Bracket1_Range2 = 9700;

if (m_Income > Bracket1_Range1 && m_Income <= Bracket1_Range2)
	{
		firstBracket = (m_Income * 0.10f);
	}
	if (m_Income >= Bracket1_Range2)
	{
		firstBracket = (Bracket1_Range2 * 0.10f);
	}

	


float secondBracket=0;
const float Bracket2_Range1 = 9701, Bracket2_Range2 = 39475;

	if (m_Income >= Bracket2_Range1 && m_Income <= Bracket2_Range2)
	{
		
		float localHolder = m_Income - Bracket2_Range1;
		secondBracket = (localHolder *= 0.12f);
	}
	if (m_Income > Bracket2_Range2)
{
	
	secondBracket = (Bracket2_Range2 - Bracket2_Range1) * 0.12f;
	
}
;



float thirdBracket=0;
const float Bracket3_Range1 = 39476, Bracket3_Range2 = 84200;

	if (m_Income >= Bracket3_Range1 && m_Income <= Bracket3_Range2)
	{
		float localHolder = m_Income - Bracket3_Range1;
		 thirdBracket = localHolder *= 0.22f;
	}
	if (m_Income > Bracket3_Range2)
	{
		thirdBracket = ((Bracket3_Range2 - Bracket3_Range1)*0.22f);
	}

	

float fourthBracket = 0;
	const float Bracket4_Range1 = 84201, Bracket4_Range2 = 160725;

	if (m_Income >= Bracket4_Range1 && m_Income <= Bracket4_Range2)
	{
		float localHolder = m_Income - Bracket4_Range1;
			fourthBracket = (localHolder *= 0.24f);
	}
	if (m_Income > Bracket4_Range2)
	{
		fourthBracket = ((Bracket4_Range2 - Bracket4_Range1)*0.24f);
	}

	float fifthBracket = 0;
	const float Bracket5_Range1 = 160726, Bracket5_Range2 = 204100;

	if (m_Income >= Bracket5_Range1 && m_Income <= Bracket5_Range2)
	{
		float localHolder = m_Income - Bracket5_Range1;
		fifthBracket = (localHolder *= 0.32f);
	}
	if (m_Income > Bracket5_Range2)
	{
		fifthBracket = ((Bracket5_Range2 - Bracket5_Range1)*0.32f);
	}

	
	
	float sixthBracket = 0;
	const float Bracket6_Range1 = 204401, Bracket6_Range2 = 510300;

	if (m_Income >= Bracket6_Range1 && m_Income <= Bracket6_Range2)
	{
		float localHolder = m_Income - Bracket6_Range1;
		sixthBracket = (localHolder *= 0.35f);
	}
	if (m_Income > Bracket6_Range2)
	{
		sixthBracket = ((Bracket6_Range2 - Bracket6_Range1)*0.35f);
	}

	
	float seventhBracket = 0;
	const float Bracket7_Range1 = 501301;

	if (m_Income >= Bracket7_Range1)
	{
		float localHolder = m_Income - Bracket7_Range1;
		seventhBracket = (localHolder *= 0.37f);
	}


	 m_fedTaxTotal = firstBracket + secondBracket + thirdBracket + fourthBracket + fifthBracket + sixthBracket + seventhBracket;
	
	return m_fedTaxTotal;
}
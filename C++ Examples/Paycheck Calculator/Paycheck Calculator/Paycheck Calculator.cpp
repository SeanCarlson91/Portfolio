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
void TaxBrackets(float m_Income, float m_FedIncTaxRate);

void main()
{
	list<float> annualSalary;
	list<float>::iterator iter;
	int Limit = 20;
	float Income = 30000.0;
	float FedIncTaxRate = 0.0f, StateIncTaxRate = 0.0f, LocalIncTaxRate = 0.0f;
	cout << "Input low-range annual salary: "; cin >> Income; cout << endl;
	cout << "Salaries will be counted in units of 1000.\nInput how many salaries to calculate:"; cin >> Limit; cout << endl;
	
	//Tax brackets
	TaxBrackets(Income, FedIncTaxRate);


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
		float fedTaxTotal = *iter * FedIncTaxRate;
		float stateTaxTotal = *iter * StateIncTaxRate;
		float result = 0;
		result = *iter - fedTaxTotal - stateTaxTotal;
		annualIncomeAfterTaxes.push_back(result);
	}
	cout << "Income after taxes\n\n";
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
Checks Income and sets the appropriate tax bracket.
*/
void TaxBrackets(float m_Income, float m_FedIncTaxRate)
{
	const float m_constIncome = m_Income;
	
	if (m_Income > 0 || m_Income >= 9700)
	{
		
	}


	

	if (m_Income >= 9701 && m_Income <= 39475)
	{
		m_FedIncTaxRate = 0.12f;
	}

	if (m_Income >= 39476 && m_Income <= 84, 200)
	{
		m_FedIncTaxRate = 0.22f;
	}
	if (m_Income >= 84201 && m_Income <= 160725)
	{
		m_FedIncTaxRate = 0.24f;
	}
	if (m_Income >= 160726 && m_Income <= 204100)
	{
		m_FedIncTaxRate = 0.32f;
	}
	if (m_Income >= 204401 && m_Income <= 510300)
	{
		m_FedIncTaxRate = 0.35f;
	}
	if (m_Income >= 501301)
	{
		m_FedIncTaxRate = 0.37f;
	}


}
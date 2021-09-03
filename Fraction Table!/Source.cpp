#include <iostream>
#include <string>
#include<iomanip>
using namespace std;

class FractionClass {
private:
	int numerator;
	int denominator;
	
public:
	static int countObj;
		
	FractionClass();
	explicit FractionClass(int num);
	FractionClass(int num, int den);
	FractionClass(int whole, int num, int den);
	FractionClass(const FractionClass& obj);

	~FractionClass();//destructor;

	//Overloaded operators
	FractionClass operator -(const FractionClass& rhs);
	FractionClass operator+(const FractionClass& rhs);

	FractionClass operator*(const FractionClass& rhs);
	FractionClass operator*(int num);
	friend FractionClass operator*(const int num, FractionClass& fraction);

	FractionClass operator/ (const FractionClass& rhs);

	FractionClass& operator=(const FractionClass& rhs);
	bool operator ==(const FractionClass& rhs)const;

	friend ostream& operator<< (ostream& output, const FractionClass& fraction);
	friend istream& operator >>(istream& input, FractionClass& fracObj);

	

	void SetNumerator(int num);
	void SetDenominator(int den);

	void SetFraction(int num);
	void SetFraction(int num, int den);
	void SetFraction(int whole, int num, int den);

	void ResetFraction();

	void Print() const;
	string ToString() const;

	//Function role to: return private member variable numerator without changing it!
	int GetNumerator()const { return numerator; }
	//Function role:To return private member variable denominator without changing it!
	int GetDenominator()const { return denominator; }


};//End of FractionClass!

class DivisonByZero {};

 void FractionTable(FractionClass**& fracArray, int den);
 void PrintFracTable(FractionClass* fracArray[], int den) ;
 void DeallocateMem(FractionClass* fracArray[], int den);

int FractionClass::countObj = 0; 
int main() {
	int den =0;
	FractionClass** fracArray =  nullptr;
	char goAgain = 'y';
	
	while (goAgain!='n'&& goAgain!='N') {
		cout << "Hello, please enter a denominator!" << endl;

		while (!(cin >> den) || den <= 0||den ==1) {
			cout << "There was an error with your input, please enter a number greater than 1! " << endl;
			cin.clear();
			cin.ignore(99999, '\n');

		}//End while loop wrong input while (!(cin >> den) || den <= 0) !

		FractionTable(fracArray,den);
		PrintFracTable(fracArray, den);

		cout << "\n\nCount of objects is: " << FractionClass::countObj << endl;

		DeallocateMem(fracArray, den);
		cout << "\n\nCount of objects after deallocation is: " << FractionClass::countObj << endl;

		cout << "Want to go again? Press 'y' If not press 'n'" << endl;
		cin >> goAgain;

	}//End goAgain loop
	

	return 0;
}// End main function!


//Functions purpose to overload opertar"-", to be able to subtract two objects of the FractionClass
FractionClass FractionClass::operator -(const FractionClass& rhs) {//1/2-3/2

	return FractionClass(numerator * rhs.denominator - rhs.numerator * denominator, denominator * rhs.denominator);

}//End subtraction overload function operator -()	

//Functions purpose to overload opertar"+", to be able to add two objects of the FractionClass
FractionClass FractionClass::operator + (const FractionClass& rhs) {

	return FractionClass(numerator * rhs.denominator + rhs.numerator * denominator, denominator * rhs.denominator);

}//End sum overload function operator +()

//Function purpose to overload multiplication operator "*", to be able to multiply two objects of the fractionClass
FractionClass FractionClass::operator*(const FractionClass& rhs) {

	return FractionClass(numerator * rhs.numerator, denominator * rhs.denominator);

}//End multiplication sign overload function operator*()


//Function purpose to overload operator"*" to be able to multiply fraction with int;
FractionClass FractionClass :: operator*(int number) {
	return FractionClass(numerator * number, denominator);


}//End overload "*" funtion, to multiply object with int

FractionClass operator*(const int num, FractionClass& fraction) {

	return FractionClass(fraction.numerator * num, fraction.denominator);
}//End overload "*" funtion, to multiply int with obj


//Fraction purpose to overload divison operator"/", to be able to divide  two object of the FractionClass
FractionClass FractionClass:: operator/ (const FractionClass& rhs) {

	try {
		if (rhs.numerator == 0) {
			throw DivisonByZero();
		}//end if staement

		return FractionClass(numerator * rhs.denominator, denominator * rhs.numerator);

	}
	catch (DivisonByZero) {
		cout << "\nERROR, can't divide by zero! Fraction was set to default" << endl;
		return FractionClass(0, 1);
	}
}//End divison operator overloade function  operator/()


//change the if stamtemnt, because int devision will set 1/2 == to 1/5!
bool FractionClass::operator==(const FractionClass& rhs)const {
	return (numerator * rhs.denominator == rhs.numerator * denominator);

}//End "==" opertopr overload function

//Fraction purpose to overload operator "=", to be able to perform a deep copy 
FractionClass& FractionClass::operator=(const FractionClass& rhs) {

	numerator = rhs.numerator;
	denominator = rhs.denominator;

	return *this;
}//End equal sign overload function operator=()

//Function purpose to overload "<<", to be able to print object of the fraction class to the screen!
ostream& operator<< (ostream& output, const FractionClass& fracObj) {

	return output << fracObj.ToString();

}//End ostrean operator << funtion


//Function purpose to overload ">>", to be able to input data into object of FractionClass
istream& operator >>(istream& input, FractionClass& fracObj) {
	int whole, num, den;

	cout << "\nEnter whole:(Only positive values allowed!) " << endl;
	while (!(input >> whole) || whole < 0) {
		cout << "There was an error please enter numerator:(Only positive values allowed!) " << endl;
		cin.clear();
		cin.ignore(99999, '\n');
	}//End while loop error check numerator input

	cout << "\nEnter numerator:(Only positive values allowed!) " << endl;
	while (!(input >> num) || num < 0) {
		cout << "There was an error please enter numerator:(Only positive values allowed!) " << endl;
		cin.clear();
		cin.ignore(99999, '\n');
	}//End while loop error check numerator input

	cout << "Enter denominator:(Only positive value allowed that are not equal to zero!) " << endl;

	while (!(input >> den) || den <= 0) {
		cout << "There was an error please enter denominator:(Only positive values allowed! That are not equal to zero!) " << endl;
		cin.clear();
		cin.ignore(99999, '\n');
	}//End while loop error check denominator input

	fracObj.SetFraction(whole, num, den);
	return input;
}// istream operator >> function

//Mutator function to store a value in private member variable numerator
void FractionClass::SetNumerator(int num) {
	SetFraction(0, num, denominator);
}//End setNumerator function

//Mutator function to store a value in private member variable denominator
void FractionClass::SetDenominator(int den) {
	//Caling SetFraction To verify if input was correct!
	SetFraction(0, numerator, den);
}//End setdenominator function!3


//Function purpose: to reset values of fraction to default
void FractionClass::ResetFraction() {
	numerator = 0;
	denominator = 1;

}// End reset fraction

//PrintFraction Outputs the fraction to the screen, by caling ToString function!
void FractionClass::Print()const {
	cout << "\t The Fraction is: " << ToString() << endl;
}//End Print Function!

//Fraction purpose to store a value in numerator member varable and set denomintor = 1!
void FractionClass::SetFraction(int num) {

	SetFraction(0, num, denominator);
}//End Set fraction with one argument

//Fraction purpose to Store values in both numerator and denominator;
void FractionClass::SetFraction(int num, int den) {

	SetFraction(0, num, den);
}//End SetFraction function with two argum nuents!

//SetFraction with 3 arguments purpose to store values into member variables
void FractionClass::SetFraction(int whole, int num, int den) {

	//Input Error Checking!
	if (num < 0 || den < 0 || whole < 0 || den == 0)
	{
		cout << "\nThere was an error, whole, numerator and denominator can't be negative!(fraction was set to default), denominator can't be zero" << endl;
		ResetFraction();
	}//End if statement
	else {
		numerator = (whole * den) + num;
		denominator = den;

	}//End else statement
}//End SetFraction with three arguments!

FractionClass:: FractionClass() :numerator(0), denominator(1) {

	countObj++;
	//cout << "\nDefault constructor has been called! " << endl;
}	//Default con5structor

//Constructor purpose to store a value in numerator member varable and set denomintor = 1!
FractionClass::FractionClass(int num) {
	countObj++;
	//cout << "\nConstructor with one argument has been called!" << endl;
	SetFraction(0, num, denominator);
}//End Constructor with one argument!

//Constructor purpose to Store values in both numerator and denominator;
FractionClass::FractionClass(int num, int den) {
	countObj++;
	//cout << "\nConstructor with two arguments has been called!" << endl;
	SetFraction(0, num, den);

}//End Constructor with two arguments.

//Constructor with 3 arguments, ading the whole to the numarator
FractionClass::FractionClass(int whole, int num, int den)
{
	countObj++;
	//cout << "\nConstructor with three arguments has been called!" << endl;
	SetFraction(whole, num, den);
}//End constructor with three arguments!

//Copy constructor
FractionClass::FractionClass(const FractionClass& obj) {
	//cout << "\nCopy constructor has been called: " << endl;
	numerator = obj.numerator;
	denominator = obj.denominator;

}//End Copy constructor

//Function changes the input of integers to strings, and returns it!
string FractionClass::ToString()const {
	if (numerator / denominator == 0)return to_string(numerator) + "/" + to_string(denominator);

	else return to_string(numerator / denominator) + " " + to_string(numerator % denominator) + "/" + to_string(denominator);
}//End fraction ToString! 

// Destructor seting the values to default
FractionClass::~FractionClass() {
	//cout << "\nThe destructor has been called(Numerator was set to 0, Denominator was set to 1)! " << endl;
	countObj--;
	ResetFraction();
	//system("pause");
}//End Destructor FractionClass!
 

//Function purpose to dynamically allocate an array of pointers, to hold a table of multiplied fractions!
void FractionTable(FractionClass**&fracArray, int den)
{
	fracArray = nullptr;
	const int arraySize = den * den;	
	int num = 0;
	try {

		fracArray = new FractionClass * [arraySize] {nullptr};

		for (int x = 1; x < den; x++) //setting up "row" 0
		{
			fracArray[x] = new FractionClass(x, den);

		}
		for (int i = den; i < arraySize; i = i + den) //set up the first column
		{
			fracArray[i] = new FractionClass(++num, den);
		}
		

		for (int a = 1; a < den; a++)//Seting up multiplication!
		{
			for (int i = 1; i < den; i++)
			{
				fracArray[den * a + i] = new FractionClass(FractionClass(a, den) * FractionClass(i, den));
				
			}
			
		}
	
	}//End try Block
	catch (bad_alloc& ex) {
		
		cout << "Exception: " << ex.what() << endl;
	    DeallocateMem(fracArray, den);

	}
	
}//End function MultiplyFractions()

//Function purpose to print a table of multiplied fractions to the screen
void PrintFracTable(FractionClass* fracArray[], int den) {
	cout << "\t";
	for (int x=1; x < den*den; x++)
	{
		if (x % den==0) cout << endl; 
		cout << *fracArray[x] << "\t";

	}
}//End function PrintFracTable()

//Function purpose to dealocate memory of fracArray!
void DeallocateMem(FractionClass* fracArray[] , int den) {
	int deletedObj = 0;
	if (fracArray != nullptr)
	{
		for (int x = 0; x < den * den; x++)
		{
			if (fracArray[x] != nullptr)
			{
				delete fracArray[x];
				fracArray[x] = nullptr;
				deletedObj++;
			}

		}
		cout << "Objects deleted: " << deletedObj;
		delete[] fracArray;
		fracArray = nullptr;
	}
	}//End function dealocaateMem ()



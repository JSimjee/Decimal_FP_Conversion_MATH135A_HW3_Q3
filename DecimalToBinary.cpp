#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

string DivisionAlgorithmForBinaryRepresentation(long long int originalNumber, int base) {
  vector<int> integerPartInBinary;
  int remainder = 0;
  while (originalNumber != 0) { // Calculate originalNumbers's binary form and push it to integerPartInBinary, with the MSB being the last bit in the array 
    remainder = originalNumber % base;
    integerPartInBinary.push_back(remainder);
    originalNumber /= base;
  }

  // We pushed to integerPartInBinary with the MSB as the final bit in the array, but since the MSB should be the first bit in the array because that's how binary numbers are written, we reverse the vector
  reverse(integerPartInBinary.begin(), integerPartInBinary.end());

  string returnString;
  for (int i = 0; i < integerPartInBinary.size(); i++) {
    returnString.push_back(integerPartInBinary.at(i) + 48);
  }
  return returnString;
}

string MultiplicationAlgorithmForBinaryRepresentation(long long int originalNumber, int base, int digitsOfFractionalPart) {
  int nextDigitForFractionalPart = 0;

  // Since fractionalPart is stored as an integer and not as a decimal number, we cannot compare fractionalPart against 1 as we would normally. 
  // We can compare against a power of 10 with n zeros, where n is the size of our fractionalPartString. 
  // For example: To evaluate 3654, we will compare against 10000, multiplying by 2 and subtracting 1 as needed. 
  long long int powerOfTenForDivision = pow(10, digitsOfFractionalPart);
  // cout << powerOfTenForDivision << '\n';
  vector<int> fractionalPartInBinary;
  while (originalNumber != 0) {
    originalNumber *= base;
    if (originalNumber>= powerOfTenForDivision) {
      nextDigitForFractionalPart = originalNumber / powerOfTenForDivision;
      originalNumber = originalNumber % powerOfTenForDivision;
    }
    else {
      nextDigitForFractionalPart = 0;
    }
    fractionalPartInBinary.push_back(nextDigitForFractionalPart);
    // cout << originalNumber<< '\n';
  }

  string returnString;
  for (int i = 0; i < fractionalPartInBinary.size(); i++) {
    returnString.push_back(fractionalPartInBinary.at(i) + 48);
  }
  return returnString;
}


int main() {
  unsigned char remainder = 0;
  unsigned char sign = '0';
  cout << "Enter a decimal form (e.g. 3960.28010) and press Enter: \n";
  string inputNumber;
  cin >> inputNumber;
  cout << "Enter the base you want to convert to: \n";
  int base;
  cin >> base;

  /*
  1. Separate integer and fractional parts into separate integers
  2. Perform division and multiplication steps respectively
  3. Create a vector of 0s and 1s for each part.
  4. Move the decimal point 'e' times from the integer vector, and then concatenate them for a final vector.
  5. Generate the final size-32 vector with your sign, exponent, and mantissa (without a leading zero)

  Don't worry about the integer part not fitting into your mantissa, assume the input number will fit.
  */

  // Put all numbers before the decimal point into a string
  string integerPartString;
  int i;
  long long int integerPart = 0;

  for (i = 0; i < inputNumber.size(); i++) { // inputNumber could not have a decimal at all
    if (inputNumber.at(i) != '.') {
      integerPartString.push_back(inputNumber.at(i));
    }
    else {
      break;
    }
  }
  // Convert integerPart to an integer so that we can perform division on it
  if (integerPartString.at(0) == '-') {
    integerPart = stoi(integerPartString.substr(1,integerPartString.size() - 1));
  }
  else {
    integerPart = stoi(integerPartString);
  }
  

  i++; // Increment i so we skip the decimal point before adding numbers to fractionalPartString
  // Take the numbers in your input string after the decimal point, put this fractional part in a new string
  string fractionalPartString;
  for (i; i < inputNumber.size(); i++) { // inputNumber could not have a decimal at all
    fractionalPartString.push_back(inputNumber.at(i));
  }
  // Convert fractionalPart to an integer so that we can perform multiplication on it
  int fractionalPart = stoi(fractionalPartString);

  cout << "Converting " << integerPartString << '.' << fractionalPartString << " to single-precision floating-point representation.\n";

  // We will store the binary representation of our integer part in integerPartString, so let's clear it of the decimal representation
  integerPartString = DivisionAlgorithmForBinaryRepresentation(integerPart, base);
  
  // cout << integerPartString << '.' << fractionalPart << '\n';

  cout << "size of fractionalPartString: " << fractionalPartString.size() << '\n';
  fractionalPartString = MultiplicationAlgorithmForBinaryRepresentation(fractionalPart, base, fractionalPartString.size());

  cout << "Integer part in binary: " << integerPartString << '\n';
  cout << "Fractional part in binary: " << fractionalPartString << '\n';
  cout << inputNumber << " in base " << base << " is " << integerPartString + fractionalPartString << ".\n";


  if (base != 2) {
    return 0;
  }
  // If we're not converting to base 2, we cannot convert to floating point representation, due to the leading digit not having a specific value implied anymore. 
  int exponent = integerPartString.size() - 1;

  string mantissa = integerPartString.substr(1, integerPartString.size() - 1) + fractionalPartString; // The mantissa is our integer and fractional parts in binary, with the leading 1 removed since it is implied
  if (mantissa.size() < 23) { // Add trailing zeros to the mantissa so you have a full 32-bit number
    while (mantissa.size() < 23) {
      mantissa.push_back('0');
    }
  }
  else if (mantissa.size() > 23) { // Remove trailing zeros from the mantissa so you only have 32-bits in the output
    mantissa = mantissa.substr(0, 22);
  }
  
  if (inputNumber.at(0) == '-') {
    sign = '1';
  }
  
  string exponentInOutput = DivisionAlgorithmForBinaryRepresentation(exponent + 127, 2);
  if (exponentInOutput.size() < 8) {
     while (exponentInOutput.size() != 8)  {
      exponentInOutput.push_back('0');
     }
  }
  else if (exponentInOutput.size() > 8) {
    exponentInOutput = exponentInOutput.substr(0, 7);
  }
  cout << "Final representation: \n" 
  << "Sign: " << sign << '\n'
  << "Exponent: " << exponentInOutput << '\n'
  << "Mantissa: " << mantissa << '\n';

  return 0;
}
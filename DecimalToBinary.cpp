#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main() {
  unsigned char remainder = 0;
  cout << "Enter a decimal form (e.g. 3960.28010) and press Enter: \n";
  string inputNumber;
  cin >> inputNumber;

  /*
  1. Separate integer and fractional parts into separate integers
  2. Perform division and multiplication steps respectively
  3. Create a vector of 0s and 1s for each part.
  4. Move the decimal point 'e' times from the integer vector, and then concatenate them for a final vector.
  5. Generate the final size-32 vector with your sign, exponent, and mantissa (without a leading zero)

  Don't worry about the integer part not fitting into your mantissa, assume the input number will fit.
  */

  string integerPartString;
  int i;
  for (i = 0; i < inputNumber.size(); i++) { // inputNumber could not have a decimal at all
    if (inputNumber.at(i) != '.') {
      integerPartString.push_back(inputNumber.at(i));
    }
    else {
      break;
    }
  }
  int integerPart = stoi(integerPartString);
  integerPartString.clear();

  i++;
  string fractionalPartString;
  for (i; i < inputNumber.size(); i++) { // inputNumber could not have a decimal at all
    fractionalPartString.push_back(inputNumber.at(i));
  }
  fractionalPartString.clear()
  int fractionalPart = stoi(fractionalPartString);

  cout << "Converting " << integerPartString << '.' << fractionalPartString << " to single-precision floating-point representation.\n";


  vector<int> integerPartInBinary;
  while (integerPart != 0) { // Calculate integerPart's binary form and push it to integerPartInBinary, with the MSB being the first bit in the array 
    remainder = integerPart % 2;
    integerPartInBinary.push_back(remainder);
    integerPart /= 2;
  }
  reverse(integerPartInBinary.begin(), integerPartInBinary.end());

  for (i = 0; i < integerPartInBinary.size(); i++) {
    integerPartString.push_back(integerPartInBinary.at(i) + 48); // Add 48 to convert it to ASCII representation
  }



  cout << "Integer part in binary: " << integerPartString << '\n';



  return 0;
}
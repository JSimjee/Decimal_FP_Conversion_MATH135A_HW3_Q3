#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
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

  string integerPart;
  int i;
  for (i = 0; i < inputNumber.size(); i++) { // inputNumber could not have a decimal at all
    if (inputNumber.at(i) != '.') {
      integerPart.push_back(inputNumber.at(i));
    }
    else {
      break;
    }
  }

  i++;
  string fractionalPart;
  for (i; i < inputNumber.size(); i++) { // inputNumber could not have a decimal at all
    fractionalPart.push_back(inputNumber.at(i));
  }

  cout << "Converting " << integerPart << '.' << fractionalPart << "to single-precision floating-point representation.";


  vector<int> integerPartInBinary;
  for (i = 0; i < integerPart.size(); i++) {
    
  }

}
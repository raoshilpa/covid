//
//  main.cpp
//  Project 3
//
//  Created by Shilpa Rao on 1/30/21.
//

#include <iostream>
#include <string>
#include <cassert>
#include <cctype>
using namespace std;

bool isValidResultString(string results);

int positiveTests(string results); //return the total number of positive tests from all batches
    //add up #'s after '+'
int negativeTests(string results); //return the total number of negative tests from all batches
    //add up #'s after '-'
int totalTests(string results); //rturn the total number of tests being reported from all batches
    //add up all numbers after R and before the first positive/negative result
int batches(string results); //return the total number of batches being reported in the string
    //count all R's
bool validBatch(string results);
int extractNumber( string commands, size_t index, bool& isValid );

int main() {

    return(0);
   
}

int positiveTests(string results) {
//   If the parameter is a well-formed test result string, this function should return the total number of positive tests from all the batches being reported in the string.  If the parameter is not valid, return -1 .

    if (isValidResultString(results)) {
        int total = 0;
        string resultsPlus(" ");
        int index2 = 0;
        bool b = true;

        //String of positive tests only.
        for (int index = 0; index != results.length(); index++) { //looping through string
            if (results[index] == '+') {
                resultsPlus = results.substr(index + 1, results.size()-index);
            }
            
            //Sum up nmber of positive tests using extractNumber. Same functionality applies for totalTests and negativeTests.
            if (results[index] == '+') {
                int var = 0;
                var = extractNumber(resultsPlus, index2, b);
                total += var;
            }
            
        }

        return total;
        
    } else {
        
        return(-1);
        
    }

}

int negativeTests(string results) {
//   If the parameter is a well-formed test result string, this function should return the total number of positive tests from all the batches being reported in the string.  If the parameter is not valid, return -1 .

    if (isValidResultString(results)) {
        int total = 0;
        string resultsNeg(" ");
        int index2 = 0;
        bool b = true;

        for (int index = 0; index != results.length(); index++) { //looping through string
            if (results[index] == '-') {
                resultsNeg = results.substr(index + 1, results.size()-index);
            }
            
            if (results[index] == '-') {
                int var = 0;
                var = extractNumber(resultsNeg, index2, b);
                total += var;
            }
            
        }

        return total;
        
    } else {
        
        return(-1);
        
    }

}

int totalTests(string results) {
//  If the parameter is a well-formed test result string, this function should return the total number of tests being reported from all the batches in the string.  If the parameter is not a valid, return  -1.

    if (isValidResultString(results)) {
        int total = 0;
        string resultsTot(" ");
        int index2 = 0;
        bool b = true;

        for (int index = 0; index != results.length(); index++) { //looping through string
            if (results[index] == 'R') {
                resultsTot = results.substr(index + 1, results.size()-index);
            }
            
            if (results[index] == 'R') {
                int var = 0;
                var = extractNumber(resultsTot, index2, b);
                total += var;
            }
            
        }

        return total;
        
    } else {
        
        return(-1);
        
    }

}

int batches(string results) {
    
    if (isValidResultString(results)) {
        
        //This will be the total number of R's.
        int rTotal = 0;
        for (int index = 0; index != results.length(); index++) {
            if (results[index] == 'R') {
                rTotal += 1;
            }
        }
        return rTotal;
        
    } else {
        return -1;
    }
    
}

bool isValidResultString(string results) {
    
    bool boolString = true;
    int rCount = 0;
    int arrayIndex = -1;

    if (results.length() < 6) {
        boolString = false;
        return boolString;
    }
    
    for (int index = 0; index != results.length(); index++) {
        
        //(Step 1) Strict check for bad characters, so that we can safely assume proper string in order for array to work. Array then checks each batch.
        if (results[index] != 'R' && results[index] != '+' && results[index] != '-' && results[index] != '0' && results[index] != '1' && results[index] != '2' && results[index] != '3' && results[index] != '4' && results[index] != '5' && results[index] != '6' && results[index] != '7' && results[index] != '8' && results[index] != '9') {
         
            boolString = false;
            return boolString;
            
        }

        //This is a count of all the 'R' values in the string. The array is then formed with a length corresponding to the number of 'R' values.
        if (results[index] == 'R') {
            rCount += 1;
        }

    }

    if (rCount < 1) {
        
        boolString = false;
        return boolString;
        
    }

    //String my_array[num_batches]; will be replaced with std::vector<string>
    //string arr[rCount]; //Make an array whose size matches the number of 'R' characters in the string.
    string* arr;
    arr = new string[rCount];
    
    //(Step 2) This code creates an array that holds each individual batch. It does so by creating a new string, looping through the for loop character by character.
    // When we reach an 'R', assuming a perfect string, it creates accesses a new place in the array.
    // The array is as large as the number of 'R's. The assumption that the inputted string is perfect should be taken care of by the
    //earlier check for bad characters, and the validBatch function.
    for (int index = 0; index != results.length(); index++) {

        if (results[index] != 'R')  {
            
            arr[arrayIndex] += results[index];
            
        } else { //if it IS R, you increase index for the array by 1.
            
            arrayIndex += 1; //should only increase if we hit an R.
            arr[arrayIndex] += 'R'; //adds an R to the individual batch
            
        }

    }
    
    if (arrayIndex < 0) {
        
        boolString = false;
        return boolString;
        
    }
        
    //(Step 3) Calling the validBatch function on each element of array
    for (int index = 0; index != arrayIndex + 1; index++) {
        
        if (validBatch(arr[index]) == false) {
            boolString = false;
            return boolString;
        }
        
    }
    
    //Wiping the dynamic array.
    delete[] arr;
    return boolString;
 
}


bool validBatch(string results) {
    
    bool boolBatch = true;
    int plusTotal = 0;
    int minusTotal = 0;
    
    //Get plusTotal and minusTotal, and check for no leading zeroes in the positive/negative batches.
    for (int index = 0; index != results.length(); index++) {
        if (results[index] == '+') {
            plusTotal += 1;
            if (results[index + 1] == '0') {
                //Explaining the below logic: these all have to be false in order for the boolean to be false. If one is true, then
                //it's a valid case and we never enter the if.
                //if the size of index + 1 is equal to the length of the string, we are at the end of the string.
                //Thus, it is okay to have a 0 in that place.
                if (results[index + 2] != '-' && results[index + 2] != 'R' && index + 2 != results.length()) {
                    //it's fine if it's '-'      it's fine if it's an 'R'     it's fine if it's the end of the string
                    //the character after the 0 HAS TO BE either R or -. If it is neither, false.
                    boolBatch = false;
                    return boolBatch;
                }
            }
        }
        
        if (results[index] == '-') {
            minusTotal += 1;
            if (results[index + 1] == '0') {
                if (results[index + 2] != '+' && results[index + 2] != 'R' && index + 2 != results.length()) {
                    boolBatch = false;
                    return boolBatch;
                }
            }
        }
        
    }
    
    //the string cannot be empty
    if (results.length() == 0) {
        boolBatch = false;
        return boolBatch;
    }
    //the zeroeth place in the string must be 'R'
    else if (results[0] != 'R') {
        boolBatch = false;
        return boolBatch;
    }
    //the first place in the string must be a non-zero number.
    else if (results[1] == '0') {
        boolBatch = false;
        return boolBatch;
    }
    else if (plusTotal != 1) {
        boolBatch = false;
        return boolBatch;
    }
    else if (minusTotal != 1) {
        boolBatch = false;
        return boolBatch;
    }
    
    //now we have to work on making sure the numbers add up.
    //we've verified that the string has valid places, no leading zeroes, starts with R, just one + or -.
    string resultsR;
    string resultsPlus;
    string resultsMinus;
    
    //obtaining three new strings to feed into extractNumber.
    for (int index = 0; index != results.length(); index++) { //looping through string
        if (results[index] == 'R') {
            //from the R to end (but extractNumber will cut off at +).
            resultsR = results.substr(index + 1, results.size()-index);
        }
        if (results[index] == '+') {
            //from the + to end (or, extractNumber will cut off at -).
            resultsPlus = results.substr(index + 1, results.size()-index);
        }
        if (results[index] == '-') {
            //from the - to end (or, extractNumber will cut off at +).
            resultsMinus = results.substr(index + 1, results.size()-index);
        }
        }
    
    //feed new strings into extractNumber to get the digits. digits of resultMinus + resultsPlus must == resultsR.
    
    size_t index;
    index = 0;
    bool b = true;
    int digitsR;
    int digitsPlus;
    int digitsMinus;
    
    digitsR = extractNumber( resultsR, index, b );
    digitsPlus = extractNumber( resultsPlus, index, b );
    digitsMinus = extractNumber( resultsMinus, index, b );
    
    if (digitsPlus + digitsMinus != digitsR) {
        
        boolBatch = false;
        return boolBatch;
        
    }
    
    return boolBatch;
    
}

int extractNumber( string commands, size_t index, bool& isValid )
{
    // track the integer value found
    int quantity( 0 );
    // the number can't start with a zero!

    // the number should be made up of digits
    while( index < commands.length() && (commands.at(index) >= '0' && commands.at(index) <= '9') ) {
    // extract one digit and add it to the cumulative value
    // held in quantity "123" ---> 123
    int digit = commands.at( index ) - '0';
    quantity = quantity * 10 + digit;
    index = index + 1;
    }

    // once we run out of digits to consume, the cumulative quantity
    // must not still be zero
    isValid = (quantity != 0);
    return( quantity );

}

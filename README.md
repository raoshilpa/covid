This was a project done for a class of mine. The objective was to parse covid-19 test data from a simulated sensor input.
My program had to enforce strict data validations and perform data analysis at the end of the validation.
Valid input consists of valid consecutive batches in a string. 

A valid batch could be: "R5+3-2", with 5 total tests, 3 positive results, and 2 negative results.
A valid string could be: "R5-3+2R8-6+2R2+2-0"

Data validation:

(1) A batch Of must begin With the character 'R'.

(2) A batch of results must report both a positive and negative number of test results with '+' and '-' signs in either order.

(3) No leading zeros are allowed in any numeric value being reported.

(4) The total number of tests in a batch must equal the number of positive and negative tests.

(5) A single result string may include multiple batches of results.


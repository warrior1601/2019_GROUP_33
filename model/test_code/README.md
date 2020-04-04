# Test Code for the Model Realizer

This code is automatically ran by Travis-CI with a build status posted on the front page of this repository.

The test can be manually ran from the `RunAllTestCode.bat` file using the terminal window. 

### Important Notes

  * To ensure accuracy the Observer uses its own double equality function. 
  * The Observer tests the machines precision to ensure it is capable of handling double precision to the required value. 
  * It is highly suggested you `DO NOT` increase the default value above `1e-13` the value can be lowered to the machines value for `DBL_EPSILON`. 
  * For more information visit [DBL_EPSILON](https://en.wikipedia.org/wiki/Machine_epsilon) or [More Information](http://www.cplusplus.com/reference/cfloat/). 
  * The value for DBL_EPSILON can be changed in the file `double_equality_finction.cpp` line `51` :warning: Changing this value can have drastic effects on the operation of the Observer.


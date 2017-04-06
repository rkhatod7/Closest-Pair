// Radhika Khatod
// CS 130B Winter 2017 Project 1
// Implement closest pair algorithm

#include <stdio.h>
#include <cstdlib>
#include <cfloat>
#include <cmath>
#include <limits>
#include <float.h>
#include <cstring>
#include <string>
#include <iomanip>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <iostream>



using namespace std;
// use a template to create 2 classes   
// should use either pairs or just struct
// try doing it with struct                                                                                                                  
template <class T1, class T2>


// use a myStruct -                                                                                                                                          

struct myStruct {
  T1 x;
  T2 y;
  myStruct() { }

  myStruct(T1 a, T2 b) {
    x = a;
    y = b;
  }
};


//HELPER FUNCTIONS:

//use bool to sort x vector in ascending order
// true if a.x < b.x
// if they're equal then check a.y < b.y

bool xSort(myStruct<double, double> a, myStruct<double, double> b){
        double difference = a.x -b.x;
        // if a < b then it less than/equal to -1 -> true
        if(difference <= -1e-7)
                return true;
        if(difference >= 1e7)
                return false;
        //if they are equal then:
        return a.y < b.y;
}

// do the same thing as above but with y
bool ySort(myStruct<double, double> a, myStruct<double, double> b){
        double difference = a.y -b.y;
        // if a < b then it less than/equal to -1 -> true
        if(difference <= -1e-7)
                return true;
        if(difference >= 1e7)
                return false;
        //if they are equal then:
        return a.x < b.x;
}


string trimExcess(const string& str) {
        size_t firstSpot = str.find_first_not_of(' ');
        if(string::npos == firstSpot) {
                return str;
        }
        size_t lastSpot = str.find_last_not_of(' ');
        return str.substr(firstSpot, (lastSpot - firstSpot + 1));
}


//function to calculate the distance between points
// sqrt((ax - bx)^2 + (ay - by)^2)
double pointDistance(myStruct<double, double> a, myStruct<double, double> b) {
        //  double dist = sqrt((pow(a.x - b.x), 2.0) + pow((a.y - b.y), 2.0));
        double dist = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
        return dist;
}



// function to compare doubles and return difference btwn them
int compDoubles(double x, double y) {
        double difference = x - y;
        if(difference > 0)
                return 1; // 1 if x > y
        if (difference < 0)
                return -1; // -1 if x < y
        return 0; // x and y are equal
}


// function to compare points
int compPoints(myStruct<double, double> a, myStruct<double, double> b) {
        int xDiff = compDoubles(a.x, b.x);
        int yDiff = compDoubles(a.y, b.y);
        if(xDiff == 0)
                return yDiff;
        else
                return xDiff;
}

// function to compare pairs
int compPairs(myStruct<myStruct<double, double>, myStruct<double, double> > a, myStruct<myStruct<double, double>, myStruct<double, double> > b)
{
        int xDiff = compPoints(a.x, b.x);
        int yDiff = compPoints(a.y, b.y);
        if(xDiff == 0)
                return yDiff;
        else
                return xDiff;
}


// compare points w bool
// true if a.x < b.x or a.y < b.y
bool boolPoint(myStruct<double, double> a, myStruct<double, double> b){
        int xDiff = compDoubles(a.x, b.x);
        if (xDiff == 1) // a.x > b.x
                return false;
        if(xDiff == -1) // a.x < b.x
                return true;
        int yDiff = compDoubles(a.y, b.y);
        if(yDiff == -1) // a.y < b.y
        {
                return true;
        }
        return false;
}


// bool compare pairs

// BRUTE force algorithm - first option
vector<myStruct<myStruct<double, double>, myStruct<double, double > > >
bruteForce(vector<myStruct<double, double> > pairs) {

        vector<myStruct<myStruct<double, double>, myStruct<double, double> > > returnVal;
        double closestDist = DBL_MAX/2.0;

        for(vector<myStruct<double, double> >::iterator i = pairs.begin(); i != pairs.end(); i++) {
                for(vector<myStruct<double, double> >::iterator n = i+1; n!= pairs.end(); n++){
                        double distance = pointDistance(*i, *n);
                        double compare = compDoubles(closestDist, distance);

                        if(compare == 0) {
                                returnVal.push_back(myStruct<myStruct<double, double>, myStruct<double, double> >(*i, *n));
                        }
                        else if(compare == 1){
                                returnVal.clear();
                                returnVal.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*i, *n));
                                closestDist = distance;
                        }
                }
        }
        return returnVal;
        // I LEFT OFF HERE!!!!!!!!!!!!!
}


// BASIC ALGORITHM
std::vector<myStruct<myStruct<double, double>, myStruct<double, double> > >basicAlg(vector<myStruct<double, double> >::iterator startX, vector<myStruct<double, double> >::iterator endX){
  
  std::vector<myStruct<myStruct<double, double>, myStruct<double, double> > > returnVect;
  size_t vectSize = endX -startX;

  //First base case: if theres only 2 points in the vector, then you can just return those 2 points
  // theres 2 points if vectSize = 2
  // since theres only 2 points, return *startX and *startX+1
  if(vectSize == 2){
    //printf("vect size is 2\n");
    returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*startX, *(startX+1)));
    return returnVect;
  }

  // Second base case: if theres only 3 points in vector, dont need to split 
  // can just check distance between points 1 and 2, points 2 and 3, points 1 and 3 and return the smallest 
  if(vectSize == 3){     
    //printf("vect size is 3");
    double dist1, dist2, dist3, min1, finalMin;

    dist1 = pointDistance(*startX, *(startX+1)); //distance btwn points 1 and 2
    dist2 = pointDistance(*startX, *(startX+2)); //distance btwn points 1 and 3
    dist3 = pointDistance(*(startX+1), *(startX+2)); //distance between points 2 and 3

    //min1 = min(dist2, dist3); //is distance between 1 and 3 or distance between 2 and 3 smaller?
    finalMin = min(dist1, min(dist2,dist3)); // is distance between 1 and 2 smaller than either of those?

    //now i need to check finalMin against dist1,2 and 3
    //if finalMin is equal to dist1
    if(compDoubles(finalMin, dist1) == 0){ 
      returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*startX, *(startX+1)));
    }
    //if finalMin equals dist2
    if(compDoubles(finalMin, dist2) == 0){
      returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*startX, *(startX+2)));
    }
    //if finalMin equals dist3
    if(compDoubles(finalMin, dist3) == 0) {
      returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*(startX+1), *(startX+2)));
    }
    return returnVect;
  }

  //if i've gotten here, then the vector is larger than 3
  // need to start splitting

  size_t halfSize = vectSize/2;

  double xMid = (startX + halfSize) -> x;
  double yMid = (startX + halfSize) -> y;

  //need to create a vector for left side of mid
  // and one for right side of mid
  //call it recursively 
  vector< myStruct<myStruct<double, double>, myStruct<double, double> > >leftHalf;
  vector< myStruct<myStruct<double, double>, myStruct<double, double> > >rightHalf;

  leftHalf = basicAlg(startX, startX + halfSize);
  rightHalf = basicAlg(startX+halfSize, endX);

  double minDistance, leftDistance, righDistance;

  // make vector for min values
  vector<myStruct<myStruct<double, double>, myStruct<double, double> > > minVect;
  vector<myStruct<double, double> > tempVect;

  leftDistance = pointDistance(leftHalf[0].x, leftHalf[0].y);
  righDistance = pointDistance(rightHalf[0].x, rightHalf[0].y);

  if(compDoubles(leftDistance, righDistance) == 1) //right is smaller
  {
    minDistance = righDistance;
    minVect = rightHalf;
  }
  else if(compDoubles(leftDistance, righDistance) == -1) //left is smaller
  {
    minDistance = leftDistance;
    minVect = leftHalf;
  }
  //else the distances are equal
  else{
    minVect = leftHalf;
    minDistance = min(righDistance, leftDistance);
    for(vector<myStruct<myStruct<double, double>, myStruct<double, double> > >::iterator iter = rightHalf.begin(); iter != rightHalf.end(); iter++){
      minVect.push_back(*iter);
    } 
  }
  for(vector<myStruct<double,double> >::iterator iter = startX; iter != endX; iter++){
    if(abs(iter -> x - xMid) < (minDistance + 1e-6)){
      tempVect.push_back(*iter);
    }
  }
  //sort the temp vector using y sort
  sort(tempVect.begin(), tempVect.end(), ySort);

  for(vector<myStruct<double, double> >::iterator iter = tempVect.begin(); iter != tempVect.end(); iter++){
    for(vector<myStruct<double, double> >::iterator iter2 = iter+1; iter2 != tempVect.end() && (iter2->y < (iter ->y + minDistance+1e-6));iter2++){
      double tempDistance = pointDistance(*iter, *iter2);

      //check the new distance
      //in the first case tempDistance is smaller than minDistance
      if(compDoubles(tempDistance, minDistance) == -1){
        minDistance = tempDistance;
        minVect.clear();
        minVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> >(*iter, *iter2));
      }
      else if(compDoubles(tempDistance, minDistance) == 0 && !(compDoubles(iter->x, iter2->x)==0 && compDoubles(iter
        ->y, iter2->y)==0)){
        minVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> >(*iter, *iter2));
      }
    }
  }
  return minVect;

}

//OPTIMAL ALGORITHM
// optimal needs to deal w y as well as x
// so the parameters need to have y options AND x options
// pre-sort the points just once by x coordinates
// and just once by y coordinates
//take-away: SORT ONLY TWICE IN THIS! 
vector<myStruct<myStruct<double, double>, myStruct<double, double> > > optimalAlg(
  vector<myStruct<double, double> >::iterator startX, 
  vector<myStruct<double, double> >::iterator endX,
  vector<myStruct<double, double> >::iterator startY, 
  vector<myStruct<double, double> >::iterator endY)
{
  vector<myStruct<myStruct<double, double>, myStruct<double, double> > > minVect;
  // need to do similar declarations to what i did in basic alg
  //create return vector
  vector<myStruct<myStruct<double, double>, myStruct<double, double> > > returnVect;
  // find the size
  size_t vectSize;
  vectSize = endX - startX;
  size_t ySize = endY - startY;
  if((vectSize != (endY - startY))){
    return returnVect;
  }
  //do the same thing for if size = 1
  if(vectSize == 2){
    returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> >(*startX, *(startX+1)));
    return returnVect;
  }
 //do the same thing for if size = 3
 if(vectSize == 3){
    double dist1, dist2, dist3, min1, finalMin;

    dist1 = pointDistance(*startX, *(startX+1)); //distance btwn points 1 and 2
    dist2 = pointDistance(*startX, *(startX+2)); //distance btwn points 1 and 3
    dist3 = pointDistance(*(startX+1), *(startX+2)); //distance between points 2 and 3

    //min1 = min(dist2, dist3); //is distance between 1 and 3 or distance between 2 and 3 smaller?
    finalMin = min(dist1, min(dist2,dist3)); // is distance between 1 and 2 smaller than either of those?

    //now i need to check finalMin against dist1,2 and 3
    //if finalMin is equal to dist1
    if(compDoubles(finalMin, dist1) == 0){ 
      returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*startX, *(startX+1)));
    }
    //if finalMin equals dist2
    if(compDoubles(finalMin, dist2) == 0){
      returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*startX, *(startX+2)));
    }
    //if finalMin equals dist3
    if(compDoubles(finalMin, dist3) == 0) {
      returnVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*(startX+1), *(startX+2)));
    }
    return returnVect;
 }
 //make a variable for half size like in basic
 size_t halfSize = (vectSize/2);

 //same variable and vector declarations as above
 double xMid = (startX + halfSize) -> x;
 double yMid = (startX + halfSize) -> y;

  //need to create a vector for left side of mid
  // and one for right side of mid
  //call it recursively 
  vector< myStruct<double, double> >leftHalf;
  vector< myStruct<double, double> >rightHalf;

  //load points into the left and right halves
  for(vector<myStruct<double, double> >::iterator iter = startY; iter != endY; iter++){
    if(compDoubles(iter->x, xMid) == 0){
      if(compDoubles(iter->y, yMid) == -1){
        leftHalf.push_back(*iter);
      }
      else{
        rightHalf.push_back(*iter);
      }      
    }
  else if(compDoubles(iter->x, xMid) == -1){
    leftHalf.push_back(*iter);
  }
  else{
    rightHalf.push_back(*iter);
  }
}
  //sort y values
  if(leftHalf.size() != rightHalf.size()){
    leftHalf.clear();
    rightHalf.clear();
    for(vector<myStruct<double, double> >::iterator iter = startX; iter != startX+halfSize; iter++){
      leftHalf.push_back(*iter);
    }
    for(vector<myStruct<double, double> >::iterator iter = startX+halfSize; iter != endX; iter++){
      rightHalf.push_back(*iter);
    }
    sort(rightHalf.begin(), rightHalf.end(), ySort);
    sort(leftHalf.begin(), leftHalf.end(), ySort);
  }
//recursively call the function again on each half
  vector<myStruct<myStruct<double, double>, myStruct<double, double> > > newLeft =optimalAlg(startX, startX + halfSize, leftHalf.begin(), leftHalf.end());
  vector<myStruct<myStruct<double, double>, myStruct<double, double> > > newRight =optimalAlg(startX+halfSize, endX, rightHalf.begin(), rightHalf.end());
  

  //do distance calculations same as above
  double rightDistance, leftDistance, minDistance;

  rightDistance = pointDistance(newRight[0].x, newRight[0].y);
  leftDistance = pointDistance(newLeft[0].x, newLeft[0].y);

  //start comparing right and left distances
  if(compDoubles(leftDistance, rightDistance) == 1){
    minDistance = rightDistance;
    minVect = newRight;
  }
  if(compDoubles(leftDistance, rightDistance) == -1){
    minDistance = leftDistance;
    minVect = newLeft;
  }
  else{
    minDistance = min(rightDistance, leftDistance);
    minVect = newLeft;
    vector<myStruct<myStruct<double, double>, myStruct<double, double> > >::iterator iter = newRight.begin();
    for(vector<myStruct<myStruct<double, double>, myStruct<double, double> > >::iterator iter = newRight.begin(); iter != newRight.end(); iter++){
      minVect.push_back(*iter);
    }
  }

  //do the same temp vect stuff as above but include y this time
  vector<myStruct<double, double> > tempVect;
  
  for(vector<myStruct<double, double> >::iterator iter1 = startY; iter1 != endY; iter1++){
    if(abs(iter1->x -xMid) < (minDistance+1e-6)){
      tempVect.push_back(*iter1);
    }
  }
  vector<myStruct<double, double> >::iterator iter3 = tempVect.begin();
  vector<myStruct<double, double> >::iterator iter2 = iter3 +1;

  for(iter3 = tempVect.begin(); iter3 != tempVect.end(); iter3++){
    for(iter2=iter3+1; iter2!=tempVect.end() && (iter2->y < (iter3->y+minDistance+1e-6)); iter2++){
      double distance = pointDistance(*iter3, *iter2);
      //check to see if this value is lower than current minDistance
      if(compDoubles(distance, minDistance) == -1){
        minDistance = distance;
        minVect.clear();
        minVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> > (*iter3, *iter2));
      }
      if(compDoubles(distance, minDistance) == 0 && !(compDoubles(iter3->x, iter2->x)==0) && compDoubles(iter3->y, iter2->y)==0){
        minVect.push_back(myStruct<myStruct<double, double>, myStruct<double, double> >(*iter3, *iter2));
      }
    }
  }
  return minVect;
 //HERE
}

//using this in main to sort the pairs before i put them into functions
bool lastSort(myStruct<myStruct<double, double>, myStruct<double, double> > a, myStruct<myStruct<double, double>, myStruct<double, double> > b){
  int xDiff, yDiff;
  xDiff = compPoints(a.x, b.x);
  yDiff = compPoints(a.y, b.y);

  if(xDiff == 1){
    return false;
  }
  if(xDiff == -1){
    return true;
  }
  if(yDiff == -1){
    return true;
  }
  return false;
}



int main(int argc, char ** argv){
        cout.precision(7);
        if(argc != 2){
	        cout << "You must input either: 'brute', 'basic', or 'optimal'" << endl;
                return 1;
        }
        string input(argv[1]);

        string inputLine;

        // NK: moving vectors here
        vector<myStruct<double, double> > xCoord;
        vector<myStruct<double, double> > yCoord;
        
        //while loop that goes through until at end of input file
        while(!cin.eof()) {
                getline(cin, inputLine);
                //REWRITE THIS BREAK STATEMENT
                if(cin.eof()) {
                        break;
                }

                inputLine = trimExcess(inputLine);
                // use c_str to return a pointer to input string
                const char* strPointer = inputLine.c_str();

                //need to convert the inputted values from string to type double
                // need to convert x value and y value
                char *xVal;
                char * yVal;

                // NK: you have defined xCoord, yCoord inside the loop scope
                // you need to move them up. So change these
                // vector<myStruct<double, double> > xCoord;
                // vector<myStruct<double, double> > yCoord;

                double xPoint  = strtod(strPointer, &xVal);
                if(*xVal != ' '){
                        continue;
                }

                double yPoint = strtod(xVal, &yVal);
                if(*yVal){
                        continue;
                }

                //use push_back to add x element to end of vector
                // NK: you do not have x, and y defined here
                // I think you want xPoint, yPoint 
                // Change this to --- xCoord.push_back(myStruct<double, double>(x, y));
                // NK: fixed
                xCoord.push_back(myStruct<double, double>(xPoint, yPoint));
        }
        sort(xCoord.begin(), xCoord.end(), xSort);
        for(vector<myStruct<double, double> >::iterator iter = xCoord.begin(); iter != xCoord.end()-1; iter++){
          if(compPoints(*iter, *(iter+1))==0){
            xCoord.erase(iter+1);
          }
        }

        if(xCoord.size() < 2) {
          cout << "you must input at least 2 points" << endl;
          return 1;
        }

        //sort(xCoord.begin(), xCoord.end(), xSort);
        //how to delete duplicates??
        for(vector<myStruct<double, double> >::iterator iterator = xCoord.begin(); iterator != xCoord.end()-1; iterator++)
        {
                if(compPoints(*iterator, *(iterator+1)) == 0){
                        xCoord.erase(iterator+1);
                        iterator--;
                }
        }

        //ok now that i've removed duplicates i should call my pair sort function 
        //sort xCoord vector by pairs
        //sort(xCoord.begin(), xCoord.end(), lastSort);
        vector<myStruct<myStruct<double, double>, myStruct<double, double> > > returnVal;


        if(input == "brute") {
                returnVal = bruteForce(xCoord);
        }

        if(input == "basic" ){
          returnVal = basicAlg(xCoord.begin(), xCoord.end());
          if(returnVal.size() < 1){
            return 1;
          }
        }
        for(vector<myStruct<double, double> >::iterator iter = xCoord.begin(); iter != xCoord.end(); iter++){
          yCoord.push_back(myStruct<double, double>(iter->x, iter->y));
        }
        sort(yCoord.begin(), yCoord.end(), ySort);

        if(input == "optimal"){
          returnVal=optimalAlg(xCoord.begin(), xCoord.end(), yCoord.begin(), yCoord.end());
          if(returnVal.size() < 1){
            return 1;
          }
        }

    for(vector<myStruct<myStruct<double, double>, myStruct<double, double> > >::iterator iter = returnVal.begin();iter != returnVal.end(); iter++){
      if(compPoints(iter->x, iter->y) == 1){
        myStruct<double, double> tempX = iter->x;
        iter->x = iter->y;
        iter->y = tempX;
    }
  }
  sort(returnVal.begin(), returnVal.end(), lastSort);
  
  for(vector<myStruct<myStruct<double, double>, myStruct<double, double> > >::iterator iter = returnVal.begin();
      iter != returnVal.end() - 1;
      iter++){
    if(compPairs(*iter, *(iter+1)) == 0){
      returnVal.erase(iter + 1);
      iter--;
    }
  }
        double min = pointDistance(returnVal[0].x, returnVal[0].y);


        cout << "closest pair distance: " << fixed << setprecision(7) << min << defaultfloat << endl;

        // loop through to print out the coordinates
        vector< myStruct< myStruct<double, double>, myStruct <double, double> > >::iterator it = returnVal.begin();
        for(it = returnVal.begin(); it != returnVal.end(); it++){
          cout << "(" << it -> x.x << ", " << it -> x.y << ") " << "(" << it -> y.x <<", " << it -> y.y << ")" << endl;

        }

        //LEFT OFF HERE
        // NK: main has return type int
        // ---- return returnVal;
        return 0;
} 

/**
 * Created by Henry Song
 * for CS492 Research project
 *
 * Professor: Dr. Zou
 */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

/* Function Headers */
vector<double> readData();
vector<int> findXData(int);
vector<double> findXY(vector<int>, vector<double>);
vector<double> findXY(vector<double>, vector<double>);
vector<double> powerVector(vector<int>, int);
double findSum(vector<int>);
double findSum(vector<double>);
void findLinearRegression(vector<int>, vector<double>);
void findQuadraticRegression(vector<int>, vector<double>);
void findFuturePrediction(double, double, double, int);
void findFuturePrediction(double, double, int);
void print(vector<double>);
void printLinear();
void printQuadratic();

/* Universal variables */
int size;
double m11, m12, m13, m14;
double m21, m22, m23, m24;
double m31, m32, m33, m34;
double L, L1, L2, L3;
double a, b, c;
double slope, yIntercept;

int main() {
    cout << "Linear & Quadratic Regression Algorithms [written in C++]" << endl;
    cout << "By Henry Song" << endl;
    cout << endl;

    int option, option2;
    cout << "Enter 1 to use hard-coded data for average annual temperatures from 2008 to 2018" << endl;
    cout << "Enter 2 to use user-input data" << endl;
    cout << "Select option: ";
    cin >> option;
    cout << endl;

    cout << "Enter 1 to calculate Linear Regression" << endl;
    cout << "Enter 2 to calculate Quadratic Regression" << endl;
    cout << "Select option: ";
    cin >> option2;
    cout << endl;

    if(option == 1){
        int x[] = {1,2,3,4,5,6,7,8,9,10,11};
        vector<int> xData (x, x+sizeof(x)/sizeof(int));
        double y[] = {27.8,27.8,27.8,27.8,27.8,28.3,28.1,27.8,28.4,28.2,28.5};
        vector<double> yData (y, y+sizeof(y)/sizeof(double));
        size = xData.size();
        print(yData);
        if(option2 == 1){
            findLinearRegression(xData, yData);
            printLinear();
        }else if(option2 == 2){
            findQuadraticRegression(xData, yData);
            printQuadratic();
        }

    }else if(option == 2) {
        vector<double> yData = readData(); //y axis data
        vector<int> xData = findXData(yData.size()); //x axis data
        size = xData.size();
        if(option2 == 1){
            findLinearRegression(xData, yData);
            printLinear();
        }else if(option2 == 2){
            findQuadraticRegression(xData, yData);
            printQuadratic();
        }
    }

    return 0;
}

/**
 * Calculates the Linear Regression Line
 * @param xData - vector of integer values representing data on the x-axis
 * @param yData - vector of integer values representing data on the y-axis
 */
void findLinearRegression(vector<int> xData, vector<double> yData){
    m11 = findSum(powerVector(xData, 2));
    m12 = findSum(xData);
    m13 = findSum(findXY(xData, yData));
    m21 = m12;
    m22 = (double)xData.size();
    m23 = findSum(yData);

    L = (m11*m22) - (m12*m21);
    L1 = (m13*m22) - (m12*m23);
    L2 = (m11*m23) - (m21*m13);

    slope = L1/L;
    yIntercept = L2/L;
}

/**
 * Calculates the Quadratic Regression Line
 * @param xData - vector of integer values representing data on the x-axis
 * @param yData - vector of integer values representing data on the y-axis
 */
void findQuadraticRegression(vector<int> xData, vector<double> yData){
    m11 = findSum(powerVector(xData, 4));
    m12 = findSum(powerVector(xData, 3));
    m13 = findSum(powerVector(xData, 2));
    m14 = findSum(findXY(powerVector(xData, 2), yData));

    m21 = m12;
    m22 = m13;
    m23 = findSum(xData);
    m24 = findSum(findXY(xData, yData));

    m31 = m13;
    m32 = m23;
    m33 = size;
    m34 = findSum(yData);

    L = (m11*m22*m33) - (m11*m23*m32) - (m12*m21*m33) + (m12*m23*m31) + (m13*m21*m32) - (m13*m22*m31);
    L1 = (m14*m22*m33) - (m14*m23*m32) - (m12*m24*m33) + (m12*m23*m34) + (m32*m24*m13) - (m34*m13*m22);
    L2 = (m11*m24*m33) - (m11*m23*m34) - (m14*m33*m21) + (m14*m23*m31) + (m13*m21*m34) - (m13*m24*m31);
    L3 = (m11*m22*m34) - (m11*m24*m32) - (m12*m34*m21) + (m12*m24*m31) + (m14*m21*m32) - (m14*m22*m31);

    a = L1/L;
    b = L2/L;
    c = L3/L;
}

/**
 * Calculates Future Predictions Quadratic Regression Line
 * @param _a - variable a of quadratic equation
 * @param _b - variable b of quadratic equation
 * @param _c - variable c of quadratic equation
 * @param i - x value
 */
void findFuturePrediction(double _a, double _b, double _c, int i){
    cout << "Year " << i  << " : " << (_a*pow(i, 2) + _b*i + _c) << endl;
}

/**
 * Calculates Future Predictions Linear Regression Line
 * @param m - slope of line
 * @param b - y-intercept of line
 * @param i - x value
 */
void findFuturePrediction(double m, double b, int i){
    cout << "Year " << i  << " [FA" << (7+i) << "] : " << (m*i+b) << endl;
}

/**
 * Reads data from the user. The user can enter data without declaring the number of data entries.
 * @return vector of all data entered by the user
 */
vector<double> readData(){
    double temp = 0;
    vector<double> input;
    cout << "Enter yearly data: " << endl;
    cout << "Press 'q' to quit" << endl;

    cout << "Year 1: ";

    for(int i = 1; cin >> temp && temp != 'q'; i++){
        input.push_back(temp);
        temp = 0;
        cout << "Year " << (i+1) << ": ";
    }

    return input;
}

/**
 * Finds corresponding x-axis values
 * @param a - Size of vector
 * @return Vector of x-axis values
 */
vector<int> findXData(int n){
    vector<int> data;
    for(int i = 1; i <= n; i++) data.push_back(i);
    return data;
}

/**
 * Finds the sum of a group of integers
 * @param a - vector array of integers
 * @return Sum of all values in the vector
 */
double findSum(vector<int> n){
    double sum = 0;
    for(auto x : n){
        sum += x;
    }

    return sum;
}

/**
 * Finds the sum of a group of doubles
 * @param a - vector array of doubles
 * @return Sum of all values in the vector
 */
double findSum(vector<double> n){
    double sum = 0;
    for(auto x : n){
        sum += x;
    }

    return sum;
}

/**
 * Calculates the squared of a vector
 * For example: (x)^2
 * @param in - vector of base values
 * @param power - exponent
 * @return Vector of squared values
 */
vector<double> powerVector(vector<int> in, int power){
    vector<double> out;
    for(auto x : in){
        double temp = pow(x, power);
        out.push_back(temp);
    }
    return out;
}

/**
 * Calculates (x*y) of a vector
 * @param x values
 * @param y values
 * @return (x*y) values
 */
vector<double> findXY(vector<int> x, vector<double> y){
    vector<double> out;
    if(x.size() == y.size()){
        for(int i = 0; i < x.size() && i < y.size(); i++){
            double temp = x.at(i) * y.at(i);
            out.push_back(temp);
        }
    }
    return out;
}

/**
 * Calculates (x*y)
 * @param x values
 * @param y values
 * @return (x*y) values
 */
vector<double> findXY(vector<double> x, vector<double> y){
    vector<double> out;
    if(x.size() == y.size()){
        for(int i = 0; i < x.size() && i < y.size(); i++){
            double temp = x.at(i) * y.at(i);
            out.push_back(temp);
        }
    }
    return out;
}

/**
 * Print data values of a vector
 * @param data - vector of y-axis values
 */
void print(vector<double> data){
    cout << "Given Data: " << endl;
    for(int i = 0; i < data.size(); i++){
        cout << "Year " << (i+1) << " : " << data.at(i) << endl;
    }
}

/**
 * Prints linear-related data values, calculations, and predictions
 */
void printLinear(){
    cout << endl << "Values and Calculations:" << endl;
    cout << "M11 = " << m11 << "\t\tM21 = M12 = " << m21 << endl;
    cout << "M12 = " << m12 << "\t\tM22 = " << m22 << endl;
    cout << "M13 = " << m13 << "\t\tM23 = " << m23 << endl;
    cout << "L = " << L << "\t\tL1 = " << L1 << "\t\tL2 = " << L2 << endl;
    cout << "a = L1/L = " << slope << "\t\tb = L2/L = " << yIntercept << endl;

    cout << endl;
    cout << "f(x) = " << slope << "x + " << yIntercept << endl;
    cout << "Slope(m) = " << slope << endl;
    cout << "Y-Intercept(b) = " << yIntercept << endl;
    cout << endl;

    cout << "Future Predictions: " << endl;
    for(int i = size+1; i < size + 6; i++){
        findFuturePrediction(slope, yIntercept, i);
    }
}

/**
 * Prints quadratic-related data values, calculations, and predictions
 */
void printQuadratic(){
    cout << endl << "Values and Calculations:" << endl;
    cout << "| M11 = " << m11 << "\t\tM12 = " << m12 << "\t\tM13 = " << m13 << "\t|\tM14 = " << m14 << "\t|" << endl;
    cout << "| M21 = " << m21 << "\t\tM22 = " << m22 << "\t\tM23 = " << m23 << "\t|\tM24 = " << m24 << "\t\t|" << endl;
    cout << "| M31 = " << m31 << "\t\t\tM32 = " << m32 << "\t\tM33 = " << m33 << "\t|\tM34 = " << m34 << "\t\t|" << endl;
    cout << endl;
    cout << "L = " << L << "\t\tL1 = " << L1 << "\t\tL2 = " << L2 << "\t\tL3 = " << L3 << endl;
    cout << "a = L1/L = " << a << "\t\tb = L2/L = " << b << "\t\tc = L3/L = " << c << endl;

    cout << endl << "Quadratic Formula: " << endl;
    cout << "f(x) = " << a << "*x^2 + " << b << "*x + " << c << endl;
    cout << endl;

    cout << "Future Predictions: " << endl;
    for(int i = size+1; i < size + 6; i++){
        findFuturePrediction(a, b, c, i);
    }
}
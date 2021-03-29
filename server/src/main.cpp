#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "PhishDetector.h"

using namespace std;

int main()
{
	string URL;
	cin >> URL;
	PhishDetector pd(URL);
	cout << pd.Check() << endl;	
	return 0;
}

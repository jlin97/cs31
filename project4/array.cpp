#include <iostream>
#include <cassert>
#include <string>

using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

//appends value to the end of each of the n elements of the array and returns n {NOPE}
int appendToAll(string a[], int n, string value) {
	if (n < 0) {    // if n is less then zero
		return -1;
	}
	for (int i = 0; i < n; i++) {   // from a[0] to a[n] append value
		a[i] += value;
	}
	for (int j = 0; j < n; j++) {   // testing
		cerr << a[j] << endl;
	}
	return n;  // return n
}
//returns the position of the string that is equal to target
int lookup(const string a[], int n, string target) {
	if (n < 0) {               // if n is invalid, return -1
		return -1;
	}
	for (int i = 0; i < n; i++) {
		if (a[i] == target) {           // search for a[i] and return i if the string is found
			return i;
		}
	}
	return -1;
}
//returns the position of the string that is greatest in the array {NOPE}
int positionOfMax(const string a[], int n) {
	if (n <= 0) {              // if n is 0 or negative, return -1
		return -1;
	}
	string max = a[0];     
	for (int i = 0; i < n; i++) {               // loop through the array and replace max with any greater entry found
		if (max < a[i]) {
			max = a[i];
		}
	}
	for (int j = 0; j < n; j++) {             // when the position of the greatest string is found, return it
		if (max == a[j]) {
			return j;
		}
	}
	return 0;
}
//moves item at position to the end and shifts all elements after it an index to the left, returns n
int rotateLeft(string a[], int n, int pos) {
	if (n <= 0 || pos > n - 1 || pos < 0) {                // if n is less than or equal to 0 or if position goes out of bounds
		return -1;
	}
	string temp = a[pos];
	for (int i = pos; i < n - 1; i++) {  // only loops up to n-1 to avoid array out-of-bounds
		a[i] = a[i + 1];
	}
	a[n - 1] = temp;
	for (int j = 0; j < n; j++) {      // testing
		cerr << a[j] << endl;
	}
	return pos;
}
//returns the number of sequences of one more more consecutive items
int countRuns(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	int counter = 0;                
	string comparison = "";
	for (int i = 0; i < n; i++) {
		if (a[i] != comparison) {      
			comparison = a[i];         // puts a[i] in the string comparison and changes comparison every iteration the a[i] is different
			counter++;                 // increase the counter every time an different string appears
		}
	}
	return counter;
}
//flips the array, returns n
int flip(string a[], int n) {
	if (n < 0) {
		return -1;
	}
	int n2 = n;
	for (int i = 0; i < n / 2; i++) {   //looped until n/2 or else the array will end up the same
		string temp = a[i];   // a[0] is put in a temp int
		a[i] = a[n2 - 1];  // a[0] == a[5]
		a[n2 - 1] = temp;   // a[5] is assigned the temp int
		n2--;  // n2 accounts for the int swapped from the greater half
	}
	for (int j = 0; j < n; j++) {
		cerr << a[j] << endl;
	}
	return n;
}
//returns the position of the first corresponding elements of a1 and a2 that are not equal
int differ(const string a1[], int n1, const string a2[], int n2) {
	// if we're comparing an array of size 3 with a 0-sized array

	if (n1 < 0 || n2 < 0) {  // if n1 or n2 is invalid, return 0
		return -1;
	}
	int min;
	if (n1 <= n2) {            // determine which has the smaller size between a1 and a2
		min = n1;
	}
	else {
		min = n2;
	}
	for (int i = 0; i < min; i++) {         // loop through until min 
		if (a1[i] != a2[i]) {              // increment i until an entry at a1 equals the corresponding entry at a2
			return i;
		}
	}
	return min;           // if none are equal, return the final position
}
//returns the position where n2 elements of a2 appear in a1, returns -1 if a1 doesn't contain a2 as a continguous subsequence
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	bool isValid = true;
	int pos = -1;
	if (n1 < 0 || n2 < 0) {   // if n1 or n2 are invalid, return -1
		return -1;
	}
	else if (n2 == 0) {    // if n2 is 0, return 0
		return 0;
	}
	for (int i = 0; i < n1; i++) {    // loops from index 0 to n1-1
		if (a1[i] == a2[0]) {           // when an entry of a1 matches the beginnning entry of a2 
			for (int j = 0; j < n2; j++) {
				if ((i + j) > n1) {
					isValid = false;       // if an index at exceeds the max size of a2
					break;
				}
				else if (a1[i + j] != a2[j]) {      // if the index at a1 doesn't match the index j of a2, isValid becomes false
					isValid = false;
				}
			}
			if (isValid) {    // if isValid remains true 
				pos = i;       // i is placed into pos
				break;
			}
		}
	}
	return pos;
}
//returns the smallest pos of an element in a1 that is equal to any of the elements in a2, returns -1 if no equal elements
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;              // if n1 or n2 is invalid, return -1
	}
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n2; j++) {
			if (a1[i] == a2[j]) {          // scan through a2 for any element that matches an element in a1 and increment
				return i;				   // if none found
			}
		}
	}
	return -1;						// returns -1 if none found
}
//rearrranges elements depending on <splitter
//returns pos of the first element after rearrangement that is not < splitter or n if there are no such elements.
int split(string a[], int n, string splitter) {
	if (n < 0) {
		return -1;					// if n is invalid, return -1
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {  // selection sort where each entries are swapped if a[i] < a[j]
			if (a[i] < a[j]) {
				string temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
	for (int k = 0; k < n; k++) {      // testing
		cerr << a[k] << endl;
	}
	for (int l = 0; l < n; l++) {     // finding the position where the entry at that position is greater than the splitter string
		if (a[l] >= splitter) {
			return l;
		}
	}
	return 0;                // returns 0 if there are no elements that are greater 
}
int main() {
	
	/*
	string test[6] = { "carly", "mike", "ted", "bernie", "jeb" };
	int shouldReturn1 =  appendToAll(test, -1, "...");
	cout << shouldReturn1 << endl;
	
	string folks[6] = { "1", "2", "3", "4", "4", "4" };

	int toReturn = lookup(folks, 0, "3");
	*/

	string folks[6] = { "chris", "marco", "", "ben", "donald", "john" };
	string group[5] = { "chris", "marco", "john", "", "carly" };
	
	string names[10] = { "ted", "hillary", "rand", "bernie", "mike", "jeb" };
	string set1[10] = { "carly", "mike", "bernie", "hillary" };
	string set2[10] = { "ben", "donald" };

	string cand[6] = { "bernie", "hillary", "donald", "marco", "carly", "ben" };
	string cand2[4] = { "donald", "hillary", "jeb", "ben" };

	const int N = 6;

	// Act as if  a  were declared:
	//   string a[N] = {
	//       "alpha", "beta", "gamma", "gamma", "beta", "delta"
	//   };
	// This is done in a way that will probably cause a crash if
	// a[-1] or a[N] is accessed:  We place garbage in those positions.
	string aa[1 + N + 1] = {
		"", "alpha", "beta", "gamma", "gamma", "beta", "delta", ""
	};
	string* a = &aa[1];
	string* z = aa;
	a[-1].string::~string();
	a[N].string::~string();
	fill_n(reinterpret_cast<char*>(&a[-1]), sizeof(a[-1]), 0xEF);
	fill_n(reinterpret_cast<char*>(&a[N]), sizeof(a[N]), 0xEF);


	case 79: {
		assert(split(a, 6, "zeta") == 6 &&
			splitcheck(a, 6, 6, "zeta"));
	}




	cout << toReturn << endl;

	
	/*
	string cand[6] = { "carly", "mike", "ted", "bernie", "jeb" };
	int irrelevant = rotateLeft(cand, 5, 3);
	cout << "The returned value is: " << irrelevant << endl;

	string h[7] = { "bernie", "hillary", "donald", "jeb", "", "carly", "ben" };
	string g[4] = { "bernie", "hillary", "jeb", "carly" };

	assert(lookup(h, 7, "carly") == 5);
	assert(lookup(h, 7, "donald") == 2);
	assert(lookup(h, 2, "donald") == -1);
	assert(positionOfMax(h, 7) == 3);

	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "bernie?" && g[3] == "carly?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jeb?" && g[3] == "hillary?");
	

	string e[4] = { "donald", "jeb", "", "carly" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "hillary", "hillary", "hillary", "ben", "ben" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "jeb", "donald", "marco" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "marco" && f[2] == "jeb");

	assert(split(h, 7, "carly") == 3);
	*/
	cout << "All tests succeeded" << endl;

}


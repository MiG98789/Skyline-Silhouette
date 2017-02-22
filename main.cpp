/*
 * main.cpp
 *
 *  Created on: 1 Feb 2017
 *      Author: Gian Miguel
 */

#include <iostream>
#include <vector>
using namespace std;

struct Point {
	int x, y;
};

/*
const int A_SIZE = 7;
int A[A_SIZE][3] = {
		{9,10,11},
		{0,6,6},
		{8,11,6},
		{0,2,3},
		{10,13,9},
		{4,6,2},
		{4,7,2}
};

CORRECT OUTPUT
0 6
6 2
7 0
8 6
9 11
10 9
13 0
*/

const int A_SIZE = 16;
int A[A_SIZE][3] = {
    {670, 870, 45},
    {520, 820, 330},
    {190, 390, 150},
    {20, 120, 405},
    {760, 960, 165},
    {370, 470, 60},
    {990, 1390, 255},
    {820, 1120, 315},
    {400, 700, 435},
    {690, 790, 300},
    {150, 350, 360},
    {460, 560, 15},
    {860, 960, 210},
    {110, 510, 360},
    {80, 480, 330},
    {410, 510, 135}
};

/* Expected output:
(20, 405)
(120, 360)
(400, 435)
(700, 330)
(820, 315)
(1120, 255)
(1390, 0)
*/

vector<Point> sil(int p, int q) {
	if(p == q) {
		Point top_left = {A[p][0], A[p][2]};
		Point bottom_right = {A[p][1], 0};

		vector<Point> vPoint;
		vPoint.push_back(top_left);
		vPoint.push_back(bottom_right);

		return vPoint;
	}

	int mid = (p + q) / 2;
	vector<Point> left = sil(p, mid);
	vector<Point> right = sil(mid + 1, q);

	vector<Point> output;
	int indexL = 0, indexR = 0;
	Point prevL = {0,0}, prevR = {0,0}, pushed = {0,0};
	Point curr;
	enum Flag {LEFT, RIGHT}; Flag flag;
	for(int i = 0; i < left.size() + right.size(); i++) {
		//--- Out of bounds ---//
		if(indexL >= left.size()) //End of left array
			flag = RIGHT;
		else if(indexR >= right.size()) //End of right array
			flag = LEFT;

		//--- Same x ---//
		else if(left[indexL].x == right[indexR].x) {
			if(left[indexL].y >= right[indexR].y) //Left above/overlap right
				flag = LEFT;
			else //Left below right
				flag = RIGHT;
		}

		//--- Use left sil ---//
		else if(left[indexL].x < right[indexR].x)
			flag = LEFT;

		//---Use right sil ---//
		else
			flag = RIGHT;

		if(flag == LEFT) { //Compare to prevR
            curr = left[indexL++]; prevL = curr;
			if(curr.y <= prevR.y)
				curr.y = prevR.y;
		}
		else if(flag == RIGHT) { //Compare to prevL
		    curr = right[indexR++]; prevR = curr;
			if(curr.y <= prevL.y)
				curr.y = prevL.y;
		}

		if(curr.y != pushed.y) {
			output.push_back(curr);
			pushed = curr;
		}
	}

	return output;
}

int main(int argc, char **argv) {
	vector<Point> output = sil(0, A_SIZE-1);

	int index = 0;
	while(index != output.size()) {
		cout << output[index].x << " " << output[index].y << endl;
		index++;
	}

	return 0;
}

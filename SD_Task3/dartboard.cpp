#include "dartboard.h"
#include <iostream>
using namespace std;

//throw bull function
int dartboard::throw_bull(int p, int& type) {
	//  Throw for the bull with accuracy p%  (20<p<85)
	//random number 0 - 99
	int r = rand() % 100;
	if (r < (p - 20))
		return 50;
	else if (r < 85) {
		//type is set to 0 to show it is now aiming at a single
		type = 0;
		return 25;
	}
	else {
		//type is set to 0 to show it is now aiming at a single
		type = 0;
		return 1 + rand() % 20;
	}
}

//throw single function
int dartboard::throw_single(int d, int& type) {
	//  return result of throwing for single d with accuracy 88% (or 80% for the outer)
	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	//random number 0 - 99
	int r = rand() % 100;
	if (d == 25) {		// outer  80%
		if (r < 80)
			return 25;
		else if (r < 90) {
			//type is set to 3 to show it is now aiming at the bull
			type = 3;
			return 50;
		}
		else
			return 1 + rand() % 20; //return random single (not including 25)
	}
	else			// 1 to 20 single
		if (r < 88)
			return d; //return single aimed at
		else if (r < 92)
			return bd[0][d]; //return single on left
		else if (r < 96)
			return bd[1][d]; //return single on right
		else if (r < 98) {
			//type is set to 2 to show it is now aiming at a treble
			type = 2;
			return 3 * d; //return treble version of single aimed at
		}
		else {
			//type is set to 1 to show it is now aiming at a double
			type = 1;
			return 2 * d; //return double version of single aimed at
		}
}

//throw double function
int dartboard::throw_double(int d, int& type) {

	//  return result of throwing for double d with accuracy 80%
	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	//random number 0 - 99
	int r = rand() % 100;

	if (r < 80)
		return 2 * d; //return double aimed at
	else if (r < 85)
		return 0; //return 0
	else if (r < 90) {
		//type is set to 0 to show it is now aiming at a single
		type = 0;
		return d; //returns single version of what was aimed at
	}
	else if (r < 93)
		return 2 * bd[0][d]; //returns double on the left
	else if (r < 96)
		return 2 * bd[1][d]; //returns double on the right
	else if (r < 98) {
		//type is set to 0 to show it is now aiming at a single
		type = 0;
		return bd[0][d]; //returns single on the left
	}
	else {
		type = 0;
		return bd[1][d]; //returns single on the right
	}
}

//throw treble function
int dartboard::throw_treble(int d, int p, int& type) {

	//  return result of throwing for treble d with accuracy p%  (o<90)

	// Board neighbours ignoring slot zero
	int bd[2][21] = { {0,20,15,17,18,12,13,19,16,14,6,8,9,4,11,10,7,2,1,3,5},
			   {0,18,17,19,13,20,10,16,11,12,15,14,5,6,9,2,8,3,4,7,1} };
	//random number 0 - 99
	int r = rand() % 100;

	if (r < p)
		return 3 * d; //return treble aimed at
	else if (r < 90) {
		//type is set to 0 to show it is now aiming at a single
		type = 0;
		return d; //returns single version of what was aimed at
	}
	else if (r < 93)
		return 3 * bd[0][d]; //returns treble on the left
	else if (r < 96)
		return 3 * bd[1][d]; //returns treble on the right
	else if (r < 98) {
		//type is set to 0 to show it is now aiming at a single
		type = 0;
		return bd[0][d]; //returns single on the left
	}
	else {
		//type is set to 0 to show it is now aiming at a single
		type = 0;
		return bd[1][d]; //returns single on the right
	}
}

//function to find if there are any one dart finishes
int dartboard::one(int n, int& a, int& shotType) {
	int singles[21] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25 };
	int doubles[20] = { 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
	int trebles[20] = { 3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60 };

	//if it can finish with a bull
	if (n == 50) {
		a = 50; //aiming at 50
		shotType = 3; //shotType set to 3 so it is known it is aiming at a bull
		return 1; //return 1 to show it can finish in one dart
	}
	//if it can finish with a double
	else if (std::find(std::begin(doubles), std::end(doubles), n) != std::end(doubles)) {
		a = n; //aiming at a double
		shotType = 1; //shotType set to 1 so it is known it is aiming at a double
		return 1; //return 1 to show it can finish in one dart
	}
	return 0; //return 0 to show it can't finish in one dart
}

//function to find if there are any two dart finishes
int dartboard::two(int n, int& a, int& shotType) {
	int singles[21] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25 };
	int doubles[20] = { 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
	int trebles[20] = { 3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60 };
	
	//two dart - single + double
	for (int i = 0; i < 20; i++)
	{
		if (std::find(std::begin(singles), std::end(singles), (n - doubles[i])) != std::end(singles))
		{
			a = (n - doubles[i]);
			shotType = 0;
			return 1;
		}
	}

	//two dart - double + double
	if (n > 40 && n % 2 == 0 && n <= 80) {
		for (int i = 0; i < 20; i++)
		{
			if (std::find(std::begin(doubles), std::end(doubles), (n - doubles[i])) != std::end(doubles))
			{
				a = doubles[i];
				shotType = 1;
				return 1;
			}
		}
	}

	//two dart - treble + double
	for (int i = 0; i < 20; i++)
	{
		if (std::find(std::begin(trebles), std::end(trebles), (n - doubles[i])) != std::end(trebles))
		{
			a = (n - doubles[i]);
			shotType = 2;
			return 1;
		}
	}

	//two dart - single + 50
	if (std::find(std::begin(singles), std::end(singles), (n - 50)) != std::end(singles))
	{
		a = n - 50;
		shotType = 0;
		return 2; //returns 2 to signal it is a risky path
	}

	//two dart - double + 50
	if (std::find(std::begin(doubles), std::end(doubles), (n - 50)) != std::end(doubles))
	{
		a = n - 50;
		shotType = 1;
		return 2;
	}

	//two dart - treble + 50
	if (std::find(std::begin(trebles), std::end(trebles), (n - 50)) != std::end(trebles))
	{
		a = n - 50;
		shotType = 2;
		return 2;
	}

	//two dart - 50 + 50
	if (n == 100) {
		a = 50;
		shotType = 3;
		return 2;
	}
	return 0;
}

//function to find if there are any three dart finishes
int dartboard::three(int n, int& a, int& shotType) {
	int singles[21] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25 };
	int doubles[20] = { 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
	int trebles[20] = { 3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60 };
	
	//single + single + double
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (std::find(std::begin(doubles), std::end(doubles), (n - singles[i] - singles[j])) != std::end(doubles))
			{
				a = singles[i];
				shotType = 0;
				return 1;
			}
		}
	}

	//single + double + double
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (std::find(std::begin(doubles), std::end(doubles), (n - singles[i] - doubles[j])) != std::end(doubles))
			{
				a = singles[i];
				shotType = 0;
				return 1;
			}
		}
	}

	//double + double + double
	if (n > 80 && n % 2 == 0 && n <= 120) {
		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (std::find(std::begin(doubles), std::end(doubles), (n - doubles[i] - doubles[j])) != std::end(doubles))
				{
					a = doubles[i];
					shotType = 1;
					return 1;
				}
			}
		}
	}

	//single + treble + double
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (std::find(std::begin(doubles), std::end(doubles), (n - singles[i] - trebles[j])) != std::end(doubles))
			{
				a = singles[i];
				shotType = 0;
				return 1;
			}
		}
	}

	//treble + double + double
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (std::find(std::begin(doubles), std::end(doubles), (n - trebles[i] - doubles[j])) != std::end(doubles))
			{
				a = trebles[i];
				shotType = 2;
				return 1;
			}
		}
	}

	//treble + treble + double
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (std::find(std::begin(doubles), std::end(doubles), (n - trebles[i] - trebles[j])) != std::end(doubles))
			{
				a = trebles[i];
				shotType = 2;
				return 1;
			}
		}
	}

	//three dart - single + single + 50
	for (int i = 0; i < 21; i++)
	{
		if (std::find(std::begin(singles), std::end(singles), (n - 50 - singles[i])) != std::end(singles))
		{
			a = singles[i];
			shotType = 0;
			return 2;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		//double + single + 50
		if (std::find(std::begin(singles), std::end(singles), (n - 50 - doubles[i])) != std::end(singles))
		{
			a = doubles[i];
			shotType = 1;
			return 2;
		}

		//double + double + 50
		if (std::find(std::begin(doubles), std::end(doubles), (n - 50 - doubles[i])) != std::end(doubles))
		{
			a = doubles[i];
			shotType = 1;
			return 2;
		}

		//treble + single + 50
		if (std::find(std::begin(singles), std::end(singles), (n - 50 - trebles[i])) != std::end(singles))
		{
			a = trebles[i];
			shotType = 2;
			return 2;
		}

		//treble + double + 50
		if (std::find(std::begin(trebles), std::end(trebles), (n - 50 - doubles[i])) != std::end(trebles))
		{
			a = trebles[i];
			shotType = 2;
			return 2;
		}

		//treble + treble + 50
		if (std::find(std::begin(trebles), std::end(trebles), (n - 50 - trebles[i])) != std::end(trebles))
		{
			a = trebles[i];
			shotType = 2;
			return 2;
		}
	}

	//three dart - single + 50 + 50
	if (std::find(std::begin(singles), std::end(singles), (n - 100)) != std::end(singles))
	{
		a = n - 100;
		shotType = 0;
		return 2;
	}

	//three dart - double + 50 + 50
	if (std::find(std::begin(doubles), std::end(doubles), (n - 100)) != std::end(doubles))
	{
		a = n - 100;
		shotType = 1;
		return 2;
	}

	//three dart - treble + 50 + 50
	if (std::find(std::begin(trebles), std::end(trebles), (n - 100)) != std::end(trebles))
	{
		a = n - 100;
		shotType = 2;
		return 2;
	}

	//three dart - 50 + 50 + 50
	if (n == 150) {
		a = 50;
		shotType = 3;
		return 2;
	}
	return 0;
}

//task one aiming
int dartboard::aim_task_one(int playerScore) {
	int aimingAt;
	//figure out what is being aimed for
	//501 - 62
	if (playerScore > 61) {
		aimingAt = 60;
	}
	//50 (win)
	else if (playerScore == 50 || playerScore == 52) {
		aimingAt = 50;
	}
	//25
	else if (playerScore == 27) {
		aimingAt = 25;
	}
	//doubles (win)
	else if (playerScore <= 40 && playerScore % 2 == 0) {
		aimingAt = playerScore;
	}
	//singles
	else if (playerScore - 2 < 20) {
		aimingAt = playerScore - 2;
	}
	//triples
	else if ((playerScore - 2) % 3 == 0) {
		aimingAt = playerScore - 2;
	}
	//doubles
	else if ((playerScore - 2) % 2 == 0) {
		aimingAt = playerScore - 2;
	}
	//finds biggest double/treble
	else
	{
		do
		{
			playerScore--;
		} while ((playerScore - 2) % 3 != 0 && ((playerScore - 2) % 2 != 0) && playerScore - 2 <= 40);
		aimingAt = playerScore - 2;
	}
	return aimingAt;
}

//task two aiming
int dartboard::aim(int plScore, int dartsLeft, int opScore, int& shotType) {
	int aimingAt;
	int singles[21] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,25 };
	int doubles[20] = { 2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
	int trebles[20] = { 3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57,60 };
	int unsuccessful[7] = { 169,168,166,165,163,162,159 }; //these are scores below 170 which can't be finished in 3 darts
	int success = 0;

	//if it is over 170, go for the highest possible (treble 60)
	if (plScore > 170 || (std::find(std::begin(unsuccessful), std::end(unsuccessful), plScore) != std::end(unsuccessful)))
	{
		aimingAt = 60;
		shotType = 2;
	}
	else {
		//3 DARTS
		if (dartsLeft == 0)
		{
			//is it a double?
			if (plScore % 2 == 0 && plScore <= 40)
			{
				success = one(plScore, aimingAt, shotType);
			}
			//if it's under 110 it's likely to be a very easy 2 dart win
			else if (plScore <= 110) {
				success = two(plScore, aimingAt, shotType);
			}
			//if previous wasn't successful, or the only one available is tricky
			if (success == 0 || success == 2)
			{
				//if it's tricky, check if there is an easier 3 dart option
				if (success == 2)
				{
					//check if there is an easier 3 dart option
					success = three(plScore, aimingAt, shotType);
					//if there isn't, will want to back to the 2 dart option
					if (success == 0)
					{
						success = two(plScore, aimingAt, shotType);
					}
				}
				else {
					//check if there is a three dart method if none previous were successful
					success = three(plScore, aimingAt, shotType);
				}
			}
		}

		//2 DARTS
		if (dartsLeft == 1)
		{
			if (plScore % 2 == 0 && plScore <= 40)
			{
				success = one(plScore, aimingAt, shotType);
			}
			else {
				success = two(plScore, aimingAt, shotType);
			}
		}

		//1 DART
		if (dartsLeft == 2)
		{
			success = one(plScore, aimingAt, shotType);
		}

		//if still not aiming at anything, or its tricky and it's not urgent, setup
		if (success == 0 || (success == 2 && opScore > 170))
		{
			//if the score is 3 - 15 and there is no finish, it's probably odd, must fix that by aiming for 1
			if (plScore > 2 && plScore < 16)
			{
				aimingAt = 1;
				shotType = 0;
			}
			//score is over 16 but less than 37, it is possible to get it to 16 with a single
			else if (plScore > 16 && plScore < 37)
			{
				int k = 1;
				while (plScore - k != 16)
				{
					k++;
				}
				aimingAt = k;
				shotType = 0;
			}
			//score is over 20 but less than 40, it is possible to get it to 20 with a single
			else if (plScore > 20 && plScore <= 40)
			{
				int k = 1;
				while (plScore - k != 20)
				{
					k++;
				}
				aimingAt = k;
				shotType = 0;
			}
			//score is over 40 but less than = 60, it is possible to get it to 40 with a single
			else if (plScore > 40 && plScore <= 60)
			{
				int k = 1;
				while (plScore - k != 40)
				{
					k++;
				}
				aimingAt = k;
				shotType = 0;
			}
			//can't get it setup to the point where it can be done in one find a double which will take it to close to 40
			else if (plScore > 60 && plScore <= 80) {
				int k = plScore - 40;
				while ((std::find(std::begin(doubles), std::end(doubles), k) != std::end(doubles)) == false) {
					k--;
				}
				aimingAt = k;
				shotType = 1;
			}
			else {
				if (plScore % 2 == 0)
				{
					aimingAt = 60;
					shotType = 2;
				}
				else {
					//make it even
					aimingAt = 57;
					shotType = 2;
				}
			}
		}
	}
	return aimingAt;
}

//shoot function, uses appropriate throw function and returns what was hit
int dartboard::shootInteractive(int hp, int aimingAt, int& type) {
	int turnScore = 0;
	//shoot for bull
	if (type == 3) {
		turnScore = throw_bull(hp, type);
	}
	//shoot for double
	else if (type == 1) {
		turnScore = throw_double(aimingAt / 2, type);
	}
	//shoot for single or outer bull
	else if (type < 1) {
		turnScore = throw_single(aimingAt, type);
	}
	//shoot for treble
	else {
		turnScore = throw_treble(aimingAt / 3, hp, type);
	}
	return turnScore;
}

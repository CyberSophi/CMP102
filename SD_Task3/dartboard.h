#pragma once
class dartboard
{
public:
	int throw_bull(int p, int& type);

	int throw_single(int d, int& type);

	int throw_double(int d, int& type);

	int throw_treble(int d, int p, int& type);

	int one(int n, int& a, int &shotType);

	int two(int n, int& a, int &shotType);

	int three(int n, int& a, int &shotType);

	int aim_task_one(int playerScore);

	int aim(int plScore, int dartsLeft, int opScore, int& shotType);

	int shootInteractive(int hp, int aimingAt, int& type);
};


#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* k = 손에 쥔 구슬 개수
* n = 건 구슬 개수
* b = 홀/짝(1/0)
*/

int main() {
	int k, n, b;
	
	int attack = 10, defence = 10;
	while (attack != 0 && defence != 0) {
		scanf("%d %d %d", &k, &n, &b);
		// 맞췄을 때
		if (k % 2 == b % 2) {
			attack += n;
			defence -= n;
		}
		//못맞췄을 때
		else {
			attack -= n;
			defence += n;
		}

		if (attack < 0 || defence < 0) {
			if (attack < defence) {
				attack = 0;
				defence = 20;
			}
			else
			{
				attack = 20;
				defence = 0;
			}
		}

		printf("%d %d\n",defence, attack);
	}
}
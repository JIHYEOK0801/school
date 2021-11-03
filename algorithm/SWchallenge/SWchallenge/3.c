#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>

int main() {
	int i, N, direction;
	int x = 0, y = 0;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &direction);
		if (direction == 1) {
			x += 1;
		}
		else if (direction == 2) {
			x -= 1;
		}
		else if (direction == 3) {
			y += 1;
		}
		if (direction == 4) {
			y -= 1;
		}
	}
	if (x == 4 && y == 4)
		printf("%d", 1);
	else {
		printf("%d\n%d %d",2, 4 - x, 4 - y);
	}
}

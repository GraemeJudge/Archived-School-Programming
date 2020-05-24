#include <stdio.h>

#define N 1000

#pragma warning(disable:4996)

int main() {
	int i, p, q, setID[N];
	
	
	for (size_t i = 0; i < N; ++i) 	//initialize array
	{
		setID[i] = i; //set them all to there own values so they strt all linked to themselves
	}


	while (scanf("%d, %d", &p, &q) == 2) {
		if (setID[p] == setID[q]) { //if already the same set no need to make any conections
			continue;
		}
		for (size_t i = 0; i < N; ++i)
		{
			if (setID[i] == setID[p]) {
				setID[i] = setID[q];
			}
		}
		printf(" %d %d\n", p,q);


	}

	return 0;
}

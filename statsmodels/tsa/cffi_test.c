#include <stdlib.h>
#include <stdio.h>

double holt_win_add_signal(double* x, double* xi, double* p, double* y, int m, long n, double max_seen, int yLen, int xLen) {
	int s_len;
	s_len = sizeof(double) * (m + n);
	int l_len;
	l_len = sizeof(double) * n;

	double* s = (double*)malloc(s_len);
	double* l = (double*)malloc(l_len);

	if (xLen == 1)
	{
		for (int i = 0; i < 6; i++)
		{
			if (xi[i] == 1)
			{
				p[i] = x[0];
			}
		}

	}
	else {
		int j = 0;
		for (int i = 0, j = 0; i < 6; i++)
		{
			if (xi[i] == 1)
			{
				p[i] = x[i];
			}
		}
	}

	double alpha = p[0];
	double gamma = p[2];
	double alphac = 1 - alpha;
	double gammac = 1 - gamma;

	l[0] = p[3];

	memcpy(s, &p[6], sizeof(double) * (m));




	if (alpha == 0.0) {
		return max_seen;
	}
	if (gamma > (1 - alpha)) {
		return max_seen;
	}


	double err = 0.0;
	double sse = 0.0;
	int tmp;


	err = y[0] - (l[0] + s[0]);
	sse = err * err;

	for (int i = 1; i < n; i++)
	{
		tmp = i - 1;

		l[i] = (alpha * (y[tmp] - s[tmp])) + (alphac * (l[tmp]));
		s[tmp + m] = gamma * (y[tmp] - l[tmp]) + (gammac * s[tmp]);
		err = y[i] - (l[i] + s[i]);
		sse += err * err;

	}

	free(l);
	free(s);

	return sse;
}

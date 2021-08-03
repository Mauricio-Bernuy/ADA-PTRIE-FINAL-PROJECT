#include <iostream>


int square_rec(int n, int m){
	if (n == m){
		//std::cout << n << ", " << m << ", " << " zero" "\n";
		return 0; 
	}

	else if (n < m){
		int min = INT32_MAX;
		int min_n, min_m;
		for (int i = 1; i < m; i++){
			int tmp = square_rec(n, i);
            int tmp2 = square_rec(n, m-i);

			if (tmp + tmp2 < min){
				min = tmp + tmp2 + 1;
				min_n = n;
				min_m = i;
			}
		}
		//std::cout << min_n << ", " << min_m << ", " << min << "\n";
		return min;
	}

	else{
		int min = INT32_MAX;
		int min_n, min_m;
		for (int j = 1; j < n; j++){
			int tmp = square_rec(j, m);
            int tmp2 = square_rec(n-j,m);
			if (tmp + tmp2 < min){
				min = tmp + tmp2 + 1;
				min_n = j;
				min_m = m;
			}
		}
		//std::cout << min_n << ", " << min_m << ", " << min << "\n";
		return min;
	}
}
int M[1000][1000];

int square_dp(int n, int m){
    for (int i = 0; i < 1000; i++)
        M[i][i] = 0;

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (i < j){
                int min = INT32_MAX;
                for (int i = 1; i < m; i++){
                    int tmp = square_rec(n, i);
                    int tmp2 = square_rec(n, m-i);
                    if (tmp + tmp2 < min){
                        min = tmp + tmp2 + 1;
                    }
                }
                M[i][j] = min;
            }
            else if (i > j){
                int min = INT32_MAX;
        		for (int j = 1; j < n; j++){
		        	int tmp = square_rec(j, m);
                    int tmp2 = square_rec(n-j,m);
                    if (tmp + tmp2 < min){
                        min = tmp + tmp2 + 1;
                    }
                }
                M[i][j] = min;
            }
        }
	}
    return M[n][m];
}


int main() {
  std::cout << square_rec(8,7) <<"\n";
  std::cout << square_dp(8,7);
}


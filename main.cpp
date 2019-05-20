#include <iostream>
#include <vector>

using namespace std;

struct Matrix
{
	vector<vector<long long>> V;
	int rows;
	int cols;
	
	Matrix(int rows, int cols){
		V = vector<vector<long long>>(rows, vector<long long>(cols));
		this->rows = rows;
		this->cols = cols;
	}

	Matrix(long long rows, long long cols, const vector<vector<long long>> &Vec){
		V = Vec;
		this->rows = rows;
		this->cols = cols;
	}

	Matrix operator*(const Matrix &other) const{
		Matrix ans(this->rows, other.cols);
		for (size_t i = 0; i < this->rows; i++){
			for (size_t j = 0; j < other.cols; j++){
				for (size_t k = 0; k < this->cols; k++){
					ans.V.at(i).at(j) += this->V.at(i).at(k) * other.V.at(j).at(k);
				}
			}
		}
		return ans;
	}

	void modMatrix(long long mod){
		for (auto &v : V){
			for (long long &x : v){
				x %= mod;
			}
		}
	}

	static Matrix identity(long long size){
		Matrix iden(size, size);
		for (size_t i = 0; i < size; i++){
			iden.V[i][i] = 1;
		}
		return iden;
	}

	void print(){
		for (auto v : this->V){
			for (long long x : v){
				cout << x << " ";
			}
			cout << endl;
		}
	}
};

Matrix matrix_fast_exp(Matrix base, long long n, long long mod){
	Matrix ans = Matrix::identity(base.rows);
	while (n > 0){
		if (n & 1){
			ans = ans * base;
			ans.modMatrix(mod);
		}
		base = base * base;
		base.modMatrix(mod);
		n >>= 1;
	}
	return ans;
}

long long fib(long long n){
	vector<vector<long long>> V{{0,1}, {1,1}};
	Matrix M(2, 2, V);
	vector<vector<long long>> V2{{1,1}};
	Matrix BaseCase(1, 2, V2);
	long long mod = 1e9 + 7;
	Matrix fibMat = matrix_fast_exp(M, n , mod);
	Matrix ans =  BaseCase * fibMat;
	return ans.V[0][1] % mod;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	long long t;
	cin >> t;
	while (t--){
		long long n;
		cin >> n;
		cout << fib(n) << endl;
	}
	return 0;
}
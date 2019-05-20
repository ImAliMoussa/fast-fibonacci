#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#define ll long long
using namespace std;

struct Matrix
{
	vector<vector<ll>> V;
	ll rows;
	ll cols;
	
	Matrix(ll rows, ll cols){
		V = vector<vector<ll>>(rows, vector<ll>(cols));
		this->rows = rows;
		this->cols = cols;
	}

	Matrix(ll rows, ll cols, vector<vector<ll>> Vec){
		V = Vec;
		this->rows = rows;
		this->cols = cols;
	}

	Matrix operator*(const Matrix &other) const{
		Matrix ans(this->rows, other.cols);
		for (ll i = 0; i < this->rows; i++){
			for (ll j = 0; j < other.cols; j++){
				for (ll k = 0; k < this->cols; k++){
					ans.V.at(i).at(j) += this->V.at(i).at(k) * other.V.at(j).at(k);
				}
			}
		}
		return ans;
	}

	void modMatrix(ll mod){
		for (auto &v : V){
			for (ll &x : v){
				x %= mod;
			}
		}
	}

	static Matrix identity(ll size){
		Matrix iden(size, size);
		for (ll i = 0; i < size; i++){
			iden.V[i][i] = 1;
		}
		return iden;
	}

	void prll(){
		for (auto v : this->V){
			for (ll x : v){
				cout << x << " ";
			}
			cout << endl;
		}
	}
};

Matrix matrix_fast_exp(Matrix base, ll n, ll mod){
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

ll fib(ll n){
	vector<vector<ll>> V{{0,1}, {1,1}};
	Matrix M(2, 2, V);
	vector<vector<ll>> V2{{1,1}};
	Matrix BaseCase(1, 2, V2);
	ll mod = 1e9 + 7;
	Matrix fibMat = matrix_fast_exp(M, n , mod);
	Matrix ans =  BaseCase * fibMat;
	return ans.V[0][1] % mod;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	ll t;
	cin >> t;
	while (t--){
		ll n;
		cin >> n;
		cout << fib(n) << endl;
	}
	return 0;
}
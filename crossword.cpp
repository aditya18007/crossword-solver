#include<iostream>
#include<vector>
#include<string>
#include<utility>

using namespace std;
using mat = vector<vector<char>>;
using list = vector<string>;
using pos = vector<pair<int,int>>;

constexpr int N = 10;
constexpr char WHITE = '-';
constexpr char BLACK = '+';

mat read_puzzle(){
    mat M(N, vector<char>(N,BLACK));
    for(int i = 0; i < N; i++){
        string s;
        cin >> s;
        for(int j = 0; j < N; j++){
            M[i][j] = s[j];
        }
    }
    return M;
}

list read_words(){
    string s;
    cin >> s;
    int i = 0; 
    int j = 0;
    list l;
    while( j <= s.size() ){
        if( (s[j] != ';') && (j < s.size()) ){
            j++;
            continue;
        }
        auto size = j-i;
        auto temp = s.substr(i,size);
        l.push_back(temp);
        i = j+1;
        j++;
    }
    return l;
}

void print(mat& M){
    for(auto& v : M){
        for(auto& c : v){
            cout << c;
        }
        cout << '\n';
    }
}


vector<pair<int,int>> left_starts(mat& M){
    vector<pair<int,int>> L;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(M[i][j] != '+'){
                if(j == 0){
                    L.emplace_back(i,j);
                } else{
                    if(M[i][j-1] == '+'){
                        L.emplace_back(i,j);
                    }
                }
            }
        }
    }
    return L;
}

vector<pair<int,int>> up_starts(mat& M){
    vector<pair<int,int>> L;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(M[i][j] != '+'){
                if(i == 0){
                    L.emplace_back(i, j);
                } else{
                    if(M[i-1][j] == '+'){
                        L.emplace_back(i,j);
                    }
                }
            }
        }
    }
    return L;
}

vector<pair<int,int>> right_starts(mat& M){
    vector<pair<int,int>> L;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(M[i][j] != '+'){
                if(j == N-1){
                    L.emplace_back(i, j);
                } else{
                    if(M[i][j+1] == '+'){
                        L.emplace_back(i,j);
                    }
                }
            }
        }
    }
    return L;
}

vector<pair<int,int>> down_starts(mat& M){
    vector<pair<int,int>> L;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(M[i][j] != '+'){
                if(i == N-1){
                    L.emplace_back(i, j);
                } else{
                    if(M[i+1][j] == '+'){
                        L.emplace_back(i,j);
                    }
                }
            }
        }
    }
    return L;
}

void print(pair<int,int>& p){
    cout << p.first << ',' << p.second << '\n';
}

void print(pos& L, string header){
    cout << header << '\n';
    for(auto& p : L){
        print(p);
    }
    cout << '\n';
}

using method = uint8_t;

constexpr method LEFT = 0;
constexpr method UP = 1;
constexpr method RIGHT = 2;
constexpr method DOWN = 3;

void refresh(mat& M, string& word, pair<int,int> position, method m, string& original){
    int n = original.size();
    int i = position.first;
    int j = position.second;
    int a = 0;
    while( a < n ){
        if( (j+a < N) && m == LEFT) M[i][j+a] = original[a];
        if( (i+a < N) && m == UP) M[i+a][j] = original[a];
        if( (j-a >=0) && m == RIGHT) M[i][j-a] = original[a];
        if( (i-a >=0) && m == DOWN) M[i-a][j] = original[a];

        a++;
    }
}

bool fit(mat& M, string& word,  pair<int,int>& position, method m, string& original){
    int n = word.size(); 
    int i = position.first;
    int j = position.second;
    if(M[i][j] != '-'){
        if(M[i][j] != word[0]){
            return false;
        }
    }
    int l = 0;
    switch(m){
        case LEFT:
            while( (l < n) && (j < N) && M[i][j] != '+' ){
                l++;
                j++;
            }
            break;
        case UP:
            while( (l < n) && (i < N) && (M[i][j] != '+')){
                i++;
                l++;
            }
            break;
        case RIGHT:
            while( (l < n) && (j >= 0) && (M[i][j] != '+') ){
                j--;
                l++;
            }
            break;
        case DOWN:
            while( (l < n) && (i >= 0) && (M[i][j] != '+') ){
                i--;
                l++;
            }
            break;
        default:
            cerr << "Wrong method type\n";
    }
    i = position.first;
    j = position.second;
    if(l == n){
        for( int a = 0; a < n; a++ ){
            if(m == LEFT){
                char c = M[i][j+a];
                if(c != '-'){
                    if( c != word[a] ){
                        return false;
                    }
                }
                original += c;
                M[i][j+a] = word[a];

            } else if( m == UP ){
                char c = M[i+a][j];
                if(c != '-'){
                    if( c != word[a] ){
                        return false;
                    }
                }
                original += c;
                M[i+a][j] = word[a];
            
            } else if( m  == DOWN){
                char c = M[i-a][j];
                if(c != '-'){
                    if( c != word[a] ){
                        return false;
                    }
                }
                original += c;
                M[i-a][j] = word[a];
            
            } else if(m == RIGHT){
                char c = M[i][j-a];
                if(c != '-'){
                    if( c != word[a] ){
                        return false;
                    }
                } 
                original += c;
                M[i][j-a] = word[a]; 
            } else{
                cerr << "WRONG METHOD TYPE CALLED\n";
            }
                    
        }
        if( l < N-1 ){
            if(m == LEFT){
                if( (j+l < N) && M[i][j+l] != '+'){
                    return false;
                }
            } else if( m == UP ){
                if( (i+l < N) && M[i+l][j] != '+'){
                    return false;
                }
            } else if( m == RIGHT ){
                if( (j-l >= 0) && M[i][j-l] != '+'){
                    return false;
                }
            } else if( m == DOWN ){
                if((i-l >= 0) && M[i-l][j] != '+'){
                    return false;
                }
            }
        }
        return true;
    }
    return false;
}

bool solve(mat& M, list& W, int curr_word, pos& L, pos& R, pos& U, pos& D){
    if(curr_word >= W.size()) {
        print(M);
        return true;
    }
    for(auto& p : L){
        string original = "";
        if(fit(M, W[curr_word], p, LEFT, original)){
            if(solve(M, W, curr_word+1, L, R, U, D)){
                return true;
            }
        }
        refresh(M, W[curr_word], p, LEFT, original);
    }
    for(auto& p : U){
        string original = "";
        if(fit(M, W[curr_word], p, UP, original)){
            if(solve(M, W, curr_word+1, L, R, U, D)){
                return true;
            }
        }
        refresh(M, W[curr_word], p, UP, original);
    }
    for(auto& p : R){
        string original = "";
        if(fit(M, W[curr_word], p, RIGHT, original)){
            if(solve(M, W, curr_word+1, L, R, U, D)){
                return true;
            }    
        }
        refresh(M, W[curr_word], p, RIGHT, original);
    }
    for(auto& p : D){
        string original = "";
        if(fit(M, W[curr_word], p, DOWN, original)){
            if(solve(M, W, curr_word+1, L, R, U, D)){
                return true;
            }        
        }
        refresh(M, W[curr_word], p, DOWN, original);
    }
    return false;
}


int main(){
    auto M = read_puzzle();
    auto W = read_words();
    
    auto L = left_starts(M);
    auto R = right_starts(M);
    auto U = up_starts(M);
    auto D = down_starts(M);
    solve(M, W, 0, L, R, U, D);
}

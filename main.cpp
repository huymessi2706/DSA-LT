#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <cmath>
#include <sstream>
#define ll long long
using namespace std;
bool bitarray[100] = {false};

void choice(bool bitarray[], int size);
void signUp(bool bitarray[], int size, string &username, string &password);
bool isLogin();
bool myPassString(string s, string un);
bool myNameString(string s);
bool lookup(bool *bitarray, int size, string s);
void insert(bool *bitarray, int size, string s);
int hash4(string s, int size);
int hash3(string s);
int hash2(string s, int size);
int hash1(string s);
void readFile(bool bitarray[], int size);
void failFile(string username);
void signUpfile(string username, string password);

int main(){
    int size = 100;
    choice(bitarray,size);
    return 0;
}
int hash1(string s)
{
    int hash = 0;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash + ((int)s[i]));
        hash = hash % 100;
    }
    return hash;
}

int hash2(string s, int size)
{
    int hash = 1;
    for (int i = 0; i < s.size(); i++)
    {
        hash = hash * 19 + s[i];
        hash = hash % size;
    }
    return hash % size;
}

int hash3(string s)
{
    int hash = 7;
    for (int i = 0; i < s.size(); i++)
        hash = (hash * 31 + s[i]) % 100;

    return hash % 100;
}

int hash4(string s, int size)
{
    ll int hash = 3;
    int p = 7;
    for (int i = 0; i < s.size(); i++)
    {
        hash += hash * 7 + s[i] * pow(p, i);
        hash = hash % size;
    }
    return (int)hash;
}

void insert(bool *bitarray, int size, string s)
{
    int a = hash1(s);
    int b = hash2(s, size);
    int c = hash3(s);
    int d = hash4(s, size);

    bitarray[a] = true;
    bitarray[b] = true;
    bitarray[c] = true;
    bitarray[d] = true;
}

bool lookup(bool *bitarray, int size, string s)
{
    int a = hash1(s);
    int b = hash2(s, size);
    int c = hash3(s);
    int d = hash4(s, size);

    if (bitarray[a] && bitarray[b] && bitarray[c] && bitarray[d])
        return true;
    else
        return false;
}


// Kiem tra dieu kien cua username
bool myNameString(string s){
    if(s.size() < 5 || s.size() > 10)
        return false;
    for(int i = 0 ; i < s.size() ; i++)
        if(s[i] == ' ')
            return false;
    return true;
}


// Kiem tra dieu kien cua mat khau
bool myPassString(string s, string un){
    if(s.size() > 20 || s.size() < 10)
        return false;
    if(s == un)
        return false;
    int countUp = 0, countLow = 0, countNum = 0, countSpe = 0;
    for(int i = 0 ; i < s.size() ; i++){
        if(s[i] == ' ')
            return false;
        if(isupper(s[i]))
            countUp++;
        if(islower(s[i]))
            countLow++;
        if(isdigit(s[i]))
            countNum++;
        if(!isalnum(s[i]))
            countSpe++;
    }
    if(countUp == 0 || countLow == 0 || countSpe == 0 || countNum == 0)
        return false;
    return true;
}


// Kiem tra dang nhap
bool isLogin(){
    string tmp;
    string username , password;
    string un , pas ;

    system("cls");
    cout << "2. Login" << endl;
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;

    ifstream ifs("SignUp.txt");
    getline(ifs,tmp,' ');
    un = tmp;
    getline(ifs,tmp);
    pas = tmp;
    ifs.close();

    if(username == un && password == pas)
        return true;
    else    
        return false;
}


// Kiem tra dang ky
void signUp(bool bitarray[], int size, string &username, string &password){
    cout << "1. Register "<< endl;
    cout << "Enter your username: ";
    getline(cin, username);
    if(myNameString(username) && !lookup(bitarray,size,username))
        insert(bitarray,size,username);
    else{
        bool flag = true;
        while(flag){
            system("cls");
            if(lookup(bitarray,size,username)){
                failFile(username);
                system("cls");
                cout << "Account already exists" << endl;
                cout << "----------------------" << endl;
                choice(bitarray,size);
            }
            else{
                failFile(username);
                cout << "1. The name length must be greater than 5 and less than 10" << endl;
                cout << "2. The name can not be contained space character" << endl;
                cout << "Enter your username: ";
                getline(cin, username);
            }
            if(myNameString(username) && !lookup(bitarray,size,username)){
                insert(bitarray,size,username);
                flag = false;
            }
            }
    }

    cout << "Enter your password: ";
    getline(cin, password);

    while(!myPassString(password,username)){
        cout << "1. The pass length must be greater than 10 and less than 20." << endl;
        cout << "2. Password must not contain spaces and cannot be the same as username." << endl;
        cout << "3. Password must include uppercase, lowercase, numbers and special characters." << endl;
        cout << "Enter your password: ";
        getline(cin, password);
    }
}

void choice(bool bitarray[], int size){
    int ch;
    string username , password;
    readFile(bitarray,size);

    cout << "Main Menu: " << endl;
    cout << "----------------------" << endl;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << endl;
    cout << "Your choice: ";
    cin >> ch;
    cin.ignore();

    if(ch == 1){
        system("cls");
        signUp(bitarray,size, username,password);
        signUpfile(username, password);
        system("cls");
        cout << "2. Login" << endl;
        if(isLogin()){
            system("cls");
            cout << "You can change your password!";
        }
        else{
            system("cls");
            cout << "Login fail!";
        }
    }
    else {
        if(isLogin()){
            system("cls");
            cout << "You can change your password!";
        }
        else{
            system("cls");
            cout << "Login fail!";
        }        
    }
}


// ghi ra tai khoan da tao thanh cong
void signUpfile(string username, string password){
    ofstream ofs("SignUp.txt", ios::app);
    ofs << username << " " << password;
    ofs.close();
}

// ghi ra tai khoan tao bi loi
void failFile(string username){
    ofstream ofs("Fail.txt", ios::app);
    ofs << username << endl;
    ofs.close();
}

// doc file nguoi dung de tao bitarray
void readFile(bool bitarray[], int size){
    string data,tmp;
    ifstream ifs("SignUp.txt");
    while(!ifs.eof()){
        getline(ifs,data);
        if(data.empty())
            break;
        stringstream ss(data);
        getline(ss,tmp,' ');
        insert(bitarray,size,tmp);
    }
    ifs.close();
}
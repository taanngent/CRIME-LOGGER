#include <bits/stdc++.h>
#include <conio.h>
#include <fstream>
#include <windows.h>
using namespace std;

int k1,k2,x2,y2;
int main(void);
vector<string> serial;

string s;
string z_sign;

vector<vector<int>> grid;

int k,f=0;

void clear(){
    system("cls");
    cout<<"loading....";
    Sleep(100);  //1000 --> 1s
    system("cls");
}


void login()
{
    string name;
    int count = 0;
    system("cls");

start:
    
    cout<<"===================================LOGIN======================================"<<endl;

    cout<<"ENTER ADMIN NAME :"<<endl;
    cin >> name;   //Raghav  
    cout<<"ENTER PASSWORD  :"<<endl;  

    //cin>>pass;
    string pass = "";
    char ch;
    
    int cou = 0;   //Password =3 word
    while (cou != 3)
    {
        ch = _getch();
        cou++;
        pass.push_back(ch);
        cout << '*';
    }

    if ( name.compare("Raghav") != 0 || pass.compare("123") != 0  ){
    
        clear();
        
        cout<<"Please Enter vailid Username & Passward!!!!!";
        cout<<endl;
        count++;
        
        printf("%d chance left!!!!", 3 - count);
        getch();
        system("cls");
        if (count == 3)
            exit(0);
        else
            goto start;
    }
    else
    {
        clear();
        cout<<"======================================WELCOME===================================================";
        Sleep(500);
        clear();
    }
}


void victim_input(){

    clear();
    cout<<"WEAPON USED TO KILL THE VICTIM - "<<endl;
    cin>>s;
    cout<<endl;

    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());

    for(int i=0;i<s.size();i++){
        if(int(s[i]) >=65 && int(s[i]) <91 ){
            s[i] = s[i]+32;
        }
    }

    cout<<"ENTER THE ZODIAC SIGN OF VICTIM - "<<endl;
    cin>>z_sign;
    cout<<endl;

    z_sign.erase(remove(z_sign.begin(), z_sign.end(), ' '), z_sign.end());

    for(int i=0;i<z_sign.size();i++){
        if(int(z_sign[i]) >=65 && int(z_sign[i]) <91 ){
            z_sign[i] = z_sign[i]+32;
        }
    }

    clear();

    main();
}

void compute(string s1,int m,int* lps){

    int len = 0;
  
    lps[0] = 0; 
  
    int i = 1;
    while (i < m) {
        if (s1[i] == s1[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else 
        {
            if (len != 0){
                len = lps[len - 1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }

}


void serial_killer(string ppp){

    //kmp
    fstream file;

    file.open("pattern.txt", ios::in);
    string s1;

    while(getline(file, s1)){
        int n = s1.size();
        int m = ppp.size();

        int lps[m];

        compute(ppp,m,lps);

        int i = 0; // s1
        int j = 0; // s

        while(i<n){
            if(ppp[j] == s1[i]){
                j++;
                i++;
            }

            if(j==m){
                // printf("Found pattern at index %d ",i-j);
                serial.push_back(s1.substr(0,(i-j)));
                j = lps[j-1];
                break;
            }

            else if(i<n && s1[i] != ppp[j]){
                if(j!=0){
                    j = lps[j-1];
                }
                else{
                    i = i+1;
                }
            }
        }
    }

}

void serial_killer(){
    serial_killer(s);

    if(serial.empty()){
        serial_killer(z_sign);
        if(serial.empty()){
            cout<<"NO serial killer is involved in this"<<endl;
            return ;
        }
    }
    for(auto x:serial){
        cout<<x<<"\"";
    }
}

void location(){
    //enter the locations point
    clear();

    if(k1==-1){
        cout<<"ENTER 1ST SPOT - "<<endl;
        cout<<"x-axis - ";
        cin>>k1;
        cout<<endl;
        cout<<"y-axis - ";
        cin>>k2;
        cout<<endl;
    }
    else{
        cout<<"WANT TO CHANGE THE LOCATION OF FIRST SPOT ?";
        string t;
        if(t == "Yes" || t =="yes" || t =="YES"){
            cin>>k1>>k2;
        }
        
    }
    if(x2== -1){
        cout<<"ENTER 2nd SPOT - "<<endl;
        cout<<"x-axis - ";
        cin>>x2;
        cout<<endl;
        cout<<"y-axis - ";
        cin>>y2;
        cout<<endl;
    }
    else{
        cout<<"WANT TO CHANGE THE LOCATION OF FIRST SPOT ?";
        string t;
        if(t == "Yes" || t =="yes" || t =="YES"){
            cin>>x2>>y2;
        }
    }

    clear();
    main();
}

bool check(int x1,int y1,vector<vector<bool>> &vis){

    return (x1>=0 && y1>=0 && x1<100 && y1<100 && !vis[x1][y1]);
}

void findpath(int uu1,int uu2,vector<vector<pair<int,int>>> prevv)
{

    if(uu1 == k1 && uu2 == k2){
        cout<<uu1<<","<<uu2<<" -> ";
        return;
    }

    int pp1 = uu1,pp2 = uu2;

    findpath(prevv[pp1][pp2].first,prevv[pp1][pp2].second,prevv);

    cout<<uu1<<","<<uu2<<" -> ";

}

void smallest_distance(){
    //bfs

    grid[k1][k2] = 0;
    grid[x2][y2] = 0;

    vector<vector<bool>> vis(100,vector<bool>(100,false));

    vector<vector<pair<int,int>>> prevv(100,vector<pair<int,int>>(100,{-1,-1}));

    queue<pair<int,int>> q;
    q.push({k1,k2});
    int ff=0;
    vis[k1][k2] = true;
    prevv[k1][k2] = {-1,-1};

    while(!q.empty()){
        int pp = q.size();

        for(int i=0;i<pp;i++){
            int g1 = q.front().first;
            int g2 = q.front().second;
            q.pop();

            if(g1 == x2 && g2 == y2){
                ff=1;
                break;
            }

            int row[] = {1,-1,0,0};
            int col[] = {0,0,1,-1};

            for(int j=0;j<4;j++){
                int ll1 = g1+row[j];
                int ll2 = g2+col[j];

                if(check(ll1,ll2,vis)){
                    q.push({ll1,ll2});
                    vis[ll1][ll2] = true;
                    prevv[ll1][ll2] = {g1,g2};
                }
            }
        }

        if(ff){
            break;
        }
    }

    findpath(x2,y2,prevv);

}

int main(void)
{
    if(!f){
        k1=-1,k2=-1,x2=-1,y2=-1;
        s="";z_sign="";
        grid.assign(100,vector<int>(100,1));
        login();
        cout<<"NUMBER OF MURDERS - ";
        cin>>k;
        f=1;
    }
hello:

    int a;

    if(k==1){
        cout<<"PRESS 1 TO TAKE THE INPUT VALUES OF VICTIM "<<endl;
        cout<<"PRESS 2 TO CHECK THE SERIAL KILLER BEHIND IT "<<endl;
        cout<<"PRESS 5 TO DISCONTINUE WITH THE CASE "<<endl;

        cin>>a;

        if(a!=1 && a!=2 && a!=5){
            cout<<"PRESS THE RIGHT KEY"<<endl;
            clear();
            goto hello;
        }
        else if(a==2 && (s=="")){
            cout<<"Input the dead body identity first";
            goto hello;
        }
    }
    else{
        cout<<"PRESS 1 TO TAKE THE INPUT VALUES OF VICTIM "<<endl;
        cout<<"PRESS 2 TO CHECK THE SERIAL KILLER BEHIND IT "<<endl;
        cout<<"PRSS 3 TO INPUT THE LOCAION OF VICTIMS KILLED "<<endl;
        cout<<"PRESS 4 TO FIND THE SMALLEST DISTANCE BETWEEN murder houses "<<endl;
        cout<<"PRESS 5 TO DISCONTINUE WITH THE CASE "<<endl;

        cin>>a;
        if(a==4 && (k1 == -1 || x2 == -1)){
            cout<<"FIRST ENTER THE LOCATON OF THE SPOTS"<<endl;
            Sleep(6000);
            clear();
            goto hello;
        } 
        else if(a==2 && (s=="")){
            cout<<"Input the dead body identity first";
            goto hello;
        } 
    }

    switch (a)
    {
    case 1:
        clear();
        victim_input();
        break;
    case 2:
        clear();
        serial_killer();
        Sleep(6000);
        break;
    case 3:
        clear();
        location();
        break;
    case 4:
        clear();
        smallest_distance();
        Sleep(6000);
        break;
    case 5:
        clear();
        exit(0);
        break;
    default:
        cout << "ENTER THE CORRECT NUMBER!!!!!" << endl;
        goto hello;
    }
    
    return 0;
}
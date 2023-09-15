#include <bits/stdc++.h>
#define ll long long int
//#define fo(i, n) for (ll i = 0; i < n; i++)

using namespace std;

int i = 0,IR=0;
vector<char> PC (2, '0'), MAR(2,'0'), MDR(3, '0'), A(3, '0'), B(3, '0'), C(3, '0'), D(3, '0'), SP(2, '0');
int E = 0;
vector<vector<char>> RAM (256, vector<char>(3, '0'));

void ram_in() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> RAM[i][j];
        }
    }
}

void inc_pc(vector<char> &pc){
if(pc[1]=='F' && pc[0]!='F')
{
    pc[1]=0;
    if(pc[0]!=9)
    pc[0]=(pc[0]-'0')+1+'0';
    else
    pc[0]='A';//9F+1;
}
else if(pc[1]=='F' && pc[0]=='F')
{
    pc[1]='0';
    pc[0]='0';
}
else if(pc[1]!='9')
pc[1]= (pc[1]-'0')+1+'0';
else if(pc[1]=='9')
{
    pc[1]='A';
}
}
string d2h(int n)
{
    string ans = "";
    while (n != 0) {
        int rem = 0;
        char ch;
        rem = n % 16;
        
        if (rem < 10) {
            ch = rem + 48;
        }
        else {
            ch = rem + 55;
        } 
        ans += ch;
        n = n / 16;
    }
    int i = 0, j = ans.size() - 1;
    while(i <= j)
    {
      swap(ans[i], ans[j]);
      i++;
      j--;
    }
    return ans;

}

int h2d(vector<char> &hexVal)
{

    int len = hexVal.size();
    int base = 1;
    int dec_val = 0;

    for (int i = len - 1; i >= 0; i--) {

        if (hexVal[i] >= '0' && hexVal[i] <= '9') {

            dec_val += (int(hexVal[i]) - 48) * base;
            base = base * 16;

        }
        else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {

            dec_val += (int(hexVal[i]) - 55) * base;
            base = base * 16;
        }
    }
    return dec_val;
}

int h2d1(char ch)
{
    if(ch=='0' || ch=='1' ||ch=='2' ||ch=='3' ||ch=='4' ||ch=='5' ||ch=='6' ||ch=='7' ||ch=='8' ||ch=='9' )
    return ch-'0';
    else if(ch=='A')
    return 10;
    else if(ch=='B')
    return 11;
    else if(ch=='C')
    return 12;
    else if(ch=='D')
    return 13;
    else if(ch=='E')
    return 14;
    else 
    return 15;

}

char d2h1(int i)
{
   if(i<=9)
   return i+'0';
   else if(i==10)
   return 'A';
   else if(i==11)
   return 'B';
   else if(i==12)
   return 'C';
   else if(i==13)
   return 'D';
   else if(i==14)
   return 'E';
   else
   return 'F';
   
   
}

void fetch()
{
   // cout << "Fetch:" << endl;
   // cout << "Enable Program Counter to address bus" << endl;
   // cout << "Load Memory Address Register from address bus" << endl;
   
   cout<<"T0: MAR<-PC"<<endl;
   cout<<"T1: MDR<- M[MAR], PC<-PC+1"<<endl;
   
    for (int i = 0; i<2; i++) {
        MAR[i] = PC[i];
    }
    int t = h2d(MAR);
    for (int i = 0; i<3; i++) {
    MDR[i] = RAM[t][i] ;
    }
    //pc+1
    inc_pc(PC);
}
void decode()
{
    //MRI
    cout<<"T2: MAR<-MDR(7-0)"<<endl;
    if(MDR[0]!='7' && MDR[0]!='F') {
        MAR[0] = MDR[1];
        MAR[1] = MDR[2];
        IR= (int)MDR[0] & 7;
    }
    //non- mri
}
void showContent()
{
    cout<<"PC=";
    for (int i = 0; i<2; i++) {
        cout<<PC[i];
    }
    cout<<" MAR=";
    for (int i = 0; i<2; i++) {
        cout<<MAR[i];
    }
    cout<<" MDR=";
    for (int i = 0; i<3; i++) {
        cout<<MDR[i];
    }
    cout<<" A=";
    for (int i = 0; i<3; i++) {
        cout<<A[i];
    }
    cout<<" B=";
    for (int i = 0; i<3; i++) {
        cout<<B[i];
    }
    cout<<" C=";
    for (int i = 0; i<3; i++) {
        cout<<C[i];
    }
    cout<<" D=";
    for (int i = 0; i<3; i++) {
        cout<<D[i];
    }
    cout<<" E="<<E<<endl;

}
void xchg (vector < char >&A, vector < char >&B)
{

  cout << "-----Initial value of A, B and C register-----" << endl;
  showContent ();
  fetch ();
  decode ();

  cout << "T3: C<-A, A<-B, B<-C" << endl;
  //   cout<<" A="<<A[0]<<A[1]<<A[2]<<" "<<"B = "<<B[0]<<B[1]<<B[2]<<" "<<"C = "<<C[0]<<C[1]<<C[2]<<endl;

  for (int i = 0; i < 3; i++)
    {
      C[i] = A[i];
    }
  cout << "----start Of XCHG A,B Microinstructions-->>" << endl;
  cout << " A=" << A[0] << A[1] << A[2] << " " << "B = " << B[0] << B[1] <<
    B[2] << " " << "C = " << C[0] << C[1] << C[2] << endl;
  for (int i = 0; i < 3; i++)
    {
      A[i] = B[i];
    }
  cout << " A=" << A[0] << A[1] << A[2] << " " << "B = " << B[0] << B[1] <<
    B[2] << " " << "C = " << C[0] << C[1] << C[2] << endl;

  for (int i = 0; i < 3; i++)
    {
      B[i] = C[i];
    }
  cout << " A=" << A[0] << A[1] << A[2] << " " << "B = " << B[0] << B[1] <<
    B[2] << " " << "C = " << C[0] << C[1] << C[2] << endl;
  cout << "----end Of XCHG A,B Microinstructions-->>" << endl;
  cout << endl;
  showContent ();
}

void lda ()
{

  // int t = h2d(MAR);
  cout << "-----Initial value of all registers" << endl;
  showContent ();
  fetch ();
  decode ();
  showContent ();
  cout << "T4:MDR <- M[MAR]" << endl;
  cout << "T5: AC <-MDR " << endl;
  //ram_in();
  // cout<<"Enter the address: ";
  // cin>>MAR[0]>> MAR[1];
  int x = h2d (MAR);
  cout << "Enter the content of RAM: ";
  cin >> RAM[x][0] >> RAM[x][1] >> RAM[x][2];
  //MDR = RAM[x];
  A = RAM[x];
  cout << "-----Value of all registers after LDA operation" << endl;
  showContent ();
}

void sta (vector < char >&MAR)
{
  //vector<char> x=MAR;
  cout << "-----Initial value of all registers" << endl;
  showContent ();
  fetch ();
  decode ();
  cout << "T4: MDR <-AC" << endl;
  cout << "T5: M[MAR] <-MDR" << endl;
  MDR = A;
  int t = h2d (MAR);
  RAM[t] = A;
  // MAR[0]=x[0];
  //MAR[1]=x[1];
  cout << "RAM = " << RAM[t][0] << RAM[t][1] << RAM[t][2] << endl;
  cout << "-----Value of all registers after STA operation" << endl;
  showContent ();

}

void addc (vector < char >&A, vector < char >&B)
{
  cout << "-----Initial value of all registers" << endl;
  showContent ();
  fetch ();
  decode ();

  cout << "T3:MDR <- M[MAR]" << endl;
  cout << "T4:MDR <- M[MAR]" << endl;

  int last_A = h2d1 (A[2]);
  int last_B = h2d1 (B[2]);

  int x = last_A + last_B + E;
  E = x / 16;
  A[2] = d2h1 (x % 16);

  last_A = h2d1 (A[1]);
  last_B = h2d1 (B[1]);
  x = last_A + last_B + E;
  E = x / 16;
  A[1] = d2h1 (x % 16);

  last_A = h2d1 (A[0]);
  last_B = h2d1 (B[0]);
  x = last_A + last_B + E;
  E = x / 16;
  A[0] = d2h1 (x % 16);

  cout << "-----Value of all registers after ADDC operation" << endl;
  showContent ();
}

void
exor (vector < char >&A, vector < char >&B)
{

  cout << "-----Initial value of all registers -----" << endl;
  showContent ();
  fetch ();
  decode ();
  
  cout<<"T3: A<- A^B"<<endl;
 
  int a = h2d (A);
  int b = h2d (B);
  int c = a ^ b;

  string temp = d2h (c);
  for (int i = 0; i < 3; i++)
    {
      A[i] = temp[i];
    }
    
    cout << "-----Final value of all registers -----" << endl;
   showContent();
}

int except (int num, int den, int *rem)
{

  if (den == 0)
    {
      throw runtime_error ("Math error: Attempted to divide by Zero\n");
      //{

      //showContent();
      //}
    }
  *rem = num % den;
  return (num / den);
}

void division (vector < char >&A, vector < char >&B)
{
  cout << "-----Initial value of all registers-----" << endl;
  showContent ();
  fetch ();
  decode();
  cout<<"T3: C<- A/B, D<- A%B"<<endl;


  int numerator, denominator, result, remain;
  numerator = h2d (A);
  denominator = h2d (B);

  // void fun(int denominator)
  // {
  //   if(denominator==0) throw denominator;
  // }
  try
  {
    // result = except(numerator, denominator, &remain ); 
    // cout << "The quotient is "
    //     << result << endl; 
    // int y= numerator/denominator;
    if (denominator == 0)
      throw denominator;
    // fun(denominator);
  }
  catch ( ...)
  {
    cout << "Exception occurred" << endl;
    C[0] = '1';
    C[1] = '1';
    C[2] = '1';
    // D[0]='0';
    // D[1]='.';
    // D[2]='2';
  }
  cout << "rest of the code...." << endl;
  string temp = "";
  temp = d2h (result);
  if (temp.size () == 0)
    {
      C[0] = '0';
      C[1] = '0';
      C[2] = '0';
    }
  else if (temp.size () == 1)
    {
      C[0] = '0';
      C[1] = '0';
      C[2] = temp[0];
    }
  else if (temp.size () == 2)
    {
      C[0] = '0';
      C[1] = temp[0];
      C[2] = temp[1];
    }
  else
    {
      C[0] = temp[0];
      C[1] = temp[1];
      C[2] = temp[2];
    }
  temp = d2h (remain);
  if (temp.size () == 0)
    {
      D[0] = '0';
      D[1] = '0';
      D[2] = '0';
    }
  else if (temp.size () == 1)
    {
      D[0] = '0';
      D[1] = '0';
      D[2] = temp[0];
    }
  else if (temp.size () == 2)
    {
      D[0] = '0';
      D[1] = temp[0];
      D[2] = temp[1];
    }
  else
    {
      D[0] = temp[0];
      D[1] = temp[1];
      D[2] = temp[2];
    }

  cout<<"-------Final value of all registers-----" << endl;
  showContent ();
}

void push_iba(vector<char>& SP, vector<char>& A)
{   
    
    cout << "Initial address pointed by SP ::" << " " << SP[0] << SP[1] << endl;
    cout << "-----Initial value of all registers-----" << endl;
    showContent();
    cout << "-----Initial value of SP-----" << endl;
    for (int i = 0; i < 2; i++) {
        cout << SP[i];
    }
    cout << endl;
     
    for (int i = 0; i<10; i++) {
        for (int j = 0; j<3; j++) {
            cin>>RAM[i][j];
        }
    }
    fetch();
    cout<<"T2: SP<- SP+1"<<endl;
    cout<<"T3: MAR<-SP"<<endl;
    cout<<"T4: RAM <- A"<<endl;
    
    if (SP[1] == 'F' && SP[0] == 'F') {
        cout << "Stack is full" << endl;
        SP[0] = '0';
        SP[1] = '0';
    }
    else if (SP[1] != 'F') {
        SP[1] = ((SP[1] - '0') + 1) + '0';
    }
    else {
        SP[1] = '0';
        SP[0] = ((SP[0] - '0') + 1) + '0';
    }
    cout << "-----Value of SP after incrementing-----" << endl;

    for (int i = 0; i < 2; i++) {
        cout << SP[i];
    }
    cout<<endl;
    MAR[0] = SP[0];
    MAR[1] = SP[1];
    
    int addr = h2d(MAR);

    for (int i = 0; i < 3; i++)
    {
        RAM[addr][i] = A[i];
    }
    
    cout << "The value at address pointed by SP is::" << " ";
    for (int i = 0; i < 3; i++)
    {
        cout << RAM[addr][i];
    }
    cout << endl;

    cout << "-----Final value of all registers-----" << endl;
    showContent();
}

void pop_daa(vector<char>& SP)
{

    fetch();
    cout<<"T2: MAR<-SP"<<endl;
    cout<<"T3: A<-RAM"<<endl;
    cout<<"T4: SP<-SP-1"<<endl;
    A = {'0','0','0'};
    cout << "-----Initial value of all registers-----" << endl;
    showContent();
    cout<<"SP = "<<SP[0]<<SP[1]<<endl;

    MAR = SP;
    cout <<"MAR = "<< MAR[0] << MAR[1] << endl;

    int addr = h2d(MAR);
    for (int i = 0; i < 3; i++)
    {
        A[i] = RAM[addr][i];
    }

    cout <<"A ="<< A[0] << A[1] << A[2] << endl;


    if (SP[0] == '0' and SP[1] == '0')
    {
        cout << "stack is now empty";
        return;
    }
    else if (SP[1] == '0')
    {
        SP[1] = 'F';
        SP[0] = ((SP[0] - '0') - 1) + '0';
    }
    else
        SP[1] = ((SP[1] - '0') - 1) + '0';

    cout << "The address pointed by the SP is :: " << SP[0] << SP[1] << endl;

    cout << "-----Final value of all registers-----" << endl;
    showContent();

}

void fcma(vector<char>& A)
{
    cout << "-----Initial value of all registers-----" << endl;
    showContent();
    fetch();
    cout<<"T2: A<-15's complement of A"<<endl;

    vector<char> temp = A;

    for (int i = 0; i < 3; i++)
    {
        temp[i] = 15 - h2d1(temp[i]);
        A[i] = d2h1(temp[i]);

    }
    
    cout << "-----Final value of all registers-----" << endl;
    showContent();
}

void cla()
{   
    cout << "-----Initial value of all registers-----" << endl;
    showContent();
    fetch();
    A[0] = '0';
    A[1] = '0';
    A[2] = '0';
    cout<<"T2: A<-0"<<endl;
    cout << "-----Final value of all registers-----" << endl;
    showContent();

}


int main() {
    /*ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif*/
    char ir1 ;
    //A = {'2', '3', 'A'};
    //B = {'0', '0', '0'};
    //MAR = {'2','1'};
    for (int i = 0; i < 10; i += 2)
    {
      RAM[i][0] = '4';
      RAM[i][1] = '6';
      RAM[i][2] = 'A';
    }

  for (int i = 1; i < 10; i += 2)
    {
      RAM[i][0] = '9';
      RAM[i][1] = '7';
      RAM[i][2] = 'B';
    }
  int i = 0;

  while (i < 10)
    {

      cin >> ir1;
      switch (ir1)
	{
	case '0':		// XCHG Operation
	  cout << "<-------Implementing XCHG operation--------->" << endl;
	  cout << "Enter the value of A:";
	  cin >> A[0] >> A[1] >> A[2];
	  cout << endl;
	  cout << "Enter the value of B:";
	  cin >> B[0] >> B[1] >> B[2];
	  cout << endl;

	  xchg (A, B);
	  break;

	case '1':		//LDA operation
	  cout << "<-------Implementing LDA operation--------->" << endl;
	  lda ();
	  break;
	case '2':		//STA operation
	  cout << "<-------Implementing STA operation--------->" << endl;
	  // cin>>MAR[0]>>MAR[1];
	  sta (MAR);
	  break;
	case '3':		//ADDC operation
	  cout << "<-------Implementing ADDC operation--------->" << endl;
	  cout << "Enter the value of A:";
	  cin >> A[0] >> A[1] >> A[2];
      cout << "Enter the value of B:";
	  cin >> B[0] >> B[1] >> B[2];
	  addc (A, B);
	  break;
	case '4':		//EXOR operation
	  cout << "<-------Implementing EXOR operation--------->" << endl;
	  cout << "Enter the value of A:";
	  cin >> A[0] >> A[1] >> A[2];
	  cout << "Enter the value of B:";
	  cin >> B[0] >> B[1] >> B[2];
	  exor (A, B);
	  break;
	case '5':		//DIV operation
	  cout << "<-------Implementing DIV operation--------->" << endl;
	   cout << "Enter the value of A:";
	  cin >> A[0] >> A[1] >> A[2];
	  cout << "Enter the value of B:";
	  cin >> B[0] >> B[1] >> B[2];
	  division (A, B);
	  break;
        case '6': //PUSH
            cout<<"<-------Implementing PUSH operation--------->"<<endl;
            cin>>A[0]>>A[1]>>A[2];
            push_iba(SP, A);
            break;
        case '7': //POP
            cout<<"<-------Implementing POP operation--------->"<<endl;
            pop_daa(SP);
            break;
        case '8': //FCMA
           cout<<"<-------Implementing FCMA operation--------->"<<endl;
           cin>>A[0]>>A[1]>>A[2];
            fcma(A);
            break;
        case '9': //CLA
            cout<<"<-------Implementing CLA operation--------->"<<endl;
            cla();
            
            break;
            
        i++;
    }

    }return 0;

}
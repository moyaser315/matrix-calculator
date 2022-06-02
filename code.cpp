#include<iostream>
using namespace std ;
int flag =0  ;
void addmat(float arr1[][10] , float arr2[][10] , int row1 ,int row2,int col1 ,int col2);
void entermat(float arr1[][10] , int row1 ,int col1);
void diffmat(float arr1[][10] , float arr2[][10] , int row1 ,int row2,int col1 ,int col2);
void multimat(float arr1[][10] , float arr2[][10] , int row1 ,int row2,int col1 ,int col2);
double delta1(float mat1[][10] , int maxrow);
double delta(float mat1[][10] , int maxrow ,float sub1[][10],double z);
void submatix(float mat[][10] ,float sub1[][10] ,int maxrow , int currentcol , int currentrow);
void inverse(float cof[][10],int row,double z,float arr2[][10]);
int approx(float x);
/*for handling unexpected cases after searching i found a function in the slides that works in c and c++ which is :
1/fail checks if the input is of the function is of the same type or not
*/
int main()
{
        unsigned int row1 ,row2, col1 , col2 ;
        cout << "Please enter dimensions of Matrix A:\n" ;
        cin >> row1 >> col1 ;
        int op ;
        if(cin.fail()){return 0 ;}
        //the dimension can't be anything but integer so if the user enter anything else it will exit
        cout << "Please enter dimensions of Matrix B:\n" ;
        cin >> row2 >> col2 ;
        if(cin.fail()){return 0 ;}

        if(row1>10 || row2>10)
        {
            return 0 ;
        }
        float arr1[10][10] , arr2[10][10] ,cof[10][10]={0};
        double z ;
        cout<<"Please enter values of Matrix A:\n" ;
        entermat(arr1 ,row1 , col1);
        if(flag == 1){return 0 ;}
        cout<<"Please enter values of Matrix B:\n" ;
        entermat(arr2 ,row2 , col2);
        if(flag == 1){return 0 ;}
        do{
        cout<< "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):\n";
        cin >> op ;
        if (cin.fail()) {return 0 ;}
        switch (op)
        {
        case 1:
             if (row1 == row2 && col1 == col2)addmat(arr1,arr2,row1,row2,col1,col2);
             else cout<< "The operation you chose is invalid for the given matrices."<<endl ;
             break;
        case 2:
            if (row1 == row2 && col1 == col2)diffmat(arr1,arr2,row1,row2,col1,col2) ;
            else cout<< "The operation you chose is invalid for the given matrices."<<endl ;
            break;
        case 3:
            if(col1 != row2) cout << "The operation you chose is invalid for the given matrices."<<endl ;
            else{multimat(arr1,arr2,row1,row2,col1,col2);}
            break;
        case 4:
            if(row2 == col2 && col1 ==  row2){
                z = delta(arr2,row2,cof,z);
                if(z==0){cout<<"The operation you chose is invalid for the given matrices."<<endl ;}
                else{
                z=1/z;
                flag = 2 ;
                delta(arr2,row2,cof,z);
                inverse(cof,row2,z,arr2);
                multimat(arr1,cof,row1,row2,col1,col2);
                flag = 0 ;
                }
            }
            else{cout<<"The operation you chose is invalid for the given matrices."<<endl ;}

            break;
        case 5:
            if(row1 == col1){
                long long x =delta1(arr1,row1);
                cout<<x<<endl;}

            else{cout<<"The operation you chose is invalid for the given matrices."<<endl ;}
            break;
        case 6:
            if(row2 == col2){
                long long x = delta1(arr2,row2);
                cout <<x<<endl;}

            else{cout<<"The operation you chose is invalid for the given matrices."<<endl ;}
            break;
        case 7:
            cout<<"Thank you!" ;
            break;

        default:
            cout<<"The operation you chose is invalid for the given matrices."<<endl ;
            break;
        }

    }
    while(op != 7);
}
//for adding the matrecies
void addmat(float arr1[][10] , float arr2[][10] , int row1 ,int row2,int col1 ,int col2)
{
    int sum[row1][col1];
    for (int i = 0; i<row1 ; i++ )
    {
        for (int k = 0; k<col1 ; k++ ){
            sum[i][k] =arr1[i][k] + arr2[i][k] ;
            cout<< approx(sum[i][k]) <<" " ;
        }
        cout << endl ;
    }
}
//for getting input
void entermat(float arr1[][10] , int row1 ,int col1){
    for (int i = 0; i<row1 ; i++ )
    {
        for (int k = 0; k<col1 ; k++ ){

            cin >> arr1[i][k] ;
            if (cin.fail()) {flag = 1;}
 //if the user accidently enter'\'with the enter it will be cleared then ignored as there's a newline the flag is changed to tell that the input is wrong to exit the program

        }
    }
}
// for substracting
void diffmat(float arr1[][10] , float arr2[][10] , int row1 ,int row2,int col1 ,int col2)
{
    int sum[row1][col1];
    for (int i = 0; i<row1 ; i++ )
    {
        for (int k = 0; k<col1 ; k++ ){
            sum[i][k] =arr1[i][k] - arr2[i][k];
            cout<< approx(sum[i][k]) <<" " ;
        }
        cout << endl ;
    }
}
/*after trying on square matrix and rectangular matrix multipling by different dimensions if ound that :
if we consider a ab * cd
1/ a changes every two loops of (b/c)
2/ b and c always change together
3/ d changes eveytime a loop of c or d happen
4/ a can't exceed the number of the new matrix row (row1)
5/ d can't exceed the number of the new matrix col(col2)
6/ b/c are the ones the loop based on so they can be either col1 or row2
*/

void multimat(float arr1[][10] , float arr2[][10] , int row1 ,int row2,int col1 ,int col2)
{
    float product[row1][col2] ;
    for(int j = 0 ; j <row1 ; j++){
        for(int i = 0 ; i < col2 ; i++)
        {   product[j][i] = 0 ;
            for(int k = 0 ; k<col1 ; k++)
            {
                product[j][i]  += (arr1[j][k] * arr2[k][i]) ;
            }
            cout<<approx( product[j][i] )<<" " ;
        }
        cout << endl ;
    }
    //j is a, i is d , b/c is k
}
/* to get deteminent we should try to substitue each square matrix by another 1 smaller by one row and column*/
void submatix(float mat[][10] ,float sub1[][10] ,int maxrow , int currentcol , int currentrow)
{
    //temorory matix row and column
    int tempr=0 ,tempc ;
    for(int i =0 ; i < maxrow ;i++ ){
        //when ever loop is on the row sent by the determinent function it will ignore the row
        if(i==currentrow)i++;
        //i assigned 0 here to reset each time it get off the loop down so it can restart as [1][0] again after the first loop ended
        tempc = 0 ;
        for(int k =0 ; k< maxrow ; k++){
            if(k==currentcol)k++;
            //the sub matrix must by one less col and row so whenever the loop as at max it will break from that loop making it reset to 0
            if(k==maxrow)break;
            sub1[tempr][tempc] = mat[i][k];
            tempc++;

        }
        tempr++;
    }

}
//it strangely outputted an error on test 6 so i made another seperate function
double delta1(float mat1[][10] , int maxrow){
        float sub[10][10] ,sign =1  ;
        double det =0 ,x ;
        if(maxrow == 1)return mat1[0][0] ;
        else if(maxrow==2){det = ((mat1[0][0]*mat1[1][1])-(mat1[0][1]*mat1[1][0]));}
        else{
            for(int i = 0 ; i<maxrow ; i++)
            {
                submatix(mat1,sub,maxrow,i,0);
                x=delta1(sub ,maxrow-1) ;
                det += sign * mat1[0][i] * x ;
                sign = -1 * sign ;

            }
        }

        return det ;
    }

double delta(float mat1[][10] , int maxrow ,float sub1[][10],double z)
{
    float sub[10][10] ,sign =1  ;
    double det =0 ,x ;
    if(maxrow == 1)return mat1[0][0] ;
    else if(maxrow==2){det = ((mat1[0][0]*mat1[1][1])-(mat1[0][1]*mat1[1][0]));}
    else{
        for(int k = 0 ; k<maxrow ; k++){
        for(int i = 0 ; i<maxrow ; i++)
        {
            submatix(mat1,sub,maxrow,i,k);
            x=delta(sub ,maxrow-1,sub1,z) ;
            //you can ignore x and just multiply the function but i was having an error and wanted to print x to check if the sub function workink properly
            det += sign * mat1[k][i] * x ;
            //i tried using pow fun instead of (sign) but it took longer in big matricies
            // i made the indicting flag to make the function make a cofactor and transpose(it was easier for me this way)
            sub1[i][k]=z*x*sign;
            sign = (-1) * sign ;
        }
        if(flag != 2){break ;}
        }
    }


    return det ;
}
//the code could have a print fun to output the results but i found printing inside easier for me
void inverse(float cof[][10],int row,double z,float arr2[][10])
{

    if (row == 2){
        cof[0][0] = z * arr2[1][1];
        cof[0][1] = (-1) * z * arr2[0][1];
        cof[1][0] = (-1) * z * arr2[1][0];
        cof[1][1] = z * arr2[0][0];
    }
    //this transpose function took more time so i ignored it still couldn't minimize the time more X(
    /*else
    {
        for(int i =0 ; i<row;i++)
        {
            for(int k =0 ; k<row ; k++)
            {
                trans[i][k] =z* cof[k][i] ;
            }

        }
    }*/
}
int approx(float x)
{
    if(x<0){
        if(x -(int)x <= -0.5){
            return (int)x-1 ;
        }
        else
            return (int) x;
    }
    else{
        if (x-(int)x >= 0.5){
            return (int)x+1 ;
        }
        else{
            return(int) x ;
        }
    }
}

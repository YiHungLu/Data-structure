//10727153 �f�y�E
 
#include <iostream>
#include <stdio.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;

bool HaveSameFactor( unsigned long long num, unsigned long long &max ) ;


int main(int argc, char** argv) {
	unsigned long long num = 0 ;
	int input = 0 ;
	unsigned long long max = 0 ;
	long long inTime = 1 ;
	int outTime ;

	cin>>input ;

	unsigned long long back2 = 0 ;
	unsigned long long back1 = 1 ;
	
	for( outTime = 0 ; outTime < input ; outTime++){
		
		num = back1 + back2 ; // �p��O��ƦC 
		back2 = back1 ;
		back1 = num ;
		
		if ( HaveSameFactor( num, max ) == true ){  // ��X�O�_����������� 
			cout<<"NO."<<outTime+1<<" "<<num<<"="<<max<<"*"<<max<<" "<<"Time : "<< inTime <<endl ;	
		}   
		
		else {   // ��X�̱��񪺨�Ӧ]�� 
			for(;max>=1;max--){
				if(num%max==0) {
					cout<<"NO."<<outTime+1<<" "<<num<<"="<<max<<"*"<<num/max<<" "<<"Time : "<< inTime <<endl ;
					break ;
				}
				inTime++ ;
			}
			
			inTime = 1 ;
		}
		
		
	
	}
	
	cout <<"outTime:"<< outTime - 1 ;

	return 0;
}

bool HaveSameFactor( unsigned long long num, unsigned long long &max ) {
	unsigned long long x = 0 ;
	for( x = 0 ; x*x < num ; x++ )
	  if(x*x==num)
	    break ;
	    
	if(x*x==num){
		max = x ;
		return true ;
	}
	
	else {
		
		max = x - 1 ;
		
		return false ;
	}
	return true ;
}

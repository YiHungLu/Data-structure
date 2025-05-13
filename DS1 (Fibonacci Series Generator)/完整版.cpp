//10727153呂宜鴻  10727155 曾博輝
 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
bool HaveSameFactor( unsigned long long num, unsigned long long &max ) ;

 
using namespace std;

void MissionOne( int input ) {     // 處理任務一的主程式 
	unsigned long long num = 0 ;
	unsigned long long max = 0 ;
	long long inTime = 1 ;
	int outTime ;


	unsigned long long back2 = 0 ;
	unsigned long long back1 = 1 ;
	
	for( outTime = 0 ; outTime < input ; outTime++){
		
		num = back1 + back2 ; // 計算費氏數列 
		back2 = back1 ;
		back1 = num ;
		
		if ( HaveSameFactor( num, max ) == true ){  // 若為完全平方數 ，則直接取得最接近的因數 
			cout<<"NO."<<outTime+1<<" "<<num<<"="<<max<<"*"<<max<<" "<<"Time : "<< inTime <<endl ;	
		}   
		
		else {   // 找出最接近的兩個因數 
			for(;max>=1;max--){
				if(num%max==0) {
					cout<<"NO."<<outTime+1<<" "<<num<<"="<<max<<"*"<<num/max<<" "<<"Inner loop : "<< inTime <<endl ;
					break ;
				}
				inTime++ ;
			}
			
			inTime = 1 ;
		}
		
		
	
	}
	
	cout <<"outTime:"<< outTime - 1 <<endl ;   

}

bool HaveSameFactor( unsigned long long num, unsigned long long &max ) {  // 找出是否為完全平方數 
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

unsigned long long Find( unsigned long long target, unsigned long long test ) ;
unsigned long long Openstem( unsigned long long target ) ;
unsigned long long Answer ( unsigned long long test, unsigned long long now, unsigned long long &intimes, unsigned long long plus ) ;

void MissionTwo( int times ) {
	unsigned long long now = 1 ;
	unsigned long long back = 0 ;
	unsigned long long plus = 1 ;
	unsigned long long outtimes = 0 ;

		outtimes = 0 ;
		Count( times, now, back, plus, outtimes ) ;
		printf( "outTime %d\n", outtimes ) ; 

 
} // missionTwo()

unsigned long long Find( unsigned long long target, unsigned long long test ) {
   if ( test*test == target )
        return test ;
   else if ( test*test < target ) {
   	    test++ ;
    	return Find( target, test ) ;
    } // if
   else {
        test-- ;
   		return test ;
   } // else
} // Find()

unsigned long long Openstem( unsigned long long target ) {
	unsigned long long returnum = 0 ;
	returnum = sqrt( target ) ;
	return returnum ;
} // Openstem()

unsigned long long Answer ( unsigned long long test, unsigned long long now, unsigned long long &intimes, unsigned long long plus ) {
	if ( intimes > 10000000 ) {
		printf( "NO.%I64u %I64u = (Inner recursion: more than  10000000 times)\n", plus, now ) ;
		return test ;
    } // if
	else if ( now % test == 0  ) 
		return test ;
	else {
	    test-- ;
	    intimes++ ;
		return Answer( test, now, intimes, plus ) ;
    } // else
} // Answer()
    

unsigned long long Count( int times, unsigned long long now, unsigned long long back, unsigned long long plus, unsigned long long &outtimes ) {
	unsigned long long test = 1 ;
	unsigned long long temp = 0 ;
	unsigned long long answer = 0 ;
	unsigned long long intimes = 1 ;
	if ( times != 0 ) {
		temp = now ;
		now = now + back ;
		back = temp ;
		test = Openstem( now ) ;
		answer = Answer( test, now, intimes, plus ) ;	
		if ( intimes <= 10000000 )
			printf( "NO.%I64u %I64u = %I64u * %I64u Time : %I64u\n", plus, now, answer, now/answer, intimes ) ;
	 	times-- ;
	 	plus++ ;
	 	outtimes ++ ;
	 	Count( times, now, back, plus, outtimes ) ;
	} // if

} // Count()

int main(){
	cout<<"Fibonacci Serice Generator"<<endl ;
	cout<<"0 Quit"<<endl ;
	cout<<"1. Iterative generation"<<endl ;
	cout<<"2. Recursive generation"<<endl ;
	cout<<"Input a command(0, 1, 2): " ;
	int missionNumber ;
	cin>>missionNumber ;
	int times ;
	while(missionNumber!=0){

			
		if( missionNumber ==1 )	{
			cout<<"Input a number: " ;
			cin>>times ;
			if(times>92)
				times = 92 ;
			MissionOne(times) ;
		}
		
		else if( missionNumber ==2 ) {
			cout<<"Input a number: " ;
			cin>>times ;
			if(times>92)
				times = 92 ;	
			MissionTwo(times) ;
		}
		
		cout<<"Fibonacci Serice Generator"<<endl ;
		cout<<"0 Quit"<<endl ;
		cout<<"1. Iterative generation"<<endl ;
		cout<<"2. Recursive generation"<<endl ;
		cout<<"Input a command(0, 1, 2): " ;			
		cin>>missionNumber ;
	}
			
			
}

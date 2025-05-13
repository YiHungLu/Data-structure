//10727153 呂宜鴻 10727155 曾博暉 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

struct collegeType{
	string rawR ;
	string name ;
	int gNum ;	
	int number ;
};

struct tree{
	int number ;
	int gNum ;
	tree* left ;
	tree* right ;
};
class ClassList{
	string fileName  ;
	string fileNumber ;
	vector<collegeType>aList ;
	vector<collegeType>minTree ;
	vector<collegeType>minMaxTree ;
	tree* gNumTree ;
	tree* nameTree ;
	
	int findGNum( int i){  // 找出字串中的畢業人數  
		int num = 0 ;
		int x ;
		int t  = 0;
		for(x = 0 ; x<aList[i].rawR.size() ;x++){
			if(aList[i].rawR[x] =='\t')
				t++ ;
			if(t==8)
				break ;
		}
		
		x++ ;
		
		for(; aList[i].rawR[x] !='\t' ; x++)
			num = num*10 + ((int)aList[i].rawR[x] - 48 );
		return num ;
	}

	void SetGNum(){ //將畢業人數設定到aList中 
		for(int i = 0 ;i <aList.size() ; i++)
			aList[i].gNum = findGNum(i) ;
	}

	void CheckMinTree(){
		int temp ;
		for(int i = 0 ; i<minTree.size() ; i++){
			if(minTree[i].gNum>minTree[(i-1)/2]){
				temp = minTree[i].gNum ;
				minTree[i].gNum = minTree[(i-1)/2].gNum ;
				minTree[(i-1)/2].gNum = temp ;

				temp = minTree[i].number ;
				minTree[i].number = minTree[(i-1)/2].number ;
				minTree[(i-1)/2].number = temp ;			
			}
		}
	}
	
	void MinTree(){
		minTree.clear() ;
		minTree.push_back(aList[0]) ;
		int i = 1 ;
		for( i = 1 ; i<aList.size() ; i++){
			minTree.push_back(aList[i]) ;
			CheckMinTree() ;
		}
	}
	
	public:	
	

		
	bool Read(){  // 讀入input 
		
		aList.clear() ;
		string temp ;
		int num ;
		nameTree = NULL ;
		gNumTree = NULL ;
		cout<<endl<<"FileNumber : " ;
		
		cin>>fileNumber ;
		
		fileName = "input" + fileNumber + ".txt" ;
		
		FILE *fPtr = NULL;
		fPtr=fopen(fileName.c_str(),"r");
		
		char ch ;
		int count = 1 ;
		collegeType ct ;
		if(fPtr==NULL)
			cout<<"ERROR FILE"<<endl ;
					
		else{
			int line = 0;
			while(line<3){
				fscanf(fPtr, "%c", &ch) ;
				if(ch=='\n')
					line++ ;
			}
			
			fscanf(fPtr, "%c", &ch) ;
			while(ch=='\n')
				fscanf(fPtr, "%c", &ch) ;
				
			do{
				
				if(ch=='\n'){
					ct.rawR = temp ;
					ct.number = number ;
					number++ ;
					aList.push_back(ct) ;
					temp = "\0" ;					
				}
				else{
					temp += ch ;					
				}
				
				
			}while(fscanf(fPtr, "%c", &ch)!=EOF);
			
			if(temp.size()>1){
				ct.rawR = temp ;
				ct.number = number ;
				aList.push_back(ct) ;
				temp = "" ;	
			}
			
			fclose(fPtr);
			
			SetGNum() ;	
			return true ;
			
				
		}
		return false ;
	}

	void PrintM1(){
		Read() ;
		MinTree() ;
		cout<<endl<<minTree[0].number<<","<<minTree[0].gNum<<endl ;
		cout<<endl<<minTree[minTree.size()-1].number<<","<<minTree.gNum[minTree.size()-1]<<endl ;
		int i = 1 ;
		int leftBot ;
		while(i <= minTree.size()){
			leftBot = i ;
			i = i*2 ;
		}
		
		cout<<endl<<minTree[leftBot-1].number<<","<<minTree[leftBot-1].gNum<<endl ;		
	}
};

int main(int argc, char **argv {
	ClassList list ;
	list.PrintM1() ;
	return 0;
}

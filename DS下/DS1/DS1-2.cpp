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
			if(minTree[i].gNum<minTree[(i-1)/2].gNum){
				temp = minTree[i].gNum ;
				minTree[i].gNum = minTree[(i-1)/2].gNum ;
				minTree[(i-1)/2].gNum = temp ;

				temp = minTree[i].number ;
				minTree[i].number = minTree[(i-1)/2].number ;
				minTree[(i-1)/2].number = temp ;			
			}
		}
	}

	void CheckMinMaxTree(){
		int temp ;
		int changeMode = 4 ;
		bool mode = true ;
		bool stop = false ;
		for(int i = 0 ; i<minTree.size() ; i++){
			if(i+1 == changeMode){
				mode = !mode ;
				changeMode = changeMode*2 ;
			}
			
			if(mode){
				if(minTree[i].gNum<minTree[(i-1)/2].gNum){
					temp = minTree[i].gNum ;
					minTree[i].gNum = minTree[(i-1)/2].gNum ;
					minTree[(i-1)/2].gNum = temp ;

					temp = minTree[i].number ;
					minTree[i].number = minTree[(i-1)/2].number ;
					minTree[(i-1)/2].number = temp ;			
				}
				
				else if(i!=1&&i!=2){
					stop = false ;
					for(int j = i ; !stop ; j = (((j-1)/2)-1)/2 ){
						if(minTree[j].gNum>minTree[(((j-1)/2)-1)/2].gNum){
							temp = minTree[j].gNum ;
							minTree[j].gNum = minTree[(((j-1)/2)-1)/2].gNum ;
							minTree[(((j-1)/2)-1)/2].gNum = temp ;

							temp = minTree[j].number ;
							minTree[j].number = minTree[(((j-1)/2)-1)/2].number ;
							minTree[(((j-1)/2)-1)/2].number = temp ;							
						}
						else{
							stop = true ;
						}
						
						if((((j-1)/2)-1)/2 == 0){
							stop = true ;
						}
					}
				}
			}
			
			else if(!mode){
				if(minTree[i].gNum>minTree[(i-1)/2].gNum){
					temp = minTree[i].gNum ;
					minTree[i].gNum = minTree[(i-1)/2].gNum ;
					minTree[(i-1)/2].gNum = temp ;

					temp = minTree[i].number ;
					minTree[i].number = minTree[(i-1)/2].number ;
					minTree[(i-1)/2].number = temp ;		
				}

				else{
					stop = false ;
					for(int j = i ; !stop ; j = (((j-1)/2)-1)/2 ){
						if(minTree[j].gNum<minTree[(((j-1)/2)-1)/2].gNum){
							temp = minTree[j].gNum ;
							minTree[j].gNum = minTree[(((j-1)/2)-1)/2].gNum ;
							minTree[(((j-1)/2)-1)/2].gNum = temp ;

							temp = minTree[j].number ;
							minTree[j].number = minTree[(((j-1)/2)-1)/2].number ;
							minTree[(((j-1)/2)-1)/2].number = temp ;							
						}
						else{
							stop = true ;
						}
						
						if((((j-1)/2)-1)/2 == 0){
							stop = true ;
						}
					}
				}				
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

	void MinMaxTree(){
		minTree.clear() ;
		minTree.push_back(aList[0]) ;
		int i = 1 ;
		for( i = 1 ; i<aList.size() ; i++){
			minTree.push_back(aList[i]) ;
			CheckMinMaxTree() ;
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
		int number = 1 ;
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

	void Print(int cmd){
		Read() ;
		if(cmd == 1)
			MinTree() ;
		else if(cmd == 2)
			MinMaxTree() ;
			 
		cout<<endl<<minTree[0].number<<","<<minTree[0].gNum<<endl ;
		cout<<endl<<minTree[minTree.size()-1].number<<","<<minTree[minTree.size()-1].gNum<<endl ;
		int i = 1 ;
		int leftBot ;
		while(i <= minTree.size()){
			leftBot = i ;
			i = i*2 ;
		}
		
		cout<<endl<<minTree[leftBot-1].number<<","<<minTree[leftBot-1].gNum<<endl ;		
	}


};


int main(int argc, char** argv) {
	ClassList list ;
	int cmd ;
	cin>>cmd ;
	while(cmd!=0){
		list.Print(cmd) ;
		cin>>cmd ;
	}
	return 0;
}

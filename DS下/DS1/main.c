//10727153 �f�y�E 10727155 ���շu 
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
	vector<collegeType>aNumList ;
	vector<collegeType>aNameList ;
	tree* gNumTree ;
	tree* nameTree ;
	
	int findGNum( int i){  // ��X�r�ꤤ�����~�H��  
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

	void SetGNum(){ //�N���~�H�Ƴ]�w��aList�� 
		for(int i = 0 ;i <aList.size() ; i++)
			aList[i].gNum = findGNum(i) ;
	}
	
	
	
	
	void Set(tree* tree){ //��l�� 
		tree->left = NULL ;
		tree->right = NULL ;
	}
	
	void Swap(int &a, int &b){
		int temp ;
		temp = a ;
		a = b ;
		b = temp ;
	}
	
	void Check(tree* gNumTree){
		int tempGNum ;
		int tempNum ;
		bool change = false ;
		if(gNumTree!=NULL){
			if(gNumTree->gNum > gNumTree->left->gNum){
				Swap(gNumTree->gNum ,gNumTree->left->gNum) ;
				Swap(gNumTree->number ,gNumTree->left->number) ;
			}
			
			Check(gNumTree->left) ;
			
			if(gNumTree->gNum > gNumTree->right->gNum){
				Swap(gNumTree->gNum ,gNumTree->right->gNum) ;
				Swap(gNumTree->number ,gNumTree->right->number) ;
			}
						
			Check(gNumTree->right) ;	
		
		}
			
	}
	
	void MakeGNumTree(){ //�إ߲��~�H�ƪ��� 
		if(gNumTree==NULL){
			gNumTree = new tree ;
			Set(gNumTree) ;
			gNumTree->gNum = aList[0].gNum ;
			gNumTree->number = aList[0].number ;
		}
		
		bool check = false ;
		
		for(int i = 1 ; i<aList.size() ; i++){
			MakeTree(i, gNumTree) ;
			Check(gNumTree) ;
		}
		
		Check(gNumTree) ;
							
	}
	
	void MakeTree(int i, tree* tree){
		if(tree==NULL){
			tree = new tree ;
			Set(tree) ;
			tree->gNum = aList[i].gNum ;
			tree->number = aList[i].number ;			
		}
		
		else if(tree->left==NULL){
			MakeTree(i,tree->left) ;
		}
		
		else if(tree->right==NULL){
			MakeTree(i,tree->right) ;
		}
		
		
		
	}
	
	void MakeMinTree( int &i){
		if(gNumTree==NULL){
			gNumTree = new tree ;
			Set(gNumTree) ;
			gNumTree->gNum = aList[i].gNum ;
			gNumTree->number = aList[i].number ;
		}
		
		else{
		}
		
	}

		
	public:	
	

		
	bool Read(){  // Ū�Jinput 
		
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
	
	
	
};

int main(int argc, char *argv[]) {
	return 0;
}

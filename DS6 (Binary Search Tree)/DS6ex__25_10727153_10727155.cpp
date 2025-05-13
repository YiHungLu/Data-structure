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
};

struct tree{
	int index ;
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
	
	void Cut(string &temp){
		int x ;
		int t  = 0;
		for(x = 0 ; x<temp.size() ;x++){
			if(temp[x] =='\t')
				t++ ;
			if(t==9)
				break ;
		}
		
		
		temp = temp.assign(temp,5, x-5) ;	
		
		t = 0 ;
		int y ;
		int index1,index2 ;
		for(y = 0 ; y<temp.size() ;y++){
			if(temp[y] =='\t'){
				t++ ;
				if(t==1)
					index1 = y ;
				if(t==2)
					index2 = y ;
			}
		}
		string temp1,temp2 ;
		temp1 = temp1.assign(temp,0, index1) ;
		temp2 = temp2.assign(temp, index2, temp.size()-index2) ;
		temp = temp1  + temp2;
	}
	
	string FindName(int i){  //找出字串中的學校名稱 
		string temp = "\0" ;
		int x ;
		int t  = 0;
		for(x = 0 ; x<aList[i].rawR.size() ;x++){
			if(aList[i].rawR[x] =='\t')
				t++ ;
			if(t==1)
				break ;
		}
		
		x++ ;
		
		for(; aList[i].rawR[x] !='\t' ; x++)
			temp += aList[i].rawR[x] ;
		return temp ;					
	}
	
	void SetName(){ //將學校名稱設定到aList中 
		for(int i = 0 ;i <aList.size() ; i++)
			aList[i].name = FindName(i) ;
	}
	
	int CountHeight(tree* tree, int height){ //計算高度 
		int left ;
		int right ;
		if(tree->left!=NULL && tree->right!=NULL){
			height ++ ;			
			left = CountHeight(tree->left, height) ;
			right = CountHeight(tree->right, height) ;
			
			if(left>right)
				return left ;
			else 
				return right ;
		}
		
		else if(tree->left!=NULL && tree->right==NULL){
			return CountHeight(tree->left, height+1) ;			
		}
		
		else if(tree->left==NULL && tree->right!=NULL){
			return CountHeight(tree->right, height+1) ;			
		}
		
		else{
			return height ;
		}
			
	}
	
	void Set(tree* tree){ //初始化 
		tree->left = NULL ;
		tree->right = NULL ;
	}
	
	void MakeGNumTree(int i,tree* gNumTree){ //建立畢業人數的樹 
		if(aList[i].gNum < aList[gNumTree->index].gNum){
			if(gNumTree->left == NULL){
				gNumTree->left = new tree ;
				gNumTree->left->index = i ;
				Set(gNumTree->left) ;
			}
			
			else{
				MakeGNumTree(i,gNumTree->left) ;
			}
		}
		
		else{
			if(gNumTree->right == NULL){
				gNumTree->right = new tree ;
				gNumTree->right->index = i ;
				Set(gNumTree->right) ;
			}
			
			else{
				MakeGNumTree(i,gNumTree->right) ;
			}
		}
								
	}

	void MakeNameTree(int i,tree* nameTree){  //建立學校名稱的樹 
		
		if(aList[i].name < aList[nameTree->index].name){
			if(nameTree->left == NULL){
				nameTree->left = new tree ;
				nameTree->left->index = i ;
				Set(nameTree->left) ;
			}
			
			else{
				MakeNameTree(i,nameTree->left) ;
			}
		}
		
		else{
			if(nameTree->right == NULL){
				nameTree->right = new tree ;
				nameTree->right->index = i ;
				Set(nameTree->right) ;
			}
			
			else{
				MakeNameTree(i,nameTree->right) ;
			}
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
					aList.push_back(ct) ;
					temp = "\0" ;					
				}
				else{
					temp += ch ;					
				}
				
			}while(fscanf(fPtr, "%c", &ch)!=EOF);
			
			if(temp.size()>1){
				ct.rawR = temp ;
				aList.push_back(ct) ;
				temp = "" ;	
			}
			
			fclose(fPtr);
			
			SetGNum() ;
			SetName() ;
			for(int y = 0 ; y<aList.size() ; y++)
				Cut(aList[y].rawR) ;
			string temp ;
			for(int j = 0 ; j < aList.size()  ;j++)
				cout<<"["<<j+1<<"]"<<"\t"<< aList[j].rawR<<endl ;	
			return true ;
			
				
		}
		return false ;
	}
	
	
	void MakeGNum(){ //建立二元樹 (畢業人數) 和印出樹高 
		gNumTree = new tree ;
		gNumTree->index = 0 ;
		Set(gNumTree) ;
		for(int i = 1 ; i<aList.size() ; i++)
			MakeGNumTree(i, gNumTree) ;
		tree*temp ;
		temp = gNumTree ;
		cout<<endl<<"Tree heights:"<<endl ;
		cout<<"{Number of graduates} = "<<CountHeight(gNumTree,1) <<endl;
	}
	
	void MakeName(){ //建立二元樹 (學校名稱) 和印出樹高
		nameTree = new tree ;
		nameTree->index = 0 ;
		Set(nameTree) ;
		for(int i = 1 ; i<aList.size() ; i++)
			MakeNameTree(i, nameTree) ;
		tree*temp ;
		temp = nameTree ;
		cout<<"{School name} = "<<CountHeight(nameTree,1)<<endl ;		
	}
	
	
	void FindNum(tree*tree, int num){ //找出不大於輸入的值的資料 
		if(aList[tree->index].gNum >= num){
			aNumList.push_back(aList[tree->index]) ;
			if(tree->left!=NULL)
				FindNum(tree->left, num) ;
			if(tree->right!=NULL)
				FindNum(tree->right, num) ;
		}
		
		else if(aList[tree->index].gNum < num){
			if(tree->right!=NULL)
				FindNum(tree->right, num) ;
		}
	}
	
	void FindName(tree*tree, string name){ //找出相同名稱的資料 
		if(aList[tree->index].name >= name){
			if(aList[tree->index].name == name)
				aNameList.push_back(aList[tree->index]) ;
			if(tree->left!=NULL)
				FindName(tree->left, name) ;
			if(tree->right!=NULL)
				FindName(tree->right, name) ;
		}
		
		else if(aList[tree->index].name < name){
			if(tree->right!=NULL)
				FindName(tree->right, name) ;
		}
	}
	
	void Print(int num){ // 印出任務二、三的結果 
		if(num==2){
			int num ;
			cout<<endl << "Input a number : " ;
			cin>>num ;
			FindNum(gNumTree, num) ;
			cout<<"search result : "<<endl ;
			if(aNumList.size()<=0)
				cout<<"There is no match."<<endl ;
			for(int i = 0 ; i<aNumList.size() ; i++)
				cout<<"["<<i+1<<"]"<<"\t"<<aNumList[i].rawR<<endl ;
		}
		
		else if(num==3){
			string name ;
			cout<<endl << "Input a name : " ;
			cin>>name ;
			FindName(nameTree, name) ;
			cout<<"search result : "<<endl ;
			if(aNameList.size()<=0)
				cout<<"There is no match."<<endl ;
			for(int i = 0 ; i<aNameList.size() ; i++)
				cout<<"["<<i+1<<"]"<<"\t"<<aNameList[i].rawR<<endl ;
		}
	}	
}; 
int main(int argc, char** argv) {
	ClassList list ;
	int cmd ;
	bool read = false ;
	cout<<endl<<"0. Quit"<<endl<<"1. Create Two Binary Search Trees"<<endl<<"2. Search by Number of Graduates"<<endl<<"3. Search by School Name"<<endl<<"input a command(0,1,2,3) :" ;
	cin>>cmd ;
	while(cmd!=0){
		if(cmd==1){
			if(list.Read() )
				read = true ;
			else
				read = false ;
			list.MakeGNum() ;
			list.MakeName() ;
		}
		
		else if(cmd==2||cmd==3){
			if(!read)
				cout<<"Please choose command 1 first!"<<endl ;
			else
				list.Print(cmd) ;
		}
		
		
		cout<<endl<<"0. Quit"<<endl<<"1. Create Two Binary Search Trees"<<endl<<"2. Search by Number of Graduates"<<endl<<"3. Search by School Name"<<endl<<"input a command(0,1,2,3) :" ;
		cin>>cmd ;		

	}
	return 0;
}

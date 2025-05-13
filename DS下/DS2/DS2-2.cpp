//10727153 呂宜鴻 10727155 曾博暉 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <stack>    //push,pop,top

#define PTR_NUM 3
#define KEY_NUM PTR_NUM-1

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
typedef struct slotT{

	vector<int>	rSet;
	string key ;

} slotType;

typedef struct nT{

	slotType data[KEY_NUM];
	struct nT *link[PTR_NUM];
	struct nT *parent;

} nodeType;

typedef struct pointT{
	
	nodeType *pnode;
	int pidx;
	
} pointType;

typedef struct bT{
	
	slotType slot;
	nodeType *link;
	
} blockType;

struct twthrtree {
	vector<int> firlist ;
	vector<int> seclist ;
	string first ;
	string second ;
	twthrtree *pre ;
	twthrtree *left ;
	twthrtree *right ;
	twthrtree *middle ;
};

//struct College {
//	int number ;
//	string name ;
//	string information ;
//}; 

typedef twthrtree* ttTree ;

struct collegeType{
	string rawR ;
	string name ;
	int number ;
	string information ;
	int gNum ;	
};

struct AVLType{
	int gNum ;
	vector<int> number ;
	AVLType *left ;
	AVLType *right ;
};

class BuildTree{
	string fileName  ;
	string fileNumber ;
	vector<collegeType>aList ;
	AVLType* tree ;
	ttTree tttree ;
	
	void Print2() {
		int i = 0 ;
		while ( i < aList.size() ) {
			cout << aList[i].information << '\n' ;
			i++ ;
		} // while
	} // Print()

	void Print( ttTree tree ) {
		int index = 1 ;
		int i = 0 ;
		if ( tree->second != "XXX" ) {
			vector<int> num = tree->seclist ;
			while ( i < num.size() ) {
				cout << index << ": " << "[" << num[i]  << "]" << " " ;
				cout << aList[num[i]-1].information << '\n' ;
				index++ ;
				i++ ;
			} // while
		}
		
		i = 0 ;
		vector<int> num = tree->firlist ;
		while ( i < num.size() ) {
			cout << index << ": " << "[" << num[i]  << "]" << " " ;
			cout << aList[num[i]-1].information << '\n' ;
			index++ ;
			i++ ;
		} // while
		

	} // Print()	
	
	
	void Cut( string chs, collegeType &ct ) {
		ct.name = "" ;
		ct.information = "" ;
		string temp ;
		int i = 0 ;
		int tab = 0 ;
		while ( chs[i] != '\n' ) {
			if ( chs[i] == '\t' ) {
				tab++ ;
			}
			
			if ( tab == 1 ) {
				i++ ;
				while ( chs[i] != '\t' ) {
					ct.name = ct.name + chs[i] ;
					i++ ;
				} // while	
				ct.information = ct.name + ", " ;
				tab++ ;
			}
			else if ( tab == 3 ) {
				i++ ;
				while ( tab != 6 ) {
					
					if ( chs[i] == '\t' ) {
						tab++ ;
						ct.information = ct.information + ", " ;
					}
					else {
						ct.information = ct.information + chs[i] ;
					}
					
					i++ ;
				} // while					
			}
			else if ( tab == 8 ) {
				i++ ;
				while ( chs[i] != '\t' ) {
					ct.information = ct.information + chs[i] ;
					i++ ;
				} // while	
				break ;			
			}		
			i++ ;	
		}	
			
	} // Cut()
	
	ttTree SetNode( ttTree previous ) {
		ttTree tree ;
		tree = new twthrtree() ;
		tree->first = "XXX" ;
		tree->second = "XXX" ;
		tree->left = NULL ;
		tree->middle = NULL ;
		tree->right = NULL ;
		tree->pre = previous ;
		return tree ;
	} // Set()
	
	int Counthigh( ttTree tree ) {
		int height = 0 ;
		while ( tree != NULL ) {
			height++ ;
			tree = tree->left ;
		}
		return height ;
	} // Counthigh()
	
	int Countnode( ttTree tree ) {
		if ( tree != NULL ) {
			return 1 + Countnode( tree->left ) + Countnode( tree->right ) + Countnode( tree->middle ) ;
		}
		else {
			return 0 ;
		}

	} // Countnode()
	

	
	void Distribute( vector<int> num, string name, ttTree cur, ttTree limit ) {
		twthrtree* temp1 = NULL ;	
		twthrtree* temp2 = NULL ;	
		twthrtree* temp3 = NULL ;	
		twthrtree* temp4 = NULL ;			//用來存分裂的四個點 
		
		twthrtree* tf1 = SetNode( NULL ) ;
		tf1->first = cur->first ;
		tf1->firlist = cur->firlist ;
		twthrtree* tf2 = SetNode( NULL ) ;		//用來存父親節點分裂成的兩個點 
		tf2->first = cur->second ;
		tf2->firlist = cur->seclist ;
		twthrtree* father = NULL ;		
		father = cur->pre ;
		while ( father != limit ) {
			if ( cur->second > father->second ) {		//分裂的點在右邊 
				temp1 = father->left ;
				temp2 = father->middle ;
				temp3 = tf1 ;
				temp4 = tf2 ;
			}
			else if ( cur->first < father->first ) {	//分裂的點在左邊 
				temp4 = father->right ;
				temp3 = father->middle ;
				temp1 = tf1 ;
				temp2 = tf2 ;
			}
			else if ( cur->first > father->first && cur->second < father->second ) {	//分裂的點在中間 
				temp1 = father->left ;
				temp4 = father->right ;
				temp2 = tf1 ;
				temp3 = tf2 ;
			}
			tf1 = SetNode( NULL ) ;
			tf2 = SetNode( NULL ) ;
			tf1->first = father->first ;
			tf1->firlist = father->firlist ;
			tf1->left = temp1 ;
			tf1->right = temp2 ;
			temp1->pre = tf1 ;
			temp2->pre = tf1 ;
			tf2->first = father->second ;
			tf2->firlist = father->seclist ;
			tf2->left = temp3 ;
			tf2->right = temp4 ;
			temp3->pre = tf2 ;
			temp4->pre = tf2 ;
			
			cur = cur->pre ;		//繼續往上 
			father = cur->pre ;
		}
		
		if ( limit != NULL ) {
			if ( tf2->first > limit->second ) {
				limit->right = tf2 ;
				limit->middle = tf1 ;
				tf2->pre = limit ;
				tf1->pre = limit ;
			}
			else if ( tf1->first < limit->first ) {
				limit->left = tf1 ;
				limit->middle = tf2 ;
				tf2->pre = limit ;
				tf1->pre = limit ;
			}
		}
		else {
			tttree = SetNode( NULL ) ;  //創新的根把新的樹接上 
			tttree->first = name ;
			tttree->firlist = num ;
			tttree->left = tf1 ;
			tf1->pre = tttree ;
			tttree->right = tf2 ;
			tf2->pre = tttree ;
		}
		
	} // Distribute()
	
	
	void Spilt( ttTree &cur, string name, vector<int> num, vector<int> &temp, string &temp2, ttTree &limit ) {
		if ( cur->first != "XXX" && cur->second == "XXX" ) {
			if ( cur->first < name ) {
				cur->second = name ;
				cur->seclist = num ;
			}
			else {
				cur->second = cur->first ;
				cur->seclist = cur->firlist ;
				cur->first = name ;
				cur->firlist = num ;
			}	
			limit = cur ;
		}
		else if ( cur->first != "XXX" && cur->second != "XXX" ) {
			if ( name < cur->first ) {
				temp2 = cur->first ;
				temp = cur->firlist ;
				cur->first = name ;
				cur->firlist = num ;
				name = temp2 ;
				num = temp ;
			}
			else if ( name > cur->second ) {
				temp2 = cur->second ;
				temp = cur->seclist ;
				cur->second = name ;
				cur->seclist = num ;
				name = temp2 ;
				num = temp ;
			}
			else {
				temp2 = name ;
				temp = num ;
			}
			
			if ( cur->pre != NULL ) {
				Spilt( cur->pre, name, num, temp, temp2, limit ) ;
			}
		}
	} // Spilt()
		
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

	void Set(AVLType* tree){ //初始化 
		tree->left = NULL ;
		tree->right = NULL ;
	}

	AVLType* Add(int i,AVLType* gNumTree){
		if(aList[i].gNum < gNumTree->gNum){
			if(gNumTree->left == NULL){
				gNumTree->left = new AVLType ;
				gNumTree->left->number.push_back(i) ;
				gNumTree->left->gNum = aList[i].gNum ;
				Set(gNumTree->left) ;
			}
			
			else{
				gNumTree->left = Add(i,gNumTree->left) ;
				gNumTree = Check(gNumTree) ;
			}
		}
		
		else if(aList[i].gNum > gNumTree->gNum){
			if(gNumTree->right == NULL){
				gNumTree->right = new AVLType ;
				gNumTree->right->number.push_back(i) ;
				gNumTree->right->gNum = aList[i].gNum ;
				Set(gNumTree->right) ;
			}
			
			else{
				gNumTree->right = Add(i,gNumTree->right) ;
				gNumTree = Check(gNumTree) ;
			}
		}
	
		return gNumTree ;
	}
	
	AVLType *Search(AVLType* tree, int num){
		if(tree->gNum == num)
			return tree ;
			
		else if(tree->gNum > num){
			if(tree->left!=NULL)
				return Search(tree->left, num) ;
		}
		
		else if(tree->gNum < num){
			if(tree->right!=NULL)
				return Search(tree->right, num) ;
		}
		
		return NULL ;
	}

	int Height(AVLType* tree, int height){ //計算高度 
		int left ;
		int right ;
		if(tree->left!=NULL && tree->right!=NULL){
			height ++ ;			
			left = Height(tree->left, height) ;
			right = Height(tree->right, height) ;
			
			if(left>right)
				return left ;
			else 
				return right ;
		}
		
		else if(tree->left!=NULL && tree->right==NULL){
			return Height(tree->left, height+1) ;			
		}
		
		else if(tree->left==NULL && tree->right!=NULL){
			return Height(tree->right, height+1) ;			
		}
		
		else{
			return height ;
		}
			
	}

	int CountAVLNode(AVLType* tree, int node){ //計算高度 
		int left = 0 ;
		int right = 0 ;
		if(tree->left!=NULL && tree->right!=NULL){			
			left = CountAVLNode(tree->left, node) ;
			right = CountAVLNode(tree->right, node) ;
 
			return right + left + 1 ;
		}
		
		else if(tree->left!=NULL && tree->right==NULL){
			return CountAVLNode(tree->left, node)+1 ;			
		}
		
		else if(tree->left==NULL && tree->right!=NULL){
			return CountAVLNode(tree->right, node)+1 ;			
		}
		
		else{
			return 1 ;
		}
			
	}
		
	AVLType *LL_Rotate( AVLType *x ){
		AVLType *y ;
		y = x->left ;
		x->left = y->right ;
		y->right = x ;
		return y ;
	}

	AVLType *RR_Rotate( AVLType *x ){
		AVLType *y ;
		y = x->right ;
		x->right = y->left ;
		y->left = x ;
		return y ;
	}
	
	AVLType *LR_Rotate(AVLType *x){
		AVLType *y ;
		AVLType *z ;
		y = x->left;
		z = y->right;
		
		y->right = z->left;
		z->left = y;
		x->left = z;
		
		x->left = z->right;
		z->right = x;
		return z;
	}
	
	AVLType *RL_Rotate(AVLType *x){
		
		AVLType *y ;
		AVLType *z ;
		y = x->right;
		z = y->left;
		
		y->left = z->right;
		z->right = y;
		x->right = z;
		
		x->right = z->left;
		z->left = x;
		
		return z ;

	}
		
	AVLType *Check(AVLType *tree){
		int left,right;
		if(tree->left!=NULL&&tree->right!=NULL){
			if((Height(tree->left,1)-Height(tree->right,1))>1){
				if((Height(tree->left->left,1)-Height(tree->left->right,1))>0)
					tree = LL_Rotate(tree) ;
				else if((Height(tree->left->left,1)-Height(tree->left->right,1))<0)
					tree = LR_Rotate(tree) ;
			}	
		
			else if((Height(tree->left,1)-Height(tree->right,1))<-1){
				if((Height(tree->right->left,1)-Height(tree->right->right,1))>0){
					tree = RL_Rotate(tree) ;
				}					
				else if((Height(tree->right->left,1)-Height(tree->right->right,1))<0)
					tree = RR_Rotate(tree) ;
			}
		}
		
		else if(tree->left==NULL && tree->right!=NULL){
			if((0-Height(tree->right,1))<-1){
				if(tree->right->left!=NULL&&tree->right->right!=NULL){							
					if((Height(tree->right->left,1)-Height(tree->right->right,1))>0){
						tree = RL_Rotate(tree) ;
					cout<<endl<<"a"<<endl ;						
					}
					else if((Height(tree->right->left,1)-Height(tree->right->right,1))<0)
						tree = RR_Rotate(tree) ;
				}
				
				else if(tree->right->left!=NULL&&tree->right->right==NULL){
					tree = RL_Rotate(tree) ;
				}
				
				else if(tree->right->left==NULL&&tree->right->right!=NULL){
					tree = RR_Rotate(tree) ;
				}
			}			
		}
		
		else if(tree->left!=NULL && tree->right==NULL){
			if((Height(tree->left,1)-0)>1){
				if(tree->left->left!=NULL&&tree->left->right!=NULL){
					if((Height(tree->left->left,1)-Height(tree->left->right,1))>0)
						tree = LL_Rotate(tree) ;
					else if((Height(tree->left->left,1)-Height(tree->left->right,1))<0)
						tree = LR_Rotate(tree) ;
				}
				else if(tree->left->left!=NULL&&tree->left->right==NULL){
					tree = LL_Rotate(tree) ;
				}
				
				else if(tree->left->left==NULL&&tree->left->right!=NULL){
					tree = LR_Rotate(tree) ;
				}
			}	
					
		}
		return tree ;			
	}
			
	public:

	void MissionOne() {
		bool same = true ;
		int i = 0 ;
		vector<int> numlist ;
		vector<int> temp ;
		string temp2 ;
		ttTree cur ;
		ttTree limit = NULL ;
		cur = NULL ;
		while ( i < aList.size() ) {
			if ( cur == NULL ) {
				tttree = SetNode( NULL ) ;
				tttree->first = aList[i].name ;
				tttree->firlist.push_back( aList[i].number ) ;
			}
			else {
				while ( cur->left != NULL || cur->right != NULL || cur->middle != NULL ) {
					if ( aList[i].name == cur->first ) {
						cur->firlist.push_back( aList[i].number ) ;
						same = false ;
						break ;
					}
					else if ( aList[i].name == cur->second ) {
						cur->seclist.push_back( aList[i].number ) ;
						same = false ;
						break ;
					}
					else if ( cur->first != "XXX" && cur->second != "XXX" ) {
						if ( aList[i].name < cur->first ) {
							cur = cur->left ;
						}
						else if ( aList[i].name < cur->second ) {
							cur = cur->middle ;
						}
						else if ( aList[i].name > cur->second ) {
							cur = cur->right ;
						}
					}
					else if ( cur->first != "XXX" && cur->second == "XXX" ) {
						if ( aList[i].name < cur->first ) {
							cur = cur->left ;
						}
						else if ( aList[i].name > cur->first ) {
							cur = cur->right ;
						}
					}
				}
				if ( same ) {
					if ( aList[i].name == cur->first ) {
						cur->firlist.push_back( aList[i].number ) ;
					}
					else if ( aList[i].name == cur->second ) {
						cur->seclist.push_back( aList[i].number ) ;
					}
					else if ( cur->first != "XXX" && cur->second == "XXX" ) {
						if ( aList[i].name < cur->first ) {
							cur->second = cur->first ;
							cur->seclist = cur->firlist ;
							cur->first = aList[i].name ;
							cur->firlist.clear() ;
							cur->firlist.push_back( aList[i].number ) ;
						}
						else if ( aList[i].name > cur->first ) {
							cur->second = aList[i].name ;
							cur->seclist.push_back( aList[i].number ) ;
						}
					}
					else if ( cur->first != "XXX" && cur->second != "XXX" ) {
						numlist.push_back( aList[i].number ) ;
						Spilt( cur, aList[i].name, numlist, temp, temp2, limit ) ;
						Distribute( temp, temp2, cur, limit ) ;
					} 
				}
					
			}
			same = true ;
			numlist.clear() ;
			temp.clear() ;
			temp2 = "" ;
			limit = NULL ;
			cur = tttree ;
			i++ ;
		}
		
		cout << "Tree Height: " << Counthigh( tttree ) << '\n' ;
		cout << "Number Of Nodes: " << Countnode( tttree ) << '\n' ;
		Print( tttree ) ;
	} // MissionOne()
			
	bool Read(){  // 讀入input 
		tree = NULL ;
		aList.clear() ;
		string temp ;
		int num = 1;
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
					ct.number = num ;
					ct.rawR = temp ;
					Cut(temp,ct) ;
					aList.push_back(ct) ;
					temp = "\0" ;
					num++ ;					
				}
				else{
					temp += ch ;					
				}
				
			}while(fscanf(fPtr, "%c", &ch)!=EOF);
			
			if(temp.size()>1){
				ct.rawR = temp ;
				Cut(temp,ct) ;
				aList.push_back(ct) ;
				temp = "" ;	
			}
			
			fclose(fPtr);
			
			SetGNum() ;	
			return true ;
			
				
		}
		return false ;
	}
			
	void BuildAVLTree(){
		int i = 0 ;
		while(i<aList.size()) {
			
			if(tree==NULL){
				tree = new AVLType ;
				tree->number.push_back(i) ;
				tree->gNum = aList[i].gNum ;
				Set(tree) ;
			}
		
			else{
				AVLType *find ;
				find = NULL ;
				find = Search(tree, aList[i].gNum) ;
				if(find != NULL){
					find->number.push_back(i) ;
				}			
				else{
					tree = Add(i,tree) ;
				}
			
			}
			i++ ;
		}
		
		cout<<"Tree Height: "<<Height(tree,1)<<endl<<"Number Of Nodes: "<<CountAVLNode(tree,1)<<endl ;
		for(int i = 0 ; i<tree->number.size() ;i++)
			cout<<i+1<<": "<<"["<<tree->number[i]+1<<"] "<<aList[tree->number[i]].information<<endl ;
	}	
	
};

int main(int argc, char** argv) {
	BuildTree list ;
	int cmd ;
	bool read = false;
	cout<<endl<<"*** Search Tree Utilities **"<<endl<<"* 0. QUIT                  *"<<endl<<"* 1. Build 2-3 tree        *"<<endl<<"* 2. Build AVL tree        *"<<endl
		<<"*************************************"<<endl<<"Input a choice(0, 1, 2):";
	cin >> cmd ;

	while(cmd!=0){
		if(cmd==1||cmd==2){
			if(cmd==1){
				if(list.Read() ){
					read = true ;
					list.MissionOne() ;
				}
					
				else
					read = false ;
				

			}
		
			else if(cmd==2){
				if(!read)
					cout<<"Please choose command 1 first!"<<endl ;
				else
					list.BuildAVLTree() ;
			}
		}
	
		else
			cout<<"ERROR COMMAND"<<endl ;
		
		
		cout<<endl<<"*** Search Tree Utilities **"<<endl<<"* 0. QUIT                  *"<<endl<<"* 1. Build 2-3 tree        *"<<endl<<"* 2. Build AVL tree        *"<<endl
			<<"*************************************"<<endl<<"Input a choice(0, 1, 2):";
		cin >> cmd ;
		
	}

	return 0;
}

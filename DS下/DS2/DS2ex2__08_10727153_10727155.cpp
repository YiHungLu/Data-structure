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

class MissionOne{
	ttTree tttree ;
	string fileName  ;
	string fileNumber ;	

	void Print( ttTree tree ) {				//印出任務一 
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
	
	
	void Cut( string chs, collegeType &ct ) {		//擷取要印出得資料 
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
	
	ttTree SetNode( ttTree previous ) {		//建立一個node 
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
	
	int Counthigh( ttTree tree ) {		//計算任務一的樹高 
		int height = 0 ;
		while ( tree != NULL ) {
			height++ ;
			tree = tree->left ;
		}
		return height ;
	} // Counthigh()
	
	int Countnode( ttTree tree ) {		//計算任務一的node數 
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
		if ( cur->first != "XXX" && cur->second == "XXX" ){ 			//node中只有一筆資料 
			if ( cur->first < name ) {				//加入node中 
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
		else if ( cur->first != "XXX" && cur->second != "XXX" ) {	//node中有兩筆資料 
			if ( name < cur->first ) {			//如果要存入的資料最小 
				temp2 = cur->first ;			//就和first交換 
				temp = cur->firlist ;
				cur->first = name ;
				cur->firlist = num ;
				name = temp2 ;
				num = temp ;
			}
			else if ( name > cur->second ) {	//如果要存入的資料最大 
				temp2 = cur->second ;			//就和second交換 
				temp = cur->seclist ;
				cur->second = name ;
				cur->seclist = num ;
				name = temp2 ;
				num = temp ;
			}
			else {								//如果要存入的資料在中間 
				temp2 = name ;
				temp = num ;
			}
			
			if ( cur->pre != NULL ) {			//如果還有父節點 就往上加	
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
	
	public:
		
	vector<collegeType>aList ;	
	void Build23Tree() {
		bool same = true ;
		int i = 0 ;
		vector<int> numlist ;
		vector<int> temp ;
		string temp2 ;
		ttTree cur ;
		ttTree limit = NULL ;
		cur = NULL ;
		while ( i < aList.size() ) {
			if ( cur == NULL ) {					//建立第一個樹根 
				tttree = SetNode( NULL ) ;
				tttree->first = aList[i].name ;
				tttree->firlist.push_back( aList[i].number ) ;
			}
			else {
				while ( cur->left != NULL || cur->right != NULL || cur->middle != NULL ) {  //現在的node有child 
					if ( aList[i].name == cur->first ) {			//如果和firlist的名字一樣 
						cur->firlist.push_back( aList[i].number ) ;
						same = false ;
						break ;
					}
					else if ( aList[i].name == cur->second ) {      //如果和seclist的名字一樣  
						cur->seclist.push_back( aList[i].number ) ;
						same = false ;
						break ;
					}
					else if ( cur->first != "XXX" && cur->second != "XXX" ) {	//如果node中有兩筆資料
						if ( aList[i].name < cur->first ) {			//往左邊走
							cur = cur->left ;
						}
						else if ( aList[i].name < cur->second ) {	//往中間走 
							cur = cur->middle ;
						}
						else if ( aList[i].name > cur->second ) {	//往右邊走 
							cur = cur->right ;
						}
					}
					else if ( cur->first != "XXX" && cur->second == "XXX" ) {	//如果node中只有一筆資料 
						if ( aList[i].name < cur->first ) {			//往左邊走
							cur = cur->left ;
						}
						else if ( aList[i].name > cur->first ) {	//往右邊走
							cur = cur->right ;
						}
					}
				}
				
				if ( same ) {		//如果沒有child且還沒找到相同的學校名稱 
					if ( aList[i].name == cur->first ) {
						cur->firlist.push_back( aList[i].number ) ;
					}
					else if ( aList[i].name == cur->second ) {
						cur->seclist.push_back( aList[i].number ) ;
					}
					else if ( cur->first != "XXX" && cur->second == "XXX" ) {	//如果現在的node只有一筆資料 
						if ( aList[i].name < cur->first ) {				//加入node中 
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
					else if ( cur->first != "XXX" && cur->second != "XXX" ) {		//如果node中資料滿了 
						numlist.push_back( aList[i].number ) ;
						Spilt( cur, aList[i].name, numlist, temp, temp2, limit ) ;	//分裂 
						Distribute( temp, temp2, cur, limit ) ;						//插入 
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
};

class MissionTwo{
	AVLType* tree ;
	vector<collegeType>aList ;
	vector<collegeType>aNumList ;
	void Set(AVLType* tree){ //初始化 
		tree->left = NULL ;
		tree->right = NULL ;
	}

	AVLType* Add(int i,AVLType* gNumTree){
		if(aList[i].gNum < gNumTree->gNum){		//如果小於節點 
			if(gNumTree->left == NULL){			//如果沒有左子樹就直接加入 
				gNumTree->left = new AVLType ;
				gNumTree->left->number.push_back(i) ;
				gNumTree->left->gNum = aList[i].gNum ;
				Set(gNumTree->left) ;
			}
			
			else{								//往左走 
				gNumTree->left = Add(i,gNumTree->left) ;
				gNumTree = Check(gNumTree) ;	//檢查需不需要旋轉 
			}
		}
		
		else if(aList[i].gNum > gNumTree->gNum){	//如果大於節點 
			if(gNumTree->right == NULL){
				gNumTree->right = new AVLType ;		//果沒有右子樹就直接加入
				gNumTree->right->number.push_back(i) ;
				gNumTree->right->gNum = aList[i].gNum ;
				Set(gNumTree->right) ;
			}
			
			else{								//往右走 
				gNumTree->right = Add(i,gNumTree->right) ;
				gNumTree = Check(gNumTree) ;	//檢查需不需要旋轉 
			}
		}
	
		return gNumTree ;
	}
	
	AVLType *Search(AVLType* tree, int num){  //搜尋AVL樹中有沒有相同的資料 
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
		if(tree->left!=NULL&&tree->right!=NULL){										//有左子樹和右子樹		
			if((Height(tree->left,1)-Height(tree->right,1))>1){							//如果左子樹的樹高-右子樹的樹高>1 
				if((Height(tree->left->left,1)-Height(tree->left->right,1))>0)			//如果左子樹的左子樹樹高 > 左子樹的右子樹樹高
					tree = LL_Rotate(tree) ;											//LL旋轉 
				else if((Height(tree->left->left,1)-Height(tree->left->right,1))<0)	 
					tree = LR_Rotate(tree) ;											//LR旋轉 
			}	
		
			else if((Height(tree->left,1)-Height(tree->right,1))<-1){					//如果左子樹的樹高-右子樹的樹高<-1 
				if((Height(tree->right->left,1)-Height(tree->right->right,1))>0){		//如果右子樹的左子樹樹高 < 右子樹的右子樹樹高
					tree = RL_Rotate(tree) ;											//RL旋轉 
				}					
				else if((Height(tree->right->left,1)-Height(tree->right->right,1))<0)
					tree = RR_Rotate(tree) ;											//RR旋轉 
			}
		}
		
		else if(tree->left==NULL && tree->right!=NULL){									//如果只有右子樹 
			if((0-Height(tree->right,1))<-1){
				if(tree->right->left!=NULL&&tree->right->right!=NULL){							
					if((Height(tree->right->left,1)-Height(tree->right->right,1))>0){
						tree = RL_Rotate(tree) ;					
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
		
		else if(tree->left!=NULL && tree->right==NULL){									//如果只有左子樹 
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


			
	void BuildAVLTree( 	vector<collegeType>m1List ){
		tree = NULL ; 
		int i = 0 ;
		aList = m1List ;
		while(i<aList.size()) {
			
			if(tree==NULL){					//存入第一筆資料 
				tree = new AVLType ;
				tree->number.push_back(i) ;
				tree->gNum = aList[i].gNum ;
				Set(tree) ;
			}
		
			else{
				AVLType *find ;
				find = NULL ;
				find = Search(tree, aList[i].gNum) ;
				if(find != NULL){			//如果有找到相同的畢業人數就直接加入 
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
	
	void MissionThree(){
		aNumList.clear() ;
		int k ;
		
		cout<<"Enter K in [" ;
		if(aList.size()>0)
			cout<<"1," ;
		else
			cout<<"0," ;
		cout<<aList.size()<<"]:" ;
		
		cin>>k ;
		TopK(k,tree) ;
		for(int i = 0 ; i<aNumList.size() ;i++)
			cout<<i+1<<": "<<"["<<aNumList[i].number<<"] "<<aNumList[i].information<<endl ;	
	}
	
	void TopK(int k, AVLType* tree){
		if(aNumList.size()<k){
			if(tree->left==NULL&&tree->right==NULL){
				if(aNumList.size()<k){
					for(int i = 0 ; i<tree->number.size() ;i++){
						aNumList.push_back(aList[tree->number[i]]) ;
					}	
				}				
			}
		
			else if(tree->right!=NULL && tree->left==NULL){
				if(aNumList.size()<k)
					TopK(k,tree->right) ;
				if(aNumList.size()<k){
					for(int i = 0 ; i<tree->number.size() ;i++){
						aNumList.push_back(aList[tree->number[i]]) ;
					}	
				}				
			}

			else if(tree->right!=NULL && tree->left!=NULL){
				if(aNumList.size()<k)
					TopK(k,tree->right) ;
			
				if(aNumList.size()<k){
					for(int i = 0 ; i<tree->number.size() ;i++){
						aNumList.push_back(aList[tree->number[i]]) ;
					}	
				}
				
				if(aNumList.size()<k)
					TopK(k,tree->left) ;
			}
				
			else if(tree->right==NULL && tree->left!=NULL){
				if(aNumList.size()<k){
					for(int i = 0 ; i<tree->number.size() ;i++){
						aNumList.push_back(aList[tree->number[i]]) ;
					}	
				}
				if(aNumList.size()<k)		
					TopK(k,tree->left) ;

			}
			
		}			
	}

			
	
	
};

int main(int argc, char** argv) {
	MissionOne m1 ;
	MissionTwo m2 ;
	int cmd ;
	bool read = false;
	bool avl = false ;
	cout<<endl<<"*** Search Tree Utilities **"<<endl<<"* 0. QUIT                  *"<<endl<<"* 1. Build 2-3 tree        *"<<endl<<"* 2. Build AVL tree        *"<<endl<<"* 3. Top-K search on AVL tree *"<<endl
		<<"*************************************"<<endl<<"Input a choice(0, 1, 2, 3):";
	cin >> cmd ;

	while(cmd!=0){
		if(cmd==1||cmd==2||cmd==3){
			if(cmd==1){
				if(m1.Read() ){
					read = true ;
					m1.Build23Tree() ;
				}
					
				else
					read = false ;
				

			}
		
			else if(cmd==2){
				avl = true ;
				if(!read)
					cout<<"Please choose command 1 first!"<<endl ;
				else
					m2.BuildAVLTree(m1.aList) ;
			}
			
			else if(cmd==3){
				if(avl==true)
					m2.MissionThree() ;
				else
					cout<<"Please choose command 2 first!"<<endl ;
			}
		}
	
		else
			cout<<"ERROR COMMAND"<<endl ;
		
		
		cout<<endl<<"*** Search Tree Utilities **"<<endl<<"* 0. QUIT                  *"<<endl<<"* 1. Build 2-3 tree        *"<<endl<<"* 2. Build AVL tree        *"<<endl<<"* 3. Top-K search on AVL tree *"<<endl
			<<"*************************************"<<endl<<"Input a choice(0, 1, 2, 3):";
		cin >> cmd ;
		
	}

	return 0;
}

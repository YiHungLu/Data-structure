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

struct collegeType{
	string rawR ;
	string name ;
	int gNum ;	
};


class BuildTree{
	string fileName  ;
	string fileNumber ;
	vector<collegeType>aList ;

	public:
		
	bool Read(){  // 讀入input 
		aList.clear() ;
		string temp ;
		int num ;
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
			
			SetName() ;	
			return true ;
			
				
		}
		return false ;
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

	void build23tree(){
		nodeType *root;
		root = NULL ;
					
		for(int i=0  ;i<aList.size();i++){
			root = insert23tree(i+1,aList[i].name, root) ;
		}
		
	}
		
	nodeType * insert23tree(int newRid,string newKey, nodeType *root){
		slotType newSlot;
		newSlot.rSet.push_back(newRid);
		newSlot.key = newKey ;
		if(root == NULL){
			root = createNode(NULL,NULL,NULL,newSlot);		
		}
		else{
			cout<<root->data[0].key ;
			stack<pointType> aPath;
			pointType curP;
			blockType blockUp;
			
			searchPath(root,newKey,aPath);
			if(!aPath.empty()){
				curP = aPath.top();
				if((curP.pnode->data[curP.pidx].rSet.size()) && (!newKey.compare(curP.pnode->data[curP.pidx].key)))
					curP.pnode->data[curP.pidx].rSet.push_back(newRid);
				else if(!curP.pnode->data[KEY_NUM-1].rSet.size())
					insertLeaf(newSlot,curP);
				else{
					splitLeaf(newSlot,curP,blockUp);
					if(curP.pnode->parent==NULL)
						root = createRoot(curP.pnode,blockUp.link,blockUp.slot);
					else
						do{
							aPath.pop();
							curP = aPath.top();
							if(!curP.pnode->data[KEY_NUM-1].rSet.size()){
								insertNonleaf(blockUp,curP);
								break;
							} //end inner if
							
							else{
								splitNonleaf(curP,blockUp);
								if(curP.pnode->parent==NULL){
									root = createRoot(curP.pnode,blockUp.link,blockUp.slot);
									break;
								}
							}
						}while(true);
				}
			}
		}
		
		return root ;
	}
	
	nodeType *createNode( nodeType *left, nodeType *right, nodeType *pNode, slotType newS ){
		nodeType *newNode = NULL;
		try{
			newNode = new nodeType;
			newNode->data[0].rSet = newS.rSet;
			newNode->data[1].rSet.clear();
			newNode->data[0].key = newS.key;
			newNode->data[1].key = "";
			newNode->parent = pNode;
			newNode->link[0] = left;
			newNode->link[1] = right;
			newNode->link[2] = NULL;
		}
		catch(std::bad_alloc& ba){
			std::cerr<<endl<<"bad_alloc caught: "<<ba.what()<<endl;
		}
		return newNode;
	}
	
	void searchPath( nodeType *cur, string name, stack<pointType> &path  ){
		pointType oneP;
		int pos;
		while (cur != NULL){
			oneP.pnode = cur;
			for(pos=0; pos<KEY_NUM; pos++)
				if((!cur->data[pos].rSet.size())||((name.compare(cur->data[pos].key))<0))
					break;
				else if(!name.compare(cur->data[pos].key)){
					oneP.pidx = pos;
					path.push(oneP);
					return;
				}
			
			oneP.pidx = pos ;
			path.push(oneP);
			
			cur = cur->link[pos];
		}
	}
	
	void insertLeaf(slotType newS, pointType &aLeaf){
		for(int i = KEY_NUM-1;i>aLeaf.pidx;i--)
			if(i>aLeaf.pidx){
				aLeaf.pnode->data[i].rSet = aLeaf.pnode->data[i-1].rSet;
				aLeaf.pnode->data[i].key = aLeaf.pnode->data[i-1].key;
			}
			
			else if(i==aLeaf.pidx){
				aLeaf.pnode->data[i].rSet = newS.rSet;
				aLeaf.pnode->data[i].key = newS.key;
			}
			else
				break;
	}

	void splitLeaf(slotType newS, pointType aLeaf, blockType &aBlock){
		slotType buff[PTR_NUM];
		int idx = 0 ;
		for(int i = 0 ;i<PTR_NUM;i++){
			buff[i].rSet = (i==aLeaf.pidx) ? newS.rSet : aLeaf.pnode->data[idx].rSet;
			buff[i].key = (i==aLeaf.pidx) ? newS.key : aLeaf.pnode->data[idx++].key;		
		}
		
		aLeaf.pnode->data[0].rSet = buff[0].rSet;
		aLeaf.pnode->data[0].key = buff[0].key;
		for(int i = 1;i < KEY_NUM;i++)
			aLeaf.pnode->data[i].rSet.clear();
		
		aBlock.link = createNode(NULL,NULL,aLeaf.pnode->parent,buff[2]);
		aBlock.slot.rSet = buff[1].rSet;
		aBlock.slot.key = buff[1].key;
	}
	
	nodeType *createRoot(nodeType *left, nodeType *right, slotType oneSlot){
		nodeType *newRoot = createNode(left,right,NULL,oneSlot);
		
		left->parent = newRoot;
		right->parent = newRoot;
		return newRoot;
	}
	
	void insertNonleaf(const blockType oneB, pointType &goal){
		if(oneB.slot.key.compare(goal.pnode->data[0].key)<0){
			for(int i = KEY_NUM-1;i>goal.pidx;i--)
				if(i>goal.pidx){
					goal.pnode->data[i].rSet = goal.pnode->data[i-1].rSet;
					goal.pnode->data[i].key = goal.pnode->data[i-1].key;
				}

				else if(i==goal.pidx){
					goal.pnode->data[i].rSet = oneB.slot.rSet;
					goal.pnode->data[i].key = oneB.slot.key;
					goal.pnode->link[2] = oneB.link ;
				}
				else
					break;
		}
		
		else{
			goal.pnode->data[1].rSet = oneB.slot.rSet;
			goal.pnode->data[1].key = oneB.slot.key;
			goal.pnode->link[2] = oneB.link ; 			
		}
				
//		if(oneB.slot.key.compare(goal.pnode->data[0].key)>0){
//			goal.pnode->data[1].key = oneB.slot.key ;
//			goal.pnode->data[1].rSet = oneB.slot.rSet ;
//			goal.pnode->link[2] = oneB.link ;
//		}
//		
//		else{
//			goal.pnode->data[1].key = goal.pnode->data[0].key ;
//			goal.pnode->data[1].rSet = goal.pnode->data[0].rSet ;
//			goal.pnode->data[0].key = oneB.slot.key ;
//			goal.pnode->data[0].rSet = oneB.slot.rSet ;
//			//goal.pnode->link[0] = oneB.link ;                      ////////			
//		}	
	}
	
	void splitNonleaf(pointType &goal, blockType &oneB){
		slotType buf[PTR_NUM];
		nodeType *ptr[PTR_NUM+1];
		int idx = 0 ;
		
		for(int i = 0;i < PTR_NUM;i++){
			buf[i].rSet = (i==goal.pidx) ? oneB.slot.rSet : goal.pnode->data[idx].rSet;
			buf[i].key = (i==goal.pidx) ? oneB.slot.key : goal.pnode->data[idx++].key;
		}
		
		ptr[0] = goal.pnode->link[0] ;
		ptr[1] = goal.pnode->link[1] ;
		ptr[2] = goal.pnode->link[2] ;
		ptr[3] = goal.pnode->link[3] ;
		cout<<"a" ;				 
		goal.pnode->data[0].rSet = buf[0].rSet ;
		goal.pnode->data[0].key = buf[0].key ;
		goal.pnode->link[2] = NULL ;
		goal.pnode->link[3] = NULL ;
		
		cout<<"b" ;
		oneB.link = createNode(ptr[2],ptr[3],goal.pnode->parent,buf[2]) ;
		cout<<"c"<<endl ;
		oneB.slot.rSet = buf[1].rSet;
		oneB.slot.key = buf[1].key ;
	}
	
	void free23tree(nodeType *root){
		if(root != NULL){
			free23tree(root->link[0]);
			for(int i = 0;i < KEY_NUM;i++){
				if(!root->data[i].rSet.size())
					break;
				free23tree(root->link[i+1]);
			}
			
			delete root;			
		}
	}
	
};

int main(int argc, char** argv) {
	BuildTree list;
	list.Read();
	list.build23tree() ;
	return 0;
}

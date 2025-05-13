//10727153 呂宜鴻 10727155 曾博暉 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <time.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

#define	MAX_LEN		10
#define	PAGE		25
#define	NONE		-1
typedef	struct	sP{				//儲存從bin檔中讀入的資料 
	char	sid1[MAX_LEN];
	char	sid2[MAX_LEN];
	float	wgt;
}	studentPair;

typedef	struct	aLN{			//儲存收訊者資料 
	string		sid2;
	float		weigh;
	aLN	*next;
}	adjListNode;
	
typedef	struct	aL{				//儲存發訊者資料 
	string		sid1;
	adjListNode*head;
	int 		inf;
	bool		visit;
	int			hvalue;
}	adjList;

typedef struct	cntL{			//儲存任務二獲得的資料 
	string		sid1;
	vector<string>head ;
	int			inf;
}	cntList;

class DirectedGragh{

	string fileName ;
	vector<adjList>	adjL;
	float			wgtLB;
	
	vector<studentPair>	aList;
	
	vector<cntList>	cntL;
	
	
	adjListNode* Creat(studentPair a){				//建立一個新的Node 
		adjListNode *temp = new adjListNode;
		temp->sid2 = a.sid2 ;
		temp->next = NULL ;
		temp->weigh = a.wgt ;
		return temp ;
	}
	
	void Set(){
		for(int i = 0 ; i<adjL.size() ; i++)
			adjL[i].visit = false ;
	}
	void InsertSid2(studentPair a)	{				//將收訊者排入主陣列中 
		bool find = false ;
		for(int j = 0 ; j<adjL.size() ; j++){
			if(a.sid2 == adjL[j].sid1){
				find = true ;
				break ;
			}
					
			else if(a.sid2 < adjL[j].sid1){
				adjList temp ;
				temp.sid1 = a.sid2 ;
				temp.head = NULL ;
				temp.inf = 0 ;
				adjL.insert(adjL.begin()+j,temp) ;
				find = true ;
				break;						
			}	
		}	
		
		if(find == false){
			adjList temp ;
			temp.sid1 = a.sid2 ;
			temp.head = NULL ;
			temp.inf = 0 ;
			adjL.push_back(temp) ;			
		}	
	}

	void MakeFileM2() {			//輸出任務二 
		int i = 0 ;
		FILE *fout = NULL;		
		fout = fopen( ("pairs"+fileName+".cnt").c_str(), "w" ) ;
		fprintf( fout,"<<< There are %d IDs in total. >>>\n",cntL.size()) ;
		while ( i < cntL.size() ) {

			if(i+1<10)
				fprintf( fout,"[  %d] %s(%d):\n",i+1,cntL[i].sid1.c_str(),cntL[i].head.size() ) ;
				
			else if(i+1<100 && i+1>=10)
				fprintf( fout,"[ %d] %s(%d):\n",i+1,cntL[i].sid1.c_str(),cntL[i].head.size() ) ;
				
			else
				fprintf( fout,"[%d] %s(%d):\n",i+1,cntL[i].sid1.c_str(),cntL[i].head.size() ) ;
							
			for(int j = 0 ; j<cntL[i].head.size() ; j++){

				if(j+1<10)
					fprintf( fout,"\t( %d) %s",j+1,cntL[i].head[j].c_str() ) ;
				
				else 
					fprintf( fout,"\t(%d) %s",j+1,cntL[i].head[j].c_str() ) ;
													
				
				if((j+1)%10==0)
					fprintf( fout,"\n" ) ;
					
			}
			fprintf( fout,"\n" ) ;
			i++ ;


		}
		
		fclose( fout ) ;

		
	}
	
	
	int SetSize(int x){						//計算雜湊表的大小 
		int i = 0 ;
		int remain = 0 ;
		int n = 0 ;
		n = x + 1 ;
		i = sqrt( n ) ;
		while ( i != 1 ) {
			remain = n % i ;
			if ( remain != 0 ) {
				i-- ;
			}
			else {
				n++ ;
				i = sqrt( n ) ;
			}
		}
		
		return n ;
	}
	
	int hash(string id){					//計算雜湊值 
		unsigned long long key = 0 ;
		int i = 0 ;
		key = (int) id[i] ;
		i++ ;
		while ( i < id.length() ) {
			key = key * (int) id[i] ;
			i++ ;
		}
		
		key = key % SetSize(aList.size()*1.2) ;
		return key ;
	}
	
	int step(string key){						//計算雙重雜湊的step 
		unsigned long long x = 1;
		int maxStep = SetSize(aList.size()/3) ;
		for(int i=0;i<key.size();i++)
			if((int)key[i] != 0)
				x = x*(int)key[i] ;
		x = x%maxStep;
		int n = maxStep - x ;
		return n ;		
	}
		
	void DoubleHash(adjList doubleHash[] ){					//任務二:雙重雜湊 
		int hashSize = SetSize(aList.size()*1.2) ;

		for(int i = 0 ; i<hashSize ; i++)
			doubleHash[i].hvalue = 0 ;		
		for(int j = 0 ; j<aList.size() ; j++){
			if(doubleHash[hash(aList[j].sid1)].hvalue == 0){
				doubleHash[hash(aList[j].sid1)].sid1 = aList[j].sid1 ; 
				doubleHash[hash(aList[j].sid1)].hvalue = hash(aList[j].sid1) ;				
			}
			
			
			else{
				int key = hash(aList[j].sid1) ;
				int x = step(aList[j].sid1) ;
				while(true){
					if(doubleHash[key].hvalue == 0){
						doubleHash[hash(aList[j].sid1)].sid1 = aList[j].sid1 ; 
						doubleHash[hash(aList[j].sid1)].hvalue = hash(aList[j].sid1) ;
						break ;				
					}
					
					else{
						key = key + x ;
						key = key%hashSize ;
					}
				}
			}
			
			

		}
		
	}
		
	void MakeFileM1() {			//輸出任務一 
		int i = 0 ;
		FILE *fout = NULL;		
		fout = fopen( ("pairs"+fileName+".adj").c_str(), "w" ) ;
		fprintf( fout,"<<< There are %d IDs in total. >>>\n",adjL.size()) ;
		while ( i < adjL.size() ) {

			if(i+1<10)
				fprintf( fout,"[  %d] %s:\n",i+1,adjL[i].sid1.c_str() ) ;
				
			else if(i+1<100 && i+1>=10)
				fprintf( fout,"[ %d] %s:\n",i+1,adjL[i].sid1.c_str() ) ;
				
			else
				fprintf( fout,"[%d] %s:\n",i+1,adjL[i].sid1.c_str() ) ;
							
			adjListNode * ptr ;
			ptr = adjL[i].head ;
			int x = 1 ;
			while(ptr!=NULL){

				if(x<10)
					fprintf( fout,"\t( %d) %s,  %.2f",x,ptr->sid2.c_str(),ptr->weigh ) ;
				
				else 
					fprintf( fout,"\t(%d) %s,  %.2f",x,ptr->sid2.c_str(),ptr->weigh ) ;
								
				ptr = ptr->next ;
				
				if(x%10==0)
					fprintf( fout,"\n" ) ;
					
				x++ ;
			}
			fprintf( fout,"\n" ) ;
			i++ ;


		}
		
		fprintf( fout,"<<< There are %d nodes in total. >>>\n",aList.size()) ;
		fclose( fout ) ;

		
	}
	
	int FindPosition(string a,adjList hashL[]){					//找到該學號的所在位置 
		int key = hash(a) ;
		while(hashL[key].hvalue!=0){
			if(hashL[key].sid1==a)
				return key ;
			else{
				key += step(hashL[key].sid1) ;
				key = key%SetSize(aList.size()*1.2)  ;
			}
		}
		
		
		return -1 ;
	}
	
	bool Find(vector<string>temp, string a){	//陣列中是否有該學號 
		for(int i = 0 ; i<temp.size() ; i++)
			if(temp[i]==a)
				return true ;
				
		return false ;
	}
	
	void BFS(adjList a, adjList hashL[]){				//任務二的寬度優先BFS走訪相鄰節點 
		int k = 0 ;
		cntList temp ;
		temp.sid1 = a.sid1 ;
		temp.inf = 0 ;
		vector<string>	q ;
		adjListNode * ptr ;
		ptr = a.head ;
		while(ptr!=NULL){						 
			q.push_back(ptr->sid2) ;				//將此學號的收訊者學號存入queue中 
			hashL[FindPosition(ptr->sid2,hashL)].visit = true ;
			bool have = false;
			for(int i = 0; i<temp.head.size() ; i++){
				if(ptr->sid2 < temp.head[i]){
					
					k++ ;
					temp.head.insert(temp.head.begin()+i,ptr->sid2) ;
					have = true ;
					break ;
				}
			}	
			
			if(!have) {
				temp.head.push_back(ptr->sid2) ;
				k++ ;
			}

			ptr = ptr->next ;
			
		}
		

		while(q.size()!=0 && k < adjL.size()-1 ){		//走訪queue中學號各自的收訊者	
			int idx ;
			for(idx = 0 ; idx<adjL.size() ; idx++){
				if(adjL[idx].sid1 == q[0])
					break ;
					
			}
			ptr = adjL[idx].head ;
			while(ptr!=NULL && k < adjL.size()-1 ){
				int n = FindPosition(ptr->sid2,hashL) ;
				if(!hashL[n].visit&&ptr->sid2!=temp.sid1){		 
					q.push_back(ptr->sid2) ;
					hashL[n].visit = true ;
					bool have = false;
					for(int i = 0 ; i<temp.head.size() ; i++){
						if(ptr->sid2 < temp.head[i]){
							k++ ;
							temp.head.insert(temp.head.begin()+i,ptr->sid2) ;
							have = true ;
							break ;
						}
					}
			
					if(!have){
						k++ ;
						temp.head.push_back(ptr->sid2) ;	
					}
				}
				
				ptr = ptr->next ;

			}
			
			q.erase(q.begin()) ; 
			 
		}
		

		bool have = false ;
		for(int i = 0 ; i<cntL.size() ; i++){
			if(temp.head.size()>cntL[i].head.size()){
				cntL.insert(cntL.begin()+i,temp) ;		
				have = true ;
				break ;			
			}

		}
		
		if(!have)
			cntL.push_back(temp) ;
			
			
		
		
	}
	
	public:	
	bool readBinary(){			//get records from a file
		fstream	binFile;
		studentPair	oneSt;						//keeponerecord with the required fields
		int stNo = 0;							//total number of students
		cout<<"Input a file number ([0] Quit): " ;
		cin>>fileName ;
		binFile.open(("pairs" + fileName + ".bin").c_str(),fstream::in|fstream::binary);	//open a file
		aList.clear() ;
		if(!binFile.is_open())
			return false ;
		else if(binFile.is_open()){
			studentPair temp ;
			binFile.read((char*)&temp.sid1,sizeof(temp.sid1));	//read the entire record from a binary file
			while(!binFile.eof()){
				binFile.read((char*)&temp.sid2,sizeof(temp.sid2));
				binFile.read((char*)&temp.wgt,sizeof(float));
				aList.push_back(temp) ;	
				
				binFile.read((char*)&temp.sid1,sizeof(temp.sid1));			
			}
		}
		
		binFile.close();

//		for(int i = 0 ; i<aList.size() ; i++)
//			cout<<i<<"  "<<aList[i].sid1<<"  "<<aList[i].sid2<<"  "<<aList[i].wgt<<endl ;
		//Insert() ;
		return true ;
	}
		
	void Insert(){									//任務一 建立相鄰串列 
		adjL.clear() ;
		for(int i=0 ; i<aList.size() ; i++){
			if(adjL.size()==0){
				adjList temp ;
				temp.sid1 = aList[0].sid1 ;
				temp.head = Creat(aList[0]) ;
				temp.inf = 1 ;
				adjL.push_back(temp) ;
			}
			
			else{
				bool find = false ;
				for(int j = 0 ; j<adjL.size() ; j++){
					if(aList[i].sid1 == adjL[j].sid1){
						adjListNode * ptr ;
						ptr = adjL[j].head ;
						if(ptr!=NULL){
							bool have = false ;
							
							if(ptr->sid2 > aList[i].sid2){
								adjListNode * temp ;
								temp = ptr ;
								adjL[j].head = Creat(aList[i]) ;
								adjL[j].head->next = temp ;
								have = true ;
							}
							
							while(ptr->next!=NULL&&!have){
								if(ptr->next->sid2 > aList[i].sid2){
									adjListNode * temp ;
									temp = ptr->next ;
									ptr->next = Creat(aList[i]) ;
									ptr = ptr->next ;
									ptr->next = temp ;
									have = true ;
									break ;
								}
									
								ptr = ptr->next ;
							}
							
							if(!have){
								ptr->next = Creat(aList[i]) ;
							}	
															
						}
												
						else
							adjL[j].head = Creat(aList[i]) ;

						find = true ;
						adjL[j].inf++ ;
						break ;
					}
					
					else if(aList[i].sid1 < adjL[j].sid1){
						adjList temp ;
						temp.sid1 = aList[i].sid1 ;
						temp.head = Creat(aList[i]) ;
						temp.inf = 1 ;
						adjL.insert(adjL.begin()+j,temp) ;
						find = true ;
						break;						
					}	
				}
				
				if(!find){
					adjList temp ;
					temp.sid1 = aList[i].sid1 ;
					temp.head = Creat(aList[i]) ;
					temp.inf = 1 ;
					adjL.push_back(temp) ;					
				}

				InsertSid2(aList[i]) ;

				
			}
		}
		
		cout<<endl<<"<<< There are "<<adjL.size()<<" IDs in total. >>>"<<endl ;
		cout<<endl<<"<<< There are "<<aList.size()<<" nodes in total. >>>"<<endl;
		MakeFileM1() ;
						
	}
	
	void M2(){						//任務二 
		adjList	hashL[SetSize(aList.size()*1.2)] ;
		DoubleHash(hashL) ;
		for(int i = 0 ; i<adjL.size() ; i++)
			hashL[i].visit = false ;
		cntL.clear() ;
		for(int i = 0 ; i<adjL.size() ; i++){
			BFS(adjL[i],hashL);
		}
		cout<<endl<<"<<< There are "<<cntL.size()<<" IDs in total. >>>"<<endl ;		
		MakeFileM2() ;
		
	}


	
	
	
};

int main(int argc, char** argv) {
	

	DirectedGragh test ;
	int cmd ;
	printf("**** Graph data manipulation ****\n* 0. QUIT                       *\n* 1. Build adjacency lists      *\n* 2. Compute connection counts  *\n*********************************\nInput a choice(0, 1, 2): ");
	cin>>cmd ;
	bool have = false;
	while(cmd!=0){
		if(cmd==1){
			if(test.readBinary()){	
				have = true ;
				test.Insert() ;				
			}
			
			else{
				have = false ;
				cout<<endl<<"### file does not exist! ###"<<endl ;
			}
				
		
		}

		else if(cmd==2){
			if(have)
				test.M2();
			else
				cout<<endl<<"### There is no graph and choose 1 first. ###"<<endl ;
		}
		
		else{
			cout<<"ERROR COMMAND"<<endl ;
		}
		
		printf("\n**** Graph data manipulation ****\n* 0. QUIT                       *\n* 1. Build adjacency lists      *\n* 2. Compute connection counts  *\n*********************************\nInput a choice(0, 1, 2): ");
		cin>>cmd ;		
			
	}
	
	return 0;
}

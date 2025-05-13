//10727153 呂宜鴻 10727155 曾博暉 
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <time.h>
#include <stack>
#include<sstream>


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
	bool		visit;
	int 		inf;
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
	
	vector<cntList> infL;
	
	vector<string> visit ;
	
	vector<float>	result ;
	vector<int>		resultIdx ;
	
	adjListNode* Creat(studentPair a){				//建立一個新的Node 
		adjListNode *temp = new adjListNode;
		temp->sid2 = a.sid2 ;
		temp->next = NULL ;
		temp->weigh = a.wgt ;
		return temp ;
	}
	
	void InsertSid2(studentPair a)	{				//將收訊者排入主陣列中 
		bool find = false ;
		for(int j = 0 ; j<adjL.size() ; j++){
			if(a.sid2 == adjL[j].sid1){
				adjListNode * ptr ;
				ptr = adjL[j].head ;
				if(ptr!=NULL){
					bool have = false ;
							
					if(ptr->sid2 > a.sid1){
						adjListNode * temp ;
						temp = ptr ;
						adjL[j].head = Creat(a) ;
						adjL[j].head->sid2 = a.sid1 ;
						adjL[j].head->next = temp ;
						have = true ;
					}
							
					while(ptr->next!=NULL&&!have){
						if(ptr->next->sid2 > a.sid1){
							adjListNode * temp ;
							temp = ptr->next ;
							ptr->next = Creat(a) ;
							ptr->next->sid2 = a.sid1 ;
							ptr = ptr->next ;
							ptr->next = temp ;
							have = true ;
							break ;
						}
									
						ptr = ptr->next ;
					}
					
					if(!have){
						ptr->next = Creat(a) ;
						ptr->next->sid2 = a.sid1 ;
					}	
															
				}
												
				else{
					adjL[j].head = Creat(a) ;
					adjL[j].head->sid2 = a.sid1 ;
				}
					
				find = true ;
				adjL[j].inf++ ;
				break ;
			}
			
			else if(a.sid2 < adjL[j].sid1){
				adjList temp ;
				temp.sid1 = a.sid2 ;
				temp.head = Creat(a) ;
				temp.head->sid2 = a.sid1 ;
				temp.inf = 1 ;
				adjL.insert(adjL.begin()+j,temp) ;
				find = true ;
				break;						
			}	
		}
		
		if(!find){
			adjList temp ;
			temp.sid1 = a.sid2 ;
			temp.head = Creat(a) ;
			temp.head->sid2 = a.sid1 ;
			temp.inf = 1 ;
			adjL.push_back(temp) ;					
		}
	}
	
	void MakeFileM0() {			//輸出任務零 
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
		int nodes = 0 ;
		for(int i = 0 ; i<adjL.size();i++)
			nodes = nodes + adjL[i].inf;		
		fprintf( fout,"<<< There are %d nodes in total. >>>\n",nodes) ;
		fclose( fout ) ;

		
	}
	
	void MakeFileM1() {			//輸出任務一 
		int i = 0 ;
		FILE *fout = NULL;		
		fout = fopen( ("pairs"+fileName+".cc").c_str(), "w" ) ;
		fprintf( fout,"<<< There are %d Connected Component in total. >>>\n",cntL.size()) ;
		while ( i < cntL.size() ) {

			if(i+1<10)
				fprintf( fout,"{ %d} Connected Component: size = %d\n",i+1,cntL[i].head.size() ) ;
				
			else if(i+1<100 && i+1>=10)
				fprintf( fout,"{ %d} Connected Component: size = %d\n",i+1,cntL[i].head.size() ) ;
				
			else
				fprintf( fout,"{ %d} Connected Component: size = %d\n",i+1,cntL[i].head.size() ) ;
							
			for(int j = 0 ; j<cntL[i].head.size() ; j++){

				if(j+1<10)
					fprintf( fout,"\t( %d) %s",j+1,cntL[i].head[j].c_str() ) ;
				
				else 
					fprintf( fout,"\t(%d) %s",j+1,cntL[i].head[j].c_str() ) ;
													
				
					
				if((j+1)%8==0)
					fprintf( fout,"\n" ) ;	
			}

				
			fprintf( fout,"\n" ) ;
			i++ ;


		}
		
		fclose( fout ) ;

		
	}
	
	void MakeFileM2(string a) {			//輸出任務二 
		int i = 0 ;
		FILE *fout = NULL;		
		fout = fopen( ("pairs"+fileName+".ds").c_str(), "a" ) ;
		fprintf( fout,"\norigin: %s\n",a.c_str()) ;

		for(int j = 0 ; j<result.size() ; j++){

			if(j+1<10)
				fprintf( fout,"( %d)\t%s, %.2f\t",j+1,adjL[resultIdx[j]].sid1.c_str(), result[j] ) ;
				
			else 
				fprintf( fout,"(%d)\t%s, %.2f\t",j+1,adjL[resultIdx[j]].sid1.c_str(), result[j] ) ;
													
				
					
			if((j+1)%8==0)
				fprintf( fout,"\n" ) ;	
		}


		fprintf( fout,"\n" ) ;
		
		fclose( fout ) ;

		
	}
			
	int FindPosition(string a){					//找到該學號的所在位置 
		for(int i = 0 ; i<adjL.size() ; i++){
			if(adjL[i].sid1 == a)
				return i;
		}
		
		return -1 ;
	}
	
	bool Find(vector<string>temp, string a){	//陣列中是否有該學號 
		for(int i = 0 ; i<temp.size() ; i++)
			if(temp[i]==a)
				return true ;
				
		return false ;
	}

	void DFS(adjList a){				//任務一的深度優先DFS走訪相鄰節點 
		cntList temp ;
		temp.sid1 = a.sid1 ;
		temp.head.push_back(a.sid1) ;
		adjL[FindPosition(a.sid1)].visit = true ;
		vector<string> stack ;
		adjListNode * ptr ;
		ptr = a.head ;
		while(ptr!=NULL){
			int n = FindPosition(ptr->sid2) ;
			if(!adjL[n].visit){		 						 	
				stack.insert(stack.begin(),ptr->sid2) ;	
				adjL[n].visit = true ;
				bool have = false;
				for(int i = 0; i<temp.head.size() ; i++){
					if(ptr->sid2 < temp.head[i]){
						temp.head.insert(temp.head.begin()+i,ptr->sid2) ;
						have = true ;
						break ;
					}
				}
			
				if(!have) {
					temp.head.push_back(ptr->sid2) ;
				}
				
			}

			ptr = ptr->next ;
			
		}
		
		while(!stack.empty() ){		
			int idx = FindPosition(stack[0]) ;
			ptr = adjL[idx].head ;
			while(ptr!=NULL ){
				int n = FindPosition(ptr->sid2) ;
				if(!adjL[n].visit){		 
					stack.insert(stack.begin()+1,ptr->sid2) ;
					adjL[n].visit = true ;
					bool have = false;
					for(int i = 0 ; i<temp.head.size() ; i++){
						if(ptr->sid2 < temp.head[i]){
							temp.head.insert(temp.head.begin()+i,ptr->sid2) ;
							have = true ;
							break ;
						}
					}
			
					if(!have){
						temp.head.push_back(ptr->sid2) ;	
					}
				}
				
				ptr = ptr->next ;

			}
			stack.erase(stack.begin()) ; 
			 
		}
		

		bool have = false ;
		for(int i = 0 ; i<cntL.size() ; i++){
			if(temp.head.size()>=cntL[i].head.size()){
				cntL.insert(cntL.begin()+i,temp) ;		
				have = true ;
				break ;			
			}

		}
		
		if(!have)
			cntL.push_back(temp) ;
			
			
		
		
	}

	void Dijkstra(string id){
		
		for(int i = 0 ; i<adjL.size() ; i++)
			adjL[i].visit = false ;
			
		float weight[adjL.size()] ;
		
		int idx = FindPosition(id) ;
		adjL[idx].visit = true ;
		for(int i = 0 ; i<adjL.size() ; i++){
			if(i == idx)
				weight[i] = 0 ;
			else
				weight[i] = 99 ;
		}			
		
		int min = -1 ;
		float minWgt = 99;		
		while(idx!=-1){
			adjL[idx].visit = true ;
			adjListNode * ptr ;
			ptr = adjL[idx].head ;
			min = -1 ;
			minWgt = 99;
			while(ptr!=NULL){
				int n = FindPosition(ptr->sid2) ;
				if(adjL[n].visit == false && weight[n] > ptr->weigh + weight[idx]){
					weight[n] = ptr->weigh + weight[idx] ;	
				}
				ptr = ptr->next ;
			}
			
			for(int i = 0 ; i<adjL.size() ; i++){
				if(minWgt > weight[i]&&adjL[i].visit == false){
					min = i ;
					minWgt = weight[i] ;
				}
			}
			
			idx = min ;			
						
		}
		

		result.clear() ;
		resultIdx.clear() ;
		
		for(int i = 0 ; i<adjL.size() ; i++){
			if(weight[i]!=99&&weight[i]!=0){
				//cout<<endl<<i+1<<"  "<<weight[i]<<endl ;
				bool have = false ;
				for(int j = 0 ; j<result.size() ; j++){
					if(result[j]>weight[i]){
						have = true ;
						result.insert(result.begin()+j,weight[i]);
						resultIdx.insert(resultIdx.begin()+j,i);
						break ;
					}
				}
				
				if(!have){
					result.push_back(weight[i]) ;
					resultIdx.push_back(i) ;			
				}
			}
							
		}
		
		MakeFileM2(id) ;
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

		return true ;
	}
		
	void Insert(float num){									//任務零 建立相鄰串列 
		adjL.clear() ;
		
		char array[6];
		sprintf(array, "%f", num);
		fileName = fileName + "_" + array[0] + array[1] ;
		int i ;
		for(i = 5 ; i>=0 ; i--){
			if(array[i]!='0')
				break ;		
		}
		
		for(int x = 2 ; x<=i ;x++){
			fileName = fileName + array[x] ;
		}

		
		
		
		
		

	
		for(int i=0 ; i<aList.size() ; i++){
			if(aList[i].wgt<=num){
			if(adjL.size()==0){
				adjList temp ;
				temp.sid1 = aList[i].sid1 ;
				temp.head = Creat(aList[i]) ;
				temp.inf = 1 ;
				adjL.push_back(temp) ;
				InsertSid2(aList[i]) ;
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

		}
		
		cout<<endl<<"<<< There are "<<adjL.size()<<" IDs in total. >>>"<<endl ;
		int nodes = 0 ;
		for(int i = 0 ; i<adjL.size();i++)
			nodes = nodes + adjL[i].inf;
		cout<<endl<<"<<< There are "<<nodes<<" nodes in total. >>>"<<endl;
		MakeFileM0() ;
						
	}
	
	void M1(){						//任務一 
		cntL.clear() ;
		for(int i = 0 ; i<adjL.size() ; i++)
			adjL[i].visit = false ;
		for(int i = 0 ; i<adjL.size() ; i++){
			if(!adjL[i].visit){
				DFS(adjL[i]);
			}
				
		}
		cout<<endl<<"<<< There are "<<cntL.size()<<" connected components in total. >>>"<<endl ;
		for(int i = 0 ; i<cntL.size() ; i++)
			cout<<"{ "<<i+1<<"} Connected Component: size = "<<cntL[i].head.size()<<endl ;		
		MakeFileM1() ;
		
	}
	
	void M2(){
		cout<<endl ;
		for(int i = 0 ; i<adjL.size() ; i++)
			cout<<" "<<adjL[i].sid1<<" " ;
		cout<<endl<<"Input a student ID [0: exit] " ;
		string id ;
		cin>>id ;
		while(id!="0"){
			if(FindPosition(id)==-1)
				cout<<endl<<"### the student id does not exist! ###"<<endl ;
			else{
				Dijkstra(id) ;
				cout<<endl ;
			}
			
			for(int i = 0 ; i<adjL.size() ; i++)
				cout<<" "<<adjL[i].sid1<<" " ;
			cout<<endl<<"Input a student ID [0: exit] " ;
			cin>>id ;					

			
		}
		
	}
	

	
			
};

int main(int argc, char** argv) {
	
	DirectedGragh test ;
	int cmd ;
	float num ;
	printf("\n******* Graph data applications ******\n* 0. Create adjacency lists          *\n* 1. Build connected components      *\n* 2. Find shortest paths by Dijkstra *\n**************************************\nInput a choice(0, 1, 2) [Any other key: QUIT]: ");
	cin>>cmd ;
	
	bool have = false;
	while(true){
		if(cmd==0){
			cout<<endl<<"Input a real number in (0,1]: ";
			cin >> num ;
			while(num>1||num<=0){
				cout<<endl<<"### It is NOT in (0,1] ###"<<endl ;
				cout<<endl<<"Input a real number in (0,1]: ";
				cin >> num ;
			}
				
			if(test.readBinary()){	
				have = true ;
				test.Insert(num) ;				
			}
			
			else{
				have = false ;
				cout<<endl<<"### file does not exist! ###"<<endl ;
			}
				
		
		}

		else if(cmd==1){
			if(have)
				test.M1();
			else
				cout<<endl<<"### There is no graph and choose 0 first. ###"<<endl ;
		}

		else if(cmd==2){
			if(have)
				test.M2();
			else
				cout<<endl<<"### Choose 1 to find connected components. ###"<<endl ;
		}
		
		else{
			break ;
		}
		
		printf("\n******* Graph data applications ******\n* 0. Create adjacency lists          *\n* 1. Build connected components      *\n* 2. Find shortest paths by Dijkstra *\n**************************************\nInput a choice(0, 1, 2) [Any other key: QUIT]: ");
		cin>>cmd ;		
			
	}
}

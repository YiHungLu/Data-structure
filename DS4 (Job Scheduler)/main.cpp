// 10727153 呂宜鴻 10727157 曾博暉 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <vector>
#include <time.h>
 
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct jobType{  //工作 
	int OID;
	int arrival;
	int duration;
	int timeout;
};

struct abortJob{ // 取消的工作 
	int OID ;
	int abort ;
	int delay ;
};

struct done{ // 完成的工作 
	int OID ;
	int departure ;
	int delay ;
};

class JobList{  // 處理任務一 
	vector<jobType>aList;
	string fileID;
	string fileNumber ;
	
	clock_t read, readDone, sort, sortDone, print, printDone;
	
	void Init(){
		aList.clear() ;
	}
	
	bool Read(){  // 讀入input 
		
		Init() ;
		
		jobType temp ;
		string str ;
		char ch ;
		int num ;
		cout<<endl<<"FileNumber : " ;
		cin>>fileNumber ;
		fileID = "input" + fileNumber + ".txt" ;
		FILE *fPtr = NULL;
		fPtr=fopen(fileID.c_str(),"r");
		read = clock();
		if(fPtr==NULL)
			cout<<"ERROR FILE"<<endl ;
		else{
			fscanf(fPtr, "%c", &ch) ;
			while(ch!='\n')
				fscanf(fPtr, "%c", &ch) ;
				
			do{
				if(fscanf(fPtr, "%d", &num) == EOF )
					break ;
				temp.OID = num ;
				fscanf(fPtr, "%c", &ch) ;
				
				fscanf(fPtr, "%d", &num) ;
				temp.arrival = num ;
				fscanf(fPtr, "%c", &ch) ;
				
				fscanf(fPtr, "%d", &num) ;
				temp.duration = num ;
				fscanf(fPtr, "%c", &ch) ;
				
				fscanf(fPtr, "%d", &num) ;
				temp.timeout = num ;
				
				aList.push_back(temp) ;
				
			}while(fscanf(fPtr, "%c", &ch)!=EOF);
			
			fclose(fPtr);
			
			readDone = clock();
			return true ;
			
				
		}
		return false ;
	}

	void SortByArrival(){ // 用希爾排序處理 
		int h = 0 ;
		int i ;
		int j ;
		jobType temp ;
		jobType next ;
		sort = clock() ;
		h = aList.size() / 2 ;
		while(h>0){
		
			for(i=h ; i < aList.size() ; i++){ // shell sort 
				next = aList[i] ;
				for(j=i ; j>=h && (aList[j-h].arrival > next.arrival || (aList[j-h].arrival == next.arrival && aList[j-h].OID > next.OID  )) ; j = j - h){
					aList[j] = aList[j-h] ;
				}
				
				aList[j] = next ;
				
			}
			
//			for(i=0 ; i<=h+1 ; i++){
//				for(j=0 ; i+j+h<aList.size() ; j = j+h){
//					if(aList[i+j].arrival>aList[i+j+h].arrival){
//						temp = aList[i+j] ;
//						aList[i+j] = aList[i+j+h] ;
//						aList[i+j+h] = temp ;
//					}
//					
//					else if(aList[i+j].arrival==aList[i+j+h].arrival){
//						if(aList[i+j].OID>aList[i+j+h].OID){
//							temp = aList[i+j] ;
//							aList[i+j] = aList[i+j+h] ;
//							aList[i+j+h] = temp ;
//						}
//					}
//				}
//				
//			}
//			cout<<endl ;
//			cout << h << endl;
//			for(int x = 0 ; x < aList.size() ; x++)
//				cout<<aList[x].OID<<"\t"<<aList[x].arrival<<endl ;
			h = h/2 ;
		}
		sortDone = clock() ;
	}
	public :
		
	bool GetSort(){
		if(!Read())
			return false ;
		else{
			SortByArrival() ;
			return true ;
		}
	}
	
	void Print(){  // 印出sorted 
		
		
		
		
		if(Read()){
			
			
			
			FILE *fout = NULL;
			fileID = "sorted" + fileNumber + ".txt" ;
			
//			for(int i = 0 ; i < aList.size() ; i++)
//				cout<<aList[i].OID<<" "<<aList[i].arrival<<" "<<aList[i].duration<<" "<<aList[i].timeout<<endl ;
			
			
					
			SortByArrival() ;
			
			
			
			print = clock() ;
			
			fout=fopen(fileID.c_str(),"w");
			fprintf(fout,"OID\tArrival\tDuration\tTimeOut\n") ;
			for(int i = 0 ; i < aList.size() ; i++)
//				cout<<aList[i].OID<<" "<<aList[i].arrival<<" "<<aList[i].duration<<" "<<aList[i].timeout<<endl ;
				fprintf(fout,"%d\t%d\t%d\t%d\n", aList[i].OID, aList[i].arrival, aList[i].duration, aList[i].timeout) ;
			fclose(fout);
			
			printDone = clock();
			
			cout<<endl<<"see in "<<fileID<<endl ;
			
			double readTime = readDone - read; // ms
			double sortTime = sortDone - sort;
			double printTime = printDone - print;
    		printf("read : %f  sec\n", readTime/ CLOCKS_PER_SEC );	//印出時間 
			printf("sort : %f  sec\n", sortTime / CLOCKS_PER_SEC );	
			printf("print : %f  sec\n", printTime / CLOCKS_PER_SEC );		
		}
	}	 
};

class Simulation{  // 處理任務二 
	vector<jobType>aList ;
	vector<jobType>aStoreList ;
	vector<abortJob>aAbortList ;
	vector<done>aDoneList ;
	int nowArrival = 0;
	string fileID ;
	string fileNumber ;	
	int total ;
	
	void Init(){ // 初始化 
		aList.clear() ;
		aStoreList.clear() ;
		aAbortList.clear() ;
		aDoneList.clear() ;
		nowArrival = 0 ;
	}
	
	bool Read(){ // 讀入sorted 

		jobType temp ;
		string str ;
		char ch ;
		int num ;
		cout<<endl<<"FileNumber : " ;
		cin>>fileNumber ;
		fileID = "sorted" + fileNumber + ".txt" ;
		FILE *fPtr = NULL;
		fPtr=fopen(fileID.c_str(),"r");
		if(fPtr==NULL)
			cout<<"ERROR FILE"<<endl ;
		else{
			fscanf(fPtr, "%c", &ch) ;
			while(ch!='\n')
				fscanf(fPtr, "%c", &ch) ;
			
			do{
				if(fscanf(fPtr, "%d", &num) == EOF )
					break ;
				temp.OID = num ;
				fscanf(fPtr, "%c", &ch) ;
				
				fscanf(fPtr, "%d", &num) ;
				temp.arrival = num ;
				fscanf(fPtr, "%c", &ch) ;
				
				fscanf(fPtr, "%d", &num) ;
				temp.duration = num ;
				fscanf(fPtr, "%c", &ch) ;
				
				fscanf(fPtr, "%d", &num) ;
				temp.timeout = num ;
				
				aList.push_back(temp) ;
				
			}while(fscanf(fPtr, "%c", &ch)!=EOF);
			
			fclose(fPtr);
			
			total = aList.size() ;
			return true ;	
		}
		
		return false ;
	}	
	
	void Work(){ // 處理工作 
		jobType nowJob ;
		nowArrival = aList[0].arrival ;		
		nowJob = aList[0] ;
		aList.erase(aList.begin()) ;
		
		while(!aList.empty()){
			
			Store() ;
						
			done temp ;
			temp.OID = nowJob.OID ;                    // 完成目前的工作 
			if(nowArrival<nowJob.arrival)
				nowArrival = nowJob.arrival ;
			temp.departure = nowArrival + nowJob.duration ;
			temp.delay = nowArrival - nowJob.arrival ;
			aDoneList.push_back(temp) ;
					
			nowArrival = nowArrival + nowJob.duration ;
			
			
			Delete() ;  // 取消工作(佇列已滿) 
			Delete2() ; // 取消佇列中的工作 
			if(aStoreList.empty()&&aList.empty())
				break ;
				
			nowJob = aStoreList[0] ;
			aStoreList.erase(aStoreList.begin()) ;			
		}
		
	}
	
	void Store(){  // 將工作存入佇列 
		while(aStoreList.size()<3 && !aList.empty()){
			aStoreList.push_back(aList[0]) ;
			aList.erase(aList.begin()) ;
		}
	}

	void Delete(){  // 取消工作(佇列已滿)  
		abortJob temp ;
		while(nowArrival > aList[0].arrival){
			temp.OID = aList[0].OID ;
			temp.abort = aList[0].arrival ;
			temp.delay = 0 ;
			aAbortList.push_back(temp) ;
			
			aList.erase(aList.begin()) ;
			if(aList.empty())
				break ;
		}
	}

	void Delete2(){  // 取消佇列中的工作 
		while(nowArrival+aStoreList[0].duration > aStoreList[0].timeout){
			abortJob temp ;
			
			temp.OID = aStoreList[0].OID ;
				
			if(aStoreList[0].timeout>nowArrival)
				nowArrival = aStoreList[0].timeout ;
					
			temp.abort = nowArrival ;				
			temp.delay = nowArrival - aStoreList[0].arrival ;
			aAbortList.push_back(temp) ;
			
			aStoreList.erase(aStoreList.begin()) ;
			
			if(aStoreList.empty())
				break ;
			
			Store() ;
		}	
	}

	float Delay(){  // 計算平均Delay 
		int delay ;
		for(int i = 0 ; i < aAbortList.size() ; i++) 
			delay += aAbortList[i].delay ;
		for(int j = 0 ; j < aDoneList.size() ; j++)
			delay += aDoneList[j].delay ;
			
		delay = (float)delay/total ;
	}
	public:
		
	void Print(){ // 印出output 
		Init() ;
		
		if(!Read() )
			cout<<"can't find "<<fileID<<endl ;
		else{
			
		FILE *fout = NULL;
		fileID = "output" + fileNumber + ".txt" ;

		
//		for(int i = 0 ; i < aList.size() ; i++)
////			cout<<aList[i].OID<<" "<<aList[i].arrival<<" "<<aList[i].duration<<" "<<aList[i].timeout<<endl ;
////		cout<<endl ;
		
		Work() ;
		fout=fopen(fileID.c_str(),"w");
		int i ;
		fprintf(fout,"\t[Abort Jobs]\n") ;
		fprintf(fout,"\tOID\tAbort\tDelay\n") ;
		for(i = 0 ; i < aAbortList.size() ; i++) 
			fprintf(fout,"(%d)\t%d\t%d\t%d\n", i+1, aAbortList[i].OID, aAbortList[i].abort, aAbortList[i].delay) ;

//			cout<<aAbortList[i].OID<<" "<<aAbortList[i].abort<<" "<<aAbortList[i].delay<<endl ;
		 
		fprintf(fout,"\t[Jobs Done]\n") ;
		fprintf(fout,"\tOID\tDeparture\tDelay\n") ;
		int j;
		for(j = 0 ; j < aDoneList.size() ; j++) 
			fprintf(fout,"(%d)\t%d\t%d\t%d\n", j+1, aDoneList[j].OID, aDoneList[j].departure, aDoneList[j].delay) ;
			
			//cout<<aDoneList[j].OID<<" "<<aDoneList[j].departure<<" "<<aDoneList[j].delay<<endl ;
		
			
		fprintf(fout,"[Average Delay]\t%.2lf ms\n", Delay()) ;
		fprintf(fout,"[Success Rate]\t%.2lf %\n", (float)aDoneList.size()/total*100) ;
		fclose(fout);	
		}
		
		cout<<endl<<"see in "<<fileID<<endl ;	
	}
}; 
int main(int argc, char** argv) {
	int num ;
	cout<<endl<<"0:QUIT"<<endl<<"1:sort"<<endl<<"2:simulate"<<endl ;
	cin>>num ;
	JobList jl ;
	Simulation list ;
	
	while(num != 0){
		Simulation list ;
		if(num==1)
			jl.Print() ;
		else if(num==2)
			list.Print() ;
		cout<<endl<<"0:QUIT"<<endl<<"1:sort"<<endl<<"2:simulate"<<endl ;
		cin>>num ;
	}
}

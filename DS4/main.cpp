// 10727153 �f�y�E 10727157 ���շu 
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
struct jobType{  //�u�@ 
	int OID;
	int arrival;
	int duration;
	int timeout;
};

struct abortJob{ // �������u�@ 
	int OID ;
	int abort ;
	int delay ;
};

struct done{ // �������u�@ 
	int OID ;
	int departure ;
	int delay ;
};

class JobList{  // �B�z���Ȥ@ 
	vector<jobType>aList;
	string fileID;
	string fileNumber ;
	
	clock_t read, readDone, sort, sortDone, print, printDone;
	
	void Init(){
		aList.clear() ;
	}
	
	bool Read(){  // Ū�Jinput 
		
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

	void SortByArrival(){ // �Χƺ��ƧǳB�z 
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
	
	void Print(){  // �L�Xsorted 
		
		
		
		
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
    		printf("read : %f  sec\n", readTime/ CLOCKS_PER_SEC );	//�L�X�ɶ� 
			printf("sort : %f  sec\n", sortTime / CLOCKS_PER_SEC );	
			printf("print : %f  sec\n", printTime / CLOCKS_PER_SEC );		
		}
	}	 
};

class Simulation{  // �B�z���ȤG 
	vector<jobType>aList ;
	vector<jobType>aStoreList ;
	vector<abortJob>aAbortList ;
	vector<done>aDoneList ;
	int nowArrival = 0;
	string fileID ;
	string fileNumber ;	
	int total ;
	
	void Init(){ // ��l�� 
		aList.clear() ;
		aStoreList.clear() ;
		aAbortList.clear() ;
		aDoneList.clear() ;
		nowArrival = 0 ;
	}
	
	bool Read(){ // Ū�Jsorted 

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
	
	void Work(){ // �B�z�u�@ 
		jobType nowJob ;
		nowArrival = aList[0].arrival ;		
		nowJob = aList[0] ;
		aList.erase(aList.begin()) ;
		
		while(!aList.empty()){
			
			Store() ;
						
			done temp ;
			temp.OID = nowJob.OID ;                    // �����ثe���u�@ 
			if(nowArrival<nowJob.arrival)
				nowArrival = nowJob.arrival ;
			temp.departure = nowArrival + nowJob.duration ;
			temp.delay = nowArrival - nowJob.arrival ;
			aDoneList.push_back(temp) ;
					
			nowArrival = nowArrival + nowJob.duration ;
			
			
			Delete() ;  // �����u�@(��C�w��) 
			Delete2() ; // ������C�����u�@ 
			if(aStoreList.empty()&&aList.empty())
				break ;
				
			nowJob = aStoreList[0] ;
			aStoreList.erase(aStoreList.begin()) ;			
		}
		
	}
	
	void Store(){  // �N�u�@�s�J��C 
		while(aStoreList.size()<3 && !aList.empty()){
			aStoreList.push_back(aList[0]) ;
			aList.erase(aList.begin()) ;
		}
	}

	void Delete(){  // �����u�@(��C�w��)  
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

	void Delete2(){  // ������C�����u�@ 
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

	float Delay(){  // �p�⥭��Delay 
		int delay ;
		for(int i = 0 ; i < aAbortList.size() ; i++) 
			delay += aAbortList[i].delay ;
		for(int j = 0 ; j < aDoneList.size() ; j++)
			delay += aDoneList[j].delay ;
			
		delay = (float)delay/total ;
	}
	public:
		
	void Print(){ // �L�Xoutput 
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

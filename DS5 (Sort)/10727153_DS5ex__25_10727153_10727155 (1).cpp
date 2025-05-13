//10727153 呂宜鴻 10727155 曾博暉 
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
struct collegeType{
	string rawR ;
	int gNum ;	
};

class ClassList{
	string fileName  ;
	string fileNumber ;
	string sortName ;
	vector<collegeType>aList ;
	vector<collegeType>cSet ;
	vector<collegeType>aSelectList ;
	vector<collegeType>aBubbleList ;
	vector<collegeType>aQuickList ;
	vector<collegeType>aMergeList ;
	vector<collegeType> aRadixList ;
	int i = 1 ;
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

	int findMin(int i){ //找出list中所要求範圍的最小值 
		int min = 0 ;
		for(int x = 0 ; x < i; x++){
			if(aSelectList[x].gNum<aSelectList[min].gNum)
				 min = x ;
		}
		
		return min ;
	}
	
			

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
			
			SetGNum() ;
//			for(int j = 0 ; j < aList.size()  ;j++)
//				cout<< aList[j].rawR << "\t"<< aList[j].gNum <<endl ;	
			return true ;
			
				
		}
		return false ;
	}

	
	void SelectSort(){ // SelectSort
		clock_t ss, sd ;
		ss = clock();
		collegeType temp ;
		aSelectList = aList ;
		int i = aSelectList.size() - 1;
		for(;i>0 ; --i){
			int min = findMin(i+1);
			temp = aSelectList[i] ;
			aSelectList[i] = aSelectList[min] ;	
			aSelectList[min] = temp	;
		}
		sd = clock();
//		FILE *fout = NULL;
//		double time = sd - ss;		
//    	printf("select sort : %2lf  ms\n", time );
//    	
//    	
//		string fileID ;
//		fileID = "select_sort" + fileNumber + ".txt" ;
//		char* temps ;
//		fout=fopen(fileID.c_str(),"w");
//		for(int i = 0 ; i < aSelectList.size() ; i++){
//			fprintf(fout,"%s\n", aSelectList[i].rawR.c_str()) ;
//		}
//			
//
//		fclose(fout);
	}	
	
	void BubbleSort(){  // BubbleSort
		clock_t bs, bd ;
		bs = clock() ;
		bool sorted = false ;
		collegeType temp ;
		aBubbleList = aList ;
		for(int i = 1 ; i < aBubbleList.size() && !sorted ; ++i){
			sorted = true ;
			for(int j = 0 ; j < aBubbleList.size()-i ;j++){
				if(aBubbleList[j].gNum<aBubbleList[j+1].gNum){
					temp = aBubbleList[j] ;
					aBubbleList[j] = aBubbleList[j+1] ;	
					aBubbleList[j+1] = temp	;
					sorted = false ;
				}
			}
		}
		
//		bd = clock() ;
//		double time = bd - bs;
//		
//    	printf("bubble sort : %2lf  ms\n", time );
//    	
//		FILE *fout = NULL;
//		string fileID ;
//		fileID = "bubble_sort" + fileNumber + ".txt" ;
//		char* temps ;
//		fout=fopen(fileID.c_str(),"w");
//		for(int i = 0 ; i < aBubbleList.size() ; i++){
//			fprintf(fout,"%s\n", aBubbleList[i].rawR.c_str()) ;
//		}
//			
//
//		fclose(fout);
	}
	
	void Merge( int first, int mid, int last ) { //排序 
		int first1 = first ;
		int last1 = mid ;
	
		int first2 = mid+1 ;
		int last2 = last ;
	
		int i = 0 ;
		vector<collegeType> temp ;
		while ( (first1 <= last1) && (first2 <= last2) ) {
			if ( aMergeList[first1].gNum < aMergeList[first2].gNum ) {
				temp.push_back( aMergeList[first2] ) ;
				first2++ ;
			}
			else{
				temp.push_back( aMergeList[first1] ) ;
				first1++ ;			
			}
		} // while
	
		while ( first1 <= last1 ) {
			temp.push_back( aMergeList[first1] ) ;
			first1++ ;
		} // while
	
		while ( first2 <= last2 ) {
			temp.push_back( aMergeList[first2] ) ;
			first2++ ;
		} // while
	
	
		while ( first <= last ) {
			aMergeList[first] = temp[i] ;
			first++ ;
			i++ ;
		} // while
	
	} // Merge()

	void MergeSort( int first, int last ) { //MergeSort 
		if ( first < last ) {
			int mid = ( first + last ) / 2 ;
			MergeSort( first, mid ) ;
			MergeSort( mid+1, last ) ;
			Merge( first, mid, last ) ;
		} // if
		
	}  // MergeSort()

	void Partition( int first, int last, int &pivot ) {//排序 
		int biglast = pivot ;
		int unknown = pivot + 1 ;
		while ( unknown <= last ) {
			if ( aQuickList[unknown].gNum > aQuickList[pivot].gNum ) {
				biglast++ ;
				swap( aQuickList[biglast], aQuickList[unknown] ) ;
			} // if
		
			unknown++ ;
		} // while
	
		swap( aQuickList[pivot], aQuickList[biglast] ) ;
		pivot = biglast ;
	} // Partition()

	void QuickSort( int first, int last ) {// QuickSort
		
		int pivot = first ;
		if ( first < last ) {
			Partition( first, last, pivot ) ;
			QuickSort( first, pivot-1 ) ;
			QuickSort( pivot+1, last ) ;
		} // if
	
	} // QuickSort()
	
	void SetMissionTwo(){ //設定Merge sort和Quick sort要用的list 
		aQuickList = aList ;
		aMergeList = aList ;
	}
	
	int ListSize(){ //return list size
		return aList.size() ;
	}	
	
	void PrintM(){ //印出merge sort的結果 
		FILE *fout = NULL;
		string fileID ;
		fileID = "merge_sort" + fileNumber + ".txt" ;
		fout=fopen(fileID.c_str(),"w");
		for(int i = 0 ; i < aMergeList.size() ; i++){
			fprintf(fout,"%s\n", aMergeList[i].rawR.c_str()) ;
		}
			

		fclose(fout);
				
	}
	
	void PrintQ(){//印出quick sort的結果 
		
		FILE *fout = NULL;
		string fileID ;
		fileID = "quick_sort" + fileNumber + ".txt" ;
		char* temps ;
		fout=fopen(fileID.c_str(),"w");
		for(int i = 0 ; i < aQuickList.size() ; i++){
			fprintf(fout,"%s\n", aQuickList[i].rawR.c_str()) ;
		}
		fclose(fout);
				
	}
	
	void RadixSort(){
		int first = 0 ;
		int last = aList.size()-1 ;
		aRadixList = aList ;
		collegeType temp[aList.size()];
		int maxData ;
		int bucket[10],i ;
		for(maxData=aRadixList[first].gNum, i=first+ 1 ; i<=last;i++ )
			if(maxData<aRadixList[i].gNum)
				maxData = aRadixList[i].gNum ;
		
		for(int base=1;(maxData/base)>0;base*=10){
			for(i=first;i<=last;i++)
				bucket[(aRadixList[i].gNum/base)%10+1]++;
			bucket[0]=0;
			for(i=1;i<10;i++)
				bucket[i]+=bucket[i-1];
			for(i=first;i<=last;i++)
				temp[bucket[(aRadixList[i].gNum/base)%10]++] = aRadixList[i];
			for(i=first;i<=last;i++)
				aRadixList[i]=temp[i];
		}
		

	}
	
	void RadixSort2(){
		int first = 0 ;
		int last = aList.size()-1 ;
		aRadixList = aList ;
		collegeType temp[10][aRadixList.size()];
		int maxData ;
		int counter[10]={0},i,j ;
		for(maxData=aRadixList[first].gNum, i=first+ 1 ; i<=last;i++ )
			if(maxData<aRadixList[i].gNum)
				maxData = aRadixList[i].gNum ;
		
		for(int base=1;(maxData/base)>0;base*=10){
			for(i=first;i<=last;i++){
				int LSD = (aRadixList[i].gNum/base)%10 ;
				temp[LSD][counter[LSD]] = aRadixList[i] ;
				counter[LSD]++;
			}
			
			int k =0;
			for	(i=9;i>=0;i--){
				if(counter[i]>0){
					for(j=0;j<counter[i];j++,k++)
						aRadixList[k]=temp[i][j];
					counter[i]=0;
				}
			}
			
		}
		

	}
	
	void Print3(){
		FILE *fout = NULL;
		string fileID ;
		fileID = "radix_sort" + fileNumber + ".txt" ;
		char* temps ;
		fout=fopen(fileID.c_str(),"w");
		for(int i = 0 ; i < aRadixList.size() ; i++){
			fprintf(fout,"%s\n", aRadixList[i].rawR.c_str()) ;
		}
		fclose(fout);
	}
	
	void PrintTime(){
		clock_t start,end;
		int selectTime,bubbleTime,mergeTime,quickTime,radixTime;
		selectTime = 0 ;
		for(int i = 1 ;i<=10;i++){
			start = clock();
			SelectSort();
			end = clock();
			selectTime = selectTime + (end - start) ;
		}
		
		selectTime = selectTime/10 ;
		
		bubbleTime = 0 ;
		for(int i = 1 ;i<=10;i++){
			start = clock();
			BubbleSort();
			end = clock();
			bubbleTime = bubbleTime + (end - start) ;
		}
		
		bubbleTime = bubbleTime/10 ;
		
		mergeTime = 0 ;
		for(int i = 1 ;i<=10;i++){
			SetMissionTwo() ;
			start = clock();
			MergeSort(0,ListSize()-1);
			end = clock();
			mergeTime = mergeTime + (end - start) ;
		}
		
		mergeTime = mergeTime/10 ;	
		
		quickTime = 0 ;
		for(int i = 1 ;i<=10;i++){
			SetMissionTwo() ;
			start = clock();
			QuickSort(0,ListSize()-1);
			end = clock();
			quickTime = quickTime + (end - start) ;
		}
		
		quickTime = quickTime/10 ;
		
		radixTime = 0 ;
		for(int i = 1 ;i<=10;i++){
			start = clock();
			RadixSort2();
			end = clock();
			radixTime = radixTime + (end - start) ;
		}
		
		radixTime = radixTime/10 ;
			
		FILE *fout = NULL;
    	

		string fileID ;
		fileID = "sort_time.txt" ;
		fout=fopen(fileID.c_str(),"a+");
		if(i==1)
			fprintf(fout,"\tSelect\tBubble\tMerge\tQuick\tRadix\n") ;
		fprintf(fout,"\nTest%d\t%d\t%d\t%d\t%d\t%d\n",i,selectTime,bubbleTime,mergeTime,quickTime,radixTime) ;
		fclose(fout);
		i++ ;		
		
	} 
};

int main(int argc, char** argv) {
	ClassList list ;
	int num ;
	clock_t one,two,three ;
	clock_t m3start, m3end ;
	cout<<endl<<"0:QUIT"<<endl<<"1:Select sort & Bubble sort"<<endl<<"2:Merge sort & Quick sort"<<endl<<"3:Radix sort"<<endl ;
	cin>>num ;
	bool have ;
	while(num != 0){
		have = list.Read() ;
		if(num==1&&have){
			list.SelectSort() ;
			list.BubbleSort() ;
		}
		
		else if(num==2&&have){
			list.SetMissionTwo() ;
			one = clock();
			list.MergeSort(0, list.ListSize()-1) ;
			two = clock();
			list.QuickSort(0, list.ListSize()-1) ;
			three = clock() ;
			list.PrintM() ;
			list.PrintQ() ;
			double time = two-one ;
			printf("merge sort : %2lf  ms\n", time );
			time = three-two ;
			printf("quick sort : %2lf  ms\n", time );
			
		}
		
		else if(num==3&&have){
			m3start = clock() ;
			list.RadixSort2();
			m3end = clock();
			list.Print3();
			double time = m3end-m3start ;
			printf("radix sort : %2lf  ms\n", time );
		}
		
		else if(num==4&&have){
			list.PrintTime();
		}
		
		cout<<endl<<"0:QUIT"<<endl<<"1:Select sort & Bubble sort"<<endl<<"2:Merge sort & Quick sort"<<endl<<"3:Radix sort"<<endl ;
		
		cin>>num ;
	}		
	return 0;
}

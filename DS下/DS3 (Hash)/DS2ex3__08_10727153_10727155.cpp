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
#include <time.h>

using namespace std;

#define COLUMNS 6				//number of scores for each student
#define MAX_LEN 10				//array size of student id and name
#define BIG_INT 255				//integer upper bound

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct sT{				//type of student record
	char	sid[MAX_LEN];		//student id
	char	sname[MAX_LEN];		//student name
	unsigned char	score[COLUMNS];		//a set of scores in [0,100]
	float	mean;				//the average if scores
}studentType;

typedef struct hT{
	string	sid;		//student id
	string	sname;		//student name
	float	mean;				//the average if scores
	int		hvalue;	
}hashType;

class Hash{
	vector<hashType> aList;
	int hashSize ;
	
	void MakeFile( string fileName, hashType quadratic[] ) {			//輸出雜湊表 
		int i = 0 ;
		FILE *fout = NULL;		
		fout = fopen( fileName.c_str(), "w" ) ;
		
		while ( i < hashSize ) {
			if ( quadratic[i].hvalue != 0 ) {
				fprintf( fout,"[%d]\t%d,\t%s,\t%s,\t%g\n", i, quadratic[i].hvalue, quadratic[i].sid.c_str(), quadratic[i].sname.c_str(), quadratic[i].mean ) ;
			}
			else {
				fprintf( fout, "[%d]\n", i ) ;
			}
			i++ ;
		}

		fclose( fout ) ;
	}
	
	int Text2Binary(string fileName){		//get records from a text file & save as a binary file
		fstream inFile,outFile;				//file handles
		int stNo = 0;
		if(!fileName.compare("0"))		//No file to open, so quit
			return false;
		inFile.open(("input"+fileName+".txt").c_str(),fstream::in);		//open a file
		if(!inFile.is_open())
			return false;
			
		//fileName = "input"+fileName+".bin";
		outFile.open(("input" + fileName + ".bin").c_str(),fstream::out|fstream::binary);		//creat a binary file
		if(outFile.is_open()){
			char rBuf[BIG_INT];	//buffer to keep one whole record
				
			while(inFile.getline(rBuf,BIG_INT,'\n')){	//retrieve one entire record from file
				string	temp;		//duplicate a string in another format
				studentType oneSt; 	//keep one record with all the required fields
				int cNo = 0, pre = 0, pos = 0; //indicators to extract each field in record
					
				stNo++;				//number of records
				temp.assign(rBuf);	//make a duplicate of the entire record
				pos = temp.find_first_of('\t',pre);	//move to the end of the first field	
				while(pos != string::npos){
					switch(++cNo)
					{
						case 1:strcpy(oneSt.sid,temp.substr(pre,pos-pre).c_str());
							break;		//copy a student id
						case 2:strcpy(oneSt.sname,temp.substr(pre,pos-pre).c_str());
							break;		//copy a student name
						default: oneSt.score[cNo-3] = atoi(temp.substr(pre,pos-pre).c_str());
							break;		//copy each score
							
					}
					pre = ++pos;
					pos = temp.find_first_of('\t',pre);	//move to the end of the next field
				}
				pos = temp.find_last_of('\t');		//position of the rightmost tab
				oneSt.mean = atof(temp.substr(pos+1).c_str());	//copy the average score
				outFile.write((char *)&oneSt,sizeof(oneSt));	//write the entire record into a Binary file
			}
			outFile.close();		//write out the binary file
		}
		
		inFile.close();
		return stNo;
	}
	
	bool readBinary(string fileName){			//get records from a file
		fstream	binFile;
		studentType	oneSt;						//keeponerecord with the required fields
		int stNo = 0;							//total number of students
		binFile.open(("input" + fileName + ".bin").c_str(),fstream::in|fstream::binary);	//open a file
		aList.clear() ;
		if(!binFile.is_open())
			return false ;
		else if(binFile.is_open()){
			binFile.seekg(0,binFile.end);
			stNo = binFile.tellg()/sizeof(oneSt);
			binFile.seekg(0,binFile.beg);
			for(int i = 0;i<stNo;i++){
				binFile.read((char*)&oneSt,sizeof(oneSt));	//read the entire record from a binary file
				hashType temp ;
				temp.sid = oneSt.sid ;
				temp.sname = oneSt.sname ;
				temp.mean = oneSt.mean ;
				aList.push_back(temp) ;
			}
		}
		binFile.close();
		return true ;
	}

	float QuaUnsuc( hashType quadratic[] ) {			//計算搜尋不存在值 
		int i = 0 ;
		int k = 1 ;
		int hashnum = 0 ;
		float unsuctimes = 0 ;
		
		while ( i < hashSize ) {
			hashnum = i ;
			while ( quadratic[hashnum].sid != "\0" ) {
				hashnum = ( i + ( k * k ) ) % hashSize ;
				k++ ;
			}
			
			
			unsuctimes = unsuctimes + k - 1 ;
			i++ ;
			k = 1 ;
		}		
		unsuctimes = unsuctimes / hashSize ;

		return unsuctimes ;
	} // QuaUnsuc()
			
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
		
		key = key % hashSize ;
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
	
	public:
	bool Read(string &fileName){	
		cout<<"Input a file number: ";
		cin>>fileName;
		bool haveBinFile = readBinary(fileName);
		if(!haveBinFile){
			cout<<endl<<"### input"<<fileName<<".bin does not exist! ###"<<endl ;
			if(!Text2Binary(fileName)){
				cout<<endl<<"### input"<<fileName<<".txt does not exist! ###"<<endl ;
				return false ;							
			}
			else
				readBinary(fileName);
		}
		
		return true ;

	}
	
	void DoubleHash(string fileName){					//任務二:雙重雜湊 
		int count = 1 ;
		float suctimes = 0 ;
		hashSize = SetSize(aList.size()*1.2) ;
		hashType doubleHash[hashSize] ;
		for(int i = 0 ; i<hashSize ; i++)
			doubleHash[i].hvalue = 0 ;		
		for(int j = 0 ; j<aList.size() ; j++){
			if(doubleHash[hash(aList[j].sid)].hvalue == 0){
				doubleHash[hash(aList[j].sid)].sid = aList[j].sid ; 
				doubleHash[hash(aList[j].sid)].sname = aList[j].sname ; 
				doubleHash[hash(aList[j].sid)].mean = aList[j].mean ;
				doubleHash[hash(aList[j].sid)].hvalue = hash(aList[j].sid) ;				
			}
			
			
			else{
				int key = hash(aList[j].sid) ;
				int x = step(aList[j].sid) ;
				while(true){
					if(doubleHash[key].hvalue == 0){
						doubleHash[key].sid = aList[j].sid ; 
						doubleHash[key].sname = aList[j].sname ; 
						doubleHash[key].mean = aList[j].mean ;
						doubleHash[key].hvalue = hash(aList[j].sid) ;
						break ;				
					}
					
					else{
						key = key + x ;
						key = key%hashSize ;
						count++ ;
					}
				}
			}
			
			suctimes = suctimes + count ;
			count = 1 ;
			

		}
		cout<<endl<<"Hash table has been successfully created by Double hashing"<<endl ;
		suctimes = suctimes / aList.size() ;
		printf( "seccessful：%.4f comparisons on average\n\n", suctimes ) ;				
		fileName = "double" + fileName + ".txt" ;
		MakeFile( fileName,  doubleHash ) ;
		
	}
	
	void MissionOne( string fileName ) {					//任務一:平方探測 
		int key = 0 ;
		int i = 0 ;
		int k = 0 ;
		int hashnum = 0 ;
		float suctimes = 0 ;
		float unsuctimes = 0 ;
		hashSize = SetSize(aList.size()*1.2) ;
		hashType quadratic[hashSize] ;
		for(int i = 0 ; i<hashSize ; i++)
			quadratic[i].hvalue = 0 ;
		while ( i < aList.size() ) {
			key = hash( aList[i].sid ) ;
			hashnum = key ;
			while ( true ) {
				if ( quadratic[hashnum].hvalue == 0 ) {
					quadratic[hashnum].sid = aList[i].sid ;
					quadratic[hashnum].sname = aList[i].sname ;
					quadratic[hashnum].mean = aList[i].mean ;
					quadratic[hashnum].hvalue = key ;
					break ;
				}
				
 				k++ ;
				hashnum = ( key + ( k * k ) ) % hashSize ;
			}
			
			suctimes = suctimes + k + 1 ;
			i++ ;
			k = 0 ;
		}
		unsuctimes = QuaUnsuc( quadratic ) ;
		suctimes = suctimes / aList.size() ;
		cout<<endl<<"Hash table has been successfully created by Quadratic probing"<<endl ;
		printf( "seccessful：%.4f comparisons on average\n\n", suctimes ) ;
		printf( "unseccessful：%.4f comparisons on average\n\n", unsuctimes ) ;
		fileName = "quadratic" + fileName + ".txt" ;
		MakeFile( fileName,  quadratic ) ;
	}

	
};

int main(int argc, char** argv) {
	Hash test;
	string fileName ;
	int cmd ;
	printf("******* Hash Table ******\n* 0. QUIT              *\n* 1. Quadratic probing *\n* 2. Double hashing    *\n*************************************\nInput a choice(0, 1, 2): ");
	cin>>cmd ;
	bool have = false;
	while(cmd!=0){
		if(cmd==1){
			if(test.Read(fileName)){
				test.MissionOne(fileName) ;	
				have = true ;				
			}
			
			else
				have = false ;
		
		}

		else if(cmd==2){
			if(have)
				test.DoubleHash(fileName);
			else
				cout<<"Please choose command 1 first!"<<endl ;
		}
		
		else{
			cout<<"ERROR COMMAND"<<endl ;
		}
		
		printf("******* Hash Table ******\n* 0. QUIT              *\n* 1. Quadratic probing *\n* 2. Double hashing    *\n*************************************\nInput a choice(0, 1, 2): ");
		cin>>cmd ;		
			
	}

	return 0;
}

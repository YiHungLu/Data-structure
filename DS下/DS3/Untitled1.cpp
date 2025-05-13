//10727153 §f©yÂE 10727155 ´¿³Õ·u 
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

#define COLUMNS 6
#define	MAX_LEN	10
#define	BIG_INT 255

typedef struct sT {
	char sid[MAX_LEN] ;
	char sname[MAX_LEN] ;
	unsigned char score[COLUMNS] ;
	float mean ;
} studentType ;

struct HashList {
	string sid ;
	string sname ;
	float mean ;
	int hvalue ;
};

class Hash {
	int hashsize ;
	vector<HashList> record ;
	
	void SetSize( int record ) {
		record = record * 1.2 ;
		int i = 0 ;
		int remain = 0 ;
		hashsize = record + 1 ;
		i = sqrt( hashsize ) ;
		while ( i != 1 ) {
			remain = hashsize % i ;
			if ( remain != 0 ) {
				i-- ;
			}
			else {
				hashsize++ ;
				i = sqrt( hashsize ) ;
			}
		}
		
	} // SetSize()
	
	int Hashing( string id ) {
		unsigned long long key = 0 ;
		int i = 0 ;
		key = (int) id[i] ;
		i++ ;
		while ( i < id.length() ) {
			key = key * (int) id[i] ;
			i++ ;
		}
		
		key = key % hashsize ;
		return key ;
	} // Hashing()
	
	float QuaUnsuc( HashList quadratic[] ) {
		int i = 0 ;
		int k = 1 ;
		int hashnum = 0 ;
		float unsuctimes = 0 ;
		
		while ( i < hashsize ) {
			hashnum = i ;
			while ( quadratic[hashnum].sid != "\0" ) {
				hashnum = ( i + ( k * k ) ) % hashsize ;
				k++ ;
			}
			
			
			unsuctimes = unsuctimes + k - 1 ;
			i++ ;
			k = 1 ;
		}
		
		cout << unsuctimes ;
		unsuctimes = unsuctimes / hashsize ;
		return unsuctimes ;
	} // QuaUnsuc()
	
	void MakeFile( string fileName, HashList quadratic[] ) {
		int i = 0 ;
		FILE *fout = NULL;		
		fout = fopen( fileName.c_str(), "w" ) ;
		
		while ( i < hashsize ) {
			if ( quadratic[i].sid != "\0" ) {
				fprintf( fout,"[%d]\t%d,\t%s,\t%s,\t%g\n", i, quadratic[i].hvalue, quadratic[i].sid.c_str(), quadratic[i].sname.c_str(), quadratic[i].mean ) ;
			}
			else {
				fprintf( fout, "[%d]\n", i ) ;
			}
			i++ ;
		}

		fclose( fout ) ;
	}
	 
	public :
	
	int Text2Binary( string fileName ) {
		fstream inFile, outFile ;
		int stNo = 0 ;
		
		do {
			if ( !fileName.compare("0") )
				return false ;
			
			inFile.open( ("input" + fileName + ".txt").c_str(), fstream::in ) ;
			if ( inFile.is_open() )
				break ;
				
		
		} while(true) ;
		fileName = "input" + fileName + ".bin" ;
		outFile.open( fileName.c_str(), fstream::out | fstream::binary ) ;
		if ( outFile.is_open() ) {
			char rBuf[BIG_INT] ;
			
			while ( inFile.getline( rBuf, BIG_INT, '\n' ) ) {
				string temp ;
				studentType oneSt ;
				int cNo = 0, pre = 0, pos = 0 ;
				
				stNo++ ;
				temp.assign( rBuf ) ;
				pos = temp.find_first_of( '\t', pre ) ;
				
				while ( pos != string::npos ) {
					switch( ++cNo ) {
						case 1 : strcpy( oneSt.sid, temp.substr( pre, pos - pre).c_str() ) ;
							break ;
						case 2 : strcpy( oneSt.sname, temp.substr( pre, pos - pre).c_str() ) ;
							break ;
						default : oneSt.score[cNo-3] = atoi( temp.substr( pre, pos - pre).c_str() ) ;
							break ;	
					}
					pre = ++pos ;
					pos = temp.find_first_of( '\t', pre ) ;
				} 
				
				pos = temp.find_last_of( '\t' ) ;
				oneSt.mean = atof( temp.substr(pos+1).c_str() ) ;
				outFile.write( (char*) &oneSt, sizeof(oneSt) ) ;
			}
			
			outFile.close() ;
		}
		
		inFile.close() ;
		return stNo ;
	} // Text2Binary()
	
	void readBinary( string fileName ) {
		fstream binFile ;
		studentType oneSt ;
		int stNo = 0 ;
		HashList temp ;
		
		binFile.open( ("input" + fileName + ".bin").c_str(), fstream::in | fstream::binary ) ;
		if ( binFile.is_open() ) {
			binFile.seekg( 0, binFile.end ) ;
			stNo = binFile.tellg() / sizeof( oneSt ) ;
			binFile.seekg( 0, binFile.beg ) ;
			
			for ( int i = 0; i < stNo; i++ ) {
				binFile.read( (char*) &oneSt, sizeof(oneSt) ) ;
				temp.sid = oneSt.sid ;
				temp.sname = oneSt.sname ;
				temp.mean = oneSt.mean ;
				record.push_back( temp ) ;
			}
		}
		binFile.close() ;
		SetSize( record.size() ) ;
	} // readBinary()
	
	void MissionOne( string fileName ) {
		int key = 0 ;
		int i = 0 ;
		int k = 0 ;
		int hashnum = 0 ;
		float suctimes = 0 ;
		float unsuctimes = 0 ;
		HashList quadratic[hashsize] ;
		cout<<endl ;
		while ( i < record.size() ) {
			key = Hashing( record[i].sid ) ;
			cout<<key<<endl ;
			hashnum = key ;
			while ( true ) {
				if ( quadratic[hashnum].sid == "\0" ) {
					quadratic[hashnum].sid = record[i].sid ;
					quadratic[hashnum].sname = record[i].sname ;
					quadratic[hashnum].mean = record[i].mean ;
					quadratic[hashnum].hvalue = key ;
					break ;
				}
				
 				k++ ;
				hashnum = ( key + ( k * k ) ) % hashsize ;
			}
			
			suctimes = suctimes + k + 1 ;
			i++ ;
			k = 0 ;
		}
		unsuctimes = QuaUnsuc( quadratic ) ;
		suctimes = suctimes / record.size() ;
		printf( "seccessful¡G%.4f\n", suctimes ) ;
		printf( "unseccessful¡G%.4f", unsuctimes ) ;
		fileName = "quadratic" + fileName + ".txt" ;
		MakeFile( fileName,  quadratic ) ;
	}
	
	void Print() {
		int i = 0 ;
		while ( i < record.size() ) {
			cout << record[i].sid << '\t' << record[i].sname << '\t' << record[i].mean << '\n' ;
			i++ ;
		}
	}
	
};

int main() {
	string fileName ;
	Hash hash ;
	cout << "Input a file number : " ;
	cin >> fileName ;
	hash.Text2Binary( fileName ) ;
	hash.readBinary( fileName ) ;
	hash.MissionOne( fileName ) ;
	
}


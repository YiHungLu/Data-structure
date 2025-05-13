//10727153 �f�y�E  10727155 ���շu 
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
enum Type { 
	OPEN_PARENTHESES = 31, CLOSE_PARENTHESES = 32, OPERATOR = 2, NUMBER = 1, ERROR = 0 
};             // �ΨӤ���Ū�i�Ӫ�������O 

enum ErrorType{  //�ΨӤ������~�����O 
	ERROR_CHARACTER = 1,
	EXTRA_OPEN_PARENTHESIS = 21,
	EXTRA_CLOSE_PARENTHESIS = 22,
	EXTRA_OPERATOR = 31,
	EXTRA_OPERAND = 32,
	NOT_INFIX = 33
};

struct Node{   //�s�Ÿ��B�Ʀr�B���O 
	int num ;
	char ch ;	
	Type type ;  // 123,1  +-*/,2  (),3	
	Node *next ;
};

typedef Node * NodePtr ;

struct Char{  //�bpostfix���s�B��Ÿ� 
	char ch ;
	Char *next ;
};

typedef Char * CharPtr ;

void Read(NodePtr &head){  //Ū�� 
	char temp ;
	scanf("%c", &temp) ;		
	while(temp==' ')
		scanf("%c", &temp) ; 

	if(temp!='\n'){
		head = new Node ;
		head->ch = temp ;
		head->next = NULL ;
		Read(head->next) ;
	}		
}

void SetType(NodePtr &head){  //�]�wŪ�i�Ӫ�������O 
	if(head!=NULL){
		if(head->ch=='(')
			head->type = OPEN_PARENTHESES ;
		else if(head->ch==')')
			head->type = CLOSE_PARENTHESES ;
		else if(head->ch=='+'||head->ch=='*'||head->ch=='-'||head->ch=='/')
			head->type = OPERATOR ;
		else if(head->ch>=0 && head->ch<='9')
			head->type = NUMBER ;
		else
			head->type = ERROR ;
			
		SetType(head->next) ;
	}
}


bool CheckCharacter(NodePtr head){  //�ˬd�O�_�����~�Ÿ� 
	if(head!=NULL){
		if(head->type==ERROR)
			return false ;
		else
			return CheckCharacter(head->next) ;
	}
	
	return true ;
	
}

bool CheckParentheses(NodePtr head, int &haveOpen){  //�ˬd�A�� 
	if(head!=NULL){
		if(head->ch=='('){
			haveOpen++ ;
		}
		
		else if(head->ch==')'){
			haveOpen-- ;
		}
		
		if(haveOpen<0)
			return false ;
		
		return CheckParentheses(head->next, haveOpen) ;			
	}
	
	if(haveOpen!=0)
		return false ;
		
	return true ;
}

bool CheckRule(NodePtr head, Type &lastType, ErrorType &errorType){  //�ˬd�B�⪺�W�h 
	if(head!=NULL){
		
		if(head->type == OPEN_PARENTHESES){   
			if(head->next->type==OPERATOR || head->next->type==CLOSE_PARENTHESES){
				errorType=NOT_INFIX ;
				return false ;				
			}
		}
		
		if(lastType==OPERATOR){  // �B��Ÿ��᭱�u�঳�Ʀr�Υ��A�� 
			if(head->type==NUMBER||head->type==OPEN_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERATOR ;
				return false ;
			}
		}
		
		else if(lastType==OPEN_PARENTHESES ){// ���A���᭱�u�঳�Ʀr�Υ��A�� 
			if(head->type==NUMBER||head->type==OPEN_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=NOT_INFIX ;
				return false ;
			}
		}
		
		else if(lastType==CLOSE_PARENTHESES){//�k�A���᭱�u�঳�B��Ÿ��Υk�A�� 
			if(head->type==OPERATOR||head->type==CLOSE_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERAND ;
				return false ;
			}
		}
		
		else if(lastType==NUMBER){// �Ʀr�᭱�u�঳�Ʀr�B�B��Ÿ��Υk�A�� 
			if(head->type==NUMBER||head->type==OPERATOR||head->type==CLOSE_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERAND ;
				return false ;
			}
		}
		

	}
	if(lastType==OPERATOR){ //�p�G�̫�@�ӬO�B��Ÿ��A�h���~ 
		errorType=EXTRA_OPERATOR ;
		return false ;
	}

		 
	return true ;
}

bool Check( NodePtr head, ErrorType &errorType ){ //�ˬd�Ҧ����~ 
	int haveOpen = 0 ;
	Type lastType = OPERATOR ; 
	if(head==NULL) {
		errorType=EXTRA_OPERATOR ;
		return false ;
	}
	if(!CheckCharacter(head)){
		errorType = ERROR_CHARACTER ;
		return false ;
	}
	
	else if(!CheckParentheses(head, haveOpen)){
		if(haveOpen>0)
			errorType = EXTRA_OPEN_PARENTHESIS ;
		else if(haveOpen<0)
			errorType = EXTRA_CLOSE_PARENTHESIS ;
			
		return false ;
	}
	
	else if(!CheckRule(head, lastType, errorType)){
		return false ;
	}
	
	return true ;
}

void PrintError(NodePtr head, ErrorType errorType){//�L�X���~ 
	NodePtr run ;
	run = head ;
	if(errorType == ERROR_CHARACTER ){
		cout<<"ERROR 1:" ;
		for(;run!=NULL;run = run->next) {
			if(run->type = ERROR){
				cout<<run->ch ;
				break ;
			}
		}
		cout<<"is not a legitimate character."<<endl ;
	}
	
	else if(errorType == EXTRA_OPEN_PARENTHESIS)
		cout<<"ERROR 2:there is one extra open parenthesis." << endl ;
	else if(errorType == EXTRA_CLOSE_PARENTHESIS)
		cout<<"ERROR 2:there is one extra close parenthesis." << endl ;
		
	else if(errorType ==EXTRA_OPERATOR)
		cout<<"ERROR 3:there is one extra operator." << endl ;
	else if(errorType ==EXTRA_OPERAND)
		cout<<"ERROR 3:there is one extra operand." << endl ;
	else if(errorType == NOT_INFIX)
		cout<<"Error 3: it is not infix in the parentheses."<< endl ;
}

void SetNum(NodePtr head, NodePtr &infix){//�N�r���ഫ���Ʀr 
	int num ;
	if(head!=NULL){
		if(head->type==NUMBER){
			if(infix==NULL){
				infix = new Node ;
				infix->next = NULL ;
				num = int(head->ch) -48 ;
				infix->num = num ;
				infix->type = head->type ;
				SetNum(head->next, infix) ;
			}
			
			else{
				num = int(head->ch) ;
				infix->num = infix->num*10 + num -48 ;
				SetNum(head->next, infix) ;
			}	
		}
		
		else{
			if(infix==NULL){
				infix = new Node ;
				infix->next = NULL ;
				infix->ch = head->ch ;
				infix->type = head->type ;
				SetNum(head->next, infix->next) ;
			}
			
			else{
				SetNum(head, infix->next) ;
			}
		}			
	}
}

void Postfix(NodePtr infix, CharPtr &ch, int &have, bool &first){//�N�����ର��� 
	CharPtr temp = NULL;
	if(infix!=NULL){
		if(infix->type==NUMBER) { //�Y���Ʀr�A�h���L�X�Ʀr 
			if(!first)
				cout<<"," ;
			else
				first = false ;
			cout<<infix->num ;
			if(ch!=NULL){
				if(ch->ch=='*'||ch->ch=='/'){ //�Y�e�@�Ӧs���Ÿ���*��/�A�N�����L�X 
					cout<<","<<ch->ch ;
					temp = ch ;
					ch = ch->next ;
					free(temp) ;
				}
			}				
		}
		
		else{
			if(infix->ch=='('){ // �YŪ��(�A�s�Jch���A�ðO��Ū�L�@��( 
				have++ ;
				temp = new Char ;
				temp->ch = infix->ch ;
				temp->next = ch ;
				ch = temp ;				
			}
			
			else if(infix->type == OPERATOR){ // �Y���B��Ÿ� 
				if(infix->ch=='+'||infix->ch=='-'){ //�YŪ��+��-�B�e�@�Ӧs����+��-�A�h�����L�X�e�@�� 
					if(ch!=NULL){
						if(ch->ch=='+'||ch->ch=='-'){
							cout<<","<<ch->ch ;
							temp = ch ;
							ch = ch->next ;
							free(temp) ;
						}						
					}
				}
				
				temp = new Char ; //�NŪ�쪺�Ÿ��s�_�ӡA�é���C���̤W�� 
				temp->ch = infix->ch ;
				temp->next = ch ;
				ch = temp ;
				
			}
			
			else if(infix->ch==')'){ //�YŪ��)�A�h�N�s���Ÿ��L�X�ӡA����J��e�@��( 
				while(have>0 && ch->ch!='(' && ch != NULL){
					temp = ch ;
					if(ch->ch!=')')
						cout<<","<<ch->ch ;
					ch = ch->next ;
					free(temp) ;
				}
				
				have-- ;
				temp = ch ;
				ch = ch->next ;
				free(temp) ;
			}
		}
		
		Postfix(infix->next, ch, have, first) ;
	}
	
	else{
		while(ch!=NULL){ //�N�ѤU���B��Ÿ����L�X�� 
			temp = ch ;
			cout<<","<<ch->ch ;
			ch = ch->next ;
			free(temp) ;
		}
		
		cout<<endl ;
	}

		


}


int main(int argc, char** argv) {
	int input = 0 ;
	int have = 0 ;
	NodePtr head = NULL ;
	NodePtr infix = NULL ;
	NodePtr run ;
	CharPtr ch = NULL;
	char temp ;
	cout<<endl<<"( 0 : Quit ; 1 : Work )"<<endl ;
	cin>>input ;
	while(input!=0&&input!=1){
		cout<<"ERROR COMMAND"<<endl ;
		cout<<endl<<"( 0 : Quit ; 1 : Work )"<<endl ;
		cin>>input ;
	}
		

	while(input!=0){
		scanf("%c", &temp) ;
		bool first = true ;
		cout<<"input infix :" ;	
		Read(head) ;                 // Ū�J 
		SetType(head) ;              //�]�w 
	
		ErrorType errorType ;
		if(!Check(head, errorType))  //�ˬd 
			PrintError(head, errorType) ;  //�L�X���~ 
		else { // ���T 
			cout<<endl<<"It is a legitimate infix expression."<< endl ;
		
			SetNum(head, infix) ; //  �����ର�Ʀr 	
			
			Postfix(infix, ch, have, first) ; //�ର��� 
		}
		
		free(infix) ;  //�M�z�Τ��쪺��� 
		infix = NULL ;
		free(ch) ;
		ch = NULL ;
		free(head) ;
		head = NULL ;
		cout<<endl<<"( 0 : Quit ; 1 : Work )"<<endl ;			
		cin>>input ;
		while(input!=0&&input!=1){
			cout<<"ERROR COMMAND"<<endl ;
			cout<<endl<<"( 0 : Quit ; 1 : Work )"<<endl ;
			cin>>input ;
		}
	}
}

//10727153 呂宜鴻  10727155 曾博暉 
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
};             // 用來分類讀進來的資料類別 

enum ErrorType{  //用來分類錯誤的類別 
	ERROR_CHARACTER = 1,
	EXTRA_OPEN_PARENTHESIS = 21,
	EXTRA_CLOSE_PARENTHESIS = 22,
	EXTRA_OPERATOR = 31,
	EXTRA_OPERAND = 32,
	NOT_INFIX = 33
};

struct Node{   //存符號、數字、類別 
	int num ;
	char ch ;	
	Type type ;  // 123,1  +-*/,2  (),3	
	Node *next ;
};

typedef Node * NodePtr ;

struct Char{  //在postfix中存運算符號 
	char ch ;
	Char *next ;
};

typedef Char * CharPtr ;

void Read(NodePtr &head){  //讀檔 
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

void SetType(NodePtr &head){  //設定讀進來的資料類別 
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


bool CheckCharacter(NodePtr head){  //檢查是否有錯誤符號 
	if(head!=NULL){
		if(head->type==ERROR)
			return false ;
		else
			return CheckCharacter(head->next) ;
	}
	
	return true ;
	
}

bool CheckParentheses(NodePtr head, int &haveOpen){  //檢查括號 
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

bool CheckRule(NodePtr head, Type &lastType, ErrorType &errorType){  //檢查運算的規則 
	if(head!=NULL){
		
		if(head->type == OPEN_PARENTHESES){   
			if(head->next->type==OPERATOR || head->next->type==CLOSE_PARENTHESES){
				errorType=NOT_INFIX ;
				return false ;				
			}
		}
		
		if(lastType==OPERATOR){  // 運算符號後面只能有數字或左括號 
			if(head->type==NUMBER||head->type==OPEN_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERATOR ;
				return false ;
			}
		}
		
		else if(lastType==OPEN_PARENTHESES ){// 左括號後面只能有數字或左括號 
			if(head->type==NUMBER||head->type==OPEN_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=NOT_INFIX ;
				return false ;
			}
		}
		
		else if(lastType==CLOSE_PARENTHESES){//右括號後面只能有運算符號或右括號 
			if(head->type==OPERATOR||head->type==CLOSE_PARENTHESES){
				lastType = head->type ;
				return CheckRule(head->next, lastType, errorType) ;
			}
			
			else{
				errorType=EXTRA_OPERAND ;
				return false ;
			}
		}
		
		else if(lastType==NUMBER){// 數字後面只能有數字、運算符號或右括號 
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
	if(lastType==OPERATOR){ //如果最後一個是運算符號，則錯誤 
		errorType=EXTRA_OPERATOR ;
		return false ;
	}

		 
	return true ;
}

bool Check( NodePtr head, ErrorType &errorType ){ //檢查所有錯誤 
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

void PrintError(NodePtr head, ErrorType errorType){//印出錯誤 
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

void SetNum(NodePtr head, NodePtr &infix){//將字元轉換為數字 
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

void Postfix(NodePtr infix, CharPtr &ch, int &have, bool &first){//將中序轉為後序 
	CharPtr temp = NULL;
	if(infix!=NULL){
		if(infix->type==NUMBER) { //若為數字，則先印出數字 
			if(!first)
				cout<<"," ;
			else
				first = false ;
			cout<<infix->num ;
			if(ch!=NULL){
				if(ch->ch=='*'||ch->ch=='/'){ //若前一個存的符號為*或/，就直接印出 
					cout<<","<<ch->ch ;
					temp = ch ;
					ch = ch->next ;
					free(temp) ;
				}
			}				
		}
		
		else{
			if(infix->ch=='('){ // 若讀到(，存入ch中，並記錄讀過一個( 
				have++ ;
				temp = new Char ;
				temp->ch = infix->ch ;
				temp->next = ch ;
				ch = temp ;				
			}
			
			else if(infix->type == OPERATOR){ // 若為運算符號 
				if(infix->ch=='+'||infix->ch=='-'){ //若讀到+或-且前一個存的為+或-，則直接印出前一個 
					if(ch!=NULL){
						if(ch->ch=='+'||ch->ch=='-'){
							cout<<","<<ch->ch ;
							temp = ch ;
							ch = ch->next ;
							free(temp) ;
						}						
					}
				}
				
				temp = new Char ; //將讀到的符號存起來，並放到串列的最上方 
				temp->ch = infix->ch ;
				temp->next = ch ;
				ch = temp ;
				
			}
			
			else if(infix->ch==')'){ //若讀到)，則將存的符號印出來，直到遇到前一個( 
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
		while(ch!=NULL){ //將剩下的運算符號都印出來 
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
		Read(head) ;                 // 讀入 
		SetType(head) ;              //設定 
	
		ErrorType errorType ;
		if(!Check(head, errorType))  //檢查 
			PrintError(head, errorType) ;  //印出錯誤 
		else { // 正確 
			cout<<endl<<"It is a legitimate infix expression."<< endl ;
		
			SetNum(head, infix) ; //  降元轉為數字 	
			
			Postfix(infix, ch, have, first) ; //轉為後序 
		}
		
		free(infix) ;  //清理用不到的資料 
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

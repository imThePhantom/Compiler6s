#define nullString 22222

typedef struct Node{
	char*text;
	int*col;
	int count;
	struct Node *next;
}Node;

Node*newNode(){
	Node*tmp;
	tmp=(Node*)malloc(sizeof(Node));
	tmp->text=NULL;
	tmp->next=NULL;
	tmp->count=0;
	return tmp;
}
Node*newNodeContent(char text[]){
	Node*tmp;
	tmp=(Node*)malloc(sizeof(Node));
	tmp->next=NULL;
	tmp->text=text;
	tmp->count=0;
	return tmp;
}

int compare(Node*des,Node*sour){
	if(des->text==NULL || sour ->text ==NULL)
		return nullString;
	else return strcmp(des->text,sour->text);
}

Node*searchNode(Node*header,Node*node){
	int check=0;
	if(header!=NULL || node!=NULL)
	for(;header->next!=NULL;header=header->next){
		if(compare(header,node)==0){
			check=1;
			return header;
			break;
		}
	}
	if(check==0) return NULL;
}

Node*searchNodeContent(Node*header,char*text){
	int check=0;
	if(header!=NULL)
	for(;header->next!=NULL;header=header->next){
		if(header->text!=NULL && text!=NULL &&strcmp(header->text,text)==0){
			check=1;
			return header;
			break;
		}
	}
	if(check==0) return NULL;
}
// add node;

int addCol(Node*node,int a){
	int i;
	int check=1;
	if(node->count==0){
		node->col=(int*)malloc(sizeof(int));
		node->col[0]=a;
		node->count++;
	}else{
		for(i=0;i<node->count;i++)
			if(node->col[i]==a){
				check=0;
				break;
			}
		if(check!=0){
			node->col=(int*)realloc(node->col,sizeof(int)*(node->count+1));
			node->col[node->count]=a;
			node->count++;
		}
	}
}
int addBeforeNode(Node*des,Node*sour){
	if(sour!=NULL){
		des->next=sour->next;
		sour->next=des;
		return 1;
	}
	else return 0;
}

int addAfter(Node*des,Node*sour){
	if(sour==NULL)
		return 0;
	else{
		des->next=sour->next;
		sour->next=des;
		return 1;
	}
}

int addEnd(Node*header,Node*node){
	if(header!=NULL){
		while(header->next!= NULL) header=header->next;
		header->next=node;
		return 1;
	}else return 0;
}

int addFirst(Node*header,Node*node){
	if(header!=NULL){
		node->next=header->next;
		header->next=node;
		return 1;
	}else return 0;
}
//delete node;
int deleteNode(Node*header,Node*des){
	Node*tmp;
	int check=0;
	tmp=header;
	if(header==NULL || des== NULL)
		return 0;
	else{
		while(tmp->next!=NULL)
			if(compare(tmp->next,des)==0){
				check=1;
				deleteAfter(header,tmp);
				break;
			}else	tmp=tmp->next;
	}
	return check;
}
int deleteFirst(Node*header){
	Node*tmp;
	if(header->next==NULL)
		return 0;
	else{
		tmp=header->next;
		header->next=tmp->next;
		free(tmp);
		return 1;
	}
}
int deleteLast(Node*header){
	if(header->next==NULL)
		return 0;
	else{
		while(header->next->next!=NULL) 
			header=header->next;
		free(header->next);
		return 1;
	}
}
int deleteBefore(Node*header,Node*sour){
	Node*tmp,*tmp1;
	tmp=searchNode(header,sour);
	if(tmp==NULL || compare(sour,header->next)==0)
		return 0;
	else{
		tmp=searchNode(header,tmp);
		tmp1=tmp->next;
		tmp->next=tmp1->next;
		free(tmp1);
		return 1;
	}
}
int deleteAfter(Node*sour){
	Node*tmp;
	if(sour->next!=NULL){
		tmp=sour->next;
		sour->next=tmp->next;
		free(tmp);
		return 1;
	}else return 0;
}

int addNodeSort(Node*header,Node*des){
	int check=0;
	if(header->next==NULL){
		header->next=des;
	 	check=1;
	}else while(header->next!=NULL){
		if(compare(header->next,des)==nullString)
			check==-1;
		else if(compare(header->next,des)<0)
			header=header->next;
		else{
			des->next=header->next;
			header->next=des;
			check=1;
			break;
		}
	}
	if(check==0){
		header->next=des;
	 	check=1;
	}else if(check==-1)
	return 0;
	else return check;
}

void printNode(Node*header){
	int i;
	while(header->next!=NULL){
		if(header->text!=NULL)
			printf("%-15s |%d| ",header->text,header->count);
		for(i=0;i<header->count;i++){
			if(i!=header->count-1)
			printf("%d, ",header->col[i]);
		else printf("%d.\n",header->col[i]);
		}
		header=header->next;
	}
}

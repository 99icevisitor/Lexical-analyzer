using namespace std;
#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<algorithm>
#include<iomanip>
struct I_Node{//index,name,Vn,Vt,isStart,isEnd
	int index;
	char name;
	char Vn;
	char Vt;
	bool isStart;
	bool isEnd;
};
class _DFA{
	private:
		int left;
		char Vt;
		int right;
	public:
		_DFA(){
			left = -1;
			right = -1;
			Vt = '\0';
		}
		int getLeft(){
			return left;
		}
		int getRight(){
			return right;
		}
		char getVt(){
			return Vt;
		}
		void setLeft(int leftIndex){
			left = leftIndex;
		}
		void setRight(int rightIndex){
			right = rightIndex;
		}
		void setVt(char VtChar){
			Vt = VtChar;
		}
		void setAll(int leftIndex,char VtChar,int rightIndex){
			left = leftIndex;
			right = rightIndex;
			Vt = VtChar;
		}
		void memsetAll(){
			left = -1;
			right = -1;
			Vt = '\0';
		}
};
class _DFAs{
	private:
		_DFA sets[100];
		int count;
	public:
		_DFAs(){
			count = 0;
		}
		int getCount(){
			return count;
		}
		void addDFA(int leftIndex,char VtChar,int rightIndex){
			sets[count].setAll(leftIndex,VtChar,rightIndex);
			count++;
		}
		_DFA getDFA(int index){
			return sets[index];
		}
};
class subSet{//一个子集 
	private:
		int array[30];//子集中元素在Vn中的具体下标 
		int count;//子集元素总个数 
		bool isMark;
		bool isStart;
		bool isEnd;
		char a;
		int fromSubset;
	public:
		subSet(){
			memset(array,-1,30);
			count=0;
			a = '\0';
			isMark = false;
			isStart = false;
			isEnd = false;
			fromSubset = -1;
		} 
		int* getArray(){
			return array;
		}
		void addAsubSet(int index){
			array[count]=index;
			count++;
		}
		void setf(int beforeIndex){
			fromSubset = beforeIndex;
		}
		int getFromIndex(){
			return fromSubset;
		}
		void setMark(){
			isMark=true;
		}
		void setChar(char b){
			a=b;
		}
		char getChar(){
			return a;
		}
		int getCount(){
			return count;
		}
		bool isMarked(){
			return isMark;
		}
		void setStart(){
			isStart = true;
		}
		bool isTStart(){
			return isStart;
		}
		void setEnd(){
			isEnd = true;
		}
		bool isTEnd(){
			return isEnd;
		}
		int getElement(int index){
			return array[index];
		}
		void memsetAll(){
			memset(array,-1,30);
			count=0;
			a = '\0';
			isMark = false;
			isStart = false;
			isEnd = false;
			fromSubset = -1;
		}
};
bool isRepeat(subSet a,subSet b){
	bool ok = true;
	if(a.getCount()!=b.getCount()){
		ok=false;
	} 
	else{
		int arrayA[30],arrayB[30],num=a.getCount();
		for(int i=0;i<num;i++){
			arrayA[i]=a.getElement(i);
		}
		for(int i=0;i<num;i++){
			arrayB[i]=b.getElement(i);
		}
		sort(arrayA,arrayA+num);
		sort(arrayB,arrayB+num);
		for(int i=0;i<num;i++){
			if(arrayA[i]!=arrayB[i]){
				ok=false;
				break;
			}
		}
	}
	return ok;
}
struct subSets{
	subSet T[100];
	int count;
};
int getDefinedID(char a){//8:Vt集出现重复 9:Vn集出现重复 
	int ID=0;
	switch(a){
		case '=':
			ID=1;
			break;
		case '{':
			ID=2;
			break;
		case '}':
			ID=3;
			break;
		case ' ':
			ID=4;
			break;
		case '(':
			ID=5;
			break;
		case ')':
			ID=6;
			break;
		case ',':
			ID=7;
			break;
		default:
			break;	
	}
	return ID;
} 
int isComma(int i,string a,int length){//逗号是否有问题 （有问题：1；没问题：0） 
	if(i-1>0){
		if(getDefinedID(a[i-1])==4){
			return isComma(i-1,a,length);			
		}
		if(getDefinedID(a[i-1])==0||getDefinedID(a[i-1])==3){
			if(i+1<length){
				if(getDefinedID(a[i+1])==4){
					return isComma(i+1,a,length);
				}
				if(getDefinedID(a[i+1])==0||getDefinedID(a[i-1])==3){
					return 0;
				}
				else{
					return 1;
				}
			}
			else{
				return 1;
			}
		}
		else{
			return 1;
		}
	}
	else{
		return 1;
	}
}
bool isRepeated(char b[1000],int m,int n){//处理Vn、Vt中重复的情况 
	bool flag=false;
	for(int i=0;i<n;i++){
		if(i!=m&&b[i]==b[m]){
			flag=true;
			break;
		}
	}
	return flag;
}
void reportError(int errorType,int errorNO,int wrongNO[20]){
	if(errorType==2){
		switch(errorNO){
			case 0:
				cout<<"Grammatically correct!\n";
				break;
			case 1:
				cout<<"Grammatical Mistake 1:超出长度\n";
				cout<<"Line "<<wrongNO[11]<<endl;
				break;
			case 2:
				cout<<"Grammatical Mistake 2:正规文法表达式错误\n";
				cout<<"Error details >>\n";
						for(int k=0;k<20;k++){//处理错误信息 
							switch(wrongNO[k]){
								case 0:
									break;
								default:
									cout<<"line ";
									cout<<wrongNO[k];
									if(k==0){
										cout<<": Grammar name is not defined.\n";
									}
									if(k==2){
										cout<<": The sign is superfluous. Please delete '{'.\n";
									}
									if(k==3){
										cout<<": Symbol deficiency '}'.\n";
									}
									if(k==5){
										cout<<": The sign is superfluous. Please delete '('.\n";
									}
									if(k==6){
										cout<<": Symbol deficiency ')'.\n";
									}
									if(k==7){
										cout<<": Comma should be removed.\n";
									}
									if(k==8){
										cout<<": Duplicate collection in element Vn.\n";
									}
									if(k==9){
										cout<<": Duplicate collection in element Vt.\n";
									}
									if(k>=10){
										cout<<": Expression error.\n";
									}
									break;
							}
						}
				break;
			default:
				cout<<"line 1: Unknown error occurred.\n";
				break;
		}
	}
	else{
		cout<<"";
	}
}
bool isExist(char a,char b[1000],int num){//判读是否是已有元素
	bool result=0;//不是
	 for(int i=0;i<num;i++){
	 	if(b[i]==a){
	 		result=true;
	 		break;
		 }
	 }
	 return result;
}
bool isValidLine(string str){
	bool ok=false;
	for(int i=0;i<str.length();i++){
		if(str[i]!=' '){
			ok=true;
			break;
		}
	}
	return ok;
}
bool isLikeRule(string str,int lineNO){//判断该行语句是否可能为规则 
	bool result=false;
	for(int i=0;i<str.length();i++){
		if(i+1<str.length()&&str[i]=='-'&&str[i+1]=='>'){
			result=true;
			break;
		}
	}
	return result;
}
int getVaildLength(string str){//判断规则语句是否标准 
	int num=0;
	for(int i=0;i<str.length();i++){
		if(getDefinedID(str[i])!=4){
			num++;
		}
	}
	return num;
}
I_Node createNode(string str,int count,char start,char Vt[1000],char Vn[1000]){
	I_Node node;
	if(getVaildLength(str)>=4&&getVaildLength(str)<=5){//长度没有越界
		node.index=count;
		node.name=str[0];
		if(start == str[0]){
			node.isStart=true;
		}
		else{
			node.isStart=false;
		}
		if(getVaildLength(str)==4&&str[3]=='$'){
			node.isEnd=true;
			node.Vt='\0';
			node.Vn='\0';
		}
		else{
			node.isEnd=false;
		}
		if(isExist(str[3],Vt,strlen(Vt)))
			node.Vt=str[3];
		else if(isExist(str[3],Vn,strlen(Vn))){
			node.Vt='\0';
			node.Vn=str[3];
		}
		if(getVaildLength(str)==5&&isExist(str[4],Vn,strlen(Vn)))
			node.Vn=str[4];
		else if(getVaildLength(str)==4){
			node.Vn='\0';
		}
		else
			node.index=-1;
	}
	else{
		node.index=-1;
	}
	return node;
}
int getIndex(char Vn[1000],char a,int VnNum){
	for(int i=0;i<VnNum;i++){
		if(Vn[i]==a){
			return i;
		}
	}
	return -1;
}
bool isSubsetExisted(int a,subSets C,int ti){
	bool ok=false;
	if(C.count==0){
		ok=true;
	}
	else{
		for(int i=0;i<C.T[ti].getCount();i++){
			if(C.T[ti].getElement(i)==a){
				ok=true;
				break;
			}
		}
	}
	return ok;
}
int getUnmarked(subSets C){
	int result=-1;
	for(int i=0;i<C.count;i++){
		if(!C.T[i].isMarked()){
			result=i;
			break;
		}
	}
	return result;
}
bool isDFA(I_Node formula[1000],int formulaNum){
	bool ok = true;
	for(int i=0;i<formulaNum;i++){
		for(int j=0;j<formulaNum;j++){
			if(i!=j&&formula[i].name==formula[j].name&&formula[i].Vt==formula[j].Vt){
				ok=false;
				break;
			}
		}
		if(ok==false){
			break;
		}
	}
	return ok;
}
subSets change2CT(I_Node formula[1000],int VnNum,int VtNum,int formulaNum,char Vn[1000],char Vt[1000]){//DFA1 = change2DFA(formula1,NO1[0],NO2[0],rules1,Vn1,Vt1);
	subSets C;
	C.count=0;
	int count=0;
	int index;
	int next2mark=0;
	int* array;
	int Tcount=0;
	bool isrepeated = false;
	//T0初始化 
	for(int i=0;i<formulaNum;i++){
		if(formula[i].isStart){//得到的是在Vn中的位置 
			index=getIndex(Vn,formula[i].name,VnNum);
			if(index!=-1&&isSubsetExisted(Vn[index],C,count)){
				C.T[count].addAsubSet(index);
				C.T[count].setStart();
				C.T[C.count].setChar('$');
				C.T[C.count].setf(0);
				C.count++;
			}
		}
	}
	while(getUnmarked(C)!=-1){
		next2mark=getUnmarked(C);
		//mark(C.T[next2mark]);
		for(int k=0;k<VtNum;k++){//先匹配路径 
			isrepeated=false;
			for(int i=0;i<C.T[next2mark].getCount();i++){//在要被标记的子集的元素（状态）中 匹配 
				int element = C.T[next2mark].getElement(i);//状态 
				for(int j=0;j<formulaNum;j++){//对每一个公式 
					if(formula[j].name==Vn[element]&&formula[j].Vt==Vt[k]){//move(T,t)
						index=getIndex(Vn,formula[j].Vn,VnNum);
						if(index!=-1&&!isSubsetExisted(index,C,C.count)&&!isSubsetExisted(index,C,next2mark)){//这里有问题 
							C.T[C.count].addAsubSet(index);
							C.T[C.count].setf(next2mark+1);
							//处理终止状态
							for(int f=0;f<formulaNum;f++){
								if(formula[j].Vn==formula[f].name&&formula[f].isEnd){
									C.T[C.count].setEnd();
									break;
								}
							}
						}
					}
				}
			}
			//$-closure{move(T,t)} 
			Tcount = C.T[next2mark].getCount();
			for(int i=0;i<Tcount;i++){//当前标记的T的内容 
				C.T[C.count].addAsubSet(C.T[next2mark].getElement(i));
				if(C.T[next2mark].isTEnd()){
					C.T[C.count].setEnd();
				}
			}
			//如果这个子集和之前的子集重复 则本次不被记录为新的子集
			for(int i=0;i<C.count;i++){
				if(isRepeat(C.T[i],C.T[C.count])){
					isrepeated = true;
				}
			}
			if(isrepeated){
				int thisCount = C.T[C.count].getCount();
				C.T[C.count].memsetAll();
			} 
			else{
				C.T[C.count].setChar(Vt[k]);
				C.count++;
				//终结状态 
			}
		}
		C.T[next2mark].setMark();
		if(C.count>30){
			break;
		}
	}
	return C;
}
_DFAs createDFA(I_Node formula[1000],int formulaNum,char Vt[1000],char Vn[1000],int VtNum,int VnNum){//create DFA
	_DFAs dfa;
	for(int i=0;i<formulaNum;i++){
		dfa.addDFA(getIndex(Vn,formula[i].name,VnNum),formula[i].Vt,getIndex(Vn,formula[i].Vn,VnNum));
	}
	return dfa;
}
_DFAs changeSubset2DFA(subSets C){
	_DFAs dfa;
	int left;
	char Vt;
	int right;
	for(int i=0;i<C.count;i++){
		for(int j=0;j<C.count;j++){
			if(C.T[j].getFromIndex()==i+1){
				Vt = C.T[j].getChar();
				dfa.addDFA(i,Vt,j);
			}
		}
	}
	for(int i=0;i<C.count;i++){
		if(C.T[i].isTEnd()){
			dfa.addDFA(i,'\0',-1);
		}
	}
	return dfa;
}
bool isA(char a){
	if(a>='A'&&a<='Z'){
		return true;
	}
	else{
		return false;
	}
}
bool isB(char a){
	bool ok = false;
	if(a>='a'&&a<='z'){
		ok = true;
	}
	return ok;
}
bool isD(char a){
	bool ok = false;
	if(a>='0'&&a<='9'){
		ok = true;
	}
	return ok;
}
bool isEmpty(char a){
	bool ok = false;
	if(a==' '){
		ok = true;
	}
	return ok;
}	
bool isBoundaries(char a){
	bool ok = false;
	switch(a){
		case '{':
		case '}':	
		case '(':	
		case ')':
		case '#':
		case ';':
		case '\'':
		case '\"':
		case ',':
			ok = true;
			break;
		default:
			break;
	}
	return ok;
} 
int getBoundId(char a){
	int id = -1;
	switch(a){
		case '#':
			id = 0;
			break;
		case '\'':
			id = 1;
			break;
		case '\"':
			id = 2;
			break;
		case ';':
			id = 3;
			break;
		case ',':
			id = 4;
			break;
		case '{':
			id = 5;
			break;
		case '}':
			id = 6;
			break;	
		case '(':
			id = 7;
			break;	
		case ')':
			id = 8;
			break;
		default:
			break;
	}
	return id;
}
bool isLikeOperators(char a){
	bool ok =false;
	switch(a){
		case '+':
		case '-':
		case '*':
		case '/':
		case '=':
		case '>':
		case '<':
		case '!':
			ok = true;
			break;
		default:
			ok = false;
			break;
	}
	return ok;
}
int getOperatorId(string str){
	int id = -1;
	if(str.compare("+")){
		id = 11;
	}
	else if(str.compare("-")){
		id = 12;
	}
	else if(str.compare("*")){
		id = 13;
	}
	else if(str.compare("/")){
		id = 14;
	}
	else if(str.compare(">")){
		id = 15;
	}
	else if(str.compare("<")){
		id = 16;
	}
	else if(str.compare(">=")){
		id = 17;
	}
	else if(str.compare("<=")){
		id = 18;
	}
	else if(str.compare("==")){
		id = 19;
	}
	else if(str.compare("!=")){
		id = 20;
	}
	else if(str.compare("=")){
		id = 21;
	}
	else if(str.compare("++")){
		id = 22;
	}
	else if(str.compare("--")){
		id = 23;
	}
	else if(str.compare(">>")){
		id = 24;
	}
	else if(str.compare("<<")){
		id = 25;
	}
	return id;
}
int getKeywordId(string str){
	int id = -1;
	if(str.compare("if")){
		id = 31;
	}
	else if(str.compare("else")){
		id = 32;
	}
	else if(str.compare("for")){
		id = 33;
	}
	else if(str.compare("while")){
		id = 34;
	}
	else if(str.compare("cin")){
		id = 35;
	}
	else if(str.compare("cout")){
		id = 36;
	}
	else if(str.compare("return")){
		id = 37;
	}
	else if(str.compare("define")){
		id = 38;
	}
	else if(str.compare("int")){
		id = 41;
	}
	else if(str.compare("double")){
		id = 42;
	}
	else if(str.compare("char")){
		id = 43;
	}
	else if(str.compare("string")){
		id = 44;
	}
	else if(str.compare("bool")){
		id = 45;
	}
	return id;
}
bool Thrase(){
	bool ok =false;
	
	return ok;
}
int main(){
	fstream iofile;
	fstream formula;
	ofstream resultFile;
	string data1[100],data2[100];
	char Vn1[1000],Vt1[1000],Vn2[1000],Vt2[1000],Gammer[1000],Start1=' ',Rule1=' ',Start2=' ',Rule2=' ';//3°文法 G=(Vn,Vt,S,P) 两个文法 
	int n=0,m=0,i,j,flag1=0,flag2=0,flag3=0,count=0,couple1=0,couple2=0,Separator=0,vn=0,vt=0;
	int NO1[2]={0},NO2[2]={0};//记录Vn、Vt个数 
	int wrongNO[20]={0};
	int rules1=0,rules2=0;
	I_Node formula1[1000],formula2[1000];
	subSets CT1,CT2;
	_DFAs DFA1,DFA2;
	char result[200][256];
	int resultNumber=0;
	string keywords[13]={"if","else","while","int","bool","char","string","double","for","cout","cin","return","define"};
	char boundaries[9]={'#','\'','\"',';',',','{','}','(',')'};
	string operators[15]={"+","-","*","/","=",">","<",">=","<=","==","!=","++","--","<<",">>"};
	iofile.open("file1.txt",ios::in|ios::out);
	if(!iofile){
		cout<<"Fail to open the file file1.txt !"<<endl;
		exit(1);
	} 
	else{
		while(!iofile.eof()&&getline(iofile,data1[n])){
			n++;
		}
	}
	iofile.close();
	formula.open("formula.txt",ios::in);
	if(!formula){
		cout<<"Fail to open the file formula.txt !"<<endl;
		exit(1);
	}
	else{
		while(!formula.eof()&&getline(formula,data2[m])){
			m++;
		}
		//处理数据---------------------------------------------- 
		rules1=rules2=0;
		for(i=0;i<m;i++){
			if(!isValidLine(data2[i])){
				continue;
			}
			if(!isLikeRule(data2[i],i)){
				int length=data2[i].length();
				if(length>=1000){
					flag2=1;//Grammatical Mistakes 1:超出长度 
				}
				else{//处理文法 
					Separator=0;
					couple1=couple2=0;
					vn=0;vt=0;
					int k=0;
					for(j=0;j<length;j++){
						Gammer[j]=data2[i][j];
						//检查第一句是否存在特殊符号
						switch(getDefinedID(data2[i][j])){
							case 0:
								//非特殊符号 
								if(vn==1&&vt==0){//Vn 
									if(Start1==' '){
										Vn1[NO1[0]]=data2[i][j];
								 		NO1[0]++;
									} 
								 	else{
								 		Vn2[NO1[1]]=data2[i][j];
								 		NO1[1]++;
									}
								}
								else if(vn==2&&vt==1){//Vt
									if(Start1==' '){
									 	Vt1[NO2[0]]=data2[i][j];
									 	NO2[0]++;
								 	}
									else{
								 		Vt2[NO2[1]]=data2[i][j];
									 	NO2[1]++;
									}
							  	}
							  	else if(vn==2&&vt==2){
							  		if(Start1==' '){
							  			Start1=data2[i][j];
									}
									else if(Rule1==' '){
										Rule1=data2[i][j];
									}
									else if(Start2==' '){
										Start2=data2[i][j];
									}
									else{
										Rule2=data2[i][j];
									}
								  }
								break;
							case 1:
								Separator++;
								break;
							case 2:
								if(vn==0){
									vn=1;
								}
								else if(vn==2&&vt==0){
									vt=1;
								}
								else{
									flag2=2;
								}
								couple1++;
								break;
							case 3:
								if(vn==1){
									vn=2;
								}
								else if(vn==2&&vt==1){
									vt=2;
								}
								else{
									flag2=2;
									wrongNO[3]=i+1;
								}
								couple1--;
								break;
							case 7://处理逗号
								if(isComma(j,data2[i],length)==1){//逗号有问题 
									flag2=2;
									wrongNO[7]=i+1;
								}
								break;
							case 4:
								break;
							case 5:
								couple2++;
								break;
							case 6:
								couple2--;
								break; 
						}	
					}
					if(getDefinedID(data2[i][0])!=0){//处理未定义文法名 
							flag2=2;
							wrongNO[0]=i+1;
						}
					if(Separator!=1){//处理没有等于号 
						flag2=2;
						wrongNO[1]=i+1;
					}
					if(couple1>0){//检查结构残缺 
						flag2=2;
						wrongNO[2]=i+1;
					} 
					else if(couple1<0){
						flag2=2;
						wrongNO[3]=i+1;
					}
					if(couple2>0){//检查结构残缺 
						flag2=2;
						wrongNO[5]=i+1;
					} 
					else if(couple2<0){
						flag2=2;
						wrongNO[6]=i+1;
					}
					if(Start2==' '){
						for(k=0;k<NO1[0];k++){//检查Vn是否重复 
							if(isRepeated(Vn1,k,NO1[0])==1){
								flag2=2;
								wrongNO[8]=i+1;
							}
						}
						for(k=0;k<NO2[0];k++){//检查Vt是否重复 
							if(isRepeated(Vt1,k,NO2[0])==1){
								flag2=2;
								wrongNO[9]=i+1;
							}
						}
					}
					else{
						for(k=0;k<NO1[1];k++){//检查Vn是否重复 
							if(isRepeated(Vn2,k,NO1[1])){
								flag2=2;
								wrongNO[8]=i+1;
							}
						}
						for(k=0;k<NO2[1];k++){//检查Vt是否重复 
							if(isRepeated(Vt2,k,NO2[1])){
								flag2=2;
								wrongNO[9]=i+1;
							}
						}
					}
				}
				continue;
			}
			//处理规则 
			if(Start2==' '){
				I_Node node_t=createNode(data2[i],rules1,Start1,Vt1,Vn1);
				if(node_t.index!=-1){
					formula1[rules1]=node_t;
					rules1++;
				}
			}
			else{
				I_Node node_t=createNode(data2[i],rules2,Start2,Vt2,Vn2);
				if(node_t.index!=-1){
					formula2[rules2]=node_t;
					rules2++;
				}
			}			
		}
		
		//输出错误原因 
		reportError(2,flag2,wrongNO);
		
		
		//先判断是否是DFA isDFA(formula)
		if(!isDFA(formula1,rules1)){//NFA->DFA
			CT1 = change2CT(formula1,NO1[0],NO2[0],rules1,Vn1,Vt1);
			DFA1 = changeSubset2DFA(CT1);
		}
		else{//DFA
			DFA1 = createDFA(formula1,rules1,Vt1,Vn1,NO2[0],NO1[0]);
		}
		cout<<"--------------------"<<endl;
		if(!isDFA(formula2,rules2)){//NFA->DFA
			CT2 = change2CT(formula2,NO1[1],NO2[1],rules2,Vn2,Vt2);
			DFA2 = changeSubset2DFA(CT2);
		}
		else{//DFA
			DFA2 = createDFA(formula2,rules2,Vt2,Vn2,NO2[1],NO1[1]);
		}
	}
	formula.close();
	//预处理完毕，开始解析
	resultFile.open("TokenResult.txt");
	//界符('#':0; '\'':1; '\"':2; ';':3; ',':4; '{':5; '}':6; '(':7; ')':8;)
	//算术运算符(11-14)、关系运算符(15-20)、赋值运算符(21)、自增自减运算符(22、23) 输入输出运算符(24、25)、
	//标识符(26) 
	//常量(27) 
	//关键词(if:31; else:32; for:33; while:34; cin:35; cout:36; return:37; define:38; int:41; double:42; char:43; string:44; bool:45;) 
	for(int i=0;i<n;i++){
		string tobeAdded="";
		bool isOK = true;
		bool isFit = false;
		int whichDFA = 0;
		int nextVn = -1;
		char middle ='\0'; 
		for(int j=0;j<data1[i].length();j++){//每一行 
			if(data1[i][j]==' '){
				if(tobeAdded!=""&&whichDFA==1){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"标识符"<<endl; 
					resultFile<<tobeAdded<<" :"<<26<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				}
				else if(tobeAdded!=""&&whichDFA==2){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"常量"<<endl; 
					resultFile<<tobeAdded<<" :"<<27<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				}
				continue;
			}
			isFit = false;
			if(isBoundaries(data1[i][j])){//界符、限定符 
				if(tobeAdded!=""&&whichDFA==1){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"标识符"<<endl; 
					resultFile<<tobeAdded<<" :"<<26<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				} 
				else if(tobeAdded!=""&&whichDFA==2){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"常量"<<endl; 
					resultFile<<tobeAdded<<" :"<<27<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				}
				cout<<setw(2)<<i+1<<"行："<<setw(15)<<data1[i][j]<<" :"<<setw(10)<<"界符"<<endl;
				resultFile<<data1[i][j]<<" :"<<getBoundId(data1[i][j])<<endl;
				isOK = true;
				isFit = true;
			}
			if(isLikeOperators(data1[i][j])){//运算符 
				if(tobeAdded!=""&&whichDFA==1){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"标识符"<<endl; 
					resultFile<<tobeAdded<<" :"<<26<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				} 
				else if(tobeAdded!=""&&whichDFA==2){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"常量"<<endl; 
					resultFile<<tobeAdded<<" :"<<27<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				}
				string tobeAdded="";
				tobeAdded+=data1[i][j];
				if(j+1<data1[i].length()){
					if(data1[i][j+1]=='='&&(data1[i][j]=='<'||data1[i][j]=='>'||data1[i][j]=='!'||data1[i][j]=='=')){
						tobeAdded += '=';
						j++;
					}
					else if(data1[i][j+1]=='<'&&data1[i][j]=='<'){
						tobeAdded += '<';
						j++;
					}
					else if(data1[i][j+1]=='>'&&data1[i][j]=='>'){
						tobeAdded += '>';
						j++;
					}
					else if(data1[i][j+1]=='+'&&data1[i][j]=='+'){
						tobeAdded += '+';
						j++;
					}
					else if(data1[i][j+1]=='-'&&data1[i][j]=='-'){
						tobeAdded += '-';
						j++;
					}
				}
				cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"运算符"<<endl; 
				resultFile<<tobeAdded<<" :"<<getOperatorId(tobeAdded)<<endl;
				isOK = true;
				isFit = true;
			}
			else{//关键词匹配 
				if(isOK){
					if(j+2<data1[i].length()&&isBoundaries(data1[i][j+2])||isLikeOperators(data1[i][j+2])||isEmpty(data1[i][j+2])){
						if(data1[i][j]=='i'&&data1[i][j+1]=='f'){
							tobeAdded = "if";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+1;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='d'&&data1[i][j+1]=='o'){
							tobeAdded = "do";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+1;
							isOK = true;
							isFit = true;
						}
					}
					else if(j+3<data1[i].length()&&isBoundaries(data1[i][j+3])||isLikeOperators(data1[i][j+3])||isEmpty(data1[i][j+3])){
						if(data1[i][j]=='f'&&data1[i][j+1]=='o'&&data1[i][j+2]=='r'){
							tobeAdded = "for";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+2;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='i'&&data1[i][j+1]=='n'&&data1[i][j+2]=='t'){
							tobeAdded = "int";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+2;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='c'&&data1[i][j+1]=='i'&&data1[i][j+2]=='n'){
							tobeAdded = "cin";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+2;
							isOK = true;
							isFit = true;
						}
					} 
					else if(j+4<data1[i].length()&&isBoundaries(data1[i][j+4])||isLikeOperators(data1[i][j+4])||isEmpty(data1[i][j+4])){
						if(data1[i][j]=='e'&&data1[i][j+1]=='l'&&data1[i][j+2]=='s'&&data1[i][j+3]=='e'){
							tobeAdded = "else";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+3;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='b'&&data1[i][j+1]=='o'&&data1[i][j+2]=='o'&&data1[i][j+3]=='l'){
							tobeAdded = "bool";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+3;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='c'&&data1[i][j+1]=='h'&&data1[i][j+2]=='a'&&data1[i][j+3]=='r'){
							tobeAdded = "char";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+3;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='c'&&data1[i][j+1]=='o'&&data1[i][j+2]=='u'&&data1[i][j+3]=='t'){
							tobeAdded = "cout";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+3;
							isOK = true;
							isFit = true;
						}
					} 
					else if(j+5<data1[i].length()&&isBoundaries(data1[i][j+5])||isLikeOperators(data1[i][j+5])||isEmpty(data1[i][j+5])){
						if(data1[i][j]=='w'&&data1[i][j+1]=='h'&&data1[i][j+2]=='i'&&data1[i][j+3]=='l'&&data1[i][j+4]=='e'){
							tobeAdded = "while";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+4;
							isOK = true;
							isFit = true;
						}
					}
					else if(j+6<data1[i].length()&&isBoundaries(data1[i][j+6])||isLikeOperators(data1[i][j+6])||isEmpty(data1[i][j+6])){
						if(data1[i][j]=='s'&&data1[i][j+1]=='t'&&data1[i][j+2]=='r'&&data1[i][j+3]=='i'&&data1[i][j+4]=='n'&&data1[i][j+5]=='g'){
							tobeAdded = "string";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl;
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl; 
							j=j+5;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='r'&&data1[i][j+1]=='e'&&data1[i][j+2]=='t'&&data1[i][j+3]=='u'&&data1[i][j+4]=='r'&&data1[i][j+5]=='n'){
							tobeAdded = "return";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+5;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='d'&&data1[i][j+1]=='e'&&data1[i][j+2]=='f'&&data1[i][j+3]=='i'&&data1[i][j+4]=='n'&&data1[i][j+5]=='e'){
							tobeAdded = "define";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl; 
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl;
							j=j+5;
							isOK = true;
							isFit = true;
						}
						else if(data1[i][j]=='d'&&data1[i][j+1]=='o'&&data1[i][j+2]=='u'&&data1[i][j+3]=='b'&&data1[i][j+4]=='l'&&data1[i][j+5]=='e'){
							tobeAdded = "double";
							cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"关键词"<<endl;
							resultFile<<tobeAdded<<" :"<<getKeywordId(tobeAdded)<<endl; 
							j=j+5;
							isOK = true;
							isFit = true;
						}
					}
					//非关键词 
					if(!isFit){
						tobeAdded="";
						//DFA1 OF DFA2?
						for(int k=0;k<DFA1.getCount();k++){//是符合DFA1？ 
							if(Vn1[DFA1.getDFA(k).getLeft()]==Start1){//看符合哪条开始路径 
								middle = DFA1.getDFA(k).getVt();
								if(middle=='a'){//大写英文字母 
									if(isA(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 1;
										nextVn = DFA1.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle=='b'){//小写英文字母 
									if(isB(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 1;
										nextVn = DFA1.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle=='d'){//阿拉伯数字 
									if(isD(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 1;
										nextVn = DFA1.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle==data1[i][j]){//其他符号 
									tobeAdded+=data1[i][j];
									whichDFA = 1;
									nextVn = DFA1.getDFA(k).getRight();
									isOK = false;
									break;
								}				 	
							} 
						} 
						if(whichDFA==0){//是符合DFA2？
							for(int k=0;k<DFA2.getCount();k++){//是符合DFA1？ 
								if(Vn1[DFA2.getDFA(k).getLeft()]==Start2){//看符合哪条开始路径 
									middle = DFA2.getDFA(k).getVt();
									if(middle=='a'){//大写英文字母 
										if(isA(data1[i][j])){
											tobeAdded+=data1[i][j];
											whichDFA = 2;
											nextVn = DFA1.getDFA(k).getRight();
											isOK = false;
											break;
										}
									}
									else if(middle=='b'){//小写英文字母 
										if(isB(data1[i][j])){
											tobeAdded+=data1[i][j];
											whichDFA = 2;
											nextVn = DFA1.getDFA(k).getRight();
											isOK = false;
											break;
										}
									}
									else if(middle=='d'){//阿拉伯数字 
										if(isD(data1[i][j])){
											tobeAdded+=data1[i][j];
											whichDFA = 2;
											nextVn = DFA1.getDFA(k).getRight();
											isOK = false;
											break;
										}
									}
									else if(middle==data1[i][j]){//其他符号 
										tobeAdded+=data1[i][j];
										whichDFA = 2;
										nextVn = DFA1.getDFA(k).getRight();
										isOK = false;
										break;
									}				 	
								}
							}
						}
						if(whichDFA==0){//两个都不符合，说明有问题 
							cout<<data1[i][j]<<"两个文法都不符合！"<<endl;
						}  
					}
				}
				else{//上一次没有匹配完 
					 if(whichDFA==1&&nextVn!=-1){//使用DFA1匹配 
					 	for(int k=0;k<DFA1.getCount();k++){
					 		if(DFA1.getDFA(k).getLeft()==nextVn){
					 			middle = DFA1.getDFA(k).getVt();
								if(middle=='a'){//大写英文字母 
									if(isA(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 1;
										nextVn = DFA1.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle=='b'){//小写英文字母 
									if(isB(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 1;
										nextVn = DFA1.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle=='d'){//阿拉伯数字 
									if(isD(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 1;
										nextVn = DFA1.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle==data1[i][j]){//其他符号 
									tobeAdded+=data1[i][j];
									whichDFA = 1;
									nextVn = DFA1.getDFA(k).getRight();
									isOK = false;
									break;
								}
							 }
						 }
					 }
					 else if(whichDFA==2&&nextVn!=-1){
					 	for(int k=0;k<DFA2.getCount();k++){
					 		if(DFA2.getDFA(k).getLeft()==nextVn){
					 			middle = DFA2.getDFA(k).getVt();
								if(middle=='a'){//大写英文字母 
									if(isA(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 2;
										nextVn = DFA2.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle=='b'){//小写英文字母 
									if(isB(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 2;
										nextVn = DFA2.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle=='d'){//阿拉伯数字 
									if(isD(data1[i][j])){
										tobeAdded+=data1[i][j];
										whichDFA = 2;
										nextVn = DFA2.getDFA(k).getRight();
										isOK = false;
										break;
									}
								}
								else if(middle==data1[i][j]){//其他符号 
									tobeAdded+=data1[i][j];
									whichDFA = 2;
									nextVn = DFA2.getDFA(k).getRight();
									isOK = false;
									break;
								}
							 }
						 }
					 }
					
				}
			}
			if(j+1>=data1[i].length()){
				if(tobeAdded!=""&&whichDFA==1){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"标识符"<<endl; 
					resultFile<<tobeAdded<<" :"<<26<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				} 
				else if(tobeAdded!=""&&whichDFA==2){
					cout<<setw(2)<<i+1<<"行："<<setw(15)<<tobeAdded<<" :"<<setw(10)<<"常量"<<endl; 
					resultFile<<tobeAdded<<" :"<<27<<endl;
					isOK = true;
					isFit = true;
					whichDFA = 0;
					nextVn = -1;
				}
			}
		}
		//cout<<data1[i]<<endl;
	}
	return 0;
}

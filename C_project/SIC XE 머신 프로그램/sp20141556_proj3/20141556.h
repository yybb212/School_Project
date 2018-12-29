#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/stat.h>
int endd;//마지막 index
typedef struct _NODE{
	char* word;
	struct _NODE* link;
}node;
node* head;
typedef struct _HNODE{
	char op[3];
	char ins[7];
	int num;
	struct _HNODE* link;
}hnode;
hnode* table[20];
typedef struct{
	int line;//라인 넘버 5의 배수다
	int loc;//location
	char one[7];//Copy, first, cloop 등등
	char two[6];//Mnemonic
	char three[8];//목적
	char comma;
	char four[8];
	char junk[100];
	char* ob;
}asmm;
asmm* sou;
typedef struct _SYMBOLT{
	char symbol[7];
	int loc;
	struct _SYMBOLT* link;
}symbolt;
symbolt* stable;
typedef struct _REF{
	char name[7];
	int ref_num;
	struct _REF* link;
}ref;

typedef struct{
	char progname[10];
	int address;
	int length;
	symbolt* head;
	ref* r_head;
}ESTAB;
ESTAB* es;
typedef struct _BPTB{
	//int num;//breakpoint 개수
	char breakpoint[7];
	struct _BPTB* link;
}bptb;
bptb* bphead;//breakpoint head
bptb* bptemp;//breakpoint를 돌리기 위한 임시 변수
int memoryend;//memory 끝 주소
int tempend;//breakpoint
int A;//A register
int X;//X register
int L;//L register;
int PC;//PC register;
int B;//Base register;
int S;//S register;
int T;//T register;
int flag;//SW register;
int now_m;//메모리 시작 주소이다. run 함수에서 사용된다.
int realend;//breakpoint가 없고 프로그램의 끝까지 실행될경우 1
int realstart;//처음으로 프로그램이 시작될경우 1
int beforePC;//breakpoint에 의해 출력될때 필요한 변수
int filenum;
int progAddr;//Program Address이다.
int erflag;//Error flag
//int end;//어셈블리 파일 마지막 줄
int savenum;//저장되는 마지막 address
void addh(char* word);//histroy에 node를 저장해주는함수
void printh();//history에 저장된 노드들을 출력해주는 함수
void deletem();//메모리 해제
int checkin(char* input);//16진수인지 확인해주는 함수
int checkin2(char* input);//입력받은 start, end가 문법상 오류가 없는지 확인해주는 함수
char* rmspace(char* input);//빈칸이나 탭을 지워주는 함수
char* changestart(char* input);//start 뒤 부분에 공백이 있을경우 삭제해주는 함수
char* rmfordump(char* input);//dump 내에서 새로 문법을 고쳐주는 함수
int powe(int one ,int two);//one의 two승을 계산해주는 함수
int to10(char* input);//16진수를 10진수로 바꿔줌
char* to16(int input);//10진수를 16진수로 바꿔줌
char m[1048576][3];//메모리크기이다.
void addtable(hnode* new);//새로운 테이블 노드를 테이블안에 넣어주는 함수
int findandprint(char* input);//명령어를 입력하면 해당하는 opcode를 출력해주는 함수
int find(char* input);//Hash table에서 input을 찾아준다.:
char* object(int i);//i번째 구조체의 Object Code를 리턴해준다.
int findnum(char* input);//input에 해당하는 형식을 리턴해주는 함수.
void printtable(void);//테이블 데이터들을 모두 출력해주는 함수.
char* findopcode(char* input);//input에 해당하는 opcode를 찾아내준다.
//int ni(char* input);//input의 n,i 값을 10진수로 변환해서 리턴
int findtargetloc(char* input);//input이 symbol이면 저장된 자료구조로부터 그 target의 location을 리턴해준다.
char* complement(int num);//num의 2의 보수를 4자리의 문자열로 반환시켜준다.
void addsymbol(int i);//i번째 심볼을 테이블에 저장
void printsymbol(void);//심볼 테이블을 출력해준다.
void addes(char* symbol, int address ,int i);//i번째 구조체에 해당되는 데이터를 테이블에 넣어준다.
void add_ref(char* resw,char* num,int i);//외부 참조 변수들 이름과 번호를 저장해준다. ESTAB에 저장해준다.
void add_num_memory(char* temp,int targetadd,int i,char plus_minus);
void add_sym_memory(char* temp,int targetadd,int i);//메모리에 수정된 부분들을 추가하는 함수들이다.
void addbp(char bp[7]);//breakpoint를 추가해주는 함수
void printbp(void);//breapoint들을 출력해준다.
void run(void);//run해주는 함수
void CLEAR(void);
void STL(void);
void LDA(void);
void J(void);
void JEQ(void);
int COMP(void);//A가 크면 1, 같으면 0 ,작으면 -1
void JSUB(void);
void LDCH(void);
void RSUB(void);
void JLT(void);
void STA(void);
void STCH(void);
void STX(void);
void LDB(void);
void LDT(void);
int COMPR(void);//왼쪽이 크면 1, 같으면 0, 오른쪽이 크면 -1
int TIXR(void);//x+1 이 크면 1, 같으면 0, 작으면 -1
void TD(void);
void WD(void);
void RD(void);
int findxbp(int*x,int* b,int* p,int* e);//x,b,p 값을 계산해 리턴해주는 함수
int data_reg(int num);//레지스터에 저장된 값을 리턴해준다.
void bpclear(void);//breakpoint를 전부 제거해준다.

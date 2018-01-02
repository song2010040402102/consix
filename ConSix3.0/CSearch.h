#ifndef CSEARCH_CONSIX
#define CSEARCH_CONSIX
	
#include "window.h"

#define BLACK 0 //���ӡ��ڷ�
#define WHITE 1 //���ӡ��׷�
#define EMPTY 2 //����

//0��135�Ƚ�
#define ANGLE0 0
#define ANGLE45 1
#define ANGLE90 2
#define ANGLE135 3

//0��135�Ƚ��ϵĵ���������ӹ���
#define Increase0(x,y){(x)++;}
#define Increase45(x,y){(x)++;(y)--;}
#define Increase90(x,y){(y)++;}
#define Increase135(x,y){(x)++;(y)++;}

//0��135�Ƚ��ϵĵ������ݼ�����
#define Decrease0(x,y){(x)--;}
#define Decrease45(x,y){(x)--;(y)++;}
#define Decrease90(x,y){(y)--;}
#define Decrease135(x,y){(x)--;(y)--;}

#define NEXT(s) (s^1) //�ֵ��Է�
#define WINLOSE 10000 //��Ӯֵ
#define THREAT (WINLOSE-1) //��вֵ
#define TABLESIZE  1048512 //���Ϳ��С
#define CMSIZE 1000 //������׸���

typedef __int64 LONGLONG;

//�ĸ����������ӹ��ɽṹ
struct IncreaseXY
{
	int ix;
	int iy;
};

//��Ľṹ
typedef struct Point
{
	BYTE side; //�����ɫ��BLACK WHITE EMPTY
	short X; //��ĺ�����
	short Y; //���������
	int Value;	//��ļ�ֵ
	int label; //���ǩ��������
} *PPoint;

//���Ľṹ
typedef struct Step
{ 
	LONGLONG HashID; //����HASHID,����Ψһ��ʾһ����
	Point First; //��һ����
	Point Second; //�ڶ�����
	int SValue;  //����ֵ֮��
	int LValue;  //�����ߵ�ֵ֮��
} *PStep;

//�ߵĽṹ
typedef struct Line //����ߴ���ĳһ��ĳ�������ϵ���
{	
	BYTE Side;  //��һ������
	int Value; //����ֵ
	int ThreatNum; //�ߵ���в����
	vector<Point> ThreatPoint;  //��һ�ӻ����Ӿ���Ӯ�ĵ�	
	vector<Point> BigPotenPoint;  //��һ�����γ�˫��в�ĵ�
	vector<Point> SmaPotenPoint;  //��һ�����γɵ���в�ĵ�
	vector<Step> BigPotenStep; //���������γ�˫��в�Ĳ�
	vector<Step> SmaPotenStep; //���������γɵ���в�Ĳ�
	vector<Point> ComPoint;  //�������γɲ�����в�ĵ�
} *PLine;

//��ϣ��ʽ�������8���Գƹ�ϵ�ľ��涼�洢��
struct HashJoseki
{	
	LONGLONG checksum[8]; //�洢�ľ���
	Step step[8];  //�洢�����Ӧ���з�
};

//��ϣ��ʷ
struct HashHistory
{
	bool pruning; //����߷��б��ڼ�������ֵʱ����֦�򲻱�����
	LONGLONG checksum; //�Ѵ�Ĺ�ϣ����
	vector<Step> MoveList;	//�Ѵ�õĵ�ǰ�����µ��߷�
};

//��������ṹ
class CSearch
{	
public:	 
	int PointID; //��¼��������Ⱥ�˳��
    int StepID;  //��¼�������Ⱥ�˳��		

	bool GameStart;  //��ѡ���˭����֮����Ϸ�Ϳ�ʼ��	
	bool SearchRecord; //�Ƿ�����������¼
	bool WillWin; //��¼�Ƿ�ҪӮ
	bool ComToCom;//���Ը�������

	BYTE ComputerColor; //������ɫ
	BYTE Board[19][19]; //����
	BYTE PreTable[TABLESIZE]; //���ͱ�
	BYTE Player; //ѡ��
	BYTE MaxDepth[2];  //ˮƽ�����
	BYTE LargeDepth[2];  //��չ���
	BYTE MaxDepthBackUp; //����ˮƽ�����
	BYTE LargeDepthBackUp; //������չ���

	Step HashStep; //��ϣ��

	Line LineInfo[2][92];//�����ߵ���Ϣ,(19+2*14-1)*2=92	
	vector<Point>  PointHistory; //����ʷ
    vector<Step>  StepHistory;	//����ʷ

	LONGLONG HashKey64; //��ǰ����
	LONGLONG HashBoard[2][19][19]; //��ʼ����˫��ÿ�����hashֵ
	HashJoseki HashCM[2][CMSIZE]; //hash����

	CSearch();
	~CSearch();		

	void BackMove(Step step, BYTE Side,Line **LineTemp); //�ص�����֮ǰ�ľ���
	void MakeMove(Step step,BYTE Side,Line **LineTemp);	 //�������ߺ�ľ���

	void InitGame(); //��ʼ����Ϸ
	void InitBoard(); //��ʼ������
	void InitHashKey(); //��ʼ��˫��������hashkey
	void InitLineInfo(); //��ʼ��������Ϣ

	void DeleteHistory(); //�ͷ���ʷ�ṹ

	//�����which����Ĭ��ֵΪ0��������е����ͽ��в���
	void BackupLine(Point point,Line **LineTemp,BYTE Side,BYTE which=0); //������
	void UpdateLineForCross(Point point,BYTE Side,BYTE which=0); //�����ߣ��������ߵķ���
	void RecoverLine(Point point,Line **LineTemp,BYTE Side,BYTE which=0); //�ָ���
	void GetLineValueForCross(Point point,Line **line,BYTE Side,BYTE which=0); //��ȡ����ֵ
	void UpdateLine(Line **line,Point point,BYTE Side,BYTE which=0); //���·���֮�����

	Line AnalyzeLine(Point Start,BYTE Angle,BYTE Side,BYTE which=0); //һ�����ߵķ���
	Line GetAllLineInfor(BYTE Side,BYTE which=0); //������Ϣ�Ļ�ȡ
	Line ValuateShape(Point CurP,int ShapeIndex,int Angle,BYTE Side,BYTE which=0); //����Ƭ�εķ���

	void GetStoneFromPreTable(int type); //��ȡ15������

	//���ºͻָ�����
	void UpdateBoard(Step step,BYTE Side);
	void RecoverBoard(Step step,BYTE Side,Line **LineTemp);

	void HashImage(int i,int &x,int &y); //��ȡ�ԳƵĵ������

	void ReadCM(BYTE side);	//��ȡ����

	void OutputAllLineInfo(); //������е��ߵ���Ϣ

	void ReleaseHashTable(); //�ͷ�hash��

	void EnsureThreatNum(Line &Si,vector<int> threat); //��һ��ȷ����в����

	void AdjustStepValue(vector<Step> &MoveList,BYTE Side); //�Բ����н�һ��������Ŀǰ���岻��

	void Discount(Line Si1,Line Si2,int &Beta); //������ȡ�����̵�����ֵ���п۷�

	int SearchRange(); //����������Χ

	int WinOrLose(BYTE Side); //�ж�ʤ��

	//����ͼ�С�����������path����Ϊ�˵���ʹ��
	int MaxSearch(int Alpha,int Beta,int Depth,char *path);
	int MinSearch(int Alpha,int Beta,int Depth,char *path);	

	bool SearchCM(BYTE side); //�������ף����Ƿ��뵱ǰ����ƥ��

	bool LookUpHashTable(int Depth); //��ѯhash�������ҵ�����ֱ�Ӹ����з�

	//�Ƿ���Ҫ��һ��˫��в����������в���������ǳ���ľ������ڣ�����Ч���������Ԥ��Ч��������Ϊ��Ҫ����������������Ϸǳ�ǡ����ԭ��
	bool NeedConSearchForDoubleThreat(Line Si1,Line Si2);
	bool NeedConSearchForSingleThreat(Line Si1,Line Si2);	
	
	//LONGLONG Rand64(void);		
	LONGLONG Rand64(int k,int i,int j); //64λ�������������������MAX_RAND

	Step ComputerMove(); //��������ڣ����ص��ǵ��Ը������з�

	Step ConstructWinStep(vector<Point> point,BYTE Side); //���ڵ�����Ӯ���з�����������
	Step ConStrangeStep();	//���ڶԷ��ߵıȽϹֵ��з���Ϊ�˷�ֹ���Լ��㳬ʱ���������Ƽ��з�

	//���־����Ӧ�ԣ�˫��в������в������в
	vector<Step> DefendForMultiThreat(Line Si);
	vector<Step> DefendForSingleThreat(Line Si1,Line Si2,bool ConSearch1,bool ConSearch2);
	vector<Step> ConstructStepForNoThreat(Line Si1,Line Si2,bool ConSearch1);
	
	vector<Point> ConstructComPoint(Point point,Line Si1,Line Si2); //��ͨ��Ĺ��죬��ͨ�������ӵ�֮�������ܴﵽ����5��

	//�����������������Ѿ���������ΪGetAllLineInfor��������������ϻ����Ͽ��Դ���
	int CalculateStepValue(Step step,BYTE Side); //���㲽��ֵ
	int CalSingleLineValue(Point point ,BYTE Angle,BYTE Side);	//���㵥���ߵ�ֵ
	int AnalyzeLineSegID(Point point,int Dir,BYTE Side); //��������ĳ���ߵ�ID
};
#endif

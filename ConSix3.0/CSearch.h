#ifndef CSEARCH_CONSIX
#define CSEARCH_CONSIX
	
#include "window.h"

#define BLACK 0 //黑子、黑方
#define WHITE 1 //白子、白方
#define EMPTY 2 //空子

//0到135度角
#define ANGLE0 0
#define ANGLE45 1
#define ANGLE90 2
#define ANGLE135 3

//0到135度角上的点的坐标增加规律
#define Increase0(x,y){(x)++;}
#define Increase45(x,y){(x)++;(y)--;}
#define Increase90(x,y){(y)++;}
#define Increase135(x,y){(x)++;(y)++;}

//0到135度角上的点的坐标递减规律
#define Decrease0(x,y){(x)--;}
#define Decrease45(x,y){(x)--;(y)++;}
#define Decrease90(x,y){(y)--;}
#define Decrease135(x,y){(x)--;(y)--;}

#define NEXT(s) (s^1) //轮到对方
#define WINLOSE 10000 //输赢值
#define THREAT (WINLOSE-1) //威胁值
#define TABLESIZE  1048512 //线型库大小
#define CMSIZE 1000 //最大棋谱个数

typedef __int64 LONGLONG;

//四个方向点的增加规律结构
struct IncreaseXY
{
	int ix;
	int iy;
};

//点的结构
typedef struct Point
{
	BYTE side; //点的颜色，BLACK WHITE EMPTY
	short X; //点的横坐标
	short Y; //点的纵坐标
	int Value;	//点的价值
	int label; //点标签，被弃用
} *PPoint;

//步的结构
typedef struct Step
{ 
	LONGLONG HashID; //步的HASHID,用来唯一标示一个步
	Point First; //第一个点
	Point Second; //第二个点
	int SValue;  //两点值之和
	int LValue;  //所有线的值之和
} *PStep;

//线的结构
typedef struct Line //这个线代表某一方某条方向上的线
{	
	BYTE Side;  //哪一方的线
	int Value; //线性值
	int ThreatNum; //线的威胁数量
	vector<Point> ThreatPoint;  //走一子或两子就能赢的点	
	vector<Point> BigPotenPoint;  //走一子能形成双威胁的点
	vector<Point> SmaPotenPoint;  //走一子能形成单威胁的点
	vector<Step> BigPotenStep; //走两子能形成双威胁的步
	vector<Step> SmaPotenStep; //走两子能形成单威胁的步
	vector<Point> ComPoint;  //走两子形成不了威胁的点
} *PLine;

//哈希定式，这里把8个对称关系的局面都存储了
struct HashJoseki
{	
	LONGLONG checksum[8]; //存储的局面
	Step step[8];  //存储局面对应的招法
};

//哈希历史
struct HashHistory
{
	bool pruning; //如果走法列表在计算线型值时被剪枝则不被采纳
	LONGLONG checksum; //已存的哈希局面
	vector<Step> MoveList;	//已存好的当前局面下的走法
};

//搜索引擎结构
class CSearch
{	
public:	 
	int PointID; //记录各个点的先后顺序
    int StepID;  //记录各步的先后顺序		

	bool GameStart;  //当选择好谁先走之后，游戏就开始了	
	bool SearchRecord; //是否生成搜索记录
	bool WillWin; //记录是否将要赢
	bool ComToCom;//电脑跟电脑下

	BYTE ComputerColor; //电脑颜色
	BYTE Board[19][19]; //棋盘
	BYTE PreTable[TABLESIZE]; //线型表
	BYTE Player; //选手
	BYTE MaxDepth[2];  //水平线深度
	BYTE LargeDepth[2];  //拓展深度
	BYTE MaxDepthBackUp; //备份水平线深度
	BYTE LargeDepthBackUp; //备份拓展深度

	Step HashStep; //哈希步

	Line LineInfo[2][92];//所有线的信息,(19+2*14-1)*2=92	
	vector<Point>  PointHistory; //点历史
    vector<Step>  StepHistory;	//步历史

	LONGLONG HashKey64; //当前局面
	LONGLONG HashBoard[2][19][19]; //初始化的双方每个点的hash值
	HashJoseki HashCM[2][CMSIZE]; //hash棋谱

	CSearch();
	~CSearch();		

	void BackMove(Step step, BYTE Side,Line **LineTemp); //回到试走之前的局面
	void MakeMove(Step step,BYTE Side,Line **LineTemp);	 //更新试走后的局面

	void InitGame(); //初始化游戏
	void InitBoard(); //初始化棋盘
	void InitHashKey(); //初始化双方各个点hashkey
	void InitLineInfo(); //初始化线型信息

	void DeleteHistory(); //释放历史结构

	//这里的which参数默认值为0代表对所有的线型进行操作
	void BackupLine(Point point,Line **LineTemp,BYTE Side,BYTE which=0); //备份线
	void UpdateLineForCross(Point point,BYTE Side,BYTE which=0); //更新线，包括对线的分析
	void RecoverLine(Point point,Line **LineTemp,BYTE Side,BYTE which=0); //恢复线
	void GetLineValueForCross(Point point,Line **line,BYTE Side,BYTE which=0); //获取线型值
	void UpdateLine(Line **line,Point point,BYTE Side,BYTE which=0); //更新分析之后的线

	Line AnalyzeLine(Point Start,BYTE Angle,BYTE Side,BYTE which=0); //一整条线的分析
	Line GetAllLineInfor(BYTE Side,BYTE which=0); //线型信息的获取
	Line ValuateShape(Point CurP,int ShapeIndex,int Angle,BYTE Side,BYTE which=0); //线型片段的分析

	void GetStoneFromPreTable(int type); //获取15种线型

	//更新和恢复棋盘
	void UpdateBoard(Step step,BYTE Side);
	void RecoverBoard(Step step,BYTE Side,Line **LineTemp);

	void HashImage(int i,int &x,int &y); //获取对称的点的坐标

	void ReadCM(BYTE side);	//读取棋谱

	void OutputAllLineInfo(); //输出所有的线的信息

	void ReleaseHashTable(); //释放hash表

	void EnsureThreatNum(Line &Si,vector<int> threat); //进一步确定威胁数量

	void AdjustStepValue(vector<Step> &MoveList,BYTE Side); //对步进行进一步调整，目前意义不大

	void Discount(Line Si1,Line Si2,int &Beta); //对最后获取的棋盘的评估值进行扣分

	int SearchRange(); //返回搜索范围

	int WinOrLose(BYTE Side); //判断胜负

	//极大和极小搜索，这里的path就是为了调试使用
	int MaxSearch(int Alpha,int Beta,int Depth,char *path);
	int MinSearch(int Alpha,int Beta,int Depth,char *path);	

	bool SearchCM(BYTE side); //搜索棋谱，看是否与当前棋盘匹配

	bool LookUpHashTable(int Depth); //查询hash表，若查找到，就直接给出招法

	//是否需要进一步双威胁、连续单威胁搜索，这是程序的精华所在，最后的效果超出设计预期效果，我认为主要是这两个函数的配合非常恰当的原因
	bool NeedConSearchForDoubleThreat(Line Si1,Line Si2);
	bool NeedConSearchForSingleThreat(Line Si1,Line Si2);	
	
	//LONGLONG Rand64(void);		
	LONGLONG Rand64(int k,int i,int j); //64位的随机数，而不是最大才MAX_RAND

	Step ComputerMove(); //搜索的入口，返回的是电脑给出的招法

	Step ConstructWinStep(vector<Point> point,BYTE Side); //对于电脑能赢的招法，单独构造
	Step ConStrangeStep();	//对于对方走的比较怪的招法，为了防止电脑计算超时，给出的推荐招法

	//三种局面的应对，双威胁、单威胁、无威胁
	vector<Step> DefendForMultiThreat(Line Si);
	vector<Step> DefendForSingleThreat(Line Si1,Line Si2,bool ConSearch1,bool ConSearch2);
	vector<Step> ConstructStepForNoThreat(Line Si1,Line Si2,bool ConSearch1);
	
	vector<Point> ConstructComPoint(Point point,Line Si1,Line Si2); //普通点的构造，普通点就是添加点之后线型能达到至少5号

	//这三个函数基本上已经废弃，因为GetAllLineInfor和其它函数的配合基本上可以代劳
	int CalculateStepValue(Step step,BYTE Side); //计算步的值
	int CalSingleLineValue(Point point ,BYTE Angle,BYTE Side);	//计算单条线的值
	int AnalyzeLineSegID(Point point,int Dir,BYTE Side); //单独分析某条线的ID
};
#endif

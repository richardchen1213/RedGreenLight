/*
�o�O�@�Ӭ���O�{��
 */
int green = 0; //�����O�G�������ܼ�
int red = 0; //������O�G�������ܼ�
int orange = 0;//������O�G�������ܼ�
int mode = 0;//�O�Ц��ɦ�󪺼Ҧ��A0���w�]�Ҧ��A1���j��Ҧ��A2�����߲v�Ҧ�
int time = 0;//���ɪ����
int GrTime = 0;//��O�]�w�x�ɶ�
int RdTime = 0;//���O�]�w�x�ɶ�
void displayTime(int time);//��ܮɶ������
void settingMode();//�I�s�i�J�]�w��O���O�ɶ����Ҧ�

//digit seven-segment LED
int diseven[10][8]
{
	{1,1,1,1,1,1,0,0},//0
	{0,1,1,0,0,0,0,0},//1
	{1,1,0,1,1,0,1,0},//2
	{1,1,1,1,0,0,1,0},//3
	{0,1,1,0,0,1,1,0},//4
	{1,0,1,1,0,1,1,0},//5
	{1,0,1,1,1,1,1,0},//6
	{1,1,1,0,0,0,0,0},//7
	{1,1,1,1,1,1,1,0},//8
	{1,1,1,1,0,1,1,0},//9
}

//tendigit seven-segment LED
int tendiseven[10][8]
{
	{1, 1, 1, 1, 1, 1, 0, 0},//0
	{ 0,1,1,0,0,0,0,0 },//1
	{ 1,1,0,1,1,0,1,0 },//2
	{ 1,1,1,1,0,0,1,0 },//3
	{ 0,1,1,0,0,1,1,0 },//4
	{ 1,0,1,1,0,1,1,0 },//5
	{ 1,0,1,1,1,1,1,0 },//6
	{ 1,1,1,0,0,0,0,0 },//7
	{ 1,1,1,1,1,1,1,0 },//8
	{ 1,1,1,1,0,1,1,0 },//9
}

// the setup function runs once when you press reset or power the board
void setup() {


}

// the loop function runs over and over again forever
void loop() {

}

void displayTime(int time)
{

}

void settingMode()
{
}

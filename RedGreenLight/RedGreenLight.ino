/*
�o�O�@�Ӭ���O�{��
 */
int mode = 0;//�O�Ц��ɦ�󪺼Ҧ��A0���w�]�Ҧ��A1���j��Ҧ��A2�����߲v�Ҧ�
int GrTime = 0;//��O�]�w�x�ɶ�
int RdTime = 0;//���O�]�w�x�ɶ�
void displayTime(int time);//��ܮɶ������
void settingMode();//�I�s�i�J�]�w��O���O�ɶ����Ҧ�
void DefaultMode();//�i�J�w�]�Ҧ�
void ForceMode();//�i�J�j��Ҧ�

int Button1();//�^�ǭӦ�ƪ����s�O�_���U�A�O�h�^��1�A�_�h�^��0
int Button2();//�^�ǤQ��ƪ����s�O�_...
int ButtonS();//�^�ǳ]�w��...

int Button1=LOW;//�����W�@���ˬdbutton1���A���ܼ�
int Button2=LOW;//�����W�@��...
int Button3 = LOW;//����...
int pause = 0;//�Ȱ���������

void Green(int val);//��O�G�Aval �ǤJLOW�����AHIGH���}
void Red(int val);//���O�G...
void Orange(int val);//���O...

// the setup function runs once when you press reset or power the board
void setup() {


}

// the loop function runs over and over again forever
void loop() {

	}


}

void displayTime(int time)
{

}

void settingMode()
{

}

void DefaultMode()
{
	int light = 0;//0 is green, 1 is orange, 2 is red
	int time = GrTime*10;//��O�ɶ����ʲ@��
	if (pause == 0) {
		if (time == 0) {
			light = light + 1;
			if (light == 3)
				light = 0;
			
		}
	}

}

/*
�o�O�@�Ӭ���O�{���A�ݭp�ɾ��P�߲v�˴���XDD
 */
int mode = 0;//�O�Ц��ɦ�󪺼Ҧ��A0���w�]�Ҧ��A1���j��Ҧ���O�A2���j��Ҧ����O�A3�����߲v�Ҧ��A4��settingMode
int GrTime = 0;//��O�]�w�x�ɶ�
int RdTime = 0;//���O�]�w�x�ɶ�
void displayTime(int time);//��ܮɶ������
void settingMode();//�I�s�i�J�]�w��O���O�ɶ����Ҧ�
void DefaultMode();//�i�J�w�]�Ҧ�
void ForceMode(int light);//�i�J�j��Ҧ��A�ǤJ0�i�J��O�A�ǤJ1�i�J���O
void HeartRateMode();//�i�J���߲v�Ҧ�
boolean changeMode();//�ഫ�Ҧ����աA�n�ഫ�Ҧ��Ǧ^�O�A�����ഫ�Ҧ��Ǧ^�_�A���ӨC0.1��Q�I�s�@����w�]�αj��Ҧ�

int Button1();//�^�ǭӦ�ƪ����s�O�_���U�A�O�h�^��1�A�_�h�^��0
int Button2();//�^�ǤQ��ƪ����s�O�_...
int ButtonS();//�^�ǳ]�w��...

int Buttons1 = 0;//����button1���A���ܼơA�Ӧ��
int Buttons2 = 0;//�����Q���
int ButtonsS = 0;//�����]�w/�Ȱ���
void Buttonsreset();//���s���s���A�ܼ�
boolean pause = false;//�Ȱ���������

void Green(int val);//��O�G�Aval �ǤJLOW�����AHIGH���}
void Red(int val);//���O�G...
void Orange(int val);//���O...

// the setup function runs once when you press reset or power the board
void setup() {


}

// the loop function runs over and over again forever
void loop() {
	switch (mode) {
	case 0:
		DefaultMode();
		break;
	case 1:
		ForceMode(0);
		break;
	case 2:
		ForceMode(1);
		break;
	case 3:
		HeartRateMode();
		break;
	case 4:
		settingMode();
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
	int time = GrTime * 10;//��O�ɶ����ʲ@��
	do {
		if (!pause) {
			if (time == 0) {
				light = light + 1;
				if (light == 3)
					light = 0;
				switch (light) {
				case 0:
					Red(LOW);
					Green(HIGH);
					time = GrTime * 10;
				case 1:
					Green(LOW);
					Orange(HIGH);
					time = 50;
				case 2:
					Orange(LOW);
					Red(HIGH);
					time = RdTime * 10;
				}
			}
			displayTime(time / 10);
			time--;
		}
		delay(100);
	} while (!changeMode());
}

void ForceMode(int light)
{
	int time = 0;//�ʲ@���
	if (light == 0) {
		Green(HIGH);
		Red(LOW);
		Orange(LOW);
	}
	else if (light == 1) {
		Green(LOW);
		Red(HIGH);
		Orange(LOW);
	}
	do {
		if (!pause) {
			if (time > 600)
				displayTime(time / 600);
			else
				displayTime(time / 10);
			time++;
			delay(100);
		}
	} while (!changeMode());
}

void HeartRateMode()
{
	int count = 0;//�p�ƾ�
	for (int time = 0; time <= 600; time++) {
		if (ButtonS())
			ButtonsS++;
		else if (ButtonsS > 0) {
			count++;
			ButtonsS = 0;
		}
		delay(100);
	}
	displayTime(count);//��ܥ����C�������߸���
	mode = 0;
}

boolean changeMode()
{
	int status = Button1() + Button2() * 10 + ButtonS() * 100;
	switch (status) {
	case 0:
		if (Buttons1 > 0) {
			Buttonsreset();
			mode = 1;
			return true;
		}
		if (Buttons2 > 0) {
			Buttonsreset();
			mode = 2;
			return true;
		}
		if (ButtonsS > 0) {
			Buttonsreset();
			pause = !pause;
			return false;
		}
		return false;
	case 100:
		ButtonsS++;
		if (ButtonsS >= 4) {
			Buttonsreset();
			if (mode == 0) {
				mode = 4;
				return true;
			}
			if (mode == 1 || mode == 2) {
				mode = 0;
				return true;
			}
		}
		return false;
	case 1:
		Buttons1++;
		if (Buttons1 >= 4) {
			Buttonsreset();
			mode = 3;
			return true;
		}
		return false;
	case 10:
		Buttons2++;
	default:
		return false;
	}
	return false;
}

void Buttonsreset()
{
	Buttons1 = 0;
	Buttons2 = 0;
	ButtonsS = 0;
}

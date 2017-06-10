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

int datapinten = 2;
int clockpinten = 4;
int latchpinten = 3;
byte index = 0;                   // �C�q��ܾ����Ʀr����
const byte LEDs[10] = {
	B01111110,
	B00110000,
	B01101101,
	B01111001,
	B00110011,
	B01011011,
	B01011111,
	B01110000,
	B01111111,
	B01111011,
};

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(latchpinten, OUTPUT);
	pinMode(clockpinten, OUTPUT);
	pinMode(datapinten, OUTPUT);
	pinMode(8, OUTPUT);



}

// the loop function runs over and over again forever
void loop() {
	digitalWrite(8, HIGH);
	for (int i = 0;; i++) {
		displaynumber(i%10);
		delay(1000);
	}
}


void displaynumber(int time)
{
	// �e��ƫe�n���� latchPin �Ԧ��C�q��
		digitalWrite(latchpinten, LOW);
		// �e�X�Ʀr���줸��� (bit pattern)
		shiftOut(datapinten, clockpinten, LSBFIRST, LEDs[time]);
		// �e����ƫ�n�� latchPin �Ԧ^�����q��
		digitalWrite(latchpinten, HIGH);
}


void settingMode()
{
	int ButtomSstatus = 0; // �ŧi�]�w�䪬�A
	int Button1status = 0; // �ŧi�Ӧ��䪬�A
	int Button2status = 0; // �ŧi�Q���䪬�A
	int digit = 0; //�C�q��ܭӦ��
	int tendigit = 0; //�C�q��ܾ��Q���
	//ButtonSstatus = digitalRead();//�P�_ButtonS ���q�� ()�����I*********************
	delay(100);

	if (ButtomSstatus == HIGH) //��]�w�䬰���q��i�J�]�w�Ҧ�---��O>>>>���O
//		Button1status = digitalRead(); //()�����I***********************************

//	displayTime();

	if (Button1status == HIGH)
		digit++;
	GrTime == digit;
	if (Button2status == HIGH)
		tendigit++;
	GrTime += tendigit * 10;


	if (GrTime != 0 && Button1status == HIGH)
		digit++;
	RdTime == digit;
	if (GrTime != 0 && Button2status == HIGH)
		tendigit++;
	RdTime += tendigit * 10;
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

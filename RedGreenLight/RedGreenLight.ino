/*
�o�O�@�Ӭ���O�{���A�ݭp�ɾ��P�߲v�˴���XDD
*/
int mode = 0;//�O�Ц��ɦ�󪺼Ҧ��A0���w�]�Ҧ��A1���j��Ҧ���O�A2���j��Ҧ����O�A3�����߲v�Ҧ��A4��settingMode
int GrTime = 20;//��O�]�w�x�ɶ�
int RdTime = 30;//���O�]�w�x�ɶ�
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

					 //�}��]�w**************************************************

					 //74HC595�}��(2~7)

					 //74HC595�Ӧ�
int dataPin = 2;//�Ӧ��IC 14�}��(data)
int latchPin = 3;//�Ӧ��IC12�}��(latch�Ȧs���ɯ�)
int clockPin = 4;//�Ӧ��IC 11�}��(clock�ǦC�ɯ�)

				 //74HC595�Q��
int dataPin1 = 5;//�Q���IC 14�}��(data)
int latchPin1 = 6;//�Q���IC12�}��(latch�Ȧs���ɯ�)
int clockPin1 = 7;//�Q���IC 11�}��(clock�ǦC�ɯ�)

				  //LED
int led_green = 8;
int led_yellow = 9;
int led_red = 10;

//Button
int Button1p = 11;//�Ӧ�
int Button2p = 12;//�Q��
int ButtonSp = 13;//�]�w


				 // the setup function runs once when you press reset or power the board
void setup() {
	for (int i = 2; i <= 10; i++)
	{
		pinMode(i, OUTPUT);
	}
	for (int j = 11; j <= 13; j++)
	{
		pinMode(j, INPUT);
	}
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
	Green(LOW);
	Red(LOW);
	Orange(LOW);
	do {
		delay(100);
	} while (Button1() || Button2() || ButtonS());
	Buttonsreset();
}



//  dp,a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[11] = {
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
	B00000000
};

byte seven_seg_tendigits[11] = {
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
	B00000000
};



//�Ӧ�
void sevenSegWrite(byte digit) {
	// �e��ƫe�n���� latchPin �Ԧ��C�q��
	digitalWrite(latchPin, LOW);

	// �e�X�Ʀr���줸��� (bit pattern)
	shiftOut(dataPin, clockPin, LSBFIRST, seven_seg_digits[digit]);

	// �e����ƫ�n�� latchPin �Ԧ^�����q��
	digitalWrite(latchPin, HIGH);
}

//�Q��
void sevenSegWrite1(byte tendigit) {
	// �e��ƫe�n���� latchPin �Ԧ��C�q��
	digitalWrite(latchPin1, LOW);

	// �e�X�Ʀr���줸��� (bit pattern)
	shiftOut(dataPin1, clockPin1, LSBFIRST, seven_seg_tendigits[tendigit]);

	// �e����ƫ�n�� latchPin �Ԧ^�����q��
	digitalWrite(latchPin1, HIGH);
}

void displayTime(int time)//
{

	sevenSegWrite(time % 10);
	sevenSegWrite1(time / 10);
}


void settingMode()
{
	int ButtonSstatus = 0; // �ŧi�]�w�䪬�A
	int Button1status = 0; // �ŧi�Ӧ��䪬�A
	int Button2status = 0; // �ŧi�Q���䪬�A
	int digit = 0; //�C�q��ܭӦ��
	int tendigit = 0; //�C�q��ܾ��Q���
	ButtonSstatus = digitalRead(13);//�P�_ButtonS ���q�� 13�����I*********************
	delay(100);

	if (ButtonSstatus == HIGH) //��]�w�䬰���q��i�J�]�w�Ҧ�---��O>>>>���O
		Button1status = digitalRead(11); //11���Ӧ챵�I
	Button2status = digitalRead(12); //12���Q�챵�I
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

	return;
}

void DefaultMode()
{
	int light = 0;//0 is green, 1 is orange, 2 is red
	int time = GrTime * 10;//��O�ɶ����ʲ@��
	Orange(LOW);
	Red(LOW);
	Green(HIGH);
	do {
		if (!pause) {
			if (time == 0) {
				light = light + 1;
				if (light == 3)
				{
					light = 0;
				}
				switch (light) {
				case 0:
					Red(LOW);
					Green(HIGH);
					time = GrTime * 10;
					break;
				case 1:
					Green(LOW);
					Orange(HIGH);
					time = 50;
					break;
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
		}
		delay(100);
	} while (!changeMode());
}

void HeartRateMode()
{
	int count = 0;//�p�ƾ�
	for (int time = 50; time >= 0; time--) {
		displayTime(time / 10);
		delay(100);
	}
	for (int time = 600; time >= 0; time--) {
		if (ButtonS()) {
			ButtonsS++;
			Red(HIGH);
			if (ButtonsS >= 4) {
				mode = 0;
				return;
			}
		}
		else if (ButtonsS > 0) {
			count++;
			ButtonsS = 0;
			Red(LOW);
		}
		displayTime(time / 10);
		delay(100);
	}
	if (count >= 400) {
		mode = 0;
		return;
	}
	else if (count >= 300) {
		Green(HIGH);
		Orange(HIGH);
		Red(HIGH);
		count = count - 300;
	}
	else if (count >= 200) {
		Orange(HIGH);
		Red(HIGH);
		count = count - 200;
	}
	else if (count >= 100) {
		Red(HIGH);
		count = count - 100;
	}
	displayTime(count);//��ܥ����C�������߸���
	mode = 0;
	delay(2000);
	ButtonsS = 0;
	do {
		if (ButtonS())
			ButtonsS++;
		delay(100);
	} while (ButtonsS == 0 || ButtonS());
}

boolean changeMode()
{
	int status = Button1() + Button2() * 10 + ButtonS() * 100;
	switch (status) {
	case 0:
		if (Buttons1 > 0) {
			mode = 1;
			return true;
		}
		if (Buttons2 > 0) {
			mode = 2;
			return true;
		}
		if (ButtonsS > 0) {
			pause = !pause;
			return false;
		}
		return false;
	case 100:
		ButtonsS++;
		if (ButtonsS >= 4) {
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

int Button1()
{
	if (digitalRead(Button1p) == HIGH) {
		return 1;
	};
	return 0;
}

int Button2()
{
	if (digitalRead(Button2p) == HIGH) {
		return 1;
	};
	return 0;
}

int ButtonS()
{
	if (digitalRead(ButtonSp) == HIGH) {
		return 1;
	};
	return 0;
}

void Buttonsreset()
{
	Buttons1 = 0;
	Buttons2 = 0;
	ButtonsS = 0;
}

void Green(int val)
{
	digitalWrite(led_green, val);
}

void Red(int val)
{
	digitalWrite(led_red, val);
}

void Orange(int val)
{
	digitalWrite(led_yellow, val);
}

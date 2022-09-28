#define LED_PIN 2

#define PWM_PIN   5
#define PWM_Freq  50

//最大255
#define PWM_On_Duty     32  //开灯占空比
#define PWM_Off_Duty    7   //关灯占空比
#define PWM_Stand_Duty  19  //待机占空比

#define KEY_PIN     12
#define KEY1_PIN    13

uint8 Status  = 0, Status_Last = 0;
uint8 Key_Tim = 0;

uint8 PWM_Duty;

int val;

void setup() {
  // put your setup code here, to run once:
  Led_Init();
  Pwm_Init();
  Key_Init();
}

void loop() {
  // put your main code here, to run repeatedly:
  Key_Scanf();
  if(Status_Last != Status)
  {
    Status_Last = Status;

    if(Status)  PWM_Duty = PWM_On_Duty;
    else        PWM_Duty = PWM_Off_Duty;
  }
  
  analogWrite(PWM_PIN,PWM_Duty);
}

void Led_Init(void)
{
    pinMode(LED_PIN,OUTPUT);      //设置引脚模式
    digitalWrite(LED_PIN, HIGH);
}

void Pwm_Init(void)
{
  pinMode(PWM_PIN,OUTPUT);      //设置引脚模式
  analogWriteFreq(PWM_Freq);
  analogWrite(PWM_PIN,0);
}

void Key_Init(void)
{
  pinMode(KEY1_PIN, INPUT_PULLUP);
}

void Key_Scanf(void)
{
  val = digitalRead(KEY1_PIN);
  if(val == LOW)
  {
    if(Key_Tim < 255) Key_Tim++;
  }
  else
  {
    if(Key_Tim > 50)
    {
      Status ^= 1;
      digitalWrite(LED_PIN, Status);
    }
    Key_Tim = 0;
  }
}

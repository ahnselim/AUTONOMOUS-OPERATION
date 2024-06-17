// 핀을 정합니다.
// 오른쪽
int rightTrig = 6;    // 주황색선
int rightEcho = 7;    // 회색선
// 정면
int trigpin = 8;   // 파란색선
int echoPin = 9;   // 보라색선
// 왼쪽
int leftTrig = 10;   // 흰색선
int leftEcho = 11;   // 검정색선

const int motorA_in1 = 2;
const int motorA_in2 = 3;
const int motorB_in1 = 4;
const int motorB_in2 = 5;

// 초음파 거리 측정 변수
long right_duration, right_dis;
long straight_duration, straight_dis;
long left_duration, left_dis;

// 임계값 설정 (단위: cm)
const int safeDistance = 150;
const int wallDistance = 50;

void setup() {
  pinMode(motorA_in1, OUTPUT);
  pinMode(motorA_in2, OUTPUT);
  pinMode(motorB_in1, OUTPUT);
  pinMode(motorB_in2, OUTPUT);

  pinMode(rightTrig, OUTPUT); // trigPin을 출력으로 
  pinMode(rightEcho, INPUT);  // echoPin을 입력으로
  pinMode(trigpin, OUTPUT);   // trigPin을 출력으로 
  pinMode(echoPin, INPUT);    // echoPin을 입력으로
  pinMode(leftTrig, OUTPUT);  // trigPin을 출력으로 
  pinMode(leftEcho, INPUT);   // echoPin을 입력으로
  goStraight();
  delay(7000);
  Serial.begin(9600);
}

void loop() {
  // 오른쪽 거리 측정
  right_dis = getDistance(rightTrig, rightEcho);
  Serial.print("right Sensor: ");
  Serial.print(right_dis);
  Serial.println(" cm");

  // 정면 거리 측정
  straight_dis = getDistance(trigpin, echoPin);
  Serial.print("straight Sensor: ");
  Serial.print(straight_dis);
  Serial.println(" cm");

  // 왼쪽 거리 측정
  left_dis = getDistance(leftTrig, leftEcho);
  Serial.print("left Sensor: ");
  Serial.print(left_dis);
  Serial.println(" cm");
  goStraight();

  // 자율 운항 로직
  
  if (straight_dis <= safeDistance) { // 정면에 장애물이 있으면 회전
    back();
    delay(2000);
    while(1){
      stop();
    }
  }

  // if(right_dis<80){
  //   digitalWrite(motorA_in1, HIGH);
  //   digitalWrite(motorA_in2, LOW);
  //   digitalWrite(motorB_in1, LOW);
  //   digitalWrite(motorB_in2, LOW);
  //   delay(1000);
  // }
  // else if(left_dis<80){
  //   digitalWrite(motorA_in1, LOW);
  //   digitalWrite(motorA_in2, LOW);
  //   digitalWrite(motorB_in1, LOW);
  //   digitalWrite(motorB_in2, HIGH);
  //   delay(1000);
  // }
  
  // else {
  //   if (right_dis > wallDistance + 20) { // 우측 벽과의 거리가 너무 멀면 우회전하여 벽에 붙기
  //     turnRight();
  //     Serial.println("right turn to align with wall");
  //     delay(200);
  //     turnLeft();
  //     delay(100);
  //   } else if (right_dis < wallDistance - 20) { // 우측 벽과의 거리가 너무 가까우면 좌회전하여 벽에서 떨어지기
  //     turnLeft();
  //     Serial.println("left turn to align with wall");
  //     delay(200);
  //     turnRight();
  //     delay(100);
  //   } else { // 우측 벽과의 거리가 적당하면 직진
  //     goStraight();
  //     Serial.println("go straight along the wall");
  //     delay(500);
  //   }
  // }
 // 측정 간격을 위한 지연
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void goStraight() {
  digitalWrite(motorA_in1, HIGH);
  digitalWrite(motorA_in2, LOW);
  digitalWrite(motorB_in1, LOW);
  digitalWrite(motorB_in2, HIGH);
}
void back() {
  digitalWrite(motorA_in1, LOW);
  digitalWrite(motorA_in2, HIGH);
  digitalWrite(motorB_in1, HIGH);
  digitalWrite(motorB_in2, LOW);
}
void stop() {
  digitalWrite(motorA_in1, LOW);
  digitalWrite(motorA_in2, LOW);
  digitalWrite(motorB_in1, LOW);
  digitalWrite(motorB_in2, LOW);
}

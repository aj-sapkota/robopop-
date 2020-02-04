int weapon=35;
int w=0;;
#define robot_rpm  (400)
#define max_rpm  (255)
#define tolerance  (10)
int velocity_robot[3]={0,0,0};
  
int M_CH1[3] = {9
    ,12
    ,11
};
int M_CH2[3] = {8
    ,7
    ,5
};
int PWM[3] = {10
    ,4
    ,13
};
 
//char data = 'S';

void setup()
{
  Serial.begin(9600);
  Serial.println("hello");
  Serial3.begin(115200);
        for (int i = 0; i < 3; i++)
        {
                pinMode(M_CH1[i], OUTPUT);
                pinMode(M_CH2[i], OUTPUT);
                pinMode(PWM[i], OUTPUT);
        }
  pinMode(weapon,OUTPUT);
  digitalWrite(weapon,LOW);
}
void loop()
{
         getData();
        calculateWheelVelocity();
        
}

void getData()
{
//  Serial.println("getdata");
       if (Serial3.available() > 0)
        {
//                Serial.println("joy");
                char data = Serial3.read();
//                Serial.println(data);
                                
                        switch (data)
                        {
                        case 'B':
                        
//                                digitalWrite(weapon,HIGH);
                                velocity_robot[0] = robot_rpm;
//                                Serial.println("robot_rpm");
                                break;
                        case 'F':
                                velocity_robot[0] = -robot_rpm;
                                break;
                        case 'L':
                                velocity_robot[1] = -robot_rpm;
                                break;
                        case 'R':
                                velocity_robot[1] = robot_rpm;
                                break;
                        case 'G':
                                velocity_robot[2] = robot_rpm;
                                break;
                        case 'I':
                                velocity_robot[2] = -robot_rpm;
                                break;
                        case 'J':
                                velocity_robot[0] = -robot_rpm;
                                velocity_robot[1] = -robot_rpm;
                                break;
                        case 'H':
                                velocity_robot[0] = -robot_rpm;
                                velocity_robot[1] = robot_rpm;
                                break;          
                                
                        case 'S':
                                velocity_robot[0] = 0;
                                velocity_robot[1] = 0;
                                velocity_robot[2] = 0;
                                w=0;
                                break;
                                
                        case 'W':
                                digitalWrite(weapon,HIGH);
                                break;
                        case 'w':
                                digitalWrite(weapon,LOW);
                                break;
                              
                         default:
                                velocity_robot[0] = 0;
                                velocity_robot[1] = 0;
                                velocity_robot[2] = 0;
                                w=0;
                                break;

                        }
        }
                
}

void calculateWheelVelocity()
{
        int velocity_motor[3] = {0, 0, 0};
        float coupling_matrix[3][3] = {{0, 0.6667, 0.3333},
                                       {0.5774, -0.3333, 0.33333},
                                       {-0.5774, -0.3333, 0.3333}};

        for (int i = 0; i < 3; i++)
        {
                velocity_motor[i] = 0;
                for (int j = 0; j < 3; j++)
                {
                        velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
                }
        }

          for (int i = 0; i < 3; i++)
        {
                if (velocity_motor[i] > max_rpm)
                {
                        velocity_motor[i] = max_rpm;
                }

                else if (velocity_motor[i] < -max_rpm)
                {
                        velocity_motor[i] = -max_rpm;
                }
        }
        for (int i = 0; i < 3; i++)
        {
//                Serial.print(i);
//                Serial.print("\t");
//                Serial.println(velocity_motor[i]);
                if (velocity_motor[i] > tolerance)
                {
                        digitalWrite(M_CH1[i], HIGH);
                        digitalWrite(M_CH2[i], LOW);
                        analogWrite(PWM[i], velocity_motor[i]);
                }
                else if (velocity_motor[i] < -tolerance)
                {
                        digitalWrite(M_CH1[i], LOW);
                        digitalWrite(M_CH2[i], HIGH);
                        analogWrite(PWM[i], -velocity_motor[i]);
                }
                else
                {
                        digitalWrite(M_CH1[i], LOW);
                        digitalWrite(M_CH2[i], LOW);
                        analogWrite(PWM[i], 0);
                }
        }        
        }

    
       


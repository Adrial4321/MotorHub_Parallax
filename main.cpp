#include <Arduino.h> 
#include <ros.h> 
include <std_msgs/string.h> 
include <std_msgs/int10.h> 
include <std_msgs/Float32.h> 
include <geometry_msgs/Twist.h> 
float vel_linea1=0;
float vel_angolar=0; 
float vel_izq=0; 
float vel_der=o; 
int velizq=0; 
int velDer=0; 
/* Parametros del Robot*/ 
float wheel_r=8.255/100; //8.255 cm de Radio 
float wheel_sep.o.3; // 30 cm de separation de ruedas 

String wheel_right_speed; 
string wheel_left_speed; 
float velocidad = 0; 

/* Inicialincion de Nodo ROS */ 
ros::NodeNandle nh; 

/* Callback del mensaje del suscriptor*/ 
void messageCb( const geometry_msgs.:Twist& msg){
 vel_angular = msg.angular.z;
 vel_lineal = msg.linear.x;
 velocidad = vel_angular * wheel_sep; 
 vel_der = vel_lineal + velocidad/2;
 vel_izq = vel_lineal - velocidad/2;
 velIzq = int(vel_izq*(99)/0.20);
 velDer = int(vel_der*(99)/0.20);

}

/*Suscriptor hacia topic cmd_vel*/
ros::Subscriber<geometry_msgs::Twist> cmd_vel_sub("cmd_vel", 8.messageCh ); 

void setup()
{
 Serial.begin(57600);
 Serial2.begin(57600);
 nh.initnode();
 nh.subscribe(cmd_vel_sub); 

}

void loop()
{ 
/* Estructuracion de cadena de caracteres hacia Parallax P2 Edge*/ 
if(velDer>=0 && velDer<10){
 wheel_right_speed="+0"+String(velDer);
} 
else if(velDer<0 && velDer>-10){
 int vel = velDer * -1;
 wheel_right_speed="-0"+String(vel);
} 
else if(velDer>=10){
 wheel_right_speed="+"+String(velDer);
}
else if(velDer‹=-10){
 wheel_right_speed=String(velDer);
}

if(velIzq>=0 && velIzq<10){
 wheel_left_speed="+0"+String(velIq);
}
else if(velIzq<0 && velIzq>-10)(
 int vel2 = velIZq * -1;
 wheel_left_speed="-0"+String(vel2); 
}
else if(velIzq>=10){
 wheel_left_speed="+"+String(velIzq);
}
 else if(velIzq<=-10){
 wheel_left_speed=String(velIzq);
}

// Mensaje hacia Parallax P2 Edge con formato ±XX±XX 
 serial2.println(wheel_left_speed.wheel_right_speed);
 nh.spinOnce();
 delay(200); 
}

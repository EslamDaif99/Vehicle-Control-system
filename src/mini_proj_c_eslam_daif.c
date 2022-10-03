/*
 ============================================================================
 Name        : mini_proj_c_eslam_daif.c
 Author      : Eslam Ali Daif
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#define WITH_ENGINE_TEMP_CONTROLLER 1 //////// bouns
/*************** enum Defination ********************/
enum state{
	OFF ,ON
};
/************* Structure Defination *****************/
struct vehicle_state {
	enum state engine_state ;
	enum state AC_state ;
	int vehicle_speed ;
	int room_temp  ;
	enum state engine_temp_controller  ;
	int engine_temp ;
}V_S ;

/*************** Functions Prototypes ***************/
char main_option (void);
char Sensors_set_menu (int bonus);
void traffic_light_data (struct vehicle_state *ptr_V_S);
void room_temperature_data(struct vehicle_state *ptr_V_S);
void engine_temperature_data(struct vehicle_state *ptr_V_S);
void Display(struct vehicle_state *ptr_V_S, int var_engine_temp,int var_room_temp,int bonus);



/****************** Main Program ********************/
int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	char ch ,sensor_set  ;
	/*using new variable(var_engine_temp)to store the value of the engine temp*/
	int  var_engine_temp =125 ;
	int var_room_temp=25;

	int bonus= WITH_ENGINE_TEMP_CONTROLLER ; /////  bonus
	struct vehicle_state V_S ={ON,OFF,60,25,ON,125};   // initialize the struct

	ch =main_option();


	while((ch=='a')||(ch=='A')){
		sensor_set=Sensors_set_menu (bonus);      // calling Sensors menu

		////////////////// check the Sensors ///////////////////////
		if((sensor_set=='a')||(sensor_set=='A')){
			ch =main_option();
			continue;
		}
		else if((sensor_set=='b')||(sensor_set=='B')){
			traffic_light_data (&V_S);     /////////// pass struct by address

		}
		else if((sensor_set=='c')||(sensor_set=='C')){
			room_temperature_data(&V_S);
			var_room_temp=V_S.room_temp ;
		}
		else if((sensor_set=='d')||(sensor_set=='D')){ /////////////////////////////////////////////
			if (1==bonus){
				engine_temperature_data(&V_S);
				var_engine_temp=V_S.engine_temp;
			}
		}

		if(V_S.vehicle_speed==30)  {
			V_S.AC_state=ON ;
			var_room_temp= V_S.room_temp*((float)5/4) +1;
			if(1==bonus){                /////////////////////  bouns check
				V_S.engine_temp_controller=ON  ;
				var_engine_temp =V_S.engine_temp*((float)5/4)+1 ;
			}

		}
		Display(&V_S,var_engine_temp,var_room_temp,bonus) ;
	}




	return 0;
}  /////////////end of the main Program///////////////////
/************* Functions Defination ********************/
char main_option (void){
	char input ;
	do {

		printf("a. Turn on the vehicle engine\n");
		printf("b. Turn off the vehicle engine\n");
		printf("c. Quit the system\n\n");
		scanf (" %c",&input);
	}while((input=='b')||(input=='B'));
	if ((input== 'c')||(input=='C')){
		printf("Quit the system\n");
		return 0;
	}
	/************ check the input from the user **************/
	while(!((input=='a')||(input=='A')||(input=='b')||(input=='B')||(input=='c')||(input=='C'))){
		printf("\t\t Error ... Please Enter the Correct Choise\n\n");
		input=main_option();
		continue;
	}
	return input;
}

char Sensors_set_menu (int bouns){
	char sensor_set ;
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
	if(1==bouns)        //////////////////////////////////  bouns
		printf("d. Set the engine temperature\n\n");
	scanf (" %c",&sensor_set);
	return sensor_set;
}

void traffic_light_data (struct vehicle_state *ptr_V_S){ //pass struct by address
	char req_color;
	printf("enter the required color : ");
	scanf (" %c",&req_color);
	if((req_color=='g')||(req_color=='G')){
		ptr_V_S->vehicle_speed =100 ;
	}
	if((req_color=='o')||(req_color=='O')){
		ptr_V_S->vehicle_speed=30 ;
	}
	if((req_color=='r')||(req_color=='R')){
		ptr_V_S->vehicle_speed=0;
	}
}
void room_temperature_data(struct vehicle_state *ptr_V_S) {
	int req_room_temp ;
	printf("enter the required room temp : ");
	scanf (" %d",&req_room_temp);
	if((req_room_temp<10)||(req_room_temp>30)){
		ptr_V_S->room_temp=20 ;
		ptr_V_S->AC_state=ON;
	}
	else{
		ptr_V_S->room_temp=req_room_temp;

		ptr_V_S->AC_state=OFF;
	}

}
void engine_temperature_data(struct vehicle_state *ptr_V_S) {
	int req_engine_temp;
	printf("enter the required engine temp : ");
	scanf (" %d",&req_engine_temp);
	if((req_engine_temp<100)||(req_engine_temp>150)){
		ptr_V_S->engine_temp=125 ;
		ptr_V_S->engine_temp_controller=ON;
	}
	else{
		ptr_V_S->engine_temp=req_engine_temp ;

		ptr_V_S->engine_temp_controller=OFF;
	}

}
void Display(struct vehicle_state *ptr_V_S, int var_engine_temp,int var_room_temp,int bouns){

	printf(" Engine is   ON\n");
	printf(" Vehicle Speed :   %d km/s\n",ptr_V_S->vehicle_speed);
	if(ptr_V_S->AC_state==ON)
		printf(" AC is   ON\n");
	else
		printf(" AC is   OFF\n");
	printf(" Room Temperature :   %d C\n",var_room_temp);
	if(1== bouns){
		if(ptr_V_S->engine_temp_controller==ON)
			printf(" Engine Temperature Controller is   ON\n");
		else
			printf(" Engine Temperature Controller is   OFF\n");
		printf(" Engine Temperature :   %d C\n",var_engine_temp);
	}
	printf("\n\n");
}

#include <kipr/wombat.h>

/************************       CONSTANTS          ***********************************/
const int l = 3; // left wheel port
const int r = 0; // right wheel port 
const int claw = 0; //claw port 
const int  arm = 3; // arm port 
const int  l_tophat = 0; // Left Tophat 
const int r_tophat = 5;  // Right Tophat 
const int l_switch = 9; //Left Digital Sensor Switch
const int r_switch = 8; // Right Digital Sensor Switch 
const int light = 3;  // light sensor 
const int threshold = 3555;
const int up = 1600;
const int down = 100;
const int open = 800;
const int closed = 200;

/******************************    Functions Prototypes   *************************/

void forward(int dist);  // Move forward 
void backward(int dist);  // move backwards 
void l90();    // Left 90 turn 
void r90();   // Right  90 turn 
void r180();//right 180 turn 
void r90piviot();//90 degree right turn but right wheel isnt moving!
void squ_pvc();//square up using pvc
void squ_black(); //square up on black line 
void find_black(int side, int dir); //find black use l_tophat or r_tophat for side use forward or backward for dir
void arm_up();
void arm_down();
void line_follow(int dist);//follow a black line for a certain distance




/******************************    Functions Definitions    *************************/
// Goes forward for a certain distance 
void forward(int dist)
{
    cmpc(l); //clear left wheel
    int distance = dist*82; // convert from cm into ticks
    while (gmpc(l)<distance ) //full speed
    {
        mav(l, 1400);
        mav(r,1400);
    }
    mav(l,0);
    mav(r,0);
    msleep(200);

}

// Goes backwards for a certain distance (distance needs to be in positive)
void backward(int dist)
{
    cmpc(l); //clear left wheel
    int distance = (sqrt(dist*dist))*-82; // convert from cm into ticks
    while (gmpc(l)>distance ) //full speed
    {
        mav(l, -1400);
        mav(r,-1400);
    }
    mav(l,0);
    mav(r,0);
    msleep(200);

}


void r90()
{
    cmpc(l); //clear left wheel
    int distance = 945; // set value for perfect 90 degree turn in ticks
    while (gmpc(l)<distance) //full speed for first 75% of distance
    {
        mav(l, 1350);
        mav(r,-1350);
    }
    mav(l,0);
    mav(r,0);

}

//90 degree turn to the left
void l90()
{
    
    cmpc(r); //clear left wheel
    int distance = 945; // set value for perfect 90 degree turn in ticks
    while (gmpc(r)<distance) //full speed for first 75% of distance
    {
        mav(l, -1350);
        mav(r,1350);
    }
    mav(l,0);
        mav(r,0);
}
//90 degree right turn but right wheel isnt moving!
void r90piviot()
{
    cmpc(l); //clear left wheel
    int distance = 1960; // set value for perfect 90 degree turn in ticks
    while (gmpc(l)<distance) //full speed for first 75% of distance
    {
        mav(l, 2000);
        mav(r,0);
    }

}

//right 180 turn 
void r180()
{
    cmpc(l); //clear left wheel
    int distance = 1900; // set value for perfect 90 degree turn in ticks
    while (gmpc(l)<distance) //full speed for first 75% of distance
    {
        mav(l, 1350);
        mav(r,-1350);
    }
    mav(l,0);
    mav(r,0);

}



//square up using pvc 
void squ_pvc()
   
    {
        while ((digital(r_switch)==0)||(digital(l_switch)==0)) //while either switch isn't bumped
        {
            if ((digital(r_switch)==0) && (digital(l_switch)==1)) //while left switch is bumped
            { //backup left wheel
                mav(r,-500);
                mav(l,50);
            }
            else if ((digital(r_switch)==1) && (digital(l_switch)==0)) //while right switch is bumped
            {
                mav(r,50);
                mav(l,-500);
            }
            else 
            { //while neither switch is bumped go backwards
                mav(r,-500);
                mav(l,-500);
            }
        }
        ao();
    }

    //square up on a black line 
    void squ_black()
    {
        while ((analog(r_tophat)< threshold)||(analog(l_tophat)< threshold)) //while either tophat isn't on black
        {
            if ((analog(r_tophat) < threshold) && (analog(l_tophat) > threshold)) //while left tophat is on black
            { //backup left wheel
                mav(r,-500);
                mav(l,50);
            }
            else if ((analog(r_tophat) > threshold) && (analog(l_tophat) < threshold)) //while right tophat is on black
            {
                mav(r,50);
                mav(l,-500);
            }
            else 
            { //while tophat sensors  
                mav(r,-500);
                mav(l,-500);
            }

        }
        ao();
    }

//find black use l_tophat or r_tophat for side use forward or backward for dir
void find_black(int side, int dir) 
{
    int speed = dir*700;
    while (analog(side)<threshold)//while white
    {
		mav (l, speed); //go forward or backward based on passed argument at 700 mav speed
        mav(r, speed);
    }
    ao();
}

void arm_up()
{
	enable_servos();
    set_servo_position(arm,up);
    msleep(500);
    ao();
}

void arm_down()
{
	enable_servos();
    set_servo_position(arm,down);
    msleep(30);
    ao();
}
//follow a black line 
void line_follow(int dist)
{
    cmpc(l);
    while (gmpc(l) > dist*82)
    {
        if (analog(l_tophat) > threshold) 
        {
            motor(l,90);
            motor(r, 5);
        }
        else 
        {
            motor(l, 5);
            motor(r,90);
        }
    }
    msleep(10);
    ao();
}

void mr90()
{
    cmpc(l); //clear left wheel
    int distance = 1200; // set value for perfect 90 degree turn in ticks
    while (gmpc(l)<distance) //full speed for first 75% of distance
    {
        mav(l, 1350);
        mav(r,-1350);
    }
    mav(l,0);
    mav(r,0);

}
    
    
    
    
    
    
    
    
#include <kipr/wombat.h>

/************************       CONSTANTS          ***********************************/
const int close = 212; // claw close value
const int bl = 3; // Back left wheel port
const int fr = 0; // Front right wheel port 
const int br = 1; // Back right wheel
const int fl = 2; // Front left wheel
const int claw = 0; //claw port 
const int  arm = 3; // arm port 
const int  rtophat = 0; // Et Tophat 
const int ltophat = 5;  //  Tophat 
const int l_switch = 9; //Left Digital Sensor Switch
const int r_switch = 8; // Right Digital Sensor Switch 
const int light = 3;  // light sensor 
const int line = 3000; //tophat threshold value

/******************************    Functions Prototypes   *************************/

void forward(int dist);  // Move forward 
void backward(int dist);  // move backwards 
void l90();    // Left 90 turn 
void r90();   // Right  90 turn 
void fwd_till_black(); // Go forward till black
void camera(); // find pink/green cup
void claw_down();
void claw_up();
void close_claw();// make specific for each item
void open_claw();
/*void claw_down_drink();//slightly lift claw*/
void line_follow(int dist);
void line_follow_back(int dist);
void back_till_black();
void square_up();
void square_up_back();

/******************************    Functions Definitions    *************************/

/*//slightly lifts claw//
void claw_down_drink()
{
    enable_servos();
    set_servo_position(arm,170);
}*/

// Goes forward for a certain distance 
void forward(int dist)
{
    cmpc(fl); //clear left wheel
    int distance = dist*82; // convert from cm into ticks
    while (gmpc(fl)<distance ) //full speed
    {
        mav(bl, 1200);
        mav(br,1200);
        mav(fr,1200);
        mav(fl,1200);
    }
    mav(bl, 0);
    mav(br,0);
    mav(fr,0);
    mav(fl,0);
    msleep(200);

}

// Goes backwards for a certain distance (distance needs to be in positive)
void backward(int dist)
{
    cmpc(fl); //clear left wheel
    int distance = sqrt(dist*dist)*-82; // convert from cm into ticks
    while (gmpc(fl)>distance ) //full speed
    {
        mav(bl,-1200);
        mav(br,-1200);
        mav(fr,-1200);
        mav(fl,-1200);
    }
    mav(bl, 0);
    mav(br,0);
    mav(fr,0);
    mav(fl,0);
    msleep(200);

}



//90 degree turn to the right
void r90()
{
    cmpc(fl); //clear left wheel
    int distance = 2400; // set value for perfect 90 degree turn in ticks
    while (gmpc(fl)<distance ) //full speed for first 75% of distance
    {
        mav(bl, 1200);
        mav(br,-1200);
        mav(fr,-1200);
        mav(fl,1200);
    }
    // while (gmpc(fl)<distance) //slow speed for last 25% of distance
    {
        mav(bl, 400);
        mav(br,-400);
        mav(fr,-400);
        mav(fl,400);
    }
    mav(bl, 0);
    mav(br,0);
    mav(fr,0);
    mav(fl,0);
    msleep(200);
    ao();   
}

//90 degree turn to the left
void l90()
{
    cmpc(fr); //clear left wheel
    int distance = 2400; // set value for perfect 90 degree turn in ticks
    while (gmpc(fr)<distance) //full speed for first 75% of distance
    {
        mav(bl, -1200);
        mav(br,1200);
        mav(fr,1200);
        mav(fl,-1200);
    }
    /* while (gmpc(fr)<distance) //slow speed for last 25% of distance
    {
        mav(bl, -400);
        mav(br,400);
        mav(fr,400);
        mav(fl,-400);
    }*/
    mav(bl, 0);
    mav(br,0);
    mav(fr,0);
    mav(fl,0);
    msleep(200);
    ao();   
}
void fwd_till_black()
{
    while (analog(ltophat)<line)
    {
        mav(bl, 1200);
        mav(br,1200);
        mav(fr,1200);
        mav(fl,1200); 
    }
    mav(bl, 0);
    mav(br,0);
    mav(fr,0);
    mav(fl,0);
    msleep(200);
}
void camera()
{
    //int i;
    camera_open();
    msleep(500);
    camera_update();

    while(get_object_center_x(0,0)>55 ||get_object_center_x(0,0) <50)
    {
        camera_update();
        if(get_object_center_x(0,0)>55)
        {
            mav(bl, 500);
            mav(br,-500);
            mav(fr,-500);
            mav(fl,500);
        }
        if(get_object_center_x(0,0)<50)
        {
            mav(bl, -500);
            mav(br,500);
            mav(fr,500);
            mav(fl,-500);
        }
    }
    //  }
    mav(bl, 0);
    mav(br,0);
    mav(fr,0);
    mav(fl,0);
    msleep(200);
    //}
}
void claw_down()
{
    enable_servos();
    set_servo_position(3,180);
}
void claw_up()
{
    enable_servos();
    set_servo_position(3,1000);
}
void close_claw()
{
    enable_servos();
    set_servo_position(0,265);
    msleep(400);
}
void open_claw()
{
    enable_servos();
    set_servo_position(0,800);
    msleep(400);
}
void line_follow(int dist)
{
    cmpc(fl); //clear left wheel
    int distance = dist*82; // convert from cm into ticks
    while (gmpc(fl)<distance ) //full speed
    {
        while (analog(rtophat)<line)
        {
            mav(fl,250);mav(bl,250);
            mav(fr,750);mav(br,750);
        }
        while (analog(rtophat)>line)
        {
            mav(fl,750);mav(bl,750);
            mav(fr,250);mav(br,250);        }
    }
    ao();
    msleep(200);
}
void line_follow_back(int dist)
{
    cmpc(fl); //clear left wheel
    int distance = sqrt(dist*dist)*-82; // convert from cm into ticks
    while (gmpc(fl)>distance ) //full speed
    {
        {
            while (analog(rtophat)>line)
            {
                mav(fl,-250);mav(bl,-250);
                mav(fr,-750);mav(br,-750);
            }
            while (analog(rtophat)<line)
            {
                mav(fl,-750);mav(bl,-750);
                mav(fr,-250);mav(br,-250);        
            }
        }
    }
    // ao();
    msleep(300);
}

void back_till_black()
{
    while (analog(ltophat||rtophat)<line)
    {
        mav(fl,-1000);mav(bl, -1000);
        mav(fr,-1200);mav(br, -1000); 
    }
    mav(fl,0);mav(bl, 0);
    mav(fr,0);mav(br, 0);
    msleep(200);
}   

void square_up()
{
    while((analog(ltophat) < line) || (analog(rtophat) < line))
    {
        if((analog(ltophat) < line) && (analog(rtophat) > line))
        {
                mav(fl,500);mav(bl,500);
                mav(fr,-500);mav(br,-500);
        }

        else if((analog(ltophat) > line) && (analog(rtophat) < line))
        {
                mav(fl,-500);mav(bl,-500);
                mav(fr,550);mav(br,550);
        }
        else
        {
                mav(fl,500);mav(bl,500);
                mav(fr,500);mav(br,500);
        }
    }
}

void square_up_back()
{
    while((analog(ltophat) < line) || (analog(rtophat) < line))
    {
        if((analog(ltophat) < line) && (analog(rtophat) > line))
        {
                mav(fl,-500);mav(bl,-500);
                mav(fr,500);mav(br,500);
        }

        else if((analog(ltophat) > line) && (analog(rtophat) < line))
        {
                mav(fl,500);mav(bl,500);
                mav(fr,-550);mav(br,-550);
        }
        else
        {
                mav(fl,-500);mav(bl,-500);
                mav(fr,-500);mav(br,-500);
        }
    }
}

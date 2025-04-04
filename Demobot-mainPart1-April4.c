#include <kipr/wombat.h>
#include <function.h>

int main()
{  
    enable_servos(); 
    set_servo_position(arm,1800); //arm up
    msleep(100);
    set_servo_position(claw,800);//claw open
    msleep(100);
    ao();
    r90piviot();
    forward(45);
    mr90();    
    squ_pvc();//on black line to get pom poms
    arm_down();
    forward(65);
    set_servo_position(claw,closed);//grab pompoms
    msleep(200);
    set_servo_position(arm,up); //lift pompoms
    msleep(200);
    ao();
    r90(); //turn towards trays
    
    //needs to go forward before turning to get to the 2nd tray
    
    r90();
    // go put poms in the 2nd tray
    forward(12);
    //back up and square up
    backward(22);
    squ_pvc();
    msleep(30);
    //go get the next set of poms 
    forward(23);
    l90();
    forward(10);
    //claw!!
    l90();
    
    //clawdown!!!!!!!
    forward(17);
    r180();
    
    //go to 3rd tray to drop poms
    forward(10);
    
    
    return 0;
    
}

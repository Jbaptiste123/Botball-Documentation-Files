#include <kipr/wombat.h>
#include "Functions.h"
void fwd_till_black();
int main()
{

   ///Cup Code
    claw_down();
    open_claw();
    fwd_till_black();
    square_up();
    forward(25);
    msleep(200);
    camera();
    msleep(200);
    forward(27);
    close_claw();
    claw_down();
    backward(20);
    r90();
    r90();
    
    //place cup down
    claw_down();
    fwd_till_black();
    forward(2);
    square_up_back();
    l90();
    forward(4);
    open_claw();
    square_up_back;
    
    
    
     //Drink code
    ao();
    
    


    return 0;
}





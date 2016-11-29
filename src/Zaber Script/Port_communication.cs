using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Ports; //The .Net Framework library for serial port communication
using Zaber;
using Zaber.PlugIns;


    class Methods : PlugInBase
    {
        // Sections above are parts of the default template for Zaber ScriptRunner. Do not change them
		private SerialPort myport; // Create the port object
        public override void Run(){ // The main function executed by ScriptRunner
        init(); // Initialize port communication
           
        var axis1 = PortFacade.GetConversation(1,1);
        var axis2 = PortFacade.GetConversation(1,2);
        var axis3 = PortFacade.GetConversation(2);
        // Get conversations for the three devices you want to move.
        var currentPosition = Conversation.Request("get pos").Data;

		myport.WriteLine("2"); // Send characters to the Arduino to change the LED pattern
            axis2.Request("set maxspeed",75000);
            axis2.Request("move abs 450000");
            myport.WriteLine("5");
            Godrink(1);
            myport.WriteLine("5");
            Godrink(1);
            /*myport.WriteLine("6");
            Godrink(2);
            myport.WriteLine("7");
            Godrink(3);*/
            myport.WriteLine("8");
            Godrink(4);
            myport.WriteLine("8");
            Godrink(4);
            myport.WriteLine("9");
            axis2.PollUntilIdle();
            axis2.Request("set maxspeed",150000);
            axis1.Request("move abs 1511811");
             axis1.PollUntilIdle();
            axis2.Request("move abs 700000");
           
            axis2.PollUntilIdle();
            myport.WriteLine("S");
            Sleep(5000);
            axis2.Request("set maxspeed",330260);
       // Move the axes to get alcohol. Numbers here represent the dispensers from left to right.
		
        axis2.Request("move abs 0");
        Sleep(2000);
        axis1.Request("move abs 0");
        axis2.PollUntilIdle();
        axis1.PollUntilIdle();
        // Finish the whole process, move the axis back
        myport.WriteLine("1");
        myport.Close();
        //Change the LED pattern again and close the port
		}


        private void init(){
            myport= new SerialPort();
            myport.BaudRate=9600;// Set the BaudRate
            myport.PortName="COM5"; // Set the PortName. Name can be found in the Device Manager
			myport.Open(); //  Open the port
        }

        private void Godrink(int drink_num){
            var axis1 = PortFacade.GetConversation(1,1);
            var axis2 = PortFacade.GetConversation(1,2);
            var axis3 = PortFacade.GetConversation(2);
            // Get conversations for the three devices you want to move.
           var distance_between_dispensers = 199108; //"199108" is the distance (unit in data) between to neighbor drink dispensers. Value should be constant.
           var first_dispenser_position = 236419;//"236419" is the position of the first drink dispenser. 
            var range_axis1=(drink_num-1)*distance_between_dispensers; // Calculate the distance between target dispenser and the first dispenser
            var data_range_axis1=first_dispenser_position+range_axis1;// Calculate the future absolute position of the axis1
            var axis3_maxspeed=825650;// the maximum speed for axis3. Value should be constant
            var currentPosition = axis1.Request("get pos").Data;// get the current position of axis 1
            
            var range_axis2=drink_num*100; //the distance axis2 is going to travel in mm
            var data_range_axis2=Convert.ToInt32(1007874/500*range_axis2);//the distance axis2 is going to travel in data unit

            if (drink_num==2){
                data_range_axis1=445725;
            } else if (drink_num==3){
                data_range_axis1=646383;
            } else if (drink_num==4){
                data_range_axis1=849755;
            }
            
            if (currentPosition != data_range_axis1){//Check if the axis1 need to move (Default situation, axis1 will move to the next dispenser)
                
                var distance=data_range_axis1-currentPosition;
                if (distance <=0){
                    distance=-distance;
                }
                //Get the absolute value of the distance
                var speed_axis1=330260/1.6384; //1.6384 is the coefficient between shown speed on the console and actual speed. Formula: Actual speed=Shown speed/1.6384
                var time=distance/speed_axis1;
                var speed_axis3=Convert.ToInt32(11363/time*1.6384);// Speed need to be an integral.
                //Calculate the speed required for axis3 to simultaneously move the two axes (axis1 and axis3).
                
 
                axis1.Request("move abs", data_range_axis1);//Move axis1
                //axis2.Request("move abs", data_range_axis2);//Move axis2
                axis3.Request("set maxspeed",speed_axis3);//Set speed

               // axis3.Request("move abs 11363");//Move axis 3
               // axis3.PollUntilIdle();// wait for axis3 to move to its halfway position
               axis1.PollUntilIdle();
                axis3.Request("set maxspeed",axis3_maxspeed);// set the speed for axis3 to maximum speed
                axis3.Request("move abs 209974");// raise axis3 to the highest
                axis3.PollUntilIdle();// Wait the axis3 to complete movement
                Sleep(3000);// Wait for the drink to be completely dispensed
                axis3.Request("move abs 0");// lower the axis3 to the lowest
                axis3.PollUntilIdle();// Wait the axis3 to complete movement
                }
            else{    //Check if the axis1 need to move (Exceptional situation, axis1 will stay at the same dispenser)
                Sleep(3500);
                axis3.Request("set maxspeed",axis3_maxspeed);// set the speed for axis3 to maximum speed
                axis3.Request("move abs 209974");// raise axis3 to the highest
                axis3.PollUntilIdle();// Wait the axis3 to complete movement
                Sleep(3000);// Wait for the drink to be completely dispensed
                axis3.Request("move abs 0");// lower the axis3 to the lowest
                axis3.PollUntilIdle();// Wait the axis3 to complete movement
            }
        }
          }

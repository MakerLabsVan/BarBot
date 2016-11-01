/* This template doesn't include a method declaration, so
 * you can define more than one method in your script.
 * Remember: you must declare a Run method like this:
 * public override void Run()
 * The same properties and methods are available from the 
 * PlugInBase class:
 * Input, Output, Log(message, exception), PortFacade, Conversation, 
 * IsCanceled, Sleep(milliseconds), and CheckForCancellation().
 */
using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.IO.Ports;
using Zaber;
using Zaber.PlugIns;

//namespace ScriptRunner.Templates
//{
    class Methods : PlugInBase
    {
		private SerialPort myport;
        public override void Run(){
        init();
        

        Output.WriteLine("hello");      
        var axis1 = PortFacade.GetConversation(1,1);
        // Get conversations for the two devices you want to move.
        //var axis1 = PortFacade.GetConversation(1,1);
        var axis2 = PortFacade.GetConversation(1,2);
        var axis3 = PortFacade.GetConversation(2);
        Output.WriteLine("hello?");
        var currentPosition = Conversation.Request("get pos").Data;
        Output.WriteLine("Current position is {0} microsteps.", currentPosition);
		myport.WriteLine("1");

        //for (i=0;i<Drink_count.length;i++){
            Godrink(1);
            Godrink(2);
            Godrink(3);
            Godrink(4);
            Godrink(5);
        //}
		myport.WriteLine("2");
        axis1.Request("move abs 0");

        axis2.Request("move abs 0");
        axis1.PollUntilIdle();
        axis2.PollUntilIdle();

        myport.Close();
		}


        private void init(){
            myport= new SerialPort();
            myport.BaudRate=9600;
            myport.PortName="COM5";
				myport.Open();
        }

        private void Godrink(int drink_num){
            var axis1 = PortFacade.GetConversation(1,1);
            var axis2 = PortFacade.GetConversation(1,2);
            var axis3 = PortFacade.GetConversation(2);
            var mm = new Measurement(1, UnitOfMeasure.Millimeter);
            var range_axis1=drink_num*150;
            var data_range_axis1=Convert.ToInt32(1511811/750*range_axis1);
            var axis3_maxspeed=825650;
            var currentPosition = axis1.Request("get pos").Data;
            
            var range_axis2=drink_num*100;
            var data_range_axis2=Convert.ToInt32(1007874/500*range_axis2);


            
            Output.WriteLine("Current position is {0} microsteps.", currentPosition);
            Output.WriteLine("Current range is {0} microsteps.", data_range_axis1);
            //console.log("can I see this?");
            
            if (currentPosition != data_range_axis1){
                
                var distance=data_range_axis1-currentPosition;
                if (distance <=0){
                    distance=-distance;
                }
                var speed_axis1=330260/1.6384;
                var time=distance/speed_axis1;
                var speed_axis3=Convert.ToInt32(104987/time*1.6384);
                
            
            
            
                axis1.Request("move abs", data_range_axis1);
                axis2.Request("move abs", data_range_axis2);
                //while ( ! axis1.Request("get pos").IsIdle){
                axis3.Request("set maxspeed",speed_axis3);
                //Sleep(time*1000);
                //axis2.PollUntilIdle();
                //axis2.Request("stop");
                //axis2.PollUntilIdle();
                axis3.Request("move abs 104987");  
                axis3.PollUntilIdle();
                //var currentPosition2 = axis2.Request("get pos").Data;
                //Output.WriteLine("Current position axis2 is {0} microsteps.", currentPosition2);
                //axis2.PollUntilIdle();
                axis3.Request("set maxspeed",axis3_maxspeed);
                axis3.Request("move abs 209974");
                axis3.PollUntilIdle();
                Sleep(1000);
                axis3.Request("move abs 0");
                axis3.PollUntilIdle();
                }
            else{
                axis3.Request("set maxspeed",axis3_maxspeed);
                axis3.Request("move abs 240000");
                axis3.PollUntilIdle();
                Sleep(1000);
                axis3.Request("move abs 0");
                axis3.PollUntilIdle();
            }
        }
          }
       // }

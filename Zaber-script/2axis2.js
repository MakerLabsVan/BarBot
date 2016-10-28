// Helper methods sample in ASCII mode - JavaScript
// In JavaScript you don't need a different template for helper methods
#template(simple)
Output.WriteLine("hello");
var axis1 = PortFacade.GetConversation(0);
Output.WriteLine("hello?");
// First check the current position
var Drink_count = [];
var i=0;
/*while (1){
	Output.WriteLine("Which kinds of alcohol you want to mix? Type 0 to finish");
	var line = Input.ReadLine();
	var buffer = Convert.ToInt32(line)
	if (buffer == 0){
		break;
	}
	Drink_count(i) = buffer;
	i++;
}*/
var currentPosition = Conversation.Request("get pos").Data;
Output.WriteLine("Current position is {0} microsteps.", currentPosition);


//for (i=0;i<Drink_count.length;i++){
	Godrink(1);
	Godrink(2);
	Godrink(3);
	Godrink(4);
	Godrink(5);
//}
axis1.Request("move abs 0");
	axis1.PollUntilIdle();



function Godrink(drink_num){
	var axis1 = PortFacade.GetConversation(1, 1);
	var axis2 = PortFacade.GetConversation(1, 2);
	var mm = new Measurement(1, UnitOfMeasure.Millimeter);
    var range=drink_num*150;
	var data_range=Convert.ToInt32(1511811/750*range);
	var axis2_maxspeed=503316;
	var currentPosition = axis1.Request("get pos").Data;
	
	
	Output.WriteLine("Current position is {0} microsteps.", currentPosition);
	Output.WriteLine("Current range is {0} microsteps.", data_range);
	
	
	if (currentPosition != data_range){
		
		var distance=data_range-currentPosition;
		if (distance <=0){
			distance=-distance;
		}
		var speed_axis1=330260/1.6384;
		var time=distance/speed_axis1;
		var speed_axis2=Convert.ToInt32(122500/time*1.6384);
		
	
	
	
		axis1.Request("move abs", data_range);
		//while ( ! axis1.Request("get pos").IsIdle){
		axis2.Request("set maxspeed",speed_axis2);
		//Sleep(time*1000);
		//axis2.PollUntilIdle();
		//axis2.Request("stop");
		//axis2.PollUntilIdle();
		axis2.Request("move abs 125000");  
		axis2.PollUntilIdle();
		//var currentPosition2 = axis2.Request("get pos").Data;
		//Output.WriteLine("Current position axis2 is {0} microsteps.", currentPosition2);
		//axis2.PollUntilIdle();
		axis2.Request("set maxspeed",axis2_maxspeed);
		axis2.Request("move abs 240000");
		axis2.PollUntilIdle();
		Sleep(1000);
		axis2.Request("move abs 0");
		axis2.PollUntilIdle();
		}
	else{
		axis2.Request("set maxspeed",axis2_maxspeed);
		axis2.Request("move abs 240000");
		axis2.PollUntilIdle();
		Sleep(1000);
		axis2.Request("move abs 0");
		axis2.PollUntilIdle();
	}
}
	


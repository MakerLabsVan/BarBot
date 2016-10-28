// C# / JavaScript sample that demonstrates moving two devices simultaneously
// in ASCII mode.
#template(Simple)
Output.WriteLine("hello");
var axis1 = PortFacade.GetConversation(0);
// Get conversations for the two devices you want to move.
var axis1 = PortFacade.GetConversation(1,1);
var axis2 = PortFacade.GetConversation(1,2);
var axis3 = PortFacade.GetConversation(2);
Output.WriteLine("hello?");
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

// We'll ask c1 to execute a long move, while c2 wiggles back and forth
function Godrink(drink_num){
	var axis1 = PortFacade.GetConversation(1,1);
	var axis2 = PortFacade.GetConversation(1,2);
	var axis3 = PortFacade.GetConversation(2);
	var mm = new Measurement(1, UnitOfMeasure.Millimeter);
    var range=drink_num*150;
	var data_range=Convert.ToInt32(1511811/750*range);
	var axis3_maxspeed=825650;
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
		var speed_axis3=Convert.ToInt32(104987/time*1.6384);
		
	
	
	
		axis1.Request("move abs", data_range);
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
	


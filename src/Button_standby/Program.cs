using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Diagnostics;

namespace Arduino_Standby
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPort myport = new SerialPort();
            myport.BaudRate = 9600;
            myport.PortName = "COM5";
            while (true)
            {
                try
                {
                    myport.Open();
                }
                catch (Exception)
                {
                    continue;
                }
               
                var command = myport.ReadLine();
                //System.Console.WriteLine(command);
                if (command == "E\r")
                {

                    //System.Console.WriteLine("Over THere");
                    System.Console.WriteLine("Command Received!");
                    myport.Close();
                    // Don't change the code below
                    System.Diagnostics.ProcessStartInfo ProcStartInfo =
                    new System.Diagnostics.ProcessStartInfo("cmd");
                    ProcStartInfo.RedirectStandardOutput = true;
                    ProcStartInfo.UseShellExecute = false;
                    ProcStartInfo.CreateNoWindow = false;
                    ProcStartInfo.RedirectStandardError = true;
                    System.Diagnostics.Process MyProcess = new System.Diagnostics.Process();
                    ProcStartInfo.Arguments = "/c start /wait Port_communication.bat"; //start the bat file and wait for exit
                    MyProcess.StartInfo = ProcStartInfo;
                    MyProcess.Start();
                    MyProcess.WaitForExit();
                    // Don't change the code above
                }
                else
                {
                    System.Console.WriteLine("Something Goes Wrong");
                }
                
            }
        }
    }
}

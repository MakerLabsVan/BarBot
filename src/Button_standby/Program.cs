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
            System.Console.WriteLine("Hello, World!~");
            while (true)
            {
                try
                {
                    myport.Open();
                    System.Console.WriteLine("Hello, World!!");
                }
                catch (Exception)
                {
                    System.Console.WriteLine("Hello, World!!!");
                }
               
                var command = myport.ReadLine();
                System.Console.WriteLine("Hello, World!");
                System.Console.WriteLine(command);
                if (command == "E\r")
                {

                    System.Console.WriteLine("Over THere");
                    myport.Close();
                    System.Diagnostics.ProcessStartInfo ProcStartInfo =
    new System.Diagnostics.ProcessStartInfo("cmd");
                    ProcStartInfo.RedirectStandardOutput = true;
                    ProcStartInfo.UseShellExecute = false;
                    ProcStartInfo.CreateNoWindow = false;
                    ProcStartInfo.RedirectStandardError = true;
                    System.Diagnostics.Process MyProcess = new System.Diagnostics.Process();
                    ProcStartInfo.Arguments = "/c start /wait C:\\Port_communication.bat ";
                    MyProcess.StartInfo = ProcStartInfo;
                    MyProcess.Start();
                    MyProcess.WaitForExit();
                }
                else
                {
                    System.Console.WriteLine("Something wrong");
                }
                
            }
        }
    }
}

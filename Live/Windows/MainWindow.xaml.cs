using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace Windows
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        SerialPort serialPort;
        Queue<double> samples = new Queue<double>();
        public MainWindow()
        {
            InitializeComponent();
            serialPort = new SerialPort("COM11");
            serialPort.DataReceived += SerialPort_DataReceived;
            serialPort.ErrorReceived += SerialPort_ErrorReceived;
            serialPort.DtrEnable = true;
            serialPort.RtsEnable = true;
            serialPort.Open();
            var dt = new DispatcherTimer(new TimeSpan(0, 0, 0, 0, 100), DispatcherPriority.Normal, new EventHandler(dt_tick), Dispatcher.CurrentDispatcher);
            dt.Start();
        }

        private void dt_tick(object sender, EventArgs e)
        {
            var counter = 0;
            double total = 0;
            while (samples.Count > 0)
            {
                counter += 1;
                total += samples.Dequeue();
            }
            tbSensor1.Text = (total / counter).ToString("p1").PadLeft(3);
        }

        private void SerialPort_ErrorReceived(object sender, SerialErrorReceivedEventArgs e)
        {
            throw new NotImplementedException();
        }

        private void SerialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string text = serialPort.ReadLine();
            double value;
            if (double.TryParse(text, out value))
            {
                samples.Enqueue(value / 100);
            }
        }
    }
}

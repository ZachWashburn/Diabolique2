using System;
using System.Collections.Generic;
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
using System.Threading;
namespace DiaboliqueServerUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {

        public class Client
        { 
            public int ID { get; set; }
            public string Name { get; set; }
        }

        private List<Client> LoadClientData()
        {
            List<Client> clients = new List<Client>();

            int nClientCount = DiaboliqueServer.GetClientCount();
            int[] client_ids = new int[nClientCount];
            DiaboliqueServer.GetClientsWrap(ref client_ids);

            foreach (int client in client_ids)
            {
                clients.Add(new Client()
                {
                    ID = client,
                    Name = DiaboliqueServer.GetConnectionName(client),

                });
            }

            return clients;
        }
        public MainWindow()
        {

            
       
            InitializeComponent();

            //


            Thread thread1 = new Thread(LoopingMethod);
            thread1.Start();
        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);

            // Begin dragging the window
            this.DragMove();
        }

        public void UpdateClientData()
        {
            ClientDataGrid.ItemsSource = LoadClientData();
        }


        private void LoopingMethod()
        {
            for (; ; )
            {
                Dispatcher.Invoke(new Action(() => { ClientDataGrid.ItemsSource = LoadClientData(); }));
                Thread.Sleep(500);
            }
        }

    }
}

using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.IO;


namespace chessGraphics
{
    public partial class Form1 : Form
    {
        private Square srcSquare;
        private Square dstSquare;

        private pipe enginePipe;
        Button[,] matBoard;

        bool isCurPlWhite = true;
        bool isGameOver = false;

        const int BOARD_SIZE = 8;
        char[,] chessBoard = new char[8 , 8];
        bool singalPlayer;
         

        public Form1()
        {
            InitializeComponent();
        }

        private void showButtons () 
        {
            

        }

        private void initForm()
        {
            loadBackEnd();
            enginePipe.connect();
            

            Invoke((MethodInvoker)delegate {  

                lblWaiting.Visible = false;
                lblCurrentPlayer.Visible = true;
                label1.Visible = true;

                string s = enginePipe.getEngineMessage();



                if (s.Length != (BOARD_SIZE * BOARD_SIZE + 1))
                {
                    MessageBox.Show("The length of the board's string is not according the PROTOCOL");
                    this.Close();

                }
                else
                {
                    isCurPlWhite = (s[s.Length - 1] == '0');
                    paintBoard(s);
                }

            });
    
        }

        Thread connectionThread;
        private void Form1_Load(object sender, EventArgs e)
        {
            enginePipe = new pipe();
            //this.Show();

            //MessageBox.Show("Press OK to start waiting for engine to connect...");
            lblWaiting.Visible = false;
            connectionThread = new Thread(showButtons);
            connectionThread.Start();
            connectionThread.IsBackground = true;
            
            //initForm();
        
        }

        Image getImageBySign(char sign)
        {
            switch (sign)
            {
                case 'q':
                    return Properties.Resources.q_black;
                case 'Q':
                    return Properties.Resources.q_white;
                case 'k':
                    return Properties.Resources.k_black;
                case 'K':
                    return Properties.Resources.k_white;
                case 'p':
                    return Properties.Resources.p_black;
                case 'P':
                    return Properties.Resources.p_white;
                case 'r':
                    return Properties.Resources.r_black;
                case 'R':
                    return Properties.Resources.r_white;
                case 'n':
                    return Properties.Resources.n_black;
                case 'N':
                    return Properties.Resources.n_white;
                case 'b':
                    return Properties.Resources.b_black;
                case 'B':
                    return Properties.Resources.b_white;
                case '#':
                    return null;
                default:
                    return Properties.Resources.x;

            }
        }

        private void paintBoard(string board)
        {
            int i, j, z=0;

            matBoard = new Button[BOARD_SIZE, BOARD_SIZE];

            btnBoard.FlatAppearance.MouseOverBackColor = Color.LightGray;
            
            Button newBtn;
            Point pnt;

            int currentWidth = btnBoard.Location.X;
            int currentHeight = btnBoard.Location.Y;
            
            bool isColBlack = true;
            bool isRowBlack = true ;
            
            this.SuspendLayout();

            lblCurrentPlayer.Text = isCurPlWhite ? "Black" : "White";

            for (i = 0; i < BOARD_SIZE; i++)
            {
                currentWidth = btnBoard.Location.X;
                isColBlack = isRowBlack;

                for (j = 0; j < BOARD_SIZE; j++)
                {
                    newBtn = new Button();
                    matBoard[i, j] = newBtn;

                    newBtn.FlatAppearance.MouseOverBackColor = btnBoard.FlatAppearance.MouseOverBackColor ;
                    newBtn.BackColor = isColBlack ? Color.White : Color.Green;
                    newBtn.FlatAppearance.BorderColor = btnBoard.FlatAppearance.BorderColor;
                    newBtn.FlatAppearance.BorderSize = btnBoard.FlatAppearance.BorderSize;
                    newBtn.FlatStyle = btnBoard.FlatStyle;

                    newBtn.Size = new System.Drawing.Size(btnBoard.Width, btnBoard.Height);
                    newBtn.Tag = new Square(i, j);
                    pnt = new Point(currentWidth, currentHeight );
                    newBtn.Location = pnt;
                    newBtn.BackgroundImageLayout = ImageLayout.Stretch;

                    newBtn.BackgroundImage  = getImageBySign(board[z]);
                    
                    newBtn.Click += lastlbl_Click;

                    Controls.Add(newBtn);
                    chessBoard[j, i] = board[z];

                    currentWidth += btnBoard.Width;
                    isColBlack = !isColBlack;
                    z++;

                }

                isRowBlack = !isRowBlack;
                currentHeight += btnBoard.Height;

            }

            Controls.Remove(btnBoard);
            this.ResumeLayout(false);
        }

        void lastlbl_Click(object sender, EventArgs e)
        {
            Button b = (Button)sender;
            if (srcSquare != null)
            {
                // unselected
                if (matBoard[srcSquare.Row, srcSquare.Col] == b)
                {
                 
                    matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                    srcSquare = null;
                }
                else
                {
                    dstSquare = (Square)b.Tag;
                    matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;

                    Thread t = new Thread(playMove);
                    t.Start();
                    
                    //   t.IsBackground = true;
                    //playMove();
                }
            }
            else
            {
                srcSquare = (Square)b.Tag;
                matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.DarkGreen;
            }
         
        }

        // messages should be according the protocol.
        // index is the message number in the protocol
        string[] messages =  {
            "Valid move",
            "Valid move - you made chess",
            "Invalid move - not your player",
            "Invalid move - destination is not free",
            "Invalid move - chess wil occure",
            "Invalid move - out of bounds",
            "Invalid move - illegeal movement with piece",
            "Invalid move - source and dest are equal",
            "Game over - check mate",
            "Unknown message"
            };


        string convertEngineToText(string m)
        {
            int res;
            bool b = int.TryParse(m, out res);

            if (!b || res < 0 || res >= messages.Length)
                return messages[messages.Length - 1];

            return messages[res];
        }
        


        void playMove()
        {
            if (isGameOver)
                return;


            try
            {
                 Invoke((MethodInvoker)delegate {

                     lblEngineCalc.Visible = true;
            
                    lblMove.Text = string.Format("Move from {0} to {1}", srcSquare, dstSquare);
                    lblMove.Visible = true;
                    //lblEngineCalc.Invalidate();
                    
                    label2.Visible = false;
                    lblResult.Visible = false;

                    this.Refresh();
            

                    // should send pipe to engine
                    enginePipe.sendEngineMove(srcSquare.ToString() + dstSquare.ToString());
                    string msg = srcSquare.ToString() + dstSquare.ToString();
                    

                     // should get pipe from engine
                    string m = enginePipe.getEngineMessage();

                    if (!enginePipe.isConnected())
                    {
                        MessageBox.Show("Connection to engine has lost. Bye bye.");
                        this.Close();
                        return;
                    }

                    string res = convertEngineToText(m);

                     if (res.ToLower().StartsWith("game over"))
                     {
                         isGameOver = true;
                     }
                     else if (res.ToLower().StartsWith("valid"))
                     {
                         chessBoard[(msg[2] - 97), msg[3] - '0' - 1] = chessBoard[(msg[0] - 97), msg[1] - '0' - 1];
                         chessBoard[(msg[0] - 97), msg[1] - '0' - 1] = '#';
                         isCurPlWhite = !isCurPlWhite;
                         if (!singalPlayer)
                            lblCurrentPlayer.Text = isCurPlWhite ? "Black" : "White";

                         matBoard[dstSquare.Row, dstSquare.Col].BackgroundImage = matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage;
                         matBoard[srcSquare.Row, srcSquare.Col].BackgroundImage = null;

                         matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                         matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;
                         if (singalPlayer)
                         {
                             AIMove();
                             
                         }

                     }
                    
                    lblEngineCalc.Visible = false;
                    lblResult.Text = string.Format("{0}", res);
                    lblResult.Visible = true;
                    label2.Visible = true;
                    this.Refresh();
                 });
                
           
                }
                catch
                {

                }
                finally
                {
                    Invoke((MethodInvoker)delegate
                    {
                        if (srcSquare != null)
                            matBoard[srcSquare.Row, srcSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                        if (dstSquare != null)
                            matBoard[dstSquare.Row, dstSquare.Col].FlatAppearance.BorderColor = Color.Blue;

                        dstSquare = null;
                        srcSquare = null;

                    });
                }

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
   

            enginePipe.sendEngineMove("quit");
            enginePipe.close();
        }
        private void AIMove ()
        {
            string bMode = ""; 
            for (int i = 0; i < BOARD_SIZE; i++)
            {
                for (int j =  0 ; j < BOARD_SIZE; j++) 
                {
                    bMode += chessBoard[j , i];
                }
            }
            Process AI = createPython(bMode);
            AI.Start();
            string res = AI.StandardOutput.ReadToEnd();
            if (res.Contains("None")) 
            {
                System.Media.SoundPlayer player = new System.Media.SoundPlayer();
                player.SoundLocation = "song.wav";
                player.Play();
                Thread.Sleep(100000);
                goto End;
            }
            string resToEngine = (char)( res[0]) + (9 - (res[1] - '0')).ToString() + (char)( res[2]) + (9 - (res[3] - '0')).ToString();
            Console.WriteLine(bMode);
            Console.WriteLine(res);
            Console.WriteLine(resToEngine);
            chessBoard[(resToEngine[2] - 97), resToEngine[3] - '0' - 1] = chessBoard[(resToEngine[0] - 97), resToEngine[1] - '0' - 1];
            chessBoard[(resToEngine[0] - 97), resToEngine[1] - '0' - 1] = '#';
            matBoard[res[3] - '0' - 1,  (res[2] - 97)].BackgroundImage = matBoard[res[1] - '0' - 1,  (res[0] - 97)].BackgroundImage;
            matBoard[res[1] - '0' - 1 ,  (res[0] - 97)].BackgroundImage = null;
            
            enginePipe.sendEngineMove(resToEngine);
            enginePipe.getEngineMessage();
            End: { };
        }

        Process createPython (string board)
        {
            Process proc = new Process();
            proc.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory();
            proc.StartInfo.FileName = @"C:\python37\python.exe";
            proc.StartInfo.Arguments = string.Format("{0} {1}", ".\\chessAI\\minMax.py", board);
            proc.StartInfo.UseShellExecute = false;
            proc.StartInfo.RedirectStandardOutput = true;
            proc.StartInfo.CreateNoWindow = true;
            return proc;
        }
        private void lblWaiting_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            singalPlayer = true;
            lblWaiting.Visible = true;
            button1.Visible = false;
            button2.Visible = false;
            Thread initThread = new Thread(initForm);
            initThread.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            singalPlayer = false;
            lblWaiting.Visible = true;
            button1.Visible = false;
            button2.Visible = false;
            Thread initThread = new Thread(initForm);
            initThread.Start();
        }

        private void loadBackEnd () 
        {
            Process backEnd = new Process();
            backEnd.StartInfo.WorkingDirectory = Directory.GetCurrentDirectory();
            backEnd.StartInfo.FileName = "Game_engine.exe";
            backEnd.StartInfo.UseShellExecute = false;
            //backEnd.StartInfo.CreateNoWindow = true;
            backEnd.Start();
        }
    }
}

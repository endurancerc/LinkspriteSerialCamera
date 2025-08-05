#pragma once
#include <stdio.h>
#include <stdlib.h>


namespace CameraController {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Drawing;
	using namespace System::Threading;


	public ref class Form1 : public System::Windows::Forms::Form
	{

		array<unsigned char,1>^ reset_command;
		array<unsigned char,1>^ reset_return;
		array<unsigned char,1>^ good_reset_return;
		array<unsigned char,1>^ take_pic_command;
		array<unsigned char,1>^ read_file_size_command;
		array<unsigned char,1>^ read_content_command;
		array<unsigned char,1>^ read_content_command_return;
		array<unsigned char,1>^ good_read_content_command_return;
		array<unsigned char,1>^ take_pic_command_return;	
		array<unsigned char,1>^ good_take_pic_command_return;	
		array<unsigned char,1>^ clear_buffer;	
		array<unsigned char,1>^ read_file_size_command_return;
		array<unsigned char,1>^ good_read_file_size_command_return;
		array<unsigned char,1>^ picture_buffer;
		array<unsigned char,1>^ picture_buffer2;
		array<unsigned char,1>^ jpeg;


		array<unsigned char,1>^ small_size;
		array<unsigned char,1>^ med_size;
		array<unsigned char,1>^ large_size;
		array<unsigned char,1>^ size_return;

		array<unsigned char,1>^ baud_9600;
		array<unsigned char,1>^ baud_19200;
		array<unsigned char,1>^ baud_38400;
		array<unsigned char,1>^ baud_57600;
		array<unsigned char,1>^ baud_115200;
		array<unsigned char,1>^ baud_return;


		private: System::Windows::Forms::Label^  label2;
		private: System::Windows::Forms::ComboBox^  comboBox3;
		private: System::Windows::Forms::Button^  button6;
		private: System::IO::Ports::SerialPort^  serialPort1;
		private: System::Windows::Forms::Button^  button7;
		private: System::Windows::Forms::Button^  button8;
		private: System::Windows::Forms::Button^  button9;


		private: System::Windows::Forms::Button^  button1;
		private: System::Windows::Forms::Button^  button2;
		private: System::Windows::Forms::PictureBox^  pictureBox1;
		private: System::Windows::Forms::GroupBox^  groupBox1;
		private: System::Windows::Forms::GroupBox^  groupBox2;
		private: System::Windows::Forms::TextBox^  textBox1;
		private: System::Windows::Forms::ProgressBar^  progressBar1;

		private: System::Windows::Forms::ComboBox^  comboBox1;
		private: System::Windows::Forms::Button^  button3;
		private: System::Windows::Forms::Button^  button4;
		private: System::Windows::Forms::ComboBox^  comboBox2;
		private: System::Windows::Forms::Label^  label3;
		private: System::Windows::Forms::ComboBox^  comboBox4;
		private: System::Windows::Forms::Button^  button5;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button10;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::ComponentModel::IContainer^  components;

			 private: Thread ^trd;

	public:
		Form1(void)
		{
			InitializeComponent();


			reset_command = gcnew array<unsigned char,1>(4){ 86, 0, 38, 0 };	
			reset_return = gcnew array<unsigned char,1>(4);
			good_reset_return = gcnew array<unsigned char,1>(4){ 118, 0, 38, 0 };	

			clear_buffer = gcnew array<unsigned char,1>(1);	

			take_pic_command = gcnew array<unsigned char,1>(5){ 86, 00, 54, 01, 00 };	
			take_pic_command_return = gcnew array<unsigned char,1>(5);	
			good_take_pic_command_return = gcnew array<unsigned char,1>(5){ 118, 00, 54, 00, 00 };	

			read_file_size_command = gcnew array<unsigned char,1>(5){ 86, 00, 52, 01, 00 };	
			read_file_size_command_return = gcnew array<unsigned char,1>(9);
			good_read_file_size_command_return = gcnew array<unsigned char,1>(7){ 118, 00, 52, 00, 04, 00, 00 };	//two more on the end are the file size so this is determined later

			read_content_command_return = gcnew array<unsigned char,1>(42);

			picture_buffer = gcnew array<unsigned char,1>(1000);
			picture_buffer2 = gcnew array<unsigned char,1>(1000);

			jpeg = gcnew cli::array<unsigned char,1>(80000);
                                            									//Value that shows the number of bytes of the picture

			med_size = gcnew cli::array<unsigned char,1>(9){ 86, 00, 49, 05, 04, 01, 00, 25, 17 };
			large_size = gcnew cli::array<unsigned char,1>(9){ 86, 00, 49, 05, 04, 01, 00, 25, 00 };
			small_size = gcnew cli::array<unsigned char,1>(9){ 86, 00, 49, 05, 04, 01, 00, 25, 34 };
			size_return = gcnew cli::array<unsigned char,1>(5){ 118, 00, 49, 00, 00 };


			baud_9600 = gcnew cli::array<unsigned char,1>(7){ 86, 00, 36, 03, 01, 174, 200 };
			baud_19200 = gcnew cli::array<unsigned char,1>(7){ 86, 00, 36, 03, 01, 86, 228 };
			baud_38400 = gcnew cli::array<unsigned char,1>(7){ 86, 00, 36, 03, 01, 42, 242 };
			baud_57600 = gcnew cli::array<unsigned char,1>(7){ 86, 00, 36, 03, 01, 28, 76 };
			baud_115200 = gcnew cli::array<unsigned char,1>(7){ 86, 00, 36, 03, 01, 13, 166 };
			baud_return = gcnew cli::array<unsigned char,1>(5);


			saveFileDialog1->Filter = "JPEG Image|*.jpg";


		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}




			
#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->comboBox4 = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(6, 19);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Connect";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(87, 19);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Disconnect";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(197, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->TabIndex = 12;
			this->pictureBox1->TabStop = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Location = System::Drawing::Point(12, 441);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(179, 55);
			this->groupBox1->TabIndex = 13;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Result";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::SystemColors::InactiveBorder;
			this->textBox1->Location = System::Drawing::Point(6, 19);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(157, 20);
			this->textBox1->TabIndex = 4;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->comboBox4);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->comboBox3);
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Location = System::Drawing::Point(12, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(176, 108);
			this->groupBox2->TabIndex = 14;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Com Access";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 78);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(32, 13);
			this->label3->TabIndex = 23;
			this->label3->Text = L"Baud";
			// 
			// comboBox4
			// 
			this->comboBox4->FormattingEnabled = true;
			this->comboBox4->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"9600", L"19200", L"38400", L"57600", L"115200"});
			this->comboBox4->Location = System::Drawing::Point(41, 75);
			this->comboBox4->Name = L"comboBox4";
			this->comboBox4->Size = System::Drawing::Size(122, 21);
			this->comboBox4->TabIndex = 22;
			this->comboBox4->Text = L"38400";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 51);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(26, 13);
			this->label2->TabIndex = 21;
			this->label2->Text = L"Port";
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Items->AddRange(gcnew cli::array< System::Object^  >(15) {L"COM1", L"COM2", L"COM3", L"COM4", L"COM5", L"COM6", 
				L"COM7", L"COM8", L"COM9", L"COM10", L"COM11", L"COM12", L"COM13", L"COM14", L"COM15"});
			this->comboBox3->Location = System::Drawing::Point(41, 48);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(122, 21);
			this->comboBox3->TabIndex = 21;
			this->comboBox3->Text = L"COM3";
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(9, 18);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(160, 23);
			this->button6->TabIndex = 19;
			this->button6->Text = L"Reset Camera";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &Form1::button6_Click);
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 38400;
			this->serialPort1->PortName = L"COM3";
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(9, 47);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(160, 23);
			this->button7->TabIndex = 20;
			this->button7->Text = L"Capture Image";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &Form1::button7_Click);
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(9, 76);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(160, 23);
			this->button8->TabIndex = 21;
			this->button8->Text = L"Read File Size";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &Form1::button8_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(9, 105);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(160, 23);
			this->button9->TabIndex = 22;
			this->button9->Text = L"Transfer Image";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &Form1::button9_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 501);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(825, 23);
			this->progressBar1->Step = 1;
			this->progressBar1->TabIndex = 26;
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) {L"160x120", L"320x240", L"640x480"});
			this->comboBox1->Location = System::Drawing::Point(48, 197);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(121, 21);
			this->comboBox1->TabIndex = 28;
			this->comboBox1->Text = L"320x240";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(9, 163);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(160, 23);
			this->button3->TabIndex = 29;
			this->button3->Text = L"Change Size";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(9, 224);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(160, 23);
			this->button4->TabIndex = 31;
			this->button4->Text = L"Change Baud";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// comboBox2
			// 
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"9600", L"19200", L"38400", L"57600", L"115200"});
			this->comboBox2->Location = System::Drawing::Point(48, 253);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(121, 21);
			this->comboBox2->TabIndex = 30;
			this->comboBox2->Text = L"38400";
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(9, 134);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(160, 23);
			this->button5->TabIndex = 32;
			this->button5->Text = L"Save Image";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &Form1::button5_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->button10);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Controls->Add(this->button5);
			this->groupBox3->Controls->Add(this->label1);
			this->groupBox3->Controls->Add(this->button4);
			this->groupBox3->Controls->Add(this->button6);
			this->groupBox3->Controls->Add(this->comboBox2);
			this->groupBox3->Controls->Add(this->button7);
			this->groupBox3->Controls->Add(this->button3);
			this->groupBox3->Controls->Add(this->button8);
			this->groupBox3->Controls->Add(this->comboBox1);
			this->groupBox3->Controls->Add(this->button9);
			this->groupBox3->Location = System::Drawing::Point(12, 127);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(176, 308);
			this->groupBox3->TabIndex = 33;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Camera Functions";
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(9, 279);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(160, 23);
			this->button10->TabIndex = 33;
			this->button10->Text = L"Video Start";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &Form1::button10_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(10, 256);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(32, 13);
			this->label4->TabIndex = 1;
			this->label4->Text = L"Baud";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(15, 200);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(27, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Size";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(850, 531);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"LinkSprite JPEG Color Camera";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	//connect button
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 try {
					 serialPort1->PortName =  comboBox3->Text;


					 if(comboBox4->Text == "9600") {
						 serialPort1->BaudRate = 9600;
					 }
					 else if(comboBox4->Text == "19200") {
						 serialPort1->BaudRate = 19200;
					 }
					 else if(comboBox4->Text == "38400") {
						 serialPort1->BaudRate = 38400;
					 }
					 else if(comboBox4->Text == "57600") {
						 serialPort1->BaudRate = 57600;
					 }
					 else {
						 serialPort1->BaudRate = 115200;
					 }


					 serialPort1->Open();							//fails here if not connected when starting

					 textBox1->Text = "Connected";
				 }
				 catch (Exception ^e) {
					textBox1->Text = "Error Connecting!";
				 }
		 }


	//disconnect button
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
            //check if com port 1 is closed
            if (serialPort1->IsOpen)
            {
                // if not closed, close port
                serialPort1->Close();
                textBox1->Text = "Com closed successfully...";  
                textBox1->Refresh();
            }
            else
            {
                //if closed,show it to user
                textBox1->Text = "Com is already closed..."; 
                textBox1->Refresh();
            }
		 }






//Reset
private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
			  reset();
		 }

		 void reset () {
			   try {
				   serialPort1->Write(reset_command, 0, 4);
			   } catch (Exception ^e){
			   }

			   Thread::Sleep(500);

			   //while (serialPort1->BytesToRead != 0){}

			   try {
				   serialPort1->Read(reset_return, 0, 4);
			   } catch (Exception ^e){
			   }
			   

			   serialPort1->DiscardInBuffer();


			   //118 00 38 00
			   if(reset_return[0].Equals(118) && reset_return[1].Equals(00) && reset_return[2].Equals(38) && reset_return[3].Equals(00)){
					textBox1->Text = "Reset";
				   
			   }
			   else {
				   textBox1->Text = "Not Reset";
			   }
		 }



//take picture
private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) { 
			capture();
		 }

		 void capture() {
			   try {
				   serialPort1->Write(take_pic_command, 0, 5);
			   } catch (Exception ^e){
			   }

			   Thread::Sleep(500);

			   try {
				   serialPort1->Read(take_pic_command_return, 0, 5);
			   } catch (Exception ^e){
			   }

			   serialPort1->DiscardInBuffer();


			   //118 00 54 00 00
			   if(take_pic_command_return[0].Equals(118) && take_pic_command_return[1].Equals(00) && take_pic_command_return[2].Equals(54) && take_pic_command_return[3].Equals(00) && take_pic_command_return[4].Equals(00)){
					textBox1->Text = "Pic Taken";
			   }
			   else {
				   textBox1->Text = "Pic was not taken";
			   }
		 }


//Read File size
private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {
			readsize();
		 }


		 void readsize() {
			   try {
				   serialPort1->Write(read_file_size_command, 0, 5);
			   } catch (Exception ^e){
			   }

			   Thread::Sleep(500);

			   try {
				   serialPort1->Read(read_file_size_command_return, 0, 9);
			   } catch (Exception ^e){
			   }

			   serialPort1->DiscardInBuffer();


			   //118 00 52 00 04, 00, 00, XH, XL
			   if(read_file_size_command_return[0].Equals(118) && read_file_size_command_return[1].Equals(00) && read_file_size_command_return[2].Equals(52) && read_file_size_command_return[3].Equals(00) && read_file_size_command_return[4].Equals(04) && read_file_size_command_return[5].Equals(00) && read_file_size_command_return[6].Equals(00)){
				   String ^ XH = read_file_size_command_return[7].ToString(); //MSB
				   String ^ XL = read_file_size_command_return[8].ToString(); //LSB

				   int msb = int(read_file_size_command_return[7]);
				   int lsb = int(read_file_size_command_return[8]);
				   int file_size_bytes = (msb * 256) + lsb;

				   //label4->Text = file_size_bytes.ToString();

				   progressBar1->Maximum = file_size_bytes;
				   progressBar1->Step = file_size_bytes/100;

				   textBox1->Text = "File Size XH: " + XH + ", XL: " + XL;
				   //textBox1->Text = file_size_bytes.ToString() + " bytes";
			   }
			   else {
				   textBox1->Text = "File Size was not read";
			   }
		 }


//Get a picutre from the camera
private: System::Void button9_Click(System::Object^  sender, System::EventArgs^  e) {
			transfer();		
		}


		 void transfer() {
			 int x = 0;
			 int y = 0;
			 int MH, ML;
			 bool done = false;
			 int counter = 0;
			 int counter2 = 0;

			 while(!done) {
				 MH = x / 256;
				 ML = x % 256;

				 read_content_command = gcnew array<unsigned char,1>(16){ 86, 00, 50, 12, 00, 10, 00, 00, MH, ML, 00, 00, 00, 32, 00, 10 };

				 try {
					serialPort1->Write(read_content_command, 0, 16);
				 } catch (Exception ^e){
				 }

//				 Thread::Sleep(20);
				 while (serialPort1->BytesToRead < 42);


				 while (serialPort1->BytesToRead != 0 && !done){
					 serialPort1->Read(picture_buffer, 0, 1);			

					 if(y > 4 && counter < 32) {
						jpeg[counter2] = picture_buffer[0];
						counter2++;
						//I guess this needs an exception?
						progressBar1->Value = counter2;
						counter++;

						 if(picture_buffer[0].Equals(217) && picture_buffer2[0].Equals(255)){
							 done = true;
						 }

						 //save the old var
						 picture_buffer2[0] = picture_buffer[0];
					 }
					 y++;

				 }

				 counter = 0;
				 y = 0;

				 x = x + 32;
			 }

			 serialPort1->DiscardInBuffer();

			 Stream^ image = gcnew MemoryStream(jpeg);
			 try {
				pictureBox1->Image = Image::FromStream(image);

				progressBar1->Value = 0;
			 }
			    catch (Exception^ e){
			 }	
		 }




//change baud rate
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			   
			 
			 if(comboBox1->Text == "320x240") {
				 try {
				     serialPort1->Write(med_size, 0, 9);
			     } catch (Exception ^e){
			     }
			 }
			 else if(comboBox1->Text == "160x120") {
				 try {
				     serialPort1->Write(small_size, 0, 9);
			     } catch (Exception ^e){
			     }
			 }
			 else {
				 try {
					 serialPort1->Write(large_size, 0, 9);
			     } catch (Exception ^e){
			     }
			 }
			 
			 
			   Thread::Sleep(500);

			   try {
				   serialPort1->Read(size_return, 0, 5);
			   } catch (Exception ^e){
			   }

			   serialPort1->DiscardInBuffer();


			   //118, 00, 49, 00, 00
			   if(size_return[0].Equals(118) && size_return[1].Equals(00) && size_return[2].Equals(49) && size_return[3].Equals(00) && size_return[4].Equals(00)){
					textBox1->Text = "Size Changed";
			   }
			   else {
				   textBox1->Text = "Size not changed";
			   }
		 }




//change baud rate
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(comboBox3->Text == "9600") {
				 try {
				     serialPort1->Write(baud_9600, 0, 7);
			     } catch (Exception ^e){
			     }
			 }
			 else if(comboBox3->Text == "19200") {
				 try {
				     serialPort1->Write(baud_19200, 0, 7);
			     } catch (Exception ^e){
			     }
			 }
			 else if(comboBox3->Text == "38400") {
				 try {
					 serialPort1->Write(baud_38400, 0, 7);
			     } catch (Exception ^e){
			     }
			 }
			 else if(comboBox3->Text == "57600") {
				 try {
					 serialPort1->Write(baud_57600, 0, 7);
			     } catch (Exception ^e){
			     }
			 }
			 else {
				 try {
					 serialPort1->Write(baud_115200, 0, 7);
			     } catch (Exception ^e){
			     }
			 }
			 
			 
			   Thread::Sleep(500);

			   try {
				   serialPort1->Read(baud_return, 0, 5);
			   } catch (Exception ^e){
			   }

			   serialPort1->DiscardInBuffer();


			   //118, 00, 36, 00, 00
			   if(baud_return[0].Equals(118) && baud_return[1].Equals(00) && baud_return[2].Equals(36) && baud_return[3].Equals(00) && baud_return[4].Equals(00)){
					textBox1->Text = "Baud Changed";
			   }
			   else {
				   textBox1->Text = "Baud not changed";
			   }			 
		 }



//Save Pic
private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveFileDialog1->ShowDialog();

			 if(saveFileDialog1->FileName != "") {
				Image^ image = pictureBox1->Image;
				image->Save( saveFileDialog1->FileName, System::Drawing::Imaging::ImageFormat::Jpeg);
			 }
		 }


//video start
private: System::Void button10_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(button10->Text == "Video Start") {
				 button10->Text = "Video Stop";
				 //timer1->Start();
			 	 ThreadStart ^myThreadDelegate = gcnew ThreadStart(this, &CameraController::Form1::repeat);
				 trd = gcnew Thread(myThreadDelegate);
				 trd->IsBackground = true;
				 trd->Start();
			 }
			 else {
				button10->Text = "Video Start";
				//timer1->Stop();
				trd->Abort();
			 }
		 }


//take a pic on a timer tick
private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
			reset();
			capture();
			readsize();
			transfer();		
		 }


private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {

		 }


private: void repeat()
{	
	while(true)
	{
	//ThreadTask();
	//Thread::Sleep(100);
			reset();
			capture();
			readsize();
			transfer();	
	}
}

};
}



/*
			 int x = 0;
			 int y = 0;
			 int MH, ML;
			 bool done = false;
			 int counter = 0;
			 int counter2 = 0;

			 while(!done) {
				 MH = x / 256;
				 ML = x % 256;

				 read_content_command = gcnew array<unsigned char,1>(16){ 86, 00, 50, 12, 00, 10, 00, 00, MH, ML, 00, 00, 00, 32, 00, 10 };

				 try {
					serialPort1->Write(read_content_command, 0, 16);
				 } catch (Exception ^e){
				 }

				 Thread::Sleep(20);

			     try {
				     serialPort1->Read(read_content_command_return, 0, 42);		//get the first 5 command bits
			     } catch (Exception ^e){
			     }


				 while(y < 42 && !done){
					 if(y > 4 && y < 37) {
						jpeg[counter2] = read_content_command_return[y];

						//textBox2->AppendText(read_content_command_return[y].ToString());
						//textBox2->AppendText(" ");

						counter2++;
						progressBar1->Value = counter2;
						//counter++;

						 if(read_content_command_return[y].Equals(217) && picture_buffer2[0].Equals(255)){
							 done = true;
						 }

						 //save the old var
						 picture_buffer2[0] = read_content_command_return[y];
					 }
					 y++;
				 }

				 //textBox2->AppendText("\n");

				 //counter = 0;
				 y = 0;

				 x = x + 32;
			 }

			 serialPort1->DiscardInBuffer();

			 Stream^ image = gcnew MemoryStream(jpeg);
			 try {
				pictureBox1->Image = Image::FromStream(image);
			 }
			 catch (Exception^ e){
				 MessageBox::Show(e->ToString());
			 }
*/









/*
			 int x = 0;
			 int y = 0;
			 int MH, ML;
			 bool done = false;
			 int counter = 0;
			 int counter2 = 0;

			 while(!done) {
				 MH = x / 256;
				 ML = x % 256;

				 read_content_command = gcnew array<unsigned char,1>(16){ 86, 00, 50, 12, 00, 10, 00, 00, MH, ML, 00, 00, 00, 32, 00, 10 };

				 try {
					serialPort1->Write(read_content_command, 0, 16);
				 } catch (Exception ^e){
				 }

				 Thread::Sleep(25);

			     try {
				     serialPort1->Read(read_content_command_return, 0, 5);		//get the first 5 command bits
			     } catch (Exception ^e){
			     }

				 while (serialPort1->BytesToRead != 0 && !done){
					 serialPort1->Read(picture_buffer, 0, 1);			

					 if(counter < 32) {
						jpeg[counter2] = picture_buffer[0];
						counter2++;
						progressBar1->Value = counter2;
					 }
					 counter++;

					 if(picture_buffer[0].Equals(217) && picture_buffer2[0].Equals(255)){
						 done = true;
					 }

					 //save the old var
					 picture_buffer2[0] = picture_buffer[0];
				 }

				 counter = 0;

				 x = x + 32;
			 }

			 label3->Text = counter2.ToString();

			 Stream^ image = gcnew MemoryStream(jpeg);
			 try {
				pictureBox1->Image = Image::FromStream(image);
			 }
			    catch (Exception^ e){
			 }
*/
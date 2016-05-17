#include "MainForm.h"
#include "ConfigForm.h"
#include "windows.h"
#include "iostream"
#include "dirent.h"
#include "msclr\marshal_cppstd.h"

#pragma comment(lib,"shell32.lib") 

using namespace System;
using namespace System::Windows::Forms;
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace VagrantManager;
using namespace std;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	VagrantManager::MainForm form;
	Application::Run(%form);
}

MainForm::MainForm(void) {
	InitializeComponent();
}

MainForm::~MainForm() {
	if (components) {
		delete components;
	}
}

void MainForm::InitializeComponent(void) {
	System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
	this->explorerBtn = (gcnew System::Windows::Forms::Button());
	this->closeBtn = (gcnew System::Windows::Forms::Button());
	this->configBtn = (gcnew System::Windows::Forms::Button());
	this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
	this->vagrantList = (gcnew System::Windows::Forms::ComboBox());
	this->vagrantupBtn = (gcnew System::Windows::Forms::Button());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->groupBox1->SuspendLayout();
	this->SuspendLayout();
	// 
	// explorerBtn
	// 
	this->explorerBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"explorerBtn.Image")));
	this->explorerBtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->explorerBtn->Location = System::Drawing::Point(12, 49);
	this->explorerBtn->Name = L"explorerBtn";
	this->explorerBtn->Size = System::Drawing::Size(79, 23);
	this->explorerBtn->TabIndex = 1;
	this->explorerBtn->Text = L"Explorer";
	this->explorerBtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->explorerBtn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->explorerBtn->UseVisualStyleBackColor = true;
	this->explorerBtn->Click += gcnew System::EventHandler(this, &MainForm::explorerBtn_Click);
	// 
	// closeBtn
	// 
	this->closeBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"closeBtn.Image")));
	this->closeBtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->closeBtn->Location = System::Drawing::Point(12, 79);
	this->closeBtn->Name = L"closeBtn";
	this->closeBtn->Size = System::Drawing::Size(79, 23);
	this->closeBtn->TabIndex = 2;
	this->closeBtn->Text = L"Quit";
	this->closeBtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->closeBtn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->closeBtn->UseVisualStyleBackColor = true;
	this->closeBtn->Click += gcnew System::EventHandler(this, &MainForm::closeBtn_Click);
	// 
	// configBtn
	// 
	this->configBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"configBtn.Image")));
	this->configBtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->configBtn->Location = System::Drawing::Point(12, 19);
	this->configBtn->Name = L"configBtn";
	this->configBtn->Size = System::Drawing::Size(79, 23);
	this->configBtn->TabIndex = 0;
	this->configBtn->Text = L"Config";
	this->configBtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->configBtn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->configBtn->UseVisualStyleBackColor = true;
	this->configBtn->Click += gcnew System::EventHandler(this, &MainForm::configBtn_Click);
	// 
	// groupBox1
	// 
	this->groupBox1->Controls->Add(this->configBtn);
	this->groupBox1->Controls->Add(this->closeBtn);
	this->groupBox1->Controls->Add(this->explorerBtn);
	this->groupBox1->Location = System::Drawing::Point(254, 12);
	this->groupBox1->Name = L"groupBox1";
	this->groupBox1->Size = System::Drawing::Size(97, 115);
	this->groupBox1->TabIndex = 3;
	this->groupBox1->TabStop = false;
	this->groupBox1->Text = L"App Action";
	// 
	// vagrantList
	// 
	this->vagrantList->FormattingEnabled = true;
	this->vagrantList->Location = System::Drawing::Point(12, 61);
	this->vagrantList->Name = L"vagrantList";
	this->vagrantList->Size = System::Drawing::Size(236, 21);
	this->vagrantList->TabIndex = 4;
	this->vagrantList->Text = L"-- Choose Vagrant VM --";
	// 
	// vagrantupBtn
	// 
	this->vagrantupBtn->Location = System::Drawing::Point(13, 88);
	this->vagrantupBtn->Name = L"vagrantupBtn";
	this->vagrantupBtn->Size = System::Drawing::Size(235, 23);
	this->vagrantupBtn->TabIndex = 5;
	this->vagrantupBtn->Text = L"Vagrant up";
	this->vagrantupBtn->UseVisualStyleBackColor = true;
	this->vagrantupBtn->Click += gcnew System::EventHandler(this, &MainForm::vagrantupBtn_Click);
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Location = System::Drawing::Point(12, 31);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(77, 13);
	this->label1->TabIndex = 6;
	this->label1->Text = L"Vagrant VM(s):";
	// 
	// MainForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(362, 145);
	this->Controls->Add(this->label1);
	this->Controls->Add(this->vagrantupBtn);
	this->Controls->Add(this->vagrantList);
	this->Controls->Add(this->groupBox1);
	this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
	this->Name = L"MainForm";
	this->Text = L"VagrantManager";
	this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
	this->groupBox1->ResumeLayout(false);
	this->ResumeLayout(false);
	this->PerformLayout();

}

void MainForm::fillDropUpDownList() {
	//get Config Path from XML
	ConfigForm^ configForm = gcnew ConfigForm();
	const char *basePath = configForm->getfromConfigBasePath();

	const char* PATH = ".";

	DIR *dir;
	struct dirent *ent;
	//Scan for subfolder
	if ((dir = opendir(basePath)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {

			string sDirectory(ent->d_name);
			string compareItem[2] = { ".",".." }; //not necessary item from scan

			if (!(find(begin(compareItem), end(compareItem), sDirectory) != end(compareItem))) {
				String^ itemName = gcnew String(sDirectory.c_str());
				vagrantList->Items->Add(itemName);
			}
		}
		closedir(dir);
	}
	else {
		//DO NOTHING
	}
	//avoid memory leak
	delete dir, PATH,ent;
}

System::Void MainForm::MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	//fill combobox on Window open
	fillDropUpDownList();
}

System::Void MainForm::closeBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	//close App
	quick_exit(EXIT_SUCCESS);
}

System::Void MainForm::configBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	//open dialog
	ConfigForm^ configForm = gcnew ConfigForm();
	configForm->ShowDialog();
}

System::Void MainForm::explorerBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	//Init vards
	wstring wstringPath;
	LPCWSTR sw;
	//get ConfigPath from XML File
	ConfigForm^ configForm = gcnew ConfigForm();
	const char *basePath = configForm->getfromConfigBasePath();

	string sbasePath(basePath);

	wstringPath = wstring(sbasePath.begin(), sbasePath.end());
	sw = wstringPath.c_str();
	//open windows explorer
	ShellExecute(NULL, NULL, sw, NULL, NULL, SW_SHOWNORMAL);
}

System::Void MainForm::vagrantupBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	// Init Vars
	STARTUPINFO si;
	wstring wstringPath;
	LPWSTR sw;
	PROCESS_INFORMATION pi;
	String^ selectedItem;
	string sselectedItem;

	SecureZeroMemory(&si, sizeof(STARTUPINFO));
	//cast
	selectedItem = vagrantList->SelectedItem->ToString();
	sselectedItem = msclr::interop::marshal_as< std::string >(selectedItem);
	sselectedItem = "cd" + sselectedItem + "&& vagrant up && exit";

	//check if item was selected
	if (vagrantList->SelectedIndex == -1) {
		MessageBox::Show("Please choose a Item");
	} else {
		wstringPath = wstring(sselectedItem.begin(), sselectedItem.end());
		sw = const_cast<LPWSTR>(wstringPath.c_str());
		si.cb = sizeof(STARTUPINFO);

		//CMD call
		CreateProcess(L"c:\\windows\\system32\\cmd.exe", sw, NULL,
			NULL, FALSE, 0, NULL, NULL, &si, &pi);
	}
}
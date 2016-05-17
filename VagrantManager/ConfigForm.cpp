#include "fstream"
#include "ConfigForm.h"
#include "tinyxml2.h"
#include "msclr\marshal_cppstd.h"

using namespace VagrantManager;
using namespace std;
using namespace tinyxml2;
//Constructor
ConfigForm::ConfigForm() {
	InitializeComponent();
}

//Destructor 
ConfigForm::~ConfigForm() {
	if (components) {
		delete components;
	}
}

void ConfigForm::InitializeComponent() {
	System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(ConfigForm::typeid));
	this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
	this->button1 = (gcnew System::Windows::Forms::Button());
	this->basePath_input = (gcnew System::Windows::Forms::TextBox());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
	this->cancelBtn = (gcnew System::Windows::Forms::Button());
	this->saveBtn = (gcnew System::Windows::Forms::Button());
	this->groupBox1->SuspendLayout();
	this->SuspendLayout();
	// 
	// groupBox1
	// 
	this->groupBox1->Controls->Add(this->button1);
	this->groupBox1->Controls->Add(this->basePath_input);
	this->groupBox1->Controls->Add(this->label1);
	this->groupBox1->Location = System::Drawing::Point(13, 13);
	this->groupBox1->Name = L"groupBox1";
	this->groupBox1->Size = System::Drawing::Size(405, 80);
	this->groupBox1->TabIndex = 0;
	this->groupBox1->TabStop = false;
	this->groupBox1->Text = L"Config";
	// 
	// button1
	// 
	this->button1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button1.Image")));
	this->button1->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->button1->Location = System::Drawing::Point(321, 28);
	this->button1->Name = L"button1";
	this->button1->Size = System::Drawing::Size(70, 23);
	this->button1->TabIndex = 2;
	this->button1->Text = L"Select";
	this->button1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->button1->UseVisualStyleBackColor = true;
	this->button1->Click += gcnew System::EventHandler(this, &ConfigForm::filebrowserBtn_Click);
	// 
	// basePath_input
	// 
	this->basePath_input->Location = System::Drawing::Point(69, 31);
	this->basePath_input->Name = L"basePath_input";
	this->basePath_input->Size = System::Drawing::Size(246, 20);
	this->basePath_input->TabIndex = 1;
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Location = System::Drawing::Point(7, 34);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(56, 13);
	this->label1->TabIndex = 0;
	this->label1->Text = L"Base Path";
	// 
	// cancelBtn
	// 
	this->cancelBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"cancelBtn.Image")));
	this->cancelBtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->cancelBtn->Location = System::Drawing::Point(354, 99);
	this->cancelBtn->Name = L"cancelBtn";
	this->cancelBtn->Size = System::Drawing::Size(64, 23);
	this->cancelBtn->TabIndex = 1;
	this->cancelBtn->Text = L"Cancel";
	this->cancelBtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->cancelBtn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->cancelBtn->UseVisualStyleBackColor = true;
	this->cancelBtn->Click += gcnew System::EventHandler(this, &ConfigForm::cancelBtn_Click);
	// 
	// saveBtn
	// 
	this->saveBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"saveBtn.Image")));
	this->saveBtn->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->saveBtn->Location = System::Drawing::Point(284, 99);
	this->saveBtn->Name = L"saveBtn";
	this->saveBtn->Size = System::Drawing::Size(64, 23);
	this->saveBtn->TabIndex = 2;
	this->saveBtn->Text = L"Save";
	this->saveBtn->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
	this->saveBtn->TextImageRelation = System::Windows::Forms::TextImageRelation::ImageBeforeText;
	this->saveBtn->UseVisualStyleBackColor = true;
	this->saveBtn->Click += gcnew System::EventHandler(this, &ConfigForm::saveBtn_Click);
	// 
	// ConfigForm
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(430, 132);
	this->Controls->Add(this->saveBtn);
	this->Controls->Add(this->cancelBtn);
	this->Controls->Add(this->groupBox1);
	this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
	this->Name = L"ConfigForm";
	this->Text = L"VagrantManager - Configuration";
	this->Load += gcnew System::EventHandler(this, &ConfigForm::ConfigForm_Load);
	this->groupBox1->ResumeLayout(false);
	this->groupBox1->PerformLayout();
	this->ResumeLayout(false);
}

System::Void ConfigForm::ConfigForm_Load(System::Object^  sender, System::EventArgs^  e) {
	
	if (isConfigFileExisting(CONFIGFILE)) {

		//set XML saved config path in textbox
		char *basePath = getfromConfigBasePath();
		string sbasePath(basePath);

		basePath_input->Text = gcnew String(sbasePath.c_str());

		//avoid memory leak
		delete basePath;
	}

}

System::Void ConfigForm::filebrowserBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	//open Filebrowser and set Value in Textbox
	if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		basePath_input->Text = folderBrowserDialog1->SelectedPath;
	}
}

System::Void ConfigForm::saveBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	//set Path in XML
	remove(CONFIGFILE); //delete old file
	if (!createConfigFileWithElement()) {
		MessageBox::Show("The operation has been completed ", "Save", MessageBoxButtons::OKCancel, MessageBoxIcon::Asterisk);
	} else {
		MessageBox::Show("The operation has been failed ", "Save", MessageBoxButtons::OKCancel, MessageBoxIcon::Error);
	}
	
}

System::Void ConfigForm::cancelBtn_Click(System::Object^  sender, System::EventArgs^  e) {
	//Hide dialog
	this->Hide();
}

bool ConfigForm::isConfigFileExisting(const char *filename) {
	//Check if config.xml exist
	ifstream ifile(filename);
	return (bool) ifile;
}

bool ConfigForm::createConfigFileWithElement() {

	//Create XMl

	//Init vars
	tinyxml2::XMLDocument xmlDoc;
	String^ tmpsystemString;
	string castedBasePath;

	//ROOT DOM ELEMENT
	XMLNode *pointerRoot = xmlDoc.NewElement("Config");
	xmlDoc.InsertFirstChild(pointerRoot);

	//CHILD DOM ELEMENT
	XMLElement *pointerElement = xmlDoc.NewElement("BasePath");
	tmpsystemString = basePath_input->Text;

	//Cast
	castedBasePath = msclr::interop::marshal_as<std::string>(tmpsystemString);

	//Save
	pointerElement->SetText(castedBasePath.c_str());
	pointerRoot->InsertEndChild(pointerElement);
	
	XMLError result = xmlDoc.SaveFile(CONFIGFILE);

	return result;
}

char* ConfigForm::getfromConfigBasePath() {
	const char *basePath;
	char returnPath;
	tinyxml2::XMLDocument xmlDoc;

	//load config.xml File
	XMLError result = xmlDoc.LoadFile(CONFIGFILE);
	if (result != XML_SUCCESS) return false;

	//Load root DOM Element
	XMLNode *root = xmlDoc.FirstChildElement("Config");
	if (root == nullptr) return false;

	//Load child DOM Element
	XMLText *value = root->FirstChildElement("BasePath")->FirstChild()->ToText();
	string sValue = value->Value();

	//cast
	char *y = new char[sValue.length() + 1];
	strcpy(y, sValue.c_str());

	//avoid memory leak
	delete basePath;
	return y;
}
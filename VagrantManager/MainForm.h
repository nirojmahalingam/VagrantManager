#pragma once
#include "windows.h"
#include "ConfigForm.h";
#include "iostream"
#include "dirent.h"
#include "msclr\marshal_cppstd.h"

namespace VagrantManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace std;

	public ref class MainForm : public System::Windows::Forms::Form {
		public:
			MainForm(void);
		protected:
			~MainForm();
		private: 
			//Def. Component
			System::Windows::Forms::Button^  explorerBtn;
			System::Windows::Forms::Button^  closeBtn;
			System::Windows::Forms::Button^  configBtn;
			System::Windows::Forms::GroupBox^  groupBox1;
			System::Windows::Forms::ComboBox^  vagrantList;
			System::Windows::Forms::Button^  vagrantupBtn;
			System::Windows::Forms::Label^  label1;
			System::ComponentModel::Container ^components;

			//Init Component
			void InitializeComponent(void);

			//Events
			System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
			System::Void configBtn_Click(System::Object^  sender, System::EventArgs^  e);
			System::Void explorerBtn_Click(System::Object^  sender, System::EventArgs^  e);
			System::Void closeBtn_Click(System::Object^  sender, System::EventArgs^  e);
			System::Void vagrantupBtn_Click(System::Object^  sender, System::EventArgs^  e);

			//Methods
			void fillDropUpDownList();
	};
}

#ifndef ConfigForm_H
#define ConfigForm_H
namespace VagrantManager {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ConfigForm : public System::Windows::Forms::Form {
		public:
			ConfigForm();
			char* getfromConfigBasePath();
		protected:
			~ConfigForm();
		private: 
			const char *CONFIGFILE = "config.xml";

			//Def. Component
			System::Windows::Forms::GroupBox^  groupBox1;
			System::Windows::Forms::Label^  label1;
			System::Windows::Forms::Button^  button1;
			System::Windows::Forms::TextBox^  basePath_input;
			System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;
			System::Windows::Forms::Button^  cancelBtn;
			System::Windows::Forms::Button^  saveBtn;
			System::ComponentModel::Container ^components;

			//Init Component
			void InitializeComponent(void);

			//Events
			System::Void filebrowserBtn_Click(System::Object^, System::EventArgs^);
			System::Void saveBtn_Click(System::Object^, System::EventArgs^);
			System::Void cancelBtn_Click(System::Object^, System::EventArgs^);
			System::Void ConfigForm_Load(System::Object^, System::EventArgs^);

			//Methods
			bool isConfigFileExisting(const char * filename);
			bool createConfigFileWithElement();
	};
}
#endif
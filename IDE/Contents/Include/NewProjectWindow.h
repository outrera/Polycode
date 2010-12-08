
#pragma once

#include "PolycodeGlobals.h"
#include "PolycodeUI.h"
#include "Polycode.h"

using namespace Polycode;

class TemplateUserData  {
public:
	string templateFolder;
	int type;
};

class NewProjectWindow : public UIWindow {
	public:
	NewProjectWindow();
	~NewProjectWindow();
	
	void parseTemplatesIntoTree(UITree *tree, OSFileEntry folder);

	string getTemplateFolder();
	wstring getProjectName();
	wstring getProjectLocation();
	
	void handleEvent(Event *event);
	void ResetForm();
	
	protected:
	
		UITree *defaultTemplateTree;
	
		UITextInput *projectLocationInput;
		UITextInput *projectNameInput;
	
		UIButton *cancelButton;
		UIButton *okButton;
		UIButton *locationSelectButton;	
		UITreeContainer *templateContainer;
	
		string templateFolder;
};
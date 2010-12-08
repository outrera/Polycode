

#include "PolycodeProjectBrowser.h"

PolycodeProjectBrowser::PolycodeProjectBrowser() : ScreenEntity() {
	treeContainer = new UITreeContainer("boxIcon.png", L"Projects", 200, 555);
	treeContainer->getRootNode()->toggleCollapsed();
	treeContainer->getRootNode()->addEventListener(this, UITreeEvent::SELECTED_EVENT);
	
	addChild(treeContainer);		
	treeContainer->setPosition(0,45);	
	
	selectedData = NULL;
}

PolycodeProjectBrowser::~PolycodeProjectBrowser() {
	
}

void PolycodeProjectBrowser::addProject(PolycodeProject *project) {
	UITree *projectTree = treeContainer->getRootNode()->addTreeChild("projectIcon.png", project->getProjectName(), (void*) project);
	projectTree->toggleCollapsed();
	
	wstring projectPath = project->getRootFolder();
	string wpath;
	wpath.assign(projectPath.begin(), projectPath.end());	
	
	parseFolderIntoNode(projectTree, wpath);	
}

void PolycodeProjectBrowser::handleEvent(Event *event) {
	if(event->getDispatcher() == treeContainer->getRootNode()) {
		if(event->getEventCode() == UITreeEvent::SELECTED_EVENT){ 
			selectedData =  (BrowserUserData *)treeContainer->getRootNode()->getSelectedNode()->getUserData();
			dispatchEvent(new Event(), Event::CHANGE_EVENT);
		}
	}
	
	ScreenEntity::handleEvent(event);
}

void PolycodeProjectBrowser::parseFolderIntoNode(UITree *node, string spath) {
	printf("Parsing %s\n", spath.c_str());
	vector<OSFileEntry> files = OSBasics::parseFolder(spath, false);
	for(int i=0; i < files.size(); i++) {
		OSFileEntry entry = files[i];
		if(entry.type == OSFileEntry::TYPE_FOLDER) {
			wstring name;
			name.assign(entry.name.begin(),entry.name.end());			
			BrowserUserData *data = new BrowserUserData();
			data->fileEntry = entry;
			UITree *newChild = node->addTreeChild("folder.png", name, (void*) data);
			parseFolderIntoNode(newChild, entry.fullPath);
		} else {
			wstring name;
			name.assign(entry.name.begin(),entry.name.end());			
			BrowserUserData *data = new BrowserUserData();
			data->fileEntry = entry;
			UITree *newChild = node->addTreeChild("file.png", name, (void*) data);			
		}
	}	
}

void PolycodeProjectBrowser::Resize(int newWidth, int newHeight) {
	treeContainer->Resize(newWidth, newHeight);
}

#include "PolycodeView.h"
#include "Polycode.h"
#include "PolycodeUI.h"

using namespace Polycode;

class PolycodeProjectGenerator : EventHandler {
public:
	PolycodeProjectGenerator(PolycodeView *view);
	~PolycodeProjectGenerator();

	bool Update();

	void generateVS10();
	void generateVS12();
	void generateXcode();
	void generateMakefile();
	void generateCMake();

	String loadFile(OSFILE *f);
	void writeFile(String f, String s);

	void handleEvent(Event *e);

private:
	Core *core;
	Scene *scene;

	UILabel *platformLabel;
	UICheckBox *vs10Proj;
	UICheckBox *vs12Proj;
	UICheckBox *xcodeProj;
	UICheckBox *makefileProj;
	UICheckBox *cmakeProj;

	UILabel *projNameLabel;
	UITextInput *projName;

	UILabel *projPosLabel;
	UITextInput *projPos;
	UIButton *browseButton;

	UILabel *moduleLabel;
	UICheckBox *physics2D;
	UICheckBox *physics3D;
	UICheckBox *ui;

	UIButton *generate;

	OSBasics bas;
};
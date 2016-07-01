#include "PolycodeProjectGenerator.h"

PolycodeProjectGenerator::PolycodeProjectGenerator(PolycodeView *view) {
	core = new POLYCODE_CORE(view, 640, 480, false, false, 0, 0, 60);
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);
	CoreServices::getInstance()->getResourceManager()->addArchive("UIThemes.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("UIThemes", false);
	CoreServices::getInstance()->getConfig()->loadConfig("Polycode", "UIThemes/dark/theme.xml");

	SceneLabel::defaultAnchor = Vector3(-1.0, -1.0, 0.0);
	SceneLabel::defaultPositionAtBaseline = true;
	SceneLabel::defaultSnapToPixels = true;
	SceneLabel::createMipmapsForLabels = false;

	Entity::defaultBlendingMode = Renderer::BLEND_MODE_NONE;
	CoreServices::getInstance()->getRenderer()->setTextureFilteringMode(Renderer::TEX_FILTERING_NEAREST);

	scene = new Scene(Scene::SCENE_2D_TOPLEFT);
	scene->getActiveCamera()->setOrthoSize(640, 480);
	scene->rootEntity.processInputEvents = true;

	platformLabel = new UILabel("Choose Your Platforms:", 16);
	platformLabel->setPosition(10, 10);
	scene->addEntity(platformLabel);
	vs10Proj = new UICheckBox("Visual Studio 2010", false);
	vs10Proj->setPosition(10, 30);
	scene->addEntity(vs10Proj);
	vs12Proj = new UICheckBox("Visual Studio 2013", false);
	vs12Proj->setPosition(10, 48);
	scene->addEntity(vs12Proj);
	//xcodeProj = new UICheckBox("Xcode", false);
	//xcodeProj->setPosition(10, 66);
	//scene->addEntity(xcodeProj);	makefileProj = new UICheckBox("Makefile", false);
	makefileProj->setPosition(10, 84);
	scene->addEntity(makefileProj);
	//cmakeProj = new UICheckBox("CMake", false);
	//cmakeProj->setPosition(10, 102);
	//scene->addEntity(cmakeProj);

	projNameLabel = new UILabel("Name your project:", 16);
	projNameLabel->setPosition(10, 130);
	scene->addEntity(projNameLabel);
	projName = new UITextInput(false, 100, 12);
	projName->setPosition(10, 150);
	scene->addEntity(projName);

	projPosLabel = new UILabel("Path:", 16);
	projPosLabel->setPosition(10, 180);
	scene->addEntity(projPosLabel);
	projPos = new UITextInput(false, 400, 12);
	projPos->setPosition(10, 200);
	scene->addEntity(projPos);

	browseButton = new UIButton("Browse", 60);
	browseButton->setPosition(420, 200);
	scene->addEntity(browseButton);
	browseButton->addEventListener(this, UIEvent::CLICK_EVENT);

	moduleLabel = new UILabel("Choose the modules you want to use:", 16);
	moduleLabel->setPosition(10, 250);
	scene->addEntity(moduleLabel);
	physics2D = new UICheckBox("2D Physics Module", false);
	physics2D->setPosition(10, 250);
	//scene->addEntity(physics2D);
	physics3D = new UICheckBox("3D Physics Module", false);
	physics3D->setPosition(10, 268);
	scene->addEntity(physics3D);
	ui = new UICheckBox("UI Module", false);
	ui->setPosition(10, 286);
	scene->addEntity(ui);

	generate = new UIButton("Generate", 70);
	generate->setPosition(10, 320);
	generate->addEventListener(this, UIEvent::CLICK_EVENT);
	scene->addEntity(generate);
}
PolycodeProjectGenerator::~PolycodeProjectGenerator() {

}

bool PolycodeProjectGenerator::Update() {
	return core->updateAndRender();
}

void PolycodeProjectGenerator::handleEvent(Event* e){
	if (e->getDispatcher() == generate){
		if (vs10Proj->isChecked())
			generateVS10();
		if (vs12Proj->isChecked())
			generateVS12();
		if (xcodeProj->isChecked())
			generateXcode();
		if (makefileProj->isChecked())
			generateMakefile();
		if (cmakeProj->isChecked())
			generateCMake();
	}
	if (e->getDispatcher() == browseButton) {
		projPos->setText(core->openFolderPicker());
	}
}

void PolycodeProjectGenerator::generateVS10(){
	OSFILE *slnF = bas.open("Projects/PolycodeProject10.sln", "r");
	OSFILE *vcxprojF = bas.open("Projects/PolycodeProject10.vcxproj", "r");
	OSFILE *mainF = bas.open("Projects/Source/mainWin.cpp", "r");
	OSFILE *appCF = bas.open("Projects/Source/PolycodeProject.cpp", "r");
	OSFILE *appHF = bas.open("Projects/Include/PolycodeProject.h", "r");

	String sln = loadFile(slnF), vcxproj = loadFile(vcxprojF), main = loadFile(mainF), appC = loadFile(appCF), appH = loadFile(appHF);

	bas.close(slnF);
	bas.close(vcxprojF);
	bas.close(mainF);
	bas.close(appCF);
	bas.close(appHF);

	String modulesInc, modulesLibD, modulesLibs, modulesLibsD, modulesIncH, extraCopy;

	if (physics2D->isChecked() || physics3D->isChecked() || ui->isChecked()){
		modulesInc = "Framework/include;";
		modulesLibD = "Framework/lib/win32/;";
		if (physics2D->isChecked() || physics3D->isChecked()){
			//modulesInc += "Framework/Modules/Dependencies/include;";
			modulesLibD += "Framework/Modules/Dependencies/lib;";
			if (physics2D->isChecked()){
				modulesLibs = "Polycode2DPhysics.lib;Box2D.lib;";
				modulesLibsD = "Polycode2DPhysics_d.lib;Box2D_d.lib;";
				modulesIncH = "#include \"Physics2D.h\"\n";
			}
			if (physics3D->isChecked()){
				modulesLibs += "Polycode3DPhysics.lib;BulletDynamics.lib;BulletCollision.lib;LinearMath.lib;";
				modulesLibsD += "Polycode3DPhysics_d.lib;BulletDynamics_d.lib;BulletCollision_d.lib;LinearMath_d.lib;";
				modulesIncH += "#include \"Physics3D.h\"\n";
			}
		}
		if (ui->isChecked()){
			modulesLibs += "PolycodeUI.lib;";
			modulesLibsD += "PolycodeUI_d.lib;";
			modulesIncH += "#include \"PolycodeUI.h\"\n";
			extraCopy = "if not exist \"$(ProjectDir)UIThemes.pak\" copy \"$(PolycodeDir)Modules/Assets/UIThemes.pak\" \"$(ProjectDir)\"\n";
		}
	}

	String name = projName->getText();

	sln = sln.replace("--ProjectName--", name);

	vcxproj = vcxproj.replace("--ProjectName--", name);
	vcxproj = vcxproj.replace("--ModulesIncDir--", modulesInc);
	vcxproj = vcxproj.replace("--ModulesLibDir--", modulesLibD);
	vcxproj = vcxproj.replace("--ModulesDebug--", modulesLibsD);
	vcxproj = vcxproj.replace("--Modules--", modulesLibs);
	vcxproj = vcxproj.replace("--ExtraCopy--", extraCopy);

	main = main.replace("--ProjectName--", name);
	appC = appC.replace("--ProjectName--", name);
	appH = appH.replace("--ProjectName--", name);
	appH = appH.replace("--ModulesInc--", modulesIncH);

	String path = projPos->getText();

	if (!bas.isFolder(path))
		bas.createFolder(path);
	if (path.find_last_of("\\") != path.length() && path.find_last_of("/") != path.length()){
		path.append('/');
	}

	bas.createFolder(path + "Source");
	bas.createFolder(path + "Include");

	String buildPath = path + "Build";
	bas.createFolder(buildPath);
	buildPath += "/VS10";
	bas.createFolder(buildPath);
	buildPath.append('/');

	if (!bas.fileExists(buildPath + name + ".sln"))
		writeFile(buildPath + name + ".sln", sln);
	if (!bas.fileExists(buildPath + name + ".vcxproj"))
		writeFile(buildPath + name + ".vcxproj", vcxproj);
	if (!bas.fileExists(path + "Source/" + name + ".cpp"))
		writeFile(path + "Source/" + name + ".cpp", appC);
	if (!bas.fileExists(buildPath + "main.cpp"))
		writeFile(buildPath + "main.cpp", main);
	if (!bas.fileExists(path + "Include/" + name + ".h"))
		writeFile(path + "Include/" + name + ".h", appH);

}

void PolycodeProjectGenerator::generateVS12(){
	OSFILE *slnF = bas.open("Projects/PolycodeProject12.sln", "r");
	OSFILE *vcxprojF = bas.open("Projects/PolycodeProject12.vcxproj", "r");
	OSFILE *mainF = bas.open("Projects/Source/mainWin.cpp", "r");
	OSFILE *appCF = bas.open("Projects/Source/PolycodeProject.cpp", "r");
	OSFILE *appHF = bas.open("Projects/Include/PolycodeProject.h", "r");

	String sln = loadFile(slnF), vcxproj = loadFile(vcxprojF), main = loadFile(mainF), appC = loadFile(appCF), appH = loadFile(appHF);

	bas.close(slnF);
	bas.close(vcxprojF);
	bas.close(mainF);
	bas.close(appCF);
	bas.close(appHF);

	String modulesInc, modulesLibD, modulesLibs, modulesLibsD, modulesIncH, extraCopy;

	if (physics2D->isChecked() || physics3D->isChecked() || ui->isChecked()){
		modulesInc = "Framework/Modules/include;";
		modulesLibD = "Framework/Modules/lib;";
		if (physics2D->isChecked() || physics3D->isChecked()){
			modulesInc += "Framework/Modules/Dependencies/include;";
			modulesLibD += "Framework/Modules/Dependencies/lib;";
			if (physics2D->isChecked()){
				modulesLibs = "Polycode2DPhysics.lib;Box2D.lib;";
				modulesLibsD = "Polycode2DPhysics_d.lib;Box2D_d.lib;";
				modulesIncH = "#include \"Physics2D.h\"\n";
			}
			if (physics3D->isChecked()){
				modulesInc += "Modules/Dependencies/include/bullet;";
				modulesLibs += "Polycode3DPhysics.lib;BulletDynamics.lib;BulletCollision.lib;LinearMath.lib;";
				modulesLibsD += "Polycode3DPhysics_d.lib;BulletDynamics_d.lib;BulletCollision_d.lib;LinearMath_d.lib;";
				modulesIncH += "#include \"Physics3D.h\"\n";
			}
		}
		if (ui->isChecked()){
			modulesLibs += "PolycodeUI.lib;";
			modulesLibsD += "PolycodeUI_d.lib;";
			modulesIncH += "#include \"PolycodeUI.h\"\n";
			extraCopy = "if not exist \"$(ProjectDir)UIThemes.pak\" copy \"$(PolycodeDir)Modules/Assets/UIThemes.pak\" \"$(ProjectDir)\"\n";
		}
	}

	String name = projName->getText();

	sln = sln.replace("--ProjectName--", name);

	vcxproj = vcxproj.replace("--ProjectName--", name);
	vcxproj = vcxproj.replace("--ModulesIncDir--", modulesInc);
	vcxproj = vcxproj.replace("--ModulesLibDir--", modulesLibD);
	vcxproj = vcxproj.replace("--ModulesDebug--", modulesLibsD);
	vcxproj = vcxproj.replace("--Modules--", modulesLibs);
	vcxproj = vcxproj.replace("--ExtraCopy--", extraCopy);

	main = main.replace("--ProjectName--", name);
	appC = appC.replace("--ProjectName--", name);
	appH = appH.replace("--ProjectName--", name);
	appH = appH.replace("--ModulesInc--", modulesIncH);

	String path = projPos->getText();

	if (!bas.isFolder(path))
		bas.createFolder(path);
	if (path.find_last_of("\\") != path.length() && path.find_last_of("/") != path.length()){
		path.append('/');
	}

	bas.createFolder(path + "Source");
	bas.createFolder(path + "Include");

	String buildPath = path + "Build";
	bas.createFolder(buildPath);
	buildPath += "/VS12";
	bas.createFolder(buildPath);
	buildPath.append('/');

	if (!bas.fileExists(buildPath + name + ".sln"))
		writeFile(buildPath + name + ".sln", sln);
	if (!bas.fileExists(buildPath + name + ".vcxproj"))
		writeFile(buildPath + name + ".vcxproj", vcxproj);
	if (!bas.fileExists(path + "Source/" + name + ".cpp"))
		writeFile(path + "Source/" + name + ".cpp", appC);
	if (!bas.fileExists(buildPath + "main.cpp"))
		writeFile(buildPath + "main.cpp", main);
	if (!bas.fileExists(path + "Include/" + name + ".h"))
		writeFile(path + "Include/" + name + ".h", appH);

}

void PolycodeProjectGenerator::generateXcode(){

}

void PolycodeProjectGenerator::generateMakefile(){
	OSFILE *makeF = bas.open("Projects/Makefile", "r");
	OSFILE *mainF = bas.open("Projects/Source/mainMakefile.cpp", "r");
	OSFILE *appCF = bas.open("Projects/Source/PolycodeProject.cpp", "r");
	OSFILE *appHF = bas.open("Projects/Include/PolycodeProject.h", "r");

	String make = loadFile(makeF), main = loadFile(mainF), appC = loadFile(appCF), appH = loadFile(appHF);

	bas.close(makeF);
	bas.close(mainF);
	bas.close(appCF);
	bas.close(appHF);

	String modulesInc, modulesLibs, modulesIncH, extraCopy;

	if (physics2D->isChecked() || physics3D->isChecked() || ui->isChecked()){
		modulesInc = "-IFramework/Modules/include ";
		if (physics2D->isChecked() || physics3D->isChecked()){
			modulesInc += "-IFramework/Modules/Dependencies/include ";
			if (physics2D->isChecked()){
				modulesLibs = "Framework/Modules/lib/libPolycode2DPhysics.a Framework/Modules/Dependencies/lib/libBox2D.a";
				modulesIncH = "#include \"Physics2D.h\"\n";
			}
			if (physics3D->isChecked()){
				modulesInc += "-IFramework/Modules/Dependencies/include/bullet ";
				modulesLibs += " Framework/Modules/lib/libPolycode3DPhysics.a Framework/Modules/Dependencies/lib/libBulletDynamics.a Framework/Modules/Dependencies/lib/libBulletCollision.a Framework/Modules/Dependencies/lib/libLinearMath.a";
				modulesIncH += "#include \"Physics3D.h\"\n";
			}
		}
		if (ui->isChecked()){
			modulesLibs += " Framework/Modules/lib/libPolycodeUI.a";
			modulesIncH += "#include \"PolycodeUI.h\"\n";
			extraCopy = "cp Framework/Modules/Assets/UIThemes.pak .";
		}
	}

	String name = projName->getText();

	make = make.replace("--ProjectName--", name);
	make = make.replace("--ModulesIncDir--", modulesInc);
	make = make.replace("--Modules--", modulesLibs);
	make = make.replace("--ExtraCopy--", extraCopy);

	main = main.replace("--ProjectName--", name);
	appC = appC.replace("--ProjectName--", name);
	appH = appH.replace("--ProjectName--", name);
	appH = appH.replace("--ModulesInc--", modulesIncH);


	String path = projPos->getText();

	if (!bas.isFolder(path))
		bas.createFolder(path);
	if (path.find_last_of("\\") != path.length() && path.find_last_of("/") != path.length()){
		path.append('/');
	}

	bas.createFolder(path + "Source");
	bas.createFolder(path + "Include");

	String buildPath = path + "Build";
	bas.createFolder(buildPath);
	buildPath += "/Linux";
	bas.createFolder(buildPath);
	buildPath.append('/');

	if (!bas.fileExists(buildPath + "Makefile"))
		writeFile(buildPath + "Makefile", make);
	if (!bas.fileExists(path + "Source/" + name + ".cpp"))
		writeFile(path + "Source/" + name + ".cpp", appC);
	if (!bas.fileExists(buildPath + "main.cpp"))
		writeFile(buildPath + "main.cpp", main);
	if (!bas.fileExists(path + "Include/" + name + ".h"))
		writeFile(path + "Include/" + name + ".h", appH);

}

void PolycodeProjectGenerator::generateCMake(){

}

String PolycodeProjectGenerator::loadFile(OSFILE *f){
	char* buf = (char*)malloc(1000 * sizeof(char));
	String ret;
	size_t read;
	while ((read = bas.read(buf, sizeof(char), 999, f)) > 0){
		buf[read] = '\0';
		ret += String(buf);
	}
	return ret;
}

void PolycodeProjectGenerator::writeFile(String f, String s){
	OSFILE* file = bas.open(f, "w");
	bas.write(s.c_str(), sizeof(char), s.length(), file);
	bas.close(file);
}
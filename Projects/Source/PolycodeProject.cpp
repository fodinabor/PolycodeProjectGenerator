#include "--ProjectName--.h"

--ProjectName--::--ProjectName--(PolycodeView *view) {
	core = new POLYCODE_CORE(view, 640,480,false, false, 0, 0,60);	  
	CoreServices::getInstance()->getResourceManager()->addArchive("default.pak");
	CoreServices::getInstance()->getResourceManager()->addDirResource("default", false);

	// Write your code here
}
--ProjectName--::~--ProjectName--() {
    
}

bool --ProjectName--::Update() {
	return core->updateAndRender();
}
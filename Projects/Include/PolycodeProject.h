#include "PolycodeView.h"
#include "Polycode.h"
--ModulesInc--

using namespace Polycode;

class --ProjectName-- {
public:
	--ProjectName--(PolycodeView *view);
	~--ProjectName--();
    
    bool Update();
    
private:
    Core *core;
};
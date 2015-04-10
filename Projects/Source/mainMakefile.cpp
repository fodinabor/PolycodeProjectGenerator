#include "Polycode.h"
#include "PolycodeView.h"
#include "--ProjectName--.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("--ProjectName--");
	--ProjectName-- *app = new --ProjectName--(view);
	while(app->Update()) {}
	return 0;
}

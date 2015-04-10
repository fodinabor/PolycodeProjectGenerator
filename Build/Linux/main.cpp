#include "Polycode.h"
#include "PolycodeView.h"
#include "PolycodeProjectGenerator.h"

int main(int argc, char *argv[]) {
	PolycodeView *view = new PolycodeView("Hello Polycode!");
	PolycodeProjectGenerator *app = new PolycodeProjectGenerator(view);
	while(app->Update()) {}
	return 0;
}

//#import <Foundation/Foundation.h>

#include "os_core_app_shell.h"
#include "GLApp.h"

int main (int argc, char **argv) {
    //BUNDLE:
    gDirBundle = "/Users/zk9gy1t/Documents/[Proto]/Roxus/[[Grid]]/Assets/";
    gDirDocuments = "/Users/zk9gy1t/Documents/[Proto]/Roxus/[[Grid]]/Data/";
    gDirExport = "/Users/zk9gy1t/Desktop/[[[Export]]]/";
    

    gDirBundle = "/Users/nraptis/Desktop/[[[[GitHub]]]]/Roxus/[[Grid]]/Assets/";
    gDirDocuments = "/Users/nraptis/Desktop/[[[[GitHub]]]]/Roxus/[[Grid]]/Data/";
    //gDirExport = "/Users/nraptis/Desktop/[[[Export]]]/";

    gApp = new GLApp();
    return os_core_main(argc, argv);
}





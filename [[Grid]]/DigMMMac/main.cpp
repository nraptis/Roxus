//#import <Foundation/Foundation.h>

#include "os_core_app_shell.h"
#include "GLApp.h"

int main (int argc, char **argv)
{
    
    //gDirBundle = "/Users/nraptis/Desktop/Darkswarm/(J2MAC)/Assets/";
    //gDirDocuments = "/Users/nraptis/Desktop/Darkswarm/(J2MAC)/Data/";
    
    //BUNDLE:
    gDirBundle = "/Users/zk9gy1t/Documents/[Proto]/Roxus/[[Grid]]/Assets/";
    gDirDocuments = "/Users/zk9gy1t/Documents/[Proto]/Roxus/[[Grid]]/Data/";
    
    //gDirBundle = "/Users/nraptis/Desktop/[[[[GitHub]]]]/Roxus/[[Grid]]/Assets/";
    //gDirDocuments = "/Users/nraptis/Desktop/[[[[GitHub]]]]/Roxus/[[Grid]]/Data/";

    gApp = new GLApp();
    return os_core_main(argc, argv);
}




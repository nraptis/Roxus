//
// Copyright 2011 Tero Saarni
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

//Is "output" even the right word for this? It's the thing that talks TO the OS,
//It will eventually be responsible for loading images, sounds, and saving files...

#ifndef APP_OUTLETS_H
#define APP_OUTLETS_H

#include "FString.h"
#include "FList.h"

#define Log printf

bool os_fileExists(const char *pFilePath);
bool os_fileExists(FString pFilePath);

unsigned long os_system_time();

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength);
bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength);

void os_load_image_to_buffer(char *pFile, unsigned int *pData);
unsigned int *os_load_image(char *pFile, int &pWidth, int &pHeight);

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight);
void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality);
void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight);


void os_load_image_to_buffer(char *pFile, unsigned int *pData);
unsigned int *os_load_image(char *pFile, int &pWidth, int &pHeight);

bool os_createDirectory(const char *pDirectory);
//FString os_getTestDirectory();
void os_getTestDirectory(FString *pString);

void os_getFilesInDirectory(const char *pFilePath, FList *pList);
void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList);

void os_getAllResources(const char *pFilePath, FList *pList);


#endif // JNIAPI_H

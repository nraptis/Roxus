#ifndef APP_OUTLETS_WIN_H
#define APP_OUTLETS_WIN_H

#define Log printf

class FList;
class FString;
//class UIImage;

bool os_fileExists(const char *pFilePath);
//bool os_fileExists(FString pFilePath);

unsigned long os_system_time();

unsigned char *os_read_file(const char *pFileName, unsigned int &pLength);
bool os_write_file(const char *pFileName, unsigned char *pData, unsigned int pLength);

void os_load_image_to_buffer(char *pFile, unsigned int *pData);
unsigned int *os_load_image(char *pFile, int &pWidth, int &pHeight);

bool os_createDirectory(const char *pDirectory);
//FString os_getTestDirectory();
void os_getTestDirectory(FString *pString);

void os_getFilesInDirectory(const char *pFilePath, FList *pList);
void os_getFilesInDirectoryRecursive(const char *pFilePath, FList *pList);

void os_getAllResources(const char *pFilePath, FList *pList);

void os_exportPNGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight);
void os_exportJPEGImage(unsigned int *pData, const char *pFilePath, int pWidth, int pHeight, float pQuality);
void os_exportToPhotoLibrary(unsigned int *pData, int pWidth, int pHeight);


#endif // JNIAPI_H

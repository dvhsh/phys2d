#include "component.h"

#define MAX_PATH_LENGTH 1024
static char g_executablePath[MAX_PATH_LENGTH] = {0};

bool InitializeResources(void) {
    #if PLATFORM == PLATFORM_MACOS_INTEL || PLATFORM == PLATFORM_MACOS_ARM || PLATFORM == PLATFORM_LINUX
        char path[MAX_PATH_LENGTH];
        uint32_t size = sizeof(path);
        if (_NSGetExecutablePath(path, &size) != 0) {
            printf("Failed to get executable path\n");
            return false;
        }
        
        char resolved[MAX_PATH_LENGTH];
        if (realpath(path, resolved) == NULL) {
            printf("Failed to resolve path: %s\n", path);
            return false;
        }
        
        strncpy(g_executablePath, dirname(resolved), MAX_PATH_LENGTH - 1);
        printf("Resource path initialized: %s\n", g_executablePath);
        return true;
    #elif PLATFORM == PLATFORM_WINDOWS32 || PLATFORM == PLATFORM_WINDOWS64
        if (GetModuleFileName(NULL, g_executablePath, MAX_PATH_LENGTH) == 0) {
            printf("Failed to get executable path\n");
            return false;
        }
        
        char* last_slash = strrchr(g_executablePath, '\\');
        if (last_slash) *last_slash = '\0';
        
        printf("Resource path initialized: %s\n", g_executablePath);
        return true;
    #else
        printf("Unsupported platform\n");
        return false;
    #endif
}

void CleanupResources(void) {
    memset(g_executablePath, 0, MAX_PATH_LENGTH);
}

char* GetResourcePath(const char* resourcePath) {
    static char fullPath[MAX_PATH_LENGTH];
    snprintf(fullPath, MAX_PATH_LENGTH, "%s/resources/%s", g_executablePath, resourcePath);
    return fullPath;
}

// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Custom injected code entry point

#include "pch-il2cpp.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "il2cpp-appdata.h"
#include "helpers.h"
#include "GUIHook.h"

using namespace app;

// Set the name of your log file here
extern const LPCWSTR LOG_FILE = L"il2cpp-log.txt";

// Custom injected code entry point
void Run()
{
    // If you would like to write to a log file, specify the name above and use il2cppi_log_write()
    // il2cppi_log_write("Startup");

    // If you would like to output to a new console window, use il2cppi_new_console() to open one and redirect stdout

    il2cppi_new_console();
   
    // get player pointer

    GameObject* player = PlayerFinder_getPlayer(nullptr);
    std::cout << "Finding player ?? " << player << std::endl; 

    // NOTE TO SELF:
    /*
        In the C# code for the project the typical call for getting a component on a game object looks something like this:
                GameObject.getComponent<ComponentType>()

        It seems that the way IL2CPP handles generic functions such as this is by condensing them into a series of functions numbered with a return type of the specific component.

        For example, in Last Epoch we have the process of getting a players health that looks like this :
        player.GetComponent<PlayerHealth>();

        This is transformed into:
        GameoObject_GetComponent_185(playerObject, *GameObject_GetComponent_185__MethodInfo);
        
        As this 185th version of getComponent is associated with the PlayerHealth component.

        */
    /**
    PlayerHealth* phealth = GameObject_GetComponent_185(player, *GameObject_GetComponent_185__MethodInfo);
  
    std::cout << "Can I get hurt = " << PlayerHealth_isDamageable(phealth, nullptr) << std::endl;

    BaseHealth* bhealth = GameObject_GetComponent_198(player, *GameObject_GetComponent_198__MethodInfo);

    bhealth->fields.damageable = false;

    std::cout << "Changed baseHealth damageability..." << std::endl;
    std::cout << "Can I get hurt = " << PlayerHealth_isDamageable(phealth, nullptr) << std::endl;
    */

    std::cout << "Initalizing gui hook..." << std::endl;
    GUIHookInit();
}
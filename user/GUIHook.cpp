#include "pch-il2cpp.h"
#include "GUIHook.h"
#include "errors.h"
#include "state.h"
#include "helpers.h"
#include "utility.h"

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
using namespace app;

/*
void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}
*/
/*
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
*/

LRESULT WINAPI hkWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetAsyncKeyState(VK_INSERT) & 0x0001)
	{
		std::cout << "Pressed Insert" << std::endl;
		GUIState::showMenu = !GUIState::showMenu;
	}

	if (GUIState::showMenu)
	{
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
	}
	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}


void DrawMenu()
{
	auto _player = getPlayer();

	if (ImGui::CollapsingHeader("Player"))
	{
		ImGui::Separator();


		if (!_player)
		{
			ImGui::Text("No player found.");
		}
		else
		{
			auto canDamage = getDamageable(_player) ? "Is Damageable : True" : "Is Damageable : False";
			ImGui::Text(canDamage);
			auto baseHealth = getBaseHealth(_player);
			baseHealth->fields.damageable = !GUIState::godMode;
			ImGui::Checkbox("GOD MODE", &GUIState::godMode);
		}

		
		if (_player && ImGui::CollapsingHeader("Stats"))
		{
			ImGui::Separator();
			
			// MoveSpeed Section
			Stats_Stat* ms = getMovespeed(_player);
			if (ms)
				ImGui::SliderFloat("move speed", &ms->fields.increasedValue, 0, 5);
			else
				ImGui::Text("Could not find movespeed pointer");
			
			ImGui::Separator();

			// Attackspeed Section
			Stats_Stat* as = getAttackSpeed(_player);
			if (as)
				ImGui::SliderFloat("attack speed", &as->fields.increasedValue, 0, 5);
			else
				ImGui::Text("Could not find AttackSpeed pointer");
			ImGui::Separator();

			// CastSpeed Section
			Stats_Stat* cs = getCastSpeed(_player);
			if (cs)
				ImGui::SliderFloat("cast speed", &cs->fields.increasedValue, 0, 5);
			else
				ImGui::Text("Could not find CastSpeed pointer");
			ImGui::Separator();
			
			// ManaRegen Section
			Stats_Stat* mr = getManaRegen(_player);
			if (mr)
				ImGui::SliderFloat("mana regen", &mr->fields.increasedValue, 0, 5);
			else
				ImGui::Text("Could not find Mana Regen pointer");
			ImGui::Separator();

			// DAMAGE Section
			Stats_Stat* dmg = getDamage(_player);
			if (dmg)
			{
				ImGui::SliderFloat("added damage", &dmg->fields.addedValue, 0, 1000);
				ImGui::SliderFloat("increased damage", &dmg->fields.increasedValue, 0, 10);

			}
			else
				ImGui::Text("Could not find Damage pointer");
			ImGui::Separator();

			}
		}

	if (ImGui::CollapsingHeader("Extras"))
	{


		if (ImGui::Button("Toggle Fracutring"))
		{
			std::cout << "Attempting to toggle fracturing" << std::endl;
			toggleFracture();
		}

		if (ImGui::Button("Generate crafting mats"))
		{
			genCraftingMats();
		}
	}
		

}


bool init = false;
HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
			//InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}

	if (GUIState::showMenu)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("YUNG DOODOO H4CKP0CH 1.0");

		// Draw Menu
		DrawMenu();


		ImGui::End();

		ImGui::Render();
		pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	return oPresent(pSwapChain, SyncInterval, Flags);
}




int GUIHookInit()
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)&oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}


DWORD WINAPI MainThread(LPVOID lpReserved)
{

	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}

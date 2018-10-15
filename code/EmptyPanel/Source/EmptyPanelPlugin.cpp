//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPlugin.cpp $
//
//  $Revision: #2 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

/*
========================================================================================
Reza Adhitya Saputra
radhitya@uwaterloo.ca
========================================================================================
*/

//sAIUser->MessageAlert(ai::UnicodeString("Your message here"));


/*
========================================================================================
Some important functions:
	GoMenuItem
	StartupPlugin
	ShutdownPlugin
========================================================================================
*/

#ifdef MAC_ENV
#include <Cocoa/Cocoa.h>
#include "CalcController.h"
#include "BarController.h"
#endif

#ifdef WIN_ENV
#include <WindowsX.h>
#include "CustomEdit.h"
#endif

#include "IllustratorSDK.h"
#include "EmptyPanelPlugin.h"
#include "EmptyPanelPluginSuites.h"
#include "EmptyPanelID.h"

#include "AVector.h"
#include "APath.h"
#include "PathIO.h"

#include <sstream>


/*#define bufMax 1024
#define controlBarHeight	40
#define controlBarWidth		800
#define controlBarWidthMin	50
#define controlBarWidthMax	1200
#define CHECK_ERROR  if (error) {return error;}*/

extern "C" SPBasicSuite*  sSPBasic;

#ifdef MAC_ENV
NSView* nibView = nil;
NSView* controlPanelNibView = nil;
#endif

/*
================================================================================
================================================================================
*/
// split string
std::vector<std::string>& Split(const std::string &s, char delim, std::vector<std::string> &elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
		{ elems.push_back(item); }
	return elems;
}

/*
================================================================================
================================================================================
*/
// split string
std::vector<std::string> Split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	Split(s, delim, elems);
	return elems;
}

Plugin *AllocatePlugin(SPPluginRef pluginRef)
{
	return new EmptyPanelPlugin(pluginRef);
}

void FixupReload(Plugin *plugin)
{
	EmptyPanelPlugin::FixupVTable( static_cast<EmptyPanelPlugin*>( plugin ) );
}

EmptyPanelPlugin::EmptyPanelPlugin(SPPluginRef pluginRef)
	: Plugin(pluginRef),
	_pathIO(0)
	//fPanel(NULL),
	//hDlg(NULL)
{
	/*strncpy(fPluginName, kEmptyPanelPluginName, kMaxStringLength);
	#ifdef WIN_ENV
		fDefaultWindProc = NULL;
	#endif*/
}

/*static void flyoutMenuPreVisFunc(AIPanelRef inPanel)
{
	sAIUser->MessageAlert(ai::UnicodeString("pre visiblity"));
}*/

/*void PanelFlyoutMenuProc(AIPanelRef inPanel, ai::uint32 itemID)
{
	AIErr error = kNoErr;
	AIPanelFlyoutMenuRef flyoutMenu = NULL;
	error = sAIPanel->GetFlyoutMenu(inPanel, flyoutMenu);
	AIPanelFlyoutMenuItemMark currentItemMark;
	switch(itemID)
	{
	case 1:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 1 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 1 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_BULLET);
		break;
	case 2:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 2 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 2 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_CHECK);
		break;
	case 3:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 3 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 3 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_DASH);
		break;
	}
}*/

/*void PanelVisibilityChangedNotifyProc(AIPanelRef inPanel, AIBoolean isVisible)
{
	AIPanelUserData ud = NULL;
	sAIPanel->GetUserData(inPanel, ud);
	EmptyPanelPlugin* sPlugin = reinterpret_cast<EmptyPanelPlugin*>(ud);
	sPlugin->UpdateMenu(isVisible, PANEL);
}*/

/*void PanelSizeChangedNotifyProc(AIPanelRef inPanel)
{
#ifdef MAC_ENV
	AISize panelSize= {0,0};
	AIErr error = kNoErr;
	
	error = sAIPanel->GetSize(inPanel, panelSize);
	
	if(!error)
	{
		NSRect newRect = NSMakeRect(0,0,panelSize.width,panelSize.height);
		[nibView setFrame:newRect];
	}
#endif
}*/	

/*void PanelStateChangedNotifyProc(AIPanelRef inPanel, ai::int16 newState)
{
	AIErr err = kNoErr;
	AISize prefSize;
	switch(newState)
	{
	case 1:
		prefSize.height = prefSize.width = 300;
		break;
	case 2:
		prefSize.height = prefSize.width = 500;
		break;
	case 3:
		prefSize.height = prefSize.width = 700;
		break;
	}
	
	err = sAIPanel->SetPreferredSizes(inPanel, prefSize);
}*/

/*void PanelClosedNotifyProc(AIPanelRef inPanel)
{
	sAIUser->MessageAlert(ai::UnicodeString("Panel Closed !!! Too bad."));
}*/

//--------------------------------------------------------------------
//Callback Procedures for Control Bar
//--------------------------------------------------------------------
/*void ControlBarVisibilityChangedNotifyProc(AIControlBarRef inControlBar, AIBoolean isVisible)
{
	AIErr err = kNoErr;

	AIControlBarUserData userData = NULL;
	err = sAIControlBar->GetUserData(inControlBar, userData);
	if(err == kNoErr && userData)
	{
		EmptyPanelPlugin* plugin = reinterpret_cast<EmptyPanelPlugin*>(userData);
		plugin->UpdateMenu(isVisible, CTRL_BAR);
	}
}*/

/*void ControlBarSizeChangedNotifyProc(AIControlBarRef inControlBar)
{

}*/

// --------------------------------------------------------------------
// Called when plugin is initially loaded
// --------------------------------------------------------------------
ASErr EmptyPanelPlugin::StartupPlugin(SPInterfaceMessage *message)
{
	AIErr error = kNoErr;
	
	// Call base class routine
	error = Plugin::StartupPlugin(message);
	if (error) { return error; }

	AINotifierHandle appShutDownNotifier;
	error = sAINotifier->AddNotifier(fPluginRef, "AI Application Shutdown Notifier", kAIApplicationShutdownNotifier, &appShutDownNotifier);
	if (error) { return error; }

	// Add menu item
	error = sAIMenu->AddMenuItemZString(fPluginRef, "[Convert to Text File]", kOtherPalettesMenuGroup, ZREF("[Convert to Text File]"), kMenuItemNoOptions, &_convertMenuItemHandle);
	if (error) { return error; }	

	// Add menu item
	//error = sAIMenu->AddMenuItemZString(fPluginRef, "[Pattern Brush Magic]", kOtherPalettesMenuGroup, ZREF("[Pattern Brush Magic]"), kMenuItemNoOptions, &_patternBrushMenuItemHandle);
	//if (error) { return error; }
	
	/*AIErr error = kNoErr;
	// Add About Plugins menu item for this plug-in.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"EmptyPanel...", 
				&fAboutPluginMenu);

	if (error)
		return error;*/

	// Add menu item
	/*error = sAIMenu->AddMenuItemZString(fPluginRef, "Third Party Panel", kOtherPalettesMenuGroup, ZREF("Third Party Panel"),
										kMenuItemNoOptions, &fEmptyPanelPanelMenuItemHandle);
	if (error)
		return error;

	fPanelFlyoutMenu = NULL;
	error = sAIPanelFlyoutMenu->Create(fPanelFlyoutMenu);
	if (error)
		return error;

	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 1, ai::UnicodeString("First Item"));
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 3, ai::UnicodeString("Third Item"));
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->InsertItem(fPanelFlyoutMenu, 3, 2, ai::UnicodeString("Second Item"));
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->InsertSeparator(fPanelFlyoutMenu, 3, 5);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 4, ai::UnicodeString("Fourth Item"));
    CHECK_ERROR
    
	error = sAIPanelFlyoutMenu->SetItemEnabled(fPanelFlyoutMenu, 4, false);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 1 , kAIPanelFlyoutMenuItemMark_BULLET);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 2 , kAIPanelFlyoutMenuItemMark_CHECK);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 3 , kAIPanelFlyoutMenuItemMark_DASH);
	CHECK_ERROR
    
	AISize pnSize = {240, 320};
	error = sAIPanel->Create(fPluginRef, ai::UnicodeString("Third Party Panel"), ai::UnicodeString("Third Party Panel"), 3, pnSize, true, fPanelFlyoutMenu, this, fPanel);
	CHECK_ERROR

	AISize minSize = {50, 50};
	AISize maxSize = {800, 800};
	AISize prefConstSize = {100, 100};
	AISize prefUnconstSize = {600, 600};

	error = sAIPanel->SetSizes(fPanel, minSize, prefUnconstSize, prefConstSize, maxSize);
	CHECK_ERROR
	error = sAIPanel->Show(fPanel, true);
      CHECK_ERROR
	error = sAIPanel->SetFlyoutMenuPreVisibilityProc(fPanel, flyoutMenuPreVisFunc);
      CHECK_ERROR
	error = sAIPanel->SetFlyoutMenuProc(fPanel, PanelFlyoutMenuProc);
      CHECK_ERROR
	error = sAIPanel->SetVisibilityChangedNotifyProc(fPanel, PanelVisibilityChangedNotifyProc);
      CHECK_ERROR
	error = sAIPanel->SetSizeChangedNotifyProc(fPanel, PanelSizeChangedNotifyProc);
      CHECK_ERROR
	error = sAIPanel->SetStateChangedNotifyProc(fPanel, PanelStateChangedNotifyProc);
      CHECK_ERROR
	error = sAIPanel->SetClosedNotifyProc(fPanel, PanelClosedNotifyProc);
	CHECK_ERROR
    
	error = SetIcon();
      CHECK_ERROR

	error = AddWidgets();
	
	//Add Menu Item for Control Bar
	if(!error)
		error = sAIMenu->AddMenuItemZString(fPluginRef, "Third Party Control Bar", kOtherPalettesMenuGroup, ZREF("Third Party Control Bar"),
											kMenuItemNoOptions, &fEmptyPanelControlBarMenuItemHandle);
	
	//Create Control Bar
	AISize sizeControlBar = {controlBarWidth, controlBarHeight};
	if(!error)
		error = sAIControlBar->Create(fPluginRef, sizeControlBar, controlBarWidthMin, controlBarWidthMax,NULL,fControlBar);
	if(!error)
		error = sAIControlBar->SetUserData(fControlBar, this);
	
	//Set Callbacks
	if(!error)
		error = sAIControlBar->SetVisibilityChangedNotifyProc(fControlBar, ControlBarVisibilityChangedNotifyProc);
	if(!error)
		error = sAIControlBar->SetSizeChangedNotifyProc(fControlBar, ControlBarSizeChangedNotifyProc);
	
	//Add Different Widgets to Control Bar
	if(!error)
		AddWidgetsToControlBar();*/
	
	return error;
}

/*
AIErr EmptyPanelPlugin::AddWidgets()
{
	AIErr error = kNoErr;
	AIPanelPlatformWindow hDlg = NULL;
	error = sAIPanel->GetPlatformWindow(fPanel, hDlg);

#ifdef WIN_ENV

	HWND hwndXStaticText = CreateWindowEx( 
		0, L"STATIC",   // Predefined class; Unicode assumed. 
		L"X",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		10,         // x position. 
		40,         // y position. 
		45,        // width.
		20,        // height.
		hDlg,       // Parent window.
		NULL,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	fHWndXEdit = CustomEdit::CreateCustomEdit( 
		0, //L"EDIT", // Predefined class; Unicode assumed. 
		L"",		//  
		WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER | WS_TABSTOP,  // Styles. 
		60,         // x position. 
		40,         // y position. 
		100,        // width.
		20,         // height.
		hDlg,       // Parent window.
		(HMENU) ID_XEdit,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	Edit_LimitText(fHWndXEdit, 9);
	
	HWND hwndYStaticText = CreateWindowEx( 
		0, L"STATIC",   // Predefined class; Unicode assumed. 
		L"Y",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		10,         // x position. 
		70,         // y position. 
		45,         // width.
		20,         // height.
		hDlg,       // Parent window.
		NULL,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	fHwndYEdit = CustomEdit::CreateCustomEdit( 
		0, //L"EDIT",   // Predefined class; Unicode assumed. 
		L"",		//  
		WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER | WS_TABSTOP,  // Styles. 
		60,         // x position. 
		70,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_YEdit,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	Edit_LimitText(fHwndYEdit, 9);

	HWND hwndSumStaticText = CreateWindowEx( 
		0, L"STATIC",   // Predefined class; Unicode assumed. 
		L"Sum",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		10,         // x position. 
		100,         // y position. 
		45,        // width.
		20,        // height.
		hDlg,       // Parent window.
		NULL,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	fHwndResultEdit = CustomEdit::CreateCustomEdit( 
		0, //L"EDIT",   // Predefined class; Unicode assumed. 
		L"",		//  
		WS_VISIBLE | WS_CHILD | ES_RIGHT | ES_NUMBER | WS_TABSTOP,  // Styles. 
		60,         // x position. 
		100,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_ResultEdit,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.


	HWND HwndButtonAdd = CreateWindowEx( 
		0, L"BUTTON",   // Predefined class; Unicode assumed. 
		L"Add",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		30,         // x position. 
		130,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_ButtonAdd,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	HWND HwndButtonShow = CreateWindowEx( 
		0, L"BUTTON",   // Predefined class; Unicode assumed. 
		L"Show Dialog",		//  
		WS_VISIBLE | WS_CHILD | ES_LEFT,  // Styles. 
		30,         // x position. 
		160,         // y position. 
		100,        // width.
		20,        // height.
		hDlg,       // Parent window.
		(HMENU) ID_ButtonShow,
		(HINSTANCE)GetWindowLongPtr(hDlg, GWLP_HINSTANCE), 
		NULL);      // Pointer not needed.

	SendMessage(fHWndXEdit, (UINT) WM_SETTEXT, 0, (LPARAM)L"50"); 

	SendMessage(fHwndYEdit, (UINT) WM_SETTEXT, 0, (LPARAM)L"50");

	SendMessage(fHwndResultEdit, (UINT) WM_SETTEXT, 0, (LPARAM)L"100"); 

	::SetPropA(hDlg, "TPNL", this);
	fDefaultWindProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hDlg, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(EmptyPanelPlugin::NewWindowProc)));
#endif
	
#ifdef MAC_ENV
	// Get our own bundle
	NSBundle* bundle = [NSBundle bundleWithIdentifier:@"com.adobe.illustrator.plugins.EmptyPanel"];
	//load the nib file
	CalcController* calculator = [CalcController alloc];
	[calculator initWithNibName:@"View" bundle:bundle];
	//set panel to be our nibs view
	NSView* newView = [calculator view];
	[hDlg setFrame:[newView frame]];
	[hDlg addSubview:newView];
	
#endif
	return error;
}
*/

ASErr EmptyPanelPlugin::ShutdownPlugin(SPInterfaceMessage *message)
{
	AIErr error = kNoErr;

	/*if(fPanel)
	{
		error = sAIPanel->Destroy(fPanel);
		fPanel = NULL;
	}
	if(fPanelFlyoutMenu)
	{
		error = sAIPanelFlyoutMenu->Destroy(fPanelFlyoutMenu);
		fPanelFlyoutMenu = NULL;
	}*/

	if (_pathIO) { delete _pathIO; }

	return kNoErr;
}

ASErr EmptyPanelPlugin::GoMenuItem(AIMenuMessage *message)
{
	ASErr error = kNoErr;
	if (message->menuItem == _convertMenuItemHandle)
	{
		// ===== PARSE !!! ===== 
		ParseDocument();

		ai::FilePath file_name_spec;
		sAIDocument->GetDocumentFileSpecification(file_name_spec);
		//ai::UnicodeString unicode_file_name = file_name_spec.GetFileName();
		//file_name_spec.GetFullPath
		ai::UnicodeString unicode_file_name = file_name_spec.GetFullPath();
		std::string std_file_name = unicode_file_name.as_UTF8();

		//std::string full_file_path = "C:\\Users\\azer\\workspace\\Images\\" + std_file_name.substr(0, std_file_name.size() - 3) + ".path";
		std::string full_file_path = std_file_name.substr(0, std_file_name.size() - 3) + ".path";
		std::string file_name = std_file_name.substr(0, std_file_name.size() - 3) + ".path";

		// ===== EDIT MEEEE ===== 
		_pathIO->SaveRegions(this->_regions, full_file_path);

		_pathIO->LoadRegions(full_file_path);

		// =====  give a message ===== 
		ai::UnicodeString msg = unicode_file_name;
		msg.append(ai::UnicodeString(" ---> "));
		msg.append(ai::UnicodeString(file_name.c_str()));

		sAIUser->MessageAlert(msg);

	}
	//else if (message->menuItem == _patternBrushMenuItemHandle)
	//{
	//	//sAIUser->MessageAlert(ai::UnicodeString("Pattern Brush !"));

	//	AILayerHandle lHandler;
	//	sAILayer->GetFirstLayer(&lHandler);

	//	/*
	//	AIAPI AIErr(* AIArtSuite::SelectNamedArtOfLayer)(AILayerHandle layer, const ai::UnicodeString &name, AIBoolean matchWholeWord, AIBoolean caseSensitive)
	//	*/
	//	// select
	//	sAIArt->SelectNamedArtOfLayer(lHandler, ai::UnicodeString(""), false, false);

	//	/*ASErr error = kNoErr;
	//	// get current path style
	//	AIPathStyle pathStyle;
	//	AIPathStyleMap pathStyleMap;
	//	AIDictionaryRef advParams = NULL;
	//	error = sAIPathStyle->GetCurrentPathStyle(&pathStyle, &pathStyleMap, &advParams);
	//	error = sAIPathStyle->SetCurrentPathStyle(&pathStyle, &pathStyleMap, advParams);*/

	//	
	//	ParseLayerForPatternBrush(lHandler);
	//}

	return error;

	/*AIErr error = kNoErr;
	if (message->menuItem == fAboutPluginMenu) 
	{
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About EmptyPanel", kSDKDefAboutSDKCompanyPluginsAlertString);
	}
	else if (message->menuItem == fEmptyPanelPanelMenuItemHandle)
	{	
		if(fPanel)
		{
			AIBoolean isShown = false;
			error = sAIPanel->IsShown(fPanel, isShown);
			error = sAIPanel->Show(fPanel, !isShown);
		}
	}
	else if (message->menuItem == fEmptyPanelControlBarMenuItemHandle)
	{
		if(fControlBar)
		{
			AIBoolean isShown = false;
			error = sAIControlBar->IsShown(fControlBar,isShown);
			error = sAIControlBar->Show(fControlBar, !isShown);
		}
	}
	return error;*/
}

/*
========================================================================================
Rules:
- Should exactly has one layer (TBD...)
- All paths are in a single layer
========================================================================================
*/
ASErr EmptyPanelPlugin::ParseDocument()
{
	/* Clear data */
	//this->_paths.clear();
	this->_regions.clear();

	/* How many layers in this document? */
	ai::int32 layerCount = 0;
	sAILayer->CountLayers(&layerCount);
	int intLayerCount = layerCount;

	this->_regions = std::vector<ARegion>(layerCount);
	this->_layerCounter = 0;

	AILayerHandle lHandler;
	sAILayer->GetFirstLayer(&lHandler);

	do
	{
		ParseLayer(lHandler);
		sAILayer->GetNextLayer(lHandler, &lHandler);
		_layerCounter++;
	} while (lHandler != nil);

	/* shape layer */
	//AILayerHandle shapeLayerHandle = 0; 
	//sAILayer->GetLayerByTitle(&shapeLayerHandle, ai::UnicodeString("shape"));	
	//ParseShapeLayer(shapeLayerHandle);
	////AIArtHandle artHandle = 0; sAIArt->GetFirstArtOfLayer(shapeLayerHandle, &artHandle); /* Get the first art in this layer */	
	////ParseShapeLayer(artHandle); /* Fun things */

	/* field layer */
	//AILayerHandle fieldLayerHandle = 0; 
	//sAILayer->GetLayerByTitle(&fieldLayerHandle, ai::UnicodeString("field"));
	//ParseFieldLayer(fieldLayerHandle);

	return kNoErr;
}

void EmptyPanelPlugin::ParseLayerForPatternBrush(AILayerHandle layerHandle)
{
	AIArtHandle artHandle = nil;
	sAIArt->GetFirstArtOfLayer(layerHandle, &artHandle);

	// Get the first art element in the group
	AIArtHandle aArtHandle = nil;
	sAIArt->GetArtFirstChild(artHandle, &aArtHandle);

	do
	{
		/*
		AIAPI AIErr(* AIBeautifulStrokesSuite::GetArtPatternPaint)(ConstAIDictionaryRef params, 
																  AIPatternHandle &beginArt, 
																  AIPatternHandle &endArt, 
																  AIPatternHandle &sideArt, 
																  AIPatternHandle &insideCornerArt, 
																  AIPatternHandle &outsideCornerArt, 
																  RepeatedArtAdjustment &adjustment, 
																  AIReal &spacing, 
																  RepeatedArtCorner &insideAutoCornerOption, 
																  RepeatedArtCorner &outsideAutoCornerOption) 
		*/		
		/*AIDictionaryRef params = 0;
		AIPatternHandle beginArt = 0;
		AIPatternHandle endArt = 0;
		AIPatternHandle sideArt = 0;
		AIPatternHandle insideCornerArt = 0;
		AIPatternHandle outsideCornerArt = 0;
		RepeatedArtAdjustment adjustment;
		AIReal spacing = 0;
		RepeatedArtCorner insideAutoCornerOption;
		RepeatedArtCorner outsideAutoCornerOption;*/

		/*
		AIAPI AIErr(* AIBeautifulStrokesSuite::GetArtStrokeParams)(AIArtHandle art, 
																  AIDictionaryRef &paramDict, 
																  AIStrokeStyle *strokeStyle, 
																  AIBoolean *hasBrush, 
																  AIReal *scaleFactor, 
																  AIBoolean *canAccept) 
		*/


		/*
		AIDictionaryRef paramDict = 0;
		AIStrokeStyle strokeStyle;
		AIBoolean hasBrush;
		AIReal scaleFactor;
		AIBoolean canAccept;

		sAIBeautifulStrokes->GetArtStrokeParams(aArtHandle, paramDict, &strokeStyle, &hasBrush, &scaleFactor, &canAccept);
		*/

		// you can get witdh
		AIPathStyle style;
		sAIPathStyle->GetPathStyle(aArtHandle, &style);

		// art style?
		AIArtStyleHandle artStyle;
		sAIArtStyle->GetArtStyle(aArtHandle, &artStyle);
		

		sAIArt->GetArtSibling(aArtHandle, &aArtHandle);
	} while (aArtHandle != nil);
}

void EmptyPanelPlugin::GetForeBackColors(AIArtHandle artHandle, MyColor& foreColor, MyColor& backColor)
{
	AIPathStyle style;
	sAIPathStyle->GetPathStyle(artHandle, &style);

	//foreColor = MyColor(0, 0, 0);
	//backColor = MyColor(255, 255, 255);

	// fill
	if (style.fillPaint)
	{

		int r = style.fill.color.c.rgb.red * 255.0;
		int g = style.fill.color.c.rgb.green * 255.0;
		int b = style.fill.color.c.rgb.blue * 255.0;

		// =====  give a message =====
		//std::stringstream ss;
		//ss << "fill: " << r << "/" << g << "/" << b;
		//ai::UnicodeString msg;
		//msg.append(ai::UnicodeString(ss.str()));
		//msg.append(ai::UnicodeString("Filled"));
		//sAIUser->MessageAlert(msg);
		backColor = MyColor(r, g, b);
	}

	// stroke
	if (style.strokePaint)
	{
		int r = style.stroke.color.c.rgb.red * 255.0;
		int g = style.stroke.color.c.rgb.green * 255.0;
		int b = style.stroke.color.c.rgb.blue * 255.0;

		// =====  give a message ===== 
		//std::stringstream ss;
		//ss << "stroke: " << r << "/" << g << "/" << b;
		//ai::UnicodeString msg;
		//msg.append(ai::UnicodeString(ss.str()));
		//msg.append(ai::UnicodeString("Filled"));
		//sAIUser->MessageAlert(msg);
		foreColor = MyColor(r, g, b);
	}

}

void EmptyPanelPlugin::ParseLayer(AILayerHandle layerHandle)
{
	AIArtHandle artHandle = nil;
	sAIArt->GetFirstArtOfLayer(layerHandle, &artHandle);

	// Get the first art element in the group
	AIArtHandle aArtHandle = nil;
	sAIArt->GetArtFirstChild(artHandle, &aArtHandle);

	do
	{
		ai::UnicodeString artName;
		sAIArt->GetArtName(aArtHandle, artName, nil);
		//sAIArt->SetArtName(aArtHandle, ai::UnicodeString("boundary"));
		//artNames.push_back(artName.as_UTF8());

		APath aPath = ParsePath(aArtHandle);	

		std::vector<std::string> arrayTemp = Split(artName.as_UTF8(), '#');
		std::string whatType = arrayTemp[0];

		
		MyColor fColorRGB;
		MyColor bColorRGB;
		GetForeBackColors(aArtHandle, fColorRGB, bColorRGB);
		

		if ( whatType == "flip" )
		{
			aPath.pathType = FIELD_PATH;
			aPath.FlipOrder();
			this->_regions[_layerCounter]._fieldPaths.push_back(aPath);

		}
		else if ( whatType == "noflip" )
		{
			aPath.pathType = FIELD_PATH;
			this->_regions[_layerCounter]._fieldPaths.push_back(aPath);
		}
		else if ( whatType == "boundary" )
		{
			aPath.pathType = BOUNDARY_PATH;
			this->_regions[_layerCounter]._boundaryPaths.push_back(aPath);

			//int fColor = 7; // black
			//int bColor = 8; // white
			if (arrayTemp.size() == 3)
			{
				int fColor = std::stoi(arrayTemp[1]);
				int bColor = std::stoi(arrayTemp[2]);

				this->_regions[_layerCounter]._boundaryFColors.push_back(fColor);
				this->_regions[_layerCounter]._boundaryBColors.push_back(bColor);
			}
			else
			{
				////////////////////////////////
				// HERE BROOOOOOOOOOOOOOOOOOOOOO
				////////////////////////////////
				this->_regions[_layerCounter]._boundaryFColorsRGB.push_back(fColorRGB);
				this->_regions[_layerCounter]._boundaryBColorsRGB.push_back(bColorRGB);

			}
		}
		//else if ( whatType == "boundary_white" )
		//{
		//	aPath.pathType = BOUNDARY_PATH_WHITE;
		//	this->_regions[_layerCounter]._boundaryPaths.push_back(aPath);
		//}
		else if ( whatType == "seed" ) // not used anymore
		{
			//aPath.pathType = SEED_PATH;
			//this->_regions[_layerCounter]._seedPaths.push_back(aPath);
		}
		else if ( whatType == "focal" )
		{
			aPath.pathType = FOCAL_PATH;
			this->_regions[_layerCounter]._focalPaths.push_back(aPath);
		}
		else if ( whatType == "skeleton" )
		{
			aPath.pathType = SKELETON_LINE;
			this->_regions[_layerCounter]._skeletonLines.push_back(aPath.points);
		}
		else if ( whatType == "streamline" )
		{
			aPath.pathType = STREAM_LINE;
			this->_regions[_layerCounter]._streamLines.push_back(aPath.points);
		}
		else if (whatType == "hole")
		{
			aPath.pathType = HOLE;
			this->_regions[_layerCounter]._holes.push_back(aPath.points);
		}
		//else if ( whatType == "boundary_mst" ) // PHYSICS-PAK
		//{
		//	aPath.pathType = BOUNDARY_MST_PATH;
		//	this->_regions[_layerCounter]._boundaryMSTPath.push_back(aPath);
		//}

		//numArt++;
		sAIArt->GetArtSibling(aArtHandle, &aArtHandle);
	} while (aArtHandle != nil);
}

/*
========================================================================================
Input should be a LAYER
========================================================================================
*/
/*void EmptyPanelPlugin::ParseFieldLayer(AILayerHandle layerHandle)
{
	AIArtHandle artHandle = nil;
	sAIArt->GetFirstArtOfLayer(layerHandle, &artHandle);

	// Get the first art element in the group
	AIArtHandle aArtHandle = nil;
	sAIArt->GetArtFirstChild(artHandle, &aArtHandle);

	// delete this later
	//std::vector<std::string> artNames;

	int numArt = 0;
	do
	{
		ai::UnicodeString artName;
		sAIArt->GetArtName(aArtHandle, artName, nil);
		//artNames.push_back(artName.as_UTF8());

		APath aPath = ParsePath(aArtHandle);
		aPath.pathType = FIELD_PATH;

		if (artName.as_UTF8() == "flip")
		{
			aPath.FlipOrder();
		}

		_paths.push_back(aPath);

		numArt++;
		sAIArt->GetArtSibling(aArtHandle, &aArtHandle);
	} while (aArtHandle != nil);

	std::cout << numArt << "\n";
}*/

/*
========================================================================================
Input should be an ART
========================================================================================
*/
//void EmptyPanelPlugin::ParseShapeLayer(AILayerHandle layerHandle)
//{
	// Get the first art element in the group
	/*AIArtHandle aArtHandle = nil;
	sAIArt->GetArtFirstChild(artHandle, &aArtHandle);

	std::vector<AIArtHandle> artHandles;

	// read all art objects in the layer
	do
	{
		APath aPath = ParsePath(aArtHandle);
		aPath.pathType = SHAPE_PATH;
		_paths.push_back(aPath);

		// Add this art handle
		artHandles.push_back(aArtHandle);

		// Find the next sibling
		sAIArt->GetArtSibling(aArtHandle, &aArtHandle);
	} while (aArtHandle != nil);*/

	/*AIArtHandle artHandle = nil;
	sAIArt->GetFirstArtOfLayer(layerHandle, &artHandle);

	// Get the first art element in the group
	AIArtHandle aArtHandle = nil;
	sAIArt->GetArtFirstChild(artHandle, &aArtHandle);

	// delete this later
	//std::vector<std::string> artNames;

	int numArt = 0;
	do
	{
		ai::UnicodeString artName;
		sAIArt->GetArtName(aArtHandle, artName, nil);
		//artNames.push_back(artName.as_UTF8());

		APath aPath = ParsePath(aArtHandle);
		//aPath.pathType = FIELD_PATH;

		if (artName.as_UTF8() == "boundary")
		{
			aPath.pathType = BOUNDARY_PATH;
		}
		else if (artName.as_UTF8() == "focal")
		{
			aPath.pathType = FOCAL_PATH;
		}
		else if (artName.as_UTF8() == "detail")
		{
			aPath.pathType = DETAIL_PATH;
		}

		_paths.push_back(aPath);

		numArt++;
		sAIArt->GetArtSibling(aArtHandle, &aArtHandle);
	} while (aArtHandle != nil);

	std::cout << numArt << "\n";
}*/


/*
========================================================================================
This function parses a single path art
========================================================================================
*/
APath EmptyPanelPlugin::ParsePath(AIArtHandle artHandle)
{
	APath aPath(true);

	// get art name
	ai::UnicodeString artName;
	sAIArt->GetArtName(artHandle, artName, nil);

	

	// get art type
	short artType = 0;
	sAIArt->GetArtType(artHandle, &artType);
	if (artType == kPathArt)
	{
		// is closed ?
		AIBoolean pathClosed = false;
		sAIPath->GetPathClosed(artHandle, &pathClosed);
		if (!pathClosed) { aPath.isClosed = false; }

		// number of segments
		short segmentCount = 0;
		sAIPath->GetPathSegmentCount(artHandle, &segmentCount);	

		/* Get the path starting point */
		AIPathSegment segment;
		sAIPath->GetPathSegments(artHandle, 0, 1, &segment);
		/* Remember the first segment, in case we have to create an extra segment to close the figure */
		AIPathSegment firstSegment = segment;

		
		// Track the last out point
		// y is negative ?
		AIPathSegment previousSegment = segment;
		aPath.points.push_back(AVector(previousSegment.p.h, -previousSegment.p.v));

		// Loop through each segment
		for (short segmentIndex = 1; segmentIndex < segmentCount; segmentIndex++)
		{
			sAIPath->GetPathSegments(artHandle, segmentIndex, 1, &segment);
			previousSegment = segment;
			// y is negative ?
			aPath.points.push_back(AVector(previousSegment.p.h, -previousSegment.p.v));
		}

		//_paths.push_back(aPath);
		
	}

	return aPath;
}

/*void EmptyPanelPlugin::UpdateMenu(AIBoolean isVisible, ItemType item)
{
	if (item == PANEL)
		sAIMenu->CheckItem (fEmptyPanelPanelMenuItemHandle , isVisible);
	else if (item == CTRL_BAR)
		sAIMenu->CheckItem (fEmptyPanelControlBarMenuItemHandle, isVisible);
}*/

ASErr EmptyPanelPlugin::Notify(AINotifierMessage *message)
{
	AIErr result = kNoErr;
	if (strcmp(message->type, kAIApplicationShutdownNotifier) == 0)
	{
	}
	return result;

	/*AIErr result = kNoErr;
	if(strcmp(message->type, kAIApplicationShutdownNotifier) == 0)
	{
		
		if(fPanel)
		{
		#ifdef WIN_ENV
			
			AIPanelPlatformWindow panelPlatfromWindow = NULL;
			result = sAIPanel->GetPlatformWindow(fPanel, panelPlatfromWindow);

			if(panelPlatfromWindow)
			{
				RemovePropA(panelPlatfromWindow, "TPNL");
				SetWindowLongPtr(panelPlatfromWindow, GWLP_WNDPROC, (LONG_PTR)(fDefaultWindProc));
				DestroyWindow(panelPlatfromWindow);
			}
		#endif

			result = sAIPanel->Destroy(fPanel);
			fPanel = NULL;
		}
		if(fPanelFlyoutMenu)
		{
			result = sAIPanelFlyoutMenu->Destroy(fPanelFlyoutMenu);
			fPanelFlyoutMenu = NULL;
		}
		if (fControlBar != NULL)
		{
#ifdef WIN_ENV
			AIControlBarPlatformWindow ctrlBarPlatformWindow = NULL;
			
			result = sAIControlBar->GetPlatformWindow(fControlBar, ctrlBarPlatformWindow);
					
			if(ctrlBarPlatformWindow)
			{
				
				RemoveProp(ctrlBarPlatformWindow, L"PLUGINPTR");
				SetWindowLongPtr(ctrlBarPlatformWindow, GWLP_WNDPROC, (LONG_PTR)(fDefCtrlBarWndProc));
				DestroyWindow(ctrlBarPlatformWindow);
			}
#endif
			result = sAIControlBar->Destroy(fControlBar);
			fControlBar = NULL;
		}
	}
	return result;*/


}

/*ASErr EmptyPanelPlugin::SetIcon()
{
	   AIErr error = kNoErr;
       ai::AutoBuffer<ai::uint32> iconResID(1), darkIconResID(1);
       iconResID[(size_t)0] = 16200;
       darkIconResID[(size_t)0] = 16200;
       error = sAIPanel->SetIconResourceID( fPanel, iconResID, darkIconResID );
       return error;
}

ASErr EmptyPanelPlugin::GetIcon(AIDataFilter* dataFilterIn, string* buffStrIn, size_t* lenIn)
{
    AIErr error = kNoErr;
    AIDataFilterSuite* sAIDataFilter = NULL;
	error = sSPBasic->AcquireSuite(kAIDataFilterSuite, kAIDataFilterVersion, (const void **)&sAIDataFilter);

    error = sAIDataFilter->LinkDataFilter(NULL, dataFilterIn);
    
    char buf[bufMax];
    
    for(;;)
    {
        size_t count = bufMax;
        const ASErr error = sAIDataFilter->ReadDataFilter(dataFilterIn, buf, &count);
        if (error)
        {
            return error;
        }
        *lenIn += count;
        buffStrIn->append(buf, count);
        if (count != bufMax)
        {
            break;
        }
    }
}*/

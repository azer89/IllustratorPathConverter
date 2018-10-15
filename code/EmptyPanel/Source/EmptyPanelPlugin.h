//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPlugin.h $
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

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
*/

#ifndef __EmptyPanelPlugin_H__
#define __EmptyPanelPlugin_H__

#include "Plugin.hpp"
#include "AIPanel.h"
#include "AIControlBar.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"

#include <vector>

#include "AVector.h"
#include "APath.h"
#include "ARegion.h"
#include "MyColor.h"

// Forward declaration
class PathIO;

Plugin *AllocatePlugin(SPPluginRef pluginRef);
void FixupReload(Plugin *plugin);

enum ItemType {
	PANEL,
	CTRL_BAR
};

class EmptyPanelPlugin : public Plugin
{
public:
	//std::vector<APath> _paths;
	std::vector<ARegion> _regions;
	PathIO* _pathIO;
	int _layerCounter;

public:

	EmptyPanelPlugin(SPPluginRef pluginRef);
	virtual ~EmptyPanelPlugin() {}
	
	virtual ASErr StartupPlugin(SPInterfaceMessage *message); 
	virtual ASErr ShutdownPlugin(SPInterfaceMessage *message); 

	void UpdateMenu(AIBoolean isVisible, ItemType item);
	ASErr GoMenuItem(AIMenuMessage *message);
	ASErr Notify(AINotifierMessage *message);

	FIXUP_VTABLE_EX(EmptyPanelPlugin, Plugin);

	// parse paths
	ASErr ParseDocument();
	void ParseLayer(AILayerHandle layerHandle); // V3
	//void ParseShapeLayer(AILayerHandle layerHandle); // V2
	//void ParseFieldLayer(AILayerHandle layerHandle); // V2
	APath ParsePath(AIArtHandle artHandle); // V1

	void ParseLayerForPatternBrush(AILayerHandle layerHandle);

	void GetForeBackColors(AIArtHandle artHandle, MyColor& foreColor, MyColor& backColor);

private:
	// added by Reza
	AIMenuItemHandle _convertMenuItemHandle;
	//AIMenuItemHandle _patternBrushMenuItemHandle;

};

#endif	// __EmptyPanelPlugin_H__

//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPluginSuites.h $
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

#ifndef __EmptyPanelPluginSuites_H__
#define __EmptyPanelPluginSuites_H__

#include "IllustratorSDK.h"
#include "Suites.hpp"

// AI suite headers
#include "AIArt.h"
#include "AIMatchingArt.h"
#include "AIUnicodeString.h"
#include "AIUser.h"
#include "AIPanel.h"
#include "AIMenu.h"
#include "AIStringFormatUtils.h"
#include "SPBlocks.h"
#include "AIControlBar.h"

/* Added suites - Reza */
#include "AIDrawArt.h"
#include "AIDataFilter.h"
#include "AIActionManager.h"
#include "AIDocument.h"
#include "AiTimer.h"
#include "AIImageOptimization.h"
#include "AIPath.h"

/* Path beautification */
#include "AIBeautifulStrokes.h"
#include "AIArtStyle.h"
#include "AIPathStyle.h"

#include "AIColorConversion.h"




// Suite externs
/*extern "C" AIArtSuite				*sAIArt;
extern "C" AIMatchingArtSuite		*sAIMatchingArt;
extern "C" AIUnicodeStringSuite		*sAIUnicodeString;
extern "C" AIPanelSuite				*sAIPanel;
extern "C" AIPanelFlyoutMenuSuite	*sAIPanelFlyoutMenu;
extern "C" AIMenuSuite				*sAIMenu;
extern "C" AIStringFormatUtilsSuite *sAIStringFormatUtils;
extern "C" SPBlocksSuite			*sSPBlocks;
extern "C" AIControlBarSuite		*sAIControlBar;*/

// Suite externs
extern "C" AIUnicodeStringSuite		*sAIUnicodeString;
extern "C" AIMenuSuite				*sAIMenu;
extern "C" AIStringFormatUtilsSuite *sAIStringFormatUtils;
extern "C" SPBlocksSuite			*sSPBlocks;

//extern "C" AIPanelSuite			*sAIPanel;
//extern "C" AIPanelFlyoutMenuSuite	*sAIPanelFlyoutMenu;
//extern "C" AIControlBarSuite		*sAIControlBar;

/* Added suites - Reza */
extern "C" AIArtSuite				*sAIArt;
extern "C" AIMatchingArtSuite		*sAIMatchingArt;
extern "C" AIDrawArtSuite			*sAIDrawArtSuite;   // reading drawing data
extern "C" AIPathSuite				*sAIPath;		    // reading path
extern "C" AIDocumentSuite			*sAIDocument;	    // what is this I don't know
extern "C" AITimerSuite				*sAITimer;          // for periodic timer
extern "C" AIDataFilterSuite		*sAIDataFilter;     // png
extern "C" AILayerSuite				*sAILayer;		    // handling layers
extern "C" AIImageOptSuite			*sAIImageOpt;		// png
extern "C" AIActionManagerSuite		*sAIActionManager;	// safe file
//extern "C" AISwatchListSuite		*sAISwatchList;     // ???

/* Path beautification */
extern "C" AIBeautifulStrokesSuite	*sAIBeautifulStrokes;
extern "C" AIArtStyleSuite			*sAIArtStyle;
extern "C" AIPathStyleSuite *sAIPathStyle;

extern "C" AICustomColorSuite *sAICustomColor;
extern "C" AIColorConversionSuite *sAIColorConversion;



#endif   // __EmptyPanelPluginSuites_H__

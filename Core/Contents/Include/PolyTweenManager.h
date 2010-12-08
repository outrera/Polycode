/*
 *  PolyTimerManager.h
 *  Poly
 *
 *  Created by Ivan Safrin on 5/18/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
// @package Services

#pragma once
#include "PolyGlobals.h"
#include "PolyTween.h"
#include <vector>

using std::vector;

namespace Polycode {

	class Tween;

	class _PolyExport TweenManager {
		public:
			TweenManager();
			~TweenManager();
			void addTween(Tween *tween);
			void Update();
		
		private:
			vector <Tween*> tweens;
	};
}
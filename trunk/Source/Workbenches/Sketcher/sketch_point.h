/*******************************************************************************
* Copyright (c) 2007, 2008, CerroKai Development
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*     * Redistributions of source code must retain the above copyright
*       notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimer in the
*       documentation and/or other materials provided with the distribution.
*     * Neither the name of CerroKai Development nor the
*       names of its contributors may be used to endorse or promote products
*       derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY CerroKai Development ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL CerroKai Development BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************/


#ifndef __SKETCH_POINT_H__
#define __SKETCH_POINT_H__


/*** Included Header Files ***/
#include "Kernel/wftrl.h"
#include "Sketcher/sketch_feature.h"
#include "Sketcher/sketch_point_actions.h"
#include "Sketcher/sketch_point_controller.h"
#include "Sketcher/sketch_point_modes.h"


/*** Locally Defined Values ***/
#define SKETCHPOINT_CLASSNAME					"Point"
#define SKETCHPOINT_CONSTRUCTION_DEFAULT		true


/*** Namespace Declaration ***/
namespace __WILDCAT_NAMESPACE__ {


/*** Class Predefines ***/
class WCSketch;


/***********************************************~***************************************************/


class WCSketchPoint : public WCSketchFeature {
protected:
	WCVector4									_position;											//!< Coordinates in the plane
	WCGeometricPoint							*_base;												//!< Cooresponding geometric point
private:
	void Initialize(void);																			//!< Private initializer
	//Deny Access
	WCSketchPoint();																				//!< Deny access to default constructor
	WCSketchPoint(const WCSketchPoint& pt);															//!< Deny access to copy constructor
	WCSketchPoint& operator=(const WCSketchPoint &pt);												//!< Deny access to equals operator
public:
	//Constructors and Destructors
	WCSketchPoint(WCSketch *sketch, const std::string &name, const WCVector4 &pos);					//!< Primary constructor
	WCSketchPoint(xercesc::DOMElement *element, WCSerialDictionary *dictionary);					//!< Persistance constructor
	~WCSketchPoint();																				//!< Default destructor
	
	//Member Access Methods
	inline WCGeometricPoint* Base(void)			{ return this->_base; }								//!< Get the geometric point
	inline WCVector4 Position(void) const		{ return this->_position; }							//!< Get the position of the point
	void Set(const WCVector4 &position);															//!< Set the x and y values (by vector)
	void Set(const WPFloat &x, const WPFloat &y);													//!< Set the x and y values (by float)

	//Inherited Methods
	inline std::string RootName(void) const		{ return SKETCHPOINT_CLASSNAME; }					//!< Get the class name
	void ReceiveNotice(WCObjectMsg msg, WCObject *sender);											//!< Receive notice from point or curve
	bool Regenerate(void);																			//!< Validate and rebuild
	void InjectConstraints(WCConstraintPlanner *planner);											//!< Induce effect onto constraint graph
	std::list<WCObject*> DeletionDependencies(void);												//!< Downward dependent objects
	void IsConstruction(const bool state);															//!< Set the construction state
	void OnSelection(const bool fromManager, std::list<WCVisualObject*> objects);					//!< Called on selection
	void OnDeselection(const bool fromManager);														//!< Called on deselection	
	xercesc::DOMElement* Serialize(xercesc::DOMDocument *document, WCSerialDictionary *dict);		//!< Serialize the object
	
	/*** Drawing Modes and Actions ***/
	static WCDrawingMode* ModeCreate(WCSketchWorkbench *wb);										//!< Return a point drawing mode controller
	static WCDrawingMode* ModeEdit(WCSketchPoint *point);											//!< Return a point editing mode controller
	
	static WCActionSketchPointCreate* ActionCreate(WCSketch *sketch, const std::string &pointName,	//!< Primary creation action
												const WCVector4 &pos);
	static WCAction* ActionMove(WCSketchPoint *point, const WCVector4 &pos);						//!< Primary modify action
	
	/*** Friend Functions ***/
	friend std::ostream& operator<<(std::ostream& out, const WCSketchPoint &point);					//!< Overloaded output operator		
};


/***********************************************~***************************************************/


}	   // End Wildcat Namespace
#endif //__SKETCH_POINT_H__

